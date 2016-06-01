#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/ContentAudio.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Media/Debug.h>

#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::Media;

// Protocol

Protocol::Protocol(Environment& aEnv)
    : iEnv(aEnv)
    , iProtocolManager(nullptr)
    , iIdProvider(nullptr)
    , iFlushIdProvider(nullptr)
    , iActive(false)
    , iLockActive("PROT")
{
}

Protocol::~Protocol()
{
}

void Protocol::Initialise(IProtocolManager& aProtocolManager, IPipelineIdProvider& aIdProvider, MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream, IFlushIdProvider& aFlushIdProvider)
{
    iProtocolManager = &aProtocolManager;
    iIdProvider = &aIdProvider;
    iFlushIdProvider = &aFlushIdProvider;
    Initialise(aMsgFactory, aDownstream);
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

TBool Protocol::TrySetActive()
{
    AutoMutex _(iLockActive);
    if (iActive) {
        return false;
    }
    iActive = true;
    return true;
}

EStreamPlay Protocol::OkToPlay(TUint aStreamId)
{
    return iIdProvider->OkToPlay(aStreamId);
}

TUint Protocol::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint Protocol::TryDiscard(TUint /*aJiffies*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

void Protocol::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool /*aStarving*/)
{
}

void Protocol::Deactivated()
{
}


// Protocol::AutoStream

Protocol::AutoStream::AutoStream(Protocol& aProtocol)
    : iProtocol(aProtocol)
{
    ASSERT(iProtocol.iActive);
}

Protocol::AutoStream::~AutoStream()
{
    AutoMutex _(iProtocol.iLockActive);
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

TBool ProtocolNetwork::Connect(const OpenHome::Uri& aUri, TUint aDefaultPort, TUint aTimeoutMs)
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
        iTcpClient.Connect(endpoint, aTimeoutMs);
    }
    catch (NetworkTimeout&) {
        Close();
        LOG(kMedia, "<ProtocolNetwork::Connect error connecting\n");
        return false;
    }
    catch (NetworkError&) {
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
    if (iSocketIsOpen) {
        LOG(kMedia, "ProtocolNetwork::Close\n");
        iSocketIsOpen = false;
        iTcpClient.Close();
    }
}


// ContentProcessor

ContentProcessor::ContentProcessor()
    : iProtocolSet(nullptr)
    , iReader(nullptr)
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
    iReader = nullptr;
}

void ContentProcessor::SetStream(IReader& aStream)
{
    iReader = &aStream;
}

Brn ContentProcessor::ReadLine(ReaderUntil& aReader, TUint64& aBytesRemaining)
{
    Brn line;
    try {
        Brn buf = aReader.ReadUntil(Ascii::kLf);
        if (aBytesRemaining < buf.Bytes() + 1) { // +1 for Ascii::kLf
            aBytesRemaining = 0;
        }
        else {
            aBytesRemaining -= buf.Bytes() + 1;
        }
        iPartialLine.Append(buf);
        line.Set(Ascii::Trim(iPartialLine));
        iPartialLine.SetBytes(0);
    }
    catch (ReaderError&) {
        // treat any content following the last newline as a final line
        Brn buf = aReader.Read(iPartialLine.MaxBytes() - iPartialLine.Bytes());
        if (aBytesRemaining < buf.Bytes()) {
            aBytesRemaining = 0;
        }
        else {
            aBytesRemaining -= buf.Bytes();
        }
        iPartialLine.Append(buf);
        if (aBytesRemaining > 0) {
            throw;
        }
        line.Set(Ascii::Trim(iPartialLine));
        iPartialLine.SetBytes(0);
        if (line.Bytes() == 0) {
            THROW(ReaderError);
        }
    }
    return line;
}

Brn ContentProcessor::ReadTag(ReaderUntil& aReader, TUint64& aBytesRemaining)
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
        Brn rem = aReader.Read(iPartialTag.MaxBytes());
        aBytesRemaining -= rem.Bytes();
        if (aBytesRemaining != 0 && partialTag) {
            iPartialTag.Replace(rem);
        }
        throw;
    }
}

