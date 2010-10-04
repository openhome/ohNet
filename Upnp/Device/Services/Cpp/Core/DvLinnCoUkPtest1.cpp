#include <Core/DvLinnCoUkPtest1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

DvServiceLinnCoUkPtest1::DvServiceLinnCoUkPtest1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Ptest", 1)
{
    Functor empty;
}

void DvServiceLinnCoUkPtest1::EnableActionTestComPort()
{
    Zapp::Action* action = new Zapp::Action("TestComPort");
    action->AddInputParameter(new ParameterUint("aPort"));
    action->AddOutputParameter(new ParameterBool("aResult"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPtest1::DoTestComPort);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPtest1::EnableActionLedsOn()
{
    Zapp::Action* action = new Zapp::Action("LedsOn");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPtest1::DoLedsOn);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPtest1::EnableActionLedsOff()
{
    Zapp::Action* action = new Zapp::Action("LedsOff");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPtest1::DoLedsOff);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPtest1::DoTestComPort(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aPort = aInvocation.InvocationReadUint("aPort");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaResult(aInvocation, "aResult");
    TestComPort(resp, aVersion, aPort, respaResult);
}

void DvServiceLinnCoUkPtest1::DoLedsOn(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    LedsOn(resp, aVersion);
}

void DvServiceLinnCoUkPtest1::DoLedsOff(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    LedsOff(resp, aVersion);
}

void DvServiceLinnCoUkPtest1::TestComPort(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaPort*/, IInvocationResponseBool& /*aaResult*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPtest1::LedsOn(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPtest1::LedsOff(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

