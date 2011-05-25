#include "CpUpnpOrgRenderingControl2.h"
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>
#include <OhNetTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace OpenHome::Net;

class CpProxyUpnpOrgRenderingControl2C : public CpProxyC
{
public:
    CpProxyUpnpOrgRenderingControl2C(CpDeviceC aDevice);
    ~CpProxyUpnpOrgRenderingControl2C();
    //CpProxyUpnpOrgRenderingControl2* Proxy() { return static_cast<CpProxyUpnpOrgRenderingControl2*>(iProxy); }

    void SyncListPresets(TUint aInstanceID, Brh& aCurrentPresetNameList);
    void BeginListPresets(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndListPresets(IAsync& aAsync, Brh& aCurrentPresetNameList);

    void SyncSelectPreset(TUint aInstanceID, const Brx& aPresetName);
    void BeginSelectPreset(TUint aInstanceID, const Brx& aPresetName, FunctorAsync& aFunctor);
    void EndSelectPreset(IAsync& aAsync);

    void SyncGetBrightness(TUint aInstanceID, TUint& aCurrentBrightness);
    void BeginGetBrightness(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetBrightness(IAsync& aAsync, TUint& aCurrentBrightness);

    void SyncSetBrightness(TUint aInstanceID, TUint aDesiredBrightness);
    void BeginSetBrightness(TUint aInstanceID, TUint aDesiredBrightness, FunctorAsync& aFunctor);
    void EndSetBrightness(IAsync& aAsync);

    void SyncGetContrast(TUint aInstanceID, TUint& aCurrentContrast);
    void BeginGetContrast(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetContrast(IAsync& aAsync, TUint& aCurrentContrast);

    void SyncSetContrast(TUint aInstanceID, TUint aDesiredContrast);
    void BeginSetContrast(TUint aInstanceID, TUint aDesiredContrast, FunctorAsync& aFunctor);
    void EndSetContrast(IAsync& aAsync);

    void SyncGetSharpness(TUint aInstanceID, TUint& aCurrentSharpness);
    void BeginGetSharpness(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetSharpness(IAsync& aAsync, TUint& aCurrentSharpness);

    void SyncSetSharpness(TUint aInstanceID, TUint aDesiredSharpness);
    void BeginSetSharpness(TUint aInstanceID, TUint aDesiredSharpness, FunctorAsync& aFunctor);
    void EndSetSharpness(IAsync& aAsync);

    void SyncGetRedVideoGain(TUint aInstanceID, TUint& aCurrentRedVideoGain);
    void BeginGetRedVideoGain(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetRedVideoGain(IAsync& aAsync, TUint& aCurrentRedVideoGain);

    void SyncSetRedVideoGain(TUint aInstanceID, TUint aDesiredRedVideoGain);
    void BeginSetRedVideoGain(TUint aInstanceID, TUint aDesiredRedVideoGain, FunctorAsync& aFunctor);
    void EndSetRedVideoGain(IAsync& aAsync);

    void SyncGetGreenVideoGain(TUint aInstanceID, TUint& aCurrentGreenVideoGain);
    void BeginGetGreenVideoGain(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetGreenVideoGain(IAsync& aAsync, TUint& aCurrentGreenVideoGain);

    void SyncSetGreenVideoGain(TUint aInstanceID, TUint aDesiredGreenVideoGain);
    void BeginSetGreenVideoGain(TUint aInstanceID, TUint aDesiredGreenVideoGain, FunctorAsync& aFunctor);
    void EndSetGreenVideoGain(IAsync& aAsync);

    void SyncGetBlueVideoGain(TUint aInstanceID, TUint& aCurrentBlueVideoGain);
    void BeginGetBlueVideoGain(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetBlueVideoGain(IAsync& aAsync, TUint& aCurrentBlueVideoGain);

    void SyncSetBlueVideoGain(TUint aInstanceID, TUint aDesiredBlueVideoGain);
    void BeginSetBlueVideoGain(TUint aInstanceID, TUint aDesiredBlueVideoGain, FunctorAsync& aFunctor);
    void EndSetBlueVideoGain(IAsync& aAsync);

    void SyncGetRedVideoBlackLevel(TUint aInstanceID, TUint& aCurrentRedVideoBlackLevel);
    void BeginGetRedVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetRedVideoBlackLevel(IAsync& aAsync, TUint& aCurrentRedVideoBlackLevel);

    void SyncSetRedVideoBlackLevel(TUint aInstanceID, TUint aDesiredRedVideoBlackLevel);
    void BeginSetRedVideoBlackLevel(TUint aInstanceID, TUint aDesiredRedVideoBlackLevel, FunctorAsync& aFunctor);
    void EndSetRedVideoBlackLevel(IAsync& aAsync);

    void SyncGetGreenVideoBlackLevel(TUint aInstanceID, TUint& aCurrentGreenVideoBlackLevel);
    void BeginGetGreenVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetGreenVideoBlackLevel(IAsync& aAsync, TUint& aCurrentGreenVideoBlackLevel);

    void SyncSetGreenVideoBlackLevel(TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel);
    void BeginSetGreenVideoBlackLevel(TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel, FunctorAsync& aFunctor);
    void EndSetGreenVideoBlackLevel(IAsync& aAsync);

    void SyncGetBlueVideoBlackLevel(TUint aInstanceID, TUint& aCurrentBlueVideoBlackLevel);
    void BeginGetBlueVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetBlueVideoBlackLevel(IAsync& aAsync, TUint& aCurrentBlueVideoBlackLevel);

    void SyncSetBlueVideoBlackLevel(TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel);
    void BeginSetBlueVideoBlackLevel(TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel, FunctorAsync& aFunctor);
    void EndSetBlueVideoBlackLevel(IAsync& aAsync);

    void SyncGetColorTemperature(TUint aInstanceID, TUint& aCurrentColorTemperature);
    void BeginGetColorTemperature(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetColorTemperature(IAsync& aAsync, TUint& aCurrentColorTemperature);

    void SyncSetColorTemperature(TUint aInstanceID, TUint aDesiredColorTemperature);
    void BeginSetColorTemperature(TUint aInstanceID, TUint aDesiredColorTemperature, FunctorAsync& aFunctor);
    void EndSetColorTemperature(IAsync& aAsync);

    void SyncGetHorizontalKeystone(TUint aInstanceID, TInt& aCurrentHorizontalKeystone);
    void BeginGetHorizontalKeystone(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetHorizontalKeystone(IAsync& aAsync, TInt& aCurrentHorizontalKeystone);

    void SyncSetHorizontalKeystone(TUint aInstanceID, TInt aDesiredHorizontalKeystone);
    void BeginSetHorizontalKeystone(TUint aInstanceID, TInt aDesiredHorizontalKeystone, FunctorAsync& aFunctor);
    void EndSetHorizontalKeystone(IAsync& aAsync);

    void SyncGetVerticalKeystone(TUint aInstanceID, TInt& aCurrentVerticalKeystone);
    void BeginGetVerticalKeystone(TUint aInstanceID, FunctorAsync& aFunctor);
    void EndGetVerticalKeystone(IAsync& aAsync, TInt& aCurrentVerticalKeystone);

    void SyncSetVerticalKeystone(TUint aInstanceID, TInt aDesiredVerticalKeystone);
    void BeginSetVerticalKeystone(TUint aInstanceID, TInt aDesiredVerticalKeystone, FunctorAsync& aFunctor);
    void EndSetVerticalKeystone(IAsync& aAsync);

    void SyncGetMute(TUint aInstanceID, const Brx& aChannel, TBool& aCurrentMute);
    void BeginGetMute(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor);
    void EndGetMute(IAsync& aAsync, TBool& aCurrentMute);

    void SyncSetMute(TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute);
    void BeginSetMute(TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute, FunctorAsync& aFunctor);
    void EndSetMute(IAsync& aAsync);

    void SyncGetVolume(TUint aInstanceID, const Brx& aChannel, TUint& aCurrentVolume);
    void BeginGetVolume(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor);
    void EndGetVolume(IAsync& aAsync, TUint& aCurrentVolume);

    void SyncSetVolume(TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume);
    void BeginSetVolume(TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume, FunctorAsync& aFunctor);
    void EndSetVolume(IAsync& aAsync);

    void SyncGetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt& aCurrentVolume);
    void BeginGetVolumeDB(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor);
    void EndGetVolumeDB(IAsync& aAsync, TInt& aCurrentVolume);

    void SyncSetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume);
    void BeginSetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume, FunctorAsync& aFunctor);
    void EndSetVolumeDB(IAsync& aAsync);

    void SyncGetVolumeDBRange(TUint aInstanceID, const Brx& aChannel, TInt& aMinValue, TInt& aMaxValue);
    void BeginGetVolumeDBRange(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor);
    void EndGetVolumeDBRange(IAsync& aAsync, TInt& aMinValue, TInt& aMaxValue);

    void SyncGetLoudness(TUint aInstanceID, const Brx& aChannel, TBool& aCurrentLoudness);
    void BeginGetLoudness(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor);
    void EndGetLoudness(IAsync& aAsync, TBool& aCurrentLoudness);

    void SyncSetLoudness(TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness);
    void BeginSetLoudness(TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness, FunctorAsync& aFunctor);
    void EndSetLoudness(IAsync& aAsync);

    void SyncGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, Brh& aStateVariableValuePairs);
    void BeginGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, FunctorAsync& aFunctor);
    void EndGetStateVariables(IAsync& aAsync, Brh& aStateVariableValuePairs);

    void SyncSetStateVariables(TUint aInstanceID, const Brx& aRenderingControlUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, Brh& aStateVariableList);
    void BeginSetStateVariables(TUint aInstanceID, const Brx& aRenderingControlUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, FunctorAsync& aFunctor);
    void EndSetStateVariables(IAsync& aAsync, Brh& aStateVariableList);

    void SetPropertyLastChangeChanged(Functor& aFunctor);

    void PropertyLastChange(Brhz& aLastChange) const;
private:
    void LastChangePropertyChanged();
private:
    Mutex iLock;
    Action* iActionListPresets;
    Action* iActionSelectPreset;
    Action* iActionGetBrightness;
    Action* iActionSetBrightness;
    Action* iActionGetContrast;
    Action* iActionSetContrast;
    Action* iActionGetSharpness;
    Action* iActionSetSharpness;
    Action* iActionGetRedVideoGain;
    Action* iActionSetRedVideoGain;
    Action* iActionGetGreenVideoGain;
    Action* iActionSetGreenVideoGain;
    Action* iActionGetBlueVideoGain;
    Action* iActionSetBlueVideoGain;
    Action* iActionGetRedVideoBlackLevel;
    Action* iActionSetRedVideoBlackLevel;
    Action* iActionGetGreenVideoBlackLevel;
    Action* iActionSetGreenVideoBlackLevel;
    Action* iActionGetBlueVideoBlackLevel;
    Action* iActionSetBlueVideoBlackLevel;
    Action* iActionGetColorTemperature;
    Action* iActionSetColorTemperature;
    Action* iActionGetHorizontalKeystone;
    Action* iActionSetHorizontalKeystone;
    Action* iActionGetVerticalKeystone;
    Action* iActionSetVerticalKeystone;
    Action* iActionGetMute;
    Action* iActionSetMute;
    Action* iActionGetVolume;
    Action* iActionSetVolume;
    Action* iActionGetVolumeDB;
    Action* iActionSetVolumeDB;
    Action* iActionGetVolumeDBRange;
    Action* iActionGetLoudness;
    Action* iActionSetLoudness;
    Action* iActionGetStateVariables;
    Action* iActionSetStateVariables;
    PropertyString* iLastChange;
    Functor iLastChangeChanged;
};


class SyncListPresetsUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncListPresetsUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, Brh& aCurrentPresetNameList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    Brh& iCurrentPresetNameList;
};

SyncListPresetsUpnpOrgRenderingControl2C::SyncListPresetsUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, Brh& aCurrentPresetNameList)
    : iService(aProxy)
    , iCurrentPresetNameList(aCurrentPresetNameList)
{
}

void SyncListPresetsUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndListPresets(aAsync, iCurrentPresetNameList);
}


class SyncSelectPresetUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSelectPresetUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSelectPresetUpnpOrgRenderingControl2C::SyncSelectPresetUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSelectPresetUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSelectPreset(aAsync);
}


class SyncGetBrightnessUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetBrightnessUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentBrightness);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TUint& iCurrentBrightness;
};

SyncGetBrightnessUpnpOrgRenderingControl2C::SyncGetBrightnessUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentBrightness)
    : iService(aProxy)
    , iCurrentBrightness(aCurrentBrightness)
{
}

void SyncGetBrightnessUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBrightness(aAsync, iCurrentBrightness);
}


class SyncSetBrightnessUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetBrightnessUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetBrightnessUpnpOrgRenderingControl2C::SyncSetBrightnessUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetBrightnessUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBrightness(aAsync);
}


class SyncGetContrastUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetContrastUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentContrast);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TUint& iCurrentContrast;
};

SyncGetContrastUpnpOrgRenderingControl2C::SyncGetContrastUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentContrast)
    : iService(aProxy)
    , iCurrentContrast(aCurrentContrast)
{
}

void SyncGetContrastUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetContrast(aAsync, iCurrentContrast);
}


class SyncSetContrastUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetContrastUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetContrastUpnpOrgRenderingControl2C::SyncSetContrastUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetContrastUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetContrast(aAsync);
}


class SyncGetSharpnessUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetSharpnessUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentSharpness);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TUint& iCurrentSharpness;
};

SyncGetSharpnessUpnpOrgRenderingControl2C::SyncGetSharpnessUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentSharpness)
    : iService(aProxy)
    , iCurrentSharpness(aCurrentSharpness)
{
}

void SyncGetSharpnessUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSharpness(aAsync, iCurrentSharpness);
}


class SyncSetSharpnessUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetSharpnessUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetSharpnessUpnpOrgRenderingControl2C::SyncSetSharpnessUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetSharpnessUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSharpness(aAsync);
}


class SyncGetRedVideoGainUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetRedVideoGainUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentRedVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TUint& iCurrentRedVideoGain;
};

SyncGetRedVideoGainUpnpOrgRenderingControl2C::SyncGetRedVideoGainUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentRedVideoGain)
    : iService(aProxy)
    , iCurrentRedVideoGain(aCurrentRedVideoGain)
{
}

void SyncGetRedVideoGainUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRedVideoGain(aAsync, iCurrentRedVideoGain);
}


class SyncSetRedVideoGainUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetRedVideoGainUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetRedVideoGainUpnpOrgRenderingControl2C::SyncSetRedVideoGainUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetRedVideoGainUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRedVideoGain(aAsync);
}


class SyncGetGreenVideoGainUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetGreenVideoGainUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentGreenVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TUint& iCurrentGreenVideoGain;
};

SyncGetGreenVideoGainUpnpOrgRenderingControl2C::SyncGetGreenVideoGainUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentGreenVideoGain)
    : iService(aProxy)
    , iCurrentGreenVideoGain(aCurrentGreenVideoGain)
{
}

void SyncGetGreenVideoGainUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetGreenVideoGain(aAsync, iCurrentGreenVideoGain);
}


class SyncSetGreenVideoGainUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetGreenVideoGainUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetGreenVideoGainUpnpOrgRenderingControl2C::SyncSetGreenVideoGainUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetGreenVideoGainUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetGreenVideoGain(aAsync);
}


class SyncGetBlueVideoGainUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetBlueVideoGainUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentBlueVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TUint& iCurrentBlueVideoGain;
};

SyncGetBlueVideoGainUpnpOrgRenderingControl2C::SyncGetBlueVideoGainUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentBlueVideoGain)
    : iService(aProxy)
    , iCurrentBlueVideoGain(aCurrentBlueVideoGain)
{
}

void SyncGetBlueVideoGainUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBlueVideoGain(aAsync, iCurrentBlueVideoGain);
}


class SyncSetBlueVideoGainUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetBlueVideoGainUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetBlueVideoGainUpnpOrgRenderingControl2C::SyncSetBlueVideoGainUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetBlueVideoGainUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBlueVideoGain(aAsync);
}


class SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentRedVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TUint& iCurrentRedVideoBlackLevel;
};

SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2C::SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentRedVideoBlackLevel)
    : iService(aProxy)
    , iCurrentRedVideoBlackLevel(aCurrentRedVideoBlackLevel)
{
}

void SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRedVideoBlackLevel(aAsync, iCurrentRedVideoBlackLevel);
}


class SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2C::SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRedVideoBlackLevel(aAsync);
}


class SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentGreenVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TUint& iCurrentGreenVideoBlackLevel;
};

SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2C::SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentGreenVideoBlackLevel)
    : iService(aProxy)
    , iCurrentGreenVideoBlackLevel(aCurrentGreenVideoBlackLevel)
{
}

void SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetGreenVideoBlackLevel(aAsync, iCurrentGreenVideoBlackLevel);
}


class SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2C::SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetGreenVideoBlackLevel(aAsync);
}


class SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentBlueVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TUint& iCurrentBlueVideoBlackLevel;
};

SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2C::SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentBlueVideoBlackLevel)
    : iService(aProxy)
    , iCurrentBlueVideoBlackLevel(aCurrentBlueVideoBlackLevel)
{
}

void SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBlueVideoBlackLevel(aAsync, iCurrentBlueVideoBlackLevel);
}


class SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2C::SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBlueVideoBlackLevel(aAsync);
}


class SyncGetColorTemperatureUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetColorTemperatureUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentColorTemperature);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TUint& iCurrentColorTemperature;
};

SyncGetColorTemperatureUpnpOrgRenderingControl2C::SyncGetColorTemperatureUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentColorTemperature)
    : iService(aProxy)
    , iCurrentColorTemperature(aCurrentColorTemperature)
{
}

void SyncGetColorTemperatureUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColorTemperature(aAsync, iCurrentColorTemperature);
}


class SyncSetColorTemperatureUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetColorTemperatureUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetColorTemperatureUpnpOrgRenderingControl2C::SyncSetColorTemperatureUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetColorTemperatureUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColorTemperature(aAsync);
}


class SyncGetHorizontalKeystoneUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetHorizontalKeystoneUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TInt& aCurrentHorizontalKeystone);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TInt& iCurrentHorizontalKeystone;
};

SyncGetHorizontalKeystoneUpnpOrgRenderingControl2C::SyncGetHorizontalKeystoneUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TInt& aCurrentHorizontalKeystone)
    : iService(aProxy)
    , iCurrentHorizontalKeystone(aCurrentHorizontalKeystone)
{
}

void SyncGetHorizontalKeystoneUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetHorizontalKeystone(aAsync, iCurrentHorizontalKeystone);
}


class SyncSetHorizontalKeystoneUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetHorizontalKeystoneUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetHorizontalKeystoneUpnpOrgRenderingControl2C::SyncSetHorizontalKeystoneUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetHorizontalKeystoneUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetHorizontalKeystone(aAsync);
}


class SyncGetVerticalKeystoneUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetVerticalKeystoneUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TInt& aCurrentVerticalKeystone);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TInt& iCurrentVerticalKeystone;
};

SyncGetVerticalKeystoneUpnpOrgRenderingControl2C::SyncGetVerticalKeystoneUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TInt& aCurrentVerticalKeystone)
    : iService(aProxy)
    , iCurrentVerticalKeystone(aCurrentVerticalKeystone)
{
}

void SyncGetVerticalKeystoneUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVerticalKeystone(aAsync, iCurrentVerticalKeystone);
}


class SyncSetVerticalKeystoneUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetVerticalKeystoneUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetVerticalKeystoneUpnpOrgRenderingControl2C::SyncSetVerticalKeystoneUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetVerticalKeystoneUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVerticalKeystone(aAsync);
}


class SyncGetMuteUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetMuteUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TBool& aCurrentMute);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TBool& iCurrentMute;
};

SyncGetMuteUpnpOrgRenderingControl2C::SyncGetMuteUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TBool& aCurrentMute)
    : iService(aProxy)
    , iCurrentMute(aCurrentMute)
{
}

void SyncGetMuteUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMute(aAsync, iCurrentMute);
}


class SyncSetMuteUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetMuteUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetMuteUpnpOrgRenderingControl2C::SyncSetMuteUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetMuteUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMute(aAsync);
}


class SyncGetVolumeUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetVolumeUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TUint& iCurrentVolume;
};

SyncGetVolumeUpnpOrgRenderingControl2C::SyncGetVolumeUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TUint& aCurrentVolume)
    : iService(aProxy)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetVolumeUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolume(aAsync, iCurrentVolume);
}


class SyncSetVolumeUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetVolumeUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetVolumeUpnpOrgRenderingControl2C::SyncSetVolumeUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolume(aAsync);
}


class SyncGetVolumeDBUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetVolumeDBUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TInt& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TInt& iCurrentVolume;
};

SyncGetVolumeDBUpnpOrgRenderingControl2C::SyncGetVolumeDBUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TInt& aCurrentVolume)
    : iService(aProxy)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetVolumeDBUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolumeDB(aAsync, iCurrentVolume);
}


class SyncSetVolumeDBUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetVolumeDBUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetVolumeDBUpnpOrgRenderingControl2C::SyncSetVolumeDBUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeDBUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolumeDB(aAsync);
}


class SyncGetVolumeDBRangeUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetVolumeDBRangeUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TInt& aMinValue, TInt& aMaxValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TInt& iMinValue;
    TInt& iMaxValue;
};

SyncGetVolumeDBRangeUpnpOrgRenderingControl2C::SyncGetVolumeDBRangeUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TInt& aMinValue, TInt& aMaxValue)
    : iService(aProxy)
    , iMinValue(aMinValue)
    , iMaxValue(aMaxValue)
{
}

void SyncGetVolumeDBRangeUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolumeDBRange(aAsync, iMinValue, iMaxValue);
}


class SyncGetLoudnessUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetLoudnessUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TBool& aCurrentLoudness);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    TBool& iCurrentLoudness;
};

SyncGetLoudnessUpnpOrgRenderingControl2C::SyncGetLoudnessUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, TBool& aCurrentLoudness)
    : iService(aProxy)
    , iCurrentLoudness(aCurrentLoudness)
{
}

void SyncGetLoudnessUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLoudness(aAsync, iCurrentLoudness);
}


class SyncSetLoudnessUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetLoudnessUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
};

SyncSetLoudnessUpnpOrgRenderingControl2C::SyncSetLoudnessUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetLoudnessUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLoudness(aAsync);
}


class SyncGetStateVariablesUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncGetStateVariablesUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, Brh& aStateVariableValuePairs);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    Brh& iStateVariableValuePairs;
};

SyncGetStateVariablesUpnpOrgRenderingControl2C::SyncGetStateVariablesUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, Brh& aStateVariableValuePairs)
    : iService(aProxy)
    , iStateVariableValuePairs(aStateVariableValuePairs)
{
}

void SyncGetStateVariablesUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStateVariables(aAsync, iStateVariableValuePairs);
}


class SyncSetStateVariablesUpnpOrgRenderingControl2C : public SyncProxyAction
{
public:
    SyncSetStateVariablesUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, Brh& aStateVariableList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl2C& iService;
    Brh& iStateVariableList;
};

SyncSetStateVariablesUpnpOrgRenderingControl2C::SyncSetStateVariablesUpnpOrgRenderingControl2C(CpProxyUpnpOrgRenderingControl2C& aProxy, Brh& aStateVariableList)
    : iService(aProxy)
    , iStateVariableList(aStateVariableList)
{
}

