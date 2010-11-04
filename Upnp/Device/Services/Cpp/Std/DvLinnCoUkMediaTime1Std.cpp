#include <Std/DvLinnCoUkMediaTime1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

bool DvProviderLinnCoUkMediaTime1Cpp::SetPropertySeconds(uint32_t aValue)
{
    return SetPropertyUint(*iPropertySeconds, aValue);
}

void DvProviderLinnCoUkMediaTime1Cpp::GetPropertySeconds(uint32_t& aValue)
{
    aValue = iPropertySeconds->Value();
}

DvProviderLinnCoUkMediaTime1Cpp::DvProviderLinnCoUkMediaTime1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "MediaTime", 1)
{
    Functor empty;
    iPropertySeconds = new PropertyUint(new ParameterUint("Seconds"), empty);
    iService->AddProperty(iPropertySeconds); // passes ownership
}

void DvProviderLinnCoUkMediaTime1Cpp::EnableActionSeconds()
{
    Zapp::Action* action = new Zapp::Action("Seconds");
    action->AddOutputParameter(new ParameterRelated("aSeconds", *iPropertySeconds));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkMediaTime1Cpp::DoSeconds);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkMediaTime1Cpp::DoSeconds(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaSeconds;
    Seconds(aVersion, respaSeconds);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraSeconds(aInvocation, "aSeconds");
    respWriteraSeconds.Write(respaSeconds);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkMediaTime1Cpp::Seconds(uint32_t /*aVersion*/, uint32_t& /*aaSeconds*/)
{
    ASSERTS();
}

