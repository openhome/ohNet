#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

EXCEPTION(ProtocolRedirect); // FIXME - unusual to have an exception declared in a .cpp.  Is this deliberate here?

// Protocol

Protocol::Protocol(Environment& aEnv, IProtocolManager& aManager)
    : iEnv(aEnv)
    , iManager(aManager)
    , iEnabled(true)
{
}

TBool Protocol::Stream(const Brx& aUri)
{
    LOG(kMedia, "Protocol::Stream\n");
    return iManager.Stream(aUri);
}

TBool Protocol::Redirect(const Brx& aUri)
{
    LOG(kMedia, "Protocol::Redirect\n");
    return iManager.Redirect(aUri);
}

TUint Protocol::Start(TUint64 aTotalBytes, ILiveStreamer* aLiveStreamer, IRestreamer* aRestreamer)
{
    LOG(kMedia, "Protocol::Start\n");
    return iManager.Start(aTotalBytes, aLiveStreamer, aRestreamer);
}

void Protocol::OutputData(const Brx& aAudio)
{
    LOG(kMedia, "Protocol::OutputData\n");
    iManager.OutputData(aAudio);
}

void Protocol::OutputMetadata(const Brx& aMetadata)
{
    LOG(kMedia, "Protocol::OutputMetadata\n");
    iManager.OutputMetadata(aMetadata);
}

void Protocol::OutputFlush()
{
    LOG(kMedia, "Protocol::OutputFlush\n");
    iManager.OutputFlush();
}

void Protocol::End()
{
    LOG(kMedia, "Protocol::End\n");
    iManager.End();
}

void Protocol::Lock()
{
    iManager.Lock();
}

void Protocol::Unlock()
{
    iManager.Unlock();
}

/*TBool Protocol::Restream(TUint64 aOffset)
{
    ASSERTS();
    return false;
}*/

// Returns true if protocol enabled
TBool Protocol::DoStream(const Brx& aUri)
{
    LOG(kMedia, ">Protocol::DoStream\n");

    if (!iEnabled) {
        LOG(kMedia, "<Protocol::DoStream - disabled\n");
        return false;
    }
    
    try {
        iUri.Replace(aUri);
    }
    catch (UriError&) {
        LOG(kMedia, "<Protocol::DoStream - uri error\n");
        return true;
    }

    iEnabled = false;
    try {
        Stream();
        iEnabled = true;
    }
    catch (...) {
        iEnabled = true;
        LOG(kMedia, "<Protocol::DoStream - exception\n");
        throw;
    }    

    LOG(kMedia, "<Protocol::DoStream\n");
    return true;
}
    
/*TBool Protocol::DoRestream(TUint64 aOffset)
{
    LOG(kMedia, "Protocol::DoRestream\n");
    return Restream(aOffset);
}*/
    
void Protocol::DoInterrupt(TBool /*aInterrupt*/)
{
}

const OpenHome::Uri& Protocol::Uri() const
{
    return iUri;
}


// ProtocolNetwork	

ProtocolNetwork::ProtocolNetwork(Environment& aEnv, IProtocolManager& aManager)
    : Protocol(aEnv, aManager)
    , iReaderBuf(iTcpClient)
    , iWriterBuf(iTcpClient)
    , iSocketIsOpen(false)
{
}

TBool ProtocolNetwork::Connect(TUint aDefaultPort)
{
    LOG(kMedia, ">ProtocolNetwork::Connect\n");

    Endpoint endpoint;
    try {
        const OpenHome::Uri& uri = Uri();
        endpoint.SetAddress(uri.Host());
        TInt port = uri.Port();
        if (port == -1) {
            port = (TInt)aDefaultPort;
        }
        endpoint.SetPort(port);
    }
    catch (NetworkError&) {
        LOG(kMedia, "<Protocol::Connect error setting address and port\n");
        return false;
    }

    Open();
    try {        
        iTcpClient.Connect(endpoint, kConnectTimeoutMs);
    }
    catch (NetworkError&) {
        Close();
        LOG(kMedia, "<ProtocolNetwork::Connect error connecting\n");
        return false;
    }

    LOG(kMedia, "<Protocol::Connect\n");
    return true;
}

// Returns true if protocol enabled
TBool ProtocolNetwork::DoStream(const Brx& aUri)
{
    try {
        if (Protocol::DoStream(aUri)) {
            Close();
            return true;
        }
        return false;
    }
    catch (...) {
        Close();
        throw;
    }
}
    
void ProtocolNetwork::DoInterrupt(TBool aInterrupt)
{
    LOG(kMedia, ">ProtocolNetwork::DoInterrupt\n");

    Protocol::DoInterrupt(aInterrupt);
    Lock();
    TBool open = iSocketIsOpen;
    Unlock();
    if (open) {
        iTcpClient.Interrupt(aInterrupt);
    }

    LOG(kMedia, "<ProtocolNetwork::DoInterrupt\n");
}

void ProtocolNetwork::Open()
{
    LOG(kMedia, "ProtocolNetwork::Open\n");

    iTcpClient.Open(iEnv);
    Lock();
    ASSERT(!iSocketIsOpen);
    iSocketIsOpen = true;
    Unlock();
}
    
void ProtocolNetwork::Close()
{
    LOG(kMedia, "ProtocolNetwork::Close\n");

    Lock();
    TBool open = iSocketIsOpen;
    iSocketIsOpen = false;
    Unlock();
    if (open) {
        iTcpClient.Close();
    }
}


