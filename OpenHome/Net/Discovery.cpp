#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Private/Stack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// SsdpSocketReader

SsdpSocketReader::SsdpSocketReader(TIpAddress aInterface, const Endpoint& aMulticast)
    : SocketUdpMulticast(aInterface, aMulticast)
{
    SetTtl(Stack::InitParams().MsearchTtl()); 
    iReader = new UdpReader(*this);
}

SsdpSocketReader::~SsdpSocketReader()
{
    delete iReader;
}

Endpoint SsdpSocketReader::Sender() const
{
    return iReader->Sender();
}

void SsdpSocketReader::Read(Bwx& aBuffer)
{
    iReader->Read(aBuffer);
}

void SsdpSocketReader::ReadFlush()
{
    iReader->ReadFlush();
}

void SsdpSocketReader::ReadInterrupt()
{
    iReader->ReadInterrupt();
}

// SsdpListener

SsdpListener::SsdpListener()
    : Thread("SSDP", kPriority)
{
}

// SsdpListenerMulticast

// Reader chain: Multicast Socket -> Srs -> ReaderHttpRequest -> this -> aMsearch
//                                                                    -> aNotify

SsdpListenerMulticast::SsdpListenerMulticast(TIpAddress aInterface)
    : iLock("LMCM")
    , iNextHandlerId(0)
    , iInterface(aInterface)
    , iSocket(aInterface, Endpoint(Ssdp::kMulticastPort, Ssdp::kMulticastAddress))
    , iBuffer(iSocket)
    , iReaderRequest(iBuffer)
{
    try
    {
        iSocket.SetRecvBufBytes(kRecvBufBytes);
    }
    catch ( NetworkError ) {}
    
    iReaderRequest.AddHeader(iHeaderHost);
    iReaderRequest.AddHeader(iHeaderCacheControl);
    iReaderRequest.AddHeader(iHeaderLocation);
    iReaderRequest.AddHeader(iHeaderNt);
    iReaderRequest.AddHeader(iHeaderNts);
    iReaderRequest.AddHeader(iHeaderServer);
    iReaderRequest.AddHeader(iHeaderUsn);
    iReaderRequest.AddHeader(iHeaderMan);
    iReaderRequest.AddHeader(iHeaderMx);
    iReaderRequest.AddHeader(iHeaderSt);
    iReaderRequest.AddMethod(Ssdp::kMethodNotify);
    iReaderRequest.AddMethod(Ssdp::kMethodMsearch);
}

void SsdpListenerMulticast::Run()
{
    Signal();
    for (;;) {
        iReaderRequest.Flush();

        try {
            LOG(kSsdpMulticast, "SSDP Multicast      Listen\n");
            iReaderRequest.Read(0);
            if (iReaderRequest.Version() == Http::eHttp11) {
                if (iReaderRequest.Uri() == Ssdp::kMethodUri) {
                    const Brx& method = iReaderRequest.Method();
                    if (method == Ssdp::kMethodNotify) {
                        LOG(kSsdpMulticast, "SSDP Multicast      Notify\n");
                        iLock.Wait();
                        EraseDisabled(iNotifyHandlers);
                        VectorNotifyHandler callbacks;
                        TUint count = (TUint)iNotifyHandlers.size();
                        for (TUint i=0; i<count; i++) {
                            callbacks.push_back(iNotifyHandlers[i]);
                        }
                        iLock.Signal();
                        for (TUint i = 0; i<count; i++) {
                            Notify(*(callbacks[i]));
                        }
                    }
                    else if (method == Ssdp::kMethodMsearch) {
                        LOG(kSsdpMulticast, "SSDP Multicast      Msearch\n");
                        iLock.Wait();
                        EraseDisabled(iMsearchHandlers);
                        VectorMsearchHandler callbacks;
                        TUint count = (TUint)iMsearchHandlers.size();
                        for (TUint i=0; i<count; i++) {
                            callbacks.push_back(iMsearchHandlers[i]);
                        }
                        iLock.Signal();
                        for (TUint i = 0; i<count; i++) {
                            Msearch(*(callbacks[i]));
                        }
                    }
                }
            }
        }
        catch (HttpError&) {
            LOG2(kSsdpMulticast, kError, "SSDP Multicast      HttpError\n");
        }
        catch (WriterError&) {
            LOG2(kSsdpMulticast, kError, "SSDP Multicast      WriterError\n");
        }
        catch (ReaderError&) {
            LOG2(kSsdpMulticast, kError, "SSDP Multicast      ReaderError\n");
            break;
        }
    }
}

