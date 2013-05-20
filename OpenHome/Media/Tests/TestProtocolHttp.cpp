#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Av/InfoProvider.h>
#include "AllocatorInfoLogger.h"
#include <OpenHome/Private/File.h>
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
    const Uri ServingUri() const;
private:
    const Uri* iUri;
};


// Http session classes.

class TestHttpSession : public SocketTcpSession
{
public:
    TestHttpSession(const Brx& aFilename);
    ~TestHttpSession();
    TUint DataSize() const;
protected:
    void WaitOnReadRequest();
    void StreamFile(TUint aStartPos, TUint aEndPos);
    virtual void Respond() = 0;
private: // from SocketTcpSession
    void Run();
private:
    static const TUint kMaxReadBytes = 1024;
    static const TUint kReadTimeoutMs = 5000;
    static const TUint kMaxWriteBufBytes = 1400;
    HttpHeaderConnection iHeaderConnection;
    // File attributes.
    const Brhz iFilename;
    // Reader and buffer.
    Srs<kMaxReadBytes>* iReadBuffer;
    ReaderHttpRequest* iReaderRequest;
    // Writer and buffer.
    Sws<kMaxWriteBufBytes>* iWriterBuffer;
    Bwh iBuf;
protected:
    IFile* iFile;
    HttpHeaderRange iHeaderRange;
    // Writer shared by derived classes
    WriterHttpResponse* iWriterResponse;
};

class TestHttpSessionStreamFull : public TestHttpSession
{
public:
    TestHttpSessionStreamFull(const Brx& aFilename);
protected:
    void WriteResponseContentLength(TUint aLength);
private: // from TestHttpSession
    void Respond();
};

class TestHttpSessionReject : public TestHttpSession
{
public:
    TestHttpSessionReject(const Brx& aFilename);
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
    TestHttpSessionReconnect(const Brx& aFilename);
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
        eConnect      = 0,
        eStream    = 1,
    };
public:
    TestHttpSessionStreamLive(const Brx& aFilename);
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
    TestHttpSessionLiveReconnect(const Brx& aFilename);
private: // from TestHttpSessionStreamLive
    void Respond();
private:
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
    };
public:
    SessionFactory(const Brx& aFilename);
    TestHttpSession* Create(ESession aSession);
private:
    const Brh iFilename;
};


// Pipeline classes.

class TestHttpSupplier : public ISupply
{
public:
    TestHttpSupplier(TUint aDataSize);
    virtual ~TestHttpSupplier();
public:
    TUint TrackId();
    TUint StreamId();
    TBool Live();
    TUint TrackCount();
    TUint StreamCount();
    TUint DataTotal();
public: // from ISupply
    void OutputTrack(Track& aTrack, TUint aTrackId);
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId);
    void OutputData(const Brx& aData);
    void OutputMetadata(const Brx& aMetadata);
    void OutputFlush(TUint aFlushId);
    void OutputQuit();
private:
    TUint iDataSize;
    TUint iTrackId;
    TUint iStreamId;
    TBool iLive;
    TUint iTrackCount;
    TUint iStreamCount;
    TUint iDataTotal;
    IStreamHandler* iStreamHandler;
};

