#include <C/DvLinnCoUkProxyManager1.h>
#include <Core/DvLinnCoUkProxyManager1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkProxyManager1C : public DvServiceLinnCoUkProxyManager1
{
public:
    DvServiceLinnCoUkProxyManager1C(DvDevice& aDevice);
    void EnableActionKontrolProductConnected(CallbackProxyManager1KontrolProductConnected aCallback, void* aPtr);
    void EnableActionSetKontrolProductConnected(CallbackProxyManager1SetKontrolProductConnected aCallback, void* aPtr);
    void EnableActionKontrolProductComPort(CallbackProxyManager1KontrolProductComPort aCallback, void* aPtr);
    void EnableActionSetKontrolProductComPort(CallbackProxyManager1SetKontrolProductComPort aCallback, void* aPtr);
    void EnableActionDiscPlayerConnected(CallbackProxyManager1DiscPlayerConnected aCallback, void* aPtr);
    void EnableActionSetDiscPlayerConnected(CallbackProxyManager1SetDiscPlayerConnected aCallback, void* aPtr);
    void EnableActionDiscPlayerComPort(CallbackProxyManager1DiscPlayerComPort aCallback, void* aPtr);
    void EnableActionSetDiscPlayerComPort(CallbackProxyManager1SetDiscPlayerComPort aCallback, void* aPtr);
    void EnableActionTestKontrolProductConnection(CallbackProxyManager1TestKontrolProductConnection aCallback, void* aPtr);
    void EnableActionTestDiscPlayerConnection(CallbackProxyManager1TestDiscPlayerConnection aCallback, void* aPtr);
private:
    void KontrolProductConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConnected);
    void SetKontrolProductConnected(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaConnected);
    void KontrolProductComPort(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPort);
    void SetKontrolProductComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaConnected);
    void DiscPlayerConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConnected);
    void SetDiscPlayerConnected(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaConnected);
    void DiscPlayerComPort(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPort);
    void SetDiscPlayerComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaConnected);
    void TestKontrolProductConnection(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaResult);
    void TestDiscPlayerConnection(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaResult);
private:
    CallbackProxyManager1KontrolProductConnected iCallbackKontrolProductConnected;
    void* iPtrKontrolProductConnected;
    CallbackProxyManager1SetKontrolProductConnected iCallbackSetKontrolProductConnected;
    void* iPtrSetKontrolProductConnected;
    CallbackProxyManager1KontrolProductComPort iCallbackKontrolProductComPort;
    void* iPtrKontrolProductComPort;
    CallbackProxyManager1SetKontrolProductComPort iCallbackSetKontrolProductComPort;
    void* iPtrSetKontrolProductComPort;
    CallbackProxyManager1DiscPlayerConnected iCallbackDiscPlayerConnected;
    void* iPtrDiscPlayerConnected;
    CallbackProxyManager1SetDiscPlayerConnected iCallbackSetDiscPlayerConnected;
    void* iPtrSetDiscPlayerConnected;
    CallbackProxyManager1DiscPlayerComPort iCallbackDiscPlayerComPort;
    void* iPtrDiscPlayerComPort;
    CallbackProxyManager1SetDiscPlayerComPort iCallbackSetDiscPlayerComPort;
    void* iPtrSetDiscPlayerComPort;
    CallbackProxyManager1TestKontrolProductConnection iCallbackTestKontrolProductConnection;
    void* iPtrTestKontrolProductConnection;
    CallbackProxyManager1TestDiscPlayerConnection iCallbackTestDiscPlayerConnection;
    void* iPtrTestDiscPlayerConnection;
};

DvServiceLinnCoUkProxyManager1C::DvServiceLinnCoUkProxyManager1C(DvDevice& aDevice)
    : DvServiceLinnCoUkProxyManager1(aDevice)
{
}

void DvServiceLinnCoUkProxyManager1C::EnableActionKontrolProductConnected(CallbackProxyManager1KontrolProductConnected aCallback, void* aPtr)
{
    iCallbackKontrolProductConnected = aCallback;
    iPtrKontrolProductConnected = aPtr;
    DvServiceLinnCoUkProxyManager1::EnableActionKontrolProductConnected();
}

void DvServiceLinnCoUkProxyManager1C::EnableActionSetKontrolProductConnected(CallbackProxyManager1SetKontrolProductConnected aCallback, void* aPtr)
{
    iCallbackSetKontrolProductConnected = aCallback;
    iPtrSetKontrolProductConnected = aPtr;
    DvServiceLinnCoUkProxyManager1::EnableActionSetKontrolProductConnected();
}

void DvServiceLinnCoUkProxyManager1C::EnableActionKontrolProductComPort(CallbackProxyManager1KontrolProductComPort aCallback, void* aPtr)
{
    iCallbackKontrolProductComPort = aCallback;
    iPtrKontrolProductComPort = aPtr;
    DvServiceLinnCoUkProxyManager1::EnableActionKontrolProductComPort();
}

