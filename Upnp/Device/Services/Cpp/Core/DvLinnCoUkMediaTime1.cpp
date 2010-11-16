#include <Core/DvLinnCoUkMediaTime1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkMediaTime1::SetPropertySeconds(TUint aValue)
{
    return SetPropertyUint(*iPropertySeconds, aValue);
}

void DvProviderLinnCoUkMediaTime1::GetPropertySeconds(TUint& aValue)
{
    aValue = iPropertySeconds->Value();
}

DvProviderLinnCoUkMediaTime1::DvProviderLinnCoUkMediaTime1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "MediaTime", 1)
{
    Functor empty;
    iPropertySeconds = new PropertyUint(new ParameterUint("Seconds"), empty);
    iService->AddProperty(iPropertySeconds); // passes ownership
}

void DvProviderLinnCoUkMediaTime1::EnableActionSeconds()
{
    Zapp::Action* action = new Zapp::Action("Seconds");
    action->AddOutputParameter(new ParameterRelated("aSeconds", *iPropertySeconds));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkMediaTime1::DoSeconds);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkMediaTime1::DoSeconds(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaSeconds(aInvocation, "aSeconds");
    Seconds(resp, aVersion, respaSeconds);
}

void DvProviderLinnCoUkMediaTime1::Seconds(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaSeconds*/)
{
    ASSERTS();
}