void SsdpListenerMulticast::Msearch(MsearchHandler& aHandler)
{
    AutoMutex a(aHandler.Mutex());
    if (!aHandler.IsDisabled()) {
        Msearch(*(aHandler.Handler()));
    }
}

void SsdpListenerMulticast::Msearch(ISsdpMsearchHandler& aMsearchHandler)
{
    TUint mx = iHeaderMx.Mx();

    if (mx && iHeaderHost.Received() && iHeaderMan.Received() && iHeaderSt.Received()) {
        switch(iHeaderSt.Target()) {
        case eSsdpRoot:
            LOG(kSsdpMulticast, "SSDP Multicast      Msearch Root\n");
            aMsearchHandler.SsdpSearchRoot(iSocket.Sender(), mx);
            return;
        case eSsdpUuid:
            LOG(kSsdpMulticast, "SSDP Multicast      Msearch Uuid\n");
            aMsearchHandler.SsdpSearchUuid(iSocket.Sender(), mx, iHeaderSt.Uuid());
            return;
        case eSsdpDeviceType:
            LOG(kSsdpMulticast, "SSDP Multicast      Msearch Device Type\n");
            aMsearchHandler.SsdpSearchDeviceType(iSocket.Sender(), mx, iHeaderSt.Domain(), iHeaderSt.Type(), iHeaderSt.Version());
            return;
        case eSsdpServiceType:
            LOG(kSsdpMulticast, "SSDP Multicast      Msearch Service Type\n");
            aMsearchHandler.SsdpSearchServiceType(iSocket.Sender(), mx, iHeaderSt.Domain(), iHeaderSt.Type(), iHeaderSt.Version());
            return;
        case eSsdpAll:
            LOG(kSsdpMulticast, "SSDP Multicast      Msearch All\n");
            aMsearchHandler.SsdpSearchAll(iSocket.Sender(), mx);
            return;
        default:
            break;
        }
    }
}

void SsdpListenerMulticast::Notify(NotifyHandler& aHandler)
{
    AutoMutex a(aHandler.Mutex());
    if (!aHandler.IsDisabled()) {
        Notify(*(aHandler.Handler()));
    }
}

