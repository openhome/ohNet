#include <C/DvLinnCoUkProxyManager1.h>
#include <Core/DvLinnCoUkProxyManager1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkProxyManager1C : public DvProviderLinnCoUkProxyManager1
{
public:
    DvProviderLinnCoUkProxyManager1C(DvDevice& aDevice);
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

DvProviderLinnCoUkProxyManager1C::DvProviderLinnCoUkProxyManager1C(DvDevice& aDevice)
    : DvProviderLinnCoUkProxyManager1(aDevice)
{
}

void DvProviderLinnCoUkProxyManager1C::EnableActionKontrolProductConnected(CallbackProxyManager1KontrolProductConnected aCallback, void* aPtr)
{
    iCallbackKontrolProductConnected = aCallback;
    iPtrKontrolProductConnected = aPtr;
    DvProviderLinnCoUkProxyManager1::EnableActionKontrolProductConnected();
}

void DvProviderLinnCoUkProxyManager1C::EnableActionSetKontrolProductConnected(CallbackProxyManager1SetKontrolProductConnected aCallback, void* aPtr)
{
    iCallbackSetKontrolProductConnected = aCallback;
    iPtrSetKontrolProductConnected = aPtr;
    DvProviderLinnCoUkProxyManager1::EnableActionSetKontrolProductConnected();
}

void DvProviderLinnCoUkProxyManager1C::EnableActionKontrolProductComPort(CallbackProxyManager1KontrolProductComPort aCallback, void* aPtr)
{
    iCallbackKontrolProductComPort = aCallback;
    iPtrKontrolProductComPort = aPtr;
    DvProviderLinnCoUkProxyManager1::EnableActionKontrolProductComPort();
}

void DvProviderLinnCoUkProxyManager1C::EnableActionSetKontrolProductComPort(CallbackProxyManager1SetKontrolProductComPort aCallback, void* aPtr)
{
    iCallbackSetKontrolProductComPort = aCallback;
    iPtrSetKontrolProductComPort = aPtr;
    DvProviderLinnCoUkProxyManager1::EnableActionSetKontrolProductComPort();
}

void DvProviderLinnCoUkProxyManager1C::EnableActionDiscPlayerConnected(CallbackProxyManager1DiscPlayerConnected aCallback, void* aPtr)
{
    iCallbackDiscPlayerConnected = aCallback;
    iPtrDiscPlayerConnected = aPtr;
    DvProviderLinnCoUkProxyManager1::EnableActionDiscPlayerConnected();
}

void DvProviderLinnCoUkProxyManager1C::EnableActionSetDiscPlayerConnected(CallbackProxyManager1SetDiscPlayerConnected aCallback, void* aPtr)
{
    iCallbackSetDiscPlayerConnected = aCallback;
    iPtrSetDiscPlayerConnected = aPtr;
    DvProviderLinnCoUkProxyManager1::EnableActionSetDiscPlayerConnected();
}

void DvProviderLinnCoUkProxyManager1C::EnableActionDiscPlayerComPort(CallbackProxyManager1DiscPlayerComPort aCallback, void* aPtr)
{
    iCallbackDiscPlayerComPort = aCallback;
    iPtrDiscPlayerComPort = aPtr;
    DvProviderLinnCoUkProxyManager1::EnableActionDiscPlayerComPort();
}

void DvProviderLinnCoUkProxyManager1C::EnableActionSetDiscPlayerComPort(CallbackProxyManager1SetDiscPlayerComPort aCallback, void* aPtr)
{
    iCallbackSetDiscPlayerComPort = aCallback;
    iPtrSetDiscPlayerComPort = aPtr;
    DvProviderLinnCoUkProxyManager1::EnableActionSetDiscPlayerComPort();
}

void DvProviderLinnCoUkProxyManager1C::EnableActionTestKontrolProductConnection(CallbackProxyManager1TestKontrolProductConnection aCallback, void* aPtr)
{
    iCallbackTestKontrolProductConnection = aCallback;
    iPtrTestKontrolProductConnection = aPtr;
    DvProviderLinnCoUkProxyManager1::EnableActionTestKontrolProductConnection();
}

void DvProviderLinnCoUkProxyManager1C::EnableActionTestDiscPlayerConnection(CallbackProxyManager1TestDiscPlayerConnection aCallback, void* aPtr)
{
    iCallbackTestDiscPlayerConnection = aCallback;
    iPtrTestDiscPlayerConnection = aPtr;
    DvProviderLinnCoUkProxyManager1::EnableActionTestDiscPlayerConnection();
}

void DvProviderLinnCoUkProxyManager1C::KontrolProductConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConnected)
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

