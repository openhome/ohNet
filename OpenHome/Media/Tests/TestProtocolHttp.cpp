#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/TestFramework.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

namespace OpenHome {
namespace Media {

class HttpHeaderRange : public HttpHeader
{
public:
    static const TUint kEndUnspecified = 0;
    static const TUint kTotalUnknown = 0;
public:
    TUint Start() const;
    TUint End() const;
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    TUint iStart;
    TUint iEnd;
};

class TestHttpServer : public SocketTcpServer
{
public:
    static const Brn kPrefixHttp;
    static const TUint kLenPrefixHttp = sizeof("http://")-1;
    static const TUint kMaxUriBytes = Endpoint::kMaxEndpointBytes + kLenPrefixHttp;
    static const TUint kTotalContentUnknown = 0;
    static const Brn kPartialContentBytes;
    static const Brn kPartialContentRangeSeparator;
    static const Brn kPartialContentTotalSeparator;
    static const Brn kPartialContentLengthUnknown;
public:
    static void WriteHeaderPartialContent(WriterHttpHeader& aWriter, TUint64 aFirst, TUint64 aLast, TUint64 aTotal);
    static void WriteHeaderPartialContentStream(WriterHttpHeader& aWriter);
public:
    TestHttpServer(Environment& aEnv, const TChar* aName, TUint aPort, TIpAddress aInterface);
    ~TestHttpServer();
    const Uri& ServingUri() const;
private:
    const Uri* iUri;
};


// Http session classes.

class TestHttpSession : public SocketTcpSession
{
public:
    static const TUint kStreamLen = 123456;
public:
    TestHttpSession();
    ~TestHttpSession();
    TUint DataSize() const;
protected:
    void WaitOnReadRequest();
    void Stream(TUint aStartPos, TUint aEndPos);
    virtual void Respond() = 0;
private: // from SocketTcpSession
    void Run();
private:
    static const TUint kMaxReadBytes = 1024;
    static const TUint kReadTimeoutMs = 5000;
    static const TUint kMaxWriteBufBytes = 1400;
    HttpHeaderConnection iHeaderConnection;
    // Reader and buffer.
    Srx* iReadBuffer;
    ReaderUntil* iReaderUntil;
    ReaderHttpRequest* iReaderRequest;
    // Writer and buffer.
    Bwh iBuf;
protected:
    HttpHeaderRange iHeaderRange;
    // Writer shared by derived classes
    WriterHttpResponse* iWriterResponse;
    WriterHttpChunked* iWriterChunked;
    Sws<kMaxWriteBufBytes>* iWriterBuffer;
};

class TestHttpSessionStreamFull : public TestHttpSession
{
public:
    TestHttpSessionStreamFull();
protected:
    void WriteResponseContentLength(TUint aLength);
private: // from TestHttpSession
    void Respond();
};

class TestHttpSessionReject : public TestHttpSession
{
public:
    TestHttpSessionReject();
private:
    void WriteResponseBadRequest();
private: // from TestHttpSession
    void Respond();
};

class TestHttpSessionReconnect : public TestHttpSessionStreamFull
{
private:
    enum EMode
    {
        eStreamBreak    = 0,
        eReconnect  = 1,
    };
public:
    TestHttpSessionReconnect();
private:
    void WriteResponsePartialContent(TUint aStartPos, TUint aEndPos, TUint aTotalLength, TUint aLength);
private: // from TestHttpSession
    void Respond();
private:
    EMode iMode;
};

class TestHttpSessionStreamLive : public TestHttpSessionStreamFull
{
private:
    enum EMode
    {
        eConnect = 0,
        eStream  = 1,
    };
public:
    TestHttpSessionStreamLive();
protected:
    void WriteResponseOk();
private: // from TestHttpSessionStreamFull
    void Respond();
private:
    EMode iMode;
};

class TestHttpSessionLiveReconnect : public TestHttpSessionStreamLive
{
private:
    enum EMode
    {
        eConnect        = 0,
        eStreamBreak    = 1,
        eReconnect      = 2,
    };
public:
    TestHttpSessionLiveReconnect();
private: // from TestHttpSessionStreamLive
    void Respond();
private:
    EMode iMode;
};

class TestHttpSessionChunked : public TestHttpSession
{
public:
    static const TUint kDataBytes = 1024 * 1024;
public:
    TestHttpSessionChunked();
private: // from TestHttpSession
    void Respond();
private:
    enum EMode
    {
        eConnect = 0,
        eStream  = 1,
    };
    EMode iMode;
};


class SessionFactory
{
public:
    enum ESession
    {
        eStreamFull       = 0,
        eReject           = 1,
        eReconnect        = 2,
        eStreamLive       = 3,
        eLiveReconnect    = 4,
        eChunked          = 5
    };
public:
    static TestHttpSession* Create(ESession aSession);
};


// Pipeline classes.

class TestHttpSupplier : public IPipelineElementDownstream, protected IMsgProcessor
{
public:
    TestHttpSupplier(TUint aDataSize);
    virtual ~TestHttpSupplier();
public:
    TUint StreamId();
    TBool Live();
    TUint TrackCount();
    TUint StreamCount();
    TUint DataTotal();
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
protected: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgChangeInput* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    TUint iDataSize;
    TUint iStreamId;
    TBool iLive;
    TUint iTrackCount;
    TUint iStreamCount;
    TUint iDataTotal;
    IStreamHandler* iStreamHandler;
};

class TestHttpSupplyChunked : public TestHttpSupplier
{
public:
    TestHttpSupplyChunked();
protected: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
private:
    TUint iExpectedNextByte;
    TByte iOutput[EncodedAudio::kMaxBytes];
};

class TestHttpPipelineProvider : public IPipelineIdProvider
{
public:
    TestHttpPipelineProvider();
    virtual ~TestHttpPipelineProvider();
public: // from IPipelineIdProvider
    TUint NextStreamId() override;
    EStreamPlay OkToPlay(TUint aStreamId) override;
private:
    TUint iNextStreamId;
    static const TUint kInvalidPipelineId = 0;
};

class TestHttpFlushIdProvider : public IFlushIdProvider
{
public:
    TestHttpFlushIdProvider();
    virtual ~TestHttpFlushIdProvider();
public: // from iFlushIdProvider
    TUint NextFlushId();
private:
    TUint iNextFlushId;
};


// Suite classes.

class SuiteHttp : public Suite
{
public:
    SuiteHttp(const TChar* aSuiteName, SessionFactory::ESession aSession);
    ~SuiteHttp();
private:
    void TestStreamFull();
    void TestServerReject();
    void TestServerRejectDoStream();
    void TestStreamReconnect();
    void TestStreamLive();
    void TestStreamLiveBreak();
private: // from Suite
    virtual void Test() = 0;
private:
    TestHttpPipelineProvider* iProvider;
    TestHttpFlushIdProvider* iFlushId;
protected:
    TestHttpServer* iServer;
    TestHttpSession* iHttpSession;
    TestHttpSupplier* iSupply;
    MsgFactory* iMsgFactory;
    ProtocolManager* iProtocolManager;
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
};

class SuiteHttpStreamFull : public SuiteHttp
{
public:
    SuiteHttpStreamFull();
private: // from SuiteHttp
    void Test();
};

class SuiteHttpReject : public SuiteHttp
{
public:
    SuiteHttpReject();
private: // from SuiteHttp
    void Test();
};

class SuiteHttpReconnect : public SuiteHttp
{
public:
    SuiteHttpReconnect();
private: // from SuiteHttp
    void Test();
};

class SuiteHttpStreamLive : public SuiteHttp
{
public:
    SuiteHttpStreamLive();
private: // from SuiteHttp
    void Test();
};

class SuiteHttpLiveReconnect : public SuiteHttp
{
public:
    SuiteHttpLiveReconnect();
private: // from SuiteHttp
    void Test();
};

class SuiteHttpChunked : public Suite
{
public:
    SuiteHttpChunked();
    ~SuiteHttpChunked();
private: // from Suite
    void Test();
private:
    TestHttpServer* iServer;
    TestHttpSupplyChunked* iSupply;
    TestHttpPipelineProvider* iProvider;
    TestHttpFlushIdProvider* iFlushId;
    MsgFactory* iMsgFactory;
    ProtocolManager* iProtocolManager;
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
};

} // namespace Media
} // namespace OpenHome



