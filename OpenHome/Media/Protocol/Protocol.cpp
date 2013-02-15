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

TBool Protocol::REVIEW_ME_Stream(const Brx& aUri)
{
    LOG(kMedia, "Protocol::Stream\n");
    return iManager.REVIEW_ME_Stream(aUri);
}

TBool Protocol::REVIEW_ME_Redirect(const Brx& aUri)
{
    LOG(kMedia, "Protocol::Redirect\n");
    return iManager.REVIEW_ME_Redirect(aUri);
}

TUint Protocol::REVIEW_ME_Start(TUint64 aTotalBytes, ILiveStreamer* aLiveStreamer, IRestreamer* aRestreamer)
{
    LOG(kMedia, "Protocol::Start\n");
    return iManager.REVIEW_ME_Start(aTotalBytes, aLiveStreamer, aRestreamer);
}

void Protocol::REVIEW_ME_OutputData(const Brx& aAudio)
{
    LOG(kMedia, "Protocol::OutputData\n");
    iManager.REVIEW_ME_OutputData(aAudio);
}

void Protocol::REVIEW_ME_OutputMetadata(const Brx& aMetadata)
{
    LOG(kMedia, "Protocol::OutputMetadata\n");
    iManager.REVIEW_ME_OutputMetadata(aMetadata);
}

void Protocol::REVIEW_ME_OutputFlush()
{
    LOG(kMedia, "Protocol::OutputFlush\n");
    iManager.REVIEW_ME_OutputFlush();
}

void Protocol::REVIEW_ME_End()
{
    LOG(kMedia, "Protocol::End\n");
    iManager.REVIEW_ME_End();
}

void Protocol::REVIEW_ME_Lock()
{
    iManager.REVIEW_ME_Lock();
}

void Protocol::REVIEW_ME_Unlock()
{
    iManager.REVIEW_ME_Unlock();
}

/*TBool Protocol::Restream(TUint64 aOffset)
{
    ASSERTS();
    return false;
}*/

// Returns true if protocol enabled
TBool Protocol::REVIEW_ME_DoStream(const Brx& aUri)
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
        REVIEW_ME_Stream();
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
    
void Protocol::REVIEW_ME_DoInterrupt(TBool /*aInterrupt*/)
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
TBool ProtocolNetwork::REVIEW_ME_DoStream(const Brx& aUri)
{
    try {
        if (Protocol::REVIEW_ME_DoStream(aUri)) {
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
    
void ProtocolNetwork::REVIEW_ME_DoInterrupt(TBool aInterrupt)
{
    LOG(kMedia, ">ProtocolNetwork::DoInterrupt\n");

    Protocol::REVIEW_ME_DoInterrupt(aInterrupt);
    REVIEW_ME_Lock();
    TBool open = iSocketIsOpen;
    REVIEW_ME_Unlock();
    if (open) {
        iTcpClient.Interrupt(aInterrupt);
    }

    LOG(kMedia, "<ProtocolNetwork::DoInterrupt\n");
}

void ProtocolNetwork::Open()
{
    LOG(kMedia, "ProtocolNetwork::Open\n");

    iTcpClient.Open(iEnv);
    REVIEW_ME_Lock();
    ASSERT(!iSocketIsOpen);
    iSocketIsOpen = true;
    REVIEW_ME_Unlock();
}
    
void ProtocolNetwork::Close()
{
    LOG(kMedia, "ProtocolNetwork::Close\n");

    REVIEW_ME_Lock();
    TBool open = iSocketIsOpen;
    iSocketIsOpen = false;
    REVIEW_ME_Unlock();
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

    REVIEW_ME_Lock();
    iProtocol = NULL;
    iStarted = NULL;
    REVIEW_ME_Unlock();

    REVIEW_ME_Stream(aUri);
    
    LOG(kMedia, "<ProtocolManager::DoStream [");
    LOG(kMedia, aUri);
    LOG(kMedia, "]\n");
}

// interrupt the current point in the stack (iProtocol)
void ProtocolManager::DoInterrupt(TBool aInterrupt)
{
    LOG(kMedia, ">ProtocolManager::DoInterrupt\n");

    REVIEW_ME_Lock();
    Protocol* protocol = iProtocol;
    REVIEW_ME_Unlock();
    if (protocol != NULL) {
        protocol->REVIEW_ME_DoInterrupt(aInterrupt);
    }
        
    LOG(kMedia, "<ProtocolManager::DoInterrupt\n");
}

// Recursive functions called from Protocol Modules
    
TBool ProtocolManager::REVIEW_ME_Stream(const Brx& aUri)
{
    LOG(kMedia, "ProtocolManager::Stream [");
    LOG(kMedia, aUri);
    LOG(kMedia, "]\n");
    
    if (!SetUri(aUri)) {
        return (false);
    }

    REVIEW_ME_Lock();
    iStarted = NULL;
    Protocol* last = iProtocol;
    REVIEW_ME_Unlock();
    TUint index = 0;
    TUint count = iProtocols.size(); 
    while (index < count) {
        Protocol* protocol = iProtocols[index++];
        REVIEW_ME_Lock();
        iProtocol = protocol;
        REVIEW_ME_Unlock();
        try {
            if (protocol->REVIEW_ME_DoStream(iUri)) {
                REVIEW_ME_Lock();
                Protocol* protocol = iStarted;
                REVIEW_ME_Unlock();
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
    
    REVIEW_ME_Lock();
    iProtocol = last;
    // iStarted indicates that some protocol in the stack started playing a track
    TBool result = (iStarted != NULL);
    REVIEW_ME_Unlock();

    return result;
}

TBool ProtocolManager::REVIEW_ME_Redirect(const Brx& aUri)
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

TUint ProtocolManager::REVIEW_ME_Start(TUint64 aTotalBytes, ILiveStreamer* aLiveStreamer, IRestreamer* aRestreamer)
{
    REVIEW_ME_Lock();
    iStarted = iProtocol;
    TUint streamId = iNextStreamId;
    iNextStreamId += 1;
    REVIEW_ME_Unlock();
    iSupply.Start(aTotalBytes, aLiveStreamer, aRestreamer, streamId);
    return streamId;
}

void ProtocolManager::REVIEW_ME_OutputData(const Brx& aAudio)
{
    iSupply.OutputData(aAudio);
}

void ProtocolManager::REVIEW_ME_OutputMetadata(const Brx& aMetadata)
{
    iSupply.OutputMetadata(aMetadata);
}

void ProtocolManager::REVIEW_ME_OutputFlush()
{
    iSupply.OutputFlush();
}

void ProtocolManager::REVIEW_ME_End()
{
    iSupply.End();
}

void ProtocolManager::REVIEW_ME_Lock()
{
    iMutex.Wait();
}

void ProtocolManager::REVIEW_ME_Unlock()
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
