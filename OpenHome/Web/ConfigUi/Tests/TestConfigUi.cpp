#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Net/Private/XmlParser.h>
#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Media/Utils/AnimatorBasic.h>

#include <OpenHome/Web/WebAppFramework.h>
#include <OpenHome/Web/ConfigUi/ConfigUi.h>
#include <OpenHome/Av/Tests/TestMediaPlayer.h>


namespace OpenHome {
namespace Web {
namespace Test {

class HelperDeviceListHandler
{
public:
    HelperDeviceListHandler(const OpenHome::Brx& aExpectedFriendlyName);
    void Added(OpenHome::Net::CpDevice& aDevice);
    void Removed(OpenHome::Net::CpDevice& aDevice);
    const OpenHome::Brx& GetPresentationUrl() const;
private:
    OpenHome::Brh iFriendlyName;
    OpenHome::Bws<OpenHome::Uri::kMaxUriBytes> iPresentationUrl;
    mutable OpenHome::Mutex iLock;
};

class UriRetriever
{
private:
    static const TUint kReadBufferBytes = 1024;
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kMaxResponseChunkBytes = 1024;
    static const TUint kConnectTimeoutMs = 3000;
public:
    UriRetriever(Environment& aEnv, const Uri& aBaseUri);
    TUint Retrieve(const Brx& aTail, const Brx& aMethod, const Brx& aRequest, IWriter& aResponseWriter);
private:
    TUint RetrieveUriSocketOpen(const Brx& aMethod, const Brx& aRequest, IWriter& aResponseWriter);
    void SetUriBase(const Uri& aUri);
private:
    Environment& iEnv;
    Bws<Uri::kMaxUriBytes> iUriBaseBuf;
    Uri iUri;
    SocketTcpClient iTcpClient;
    Srs<kReadBufferBytes> iReaderBuf;
    ReaderUntilS<kReadBufferBytes> iReaderUntil;
    Sws<kWriteBufferBytes> iWriterBuf;