using namespace OpenHome::Media;


// HttpHeaderRange

const TUint HttpHeaderRange::kEndUnspecified;
const TUint HttpHeaderRange::kTotalUnknown;

TUint HttpHeaderRange::Start() const
{
    return (Received()? iStart : 0);
}

TUint HttpHeaderRange::End() const
{
    return (Received()? iEnd : kEndUnspecified);
}

TBool HttpHeaderRange::Recognise(const Brx& aHeader)
{
    TBool recognised = Ascii::CaseInsensitiveEquals(aHeader, Http::kHeaderRange);
    return recognised;
}

void HttpHeaderRange::Process(const Brx& aValue)
{
    iStart = 0;
    iEnd = kEndUnspecified;
    TUint indEquals;
    TUint indHyphen;
    Brn range;
    Brn start;
    Brn end;

    SetReceived();
    try {
        indEquals = Ascii::IndexOf(aValue, '=');
        if (indEquals == aValue.Bytes()) {  // An equals sign does not exist.
            THROW(HttpError);
        }

        indEquals++; // Shift index so we skip over separator.
        range = aValue.Split(indEquals, aValue.Bytes()-indEquals);

        indHyphen = Ascii::IndexOf(range, '-');
        if (indHyphen == range.Bytes()) {   // A hyphen does not exist, so range points are not specified.
            THROW(HttpError);
        }

        Brn start(range.Ptr(), indHyphen);      // Get the start value.
        indHyphen++; // Shift index so we skip over separator.
        end = range.Split(indHyphen, range.Bytes()-indHyphen);  // Get the end value.

        iStart = Ascii::Uint(start);
        if (end.Bytes() == 0) { // End range may be empty.
            iEnd = 0;
        }
        else {
            iEnd = Ascii::Uint(end);
        }
    }
    catch (AsciiError&) {
        THROW(HttpError);
    }
}


