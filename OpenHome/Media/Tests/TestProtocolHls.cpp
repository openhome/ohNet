#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/ProtocolHls.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Tests/TestProtocolHls.h>

#include <limits>


namespace OpenHome {
namespace Media {
namespace Test {

class TestTimer : public ITimer
{
public:
    TestTimer();
    void Clear();
    ITimerHandler* LastHandler() const; // NOT passing ownership; may return NULL
    TUint LastDurationMs() const;
    TUint StartCount() const;
    TUint CancelCount() const;
public: // from ITimer
    void Start(TUint aDurationMs, ITimerHandler& aHandler) override;
    void Cancel() override;
private:
    ITimerHandler* iHandler;
    TUint iDurationMs;
    TUint iStartCount;
    TUint iCancelCount;
    mutable Mutex iLock;
};

class TestSemaphore : public ISemaphore
{
public:
    TestSemaphore(Semaphore& aSem);
    //TUint WaitCount() const;
    TUint ClearCount() const;
    //TUint SignalCount() const;
public: // from ISemaphore
    void Wait() override;
    TBool Clear() override;
    void Signal() override;
private:
    Semaphore& iSemWait;
    Semaphore iSem;
    TUint iClearCount;
};

class TestHttpReader : public IHlsReader, public IHttpSocket, public IReaderBuffered
{
public:
    typedef std::vector<const Uri*> UriList;
    typedef std::vector<const Brx*> BufList;
public:
    TestHttpReader(Semaphore& aObserverSem, Semaphore& aWaitSem);
    void SetContent(const UriList& aUris, const BufList& aContent);
    void BlockAtOffset(TUint aOffset);
    void ThrowReadErrorAtOffset(TUint aOffset);
    void WaitAtOffset(TUint aOffset); // waits on aWaitSem being signalled
    TUint ConnectCount() const;
public: // from IHlsReader
    IHttpSocket& Socket() override;
    IReaderBuffered& Reader() override;
public: // from IHttpSocket
    TBool Connect(const Uri& aUri) override;
    void Close() override;
    TUint ContentLength() const override;
public: // from IReaderBuffered
    Brn Read(TUint aBytes) override;
    Brn ReadUntil(TByte aSeparator) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
    Brn ReadRemaining() override;
private:
    const UriList* iUris;
    const BufList* iContent;
    Brn iCurrent;
    TUint iIndex;
    TUint iOffset;
    TUint iBlockOffset;
    Semaphore& iObserverSem;
    Semaphore iBlockSem;
    TUint iThrowOffset;
    Semaphore& iWaitSem;
    TUint iWaitOffset;
    TUint iConnectCount;
    TBool iConnected;
};

class TestSegmentUriProvider : public ISegmentUriProvider
{
public:
    TestSegmentUriProvider();
    void Clear();
    void SetUri(const Uri& aUri, TUint aDuration);
    void SetEndOfStream();
    void SetPlaylistError();
public: // from ISegmentUriProvider
    TUint NextSegmentUri(Uri& aUri) override;
private:
    Uri iUri;
    TUint iDuration;
    TBool iEndOfStream;
    TBool iPlaylistError;
};

class TestPipelineIdProvider : public IPipelineIdProvider
{
public:
    TestPipelineIdProvider();
public: // from IPipelineIdProvider
    TUint NextStreamId() override;
    EStreamPlay OkToPlay(TUint aStreamId) override;
private:
    TUint iCurrentStreamId;
    Mutex iLock;
};

class TestFlushIdProvider : public IFlushIdProvider
{
private:
    static const TUint kIdStart = MsgFlush::kIdInvalid+1;
public:
    TestFlushIdProvider();
public: // from IFlushIdProvider
    TUint NextFlushId() override;
private:
    TUint iNextFlushId;
};

class TestElementDownstream : public IPipelineElementDownstream, private IMsgProcessor
{
private:
    static const TUint kBufferBytes = 1024;
public:
    TestElementDownstream();
    const Brx& Data() const;
    TBool IsLive() const;
    TUint StreamId() const;
    TUint TrackCount() const;
    TUint StreamCount() const;
    TUint FlushCount() const;
    IStreamHandler* StreamHandler() const;  // NOT passing ownership; may return NULL
public: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
public: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    TUint iStreamId;
    TBool iLive;
    TUint iTrackCount;
    TUint iStreamCount;
    TUint iFlushCount;
    TUint iDataTotal;
    IStreamHandler* iStreamHandler;
    Bws<kBufferBytes> iBuf;
};

class SuiteHlsM3uReader : public OpenHome::TestFramework::SuiteUnitTest
{
private:
    static const TUint kSemWaitMs = 50;
    static const Brn kFileDefault;
public:
    SuiteHlsM3uReader();
public: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void NextSegmentThread();
    void TestSetUri();
    void TestPlaylistNoMediaSequence();
    void TestPlaylistMediaSequenceStartZero();
    void TestPlaylistMediaSequenceStartNonZero();
    void TestPlaylistRelativeUris();
    void TestReloadNonContinuous();
    void TestEndlist();
    void TestPlaylistCrLf();
    void TestUnsupportedVersion();
    void TestInterrupt();
    void TestFailedConnection();
    void TestInvalidAttributes();
private:
    const Uri iUriDefault;
    Semaphore* iSemReader;
    Semaphore* iSemWait;
    TestHttpReader* iHttpReader;
    TestTimer* iTimer;
    Semaphore* iSem;
    Semaphore* iThreadSem;
    TestSemaphore* iTestSem;
    HlsM3uReader* iM3uReader;
};

class SuiteSegmentStreamer : public OpenHome::TestFramework::SuiteUnitTest
{
private:
    static const TUint kSemWaitMs = 50;
public:
    SuiteSegmentStreamer();
public: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void ReadThread();
    void TestSetStream();
    void TestRead();
    void TestGetNextSegmentFail();
    void TestInterrupt();
private:
    TestSegmentUriProvider* iUriProvider;
    Semaphore* iSemReader;
    Semaphore* iSemWait;
    TestHttpReader* iHttpReader;
    SegmentStreamer* iStreamer;
    TUint iReadBytes;
    Semaphore* iThreadSem;
};

class SuiteProtocolHls : public OpenHome::TestFramework::SuiteUnitTest, public INonCopyable
{
private:
    static const TUint kSemWaitMs = 50;
public:
    SuiteProtocolHls(Environment& aEnv);
public: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void StreamThread();
    void TestStreamSuccessful();
    void TestStreamErrorRecoverable();
    void TestStreamM3uError();
    void TestStreamSegmentError();
    void TestGet();
    void TestTrySeek();
    void TestTryStop();
    void TestTryGet();
    void TestInterrupt();
private:
    Environment& iEnv;
    AllocatorInfoLogger* iInfoAggregator;
    TrackFactory* iTrackFactory;
    MsgFactory* iMsgFactory;
    TestPipelineIdProvider* iIdProvider;
    TestFlushIdProvider* iFlushIdProvider;
    TestElementDownstream* iElementDownstream;
    ProtocolManager* iProtocolManager;

    Semaphore* iThreadSem;
    Semaphore* iM3uSem;
    Semaphore* iM3uWaitSem;
    TestHttpReader* iM3uReader;
    Semaphore* iSegmentSem;
    Semaphore* iSegmentWaitSem;
    TestHttpReader* iSegmentReader;
    Protocol* iProtocolHls;

