#include <Core/DvLinnCoUkPreamp4.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkPreamp4::SetPropertyVolume(TUint aValue)
{
    SetPropertyUint(*iPropertyVolume, aValue);
}

void DvServiceLinnCoUkPreamp4::GetPropertyVolume(TUint& aValue)
{
    aValue = iPropertyVolume->Value();
}

void DvServiceLinnCoUkPreamp4::SetPropertyMute(TBool aValue)
{
    SetPropertyBool(*iPropertyMute, aValue);
}

void DvServiceLinnCoUkPreamp4::GetPropertyMute(TBool& aValue)
{
    aValue = iPropertyMute->Value();
}

void DvServiceLinnCoUkPreamp4::SetPropertyBalance(TInt aValue)
{
    SetPropertyInt(*iPropertyBalance, aValue);
}

void DvServiceLinnCoUkPreamp4::GetPropertyBalance(TInt& aValue)
{
    aValue = iPropertyBalance->Value();
}

void DvServiceLinnCoUkPreamp4::SetPropertyVolumeLimit(TUint aValue)
{
    SetPropertyUint(*iPropertyVolumeLimit, aValue);
}

void DvServiceLinnCoUkPreamp4::GetPropertyVolumeLimit(TUint& aValue)
{
    aValue = iPropertyVolumeLimit->Value();
}

void DvServiceLinnCoUkPreamp4::SetPropertyStartupVolume(TUint aValue)
{
    SetPropertyUint(*iPropertyStartupVolume, aValue);
}

void DvServiceLinnCoUkPreamp4::GetPropertyStartupVolume(TUint& aValue)
{
    aValue = iPropertyStartupVolume->Value();
}

void DvServiceLinnCoUkPreamp4::SetPropertyStartupVolumeEnabled(TBool aValue)
{
    SetPropertyBool(*iPropertyStartupVolumeEnabled, aValue);
}

void DvServiceLinnCoUkPreamp4::GetPropertyStartupVolumeEnabled(TBool& aValue)
{
    aValue = iPropertyStartupVolumeEnabled->Value();
}

DvServiceLinnCoUkPreamp4::DvServiceLinnCoUkPreamp4(DvDevice& aDevice)
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