// TestHttpServer

const Brn TestHttpServer::kPrefixHttp("http://");
const Brn TestHttpServer::kPartialContentBytes("bytes ");
const Brn TestHttpServer::kPartialContentRangeSeparator("-");
const Brn TestHttpServer::kPartialContentTotalSeparator("/");
const Brn TestHttpServer::kPartialContentLengthUnknown("*");

void TestHttpServer::WriteHeaderPartialContent(WriterHttpHeader& aWriter, TUint64 aFirst, TUint64 aLast, TUint64 aTotal)
{
    // Format of value is: "bytes 21010-47021/47022"
    // i.e. maxLen = lenValPrefix + lenTUint64 + lenDelimiter + lenTUint64 + lenDelimiter + lenTUint64;

    Bws<6+20+1+20+1+20> buf;
    buf.Append(kPartialContentBytes);
    Ascii::AppendDec(buf, aFirst);
    buf.Append(kPartialContentRangeSeparator);
    Ascii::AppendDec(buf, aLast);
    buf.Append(kPartialContentTotalSeparator);
    if (aTotal == kTotalContentUnknown) {
        buf.Append(kPartialContentLengthUnknown);
    }
    else {
        Ascii::AppendDec(buf, aTotal);
    }

    aWriter.WriteHeader(Http::kHeaderContentRange, buf);
}

TestHttpServer::TestHttpServer(Environment& aEnv, const TChar* aName, TUint aPort, TIpAddress aInterface)
    :SocketTcpServer(aEnv, aName, aPort, aInterface)
{
    // Get server URI.
    Endpoint endpoint = Endpoint(Port(), Interface());
    Bws<kMaxUriBytes> uri;
    uri.Append(kPrefixHttp);
    endpoint.AppendEndpoint(uri);
    iUri = new Uri(uri);
}

TestHttpServer::~TestHttpServer()
{
    delete iUri;
}

const Uri& TestHttpServer::ServingUri() const
{
    return *iUri;
}


// TestHttpSession

