#include "DvLinnCoUkConfiguration1.h"
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

class DvProviderLinnCoUkConfiguration1C : public DvProvider
{
public:
    DvProviderLinnCoUkConfiguration1C(DvDeviceC aDevice);
    TBool SetPropertyConfigurationXml(const Brx& aValue);
    void GetPropertyConfigurationXml(Brhz& aValue);
    TBool SetPropertyParameterXml(const Brx& aValue);
    void GetPropertyParameterXml(Brhz& aValue);
    void EnableActionConfigurationXml(CallbackConfiguration1ConfigurationXml aCallback, void* aPtr);
    void EnableActionParameterXml(CallbackConfiguration1ParameterXml aCallback, void* aPtr);
    void EnableActionSetParameter(CallbackConfiguration1SetParameter aCallback, void* aPtr);
private:
    void DoConfigurationXml(IDviInvocation& aInvocation, TUint aVersion);
    void DoParameterXml(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetParameter(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackConfiguration1ConfigurationXml iCallbackConfigurationXml;
    void* iPtrConfigurationXml;
    CallbackConfiguration1ParameterXml iCallbackParameterXml;
    void* iPtrParameterXml;
    CallbackConfiguration1SetParameter iCallbackSetParameter;
    void* iPtrSetParameter;
    PropertyString* iPropertyConfigurationXml;
    PropertyString* iPropertyParameterXml;
};

DvProviderLinnCoUkConfiguration1C::DvProviderLinnCoUkConfiguration1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Configuration", 1)
{
    
    iPropertyConfigurationXml = new PropertyString(new ParameterString("ConfigurationXml"));
    iService->AddProperty(iPropertyConfigurationXml); // passes ownership
    iPropertyParameterXml = new PropertyString(new ParameterString("ParameterXml"));
    iService->AddProperty(iPropertyParameterXml); // passes ownership
}

TBool DvProviderLinnCoUkConfiguration1C::SetPropertyConfigurationXml(const Brx& aValue)
{
    return SetPropertyString(*iPropertyConfigurationXml, aValue);
}

void DvProviderLinnCoUkConfiguration1C::GetPropertyConfigurationXml(Brhz& aValue)
{
    aValue.Set(iPropertyConfigurationXml->Value());
}

TBool DvProviderLinnCoUkConfiguration1C::SetPropertyParameterXml(const Brx& aValue)
{
    return SetPropertyString(*iPropertyParameterXml, aValue);
}

void DvProviderLinnCoUkConfiguration1C::GetPropertyParameterXml(Brhz& aValue)
{
    aValue.Set(iPropertyParameterXml->Value());
}

void DvProviderLinnCoUkConfiguration1C::EnableActionConfigurationXml(CallbackConfiguration1ConfigurationXml aCallback, void* aPtr)
{
    iCallbackConfigurationXml = aCallback;
    iPtrConfigurationXml = aPtr;
    Zapp::Action* action = new Zapp::Action("ConfigurationXml");
    action->AddOutputParameter(new ParameterRelated("aConfigurationXml", *iPropertyConfigurationXml));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkConfiguration1C::DoConfigurationXml);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkConfiguration1C::EnableActionParameterXml(CallbackConfiguration1ParameterXml aCallback, void* aPtr)
{
    iCallbackParameterXml = aCallback;
    iPtrParameterXml = aPtr;
    Zapp::Action* action = new Zapp::Action("ParameterXml");
    action->AddOutputParameter(new ParameterRelated("aParameterXml", *iPropertyParameterXml));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkConfiguration1C::DoParameterXml);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkConfiguration1C::EnableActionSetParameter(CallbackConfiguration1SetParameter aCallback, void* aPtr)
{
    iCallbackSetParameter = aCallback;
    iPtrSetParameter = aPtr;
    Zapp::Action* action = new Zapp::Action("SetParameter");
    action->AddInputParameter(new ParameterString("aTarget"));
    action->AddInputParameter(new ParameterString("aName"));
    action->AddInputParameter(new ParameterString("aValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkConfiguration1C::DoSetParameter);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkConfiguration1C::DoConfigurationXml(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aConfigurationXml;
    ASSERT(iCallbackConfigurationXml != NULL);
    if (0 != iCallbackConfigurationXml(iPtrConfigurationXml, aVersion, &aConfigurationXml)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaConfigurationXml(aInvocation, "aConfigurationXml");
    resp.Start();
    Brhz bufaConfigurationXml((const TChar*)aConfigurationXml);
    ZappFreeExternal(aConfigurationXml);
    respaConfigurationXml.Write(bufaConfigurationXml);
    respaConfigurationXml.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkConfiguration1C::DoParameterXml(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aParameterXml;
    ASSERT(iCallbackParameterXml != NULL);
    if (0 != iCallbackParameterXml(iPtrParameterXml, aVersion, &aParameterXml)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaParameterXml(aInvocation, "aParameterXml");
    resp.Start();
    Brhz bufaParameterXml((const TChar*)aParameterXml);
    ZappFreeExternal(aParameterXml);
    respaParameterXml.Write(bufaParameterXml);
    respaParameterXml.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkConfiguration1C::DoSetParameter(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aTarget;
    aInvocation.InvocationReadString("aTarget", aTarget);
    Brhz aName;
    aInvocation.InvocationReadString("aName", aName);
    Brhz aValue;
    aInvocation.InvocationReadString("aValue", aValue);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetParameter != NULL);
    if (0 != iCallbackSetParameter(iPtrSetParameter, aVersion, (const char*)aTarget.Ptr(), (const char*)aName.Ptr(), (const char*)aValue.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}



THandle DvProviderLinnCoUkConfiguration1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkConfiguration1C(aDevice);
}

void DvProviderLinnCoUkConfiguration1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkConfiguration1C*>(aProvider);
}

void DvProviderLinnCoUkConfiguration1EnableActionConfigurationXml(THandle aProvider, CallbackConfiguration1ConfigurationXml aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkConfiguration1C*>(aProvider)->EnableActionConfigurationXml(aCallback, aPtr);
}

void DvProviderLinnCoUkConfiguration1EnableActionParameterXml(THandle aProvider, CallbackConfiguration1ParameterXml aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkConfiguration1C*>(aProvider)->EnableActionParameterXml(aCallback, aPtr);
}

void DvProviderLinnCoUkConfiguration1EnableActionSetParameter(THandle aProvider, CallbackConfiguration1SetParameter aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkConfiguration1C*>(aProvider)->EnableActionSetParameter(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkConfiguration1SetPropertyConfigurationXml(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkConfiguration1C*>(aProvider)->SetPropertyConfigurationXml(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkConfiguration1GetPropertyConfigurationXml(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkConfiguration1C*>(aProvider)->GetPropertyConfigurationXml(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkConfiguration1SetPropertyParameterXml(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkConfiguration1C*>(aProvider)->SetPropertyParameterXml(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkConfiguration1GetPropertyParameterXml(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkConfiguration1C*>(aProvider)->GetPropertyParameterXml(buf);
    *aValue = (char*)buf.Transfer();
}

