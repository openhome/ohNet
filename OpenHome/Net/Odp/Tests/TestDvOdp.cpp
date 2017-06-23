#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Private/Tests/TestBasicDv.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Core/CpOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Net/Odp/DviProtocolOdp.h>
#include <OpenHome/Net/Odp/DviServerOdp.h>
#include <OpenHome/Net/Odp/Tests/CpiDeviceOdp.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Debug-ohMediaPlayer.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

namespace OpenHome {
namespace Net {
namespace Test {

class DeviceOdp
{
    static const TChar* kOdpName;
    static const Brn kOdpNameBuf;
public:
    DeviceOdp(DvStack& aDvStack);
    ~DeviceOdp();
    const Brx& OdpDeviceName() const;
private:
    DvDeviceStandard* iDevice;
    ProviderTestBasic* iTestBasic;
};

class TestOdp
{
    static const TUint kTestIterations = 10;
public:
    TestOdp(CpStack& aCpStack, Endpoint aLocation, const Brx& aOdpName, Semaphore& aSem);
    ~TestOdp();
    void TestActions();
    void TestSubscriptions();
private:
    void DeviceReady();
    void UpdatesComplete();
private:
    Semaphore& iSem;
    Semaphore iUpdatesComplete;
    CpDevice* iCpDevice;
    CpiDeviceOdp* iCpDeviceOdp;
};

} // namespace Test
} // namespace Net
} // namespace OpenHome

using namespace OpenHome::Net::Test;


// DeviceOdp

const TChar* DeviceOdp::kOdpName = "TestOdpDevice";
const Brn DeviceOdp::kOdpNameBuf(kOdpName);
static Bwh gDeviceName("device");

DeviceOdp::DeviceOdp(DvStack& aDvStack)
{
    TestFramework::RandomiseUdn(aDvStack.Env(), gDeviceName);
    iDevice = new DvDeviceStandard(aDvStack, gDeviceName);
    iDevice->SetAttribute("Upnp.Domain", "openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Test");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", "ohNetTestDevice");
    iDevice->SetAttribute("Upnp.Manufacturer", "None");
    iDevice->SetAttribute("Upnp.ModelName", "ohNet test device");
    iDevice->SetAttribute("Odp.Name", kOdpName);
    iTestBasic = new ProviderTestBasic(*iDevice);
    iDevice->SetEnabled();
}

DeviceOdp::~DeviceOdp()
{
    delete iTestBasic;
    delete iDevice;
}

const Brx& DeviceOdp::OdpDeviceName() const
{
    return kOdpNameBuf;
}


// TestOdp

TestOdp::TestOdp(CpStack& aCpStack, Endpoint aLocation, const Brx& aOdpName, Semaphore& aSem)
    : iSem(aSem)
    , iUpdatesComplete("SEM2", 0)
    , iCpDevice(nullptr)
{
    iCpDeviceOdp = new CpiDeviceOdp(aCpStack, aLocation, aOdpName, MakeFunctor(*this, &TestOdp::DeviceReady));
}

TestOdp::~TestOdp()
{
    iCpDeviceOdp->Destroy();
    iCpDevice->RemoveRef();
}

void TestOdp::TestActions()
{
    Print("  Actions...\n");
    auto proxy = new CpProxyOpenhomeOrgTestBasic1(*iCpDevice);
    TUint i;

    Print("    Uint...\n");
    TUint valUint = 15;
    for (i=0; i<kTestIterations; i++) {
        TUint result;
        proxy->SyncIncrement(valUint, result);
        ASSERT(result == valUint+1);
        valUint = result;
    }

    Print("    Int...\n");
    TInt valInt = 3;
    for (i=0; i<kTestIterations; i++) {
        TInt result;
        proxy->SyncDecrement(valInt, result);
        ASSERT(result == valInt-1);
        valInt = result;
    }

    Print("    Bool...\n");
    TBool valBool = true;
    for (i=0; i<kTestIterations; i++) {
        TBool result;
        proxy->SyncToggle(valBool, result);
        ASSERT(result == !valBool);
        valBool = result;
    }

    Print("    String...\n");
    Brn valStr(Brx::Empty());
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoString(valStr, result);
        ASSERT(result == valStr);
    }
    valStr.Set("\"\\/\b\f\t\r\n");
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoString(valStr, result);
        ASSERT(result == valStr);
    }
    valStr.Set("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut "
               "labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco "
               "laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in "
               "voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
               "non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoString(valStr, result);
        ASSERT(result == valStr);
    }

    Print("    Binary...\n");
    char bin[256];
    for (i=0; i<256; i++) {
        bin[i] = (char)i;
    }
    Brn valBin((const TByte*)&bin[0], 256);
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoBinary(valBin, result);
        ASSERT(result == valBin);
    }

    delete proxy;
}

