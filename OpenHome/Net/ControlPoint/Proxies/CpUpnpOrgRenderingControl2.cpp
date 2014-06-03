#include "CpUpnpOrgRenderingControl2.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncListPresetsUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncListPresetsUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, Brh& aCurrentPresetNameList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncListPresetsUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    Brh& iCurrentPresetNameList;
};

SyncListPresetsUpnpOrgRenderingControl2::SyncListPresetsUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, Brh& aCurrentPresetNameList)
    : iService(aProxy)
    , iCurrentPresetNameList(aCurrentPresetNameList)
{
}

void SyncListPresetsUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndListPresets(aAsync, iCurrentPresetNameList);
}


class SyncSelectPresetUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSelectPresetUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSelectPresetUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSelectPresetUpnpOrgRenderingControl2::SyncSelectPresetUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSelectPresetUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSelectPreset(aAsync);
}


class SyncGetBrightnessUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetBrightnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentBrightness);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBrightnessUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TUint& iCurrentBrightness;
};

SyncGetBrightnessUpnpOrgRenderingControl2::SyncGetBrightnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentBrightness)
    : iService(aProxy)
    , iCurrentBrightness(aCurrentBrightness)
{
}

void SyncGetBrightnessUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBrightness(aAsync, iCurrentBrightness);
}


class SyncSetBrightnessUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetBrightnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBrightnessUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetBrightnessUpnpOrgRenderingControl2::SyncSetBrightnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetBrightnessUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBrightness(aAsync);
}


class SyncGetContrastUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetContrastUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentContrast);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetContrastUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TUint& iCurrentContrast;
};

SyncGetContrastUpnpOrgRenderingControl2::SyncGetContrastUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentContrast)
    : iService(aProxy)
    , iCurrentContrast(aCurrentContrast)
{
}

void SyncGetContrastUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetContrast(aAsync, iCurrentContrast);
}


class SyncSetContrastUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetContrastUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetContrastUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetContrastUpnpOrgRenderingControl2::SyncSetContrastUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetContrastUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetContrast(aAsync);
}


class SyncGetSharpnessUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetSharpnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentSharpness);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSharpnessUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TUint& iCurrentSharpness;
};

SyncGetSharpnessUpnpOrgRenderingControl2::SyncGetSharpnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentSharpness)
    : iService(aProxy)
    , iCurrentSharpness(aCurrentSharpness)
{
}

void SyncGetSharpnessUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSharpness(aAsync, iCurrentSharpness);
}


class SyncSetSharpnessUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetSharpnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetSharpnessUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetSharpnessUpnpOrgRenderingControl2::SyncSetSharpnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetSharpnessUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSharpness(aAsync);
}


class SyncGetRedVideoGainUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetRedVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentRedVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRedVideoGainUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TUint& iCurrentRedVideoGain;
};

SyncGetRedVideoGainUpnpOrgRenderingControl2::SyncGetRedVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentRedVideoGain)
    : iService(aProxy)
    , iCurrentRedVideoGain(aCurrentRedVideoGain)
{
}

void SyncGetRedVideoGainUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRedVideoGain(aAsync, iCurrentRedVideoGain);
}


class SyncSetRedVideoGainUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetRedVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRedVideoGainUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetRedVideoGainUpnpOrgRenderingControl2::SyncSetRedVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetRedVideoGainUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRedVideoGain(aAsync);
}


class SyncGetGreenVideoGainUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetGreenVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentGreenVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetGreenVideoGainUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TUint& iCurrentGreenVideoGain;
};

SyncGetGreenVideoGainUpnpOrgRenderingControl2::SyncGetGreenVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentGreenVideoGain)
    : iService(aProxy)
    , iCurrentGreenVideoGain(aCurrentGreenVideoGain)
{
}

void SyncGetGreenVideoGainUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetGreenVideoGain(aAsync, iCurrentGreenVideoGain);
}


class SyncSetGreenVideoGainUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetGreenVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetGreenVideoGainUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetGreenVideoGainUpnpOrgRenderingControl2::SyncSetGreenVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetGreenVideoGainUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetGreenVideoGain(aAsync);
}


class SyncGetBlueVideoGainUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetBlueVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentBlueVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBlueVideoGainUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TUint& iCurrentBlueVideoGain;
};

SyncGetBlueVideoGainUpnpOrgRenderingControl2::SyncGetBlueVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentBlueVideoGain)
    : iService(aProxy)
    , iCurrentBlueVideoGain(aCurrentBlueVideoGain)
{
}

void SyncGetBlueVideoGainUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBlueVideoGain(aAsync, iCurrentBlueVideoGain);
}


class SyncSetBlueVideoGainUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetBlueVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBlueVideoGainUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetBlueVideoGainUpnpOrgRenderingControl2::SyncSetBlueVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetBlueVideoGainUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBlueVideoGain(aAsync);
}


class SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentRedVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TUint& iCurrentRedVideoBlackLevel;
};

SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2::SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentRedVideoBlackLevel)
    : iService(aProxy)
    , iCurrentRedVideoBlackLevel(aCurrentRedVideoBlackLevel)
{
}

void SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRedVideoBlackLevel(aAsync, iCurrentRedVideoBlackLevel);
}


class SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2::SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRedVideoBlackLevel(aAsync);
}


class SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentGreenVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TUint& iCurrentGreenVideoBlackLevel;
};

SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2::SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentGreenVideoBlackLevel)
    : iService(aProxy)
    , iCurrentGreenVideoBlackLevel(aCurrentGreenVideoBlackLevel)
{
}

void SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetGreenVideoBlackLevel(aAsync, iCurrentGreenVideoBlackLevel);
}


class SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2::SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetGreenVideoBlackLevel(aAsync);
}


class SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentBlueVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TUint& iCurrentBlueVideoBlackLevel;
};

SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2::SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentBlueVideoBlackLevel)
    : iService(aProxy)
    , iCurrentBlueVideoBlackLevel(aCurrentBlueVideoBlackLevel)
{
}

void SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBlueVideoBlackLevel(aAsync, iCurrentBlueVideoBlackLevel);
}


class SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2::SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBlueVideoBlackLevel(aAsync);
}


class SyncGetColorTemperatureUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetColorTemperatureUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentColorTemperature);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetColorTemperatureUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TUint& iCurrentColorTemperature;
};

SyncGetColorTemperatureUpnpOrgRenderingControl2::SyncGetColorTemperatureUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentColorTemperature)
    : iService(aProxy)
    , iCurrentColorTemperature(aCurrentColorTemperature)
{
}

void SyncGetColorTemperatureUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColorTemperature(aAsync, iCurrentColorTemperature);
}


class SyncSetColorTemperatureUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetColorTemperatureUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetColorTemperatureUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetColorTemperatureUpnpOrgRenderingControl2::SyncSetColorTemperatureUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetColorTemperatureUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColorTemperature(aAsync);
}


class SyncGetHorizontalKeystoneUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetHorizontalKeystoneUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TInt& aCurrentHorizontalKeystone);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetHorizontalKeystoneUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TInt& iCurrentHorizontalKeystone;
};

SyncGetHorizontalKeystoneUpnpOrgRenderingControl2::SyncGetHorizontalKeystoneUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TInt& aCurrentHorizontalKeystone)
    : iService(aProxy)
    , iCurrentHorizontalKeystone(aCurrentHorizontalKeystone)
{
}

void SyncGetHorizontalKeystoneUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetHorizontalKeystone(aAsync, iCurrentHorizontalKeystone);
}


class SyncSetHorizontalKeystoneUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetHorizontalKeystoneUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetHorizontalKeystoneUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetHorizontalKeystoneUpnpOrgRenderingControl2::SyncSetHorizontalKeystoneUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetHorizontalKeystoneUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetHorizontalKeystone(aAsync);
}


class SyncGetVerticalKeystoneUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetVerticalKeystoneUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TInt& aCurrentVerticalKeystone);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVerticalKeystoneUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TInt& iCurrentVerticalKeystone;
};

SyncGetVerticalKeystoneUpnpOrgRenderingControl2::SyncGetVerticalKeystoneUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TInt& aCurrentVerticalKeystone)
    : iService(aProxy)
    , iCurrentVerticalKeystone(aCurrentVerticalKeystone)
{
}

void SyncGetVerticalKeystoneUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVerticalKeystone(aAsync, iCurrentVerticalKeystone);
}


class SyncSetVerticalKeystoneUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetVerticalKeystoneUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVerticalKeystoneUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetVerticalKeystoneUpnpOrgRenderingControl2::SyncSetVerticalKeystoneUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetVerticalKeystoneUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVerticalKeystone(aAsync);
}


class SyncGetMuteUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetMuteUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TBool& aCurrentMute);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetMuteUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TBool& iCurrentMute;
};

SyncGetMuteUpnpOrgRenderingControl2::SyncGetMuteUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TBool& aCurrentMute)
    : iService(aProxy)
    , iCurrentMute(aCurrentMute)
{
}

void SyncGetMuteUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMute(aAsync, iCurrentMute);
}


class SyncSetMuteUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetMuteUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetMuteUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetMuteUpnpOrgRenderingControl2::SyncSetMuteUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetMuteUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMute(aAsync);
}


class SyncGetVolumeUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetVolumeUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVolumeUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TUint& iCurrentVolume;
};

SyncGetVolumeUpnpOrgRenderingControl2::SyncGetVolumeUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TUint& aCurrentVolume)
    : iService(aProxy)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetVolumeUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolume(aAsync, iCurrentVolume);
}


class SyncSetVolumeUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetVolumeUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVolumeUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetVolumeUpnpOrgRenderingControl2::SyncSetVolumeUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolume(aAsync);
}


class SyncGetVolumeDBUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetVolumeDBUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TInt& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVolumeDBUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TInt& iCurrentVolume;
};

SyncGetVolumeDBUpnpOrgRenderingControl2::SyncGetVolumeDBUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TInt& aCurrentVolume)
    : iService(aProxy)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetVolumeDBUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolumeDB(aAsync, iCurrentVolume);
}


class SyncSetVolumeDBUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetVolumeDBUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVolumeDBUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetVolumeDBUpnpOrgRenderingControl2::SyncSetVolumeDBUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeDBUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolumeDB(aAsync);
}


class SyncGetVolumeDBRangeUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetVolumeDBRangeUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TInt& aMinValue, TInt& aMaxValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVolumeDBRangeUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TInt& iMinValue;
    TInt& iMaxValue;
};

SyncGetVolumeDBRangeUpnpOrgRenderingControl2::SyncGetVolumeDBRangeUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TInt& aMinValue, TInt& aMaxValue)
    : iService(aProxy)
    , iMinValue(aMinValue)
    , iMaxValue(aMaxValue)
{
}

void SyncGetVolumeDBRangeUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolumeDBRange(aAsync, iMinValue, iMaxValue);
}


class SyncGetLoudnessUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetLoudnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TBool& aCurrentLoudness);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetLoudnessUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    TBool& iCurrentLoudness;
};

SyncGetLoudnessUpnpOrgRenderingControl2::SyncGetLoudnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, TBool& aCurrentLoudness)
    : iService(aProxy)
    , iCurrentLoudness(aCurrentLoudness)
{
}

void SyncGetLoudnessUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLoudness(aAsync, iCurrentLoudness);
}


class SyncSetLoudnessUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetLoudnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetLoudnessUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
};

SyncSetLoudnessUpnpOrgRenderingControl2::SyncSetLoudnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy)
    : iService(aProxy)
{
}

void SyncSetLoudnessUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLoudness(aAsync);
}


class SyncGetStateVariablesUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncGetStateVariablesUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, Brh& aStateVariableValuePairs);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStateVariablesUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    Brh& iStateVariableValuePairs;
};

