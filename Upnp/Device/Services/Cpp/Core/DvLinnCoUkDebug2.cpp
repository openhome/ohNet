#include <Core/DvLinnCoUkDebug2.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

DvProviderLinnCoUkDebug2::DvProviderLinnCoUkDebug2(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Debug", 2)
{
    Functor empty;
}

void DvProviderLinnCoUkDebug2::EnableActionSetDebugLevel()
{
    Zapp::Action* action = new Zapp::Action("SetDebugLevel");
    action->AddInputParameter(new ParameterUint("aDebugLevel"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkDebug2::DoSetDebugLevel);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDebug2::EnableActionDebugLevel()
{
    Zapp::Action* action = new Zapp::Action("DebugLevel");
    action->AddOutputParameter(new ParameterUint("aDebugLevel"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkDebug2::DoDebugLevel);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDebug2::EnableActionMemWrite()
{
    Zapp::Action* action = new Zapp::Action("MemWrite");
    action->AddInputParameter(new ParameterUint("aMemAddress"));
    action->AddInputParameter(new ParameterBinary("aMemData"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkDebug2::DoMemWrite);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDebug2::DoSetDebugLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aDebugLevel = aInvocation.InvocationReadUint("aDebugLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDebugLevel(resp, aVersion, aDebugLevel);
}

void DvProviderLinnCoUkDebug2::DoDebugLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaDebugLevel(aInvocation, "aDebugLevel");
    DebugLevel(resp, aVersion, respaDebugLevel);
}

void DvProviderLinnCoUkDebug2::DoMemWrite(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aMemAddress = aInvocation.InvocationReadUint("aMemAddress");
    Brh aMemData;
    aInvocation.InvocationReadBinary("aMemData", aMemData);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    MemWrite(resp, aVersion, aMemAddress, aMemData);
}

void DvProviderLinnCoUkDebug2::SetDebugLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaDebugLevel*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDebug2::DebugLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaDebugLevel*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDebug2::MemWrite(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaMemAddress*/, const Brx& /*aaMemData*/)
{
    ASSERTS();
}

