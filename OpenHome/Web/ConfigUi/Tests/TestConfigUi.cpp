#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Net/Private/XmlParser.h>
#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Media/Utils/AnimatorBasic.h>

#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Configuration/Tests/ConfigRamStore.h>
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

class HelperWriterPrinter : public IWriter
{
public:
    HelperWriterPrinter();
    TUint BytesPrinted() const;
    void Reset();
public: // from IWriter
    void Write(TByte aValue) override;
    void Write(const Brx& aBuffer) override;
    void WriteFlush() override;
private:
    TUint iBytesPrinted;
};

class SuiteConfigMessageAllocator : public TestFramework::SuiteUnitTest
{
public:
    SuiteConfigMessageAllocator();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void TestExhaustMessageQueue();
};

class SuiteConfigMessageNum : public TestFramework::SuiteUnitTest
{
private:
    static const TUint kMaxMsgBytes = 1024;
public:
    SuiteConfigMessageNum();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void TestSend();
    void TestSendEscapedChars();
    void TestSendAdditional();
private:
    Configuration::ConfigRamStore* iStore;
    Configuration::ConfigManager* iConfigManager;
    ConfigMessageNumAllocator* iMessageAllocator;
};

class SuiteConfigMessageChoice : public TestFramework::SuiteUnitTest
{
private:
    static const TUint kMaxMsgBytes = 1024;
public:
    SuiteConfigMessageChoice();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void TestSend();
    void TestSendEscapedChars();
    void TestSendAdditional();
private:
    class ILanguageResourceReaderDestroyer
    {
    public:
        virtual void Destroy(ILanguageResourceReader* aResourceReader) = 0;
        virtual ~ILanguageResourceReaderDestroyer() {}
    };
    class LanguageResourceReader : public ILanguageResourceReader, private INonCopyable
    {
    public:
        LanguageResourceReader(const Brx& aLanguageMap, ILanguageResourceReaderDestroyer& aDestroyer);
    public: // from ILanguageResourceReader
        Brn ReadLine() override;
        void Destroy() override;
    private:
        const Brx& iLanguageMap;
        ILanguageResourceReaderDestroyer& iDestroyer;
        Parser iParser;
    };
    class LanguageResourceManager : public ILanguageResourceManager, public ILanguageResourceReaderDestroyer, private INonCopyable
    {
    public:
        LanguageResourceManager(const Brx& aLanguageMap);
    public: // from ILanguageResourceManager
        ILanguageResourceReader& CreateLanguageResourceHandler(const Brx& aResourceUriTail, std::vector<const Brx*>& aLanguageList) override;
    private: // from ILanguageResourceReaderDestroyer
        void Destroy(ILanguageResourceReader* aResourceReader) override;
    private:
        const Brx& iLanguageMap;
    };
private:
    Configuration::ConfigRamStore* iStore;
    Configuration::ConfigManager* iConfigManager;
    ConfigMessageChoiceAllocator* iMessageAllocator;
    Bws<1024> iLanguageMap;
    LanguageResourceManager* iResourceManager;
};

