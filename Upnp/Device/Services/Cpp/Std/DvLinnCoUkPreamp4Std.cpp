#include <Std/DvLinnCoUkPreamp4.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkPreamp4Cpp::SetPropertyVolume(uint32_t aValue)
{
    SetPropertyUint(*iPropertyVolume, aValue);
}

void DvServiceLinnCoUkPreamp4Cpp::GetPropertyVolume(uint32_t& aValue)
{
    aValue = iPropertyVolume->Value();
}

void DvServiceLinnCoUkPreamp4Cpp::SetPropertyMute(bool aValue)
{
    SetPropertyBool(*iPropertyMute, aValue);
}

void DvServiceLinnCoUkPreamp4Cpp::GetPropertyMute(bool& aValue)
{
    aValue = iPropertyMute->Value();
}

void DvServiceLinnCoUkPreamp4Cpp::SetPropertyBalance(int32_t aValue)
{
    SetPropertyInt(*iPropertyBalance, aValue);
}

void DvServiceLinnCoUkPreamp4Cpp::GetPropertyBalance(int32_t& aValue)
{
    aValue = iPropertyBalance->Value();
}

void DvServiceLinnCoUkPreamp4Cpp::SetPropertyVolumeLimit(uint32_t aValue)
{
    SetPropertyUint(*iPropertyVolumeLimit, aValue);
}

void DvServiceLinnCoUkPreamp4Cpp::GetPropertyVolumeLimit(uint32_t& aValue)
{
    aValue = iPropertyVolumeLimit->Value();
}

void DvServiceLinnCoUkPreamp4Cpp::SetPropertyStartupVolume(uint32_t aValue)
{
    SetPropertyUint(*iPropertyStartupVolume, aValue);
}

void DvServiceLinnCoUkPreamp4Cpp::GetPropertyStartupVolume(uint32_t& aValue)
{
    aValue = iPropertyStartupVolume->Value();
}

void DvServiceLinnCoUkPreamp4Cpp::SetPropertyStartupVolumeEnabled(bool aValue)
{
    SetPropertyBool(*iPropertyStartupVolumeEnabled, aValue);
}

void DvServiceLinnCoUkPreamp4Cpp::GetPropertyStartupVolumeEnabled(bool& aValue)
{
    aValue = iPropertyStartupVolumeEnabled->Value();
}

