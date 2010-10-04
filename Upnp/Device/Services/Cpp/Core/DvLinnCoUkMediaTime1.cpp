#include <Core/DvLinnCoUkMediaTime1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkMediaTime1::SetPropertySeconds(TUint aValue)
{
    SetPropertyUint(*iPropertySeconds, aValue);
}

void DvServiceLinnCoUkMediaTime1::GetPropertySeconds(TUint& aValue)
{
    aValue = iPropertySeconds->Value();
}

DvServiceLinnCoUkMediaTime1::DvServiceLinnCoUkMediaTime1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "MediaTime", 1)
{
    Functor empty;
    iPropertySeconds = new PropertyUint(new ParameterUint("Seconds"), empty);
    iService->AddProperty(iPropertySeconds); // passes ownership
}

void DvServiceLinnCoUkMediaTime1::EnableActionSeconds()
{
    Zapp::Action* action = new Zapp::Action("Seconds");
    action->AddOutputParameter(new ParameterRelated("aSeconds", *iPropertySeconds));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkMediaTime1::DoSeconds);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkMediaTime1::DoSeconds(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaSeconds(aInvocation, "aSeconds");
    Seconds(resp, aVersion, respaSeconds);
}

void DvServiceLinnCoUkMediaTime1::Seconds(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaSeconds*/)
{
    ASSERTS();
}