TestHttpSession::TestHttpSession()
    : iBuf(kMaxWriteBufBytes)
{
    iReadBuffer = new Srs<kMaxReadBytes>(*this);
    iReaderUntil = new ReaderUntilS<kMaxReadBytes>(*iReadBuffer);
    iReaderRequest = new ReaderHttpRequest(*gEnv, *iReaderUntil);
    iReaderRequest->AddMethod(Http::kMethodGet);
    iReaderRequest->AddHeader(iHeaderConnection);
    iReaderRequest->AddHeader(iHeaderRange);

    iWriterChunked = new WriterHttpChunked(*this);
    iWriterBuffer = new Sws<kMaxWriteBufBytes>(*iWriterChunked);
    iWriterResponse = new WriterHttpResponse(*iWriterBuffer);
}

TestHttpSession::~TestHttpSession()
{
    delete iReaderRequest;
    iReaderUntil->ReadInterrupt();
    delete iReaderUntil;
    delete iReadBuffer;
    delete iWriterResponse;
    delete iWriterBuffer;
    delete iWriterChunked;
}

void TestHttpSession::WaitOnReadRequest()
{
    iReaderRequest->Flush();
    iReaderRequest->Read(kReadTimeoutMs);

    if (!iHeaderConnection.Received()) {
        ASSERTS();
    }
}

void TestHttpSession::Stream(TUint aStartPos, TUint aEndPos)
{
    TUint bytesRemaining = aEndPos - aStartPos;

    // Loop until we've streamed all bytes.
    while (bytesRemaining > 0) {
        // Bytes to transmit.
        TUint bytes = iBuf.MaxBytes();
        if (bytesRemaining < bytes) {
            bytes = bytesRemaining;
        }

        memset((void*)(iBuf.Ptr()), 0, bytes);
        iBuf.SetBytes(bytes);   // Buffer of empty bytes.
        bytesRemaining -= bytes;

        // Write data out.
        iWriterResponse->Write(iBuf);
    }
    iWriterBuffer->WriteFlush();
}

TUint TestHttpSession::DataSize() const
{
    return kStreamLen;
}

void TestHttpSession::Run()
{
    try {
        WaitOnReadRequest();
        Respond();      // From derived classes.
    }
    catch (HttpError&) {ASSERTS();}
    catch (ReaderError&) {ASSERTS();}
    catch (WriterError&) {ASSERTS();}
    catch (NetworkError&) {ASSERTS();}
}


// TestHttpSessionStreamFull

TestHttpSessionStreamFull::TestHttpSessionStreamFull()
    : TestHttpSession()
{
}

void TestHttpSessionStreamFull::WriteResponseContentLength(TUint aLength)
{
    const HttpStatus* errorStatus = &HttpStatus::kOk;

    iWriterResponse->WriteStatus(*errorStatus, Http::eHttp11);
    Http::WriteHeaderContentLength(*iWriterResponse, aLength);
    iWriterResponse->WriteFlush();
}

void TestHttpSessionStreamFull::Respond()
{
    WriteResponseContentLength(kStreamLen);
    Stream(0, kStreamLen);
}


// TestHttpSessionReject

TestHttpSessionReject::TestHttpSessionReject()
    : TestHttpSession()
{
}

void TestHttpSessionReject::WriteResponseBadRequest()
{
    const HttpStatus* errorStatus = &HttpStatus::kBadRequest;

    iWriterResponse->WriteStatus(*errorStatus, Http::eHttp11);
    iWriterResponse->WriteFlush();
}

void TestHttpSessionReject::Respond()
{
    WriteResponseBadRequest();
}

// TestHttpSessionReconnect

TestHttpSessionReconnect::TestHttpSessionReconnect()
    : TestHttpSessionStreamFull()
    , iMode(eStreamBreak)
{
}

void TestHttpSessionReconnect::WriteResponsePartialContent(TUint aStartPos, TUint aEndPos, TUint aTotalLength, TUint aLength)
{
    const HttpStatus* errorStatus = &HttpStatus::kPartialContent;

    iWriterResponse->WriteStatus(*errorStatus, Http::eHttp11);
    TestHttpServer::WriteHeaderPartialContent(*iWriterResponse, aStartPos, aEndPos, aTotalLength);
    Http::WriteHeaderContentLength(*iWriterResponse, aLength);
    iWriterResponse->WriteFlush();
}

