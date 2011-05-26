#include <TestFramework.h>
#include <OhNetTypes.h>
#include <Core/DvDevice.h>
#include <Core/DvOpenhomeOrgTestBasic1.h>
#include <Core/CpOpenhomeOrgTestBasic1.h>
#include <OhNet.h>
#include <Core/CpDeviceDv.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class ProviderTestBasic : public DvProviderOpenhomeOrgTestBasic1
{
public:
    ProviderTestBasic(DvDevice& aDevice);
private:
    void Increment(IInvocationResponse& aResponse, TUint aVersion, TUint aValue, IInvocationResponseUint& aResult);
    void Decrement(IInvocationResponse& aResponse, TUint aVersion, TInt aValue, IInvocationResponseInt& aResult);
    void Toggle(IInvocationResponse& aResponse, TUint aVersion, TBool aValue, IInvocationResponseBool& aResult);
    void EchoString(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IInvocationResponseString& aResult);
    void EchoBinary(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IInvocationResponseBinary& aResult);
    void SetUint(IInvocationResponse& aResponse, TUint aVersion, TUint aValueUint);
    void GetUint(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValueUint);
    void SetInt(IInvocationResponse& aResponse, TUint aVersion, TInt aValueInt);
    void GetInt(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseInt& aValueInt);
    void SetBool(IInvocationResponse& aResponse, TUint aVersion, TBool aValueBool);
    void GetBool(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValueBool);
    void SetMultiple(IInvocationResponse& aResponse, TUint aVersion, TUint aValueUint, TInt aValueInt, TBool aValueBool);
    void SetString(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValueStr);
    void GetString(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValueStr);
    void SetBinary(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValueBin);
    void GetBinary(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aValueBin);
};

class DeviceBasic
{
public:
    DeviceBasic();
    ~DeviceBasic();
    DvDevice& Device();
private:
    DvDevice* iDevice;
    ProviderTestBasic* iTestBasic;
};


ProviderTestBasic::ProviderTestBasic(DvDevice& aDevice)
    : DvProviderOpenhomeOrgTestBasic1(aDevice)
{
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

void ProviderTestBasic::Increment(IInvocationResponse& aResponse, TUint /*aVersion*/, TUint aValue, IInvocationResponseUint& aResult)
{
    aResponse.Start();
    aResult.Write(++aValue);
    aResponse.End();
}

void ProviderTestBasic::Decrement(IInvocationResponse& aResponse, TUint /*aVersion*/, TInt aValue, IInvocationResponseInt& aResult)
{
    aResponse.Start();
    aResult.Write(--aValue);
    aResponse.End();
}

void ProviderTestBasic::Toggle(IInvocationResponse& aResponse, TUint /*aVersion*/, TBool aValue, IInvocationResponseBool& aResult)
{
    aResponse.Start();
    aResult.Write(!aValue);
    aResponse.End();
}

void ProviderTestBasic::EchoString(IInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValue, IInvocationResponseString& aResult)
{
    aResponse.Start();
    aResult.Write(aValue);
    aResult.WriteFlush();
    aResponse.End();
}

void ProviderTestBasic::EchoBinary(IInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValue, IInvocationResponseBinary& aResult)
{
    aResponse.Start();
    aResult.Write(aValue);
    aResult.WriteFlush();
    aResponse.End();
}

void ProviderTestBasic::SetUint(IInvocationResponse& aResponse, TUint /*aVersion*/, TUint aValueUint)
{
    SetPropertyVarUint(aValueUint);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetUint(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseUint& aValueUint)
{
    aResponse.Start();
    TUint val;
    GetPropertyVarUint(val);
    aValueUint.Write(val);
    aResponse.End();
}

void ProviderTestBasic::SetInt(IInvocationResponse& aResponse, TUint /*aVersion*/, TInt aValueInt)
{
    SetPropertyVarInt(aValueInt);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetInt(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseInt& aValueInt)
{
    aResponse.Start();
    TInt val;
    GetPropertyVarInt(val);
    aValueInt.Write(val);
    aResponse.End();
}

void ProviderTestBasic::SetBool(IInvocationResponse& aResponse, TUint /*aVersion*/, TBool aValueBool)
{
    SetPropertyVarBool(aValueBool);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetBool(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseBool& aValueBool)
{
    aResponse.Start();
    TBool val;
    GetPropertyVarBool(val);
    aValueBool.Write(val);
    aResponse.End();
}

void ProviderTestBasic::SetMultiple(IInvocationResponse& aResponse, TUint /*aVersion*/, TUint aValueUint, TInt aValueInt, TBool aValueBool)
{
    PropertiesLock();
    SetPropertyVarUint(aValueUint);
    SetPropertyVarInt(aValueInt);
    SetPropertyVarBool(aValueBool);
    PropertiesUnlock();
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::SetString(IInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValueStr)
{
    SetPropertyVarStr(aValueStr);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetString(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseString& aValueStr)
{
    aResponse.Start();
    Brhz val;
    GetPropertyVarStr(val);
    aValueStr.Write(val);
    aValueStr.WriteFlush();
    aResponse.End();
}

void ProviderTestBasic::SetBinary(IInvocationResponse& aResponse, TUint /*aVersion*/, const Brx& aValueBin)
{
    SetPropertyVarBin(aValueBin);
    aResponse.Start();
    aResponse.End();
}

void ProviderTestBasic::GetBinary(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseBinary& aValueBin)
{
    aResponse.Start();
    Brh val;
    GetPropertyVarBin(val);
    aValueBin.Write(val);
    aValueBin.WriteFlush();
    aResponse.End();
}


static Bwh gDeviceName("device");

static void RandomiseUdn(Bwh& aUdn)
{
    aUdn.Grow(aUdn.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1);
    aUdn.Append('-');
    Bws<Ascii::kMaxUintStringBytes> buf;
    NetworkInterface* nif = Stack::NetworkInterfaceList().CurrentInterface();
    TUint max = nif->Address();
    delete nif;
    (void)Ascii::AppendDec(buf, Random(max));
    aUdn.Append(buf);
    aUdn.PtrZ();
}

DeviceBasic::DeviceBasic()
{
    RandomiseUdn(gDeviceName);
    iDevice = new DvDevice(gDeviceName);
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

static void updatesComplete(void* aPtr)
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

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartCombined();

    Print("TestCpDeviceDv - starting\n");

    DeviceBasic* device = new DeviceBasic;
    CpDeviceDv* cpDevice = CpDeviceDv::New(device->Device());
    TestInvocation(*cpDevice);
    TestSubscription(*cpDevice);
    cpDevice->RemoveRef();
    delete device;

    Print("TestCpDeviceDv - completed\n");
    UpnpLibrary::Close();
}
