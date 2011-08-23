#include "DvAvOpenhomeOrgTime1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgTime1Cpp::SetPropertyTrackCount(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvProviderAvOpenhomeOrgTime1Cpp::GetPropertyTrackCount(uint32_t& aValue)
{
    aValue = iPropertyTrackCount->Value();
}

bool DvProviderAvOpenhomeOrgTime1Cpp::SetPropertyDuration(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyDuration, aValue);
}

void DvProviderAvOpenhomeOrgTime1Cpp::GetPropertyDuration(uint32_t& aValue)
{
    aValue = iPropertyDuration->Value();
}

bool DvProviderAvOpenhomeOrgTime1Cpp::SetPropertySeconds(uint32_t aValue)
{
    return SetPropertyUint(*iPropertySeconds, aValue);
}

void DvProviderAvOpenhomeOrgTime1Cpp::GetPropertySeconds(uint32_t& aValue)
{
    aValue = iPropertySeconds->Value();
}

DvProviderAvOpenhomeOrgTime1Cpp::DvProviderAvOpenhomeOrgTime1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Time", 1)
{
    
    iPropertyTrackCount = new PropertyUint(new ParameterUint("TrackCount"));
    iService->AddProperty(iPropertyTrackCount); // passes ownership
    iPropertyDuration = new PropertyUint(new ParameterUint("Duration"));
    iService->AddProperty(iPropertyDuration); // passes ownership
    iPropertySeconds = new PropertyUint(new ParameterUint("Seconds"));
    iService->AddProperty(iPropertySeconds); // passes ownership
}

void DvProviderAvOpenhomeOrgTime1Cpp::EnableActionTime()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Time");
    action->AddOutputParameter(new ParameterRelated("TrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("Duration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("Seconds", *iPropertySeconds));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgTime1Cpp::DoTime);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgTime1Cpp::DoTime(IDviInvocation& aInvocation, uint32_t /*aVersion*/)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respTrackCount;
    uint32_t respDuration;
    uint32_t respSeconds;
    DvInvocationStd invocation(aInvocation);
    Time(invocation, respTrackCount, respDuration, respSeconds);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterTrackCount(aInvocation, "TrackCount");
    respWriterTrackCount.Write(respTrackCount);
    DviInvocationResponseUint respWriterDuration(aInvocation, "Duration");
    respWriterDuration.Write(respDuration);
    DviInvocationResponseUint respWriterSeconds(aInvocation, "Seconds");
    respWriterSeconds.Write(respSeconds);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgTime1Cpp::Time(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aTrackCount*/, uint32_t& /*aDuration*/, uint32_t& /*aSeconds*/)
{
    ASSERTS();
}

