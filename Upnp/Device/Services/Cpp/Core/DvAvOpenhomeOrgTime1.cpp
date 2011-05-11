#include "DvAvOpenhomeOrgTime1.h"
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderAvOpenhomeOrgTime1::SetPropertyTrackCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvProviderAvOpenhomeOrgTime1::GetPropertyTrackCount(TUint& aValue)
{
    aValue = iPropertyTrackCount->Value();
}

TBool DvProviderAvOpenhomeOrgTime1::SetPropertyDuration(TUint aValue)
{
    return SetPropertyUint(*iPropertyDuration, aValue);
}

void DvProviderAvOpenhomeOrgTime1::GetPropertyDuration(TUint& aValue)
{
    aValue = iPropertyDuration->Value();
}

TBool DvProviderAvOpenhomeOrgTime1::SetPropertySeconds(TUint aValue)
{
    return SetPropertyUint(*iPropertySeconds, aValue);
}

void DvProviderAvOpenhomeOrgTime1::GetPropertySeconds(TUint& aValue)
{
    aValue = iPropertySeconds->Value();
}

DvProviderAvOpenhomeOrgTime1::DvProviderAvOpenhomeOrgTime1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Time", 1)
{
    
    iPropertyTrackCount = new PropertyUint(new ParameterUint("TrackCount"));
    iService->AddProperty(iPropertyTrackCount); // passes ownership
    iPropertyDuration = new PropertyUint(new ParameterUint("Duration"));
    iService->AddProperty(iPropertyDuration); // passes ownership
    iPropertySeconds = new PropertyUint(new ParameterUint("Seconds"));
    iService->AddProperty(iPropertySeconds); // passes ownership
}

void DvProviderAvOpenhomeOrgTime1::EnableActionTime()
{
    Zapp::Action* action = new Zapp::Action("Time");
    action->AddOutputParameter(new ParameterRelated("aTrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("aDuration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("aSeconds", *iPropertySeconds));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgTime1::DoTime);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgTime1::DoTime(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaTrackCount(aInvocation, "aTrackCount");
    InvocationResponseUint respaDuration(aInvocation, "aDuration");
    InvocationResponseUint respaSeconds(aInvocation, "aSeconds");
    Time(resp, aVersion, respaTrackCount, respaDuration, respaSeconds);
}

void DvProviderAvOpenhomeOrgTime1::Time(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaTrackCount*/, IInvocationResponseUint& /*aaDuration*/, IInvocationResponseUint& /*aaSeconds*/)
{
    ASSERTS();
}