class TestHttpPipelineProvider : public IPipelineIdProvider
{
public:
    TestHttpPipelineProvider();
    virtual ~TestHttpPipelineProvider();
public: // from IPipelineIdProvider
    TUint NextTrackId();
    TUint NextStreamId();
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    void InvalidateAt(const Brx& aStyle, const Brx& aProviderId);
    void InvalidateAfter(const Brx& aStyle, const Brx& aProviderId);
    void InvalidateAll();
private:
    TUint iNextTrackId;
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
        end = range.Split(indHyphen, range.Bytes()-indHyphen);	// Get the end value.

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

const Uri TestHttpServer::ServingUri() const
{
    return *iUri;
}


// TestHttpSession

TestHttpSession::TestHttpSession(const Brx& aFilename)
    : iFilename(aFilename)
    , iBuf(kMaxWriteBufBytes)
{
    // Try opening the file.
    try {
        iFile = IFile::Open(iFilename.CString(), eFileReadOnly);
    }
    catch (FileOpenError aFileErr) {
        ASSERTS();
    }

    iReadBuffer = new Srs<kMaxReadBytes>(*this);
    iReaderRequest = new ReaderHttpRequest(*gEnv, *iReadBuffer);
    iReaderRequest->AddMethod(Http::kMethodGet);
    iReaderRequest->AddHeader(iHeaderConnection);
    iReaderRequest->AddHeader(iHeaderRange);

    iWriterBuffer = new Sws<kMaxWriteBufBytes>(*this);
    iWriterResponse = new WriterHttpResponse(*iWriterBuffer);
}

TestHttpSession::~TestHttpSession()
{
    delete iFile;
    delete iReaderRequest;
    iReadBuffer->ReadInterrupt();
    delete iReadBuffer;
    delete iWriterResponse;
    delete iWriterBuffer;
}

void TestHttpSession::WaitOnReadRequest()
{
    iReaderRequest->Flush();
    iReaderRequest->Read(kReadTimeoutMs);

    if (!iHeaderConnection.Received()) {
        ASSERTS();
    }
}

void TestHttpSession::StreamFile(TUint aStartPos, TUint aEndPos)
{
        TUint bytesRemaining = aEndPos - aStartPos;

        iFile->Seek(aStartPos);

        // Loop until we've streamed all of file.
        while (bytesRemaining > 0) {
            // Bytes to read from file.
            iBuf.SetBytes(0);
            TUint bytes = iBuf.MaxBytes();
            if (bytesRemaining < bytes) {
                bytes = bytesRemaining;
            }

            // Read from the file.
            iFile->Read(iBuf, bytes);

            // Check the number of bytes read is what we expected; file error otherwise.
            if (iBuf.Bytes() != bytes) {
                ASSERTS();
            }
            bytesRemaining -= bytes;

            // Write file data out.
            iWriterResponse->Write(iBuf);
        }
        iWriterBuffer->WriteFlush();
}

TUint TestHttpSession::DataSize() const
{
    return iFile->Bytes();
}

void TestHttpSession::Run()
{
    try {
        WaitOnReadRequest();
        Respond();      // From derived classes.
    }
    catch (HttpError) {ASSERTS();}
    catch (ReaderError) {ASSERTS();}
    catch (WriterError) {ASSERTS();}
    catch (NetworkError) {ASSERTS();}
}


// TestHttpSessionStreamFull

TestHttpSessionStreamFull::TestHttpSessionStreamFull(const Brx& aFilename)
    : TestHttpSession(aFilename)
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
    WriteResponseContentLength(iFile->Bytes());
    StreamFile(0, iFile->Bytes());
}


// TestHttpSessionReject

TestHttpSessionReject::TestHttpSessionReject(const Brx& aFilename)
    : TestHttpSession(aFilename)
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

TestHttpSessionReconnect::TestHttpSessionReconnect(const Brx& aFilename)
    : TestHttpSessionStreamFull(aFilename)
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
        WriteResponseContentLength(iFile->Bytes());
        // Stream only a portion of file.
        StreamFile(0, iFile->Bytes()/2);
        iMode = eReconnect;
    }
    else if (iMode == eReconnect) {
        if (iHeaderRange.Received()) {
            TUint startByte = iHeaderRange.Start();
            //TUint endByte = iHeaderRange.End();
            WriteResponsePartialContent(startByte, iFile->Bytes()-1, iFile->Bytes(), iFile->Bytes()-startByte);
            StreamFile(startByte, iFile->Bytes());
        }
        else {
            ASSERTS();
        }
    }
}


// TestHttpSessionStreamLive

TestHttpSessionStreamLive::TestHttpSessionStreamLive(const Brx& aFilename)
    : TestHttpSessionStreamFull(aFilename)
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
        StreamFile(0, iFile->Bytes());
    }
}


// TestHttpSessionLiveReconnect

TestHttpSessionLiveReconnect::TestHttpSessionLiveReconnect(const Brx& aFilename)
    : TestHttpSessionStreamLive(aFilename)
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
        StreamFile(0, iFile->Bytes()/2);
        iMode = eReconnect;
    }
    else if (iMode == eReconnect) {
        WriteResponseContentLength(0);
        StreamFile(iFile->Bytes()/2, iFile->Bytes());
    }
}


// SessionFactory

SessionFactory::SessionFactory(const Brx& aFilename)
    : iFilename(aFilename)
{}

TestHttpSession* SessionFactory::Create(ESession aSession)
{
    switch (aSession)
    {
    case eStreamFull:
        return new TestHttpSessionStreamFull(iFilename);
    case eReject:
        return new TestHttpSessionReject(iFilename);
    case eReconnect:
        return new TestHttpSessionReconnect(iFilename);
    case eStreamLive:
        return new TestHttpSessionStreamLive(iFilename);
    case eLiveReconnect:
        return new TestHttpSessionLiveReconnect(iFilename);
    default:
        ASSERTS();
        return NULL;    // Will never reach here.
    }
}


// TestHttpSupplier

