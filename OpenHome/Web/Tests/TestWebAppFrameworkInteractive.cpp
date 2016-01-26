#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Tests/Cdecl.h>
#include <OpenHome/Media/Tests/GetCh.h>
#include <OpenHome/Web/WebAppFramework.h>
#include <OpenHome/Web/ConfigUi/FileResourceHandler.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Configuration/ProviderConfig.h>
#include <OpenHome/Configuration/Tests/ConfigRamStore.h>

#include <stdlib.h>

namespace OpenHome {
namespace Web {
namespace Test {

class ITestTabMessageAllocator
{
public:
    virtual ITabMessage& Allocate(const OpenHome::Brx& aMessage) = 0;
    virtual ~ITestTabMessageAllocator() {}
};

class TestTabMessage;

class ITestTabMessageDeallocator
{
public:
    virtual void Free(TestTabMessage& aMessage) = 0;
    virtual ~ITestTabMessageDeallocator() {}
};

class TestTabMessageAllocator : public ITestTabMessageAllocator, public ITestTabMessageDeallocator
{
public:
    TestTabMessageAllocator(TUint aMaxMessages, TUint aMaxMessageBytes);
    ~TestTabMessageAllocator();
private: // from ITestTabMessageAllocator
    ITabMessage& Allocate(const OpenHome::Brx& aMessage);
private: // from ITestTabMessageDeallocator
    void Free(TestTabMessage& aMessage);
private:
    OpenHome::Fifo<TestTabMessage*> iFifo;
    OpenHome::Mutex iLock;
};

class TestTabMessage : public ITabMessage
{
public:
    TestTabMessage(ITestTabMessageDeallocator& aDeallocator, TUint aMaxBytes);
    void Set(const OpenHome::Brx& aMessage);
public: // from ITabMessage
    void Send(OpenHome::IWriter& aWriter);
    void Destroy();
private:
    ITestTabMessageDeallocator& iDeallocator;
    OpenHome::Bwh iBuf;
};

class TestTab : public ITab
{
public:
    TestTab(TUint aId, ITestTabMessageAllocator& aAllocator);
    TBool Allocated();
    void Allocate(ITabHandler& aHandler);
private: // from ITab
    void Receive(const OpenHome::Brx& aMessage);
    void Destroy();
private:
    const TUint iId;
    ITestTabMessageAllocator& iMsgAllocator;
    ITabHandler* iHandler;
    OpenHome::Mutex iLock;
};

class TestHttpApp : public IWebApp
{
public:
    static const TUint kMaxMessages = 128;
    static const TUint kMaxMessageBytes = 512;
    //static const TUint kPort = 55178;
    //static const TUint kMaxSessions = 4;
    //static const TUint kBufferBytes = 1024;
private:
    static const OpenHome::Brn kResourcePrefix;
public:
    TestHttpApp(TUint aMaxSessions, const OpenHome::Brx& aResourceDir);
    ~TestHttpApp();
public: // from IWebApp
    ITab& Create(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList);
    const OpenHome::Brx& ResourcePrefix() const;
    IResourceHandler& CreateResourceHandler(const OpenHome::Brx& aResource);
private:
    TestTabMessageAllocator iMsgAllocator;
    std::vector<TestTab*> iTabs;
    std::vector<FileResourceHandler*> iResourceHandlers;
    OpenHome::Mutex iLock;
};

class TestPresentationUrlHandler
{
public:
    void PresentationUrlChanged(const Brx& aUrl);
};

} // namespace Test
} // namespace Web
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Web;
using namespace OpenHome::Web::Test;


// TestTabMessageAllocator

TestTabMessageAllocator::TestTabMessageAllocator(TUint aMaxMessages, TUint aMaxMessageBytes)
    : iFifo(aMaxMessages)
    , iLock("TMAL")
{
    AutoMutex a(iLock);
    while (iFifo.SlotsFree() > 0) {
        iFifo.Write(new TestTabMessage(*this, aMaxMessageBytes));
    }
}

TestTabMessageAllocator::~TestTabMessageAllocator()
{
    AutoMutex a(iLock);
    ASSERT(iFifo.SlotsFree() == 0); // All messages must have been returned via Free()
    while (iFifo.SlotsUsed() > 0) {
        TestTabMessage* msg = iFifo.Read();
        delete msg;
    }
}

ITabMessage& TestTabMessageAllocator::Allocate(const OpenHome::Brx& aMessage)
{
    AutoMutex a(iLock);
    TestTabMessage& msg = *iFifo.Read();
    msg.Set(aMessage);
    return msg;
}

void TestTabMessageAllocator::Free(TestTabMessage& aMessage)
{
    AutoMutex a(iLock);
    iFifo.Write(&aMessage);
}


// TestTabMessage

TestTabMessage::TestTabMessage(ITestTabMessageDeallocator& aDeallocator, TUint aMaxBytes)
    : iDeallocator(aDeallocator)
    , iBuf(aMaxBytes)
{
}

void TestTabMessage::Set(const OpenHome::Brx& aMessage)
{
    iBuf.Replace(aMessage);
}

void TestTabMessage::Send(OpenHome::IWriter& aWriter)
{
    aWriter.Write(iBuf);
}

void TestTabMessage::Destroy()
{
    iBuf.SetBytes(0);
    iDeallocator.Free(*this);
}


// TestTab

TestTab::TestTab(TUint aId, ITestTabMessageAllocator& aAllocator)
    : iId(aId)
    , iMsgAllocator(aAllocator)
    , iHandler(nullptr)
    , iLock("TTBL")
{
}

TBool TestTab::Allocated()
{
    AutoMutex a(iLock);
    return (iHandler != nullptr);
}

void TestTab::Allocate(ITabHandler& aHandler)
{
    Log::Print("TestTab::Allocate iId: %u\n", iId);
    AutoMutex a(iLock);
    ASSERT(iHandler == nullptr);
    iHandler = &aHandler;
}

void TestTab::Receive(const Brx& aMessage)
{
    Log::Print("TestTab::Receive iId: %u\n", iId);
    // Echo message back.
    ITabMessage& msg = iMsgAllocator.Allocate(aMessage);
    iHandler->Send(msg);
}

void TestTab::Destroy()
{
    Log::Print("TestTab::Destroy iId: %u\n", iId);
    AutoMutex a(iLock);
    ASSERT(iHandler != nullptr);
    iHandler = nullptr;
}


// TestHttpApp

const Brn TestHttpApp::kResourcePrefix("TestHttpApp");

TestHttpApp::TestHttpApp(TUint aMaxSessions, const OpenHome::Brx& aResourceDir)
    : iMsgAllocator(kMaxMessages, kMaxMessageBytes)
    , iLock("THAL")
{
    for (TUint i=0; i<aMaxSessions; i++) {
        iTabs.push_back(new TestTab(i, iMsgAllocator));
        iResourceHandlers.push_back(new FileResourceHandler(aResourceDir));
    }
}

TestHttpApp::~TestHttpApp()
{
    AutoMutex a(iLock);
    for (TUint i=0; i<iTabs.size(); i++) {
        delete iTabs[i];
        delete iResourceHandlers[i];
    }
}

ITab& TestHttpApp::Create(ITabHandler& aHandler, const std::vector<Bws<10>>& /*aLanguageList*/)
{
    AutoMutex a(iLock);
    for (TUint i=0; i<iTabs.size(); i++) {
        if (!iTabs[i]->Allocated()) {
            TestTab& tab = *iTabs[i];
            tab.Allocate(aHandler);
            return tab;
        }
    }
    ASSERTS(); // FIXME - throw exception instead?
    return *iTabs[0];   // won't be reached
}

const Brx& TestHttpApp::ResourcePrefix() const
{
    return kResourcePrefix;
}

IResourceHandler& TestHttpApp::CreateResourceHandler(const Brx& aResource)
{
    AutoMutex a(iLock);
    for (TUint i=0; i<iResourceHandlers.size(); i++) {
        if (!iResourceHandlers[i]->Allocated()) {
            FileResourceHandler& handler = *iResourceHandlers[i];
            handler.SetResource(aResource);
            return handler;
        }
    }
    ASSERTS();  // FIXME - throw exception instead?
    return *iResourceHandlers[0];   // won't be reached
}


// TestPresentationUrlHandler

void TestPresentationUrlHandler::PresentationUrlChanged(const Brx& aUrl)
{
    Log::Print("Presentation URL changed: ");
    Log::Print(aUrl);
    Log::Print("\n");
}




int CDECL main(int aArgc, char* aArgv[])
{
#ifdef _WIN32
    char* noErrDlgs = getenv("NO_ERROR_DIALOGS");
    if (noErrDlgs != nullptr && strcmp(noErrDlgs, "1") == 0) {
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    }
#endif // _WIN32

    // Parse command line args.
    OptionParser parser;
    OptionString optionDir("-d", "--root-dir", Brn("../OpenHome/Web/Tests/res/"), "Root directory for serving static files");
    parser.AddOption(&optionDir);

    if (!parser.Parse(aArgc, aArgv)) {
        return 1;
    }

    // Initialise ohNet.
    InitialisationParams* initParams = InitialisationParams::Create();
    //initParams->SetUseLoopbackNetworkAdapter();
    Library* lib = new Library(initParams);
    DvStack* dvStack = lib->StartDv();
    Environment& env = dvStack->Env();

    // Set up the server.
    Debug::SetLevel(Debug::kHttp);
    static const TIpAddress addr = 0;    // bind to all interfaces
    static const TUint port = 0;         // bind to OS-assigned port
    static const TUint maxSessions = 4;
    static const TUint bufferBytes = 1024;

    WebAppFramework* server = new WebAppFramework(env, addr, port, maxSessions, bufferBytes);

    TestHttpApp* app = new TestHttpApp(maxSessions, optionDir.Value());  // read files from posix-style filesystem

    TestPresentationUrlHandler* urlHandler = new TestPresentationUrlHandler();
    server->Add(app, MakeFunctorGeneric(*urlHandler, &TestPresentationUrlHandler::PresentationUrlChanged));   // takes ownership
    server->Start();

    Log::Print("\nTest Http server for Web UI\n");
    Log::Print("Root dir for static resources: ");
    Log::Print(optionDir.Value());
    Log::Print("\n");

    Log::Print("Press <q> followed by <enter> to quit:\n");
    Log::Print("\n");
    while (getchar() != 'q') {
        ;
    }

    // Shutdown.
    delete server;
    delete lib;
    delete urlHandler;

    return 0;
}
