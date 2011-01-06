#include "DvLinnCoUkProxyManager1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderLinnCoUkProxyManager1C : public DvProvider
{
public:
    DvProviderLinnCoUkProxyManager1C(DvDeviceC aDevice);
    TBool SetPropertyKontrolProductConnected(const Brx& aValue);
    void GetPropertyKontrolProductConnected(Brhz& aValue);
    TBool SetPropertyKontrolProductComPort(TUint aValue);
    void GetPropertyKontrolProductComPort(TUint& aValue);
    TBool SetPropertyDiscPlayerConnected(const Brx& aValue);
    void GetPropertyDiscPlayerConnected(Brhz& aValue);
    TBool SetPropertyDiscPlayerComPort(TUint aValue);
    void GetPropertyDiscPlayerComPort(TUint& aValue);
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
    void DoKontrolProductConnected(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetKontrolProductConnected(IDviInvocation& aInvocation, TUint aVersion);
    void DoKontrolProductComPort(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetKontrolProductComPort(IDviInvocation& aInvocation, TUint aVersion);
    void DoDiscPlayerConnected(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDiscPlayerConnected(IDviInvocation& aInvocation, TUint aVersion);
    void DoDiscPlayerComPort(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDiscPlayerComPort(IDviInvocation& aInvocation, TUint aVersion);
    void DoTestKontrolProductConnection(IDviInvocation& aInvocation, TUint aVersion);
    void DoTestDiscPlayerConnection(IDviInvocation& aInvocation, TUint aVersion);
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
    PropertyString* iPropertyKontrolProductConnected;
    PropertyUint* iPropertyKontrolProductComPort;
    PropertyString* iPropertyDiscPlayerConnected;
    PropertyUint* iPropertyDiscPlayerComPort;
};

DvProviderLinnCoUkProxyManager1C::DvProviderLinnCoUkProxyManager1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "ProxyManager", 1)
{
    
    TChar** allowedValues;
    TUint index;
    index = 0;
    allowedValues = new TChar*[11];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"Klimax Kontrol";
    allowedValues[index++] = (TChar*)"Akurate Kontrol";
    allowedValues[index++] = (TChar*)"Kisto";
    allowedValues[index++] = (TChar*)"Kinos";
    allowedValues[index++] = (TChar*)"Majik Kontrol";
    allowedValues[index++] = (TChar*)"Majik-I";
    allowedValues[index++] = (TChar*)"Unidisk SC";
    allowedValues[index++] = (TChar*)"Classik Movie";
    allowedValues[index++] = (TChar*)"Classik Music";
    allowedValues[index++] = (TChar*)"Roomamp 2";
    iPropertyKontrolProductConnected = new PropertyString(new ParameterString("KontrolProductConnected", allowedValues, 11));
    delete[] allowedValues;
    iService->AddProperty(iPropertyKontrolProductConnected); // passes ownership
    iPropertyKontrolProductComPort = new PropertyUint(new ParameterUint("KontrolProductComPort"));
    iService->AddProperty(iPropertyKontrolProductComPort); // passes ownership
    index = 0;
    allowedValues = new TChar*[9];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"CD12";
    allowedValues[index++] = (TChar*)"Akurate CD";
    allowedValues[index++] = (TChar*)"Unidisk 1.1";
    allowedValues[index++] = (TChar*)"Unidisk 2.1";
    allowedValues[index++] = (TChar*)"Majik CD";
    allowedValues[index++] = (TChar*)"Unidisk SC";
    allowedValues[index++] = (TChar*)"Classik Movie";
    allowedValues[index++] = (TChar*)"Classik Music";
    iPropertyDiscPlayerConnected = new PropertyString(new ParameterString("DiscPlayerConnected", allowedValues, 9));
    delete[] allowedValues;
    iService->AddProperty(iPropertyDiscPlayerConnected); // passes ownership
    iPropertyDiscPlayerComPort = new PropertyUint(new ParameterUint("DiscPlayerComPort"));
    iService->AddProperty(iPropertyDiscPlayerComPort); // passes ownership
}

TBool DvProviderLinnCoUkProxyManager1C::SetPropertyKontrolProductConnected(const Brx& aValue)
{
    return SetPropertyString(*iPropertyKontrolProductConnected, aValue);
}

void DvProviderLinnCoUkProxyManager1C::GetPropertyKontrolProductConnected(Brhz& aValue)
{
    aValue.Set(iPropertyKontrolProductConnected->Value());
}

TBool DvProviderLinnCoUkProxyManager1C::SetPropertyKontrolProductComPort(TUint aValue)
{
    return SetPropertyUint(*iPropertyKontrolProductComPort, aValue);
}

void DvProviderLinnCoUkProxyManager1C::GetPropertyKontrolProductComPort(TUint& aValue)
{
    aValue = iPropertyKontrolProductComPort->Value();
}

TBool DvProviderLinnCoUkProxyManager1C::SetPropertyDiscPlayerConnected(const Brx& aValue)
{
    return SetPropertyString(*iPropertyDiscPlayerConnected, aValue);
}

void DvProviderLinnCoUkProxyManager1C::GetPropertyDiscPlayerConnected(Brhz& aValue)
{
    aValue.Set(iPropertyDiscPlayerConnected->Value());
}

TBool DvProviderLinnCoUkProxyManager1C::SetPropertyDiscPlayerComPort(TUint aValue)
{
    return SetPropertyUint(*iPropertyDiscPlayerComPort, aValue);
}

void DvProviderLinnCoUkProxyManager1C::GetPropertyDiscPlayerComPort(TUint& aValue)
{
    aValue = iPropertyDiscPlayerComPort->Value();
}

void DvProviderLinnCoUkProxyManager1C::EnableActionKontrolProductConnected(CallbackProxyManager1KontrolProductConnected aCallback, void* aPtr)
{
    iCallbackKontrolProductConnected = aCallback;
    iPtrKontrolProductConnected = aPtr;
    Zapp::Action* action = new Zapp::Action("KontrolProductConnected");
    action->AddOutputParameter(new ParameterRelated("aConnected", *iPropertyKontrolProductConnected));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1C::DoKontrolProductConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1C::EnableActionSetKontrolProductConnected(CallbackProxyManager1SetKontrolProductConnected aCallback, void* aPtr)
{
    iCallbackSetKontrolProductConnected = aCallback;
    iPtrSetKontrolProductConnected = aPtr;
    Zapp::Action* action = new Zapp::Action("SetKontrolProductConnected");
    action->AddInputParameter(new ParameterRelated("aConnected", *iPropertyKontrolProductConnected));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1C::DoSetKontrolProductConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1C::EnableActionKontrolProductComPort(CallbackProxyManager1KontrolProductComPort aCallback, void* aPtr)
{
    iCallbackKontrolProductComPort = aCallback;
    iPtrKontrolProductComPort = aPtr;
    Zapp::Action* action = new Zapp::Action("KontrolProductComPort");
    action->AddOutputParameter(new ParameterRelated("aPort", *iPropertyKontrolProductComPort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1C::DoKontrolProductComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1C::EnableActionSetKontrolProductComPort(CallbackProxyManager1SetKontrolProductComPort aCallback, void* aPtr)
{
    iCallbackSetKontrolProductComPort = aCallback;
    iPtrSetKontrolProductComPort = aPtr;
    Zapp::Action* action = new Zapp::Action("SetKontrolProductComPort");
    action->AddInputParameter(new ParameterRelated("aConnected", *iPropertyKontrolProductComPort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1C::DoSetKontrolProductComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1C::EnableActionDiscPlayerConnected(CallbackProxyManager1DiscPlayerConnected aCallback, void* aPtr)
{
    iCallbackDiscPlayerConnected = aCallback;
    iPtrDiscPlayerConnected = aPtr;
    Zapp::Action* action = new Zapp::Action("DiscPlayerConnected");
    action->AddOutputParameter(new ParameterRelated("aConnected", *iPropertyDiscPlayerConnected));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1C::DoDiscPlayerConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1C::EnableActionSetDiscPlayerConnected(CallbackProxyManager1SetDiscPlayerConnected aCallback, void* aPtr)
{
    iCallbackSetDiscPlayerConnected = aCallback;
    iPtrSetDiscPlayerConnected = aPtr;
    Zapp::Action* action = new Zapp::Action("SetDiscPlayerConnected");
    action->AddInputParameter(new ParameterRelated("aConnected", *iPropertyDiscPlayerConnected));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1C::DoSetDiscPlayerConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1C::EnableActionDiscPlayerComPort(CallbackProxyManager1DiscPlayerComPort aCallback, void* aPtr)
{
    iCallbackDiscPlayerComPort = aCallback;
    iPtrDiscPlayerComPort = aPtr;
    Zapp::Action* action = new Zapp::Action("DiscPlayerComPort");
    action->AddOutputParameter(new ParameterRelated("aPort", *iPropertyDiscPlayerComPort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1C::DoDiscPlayerComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1C::EnableActionSetDiscPlayerComPort(CallbackProxyManager1SetDiscPlayerComPort aCallback, void* aPtr)
{
    iCallbackSetDiscPlayerComPort = aCallback;
    iPtrSetDiscPlayerComPort = aPtr;
    Zapp::Action* action = new Zapp::Action("SetDiscPlayerComPort");
    action->AddInputParameter(new ParameterRelated("aConnected", *iPropertyDiscPlayerComPort));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1C::DoSetDiscPlayerComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1C::EnableActionTestKontrolProductConnection(CallbackProxyManager1TestKontrolProductConnection aCallback, void* aPtr)
{
    iCallbackTestKontrolProductConnection = aCallback;
    iPtrTestKontrolProductConnection = aPtr;
    Zapp::Action* action = new Zapp::Action("TestKontrolProductConnection");
    action->AddOutputParameter(new ParameterBool("aResult"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1C::DoTestKontrolProductConnection);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1C::EnableActionTestDiscPlayerConnection(CallbackProxyManager1TestDiscPlayerConnection aCallback, void* aPtr)
{
    iCallbackTestDiscPlayerConnection = aCallback;
    iPtrTestDiscPlayerConnection = aPtr;
    Zapp::Action* action = new Zapp::Action("TestDiscPlayerConnection");
    action->AddOutputParameter(new ParameterBool("aResult"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkProxyManager1C::DoTestDiscPlayerConnection);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkProxyManager1C::DoKontrolProductConnected(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aConnected;
    ASSERT(iCallbackKontrolProductConnected != NULL);
    if (0 != iCallbackKontrolProductConnected(iPtrKontrolProductConnected, aVersion, &aConnected)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaConnected(aInvocation, "aConnected");
    resp.Start();
    Brhz bufaConnected((const TChar*)aConnected);
    ZappFreeExternal(aConnected);
    respaConnected.Write(bufaConnected);
    respaConnected.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkProxyManager1C::DoSetKontrolProductConnected(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aConnected;
    aInvocation.InvocationReadString("aConnected", aConnected);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetKontrolProductConnected != NULL);
    if (0 != iCallbackSetKontrolProductConnected(iPtrSetKontrolProductConnected, aVersion, (const char*)aConnected.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkProxyManager1C::DoKontrolProductComPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aPort;
    ASSERT(iCallbackKontrolProductComPort != NULL);
    if (0 != iCallbackKontrolProductComPort(iPtrKontrolProductComPort, aVersion, &aPort)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaPort(aInvocation, "aPort");
    resp.Start();
    respaPort.Write(aPort);
    resp.End();
}

void DvProviderLinnCoUkProxyManager1C::DoSetKontrolProductComPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aConnected = aInvocation.InvocationReadUint("aConnected");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetKontrolProductComPort != NULL);
    if (0 != iCallbackSetKontrolProductComPort(iPtrSetKontrolProductComPort, aVersion, aConnected)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkProxyManager1C::DoDiscPlayerConnected(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aConnected;
    ASSERT(iCallbackDiscPlayerConnected != NULL);
    if (0 != iCallbackDiscPlayerConnected(iPtrDiscPlayerConnected, aVersion, &aConnected)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaConnected(aInvocation, "aConnected");
    resp.Start();
    Brhz bufaConnected((const TChar*)aConnected);
    ZappFreeExternal(aConnected);
    respaConnected.Write(bufaConnected);
    respaConnected.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkProxyManager1C::DoSetDiscPlayerConnected(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aConnected;
    aInvocation.InvocationReadString("aConnected", aConnected);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetDiscPlayerConnected != NULL);
    if (0 != iCallbackSetDiscPlayerConnected(iPtrSetDiscPlayerConnected, aVersion, (const char*)aConnected.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkProxyManager1C::DoDiscPlayerComPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aPort;
    ASSERT(iCallbackDiscPlayerComPort != NULL);
    if (0 != iCallbackDiscPlayerComPort(iPtrDiscPlayerComPort, aVersion, &aPort)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaPort(aInvocation, "aPort");
    resp.Start();
    respaPort.Write(aPort);
    resp.End();
}

void DvProviderLinnCoUkProxyManager1C::DoSetDiscPlayerComPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aConnected = aInvocation.InvocationReadUint("aConnected");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetDiscPlayerComPort != NULL);
    if (0 != iCallbackSetDiscPlayerComPort(iPtrSetDiscPlayerComPort, aVersion, aConnected)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkProxyManager1C::DoTestKontrolProductConnection(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aResult;
    ASSERT(iCallbackTestKontrolProductConnection != NULL);
    if (0 != iCallbackTestKontrolProductConnection(iPtrTestKontrolProductConnection, aVersion, &aResult)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaResult(aInvocation, "aResult");
    resp.Start();
    respaResult.Write((aResult!=0));
    resp.End();
}

void DvProviderLinnCoUkProxyManager1C::DoTestDiscPlayerConnection(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aResult;
    ASSERT(iCallbackTestDiscPlayerConnection != NULL);
    if (0 != iCallbackTestDiscPlayerConnection(iPtrTestDiscPlayerConnection, aVersion, &aResult)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaResult(aInvocation, "aResult");
    resp.Start();
    respaResult.Write((aResult!=0));
    resp.End();
}



THandle DvProviderLinnCoUkProxyManager1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkProxyManager1C(aDevice);
}

void DvProviderLinnCoUkProxyManager1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider);
}

void DvProviderLinnCoUkProxyManager1EnableActionKontrolProductConnected(THandle aProvider, CallbackProxyManager1KontrolProductConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->EnableActionKontrolProductConnected(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductConnected(THandle aProvider, CallbackProxyManager1SetKontrolProductConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->EnableActionSetKontrolProductConnected(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionKontrolProductComPort(THandle aProvider, CallbackProxyManager1KontrolProductComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->EnableActionKontrolProductComPort(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductComPort(THandle aProvider, CallbackProxyManager1SetKontrolProductComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->EnableActionSetKontrolProductComPort(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerConnected(THandle aProvider, CallbackProxyManager1DiscPlayerConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->EnableActionDiscPlayerConnected(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerConnected(THandle aProvider, CallbackProxyManager1SetDiscPlayerConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->EnableActionSetDiscPlayerConnected(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerComPort(THandle aProvider, CallbackProxyManager1DiscPlayerComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->EnableActionDiscPlayerComPort(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerComPort(THandle aProvider, CallbackProxyManager1SetDiscPlayerComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->EnableActionSetDiscPlayerComPort(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionTestKontrolProductConnection(THandle aProvider, CallbackProxyManager1TestKontrolProductConnection aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->EnableActionTestKontrolProductConnection(aCallback, aPtr);
}

void DvProviderLinnCoUkProxyManager1EnableActionTestDiscPlayerConnection(THandle aProvider, CallbackProxyManager1TestDiscPlayerConnection aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->EnableActionTestDiscPlayerConnection(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkProxyManager1SetPropertyKontrolProductConnected(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->SetPropertyKontrolProductConnected(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProxyManager1GetPropertyKontrolProductConnected(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->GetPropertyKontrolProductConnected(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProxyManager1SetPropertyKontrolProductComPort(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->SetPropertyKontrolProductComPort(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProxyManager1GetPropertyKontrolProductComPort(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->GetPropertyKontrolProductComPort(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkProxyManager1SetPropertyDiscPlayerConnected(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->SetPropertyDiscPlayerConnected(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProxyManager1GetPropertyDiscPlayerConnected(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->GetPropertyDiscPlayerConnected(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkProxyManager1SetPropertyDiscPlayerComPort(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->SetPropertyDiscPlayerComPort(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkProxyManager1GetPropertyDiscPlayerComPort(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkProxyManager1C*>(aProvider)->GetPropertyDiscPlayerComPort(val);
    *aValue = val;
}

