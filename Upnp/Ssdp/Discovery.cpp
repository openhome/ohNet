#include <Discovery.h>
#include <Ssdp.h>
#include <Debug.h>
#include <Stack.h>

using namespace Zapp;

// SsdpSocketReader

SsdpSocketReader::SsdpSocketReader(const Endpoint& aMulticast, TIpAddress aInterface)
    : SocketUdpMulticast(aMulticast, Stack::InitParams().MsearchTtl(), aInterface)
{
    iReader = new UdpControllerReader(*this);
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
    , iSocket(Endpoint(Ssdp::kMulticastPort, Ssdp::kMulticastAddress), aInterface)
    , iBuffer(iSocket)
    , iReaderRequest(iBuffer)
{
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
            iReaderRequest.Read();
            if (iReaderRequest.Version() == Http::eHttp11) {
                if (iReaderRequest.Uri() == Ssdp::kMethodUri) {
                    const Brx& method = iReaderRequest.Method();
                    if (method == Ssdp::kMethodNotify) {
                        LOG(kSsdpMulticast, "SSDP Multicast      Notify\n");
                        iLock.Wait();
                        TUint count = iNotifyHandlers.size();
                        for (TUint i = 0; i<count; i++) {
                            Notify(*(iNotifyHandlers[i].iHandler));
                        }
                        iLock.Signal();
                    }
                    else if (method == Ssdp::kMethodMsearch) {
                        LOG(kSsdpMulticast, "SSDP Multicast      Msearch\n");
                        iLock.Wait();
                        TUint count = iMsearchHandlers.size();
                        for (TUint i = 0; i<count; i++) {
                            Msearch(*(iMsearchHandlers[i].iHandler));
                        }
                        iLock.Signal();
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
    iNotifyHandlers.clear();
    iMsearchHandlers.clear();
    iReaderRequest.Interrupt();
    Join();
}

TInt SsdpListenerMulticast::AddNotifyHandler(ISsdpNotifyHandler* aNotifyHandler)
{
    ASSERT(aNotifyHandler != NULL);
    iLock.Wait();
    TInt id = iNextHandlerId;
    NotifyHandler handler(aNotifyHandler, iNextHandlerId);
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
    MsearchHandler handler(aMsearchHandler, iNextHandlerId);
    iMsearchHandlers.push_back(handler);
    iNextHandlerId++;
    iLock.Signal();
    return id;
}

void SsdpListenerMulticast::RemoveNotifyHandler(TInt aHandlerId)
{
    iLock.Wait();
    TUint count = iNotifyHandlers.size();
    for (TUint i = 0; i<count; i++) {
        if (iNotifyHandlers[i].iId == aHandlerId) {
            iNotifyHandlers.erase(iNotifyHandlers.begin() + i);
        }
    }
    iLock.Signal();
}

void SsdpListenerMulticast::RemoveMsearchHandler(TInt aHandlerId)
{
    iLock.Wait();
    TUint count = iMsearchHandlers.size();
    for (TUint i = 0; i<count; i++) {
        if (iMsearchHandlers[i].iId == aHandlerId) {
            iMsearchHandlers.erase(iMsearchHandlers.begin() + i);
            break;
        }
    }
    iLock.Signal();
}

TIpAddress SsdpListenerMulticast::Interface() const
{
    return iInterface;
}

// SsdpListenerUnicast

// Writes request to SSDP multicast address and listens for unicast responses
//
// Reader chain: Multicast Socket -> Srs -> ReaderHttpRequest -> this -> aMsearch
//                                                                    -> aNotify

SsdpListenerUnicast::SsdpListenerUnicast(ISsdpNotifyHandler& aNotifyHandler, TIpAddress aInterface)
    : iNotifyHandler(aNotifyHandler)
    , iSocket(Endpoint(Ssdp::kMulticastPort, Ssdp::kMulticastAddress),
              Stack::InitParams().MsearchTtl(),
              aInterface)
    , iWriteBuffer(iSocket)
    , iWriter(iWriteBuffer)
    , iReadBuffer(iSocket)
    , iReaderResponse(iReadBuffer)
{
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
    iSocket.ReadInterrupt();
    Join();
}

void SsdpListenerUnicast::Run()
{
    LOG(kSsdpUnicast, "SSDP Unicast        Run\n");
    Signal();
    for (;;) {
        iReaderResponse.Flush();

        try {
            iReaderResponse.Read();

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
