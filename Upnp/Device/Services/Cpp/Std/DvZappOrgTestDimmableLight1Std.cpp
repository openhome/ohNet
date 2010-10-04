#include <Std/DvZappOrgTestDimmableLight1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceZappOrgTestDimmableLight1Cpp::SetPropertyA_ARG_Level(uint32_t aValue)
{
    SetPropertyUint(*iPropertyA_ARG_Level, aValue);
}

void DvServiceZappOrgTestDimmableLight1Cpp::GetPropertyA_ARG_Level(uint32_t& aValue)
{
    aValue = iPropertyA_ARG_Level->Value();
}

DvServiceZappOrgTestDimmableLight1Cpp::DvServiceZappOrgTestDimmableLight1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "zapp.org", "TestDimmableLight", 1)
{
    Functor empty;
    iPropertyA_ARG_Level = new PropertyUint(new ParameterUint("A_ARG_Level"), empty);
    iService->AddProperty(iPropertyA_ARG_Level); // passes ownership
}

void DvServiceZappOrgTestDimmableLight1Cpp::EnableActionGetLevel()
{
    Zapp::Action* action = new Zapp::Action("GetLevel");
    action->AddOutputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestDimmableLight1Cpp::DoGetLevel);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestDimmableLight1Cpp::EnableActionSetLevel()
{
    Zapp::Action* action = new Zapp::Action("SetLevel");
    action->AddInputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestDimmableLight1Cpp::DoSetLevel);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestDimmableLight1Cpp::DoGetLevel(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceZappOrgTestDimmableLight1Cpp::DoSetLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Level = aInvocation.InvocationReadUint("Level");
    aInvocation.InvocationReadEnd();
    SetLevel(aVersion, Level);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestDimmableLight1Cpp::GetLevel(uint32_t /*aVersion*/, uint32_t& /*aLevel*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestDimmableLight1Cpp::SetLevel(uint32_t /*aVersion*/, uint32_t /*aLevel*/)
{
    ASSERTS();
}

