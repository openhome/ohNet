#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include "TestBasicDv.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Core/CpOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviStack.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

namespace OpenHome {
namespace TestDvSubscription {

class CpDevices
{
public:
    CpDevices(Semaphore& aAddedSem, const Brx& aTargetUdn);
    ~CpDevices();
    void Test();
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
private:
    void UpdatesComplete();
private:
    Mutex iLock;
    std::vector<CpDevice*> iList;
    Semaphore& iAddedSem;
    Semaphore iUpdatesComplete;
    const Brx& iTargetUdn;
};

} // namespace TestDvSubscription
} // namespace OpenHome

using namespace OpenHome::TestDvSubscription;

CpDevices::CpDevices(Semaphore& aAddedSem, const Brx& aTargetUdn)
    : iLock("DLMX")
    , iAddedSem(aAddedSem)
    , iUpdatesComplete("DSB2", 0)
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

void CpDevices::Test()
{
    ASSERT(iList.size() == 1);
    CpProxyOpenhomeOrgTestBasic1* proxy = new CpProxyOpenhomeOrgTestBasic1(*(iList[0]));
    // reset state of provider such that setters below result in evented updates
    proxy->SyncSetUint(0);
    proxy->SyncSetInt(0);
    proxy->SyncSetBool(false);
    proxy->SyncSetString(Brx::Empty());
    proxy->SyncSetBinary(Brx::Empty());
    //
    Functor functor = MakeFunctor(*this, &CpDevices::UpdatesComplete);
    proxy->SetPropertyChanged(functor);
    proxy->Subscribe();
    iUpdatesComplete.Wait(); // wait for initial event

    /* For each property,
         call the setter action it
         wait on a property being updated
         check that the property matches the value set
         check that the getter action matches the property
    */

    Print("  Uint...\n");
    proxy->SyncSetUint(1);
    iUpdatesComplete.Wait();
    TUint propUint;
    proxy->PropertyVarUint(propUint);
    ASSERT(propUint == 1);
    TUint valUint;
    proxy->SyncGetUint(valUint);
    ASSERT(propUint == valUint);

    Print("  Int...\n");
    proxy->SyncSetInt(-99);
    iUpdatesComplete.Wait();
    TInt propInt;
    proxy->PropertyVarInt(propInt);
    ASSERT(propInt == -99);
    TInt valInt;
    proxy->SyncGetInt(valInt);
    ASSERT(propInt == valInt);

    Print("  Bool...\n");
    proxy->SyncSetBool(true);
    iUpdatesComplete.Wait();
    TBool propBool;
    proxy->PropertyVarBool(propBool);
    ASSERT(propBool);
    TBool valBool;
    proxy->SyncGetBool(valBool);
    ASSERT(valBool);

    Print("  String...\n");
    Brn str("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut "
            "labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco "
            "laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in "
            "voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
            "non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    proxy->SyncSetString(str);
    iUpdatesComplete.Wait();
    Brhz propStr;
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    // test again to check that PropertyVarStr didn't TransferTo the property
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    Brh valStr;
    proxy->SyncGetString(valStr);
    ASSERT(propStr == valStr);

    Print("  Binary...\n");
    char bin[256];
    for (TUint i=0; i<256; i++) {
        bin[i] = (char)i;
    }
    Brn bufBin((const TByte*)&bin[0], 256);
    proxy->SyncSetBinary(bufBin);
    iUpdatesComplete.Wait();
    Brh propBin;
    proxy->PropertyVarBin(propBin);
    ASSERT(propBin == bufBin);
    // test again to check that PropertyVarBin didn't TransferTo the property
    proxy->PropertyVarBin(propBin);
    ASSERT(propBin == bufBin);
    Brh valBin;
    proxy->SyncGetBinary(valBin);
    ASSERT(propBin == valBin);

    Print("  Multiple...\n");
    proxy->SyncSetMultiple(15, 658, false);
    iUpdatesComplete.Wait();
    proxy->PropertyVarUint(propUint);
    ASSERT(propUint == 15);
    proxy->SyncGetUint(valUint);
    ASSERT(propUint == valUint);
    proxy->PropertyVarInt(propInt);
    ASSERT(propInt == 658);
    proxy->SyncGetInt(valInt);
    ASSERT(propInt == valInt);
    proxy->PropertyVarBool(propBool);
    ASSERT(!propBool);
    proxy->SyncGetBool(valBool);
    ASSERT(!valBool);

    delete proxy; // automatically unsubscribes
}

void CpDevices::Added(CpDevice& aDevice)
{
    iLock.Wait();
    if (aDevice.Udn() == iTargetUdn) {
        iList.push_back(&aDevice);
        aDevice.AddRef();
        iAddedSem.Signal();
    }
    iLock.Signal();
}

void CpDevices::Removed(CpDevice& /*aDevice*/)
{
}

void CpDevices::UpdatesComplete()
{
    iUpdatesComplete.Signal();
}


void TestDvSubscription(CpStack& aCpStack, DvStack& aDvStack)
{
    Environment& env = aDvStack.Env();
    InitialisationParams* initParams = env.InitParams();
    TUint oldMsearchTime = initParams->MsearchTimeSecs();
    initParams->SetMsearchTime(1);
    Print("TestDvSubscription - starting\n");

    Semaphore* sem = new Semaphore("SEM1", 0);
    DeviceBasic* device = new DeviceBasic(aDvStack);
    CpDevices* deviceList = new CpDevices(*sem, device->Udn());
    FunctorCpDevice added = MakeFunctorCpDevice(*deviceList, &CpDevices::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(*deviceList, &CpDevices::Removed);
    Brn domainName("openhome.org");
    Brn serviceType("TestBasic");
    TUint ver = 1;
    CpDeviceListUpnpServiceType* list =
                new CpDeviceListUpnpServiceType(aCpStack, domainName, serviceType, ver, added, removed);
    sem->Wait(30*1000); // allow up to 30 seconds to issue the msearch and receive a response
    delete sem;
    for (TUint i=0; i<100; i++) {
        Print(" loop #%u\n", i);
        deviceList->Test();
    }
    delete list;
    delete deviceList;
    delete device;

    Print("TestDvSubscription - completed\n");
    initParams->SetMsearchTime(oldMsearchTime);
}