// ProtocolManager

ProtocolManager::ProtocolManager(ISupply& aSupply)
    : iSupply(aSupply)
    , iMutex("PMAN")
    , iProtocol(0)
    , iStarted(0)
    , iNextStreamId(kStreamIdInvalid + 1)
{
}

void ProtocolManager::Add(Protocol* aProtocol)
{
	LOG(kMedia, "ProtocolManager::Add\n");
	iProtocols.push_back(aProtocol);
}

// Standard functions called from the supply

void ProtocolManager::DoStream(const Brx& aUri)
{
    LOG(kMedia, ">ProtocolManager::DoStream [");
    LOG(kMedia, aUri);
    LOG(kMedia, "]\n");

    Lock();
    iProtocol = NULL;
    iStarted = NULL;
    Unlock();

    Stream(aUri);
    
    LOG(kMedia, "<ProtocolManager::DoStream [");
    LOG(kMedia, aUri);
    LOG(kMedia, "]\n");
}

// restream the last protocol that started (iStarted)

/*TBool ProtocolManager::DoRestream(TUint64 aOffset)
{
    LOG(kMedia, ">ProtocolManager::DoRestream offset %lld\n", aOffset);
    
    TBool success = false;
    Lock();
    Protocol* protocol = iStarted;
    Unlock();
    ASSERT(protocol != 0);
    try {
        success = protocol->DoRestream(aOffset);
    }
    catch (ProtocolRedirect&) {
        ASSERTS();
    }
    
    LOG(kMedia, "<ProtocolManager::DoRestream\n");
    return success;
}*/

// interrupt the current point in the stack (iProtocol)
void ProtocolManager::DoInterrupt(TBool aInterrupt)
{
    LOG(kMedia, ">ProtocolManager::DoInterrupt\n");

    Lock();
    Protocol* protocol = iProtocol;
    Unlock();
    if (protocol != NULL) {
        protocol->DoInterrupt(aInterrupt);
    }
        
    LOG(kMedia, "<ProtocolManager::DoInterrupt\n");
}

// Recursive functions called from Protocol Modules
    
TBool ProtocolManager::Stream(const Brx& aUri)
{
    LOG(kMedia, "ProtocolManager::Stream [");
    LOG(kMedia, aUri);
    LOG(kMedia, "]\n");
    
    if (!SetUri(aUri)) {
        return (false);
    }

    Lock();
    iStarted = NULL;
    Protocol* last = iProtocol;
    Unlock();
    TUint index = 0;
    TUint count = iProtocols.size(); 
    while (index < count) {
        Protocol* protocol = iProtocols[index++];
        Lock();
        iProtocol = protocol;
        Unlock();
        try {
            if (protocol->DoStream(iUri)) {
                Lock();
                Protocol* protocol = iStarted;
                Unlock();
                if (protocol != NULL) { 
                    break;
                }
            }
        }
        catch (ProtocolRedirect&) {
            /* iUri has been replaced with the redirection uri
               start looking through all the protocols again
               trying to stream from this new uri */
            index = 0;
        }
    }
    
    Lock();
    iProtocol = last;
    // iStarted indicates that some protocol in the stack started playing a track
    TBool result = (iStarted != NULL);
    Unlock();

    return result;
}

TBool ProtocolManager::Redirect(const Brx& aUri)
{
    LOG(kMedia, "ProtocolManager::Redirect\n");

    OpenHome::Uri uri;
    try {
        uri.Replace(aUri);
    }
    catch (UriError&) {
        // invalid uri, check to see if it makes sense as a relative uri
        try {
            uri.Replace(iUri, aUri);
        }
        catch (UriError&) {
            return false;
        }
    }

    if (!SetUri(uri.AbsoluteUri())) {
        return false;
    }

    THROW(ProtocolRedirect);
}

TBool ProtocolManager::SetUri(const Brx& aUri)
{
    try {
        iUri.ReplaceThrow(aUri);
    }
    catch (BufferOverflow&) {
        return false;
    }
    
    return true;
}

const Brx& ProtocolManager::Uri() const
{
    return iUri;
}

TUint ProtocolManager::Start(TUint64 aTotalBytes, ILiveStreamer* aLiveStreamer, IRestreamer* aRestreamer)
{
    Lock();
    iStarted = iProtocol;
    TUint streamId = iNextStreamId;
    iNextStreamId += 1;
    Unlock();
    iSupply.Start(aTotalBytes, aLiveStreamer, aRestreamer, streamId);
    return streamId;
}

void ProtocolManager::OutputData(const Brx& aAudio)
{
    iSupply.OutputData(aAudio);
}

void ProtocolManager::OutputMetadata(const Brx& aMetadata)
{
    iSupply.OutputMetadata(aMetadata);
}

void ProtocolManager::OutputFlush()
{
    iSupply.OutputFlush();
}

void ProtocolManager::End()
{
    iSupply.End();
}

void ProtocolManager::Lock()
{
    iMutex.Wait();
}

void ProtocolManager::Unlock()
{
    iMutex.Signal();
}

ProtocolManager::~ProtocolManager()
{
    const TUint count = iProtocols.size(); 
    for (TUint i = 0; i < count; i++) {
        delete iProtocols[i];
    }
}
