#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/ContentAudio.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Protocol

Protocol::Protocol(Environment& aEnv)
    : iEnv(aEnv)
    , iProtocolManager(NULL)
    , iIdProvider(NULL)
    , iSupply(NULL)
    , iFlushIdProvider(NULL)
    , iActive(false)
{
}

Protocol::~Protocol()
{
}

void Protocol::Initialise(IProtocolManager& aProtocolManager, IPipelineIdProvider& aIdProvider, ISupply& aSupply, IFlushIdProvider& aFlushIdProvider)
{
    iProtocolManager = &aProtocolManager;
    iIdProvider = &aIdProvider;
    iSupply = &aSupply;
    iFlushIdProvider = &aFlushIdProvider;
}

ProtocolGetResult Protocol::DoGet(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes)
{
    AutoStream a(*this);
    return Get(aWriter, aUri, aOffset, aBytes);
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

EStreamPlay Protocol::OkToPlay(TUint aTrackId, TUint aStreamId)
{
    return iIdProvider->OkToPlay(aTrackId, aStreamId);
}

TUint Protocol::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TBool Protocol::TryGet(IWriter& /*aWriter*/, TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return false;
}

void Protocol::NotifyStarving(const Brx& /*aMode*/, TUint /*aTrackId*/, TUint /*aStreamId*/)
{
}

void Protocol::Deactivated()
{
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
    iProtocol.Deactivated();
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

    try {
        Open();
    }
    catch (NetworkError&) {
        LOG(kMedia, "<ProtocolNetwork::Connect error opening\n");
        return false;
    }
    try {        
        iTcpClient.Connect(endpoint, kConnectTimeoutMs);
    }
    catch (NetworkTimeout&) {
        Close();
        LOG(kMedia, "<ProtocolNetwork::Connect error connecting\n");
        return false;
    }

    LOG(kMedia, "<Protocol::Connect\n");
    return true;
}

void ProtocolNetwork::Interrupt(TBool aInterrupt)
{
    iLock.Wait();
    if (iActive) {
        iTcpClient.Interrupt(aInterrupt);
    }
    iLock.Signal();
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
    Reset();
}

TBool ContentProcessor::IsActive() const
{
    return iActive;
}

void ContentProcessor::SetActive()
{
    ASSERT(!iActive);
    iActive = true;
}

void ContentProcessor::Reset()
{
    iActive = false;
    iPartialLine.SetBytes(0);
    iPartialTag.SetBytes(0);
    iInTag = false;
}

Brn ContentProcessor::ReadLine(IProtocolReader& aReader, TUint64& aBytesRemaining)
{
    TBool done = false;
    while (!done) {
        Brn line;
        try {
            line.Set(aReader.ReadUntil(Ascii::kLf));
            aBytesRemaining -= (line.Bytes() + 1); // +1 for Ascii::kLf
            if (iPartialLine.Bytes() == 0) {
                line.Set(Ascii::Trim(line));
            }
            else {
                if (iPartialLine.Bytes() + line.Bytes() <= iPartialLine.MaxBytes()) {
                    iPartialLine.Append(line);
                    line.Set(iPartialLine);
                }
                else {
                    // line is too long to store, no point in trying to process a fragment of it
                    line.Set(Brx::Empty());
                }
                iPartialLine.SetBytes(0);
            }
        }
        catch (ReaderError&) {
            line.Set(aReader.ReadRemaining());
            aBytesRemaining -= line.Bytes();
            if (aBytesRemaining != 0 && line.Bytes() < iPartialLine.MaxBytes() - iPartialLine.Bytes()) {
                iPartialLine.Append(line);
            }
            done = true;
        }
        if (iPartialLine.Bytes() > 0) {
            THROW(ReaderError);
        }
        if (line.Bytes() > 0) {
            return line;
        }
    }
    THROW(ReaderError);
}

Brn ContentProcessor::ReadTag(IProtocolReader& aReader, TUint64& aBytesRemaining)
{
    TBool partialTag = false;
    try {
        if (!iInTag) {
            aReader.ReadUntil('<');
            iInTag = true;
        }
        partialTag = true;
        Brn tag = aReader.ReadUntil('>');
        iInTag= false;
        aBytesRemaining -= tag.Bytes();
        if (iPartialTag.Bytes() > 0) {
            iPartialTag.Append(tag);
            tag.Set(iPartialTag);
            iPartialTag.SetBytes(0);
        }
        return tag;
    }
    catch (ReaderError&) {
        Brn rem = aReader.ReadRemaining();
        aBytesRemaining -= rem.Bytes();
        if (aBytesRemaining != 0 && partialTag) {
            iPartialTag.Replace(rem);
        }
        throw;
    }
}


// ProtocolManager

ProtocolManager::ProtocolManager(ISupply& aSupply, IPipelineIdProvider& aIdProvider, IFlushIdProvider& aFlushIdProvider)
    : iIdProvider(aIdProvider)
    , iFlushIdProvider(aFlushIdProvider)
    , iSupply(aSupply)
    , iLock("PMGR")
{
    iAudioProcessor = new ContentAudio(aSupply);
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
    delete iAudioProcessor;
}

void ProtocolManager::Add(Protocol* aProtocol)
{
    LOG(kMedia, "ProtocolManager::Add(Protocol*)\n");
    iProtocols.push_back(aProtocol);
    aProtocol->Initialise(*this, iIdProvider, *this, iFlushIdProvider);
}

void ProtocolManager::Add(ContentProcessor* aProcessor)
{
    LOG(kMedia, "ProtocolManager::Add(ContentProcessor*)\n");
    iContentProcessors.push_back(aProcessor);
    aProcessor->Initialise(*this);
}

void ProtocolManager::Interrupt(TBool aInterrupt)
{
    /* Deliberately don't take iLock.  Avoids any possibility of deadlock with protocols
       who're holding a local lock while calling IProtocolManager::Stream.  iProtocols
       never changes size/order so we can safely access it without locks. */
    for (auto it=iProtocols.begin(); it!=iProtocols.end(); ++it) {
        (*it)->Interrupt(aInterrupt);
    }
}

void ProtocolManager::OutputMode(const Brx& aMode, TBool aSupportsLatency, TBool aRealTime, IClockPuller* aClockPuller)
{
    iSupply.OutputMode(aMode, aSupportsLatency, aRealTime, aClockPuller);
}

void ProtocolManager::OutputSession()
{
    iSupply.OutputSession();
}

void ProtocolManager::OutputTrack(Track& aTrack, TUint aTrackId)
{
    iLock.Wait();
    iTrackId = aTrackId;
    iLock.Signal();
    iSupply.OutputTrack(aTrack, aTrackId);
}

void ProtocolManager::OutputDelay(TUint aJiffies)
{
    iSupply.OutputDelay(aJiffies);
}

void ProtocolManager::OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId)
{
    iSupply.OutputStream(aUri, aTotalBytes, aSeekable, aLive, aStreamHandler, aStreamId);
}