void SyncSetStateVariablesUpnpOrgRenderingControl2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStateVariables(aAsync, iStateVariableList);
}

CpProxyUpnpOrgRenderingControl2C::CpProxyUpnpOrgRenderingControl2C(CpDeviceC aDevice)
    : CpProxyC("schemas-upnp-org", "RenderingControl", 2, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionListPresets = new Action("ListPresets");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionListPresets->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentPresetNameList");
    iActionListPresets->AddOutputParameter(param);

    iActionSelectPreset = new Action("SelectPreset");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSelectPreset->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"FactoryDefaults";
    param = new OpenHome::Net::ParameterString("PresetName", allowedValues, 1);
    iActionSelectPreset->AddInputParameter(param);
    delete[] allowedValues;

    iActionGetBrightness = new Action("GetBrightness");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetBrightness->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentBrightness", 0, 0, 1);
    iActionGetBrightness->AddOutputParameter(param);

    iActionSetBrightness = new Action("SetBrightness");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetBrightness->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredBrightness", 0, 0, 1);
    iActionSetBrightness->AddInputParameter(param);

    iActionGetContrast = new Action("GetContrast");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetContrast->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentContrast", 0, 0, 1);
    iActionGetContrast->AddOutputParameter(param);

    iActionSetContrast = new Action("SetContrast");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetContrast->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredContrast", 0, 0, 1);
    iActionSetContrast->AddInputParameter(param);

    iActionGetSharpness = new Action("GetSharpness");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetSharpness->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentSharpness", 0, 0, 1);
    iActionGetSharpness->AddOutputParameter(param);

    iActionSetSharpness = new Action("SetSharpness");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetSharpness->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredSharpness", 0, 0, 1);
    iActionSetSharpness->AddInputParameter(param);

    iActionGetRedVideoGain = new Action("GetRedVideoGain");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetRedVideoGain->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentRedVideoGain", 0, 0, 1);
    iActionGetRedVideoGain->AddOutputParameter(param);

    iActionSetRedVideoGain = new Action("SetRedVideoGain");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetRedVideoGain->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredRedVideoGain", 0, 0, 1);
    iActionSetRedVideoGain->AddInputParameter(param);

    iActionGetGreenVideoGain = new Action("GetGreenVideoGain");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetGreenVideoGain->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentGreenVideoGain", 0, 0, 1);
    iActionGetGreenVideoGain->AddOutputParameter(param);

    iActionSetGreenVideoGain = new Action("SetGreenVideoGain");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetGreenVideoGain->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredGreenVideoGain", 0, 0, 1);
    iActionSetGreenVideoGain->AddInputParameter(param);

    iActionGetBlueVideoGain = new Action("GetBlueVideoGain");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetBlueVideoGain->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentBlueVideoGain", 0, 0, 1);
    iActionGetBlueVideoGain->AddOutputParameter(param);

    iActionSetBlueVideoGain = new Action("SetBlueVideoGain");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetBlueVideoGain->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredBlueVideoGain", 0, 0, 1);
    iActionSetBlueVideoGain->AddInputParameter(param);

    iActionGetRedVideoBlackLevel = new Action("GetRedVideoBlackLevel");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetRedVideoBlackLevel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentRedVideoBlackLevel", 0, 0, 1);
    iActionGetRedVideoBlackLevel->AddOutputParameter(param);

    iActionSetRedVideoBlackLevel = new Action("SetRedVideoBlackLevel");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetRedVideoBlackLevel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredRedVideoBlackLevel", 0, 0, 1);
    iActionSetRedVideoBlackLevel->AddInputParameter(param);

    iActionGetGreenVideoBlackLevel = new Action("GetGreenVideoBlackLevel");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetGreenVideoBlackLevel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentGreenVideoBlackLevel", 0, 0, 1);
    iActionGetGreenVideoBlackLevel->AddOutputParameter(param);

    iActionSetGreenVideoBlackLevel = new Action("SetGreenVideoBlackLevel");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetGreenVideoBlackLevel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredGreenVideoBlackLevel", 0, 0, 1);
    iActionSetGreenVideoBlackLevel->AddInputParameter(param);

    iActionGetBlueVideoBlackLevel = new Action("GetBlueVideoBlackLevel");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetBlueVideoBlackLevel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentBlueVideoBlackLevel", 0, 0, 1);
    iActionGetBlueVideoBlackLevel->AddOutputParameter(param);

    iActionSetBlueVideoBlackLevel = new Action("SetBlueVideoBlackLevel");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetBlueVideoBlackLevel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredBlueVideoBlackLevel", 0, 0, 1);
    iActionSetBlueVideoBlackLevel->AddInputParameter(param);

    iActionGetColorTemperature = new Action("GetColorTemperature");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetColorTemperature->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentColorTemperature", 0, 0, 1);
    iActionGetColorTemperature->AddOutputParameter(param);

    iActionSetColorTemperature = new Action("SetColorTemperature");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetColorTemperature->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredColorTemperature", 0, 0, 1);
    iActionSetColorTemperature->AddInputParameter(param);

    iActionGetHorizontalKeystone = new Action("GetHorizontalKeystone");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetHorizontalKeystone->AddInputParameter(param);
    param = new OpenHome::Net::ParameterInt("CurrentHorizontalKeystone");
    iActionGetHorizontalKeystone->AddOutputParameter(param);

    iActionSetHorizontalKeystone = new Action("SetHorizontalKeystone");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetHorizontalKeystone->AddInputParameter(param);
    param = new OpenHome::Net::ParameterInt("DesiredHorizontalKeystone");
    iActionSetHorizontalKeystone->AddInputParameter(param);

    iActionGetVerticalKeystone = new Action("GetVerticalKeystone");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetVerticalKeystone->AddInputParameter(param);
    param = new OpenHome::Net::ParameterInt("CurrentVerticalKeystone");
    iActionGetVerticalKeystone->AddOutputParameter(param);

    iActionSetVerticalKeystone = new Action("SetVerticalKeystone");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetVerticalKeystone->AddInputParameter(param);
    param = new OpenHome::Net::ParameterInt("DesiredVerticalKeystone");
    iActionSetVerticalKeystone->AddInputParameter(param);

    iActionGetMute = new Action("GetMute");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetMute->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new OpenHome::Net::ParameterString("Channel", allowedValues, 1);
    iActionGetMute->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterBool("CurrentMute");
    iActionGetMute->AddOutputParameter(param);

    iActionSetMute = new Action("SetMute");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetMute->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new OpenHome::Net::ParameterString("Channel", allowedValues, 1);
    iActionSetMute->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterBool("DesiredMute");
    iActionSetMute->AddInputParameter(param);

    iActionGetVolume = new Action("GetVolume");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetVolume->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new OpenHome::Net::ParameterString("Channel", allowedValues, 1);
    iActionGetVolume->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterUint("CurrentVolume", 0, 0, 1);
    iActionGetVolume->AddOutputParameter(param);

    iActionSetVolume = new Action("SetVolume");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetVolume->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new OpenHome::Net::ParameterString("Channel", allowedValues, 1);
    iActionSetVolume->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterUint("DesiredVolume", 0, 0, 1);
    iActionSetVolume->AddInputParameter(param);

    iActionGetVolumeDB = new Action("GetVolumeDB");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetVolumeDB->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new OpenHome::Net::ParameterString("Channel", allowedValues, 1);
    iActionGetVolumeDB->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterInt("CurrentVolume");
    iActionGetVolumeDB->AddOutputParameter(param);

    iActionSetVolumeDB = new Action("SetVolumeDB");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetVolumeDB->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new OpenHome::Net::ParameterString("Channel", allowedValues, 1);
    iActionSetVolumeDB->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterInt("DesiredVolume");
    iActionSetVolumeDB->AddInputParameter(param);

    iActionGetVolumeDBRange = new Action("GetVolumeDBRange");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetVolumeDBRange->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new OpenHome::Net::ParameterString("Channel", allowedValues, 1);
    iActionGetVolumeDBRange->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterInt("MinValue");
    iActionGetVolumeDBRange->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterInt("MaxValue");
    iActionGetVolumeDBRange->AddOutputParameter(param);

    iActionGetLoudness = new Action("GetLoudness");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetLoudness->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new OpenHome::Net::ParameterString("Channel", allowedValues, 1);
    iActionGetLoudness->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterBool("CurrentLoudness");
    iActionGetLoudness->AddOutputParameter(param);

    iActionSetLoudness = new Action("SetLoudness");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetLoudness->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new OpenHome::Net::ParameterString("Channel", allowedValues, 1);
    iActionSetLoudness->AddInputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterBool("DesiredLoudness");
    iActionSetLoudness->AddInputParameter(param);

    iActionGetStateVariables = new Action("GetStateVariables");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("StateVariableList");
    iActionGetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("StateVariableValuePairs");
    iActionGetStateVariables->AddOutputParameter(param);

    iActionSetStateVariables = new Action("SetStateVariables");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("RenderingControlUDN");
    iActionSetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ServiceType");
    iActionSetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("ServiceId");
    iActionSetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("StateVariableValuePairs");
    iActionSetStateVariables->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("StateVariableList");
    iActionSetStateVariables->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgRenderingControl2C::LastChangePropertyChanged);
    iLastChange = new PropertyString("LastChange", functor);
    AddProperty(iLastChange);
}

