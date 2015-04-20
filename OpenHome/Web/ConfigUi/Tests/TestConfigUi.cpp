#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Net/Private/XmlParser.h>
#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Media/Utils/DriverBasic.h>

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


// ConfigApps are not expected to check the existence of ConfigVals at startup.
// This means that the ConfigManager will assert when the config page is loaded
// if a ConfigVal included in the ConfigApp doesn't exist in the ConfigManager.

// This test exploits that behaviour to check if the ConfigApp is valid by
// loading the web page and initiating long-polling. If the ConfigManager
// doesn't assert, the ConfigVals in the ConfigApp are all valid.

class SuiteConfigUi : public OpenHome::TestFramework::SuiteUnitTest, public OpenHome::INonCopyable
{
private:
    static const TUint kMaxUiTabs = 4;
    static const TUint kUiSendQueueSize = 32;
    static const TUint kReadBufferBytes = 1024;
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 3000;
public:
    SuiteConfigUi(OpenHome::Net::CpStack& aCpStack, OpenHome::Net::DvStack& aDvStack);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void Run();
    void OpenSocket();
    void CloseSocket();
    TUint RetrieveUri(const OpenHome::Uri& aUri, const OpenHome::Brx& aMethod, const OpenHome::Brx& aDataRequest, OpenHome::Bwx& aDataResponse);
    TUint RetrieveUriSocketOpen(const OpenHome::Uri& aUri, const OpenHome::Brx& aMethod, const OpenHome::Brx& aDataRequest, OpenHome::Bwx& aDataResponse);
    void GetUriBase(const OpenHome::Uri& aUri, OpenHome::Bwx& aBufOut);
    void ConstructUri(const OpenHome::Brx& aBase, const OpenHome::Brx& aTail, OpenHome::Uri& aUriOut);
    void TestGetStaticResource();
    void TestLongPollCreate();
private:
    OpenHome::Net::CpStack& iCpStack;
    OpenHome::Net::DvStack& iDvStack;
    OpenHome::Media::DriverBasic* iDriver;
    OpenHome::Av::Test::TestMediaPlayer* iMediaPlayer;
    OpenHome::ThreadFunctor* iMediaPlayerThread;
    HelperDeviceListHandler* iDeviceListHandler;

    WebAppFramework* iAppFramework;
    ConfigAppMediaPlayer* iConfigApp;

    OpenHome::Srs<kReadBufferBytes>* iReaderBuf;
    OpenHome::ReaderUntil* iReaderUntil;
    OpenHome::Sws<kWriteBufferBytes>* iWriterBuf;
    OpenHome::Mutex* iLock;
    OpenHome::SocketTcpClient* iTcpClient;
    TBool iSocketIsOpen;