void TestOdp::TestSubscriptions()
{
    static const TUint kTimeoutMs = 5 * 1000;
    Print("  Subscriptions...\n");
    auto proxy = new CpProxyOpenhomeOrgTestBasic1(*iCpDevice);
    auto functor = MakeFunctor(*this, &TestOdp::UpdatesComplete);
    proxy->SetPropertyChanged(functor);
    proxy->Subscribe();
    iUpdatesComplete.Wait(kTimeoutMs); // wait for initial event

    /* For each property,
         call the setter action it
         wait on a property being updated
         check that the property matches the value set
         check that the getter action matches the property
    */

    Print("    Uint...\n");
    proxy->SyncSetUint(1);
    iUpdatesComplete.Wait(kTimeoutMs);
    TUint propUint;
    proxy->PropertyVarUint(propUint);
    ASSERT(propUint == 1);
    TUint valUint;
    proxy->SyncGetUint(valUint);
    ASSERT(propUint == valUint);

    Print("    Int...\n");
    proxy->SyncSetInt(-99);
    iUpdatesComplete.Wait(kTimeoutMs);
    TInt propInt;
    proxy->PropertyVarInt(propInt);
    ASSERT(propInt == -99);
    TInt valInt;
    proxy->SyncGetInt(valInt);
    ASSERT(propInt == valInt);

    Print("    Bool...\n");
    proxy->SyncSetBool(true);
    iUpdatesComplete.Wait(kTimeoutMs);
    TBool propBool;
    proxy->PropertyVarBool(propBool);
    ASSERT(propBool);
    TBool valBool;
    proxy->SyncGetBool(valBool);
    ASSERT(valBool);

    Print("    String...\n");
    Brn str("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut "
            "labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco "
            "laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in "
            "voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
            "non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    proxy->SyncSetString(str);
    iUpdatesComplete.Wait(kTimeoutMs);
    Brhz propStr;
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    // test again to check that PropertyVarStr didn't TransferTo the property
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    Brh valStr;
    proxy->SyncGetString(valStr);
    ASSERT(propStr == valStr);

    str.Set(Brx::Empty());
    proxy->SyncSetString(str);
    iUpdatesComplete.Wait(kTimeoutMs);
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    proxy->SyncGetString(valStr);
    ASSERT(propStr == valStr);

    str.Set("\"\\/\b\f\t\r\n");
    proxy->SyncSetString(str);
    iUpdatesComplete.Wait(kTimeoutMs);
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    proxy->SyncGetString(valStr);
    ASSERT(propStr == valStr);

    Print("    Binary...\n");
    char bin[256];
    for (TUint i=0; i<256; i++) {
        bin[i] = (char)i;
    }
    Brn bufBin((const TByte*)&bin[0], 256);
    proxy->SyncSetBinary(bufBin);
    iUpdatesComplete.Wait(kTimeoutMs);
    Brh propBin;
    proxy->PropertyVarBin(propBin);
    ASSERT(propBin == bufBin);
    // test again to check that PropertyVarBin didn't TransferTo the property
    proxy->PropertyVarBin(propBin);
    ASSERT(propBin == bufBin);
    Brh valBin;
    proxy->SyncGetBinary(valBin);
    ASSERT(propBin == valBin);

    Print("    Multiple...\n");
    proxy->SyncSetMultiple(15, 658, false);
    iUpdatesComplete.Wait(kTimeoutMs);
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

void TestOdp::DeviceReady()
{
    ASSERT(iCpDeviceOdp->Device() != nullptr);
    iCpDevice = new CpDevice(*(iCpDeviceOdp->Device()));
    iSem.Signal();
}

void TestOdp::UpdatesComplete()
{
    iUpdatesComplete.Signal();
}



void TestDvOdp(CpStack& aCpStack, DvStack& aDvStack)
{
    Print("TestDvOdp - starting\n");

    Debug::SetLevel(Debug::kOdp | Debug::kError | Debug::kEvent);
    auto server = new DviServerOdp(aDvStack, 1);
    aDvStack.AddProtocolFactory(new DviProtocolFactoryOdp());
    auto sem = new Semaphore("SEM1", 0);
    auto device = new DeviceOdp(aDvStack);
    auto nif = UpnpLibrary::CurrentSubnetAdapter("TestDvOdp");
    ASSERT(nif != nullptr);
    Endpoint location(server->Port(), nif->Address());
    nif->RemoveRef("TestDvOdp");
    auto cpDevice = new TestOdp(aCpStack, location, device->OdpDeviceName(), *sem);
    sem->Wait(5*1000); // allow up to 5 seconds to connect to Odp server and receive initial ALIVE message
    delete sem;
    cpDevice->TestActions();
    cpDevice->TestSubscriptions();
    delete cpDevice;
    delete device;
    delete server;

    Print("TestDvOdp - completed\n");
}