void TestHttpSessionReconnect::Respond()
{
    if (iMode == eStreamBreak) {
        WriteResponseContentLength(kStreamLen);
        // Portion of stream.
        Stream(0, kStreamLen/2);
        iMode = eReconnect;
    }
    else if (iMode == eReconnect) {
        if (iHeaderRange.Received()) {
            TUint startByte = iHeaderRange.Start();
            //TUint endByte = iHeaderRange.End();
            WriteResponsePartialContent(startByte, kStreamLen-1, kStreamLen, kStreamLen-startByte);
            Stream(startByte, kStreamLen);
        }
        else {
            ASSERTS();
        }
    }
}


// TestHttpSessionStreamLive

TestHttpSessionStreamLive::TestHttpSessionStreamLive()
    : TestHttpSessionStreamFull()
    , iMode(eConnect)
{
}

void TestHttpSessionStreamLive::WriteResponseOk()
{
    const HttpStatus* errorStatus = &HttpStatus::kOk;

    iWriterResponse->WriteStatus(*errorStatus, Http::eHttp11);
    iWriterResponse->WriteFlush();
}

void TestHttpSessionStreamLive::Respond()
{
    if (iMode == eConnect) {
        WriteResponseOk();
        iMode = eStream;
    }
    else if (iMode == eStream) {
        WriteResponseContentLength(0);
        Stream(0, kStreamLen);
    }
}


// TestHttpSessionLiveReconnect

TestHttpSessionLiveReconnect::TestHttpSessionLiveReconnect()
    : TestHttpSessionStreamLive()
    , iMode(eConnect)
{
}

void TestHttpSessionLiveReconnect::Respond()
{
    if (iMode == eConnect) {
        WriteResponseOk();
        iMode = eStreamBreak;
    }
    else if (iMode == eStreamBreak) {
        WriteResponseContentLength(0);
        Stream(0, kStreamLen/2);
        iMode = eReconnect;
    }
    else if (iMode == eReconnect) {
        WriteResponseContentLength(0);
        Stream(kStreamLen/2, kStreamLen);
    }
}


// TestHttpSessionChunked

TestHttpSessionChunked::TestHttpSessionChunked()
    : iMode(eConnect)
{
}

void TestHttpSessionChunked::Respond()
{
    const HttpStatus* errorStatus = &HttpStatus::kOk;
    iWriterResponse->WriteStatus(*errorStatus, Http::eHttp11);
    iWriterResponse->WriteHeader(Http::kHeaderTransferEncoding, Http::kTransferEncodingChunked);
    iWriterResponse->WriteFlush();

    if (iMode == eConnect) {
        iMode = eStream;
        return;
    }

    iWriterChunked->SetChunked(true);
    Bws<256> buf;
    buf.SetBytes(256);
    for (TUint i=0; i<256; i++) {
        buf[i] = (TByte)i;
    }
    ASSERT(kDataBytes % 256 == 0);
    for (TUint i=0; i<kDataBytes; i+=256) {
        iWriterBuffer->Write(buf);
    }
    iWriterBuffer->WriteFlush();
}


// SessionFactory

TestHttpSession* SessionFactory::Create(ESession aSession)
{
    switch (aSession)
    {
    case eStreamFull:
        return new TestHttpSessionStreamFull();
    case eReject:
        return new TestHttpSessionReject();
    case eReconnect:
        return new TestHttpSessionReconnect();
    case eStreamLive:
        return new TestHttpSessionStreamLive();
    case eLiveReconnect:
        return new TestHttpSessionLiveReconnect();
    case eChunked:
        return new TestHttpSessionChunked();
    default:
        ASSERTS();
        return NULL;    // Will never reach here.
    }
}


// TestHttpSupplier

TestHttpSupplier::TestHttpSupplier(TUint aDataSize)
    : iDataSize(aDataSize)
    , iStreamId(0)
    , iLive(false)
    , iTrackCount(0)
    , iStreamCount(0)
    , iDataTotal(0)
    , iStreamHandler(NULL)
{
}

TestHttpSupplier::~TestHttpSupplier()
{
}

