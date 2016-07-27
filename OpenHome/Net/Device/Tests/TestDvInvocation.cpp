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
namespace TestDvInvocation {

class CpDevices
{
    static const TUint kTestIterations = 10;
public:
    CpDevices(Semaphore& aAddedSem, const Brx& aTargetUdn);
    ~CpDevices();
    void Test();
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
private:
    Mutex iLock;
    std::vector<CpDevice*> iList;
    Semaphore& iAddedSem;
    const Brx& iTargetUdn;
};

} // namespace TestDvInvocation
} // namespace OpenHome

using namespace OpenHome::TestDvInvocation;

CpDevices::CpDevices(Semaphore& aAddedSem, const Brx& aTargetUdn)
    : iLock("DLMX")
    , iAddedSem(aAddedSem)
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
    ASSERT(iList.size() != 0);
    CpProxyOpenhomeOrgTestBasic1* proxy = new CpProxyOpenhomeOrgTestBasic1(*(iList[0]));
    TUint i;

    Print("  Unsigned integer arguments...\n");
    TUint valUint = 15;
    for (i=0; i<kTestIterations; i++) {
        TUint result;
        proxy->SyncIncrement(valUint, result);
        ASSERT(result == valUint+1);
        valUint = result;
    }

    TUint resUint;
    for (valUint=10; valUint<=20; valUint++) {
        proxy->SyncEchoAllowedRangeUint(valUint, resUint);
    }
    // can't easily validate handling of unsupported values - it asserts rather than throws
#if 0
    try {
        proxy->SyncEchoAllowedRangeUint(9, resUint);
        ASSERTS();
    }
    catch (ProxyError&) {}
    try {
        proxy->SyncEchoAllowedRangeUint(21, resUint);
        ASSERTS();
    }
    catch (ProxyError&) {}
#endif

    Print("  Integer arguments...\n");
    TInt valInt = 3;
    for (i=0; i<kTestIterations; i++) {
        TInt result;
        proxy->SyncDecrement(valInt, result);
        ASSERT(result == valInt-1);
        valInt = result;
    }

    Print("  Boolean arguments...\n");
    TBool valBool = true;
    for (i=0; i<kTestIterations; i++) {
        TBool result;
        proxy->SyncToggle(valBool, result);
        ASSERT(result == !valBool);
        valBool = result;
    }

    Print("  String arguments...\n");
    Brn valStr("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut "
               "labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco "
               "laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in "
               "voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
               "non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoString(valStr, result);
        ASSERT(result == valStr);
    }
    // Test some end-of-line conversions.
    // '\n', '\r', and '\r\n' should all be returned as a single '\n'.
    Brn valLf("<tag>some\ntext</<tag>");
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoString(valLf, result);
        ASSERT(result == valLf);
    }
    Brn valCr("<tag>some\rtext</<tag>");
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoString(valCr, result);
        ASSERT(result == valLf);
    }
    Brn valCrLf("<tag>some\r\ntext</<tag>");
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoString(valCrLf, result);
        ASSERT(result == valLf);
    }
    Brn valCrLfMultiple("<tag>some\r\n\r\ntext</<tag>");
    Brn valCrLfMultipleExpected("<tag>some\n\ntext</<tag>");
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoString(valCrLfMultiple, result);
        ASSERT(result == valCrLfMultipleExpected);
    }
    Brn valCrLfSplit("<tag>some\r\nmore\r\ntext</<tag>");
    Brn valCrLfSplitExpected("<tag>some\nmore\ntext</<tag>");
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoString(valCrLfSplit, result);
        ASSERT(result == valCrLfSplitExpected);
    }
    Brn valMixed("<tag>some\r\rmore\n\ntext</tag>");
    Brn valMixedExpected("<tag>some\n\nmore\n\ntext</tag>");
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoString(valMixed, result);
        ASSERT(result == valMixedExpected);
    }

    Brh resStr;
    proxy->SyncEchoAllowedValueString(Brn("One"), resStr);
    proxy->SyncEchoAllowedValueString(Brn("Two"), resStr);
    proxy->SyncEchoAllowedValueString(Brn("Three"), resStr);
    proxy->SyncEchoAllowedValueString(Brn("Four"), resStr);
    // can't easily validate handling of unsupported values - it asserts rather than throws
#if 0
    try {
        proxy->SyncEchoAllowedValueString(Brn("Four"), resStr);
        ASSERTS();
    }
    catch (ProxyError&) {}
    try {
        proxy->SyncEchoAllowedValueString(Brn(""), resStr);
        ASSERTS();
    }
    catch (ProxyError&) {}
#endif

    Print("  Binary arguments...\n");
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

void CpDevices::Added(CpDevice& aDevice)
{
    AutoMutex _(iLock);
    if (aDevice.Udn() == iTargetUdn) {
        iList.push_back(&aDevice);
        aDevice.AddRef();
        iAddedSem.Signal();
    }
}

void CpDevices::Removed(CpDevice& /*aDevice*/)
{
}


void TestDvInvocation(CpStack& aCpStack, DvStack& aDvStack)
{
    InitialisationParams* initParams = aDvStack.Env().InitParams();
    TUint oldMsearchTime = initParams->MsearchTimeSecs();
    initParams->SetMsearchTime(1);
    Print("TestDvInvocation - starting\n");

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
    sem->Wait(30*1000); // allow up to 30 seconds to find our one device
    deviceList->Test();
    delete list;
    delete deviceList;
    delete sem;

    // validate fixes for hangs/crashes with overlapping calls to SetDisabled
    Print("  Overlapping calls to SetDisabled...\n");
    Semaphore sem2("SEM2", 0);
    Semaphore sem3("SEM3", 0);
    device->Device().SetDisabled(MakeFunctor(sem2, &Semaphore::Signal));
    device->Device().SetDisabled(MakeFunctor(sem3, &Semaphore::Signal));
    sem2.Wait();
    sem3.Wait();

    delete device;

    Print("TestDvInvocation - completed\n");
    initParams->SetMsearchTime(oldMsearchTime);
}
