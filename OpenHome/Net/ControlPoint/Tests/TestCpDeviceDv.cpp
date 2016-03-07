#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Core/CpStack.h>
#include <OpenHome/Net/Core/DvStack.h>
#include <OpenHome/Net/Core/DvOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Core/CpOpenhomeOrgTestBasic1.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/NetworkAdapterList.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

namespace OpenHome {
namespace TestCpDeviceDv {

class ProviderTestBasic : public DvProviderOpenhomeOrgTestBasic1
{
public:
    ProviderTestBasic(DvDevice& aDevice);
private:
    void Increment(IDvInvocation& aInvocation, TUint aValue, IDvInvocationResponseUint& aResult);
    void Decrement(IDvInvocation& aInvocation, TInt aValue, IDvInvocationResponseInt& aResult);
    void Toggle(IDvInvocation& aInvocation, TBool aValue, IDvInvocationResponseBool& aResult);
    void EchoString(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseString& aResult);
    void EchoBinary(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseBinary& aResult);
    void SetUint(IDvInvocation& aInvocation, TUint aValueUint);
    void GetUint(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValueUint);
    void SetInt(IDvInvocation& aInvocation, TInt aValueInt);
    void GetInt(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValueInt);
    void SetBool(IDvInvocation& aInvocation, TBool aValueBool);
    void GetBool(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValueBool);
    void SetMultiple(IDvInvocation& aInvocation, TUint aValueUint, TInt aValueInt, TBool aValueBool);
    void SetString(IDvInvocation& aInvocation, const Brx& aValueStr);
    void GetString(IDvInvocation& aInvocation, IDvInvocationResponseString& aValueStr);
    void SetBinary(IDvInvocation& aInvocation, const Brx& aValueBin);
    void GetBinary(IDvInvocation& aInvocation, IDvInvocationResponseBinary& aValueBin);
};

class DeviceBasic
{
public:
    DeviceBasic(DvStack& aDvStack);
    ~DeviceBasic();
    DvDevice& Device();
private:
    DvDevice* iDevice;
    ProviderTestBasic* iTestBasic;
};

} // namespace OpenHome
} // namespace TestCpDeviceDv
using namespace OpenHome::TestCpDeviceDv;

ProviderTestBasic::ProviderTestBasic(DvDevice& aDevice)
    : DvProviderOpenhomeOrgTestBasic1(aDevice)
{
    EnablePropertyVarUint();
    EnablePropertyVarInt();
    EnablePropertyVarBool();
    EnablePropertyVarStr();
    EnablePropertyVarBin();
    SetPropertyVarUint(0);
    SetPropertyVarInt(0);
    SetPropertyVarBool(false);
    SetPropertyVarStr(Brx::Empty());
    SetPropertyVarBin(Brx::Empty());

    EnableActionIncrement();
    EnableActionDecrement();
    EnableActionToggle();
    EnableActionEchoString();
    EnableActionEchoBinary();
    EnableActionSetUint();
    EnableActionGetUint();
    EnableActionSetInt();
    EnableActionGetInt();
    EnableActionSetBool();
    EnableActionGetBool();
    EnableActionSetMultiple();
    EnableActionSetString();
    EnableActionGetString();
    EnableActionSetBinary();
    EnableActionGetBinary();
}

void ProviderTestBasic::Increment(IDvInvocation& aInvocation, TUint aValue, IDvInvocationResponseUint& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(++aValue);
    aInvocation.EndResponse();
}

void ProviderTestBasic::Decrement(IDvInvocation& aInvocation, TInt aValue, IDvInvocationResponseInt& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(--aValue);
    aInvocation.EndResponse();
}

void ProviderTestBasic::Toggle(IDvInvocation& aInvocation, TBool aValue, IDvInvocationResponseBool& aResult)
{
    aInvocation.StartResponse();
    aResult.Write(!aValue);
    aInvocation.EndResponse();
}

