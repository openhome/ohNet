#include "DvOpenhomeOrgTestDimmableLight1.h"
#include <OhNetTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/OhNet.h>
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderOpenhomeOrgTestDimmableLight1C : public DvProvider
{
public:
    DvProviderOpenhomeOrgTestDimmableLight1C(DvDeviceC aDevice);
    TBool SetPropertyA_ARG_Level(TUint aValue);
    void GetPropertyA_ARG_Level(TUint& aValue);
    void EnableActionGetLevel(CallbackTestDimmableLight1GetLevel aCallback, void* aPtr);
    void EnableActionSetLevel(CallbackTestDimmableLight1SetLevel aCallback, void* aPtr);
private:
    void DoGetLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetLevel(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackTestDimmableLight1GetLevel iCallbackGetLevel;
    void* iPtrGetLevel;
    CallbackTestDimmableLight1SetLevel iCallbackSetLevel;
    void* iPtrSetLevel;
    PropertyUint* iPropertyA_ARG_Level;
};

DvProviderOpenhomeOrgTestDimmableLight1C::DvProviderOpenhomeOrgTestDimmableLight1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "openhome.org", "TestDimmableLight", 1)
{
    
    iPropertyA_ARG_Level = new PropertyUint(new ParameterUint("A_ARG_Level"));
    iService->AddProperty(iPropertyA_ARG_Level); // passes ownership
}

TBool DvProviderOpenhomeOrgTestDimmableLight1C::SetPropertyA_ARG_Level(TUint aValue)
{
    return SetPropertyUint(*iPropertyA_ARG_Level, aValue);
}

void DvProviderOpenhomeOrgTestDimmableLight1C::GetPropertyA_ARG_Level(TUint& aValue)
{
    aValue = iPropertyA_ARG_Level->Value();
}

void DvProviderOpenhomeOrgTestDimmableLight1C::EnableActionGetLevel(CallbackTestDimmableLight1GetLevel aCallback, void* aPtr)
{
    iCallbackGetLevel = aCallback;
    iPtrGetLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetLevel");
    action->AddOutputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestDimmableLight1C::DoGetLevel);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestDimmableLight1C::EnableActionSetLevel(CallbackTestDimmableLight1SetLevel aCallback, void* aPtr)
{
    iCallbackSetLevel = aCallback;
    iPtrSetLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetLevel");
    action->AddInputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestDimmableLight1C::DoSetLevel);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestDimmableLight1C::DoGetLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Level;
    ASSERT(iCallbackGetLevel != NULL);
    if (0 != iCallbackGetLevel(iPtrGetLevel, aVersion, &Level)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respLevel(aInvocation, "Level");
    resp.Start();
    respLevel.Write(Level);
    resp.End();
}

void DvProviderOpenhomeOrgTestDimmableLight1C::DoSetLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Level = aInvocation.InvocationReadUint("Level");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetLevel != NULL);
    if (0 != iCallbackSetLevel(iPtrSetLevel, aVersion, Level)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}



THandle DvProviderOpenhomeOrgTestDimmableLight1Create(DvDeviceC aDevice)
{
	return new DvProviderOpenhomeOrgTestDimmableLight1C(aDevice);
}

void DvProviderOpenhomeOrgTestDimmableLight1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderOpenhomeOrgTestDimmableLight1C*>(aProvider);
}

void DvProviderOpenhomeOrgTestDimmableLight1EnableActionGetLevel(THandle aProvider, CallbackTestDimmableLight1GetLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestDimmableLight1C*>(aProvider)->EnableActionGetLevel(aCallback, aPtr);
}

void DvProviderOpenhomeOrgTestDimmableLight1EnableActionSetLevel(THandle aProvider, CallbackTestDimmableLight1SetLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestDimmableLight1C*>(aProvider)->EnableActionSetLevel(aCallback, aPtr);
}

int32_t DvProviderOpenhomeOrgTestDimmableLight1SetPropertyA_ARG_Level(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderOpenhomeOrgTestDimmableLight1C*>(aProvider)->SetPropertyA_ARG_Level(aValue)? 1 : 0);
    return 0;
}

void DvProviderOpenhomeOrgTestDimmableLight1GetPropertyA_ARG_Level(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderOpenhomeOrgTestDimmableLight1C*>(aProvider)->GetPropertyA_ARG_Level(val);
    *aValue = val;
}

