#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Cpp/CpDeviceUpnp.h>
#include "TestBasicDv.h"
#include "../../ControlPoint/Tests/TestBasicCp.h"
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Private/Globals.h>

#include <string>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class CpDevices
{
    static const TUint kTestIterations = 10;
public:
    CpDevices(const std::string& aTargetUdn, Semaphore& aAddedSem);
    ~CpDevices();
    void TestActions();
    void TestThrowsWhenDisabled();
    void TestThrowsCustomError();
    void TestSubscriptions();
    void Added(CpDeviceCpp& aDevice);
    void Removed(CpDeviceCpp& aDevice);
private:
    Mutex iLock;
    std::string iTargetUdn;
    std::vector<CpDeviceCpp*> iList;
    Semaphore& iAddedSem;
};

CpDevices::CpDevices(const std::string& aTargetUdn, Semaphore& aAddedSem)
    : iLock("DLMX")
    , iTargetUdn(aTargetUdn)
    , iAddedSem(aAddedSem)
{
}

CpDevices::~CpDevices()
{
    const TUint count = (TUint)iList.size();
    for (TUint i=0; i<count; i++) {
        iList[i]->RemoveRef();
    }
    iList.clear();
}

void CpDevices::TestActions()
{
    ASSERT(iList.size() != 0);
    CpDeviceCpp* device = iList[0];
    TestBasicCp::TestActions(*device);
}

void CpDevices::TestThrowsWhenDisabled()
{
    ASSERT(iList.size() != 0);
    CpDeviceCpp* device = iList[0];
    TestBasicCp::TestThrowsWhenDisabled(*device);
}

void CpDevices::TestThrowsCustomError()
{
    ASSERT(iList.size() != 0);
    CpDeviceCpp* device = iList[0];
    TestBasicCp::TestThrowsCustomError(*device);
}

void CpDevices::TestSubscriptions()
{
    ASSERT(iList.size() != 0);
    CpDeviceCpp* device = iList[0];
    TestBasicCp::TestSubscriptions(*device);
}

void CpDevices::Added(CpDeviceCpp& aDevice)
{
    iLock.Wait();
    if (iList.size() == 0 && aDevice.Udn() == iTargetUdn) {
        iList.push_back(&aDevice);
        aDevice.AddRef();
        iAddedSem.Signal();
    }
    iLock.Signal();
}

void CpDevices::Removed(CpDeviceCpp& /*aDevice*/)
{
}


void STDCALL DeviceDisabled(void* aPtr)
{
    ((Semaphore*)aPtr)->Signal();
}

void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;
    OptionBool loopback("-l", "--loopback", "Use the loopback adapter only");
    parser.AddOption(&loopback);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }
    if (loopback.Value()) {
        aInitParams->SetUseLoopbackNetworkAdapter();
    }
    aInitParams->SetMsearchTime(1);
    aInitParams->SetDvUpnpServerPort(0);
    aInitParams->SetDvPublisherModerationTime(10); // arbitrary small value.  Not required here but
                                                   // useful to have moderation tested somewhere.
    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCombined(subnet);
    //Debug::SetLevel(Debug::kEvent | Debug::kDvEvent);

    Print("TestDvDeviceStd - starting\n");

    Semaphore* sem = new Semaphore("SEM1", 0);
    DeviceBasic* device = new DeviceBasic(*gEnv, DeviceBasic::eProtocolUpnp);
    CpDevices* deviceList = new CpDevices(device->Device().Udn(), *sem);
    FunctorCpDeviceCpp added = MakeFunctorCpDeviceCpp(*deviceList, &CpDevices::Added);
    FunctorCpDeviceCpp removed = MakeFunctorCpDeviceCpp(*deviceList, &CpDevices::Removed);
    std::string domainName("openhome.org");
    std::string serviceType("TestBasic");
    TUint ver = 1;
    CpDeviceListCppUpnpServiceType* list =
                new CpDeviceListCppUpnpServiceType(domainName, serviceType, ver, added, removed);
    sem->Wait(30*1000); // allow up to 30s to find our one device
    try {
        deviceList->TestActions();
        Functor cb = MakeFunctor(sem, &DeviceDisabled);
        device->Device().SetDisabled(cb);
        sem->Wait();
        deviceList->TestThrowsWhenDisabled();
        device->Device().SetEnabled();
        deviceList->TestThrowsCustomError();
        deviceList->TestSubscriptions();
    }
    catch (Exception& e) {
        Print("Exception %s from %s:%u\n", e.Message(), e.File(), e.Line());
        ASSERTS();
    }
    delete sem;
    delete list;
    delete deviceList;
    delete device;

    Print("TestDvDeviceStd - completed\n");
    UpnpLibrary::Close();
}
