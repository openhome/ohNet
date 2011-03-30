#include <TestFramework.h>
#include <OptionParser.h>
#include <ZappTypes.h>
#include <Zapp.h>
#include <Std/CpDevice.h>
#include <Std/CpDeviceUpnp.h>
#include <Std/TestBasicDv.h>
#include <Std/TestBasicCp.h>
#include <Std/DvDevice.h>

#include <string>
#include <vector>

using namespace Zapp;
using namespace Zapp::TestFramework;

class CpDevices
{
    static const TUint kTestIterations = 10;
public:
    CpDevices(const std::string& aTargetUdn);
    ~CpDevices();
    void TestActions();
    void TestSubscriptions();
    void Added(CpDeviceCpp& aDevice);
    void Removed(CpDeviceCpp& aDevice);
private:
    Mutex iLock;
    std::string iTargetUdn;
    std::vector<CpDeviceCpp*> iList;
};

CpDevices::CpDevices(const std::string& aTargetUdn)
    : iLock("DLMX")
    , iTargetUdn(aTargetUdn)
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

void CpDevices::TestSubscriptions()
{
    ASSERT(iList.size() != 0);
    CpDeviceCpp* device = iList[0];
    TestBasicCp::TestSubscriptions(*device);
}

void CpDevices::Added(CpDeviceCpp& aDevice)
{
    iLock.Wait();
    if (aDevice.Udn() == iTargetUdn) {
        iList.push_back(&aDevice);
        aDevice.AddRef();
    }
    iLock.Signal();
}

void CpDevices::Removed(CpDeviceCpp& /*aDevice*/)
{
}


void Zapp::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams)
{
    OptionParser parser;
    OptionBool loopback("-l", "--loopback", "Use the loopback adapter only");
    parser.AddOption(&loopback);
    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }
    if (loopback.Value()) {
        aInitParams->SetUseLoopbackNetworkInterface();
    }
    aInitParams->SetMsearchTime(1);
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartCombined();
	//Debug::SetLevel(Debug::kEvent | Debug::kDvEvent);

    Print("TestDvDeviceStd - starting\n");

    DeviceBasic* device = new DeviceBasic;
    CpDevices* deviceList = new CpDevices(device->Device().Udn());
    FunctorCpDeviceCpp added = MakeFunctorCpDeviceCpp(*deviceList, &CpDevices::Added);
    FunctorCpDeviceCpp removed = MakeFunctorCpDeviceCpp(*deviceList, &CpDevices::Removed);
    std::string domainName("zapp.org");
    std::string serviceType("TestBasic");
    TUint ver = 1;
    CpDeviceListCppUpnpServiceType* list =
                new CpDeviceListCppUpnpServiceType(domainName, serviceType, ver, added, removed);
    Blocker* blocker = new Blocker;
    blocker->Wait(aInitParams->MsearchTimeSecs());
    delete blocker;
    try {
		deviceList->TestActions();
		deviceList->TestSubscriptions();
	}
	catch (Exception& e) {
		Print("Exception %s from %s:%u\n", e.Message(), e.File(), e.Line());
		ASSERTS();
	}
    delete list;
    delete deviceList;
    delete device;

    Print("TestDvDeviceStd - completed\n");
    UpnpLibrary::Close();
}
