#include <Std/DvZappOrgTestDimmableLight1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

DvServiceZappOrgTestDimmableLight1Cpp::DvServiceZappOrgTestDimmableLight1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "zapp.org", "TestDimmableLight", 1)
{
    Functor empty;
}

void DvServiceZappOrgTestDimmableLight1Cpp::EnableActionGetLevel()
{
    Zapp::Action* action = new Zapp::Action("GetLevel");
    action->AddOutputParameter(new ParameterUint("Level"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestDimmableLight1Cpp::DoGetLevel);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestDimmableLight1Cpp::EnableActionSetLevel()
{
    Zapp::Action* action = new Zapp::Action("SetLevel");
    action->AddInputParameter(new ParameterUint("Level"));
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

