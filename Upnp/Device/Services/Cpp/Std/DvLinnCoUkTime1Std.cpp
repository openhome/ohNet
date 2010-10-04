#include <Std/DvLinnCoUkTime1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkTime1Cpp::SetPropertyTrackCount(uint32_t aValue)
{
    SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvServiceLinnCoUkTime1Cpp::GetPropertyTrackCount(uint32_t& aValue)
{
    aValue = iPropertyTrackCount->Value();
}

void DvServiceLinnCoUkTime1Cpp::SetPropertyDuration(uint32_t aValue)
{
    SetPropertyUint(*iPropertyDuration, aValue);
}

void DvServiceLinnCoUkTime1Cpp::GetPropertyDuration(uint32_t& aValue)
{
    aValue = iPropertyDuration->Value();
}

void DvServiceLinnCoUkTime1Cpp::SetPropertySeconds(uint32_t aValue)
{
    SetPropertyUint(*iPropertySeconds, aValue);
}

void DvServiceLinnCoUkTime1Cpp::GetPropertySeconds(uint32_t& aValue)
{
    aValue = iPropertySeconds->Value();
}

DvServiceLinnCoUkTime1Cpp::DvServiceLinnCoUkTime1Cpp(DvDeviceStd& aDevice)
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

void DvServiceLinnCoUkTime1Cpp::EnableActionTime()
{
    Zapp::Action* action = new Zapp::Action("Time");
    action->AddOutputParameter(new ParameterRelated("aTrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("aDuration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("aSeconds", *iPropertySeconds));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkTime1Cpp::DoTime);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkTime1Cpp::DoTime(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkTime1Cpp::Time(uint32_t /*aVersion*/, uint32_t& /*aaTrackCount*/, uint32_t& /*aaDuration*/, uint32_t& /*aaSeconds*/)
{
    ASSERTS();
}