void DvProviderLinnCoUkProxyManager1C::SetKontrolProductConnected(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaConnected)
{
    ASSERT(iCallbackSetKontrolProductConnected != NULL);
    if (0 != iCallbackSetKontrolProductConnected(iPtrSetKontrolProductConnected, aVersion, (const char*)aaConnected.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProxyManager1C::KontrolProductComPort(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPort)
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

void DvProviderLinnCoUkProxyManager1C::SetKontrolProductComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaConnected)
{
    ASSERT(iCallbackSetKontrolProductComPort != NULL);
    if (0 != iCallbackSetKontrolProductComPort(iPtrSetKontrolProductComPort, aVersion, aaConnected)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProxyManager1C::DiscPlayerConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConnected)
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

void DvProviderLinnCoUkProxyManager1C::SetDiscPlayerConnected(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaConnected)
{
    ASSERT(iCallbackSetDiscPlayerConnected != NULL);
    if (0 != iCallbackSetDiscPlayerConnected(iPtrSetDiscPlayerConnected, aVersion, (const char*)aaConnected.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProxyManager1C::DiscPlayerComPort(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPort)
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

void DvProviderLinnCoUkProxyManager1C::SetDiscPlayerComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaConnected)
{
    ASSERT(iCallbackSetDiscPlayerComPort != NULL);
    if (0 != iCallbackSetDiscPlayerComPort(iPtrSetDiscPlayerComPort, aVersion, aaConnected)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkProxyManager1C::TestKontrolProductConnection(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaResult)
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

void DvProviderLinnCoUkProxyManager1C::TestDiscPlayerConnection(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaResult)
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



THandle DvProviderLinnCoUkProxyManager1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkProxyManager1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkProxyManager1Destroy(THandle aService)
{
    delete reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService);
}

void DvProviderLinnCoUkProxyManager1EnableActionKontrolProductConnected(THandle aService, CallbackProxyManager1KontrolProductConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->EnableActionKontrolProductConnected(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductConnected(THandle aService, CallbackProxyManager1SetKontrolProductConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->EnableActionSetKontrolProductConnected(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionKontrolProductComPort(THandle aService, CallbackProxyManager1KontrolProductComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->EnableActionKontrolProductComPort(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductComPort(THandle aService, CallbackProxyManager1SetKontrolProductComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->EnableActionSetKontrolProductComPort(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerConnected(THandle aService, CallbackProxyManager1DiscPlayerConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->EnableActionDiscPlayerConnected(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerConnected(THandle aService, CallbackProxyManager1SetDiscPlayerConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->EnableActionSetDiscPlayerConnected(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerComPort(THandle aService, CallbackProxyManager1DiscPlayerComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->EnableActionDiscPlayerComPort(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerComPort(THandle aService, CallbackProxyManager1SetDiscPlayerComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->EnableActionSetDiscPlayerComPort(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionTestKontrolProductConnection(THandle aService, CallbackProxyManager1TestKontrolProductConnection aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->EnableActionTestKontrolProductConnection(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionTestDiscPlayerConnection(THandle aService, CallbackProxyManager1TestDiscPlayerConnection aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->EnableActionTestDiscPlayerConnection(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkProxyManager1SetPropertyKontrolProductConnected(THandle aService, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->SetPropertyKontrolProductConnected(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProxyManager1GetPropertyKontrolProductConnected(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->GetPropertyKontrolProductConnected(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProxyManager1SetPropertyKontrolProductComPort(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->SetPropertyKontrolProductComPort(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProxyManager1GetPropertyKontrolProductComPort(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->GetPropertyKontrolProductComPort(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkProxyManager1SetPropertyDiscPlayerConnected(THandle aService, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->SetPropertyDiscPlayerConnected(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProxyManager1GetPropertyDiscPlayerConnected(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->GetPropertyDiscPlayerConnected(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProxyManager1SetPropertyDiscPlayerComPort(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->SetPropertyDiscPlayerComPort(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProxyManager1GetPropertyDiscPlayerComPort(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aService)->GetPropertyDiscPlayerComPort(val);
    *aValue = val;
}

