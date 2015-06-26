#include <OpenHome/Types.h>
#include <OpenHome/Net/Cpp/CpOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include "TestBasicCp.h"
#include <OpenHome/Private/TestFramework.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;


void TestBasicCp::TestActions(CpDeviceCpp& aDevice)
{
    Print("  Actions\n");
    CpProxyOpenhomeOrgTestBasic1Cpp* proxy = new CpProxyOpenhomeOrgTestBasic1Cpp(aDevice);
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
    std::string valStr("<&'tag\">");
    for (i=0; i<kTestIterations; i++) {
        std::string result;
        proxy->SyncEchoString(valStr, result);
        ASSERT(result == valStr);
    }

    Print("    Binary arguments...\n");
    char bin[256];
    for (i=0; i<256; i++) {
        bin[i] = (char)i;
    }
    std::string valBin(&bin[0], 256);
    for (i=0; i<kTestIterations; i++) {
        std::string result;
        proxy->SyncEchoBinary(valBin, result);
        ASSERT(result == valBin);
        ASSERT(result.length() == 256);
    }

    delete proxy;
}

void TestBasicCp::TestThrowsWhenDisabled(CpDeviceCpp& aDevice)
{
    CpProxyOpenhomeOrgTestBasic1Cpp* proxy = new CpProxyOpenhomeOrgTestBasic1Cpp(aDevice);
    Print("  Actions throw when device disabled\n");
    try {
        TUint valUint;
        proxy->SyncGetUint(valUint);
        ASSERTS();
    }
    catch(ProxyError&) { }
    delete proxy;
}

void TestBasicCp::TestThrowsCustomError(CpDeviceCpp& aDevice)
{
    CpProxyOpenhomeOrgTestBasic1Cpp* proxy = new CpProxyOpenhomeOrgTestBasic1Cpp(aDevice);
    Print("  Custom errors are reported\n");
    try {
        proxy->SyncSetInt(12345);
        ASSERTS();
    }
    catch (ProxyError& pe) {
        ASSERT(pe.Code() == 801);
    }
    delete proxy;
}

static void STDCALL updatesComplete(void* aPtr)
{
    reinterpret_cast<Semaphore*>(aPtr)->Signal();
}

void TestBasicCp::TestSubscriptions(CpDeviceCpp& aDevice)
{
    Semaphore sem("TSEM", 0);
    Print("  Subscriptions\n");
    CpProxyOpenhomeOrgTestBasic1Cpp* proxy = new CpProxyOpenhomeOrgTestBasic1Cpp(aDevice);
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
    std::string str("<&'tag\">");
    proxy->SyncSetString(str);
    sem.Wait();
    std::string propStr;
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    // test again to check that PropertyVarStr didn't TransferTo the property
    proxy->PropertyVarStr(propStr);
    ASSERT(propStr == str);
    std::string valStr;
    proxy->SyncGetString(valStr);
    ASSERT(propStr == valStr);

    Print("    Binary...\n");
    char bin[256];
    for (TUint i=0; i<256; i++) {
        bin[i] = (char)i;
    }
    std::string bufBin(&bin[0], 256);
    proxy->SyncSetBinary(bufBin);
    sem.Wait();
    std::string propBin;
    proxy->PropertyVarBin(propBin);
    ASSERT(propBin == bufBin);
    // test again to check that PropertyVarBin didn't TransferTo the property
    proxy->PropertyVarBin(propBin);
    ASSERT(propBin == bufBin);
    std::string valBin;
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
