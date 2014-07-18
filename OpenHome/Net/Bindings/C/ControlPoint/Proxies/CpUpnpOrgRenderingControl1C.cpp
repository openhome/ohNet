#include "CpUpnpOrgRenderingControl1.h"
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/C/CpProxyCPrivate.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class CpProxyUpnpOrgRenderingControl1C : public CpProxyC
{
public:
    CpProxyUpnpOrgRenderingControl1C(CpDeviceC aDevice);
    ~CpProxyUpnpOrgRenderingControl1C();
    //CpProxyUpnpOrgRenderingControl1* Proxy() { return static_cast<CpProxyUpnpOrgRenderingControl1*>(iProxy); }

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
    PropertyString* iLastChange;
    Functor iLastChangeChanged;
};


class SyncListPresetsUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncListPresetsUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, Brh& aCurrentPresetNameList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncListPresetsUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    Brh& iCurrentPresetNameList;
};

SyncListPresetsUpnpOrgRenderingControl1C::SyncListPresetsUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, Brh& aCurrentPresetNameList)
    : iService(aProxy)
    , iCurrentPresetNameList(aCurrentPresetNameList)
{
}

void SyncListPresetsUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndListPresets(aAsync, iCurrentPresetNameList);
}


class SyncSelectPresetUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSelectPresetUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSelectPresetUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSelectPresetUpnpOrgRenderingControl1C::SyncSelectPresetUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSelectPresetUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSelectPreset(aAsync);
}


class SyncGetBrightnessUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetBrightnessUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentBrightness);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBrightnessUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TUint& iCurrentBrightness;
};

SyncGetBrightnessUpnpOrgRenderingControl1C::SyncGetBrightnessUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentBrightness)
    : iService(aProxy)
    , iCurrentBrightness(aCurrentBrightness)
{
}

void SyncGetBrightnessUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBrightness(aAsync, iCurrentBrightness);
}


class SyncSetBrightnessUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetBrightnessUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBrightnessUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetBrightnessUpnpOrgRenderingControl1C::SyncSetBrightnessUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetBrightnessUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBrightness(aAsync);
}


class SyncGetContrastUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetContrastUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentContrast);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetContrastUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TUint& iCurrentContrast;
};

SyncGetContrastUpnpOrgRenderingControl1C::SyncGetContrastUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentContrast)
    : iService(aProxy)
    , iCurrentContrast(aCurrentContrast)
{
}

void SyncGetContrastUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetContrast(aAsync, iCurrentContrast);
}


class SyncSetContrastUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetContrastUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetContrastUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetContrastUpnpOrgRenderingControl1C::SyncSetContrastUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetContrastUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetContrast(aAsync);
}


class SyncGetSharpnessUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetSharpnessUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentSharpness);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSharpnessUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TUint& iCurrentSharpness;
};

SyncGetSharpnessUpnpOrgRenderingControl1C::SyncGetSharpnessUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentSharpness)
    : iService(aProxy)
    , iCurrentSharpness(aCurrentSharpness)
{
}

void SyncGetSharpnessUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSharpness(aAsync, iCurrentSharpness);
}


class SyncSetSharpnessUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetSharpnessUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetSharpnessUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetSharpnessUpnpOrgRenderingControl1C::SyncSetSharpnessUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetSharpnessUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSharpness(aAsync);
}


class SyncGetRedVideoGainUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetRedVideoGainUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentRedVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRedVideoGainUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TUint& iCurrentRedVideoGain;
};

SyncGetRedVideoGainUpnpOrgRenderingControl1C::SyncGetRedVideoGainUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentRedVideoGain)
    : iService(aProxy)
    , iCurrentRedVideoGain(aCurrentRedVideoGain)
{
}

void SyncGetRedVideoGainUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRedVideoGain(aAsync, iCurrentRedVideoGain);
}


class SyncSetRedVideoGainUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetRedVideoGainUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRedVideoGainUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetRedVideoGainUpnpOrgRenderingControl1C::SyncSetRedVideoGainUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetRedVideoGainUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRedVideoGain(aAsync);
}


class SyncGetGreenVideoGainUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetGreenVideoGainUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentGreenVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetGreenVideoGainUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TUint& iCurrentGreenVideoGain;
};

SyncGetGreenVideoGainUpnpOrgRenderingControl1C::SyncGetGreenVideoGainUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentGreenVideoGain)
    : iService(aProxy)
    , iCurrentGreenVideoGain(aCurrentGreenVideoGain)
{
}

void SyncGetGreenVideoGainUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetGreenVideoGain(aAsync, iCurrentGreenVideoGain);
}


class SyncSetGreenVideoGainUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetGreenVideoGainUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetGreenVideoGainUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetGreenVideoGainUpnpOrgRenderingControl1C::SyncSetGreenVideoGainUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetGreenVideoGainUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetGreenVideoGain(aAsync);
}


class SyncGetBlueVideoGainUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetBlueVideoGainUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentBlueVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBlueVideoGainUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TUint& iCurrentBlueVideoGain;
};

SyncGetBlueVideoGainUpnpOrgRenderingControl1C::SyncGetBlueVideoGainUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentBlueVideoGain)
    : iService(aProxy)
    , iCurrentBlueVideoGain(aCurrentBlueVideoGain)
{
}

void SyncGetBlueVideoGainUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBlueVideoGain(aAsync, iCurrentBlueVideoGain);
}


class SyncSetBlueVideoGainUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetBlueVideoGainUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBlueVideoGainUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetBlueVideoGainUpnpOrgRenderingControl1C::SyncSetBlueVideoGainUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetBlueVideoGainUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBlueVideoGain(aAsync);
}


class SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentRedVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TUint& iCurrentRedVideoBlackLevel;
};

SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1C::SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentRedVideoBlackLevel)
    : iService(aProxy)
    , iCurrentRedVideoBlackLevel(aCurrentRedVideoBlackLevel)
{
}

void SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRedVideoBlackLevel(aAsync, iCurrentRedVideoBlackLevel);
}


class SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1C::SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRedVideoBlackLevel(aAsync);
}


class SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentGreenVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TUint& iCurrentGreenVideoBlackLevel;
};

SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1C::SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentGreenVideoBlackLevel)
    : iService(aProxy)
    , iCurrentGreenVideoBlackLevel(aCurrentGreenVideoBlackLevel)
{
}

void SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetGreenVideoBlackLevel(aAsync, iCurrentGreenVideoBlackLevel);
}


class SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1C::SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetGreenVideoBlackLevel(aAsync);
}


class SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentBlueVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TUint& iCurrentBlueVideoBlackLevel;
};

SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1C::SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentBlueVideoBlackLevel)
    : iService(aProxy)
    , iCurrentBlueVideoBlackLevel(aCurrentBlueVideoBlackLevel)
{
}

void SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBlueVideoBlackLevel(aAsync, iCurrentBlueVideoBlackLevel);
}


class SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1C::SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBlueVideoBlackLevel(aAsync);
}


class SyncGetColorTemperatureUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetColorTemperatureUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentColorTemperature);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetColorTemperatureUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TUint& iCurrentColorTemperature;
};

SyncGetColorTemperatureUpnpOrgRenderingControl1C::SyncGetColorTemperatureUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentColorTemperature)
    : iService(aProxy)
    , iCurrentColorTemperature(aCurrentColorTemperature)
{
}

void SyncGetColorTemperatureUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColorTemperature(aAsync, iCurrentColorTemperature);
}


class SyncSetColorTemperatureUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetColorTemperatureUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetColorTemperatureUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetColorTemperatureUpnpOrgRenderingControl1C::SyncSetColorTemperatureUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetColorTemperatureUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColorTemperature(aAsync);
}


class SyncGetHorizontalKeystoneUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetHorizontalKeystoneUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TInt& aCurrentHorizontalKeystone);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetHorizontalKeystoneUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TInt& iCurrentHorizontalKeystone;
};

SyncGetHorizontalKeystoneUpnpOrgRenderingControl1C::SyncGetHorizontalKeystoneUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TInt& aCurrentHorizontalKeystone)
    : iService(aProxy)
    , iCurrentHorizontalKeystone(aCurrentHorizontalKeystone)
{
}

void SyncGetHorizontalKeystoneUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetHorizontalKeystone(aAsync, iCurrentHorizontalKeystone);
}


class SyncSetHorizontalKeystoneUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetHorizontalKeystoneUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetHorizontalKeystoneUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetHorizontalKeystoneUpnpOrgRenderingControl1C::SyncSetHorizontalKeystoneUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetHorizontalKeystoneUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetHorizontalKeystone(aAsync);
}


class SyncGetVerticalKeystoneUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetVerticalKeystoneUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TInt& aCurrentVerticalKeystone);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVerticalKeystoneUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TInt& iCurrentVerticalKeystone;
};

SyncGetVerticalKeystoneUpnpOrgRenderingControl1C::SyncGetVerticalKeystoneUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TInt& aCurrentVerticalKeystone)
    : iService(aProxy)
    , iCurrentVerticalKeystone(aCurrentVerticalKeystone)
{
}

void SyncGetVerticalKeystoneUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVerticalKeystone(aAsync, iCurrentVerticalKeystone);
}


class SyncSetVerticalKeystoneUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetVerticalKeystoneUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVerticalKeystoneUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetVerticalKeystoneUpnpOrgRenderingControl1C::SyncSetVerticalKeystoneUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetVerticalKeystoneUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVerticalKeystone(aAsync);
}


class SyncGetMuteUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetMuteUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TBool& aCurrentMute);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetMuteUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TBool& iCurrentMute;
};

SyncGetMuteUpnpOrgRenderingControl1C::SyncGetMuteUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TBool& aCurrentMute)
    : iService(aProxy)
    , iCurrentMute(aCurrentMute)
{
}

void SyncGetMuteUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMute(aAsync, iCurrentMute);
}


class SyncSetMuteUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetMuteUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetMuteUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetMuteUpnpOrgRenderingControl1C::SyncSetMuteUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetMuteUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMute(aAsync);
}


class SyncGetVolumeUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetVolumeUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVolumeUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TUint& iCurrentVolume;
};

SyncGetVolumeUpnpOrgRenderingControl1C::SyncGetVolumeUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TUint& aCurrentVolume)
    : iService(aProxy)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetVolumeUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolume(aAsync, iCurrentVolume);
}


class SyncSetVolumeUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetVolumeUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVolumeUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetVolumeUpnpOrgRenderingControl1C::SyncSetVolumeUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolume(aAsync);
}


class SyncGetVolumeDBUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetVolumeDBUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TInt& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVolumeDBUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TInt& iCurrentVolume;
};

SyncGetVolumeDBUpnpOrgRenderingControl1C::SyncGetVolumeDBUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TInt& aCurrentVolume)
    : iService(aProxy)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetVolumeDBUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolumeDB(aAsync, iCurrentVolume);
}


class SyncSetVolumeDBUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetVolumeDBUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVolumeDBUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetVolumeDBUpnpOrgRenderingControl1C::SyncSetVolumeDBUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeDBUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolumeDB(aAsync);
}


class SyncGetVolumeDBRangeUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetVolumeDBRangeUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TInt& aMinValue, TInt& aMaxValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVolumeDBRangeUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TInt& iMinValue;
    TInt& iMaxValue;
};

SyncGetVolumeDBRangeUpnpOrgRenderingControl1C::SyncGetVolumeDBRangeUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TInt& aMinValue, TInt& aMaxValue)
    : iService(aProxy)
    , iMinValue(aMinValue)
    , iMaxValue(aMaxValue)
{
}

void SyncGetVolumeDBRangeUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolumeDBRange(aAsync, iMinValue, iMaxValue);
}


class SyncGetLoudnessUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncGetLoudnessUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TBool& aCurrentLoudness);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetLoudnessUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
    TBool& iCurrentLoudness;
};

SyncGetLoudnessUpnpOrgRenderingControl1C::SyncGetLoudnessUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy, TBool& aCurrentLoudness)
    : iService(aProxy)
    , iCurrentLoudness(aCurrentLoudness)
{
}

void SyncGetLoudnessUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLoudness(aAsync, iCurrentLoudness);
}


class SyncSetLoudnessUpnpOrgRenderingControl1C : public SyncProxyAction
{
public:
    SyncSetLoudnessUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetLoudnessUpnpOrgRenderingControl1C() {};
private:
    CpProxyUpnpOrgRenderingControl1C& iService;
};

SyncSetLoudnessUpnpOrgRenderingControl1C::SyncSetLoudnessUpnpOrgRenderingControl1C(CpProxyUpnpOrgRenderingControl1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetLoudnessUpnpOrgRenderingControl1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLoudness(aAsync);
}