void DvServiceLinnCoUkPreamp4::EnableActionVolumeInc()
{
    Zapp::Action* action = new Zapp::Action("VolumeInc");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoVolumeInc);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::EnableActionVolumeDec()
{
    Zapp::Action* action = new Zapp::Action("VolumeDec");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoVolumeDec);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::EnableActionSetVolume()
{
    Zapp::Action* action = new Zapp::Action("SetVolume");
    action->AddInputParameter(new ParameterUint("aVolume"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::EnableActionVolume()
{
    Zapp::Action* action = new Zapp::Action("Volume");
    action->AddOutputParameter(new ParameterUint("aVolume"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoVolume);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::EnableActionSetMute()
{
    Zapp::Action* action = new Zapp::Action("SetMute");
    action->AddInputParameter(new ParameterBool("aMute"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoSetMute);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::EnableActionMute()
{
    Zapp::Action* action = new Zapp::Action("Mute");
    action->AddOutputParameter(new ParameterBool("aMute"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoMute);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::EnableActionSetBalance()
{
    Zapp::Action* action = new Zapp::Action("SetBalance");
    action->AddInputParameter(new ParameterInt("aBalance"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoSetBalance);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::EnableActionBalance()
{
    Zapp::Action* action = new Zapp::Action("Balance");
    action->AddOutputParameter(new ParameterInt("aBalance"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoBalance);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::EnableActionSetVolumeLimit()
{
    Zapp::Action* action = new Zapp::Action("SetVolumeLimit");
    action->AddInputParameter(new ParameterUint("aVolumeLimit"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoSetVolumeLimit);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::EnableActionVolumeLimit()
{
    Zapp::Action* action = new Zapp::Action("VolumeLimit");
    action->AddOutputParameter(new ParameterUint("aVolumeLimit"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoVolumeLimit);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::EnableActionSetStartupVolume()
{
    Zapp::Action* action = new Zapp::Action("SetStartupVolume");
    action->AddInputParameter(new ParameterUint("aStartupVolume"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoSetStartupVolume);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::EnableActionStartupVolume()
{
    Zapp::Action* action = new Zapp::Action("StartupVolume");
    action->AddOutputParameter(new ParameterUint("aStartupVolume"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoStartupVolume);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::EnableActionSetStartupVolumeEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetStartupVolumeEnabled");
    action->AddInputParameter(new ParameterBool("aStartupVolumeEnabled"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoSetStartupVolumeEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::EnableActionStartupVolumeEnabled()
{
    Zapp::Action* action = new Zapp::Action("StartupVolumeEnabled");
    action->AddOutputParameter(new ParameterBool("aStartupVolumeEnabled"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPreamp4::DoStartupVolumeEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPreamp4::DoVolumeInc(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    VolumeInc(resp, aVersion);
}

void DvServiceLinnCoUkPreamp4::DoVolumeDec(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    VolumeDec(resp, aVersion);
}

void DvServiceLinnCoUkPreamp4::DoSetVolume(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aVolume = aInvocation.InvocationReadUint("aVolume");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetVolume(resp, aVersion, aVolume);
}

void DvServiceLinnCoUkPreamp4::DoVolume(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaVolume(aInvocation, "aVolume");
    Volume(resp, aVersion, respaVolume);
}

void DvServiceLinnCoUkPreamp4::DoSetMute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aMute = aInvocation.InvocationReadBool("aMute");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetMute(resp, aVersion, aMute);
}

void DvServiceLinnCoUkPreamp4::DoMute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaMute(aInvocation, "aMute");
    Mute(resp, aVersion, respaMute);
}

void DvServiceLinnCoUkPreamp4::DoSetBalance(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aBalance = aInvocation.InvocationReadInt("aBalance");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBalance(resp, aVersion, aBalance);
}

void DvServiceLinnCoUkPreamp4::DoBalance(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respaBalance(aInvocation, "aBalance");
    Balance(resp, aVersion, respaBalance);
}

void DvServiceLinnCoUkPreamp4::DoSetVolumeLimit(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aVolumeLimit = aInvocation.InvocationReadUint("aVolumeLimit");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetVolumeLimit(resp, aVersion, aVolumeLimit);
}

void DvServiceLinnCoUkPreamp4::DoVolumeLimit(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaVolumeLimit(aInvocation, "aVolumeLimit");
    VolumeLimit(resp, aVersion, respaVolumeLimit);
}

void DvServiceLinnCoUkPreamp4::DoSetStartupVolume(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aStartupVolume = aInvocation.InvocationReadUint("aStartupVolume");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStartupVolume(resp, aVersion, aStartupVolume);
}

void DvServiceLinnCoUkPreamp4::DoStartupVolume(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaStartupVolume(aInvocation, "aStartupVolume");
    StartupVolume(resp, aVersion, respaStartupVolume);
}

void DvServiceLinnCoUkPreamp4::DoSetStartupVolumeEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aStartupVolumeEnabled = aInvocation.InvocationReadBool("aStartupVolumeEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStartupVolumeEnabled(resp, aVersion, aStartupVolumeEnabled);
}

void DvServiceLinnCoUkPreamp4::DoStartupVolumeEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaStartupVolumeEnabled(aInvocation, "aStartupVolumeEnabled");
    StartupVolumeEnabled(resp, aVersion, respaStartupVolumeEnabled);
}

void DvServiceLinnCoUkPreamp4::VolumeInc(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4::VolumeDec(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4::SetVolume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaVolume*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4::Volume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaVolume*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4::SetMute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaMute*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4::Mute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaMute*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4::SetBalance(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aaBalance*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4::Balance(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseInt& /*aaBalance*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4::SetVolumeLimit(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaVolumeLimit*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4::VolumeLimit(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaVolumeLimit*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4::SetStartupVolume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaStartupVolume*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4::StartupVolume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaStartupVolume*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4::SetStartupVolumeEnabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaStartupVolumeEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPreamp4::StartupVolumeEnabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaStartupVolumeEnabled*/)
{
    ASSERTS();
}

