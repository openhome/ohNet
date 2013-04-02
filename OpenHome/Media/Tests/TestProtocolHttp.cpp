#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/ProtocolHttp.h>
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

class TestHttpSession;

class TestHttpServer : public SocketTcpServer
{
public:
    enum EMode
    {
        eStreamFull = 0,            // Stream a full track.
        eServerReject = 1,          // Server sends bad initial response.
        eServerRejectDoStream = 2,  // DoStream reaction after bad initial response.
        eStreamFail = 3,            // Fail part way through streaming.
        eStreamReconnect = 4,       // Server allows reconnection after a failed stream.
        eStreamLive = 5,            // Live streaming.
        eLiveReconnect = 6          // Client reconnects to commence live streaming.
    };
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
    TestHttpServer(Environment& aEnv, const TChar* aName, TUint aPort, TIpAddress aInterface,
                   EMode aMode = eStreamFull);
    ~TestHttpServer();
    EMode Mode() const;
    void SetMode(EMode aMode);
    const Uri ServingUri() const;
private:
    EMode iMode;
    const Uri* iUri;
};

class TestHttpSession : public SocketTcpSession
{
public:
    TestHttpSession(const Brx& aFilename, TestHttpServer* aServer);
    ~TestHttpSession();
    TUint DataSize() const;
    void Reset();
private: // from SocketTcpSession
    void Run();
private:
    static const TUint kMaxReadBytes = 1024;
    static const TUint kReadTimeoutMs = 5000;
    static const TUint kMaxWriteBufBytes = 1400;
    const HttpStatus* iErrorStatus; // Default is HttpStatus::kOk
    HttpHeaderConnection iHeaderConnection;
    HttpHeaderRange iHeaderRange;
    // Hosting server.
    TestHttpServer* iServer;
    // File attributes.
    const Brhz iFilename;
    IFile* iFile;
    TUint iDataSize;
    // Reader and buffer.
    Srs<kMaxReadBytes>* iReadBuffer;
    ReaderHttpRequest* iReaderRequest;
    // Writer and buffer.
    Sws<kMaxWriteBufBytes>* iWriterBuffer;
    WriterHttpResponse* iWriterResponse;
    Bwh iBuf;
};

class TestHttpSupplier : public ISupply
{
public:
    TestHttpSupplier();
    virtual ~TestHttpSupplier();
public:
    TUint TrackCount();
    TUint StreamCount();
    TUint DataTotal();
    void Reset();
public: // from ISupply
    void OutputTrack(const Brx& aUri, TUint aTrackId);
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId);
    void OutputData(const Brx& aData);
    void OutputMetadata(const Brx& aMetadata);
    void OutputFlush(TUint aFlushId);
    void OutputQuit();
private:
    TUint iCurrTrackId;
    TUint iTrackCount;
    TUint iStreamCount;
    TUint iDataTotal;
};

class TestHttpPipelineProvider : public IPipelineIdProvider
{
public:
    TestHttpPipelineProvider();
    virtual ~TestHttpPipelineProvider();
public: // from IPipelineIdProvider
    TUint NextTrackId();
    TUint NextStreamId();
    TBool OkToPlay(TUint aTrackId);
private:
    TUint iNextTrackId;
    TUint iNextStreamId;
    static const TUint kInvalidPipelineId = 0;
};

class TestHttpFlushIdProvider : public IFlushIdProvider
{
public:
    TestHttpFlushIdProvider();;
public: // from iFlushIdProvider
    TUint NextFlushId();
private:
    TUint iNextFlushId;
};

class SuiteHttp : public Suite
{
public:
    SuiteHttp();
    ~SuiteHttp();
    void Test();
    void TestStreamFull();
    void TestServerReject();
    void TestServerRejectDoStream();
    void TestStreamReconnect();
    void TestStreamLive();
private:
    TestHttpServer* iServer;
    TestHttpSession* iHttpSession;
    TestHttpSupplier* iSupply;
    TestHttpPipelineProvider* iProvider;
    TestHttpFlushIdProvider* iFlushId;
    ProtocolManager* iProtocolManager;
    ProtocolHttp* iProtocolHttp;
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
    return (Ascii::CaseInsensitiveEquals(aHeader, Http::kHeaderRange));
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
        if (indEquals == aValue.Bytes()) {	// An equals sign does not exist.
            THROW(HttpError);
        }