SyncGetStateVariablesUpnpOrgRenderingControl2::SyncGetStateVariablesUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, Brh& aStateVariableValuePairs)
    : iService(aProxy)
    , iStateVariableValuePairs(aStateVariableValuePairs)
{
}

void SyncGetStateVariablesUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStateVariables(aAsync, iStateVariableValuePairs);
}


class SyncSetStateVariablesUpnpOrgRenderingControl2 : public SyncProxyAction
{
public:
    SyncSetStateVariablesUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, Brh& aStateVariableList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetStateVariablesUpnpOrgRenderingControl2() {}
private:
    CpProxyUpnpOrgRenderingControl2& iService;
    Brh& iStateVariableList;
};

SyncSetStateVariablesUpnpOrgRenderingControl2::SyncSetStateVariablesUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2& aProxy, Brh& aStateVariableList)
    : iService(aProxy)
    , iStateVariableList(aStateVariableList)
{
}

void SyncSetStateVariablesUpnpOrgRenderingControl2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStateVariables(aAsync, iStateVariableList);
}


CpProxyUpnpOrgRenderingControl2::CpProxyUpnpOrgRenderingControl2(CpDevice& aDevice)
    : CpProxy("schemas-upnp-org", "RenderingControl", 2, aDevice.Device())
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgRenderingControl2::LastChangePropertyChanged);
    iLastChange = new PropertyString(aDevice.Device().GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
}

CpProxyUpnpOrgRenderingControl2::~CpProxyUpnpOrgRenderingControl2()
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

