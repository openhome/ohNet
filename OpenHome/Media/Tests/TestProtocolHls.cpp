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

class TestHttpReader : public IHttpSocket, public IReaderBuffered
{
public:
    TestHttpReader(Semaphore& aObserverSem);
    void SetContentOnReconnect(const Uri& aUri, const Brx& aBuf);
    void BlockAtOffset(TUint64 aOffset);
    void ThrowReadErrorAtOffset(TUint64 aOffset);
    TUint ConnectCount() const;
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
    Uri iUriCurrent;
    Brn iBufCurrent;
    ReaderBuffer iReader;
    Uri iUriNext;
    Brn iBufNext;
    TUint64 iOffset;
    TUint64 iBlockOffset;
    Semaphore& iObserverSem;
    Semaphore iBlockSem;
    TUint64 iThrowOffset;
    TUint iConnectCount;
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

class SuiteHlsM3uReader : public OpenHome::TestFramework::SuiteUnitTest
{
private:
    static const TUint kSemWaitMs = 0;//50;
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
    TestHttpReader* iHttpReader;
    SegmentStreamer* iStreamer;
    TUint iReadBytes;
    Semaphore* iThreadSem;
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

TestHttpReader::TestHttpReader(Semaphore& aObserverSem)
    : iBlockSem("THRS", 0)
    , iObserverSem(aObserverSem)
{
}

void TestHttpReader::SetContentOnReconnect(const Uri& aUri, const Brx& aBuf)
{
    iUriNext.Replace(aUri.AbsoluteUri());
    iBufNext.Set(aBuf);
    iBlockOffset = std::numeric_limits<TUint64>::max();
    iThrowOffset = std::numeric_limits<TUint64>::max();
}

void TestHttpReader::BlockAtOffset(TUint64 aOffset)
{
    ASSERT(iThrowOffset == std::numeric_limits<TUint64>::max());
    iBlockOffset = aOffset;
}

void TestHttpReader::ThrowReadErrorAtOffset(TUint64 aOffset)
{
    ASSERT(iBlockOffset == std::numeric_limits<TUint64>::max());
    iThrowOffset = aOffset;
}

TUint TestHttpReader::ConnectCount() const
{
    return iConnectCount;
}

TBool TestHttpReader::Connect(const Uri& aUri)
{
    iConnectCount++;
    if (aUri.AbsoluteUri() == iUriNext.AbsoluteUri()) {
        iUriCurrent.Replace(iUriNext.AbsoluteUri());
        iBufCurrent.Set(iBufNext);
        iReader.Set(iBufCurrent);

        iBlockSem.Clear();
        iOffset = 0;
        return true;
    }
    return false;
}

void TestHttpReader::Close()
{
}

TUint TestHttpReader::ContentLength() const
{
    return iBufCurrent.Bytes();
}

Brn TestHttpReader::Read(TUint aBytes)
{
    Brn buf = iReader.Read(aBytes);
    iOffset += buf.Bytes();
    if (iOffset >= iBlockOffset) {
        iObserverSem.Signal();
        iBlockSem.Wait();
        THROW(ReaderError);
    }
    else if (iOffset >= iThrowOffset) {
        THROW(ReaderError);
    }
    return buf;
}

Brn TestHttpReader::ReadUntil(TByte aSeparator)
{
    Brn buf = iReader.ReadUntil(aSeparator);
    iOffset += buf.Bytes();
    if (iOffset >= iBlockOffset) {
        iObserverSem.Signal();
        iBlockSem.Wait();
        THROW(ReaderError);
    }
    else if (iOffset >= iThrowOffset) {
        THROW(ReaderError);
    }
    return buf;
}

void TestHttpReader::ReadFlush()
{
    iReader.ReadFlush();
}

void TestHttpReader::ReadInterrupt()
{
    iReader.ReadInterrupt();
    iBlockSem.Signal();
}

Brn TestHttpReader::ReadRemaining()
{
    Brn buf = iReader.ReadRemaining();
    iOffset += buf.Bytes();
    if (iOffset >= iBlockOffset) {
        iObserverSem.Signal();
        iBlockSem.Wait();
        THROW(ReaderError);
    }
    else if (iOffset >= iThrowOffset) {
        THROW(ReaderError);
    }
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
    iHttpReader = new TestHttpReader(*iSemReader);
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
    iHttpReader->SetContentOnReconnect(iUriDefault, kFileDefault);
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

    iHttpReader->SetContentOnReconnect(kUri2, kFile2);
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

    iHttpReader->SetContentOnReconnect(kUriNoMediaSeq, kFileNoMediaSeq);
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


    iHttpReader->SetContentOnReconnect(kUriNoMediaSeq, kFileNoMediaSeqExtended);
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

    iHttpReader->SetContentOnReconnect(kUriMediaSeqStartZero, kFileMediaSeqStartZero);
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


    iHttpReader->SetContentOnReconnect(kUriMediaSeqStartZero, kFileMediaSeqStartZeroExtended);
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

    iHttpReader->SetContentOnReconnect(kUriMediaSeqStartNonZero, kFileMediaSeqStartNonZero);
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


    iHttpReader->SetContentOnReconnect(kUriMediaSeqStartNonZero, kFileMediaSeqStartNonZeroExtended);
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

    iHttpReader->SetContentOnReconnect(kUriRelative, kFileRelative);
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

    iHttpReader->SetContentOnReconnect(kUriMediaSeqNonContinuous, kFileMediaSeqNonContinuous);
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


    iHttpReader->SetContentOnReconnect(kUriMediaSeqNonContinuous, kFileMediaSeqStartNonContinuousExtended);
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

    iHttpReader->SetContentOnReconnect(kUriEndlistEnd, kFileEndlistEnd);
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

    iHttpReader->SetContentOnReconnect(kUriEndlistStart, kFileEndlistStart);
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
    TEST(iTimer->CancelCount() == 0);
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

    iHttpReader->SetContentOnReconnect(kUriMediaCrLf, kFileMediaCrLf);
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

    iHttpReader->SetContentOnReconnect(kUriVersion3, kFileVersion3);
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

    iHttpReader->SetContentOnReconnect(kUriVersion4, kFileVersion4);
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
    TEST(iTimer->CancelCount() == 0);
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

    iHttpReader->SetContentOnReconnect(kUriVersion3Encrypted, kFileVersion3Encrypted);
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
    TEST(iTimer->CancelCount() == 0);
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

    iHttpReader->SetContentOnReconnect(kUri, kFile);
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



    // Test interrupt while reading from stream.
    iHttpReader->SetContentOnReconnect(kUri, kFile);
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



    // Test error thrown up from underlying stream reader.
    iHttpReader->SetContentOnReconnect(kUri, kFile);
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
    iHttpReader->SetContentOnReconnect(kServingUri, Brx::Empty());  // Ensure the requested URI won't be recognise, so Connect() will fail.
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

    iHttpReader->SetContentOnReconnect(kUri, kFileInvalidTargetDuration);
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
    iHttpReader = new TestHttpReader(*iSemReader);
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

    iUriProvider->SetUri(kUri1, 50);
    iHttpReader->SetContentOnReconnect(kUri1, kBuf1);
    iStreamer->Stream(*iUriProvider);

    // Start streaming some audio.
    Brn buf = iStreamer->Read(20);
    TEST(buf == Brn("abcdefghijklmnopqrst"));
    // Set next segment up.
    iUriProvider->SetUri(kUri2, 50);
    iHttpReader->SetContentOnReconnect(kUri2, kBuf2);
    // Now, read until end of current segment.
    buf = iStreamer->Read(6);
    TEST(buf == Brn("uvwxyz"));
    // Request more data; streamer should seamlessly start supplying from next segment.
    buf = iStreamer->Read(26);
    TEST(buf == kBuf2);



    // Current behaviour of each read request is to only read (at most) up to end of each segment.
    // So, attempt to read more than amount buffered. Should throw ReaderError, then ReadRemaining() can be called.
    iStreamer->ReadInterrupt();
    iUriProvider->SetUri(kUri1, 50);
    iHttpReader->SetContentOnReconnect(kUri1, kBuf1);
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
    iUriProvider->SetUri(kUri1, 50);
    iHttpReader->SetContentOnReconnect(kUri1, kBuf1);
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

    iUriProvider->SetUri(kUri1, 50);
    iHttpReader->SetContentOnReconnect(kUri1, kBuf1);
    iHttpReader->BlockAtOffset(20);
    iStreamer->Stream(*iUriProvider);

    iReadBytes = 26;

    ThreadFunctor functor("ThreadSegStreamer", MakeFunctor(*this, &SuiteSegmentStreamer::ReadThread));
    functor.Start();
    iSemReader->Clear();
    iSemReader->Wait(kSemWaitMs);    // iStreamer->Read(iReadBytes) has been called in other thread.
    iStreamer->ReadInterrupt();
    iThreadSem->Wait(kSemWaitMs);   // Wait on iStreamer->Read() returning.



    // Test interrupt thrown from underlying stream reader.
    iUriProvider->SetUri(kUri1, 50);
    iHttpReader->SetContentOnReconnect(kUri1, kBuf1);
    iHttpReader->ThrowReadErrorAtOffset(20);
    iStreamer->Stream(*iUriProvider);

    TEST_THROWS(iStreamer->Read(26), ReaderError);



    // Test failed connection.
    iStreamer->ReadInterrupt();
    iUriProvider->SetUri(kUri1, 50);
    iHttpReader->SetContentOnReconnect(Uri(Brn("http://dummy")), Brx::Empty());   // Can force a failed connection by ensuring iHttpReader does not recognise the URI iStreamer will ask for.
    iStreamer->Stream(*iUriProvider);
    TEST_THROWS(iStreamer->Read(26), HlsSegmentError);
}



void TestProtocolHls()
{
    Runner runner("HLS tests\n");
    runner.Add(new SuiteHlsM3uReader());
    runner.Add(new SuiteSegmentStreamer());
    runner.Run();
}
