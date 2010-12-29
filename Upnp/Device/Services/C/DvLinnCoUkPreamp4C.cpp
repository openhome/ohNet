#include "DvLinnCoUkPreamp4.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderLinnCoUkPreamp4C : public DvProvider
{
public:
    DvProviderLinnCoUkPreamp4C(DvDeviceC aDevice);
    TBool SetPropertyVolume(TUint aValue);
    void GetPropertyVolume(TUint& aValue);
    TBool SetPropertyMute(TBool aValue);
    void GetPropertyMute(TBool& aValue);
    TBool SetPropertyBalance(TInt aValue);
    void GetPropertyBalance(TInt& aValue);
    TBool SetPropertyVolumeLimit(TUint aValue);
    void GetPropertyVolumeLimit(TUint& aValue);
    TBool SetPropertyStartupVolume(TUint aValue);
    void GetPropertyStartupVolume(TUint& aValue);
    TBool SetPropertyStartupVolumeEnabled(TBool aValue);
    void GetPropertyStartupVolumeEnabled(TBool& aValue);
    void EnableActionVolumeInc(CallbackPreamp4VolumeInc aCallback, void* aPtr);
    void EnableActionVolumeDec(CallbackPreamp4VolumeDec aCallback, void* aPtr);
    void EnableActionSetVolume(CallbackPreamp4SetVolume aCallback, void* aPtr);
    void EnableActionVolume(CallbackPreamp4Volume aCallback, void* aPtr);
    void EnableActionSetMute(CallbackPreamp4SetMute aCallback, void* aPtr);
    void EnableActionMute(CallbackPreamp4Mute aCallback, void* aPtr);
    void EnableActionSetBalance(CallbackPreamp4SetBalance aCallback, void* aPtr);
    void EnableActionBalance(CallbackPreamp4Balance aCallback, void* aPtr);
    void EnableActionSetVolumeLimit(CallbackPreamp4SetVolumeLimit aCallback, void* aPtr);
    void EnableActionVolumeLimit(CallbackPreamp4VolumeLimit aCallback, void* aPtr);
    void EnableActionSetStartupVolume(CallbackPreamp4SetStartupVolume aCallback, void* aPtr);
    void EnableActionStartupVolume(CallbackPreamp4StartupVolume aCallback, void* aPtr);
    void EnableActionSetStartupVolumeEnabled(CallbackPreamp4SetStartupVolumeEnabled aCallback, void* aPtr);
    void EnableActionStartupVolumeEnabled(CallbackPreamp4StartupVolumeEnabled aCallback, void* aPtr);
private:
    void DoVolumeInc(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolumeDec(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetMute(IDviInvocation& aInvocation, TUint aVersion);
    void DoMute(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBalance(IDviInvocation& aInvocation, TUint aVersion);
    void DoBalance(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolumeLimit(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolumeLimit(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStartupVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartupVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStartupVolumeEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartupVolumeEnabled(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackPreamp4VolumeInc iCallbackVolumeInc;
    void* iPtrVolumeInc;
    CallbackPreamp4VolumeDec iCallbackVolumeDec;
    void* iPtrVolumeDec;
    CallbackPreamp4SetVolume iCallbackSetVolume;
    void* iPtrSetVolume;
    CallbackPreamp4Volume iCallbackVolume;
    void* iPtrVolume;
    CallbackPreamp4SetMute iCallbackSetMute;
    void* iPtrSetMute;
    CallbackPreamp4Mute iCallbackMute;
    void* iPtrMute;
    CallbackPreamp4SetBalance iCallbackSetBalance;
    void* iPtrSetBalance;
    CallbackPreamp4Balance iCallbackBalance;
    void* iPtrBalance;
    CallbackPreamp4SetVolumeLimit iCallbackSetVolumeLimit;
    void* iPtrSetVolumeLimit;
    CallbackPreamp4VolumeLimit iCallbackVolumeLimit;
    void* iPtrVolumeLimit;
    CallbackPreamp4SetStartupVolume iCallbackSetStartupVolume;
    void* iPtrSetStartupVolume;
    CallbackPreamp4StartupVolume iCallbackStartupVolume;
    void* iPtrStartupVolume;
    CallbackPreamp4SetStartupVolumeEnabled iCallbackSetStartupVolumeEnabled;
    void* iPtrSetStartupVolumeEnabled;
    CallbackPreamp4StartupVolumeEnabled iCallbackStartupVolumeEnabled;
    void* iPtrStartupVolumeEnabled;
    PropertyUint* iPropertyVolume;
    PropertyBool* iPropertyMute;
    PropertyInt* iPropertyBalance;
    PropertyUint* iPropertyVolumeLimit;
    PropertyUint* iPropertyStartupVolume;
    PropertyBool* iPropertyStartupVolumeEnabled;
};

DvProviderLinnCoUkPreamp4C::DvProviderLinnCoUkPreamp4C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Preamp", 4)
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

TBool DvProviderLinnCoUkPreamp4C::SetPropertyVolume(TUint aValue)
{
    return SetPropertyUint(*iPropertyVolume, aValue);
}

void DvProviderLinnCoUkPreamp4C::GetPropertyVolume(TUint& aValue)
{
    aValue = iPropertyVolume->Value();
}

TBool DvProviderLinnCoUkPreamp4C::SetPropertyMute(TBool aValue)
{
    return SetPropertyBool(*iPropertyMute, aValue);
}

void DvProviderLinnCoUkPreamp4C::GetPropertyMute(TBool& aValue)
{
    aValue = iPropertyMute->Value();
}

TBool DvProviderLinnCoUkPreamp4C::SetPropertyBalance(TInt aValue)
{
    return SetPropertyInt(*iPropertyBalance, aValue);
}

void DvProviderLinnCoUkPreamp4C::GetPropertyBalance(TInt& aValue)
{
    aValue = iPropertyBalance->Value();
}

TBool DvProviderLinnCoUkPreamp4C::SetPropertyVolumeLimit(TUint aValue)
{
    return SetPropertyUint(*iPropertyVolumeLimit, aValue);
}

void DvProviderLinnCoUkPreamp4C::GetPropertyVolumeLimit(TUint& aValue)
{
    aValue = iPropertyVolumeLimit->Value();
}

TBool DvProviderLinnCoUkPreamp4C::SetPropertyStartupVolume(TUint aValue)
{
    return SetPropertyUint(*iPropertyStartupVolume, aValue);
}

void DvProviderLinnCoUkPreamp4C::GetPropertyStartupVolume(TUint& aValue)
{
    aValue = iPropertyStartupVolume->Value();
}

TBool DvProviderLinnCoUkPreamp4C::SetPropertyStartupVolumeEnabled(TBool aValue)
{
    return SetPropertyBool(*iPropertyStartupVolumeEnabled, aValue);
}

void DvProviderLinnCoUkPreamp4C::GetPropertyStartupVolumeEnabled(TBool& aValue)
{
    aValue = iPropertyStartupVolumeEnabled->Value();
}

void DvProviderLinnCoUkPreamp4C::EnableActionVolumeInc(CallbackPreamp4VolumeInc aCallback, void* aPtr)
{
    iCallbackVolumeInc = aCallback;
    iPtrVolumeInc = aPtr;
    Zapp::Action* action = new Zapp::Action("VolumeInc");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoVolumeInc);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::EnableActionVolumeDec(CallbackPreamp4VolumeDec aCallback, void* aPtr)
{
    iCallbackVolumeDec = aCallback;
    iPtrVolumeDec = aPtr;
    Zapp::Action* action = new Zapp::Action("VolumeDec");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoVolumeDec);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::EnableActionSetVolume(CallbackPreamp4SetVolume aCallback, void* aPtr)
{
    iCallbackSetVolume = aCallback;
    iPtrSetVolume = aPtr;
    Zapp::Action* action = new Zapp::Action("SetVolume");
    action->AddInputParameter(new ParameterUint("aVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::EnableActionVolume(CallbackPreamp4Volume aCallback, void* aPtr)
{
    iCallbackVolume = aCallback;
    iPtrVolume = aPtr;
    Zapp::Action* action = new Zapp::Action("Volume");
    action->AddOutputParameter(new ParameterUint("aVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoVolume);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::EnableActionSetMute(CallbackPreamp4SetMute aCallback, void* aPtr)
{
    iCallbackSetMute = aCallback;
    iPtrSetMute = aPtr;
    Zapp::Action* action = new Zapp::Action("SetMute");
    action->AddInputParameter(new ParameterBool("aMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::EnableActionMute(CallbackPreamp4Mute aCallback, void* aPtr)
{
    iCallbackMute = aCallback;
    iPtrMute = aPtr;
    Zapp::Action* action = new Zapp::Action("Mute");
    action->AddOutputParameter(new ParameterBool("aMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoMute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::EnableActionSetBalance(CallbackPreamp4SetBalance aCallback, void* aPtr)
{
    iCallbackSetBalance = aCallback;
    iPtrSetBalance = aPtr;
    Zapp::Action* action = new Zapp::Action("SetBalance");
    action->AddInputParameter(new ParameterInt("aBalance"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoSetBalance);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::EnableActionBalance(CallbackPreamp4Balance aCallback, void* aPtr)
{
    iCallbackBalance = aCallback;
    iPtrBalance = aPtr;
    Zapp::Action* action = new Zapp::Action("Balance");
    action->AddOutputParameter(new ParameterInt("aBalance"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoBalance);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::EnableActionSetVolumeLimit(CallbackPreamp4SetVolumeLimit aCallback, void* aPtr)
{
    iCallbackSetVolumeLimit = aCallback;
    iPtrSetVolumeLimit = aPtr;
    Zapp::Action* action = new Zapp::Action("SetVolumeLimit");
    action->AddInputParameter(new ParameterUint("aVolumeLimit"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoSetVolumeLimit);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::EnableActionVolumeLimit(CallbackPreamp4VolumeLimit aCallback, void* aPtr)
{
    iCallbackVolumeLimit = aCallback;
    iPtrVolumeLimit = aPtr;
    Zapp::Action* action = new Zapp::Action("VolumeLimit");
    action->AddOutputParameter(new ParameterUint("aVolumeLimit"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoVolumeLimit);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::EnableActionSetStartupVolume(CallbackPreamp4SetStartupVolume aCallback, void* aPtr)
{
    iCallbackSetStartupVolume = aCallback;
    iPtrSetStartupVolume = aPtr;
    Zapp::Action* action = new Zapp::Action("SetStartupVolume");
    action->AddInputParameter(new ParameterUint("aStartupVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoSetStartupVolume);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::EnableActionStartupVolume(CallbackPreamp4StartupVolume aCallback, void* aPtr)
{
    iCallbackStartupVolume = aCallback;
    iPtrStartupVolume = aPtr;
    Zapp::Action* action = new Zapp::Action("StartupVolume");
    action->AddOutputParameter(new ParameterUint("aStartupVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoStartupVolume);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::EnableActionSetStartupVolumeEnabled(CallbackPreamp4SetStartupVolumeEnabled aCallback, void* aPtr)
{
    iCallbackSetStartupVolumeEnabled = aCallback;
    iPtrSetStartupVolumeEnabled = aPtr;
    Zapp::Action* action = new Zapp::Action("SetStartupVolumeEnabled");
    action->AddInputParameter(new ParameterBool("aStartupVolumeEnabled"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoSetStartupVolumeEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::EnableActionStartupVolumeEnabled(CallbackPreamp4StartupVolumeEnabled aCallback, void* aPtr)
{
    iCallbackStartupVolumeEnabled = aCallback;
    iPtrStartupVolumeEnabled = aPtr;
    Zapp::Action* action = new Zapp::Action("StartupVolumeEnabled");
    action->AddOutputParameter(new ParameterBool("aStartupVolumeEnabled"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPreamp4C::DoStartupVolumeEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPreamp4C::DoVolumeInc(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackVolumeInc != NULL);
    if (0 != iCallbackVolumeInc(iPtrVolumeInc, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkPreamp4C::DoVolumeDec(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackVolumeDec != NULL);
    if (0 != iCallbackVolumeDec(iPtrVolumeDec, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkPreamp4C::DoSetVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aVolume = aInvocation.InvocationReadUint("aVolume");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetVolume != NULL);
    if (0 != iCallbackSetVolume(iPtrSetVolume, aVersion, aVolume)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkPreamp4C::DoVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aVolume;
    ASSERT(iCallbackVolume != NULL);
    if (0 != iCallbackVolume(iPtrVolume, aVersion, &aVolume)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaVolume(aInvocation, "aVolume");
    resp.Start();
    respaVolume.Write(aVolume);
    resp.End();
}

void DvProviderLinnCoUkPreamp4C::DoSetMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aMute = aInvocation.InvocationReadBool("aMute");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetMute != NULL);
    if (0 != iCallbackSetMute(iPtrSetMute, aVersion, aMute)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkPreamp4C::DoMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aMute;
    ASSERT(iCallbackMute != NULL);
    if (0 != iCallbackMute(iPtrMute, aVersion, &aMute)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaMute(aInvocation, "aMute");
    resp.Start();
    respaMute.Write((aMute!=0));
    resp.End();
}

void DvProviderLinnCoUkPreamp4C::DoSetBalance(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aBalance = aInvocation.InvocationReadInt("aBalance");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetBalance != NULL);
    if (0 != iCallbackSetBalance(iPtrSetBalance, aVersion, aBalance)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkPreamp4C::DoBalance(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    int32_t aBalance;
    ASSERT(iCallbackBalance != NULL);
    if (0 != iCallbackBalance(iPtrBalance, aVersion, &aBalance)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseInt respaBalance(aInvocation, "aBalance");
    resp.Start();
    respaBalance.Write(aBalance);
    resp.End();
}

void DvProviderLinnCoUkPreamp4C::DoSetVolumeLimit(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aVolumeLimit = aInvocation.InvocationReadUint("aVolumeLimit");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetVolumeLimit != NULL);
    if (0 != iCallbackSetVolumeLimit(iPtrSetVolumeLimit, aVersion, aVolumeLimit)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkPreamp4C::DoVolumeLimit(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aVolumeLimit;
    ASSERT(iCallbackVolumeLimit != NULL);
    if (0 != iCallbackVolumeLimit(iPtrVolumeLimit, aVersion, &aVolumeLimit)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaVolumeLimit(aInvocation, "aVolumeLimit");
    resp.Start();
    respaVolumeLimit.Write(aVolumeLimit);
    resp.End();
}

void DvProviderLinnCoUkPreamp4C::DoSetStartupVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aStartupVolume = aInvocation.InvocationReadUint("aStartupVolume");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetStartupVolume != NULL);
    if (0 != iCallbackSetStartupVolume(iPtrSetStartupVolume, aVersion, aStartupVolume)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkPreamp4C::DoStartupVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aStartupVolume;
    ASSERT(iCallbackStartupVolume != NULL);
    if (0 != iCallbackStartupVolume(iPtrStartupVolume, aVersion, &aStartupVolume)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaStartupVolume(aInvocation, "aStartupVolume");
    resp.Start();
    respaStartupVolume.Write(aStartupVolume);
    resp.End();
}

void DvProviderLinnCoUkPreamp4C::DoSetStartupVolumeEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aStartupVolumeEnabled = aInvocation.InvocationReadBool("aStartupVolumeEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetStartupVolumeEnabled != NULL);
    if (0 != iCallbackSetStartupVolumeEnabled(iPtrSetStartupVolumeEnabled, aVersion, aStartupVolumeEnabled)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkPreamp4C::DoStartupVolumeEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aStartupVolumeEnabled;
    ASSERT(iCallbackStartupVolumeEnabled != NULL);
    if (0 != iCallbackStartupVolumeEnabled(iPtrStartupVolumeEnabled, aVersion, &aStartupVolumeEnabled)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaStartupVolumeEnabled(aInvocation, "aStartupVolumeEnabled");
    resp.Start();
    respaStartupVolumeEnabled.Write((aStartupVolumeEnabled!=0));
    resp.End();
}



THandle DvProviderLinnCoUkPreamp4Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkPreamp4C(aDevice);
}

void DvProviderLinnCoUkPreamp4Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider);
}

void DvProviderLinnCoUkPreamp4EnableActionVolumeInc(THandle aProvider, CallbackPreamp4VolumeInc aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionVolumeInc(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionVolumeDec(THandle aProvider, CallbackPreamp4VolumeDec aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionVolumeDec(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionSetVolume(THandle aProvider, CallbackPreamp4SetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionSetVolume(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionVolume(THandle aProvider, CallbackPreamp4Volume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionVolume(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionSetMute(THandle aProvider, CallbackPreamp4SetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionSetMute(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionMute(THandle aProvider, CallbackPreamp4Mute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionMute(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionSetBalance(THandle aProvider, CallbackPreamp4SetBalance aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionSetBalance(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionBalance(THandle aProvider, CallbackPreamp4Balance aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionBalance(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionSetVolumeLimit(THandle aProvider, CallbackPreamp4SetVolumeLimit aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionSetVolumeLimit(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionVolumeLimit(THandle aProvider, CallbackPreamp4VolumeLimit aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionVolumeLimit(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionSetStartupVolume(THandle aProvider, CallbackPreamp4SetStartupVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionSetStartupVolume(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionStartupVolume(THandle aProvider, CallbackPreamp4StartupVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionStartupVolume(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionSetStartupVolumeEnabled(THandle aProvider, CallbackPreamp4SetStartupVolumeEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionSetStartupVolumeEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkPreamp4EnableActionStartupVolumeEnabled(THandle aProvider, CallbackPreamp4StartupVolumeEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->EnableActionStartupVolumeEnabled(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkPreamp4SetPropertyVolume(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->SetPropertyVolume(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPreamp4GetPropertyVolume(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->GetPropertyVolume(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkPreamp4SetPropertyMute(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->SetPropertyMute((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPreamp4GetPropertyMute(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->GetPropertyMute(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkPreamp4SetPropertyBalance(THandle aProvider, int32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->SetPropertyBalance(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPreamp4GetPropertyBalance(THandle aProvider, int32_t* aValue)
{
    int32_t val;
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->GetPropertyBalance(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkPreamp4SetPropertyVolumeLimit(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->SetPropertyVolumeLimit(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPreamp4GetPropertyVolumeLimit(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->GetPropertyVolumeLimit(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkPreamp4SetPropertyStartupVolume(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->SetPropertyStartupVolume(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPreamp4GetPropertyStartupVolume(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->GetPropertyStartupVolume(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkPreamp4SetPropertyStartupVolumeEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->SetPropertyStartupVolumeEnabled((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPreamp4GetPropertyStartupVolumeEnabled(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkPreamp4C*>(aProvider)->GetPropertyStartupVolumeEnabled(val);
    *aValue = (val? 1 : 0);
}