        indEquals++; // Shift index so we skip over separator.
        range = aValue.Split(indEquals, aValue.Bytes()-indEquals);

        indHyphen = Ascii::IndexOf(range, '-');
        if (indHyphen == range.Bytes()) {	// A hyphen does not exist, so range points are not specified.
            THROW(HttpError);
        }

        Brn start(range.Ptr(), indHyphen);		// Get the start value.
        indHyphen++; // Shift index so we skip over separator.
        end = range.Split(indHyphen, range.Bytes()-indHyphen);	// Get the end value.

        iStart = Ascii::Uint(start);
        if (end.Bytes() == 0) {	// End range may be empty.
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

    Log::Print("PartialContent val: ");
    Log::Print(Http::kHeaderContentRange);
    Log::Print(": ");
    Log::Print(buf);
    Log::Print("\n");

    aWriter.WriteHeader(Http::kHeaderContentRange, buf);
}

void TestHttpServer::WriteHeaderPartialContentStream(WriterHttpHeader& aWriter)
{
    WriteHeaderPartialContent(aWriter, 0, 0, TestHttpServer::kTotalContentUnknown);
}

TestHttpServer::TestHttpServer(Environment& aEnv, const TChar* aName, TUint aPort, TIpAddress aInterface,
                               EMode aMode)
    :SocketTcpServer(aEnv, aName, aPort, aInterface)
    , iMode(aMode)
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

TestHttpServer::EMode TestHttpServer::Mode() const
{
    return iMode;
}

void TestHttpServer::SetMode(TestHttpServer::EMode aMode)
{
    iMode = aMode;
}

const Uri TestHttpServer::ServingUri() const
{
    return *iUri;
}


// TestHttpSession

TestHttpSession::TestHttpSession(const Brx& aFilename, TestHttpServer* aServer)
    : iErrorStatus(&HttpStatus::kOk)
    , iServer(aServer)
    , iFilename(aFilename)
    , iBuf(kMaxWriteBufBytes)
{
    // Try opening the file.
    try {
        iFile = IFile::Open(iFilename.CString(), eFileReadOnly);
        Log::Print("file bytes: %u\n", iFile->Bytes());
    }
    catch (FileOpenError aFileErr) {
        Log::Print("FileOpenError: %s\n", aFileErr.File());
        Log::Print("FileOpenError: %s\n", aFileErr.Message());
        throw;
    }

    iDataSize = iFile->Bytes();

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

void TestHttpSession::Reset()
{
    delete iFile;

    // Try reopening the file.
    try {
        iFile = IFile::Open(iFilename.CString(), eFileReadOnly);
    }
    catch (FileOpenError aFileErr) {
        Log::Print("FileOpenError: %s\n", aFileErr.File());
        Log::Print("FileOpenError: %s\n", aFileErr.Message());
        throw;
    }

    iDataSize = iFile->Bytes();
}

TUint TestHttpSession::DataSize() const
{
    return iDataSize;
}

void TestHttpSession::Run() // FIXME - refactor
{
    iErrorStatus = &HttpStatus::kOk;
    //AutoSemaphore a(iShutdownSem);

    if (iServer->Mode() == TestHttpServer::eStreamFull) {
        Log::Print("TestHttpServer::eStreamFull\n");
        try {
            TUint bytesRemaining = iDataSize;

            // Wait on a request.
            iReaderRequest->Flush();
            iReaderRequest->Read(kReadTimeoutMs);

            // Write the header back with the content length.
            iWriterResponse->WriteStatus(*iErrorStatus, Http::eHttp11);
            Http::WriteHeaderContentLength(*iWriterResponse, iDataSize);
            iWriterResponse->WriteFlush();

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
            //iWriterResponse->WriteFlush();
            //this->WriteFlush();
        }
        catch (HttpError) {ASSERTS();}
        catch (ReaderError) {ASSERTS();}
        catch (WriterError) {ASSERTS();}
        catch (NetworkError) {ASSERTS();}
    }
    else if (iServer->Mode() == TestHttpServer::eServerReject) {
        Log::Print("TestHttpServer::eServerReject\n");
        iErrorStatus = &HttpStatus::kBadRequest;
        try {
            // Wait on a request.
            iReaderRequest->Flush();
            iReaderRequest->Read(kReadTimeoutMs);

            // Send a header response indicating some issue resulting in non-streaming.
            iWriterResponse->WriteStatus(*iErrorStatus, Http::eHttp11);
            iWriterResponse->WriteFlush();
        }
        catch (HttpError) {ASSERTS();}
        catch (ReaderError) {ASSERTS();}
        catch (WriterError) {ASSERTS();}
        catch (NetworkError) {ASSERTS();}
        iErrorStatus = &HttpStatus::kOk;
    }
    else if (iServer->Mode() == TestHttpServer::eStreamFail) {
        Log::Print("TestHttpServer::eStreamFail\n");
        try {
            // Point to break streaming - middle of track.
            TUint totalBuffs = iDataSize/iBuf.MaxBytes();
            TUint pausePoint = totalBuffs/2;
            TUint writeCount = 0;
            TUint bytesRemaining = iDataSize;

            Log::Print("totalBuffs: %u\n", totalBuffs);
            Log::Print("pausePoint: %u\n", pausePoint);

            // Wait on a request.
            iReaderRequest->Flush();
            iReaderRequest->Read(kReadTimeoutMs);

            // Write the header back with the content length.
            iWriterResponse->WriteStatus(*iErrorStatus, Http::eHttp11);
            Http::WriteHeaderContentLength(*iWriterResponse, iDataSize);
            iWriterResponse->WriteFlush();

            // Loop until we've streamed all of file, pausing  somewhere in the middle of streaming.
            while (bytesRemaining > 0) {
                // Simulate break in streaming.
                if (writeCount == pausePoint) {
                    Log::Print("Bytes written: %u\n", iDataSize-bytesRemaining);
                    iWriterBuffer->WriteFlush();
                    iServer->SetMode(TestHttpServer::eStreamReconnect);
                    this->Reset();
                    //iWriterResponse->WriteFlush();
                    //this->WriteFlush();
                    return;        // Close the session.
                }

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

                writeCount++;
            }
            iWriterBuffer->WriteFlush();
            //iWriterResponse->WriteFlush();
            //this->WriteFlush();
        }
        catch (HttpError) {ASSERTS();}
        catch (ReaderError) {ASSERTS();}
        catch (WriterError) {ASSERTS();}
        catch (NetworkError) {ASSERTS();}
    }
    else if (iServer->Mode() == TestHttpServer::eStreamReconnect) {
        Log::Print("TestHttpServer::eStreamReconnect\n");
        try {
            TUint startByte = 0;
            TUint bytesRemaining = 0;

            // Wait on a request.
            iReaderRequest->Flush();
            iReaderRequest->Read(kReadTimeoutMs);

            if (iHeaderRange.Received()) {
                Log::Print("Range start: %u\n", iHeaderRange.Start());
                Log::Print("Range end: %u\n", iHeaderRange.End());
                startByte = iHeaderRange.Start();
            }
            else {
                ASSERTS();
            }

            // Write the header back with the content length.
            iErrorStatus = &HttpStatus::kPartialContent;
            iWriterResponse->WriteStatus(*iErrorStatus, Http::eHttp11);
            TestHttpServer::WriteHeaderPartialContent(*iWriterResponse, startByte, iDataSize-1, iDataSize);
            Http::WriteHeaderContentLength(*iWriterResponse, iDataSize-startByte);
            iWriterResponse->WriteFlush();


            // Seek to resume point in file.
            iFile->Seek(startByte, eSeekFromStart);
            bytesRemaining = iDataSize-startByte;
            //iFile->Seek(0, eSeekFromStart);
            //bytesRemaining = iDataSize;
            Log::Print("Filesize-request: %u-%u=%u\n", iDataSize, startByte, iDataSize-startByte);
            Log::Print("bytesRemaining: %u\n", bytesRemaining);

            // Stream remaining bytes.
            while (bytesRemaining > 0) {
                // Bytes to read from file.
                iBuf.SetBytes(0);
                TUint bytes = iBuf.MaxBytes();
                if (bytesRemaining < bytes) {
                    bytes = bytesRemaining;
                }

                // Read from the file.
                iFile->Read(iBuf, bytes);

                //Log::Print("Bytes read: %u\n", iBuf.Bytes());

                // Check the number of bytes read is what we expected; file error otherwise.
                if (iBuf.Bytes() != bytes) {
                    ASSERTS();
                }
                bytesRemaining -= bytes;

                // Write file data out.
                //Log::Print("Before iWriterBuffer->Write\n");
                //Log::Print("bytesRemaining: %u\n", bytesRemaining);
                iWriterResponse->Write(iBuf);
                //Log::Print("After iWriterBuffer->Write\n");
            }
            Log::Print("Before iWriterBuffer->WriteFlush\n");
            iWriterBuffer->WriteFlush();
            Log::Print("After iWriterBuffer->WriteFlush\n");
            //iWriterResponse->WriteFlush();
            //this->WriteFlush();
        }
        catch (HttpError) {ASSERTS();}
        catch (ReaderError) {ASSERTS();}
        catch (WriterError) {ASSERTS();}
        catch (NetworkError) {ASSERTS();}

        iErrorStatus = &HttpStatus::kOk;
    }
    else if (iServer->Mode() == TestHttpServer::eStreamLive) {
        Log::Print("TestHttpServer::eStreamLive\n");
        try {
            //TUint bytesRemaining = iDataSize;

            // Wait on a request.
            iReaderRequest->Flush();
            iReaderRequest->Read(kReadTimeoutMs);

            // Write the header back.
            iWriterResponse->WriteStatus(*iErrorStatus, Http::eHttp11);
            iWriterResponse->WriteFlush();
            iServer->SetMode(TestHttpServer::eLiveReconnect);
        }
        catch (HttpError) {ASSERTS();}
        catch (ReaderError) {ASSERTS();}
        catch (WriterError) {ASSERTS();}
        catch (NetworkError) {ASSERTS();}
    }
    else if (iServer->Mode() == TestHttpServer::eLiveReconnect) {
        Log::Print("TestHttpServer::eLiveReconnect\n");
        try {
            TUint startByte = 0;
            TUint bytesRemaining = iDataSize;

            // Wait on a request.
            iReaderRequest->Flush();
            iReaderRequest->Read(kReadTimeoutMs);

            if (iHeaderRange.Received()) {
                Log::Print("Range start: %u\n", iHeaderRange.Start());
                Log::Print("Range end: %u\n", iHeaderRange.End());
                startByte = iHeaderRange.Start();
            }
            else {
                ASSERTS();
            }

            // Write the header back with the content range.
            iErrorStatus = &HttpStatus::kPartialContent;
            iWriterResponse->WriteStatus(*iErrorStatus, Http::eHttp11);
            TestHttpServer::WriteHeaderPartialContentStream(*iWriterResponse);
            Http::WriteHeaderContentLength(*iWriterResponse, iDataSize-startByte);
            iWriterResponse->WriteFlush();

            bytesRemaining = iDataSize;
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
                    Log::Print("iBuf.Bytes: %u, bytes: %u\n", iBuf.Bytes(), bytes);
                    ASSERTS();
                }
                bytesRemaining -= bytes;

                // Write file data out.
                iWriterResponse->Write(iBuf);
            }
            iWriterBuffer->WriteFlush();
            //iWriterResponse->WriteFlush();
            //this->WriteFlush();
        }
        catch (HttpError) {ASSERTS();}
        catch (ReaderError) {ASSERTS();}
        catch (WriterError) {ASSERTS();}
        catch (NetworkError) {ASSERTS();}
    }
}