    WriterHttpRequest iWriterRequest;
    ReaderHttpResponse iReaderResponse;
    //ReaderHttpChunked iDechunker;
    HttpHeaderContentType iHeaderContentType;
    HttpHeaderContentLength iHeaderContentLength;
};

class WriterPrinter : public IWriter
{
public:
    WriterPrinter();
    TUint BytesPrinted() const;
    void Reset();
public: // from IWriter
    void Write(TByte aValue) override;
    void Write(const Brx& aBuffer) override;
    void WriteFlush() override;
private:
    TUint iBytesPrinted;
};

// ConfigApps are not expected to check the existence of ConfigVals at startup.
// This means that the ConfigManager will assert when the config page is loaded
// if a ConfigVal included in the ConfigApp doesn't exist in the ConfigManager.

// This test exploits that behaviour to check if the ConfigApp is valid by
// loading the web page and initiating long-polling. If the ConfigManager
// doesn't assert, the ConfigVals in the ConfigApp are all valid.

// As a side-effect, this test also checks that the (default) language mapping
// for ConfigOptions is valid (i.e., the mapping file is correctly formed, and
// mapping entries for each ConfigOption are listed in the same order that they
// are programmatically added to the ConfigOption).

class SuiteConfigUi : public OpenHome::TestFramework::SuiteUnitTest, public OpenHome::INonCopyable
{
private:
    static const TUint kMaxUiTabs = 4;
    static const TUint kUiSendQueueSize = 32;
public:
    SuiteConfigUi(OpenHome::Net::CpStack& aCpStack, OpenHome::Net::DvStack& aDvStack);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void Run();
    void TestGetStaticResource();
    void TestLongPollCreate();
    void TestLongPoll();
private:
    OpenHome::Net::CpStack& iCpStack;
    OpenHome::Net::DvStack& iDvStack;
    OpenHome::Media::AnimatorBasic* iAnimator;
    OpenHome::Av::Test::TestMediaPlayer* iMediaPlayer;
    OpenHome::ThreadFunctor* iMediaPlayerThread;
    HelperDeviceListHandler* iDeviceListHandler;
};

} // namespace Test
} // namespace Web
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Web;
using namespace OpenHome::Web::Test;


// HelperDeviceListHandler

HelperDeviceListHandler::HelperDeviceListHandler(const Brx& aExpectedFriendlyName)
    : iFriendlyName(aExpectedFriendlyName)
    , iLock("DLLM")
{
}

void HelperDeviceListHandler::Added(CpDevice& aDevice)
{
    Brh xml;
    aDevice.GetAttribute("Upnp.DeviceXml", xml);
    try {
        Brn presentationUrl = XmlParserBasic::Find("presentationURL", xml);
        Brn friendlyName = XmlParserBasic::Find("friendlyName", xml);
        Log::Print("friendlyName: ");
        Log::Print(friendlyName);
        Log::Print("\n");
        if (friendlyName == iFriendlyName) {
            AutoMutex a(iLock);
            ASSERT(iPresentationUrl.Bytes() == 0);
            iPresentationUrl.Replace(presentationUrl);
        }
    }
    catch (XmlError&) {
        // Do nothing.
    }
}

void HelperDeviceListHandler::Removed(CpDevice& /*aDevice*/)
{
}

const Brx& HelperDeviceListHandler::GetPresentationUrl() const
{
    AutoMutex a(iLock);
    return iPresentationUrl;
}


// UriRetriever

UriRetriever::UriRetriever(Environment& aEnv, const Uri& aBaseUri)
    : iEnv(aEnv)
    , iReaderBuf(iTcpClient)
    , iReaderUntil(iReaderBuf)
    , iWriterBuf(iTcpClient)
    , iWriterRequest(iWriterBuf)
    , iReaderResponse(iEnv, iReaderUntil)
{
    iReaderResponse.AddHeader(iHeaderContentType);
    iReaderResponse.AddHeader(iHeaderContentLength);
    SetUriBase(aBaseUri);
}

TUint UriRetriever::Retrieve(const Brx& aTail, const Brx& aMethod, const Brx& aRequest, IWriter& aResponseWriter)
{
    iUri.Replace(iUriBaseBuf, aTail);

    Log::Print("UriRetriever::Retrieve: ");
    Log::Print(iUri.AbsoluteUri());
    Log::Print("\n");

    iTcpClient.Open(iEnv);
    TUint code = RetrieveUriSocketOpen(aMethod, aRequest, aResponseWriter);
    iTcpClient.Close();
    return code;
}

TUint UriRetriever::RetrieveUriSocketOpen(const Brx& aMethod, const Brx& aRequest, IWriter& aResponseWriter)
{
    TUint code = 0;
    Endpoint ep(iUri.Port(), iUri.Host());

    try {
        iTcpClient.Connect(ep, kConnectTimeoutMs);
    }
    catch (NetworkTimeout&) {
        return code;
    }
    catch (NetworkError&) {
        return code;
    }

    try {
        iWriterRequest.WriteMethod(aMethod, iUri.PathAndQuery(), Http::eHttp11);
        const TUint port = (iUri.Port() == -1 ? 80 : (TUint)iUri.Port());
        Http::WriteHeaderHostAndPort(iWriterRequest, iUri.Host(), port);
        Http::WriteHeaderContentLength(iWriterRequest, aRequest.Bytes());
        Http::WriteHeaderConnectionClose(iWriterRequest);
        iWriterRequest.WriteFlush();
        iWriterBuf.Write(aRequest);
        iWriterBuf.WriteFlush();
    }
    catch(WriterError&) {
        return code;
    }

    try {
        iReaderResponse.Read();

        code = iReaderResponse.Status().Code();
        if (code == HttpStatus::kOk.Code()) {
            // Content-Length currently returns 0 so read until ReaderError
            try {
                for (;;) {
                    Brn buf = iReaderUntil.Read(kMaxResponseChunkBytes);
                    if (buf.Bytes() == 0) {
                        // Reached end of data.
                        return code;
                    }
                    aResponseWriter.Write(buf);
                }
            }
            catch (ReaderError&) {
            }
            catch (WriterError&) {
            }
        }
    }
    catch(HttpError&) {
        return code;
    }
    catch(ReaderError&) {
        return code;
    }

    return code;
}

void UriRetriever::SetUriBase(const Uri& aUri)
{
    iUriBaseBuf.Replace(aUri.Scheme());
    iUriBaseBuf.Append("://");
    iUriBaseBuf.Append(aUri.Host());
    iUriBaseBuf.Append(":");
    Ascii::AppendDec(iUriBaseBuf, aUri.Port());
    iUriBaseBuf.Append("/");

    Parser p(aUri.Path());
    p.Next('/');                        // skip '/' at start
    iUriBaseBuf.Append(p.Next('/'));    // append resource prefix
    iUriBaseBuf.Append("/");
}


// WriterPrinter

WriterPrinter::WriterPrinter()
    : iBytesPrinted(0)
{
}

TUint WriterPrinter::BytesPrinted() const
{
    return iBytesPrinted;
}

void WriterPrinter::Reset()
{
    iBytesPrinted = 0;
}

void WriterPrinter::Write(TByte aValue)
{
    Log::Print("%c", aValue);
    iBytesPrinted += 1;
}

void WriterPrinter::Write(const Brx& aBuffer)
{
    Log::Print(aBuffer);
    iBytesPrinted += aBuffer.Bytes();
}

void WriterPrinter::WriteFlush()
{
    Log::Flush();
}


// SuiteConfigUi

// FIXME - take resource dir as param
SuiteConfigUi::SuiteConfigUi(CpStack& aCpStack, DvStack& aDvStack)
    : SuiteUnitTest("SuiteConfigUi")
    , iCpStack(aCpStack)
    , iDvStack(aDvStack)
{
    AddTest(MakeFunctor(*this, &SuiteConfigUi::TestGetStaticResource), "TestGetStaticResource");
    AddTest(MakeFunctor(*this, &SuiteConfigUi::TestLongPollCreate), "TestLongPollCreate");
    AddTest(MakeFunctor(*this, &SuiteConfigUi::TestLongPoll), "TestLongPoll");
}

void SuiteConfigUi::Setup()
{
    const TChar* suiteConfigUiStr = "SuiteConfigUi";
    Brn suiteConfigUiBuf("SuiteConfigUi");
    Brn friendlyName("SuiteConfigUi:SoftPlayer");
    Bwh friendlyNameBwh(friendlyName.Bytes()+1);    // +1 for '\0'
    friendlyNameBwh.Replace(friendlyName);
    Brn udn("SuiteConfigUi");

    // Force values for parameters that disable features (and ConfigVals) if left empty.
    Brn tuneInPartnerId("dummyTunein");
    Brn tidalId("dummyTidal");
    Brn qobuzIdSecret("dummyQobuz");
    Brn userAgent("dummyUA");

    iMediaPlayer = new Av::Test::TestMediaPlayer(iDvStack, udn, suiteConfigUiStr, "SoftPlayer", tuneInPartnerId, tidalId, qobuzIdSecret, userAgent);
    iAnimator = new Media::AnimatorBasic(iDvStack.Env(), iMediaPlayer->Pipeline());

    iMediaPlayerThread = new ThreadFunctor("TestConfigUi", MakeFunctor(*this, &SuiteConfigUi::Run));
    iMediaPlayerThread->Start();

    // TestMediaPlayer may not have been started by thread by time we try an MSEARCH
    //Thread::Sleep(5000);

    iDeviceListHandler = new HelperDeviceListHandler(friendlyName);
    FunctorCpDevice added = MakeFunctorCpDevice(*iDeviceListHandler, &HelperDeviceListHandler::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(*iDeviceListHandler, &HelperDeviceListHandler::Removed);

    Brn domainName;
    Brn type;
    TUint ver;
    if (Ssdp::ParseUrnService(Brn("av.openhome.org:service:Configuration:1"), domainName, type, ver)) {
        CpDeviceList* deviceList = new CpDeviceListUpnpServiceType(iCpStack, domainName, type, ver, added, removed);
        Blocker* blocker = new Blocker(iCpStack.Env());
        blocker->Wait(iCpStack.Env().InitParams()->MsearchTimeSecs());
        delete blocker;
        delete deviceList;
    }
}

void SuiteConfigUi::TearDown()
{
    // FIXME - currently an issue in Credentials service.
    // Key can take a while to be generated, which can then cause
    // CredentialsThread to be run after Credentials destructor has already
    // been called.
    Thread::Sleep(1000);

    iMediaPlayer->StopPipeline();
    delete iDeviceListHandler;
    delete iMediaPlayerThread;
    delete iMediaPlayer;
    delete iAnimator;
}

void SuiteConfigUi::Run()
{
    iMediaPlayer->RunWithSemaphore();
}

void SuiteConfigUi::TestGetStaticResource()
{
    const Brx& url = iDeviceListHandler->GetPresentationUrl();
    TEST(url.Bytes() > 0);
    Log::Print("SuiteConfigUi::TestGetStaticResource url: ");
    Log::Print(url);
    Log::Print("\n");

    const Uri uri(url);
    UriRetriever uriRetriever(iDvStack.Env(), uri);
    Bws<1024> responseBuffer;
    WriterBuffer writerBuf(responseBuffer);
    TUint code = uriRetriever.Retrieve(Brn("index.html"), Http::kMethodGet, Brx::Empty(), writerBuf);
    TEST (code == HttpStatus::kOk.Code());
    // Check document looks like:
    // <!DOCTYPE ...>
    // <html>
    // ...
    // </html>

    Parser p(responseBuffer);
    p.Next('!');    // skip "<!"
    Brn docType = p.Next();
    TEST(docType == Brn("DOCTYPE"));

    p.Next('<');    // skip remainder of DOCTYPE
    Brn htmlOpen = p.Next('>');
    TEST(htmlOpen == Brn("html"));

    Bws<100> tag;
    p.Next('<');    // find start of next tag
    while (!p.Finished()) {
        tag.Replace(p.Next('>'));   // get tag
        p.Next('<');                // find start of next tag
    }

    // "</html>" should be last tag in document.
    TEST(p.Finished());
    TEST(tag == Brn("/html"));
}

void SuiteConfigUi::TestLongPollCreate()
{
    static const Brn kExpectedSessionId("session-id: 1\r\n");
    const Brx& url = iDeviceListHandler->GetPresentationUrl();
    TEST(url.Bytes() > 0);
    const Uri uri(url);

    UriRetriever uriRetriever(iDvStack.Env(), uri);
    Bws<1024> responseBuffer;
    WriterBuffer writerBuf(responseBuffer);
    TUint code = uriRetriever.Retrieve(Brn("lpcreate"), Http::kMethodPost, Brx::Empty(), writerBuf);
    TEST(code == HttpStatus::kOk.Code());
    TEST(responseBuffer == kExpectedSessionId);


    // FIXME - if test ends without requesting /lpterminate, TestMediaPlayer crashes during
    // destruction (looks like it's related to deleting ConfigVals before all
    // observers have unsubscribed).
    WriterPrinter writerPrinter;
    code = uriRetriever.Retrieve(Brn("lpterminate"), Http::kMethodPost, kExpectedSessionId, writerPrinter);
    TEST(code == HttpStatus::kOk.Code());
}

void SuiteConfigUi::TestLongPoll()
{
    static const Brn kExpectedSessionId("session-id: 1\r\n");
    const Brx& url = iDeviceListHandler->GetPresentationUrl();
    TEST(url.Bytes() > 0);
    const Uri uri(url);

    UriRetriever uriRetriever(iDvStack.Env(), uri);
    Bws<1024> responseBuffer;
    WriterBuffer writerBuf(responseBuffer);
    TUint code = uriRetriever.Retrieve(Brn("lpcreate"), Http::kMethodPost, Brx::Empty(), writerBuf);
    TEST(code == HttpStatus::kOk.Code());
    TEST(responseBuffer == kExpectedSessionId);

    WriterPrinter writerPrinter;
    code = uriRetriever.Retrieve(Brn("lp"), Http::kMethodPost, kExpectedSessionId, writerPrinter);
    TEST(code == HttpStatus::kOk.Code());
    TEST(writerPrinter.BytesPrinted() > 0);
    writerPrinter.Reset();

    code = uriRetriever.Retrieve(Brn("lpterminate"), Http::kMethodPost, kExpectedSessionId, writerPrinter);
    TEST(code == HttpStatus::kOk.Code());
}



void TestConfigUi(CpStack& aCpStack, DvStack& aDvStack)
{
    Runner runner("Config UI tests\n");
    runner.Add(new SuiteConfigUi(aCpStack, aDvStack));
    runner.Run();
}