TestHttpSupplier::TestHttpSupplier(TUint aDataSize)
    : iDataSize(aDataSize)
    , iTrackId(0)
    , iStreamId(0)
    , iLive(false)
    , iTrackCount(0)
    , iStreamCount(0)
    , iDataTotal(0)
    , iStreamHandler(NULL)
{
}

TestHttpSupplier::~TestHttpSupplier() {}

TUint TestHttpSupplier::TrackId()
{
    return iTrackId;
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

void TestHttpSupplier::OutputTrack(Track& /*aTrack*/, TUint aTrackId)
{
    //Log::Print("TestHttpSupplier::OutputTrack %u\n", aTrackId);
    iTrackId = aTrackId;
    iTrackCount++;
}

void TestHttpSupplier::OutputStream(const Brx& /*aUri*/, TUint64 /*aTotalBytes*/, TBool /*aSeekable*/, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId)
{
    //Log::Print("TestHttpSupplier::OutputStream\n");
    iLive = aLive;
    iStreamId = aStreamId;
    iStreamHandler = &aStreamHandler;
    (void)aStreamHandler.OkToPlay(iTrackId, iStreamId);
    iStreamCount++;
}

void TestHttpSupplier::OutputData(const Brx& aData)
{
    //Log::Print("TestHttpSupplier::OutputData\n");
    iDataTotal += aData.Bytes();
    if (iLive && iDataTotal >= iDataSize) {
        // We are only simulating a live stream, so want to tell
        // client to stop when data has run out.
        iStreamHandler->TryStop(iTrackId, iStreamId);
    }
}

void TestHttpSupplier::OutputMetadata(const Brx& /*aMetadata*/)
{
    //Log::Print("TestHttpSupplier::OutputMetadata\n");
}

void TestHttpSupplier::OutputFlush(TUint /*aFlushId*/)
{
    //Log::Print("TestHttpSupplier::OutputFlush\n");
}

void TestHttpSupplier::OutputQuit()
{
    //Log::Print("TestHttpSupplier::OutputQuit\n");
}


// TestHttpPipelineProvider

TestHttpPipelineProvider::TestHttpPipelineProvider()
    : iNextTrackId(kInvalidPipelineId+1)
    , iNextStreamId(kInvalidPipelineId+1)
{
}

TestHttpPipelineProvider::~TestHttpPipelineProvider()
{
}

TUint TestHttpPipelineProvider::NextTrackId()
{
    //Log::Print("TestHttpPipelineProvider::NextTrackId\n");
    return iNextTrackId++;
}

TUint TestHttpPipelineProvider::NextStreamId()
{
    //Log::Print("TestHttpPipelineProvider::NextStreamId\n");
    return iNextStreamId++;
}

EStreamPlay TestHttpPipelineProvider::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    //Log::Print("TestHttpPipelineProvider::OkToPlay\n");
    return ePlayYes;
}

void TestHttpPipelineProvider::InvalidateAt(const Brx& /*aStyle*/, const Brx& /*aProviderId*/)
{
    ASSERTS();
}

void TestHttpPipelineProvider::InvalidateAfter(const Brx& /*aStyle*/, const Brx& /*aProviderId*/)
{
    ASSERTS();
}

void TestHttpPipelineProvider::InvalidateAll()
{
    ASSERTS();
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
    // The file to be served.
    Brn serveFile("10s-stereo-44k.wav");

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

    // Try opening the file to get the size.
    TUint iDataSize = 0;
    try {
        IFile *file = IFile::Open(Brhz(serveFile).CString(), eFileReadOnly);
        iDataSize = file->Bytes();
        delete file;
    }
    catch (FileOpenError aFileErr) {
        ASSERTS();
    }

    // Create a custom HTTP session for testing purposes.
    SessionFactory factory(serveFile);
    iHttpSession = factory.Create(aSession);
    iServer->Add("HTP1", iHttpSession);

    // Create our HTTP client.
    iSupply = new TestHttpSupplier(iDataSize);
    iProvider = new TestHttpPipelineProvider();
    iFlushId = new TestHttpFlushIdProvider();

    iProtocolManager = new ProtocolManager(*iSupply, *iProvider, *iFlushId);
    iProtocolManager->Add(ProtocolFactory::NewHttp(*gEnv));

    iTrackFactory= new TrackFactory(iInfoAggregator, 1);
}

SuiteHttp::~SuiteHttp()
{
    delete iTrackFactory;
    delete iProtocolManager;
    delete iProvider;
    delete iSupply;
    delete iServer;
    //delete iHttpSession;    // Owned by iHttpSession.
    delete iFlushId;
}


// SuiteHttpStreamFull

SuiteHttpStreamFull::SuiteHttpStreamFull()
    : SuiteHttp("HTTP file streaming tests", SessionFactory::eStreamFull)
{
}