CpProxyUpnpOrgRenderingControl1C::CpProxyUpnpOrgRenderingControl1C(CpDeviceC aDevice)
    : CpProxyC("schemas-upnp-org", "RenderingControl", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    OpenHome::Net::Parameter* param;

    iActionListPresets = new Action("ListPresets");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionListPresets->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("CurrentPresetNameList");
    iActionListPresets->AddOutputParameter(param);

    iActionSelectPreset = new Action("SelectPreset");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSelectPreset->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("PresetName");
    iActionSelectPreset->AddInputParameter(param);

    iActionGetBrightness = new Action("GetBrightness");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetBrightness->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentBrightness", 0, 2147483647, 1);
    iActionGetBrightness->AddOutputParameter(param);

    iActionSetBrightness = new Action("SetBrightness");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetBrightness->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredBrightness", 0, 2147483647, 1);
    iActionSetBrightness->AddInputParameter(param);

    iActionGetContrast = new Action("GetContrast");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetContrast->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentContrast", 0, 2147483647, 1);
    iActionGetContrast->AddOutputParameter(param);

    iActionSetContrast = new Action("SetContrast");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetContrast->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredContrast", 0, 2147483647, 1);
    iActionSetContrast->AddInputParameter(param);

    iActionGetSharpness = new Action("GetSharpness");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetSharpness->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentSharpness", 0, 2147483647, 1);
    iActionGetSharpness->AddOutputParameter(param);

    iActionSetSharpness = new Action("SetSharpness");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetSharpness->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredSharpness", 0, 2147483647, 1);
    iActionSetSharpness->AddInputParameter(param);

    iActionGetRedVideoGain = new Action("GetRedVideoGain");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetRedVideoGain->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentRedVideoGain", 0, 2147483647, 1);
    iActionGetRedVideoGain->AddOutputParameter(param);

    iActionSetRedVideoGain = new Action("SetRedVideoGain");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetRedVideoGain->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredRedVideoGain", 0, 2147483647, 1);
    iActionSetRedVideoGain->AddInputParameter(param);

    iActionGetGreenVideoGain = new Action("GetGreenVideoGain");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetGreenVideoGain->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentGreenVideoGain", 0, 2147483647, 1);
    iActionGetGreenVideoGain->AddOutputParameter(param);

    iActionSetGreenVideoGain = new Action("SetGreenVideoGain");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetGreenVideoGain->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredGreenVideoGain", 0, 2147483647, 1);
    iActionSetGreenVideoGain->AddInputParameter(param);

    iActionGetBlueVideoGain = new Action("GetBlueVideoGain");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetBlueVideoGain->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentBlueVideoGain", 0, 2147483647, 1);
    iActionGetBlueVideoGain->AddOutputParameter(param);

    iActionSetBlueVideoGain = new Action("SetBlueVideoGain");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetBlueVideoGain->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredBlueVideoGain", 0, 2147483647, 1);
    iActionSetBlueVideoGain->AddInputParameter(param);

    iActionGetRedVideoBlackLevel = new Action("GetRedVideoBlackLevel");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetRedVideoBlackLevel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentRedVideoBlackLevel", 0, 2147483647, 1);
    iActionGetRedVideoBlackLevel->AddOutputParameter(param);

    iActionSetRedVideoBlackLevel = new Action("SetRedVideoBlackLevel");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetRedVideoBlackLevel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredRedVideoBlackLevel", 0, 2147483647, 1);
    iActionSetRedVideoBlackLevel->AddInputParameter(param);

    iActionGetGreenVideoBlackLevel = new Action("GetGreenVideoBlackLevel");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetGreenVideoBlackLevel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentGreenVideoBlackLevel", 0, 2147483647, 1);
    iActionGetGreenVideoBlackLevel->AddOutputParameter(param);

    iActionSetGreenVideoBlackLevel = new Action("SetGreenVideoBlackLevel");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetGreenVideoBlackLevel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredGreenVideoBlackLevel", 0, 2147483647, 1);
    iActionSetGreenVideoBlackLevel->AddInputParameter(param);

    iActionGetBlueVideoBlackLevel = new Action("GetBlueVideoBlackLevel");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetBlueVideoBlackLevel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentBlueVideoBlackLevel", 0, 2147483647, 1);
    iActionGetBlueVideoBlackLevel->AddOutputParameter(param);

    iActionSetBlueVideoBlackLevel = new Action("SetBlueVideoBlackLevel");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetBlueVideoBlackLevel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredBlueVideoBlackLevel", 0, 2147483647, 1);
    iActionSetBlueVideoBlackLevel->AddInputParameter(param);

    iActionGetColorTemperature = new Action("GetColorTemperature");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetColorTemperature->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentColorTemperature", 0, 2147483647, 1);
    iActionGetColorTemperature->AddOutputParameter(param);

    iActionSetColorTemperature = new Action("SetColorTemperature");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetColorTemperature->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredColorTemperature", 0, 2147483647, 1);
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
    param = new OpenHome::Net::ParameterString("Channel");
    iActionGetMute->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBool("CurrentMute");
    iActionGetMute->AddOutputParameter(param);

    iActionSetMute = new Action("SetMute");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetMute->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Channel");
    iActionSetMute->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBool("DesiredMute");
    iActionSetMute->AddInputParameter(param);

    iActionGetVolume = new Action("GetVolume");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetVolume->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Channel");
    iActionGetVolume->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("CurrentVolume", 0, 2147483647, 1);
    iActionGetVolume->AddOutputParameter(param);

    iActionSetVolume = new Action("SetVolume");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetVolume->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Channel");
    iActionSetVolume->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("DesiredVolume", 0, 2147483647, 1);
    iActionSetVolume->AddInputParameter(param);

    iActionGetVolumeDB = new Action("GetVolumeDB");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetVolumeDB->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Channel");
    iActionGetVolumeDB->AddInputParameter(param);
    param = new OpenHome::Net::ParameterInt("CurrentVolume");
    iActionGetVolumeDB->AddOutputParameter(param);

    iActionSetVolumeDB = new Action("SetVolumeDB");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetVolumeDB->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Channel");
    iActionSetVolumeDB->AddInputParameter(param);
    param = new OpenHome::Net::ParameterInt("DesiredVolume");
    iActionSetVolumeDB->AddInputParameter(param);

    iActionGetVolumeDBRange = new Action("GetVolumeDBRange");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetVolumeDBRange->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Channel");
    iActionGetVolumeDBRange->AddInputParameter(param);
    param = new OpenHome::Net::ParameterInt("MinValue");
    iActionGetVolumeDBRange->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterInt("MaxValue");
    iActionGetVolumeDBRange->AddOutputParameter(param);

    iActionGetLoudness = new Action("GetLoudness");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionGetLoudness->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Channel");
    iActionGetLoudness->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBool("CurrentLoudness");
    iActionGetLoudness->AddOutputParameter(param);

    iActionSetLoudness = new Action("SetLoudness");
    param = new OpenHome::Net::ParameterUint("InstanceID");
    iActionSetLoudness->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Channel");
    iActionSetLoudness->AddInputParameter(param);
    param = new OpenHome::Net::ParameterBool("DesiredLoudness");
    iActionSetLoudness->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgRenderingControl1C::LastChangePropertyChanged);
    iLastChange = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
}

CpProxyUpnpOrgRenderingControl1C::~CpProxyUpnpOrgRenderingControl1C()
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
}