void ProviderTestBasic::EchoString(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseString& aResult)
{
    aInvocation.StartResponse();
    // validate that string response can be streamed over multiple calls
    Brn start(aValue);
    const TUint pos = start.Bytes() / 2;
    Brn end = start.Split(pos);
    start.Set(start.Ptr(), pos);
    aResult.Write(start);
    aResult.Write(end);
    aResult.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderTestBasic::EchoBinary(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseBinary& aResult)
{
    aInvocation.StartResponse();
    // validate that binary response can be streamed over multiple calls
    Brn start(aValue);
    const TUint pos = start.Bytes() / 2;
    Brn end = start.Split(pos);
    start.Set(start.Ptr(), pos);
    aResult.Write(start);
    aResult.Write(end);
    aResult.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetUint(IDvInvocation& aInvocation, TUint aValueUint)
{
    SetPropertyVarUint(aValueUint);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetUint(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValueUint)
{
    aInvocation.StartResponse();
    TUint val;
    GetPropertyVarUint(val);
    aValueUint.Write(val);
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetInt(IDvInvocation& aInvocation, TInt aValueInt)
{
    SetPropertyVarInt(aValueInt);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetInt(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValueInt)
{
    aInvocation.StartResponse();
    TInt val;
    GetPropertyVarInt(val);
    aValueInt.Write(val);
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetBool(IDvInvocation& aInvocation, TBool aValueBool)
{
    SetPropertyVarBool(aValueBool);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetBool(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValueBool)
{
    aInvocation.StartResponse();
    TBool val;
    GetPropertyVarBool(val);
    aValueBool.Write(val);
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetMultiple(IDvInvocation& aInvocation, TUint aValueUint, TInt aValueInt, TBool aValueBool)
{
    PropertiesLock();
    SetPropertyVarUint(aValueUint);
    SetPropertyVarInt(aValueInt);
    SetPropertyVarBool(aValueBool);
    PropertiesUnlock();
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetString(IDvInvocation& aInvocation, const Brx& aValueStr)
{
    SetPropertyVarStr(aValueStr);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetString(IDvInvocation& aInvocation, IDvInvocationResponseString& aValueStr)
{
    aInvocation.StartResponse();
    Brhz val;
    GetPropertyVarStr(val);
    aValueStr.Write(val);
    aValueStr.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderTestBasic::SetBinary(IDvInvocation& aInvocation, const Brx& aValueBin)
{
    SetPropertyVarBin(aValueBin);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTestBasic::GetBinary(IDvInvocation& aInvocation, IDvInvocationResponseBinary& aValueBin)
{
    aInvocation.StartResponse();
    Brh val;
    GetPropertyVarBin(val);
    aValueBin.Write(val);
    aValueBin.WriteFlush();
    aInvocation.EndResponse();
}


static Bwh gDeviceName("device");

DeviceBasic::DeviceBasic(DvStack& aDvStack)
{
    RandomiseUdn(aDvStack.Env(), gDeviceName);
    iDevice = new DvDevice(aDvStack, gDeviceName);
    iDevice->SetAttribute("Upnp.Domain", "openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Test");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", "ohNetTestDevice");
    iDevice->SetAttribute("Upnp.Manufacturer", "None");
    iDevice->SetAttribute("Upnp.ModelName", "ohNet test device");
    iTestBasic = new ProviderTestBasic(*iDevice);
    iDevice->SetEnabled();
}

DeviceBasic::~DeviceBasic()
{
    delete iTestBasic;
    delete iDevice;
}

DvDevice& DeviceBasic::Device()
{
    return *iDevice;
}


static void TestInvocation(CpDevice& aDevice)
{
    static const TUint kTestIterations = 10;
    
    Print("  Actions\n");
    CpProxyOpenhomeOrgTestBasic1* proxy = new CpProxyOpenhomeOrgTestBasic1(aDevice);
    TUint i;

    Print("    Unsigned integer arguments...\n");
    TUint valUint = 15;
    for (i=0; i<kTestIterations; i++) {
        TUint result;
        proxy->SyncIncrement(valUint, result);
        ASSERT(result == valUint+1);
        valUint = result;
    }

    Print("    Integer arguments...\n");
    TInt valInt = 3;
    for (i=0; i<kTestIterations; i++) {
        TInt result;
        proxy->SyncDecrement(valInt, result);
        ASSERT(result == valInt-1);
        valInt = result;
    }

    Print("    Boolean arguments...\n");
    TBool valBool = true;
    for (i=0; i<kTestIterations; i++) {
        TBool result;
        proxy->SyncToggle(valBool, result);
        ASSERT(result == !valBool);
        valBool = result;
    }

    Print("    String arguments...\n");
    Brn valStr("<&'tag\">");
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoString(valStr, result);
        ASSERT(result == valStr);
    }

    Print("    Binary arguments...\n");
    char bin[256];
    for (i=0; i<256; i++) {
        bin[i] = (char)i;
    }
    Brn valBin((const TByte*)&bin[0], 256);
    for (i=0; i<kTestIterations; i++) {
        Brh result;
        proxy->SyncEchoBinary(valBin, result);
        ASSERT(result == valBin);
        ASSERT(result.Bytes() == 256);
    }

    delete proxy;
}

static void STDCALL updatesComplete(void* aPtr)
{
    reinterpret_cast<Semaphore*>(aPtr)->Signal();
}

static void TestSubscription(CpDevice& aDevice)
{
    Semaphore sem("TSEM", 0);
    Print("  Subscriptions\n");
    CpProxyOpenhomeOrgTestBasic1* proxy = new CpProxyOpenhomeOrgTestBasic1(aDevice);
    Functor functor = MakeFunctor(&sem, updatesComplete);
    proxy->SetPropertyChanged(functor);
    proxy->Subscribe();
    sem.Wait(); // wait for initial event

    /* For each property,
         call the setter action it
         wait on a property being updated
         check that the property matches the value set
         check that the getter action matches the property
    */

    Print("    Uint...\n");
    proxy->SyncSetUint(1);
    sem.Wait();
    TUint propUint;
    proxy->PropertyVarUint(propUint);
    ASSERT(propUint == 1);
    TUint valUint;
    proxy->SyncGetUint(valUint);
    ASSERT(propUint == valUint);

    Print("    Int...\n");
    proxy->SyncSetInt(-99);
    sem.Wait();
    TInt propInt;
    proxy->PropertyVarInt(propInt);
    ASSERT(propInt == -99);
    TInt valInt;
    proxy->SyncGetInt(valInt);
    ASSERT(propInt == valInt);

    Print("    Bool...\n");
    proxy->SyncSetBool(true);
    sem.Wait();
    TBool propBool;
    proxy->PropertyVarBool(propBool);
    ASSERT(propBool);
    TBool valBool;
    proxy->SyncGetBool(valBool);
    ASSERT(valBool);

    Print("    String...\n");
    Brn str("<&'tag\">");
    proxy->SyncSetString(str);
    sem.Wait();
    Brhz propStr;
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    // test again to check that PropertyVarStr didn't TransferTo the property
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    Brh valStr;
    proxy->SyncGetString(valStr);
    ASSERT(propStr == valStr);
    // change str, check evented update doesn't aggregate previous and new values
    Brn str2(str.Ptr(), str.Bytes()/2);
    proxy->SyncSetString(str2);
    sem.Wait();
    Brhz propStr2;
    proxy->PropertyVarStr(propStr2);
    ASSERT(propStr2 == str2);
    ASSERT(propStr2.Bytes() == propStr.Bytes()/2);

    Print("    Binary...\n");
    char bin[256];
    for (TUint i=0; i<256; i++) {
        bin[i] = (char)i;
    }
    Brn bufBin((const TByte*)&bin[0], 256);
    proxy->SyncSetBinary(bufBin);
    sem.Wait();
    Brh propBin;
    proxy->PropertyVarBin(propBin);
    ASSERT(propBin == bufBin);
    // test again to check that PropertyVarBin didn't TransferTo the property
    proxy->PropertyVarBin(propBin);
    ASSERT(propBin == bufBin);
    Brh valBin;
    proxy->SyncGetBinary(valBin);
    ASSERT(propBin == valBin);
    // change bufBin, check evented update doesn't aggregate previous and new values
    Brn bufBin2(bufBin.Ptr(), bufBin.Bytes()/2);
    proxy->SyncSetBinary(bufBin2);
    sem.Wait();
    Brh propBin2;
    proxy->PropertyVarBin(propBin2);
    ASSERT(propBin2 == bufBin2);
    ASSERT(propBin2.Bytes() == propBin.Bytes()/2);

    Print("    Multiple...\n");
    proxy->SyncSetMultiple(15, 658, false);
    sem.Wait();
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

void TestCpDeviceDv(CpStack& aCpStack, DvStack& aDvStack)
{
    Print("TestCpDeviceDv - starting\n");

    DeviceBasic* device = new DeviceBasic(aDvStack);
    CpDeviceDv* cpDevice = CpDeviceDv::New(aCpStack, device->Device());
    TestInvocation(*cpDevice);
    TestSubscription(*cpDevice);
    cpDevice->RemoveRef();
    delete device;

    Print("TestCpDeviceDv - completed\n");
}
