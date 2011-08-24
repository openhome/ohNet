#include "DvAvOpenhomeOrgTime1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

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
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Time");
    action->AddOutputParameter(new ParameterRelated("TrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("Duration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("Seconds", *iPropertySeconds));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgTime1::DoTime);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgTime1::DoTime(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respTrackCount(aInvocation, "TrackCount");
    DviInvocationResponseUint respDuration(aInvocation, "Duration");
    DviInvocationResponseUint respSeconds(aInvocation, "Seconds");
    Time(invocation, respTrackCount, respDuration, respSeconds);
}

void DvProviderAvOpenhomeOrgTime1::Time(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aTrackCount*/, IDvInvocationResponseUint& /*aDuration*/, IDvInvocationResponseUint& /*aSeconds*/)
{
    ASSERTS();
}

