#include "DvZappOrgTestDimmableLight1.h"
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

class DvProviderZappOrgTestDimmableLight1C : public DvProvider
{
public:
    DvProviderZappOrgTestDimmableLight1C(DvDeviceC aDevice);
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

DvProviderZappOrgTestDimmableLight1C::DvProviderZappOrgTestDimmableLight1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "zapp.org", "TestDimmableLight", 1)
{
    
    iPropertyA_ARG_Level = new PropertyUint(new ParameterUint("A_ARG_Level"));
    iService->AddProperty(iPropertyA_ARG_Level); // passes ownership
}

TBool DvProviderZappOrgTestDimmableLight1C::SetPropertyA_ARG_Level(TUint aValue)
{
    return SetPropertyUint(*iPropertyA_ARG_Level, aValue);
}

void DvProviderZappOrgTestDimmableLight1C::GetPropertyA_ARG_Level(TUint& aValue)
{
    aValue = iPropertyA_ARG_Level->Value();
}

void DvProviderZappOrgTestDimmableLight1C::EnableActionGetLevel(CallbackTestDimmableLight1GetLevel aCallback, void* aPtr)
{
    iCallbackGetLevel = aCallback;
    iPtrGetLevel = aPtr;
    Zapp::Action* action = new Zapp::Action("GetLevel");
    action->AddOutputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestDimmableLight1C::DoGetLevel);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestDimmableLight1C::EnableActionSetLevel(CallbackTestDimmableLight1SetLevel aCallback, void* aPtr)
{
    iCallbackSetLevel = aCallback;
    iPtrSetLevel = aPtr;
    Zapp::Action* action = new Zapp::Action("SetLevel");
    action->AddInputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestDimmableLight1C::DoSetLevel);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestDimmableLight1C::DoGetLevel(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderZappOrgTestDimmableLight1C::DoSetLevel(IDviInvocation& aInvocation, TUint aVersion)
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



THandle DvProviderZappOrgTestDimmableLight1Create(DvDeviceC aDevice)
{
	return new DvProviderZappOrgTestDimmableLight1C(aDevice);
}

void DvProviderZappOrgTestDimmableLight1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderZappOrgTestDimmableLight1C*>(aProvider);
}

void DvProviderZappOrgTestDimmableLight1EnableActionGetLevel(THandle aProvider, CallbackTestDimmableLight1GetLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestDimmableLight1C*>(aProvider)->EnableActionGetLevel(aCallback, aPtr);
}

void DvProviderZappOrgTestDimmableLight1EnableActionSetLevel(THandle aProvider, CallbackTestDimmableLight1SetLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestDimmableLight1C*>(aProvider)->EnableActionSetLevel(aCallback, aPtr);
}

int32_t DvProviderZappOrgTestDimmableLight1SetPropertyA_ARG_Level(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestDimmableLight1C*>(aProvider)->SetPropertyA_ARG_Level(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestDimmableLight1GetPropertyA_ARG_Level(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestDimmableLight1C*>(aProvider)->GetPropertyA_ARG_Level(val);
    *aValue = val;
}