void SsdpListenerMulticast::Notify(ISsdpNotifyHandler& aNotifyHandler)
{
    if (iHeaderNts.Received()) {
        if (iHeaderNts.Alive()) {
            TUint maxage = iHeaderCacheControl.MaxAge();
            if (maxage && iHeaderHost.Received() && iHeaderLocation.Received() && iHeaderServer.Received() && iHeaderNt.Received() && iHeaderUsn.Received()) {
                switch(iHeaderNt.Target()) {
                case eSsdpRoot:
                    if (iHeaderUsn.Target() == eSsdpRoot) {
                        LOG(kSsdpMulticast, "SSDP Multicast      Notify Alive Root\n");
                        aNotifyHandler.SsdpNotifyRootAlive(iHeaderUsn.Uuid(), iHeaderLocation.Location(), maxage);
                        return;
                    }
                    break;
                case eSsdpUuid:
                    if (iHeaderUsn.Target() == eSsdpUuid) {
                        if (iHeaderNt.Uuid() == iHeaderUsn.Uuid()) {
                            LOG(kSsdpMulticast, "SSDP Multicast      Notify Alive Uuid\n");
                            aNotifyHandler.SsdpNotifyUuidAlive(iHeaderUsn.Uuid(), iHeaderLocation.Location(), maxage);
                            return;
                        }
                    }
                    break;
                case eSsdpDeviceType:
                    if (iHeaderUsn.Target() == eSsdpDeviceType) {
                        if (iHeaderNt.Domain() == iHeaderUsn.Domain()) {
                            if (iHeaderNt.Type() == iHeaderUsn.Type()) {
                                if (iHeaderNt.Version() == iHeaderUsn.Version()) {
                                    LOG(kSsdpMulticast, "SSDP Multicast      Notify Alive Device Type\n");
                                    aNotifyHandler.SsdpNotifyDeviceTypeAlive(iHeaderUsn.Uuid(), iHeaderNt.Domain(), iHeaderNt.Type(), iHeaderNt.Version(), iHeaderLocation.Location(), maxage);
                                    return;
                                }
                            }
                        }
                    }
                    break;
                case eSsdpServiceType:
                    if (iHeaderUsn.Target() == eSsdpServiceType) {
                        if (iHeaderNt.Domain() == iHeaderUsn.Domain()) {
                            if (iHeaderNt.Type() == iHeaderUsn.Type()) {
                                if (iHeaderNt.Version() == iHeaderUsn.Version()) {
                                    LOG(kSsdpMulticast, "SSDP Multicast      Notify Alive Service Type\n");
                                    aNotifyHandler.SsdpNotifyServiceTypeAlive(iHeaderUsn.Uuid(), iHeaderNt.Domain(), iHeaderNt.Type(), iHeaderNt.Version(), iHeaderLocation.Location(), maxage);
                                    return;
                                }
                            }
                        }
                    }
                    break;
                default:
                    break;
                }
            }
        }
        else {
            if (iHeaderHost.Received() && iHeaderNt.Received() && iHeaderUsn.Received()) {
                switch(iHeaderNt.Target()) {
                case eSsdpRoot:
                    if (iHeaderUsn.Target() == eSsdpRoot) {
                        LOG(kSsdpMulticast, "SSDP Multicast      Notify ByeBye Root\n");
                        aNotifyHandler.SsdpNotifyRootByeBye(iHeaderUsn.Uuid());
                        return;
                    }
                    break;
                case eSsdpUuid:
                    if (iHeaderUsn.Target() == eSsdpUuid) {
                        if (iHeaderNt.Uuid() == iHeaderUsn.Uuid()) {
                            LOG(kSsdpMulticast, "SSDP Multicast      Notify ByeBye Uuid\n");
                            aNotifyHandler.SsdpNotifyUuidByeBye(iHeaderUsn.Uuid());
                            return;
                        }
                    }
                    break;
                case eSsdpDeviceType:
                    if (iHeaderUsn.Target() == eSsdpDeviceType) {
                        if (iHeaderNt.Domain() == iHeaderUsn.Domain()) {
                            if (iHeaderNt.Type() == iHeaderUsn.Type()) {
                                if (iHeaderNt.Version() == iHeaderUsn.Version()) {
                                    LOG(kSsdpMulticast, "SSDP Multicast      Notify ByeBye Device Type\n");
                                    aNotifyHandler.SsdpNotifyDeviceTypeByeBye(iHeaderUsn.Uuid(), iHeaderNt.Domain(), iHeaderNt.Type(), iHeaderNt.Version());
                                    return;
                                }
                            }
                        }
                    }
                    break;
                case eSsdpServiceType:
                    if (iHeaderUsn.Target() == eSsdpServiceType) {
                        if (iHeaderNt.Domain() == iHeaderUsn.Domain()) {
                            if (iHeaderNt.Type() == iHeaderUsn.Type()) {
                                if (iHeaderNt.Version() == iHeaderUsn.Version()) {
                                    LOG(kSsdpMulticast, "SSDP Multicast      Notify ByeBye Service Type\n");
                                    aNotifyHandler.SsdpNotifyServiceTypeByeBye(iHeaderUsn.Uuid(), iHeaderNt.Domain(), iHeaderNt.Type(), iHeaderNt.Version());
                                    return;
                                }
                            }
                        }
                    }
                default:
                    break;
                }
            }
        }
    }
}

SsdpListenerMulticast::~SsdpListenerMulticast()
{
    LOG(kSsdpMulticast, "SSDP Multicast      Destructor\n");
    EraseDisabled(iNotifyHandlers);
    ASSERT(iNotifyHandlers.size() == 0);
    EraseDisabled(iMsearchHandlers);
    ASSERT(iMsearchHandlers.size() == 0);
    iReaderRequest.Interrupt();
    Join();
}

TInt SsdpListenerMulticast::AddNotifyHandler(ISsdpNotifyHandler* aNotifyHandler)
{
    ASSERT(aNotifyHandler != NULL);
    iLock.Wait();
    TInt id = iNextHandlerId;
    NotifyHandler* handler = new NotifyHandler(aNotifyHandler, iNextHandlerId);
    iNotifyHandlers.push_back(handler);
    iNextHandlerId++;
    iLock.Signal();
    return id;
}