// TestHttpSupplier

TestHttpSupplier::TestHttpSupplier()
    : iCurrTrackId(0)
    , iTrackCount(0)
    , iStreamCount(0)
    , iDataTotal(0)
{
}

TestHttpSupplier::~TestHttpSupplier()
{
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

void TestHttpSupplier::Reset()
{
    iCurrTrackId = 0;
    iTrackCount = 0;
    iStreamCount = 0;
    iDataTotal = 0;
}

void TestHttpSupplier::OutputTrack(const Brx& /*aUri*/, TUint aTrackId)
{
    iCurrTrackId = aTrackId;
    iTrackCount++;
    Log::Print("><TestHttpSupplier::OutputTrack %u\n", aTrackId);
}

void TestHttpSupplier::OutputStream(const Brx& /*aUri*/, TUint64 aTotalBytes, TBool /*aSeekable*/, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId)
{
    if (aLive) {
        Log::Print("TestHttpSupplier::OutputStream live stream\n");
    }
    aStreamHandler.OkToPlay(iCurrTrackId, aStreamId);
    iStreamCount++;
    Log::Print("><TestHttpSupplier::OutputStream\n");
    Log::Print("aTotalBytes: %u bytes.\n", aTotalBytes);
}

void TestHttpSupplier::OutputData(const Brx& aData)
{
    iDataTotal += aData.Bytes();
    //Log::Print("TestHttpSupplier::OutputData\n");
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
    Log::Print(">TestHttpPipelineProvider::NextTrackId\n");
    return iNextTrackId++;
}

TUint TestHttpPipelineProvider::NextStreamId()
{
    Log::Print(">TestHttpPipelineProvider::NextStreamId\n");
    return iNextStreamId++;
}

TBool TestHttpPipelineProvider::OkToPlay(TUint /*aTrackId*/)
{
    Log::Print(">TestHttpPipelineProvider::OkToPlay\n");
    return true;
}


// TestHttpFlushIdProvider

TestHttpFlushIdProvider::TestHttpFlushIdProvider()
    : iNextFlushId(MsgFlush::kIdInvalid + 1)
{
}

TUint TestHttpFlushIdProvider::NextFlushId()
{
    return iNextFlushId++;
}


// SuiteHttp

SuiteHttp::SuiteHttp()
    : Suite("HTTP tests")
{
    // The file to be served.
    //Brn serveFile("TestTones/1k_tone-10s.wav");
    Brn serveFile("1k_tone-10s-stereo.wav");
    // Get a list of network adapters (using loopback, so first one should do).
    std::vector<NetworkAdapter*>* ifs = Os::NetworkListAdapters(*gEnv, Net::InitialisationParams::ELoopbackUse, "Loopback");
    TIpAddress addr = (*ifs)[0]->Address();
    for (TUint i=0; i<ifs->size(); i++) {
        (*ifs)[i]->RemoveRef("Loopback");
    }
    delete ifs;

    // Create our TCP server.
    iServer = new TestHttpServer(*gEnv, "HSV1", 0, addr, TestHttpServer::eStreamFull);

    Log::Print("uri1: ");
    Log::Print(iServer->ServingUri().AbsoluteUri());
    Log::Print("\n");

    // Create a custom HTTP session for testing purposes.
    iHttpSession = new TestHttpSession(serveFile, iServer);
    iServer->Add("HTP1", iHttpSession);

    // Create our HTTP client.
    iSupply = new TestHttpSupplier();
    iProvider = new TestHttpPipelineProvider();
    iFlushId = new TestHttpFlushIdProvider();

    iProtocolManager = new ProtocolManager(*iSupply, *iProvider, *iFlushId);
    iProtocolHttp = new ProtocolHttp(*gEnv);
    iProtocolManager->Add(iProtocolHttp);
}

SuiteHttp::~SuiteHttp()
{
    delete iProtocolManager;
    //delete iProtocolHttp;    // Owned by iProtocolManager.
    delete iProvider;
    delete iSupply;
    delete iServer;
    //delete iHttpSession;    // Owned by iHttpSession.
}

void SuiteHttp::Test()
{
    //Debug::SetLevel(Debug::kHttp);
    Debug::SetLevel(Debug::kMedia);

    Functor tests[] = { MakeFunctor(*this, &SuiteHttp::TestStreamFull)
                       ,MakeFunctor(*this, &SuiteHttp::TestServerReject)
                       ,MakeFunctor(*this, &SuiteHttp::TestStreamReconnect)
                       //,MakeFunctor(*this, &SuiteHttp::TestStreamLive)
                      };
    for (TUint i=0; i<sizeof(tests)/sizeof(tests[0]); i++) {
        tests[i]();
        iHttpSession->Reset();
        iSupply->Reset();
    }
}

void SuiteHttp::TestStreamFull()
{
    iServer->SetMode(TestHttpServer::eStreamFull);

    // Test if streaming is successful.
    TBool boolStream = iProtocolManager->DoStream(iServer->ServingUri().AbsoluteUri());
    TEST(boolStream == 1);

    // Test if a single track message is received.
    TEST(iSupply->TrackCount() == 1);

    // Test if a single stream message is received.
    TEST(iSupply->StreamCount() == 1);

    // Test if the data transferred is equivalent to the file size.
    TUint fileSize = iHttpSession->DataSize();
    TUint dataTotal = iSupply->DataTotal();
    TEST(fileSize == dataTotal);
}

void SuiteHttp::TestServerReject()
{
    iServer->SetMode(TestHttpServer::eServerReject);

    // Test if streaming is successful.
    TBool boolStream = iProtocolManager->DoStream(iServer->ServingUri().AbsoluteUri());
    TEST(boolStream == 1);

    // Test if a single track message is received.
    TEST(iSupply->TrackCount() == 1);

    // Test if no stream message is received.
    TEST(iSupply->StreamCount() == 0);

    // Test if no data was transferred.
    TUint dataTotal = iSupply->DataTotal();
    TEST(dataTotal == 0);
}

void SuiteHttp::TestStreamReconnect()
{
    iServer->SetMode(TestHttpServer::eStreamFail);

    // Test if streaming is successful.
    TBool boolStream = iProtocolManager->DoStream(iServer->ServingUri().AbsoluteUri());
    TEST(boolStream == 1);

    // Test if a single track message is received.
    TEST(iSupply->TrackCount() == 1);

    // Test if a single stream message is received.
    TEST(iSupply->StreamCount() == 1);

    // Test if the total data transferred over both sessions is equivalent to the file size.
    TUint fileSize = iHttpSession->DataSize();
    TUint dataTotal = iSupply->DataTotal();
    TEST(fileSize == dataTotal);
}

void SuiteHttp::TestStreamLive()
{
    iServer->SetMode(TestHttpServer::eStreamLive);

    // Test if streaming is successful.
    TBool boolStream = iProtocolManager->DoStream(iServer->ServingUri().AbsoluteUri());
    TEST(boolStream == 1);

    //// Test if a single track message is received.
    //TEST(iSupply->TrackCount() == 1);

    //// Test if a single stream message is received.
    //TEST(iSupply->StreamCount() == 1);

    //// Test if the total data transferred over both sessions is equivalent to the file size.
    //TUint fileSize = iHttpSession->DataSize();
    //TUint dataTotal = iSupply->DataTotal();
    //TEST(fileSize == dataTotal);
}

void TestHttp()
{
    Runner runner("HTTP tests\n");
    runner.Add(new SuiteHttp());
    runner.Run();
}