Brn ContentProcessor::Read(TUint aBytes)
{
    ASSERT(iReader != nullptr);
    return iReader->Read(aBytes);
}

void ContentProcessor::ReadFlush()
{
    if (iReader != nullptr) {
        iReader->ReadFlush();
    }
}

void ContentProcessor::ReadInterrupt()
{
    if (iReader != nullptr) {
        iReader->ReadInterrupt();
    }
}


// ContentRecogBuf

ContentRecogBuf::ContentRecogBuf(IReader& aReader)
    : iReader(aReader)
    , iBytesRemaining(0)
{
}

void ContentRecogBuf::Populate(TUint64 aStreamTotalBytes)
{
    iBuf.SetBytes(0);
    TUint bytes = iBuf.MaxBytes();
    if (aStreamTotalBytes != 0 && aStreamTotalBytes < bytes) {
        bytes = (TUint)aStreamTotalBytes;
    }
    try {
        while (bytes != 0) {
            Brn buf = iReader.Read(bytes);
            bytes -= buf.Bytes();
            iBuf.Append(buf);
        }
    }
    catch (ReaderError&) {
        if (aStreamTotalBytes != 0) {
            throw;
        }
    }
    iBytesRemaining = iBuf.Bytes();
}

const Brx& ContentRecogBuf::Buffer() const
{
    return iBuf;
}

Brn ContentRecogBuf::Read(TUint aBytes)
{
    if (iBytesRemaining == 0) {
        return iReader.Read(aBytes);
    }
    const TUint bytes = std::min(aBytes, iBytesRemaining);
    Brn buf(iBuf.Ptr() + iBuf.Bytes() - iBytesRemaining, bytes);
    iBytesRemaining -= bytes;
    return buf;
}

void ContentRecogBuf::ReadFlush()
{
    iBuf.SetBytes(0);
    iBytesRemaining = 0;
    iReader.ReadFlush();
}

void ContentRecogBuf::ReadInterrupt()
{
    iReader.ReadInterrupt();
}


// ProtocolManager

ProtocolManager::ProtocolManager(IPipelineElementDownstream& aDownstream, MsgFactory& aMsgFactory, IPipelineIdProvider& aIdProvider, IFlushIdProvider& aFlushIdProvider)
    : iDownstream(aDownstream)
    , iMsgFactory(aMsgFactory)
    , iIdProvider(aIdProvider)
    , iFlushIdProvider(aFlushIdProvider)
    , iLock("PMGR")
{
    iAudioProcessor = new ContentAudio(aMsgFactory, aDownstream);
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
    iProtocols.push_back(aProtocol);
    aProtocol->Initialise(*this, iIdProvider, iMsgFactory, iDownstream, iFlushIdProvider);
}

void ProtocolManager::Add(ContentProcessor* aProcessor)
{
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

TBool ProtocolManager::TryGet(IWriter& aWriter, const Brx& aUrl, TUint64 aOffset, TUint aBytes)
{
    return Get(aWriter, aUrl, aOffset, aBytes);
}

ProtocolStreamResult ProtocolManager::DoStream(Track& aTrack)
{
    iDownstream.Push(iMsgFactory.CreateMsgTrack(aTrack));
    iDownstream.Push(iMsgFactory.CreateMsgMetaText(Brx::Empty()));
    ProtocolStreamResult res = Stream(aTrack.Uri());
    return res;
}

ProtocolStreamResult ProtocolManager::Stream(const Brx& aUri)
{
    ProtocolStreamResult res = EProtocolErrorNotSupported;
    const TUint count = iProtocols.size();
    for (TUint i=0; i<count && res==EProtocolErrorNotSupported; i++) {
        Protocol* protocol = iProtocols[i];
        if (protocol->TrySetActive()) {
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
    return nullptr;
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
        if (protocol->TrySetActive()) {
            try {
                res = protocol->DoGet(aWriter, aUri, aOffset, aBytes);
            }
            catch (UriError&) {}
        }
    }
    return (res == EProtocolGetSuccess);
}