CpProxyUpnpOrgRenderingControl2C::~CpProxyUpnpOrgRenderingControl2C()
{
    DestroyService();
    delete iActionListPresets;
    delete iActionSelectPreset;
    delete iActionGetBrightness;
    delete iActionSetBrightness;
    delete iActionGetContrast;
    delete iActionSetContrast;
    delete iActionGetSharpness;
    delete iActionSetSharpness;
    delete iActionGetRedVideoGain;
    delete iActionSetRedVideoGain;
    delete iActionGetGreenVideoGain;
    delete iActionSetGreenVideoGain;
    delete iActionGetBlueVideoGain;
    delete iActionSetBlueVideoGain;
    delete iActionGetRedVideoBlackLevel;
    delete iActionSetRedVideoBlackLevel;
    delete iActionGetGreenVideoBlackLevel;
    delete iActionSetGreenVideoBlackLevel;
    delete iActionGetBlueVideoBlackLevel;
    delete iActionSetBlueVideoBlackLevel;
    delete iActionGetColorTemperature;
    delete iActionSetColorTemperature;
    delete iActionGetHorizontalKeystone;
    delete iActionSetHorizontalKeystone;
    delete iActionGetVerticalKeystone;
    delete iActionSetVerticalKeystone;
    delete iActionGetMute;
    delete iActionSetMute;
    delete iActionGetVolume;
    delete iActionSetVolume;
    delete iActionGetVolumeDB;
    delete iActionSetVolumeDB;
    delete iActionGetVolumeDBRange;
    delete iActionGetLoudness;
    delete iActionSetLoudness;
    delete iActionGetStateVariables;
    delete iActionSetStateVariables;
}

