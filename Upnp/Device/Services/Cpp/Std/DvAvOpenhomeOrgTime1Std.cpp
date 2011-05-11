#include "DvAvOpenhomeOrgTime1.h"
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

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
    Zapp::Action* action = new Zapp::Action("Time");
    action->AddOutputParameter(new ParameterRelated("aTrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("aDuration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("aSeconds", *iPropertySeconds));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgTime1Cpp::DoTime);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgTime1Cpp::DoTime(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaTrackCount;
    uint32_t respaDuration;
    uint32_t respaSeconds;
    Time(aVersion, respaTrackCount, respaDuration, respaSeconds);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraTrackCount(aInvocation, "aTrackCount");
    respWriteraTrackCount.Write(respaTrackCount);
    InvocationResponseUint respWriteraDuration(aInvocation, "aDuration");
    respWriteraDuration.Write(respaDuration);
    InvocationResponseUint respWriteraSeconds(aInvocation, "aSeconds");
    respWriteraSeconds.Write(respaSeconds);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgTime1Cpp::Time(uint32_t /*aVersion*/, uint32_t& /*aaTrackCount*/, uint32_t& /*aaDuration*/, uint32_t& /*aaSeconds*/)
{
    ASSERTS();
}

