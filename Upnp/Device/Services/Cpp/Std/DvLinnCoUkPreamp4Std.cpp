#include <Std/DvLinnCoUkPreamp4.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

bool DvProviderLinnCoUkPreamp4Cpp::SetPropertyVolume(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyVolume, aValue);
}

void DvProviderLinnCoUkPreamp4Cpp::GetPropertyVolume(uint32_t& aValue)
{
    aValue = iPropertyVolume->Value();
}

bool DvProviderLinnCoUkPreamp4Cpp::SetPropertyMute(bool aValue)
{
    return SetPropertyBool(*iPropertyMute, aValue);
}

void DvProviderLinnCoUkPreamp4Cpp::GetPropertyMute(bool& aValue)
{
    aValue = iPropertyMute->Value();
}

bool DvProviderLinnCoUkPreamp4Cpp::SetPropertyBalance(int32_t aValue)
{
    return SetPropertyInt(*iPropertyBalance, aValue);
}

void DvProviderLinnCoUkPreamp4Cpp::GetPropertyBalance(int32_t& aValue)
{
    aValue = iPropertyBalance->Value();
}

bool DvProviderLinnCoUkPreamp4Cpp::SetPropertyVolumeLimit(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyVolumeLimit, aValue);
}

void DvProviderLinnCoUkPreamp4Cpp::GetPropertyVolumeLimit(uint32_t& aValue)
{
    aValue = iPropertyVolumeLimit->Value();
}

bool DvProviderLinnCoUkPreamp4Cpp::SetPropertyStartupVolume(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyStartupVolume, aValue);
}

void DvProviderLinnCoUkPreamp4Cpp::GetPropertyStartupVolume(uint32_t& aValue)
{
    aValue = iPropertyStartupVolume->Value();
}

bool DvProviderLinnCoUkPreamp4Cpp::SetPropertyStartupVolumeEnabled(bool aValue)
{
    return SetPropertyBool(*iPropertyStartupVolumeEnabled, aValue);
}

void DvProviderLinnCoUkPreamp4Cpp::GetPropertyStartupVolumeEnabled(bool& aValue)
{
    aValue = iPropertyStartupVolumeEnabled->Value();
}

DvProviderLinnCoUkPreamp4Cpp::DvProviderLinnCoUkPreamp4Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Preamp", 4)
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