void CpProxyUpnpOrgRenderingControl2C::SyncListPresets(TUint aInstanceID, Brh& aCurrentPresetNameList)
{
    SyncListPresetsUpnpOrgRenderingControl2C sync(*this, aCurrentPresetNameList);
    BeginListPresets(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginListPresets(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionListPresets, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionListPresets->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionListPresets->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndListPresets(IAsync& aAsync, Brh& aCurrentPresetNameList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ListPresets"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentPresetNameList);
}

void CpProxyUpnpOrgRenderingControl2C::SyncSelectPreset(TUint aInstanceID, const Brx& aPresetName)
{
    SyncSelectPresetUpnpOrgRenderingControl2C sync(*this);
    BeginSelectPreset(aInstanceID, aPresetName, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSelectPreset(TUint aInstanceID, const Brx& aPresetName, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSelectPreset, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSelectPreset->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aPresetName));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSelectPreset(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SelectPreset"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetBrightness(TUint aInstanceID, TUint& aCurrentBrightness)
{
    SyncGetBrightnessUpnpOrgRenderingControl2C sync(*this, aCurrentBrightness);
    BeginGetBrightness(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetBrightness(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetBrightness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetBrightness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBrightness->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetBrightness(IAsync& aAsync, TUint& aCurrentBrightness)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetBrightness"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentBrightness = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetBrightness(TUint aInstanceID, TUint aDesiredBrightness)
{
    SyncSetBrightnessUpnpOrgRenderingControl2C sync(*this);
    BeginSetBrightness(aInstanceID, aDesiredBrightness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetBrightness(TUint aInstanceID, TUint aDesiredBrightness, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetBrightness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBrightness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBrightness));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetBrightness(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBrightness"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetContrast(TUint aInstanceID, TUint& aCurrentContrast)
{
    SyncGetContrastUpnpOrgRenderingControl2C sync(*this, aCurrentContrast);
    BeginGetContrast(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetContrast(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetContrast, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetContrast->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetContrast->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetContrast(IAsync& aAsync, TUint& aCurrentContrast)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetContrast"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentContrast = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetContrast(TUint aInstanceID, TUint aDesiredContrast)
{
    SyncSetContrastUpnpOrgRenderingControl2C sync(*this);
    BeginSetContrast(aInstanceID, aDesiredContrast, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetContrast(TUint aInstanceID, TUint aDesiredContrast, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetContrast, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetContrast->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredContrast));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetContrast(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetContrast"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetSharpness(TUint aInstanceID, TUint& aCurrentSharpness)
{
    SyncGetSharpnessUpnpOrgRenderingControl2C sync(*this, aCurrentSharpness);
    BeginGetSharpness(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetSharpness(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetSharpness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetSharpness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSharpness->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetSharpness(IAsync& aAsync, TUint& aCurrentSharpness)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSharpness"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentSharpness = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetSharpness(TUint aInstanceID, TUint aDesiredSharpness)
{
    SyncSetSharpnessUpnpOrgRenderingControl2C sync(*this);
    BeginSetSharpness(aInstanceID, aDesiredSharpness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetSharpness(TUint aInstanceID, TUint aDesiredSharpness, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetSharpness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSharpness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredSharpness));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetSharpness(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSharpness"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetRedVideoGain(TUint aInstanceID, TUint& aCurrentRedVideoGain)
{
    SyncGetRedVideoGainUpnpOrgRenderingControl2C sync(*this, aCurrentRedVideoGain);
    BeginGetRedVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetRedVideoGain(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetRedVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRedVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRedVideoGain->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetRedVideoGain(IAsync& aAsync, TUint& aCurrentRedVideoGain)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRedVideoGain"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentRedVideoGain = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetRedVideoGain(TUint aInstanceID, TUint aDesiredRedVideoGain)
{
    SyncSetRedVideoGainUpnpOrgRenderingControl2C sync(*this);
    BeginSetRedVideoGain(aInstanceID, aDesiredRedVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetRedVideoGain(TUint aInstanceID, TUint aDesiredRedVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetRedVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRedVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredRedVideoGain));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetRedVideoGain(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRedVideoGain"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetGreenVideoGain(TUint aInstanceID, TUint& aCurrentGreenVideoGain)
{
    SyncGetGreenVideoGainUpnpOrgRenderingControl2C sync(*this, aCurrentGreenVideoGain);
    BeginGetGreenVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetGreenVideoGain(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetGreenVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetGreenVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetGreenVideoGain->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetGreenVideoGain(IAsync& aAsync, TUint& aCurrentGreenVideoGain)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetGreenVideoGain"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentGreenVideoGain = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetGreenVideoGain(TUint aInstanceID, TUint aDesiredGreenVideoGain)
{
    SyncSetGreenVideoGainUpnpOrgRenderingControl2C sync(*this);
    BeginSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetGreenVideoGain(TUint aInstanceID, TUint aDesiredGreenVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetGreenVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetGreenVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredGreenVideoGain));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetGreenVideoGain(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetGreenVideoGain"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetBlueVideoGain(TUint aInstanceID, TUint& aCurrentBlueVideoGain)
{
    SyncGetBlueVideoGainUpnpOrgRenderingControl2C sync(*this, aCurrentBlueVideoGain);
    BeginGetBlueVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetBlueVideoGain(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetBlueVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetBlueVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBlueVideoGain->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetBlueVideoGain(IAsync& aAsync, TUint& aCurrentBlueVideoGain)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetBlueVideoGain"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentBlueVideoGain = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetBlueVideoGain(TUint aInstanceID, TUint aDesiredBlueVideoGain)
{
    SyncSetBlueVideoGainUpnpOrgRenderingControl2C sync(*this);
    BeginSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetBlueVideoGain(TUint aInstanceID, TUint aDesiredBlueVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetBlueVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBlueVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBlueVideoGain));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetBlueVideoGain(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBlueVideoGain"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetRedVideoBlackLevel(TUint aInstanceID, TUint& aCurrentRedVideoBlackLevel)
{
    SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2C sync(*this, aCurrentRedVideoBlackLevel);
    BeginGetRedVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetRedVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetRedVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRedVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRedVideoBlackLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetRedVideoBlackLevel(IAsync& aAsync, TUint& aCurrentRedVideoBlackLevel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRedVideoBlackLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentRedVideoBlackLevel = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetRedVideoBlackLevel(TUint aInstanceID, TUint aDesiredRedVideoBlackLevel)
{
    SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2C sync(*this);
    BeginSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetRedVideoBlackLevel(TUint aInstanceID, TUint aDesiredRedVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetRedVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRedVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredRedVideoBlackLevel));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetRedVideoBlackLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRedVideoBlackLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetGreenVideoBlackLevel(TUint aInstanceID, TUint& aCurrentGreenVideoBlackLevel)
{
    SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2C sync(*this, aCurrentGreenVideoBlackLevel);
    BeginGetGreenVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetGreenVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetGreenVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetGreenVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetGreenVideoBlackLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetGreenVideoBlackLevel(IAsync& aAsync, TUint& aCurrentGreenVideoBlackLevel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetGreenVideoBlackLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentGreenVideoBlackLevel = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetGreenVideoBlackLevel(TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel)
{
    SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2C sync(*this);
    BeginSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetGreenVideoBlackLevel(TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetGreenVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetGreenVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredGreenVideoBlackLevel));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetGreenVideoBlackLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetGreenVideoBlackLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetBlueVideoBlackLevel(TUint aInstanceID, TUint& aCurrentBlueVideoBlackLevel)
{
    SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2C sync(*this, aCurrentBlueVideoBlackLevel);
    BeginGetBlueVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetBlueVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetBlueVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetBlueVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBlueVideoBlackLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetBlueVideoBlackLevel(IAsync& aAsync, TUint& aCurrentBlueVideoBlackLevel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetBlueVideoBlackLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentBlueVideoBlackLevel = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetBlueVideoBlackLevel(TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel)
{
    SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2C sync(*this);
    BeginSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetBlueVideoBlackLevel(TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetBlueVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBlueVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBlueVideoBlackLevel));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetBlueVideoBlackLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBlueVideoBlackLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetColorTemperature(TUint aInstanceID, TUint& aCurrentColorTemperature)
{
    SyncGetColorTemperatureUpnpOrgRenderingControl2C sync(*this, aCurrentColorTemperature);
    BeginGetColorTemperature(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetColorTemperature(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetColorTemperature, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetColorTemperature->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetColorTemperature->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetColorTemperature(IAsync& aAsync, TUint& aCurrentColorTemperature)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetColorTemperature"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentColorTemperature = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetColorTemperature(TUint aInstanceID, TUint aDesiredColorTemperature)
{
    SyncSetColorTemperatureUpnpOrgRenderingControl2C sync(*this);
    BeginSetColorTemperature(aInstanceID, aDesiredColorTemperature, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetColorTemperature(TUint aInstanceID, TUint aDesiredColorTemperature, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetColorTemperature, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColorTemperature->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredColorTemperature));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetColorTemperature(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetColorTemperature"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetHorizontalKeystone(TUint aInstanceID, TInt& aCurrentHorizontalKeystone)
{
    SyncGetHorizontalKeystoneUpnpOrgRenderingControl2C sync(*this, aCurrentHorizontalKeystone);
    BeginGetHorizontalKeystone(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetHorizontalKeystone(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetHorizontalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetHorizontalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetHorizontalKeystone->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetHorizontalKeystone(IAsync& aAsync, TInt& aCurrentHorizontalKeystone)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetHorizontalKeystone"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentHorizontalKeystone = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetHorizontalKeystone(TUint aInstanceID, TInt aDesiredHorizontalKeystone)
{
    SyncSetHorizontalKeystoneUpnpOrgRenderingControl2C sync(*this);
    BeginSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetHorizontalKeystone(TUint aInstanceID, TInt aDesiredHorizontalKeystone, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetHorizontalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetHorizontalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredHorizontalKeystone));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetHorizontalKeystone(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetHorizontalKeystone"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetVerticalKeystone(TUint aInstanceID, TInt& aCurrentVerticalKeystone)
{
    SyncGetVerticalKeystoneUpnpOrgRenderingControl2C sync(*this, aCurrentVerticalKeystone);
    BeginGetVerticalKeystone(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetVerticalKeystone(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetVerticalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVerticalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVerticalKeystone->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetVerticalKeystone(IAsync& aAsync, TInt& aCurrentVerticalKeystone)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetVerticalKeystone"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentVerticalKeystone = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetVerticalKeystone(TUint aInstanceID, TInt aDesiredVerticalKeystone)
{
    SyncSetVerticalKeystoneUpnpOrgRenderingControl2C sync(*this);
    BeginSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetVerticalKeystone(TUint aInstanceID, TInt aDesiredVerticalKeystone, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetVerticalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVerticalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredVerticalKeystone));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetVerticalKeystone(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVerticalKeystone"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetMute(TUint aInstanceID, const Brx& aChannel, TBool& aCurrentMute)
{
    SyncGetMuteUpnpOrgRenderingControl2C sync(*this, aCurrentMute);
    BeginGetMute(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetMute(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetMute->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetMute(IAsync& aAsync, TBool& aCurrentMute)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetMute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentMute = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetMute(TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute)
{
    SyncSetMuteUpnpOrgRenderingControl2C sync(*this);
    BeginSetMute(aInstanceID, aChannel, aDesiredMute, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetMute(TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredMute));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetMute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetVolume(TUint aInstanceID, const Brx& aChannel, TUint& aCurrentVolume)
{
    SyncGetVolumeUpnpOrgRenderingControl2C sync(*this, aCurrentVolume);
    BeginGetVolume(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetVolume(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetVolume(IAsync& aAsync, TUint& aCurrentVolume)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetVolume"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentVolume = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetVolume(TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume)
{
    SyncSetVolumeUpnpOrgRenderingControl2C sync(*this);
    BeginSetVolume(aInstanceID, aChannel, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetVolume(TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredVolume));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolume"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt& aCurrentVolume)
{
    SyncGetVolumeDBUpnpOrgRenderingControl2C sync(*this, aCurrentVolume);
    BeginGetVolumeDB(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetVolumeDB(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetVolumeDB, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVolumeDB->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVolumeDB->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetVolumeDB(IAsync& aAsync, TInt& aCurrentVolume)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetVolumeDB"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentVolume = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume)
{
    SyncSetVolumeDBUpnpOrgRenderingControl2C sync(*this);
    BeginSetVolumeDB(aInstanceID, aChannel, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetVolumeDB, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolumeDB->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredVolume));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetVolumeDB(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolumeDB"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetVolumeDBRange(TUint aInstanceID, const Brx& aChannel, TInt& aMinValue, TInt& aMaxValue)
{
    SyncGetVolumeDBRangeUpnpOrgRenderingControl2C sync(*this, aMinValue, aMaxValue);
    BeginGetVolumeDBRange(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetVolumeDBRange(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetVolumeDBRange, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVolumeDBRange->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVolumeDBRange->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetVolumeDBRange(IAsync& aAsync, TInt& aMinValue, TInt& aMaxValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetVolumeDBRange"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aMinValue = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    aMaxValue = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetLoudness(TUint aInstanceID, const Brx& aChannel, TBool& aCurrentLoudness)
{
    SyncGetLoudnessUpnpOrgRenderingControl2C sync(*this, aCurrentLoudness);
    BeginGetLoudness(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetLoudness(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetLoudness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetLoudness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLoudness->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetLoudness(IAsync& aAsync, TBool& aCurrentLoudness)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetLoudness"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCurrentLoudness = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetLoudness(TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness)
{
    SyncSetLoudnessUpnpOrgRenderingControl2C sync(*this);
    BeginSetLoudness(aInstanceID, aChannel, aDesiredLoudness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetLoudness(TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetLoudness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLoudness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredLoudness));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetLoudness(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetLoudness"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl2C::SyncGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, Brh& aStateVariableValuePairs)
{
    SyncGetStateVariablesUpnpOrgRenderingControl2C sync(*this, aStateVariableValuePairs);
    BeginGetStateVariables(aInstanceID, aStateVariableList, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetStateVariables, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetStateVariables->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aStateVariableList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStateVariables->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndGetStateVariables(IAsync& aAsync, Brh& aStateVariableValuePairs)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStateVariables"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aStateVariableValuePairs);
}

void CpProxyUpnpOrgRenderingControl2C::SyncSetStateVariables(TUint aInstanceID, const Brx& aRenderingControlUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, Brh& aStateVariableList)
{
    SyncSetStateVariablesUpnpOrgRenderingControl2C sync(*this, aStateVariableList);
    BeginSetStateVariables(aInstanceID, aRenderingControlUDN, aServiceType, aServiceId, aStateVariableValuePairs, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2C::BeginSetStateVariables(TUint aInstanceID, const Brx& aRenderingControlUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetStateVariables, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStateVariables->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRenderingControlUDN));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aServiceType));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aServiceId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aStateVariableValuePairs));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSetStateVariables->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2C::EndSetStateVariables(IAsync& aAsync, Brh& aStateVariableList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStateVariables"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aStateVariableList);
}

void CpProxyUpnpOrgRenderingControl2C::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock.Wait();
    iLastChangeChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgRenderingControl2C::PropertyLastChange(Brhz& aLastChange) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aLastChange.Set(iLastChange->Value());
    PropertyReadUnlock();
}

void CpProxyUpnpOrgRenderingControl2C::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}


THandle CpProxyUpnpOrgRenderingControl2Create(CpDeviceC aDevice)
{
    return new CpProxyUpnpOrgRenderingControl2C(aDevice);
}

void CpProxyUpnpOrgRenderingControl2Destroy(THandle aHandle)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgRenderingControl2SyncListPresets(THandle aHandle, uint32_t aInstanceID, char** aCurrentPresetNameList)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentPresetNameList;
    proxyC->SyncListPresets(aInstanceID, buf_aCurrentPresetNameList);
    *aCurrentPresetNameList = buf_aCurrentPresetNameList.Extract();
}

void CpProxyUpnpOrgRenderingControl2BeginListPresets(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginListPresets(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndListPresets(THandle aHandle, OhNetHandleAsync aAsync, char** aCurrentPresetNameList)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aCurrentPresetNameList;
    *aCurrentPresetNameList = NULL;
    try {
        proxyC->EndListPresets(*async, buf_aCurrentPresetNameList);
        *aCurrentPresetNameList = buf_aCurrentPresetNameList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSelectPreset(THandle aHandle, uint32_t aInstanceID, const char* aPresetName)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPresetName(aPresetName);
    proxyC->SyncSelectPreset(aInstanceID, buf_aPresetName);
}

void CpProxyUpnpOrgRenderingControl2BeginSelectPreset(THandle aHandle, uint32_t aInstanceID, const char* aPresetName, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPresetName(aPresetName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSelectPreset(aInstanceID, buf_aPresetName, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSelectPreset(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSelectPreset(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBrightness)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetBrightness(aInstanceID, *aCurrentBrightness);
}

void CpProxyUpnpOrgRenderingControl2BeginGetBrightness(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetBrightness(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetBrightness(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentBrightness)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetBrightness(*async, *aCurrentBrightness);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBrightness)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetBrightness(aInstanceID, aDesiredBrightness);
}

void CpProxyUpnpOrgRenderingControl2BeginSetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBrightness, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetBrightness(aInstanceID, aDesiredBrightness, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetBrightness(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetBrightness(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentContrast)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetContrast(aInstanceID, *aCurrentContrast);
}

void CpProxyUpnpOrgRenderingControl2BeginGetContrast(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetContrast(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetContrast(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentContrast)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetContrast(*async, *aCurrentContrast);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredContrast)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetContrast(aInstanceID, aDesiredContrast);
}

void CpProxyUpnpOrgRenderingControl2BeginSetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredContrast, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetContrast(aInstanceID, aDesiredContrast, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetContrast(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetContrast(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentSharpness)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetSharpness(aInstanceID, *aCurrentSharpness);
}

void CpProxyUpnpOrgRenderingControl2BeginGetSharpness(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetSharpness(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetSharpness(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentSharpness)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetSharpness(*async, *aCurrentSharpness);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredSharpness)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetSharpness(aInstanceID, aDesiredSharpness);
}

void CpProxyUpnpOrgRenderingControl2BeginSetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredSharpness, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetSharpness(aInstanceID, aDesiredSharpness, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetSharpness(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetSharpness(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentRedVideoGain)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetRedVideoGain(aInstanceID, *aCurrentRedVideoGain);
}

void CpProxyUpnpOrgRenderingControl2BeginGetRedVideoGain(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRedVideoGain(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetRedVideoGain(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentRedVideoGain)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetRedVideoGain(*async, *aCurrentRedVideoGain);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetRedVideoGain(aInstanceID, aDesiredRedVideoGain);
}

void CpProxyUpnpOrgRenderingControl2BeginSetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetRedVideoGain(aInstanceID, aDesiredRedVideoGain, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetRedVideoGain(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetRedVideoGain(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoGain)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetGreenVideoGain(aInstanceID, *aCurrentGreenVideoGain);
}

void CpProxyUpnpOrgRenderingControl2BeginGetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetGreenVideoGain(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetGreenVideoGain(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentGreenVideoGain)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetGreenVideoGain(*async, *aCurrentGreenVideoGain);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain);
}

void CpProxyUpnpOrgRenderingControl2BeginSetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetGreenVideoGain(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetGreenVideoGain(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoGain)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetBlueVideoGain(aInstanceID, *aCurrentBlueVideoGain);
}

void CpProxyUpnpOrgRenderingControl2BeginGetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetBlueVideoGain(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetBlueVideoGain(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentBlueVideoGain)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetBlueVideoGain(*async, *aCurrentBlueVideoGain);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain);
}

void CpProxyUpnpOrgRenderingControl2BeginSetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetBlueVideoGain(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetBlueVideoGain(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentRedVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetRedVideoBlackLevel(aInstanceID, *aCurrentRedVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl2BeginGetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRedVideoBlackLevel(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetRedVideoBlackLevel(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentRedVideoBlackLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetRedVideoBlackLevel(*async, *aCurrentRedVideoBlackLevel);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl2BeginSetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetRedVideoBlackLevel(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetRedVideoBlackLevel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetGreenVideoBlackLevel(aInstanceID, *aCurrentGreenVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl2BeginGetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetGreenVideoBlackLevel(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetGreenVideoBlackLevel(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentGreenVideoBlackLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetGreenVideoBlackLevel(*async, *aCurrentGreenVideoBlackLevel);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl2BeginSetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetGreenVideoBlackLevel(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetGreenVideoBlackLevel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetBlueVideoBlackLevel(aInstanceID, *aCurrentBlueVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl2BeginGetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetBlueVideoBlackLevel(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetBlueVideoBlackLevel(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentBlueVideoBlackLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetBlueVideoBlackLevel(*async, *aCurrentBlueVideoBlackLevel);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl2BeginSetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetBlueVideoBlackLevel(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetBlueVideoBlackLevel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentColorTemperature)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetColorTemperature(aInstanceID, *aCurrentColorTemperature);
}

void CpProxyUpnpOrgRenderingControl2BeginGetColorTemperature(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetColorTemperature(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetColorTemperature(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentColorTemperature)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetColorTemperature(*async, *aCurrentColorTemperature);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredColorTemperature)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetColorTemperature(aInstanceID, aDesiredColorTemperature);
}

void CpProxyUpnpOrgRenderingControl2BeginSetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredColorTemperature, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetColorTemperature(aInstanceID, aDesiredColorTemperature, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetColorTemperature(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetColorTemperature(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t* aCurrentHorizontalKeystone)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetHorizontalKeystone(aInstanceID, *aCurrentHorizontalKeystone);
}

void CpProxyUpnpOrgRenderingControl2BeginGetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetHorizontalKeystone(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetHorizontalKeystone(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aCurrentHorizontalKeystone)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetHorizontalKeystone(*async, *aCurrentHorizontalKeystone);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone);
}

void CpProxyUpnpOrgRenderingControl2BeginSetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetHorizontalKeystone(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetHorizontalKeystone(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t* aCurrentVerticalKeystone)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetVerticalKeystone(aInstanceID, *aCurrentVerticalKeystone);
}

void CpProxyUpnpOrgRenderingControl2BeginGetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetVerticalKeystone(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetVerticalKeystone(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aCurrentVerticalKeystone)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetVerticalKeystone(*async, *aCurrentVerticalKeystone);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone);
}

void CpProxyUpnpOrgRenderingControl2BeginSetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetVerticalKeystone(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetVerticalKeystone(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentMute)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    *aCurrentMute = 0;
    proxyC->SyncGetMute(aInstanceID, buf_aChannel, *(TBool*)aCurrentMute);
}

void CpProxyUpnpOrgRenderingControl2BeginGetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetMute(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetMute(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentMute)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aCurrentMute = 0;
    try {
        proxyC->EndGetMute(*async, *(TBool*)aCurrentMute);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->SyncSetMute(aInstanceID, buf_aChannel, (aDesiredMute==0? false : true));
}

void CpProxyUpnpOrgRenderingControl2BeginSetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetMute(aInstanceID, buf_aChannel, (aDesiredMute==0? false : true), functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetMute(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetMute(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentVolume)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->SyncGetVolume(aInstanceID, buf_aChannel, *aCurrentVolume);
}

void CpProxyUpnpOrgRenderingControl2BeginGetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetVolume(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetVolume(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentVolume)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetVolume(*async, *aCurrentVolume);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->SyncSetVolume(aInstanceID, buf_aChannel, aDesiredVolume);
}

void CpProxyUpnpOrgRenderingControl2BeginSetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetVolume(aInstanceID, buf_aChannel, aDesiredVolume, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetVolume(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetVolume(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t* aCurrentVolume)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->SyncGetVolumeDB(aInstanceID, buf_aChannel, *aCurrentVolume);
}

void CpProxyUpnpOrgRenderingControl2BeginGetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetVolumeDB(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetVolumeDB(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aCurrentVolume)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetVolumeDB(*async, *aCurrentVolume);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->SyncSetVolumeDB(aInstanceID, buf_aChannel, aDesiredVolume);
}

void CpProxyUpnpOrgRenderingControl2BeginSetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetVolumeDB(aInstanceID, buf_aChannel, aDesiredVolume, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetVolumeDB(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetVolumeDB(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetVolumeDBRange(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t* aMinValue, int32_t* aMaxValue)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->SyncGetVolumeDBRange(aInstanceID, buf_aChannel, *aMinValue, *aMaxValue);
}

void CpProxyUpnpOrgRenderingControl2BeginGetVolumeDBRange(THandle aHandle, uint32_t aInstanceID, const char* aChannel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetVolumeDBRange(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetVolumeDBRange(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aMinValue, int32_t* aMaxValue)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetVolumeDBRange(*async, *aMinValue, *aMaxValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentLoudness)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    *aCurrentLoudness = 0;
    proxyC->SyncGetLoudness(aInstanceID, buf_aChannel, *(TBool*)aCurrentLoudness);
}

void CpProxyUpnpOrgRenderingControl2BeginGetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetLoudness(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetLoudness(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentLoudness)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aCurrentLoudness = 0;
    try {
        proxyC->EndGetLoudness(*async, *(TBool*)aCurrentLoudness);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->SyncSetLoudness(aInstanceID, buf_aChannel, (aDesiredLoudness==0? false : true));
}

void CpProxyUpnpOrgRenderingControl2BeginSetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetLoudness(aInstanceID, buf_aChannel, (aDesiredLoudness==0? false : true), functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetLoudness(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetLoudness(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aStateVariableList, char** aStateVariableValuePairs)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aStateVariableList(aStateVariableList);
    Brh buf_aStateVariableValuePairs;
    proxyC->SyncGetStateVariables(aInstanceID, buf_aStateVariableList, buf_aStateVariableValuePairs);
    *aStateVariableValuePairs = buf_aStateVariableValuePairs.Extract();
}

void CpProxyUpnpOrgRenderingControl2BeginGetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aStateVariableList, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aStateVariableList(aStateVariableList);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetStateVariables(aInstanceID, buf_aStateVariableList, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetStateVariables(THandle aHandle, OhNetHandleAsync aAsync, char** aStateVariableValuePairs)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aStateVariableValuePairs;
    *aStateVariableValuePairs = NULL;
    try {
        proxyC->EndGetStateVariables(*async, buf_aStateVariableValuePairs);
        *aStateVariableValuePairs = buf_aStateVariableValuePairs.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aRenderingControlUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, char** aStateVariableList)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRenderingControlUDN(aRenderingControlUDN);
    Brh buf_aServiceType(aServiceType);
    Brh buf_aServiceId(aServiceId);
    Brh buf_aStateVariableValuePairs(aStateVariableValuePairs);
    Brh buf_aStateVariableList;
    proxyC->SyncSetStateVariables(aInstanceID, buf_aRenderingControlUDN, buf_aServiceType, buf_aServiceId, buf_aStateVariableValuePairs, buf_aStateVariableList);
    *aStateVariableList = buf_aStateVariableList.Extract();
}

void CpProxyUpnpOrgRenderingControl2BeginSetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aRenderingControlUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRenderingControlUDN(aRenderingControlUDN);
    Brh buf_aServiceType(aServiceType);
    Brh buf_aServiceId(aServiceId);
    Brh buf_aStateVariableValuePairs(aStateVariableValuePairs);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetStateVariables(aInstanceID, buf_aRenderingControlUDN, buf_aServiceType, buf_aServiceId, buf_aStateVariableValuePairs, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetStateVariables(THandle aHandle, OhNetHandleAsync aAsync, char** aStateVariableList)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aStateVariableList;
    *aStateVariableList = NULL;
    try {
        proxyC->EndSetStateVariables(*async, buf_aStateVariableList);
        *aStateVariableList = buf_aStateVariableList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SetPropertyLastChangeChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyLastChangeChanged(functor);
}

void CpProxyUpnpOrgRenderingControl2PropertyLastChange(THandle aHandle, char** aLastChange)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aLastChange;
    proxyC->PropertyLastChange(buf_aLastChange);
    *aLastChange = buf_aLastChange.Transfer();
}

