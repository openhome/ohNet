#include "DvLinnCoUkPreamp4.h"
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkPreamp4::SetPropertyVolume(TUint aValue)
{
    return SetPropertyUint(*iPropertyVolume, aValue);
}

void DvProviderLinnCoUkPreamp4::GetPropertyVolume(TUint& aValue)
{
    aValue = iPropertyVolume->Value();
}

TBool DvProviderLinnCoUkPreamp4::SetPropertyMute(TBool aValue)
{
    return SetPropertyBool(*iPropertyMute, aValue);
}

void DvProviderLinnCoUkPreamp4::GetPropertyMute(TBool& aValue)
{
    aValue = iPropertyMute->Value();
}

TBool DvProviderLinnCoUkPreamp4::SetPropertyBalance(TInt aValue)
{
    return SetPropertyInt(*iPropertyBalance, aValue);
}

void DvProviderLinnCoUkPreamp4::GetPropertyBalance(TInt& aValue)
{
    aValue = iPropertyBalance->Value();
}

TBool DvProviderLinnCoUkPreamp4::SetPropertyVolumeLimit(TUint aValue)
{
    return SetPropertyUint(*iPropertyVolumeLimit, aValue);
}

void DvProviderLinnCoUkPreamp4::GetPropertyVolumeLimit(TUint& aValue)
{
    aValue = iPropertyVolumeLimit->Value();
}

TBool DvProviderLinnCoUkPreamp4::SetPropertyStartupVolume(TUint aValue)
{
    return SetPropertyUint(*iPropertyStartupVolume, aValue);
}

void DvProviderLinnCoUkPreamp4::GetPropertyStartupVolume(TUint& aValue)
{
    aValue = iPropertyStartupVolume->Value();
}

TBool DvProviderLinnCoUkPreamp4::SetPropertyStartupVolumeEnabled(TBool aValue)
{
    return SetPropertyBool(*iPropertyStartupVolumeEnabled, aValue);
}

void DvProviderLinnCoUkPreamp4::GetPropertyStartupVolumeEnabled(TBool& aValue)
{
    aValue = iPropertyStartupVolumeEnabled->Value();
}

