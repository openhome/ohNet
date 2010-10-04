#include <Core/DvLinnCoUkTime1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkTime1::SetPropertyTrackCount(TUint aValue)
{
    SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvServiceLinnCoUkTime1::GetPropertyTrackCount(TUint& aValue)
{
    aValue = iPropertyTrackCount->Value();
}

void DvServiceLinnCoUkTime1::SetPropertyDuration(TUint aValue)
{
    SetPropertyUint(*iPropertyDuration, aValue);
}

void DvServiceLinnCoUkTime1::GetPropertyDuration(TUint& aValue)
{
    aValue = iPropertyDuration->Value();
}

void DvServiceLinnCoUkTime1::SetPropertySeconds(TUint aValue)
{
    SetPropertyUint(*iPropertySeconds, aValue);
}

void DvServiceLinnCoUkTime1::GetPropertySeconds(TUint& aValue)
{
    aValue = iPropertySeconds->Value();
}

DvServiceLinnCoUkTime1::DvServiceLinnCoUkTime1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Time", 1)
{
    Functor empty;
    iPropertyTrackCount = new PropertyUint(new ParameterUint("TrackCount"), empty);
    iService->AddProperty(iPropertyTrackCount); // passes ownership
    iPropertyDuration = new PropertyUint(new ParameterUint("Duration"), empty);
    iService->AddProperty(iPropertyDuration); // passes ownership
    iPropertySeconds = new PropertyUint(new ParameterUint("Seconds"), empty);
    iService->AddProperty(iPropertySeconds); // passes ownership
}

void DvServiceLinnCoUkTime1::EnableActionTime()
{
    Zapp::Action* action = new Zapp::Action("Time");
    action->AddOutputParameter(new ParameterRelated("aTrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("aDuration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("aSeconds", *iPropertySeconds));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkTime1::DoTime);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkTime1::DoTime(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaTrackCount(aInvocation, "aTrackCount");
    InvocationResponseUint respaDuration(aInvocation, "aDuration");
    InvocationResponseUint respaSeconds(aInvocation, "aSeconds");
    Time(resp, aVersion, respaTrackCount, respaDuration, respaSeconds);
}

void DvServiceLinnCoUkTime1::Time(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaTrackCount*/, IInvocationResponseUint& /*aaDuration*/, IInvocationResponseUint& /*aaSeconds*/)
{
    ASSERTS();
}