void DvProviderLinnCoUkPreamp4Cpp::EnableActionVolumeInc()
{
    Zapp::Action* action = new Zapp::Action("VolumeInc");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoVolumeInc);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::EnableActionVolumeDec()
{
    Zapp::Action* action = new Zapp::Action("VolumeDec");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoVolumeDec);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::EnableActionSetVolume()
{
    Zapp::Action* action = new Zapp::Action("SetVolume");
    action->AddInputParameter(new ParameterUint("aVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::EnableActionVolume()
{
    Zapp::Action* action = new Zapp::Action("Volume");
    action->AddOutputParameter(new ParameterUint("aVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoVolume);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::EnableActionSetMute()
{
    Zapp::Action* action = new Zapp::Action("SetMute");
    action->AddInputParameter(new ParameterBool("aMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::EnableActionMute()
{
    Zapp::Action* action = new Zapp::Action("Mute");
    action->AddOutputParameter(new ParameterBool("aMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoMute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::EnableActionSetBalance()
{
    Zapp::Action* action = new Zapp::Action("SetBalance");
    action->AddInputParameter(new ParameterInt("aBalance"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoSetBalance);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::EnableActionBalance()
{
    Zapp::Action* action = new Zapp::Action("Balance");
    action->AddOutputParameter(new ParameterInt("aBalance"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoBalance);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::EnableActionSetVolumeLimit()
{
    Zapp::Action* action = new Zapp::Action("SetVolumeLimit");
    action->AddInputParameter(new ParameterUint("aVolumeLimit"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoSetVolumeLimit);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::EnableActionVolumeLimit()
{
    Zapp::Action* action = new Zapp::Action("VolumeLimit");
    action->AddOutputParameter(new ParameterUint("aVolumeLimit"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoVolumeLimit);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::EnableActionSetStartupVolume()
{
    Zapp::Action* action = new Zapp::Action("SetStartupVolume");
    action->AddInputParameter(new ParameterUint("aStartupVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoSetStartupVolume);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::EnableActionStartupVolume()
{
    Zapp::Action* action = new Zapp::Action("StartupVolume");
    action->AddOutputParameter(new ParameterUint("aStartupVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoStartupVolume);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::EnableActionSetStartupVolumeEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetStartupVolumeEnabled");
    action->AddInputParameter(new ParameterBool("aStartupVolumeEnabled"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoSetStartupVolumeEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::EnableActionStartupVolumeEnabled()
{
    Zapp::Action* action = new Zapp::Action("StartupVolumeEnabled");
    action->AddOutputParameter(new ParameterBool("aStartupVolumeEnabled"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4Cpp::DoStartupVolumeEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4Cpp::DoVolumeInc(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    VolumeInc(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPreamp4Cpp::DoVolumeDec(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    VolumeDec(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPreamp4Cpp::DoSetVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aVolume = aInvocation.InvocationReadUint("aVolume");
    aInvocation.InvocationReadEnd();
    SetVolume(aVersion, aVolume);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPreamp4Cpp::DoVolume(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkPreamp4Cpp::DoSetMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aMute = aInvocation.InvocationReadBool("aMute");
    aInvocation.InvocationReadEnd();
    SetMute(aVersion, aMute);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPreamp4Cpp::DoMute(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkPreamp4Cpp::DoSetBalance(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t aBalance = aInvocation.InvocationReadInt("aBalance");
    aInvocation.InvocationReadEnd();
    SetBalance(aVersion, aBalance);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPreamp4Cpp::DoBalance(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkPreamp4Cpp::DoSetVolumeLimit(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aVolumeLimit = aInvocation.InvocationReadUint("aVolumeLimit");
    aInvocation.InvocationReadEnd();
    SetVolumeLimit(aVersion, aVolumeLimit);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPreamp4Cpp::DoVolumeLimit(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkPreamp4Cpp::DoSetStartupVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aStartupVolume = aInvocation.InvocationReadUint("aStartupVolume");
    aInvocation.InvocationReadEnd();
    SetStartupVolume(aVersion, aStartupVolume);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPreamp4Cpp::DoStartupVolume(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkPreamp4Cpp::DoSetStartupVolumeEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aStartupVolumeEnabled = aInvocation.InvocationReadBool("aStartupVolumeEnabled");
    aInvocation.InvocationReadEnd();
    SetStartupVolumeEnabled(aVersion, aStartupVolumeEnabled);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPreamp4Cpp::DoStartupVolumeEnabled(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkPreamp4Cpp::VolumeInc(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4Cpp::VolumeDec(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4Cpp::SetVolume(uint32_t /*aVersion*/, uint32_t /*aaVolume*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4Cpp::Volume(uint32_t /*aVersion*/, uint32_t& /*aaVolume*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4Cpp::SetMute(uint32_t /*aVersion*/, bool /*aaMute*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4Cpp::Mute(uint32_t /*aVersion*/, bool& /*aaMute*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4Cpp::SetBalance(uint32_t /*aVersion*/, int32_t /*aaBalance*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4Cpp::Balance(uint32_t /*aVersion*/, int32_t& /*aaBalance*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4Cpp::SetVolumeLimit(uint32_t /*aVersion*/, uint32_t /*aaVolumeLimit*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4Cpp::VolumeLimit(uint32_t /*aVersion*/, uint32_t& /*aaVolumeLimit*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4Cpp::SetStartupVolume(uint32_t /*aVersion*/, uint32_t /*aaStartupVolume*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4Cpp::StartupVolume(uint32_t /*aVersion*/, uint32_t& /*aaStartupVolume*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4Cpp::SetStartupVolumeEnabled(uint32_t /*aVersion*/, bool /*aaStartupVolumeEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4Cpp::StartupVolumeEnabled(uint32_t /*aVersion*/, bool& /*aaStartupVolumeEnabled*/)
{
    ASSERTS();
}