TUint TestHttpSupplier::StreamId()
{
    return iStreamId;
}

TBool TestHttpSupplier::Live()
{
    return iLive;
}

TUint TestHttpSupplier::TrackCount()
{
    return iTrackCount;
}

TUint TestHttpSupplier::StreamCount()
{
    return iStreamCount;
}

TUint TestHttpSupplier::DataTotal()
{
    return iDataTotal;
}

void TestHttpSupplier::Push(Msg* aMsg)
{
    (void)aMsg->Process(*this);
    aMsg->RemoveRef();
}

Msg* TestHttpSupplier::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgTrack* aMsg)
{
    iTrackCount++;
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgChangeInput* aMsg)
{
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLive = aMsg->Live();
    iStreamId = aMsg->StreamId();
    iStreamHandler = aMsg->StreamHandler();
    (void)iStreamHandler->OkToPlay(iStreamId);
    iStreamCount++;
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iDataTotal += aMsg->Bytes();
    if (iLive && iDataTotal >= iDataSize) {
        // We are only simulating a live stream, so want to tell
        // client to stop when data has run out.
        iStreamHandler->TryStop(iStreamId);
    }
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgFlush* aMsg)
{
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgDecodedStream* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgAudioPcm* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgSilence* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgPlayable* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* TestHttpSupplier::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}


// TestHttpSupplyChunked : public TestHttpSupplier

TestHttpSupplyChunked::TestHttpSupplyChunked()
    : TestHttpSupplier(TestHttpSessionChunked::kDataBytes)
    , iExpectedNextByte(0)
{
}

Msg* TestHttpSupplyChunked::ProcessMsg(MsgAudioEncoded* aMsg)
{
    TestHttpSupplier::ProcessMsg(aMsg);
    const TUint bytes = aMsg->Bytes();
    aMsg->CopyTo(iOutput);
    for (TUint i=0; i<bytes; i++) {
        TEST_QUIETLY(iOutput[i] == iExpectedNextByte);
        iExpectedNextByte = (iExpectedNextByte + 1) % 256;
    }
    return aMsg;
}


// TestHttpPipelineProvider

TestHttpPipelineProvider::TestHttpPipelineProvider()
    : iNextStreamId(kInvalidPipelineId+1)
{
}

TestHttpPipelineProvider::~TestHttpPipelineProvider()
{
}

TUint TestHttpPipelineProvider::NextStreamId()
{
    //Log::Print("TestHttpPipelineProvider::NextStreamId\n");
    return iNextStreamId++;
}

EStreamPlay TestHttpPipelineProvider::OkToPlay(TUint /*aStreamId*/)
{
    //Log::Print("TestHttpPipelineProvider::OkToPlay\n");
    return ePlayYes;
}


// TestHttpFlushIdProvider

TestHttpFlushIdProvider::TestHttpFlushIdProvider()
    : iNextFlushId(MsgFlush::kIdInvalid + 1)
{
}

TestHttpFlushIdProvider::~TestHttpFlushIdProvider() {}


TUint TestHttpFlushIdProvider::NextFlushId()
{
    return iNextFlushId++;
}


// SuiteHttp

SuiteHttp::SuiteHttp(const TChar* aSuiteName, SessionFactory::ESession aSession)
    : Suite(aSuiteName)
{
    // Get a list of network adapters (using loopback, so first one should do).
    std::vector<NetworkAdapter*>* ifs = Os::NetworkListAdapters(*gEnv, Net::InitialisationParams::ELoopbackUse, "Loopback");
    TIpAddress addr = (*ifs)[0]->Address();
    for (TUint i=0; i<ifs->size(); i++) {
        (*ifs)[i]->RemoveRef("Loopback");
    }
    delete ifs;

    // Create our TCP server.
    iServer = new TestHttpServer(*gEnv, "HSV1", 0, addr);

    //Log::Print("uri: ");
    //Log::Print(iServer->ServingUri().AbsoluteUri());
    //Log::Print("\n");

    TUint dataSize = TestHttpSession::kStreamLen;

    // Create a custom HTTP session for testing purposes.
    iHttpSession = SessionFactory::Create(aSession);
    iServer->Add("HTP1", iHttpSession);

    // Create our HTTP client.
    iSupply = new TestHttpSupplier(dataSize);
    iProvider = new TestHttpPipelineProvider();
    iFlushId = new TestHttpFlushIdProvider();

    iMsgFactory = new MsgFactory(iInfoAggregator, 100, 100, 1, 1, 1, 1, 1, 1, 10, 1, 10, 10, 1, 1, 10, 1, 1, 10, 1, 1);

    iProtocolManager = new ProtocolManager(*iSupply, *iMsgFactory, *iProvider, *iFlushId);
    iProtocolManager->Add(ProtocolFactory::NewHttp(*gEnv, Brx::Empty()));

    iTrackFactory= new TrackFactory(iInfoAggregator, 1);
}