    OpenHome::WriterHttpRequest* iWriterRequest;
    OpenHome::ReaderHttpResponse* iReaderResponse;
    //OpenHome::ReaderHttpChunked* iDechunker;
    OpenHome::HttpHeaderContentType* iHeaderContentType;
    OpenHome::HttpHeaderContentLength* iHeaderContentLength;
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


// SuiteConfigUi

// FIXME - take resource dir as param
SuiteConfigUi::SuiteConfigUi(CpStack& aCpStack, DvStack& aDvStack)
    : SuiteUnitTest("SuiteConfigUi")
    , iCpStack(aCpStack)
    , iDvStack(aDvStack)
{
    AddTest(MakeFunctor(*this, &SuiteConfigUi::TestGetStaticResource), "TestGetStaticResource");
    AddTest(MakeFunctor(*this, &SuiteConfigUi::TestLongPollCreate), "TestLongPollCreate");
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
    iDriver = new Media::DriverBasic(iDvStack.Env(), iMediaPlayer->Pipeline());

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

    // TCP client setup.
    iLock = new Mutex ("SCOM");
    iTcpClient = new SocketTcpClient();
    iReaderBuf = new Srs<kReadBufferBytes>(*iTcpClient);
    iReaderUntil = new ReaderUntilS<kReadBufferBytes>(*iReaderBuf);
    iWriterBuf = new Sws<kWriteBufferBytes>(*iTcpClient);
    iSocketIsOpen = false;

    iHeaderContentType = new HttpHeaderContentType();
    iHeaderContentLength = new HttpHeaderContentLength();

    iWriterRequest = new WriterHttpRequest(*iWriterBuf);
    iReaderResponse = new ReaderHttpResponse(iDvStack.Env(), *iReaderUntil);

    iReaderResponse->AddHeader(*iHeaderContentType);
    iReaderResponse->AddHeader(*iHeaderContentLength);
}

void SuiteConfigUi::TearDown()
{
    delete iReaderResponse;
    delete iWriterRequest;
    delete iHeaderContentLength;
    delete iHeaderContentType;

    delete iLock;
    delete iWriterBuf;
    delete iReaderUntil;
    delete iReaderBuf;
    delete iTcpClient;

    iMediaPlayer->StopPipeline();
    delete iDeviceListHandler;
    delete iMediaPlayerThread;
    delete iMediaPlayer;
    delete iDriver;
}

void SuiteConfigUi::Run()
{
    iMediaPlayer->RunWithSemaphore();
}

TUint SuiteConfigUi::RetrieveUri(const Uri& aUri, const Brx& aMethod, const Brx& aDataRequest, Bwx& aDataResponse)
{
    iTcpClient->Open(iDvStack.Env());
    TUint code = RetrieveUriSocketOpen(aUri, aMethod, aDataRequest, aDataResponse);
    iTcpClient->Close();
    return code;
}

TUint SuiteConfigUi::RetrieveUriSocketOpen(const Uri& aUri, const Brx& aMethod, const Brx& aDataRequest, Bwx& aDataResponse)
{
    TUint code = 0;
    Endpoint ep(aUri.Port(), aUri.Host());

    try {
        iTcpClient->Connect(ep, kConnectTimeoutMs);
    }
    catch (NetworkTimeout&) {
        return code;
    }
    catch (NetworkError&) {
        return code;
    }

    try {
        iWriterRequest->WriteMethod(aMethod, aUri.PathAndQuery(), Http::eHttp11);
        const TUint port = (aUri.Port() == -1 ? 80 : (TUint)aUri.Port());
        Http::WriteHeaderHostAndPort(*iWriterRequest, aUri.Host(), port);
        Http::WriteHeaderContentLength(*iWriterRequest, aDataRequest.Bytes());
        Http::WriteHeaderConnectionClose(*iWriterRequest);
        iWriterRequest->WriteFlush();
        iWriterBuf->Write(aDataRequest);
        iWriterBuf->WriteFlush();
    }
    catch(WriterError&) {
        return code;
    }

    try {
        iReaderResponse->Read();

        code = iReaderResponse->Status().Code();
        //const TUint totalBytes = iHeaderContentLength->ContentLength();
        //totalBytes;

        if (code == HttpStatus::kOk.Code()) {
            // Content-Length currently returns 0 so read until ReaderError
            aDataResponse.SetBytes(0);
            try {
                for (;;) {
                    Brn buf = iReaderUntil->Read(aDataResponse.MaxBytes() - aDataResponse.Bytes());
                    aDataResponse.Append(buf);
                }
            }
            catch (ReaderError&) {
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

void SuiteConfigUi::GetUriBase(const Uri& aUri, Bwx& aBufOut)
{
    aBufOut.Replace(aUri.Scheme());
    aBufOut.Append("://");
    aBufOut.Append(aUri.Host());
    aBufOut.Append(":");
    Ascii::AppendDec(aBufOut, aUri.Port());
    aBufOut.Append("/");

    Parser p(aUri.Path());
    p.Next('/');                    // skip '/' at start
    aBufOut.Append(p.Next('/'));    // append resource prefix
    aBufOut.Append("/");
}

void SuiteConfigUi::ConstructUri(const Brx& aBase, const Brx& aTail, Uri& aUriOut)
{
    Bws<Uri::kMaxUriBytes> uri;
    uri.Append(aBase);
    uri.Append(aTail);
    aUriOut.Replace(uri);
}

void SuiteConfigUi::TestGetStaticResource()
{
    const Brx& url = iDeviceListHandler->GetPresentationUrl();
    TEST(url.Bytes() > 0);
    Log::Print("SuiteConfigUi::TestGetStaticResource url: ");
    Log::Print(url);
    Log::Print("\n");

    const Uri uri(url);
    Bws<kReadBufferBytes> data;
    TUint code = RetrieveUri(uri, Http::kMethodGet, Brx::Empty(), data);
    TEST (code == HttpStatus::kOk.Code());
    // Check document looks like:
    // <!DOCTYPE ...>
    // <html>
    // ...
    // </html>

    Parser p(data);
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
    const Brx& url = iDeviceListHandler->GetPresentationUrl();
    TEST(url.Bytes() > 0);
    const Uri uri(url);

    Bws<Uri::kMaxUriBytes> uriBase;
    GetUriBase(uri, uriBase);
    Uri uriLpCreate;
    ConstructUri(uriBase, Brn("lpcreate"), uriLpCreate);
    Log::Print("SuiteConfigUi::TestLongPollCreate uriLpCreate: ");
    Log::Print(uriLpCreate.AbsoluteUri());
    Log::Print("\n");

    Bws<kReadBufferBytes> data;
    TUint code = RetrieveUri(uriLpCreate, Http::kMethodPost, Brx::Empty(), data);
    TEST (code == HttpStatus::kOk.Code());

    Log::Print("data: ");
    Log::Print(data);
    Log::Print("\n");

    const TUint kExpectedSessionId = 1;
    Bws<20> expectedSessionBuf("session-id: ");
    Ascii::AppendDec(expectedSessionBuf, kExpectedSessionId);
    TEST(data == expectedSessionBuf);


    // FIXME - if test ends without requesting /lpterminate, TestMediaPlayer crashes during
    // destruction (looks like it's related to deleting ConfigVals before all
    // observers have unsubscribed).

    Uri uriLpTerminate;
    ConstructUri(uriBase, Brn("lpterminate"), uriLpTerminate);
    Log::Print("SuiteConfigUi::TestLongPollCreate uriLpTerminate: ");
    Log::Print(uriLpTerminate.AbsoluteUri());
    Log::Print("\n");

    Brn kSessionId("session-id: 1");
    code = RetrieveUri(uriLpTerminate, Http::kMethodPost, kSessionId, data);
    TEST (code == HttpStatus::kOk.Code());
}



void TestConfigUi(CpStack& aCpStack, DvStack& aDvStack)
{
    Runner runner("Config UI tests\n");
    runner.Add(new SuiteConfigUi(aCpStack, aDvStack));
    runner.Run();
}
