#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Protocol

Protocol::Protocol(Environment& aEnv)
    : iEnv(aEnv)
    , iProtocolManager(NULL)
    , iIdProvider(NULL)
    , iSupply(NULL)
    , iActive(false)
{
}

void Protocol::Initialise(IProtocolManager& aProtocolManager, IPipelineIdProvider& aIdProvider, ISupply& aSupply)
{
    iProtocolManager = &aProtocolManager;
    iIdProvider = &aIdProvider;
    iSupply = &aSupply;
}

ProtocolStreamResult Protocol::TryStream(const Brx& aUri)
{
    AutoStream a(*this);
    return Stream(aUri);
}

TBool Protocol::Active() const
{
    return iActive;
}

TBool Protocol::OkToPlay(TUint aTrackId, TUint aStreamId)
{
    return iIdProvider->OkToPlay(aTrackId, aStreamId);
}

TUint Protocol::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}


// Protocol::AutoStream

Protocol::AutoStream::AutoStream(Protocol& aProtocol)
    : iProtocol(aProtocol)
{
    iProtocol.iActive = true;
}

Protocol::AutoStream::~AutoStream()
{
    iProtocol.iActive = false;
}


// ProtocolNetwork	

ProtocolNetwork::ProtocolNetwork(Environment& aEnv)
    : Protocol(aEnv)
    , iReaderBuf(iTcpClient)
    , iWriterBuf(iTcpClient)
    , iLock("PRNW")
    , iSocketIsOpen(false)
{
}

TBool ProtocolNetwork::Connect(const OpenHome::Uri& aUri, TUint aDefaultPort)
{
    LOG(kMedia, ">ProtocolNetwork::Connect\n");

    Endpoint endpoint;
    try {
        endpoint.SetAddress(aUri.Host());
        TInt port = aUri.Port();
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
/*TBool ProtocolNetwork::REVIEW_ME_DoStream(const Brx& aUri)
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
}*/
    
void ProtocolNetwork::Interrupt(TBool aInterrupt)
{
    LOG(kMedia, ">ProtocolNetwork::Interrupt\n");

    iLock.Wait();
    TBool open = iSocketIsOpen;
    if (open) {
        iTcpClient.Interrupt(aInterrupt);
    }
    iLock.Signal();

    LOG(kMedia, "<ProtocolNetwork::Interrupt\n");
}

void ProtocolNetwork::Open()
{
    LOG(kMedia, "ProtocolNetwork::Open\n");

    iTcpClient.Open(iEnv);
    ASSERT(!iSocketIsOpen);
    iSocketIsOpen = true;
}
    
void ProtocolNetwork::Close()
{
    LOG(kMedia, "ProtocolNetwork::Close\n");

    if (iSocketIsOpen) {
        iSocketIsOpen = false;
        iTcpClient.Close();
    }
}


// ContentProcessor

ContentProcessor::ContentProcessor()
    : iProtocolSet(NULL)
    , iActive(false)
{
}

ContentProcessor::~ContentProcessor()
{
}

void ContentProcessor::Initialise(IProtocolSet& aProtocolSet)
{
    iProtocolSet = &aProtocolSet;
}

TBool ContentProcessor::Active() const
{
    return iActive;
}

ProtocolStreamResult ContentProcessor::TryStream(Srx& aReaderStream, TUint64 aTotalBytes, TUint aMaxReadBytes)
{
    AutoStream a(*this);
    return Stream(aReaderStream, aTotalBytes, aMaxReadBytes);
}


// ContentProcessor::AutoStream

ContentProcessor::AutoStream::AutoStream(ContentProcessor& aProcessor)
    : iProcessor(aProcessor)
{
    iProcessor.iActive = true;
}

ContentProcessor::AutoStream::~AutoStream()
{
    iProcessor.iActive = false;
}


// ProtocolManager

ProtocolManager::ProtocolManager(ISupply& aSupply, IPipelineIdProvider& aIdProvider)
    : iIdProvider(aIdProvider)
    , iSupply(aSupply)
    , iLock("PMGR")
{
}

ProtocolManager::~ProtocolManager()
{
    TUint count = iProtocols.size(); 
    for (TUint i = 0; i < count; i++) {
        delete iProtocols[i];
    }
    count = iContentProcessors.size(); 
    for (TUint i = 0; i < count; i++) {
        delete iContentProcessors[i];
    }
}

void ProtocolManager::Add(Protocol* aProtocol)
{
	LOG(kMedia, "ProtocolManager::Add(Protocol*)\n");
	iProtocols.push_back(aProtocol);
    aProtocol->Initialise(*this, iIdProvider, iSupply);
}

void ProtocolManager::Add(ContentProcessor* aProcessor)
{
	LOG(kMedia, "ProtocolManager::Add(ContentProcessor*)\n");
    iContentProcessors.push_back(aProcessor);
    aProcessor->Initialise(*this);
}

TBool ProtocolManager::DoStream(const Brx& aUri)
{
    iLock.Wait();
    iTrackId = iIdProvider.NextTrackId();
    iLock.Signal();
    iSupply.OutputTrack(aUri, iTrackId);
    ProtocolStreamResult res = Stream(aUri);
    return (res != EProtocolStreamStopped);
}

ProtocolStreamResult ProtocolManager::Stream(const Brx& aUri)
{
    ProtocolStreamResult res = EProtocolErrorNotSupported;
    const TUint count = iProtocols.size();
    for (TUint i=0; i<count, res==EProtocolErrorNotSupported; i++) {
        Protocol* protocol = iProtocols[i];
        if (!protocol->Active()) {
            res = protocol->TryStream(aUri);
            ASSERT(res != EProtocolStreamErrorRecoverable);
        }
    }
    return res;
}

ContentProcessor* ProtocolManager::GetContentProcessor(const Brx& aUri, const Brx& aMimeType, const Brx& aData) const
{
    const TUint count = iContentProcessors.size();
    for (TUint i=0; i<count; i++) {
        ContentProcessor* processor = iContentProcessors[i];
        if (!processor->Active() && processor->Recognise(aUri, aMimeType, aData)) {
            return processor;
        }
    }
    // unrecognised content (may well be audio)
    return NULL;
}

TBool ProtocolManager::OkToSeek(TUint /*aTrackId*/) const
{
    iLock.Wait();
    // FIXME - MsgTrack needs getter/setter for TrackIdPipeline() before test of iTrackId becomes valid
    const TBool ok = true;//(iTrackId == aTrackId);
    iLock.Signal();
    return ok;
}