class SuiteConfigMessageText : public TestFramework::SuiteUnitTest
{
private:
    static const TUint kMaxMsgBytes = 1024;
public:
    SuiteConfigMessageText();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void TestSend();
    void TestSendEscapedChars();
    void TestSendAdditional();
private:
    Configuration::ConfigRamStore* iStore;
    Configuration::ConfigManager* iConfigManager;
    ConfigMessageTextAllocator* iMessageAllocator;
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

class SuiteConfigUi : public TestFramework::SuiteUnitTest, private INonCopyable
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
using namespace OpenHome::Configuration;
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


// HelperWriterPrinter

HelperWriterPrinter::HelperWriterPrinter()
    : iBytesPrinted(0)
{
}

TUint HelperWriterPrinter::BytesPrinted() const
{
    return iBytesPrinted;
}

void HelperWriterPrinter::Reset()
{
    iBytesPrinted = 0;
}

void HelperWriterPrinter::Write(TByte aValue)
{
    Log::Print("%c", aValue);
    iBytesPrinted += 1;
}

void HelperWriterPrinter::Write(const Brx& aBuffer)
{
    Log::Print(aBuffer);
    iBytesPrinted += aBuffer.Bytes();
}

void HelperWriterPrinter::WriteFlush()
{
    Log::Flush();
}


// SuiteConfigMessageNum

SuiteConfigMessageNum::SuiteConfigMessageNum()
    : SuiteUnitTest("SuiteConfigMessageNum")
{
    AddTest(MakeFunctor(*this, &SuiteConfigMessageNum::TestSend), "TestSend");
    AddTest(MakeFunctor(*this, &SuiteConfigMessageNum::TestSendEscapedChars), "TestSendEscapedChars");
    AddTest(MakeFunctor(*this, &SuiteConfigMessageNum::TestSendAdditional), "TestSendAdditional");
}

void SuiteConfigMessageNum::Setup()
{
    iStore = new Configuration::ConfigRamStore();
    iConfigManager = new ConfigManager(*iStore);
    iMessageAllocator = new ConfigMessageNumAllocator(1);
}

void SuiteConfigMessageNum::TearDown()
{
    delete iMessageAllocator;
    delete iConfigManager;
    delete iStore;
}

void SuiteConfigMessageNum::TestSend()
{
    static const TUint value = 1;
    ConfigNum configNum(*iConfigManager, Brn("Config.Num.Key"), 0, 10, value);
    IConfigMessage& msg = iMessageAllocator->Allocate(configNum, value, Brx::Empty());
    Bws<kMaxMsgBytes> buf;
    WriterBuffer writerBuffer(buf);
    msg.Send(writerBuffer);

    Bws<kMaxMsgBytes> expectedBuf("{"
        "\"key\":\"Config.Num.Key\","
        "\"value\":1,"
        "\"type\":\"numeric\","
        "\"meta\":{\"min\":0,\"max\":10}}");
    TEST(buf == expectedBuf);
    msg.Destroy();
}

void SuiteConfigMessageNum::TestSendEscapedChars()
{
    // Try sending text that should be escaped.
    static const TUint value = 1;
    ConfigNum configNum(*iConfigManager, Brn("\nConfig.\rNum.\tKey"), 0, 10, value);
    IConfigMessage& msg = iMessageAllocator->Allocate(configNum, value, Brx::Empty());
    Bws<kMaxMsgBytes> buf;
    WriterBuffer writerBuffer(buf);
    msg.Send(writerBuffer);

    Bws<kMaxMsgBytes> expectedBuf("{"
        "\"key\":\"\\nConfig.\\rNum.\\tKey\","
        "\"value\":1,"
        "\"type\":\"numeric\","
        "\"meta\":{\"min\":0,\"max\":10}}");
    TEST(buf == expectedBuf);
    msg.Destroy();
}

void SuiteConfigMessageNum::TestSendAdditional()
{
    static const TUint value = 1;
    ConfigNum configNum(*iConfigManager, Brn("Config.Num.Key"), 0, 10, value);
    Brn additionalJson("\"additional\": {\"additionalKey\": 1}");
    IConfigMessage& msg = iMessageAllocator->Allocate(configNum, value, additionalJson);
    Bws<kMaxMsgBytes> buf;
    WriterBuffer writerBuffer(buf);
    msg.Send(writerBuffer);

    Bws<kMaxMsgBytes> expectedBuf("{"
        "\"key\":\"Config.Num.Key\","
        "\"value\":1,"
        "\"type\":\"numeric\","
        "\"meta\":{\"min\":0,\"max\":10},"
        "\"additional\": {\"additionalKey\": 1}}");
    TEST(buf == expectedBuf);
    msg.Destroy();
}


// SuiteConfigMessageChoice::LanguageResourceReader

SuiteConfigMessageChoice::LanguageResourceReader::LanguageResourceReader(const Brx& aLanguageMap, ILanguageResourceReaderDestroyer& aDestroyer)
    : iLanguageMap(aLanguageMap)
    , iDestroyer(aDestroyer)
    , iParser(iLanguageMap)
{
}

// FIXME - what if parse is exhausted?
Brn SuiteConfigMessageChoice::LanguageResourceReader::ReadLine()
{
    //return Ascii::Trim(iParser.Next('\n')); // FIXME - if Trim() is done, may strip any escaped chars in key.
    return iParser.Next('\n');
}

void SuiteConfigMessageChoice::LanguageResourceReader::Destroy()
{
    iDestroyer.Destroy(this);
}


// SuiteConfigMessageChoice::LanguageResourceManager

SuiteConfigMessageChoice::LanguageResourceManager::LanguageResourceManager(const Brx& aLanguageMap)
    : iLanguageMap(aLanguageMap)
{
}

ILanguageResourceReader& SuiteConfigMessageChoice::LanguageResourceManager::CreateLanguageResourceHandler(const Brx& /*aResourceUriTail*/, std::vector<const Brx*>& /*aLanguageList*/)
{
    SuiteConfigMessageChoice::LanguageResourceReader* reader = new SuiteConfigMessageChoice::LanguageResourceReader(iLanguageMap, *this);
    return *reader;
}

void SuiteConfigMessageChoice::LanguageResourceManager::Destroy(ILanguageResourceReader* aResourceReader)
{
    delete aResourceReader;
}


// SuiteConfigMessageChoice

SuiteConfigMessageChoice::SuiteConfigMessageChoice()
    : SuiteUnitTest("SuiteConfigMessageChoice")
{
    AddTest(MakeFunctor(*this, &SuiteConfigMessageChoice::TestSend), "TestSend");
    AddTest(MakeFunctor(*this, &SuiteConfigMessageChoice::TestSendEscapedChars), "TestSendEscapedChars");
    AddTest(MakeFunctor(*this, &SuiteConfigMessageChoice::TestSendAdditional), "TestSendAdditional");
}

void SuiteConfigMessageChoice::Setup()
{
    iStore = new Configuration::ConfigRamStore();
    iConfigManager = new ConfigManager(*iStore);
    iLanguageMap.Replace("Config.Choice.Key\r\n0 False\r\n1 True\r\n"
                         "\r\n"
                         "Config.\rChoice.\tKey\r\n0 Fal\tse\r\n1 Tr\fue\r\n");
    iResourceManager = new LanguageResourceManager(iLanguageMap);
    iMessageAllocator = new ConfigMessageChoiceAllocator(1, *iResourceManager);
}

void SuiteConfigMessageChoice::TearDown()
{
    delete iMessageAllocator;
    delete iResourceManager;
    iLanguageMap.SetBytes(0);
    delete iConfigManager;
    delete iStore;
}

void SuiteConfigMessageChoice::TestSend()
{
    static const TUint value = 0;
    std::vector<TUint> options;
    options.push_back(0);
    options.push_back(1);
    std::vector<const Brx*> languages;
    ConfigChoice configChoice(*iConfigManager, Brn("Config.Choice.Key"), options, value);
    IConfigMessage& msg = iMessageAllocator->Allocate(configChoice, value, Brx::Empty(), languages);
    Bws<kMaxMsgBytes> buf;
    WriterBuffer writerBuffer(buf);
    msg.Send(writerBuffer);

    Bws<kMaxMsgBytes> expectedBuf("{"
        "\"key\":\"Config.Choice.Key\","
        "\"value\":0,"
        "\"type\":\"choice\","
        "\"meta\":{"
            "\"options\":["
                "{\"id\": 0,\"value\": \"False\"},"
                "{\"id\": 1,\"value\": \"True\"}"
            "]"
        "}}");
    TEST(buf == expectedBuf);
    msg.Destroy();
}

void SuiteConfigMessageChoice::TestSendEscapedChars()
{
    // Try sending text that should be escaped.
    static const TUint value = 0;
    std::vector<TUint> options;
    options.push_back(0);
    options.push_back(1);
    std::vector<const Brx*> languages;

    // FIXME - can't have \n in ConfigChoice keys, as language resource parser relies on \n as a separator!
    // Nor can have whitespace chars at start/end of keys, as Parser will strip these!
    //ConfigChoice configChoice(*iConfigManager, Brn("\nConfig.\rChoice.\tKey"), options, value);

    ConfigChoice configChoice(*iConfigManager, Brn("Config.\rChoice.\tKey"), options, value);
    IConfigMessage& msg = iMessageAllocator->Allocate(configChoice, value, Brx::Empty(), languages);
    Bws<kMaxMsgBytes> buf;
    WriterBuffer writerBuffer(buf);
    msg.Send(writerBuffer);

    Bws<kMaxMsgBytes> expectedBuf("{"
        "\"key\":\"Config.\\rChoice.\\tKey\","
        "\"value\":0,"
        "\"type\":\"choice\","
        "\"meta\":{"
            "\"options\":["
                "{\"id\": 0,\"value\": \"Fal\\tse\"},"
                "{\"id\": 1,\"value\": \"Tr\\fue\"}"
            "]"
        "}}");
    TEST(buf == expectedBuf);
    msg.Destroy();
}

void SuiteConfigMessageChoice::TestSendAdditional()
{
    static const TUint value = 0;
    std::vector<TUint> options;
    options.push_back(0);
    options.push_back(1);
    std::vector<const Brx*> languages;
    ConfigChoice configChoice(*iConfigManager, Brn("Config.Choice.Key"), options, value);
    Brn additionalJson("\"additional\": {\"additionalKey\": 1}");
    IConfigMessage& msg = iMessageAllocator->Allocate(configChoice, value, additionalJson, languages);
    Bws<kMaxMsgBytes> buf;
    WriterBuffer writerBuffer(buf);
    msg.Send(writerBuffer);

    Bws<kMaxMsgBytes> expectedBuf("{"
        "\"key\":\"Config.Choice.Key\","
        "\"value\":0,"
        "\"type\":\"choice\","
        "\"meta\":{"
            "\"options\":["
                "{\"id\": 0,\"value\": \"False\"},"
                "{\"id\": 1,\"value\": \"True\"}"
            "]"
        "},"
        "\"additional\": {\"additionalKey\": 1}}");
    TEST(buf == expectedBuf);
    msg.Destroy();
}


// SuiteConfigMessageText

SuiteConfigMessageText::SuiteConfigMessageText()
    : SuiteUnitTest("SuiteConfigMessageText")
{
    AddTest(MakeFunctor(*this, &SuiteConfigMessageText::TestSend), "TestSend");
    AddTest(MakeFunctor(*this, &SuiteConfigMessageText::TestSendEscapedChars), "TestSendEscapedChars");
    AddTest(MakeFunctor(*this, &SuiteConfigMessageText::TestSendAdditional), "TestSendAdditional");
}

void SuiteConfigMessageText::Setup()
{
    iStore = new Configuration::ConfigRamStore();
    iConfigManager = new ConfigManager(*iStore);
    iMessageAllocator = new ConfigMessageTextAllocator(1);
}

void SuiteConfigMessageText::TearDown()
{
    delete iMessageAllocator;
    delete iConfigManager;
    delete iStore;
}

void SuiteConfigMessageText::TestSend()
{
    static const Brn value("abc");
    ConfigText configText(*iConfigManager, Brn("Config.Text.Key"), 25, value);
    IConfigMessage& msg = iMessageAllocator->Allocate(configText, value, Brx::Empty());
    Bws<kMaxMsgBytes> buf;
    WriterBuffer writerBuffer(buf);
    msg.Send(writerBuffer);

    Bws<kMaxMsgBytes> expectedBuf("{"
        "\"key\":\"Config.Text.Key\","
        "\"value\":\"abc\","
        "\"type\":\"text\","
        "\"meta\":{\"maxlength\":25}}");
    TEST(buf == expectedBuf);
    msg.Destroy();
}

void SuiteConfigMessageText::TestSendEscapedChars()
{
    // Try sending text that should be escaped.
    static const Brn value("a\rb\bc");
    ConfigText configText(*iConfigManager, Brn("\nConfig.\rText.\tKey"), 25, value);
    IConfigMessage& msg = iMessageAllocator->Allocate(configText, value, Brx::Empty());
    Bws<kMaxMsgBytes> buf;
    WriterBuffer writerBuffer(buf);
    msg.Send(writerBuffer);

    Bws<kMaxMsgBytes> expectedBuf("{"
        "\"key\":\"\\nConfig.\\rText.\\tKey\","
        "\"value\":\"a\\rb\\bc\","
        "\"type\":\"text\","
        "\"meta\":{\"maxlength\":25}}");
    TEST(buf == expectedBuf);
    msg.Destroy();
}

void SuiteConfigMessageText::TestSendAdditional()
{
    static const Brn value("abc");
    ConfigText configText(*iConfigManager, Brn("Config.Text.Key"), 25, value);
    Brn additionalJson("\"additional\": {\"additionalKey\": 1}");
    IConfigMessage& msg = iMessageAllocator->Allocate(configText, value, additionalJson);
    Bws<kMaxMsgBytes> buf;
    WriterBuffer writerBuffer(buf);
    msg.Send(writerBuffer);

    Bws<kMaxMsgBytes> expectedBuf("{"
        "\"key\":\"Config.Text.Key\","
        "\"value\":\"abc\","
        "\"type\":\"text\","
        "\"meta\":{\"maxlength\":25},"
        "\"additional\": {\"additionalKey\": 1}}");
    TEST(buf == expectedBuf);
    msg.Destroy();
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
    HelperWriterPrinter writerPrinter;
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

    HelperWriterPrinter writerPrinter;
    code = uriRetriever.Retrieve(Brn("lp"), Http::kMethodPost, kExpectedSessionId, writerPrinter);
    TEST(code == HttpStatus::kOk.Code());
    TEST(writerPrinter.BytesPrinted() > 0);
    writerPrinter.Reset();

    code = uriRetriever.Retrieve(Brn("lpterminate"), Http::kMethodPost, kExpectedSessionId, writerPrinter);
    TEST(code == HttpStatus::kOk.Code());
}



void TestConfigUi(CpStack& /*aCpStack*/, DvStack& /*aDvStack*/)
{
    Runner runner("Config UI tests\n");
    runner.Add(new SuiteConfigMessageNum());
    runner.Add(new SuiteConfigMessageChoice());
    runner.Add(new SuiteConfigMessageText());
    //runner.Add(new SuiteConfigUi(aCpStack, aDvStack));
    runner.Run();
}