    Track* iTrack;
    ProtocolStreamResult iResult;
};

} // namespace Test
} // namespace Media
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Test;
using namespace OpenHome::TestFramework;


// TestTimer

TestTimer::TestTimer()
    : iHandler(NULL)
    , iDurationMs(0)
    , iStartCount(0)
    , iCancelCount(0)
    , iLock("TTIL")
{
}

void TestTimer::Clear()
{
    iHandler = NULL;
    iDurationMs = 0;
    iStartCount = 0;
    iCancelCount = 0;
}

ITimerHandler* TestTimer::LastHandler() const
{
    AutoMutex a(iLock);
    return iHandler;
}

TUint TestTimer::LastDurationMs() const
{
    AutoMutex a(iLock);
    return iDurationMs;
}

TUint TestTimer::StartCount() const
{
    AutoMutex a(iLock);
    return iStartCount;
}

TUint TestTimer::CancelCount() const
{
    AutoMutex a(iLock);
    return iCancelCount;
}

void TestTimer::Start(TUint aDurationMs, ITimerHandler& aHandler)
{
    AutoMutex a(iLock);
    iStartCount++;
    iDurationMs = aDurationMs;
    iHandler = &aHandler;
};

void TestTimer::Cancel()
{
    AutoMutex a(iLock);
    iCancelCount++;
}


// TestSemaphore

TestSemaphore::TestSemaphore(Semaphore& aSem)
    : iSemWait(aSem)
    , iSem("TSES", 0)
    //, iWaitCount(0)
    , iClearCount(0)
    //, iSignalCount(0)
{
}

TUint TestSemaphore::ClearCount() const
{
    return iClearCount;
}

void TestSemaphore::Wait()
{
    //iWaitCount++;
    iSemWait.Signal();
    iSem.Wait();
}

TBool TestSemaphore::Clear()
{
    return iSem.Clear();
    //iClearCount++;
}

void TestSemaphore::Signal()
{
    iSem.Signal();
    //iSignalCount++;
}


// TestHttpReader

TestHttpReader::TestHttpReader(Semaphore& aObserverSem, Semaphore& aWaitSem)
    : iObserverSem(aObserverSem)
    , iBlockSem("THRS", 0)
    , iWaitSem(aWaitSem)
    , iConnected(false)
{
}

void TestHttpReader::SetContent(const UriList& aUris, const BufList& aContent)
{
    ASSERT(!iConnected);
    iUris = &aUris;
    iContent = &aContent;
    iIndex = 0;
    iBlockOffset = std::numeric_limits<TUint>::max();
    iThrowOffset = std::numeric_limits<TUint>::max();
    iWaitOffset = std::numeric_limits<TUint>::max();
}

void TestHttpReader::BlockAtOffset(TUint aOffset)
{
    ASSERT(iThrowOffset == std::numeric_limits<TUint>::max());
    ASSERT(iWaitOffset == std::numeric_limits<TUint>::max());
    iBlockOffset = aOffset;
}

void TestHttpReader::ThrowReadErrorAtOffset(TUint aOffset)
{
    ASSERT(iBlockOffset == std::numeric_limits<TUint>::max());
    ASSERT(iWaitOffset == std::numeric_limits<TUint>::max());
    iThrowOffset = aOffset;
}

void TestHttpReader::WaitAtOffset(TUint aOffset)
{
    ASSERT(iThrowOffset == std::numeric_limits<TUint>::max());
    ASSERT(iBlockOffset == std::numeric_limits<TUint>::max());
    iWaitOffset = aOffset;
}

TUint TestHttpReader::ConnectCount() const
{
    return iConnectCount;
}

IHttpSocket& TestHttpReader::Socket()
{
    return *this;
}

IReaderBuffered& TestHttpReader::Reader()
{
    return *this;
}

TBool TestHttpReader::Connect(const Uri& aUri)
{
    iConnectCount++;
    if (iIndex < iUris->size() && aUri.AbsoluteUri() == (*iUris)[iIndex]->AbsoluteUri()) {
        iCurrent.Set(*(*iContent)[iIndex]);
        iBlockSem.Clear();
        iOffset = 0;
        iIndex++;
        iConnected = true;
        return true;
    }
    return false;
}

void TestHttpReader::Close()
{
    ASSERT(iConnected);
    iConnected = false;
}

TUint TestHttpReader::ContentLength() const
{
    return (*iContent)[iIndex-1]->Bytes();
}

Brn TestHttpReader::Read(TUint aBytes)
{
    TUint offsetNew = iOffset + aBytes;

    if (offsetNew >= iBlockOffset) {
        iObserverSem.Signal();
        iBlockSem.Wait();
        iBlockOffset = std::numeric_limits<TUint>::max();
        THROW(ReaderError);
    }
    else if (offsetNew >= iWaitOffset) {
        iObserverSem.Signal();
        iWaitSem.Wait();
        iWaitOffset = std::numeric_limits<TUint>::max();
    }
    else if (offsetNew >= iThrowOffset) {
        iThrowOffset = std::numeric_limits<TUint>::max();
        THROW(ReaderError);
    }

    if (offsetNew > iCurrent.Bytes()) {
        THROW(ReaderError);
    }

    Brn buf = iCurrent.Split(iOffset, aBytes);
    iOffset = offsetNew;
    return buf;
}

Brn TestHttpReader::ReadUntil(TByte aSeparator)
{
    TUint start = iOffset;
    TUint offset = iOffset;

    TUint bytes = iCurrent.Bytes();
    TUint offsetNew = iOffset;

    while (offset < bytes && offsetNew == iOffset) {
        if (iCurrent[offset++] == aSeparator) {
            offsetNew = offset;
            break;
        }
    }

    if (offsetNew >= iBlockOffset) {
        iObserverSem.Signal();
        iBlockSem.Wait();
        iBlockOffset = std::numeric_limits<TUint>::max();
        THROW(ReaderError);
    }
    else if (offsetNew >= iWaitOffset) {
        iObserverSem.Signal();
        iWaitSem.Wait();
        iWaitOffset = std::numeric_limits<TUint>::max();
    }
    else if (offsetNew >= iThrowOffset) {
        iThrowOffset = std::numeric_limits<TUint>::max();
        THROW(ReaderError);
    }

    if (offsetNew > iOffset && offsetNew <= bytes) {
        iOffset = offsetNew;
        return (iCurrent.Split(start, offset - start - 1));
    }
    else {
        THROW(ReaderError);
    }
}

void TestHttpReader::ReadFlush()
{
    //iOffset = 0;
}

void TestHttpReader::ReadInterrupt()
{
    ASSERT(iConnected);
    iBlockSem.Signal();
}

Brn TestHttpReader::ReadRemaining()
{
    Brn buf = iCurrent.Split(iOffset, iCurrent.Bytes()-iOffset);
    iOffset += buf.Bytes();
    return buf;
}


// TestSegmentUriProvider

TestSegmentUriProvider::TestSegmentUriProvider()
    : iDuration(0)
    , iEndOfStream(false)
    , iPlaylistError(false)
{
}

void TestSegmentUriProvider::Clear()
{
    iUri.Clear();
    iDuration = 0;
    iEndOfStream = false;
    iPlaylistError = false;
}

void TestSegmentUriProvider::SetUri(const Uri& aUri, TUint aDuration)
{
    iUri.Replace(aUri.AbsoluteUri());
    iDuration = aDuration;
}

void TestSegmentUriProvider::SetEndOfStream()
{
    iEndOfStream = true;
}

void TestSegmentUriProvider::SetPlaylistError()
{
    iPlaylistError = true;
}

TUint TestSegmentUriProvider::NextSegmentUri(Uri& aUri)
{
    if (iEndOfStream) {
        THROW(HlsEndOfStream);
    }
    if (iPlaylistError) {
        THROW(HlsVariantPlaylistError);
    }
    aUri.Replace(iUri.AbsoluteUri());
    return iDuration;
}


// TestPipelineIdProvider

TestPipelineIdProvider::TestPipelineIdProvider()
    : iCurrentStreamId(kStreamIdInvalid)
    , iLock("TPIL")
{
}

TUint TestPipelineIdProvider::NextStreamId()
{
    AutoMutex a(iLock);
    ++iCurrentStreamId;
    return iCurrentStreamId;
}

EStreamPlay TestPipelineIdProvider::OkToPlay(TUint aStreamId)
{
    AutoMutex a(iLock);
    if (aStreamId != iCurrentStreamId) {
        return ePlayNo;
    }
    return ePlayYes;
}


// TestFlushIdProvider

TestFlushIdProvider::TestFlushIdProvider()
    : iNextFlushId(kIdStart)
{
}

TUint TestFlushIdProvider::NextFlushId()
{
    return iNextFlushId++;
}


// TestElementDownstream

TestElementDownstream::TestElementDownstream()
    : iStreamId(IPipelineIdProvider::kStreamIdInvalid)
    , iLive(false)
    , iTrackCount(0)
    , iStreamCount(0)
    , iFlushCount(0)
    , iDataTotal(0)
    , iStreamHandler(NULL)
{
}

const Brx& TestElementDownstream::Data() const
{
    return iBuf;
}

TBool TestElementDownstream::IsLive() const
{
    return iLive;
}

TUint TestElementDownstream::StreamId() const
{
    return iStreamId;
}

TUint TestElementDownstream::TrackCount() const
{
    return iTrackCount;
}

TUint TestElementDownstream::StreamCount() const
{
    return iStreamCount;
}

TUint TestElementDownstream::FlushCount() const
{
    return iFlushCount;
}

IStreamHandler* TestElementDownstream::StreamHandler() const
{
    return iStreamHandler;
}

void TestElementDownstream::Push(Msg* aMsg)
{
    (void)aMsg->Process(*this);
    aMsg->RemoveRef();
}

Msg* TestElementDownstream::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgTrack* aMsg)
{
    iTrackCount++;
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLive = aMsg->Live();
    iStreamId = aMsg->StreamId();
    iStreamHandler = aMsg->StreamHandler();
    (void)iStreamHandler->OkToPlay(iStreamId);
    iStreamCount++;
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iDataTotal += aMsg->Bytes();
    aMsg->CopyTo(const_cast<TByte*>(iBuf.Ptr())+iBuf.Bytes());
    iBuf.SetBytes(iBuf.Bytes()+aMsg->Bytes());
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgFlush* aMsg)
{
    iFlushCount++;
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgDecodedStream* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgAudioPcm* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgSilence* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgPlayable* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* TestElementDownstream::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}


// SuiteHlsM3uReader

//https://tools.ietf.org/html/draft-pantos-http-live-streaming-14#section-8

const Brn SuiteHlsM3uReader::kFileDefault(
    "#EXTM3U\n"
    "#EXT-X-VERSION:2\n"
    "#EXT-X-TARGETDURATION:8\n"
    "#EXT-X-MEDIA-SEQUENCE:2680\n"
    "\n"
    "#EXTINF:8,\n"
    "https://priv.example.com/fileSequence2680.ts\n"
    "#EXTINF:8,\n"
    "https://priv.example.com/fileSequence2681.ts\n"
    "#EXTINF:8,\n"
    "https://priv.example.com/fileSequence2682.ts\n"
    );

SuiteHlsM3uReader::SuiteHlsM3uReader()
    : SuiteUnitTest("SuiteHlsM3uReader")
    , iUriDefault(Brn("http://example.com/hls_variant.m3u8"))
{
    AddTest(MakeFunctor(*this, &SuiteHlsM3uReader::TestSetUri), "TestSetUri");
    AddTest(MakeFunctor(*this, &SuiteHlsM3uReader::TestPlaylistNoMediaSequence), "TestPlaylistNoMediaSequence");
    AddTest(MakeFunctor(*this, &SuiteHlsM3uReader::TestPlaylistMediaSequenceStartZero), "TestPlaylistMediaSequenceStartZero");
    AddTest(MakeFunctor(*this, &SuiteHlsM3uReader::TestPlaylistMediaSequenceStartNonZero), "TestPlaylistMediaSequenceStartNonZero");
    AddTest(MakeFunctor(*this, &SuiteHlsM3uReader::TestPlaylistRelativeUris), "TestPlaylistRelativeUris");
    AddTest(MakeFunctor(*this, &SuiteHlsM3uReader::TestReloadNonContinuous), "TestReloadNonContinuous");
    AddTest(MakeFunctor(*this, &SuiteHlsM3uReader::TestEndlist), "TestEndlist");
    AddTest(MakeFunctor(*this, &SuiteHlsM3uReader::TestPlaylistCrLf), "TestPlaylistCrLf");
    AddTest(MakeFunctor(*this, &SuiteHlsM3uReader::TestUnsupportedVersion), "TestUnsupportedVersion");
    AddTest(MakeFunctor(*this, &SuiteHlsM3uReader::TestInterrupt), "TestInterrupt");
    AddTest(MakeFunctor(*this, &SuiteHlsM3uReader::TestFailedConnection), "TestFailedConnection");
    AddTest(MakeFunctor(*this, &SuiteHlsM3uReader::TestInvalidAttributes), "TestInvalidAttributes");
}

void SuiteHlsM3uReader::Setup()
{
    iSemReader = new Semaphore("SHRS", 0);
    iSemWait = new Semaphore("SHWS", 0);
    iHttpReader = new TestHttpReader(*iSemReader, *iSemWait);
    iTimer = new TestTimer();
    iSem = new Semaphore("SHMS", 0);
    iThreadSem = new Semaphore("SHTS", 0);
    iTestSem = new TestSemaphore(*iSem);
    iM3uReader = new HlsM3uReader(*iHttpReader, *iHttpReader, *iTimer, *iTestSem);
}

