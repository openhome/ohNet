#include <C/DvLinnCoUkConfiguration1.h>
#include <Core/DvLinnCoUkConfiguration1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkConfiguration1C : public DvServiceLinnCoUkConfiguration1
{
public:
    DvServiceLinnCoUkConfiguration1C(DvDevice& aDevice);
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

DvServiceLinnCoUkConfiguration1C::DvServiceLinnCoUkConfiguration1C(DvDevice& aDevice)
    : DvServiceLinnCoUkConfiguration1(aDevice)
{
}

void DvServiceLinnCoUkConfiguration1C::EnableActionConfigurationXml(CallbackConfiguration1ConfigurationXml aCallback, void* aPtr)
{
    iCallbackConfigurationXml = aCallback;
    iPtrConfigurationXml = aPtr;
    DvServiceLinnCoUkConfiguration1::EnableActionConfigurationXml();
}

void DvServiceLinnCoUkConfiguration1C::EnableActionParameterXml(CallbackConfiguration1ParameterXml aCallback, void* aPtr)
{
    iCallbackParameterXml = aCallback;
    iPtrParameterXml = aPtr;
    DvServiceLinnCoUkConfiguration1::EnableActionParameterXml();
}

void DvServiceLinnCoUkConfiguration1C::EnableActionSetParameter(CallbackConfiguration1SetParameter aCallback, void* aPtr)
{
    iCallbackSetParameter = aCallback;
    iPtrSetParameter = aPtr;
    DvServiceLinnCoUkConfiguration1::EnableActionSetParameter();
}

void DvServiceLinnCoUkConfiguration1C::ConfigurationXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaConfigurationXml)
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

void DvServiceLinnCoUkConfiguration1C::ParameterXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaParameterXml)
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

void DvServiceLinnCoUkConfiguration1C::SetParameter(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaTarget, const Brx& aaName, const Brx& aaValue)
{
    ASSERT(iCallbackSetParameter != NULL);
    if (0 != iCallbackSetParameter(iPtrSetParameter, aVersion, (const char*)aaTarget.Ptr(), (const char*)aaName.Ptr(), (const char*)aaValue.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvServiceLinnCoUkConfiguration1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkConfiguration1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkConfiguration1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkConfiguration1C*>(aService);
}

void DvServiceLinnCoUkConfiguration1EnableActionConfigurationXml(THandle aService, CallbackConfiguration1ConfigurationXml aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkConfiguration1C*>(aService)->EnableActionConfigurationXml(aCallback, aPtr);
}

void DvServiceLinnCoUkConfiguration1EnableActionParameterXml(THandle aService, CallbackConfiguration1ParameterXml aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkConfiguration1C*>(aService)->EnableActionParameterXml(aCallback, aPtr);
}

void DvServiceLinnCoUkConfiguration1EnableActionSetParameter(THandle aService, CallbackConfiguration1SetParameter aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkConfiguration1C*>(aService)->EnableActionSetParameter(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkConfiguration1SetPropertyConfigurationXml(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkConfiguration1C*>(aService)->SetPropertyConfigurationXml(buf);
    return 0;
}

void DvServiceLinnCoUkConfiguration1GetPropertyConfigurationXml(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkConfiguration1C*>(aService)->GetPropertyConfigurationXml(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkConfiguration1SetPropertyParameterXml(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkConfiguration1C*>(aService)->SetPropertyParameterXml(buf);
    return 0;
}

void DvServiceLinnCoUkConfiguration1GetPropertyParameterXml(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkConfiguration1C*>(aService)->GetPropertyParameterXml(buf);
    *aValue = (char*)buf.Transfer();
}