DvProviderLinnCoUkPreamp4::DvProviderLinnCoUkPreamp4(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Preamp", 4)
{
    
    iPropertyVolume = new PropertyUint(new ParameterUint("Volume"));
    iService->AddProperty(iPropertyVolume); // passes ownership
    iPropertyMute = new PropertyBool(new ParameterBool("Mute"));
    iService->AddProperty(iPropertyMute); // passes ownership
    iPropertyBalance = new PropertyInt(new ParameterInt("Balance"));
    iService->AddProperty(iPropertyBalance); // passes ownership
    iPropertyVolumeLimit = new PropertyUint(new ParameterUint("VolumeLimit"));
    iService->AddProperty(iPropertyVolumeLimit); // passes ownership
    iPropertyStartupVolume = new PropertyUint(new ParameterUint("StartupVolume"));
    iService->AddProperty(iPropertyStartupVolume); // passes ownership
    iPropertyStartupVolumeEnabled = new PropertyBool(new ParameterBool("StartupVolumeEnabled"));
    iService->AddProperty(iPropertyStartupVolumeEnabled); // passes ownership
}

void DvProviderLinnCoUkPreamp4::EnableActionVolumeInc()
{
    Zapp::Action* action = new Zapp::Action("VolumeInc");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoVolumeInc);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::EnableActionVolumeDec()
{
    Zapp::Action* action = new Zapp::Action("VolumeDec");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoVolumeDec);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::EnableActionSetVolume()
{
    Zapp::Action* action = new Zapp::Action("SetVolume");
    action->AddInputParameter(new ParameterUint("aVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::EnableActionVolume()
{
    Zapp::Action* action = new Zapp::Action("Volume");
    action->AddOutputParameter(new ParameterUint("aVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoVolume);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::EnableActionSetMute()
{
    Zapp::Action* action = new Zapp::Action("SetMute");
    action->AddInputParameter(new ParameterBool("aMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::EnableActionMute()
{
    Zapp::Action* action = new Zapp::Action("Mute");
    action->AddOutputParameter(new ParameterBool("aMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoMute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::EnableActionSetBalance()
{
    Zapp::Action* action = new Zapp::Action("SetBalance");
    action->AddInputParameter(new ParameterInt("aBalance"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoSetBalance);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::EnableActionBalance()
{
    Zapp::Action* action = new Zapp::Action("Balance");
    action->AddOutputParameter(new ParameterInt("aBalance"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoBalance);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::EnableActionSetVolumeLimit()
{
    Zapp::Action* action = new Zapp::Action("SetVolumeLimit");
    action->AddInputParameter(new ParameterUint("aVolumeLimit"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoSetVolumeLimit);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::EnableActionVolumeLimit()
{
    Zapp::Action* action = new Zapp::Action("VolumeLimit");
    action->AddOutputParameter(new ParameterUint("aVolumeLimit"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoVolumeLimit);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::EnableActionSetStartupVolume()
{
    Zapp::Action* action = new Zapp::Action("SetStartupVolume");
    action->AddInputParameter(new ParameterUint("aStartupVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoSetStartupVolume);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::EnableActionStartupVolume()
{
    Zapp::Action* action = new Zapp::Action("StartupVolume");
    action->AddOutputParameter(new ParameterUint("aStartupVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoStartupVolume);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::EnableActionSetStartupVolumeEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetStartupVolumeEnabled");
    action->AddInputParameter(new ParameterBool("aStartupVolumeEnabled"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoSetStartupVolumeEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::EnableActionStartupVolumeEnabled()
{
    Zapp::Action* action = new Zapp::Action("StartupVolumeEnabled");
    action->AddOutputParameter(new ParameterBool("aStartupVolumeEnabled"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4::DoStartupVolumeEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4::DoVolumeInc(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    VolumeInc(resp, aVersion);
}

void DvProviderLinnCoUkPreamp4::DoVolumeDec(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    VolumeDec(resp, aVersion);
}

void DvProviderLinnCoUkPreamp4::DoSetVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aVolume = aInvocation.InvocationReadUint("aVolume");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetVolume(resp, aVersion, aVolume);
}

void DvProviderLinnCoUkPreamp4::DoVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaVolume(aInvocation, "aVolume");
    Volume(resp, aVersion, respaVolume);
}

void DvProviderLinnCoUkPreamp4::DoSetMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aMute = aInvocation.InvocationReadBool("aMute");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetMute(resp, aVersion, aMute);
}

void DvProviderLinnCoUkPreamp4::DoMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaMute(aInvocation, "aMute");
    Mute(resp, aVersion, respaMute);
}

void DvProviderLinnCoUkPreamp4::DoSetBalance(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aBalance = aInvocation.InvocationReadInt("aBalance");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBalance(resp, aVersion, aBalance);
}

void DvProviderLinnCoUkPreamp4::DoBalance(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respaBalance(aInvocation, "aBalance");
    Balance(resp, aVersion, respaBalance);
}

void DvProviderLinnCoUkPreamp4::DoSetVolumeLimit(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aVolumeLimit = aInvocation.InvocationReadUint("aVolumeLimit");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetVolumeLimit(resp, aVersion, aVolumeLimit);
}

void DvProviderLinnCoUkPreamp4::DoVolumeLimit(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaVolumeLimit(aInvocation, "aVolumeLimit");
    VolumeLimit(resp, aVersion, respaVolumeLimit);
}

void DvProviderLinnCoUkPreamp4::DoSetStartupVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aStartupVolume = aInvocation.InvocationReadUint("aStartupVolume");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStartupVolume(resp, aVersion, aStartupVolume);
}

void DvProviderLinnCoUkPreamp4::DoStartupVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaStartupVolume(aInvocation, "aStartupVolume");
    StartupVolume(resp, aVersion, respaStartupVolume);
}

void DvProviderLinnCoUkPreamp4::DoSetStartupVolumeEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aStartupVolumeEnabled = aInvocation.InvocationReadBool("aStartupVolumeEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStartupVolumeEnabled(resp, aVersion, aStartupVolumeEnabled);
}

void DvProviderLinnCoUkPreamp4::DoStartupVolumeEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaStartupVolumeEnabled(aInvocation, "aStartupVolumeEnabled");
    StartupVolumeEnabled(resp, aVersion, respaStartupVolumeEnabled);
}

void DvProviderLinnCoUkPreamp4::VolumeInc(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4::VolumeDec(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4::SetVolume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaVolume*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4::Volume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaVolume*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4::SetMute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaMute*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4::Mute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaMute*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4::SetBalance(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aaBalance*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4::Balance(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseInt& /*aaBalance*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4::SetVolumeLimit(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaVolumeLimit*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4::VolumeLimit(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaVolumeLimit*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4::SetStartupVolume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaStartupVolume*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4::StartupVolume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaStartupVolume*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4::SetStartupVolumeEnabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaStartupVolumeEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPreamp4::StartupVolumeEnabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaStartupVolumeEnabled*/)
{
    ASSERTS();
}