void SuiteHlsM3uReader::TearDown()
{
    iM3uReader->Close();
    delete iM3uReader;
    delete iTestSem;
    delete iThreadSem;
    delete iSem;
    delete iTimer;
    delete iHttpReader;
    delete iSemWait;
    delete iSemReader;
}

void SuiteHlsM3uReader::NextSegmentThread()
{
    Uri segmentUri;
    TEST_THROWS(iM3uReader->NextSegmentUri(segmentUri), HlsVariantPlaylistError);
    TEST(segmentUri.AbsoluteUri().Bytes() == 0);
    iThreadSem->Signal();
}

void SuiteHlsM3uReader::TestSetUri()
{
    TestHttpReader::UriList uriList1;
    uriList1.push_back(&iUriDefault);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&kFileDefault);
    iHttpReader->SetContent(uriList1, bufList1);
    iM3uReader->SetUri(iUriDefault);

    static const TUint kExpectedDuration = 8000;
    static const Brn kExpectedUri("https://priv.example.com/fileSequence2680.ts");
    Uri segmentUri;
    TUint duration = iM3uReader->NextSegmentUri(segmentUri);

    TEST(duration == kExpectedDuration);
    TEST(segmentUri.AbsoluteUri() == kExpectedUri);


    // Call SetUri() again and ensure everything is reset correctly.
    const Uri kUri2(Brn("http://example.com/hls_variant_2.m3u8"));
    const Brn kFile2(
    "#EXTM3U\n"
    "#EXT-X-VERSION:2\n"
    "#EXT-X-TARGETDURATION:6\n"
    "#EXT-X-MEDIA-SEQUENCE:3048\n"
    "\n"
    "#EXTINF:6,\n"
    "https://priv.example.com/fileSequence3048.ts\n"
    "#EXTINF:6,\n"
    "https://priv.example.com/fileSequence3049.ts\n"
    "#EXTINF:6,\n"
    "https://priv.example.com/fileSequence3050.ts\n"
    );

    iM3uReader->Interrupt();
    iM3uReader->Close();
    TestHttpReader::UriList uriList2;
    uriList2.push_back(&kUri2);
    TestHttpReader::BufList bufList2;
    bufList2.push_back(&kFile2);
    iHttpReader->SetContent(uriList2, bufList2);
    iM3uReader->SetUri(kUri2);

    static const TUint kExpectedDuration2 = 6000;
    static const Brn kExpectedUri2("https://priv.example.com/fileSequence3048.ts");
    Uri segmentUri2;
    TUint duration2 = iM3uReader->NextSegmentUri(segmentUri2);

    TEST(duration2 == kExpectedDuration2);
    TEST(segmentUri2.AbsoluteUri() == kExpectedUri2);
}

void SuiteHlsM3uReader::TestPlaylistNoMediaSequence()
{
    // A playlist with no EXT-X-MEDIA-SEQUENCE should assume it starts from 0.
    // (Can infer that this means the playlist will NOT have segments removed
    // and will only ever have segments added.)
    // Media segments do NOT have to contain their sequence number.
    // Segment durations must be >= EXT-X-TARGETDURATION
    const Uri kUriNoMediaSeq(Brn("http://example.com/hls_no_media_seq.m3u8"));
    const Brn kFileNoMediaSeq(
    "#EXTM3U\n"
    "#EXT-X-VERSION:2\n"
    "#EXT-X-TARGETDURATION:6\n"
    "\n"
    "#EXTINF:6,\n"
    "https://priv.example.com/a.ts\n"
    "#EXTINF:5,\n"
    "https://priv.example.com/b.ts\n"
    "#EXTINF:4,\n"
    "https://priv.example.com/c.ts\n"
    );

    // Playlist above with new segments added.
    const Brn kFileNoMediaSeqExtended(
    "#EXTM3U\n"
    "#EXT-X-VERSION:2\n"
    "#EXT-X-TARGETDURATION:6\n"
    "\n"
    "#EXTINF:6,\n"
    "https://priv.example.com/a.ts\n"
    "#EXTINF:5,\n"
    "https://priv.example.com/b.ts\n"
    "#EXTINF:4,\n"
    "https://priv.example.com/c.ts\n"
    "#EXTINF:3,\n"
    "https://priv.example.com/d.ts\n"
    "#EXTINF:2,\n"
    "https://priv.example.com/e.ts\n"
    );

    TestHttpReader::UriList uriList1;
    uriList1.push_back(&kUriNoMediaSeq);
    uriList1.push_back(&kUriNoMediaSeq);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&kFileNoMediaSeq);
    bufList1.push_back(&kFileNoMediaSeqExtended);
    iHttpReader->SetContent(uriList1, bufList1);
    iM3uReader->SetUri(kUriNoMediaSeq);

    Uri segmentUri;
    TUint duration = 0;

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 6000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/a.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 5000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/b.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 4000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/c.ts"));

    TEST(iTimer->StartCount() == 1);
    TEST(iTimer->CancelCount() == 0);
    TEST(iTimer->LastDurationMs() == 6000);
    TEST(iTimer->LastHandler() == iM3uReader);

    iM3uReader->TimerFired();

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 3000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/d.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 2000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/e.ts"));
}

void SuiteHlsM3uReader::TestPlaylistMediaSequenceStartZero()
{
    // Test a variant playlist that starts at seq 0 and DOESN'T remove segments.
    const Uri kUriMediaSeqStartZero(Brn("http://example.com/hls_media_seq_0.m3u8"));
    const Brn kFileMediaSeqStartZero(
    "#EXTM3U\n"
    "#EXT-X-VERSION:2\n"
    "#EXT-X-TARGETDURATION:6\n"
    "#EXT-X-MEDIA-SEQUENCE:0\n"
    "\n"
    "#EXTINF:6,\n"
    "https://priv.example.com/a.ts\n"
    "#EXTINF:5,\n"
    "https://priv.example.com/b.ts\n"
    "#EXTINF:4,\n"
    "https://priv.example.com/c.ts\n"
    );

    const Brn kFileMediaSeqStartZeroExtended(
    "#EXTM3U\n"
    "#EXT-X-VERSION:2\n"
    "#EXT-X-TARGETDURATION:6\n"
    "#EXT-X-MEDIA-SEQUENCE:0\n"
    "\n"
    "#EXTINF:6,\n"
    "https://priv.example.com/a.ts\n"
    "#EXTINF:5,\n"
    "https://priv.example.com/b.ts\n"
    "#EXTINF:4,\n"
    "https://priv.example.com/c.ts\n"
    "#EXTINF:3,\n"
    "https://priv.example.com/d.ts\n"
    "#EXTINF:2,\n"
    "https://priv.example.com/e.ts\n"
    );

    TestHttpReader::UriList uriList1;
    uriList1.push_back(&kUriMediaSeqStartZero);
    uriList1.push_back(&kUriMediaSeqStartZero);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&kFileMediaSeqStartZero);
    bufList1.push_back(&kFileMediaSeqStartZeroExtended);
    iHttpReader->SetContent(uriList1, bufList1);
    iM3uReader->SetUri(kUriMediaSeqStartZero);

    Uri segmentUri;
    TUint duration = 0;

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 6000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/a.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 5000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/b.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 4000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/c.ts"));

    TEST(iTimer->StartCount() == 1);
    TEST(iTimer->CancelCount() == 0);
    TEST(iTimer->LastDurationMs() == 6000);
    TEST(iTimer->LastHandler() == iM3uReader);

    iM3uReader->TimerFired();

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 3000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/d.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 2000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/e.ts"));
}

void SuiteHlsM3uReader::TestPlaylistMediaSequenceStartNonZero()
{
    // Test a variant playlist that starts at a non-zero seq no. and DOES
    // remove old segments.
    const Uri kUriMediaSeqStartNonZero(Brn("http://example.com/hls_media_seq_nonzero.m3u8"));
    const Brn kFileMediaSeqStartNonZero(
    "#EXTM3U\n"
    "#EXT-X-VERSION:2\n"
    "#EXT-X-TARGETDURATION:6\n"
    "#EXT-X-MEDIA-SEQUENCE:1234\n"
    "\n"
    "#EXTINF:6,\n"
    "https://priv.example.com/a.ts\n"
    "#EXTINF:5,\n"
    "https://priv.example.com/b.ts\n"
    "#EXTINF:4,\n"
    "https://priv.example.com/c.ts\n"
    );

    const Brn kFileMediaSeqStartNonZeroExtended(
    "#EXTM3U\n"
    "#EXT-X-VERSION:2\n"
    "#EXT-X-TARGETDURATION:6\n"
    "#EXT-X-MEDIA-SEQUENCE:1236\n"
    "\n"
    "#EXTINF:4,\n"
    "https://priv.example.com/c.ts\n"
    "#EXTINF:3,\n"
    "https://priv.example.com/d.ts\n"
    "#EXTINF:2,\n"
    "https://priv.example.com/e.ts\n"
    );

    TestHttpReader::UriList uriList1;
    uriList1.push_back(&kUriMediaSeqStartNonZero);
    uriList1.push_back(&kUriMediaSeqStartNonZero);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&kFileMediaSeqStartNonZero);
    bufList1.push_back(&kFileMediaSeqStartNonZeroExtended);
    iHttpReader->SetContent(uriList1, bufList1);
    iM3uReader->SetUri(kUriMediaSeqStartNonZero);

    Uri segmentUri;
    TUint duration = 0;

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 6000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/a.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 5000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/b.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 4000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/c.ts"));

    TEST(iTimer->StartCount() == 1);
    TEST(iTimer->CancelCount() == 0);
    TEST(iTimer->LastDurationMs() == 6000);
    TEST(iTimer->LastHandler() == iM3uReader);

    iM3uReader->TimerFired();

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 3000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/d.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 2000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/e.ts"));
}

