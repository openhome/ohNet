#include "TestBasicCp.h"
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/C/CpProxy.h>
#include <OpenHome/Net/C/CpOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/C/CpDevice.h>

#include <stdlib.h>
#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;


void TestBasicCpC::TestActions(CpDeviceC aDevice)
{
    Print("  Actions\n");
    THandle proxy = CpProxyOpenhomeOrgTestBasic1Create(aDevice);
    TUint i;

    Print("    Unsigned integer arguments...\n");
    uint32_t valUint = 15;
    for (i=0; i<kTestIterations; i++) {
        uint32_t result;
        CpProxyOpenhomeOrgTestBasic1SyncIncrement(proxy, valUint, &result);
        ASSERT(result == valUint+1);
        valUint = result;
    }

    Print("    Integer arguments...\n");
    int32_t valInt = 3;
    for (i=0; i<kTestIterations; i++) {
        int32_t result;
        CpProxyOpenhomeOrgTestBasic1SyncDecrement(proxy, valInt, &result);
        ASSERT(result == valInt-1);
        valInt = result;
    }

    Print("    Boolean arguments...\n");
    uint32_t valBool = 1;
    for (i=0; i<kTestIterations; i++) {
        uint32_t result;
        CpProxyOpenhomeOrgTestBasic1SyncToggle(proxy, valBool, &result);
        ASSERT((result==1 && valBool==0) || (result==0 && valBool==1));
        valBool = result;
    }

    Print("    String arguments...\n");
    const char* valStr = "<&'tag\">";
    for (i=0; i<kTestIterations; i++) {
        char* result;
        CpProxyOpenhomeOrgTestBasic1SyncEchoString(proxy, valStr, &result);
        ASSERT(strcmp(result, valStr) == 0);
        free(result);
    }

    Print("    Binary arguments...\n");
    char valBin[256];
    for (i=0; i<256; i++) {
        valBin[i] = (char)i;
    }
    for (i=0; i<kTestIterations; i++) {
        char* result;
        uint32_t resultLen;
        CpProxyOpenhomeOrgTestBasic1SyncEchoBinary(proxy, valBin, 256, &result, &resultLen);
        ASSERT(resultLen == 256);
        ASSERT(strncmp(result, valBin, resultLen) == 0);
        free(result);
    }

    CpProxyOpenhomeOrgTestBasic1Destroy(proxy);
}

static void STDCALL updatesComplete(void* aPtr)
{
    reinterpret_cast<Semaphore*>(aPtr)->Signal();
}

void TestBasicCpC::TestSubscriptions(CpDeviceC aDevice)
{
    Print("  Subscriptions\n");
    THandle proxy = CpProxyOpenhomeOrgTestBasic1Create(aDevice);
    Semaphore sem("TSEM", 0);
    CpProxySetPropertyChanged(proxy, updatesComplete, &sem);
    CpProxySubscribe(proxy);
    sem.Wait(); // wait for initial event

    /* For each property,
         call the setter action it
         wait on a property being updated
         check that the property matches the value set
         check that the getter action matches the property
    */

    Print("    Uint...\n");
    CpProxyOpenhomeOrgTestBasic1SyncSetUint(proxy, 1);
    sem.Wait();
    uint32_t propUint;
    CpProxyOpenhomeOrgTestBasic1PropertyVarUint(proxy, &propUint);
    ASSERT(propUint == 1);
    uint32_t valUint;
    CpProxyOpenhomeOrgTestBasic1SyncGetUint(proxy, &valUint);
    ASSERT(propUint == valUint);

    Print("    Int...\n");
    CpProxyOpenhomeOrgTestBasic1SyncSetInt(proxy, -99);
    sem.Wait();
    int32_t propInt;
    CpProxyOpenhomeOrgTestBasic1PropertyVarInt(proxy, &propInt);
    ASSERT(propInt == -99);
    int32_t valInt;
    CpProxyOpenhomeOrgTestBasic1SyncGetInt(proxy, &valInt);
    ASSERT(propInt == valInt);

    Print("    Bool...\n");
    CpProxyOpenhomeOrgTestBasic1SyncSetBool(proxy, 1);
    sem.Wait();
    uint32_t propBool;
    CpProxyOpenhomeOrgTestBasic1PropertyVarBool(proxy, &propBool);
    ASSERT(propBool == 1);
    uint32_t valBool;
    CpProxyOpenhomeOrgTestBasic1SyncGetBool(proxy, &valBool);
    ASSERT(valBool == 1);

    Print("    String...\n");
    const char* str = "<&'tag\">";
    CpProxyOpenhomeOrgTestBasic1SyncSetString(proxy, str);
    sem.Wait();
    char* propStr;
    CpProxyOpenhomeOrgTestBasic1PropertyVarStr(proxy, &propStr);
    ASSERT(strcmp(propStr, str) == 0);
    // test again to check that PropertyVarStr didn't TransferTo the property
    free(propStr);
    CpProxyOpenhomeOrgTestBasic1PropertyVarStr(proxy, &propStr);
    ASSERT(strcmp(propStr, str) == 0);
    char* valStr;
    CpProxyOpenhomeOrgTestBasic1SyncGetString(proxy, &valStr);
    ASSERT(strcmp(propStr, valStr) == 0);
    free(propStr);
    free(valStr);

    Print("    Binary...\n");
    char bufBin[256];
    for (TUint i=0; i<256; i++) {
        bufBin[i] = (char)i;
    }
    CpProxyOpenhomeOrgTestBasic1SyncSetBinary(proxy, &bufBin[0], 256);
    sem.Wait();
    char* propBin;
    uint32_t propBinLen;
    CpProxyOpenhomeOrgTestBasic1PropertyVarBin(proxy, &propBin, &propBinLen);
    ASSERT(propBinLen == 256);
    ASSERT(strncmp(propBin, bufBin, propBinLen) == 0);
    // test again to check that PropertyVarBin didn't TransferTo the property
    free(propBin);
    CpProxyOpenhomeOrgTestBasic1PropertyVarBin(proxy, &propBin, &propBinLen);
    ASSERT(propBinLen == 256);
    ASSERT(strncmp(propBin, bufBin, propBinLen) == 0);
    char* valBin;
    uint32_t valBinLen;
    CpProxyOpenhomeOrgTestBasic1SyncGetBinary(proxy, &valBin, &valBinLen);
    ASSERT(valBinLen == 256)
    ASSERT(strncmp(propBin, valBin, valBinLen) ==0);
    free(propBin);
    free(valBin);

    Print("    Multiple...\n");
    CpProxyOpenhomeOrgTestBasic1SyncSetMultiple(proxy, 15, 658, 0);
    sem.Wait();
    CpProxyOpenhomeOrgTestBasic1PropertyVarUint(proxy, &propUint);
    ASSERT(propUint == 15);
    CpProxyOpenhomeOrgTestBasic1SyncGetUint(proxy, &valUint);
    ASSERT(propUint == valUint);
    CpProxyOpenhomeOrgTestBasic1PropertyVarInt(proxy, &propInt);
    ASSERT(propInt == 658);
    CpProxyOpenhomeOrgTestBasic1SyncGetInt(proxy, &valInt);
    ASSERT(propInt == valInt);
    CpProxyOpenhomeOrgTestBasic1PropertyVarBool(proxy, &propBool);
    ASSERT(propBool == 0);
    CpProxyOpenhomeOrgTestBasic1SyncGetBool(proxy, &valBool);
    ASSERT(valBool == 0);

    CpProxyOpenhomeOrgTestBasic1Destroy(proxy); // automatically unsubscribes
}