void CpProxyUpnpOrgRenderingControl1C::SyncListPresets(TUint aInstanceID, Brh& aCurrentPresetNameList)
{
    SyncListPresetsUpnpOrgRenderingControl1C sync(*this, aCurrentPresetNameList);
    BeginListPresets(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginListPresets(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndListPresets(IAsync& aAsync, Brh& aCurrentPresetNameList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ListPresets"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCurrentPresetNameList);
}

void CpProxyUpnpOrgRenderingControl1C::SyncSelectPreset(TUint aInstanceID, const Brx& aPresetName)
{
    SyncSelectPresetUpnpOrgRenderingControl1C sync(*this);
    BeginSelectPreset(aInstanceID, aPresetName, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSelectPreset(TUint aInstanceID, const Brx& aPresetName, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSelectPreset, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSelectPreset->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aPresetName));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSelectPreset(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SelectPreset"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetBrightness(TUint aInstanceID, TUint& aCurrentBrightness)
{
    SyncGetBrightnessUpnpOrgRenderingControl1C sync(*this, aCurrentBrightness);
    BeginGetBrightness(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetBrightness(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetBrightness(IAsync& aAsync, TUint& aCurrentBrightness)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetBrightness"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentBrightness = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetBrightness(TUint aInstanceID, TUint aDesiredBrightness)
{
    SyncSetBrightnessUpnpOrgRenderingControl1C sync(*this);
    BeginSetBrightness(aInstanceID, aDesiredBrightness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetBrightness(TUint aInstanceID, TUint aDesiredBrightness, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetBrightness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBrightness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBrightness));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetBrightness(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBrightness"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetContrast(TUint aInstanceID, TUint& aCurrentContrast)
{
    SyncGetContrastUpnpOrgRenderingControl1C sync(*this, aCurrentContrast);
    BeginGetContrast(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetContrast(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetContrast(IAsync& aAsync, TUint& aCurrentContrast)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetContrast"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentContrast = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetContrast(TUint aInstanceID, TUint aDesiredContrast)
{
    SyncSetContrastUpnpOrgRenderingControl1C sync(*this);
    BeginSetContrast(aInstanceID, aDesiredContrast, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetContrast(TUint aInstanceID, TUint aDesiredContrast, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetContrast, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetContrast->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredContrast));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetContrast(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetContrast"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetSharpness(TUint aInstanceID, TUint& aCurrentSharpness)
{
    SyncGetSharpnessUpnpOrgRenderingControl1C sync(*this, aCurrentSharpness);
    BeginGetSharpness(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetSharpness(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetSharpness(IAsync& aAsync, TUint& aCurrentSharpness)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetSharpness"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentSharpness = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetSharpness(TUint aInstanceID, TUint aDesiredSharpness)
{
    SyncSetSharpnessUpnpOrgRenderingControl1C sync(*this);
    BeginSetSharpness(aInstanceID, aDesiredSharpness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetSharpness(TUint aInstanceID, TUint aDesiredSharpness, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetSharpness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSharpness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredSharpness));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetSharpness(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSharpness"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetRedVideoGain(TUint aInstanceID, TUint& aCurrentRedVideoGain)
{
    SyncGetRedVideoGainUpnpOrgRenderingControl1C sync(*this, aCurrentRedVideoGain);
    BeginGetRedVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetRedVideoGain(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetRedVideoGain(IAsync& aAsync, TUint& aCurrentRedVideoGain)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRedVideoGain"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentRedVideoGain = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetRedVideoGain(TUint aInstanceID, TUint aDesiredRedVideoGain)
{
    SyncSetRedVideoGainUpnpOrgRenderingControl1C sync(*this);
    BeginSetRedVideoGain(aInstanceID, aDesiredRedVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetRedVideoGain(TUint aInstanceID, TUint aDesiredRedVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetRedVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRedVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredRedVideoGain));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetRedVideoGain(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRedVideoGain"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetGreenVideoGain(TUint aInstanceID, TUint& aCurrentGreenVideoGain)
{
    SyncGetGreenVideoGainUpnpOrgRenderingControl1C sync(*this, aCurrentGreenVideoGain);
    BeginGetGreenVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetGreenVideoGain(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetGreenVideoGain(IAsync& aAsync, TUint& aCurrentGreenVideoGain)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetGreenVideoGain"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentGreenVideoGain = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetGreenVideoGain(TUint aInstanceID, TUint aDesiredGreenVideoGain)
{
    SyncSetGreenVideoGainUpnpOrgRenderingControl1C sync(*this);
    BeginSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetGreenVideoGain(TUint aInstanceID, TUint aDesiredGreenVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetGreenVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetGreenVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredGreenVideoGain));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetGreenVideoGain(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetGreenVideoGain"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetBlueVideoGain(TUint aInstanceID, TUint& aCurrentBlueVideoGain)
{
    SyncGetBlueVideoGainUpnpOrgRenderingControl1C sync(*this, aCurrentBlueVideoGain);
    BeginGetBlueVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetBlueVideoGain(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetBlueVideoGain(IAsync& aAsync, TUint& aCurrentBlueVideoGain)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetBlueVideoGain"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentBlueVideoGain = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetBlueVideoGain(TUint aInstanceID, TUint aDesiredBlueVideoGain)
{
    SyncSetBlueVideoGainUpnpOrgRenderingControl1C sync(*this);
    BeginSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetBlueVideoGain(TUint aInstanceID, TUint aDesiredBlueVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetBlueVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBlueVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBlueVideoGain));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetBlueVideoGain(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBlueVideoGain"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetRedVideoBlackLevel(TUint aInstanceID, TUint& aCurrentRedVideoBlackLevel)
{
    SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1C sync(*this, aCurrentRedVideoBlackLevel);
    BeginGetRedVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetRedVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetRedVideoBlackLevel(IAsync& aAsync, TUint& aCurrentRedVideoBlackLevel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRedVideoBlackLevel"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentRedVideoBlackLevel = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetRedVideoBlackLevel(TUint aInstanceID, TUint aDesiredRedVideoBlackLevel)
{
    SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1C sync(*this);
    BeginSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetRedVideoBlackLevel(TUint aInstanceID, TUint aDesiredRedVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetRedVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRedVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredRedVideoBlackLevel));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetRedVideoBlackLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRedVideoBlackLevel"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetGreenVideoBlackLevel(TUint aInstanceID, TUint& aCurrentGreenVideoBlackLevel)
{
    SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1C sync(*this, aCurrentGreenVideoBlackLevel);
    BeginGetGreenVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetGreenVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetGreenVideoBlackLevel(IAsync& aAsync, TUint& aCurrentGreenVideoBlackLevel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetGreenVideoBlackLevel"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentGreenVideoBlackLevel = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetGreenVideoBlackLevel(TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel)
{
    SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1C sync(*this);
    BeginSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetGreenVideoBlackLevel(TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetGreenVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetGreenVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredGreenVideoBlackLevel));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetGreenVideoBlackLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetGreenVideoBlackLevel"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetBlueVideoBlackLevel(TUint aInstanceID, TUint& aCurrentBlueVideoBlackLevel)
{
    SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1C sync(*this, aCurrentBlueVideoBlackLevel);
    BeginGetBlueVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetBlueVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetBlueVideoBlackLevel(IAsync& aAsync, TUint& aCurrentBlueVideoBlackLevel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetBlueVideoBlackLevel"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentBlueVideoBlackLevel = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetBlueVideoBlackLevel(TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel)
{
    SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1C sync(*this);
    BeginSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetBlueVideoBlackLevel(TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetBlueVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBlueVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBlueVideoBlackLevel));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetBlueVideoBlackLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBlueVideoBlackLevel"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetColorTemperature(TUint aInstanceID, TUint& aCurrentColorTemperature)
{
    SyncGetColorTemperatureUpnpOrgRenderingControl1C sync(*this, aCurrentColorTemperature);
    BeginGetColorTemperature(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetColorTemperature(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetColorTemperature(IAsync& aAsync, TUint& aCurrentColorTemperature)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetColorTemperature"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentColorTemperature = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetColorTemperature(TUint aInstanceID, TUint aDesiredColorTemperature)
{
    SyncSetColorTemperatureUpnpOrgRenderingControl1C sync(*this);
    BeginSetColorTemperature(aInstanceID, aDesiredColorTemperature, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetColorTemperature(TUint aInstanceID, TUint aDesiredColorTemperature, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetColorTemperature, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColorTemperature->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredColorTemperature));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetColorTemperature(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetColorTemperature"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetHorizontalKeystone(TUint aInstanceID, TInt& aCurrentHorizontalKeystone)
{
    SyncGetHorizontalKeystoneUpnpOrgRenderingControl1C sync(*this, aCurrentHorizontalKeystone);
    BeginGetHorizontalKeystone(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetHorizontalKeystone(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetHorizontalKeystone(IAsync& aAsync, TInt& aCurrentHorizontalKeystone)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetHorizontalKeystone"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentHorizontalKeystone = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetHorizontalKeystone(TUint aInstanceID, TInt aDesiredHorizontalKeystone)
{
    SyncSetHorizontalKeystoneUpnpOrgRenderingControl1C sync(*this);
    BeginSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetHorizontalKeystone(TUint aInstanceID, TInt aDesiredHorizontalKeystone, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetHorizontalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetHorizontalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredHorizontalKeystone));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetHorizontalKeystone(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetHorizontalKeystone"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetVerticalKeystone(TUint aInstanceID, TInt& aCurrentVerticalKeystone)
{
    SyncGetVerticalKeystoneUpnpOrgRenderingControl1C sync(*this, aCurrentVerticalKeystone);
    BeginGetVerticalKeystone(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetVerticalKeystone(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetVerticalKeystone(IAsync& aAsync, TInt& aCurrentVerticalKeystone)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetVerticalKeystone"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentVerticalKeystone = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetVerticalKeystone(TUint aInstanceID, TInt aDesiredVerticalKeystone)
{
    SyncSetVerticalKeystoneUpnpOrgRenderingControl1C sync(*this);
    BeginSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetVerticalKeystone(TUint aInstanceID, TInt aDesiredVerticalKeystone, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetVerticalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVerticalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredVerticalKeystone));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetVerticalKeystone(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVerticalKeystone"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetMute(TUint aInstanceID, const Brx& aChannel, TBool& aCurrentMute)
{
    SyncGetMuteUpnpOrgRenderingControl1C sync(*this, aCurrentMute);
    BeginGetMute(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetMute(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetMute(IAsync& aAsync, TBool& aCurrentMute)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetMute"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentMute = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetMute(TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute)
{
    SyncSetMuteUpnpOrgRenderingControl1C sync(*this);
    BeginSetMute(aInstanceID, aChannel, aDesiredMute, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetMute(TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredMute));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetMute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMute"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetVolume(TUint aInstanceID, const Brx& aChannel, TUint& aCurrentVolume)
{
    SyncGetVolumeUpnpOrgRenderingControl1C sync(*this, aCurrentVolume);
    BeginGetVolume(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetVolume(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetVolume(IAsync& aAsync, TUint& aCurrentVolume)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetVolume"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentVolume = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetVolume(TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume)
{
    SyncSetVolumeUpnpOrgRenderingControl1C sync(*this);
    BeginSetVolume(aInstanceID, aChannel, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetVolume(TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredVolume));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolume"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt& aCurrentVolume)
{
    SyncGetVolumeDBUpnpOrgRenderingControl1C sync(*this, aCurrentVolume);
    BeginGetVolumeDB(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetVolumeDB(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetVolumeDB(IAsync& aAsync, TInt& aCurrentVolume)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetVolumeDB"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentVolume = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume)
{
    SyncSetVolumeDBUpnpOrgRenderingControl1C sync(*this);
    BeginSetVolumeDB(aInstanceID, aChannel, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetVolumeDB, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolumeDB->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredVolume));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetVolumeDB(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolumeDB"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetVolumeDBRange(TUint aInstanceID, const Brx& aChannel, TInt& aMinValue, TInt& aMaxValue)
{
    SyncGetVolumeDBRangeUpnpOrgRenderingControl1C sync(*this, aMinValue, aMaxValue);
    BeginGetVolumeDBRange(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetVolumeDBRange(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetVolumeDBRange(IAsync& aAsync, TInt& aMinValue, TInt& aMaxValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetVolumeDBRange"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aMinValue = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
    aMaxValue = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncGetLoudness(TUint aInstanceID, const Brx& aChannel, TBool& aCurrentLoudness)
{
    SyncGetLoudnessUpnpOrgRenderingControl1C sync(*this, aCurrentLoudness);
    BeginGetLoudness(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginGetLoudness(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1C::EndGetLoudness(IAsync& aAsync, TBool& aCurrentLoudness)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetLoudness"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCurrentLoudness = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgRenderingControl1C::SyncSetLoudness(TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness)
{
    SyncSetLoudnessUpnpOrgRenderingControl1C sync(*this);
    BeginSetLoudness(aInstanceID, aChannel, aDesiredLoudness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1C::BeginSetLoudness(TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetLoudness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLoudness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredLoudness));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1C::EndSetLoudness(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetLoudness"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgRenderingControl1C::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock.Wait();
    iLastChangeChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgRenderingControl1C::PropertyLastChange(Brhz& aLastChange) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aLastChange.Set(iLastChange->Value());
}

void CpProxyUpnpOrgRenderingControl1C::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}


THandle STDCALL CpProxyUpnpOrgRenderingControl1Create(CpDeviceC aDevice)
{
    return new CpProxyUpnpOrgRenderingControl1C(aDevice);
}

void STDCALL CpProxyUpnpOrgRenderingControl1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncListPresets(THandle aHandle, uint32_t aInstanceID, char** aCurrentPresetNameList)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentPresetNameList;
    int32_t err = 0;
    try {
        proxyC->SyncListPresets(aInstanceID, buf_aCurrentPresetNameList);
        *aCurrentPresetNameList = buf_aCurrentPresetNameList.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentPresetNameList = NULL;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginListPresets(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginListPresets(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndListPresets(THandle aHandle, OhNetHandleAsync aAsync, char** aCurrentPresetNameList)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSelectPreset(THandle aHandle, uint32_t aInstanceID, const char* aPresetName)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPresetName(aPresetName);
    int32_t err = 0;
    try {
        proxyC->SyncSelectPreset(aInstanceID, buf_aPresetName);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSelectPreset(THandle aHandle, uint32_t aInstanceID, const char* aPresetName, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPresetName(aPresetName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSelectPreset(aInstanceID, buf_aPresetName, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSelectPreset(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBrightness)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetBrightness(aInstanceID, *aCurrentBrightness);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentBrightness = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetBrightness(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetBrightness(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetBrightness(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentBrightness)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBrightness)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetBrightness(aInstanceID, aDesiredBrightness);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBrightness, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetBrightness(aInstanceID, aDesiredBrightness, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetBrightness(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentContrast)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetContrast(aInstanceID, *aCurrentContrast);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentContrast = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetContrast(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetContrast(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetContrast(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentContrast)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredContrast)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetContrast(aInstanceID, aDesiredContrast);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredContrast, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetContrast(aInstanceID, aDesiredContrast, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetContrast(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentSharpness)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetSharpness(aInstanceID, *aCurrentSharpness);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentSharpness = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetSharpness(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetSharpness(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetSharpness(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentSharpness)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredSharpness)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetSharpness(aInstanceID, aDesiredSharpness);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredSharpness, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetSharpness(aInstanceID, aDesiredSharpness, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetSharpness(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentRedVideoGain)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetRedVideoGain(aInstanceID, *aCurrentRedVideoGain);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentRedVideoGain = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetRedVideoGain(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRedVideoGain(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetRedVideoGain(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentRedVideoGain)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetRedVideoGain(aInstanceID, aDesiredRedVideoGain);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetRedVideoGain(aInstanceID, aDesiredRedVideoGain, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetRedVideoGain(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoGain)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetGreenVideoGain(aInstanceID, *aCurrentGreenVideoGain);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentGreenVideoGain = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetGreenVideoGain(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetGreenVideoGain(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentGreenVideoGain)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetGreenVideoGain(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoGain)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetBlueVideoGain(aInstanceID, *aCurrentBlueVideoGain);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentBlueVideoGain = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetBlueVideoGain(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetBlueVideoGain(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentBlueVideoGain)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetBlueVideoGain(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentRedVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetRedVideoBlackLevel(aInstanceID, *aCurrentRedVideoBlackLevel);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentRedVideoBlackLevel = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRedVideoBlackLevel(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetRedVideoBlackLevel(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentRedVideoBlackLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetRedVideoBlackLevel(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetGreenVideoBlackLevel(aInstanceID, *aCurrentGreenVideoBlackLevel);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentGreenVideoBlackLevel = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetGreenVideoBlackLevel(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetGreenVideoBlackLevel(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentGreenVideoBlackLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetGreenVideoBlackLevel(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetBlueVideoBlackLevel(aInstanceID, *aCurrentBlueVideoBlackLevel);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentBlueVideoBlackLevel = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetBlueVideoBlackLevel(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetBlueVideoBlackLevel(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentBlueVideoBlackLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetBlueVideoBlackLevel(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentColorTemperature)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetColorTemperature(aInstanceID, *aCurrentColorTemperature);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentColorTemperature = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetColorTemperature(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetColorTemperature(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetColorTemperature(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentColorTemperature)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredColorTemperature)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetColorTemperature(aInstanceID, aDesiredColorTemperature);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredColorTemperature, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetColorTemperature(aInstanceID, aDesiredColorTemperature, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetColorTemperature(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t* aCurrentHorizontalKeystone)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetHorizontalKeystone(aInstanceID, *aCurrentHorizontalKeystone);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentHorizontalKeystone = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetHorizontalKeystone(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetHorizontalKeystone(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aCurrentHorizontalKeystone)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetHorizontalKeystone(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t* aCurrentVerticalKeystone)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetVerticalKeystone(aInstanceID, *aCurrentVerticalKeystone);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentVerticalKeystone = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetVerticalKeystone(aInstanceID, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetVerticalKeystone(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aCurrentVerticalKeystone)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetVerticalKeystone(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentMute)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    TBool CurrentMute;
    int32_t err = 0;
    try {
        proxyC->SyncGetMute(aInstanceID, buf_aChannel, CurrentMute);
        *aCurrentMute = CurrentMute? 1 : 0;
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentMute = false;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetMute(aInstanceID, buf_aChannel, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetMute(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentMute)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    TBool CurrentMute;
    try {
        proxyC->EndGetMute(*async, CurrentMute);
        *aCurrentMute = CurrentMute? 1 : 0;
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    int32_t err = 0;
    try {
        proxyC->SyncSetMute(aInstanceID, buf_aChannel, (aDesiredMute==0? false : true));
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetMute(aInstanceID, buf_aChannel, (aDesiredMute==0? false : true), functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetMute(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentVolume)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    int32_t err = 0;
    try {
        proxyC->SyncGetVolume(aInstanceID, buf_aChannel, *aCurrentVolume);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentVolume = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetVolume(aInstanceID, buf_aChannel, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetVolume(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentVolume)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    int32_t err = 0;
    try {
        proxyC->SyncSetVolume(aInstanceID, buf_aChannel, aDesiredVolume);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetVolume(aInstanceID, buf_aChannel, aDesiredVolume, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetVolume(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t* aCurrentVolume)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    int32_t err = 0;
    try {
        proxyC->SyncGetVolumeDB(aInstanceID, buf_aChannel, *aCurrentVolume);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentVolume = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetVolumeDB(aInstanceID, buf_aChannel, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetVolumeDB(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aCurrentVolume)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    int32_t err = 0;
    try {
        proxyC->SyncSetVolumeDB(aInstanceID, buf_aChannel, aDesiredVolume);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetVolumeDB(aInstanceID, buf_aChannel, aDesiredVolume, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetVolumeDB(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetVolumeDBRange(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t* aMinValue, int32_t* aMaxValue)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    int32_t err = 0;
    try {
        proxyC->SyncGetVolumeDBRange(aInstanceID, buf_aChannel, *aMinValue, *aMaxValue);
    }
    catch (ProxyError& ) {
        err = -1;
        *aMinValue = 0;
        *aMaxValue = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetVolumeDBRange(THandle aHandle, uint32_t aInstanceID, const char* aChannel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetVolumeDBRange(aInstanceID, buf_aChannel, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetVolumeDBRange(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aMinValue, int32_t* aMaxValue)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncGetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentLoudness)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    TBool CurrentLoudness;
    int32_t err = 0;
    try {
        proxyC->SyncGetLoudness(aInstanceID, buf_aChannel, CurrentLoudness);
        *aCurrentLoudness = CurrentLoudness? 1 : 0;
    }
    catch (ProxyError& ) {
        err = -1;
        *aCurrentLoudness = false;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginGetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetLoudness(aInstanceID, buf_aChannel, functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndGetLoudness(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCurrentLoudness)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    TBool CurrentLoudness;
    try {
        proxyC->EndGetLoudness(*async, CurrentLoudness);
        *aCurrentLoudness = CurrentLoudness? 1 : 0;
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1SyncSetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    int32_t err = 0;
    try {
        proxyC->SyncSetLoudness(aInstanceID, buf_aChannel, (aDesiredLoudness==0? false : true));
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgRenderingControl1BeginSetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetLoudness(aInstanceID, buf_aChannel, (aDesiredLoudness==0? false : true), functor);
}

int32_t STDCALL CpProxyUpnpOrgRenderingControl1EndSetLoudness(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void STDCALL CpProxyUpnpOrgRenderingControl1SetPropertyLastChangeChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyLastChangeChanged(functor);
}

void STDCALL CpProxyUpnpOrgRenderingControl1PropertyLastChange(THandle aHandle, char** aLastChange)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aLastChange;
    proxyC->PropertyLastChange(buf_aLastChange);
    *aLastChange = buf_aLastChange.Transfer();
}