DvServiceLinnCoUkPreamp4Cpp::DvServiceLinnCoUkPreamp4Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Preamp", 4)
{
    Functor empty;
    iPropertyVolume = new PropertyUint(new ParameterUint("Volume"), empty);
    iService->AddProperty(iPropertyVolume); // passes ownership
    iPropertyMute = new PropertyBool(new ParameterBool("Mute"), empty);
    iService->AddProperty(iPropertyMute); // passes ownership
    iPropertyBalance = new PropertyInt(new ParameterInt("Balance"), empty);
    iService->AddProperty(iPropertyBalance); // passes ownership
    iPropertyVolumeLimit = new PropertyUint(new ParameterUint("VolumeLimit"), empty);
    iService->AddProperty(iPropertyVolumeLimit); // passes ownership
    iPropertyStartupVolume = new PropertyUint(new ParameterUint("StartupVolume"), empty);
    iService->AddProperty(iPropertyStartupVolume); // passes ownership
    iPropertyStartupVolumeEnabled = new PropertyBool(new ParameterBool("StartupVolumeEnabled"), empty);
    iService->AddProperty(iPropertyStartupVolumeEnabled); // passes ownership
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionVolumeInc()
{
    Zapp::Action* action = new Zapp::Action("VolumeInc");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoVolumeInc);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionVolumeDec()
{
    Zapp::Action* action = new Zapp::Action("VolumeDec");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoVolumeDec);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionSetVolume()
{
    Zapp::Action* action = new Zapp::Action("SetVolume");
    action->AddInputParameter(new ParameterUint("aVolume"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionVolume()
{
    Zapp::Action* action = new Zapp::Action("Volume");
    action->AddOutputParameter(new ParameterUint("aVolume"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoVolume);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionSetMute()
{
    Zapp::Action* action = new Zapp::Action("SetMute");
    action->AddInputParameter(new ParameterBool("aMute"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoSetMute);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionMute()
{
    Zapp::Action* action = new Zapp::Action("Mute");
    action->AddOutputParameter(new ParameterBool("aMute"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoMute);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionSetBalance()
{
    Zapp::Action* action = new Zapp::Action("SetBalance");
    action->AddInputParameter(new ParameterInt("aBalance"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoSetBalance);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionBalance()
{
    Zapp::Action* action = new Zapp::Action("Balance");
    action->AddOutputParameter(new ParameterInt("aBalance"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoBalance);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionSetVolumeLimit()
{
    Zapp::Action* action = new Zapp::Action("SetVolumeLimit");
    action->AddInputParameter(new ParameterUint("aVolumeLimit"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoSetVolumeLimit);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionVolumeLimit()
{
    Zapp::Action* action = new Zapp::Action("VolumeLimit");
    action->AddOutputParameter(new ParameterUint("aVolumeLimit"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoVolumeLimit);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionSetStartupVolume()
{
    Zapp::Action* action = new Zapp::Action("SetStartupVolume");
    action->AddInputParameter(new ParameterUint("aStartupVolume"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoSetStartupVolume);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionStartupVolume()
{
    Zapp::Action* action = new Zapp::Action("StartupVolume");
    action->AddOutputParameter(new ParameterUint("aStartupVolume"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoStartupVolume);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionSetStartupVolumeEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetStartupVolumeEnabled");
    action->AddInputParameter(new ParameterBool("aStartupVolumeEnabled"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoSetStartupVolumeEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::EnableActionStartupVolumeEnabled()
{
    Zapp::Action* action = new Zapp::Action("StartupVolumeEnabled");
    action->AddOutputParameter(new ParameterBool("aStartupVolumeEnabled"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4Cpp::DoStartupVolumeEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4Cpp::DoVolumeInc(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    VolumeInc(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::DoVolumeDec(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    VolumeDec(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::DoSetVolume(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aVolume = aInvocation.InvocationReadUint("aVolume");
    aInvocation.InvocationReadEnd();
    SetVolume(aVersion, aVolume);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::DoVolume(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaVolume;
    Volume(aVersion, respaVolume);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraVolume(aInvocation, "aVolume");
    respWriteraVolume.Write(respaVolume);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::DoSetMute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aMute = aInvocation.InvocationReadBool("aMute");
    aInvocation.InvocationReadEnd();
    SetMute(aVersion, aMute);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::DoMute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaMute;
    Mute(aVersion, respaMute);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraMute(aInvocation, "aMute");
    respWriteraMute.Write(respaMute);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::DoSetBalance(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t aBalance = aInvocation.InvocationReadInt("aBalance");
    aInvocation.InvocationReadEnd();
    SetBalance(aVersion, aBalance);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::DoBalance(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    int32_t respaBalance;
    Balance(aVersion, respaBalance);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriteraBalance(aInvocation, "aBalance");
    respWriteraBalance.Write(respaBalance);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::DoSetVolumeLimit(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aVolumeLimit = aInvocation.InvocationReadUint("aVolumeLimit");
    aInvocation.InvocationReadEnd();
    SetVolumeLimit(aVersion, aVolumeLimit);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::DoVolumeLimit(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaVolumeLimit;
    VolumeLimit(aVersion, respaVolumeLimit);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraVolumeLimit(aInvocation, "aVolumeLimit");
    respWriteraVolumeLimit.Write(respaVolumeLimit);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::DoSetStartupVolume(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aStartupVolume = aInvocation.InvocationReadUint("aStartupVolume");
    aInvocation.InvocationReadEnd();
    SetStartupVolume(aVersion, aStartupVolume);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::DoStartupVolume(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaStartupVolume;
    StartupVolume(aVersion, respaStartupVolume);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraStartupVolume(aInvocation, "aStartupVolume");
    respWriteraStartupVolume.Write(respaStartupVolume);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::DoSetStartupVolumeEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aStartupVolumeEnabled = aInvocation.InvocationReadBool("aStartupVolumeEnabled");
    aInvocation.InvocationReadEnd();
    SetStartupVolumeEnabled(aVersion, aStartupVolumeEnabled);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::DoStartupVolumeEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaStartupVolumeEnabled;
    StartupVolumeEnabled(aVersion, respaStartupVolumeEnabled);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraStartupVolumeEnabled(aInvocation, "aStartupVolumeEnabled");
    respWriteraStartupVolumeEnabled.Write(respaStartupVolumeEnabled);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPreamp4Cpp::VolumeInc(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4Cpp::VolumeDec(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4Cpp::SetVolume(uint32_t /*aVersion*/, uint32_t /*aaVolume*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4Cpp::Volume(uint32_t /*aVersion*/, uint32_t& /*aaVolume*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4Cpp::SetMute(uint32_t /*aVersion*/, bool /*aaMute*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4Cpp::Mute(uint32_t /*aVersion*/, bool& /*aaMute*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4Cpp::SetBalance(uint32_t /*aVersion*/, int32_t /*aaBalance*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4Cpp::Balance(uint32_t /*aVersion*/, int32_t& /*aaBalance*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4Cpp::SetVolumeLimit(uint32_t /*aVersion*/, uint32_t /*aaVolumeLimit*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4Cpp::VolumeLimit(uint32_t /*aVersion*/, uint32_t& /*aaVolumeLimit*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4Cpp::SetStartupVolume(uint32_t /*aVersion*/, uint32_t /*aaStartupVolume*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4Cpp::StartupVolume(uint32_t /*aVersion*/, uint32_t& /*aaStartupVolume*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4Cpp::SetStartupVolumeEnabled(uint32_t /*aVersion*/, bool /*aaStartupVolumeEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4Cpp::StartupVolumeEnabled(uint32_t /*aVersion*/, bool& /*aaStartupVolumeEnabled*/)
{
    ASSERTS();
}

