#include <C/DvLinnCoUkConfiguration1.h>
#include <Core/DvLinnCoUkConfiguration1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkConfiguration1C : public DvProviderLinnCoUkConfiguration1
{
public:
    DvProviderLinnCoUkConfiguration1C(DvDevice& aDevice);
    void EnableActionConfigurationXml(CallbackConfiguration1ConfigurationXml aCallback, void* aPtr);
    void EnableActionParameterXml(CallbackConfiguration1ParameterXml aCallback, void* aPtr);
    void EnableActionSetParameter(CallbackConfiguration1SetParameter aCallback, void* aPtr);
private:
    void ConfigurationXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConfigurationXml);
    void ParameterXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaParameterXml);
    void SetParameter(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaTarget, const Brx& aaName, const Brx& aaValue);
private:
    CallbackConfiguration1ConfigurationXml iCallbackConfigurationXml;
    void* iPtrConfigurationXml;
    CallbackConfiguration1ParameterXml iCallbackParameterXml;
    void* iPtrParameterXml;
    CallbackConfiguration1SetParameter iCallbackSetParameter;
    void* iPtrSetParameter;
};

DvProviderLinnCoUkConfiguration1C::DvProviderLinnCoUkConfiguration1C(DvDevice& aDevice)
    : DvProviderLinnCoUkConfiguration1(aDevice)
{
}

void DvProviderLinnCoUkConfiguration1C::EnableActionConfigurationXml(CallbackConfiguration1ConfigurationXml aCallback, void* aPtr)
{
    iCallbackConfigurationXml = aCallback;
    iPtrConfigurationXml = aPtr;
    DvProviderLinnCoUkConfiguration1::EnableActionConfigurationXml();
}

void DvProviderLinnCoUkConfiguration1C::EnableActionParameterXml(CallbackConfiguration1ParameterXml aCallback, void* aPtr)
{
    iCallbackParameterXml = aCallback;
    iPtrParameterXml = aPtr;
    DvProviderLinnCoUkConfiguration1::EnableActionParameterXml();
}

void DvProviderLinnCoUkConfiguration1C::EnableActionSetParameter(CallbackConfiguration1SetParameter aCallback, void* aPtr)
{
    iCallbackSetParameter = aCallback;
    iPtrSetParameter = aPtr;
    DvProviderLinnCoUkConfiguration1::EnableActionSetParameter();
}

void DvProviderLinnCoUkConfiguration1C::ConfigurationXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConfigurationXml)
{
    char* aConfigurationXml;
    ASSERT(iCallbackConfigurationXml != NULL);
    if (0 != iCallbackConfigurationXml(iPtrConfigurationXml, aVersion, &aConfigurationXml)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaConfigurationXml((const TChar*)aConfigurationXml);
    ZappFreeExternal(aConfigurationXml);
    aaConfigurationXml.Write(bufaConfigurationXml);
    aaConfigurationXml.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkConfiguration1C::ParameterXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaParameterXml)
{
    char* aParameterXml;
    ASSERT(iCallbackParameterXml != NULL);
    if (0 != iCallbackParameterXml(iPtrParameterXml, aVersion, &aParameterXml)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaParameterXml((const TChar*)aParameterXml);
    ZappFreeExternal(aParameterXml);
    aaParameterXml.Write(bufaParameterXml);
    aaParameterXml.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkConfiguration1C::SetParameter(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaTarget, const Brx& aaName, const Brx& aaValue)
{
    ASSERT(iCallbackSetParameter != NULL);
    if (0 != iCallbackSetParameter(iPtrSetParameter, aVersion, (const char*)aaTarget.Ptr(), (const char*)aaName.Ptr(), (const char*)aaValue.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvProviderLinnCoUkConfiguration1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkConfiguration1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
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

