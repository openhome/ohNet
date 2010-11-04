#include <Core/DvLinnCoUkTime1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkTime1::SetPropertyTrackCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvProviderLinnCoUkTime1::GetPropertyTrackCount(TUint& aValue)
{
    aValue = iPropertyTrackCount->Value();
}

TBool DvProviderLinnCoUkTime1::SetPropertyDuration(TUint aValue)
{
    return SetPropertyUint(*iPropertyDuration, aValue);
}

void DvProviderLinnCoUkTime1::GetPropertyDuration(TUint& aValue)
{
    aValue = iPropertyDuration->Value();
}

TBool DvProviderLinnCoUkTime1::SetPropertySeconds(TUint aValue)
{
    return SetPropertyUint(*iPropertySeconds, aValue);
}

void DvProviderLinnCoUkTime1::GetPropertySeconds(TUint& aValue)
{
    aValue = iPropertySeconds->Value();
}

DvProviderLinnCoUkTime1::DvProviderLinnCoUkTime1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Time", 1)
{
    Functor empty;
    iPropertyTrackCount = new PropertyUint(new ParameterUint("TrackCount"), empty);
    iService->AddProperty(iPropertyTrackCount); // passes ownership
    iPropertyDuration = new PropertyUint(new ParameterUint("Duration"), empty);
    iService->AddProperty(iPropertyDuration); // passes ownership
    iPropertySeconds = new PropertyUint(new ParameterUint("Seconds"), empty);
    iService->AddProperty(iPropertySeconds); // passes ownership
}

void DvProviderLinnCoUkTime1::EnableActionTime()
{
    Zapp::Action* action = new Zapp::Action("Time");
    action->AddOutputParameter(new ParameterRelated("aTrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("aDuration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("aSeconds", *iPropertySeconds));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkTime1::DoTime);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkTime1::DoTime(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaTrackCount(aInvocation, "aTrackCount");
    InvocationResponseUint respaDuration(aInvocation, "aDuration");
    InvocationResponseUint respaSeconds(aInvocation, "aSeconds");
    Time(resp, aVersion, respaTrackCount, respaDuration, respaSeconds);
}

void DvProviderLinnCoUkTime1::Time(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaTrackCount*/, IInvocationResponseUint& /*aaDuration*/, IInvocationResponseUint& /*aaSeconds*/)
{
    ASSERTS();
}

