#include "DvAvOpenhomeOrgTime1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgTime1::SetPropertyTrackCount(TUint aValue)
{
    ASSERT(iPropertyTrackCount != NULL);
    return SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvProviderAvOpenhomeOrgTime1::GetPropertyTrackCount(TUint& aValue)
{
    ASSERT(iPropertyTrackCount != NULL);
    aValue = iPropertyTrackCount->Value();
}

TBool DvProviderAvOpenhomeOrgTime1::SetPropertyDuration(TUint aValue)
{
    ASSERT(iPropertyDuration != NULL);
    return SetPropertyUint(*iPropertyDuration, aValue);
}

void DvProviderAvOpenhomeOrgTime1::GetPropertyDuration(TUint& aValue)
{
    ASSERT(iPropertyDuration != NULL);
    aValue = iPropertyDuration->Value();
}

TBool DvProviderAvOpenhomeOrgTime1::SetPropertySeconds(TUint aValue)
{
    ASSERT(iPropertySeconds != NULL);
    return SetPropertyUint(*iPropertySeconds, aValue);
}

void DvProviderAvOpenhomeOrgTime1::GetPropertySeconds(TUint& aValue)
{
    ASSERT(iPropertySeconds != NULL);
    aValue = iPropertySeconds->Value();
}

DvProviderAvOpenhomeOrgTime1::DvProviderAvOpenhomeOrgTime1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Time", 1)
{
    Construct();
}

DvProviderAvOpenhomeOrgTime1::DvProviderAvOpenhomeOrgTime1(DviDevice& aDevice)
    : DvProvider(aDevice, "av.openhome.org", "Time", 1)
{
    Construct();
}

void DvProviderAvOpenhomeOrgTime1::Construct()
{
    iPropertyTrackCount = NULL;
    iPropertyDuration = NULL;
    iPropertySeconds = NULL;
}

void DvProviderAvOpenhomeOrgTime1::EnablePropertyTrackCount()
{
    iPropertyTrackCount = new PropertyUint(iDvStack.Env(), new ParameterUint("TrackCount"));
    iService->AddProperty(iPropertyTrackCount); // passes ownership
}

void DvProviderAvOpenhomeOrgTime1::EnablePropertyDuration()
{
    iPropertyDuration = new PropertyUint(iDvStack.Env(), new ParameterUint("Duration"));
    iService->AddProperty(iPropertyDuration); // passes ownership
}

void DvProviderAvOpenhomeOrgTime1::EnablePropertySeconds()
{
    iPropertySeconds = new PropertyUint(iDvStack.Env(), new ParameterUint("Seconds"));
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