SuiteHttp::~SuiteHttp()
{
    delete iTrackFactory;
    delete iProtocolManager;
    delete iProvider;
    delete iSupply;
    delete iMsgFactory;
    delete iServer;
    delete iFlushId;
}


// SuiteHttpStreamFull

SuiteHttpStreamFull::SuiteHttpStreamFull()
    : SuiteHttp("HTTP streaming tests", SessionFactory::eStreamFull)
{
}

void SuiteHttpStreamFull::Test()
{
    // Test if streaming is successful.
    Track* track = iTrackFactory->CreateTrack(iServer->ServingUri().AbsoluteUri(), Brx::Empty());
    ProtocolStreamResult res = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(res == EProtocolStreamSuccess);

    // Test if a single track message is received.
    TEST(iSupply->TrackCount() == 1);

    // Test if a single stream message is received.
    TEST(iSupply->StreamCount() == 1);

    // Test if it was a live stream
    TEST(iSupply->Live() == false);

    // Test if the data transferred is equivalent to the stream length.
    TUint streamSize = iHttpSession->DataSize();
    TUint dataTotal = iSupply->DataTotal();
    TEST(streamSize == dataTotal);
}


// SuiteHttpReject

SuiteHttpReject::SuiteHttpReject()
    : SuiteHttp("HTTP server rejection tests", SessionFactory::eReject)
{
}

void SuiteHttpReject::Test()
{
    // Test if streaming is successful.
    Track* track = iTrackFactory->CreateTrack(iServer->ServingUri().AbsoluteUri(), Brx::Empty());
    ProtocolStreamResult res = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(res == EProtocolStreamErrorUnrecoverable);

    // Test if a single track message is received.
    TEST(iSupply->TrackCount() == 1);

    // Test if no stream message is received.
    TEST(iSupply->StreamCount() == 0);

    // Test if no data was transferred.
    TUint dataTotal = iSupply->DataTotal();
    TEST(dataTotal == 0);
}


// SuiteHttpReconnect

SuiteHttpReconnect::SuiteHttpReconnect()
    : SuiteHttp("HTTP stream reconnection tests", SessionFactory::eReconnect)
{
}

void SuiteHttpReconnect::Test()
{
    // Test if streaming is successful.
    Track* track = iTrackFactory->CreateTrack(iServer->ServingUri().AbsoluteUri(), Brx::Empty());
    ProtocolStreamResult res = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(res == EProtocolStreamSuccess);

    // Test if a single track message is received.
    TEST(iSupply->TrackCount() == 1);

    // Test if a single stream message is received.
    TEST(iSupply->StreamCount() == 1);

    // Test if it was a live stream
    TEST(iSupply->Live() == false);

    // Test if the total data transferred over both sessions is equivalent to the stream length.
    TUint streamSize = iHttpSession->DataSize();
    TUint dataTotal = iSupply->DataTotal();
    TEST(streamSize == dataTotal);
}


// SuiteHttpStreamLive

SuiteHttpStreamLive::SuiteHttpStreamLive()
    : SuiteHttp("HTTP live streaming tests", SessionFactory::eStreamLive)
{
}