TInt SsdpListenerMulticast::AddMsearchHandler(ISsdpMsearchHandler* aMsearchHandler)
{
    ASSERT(aMsearchHandler != NULL);
    iLock.Wait();
    TInt id = iNextHandlerId;
    MsearchHandler* handler = new MsearchHandler(aMsearchHandler, iNextHandlerId);
    iMsearchHandlers.push_back(handler);
    iNextHandlerId++;
    iLock.Signal();
    return id;
}

void SsdpListenerMulticast::RemoveNotifyHandler(TInt aHandlerId)
{
    iLock.Wait();
    TUint count = (TUint)iNotifyHandlers.size();
    for (TUint i = 0; i<count; i++) {
        NotifyHandler* nh = iNotifyHandlers[i];
        if (nh->Id() == aHandlerId) {
            nh->Lock();
            nh->Disable();
            nh->Unlock();
            break;
        }
    }
    iLock.Signal();
}

void SsdpListenerMulticast::RemoveMsearchHandler(TInt aHandlerId)
{
    iLock.Wait();
    TUint count = (TUint)iMsearchHandlers.size();
    for (TUint i = 0; i<count; i++) {
        MsearchHandler* mh = iMsearchHandlers[i];
        if (mh->Id() == aHandlerId) {
            mh->Lock();
            mh->Disable();
            mh->Unlock();
            break;
        }
    }
    iLock.Signal();
}

TIpAddress SsdpListenerMulticast::Interface() const
{
    return iInterface;
}

void SsdpListenerMulticast::EraseDisabled(VectorNotifyHandler& aVector)
{
    VectorNotifyHandler::iterator it = aVector.begin();
    while (it != aVector.end()) {
        NotifyHandler* handler = reinterpret_cast<NotifyHandler*>(*it);
        handler->Lock();
        if (handler->IsDisabled()) {
            handler->Unlock();
            delete handler;
            it = aVector.erase(it);
        }
        else {
            handler->Unlock();
            it++;
        }
    }
}

void SsdpListenerMulticast::EraseDisabled(VectorMsearchHandler& aVector)
{
    VectorMsearchHandler::iterator it = aVector.begin();
    while (it != aVector.end()) {
        MsearchHandler* handler = reinterpret_cast<MsearchHandler*>(*it);
        handler->Lock();
        if (handler->IsDisabled()) {
            handler->Unlock();
            delete handler;
            it = aVector.erase(it);
        }
        else {
            handler->Unlock();
            it++;
        }
    }
}


// SsdpListenerUnicast

// Writes request to SSDP multicast address and listens for unicast responses
//
// Reader chain: Multicast Socket -> Srs -> ReaderHttpRequest -> this -> aMsearch
//                                                                    -> aNotify

SsdpListenerUnicast::SsdpListenerUnicast(ISsdpNotifyHandler& aNotifyHandler, TIpAddress aInterface)
    : iNotifyHandler(aNotifyHandler)
    , iSocket(0, aInterface)
    , iSocketWriter(iSocket, Endpoint(Ssdp::kMulticastPort, Ssdp::kMulticastAddress))
    , iSocketReader(iSocket)
    , iWriteBuffer(iSocketWriter)
    , iWriter(iWriteBuffer)
    , iReadBuffer(iSocketReader)
    , iReaderResponse(iReadBuffer)
{
    iSocket.SetTtl(Stack::InitParams().MsearchTtl());
    try
    {
        iSocket.SetRecvBufBytes(kRecvBufBytes);
    }
    catch ( NetworkError ) {}
    
    iReaderResponse.AddHeader(iHeaderCacheControl);
    iReaderResponse.AddHeader(iHeaderExt);
    iReaderResponse.AddHeader(iHeaderLocation);
    iReaderResponse.AddHeader(iHeaderServer);
    iReaderResponse.AddHeader(iHeaderSt);
    iReaderResponse.AddHeader(iHeaderUsn);
}

SsdpListenerUnicast::~SsdpListenerUnicast()
{
    LOG(kSsdpUnicast, "SSDP Unicast        Destructor\n");
    iSocketReader.ReadInterrupt();
    Join();
}

