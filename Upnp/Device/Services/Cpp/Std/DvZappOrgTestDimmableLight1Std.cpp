#include <Std/DvZappOrgTestDimmableLight1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

bool DvProviderZappOrgTestDimmableLight1Cpp::SetPropertyA_ARG_Level(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyA_ARG_Level, aValue);
}

void DvProviderZappOrgTestDimmableLight1Cpp::GetPropertyA_ARG_Level(uint32_t& aValue)
{
    aValue = iPropertyA_ARG_Level->Value();
}

DvProviderZappOrgTestDimmableLight1Cpp::DvProviderZappOrgTestDimmableLight1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "zapp.org", "TestDimmableLight", 1)
{
    
    iPropertyA_ARG_Level = new PropertyUint(new ParameterUint("A_ARG_Level"));
    iService->AddProperty(iPropertyA_ARG_Level); // passes ownership
}

void DvProviderZappOrgTestDimmableLight1Cpp::EnableActionGetLevel()
{
    Zapp::Action* action = new Zapp::Action("GetLevel");
    action->AddOutputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestDimmableLight1Cpp::DoGetLevel);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestDimmableLight1Cpp::EnableActionSetLevel()
{
    Zapp::Action* action = new Zapp::Action("SetLevel");
    action->AddInputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestDimmableLight1Cpp::DoSetLevel);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestDimmableLight1Cpp::DoGetLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respLevel;
    GetLevel(aVersion, respLevel);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterLevel(aInvocation, "Level");
    respWriterLevel.Write(respLevel);
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestDimmableLight1Cpp::DoSetLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Level = aInvocation.InvocationReadUint("Level");
    aInvocation.InvocationReadEnd();
    SetLevel(aVersion, Level);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestDimmableLight1Cpp::GetLevel(uint32_t /*aVersion*/, uint32_t& /*aLevel*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestDimmableLight1Cpp::SetLevel(uint32_t /*aVersion*/, uint32_t /*aLevel*/)
{
    ASSERTS();
}