void SuiteHttpStreamLive::Test()
{
    // Test if streaming is successful.
    Track* track = iTrackFactory->CreateTrack(iServer->ServingUri().AbsoluteUri(), Brx::Empty());
    ProtocolStreamResult res = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(res == EProtocolStreamStopped);

    // Test if a single track message is received.
    TEST(iSupply->TrackCount() == 1);

    // Test if a single stream message is received.
    TEST(iSupply->StreamCount() == 1);

    // Test if it was a live stream
    TEST(iSupply->Live() == true);

    // Test if the total data transferred over both sessions is equivalent to the stream length.
    TUint streamSize = iHttpSession->DataSize();
    TUint dataTotal = iSupply->DataTotal();
    TEST(streamSize <= dataTotal);
}


// SuiteHttpLiveReconnect : SuiteHttp

SuiteHttpLiveReconnect::SuiteHttpLiveReconnect()
    : SuiteHttp("HTTP live stream reconnection tests", SessionFactory::eLiveReconnect)
{
}

void SuiteHttpLiveReconnect::Test()
{
    // Test if streaming is successful.
    Track* track = iTrackFactory->CreateTrack(iServer->ServingUri().AbsoluteUri(), Brx::Empty());
    ProtocolStreamResult res = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(res == EProtocolStreamStopped);

    // Test if a single track message is received.
    TEST(iSupply->TrackCount() == 1);

    // Test if a single stream message is received.
    TEST(iSupply->StreamCount() == 1);

    // Test if it was a live stream
    TEST(iSupply->Live() == true);

    // Test if the total data transferred over both sessions is equivalent to the stream length.
    TUint streamSize = iHttpSession->DataSize();
    TUint dataTotal = iSupply->DataTotal();
    TEST(streamSize <= dataTotal);
}


// SuiteHttpChunked

SuiteHttpChunked::SuiteHttpChunked()
    : Suite("Chunked http")
{
    std::vector<NetworkAdapter*>* ifs = Os::NetworkListAdapters(*gEnv, Net::InitialisationParams::ELoopbackUse, "SuiteHttpChunked");
    TIpAddress addr = (*ifs)[0]->Address();
    for (TUint i=0; i<ifs->size(); i++) {
        (*ifs)[i]->RemoveRef("SuiteHttpChunked");
    }
    delete ifs;

    iServer = new TestHttpServer(*gEnv, "HSV1", 0, addr);
    TestHttpSession* session = SessionFactory::Create(SessionFactory::eChunked);
    iServer->Add("HTP1", session);

    iSupply = new TestHttpSupplyChunked();
    iProvider = new TestHttpPipelineProvider();
    iFlushId = new TestHttpFlushIdProvider();

    iMsgFactory = new MsgFactory(iInfoAggregator, 100, 100, 1, 1, 1, 1, 1, 1, 10, 1, 10, 10, 1, 1, 10, 1, 1, 10, 1, 1);

    iProtocolManager = new ProtocolManager(*iSupply, *iMsgFactory, *iProvider, *iFlushId);
    iProtocolManager->Add(ProtocolFactory::NewHttp(*gEnv, Brx::Empty()));

    iTrackFactory= new TrackFactory(iInfoAggregator, 1);
}

SuiteHttpChunked::~SuiteHttpChunked()
{
    delete iTrackFactory;
    delete iProtocolManager;
    delete iProvider;
    delete iSupply;
    delete iMsgFactory;
    delete iServer;
    delete iFlushId;
}

void SuiteHttpChunked::Test()
{
    Track* track = iTrackFactory->CreateTrack(iServer->ServingUri().AbsoluteUri(), Brx::Empty());
    const ProtocolStreamResult res = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(res == EProtocolStreamStopped);
    TEST(iSupply->TrackCount() == 1);
    TEST(iSupply->StreamCount() == 1);
    TEST(iSupply->Live());
    TEST(iSupply->DataTotal() == TestHttpSessionChunked::kDataBytes);
}



void TestProtocolHttp()
{
    Runner runner("HTTP tests\n");
    runner.Add(new SuiteHttpStreamFull());
    runner.Add(new SuiteHttpReject());
    runner.Add(new SuiteHttpReconnect());
    runner.Add(new SuiteHttpStreamLive());
    runner.Add(new SuiteHttpLiveReconnect());
    runner.Add(new SuiteHttpChunked());
    runner.Run();
}