void SsdpListenerUnicast::Run()
{
    LOG(kSsdpUnicast, "SSDP Unicast        Run\n");
    Signal();
    for (;;) {
        iReaderResponse.Flush();

        try {
            iReaderResponse.Read(0);

            if (iReaderResponse.Version() == Http::eHttp11) {
                if (iReaderResponse.Status() == HttpStatus::kOk) {
                    TUint maxage = iHeaderCacheControl.MaxAge();
                    if (maxage && iHeaderExt.Received() && iHeaderLocation.Received() && iHeaderServer.Received() && iHeaderSt.Received() && iHeaderUsn.Received()) {
                        switch(iHeaderSt.Target()) {
                        case eSsdpRoot:
                            if (iHeaderUsn.Target() == eSsdpRoot) {
                                LOG(kSsdpUnicast, "SSDP Unicast        Notify Alive Root\n");
                                iNotifyHandler.SsdpNotifyRootAlive(iHeaderUsn.Uuid(), iHeaderLocation.Location(), maxage);
                            }
                            break;
                        case eSsdpUuid:
                            if (iHeaderUsn.Target() == eSsdpUuid) {
                                if (iHeaderSt.Uuid() == iHeaderUsn.Uuid()) {
                                    LOG(kSsdpUnicast, "SSDP Unicast        Notify Alive Uuid\n");
                                    iNotifyHandler.SsdpNotifyUuidAlive(iHeaderUsn.Uuid(), iHeaderLocation.Location(), maxage);
                                }
                            }
                            break;
                        case eSsdpDeviceType:
                            if (iHeaderUsn.Target() == eSsdpDeviceType) {
                                if (iHeaderSt.Domain() == iHeaderUsn.Domain()) {
                                    if (iHeaderSt.Type() == iHeaderUsn.Type()) {
                                        if (iHeaderSt.Version() == iHeaderUsn.Version()) {
                                            LOG(kSsdpUnicast, "SSDP Unicast        Notify Alive Device Type\n");
                                            iNotifyHandler.SsdpNotifyDeviceTypeAlive(iHeaderUsn.Uuid(), iHeaderSt.Domain(), iHeaderSt.Type(), iHeaderSt.Version(), iHeaderLocation.Location(), maxage);
                                        }
                                    }
                                }
                            }
                            break;
                        case eSsdpServiceType:
                            if (iHeaderUsn.Target() == eSsdpServiceType) {
                                if (iHeaderSt.Domain() == iHeaderUsn.Domain()) {
                                    if (iHeaderSt.Type() == iHeaderUsn.Type()) {
                                        if (iHeaderSt.Version() == iHeaderUsn.Version()) {
                                            LOG(kSsdpUnicast, "SSDP Unicast        Notify Alive Service Type\n");
                                            iNotifyHandler.SsdpNotifyServiceTypeAlive(iHeaderUsn.Uuid(), iHeaderSt.Domain(), iHeaderSt.Type(), iHeaderSt.Version(), iHeaderLocation.Location(), maxage);
                                        }
                                    }
                                }
                            }
                        default:
                            break;
                        }
                    }
                }
            }
        }
        catch (HttpError&) {
            LOG2(kSsdpUnicast, kError, "SSDP Unicast        HttpError\n");
        }
        catch (ReaderError&) {
            LOG2(kSsdpUnicast, kError, "SSDP Unicast        ReaderError\n");
            break;
        }
        catch (WriterError&) {
            LOG2(kSsdpUnicast, kError, "SSDP Unicast        WriterError\n");
        }
    }
}

void SsdpListenerUnicast::MsearchRoot()
{
    iWriter.MsearchRoot(MsearchDurationSeconds());
}

void SsdpListenerUnicast::MsearchUuid(const Brx& aUuid)
{
    iWriter.MsearchUuid(aUuid, MsearchDurationSeconds());
}

void SsdpListenerUnicast::MsearchDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    iWriter.MsearchDeviceType(aDomain, aType, aVersion, MsearchDurationSeconds());
}

void SsdpListenerUnicast::MsearchServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    iWriter.MsearchServiceType(aDomain, aType, aVersion, MsearchDurationSeconds());
}

void SsdpListenerUnicast::MsearchAll()
{
    iWriter.MsearchAll(MsearchDurationSeconds());
}

TUint SsdpListenerUnicast::MsearchDurationSeconds() const
{
    return Stack::InitParams().MsearchTimeSecs();
}