void CpProxyUpnpOrgRenderingControl2::SyncListPresets(TUint aInstanceID, Brh& aCurrentPresetNameList)
{
    SyncListPresetsUpnpOrgRenderingControl2 sync(*this, aCurrentPresetNameList);
    BeginListPresets(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginListPresets(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionListPresets, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionListPresets->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionListPresets->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndListPresets(IAsync& aAsync, Brh& aCurrentPresetNameList)
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

void CpProxyUpnpOrgRenderingControl2::SyncSelectPreset(TUint aInstanceID, const Brx& aPresetName)
{
    SyncSelectPresetUpnpOrgRenderingControl2 sync(*this);
    BeginSelectPreset(aInstanceID, aPresetName, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSelectPreset(TUint aInstanceID, const Brx& aPresetName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSelectPreset, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSelectPreset->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aPresetName));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSelectPreset(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetBrightness(TUint aInstanceID, TUint& aCurrentBrightness)
{
    SyncGetBrightnessUpnpOrgRenderingControl2 sync(*this, aCurrentBrightness);
    BeginGetBrightness(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetBrightness(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetBrightness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetBrightness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBrightness->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetBrightness(IAsync& aAsync, TUint& aCurrentBrightness)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetBrightness(TUint aInstanceID, TUint aDesiredBrightness)
{
    SyncSetBrightnessUpnpOrgRenderingControl2 sync(*this);
    BeginSetBrightness(aInstanceID, aDesiredBrightness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetBrightness(TUint aInstanceID, TUint aDesiredBrightness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBrightness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBrightness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBrightness));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetBrightness(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetContrast(TUint aInstanceID, TUint& aCurrentContrast)
{
    SyncGetContrastUpnpOrgRenderingControl2 sync(*this, aCurrentContrast);
    BeginGetContrast(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetContrast(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetContrast, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetContrast->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetContrast->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetContrast(IAsync& aAsync, TUint& aCurrentContrast)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetContrast(TUint aInstanceID, TUint aDesiredContrast)
{
    SyncSetContrastUpnpOrgRenderingControl2 sync(*this);
    BeginSetContrast(aInstanceID, aDesiredContrast, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetContrast(TUint aInstanceID, TUint aDesiredContrast, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetContrast, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetContrast->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredContrast));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetContrast(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetSharpness(TUint aInstanceID, TUint& aCurrentSharpness)
{
    SyncGetSharpnessUpnpOrgRenderingControl2 sync(*this, aCurrentSharpness);
    BeginGetSharpness(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetSharpness(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSharpness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetSharpness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSharpness->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetSharpness(IAsync& aAsync, TUint& aCurrentSharpness)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetSharpness(TUint aInstanceID, TUint aDesiredSharpness)
{
    SyncSetSharpnessUpnpOrgRenderingControl2 sync(*this);
    BeginSetSharpness(aInstanceID, aDesiredSharpness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetSharpness(TUint aInstanceID, TUint aDesiredSharpness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSharpness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSharpness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredSharpness));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetSharpness(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetRedVideoGain(TUint aInstanceID, TUint& aCurrentRedVideoGain)
{
    SyncGetRedVideoGainUpnpOrgRenderingControl2 sync(*this, aCurrentRedVideoGain);
    BeginGetRedVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetRedVideoGain(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRedVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRedVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRedVideoGain->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetRedVideoGain(IAsync& aAsync, TUint& aCurrentRedVideoGain)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetRedVideoGain(TUint aInstanceID, TUint aDesiredRedVideoGain)
{
    SyncSetRedVideoGainUpnpOrgRenderingControl2 sync(*this);
    BeginSetRedVideoGain(aInstanceID, aDesiredRedVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetRedVideoGain(TUint aInstanceID, TUint aDesiredRedVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRedVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRedVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredRedVideoGain));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetRedVideoGain(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetGreenVideoGain(TUint aInstanceID, TUint& aCurrentGreenVideoGain)
{
    SyncGetGreenVideoGainUpnpOrgRenderingControl2 sync(*this, aCurrentGreenVideoGain);
    BeginGetGreenVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetGreenVideoGain(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetGreenVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetGreenVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetGreenVideoGain->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetGreenVideoGain(IAsync& aAsync, TUint& aCurrentGreenVideoGain)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetGreenVideoGain(TUint aInstanceID, TUint aDesiredGreenVideoGain)
{
    SyncSetGreenVideoGainUpnpOrgRenderingControl2 sync(*this);
    BeginSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetGreenVideoGain(TUint aInstanceID, TUint aDesiredGreenVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetGreenVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetGreenVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredGreenVideoGain));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetGreenVideoGain(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetBlueVideoGain(TUint aInstanceID, TUint& aCurrentBlueVideoGain)
{
    SyncGetBlueVideoGainUpnpOrgRenderingControl2 sync(*this, aCurrentBlueVideoGain);
    BeginGetBlueVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetBlueVideoGain(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetBlueVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetBlueVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBlueVideoGain->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetBlueVideoGain(IAsync& aAsync, TUint& aCurrentBlueVideoGain)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetBlueVideoGain(TUint aInstanceID, TUint aDesiredBlueVideoGain)
{
    SyncSetBlueVideoGainUpnpOrgRenderingControl2 sync(*this);
    BeginSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetBlueVideoGain(TUint aInstanceID, TUint aDesiredBlueVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBlueVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBlueVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBlueVideoGain));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetBlueVideoGain(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetRedVideoBlackLevel(TUint aInstanceID, TUint& aCurrentRedVideoBlackLevel)
{
    SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2 sync(*this, aCurrentRedVideoBlackLevel);
    BeginGetRedVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetRedVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRedVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRedVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRedVideoBlackLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetRedVideoBlackLevel(IAsync& aAsync, TUint& aCurrentRedVideoBlackLevel)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetRedVideoBlackLevel(TUint aInstanceID, TUint aDesiredRedVideoBlackLevel)
{
    SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2 sync(*this);
    BeginSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetRedVideoBlackLevel(TUint aInstanceID, TUint aDesiredRedVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRedVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRedVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredRedVideoBlackLevel));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetRedVideoBlackLevel(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetGreenVideoBlackLevel(TUint aInstanceID, TUint& aCurrentGreenVideoBlackLevel)
{
    SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2 sync(*this, aCurrentGreenVideoBlackLevel);
    BeginGetGreenVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetGreenVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetGreenVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetGreenVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetGreenVideoBlackLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetGreenVideoBlackLevel(IAsync& aAsync, TUint& aCurrentGreenVideoBlackLevel)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetGreenVideoBlackLevel(TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel)
{
    SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2 sync(*this);
    BeginSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetGreenVideoBlackLevel(TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetGreenVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetGreenVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredGreenVideoBlackLevel));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetGreenVideoBlackLevel(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetBlueVideoBlackLevel(TUint aInstanceID, TUint& aCurrentBlueVideoBlackLevel)
{
    SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2 sync(*this, aCurrentBlueVideoBlackLevel);
    BeginGetBlueVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetBlueVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetBlueVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetBlueVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBlueVideoBlackLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetBlueVideoBlackLevel(IAsync& aAsync, TUint& aCurrentBlueVideoBlackLevel)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetBlueVideoBlackLevel(TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel)
{
    SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2 sync(*this);
    BeginSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetBlueVideoBlackLevel(TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBlueVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBlueVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBlueVideoBlackLevel));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetBlueVideoBlackLevel(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetColorTemperature(TUint aInstanceID, TUint& aCurrentColorTemperature)
{
    SyncGetColorTemperatureUpnpOrgRenderingControl2 sync(*this, aCurrentColorTemperature);
    BeginGetColorTemperature(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetColorTemperature(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetColorTemperature, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetColorTemperature->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetColorTemperature->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetColorTemperature(IAsync& aAsync, TUint& aCurrentColorTemperature)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetColorTemperature(TUint aInstanceID, TUint aDesiredColorTemperature)
{
    SyncSetColorTemperatureUpnpOrgRenderingControl2 sync(*this);
    BeginSetColorTemperature(aInstanceID, aDesiredColorTemperature, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetColorTemperature(TUint aInstanceID, TUint aDesiredColorTemperature, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetColorTemperature, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColorTemperature->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredColorTemperature));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetColorTemperature(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetHorizontalKeystone(TUint aInstanceID, TInt& aCurrentHorizontalKeystone)
{
    SyncGetHorizontalKeystoneUpnpOrgRenderingControl2 sync(*this, aCurrentHorizontalKeystone);
    BeginGetHorizontalKeystone(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetHorizontalKeystone(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetHorizontalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetHorizontalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetHorizontalKeystone->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetHorizontalKeystone(IAsync& aAsync, TInt& aCurrentHorizontalKeystone)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetHorizontalKeystone(TUint aInstanceID, TInt aDesiredHorizontalKeystone)
{
    SyncSetHorizontalKeystoneUpnpOrgRenderingControl2 sync(*this);
    BeginSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetHorizontalKeystone(TUint aInstanceID, TInt aDesiredHorizontalKeystone, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetHorizontalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetHorizontalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredHorizontalKeystone));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetHorizontalKeystone(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetVerticalKeystone(TUint aInstanceID, TInt& aCurrentVerticalKeystone)
{
    SyncGetVerticalKeystoneUpnpOrgRenderingControl2 sync(*this, aCurrentVerticalKeystone);
    BeginGetVerticalKeystone(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetVerticalKeystone(TUint aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetVerticalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVerticalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVerticalKeystone->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetVerticalKeystone(IAsync& aAsync, TInt& aCurrentVerticalKeystone)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetVerticalKeystone(TUint aInstanceID, TInt aDesiredVerticalKeystone)
{
    SyncSetVerticalKeystoneUpnpOrgRenderingControl2 sync(*this);
    BeginSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetVerticalKeystone(TUint aInstanceID, TInt aDesiredVerticalKeystone, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVerticalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVerticalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredVerticalKeystone));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetVerticalKeystone(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetMute(TUint aInstanceID, const Brx& aChannel, TBool& aCurrentMute)
{
    SyncGetMuteUpnpOrgRenderingControl2 sync(*this, aCurrentMute);
    BeginGetMute(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetMute(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetMute->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetMute(IAsync& aAsync, TBool& aCurrentMute)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetMute(TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute)
{
    SyncSetMuteUpnpOrgRenderingControl2 sync(*this);
    BeginSetMute(aInstanceID, aChannel, aDesiredMute, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetMute(TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredMute));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetMute(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetVolume(TUint aInstanceID, const Brx& aChannel, TUint& aCurrentVolume)
{
    SyncGetVolumeUpnpOrgRenderingControl2 sync(*this, aCurrentVolume);
    BeginGetVolume(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetVolume(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetVolume(IAsync& aAsync, TUint& aCurrentVolume)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetVolume(TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume)
{
    SyncSetVolumeUpnpOrgRenderingControl2 sync(*this);
    BeginSetVolume(aInstanceID, aChannel, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetVolume(TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredVolume));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetVolume(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt& aCurrentVolume)
{
    SyncGetVolumeDBUpnpOrgRenderingControl2 sync(*this, aCurrentVolume);
    BeginGetVolumeDB(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetVolumeDB(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetVolumeDB, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVolumeDB->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVolumeDB->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetVolumeDB(IAsync& aAsync, TInt& aCurrentVolume)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume)
{
    SyncSetVolumeDBUpnpOrgRenderingControl2 sync(*this);
    BeginSetVolumeDB(aInstanceID, aChannel, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolumeDB, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolumeDB->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredVolume));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetVolumeDB(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetVolumeDBRange(TUint aInstanceID, const Brx& aChannel, TInt& aMinValue, TInt& aMaxValue)
{
    SyncGetVolumeDBRangeUpnpOrgRenderingControl2 sync(*this, aMinValue, aMaxValue);
    BeginGetVolumeDBRange(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetVolumeDBRange(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetVolumeDBRange, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVolumeDBRange->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVolumeDBRange->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetVolumeDBRange(IAsync& aAsync, TInt& aMinValue, TInt& aMaxValue)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetLoudness(TUint aInstanceID, const Brx& aChannel, TBool& aCurrentLoudness)
{
    SyncGetLoudnessUpnpOrgRenderingControl2 sync(*this, aCurrentLoudness);
    BeginGetLoudness(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetLoudness(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetLoudness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetLoudness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLoudness->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetLoudness(IAsync& aAsync, TBool& aCurrentLoudness)
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

void CpProxyUpnpOrgRenderingControl2::SyncSetLoudness(TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness)
{
    SyncSetLoudnessUpnpOrgRenderingControl2 sync(*this);
    BeginSetLoudness(aInstanceID, aChannel, aDesiredLoudness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetLoudness(TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetLoudness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLoudness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredLoudness));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetLoudness(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2::SyncGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, Brh& aStateVariableValuePairs)
{
    SyncGetStateVariablesUpnpOrgRenderingControl2 sync(*this, aStateVariableValuePairs);
    BeginGetStateVariables(aInstanceID, aStateVariableList, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetStateVariables, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetStateVariables->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aStateVariableList));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStateVariables->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndGetStateVariables(IAsync& aAsync, Brh& aStateVariableValuePairs)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStateVariables"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aStateVariableValuePairs);
}

void CpProxyUpnpOrgRenderingControl2::SyncSetStateVariables(TUint aInstanceID, const Brx& aRenderingControlUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, Brh& aStateVariableList)
{
    SyncSetStateVariablesUpnpOrgRenderingControl2 sync(*this, aStateVariableList);
    BeginSetStateVariables(aInstanceID, aRenderingControlUDN, aServiceType, aServiceId, aStateVariableValuePairs, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2::BeginSetStateVariables(TUint aInstanceID, const Brx& aRenderingControlUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStateVariables, aFunctor);
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
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2::EndSetStateVariables(IAsync& aAsync, Brh& aStateVariableList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStateVariables"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aStateVariableList);
}

void CpProxyUpnpOrgRenderingControl2::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgRenderingControl2::PropertyLastChange(Brhz& aLastChange) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aLastChange.Set(iLastChange->Value());
}

void CpProxyUpnpOrgRenderingControl2::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}