void DvServiceLinnCoUkProxyManager1C::EnableActionSetKontrolProductComPort(CallbackProxyManager1SetKontrolProductComPort aCallback, void* aPtr)
{
    iCallbackSetKontrolProductComPort = aCallback;
    iPtrSetKontrolProductComPort = aPtr;
    DvServiceLinnCoUkProxyManager1::EnableActionSetKontrolProductComPort();
}

void DvServiceLinnCoUkProxyManager1C::EnableActionDiscPlayerConnected(CallbackProxyManager1DiscPlayerConnected aCallback, void* aPtr)
{
    iCallbackDiscPlayerConnected = aCallback;
    iPtrDiscPlayerConnected = aPtr;
    DvServiceLinnCoUkProxyManager1::EnableActionDiscPlayerConnected();
}

void DvServiceLinnCoUkProxyManager1C::EnableActionSetDiscPlayerConnected(CallbackProxyManager1SetDiscPlayerConnected aCallback, void* aPtr)
{
    iCallbackSetDiscPlayerConnected = aCallback;
    iPtrSetDiscPlayerConnected = aPtr;
    DvServiceLinnCoUkProxyManager1::EnableActionSetDiscPlayerConnected();
}

void DvServiceLinnCoUkProxyManager1C::EnableActionDiscPlayerComPort(CallbackProxyManager1DiscPlayerComPort aCallback, void* aPtr)
{
    iCallbackDiscPlayerComPort = aCallback;
    iPtrDiscPlayerComPort = aPtr;
    DvServiceLinnCoUkProxyManager1::EnableActionDiscPlayerComPort();
}

void DvServiceLinnCoUkProxyManager1C::EnableActionSetDiscPlayerComPort(CallbackProxyManager1SetDiscPlayerComPort aCallback, void* aPtr)
{
    iCallbackSetDiscPlayerComPort = aCallback;
    iPtrSetDiscPlayerComPort = aPtr;
    DvServiceLinnCoUkProxyManager1::EnableActionSetDiscPlayerComPort();
}

void DvServiceLinnCoUkProxyManager1C::EnableActionTestKontrolProductConnection(CallbackProxyManager1TestKontrolProductConnection aCallback, void* aPtr)
{
    iCallbackTestKontrolProductConnection = aCallback;
    iPtrTestKontrolProductConnection = aPtr;
    DvServiceLinnCoUkProxyManager1::EnableActionTestKontrolProductConnection();
}

void DvServiceLinnCoUkProxyManager1C::EnableActionTestDiscPlayerConnection(CallbackProxyManager1TestDiscPlayerConnection aCallback, void* aPtr)
{
    iCallbackTestDiscPlayerConnection = aCallback;
    iPtrTestDiscPlayerConnection = aPtr;
    DvServiceLinnCoUkProxyManager1::EnableActionTestDiscPlayerConnection();
}

