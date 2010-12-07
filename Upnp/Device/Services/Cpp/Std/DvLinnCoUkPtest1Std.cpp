#include <Std/DvLinnCoUkPtest1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

DvProviderLinnCoUkPtest1Cpp::DvProviderLinnCoUkPtest1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Ptest", 1)
{
    
}

void DvProviderLinnCoUkPtest1Cpp::EnableActionTestComPort()
{
    Zapp::Action* action = new Zapp::Action("TestComPort");
    action->AddInputParameter(new ParameterUint("aPort"));
    action->AddOutputParameter(new ParameterBool("aResult"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPtest1Cpp::DoTestComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPtest1Cpp::EnableActionLedsOn()
{
    Zapp::Action* action = new Zapp::Action("LedsOn");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPtest1Cpp::DoLedsOn);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPtest1Cpp::EnableActionLedsOff()
{
    Zapp::Action* action = new Zapp::Action("LedsOff");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPtest1Cpp::DoLedsOff);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPtest1Cpp::DoTestComPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aPort = aInvocation.InvocationReadUint("aPort");
    aInvocation.InvocationReadEnd();
    bool respaResult;
    TestComPort(aVersion, aPort, respaResult);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraResult(aInvocation, "aResult");
    respWriteraResult.Write(respaResult);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPtest1Cpp::DoLedsOn(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    LedsOn(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPtest1Cpp::DoLedsOff(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    LedsOff(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPtest1Cpp::TestComPort(uint32_t /*aVersion*/, uint32_t /*aaPort*/, bool& /*aaResult*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPtest1Cpp::LedsOn(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPtest1Cpp::LedsOff(uint32_t /*aVersion*/)
{
    ASSERTS();
}

