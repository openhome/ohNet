#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Cpp/CpDeviceUpnp.h>
#include <OpenHome/Net/Cpp/FunctorCpDevice.h>
#include <OpenHome/Net/Cpp/CpOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Private/Env.h>

#include <stdlib.h>
#include <vector>
#include <sys/stat.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class PerformanceTests
{
public:
    PerformanceTests(uint32_t aTimeoutSecs);
    ~PerformanceTests();
    void RunTests();
private:
    void TestActions();
    void TestSubscriptions();
    bool IncrementCount();
    void TimerExpired();
    void Added(CpDeviceCpp& aDevice);
    void Removed(CpDeviceCpp& aDevice);
    void ActionThread();
    void Subscribed();
private:
    Mutex iLock;
    Semaphore iSem;
    uint32_t iTimeoutSecs;
    Timer* iTimer;
    CpDeviceListCpp* iDeviceList;
    CpDeviceCpp* iDevice;
    uint32_t iCount;
    uint32_t iTestStopTime;
};


PerformanceTests::PerformanceTests(uint32_t aTimeoutSecs)
    : iLock("PFTM")
    , iSem("PFTS", 0)
    , iTimeoutSecs(aTimeoutSecs)
    , iDeviceList(NULL)
    , iDevice(NULL)
{
    iTimer = new Timer(*gEnv, MakeFunctor(*this, &PerformanceTests::TimerExpired), "TestPerformanceCp");
}

PerformanceTests::~PerformanceTests()
{
    if (iDevice != NULL) {
        iDevice->RemoveRef();
    }
    delete iDeviceList;
}

void PerformanceTests::RunTests()
{
    std::string domain("openhome.org");
    std::string service("TestBasic");
    iDeviceList = new CpDeviceListCppUpnpServiceType(domain, service, 1, 
                                                     MakeFunctorCpDeviceCpp(*this, &PerformanceTests::Added),
                                                     MakeFunctorCpDeviceCpp(*this, &PerformanceTests::Removed));
    iSem.Wait();
    Print("\n");
    TestActions();
    TestSubscriptions();
}

void PerformanceTests::TestActions()
{
    ThreadFunctor* threads[4] = { NULL, NULL, NULL, NULL };
    uint32_t threadsCount[3] = { 1, 2, 4 };
    for (uint32_t i=0; i<sizeof(threadsCount)/sizeof(threadsCount[0]); i++) {
        uint32_t numThreads = threadsCount[i];
        iCount = 0;
        for (uint32_t j=0; j<numThreads; j++) {
            threads[j] = new ThreadFunctor("", MakeFunctor(*this, &PerformanceTests::ActionThread));
        }
        iTestStopTime = Os::TimeInMs(gEnv->OsCtx()) + (iTimeoutSecs * 1000);
        for (uint32_t j=0; j<numThreads; j++) {
            threads[j]->Start();
        }
        iTimer->FireIn(iTimeoutSecs * 1000);
        iSem.Wait();
        for (uint32_t j=0; j<numThreads; j++) {
            delete threads[j];
            threads[j] = NULL;
        }
        Print("Invoked %u actions in %us using %u threads\n", iCount, iTimeoutSecs, numThreads);
    }
}

void PerformanceTests::TestSubscriptions()
{
    iCount = 0;
    Functor subscribed = MakeFunctor(*this, &PerformanceTests::Subscribed);
    iTestStopTime = Os::TimeInMs(gEnv->OsCtx()) + (iTimeoutSecs * 1000);
    do {
        CpProxyOpenhomeOrgTestBasic1Cpp* proxy = new CpProxyOpenhomeOrgTestBasic1Cpp(*iDevice);
        proxy->SetPropertyInitialEvent(subscribed);
        (void)iSem.Clear();
        proxy->Subscribe();
        iSem.Wait();
        delete proxy;
    } while (IncrementCount());
    Print("\nCompleted %u subscriptions in %us\n", iCount, iTimeoutSecs);
}

bool PerformanceTests::IncrementCount()
{
    if (Os::TimeInMs(gEnv->OsCtx()) <= iTestStopTime) {
        iLock.Wait();
        iCount++;
        iLock.Signal();
        return true;
    }
    return false;
}

void PerformanceTests::TimerExpired()
{
    iSem.Signal();
}

void PerformanceTests::Added(CpDeviceCpp& aDevice)
{
    if (iDevice != NULL) {
        Print("Found more than one device.  Giving up as test results will probably be invalid.\n");
        ASSERTS();
    }
    iDevice = &aDevice;
    iDevice->AddRef();
    iSem.Signal();
}

void PerformanceTests::Removed(CpDeviceCpp& /*aDevice*/)
{
    Print("ERROR: Device removed while test is running.\n");
    ASSERTS();
}

void PerformanceTests::ActionThread()
{
    CpProxyOpenhomeOrgTestBasic1Cpp* proxy = new CpProxyOpenhomeOrgTestBasic1Cpp(*iDevice);
    uint32_t val;
    do {
        proxy->SyncGetUint(val);
    } while (IncrementCount());
    delete proxy;
}

void PerformanceTests::Subscribed()
{
    iSem.Signal();
}


void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;
    Brn emptyString("");
    OptionBool loopback("-l", "--loopback", "Use the loopback adapter only");
    parser.AddOption(&loopback);
    OptionUint timeout("-t", "--timeout", 1, "Time (in seconds) to run tests for");
    parser.AddOption(&timeout);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }
    if (loopback.Value()) {
        aInitParams->SetUseLoopbackNetworkAdapter();
    }
    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCp(subnet);

    Print("TestPerformanceCp - starting\n");
    PerformanceTests* tests = new PerformanceTests(timeout.Value());
    tests->RunTests();
    delete tests;
    Print("Tests complete - press 'q' to exit\n");
    while (getchar() != 'q');

    UpnpLibrary::Close();
}