void DvServiceLinnCoUkProxyManager1C::KontrolProductConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConnected)
{
    char* aConnected;
    ASSERT(iCallbackKontrolProductConnected != NULL);
    if (0 != iCallbackKontrolProductConnected(iPtrKontrolProductConnected, aVersion, &aConnected)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaConnected((const TChar*)aConnected);
    ZappFreeExternal(aConnected);
    aaConnected.Write(bufaConnected);
    aaConnected.WriteFlush();
    aResponse.End();
}

void DvServiceLinnCoUkProxyManager1C::SetKontrolProductConnected(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaConnected)
{
    ASSERT(iCallbackSetKontrolProductConnected != NULL);
    if (0 != iCallbackSetKontrolProductConnected(iPtrSetKontrolProductConnected, aVersion, (const char*)aaConnected.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProxyManager1C::KontrolProductComPort(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPort)
{
    uint32_t aPort;
    ASSERT(iCallbackKontrolProductComPort != NULL);
    if (0 != iCallbackKontrolProductComPort(iPtrKontrolProductComPort, aVersion, &aPort)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaPort.Write(aPort);
    aResponse.End();
}

void DvServiceLinnCoUkProxyManager1C::SetKontrolProductComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaConnected)
{
    ASSERT(iCallbackSetKontrolProductComPort != NULL);
    if (0 != iCallbackSetKontrolProductComPort(iPtrSetKontrolProductComPort, aVersion, aaConnected)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProxyManager1C::DiscPlayerConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConnected)
{
    char* aConnected;
    ASSERT(iCallbackDiscPlayerConnected != NULL);
    if (0 != iCallbackDiscPlayerConnected(iPtrDiscPlayerConnected, aVersion, &aConnected)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaConnected((const TChar*)aConnected);
    ZappFreeExternal(aConnected);
    aaConnected.Write(bufaConnected);
    aaConnected.WriteFlush();
    aResponse.End();
}

void DvServiceLinnCoUkProxyManager1C::SetDiscPlayerConnected(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaConnected)
{
    ASSERT(iCallbackSetDiscPlayerConnected != NULL);
    if (0 != iCallbackSetDiscPlayerConnected(iPtrSetDiscPlayerConnected, aVersion, (const char*)aaConnected.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProxyManager1C::DiscPlayerComPort(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPort)
{
    uint32_t aPort;
    ASSERT(iCallbackDiscPlayerComPort != NULL);
    if (0 != iCallbackDiscPlayerComPort(iPtrDiscPlayerComPort, aVersion, &aPort)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaPort.Write(aPort);
    aResponse.End();
}

void DvServiceLinnCoUkProxyManager1C::SetDiscPlayerComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaConnected)
{
    ASSERT(iCallbackSetDiscPlayerComPort != NULL);
    if (0 != iCallbackSetDiscPlayerComPort(iPtrSetDiscPlayerComPort, aVersion, aaConnected)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkProxyManager1C::TestKontrolProductConnection(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaResult)
{
    uint32_t aResult;
    ASSERT(iCallbackTestKontrolProductConnection != NULL);
    if (0 != iCallbackTestKontrolProductConnection(iPtrTestKontrolProductConnection, aVersion, &aResult)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaResult.Write((aResult!=0));
    aResponse.End();
}

void DvServiceLinnCoUkProxyManager1C::TestDiscPlayerConnection(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaResult)
{
    uint32_t aResult;
    ASSERT(iCallbackTestDiscPlayerConnection != NULL);
    if (0 != iCallbackTestDiscPlayerConnection(iPtrTestDiscPlayerConnection, aVersion, &aResult)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaResult.Write((aResult!=0));
    aResponse.End();
}



THandle DvServiceLinnCoUkProxyManager1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkProxyManager1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkProxyManager1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService);
}

void DvServiceLinnCoUkProxyManager1EnableActionKontrolProductConnected(THandle aService, CallbackProxyManager1KontrolProductConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->EnableActionKontrolProductConnected(aCallback, aPtr);
}

void DvServiceLinnCoUkProxyManager1EnableActionSetKontrolProductConnected(THandle aService, CallbackProxyManager1SetKontrolProductConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->EnableActionSetKontrolProductConnected(aCallback, aPtr);
}

void DvServiceLinnCoUkProxyManager1EnableActionKontrolProductComPort(THandle aService, CallbackProxyManager1KontrolProductComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->EnableActionKontrolProductComPort(aCallback, aPtr);
}

void DvServiceLinnCoUkProxyManager1EnableActionSetKontrolProductComPort(THandle aService, CallbackProxyManager1SetKontrolProductComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->EnableActionSetKontrolProductComPort(aCallback, aPtr);
}

void DvServiceLinnCoUkProxyManager1EnableActionDiscPlayerConnected(THandle aService, CallbackProxyManager1DiscPlayerConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->EnableActionDiscPlayerConnected(aCallback, aPtr);
}

void DvServiceLinnCoUkProxyManager1EnableActionSetDiscPlayerConnected(THandle aService, CallbackProxyManager1SetDiscPlayerConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->EnableActionSetDiscPlayerConnected(aCallback, aPtr);
}

void DvServiceLinnCoUkProxyManager1EnableActionDiscPlayerComPort(THandle aService, CallbackProxyManager1DiscPlayerComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->EnableActionDiscPlayerComPort(aCallback, aPtr);
}

void DvServiceLinnCoUkProxyManager1EnableActionSetDiscPlayerComPort(THandle aService, CallbackProxyManager1SetDiscPlayerComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->EnableActionSetDiscPlayerComPort(aCallback, aPtr);
}

void DvServiceLinnCoUkProxyManager1EnableActionTestKontrolProductConnection(THandle aService, CallbackProxyManager1TestKontrolProductConnection aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->EnableActionTestKontrolProductConnection(aCallback, aPtr);
}

void DvServiceLinnCoUkProxyManager1EnableActionTestDiscPlayerConnection(THandle aService, CallbackProxyManager1TestDiscPlayerConnection aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->EnableActionTestDiscPlayerConnection(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkProxyManager1SetPropertyKontrolProductConnected(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->SetPropertyKontrolProductConnected(buf);
    return 0;
}

void DvServiceLinnCoUkProxyManager1GetPropertyKontrolProductConnected(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->GetPropertyKontrolProductConnected(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkProxyManager1SetPropertyKontrolProductComPort(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->SetPropertyKontrolProductComPort(aValue);
    return 0;
}

void DvServiceLinnCoUkProxyManager1GetPropertyKontrolProductComPort(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->GetPropertyKontrolProductComPort(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkProxyManager1SetPropertyDiscPlayerConnected(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->SetPropertyDiscPlayerConnected(buf);
    return 0;
}

void DvServiceLinnCoUkProxyManager1GetPropertyDiscPlayerConnected(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->GetPropertyDiscPlayerConnected(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkProxyManager1SetPropertyDiscPlayerComPort(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->SetPropertyDiscPlayerComPort(aValue);
    return 0;
}

void DvServiceLinnCoUkProxyManager1GetPropertyDiscPlayerComPort(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkProxyManager1C*>(aService)->GetPropertyDiscPlayerComPort(val);
    *aValue = val;
}