void ProtocolManager::OutputPcmStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId, const PcmStreamInfo& aPcmStream)
{
    iSupply.OutputPcmStream(aUri, aTotalBytes, aSeekable, aLive, aStreamHandler, aStreamId, aPcmStream);
}

void ProtocolManager::OutputData(const Brx& aData)
{
    iSupply.OutputData(aData);
}

void ProtocolManager::OutputMetadata(const Brx& aMetadata)
{
    iSupply.OutputMetadata(aMetadata);
}

void ProtocolManager::OutputFlush(TUint aFlushId)
{
    iSupply.OutputFlush(aFlushId);
}

void ProtocolManager::OutputWait()
{
    iSupply.OutputWait();
}

void ProtocolManager::OutputHalt(TUint aHaltId)
{
    iSupply.OutputHalt(aHaltId);
}

void ProtocolManager::OutputQuit()
{
    iSupply.OutputQuit();
}

ProtocolStreamResult ProtocolManager::DoStream(Track& aTrack)
{
    iLock.Wait();
    iTrackId = iIdProvider.NextTrackId();
    iLock.Signal();
    iSupply.OutputTrack(aTrack, iTrackId);
    ProtocolStreamResult res = Stream(aTrack.Uri());
    return res;
}

ProtocolStreamResult ProtocolManager::Stream(const Brx& aUri)
{
    ProtocolStreamResult res = EProtocolErrorNotSupported;
    const TUint count = iProtocols.size();
    for (TUint i=0; i<count && res==EProtocolErrorNotSupported; i++) {
        Protocol* protocol = iProtocols[i];
        if (!protocol->Active()) {
            try {
                res = protocol->TryStream(aUri);
            }
            catch (UriError&) {}
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
        if (!processor->IsActive() && processor->Recognise(aUri, aMimeType, aData)) {
            processor->SetActive();
            return processor;
        }
    }
    // unrecognised content (may well be audio)
    return NULL;
}

ContentProcessor* ProtocolManager::GetAudioProcessor() const
{
    return iAudioProcessor;
}

TBool ProtocolManager::Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes)
{
    ProtocolGetResult res = EProtocolGetErrorNotSupported;
    const TUint count = iProtocols.size();
    for (TUint i=0; i<count && res==EProtocolGetErrorNotSupported; i++) {
        Protocol* protocol = iProtocols[i];
        if (!protocol->Active()) {
            try {
                res = protocol->DoGet(aWriter, aUri, aOffset, aBytes);
            }
            catch (UriError&) {}
        }
    }
    return (res == EProtocolGetSuccess);
}

TBool ProtocolManager::IsCurrentTrack(TUint aTrackId) const
{
    iLock.Wait();
    const TBool ok = (iTrackId == aTrackId);
    iLock.Signal();
    return ok;
}