void SuiteHttpStreamFull::Test()
{
    // Test if streaming is successful.
    Track* track = iTrackFactory->CreateTrack(iServer->ServingUri().AbsoluteUri(), Brx::Empty(), Brx::Empty(), Brx::Empty(), 0);
    TBool boolStream = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(boolStream == 1);

    // Test if a single track message is received.
    TEST(iSupply->TrackCount() == 1);

    // Test if a single stream message is received.
    TEST(iSupply->StreamCount() == 1);

    // Test if it was a live stream
    TEST(iSupply->Live() == false);

    // Test if the data transferred is equivalent to the file size.
    TUint fileSize = iHttpSession->DataSize();
    TUint dataTotal = iSupply->DataTotal();
    TEST(fileSize == dataTotal);
}


// SuiteHttpReject

SuiteHttpReject::SuiteHttpReject()
    : SuiteHttp("HTTP server rejection tests", SessionFactory::eReject)
{
}

void SuiteHttpReject::Test()
{
    // Test if streaming is successful.
    Track* track = iTrackFactory->CreateTrack(iServer->ServingUri().AbsoluteUri(), Brx::Empty(), Brx::Empty(), Brx::Empty(), 0);
    TBool boolStream = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(boolStream == 1);

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
    : SuiteHttp("HTTP file stream reconnection tests", SessionFactory::eReconnect)
{
}

void SuiteHttpReconnect::Test()
{
    // Test if streaming is successful.
    Track* track = iTrackFactory->CreateTrack(iServer->ServingUri().AbsoluteUri(), Brx::Empty(), Brx::Empty(), Brx::Empty(), 0);
    TBool boolStream = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(boolStream == 1);

    // Test if a single track message is received.
    TEST(iSupply->TrackCount() == 1);

    // Test if a single stream message is received.
    TEST(iSupply->StreamCount() == 1);

    // Test if it was a live stream
    TEST(iSupply->Live() == false);

    // Test if the total data transferred over both sessions is equivalent to the file size.
    TUint fileSize = iHttpSession->DataSize();
    TUint dataTotal = iSupply->DataTotal();
    TEST(fileSize == dataTotal);
}


// SuiteHttpStreamLive

SuiteHttpStreamLive::SuiteHttpStreamLive()
    : SuiteHttp("HTTP live streaming tests", SessionFactory::eStreamLive)
{
}

void SuiteHttpStreamLive::Test()
{
    // Test if streaming is successful.
    Track* track = iTrackFactory->CreateTrack(iServer->ServingUri().AbsoluteUri(), Brx::Empty(), Brx::Empty(), Brx::Empty(), 0);
    TBool boolStream = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(boolStream == false);

    // Test if a single track message is received.
    TEST(iSupply->TrackCount() == 1);

    // Test if a single stream message is received.
    TEST(iSupply->StreamCount() == 1);

    // Test if it was a live stream
    TEST(iSupply->Live() == true);

    // Test if the total data transferred over both sessions is equivalent to the file size.
    TUint fileSize = iHttpSession->DataSize();
    TUint dataTotal = iSupply->DataTotal();
    TEST(fileSize <= dataTotal);
}


// SuiteHttpLiveReconnect : SuiteHttp

SuiteHttpLiveReconnect::SuiteHttpLiveReconnect()
    : SuiteHttp("HTTP live stream reconnection tests", SessionFactory::eLiveReconnect)
{
}

void SuiteHttpLiveReconnect::Test()
{
    // Test if streaming is successful.
    Track* track = iTrackFactory->CreateTrack(iServer->ServingUri().AbsoluteUri(), Brx::Empty(), Brx::Empty(), Brx::Empty(), 0);
    TBool boolStream = iProtocolManager->DoStream(*track);
    track->RemoveRef();
    TEST(boolStream == false);

    // Test if a single track message is received.
    TEST(iSupply->TrackCount() == 1);

    // Test if a single stream message is received.
    TEST(iSupply->StreamCount() == 1);

    // Test if it was a live stream
    TEST(iSupply->Live() == true);

    // Test if the total data transferred over both sessions is equivalent to the file size.
    TUint fileSize = iHttpSession->DataSize();
    TUint dataTotal = iSupply->DataTotal();
    TEST(fileSize <= dataTotal);
}


void TestHttp()
{
    Runner runner("HTTP tests\n");
    runner.Add(new SuiteHttpStreamFull());
    runner.Add(new SuiteHttpReject());
    runner.Add(new SuiteHttpReconnect());
    runner.Add(new SuiteHttpStreamLive());
    runner.Add(new SuiteHttpLiveReconnect());
    runner.Run();
}
