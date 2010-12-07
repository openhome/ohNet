#include <Core/DvLinnCoUkPtest1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

DvProviderLinnCoUkPtest1::DvProviderLinnCoUkPtest1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Ptest", 1)
{
    
}

void DvProviderLinnCoUkPtest1::EnableActionTestComPort()
{
    Zapp::Action* action = new Zapp::Action("TestComPort");
    action->AddInputParameter(new ParameterUint("aPort"));
    action->AddOutputParameter(new ParameterBool("aResult"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPtest1::DoTestComPort);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPtest1::EnableActionLedsOn()
{
    Zapp::Action* action = new Zapp::Action("LedsOn");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPtest1::DoLedsOn);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPtest1::EnableActionLedsOff()
{
    Zapp::Action* action = new Zapp::Action("LedsOff");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPtest1::DoLedsOff);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPtest1::DoTestComPort(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aPort = aInvocation.InvocationReadUint("aPort");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaResult(aInvocation, "aResult");
    TestComPort(resp, aVersion, aPort, respaResult);
}

void DvProviderLinnCoUkPtest1::DoLedsOn(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    LedsOn(resp, aVersion);
}

void DvProviderLinnCoUkPtest1::DoLedsOff(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    LedsOff(resp, aVersion);
}

void DvProviderLinnCoUkPtest1::TestComPort(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaPort*/, IInvocationResponseBool& /*aaResult*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPtest1::LedsOn(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPtest1::LedsOff(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