void SuiteHlsM3uReader::TestPlaylistRelativeUris()
{
    // Test a variant playlist that uses relative URIs.
    // Relative URIs are considered relative to the URI of the playlist that
    // contains it.
    const Uri kUriRelative(Brn("http://example.com/some/path/hls_relative.m3u8"));
    const Brn kFileRelative(
    "#EXTM3U\n"
    "#EXT-X-VERSION:2\n"
    "#EXT-X-TARGETDURATION:6\n"
    "#EXT-X-MEDIA-SEQUENCE:1234\n"
    "\n"
    "#EXTINF:6,\n"
    "a.ts\n"
    "#EXTINF:5,\n"
    "b.ts\n"
    "#EXTINF:4,\n"
    "c.ts\n"
    );

    TestHttpReader::UriList uriList1;
    uriList1.push_back(&kUriRelative);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&kFileRelative);
    iHttpReader->SetContent(uriList1, bufList1);
    iM3uReader->SetUri(kUriRelative);

    Uri segmentUri;
    TUint duration = 0;

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 6000);
    TEST(segmentUri.AbsoluteUri() == Brn("http://example.com/some/path/a.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 5000);
    TEST(segmentUri.AbsoluteUri() == Brn("http://example.com/some/path/b.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 4000);
    TEST(segmentUri.AbsoluteUri() == Brn("http://example.com/some/path/c.ts"));

    TEST(iTimer->StartCount() == 1);
    TEST(iTimer->CancelCount() == 0);
    TEST(iTimer->LastDurationMs() == 6000);
    TEST(iTimer->LastHandler() == iM3uReader);
}

void SuiteHlsM3uReader::TestReloadNonContinuous()
{
    // Test a variant playlist where part of the sequence has disappeared when
    // reloaded (i.e., client has been to slow in reloading).
    const Uri kUriMediaSeqNonContinuous(Brn("http://example.com/hls_media_seq_noncontinuous.m3u8"));
    const Brn kFileMediaSeqNonContinuous(
    "#EXTM3U\n"
    "#EXT-X-VERSION:2\n"
    "#EXT-X-TARGETDURATION:6\n"
    "#EXT-X-MEDIA-SEQUENCE:1234\n"
    "\n"
    "#EXTINF:6,\n"
    "https://priv.example.com/a.ts\n"
    "#EXTINF:5,\n"
    "https://priv.example.com/b.ts\n"
    "#EXTINF:4,\n"
    "https://priv.example.com/c.ts\n"
    );

    const Brn kFileMediaSeqStartNonContinuousExtended(
    "#EXTM3U\n"
    "#EXT-X-VERSION:2\n"
    "#EXT-X-TARGETDURATION:6\n"
    "#EXT-X-MEDIA-SEQUENCE:1239\n"
    "\n"
    "#EXTINF:4,\n"
    "https://priv.example.com/f.ts\n"
    "#EXTINF:3,\n"
    "https://priv.example.com/g.ts\n"
    "#EXTINF:2,\n"
    "https://priv.example.com/h.ts\n"
    );

    TestHttpReader::UriList uriList1;
    uriList1.push_back(&kUriMediaSeqNonContinuous);
    uriList1.push_back(&kUriMediaSeqNonContinuous);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&kFileMediaSeqNonContinuous);
    bufList1.push_back(&kFileMediaSeqStartNonContinuousExtended);
    iHttpReader->SetContent(uriList1, bufList1);
    iM3uReader->SetUri(kUriMediaSeqNonContinuous);

    Uri segmentUri;
    TUint duration = 0;

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 6000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/a.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 5000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/b.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 4000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/c.ts"));

    TEST(iTimer->StartCount() == 1);
    TEST(iTimer->CancelCount() == 0);
    TEST(iTimer->LastDurationMs() == 6000);
    TEST(iTimer->LastHandler() == iM3uReader);

    iM3uReader->TimerFired();

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 4000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/f.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 3000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/g.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 2000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/h.ts"));
}

void SuiteHlsM3uReader::TestEndlist()
{
    // Test a file with the EXT-X-ENDLIST tag, which indicates that no more
    // media segments will be added to the existing playlist.
    // The tag may occur anywhere in the playlist file.

    // Test tag at end of playlist.
    const Uri kUriEndlistEnd(Brn("http://example.com/hls_endlist_end.m3u8"));
    const Brn kFileEndlistEnd(
    "#EXTM3U\n"
    "#EXT-X-TARGETDURATION:10\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/first.ts\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/second.ts\n"
    "#EXTINF:3.003,\n"
    "http://media.example.com/third.ts\n"
    "#EXT-X-ENDLIST\n");

    TestHttpReader::UriList uriList1;
    uriList1.push_back(&kUriEndlistEnd);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&kFileEndlistEnd);
    iHttpReader->SetContent(uriList1, bufList1);
    iM3uReader->SetUri(kUriEndlistEnd);

    Uri segmentUri;
    TUint duration = 0;

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 9009);
    TEST(segmentUri.AbsoluteUri() == Brn("http://media.example.com/first.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 9009);
    TEST(segmentUri.AbsoluteUri() == Brn("http://media.example.com/second.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 3003);
    TEST(segmentUri.AbsoluteUri() == Brn("http://media.example.com/third.ts"));

    TEST(iTimer->StartCount() == 1);
    TEST(iTimer->CancelCount() == 0);
    TEST(iTimer->LastDurationMs() == 10000);
    TEST(iTimer->LastHandler() == iM3uReader);

    const TUint connectCount1 = iHttpReader->ConnectCount();
    segmentUri.Clear();
    TEST_THROWS(iM3uReader->NextSegmentUri(segmentUri), HlsEndOfStream);  // should be no attempt to reload playlist
    TEST(segmentUri.AbsoluteUri().Bytes() == 0);
    TEST(iHttpReader->ConnectCount() == connectCount1);


    // Test tag at start of playlist and that all media is still played.
    const Uri kUriEndlistStart(Brn("http://example.com/hls_endlist_start.m3u8"));
    const Brn kFileEndlistStart(
    "#EXTM3U\n"
    "#EXT-X-TARGETDURATION:10\n"
    "#EXT-X-ENDLIST\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/first.ts\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/second.ts\n"
    "#EXTINF:3.003,\n"
    "http://media.example.com/third.ts\n"
    );

    iM3uReader->Interrupt();
    iM3uReader->Close();
    TestHttpReader::UriList uriList2;
    uriList2.push_back(&kUriEndlistStart);
    TestHttpReader::BufList bufList2;
    bufList2.push_back(&kFileEndlistStart);
    iHttpReader->SetContent(uriList2, bufList2);
    iM3uReader->SetUri(kUriEndlistStart);

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 9009);
    TEST(segmentUri.AbsoluteUri() == Brn("http://media.example.com/first.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 9009);
    TEST(segmentUri.AbsoluteUri() == Brn("http://media.example.com/second.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 3003);
    TEST(segmentUri.AbsoluteUri() == Brn("http://media.example.com/third.ts"));

    TEST(iTimer->StartCount() == 2);
    TEST(iTimer->CancelCount() == 1);
    TEST(iTimer->LastDurationMs() == 10000);
    TEST(iTimer->LastHandler() == iM3uReader);

    const TUint connectCount2 = iHttpReader->ConnectCount();
    segmentUri.Clear();
    TEST_THROWS(iM3uReader->NextSegmentUri(segmentUri), HlsEndOfStream);  // should be no attempt to reload playlist
    TEST(segmentUri.AbsoluteUri().Bytes() == 0);
    TEST(iHttpReader->ConnectCount() == connectCount2);
}

void SuiteHlsM3uReader::TestPlaylistCrLf()
{
    // Test a variant playlist that uses "\r\n" as line terminators.
    const Uri kUriMediaCrLf(Brn("http://example.com/hls_crlf.m3u8"));
    const Brn kFileMediaCrLf(
    "#EXTM3U\r\n"
    "#EXT-X-VERSION:2\r\n"
    "#EXT-X-TARGETDURATION:6\r\n"
    "#EXT-X-MEDIA-SEQUENCE:1234\r\n"
    "\r\n"
    "#EXTINF:6,\r\n"
    "https://priv.example.com/a.ts\n"
    "#EXTINF:5,\r\n"
    "https://priv.example.com/b.ts\n"
    "#EXTINF:4,\r\n"
    "https://priv.example.com/c.ts\n"
    );

    TestHttpReader::UriList uriList1;
    uriList1.push_back(&kUriMediaCrLf);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&kFileMediaCrLf);
    iHttpReader->SetContent(uriList1, bufList1);
    iM3uReader->SetUri(kUriMediaCrLf);

    Uri segmentUri;
    TUint duration = 0;

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 6000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/a.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 5000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/b.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 4000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/c.ts"));

    TEST(iTimer->StartCount() == 1);
    TEST(iTimer->CancelCount() == 0);
    TEST(iTimer->LastDurationMs() == 6000);
    TEST(iTimer->LastHandler() == iM3uReader);
}

void SuiteHlsM3uReader::TestUnsupportedVersion()
{
    // Test version 3 playlist with floating-point milliseconds for segment durations.
    const Uri kUriVersion3(Brn("http://example.com/hls_v3.m3u8"));
    const Brn kFileVersion3(
    "#EXTM3U\n"
    "#EXT-X-VERSION:3\n"
    "#EXT-X-TARGETDURATION:8\n"
    "#EXT-X-MEDIA-SEQUENCE:2680\n"
    "\n"
    "#EXTINF:7.975,\n"
    "https://priv.example.com/fileSequence2680.ts\n"
    "#EXTINF:7.941,\n"
    "https://priv.example.com/fileSequence2681.ts\n"
    "#EXTINF:7.975,\n"
    "https://priv.example.com/fileSequence2682.ts\n"
    );

    TestHttpReader::UriList uriList1;
    uriList1.push_back(&kUriVersion3);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&kFileVersion3);
    iHttpReader->SetContent(uriList1, bufList1);
    iM3uReader->SetUri(kUriVersion3);

    Uri segmentUri;
    TUint duration = 0;

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 7975);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/fileSequence2680.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 7941);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/fileSequence2681.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 7975);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/fileSequence2682.ts"));

    TEST(iTimer->StartCount() == 1);
    TEST(iTimer->CancelCount() == 0);
    TEST(iTimer->LastDurationMs() == 8000);
    TEST(iTimer->LastHandler() == iM3uReader);

    // Test same file as above, but with another version #.
    const Uri kUriVersion4(Brn("http://example.com/hls_v4.m3u8"));
    const Brn kFileVersion4(
    "#EXTM3U\n"
    "#EXT-X-VERSION:4\n"
    "#EXT-X-TARGETDURATION:8\n"
    "#EXT-X-MEDIA-SEQUENCE:2680\n"
    "\n"
    "#EXTINF:7.975,\n"
    "https://priv.example.com/fileSequence2680.ts\n"
    "#EXTINF:7.941,\n"
    "https://priv.example.com/fileSequence2681.ts\n"
    "#EXTINF:7.975,\n"
    "https://priv.example.com/fileSequence2682.ts\n"
    );

    iM3uReader->Interrupt();
    iM3uReader->Close();
    TestHttpReader::UriList uriList2;
    uriList2.push_back(&kUriVersion4);
    TestHttpReader::BufList bufList2;
    bufList2.push_back(&kFileVersion4);
    iHttpReader->SetContent(uriList2, bufList2);
    iM3uReader->SetUri(kUriVersion4);

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 7975);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/fileSequence2680.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 7941);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/fileSequence2681.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 7975);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/fileSequence2682.ts"));

    TEST(iTimer->StartCount() == 2);
    TEST(iTimer->CancelCount() == 1);
    TEST(iTimer->LastDurationMs() == 8000);
    TEST(iTimer->LastHandler() == iM3uReader);


    // Test version 3 playlist with EXT-X-KEY tags. Should skip over tags
    // (would fail to decrypt in real-world use, but just want to check
    // unrecognised tags are successfully skipped here).
    const Uri kUriVersion3Encrypted(Brn("http://example.com/hls_v3_enc.m3u8"));
    const Brn kFileVersion3Encrypted(
    "#EXTM3U\n"
    "#EXT-X-VERSION:3\n"
    "#EXT-X-MEDIA-SEQUENCE:7794\n"
    "#EXT-X-TARGETDURATION:15\n"
    "\n"
    "#EXT-X-KEY:METHOD=AES-128,URI=\"https://priv.example.com/key.php?r=52\"\n"
    "\n"
    "#EXTINF:2.833,\n"
    "http://media.example.com/fileSequence52-A.ts\n"
    "#EXTINF:15.0,\n"
    "http://media.example.com/fileSequence52-B.ts\n"
    "#EXTINF:13.333,\n"
    "http://media.example.com/fileSequence52-C.ts\n"
    "\n"
    "#EXT-X-KEY:METHOD=AES-128,URI=\"https://priv.example.com/key.php?r=53\"\n"
    "\n"
    "#EXTINF:15.0,\n"
    "http://media.example.com/fileSequence53-A.ts\n");

    iM3uReader->Interrupt();
    iM3uReader->Close();
    TestHttpReader::UriList uriList3;
    uriList3.push_back(&kUriVersion3Encrypted);
    TestHttpReader::BufList bufList3;
    bufList3.push_back(&kFileVersion3Encrypted);
    iHttpReader->SetContent(uriList3, bufList3);
    iM3uReader->SetUri(kUriVersion3Encrypted);

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 2833);
    TEST(segmentUri.AbsoluteUri() == Brn("http://media.example.com/fileSequence52-A.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 15000);
    TEST(segmentUri.AbsoluteUri() == Brn("http://media.example.com/fileSequence52-B.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 13333);
    TEST(segmentUri.AbsoluteUri() == Brn("http://media.example.com/fileSequence52-C.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 15000);
    TEST(segmentUri.AbsoluteUri() == Brn("http://media.example.com/fileSequence53-A.ts"));

    TEST(iTimer->StartCount() == 3);
    TEST(iTimer->CancelCount() == 2);
    TEST(iTimer->LastDurationMs() == 15000);
    TEST(iTimer->LastHandler() == iM3uReader);
}

void SuiteHlsM3uReader::TestInterrupt()
{
    // Have the reader waiting on timer to allow it to reload playlist and
    // call Interrupt(). Should cause it to return immediately and will not be
    // reusable until SetUri() is called again.

    const Uri kUri(Brn("http://example.com/hls_interrupt.m3u8"));
    const Brn kFile(
    "#EXTM3U\n"
    "#EXT-X-VERSION:2\n"
    "#EXT-X-TARGETDURATION:6\n"
    "#EXT-X-MEDIA-SEQUENCE:1234\n"
    "\n"
    "#EXTINF:6,\n"
    "https://priv.example.com/a.ts\n"
    "#EXTINF:5,\n"
    "https://priv.example.com/b.ts\n"
    "#EXTINF:4,\n"
    "https://priv.example.com/c.ts\n"
    );

    TestHttpReader::UriList uriList1;
    uriList1.push_back(&kUri);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&kFile);
    iHttpReader->SetContent(uriList1, bufList1);
    iM3uReader->SetUri(kUri);

    Uri segmentUri;
    TUint duration = 0;

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 6000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/a.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 5000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/b.ts"));

    duration = iM3uReader->NextSegmentUri(segmentUri);
    TEST(duration == 4000);
    TEST(segmentUri.AbsoluteUri() == Brn("https://priv.example.com/c.ts"));

    // Now, call NextSegmentUri() in another thread.
    // iM3uReader will block while waiting for timer to fire.
    // From this thread, call Interrupt(), and make sure NextSegmentUri() returns.
    ThreadFunctor functor("ThreadHlsM3uReader", MakeFunctor(*this, &SuiteHlsM3uReader::NextSegmentThread));
    functor.Start();
    iSem->Clear();
    iSem->Wait(kSemWaitMs);    // iM3uReader->NextSegmentUri() has been called in other thread.
    iM3uReader->Interrupt();
    iThreadSem->Wait(kSemWaitMs);   // Wait on iM3uReader->NextSegmentUri() returning.
    iM3uReader->Close();


    // Test interrupt while reading from stream.
    iHttpReader->SetContent(uriList1, bufList1);
    iHttpReader->BlockAtOffset(34);
    iM3uReader->SetUri(kUri);

    // Now, call NextSegmentUri() in another thread.
    // iReader will block at above offset.
    // From this thread, call Interrupt(), and make sure NextSegmentUri() returns.
    ThreadFunctor functor2("ThreadHlsM3uReader", MakeFunctor(*this, &SuiteHlsM3uReader::NextSegmentThread));
    functor2.Start();
    iSemReader->Clear();
    iSemReader->Wait(kSemWaitMs);   // iReader has blocked at above offset in other thread.
    iM3uReader->Interrupt();
    iThreadSem->Wait(kSemWaitMs);   // Wait on iM3uReader->NextSegmentUri() returning.
    iM3uReader->Close();



    // Test error thrown up from underlying stream reader.
    iHttpReader->SetContent(uriList1, bufList1);
    iHttpReader->ThrowReadErrorAtOffset(34);
    iM3uReader->SetUri(kUri);

    segmentUri.Clear();
    TEST_THROWS(iM3uReader->NextSegmentUri(segmentUri), HlsVariantPlaylistError);
    TEST(segmentUri.AbsoluteUri().Bytes() == 0);
}

void SuiteHlsM3uReader::TestFailedConnection()
{
    static const Uri kServingUri(Brn("http://dummy"));
    static const Uri kPlaylistUri(Brn("http://example.com/playlist.m3u8"));

    // Test error thrown up from underlying stream reader.
    TestHttpReader::UriList uriList1;
    uriList1.push_back(&kServingUri);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&Brx::Empty());
    iHttpReader->SetContent(uriList1, bufList1);    // Ensure the requested URI won't be recognised, so Connect() will fail.
    iM3uReader->SetUri(kPlaylistUri);
    Uri segmentUri;
    TEST_THROWS(iM3uReader->NextSegmentUri(segmentUri), HlsVariantPlaylistError);
}

void SuiteHlsM3uReader::TestInvalidAttributes()
{
    // Test attempting to load a malformed playlist where EXT-X-TARGETDURATION
    // is not a numeric value.
    const Uri kUri(Brn("http://example.com/hls_invalid_target_duration.m3u8"));
    const Brn kFileInvalidTargetDuration(
    "#EXTM3U\r\n"
    "#EXT-X-VERSION:2\r\n"
    "#EXT-X-TARGETDURATION:abc\r\n"
    "#EXT-X-MEDIA-SEQUENCE:1234\r\n"
    "\r\n"
    "#EXTINF:6,\r\n"
    "https://priv.example.com/a.ts\n"
    "#EXTINF:5,\r\n"
    "https://priv.example.com/b.ts\n"
    "#EXTINF:4,\r\n"
    "https://priv.example.com/c.ts\n"
    );

    TestHttpReader::UriList uriList1;
    uriList1.push_back(&kUri);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&kFileInvalidTargetDuration);
    iHttpReader->SetContent(uriList1, bufList1);
    iM3uReader->SetUri(kUri);
    Uri segmentUri;
    TEST_THROWS(iM3uReader->NextSegmentUri(segmentUri), HlsVariantPlaylistError);
}


// SuiteSegmentStreamer

SuiteSegmentStreamer::SuiteSegmentStreamer()
    : SuiteUnitTest("SuiteSegmentStreamer")
{
    AddTest(MakeFunctor(*this, &SuiteSegmentStreamer::TestSetStream), "TestSetStream");
    AddTest(MakeFunctor(*this, &SuiteSegmentStreamer::TestRead), "TestRead");
    AddTest(MakeFunctor(*this, &SuiteSegmentStreamer::TestGetNextSegmentFail), "TestGetNextSegmentFail");
    AddTest(MakeFunctor(*this, &SuiteSegmentStreamer::TestInterrupt), "TestInterrupt");
}

void SuiteSegmentStreamer::Setup()
{
    iUriProvider = new TestSegmentUriProvider();
    iSemReader = new Semaphore("SSSS", 0);
    iSemWait = new Semaphore("SSWS", 0);
    iHttpReader = new TestHttpReader(*iSemReader, *iSemWait);
    iStreamer = new SegmentStreamer(*iHttpReader, *iHttpReader);
    iReadBytes = 0;
    iThreadSem = new Semaphore("SSTS", 0);
}

void SuiteSegmentStreamer::TearDown()
{
    iStreamer->Close();
    delete iThreadSem;
    delete iStreamer;
    delete iHttpReader;
    delete iSemWait;
    delete iSemReader;
    delete iUriProvider;
}

void SuiteSegmentStreamer::ReadThread()
{
    TEST_THROWS(iStreamer->Read(iReadBytes), ReaderError);
    iThreadSem->Signal();
}

void SuiteSegmentStreamer::TestSetStream()
{
    const Uri kUri1(Brn("http://example.com/seg_a.ts"));

    iUriProvider->SetUri(kUri1, 0);
    iStreamer->Stream(*iUriProvider);

    // Try call Stream() again.
    iStreamer->ReadInterrupt();
    iStreamer->Stream(*iUriProvider);

    // Try call Stream() without calling ReadInterrupt();
    TEST_THROWS(iStreamer->Stream(*iUriProvider), AssertionFailed);
}

void SuiteSegmentStreamer::TestRead()
{
    const Uri kUri1(Brn("http://example.com/seg_a.ts"));
    const Brn kBuf1("abcdefghijklmnopqrstuvwxyz");
    const Uri kUri2(Brn("http://example.com/seg_b.ts"));
    const Brn kBuf2("ABCDEFGHIJKLMNOPQRSTUVWXYZ");



    // Test reading up to segment boundaries.

    TestHttpReader::UriList uriList1;
    uriList1.push_back(&kUri1);
    uriList1.push_back(&kUri2);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&kBuf1);
    bufList1.push_back(&kBuf2);
    iHttpReader->SetContent(uriList1, bufList1);
    iUriProvider->SetUri(kUri1, 50);
    iStreamer->Stream(*iUriProvider);

    // Start streaming some audio.
    Brn buf = iStreamer->Read(20);
    TEST(buf == Brn("abcdefghijklmnopqrst"));
    // Set next segment up.
    iUriProvider->SetUri(kUri2, 50);
    // Now, read until end of current segment.
    buf = iStreamer->Read(6);
    TEST(buf == Brn("uvwxyz"));
    // Request more data; streamer should seamlessly start supplying from next segment.
    buf = iStreamer->Read(26);
    TEST(buf == kBuf2);



    // Current behaviour of each read request is to only read (at most) up to end of each segment.
    // So, attempt to read more than amount buffered. Should throw ReaderError, then ReadRemaining() can be called.
    iStreamer->ReadInterrupt();
    iStreamer->Close();
    iUriProvider->SetUri(kUri1, 50);
    iHttpReader->SetContent(uriList1, bufList1);
    iStreamer->Stream(*iUriProvider);

    // Start streaming some audio.
    buf = iStreamer->Read(20);
    TEST(buf == Brn("abcdefghijklmnopqrst"));
    // Attempt to read another 20 bytes.
    TEST_THROWS(iStreamer->Read(20), ReaderError);
    buf = iStreamer->ReadRemaining();
    TEST(buf == Brn("uvwxyz"));



    // Test ReadUntil().
    iStreamer->ReadInterrupt();
    iStreamer->Close();
    iUriProvider->SetUri(kUri1, 50);
    iHttpReader->SetContent(uriList1, bufList1);
    iStreamer->Stream(*iUriProvider);

    buf = iStreamer->ReadUntil('z');
    TEST(buf == Brn("abcdefghijklmnopqrstuvwxy"));
}

void SuiteSegmentStreamer::TestGetNextSegmentFail()
{
    // Check HlsVariantPlaylistErrors are passed up.
    iUriProvider->SetPlaylistError();
    iStreamer->Stream(*iUriProvider);

    TEST_THROWS(iStreamer->Read(10), HlsVariantPlaylistError);


    // Check HlsEndOfStream errors are passed up.
    iUriProvider->Clear();
    iUriProvider->SetEndOfStream();
    iStreamer->ReadInterrupt();
    iStreamer->Stream(*iUriProvider);

    TEST_THROWS(iStreamer->Read(10), HlsEndOfStream);
}

void SuiteSegmentStreamer::TestInterrupt()
{
    // Test ReadInterrupt() called while reading.
    const Uri kUri1(Brn("http://example.com/seg_a.ts"));
    const Brn kBuf1("abcdefghijklmnopqrstuvwxyz");

    TestHttpReader::UriList uriList1;
    uriList1.push_back(&kUri1);
    TestHttpReader::BufList bufList1;
    bufList1.push_back(&kBuf1);
    iHttpReader->SetContent(uriList1, bufList1);
    iUriProvider->SetUri(kUri1, 50);
    iHttpReader->BlockAtOffset(20);
    iStreamer->Stream(*iUriProvider);

    iReadBytes = 26;

    ThreadFunctor functor("ThreadSegStreamer", MakeFunctor(*this, &SuiteSegmentStreamer::ReadThread));
    functor.Start();
    iSemReader->Clear();
    iSemReader->Wait(kSemWaitMs);    // iStreamer->Read(iReadBytes) has been called in other thread.
    iStreamer->ReadInterrupt();
    iThreadSem->Wait(kSemWaitMs);   // Wait on iStreamer->Read() returning.
    iStreamer->Close();



    // Test interrupt thrown from underlying stream reader.
    iUriProvider->SetUri(kUri1, 50);
    iHttpReader->SetContent(uriList1, bufList1);
    iHttpReader->ThrowReadErrorAtOffset(20);
    iStreamer->Stream(*iUriProvider);

    TEST_THROWS(iStreamer->Read(26), ReaderError);



    // Test failed connection.
    static const Uri kUriDummy(Brn("http://dummy"));
    iStreamer->ReadInterrupt();
    iStreamer->Close();
    TestHttpReader::UriList uriList2;
    uriList2.push_back(&kUriDummy);
    TestHttpReader::BufList bufList2;
    bufList2.push_back(&Brx::Empty());
    iHttpReader->SetContent(uriList2, bufList2);    // Can force a failed connection by ensuring iHttpReader does not recognise the URI iStreamer will ask for.
    iUriProvider->SetUri(kUri1, 50);
    iStreamer->Stream(*iUriProvider);
    TEST_THROWS(iStreamer->Read(26), HlsSegmentError);
}


// SuiteProtocolHls

SuiteProtocolHls::SuiteProtocolHls(Environment& aEnv)
    : SuiteUnitTest("SuiteProtocolHls")
    , iEnv(aEnv)
{
    AddTest(MakeFunctor(*this, &SuiteProtocolHls::TestStreamSuccessful), "TestStreamSuccessful");
    AddTest(MakeFunctor(*this, &SuiteProtocolHls::TestStreamErrorRecoverable), "TestStreamErrorRecoverable");
    AddTest(MakeFunctor(*this, &SuiteProtocolHls::TestStreamM3uError), "TestStreamM3uError");
    AddTest(MakeFunctor(*this, &SuiteProtocolHls::TestStreamSegmentError), "TestStreamSegmentError");
    AddTest(MakeFunctor(*this, &SuiteProtocolHls::TestGet), "TestGet");
    AddTest(MakeFunctor(*this, &SuiteProtocolHls::TestTrySeek), "TestTrySeek");
    AddTest(MakeFunctor(*this, &SuiteProtocolHls::TestTryStop), "TestTryStop");
    AddTest(MakeFunctor(*this, &SuiteProtocolHls::TestTryGet), "TestTryGet");
    AddTest(MakeFunctor(*this, &SuiteProtocolHls::TestInterrupt), "TestInterrupt");
}


void SuiteProtocolHls::Setup()
{
    iThreadSem = new Semaphore("HLTS", 0);
    iM3uSem = new Semaphore("HLMS", 0);
    iM3uWaitSem = new Semaphore("HMWS", 0);
    iM3uReader = new TestHttpReader(*iM3uSem, *iM3uWaitSem);
    iSegmentSem = new Semaphore("HLSS", 0);
    iSegmentWaitSem = new Semaphore("HSWS", 0);
    iSegmentReader = new TestHttpReader(*iSegmentSem, *iSegmentWaitSem);
    iProtocolHls = HlsTestFactory::NewTestableHls(iEnv, iM3uReader, iSegmentReader);    // takes ownership of iM3uReader, iSegmentReader.

    iInfoAggregator = new AllocatorInfoLogger();
    iTrackFactory= new TrackFactory(*iInfoAggregator, 1);
    iMsgFactory = new MsgFactory(*iInfoAggregator, 100, 100, 1, 1, 1, 1, 1, 1, 10, 10, 10, 1, 10, 1, 1, 10, 1, 1);
    iIdProvider = new TestPipelineIdProvider();
    iFlushIdProvider = new TestFlushIdProvider();
    iElementDownstream = new TestElementDownstream();
    iProtocolManager = new ProtocolManager(*iElementDownstream, *iMsgFactory, *iIdProvider, *iFlushIdProvider);

    iProtocolManager->Add(iProtocolHls);    // takes ownership

    iTrack = NULL;
    iResult = EProtocolStreamSuccess;
}

void SuiteProtocolHls::TearDown()
{
    delete iProtocolManager;
    delete iElementDownstream;
    delete iFlushIdProvider;
    delete iIdProvider;
    delete iMsgFactory;
    delete iTrackFactory;
    delete iInfoAggregator;

    //delete iSegmentReader;    // owned by ProtocolHls
    delete iSegmentSem;
    //delete iM3uReader;        // owned by ProtocolHls
    delete iM3uSem;
    delete iThreadSem;
}

void SuiteProtocolHls::StreamThread()
{
    iResult = iProtocolManager->DoStream(*iTrack);
    iThreadSem->Signal();
}

void SuiteProtocolHls::TestStreamSuccessful()
{
    static const Brn kUriHlsEndList("hls://example.com/hls_endlist_end.m3u8");
    static const Uri kUriEndlistEnd(Brn("http://example.com/hls_endlist_end.m3u8"));
    static const Brn kFileEndlistEnd(
    "#EXTM3U\n"
    "#EXT-X-TARGETDURATION:10\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/first.ts\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/second.ts\n"
    "#EXTINF:3.003,\n"
    "http://media.example.com/third.ts\n"
    "#EXT-X-ENDLIST\n");

    TestHttpReader::UriList uriListM3u1;
    uriListM3u1.push_back(&kUriEndlistEnd);
    TestHttpReader::BufList bufListM3u1;
    bufListM3u1.push_back(&kFileEndlistEnd);
    iM3uReader->SetContent(uriListM3u1, bufListM3u1);


    static const Uri kSegUri1(Brn("http://media.example.com/first.ts"));
    static const Brn kSegFile1(Brn("abcdefghijklmnopqrstuvwxyz"));
    static const Uri kSegUri2(Brn("http://media.example.com/second.ts"));
    static const Brn kSegFile2(Brn("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    static const Uri kSegUri3(Brn("http://media.example.com/third.ts"));
    static const Brn kSegFile3(Brn("1234567890"));

    TestHttpReader::UriList uriListSeg1;
    uriListSeg1.push_back(&kSegUri1);
    uriListSeg1.push_back(&kSegUri2);
    uriListSeg1.push_back(&kSegUri3);
    TestHttpReader::BufList bufListSeg1;
    bufListSeg1.push_back(&kSegFile1);
    bufListSeg1.push_back(&kSegFile2);
    bufListSeg1.push_back(&kSegFile3);
    iSegmentReader->SetContent(uriListSeg1, bufListSeg1);

    // ProtocolHls needs to take a URI starting with hls://; not http:// !
    Track* track = iTrackFactory->CreateTrack(kUriHlsEndList, Brx::Empty());
    ProtocolStreamResult res = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(res == EProtocolStreamSuccess);

    TEST(iElementDownstream->Data() == Brn("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"));
    TEST(iElementDownstream->IsLive() == true);
    TEST(iElementDownstream->StreamId() == 1);
    TEST(iElementDownstream->TrackCount() == 1);
    TEST(iElementDownstream->StreamCount() == 1);
}

void SuiteProtocolHls::TestStreamErrorRecoverable()
{
    // ProtocolHls needs to take a URI starting with hls://; not http:// !
    static const Brn kUriHlsEndList("hls://example.com/hls_endlist_end.m3u8");
    static const Uri kUriEndlistEnd(Brn("http://example.com/hls_endlist_end.m3u8"));
    static const Brn kFileEndlistEnd(
    "#EXTM3U\n"
    "#EXT-X-TARGETDURATION:10\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/first.ts\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/second.ts\n"
    "#EXTINF:3.003,\n"
    "http://media.example.com/third.ts\n"
    "#EXT-X-ENDLIST\n");

    TestHttpReader::UriList uriListM3u1;
    uriListM3u1.push_back(&kUriEndlistEnd);
    TestHttpReader::BufList bufListM3u1;
    bufListM3u1.push_back(&kFileEndlistEnd);
    iM3uReader->SetContent(uriListM3u1, bufListM3u1);


    static const Uri kSegUri1(Brn("http://media.example.com/first.ts"));
    static const Brn kSegFile1(Brn("abcdefghijklmnopqrstuvwxyz"));
    static const Uri kSegUri2(Brn("http://media.example.com/second.ts"));
    static const Brn kSegFile2(Brn("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    static const Uri kSegUri3(Brn("http://media.example.com/third.ts"));
    static const Brn kSegFile3(Brn("1234567890"));

    TestHttpReader::UriList uriListSeg1;
    uriListSeg1.push_back(&kSegUri1);
    uriListSeg1.push_back(&kSegUri2);
    uriListSeg1.push_back(&kSegUri3);
    TestHttpReader::BufList bufListSeg1;
    bufListSeg1.push_back(&kSegFile1);
    bufListSeg1.push_back(&kSegFile2);
    bufListSeg1.push_back(&kSegFile3);
    iSegmentReader->SetContent(uriListSeg1, bufListSeg1);

    iSegmentReader->ThrowReadErrorAtOffset(20); // Will cause a ReaderError to be thrown up by underlying reader, but ProtocolHls should retry and successfully read whole stream.

    iTrack = iTrackFactory->CreateTrack(kUriHlsEndList, Brx::Empty());
    ThreadFunctor thread("SuiteProtocolHls", MakeFunctor(*this, &SuiteProtocolHls::StreamThread));
    thread.Start();

    iThreadSem->Wait();//kSemWaitMs);

    iTrack->RemoveRef();
    TEST(iResult == EProtocolStreamSuccess);

    TEST(iElementDownstream->Data() == Brn("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"));  // ProtocolHls should have successfully read all data.
    TEST(iElementDownstream->IsLive() == true);
    TEST(iElementDownstream->StreamId() == 1);
    TEST(iElementDownstream->TrackCount() == 1);
    TEST(iElementDownstream->StreamCount() == 1);
    TEST(iElementDownstream->FlushCount() == 0);
}

void SuiteProtocolHls::TestStreamM3uError()
{
    static const Brn kUriHlsEndList("hls://example.com/hls_endlist_end.m3u8");
    static const Uri kUriEndlistEnd(Brn("http://example.com/hls_endlist_end.m3u8"));
    static const Brn kFileEndlistEnd(   // corrupt M3U with invalid EXT-X-TARGETDURATION
    "#EXTM3U\n"
    "#EXT-X-TARGETDURATION:abc\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/first.ts\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/second.ts\n"
    "#EXTINF:3.003,\n"
    "http://media.example.com/third.ts\n"
    "#EXT-X-ENDLIST\n");

    TestHttpReader::UriList uriListM3u1;
    uriListM3u1.push_back(&kUriEndlistEnd);
    TestHttpReader::BufList bufListM3u1;
    bufListM3u1.push_back(&kFileEndlistEnd);
    iM3uReader->SetContent(uriListM3u1, bufListM3u1);


    static const Uri kSegUri1(Brn("http://media.example.com/first.ts"));
    static const Brn kSegFile1(Brn("abcdefghijklmnopqrstuvwxyz"));
    static const Uri kSegUri2(Brn("http://media.example.com/second.ts"));
    static const Brn kSegFile2(Brn("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    static const Uri kSegUri3(Brn("http://media.example.com/third.ts"));
    static const Brn kSegFile3(Brn("1234567890"));

    TestHttpReader::UriList uriListSeg1;
    uriListSeg1.push_back(&kSegUri1);
    uriListSeg1.push_back(&kSegUri2);
    uriListSeg1.push_back(&kSegUri3);
    TestHttpReader::BufList bufListSeg1;
    bufListSeg1.push_back(&kSegFile1);
    bufListSeg1.push_back(&kSegFile2);
    bufListSeg1.push_back(&kSegFile3);
    iSegmentReader->SetContent(uriListSeg1, bufListSeg1);

    // ProtocolHls needs to take a URI starting with hls://; not http:// !
    Track* track = iTrackFactory->CreateTrack(kUriHlsEndList, Brx::Empty());
    ProtocolStreamResult res = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(res == EProtocolStreamErrorUnrecoverable);

    TEST(iElementDownstream->Data().Bytes() == 0);
    TEST(iElementDownstream->IsLive() == true);
    TEST(iElementDownstream->StreamId() == 1);
    TEST(iElementDownstream->TrackCount() == 1);
    TEST(iElementDownstream->StreamCount() == 1);
}

void SuiteProtocolHls::TestStreamSegmentError()
{
    // ProtocolHls needs to take a URI starting with hls://; not http:// !
    static const Brn kUriHlsEndList("hls://example.com/hls_endlist_end.m3u8");
    static const Uri kUriEndlistEnd(Brn("http://example.com/hls_endlist_end.m3u8"));
    static const Brn kFileEndlistEnd(
    "#EXTM3U\n"
    "#EXT-X-TARGETDURATION:10\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/first.ts\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/second.ts\n"
    "#EXTINF:3.003,\n"
    "http://media.example.com/third.ts\n"
    "#EXT-X-ENDLIST\n");

    TestHttpReader::UriList uriListM3u1;
    uriListM3u1.push_back(&kUriEndlistEnd);
    TestHttpReader::BufList bufListM3u1;
    bufListM3u1.push_back(&kFileEndlistEnd);
    iM3uReader->SetContent(uriListM3u1, bufListM3u1);


    static const Uri kSegUri1(Brn("http://media.example.com/first.ts"));
    static const Brn kSegFile1(Brn("abcdefghijklmnopqrstuvwxyz"));
    static const Uri kSegUri2(Brn("http://media.example.com/second.ts"));
    static const Brn kSegFile2(Brn("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    static const Uri kSegUri3(Brn("http://media.example.com/dummy.ts"));    // Doesn't match third URI in playlist, so should cause an error.
    static const Brn kSegFile3(Brn("1234567890"));

    TestHttpReader::UriList uriListSeg1;
    uriListSeg1.push_back(&kSegUri1);
    uriListSeg1.push_back(&kSegUri2);
    uriListSeg1.push_back(&kSegUri3);
    TestHttpReader::BufList bufListSeg1;
    bufListSeg1.push_back(&kSegFile1);
    bufListSeg1.push_back(&kSegFile2);
    bufListSeg1.push_back(&kSegFile3);
    iSegmentReader->SetContent(uriListSeg1, bufListSeg1);


    Track* track = iTrackFactory->CreateTrack(kUriHlsEndList, Brx::Empty());
    ProtocolStreamResult res = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(res == EProtocolStreamErrorUnrecoverable);

    TEST(iElementDownstream->Data() == Brn("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    TEST(iElementDownstream->IsLive() == true);
    TEST(iElementDownstream->StreamId() == 1);
    TEST(iElementDownstream->TrackCount() == 1);
    TEST(iElementDownstream->StreamCount() == 1);
}

void SuiteProtocolHls::TestGet()
{
    Bws<1> buf;
    WriterBuffer writerBuf(buf);

    //IProtocolManager* protocolManager = (IProtocolManager*)iProtocolManager;
    //TBool result = protocolManager->Get(writerBuf, Brn("http://example.com/dummy.ts"), 0, 20);
    //TEST(result == false);

    // FIXME - reinstate
}

void SuiteProtocolHls::TestTrySeek()
{
    // ProtocolHls needs to take a URI starting with hls://; not http:// !
    static const Brn kUriHlsEndList("hls://example.com/hls_endlist_end.m3u8");
    static const Uri kUriEndlistEnd(Brn("http://example.com/hls_endlist_end.m3u8"));
    static const Brn kFileEndlistEnd(
    "#EXTM3U\n"
    "#EXT-X-TARGETDURATION:10\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/first.ts\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/second.ts\n"
    "#EXTINF:3.003,\n"
    "http://media.example.com/third.ts\n"
    "#EXT-X-ENDLIST\n");

    TestHttpReader::UriList uriListM3u1;
    uriListM3u1.push_back(&kUriEndlistEnd);
    TestHttpReader::BufList bufListM3u1;
    bufListM3u1.push_back(&kFileEndlistEnd);
    iM3uReader->SetContent(uriListM3u1, bufListM3u1);


    static const Uri kSegUri1(Brn("http://media.example.com/first.ts"));
    static const Brn kSegFile1(Brn("abcdefghijklmnopqrstuvwxyz"));
    static const Uri kSegUri2(Brn("http://media.example.com/second.ts"));
    static const Brn kSegFile2(Brn("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    static const Uri kSegUri3(Brn("http://media.example.com/third.ts"));
    static const Brn kSegFile3(Brn("1234567890"));

    TestHttpReader::UriList uriListSeg1;
    uriListSeg1.push_back(&kSegUri1);
    uriListSeg1.push_back(&kSegUri2);
    uriListSeg1.push_back(&kSegUri3);
    TestHttpReader::BufList bufListSeg1;
    bufListSeg1.push_back(&kSegFile1);
    bufListSeg1.push_back(&kSegFile2);
    bufListSeg1.push_back(&kSegFile3);
    iSegmentReader->SetContent(uriListSeg1, bufListSeg1);

    iSegmentReader->WaitAtOffset(20);

    iTrack = iTrackFactory->CreateTrack(kUriHlsEndList, Brx::Empty());
    ThreadFunctor thread("SuiteProtocolHls", MakeFunctor(*this, &SuiteProtocolHls::StreamThread));
    thread.Start();

    iSegmentSem->Wait();//kSemWaitMs);

    static const TUint kExpectedStreamId = 1;
    IStreamHandler* streamHandler = iElementDownstream->StreamHandler();
    TEST(streamHandler != NULL);
    TUint resultSeek = streamHandler->TrySeek(kExpectedStreamId, 0);
    TEST(resultSeek == MsgFlush::kIdInvalid);

    iSegmentWaitSem->Signal();//kSemWaitMs);
    iThreadSem->Wait();//kSemWaitMs);

    iTrack->RemoveRef();
    TEST(iResult == EProtocolStreamSuccess);

    TEST(iElementDownstream->Data() == Brn("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"));
    TEST(iElementDownstream->IsLive() == true);
    TEST(iElementDownstream->StreamId() == kExpectedStreamId);
    TEST(iElementDownstream->TrackCount() == 1);
    TEST(iElementDownstream->StreamCount() == 1);
}

void SuiteProtocolHls::TestTryStop()
{
    // ProtocolHls needs to take a URI starting with hls://; not http:// !
    static const Brn kUriHlsEndList("hls://example.com/hls_endlist_end.m3u8");
    static const Uri kUriEndlistEnd(Brn("http://example.com/hls_endlist_end.m3u8"));
    static const Brn kFileEndlistEnd(
    "#EXTM3U\n"
    "#EXT-X-TARGETDURATION:10\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/first.ts\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/second.ts\n"
    "#EXTINF:3.003,\n"
    "http://media.example.com/third.ts\n"
    "#EXT-X-ENDLIST\n");

    TestHttpReader::UriList uriListM3u1;
    uriListM3u1.push_back(&kUriEndlistEnd);
    TestHttpReader::BufList bufListM3u1;
    bufListM3u1.push_back(&kFileEndlistEnd);
    iM3uReader->SetContent(uriListM3u1, bufListM3u1);


    static const Uri kSegUri1(Brn("http://media.example.com/first.ts"));
    static const Brn kSegFile1(Brn("abcdefghijklmnopqrstuvwxyz"));
    static const Uri kSegUri2(Brn("http://media.example.com/second.ts"));
    static const Brn kSegFile2(Brn("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    static const Uri kSegUri3(Brn("http://media.example.com/third.ts"));
    static const Brn kSegFile3(Brn("1234567890"));

    TestHttpReader::UriList uriListSeg1;
    uriListSeg1.push_back(&kSegUri1);
    uriListSeg1.push_back(&kSegUri2);
    uriListSeg1.push_back(&kSegUri3);
    TestHttpReader::BufList bufListSeg1;
    bufListSeg1.push_back(&kSegFile1);
    bufListSeg1.push_back(&kSegFile2);
    bufListSeg1.push_back(&kSegFile3);
    iSegmentReader->SetContent(uriListSeg1, bufListSeg1);

    iSegmentReader->BlockAtOffset(20);  // needs to be unblocked by ReadInterrupt(), which should be initiated by protocol module

    iTrack = iTrackFactory->CreateTrack(kUriHlsEndList, Brx::Empty());
    ThreadFunctor thread("SuiteProtocolHls", MakeFunctor(*this, &SuiteProtocolHls::StreamThread));
    thread.Start();

    iSegmentSem->Wait();//kSemWaitMs);

    static const TUint kExpectedStreamId = 1;
    IStreamHandler* streamHandler = iElementDownstream->StreamHandler();
    TEST(streamHandler != NULL);
    TUint resultStop = streamHandler->TryStop(kExpectedStreamId);
    TEST(resultStop == 1);

    iSegmentWaitSem->Signal();//kSemWaitMs);
    iThreadSem->Wait();//kSemWaitMs);

    iTrack->RemoveRef();
    TEST(iResult == EProtocolStreamStopped);

    TEST(iElementDownstream->Data() == Brn("abcdefghijklmnopqrstuvwxyz"));  // Only 20 bytes will have been read by time ReadInterrupt() was called, but ContentAudio() will call ReadRemaining() after ReaderError is thrown as a result of the ReadInterrupt().
    TEST(iElementDownstream->IsLive() == true);
    TEST(iElementDownstream->StreamId() == kExpectedStreamId);
    TEST(iElementDownstream->TrackCount() == 1);
    TEST(iElementDownstream->StreamCount() == 1);
    TEST(iElementDownstream->FlushCount() == 1);
}

void SuiteProtocolHls::TestTryGet()
{
    // ProtocolHls needs to take a URI starting with hls://; not http:// !
    static const Brn kUriHlsEndList("hls://example.com/hls_endlist_end.m3u8");
    static const Uri kUriEndlistEnd(Brn("http://example.com/hls_endlist_end.m3u8"));
    static const Brn kFileEndlistEnd(
    "#EXTM3U\n"
    "#EXT-X-TARGETDURATION:10\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/first.ts\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/second.ts\n"
    "#EXTINF:3.003,\n"
    "http://media.example.com/third.ts\n"
    "#EXT-X-ENDLIST\n");

    TestHttpReader::UriList uriListM3u1;
    uriListM3u1.push_back(&kUriEndlistEnd);
    TestHttpReader::BufList bufListM3u1;
    bufListM3u1.push_back(&kFileEndlistEnd);
    iM3uReader->SetContent(uriListM3u1, bufListM3u1);


    static const Uri kSegUri1(Brn("http://media.example.com/first.ts"));
    static const Brn kSegFile1(Brn("abcdefghijklmnopqrstuvwxyz"));
    static const Uri kSegUri2(Brn("http://media.example.com/second.ts"));
    static const Brn kSegFile2(Brn("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    static const Uri kSegUri3(Brn("http://media.example.com/third.ts"));
    static const Brn kSegFile3(Brn("1234567890"));

    TestHttpReader::UriList uriListSeg1;
    uriListSeg1.push_back(&kSegUri1);
    uriListSeg1.push_back(&kSegUri2);
    uriListSeg1.push_back(&kSegUri3);
    TestHttpReader::BufList bufListSeg1;
    bufListSeg1.push_back(&kSegFile1);
    bufListSeg1.push_back(&kSegFile2);
    bufListSeg1.push_back(&kSegFile3);
    iSegmentReader->SetContent(uriListSeg1, bufListSeg1);

    iSegmentReader->WaitAtOffset(20);

    iTrack = iTrackFactory->CreateTrack(kUriHlsEndList, Brx::Empty());
    ThreadFunctor thread("SuiteProtocolHls", MakeFunctor(*this, &SuiteProtocolHls::StreamThread));
    thread.Start();

    iSegmentSem->Wait();//kSemWaitMs);

    static const TUint kExpectedStreamId = 1;
    Bws<1> buf;
    WriterBuffer writerBuf(buf);
    IStreamHandler* streamHandler = iElementDownstream->StreamHandler();
    TEST(streamHandler != NULL);
    TBool resultGet = streamHandler->TryGet(writerBuf, kExpectedStreamId, 0, 20);
    TEST(resultGet == false);

    iSegmentWaitSem->Signal();//kSemWaitMs);
    iThreadSem->Wait();//kSemWaitMs);

    iTrack->RemoveRef();
    TEST(iResult == EProtocolStreamSuccess);

    TEST(iElementDownstream->Data() == Brn("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"));
    TEST(iElementDownstream->IsLive() == true);
    TEST(iElementDownstream->StreamId() == kExpectedStreamId);
    TEST(iElementDownstream->TrackCount() == 1);
    TEST(iElementDownstream->StreamCount() == 1);
}

void SuiteProtocolHls::TestInterrupt()
{
    // ProtocolHls needs to take a URI starting with hls://; not http:// !
    static const Brn kUriHlsEndList("hls://example.com/hls_endlist_end.m3u8");
    static const Uri kUriEndlistEnd(Brn("http://example.com/hls_endlist_end.m3u8"));
    static const Brn kFileEndlistEnd(
    "#EXTM3U\n"
    "#EXT-X-TARGETDURATION:10\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/first.ts\n"
    "#EXTINF:9.009,\n"
    "http://media.example.com/second.ts\n"
    "#EXTINF:3.003,\n"
    "http://media.example.com/third.ts\n"
    "#EXT-X-ENDLIST\n");

    TestHttpReader::UriList uriListM3u1;
    uriListM3u1.push_back(&kUriEndlistEnd);
    TestHttpReader::BufList bufListM3u1;
    bufListM3u1.push_back(&kFileEndlistEnd);
    iM3uReader->SetContent(uriListM3u1, bufListM3u1);


    static const Uri kSegUri1(Brn("http://media.example.com/first.ts"));
    static const Brn kSegFile1(Brn("abcdefghijklmnopqrstuvwxyz"));
    static const Uri kSegUri2(Brn("http://media.example.com/second.ts"));
    static const Brn kSegFile2(Brn("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    static const Uri kSegUri3(Brn("http://media.example.com/third.ts"));
    static const Brn kSegFile3(Brn("1234567890"));

    TestHttpReader::UriList uriListSeg1;
    uriListSeg1.push_back(&kSegUri1);
    uriListSeg1.push_back(&kSegUri2);
    uriListSeg1.push_back(&kSegUri3);
    TestHttpReader::BufList bufListSeg1;
    bufListSeg1.push_back(&kSegFile1);
    bufListSeg1.push_back(&kSegFile2);
    bufListSeg1.push_back(&kSegFile3);
    iSegmentReader->SetContent(uriListSeg1, bufListSeg1);

    iSegmentReader->BlockAtOffset(20);  // Needs to be unblocked by calling ReadInterrupt() (via ProtocolHls).

    iTrack = iTrackFactory->CreateTrack(kUriHlsEndList, Brx::Empty());
    ThreadFunctor thread("SuiteProtocolHls", MakeFunctor(*this, &SuiteProtocolHls::StreamThread));
    thread.Start();

    iSegmentSem->Wait();//kSemWaitMs);

    iProtocolManager->Interrupt(true);

    iSegmentWaitSem->Signal();//kSemWaitMs);
    iThreadSem->Wait();//kSemWaitMs);

    iTrack->RemoveRef();
    TEST(iResult == EProtocolStreamStopped);

    TEST(iElementDownstream->Data() == Brn("abcdefghijklmnopqrstuvwxyz"));
    TEST(iElementDownstream->IsLive() == true);
    TEST(iElementDownstream->StreamId() == 1);
    TEST(iElementDownstream->TrackCount() == 1);
    TEST(iElementDownstream->StreamCount() == 1);
    TEST(iElementDownstream->FlushCount() == 0);
}



void TestProtocolHls(Environment& aEnv)
{
    Runner runner("HLS tests\n");
    runner.Add(new SuiteHlsM3uReader());
    runner.Add(new SuiteSegmentStreamer());
    runner.Add(new SuiteProtocolHls(aEnv));
    runner.Run();
}
