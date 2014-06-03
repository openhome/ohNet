#include "CpUpnpOrgRenderingControl1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncListPresetsUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncListPresetsUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, Brh& aCurrentPresetNameList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncListPresetsUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    Brh& iCurrentPresetNameList;
};

SyncListPresetsUpnpOrgRenderingControl1::SyncListPresetsUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, Brh& aCurrentPresetNameList)
    : iService(aProxy)
    , iCurrentPresetNameList(aCurrentPresetNameList)
{
}

void SyncListPresetsUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndListPresets(aAsync, iCurrentPresetNameList);
}


class SyncSelectPresetUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSelectPresetUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSelectPresetUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSelectPresetUpnpOrgRenderingControl1::SyncSelectPresetUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSelectPresetUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSelectPreset(aAsync);
}


class SyncGetBrightnessUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetBrightnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentBrightness);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBrightnessUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TUint& iCurrentBrightness;
};

SyncGetBrightnessUpnpOrgRenderingControl1::SyncGetBrightnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentBrightness)
    : iService(aProxy)
    , iCurrentBrightness(aCurrentBrightness)
{
}

void SyncGetBrightnessUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBrightness(aAsync, iCurrentBrightness);
}


class SyncSetBrightnessUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetBrightnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBrightnessUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetBrightnessUpnpOrgRenderingControl1::SyncSetBrightnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetBrightnessUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBrightness(aAsync);
}


class SyncGetContrastUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetContrastUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentContrast);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetContrastUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TUint& iCurrentContrast;
};

SyncGetContrastUpnpOrgRenderingControl1::SyncGetContrastUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentContrast)
    : iService(aProxy)
    , iCurrentContrast(aCurrentContrast)
{
}

void SyncGetContrastUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetContrast(aAsync, iCurrentContrast);
}


class SyncSetContrastUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetContrastUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetContrastUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetContrastUpnpOrgRenderingControl1::SyncSetContrastUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetContrastUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetContrast(aAsync);
}


class SyncGetSharpnessUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetSharpnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentSharpness);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSharpnessUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TUint& iCurrentSharpness;
};

SyncGetSharpnessUpnpOrgRenderingControl1::SyncGetSharpnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentSharpness)
    : iService(aProxy)
    , iCurrentSharpness(aCurrentSharpness)
{
}

void SyncGetSharpnessUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSharpness(aAsync, iCurrentSharpness);
}


class SyncSetSharpnessUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetSharpnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetSharpnessUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetSharpnessUpnpOrgRenderingControl1::SyncSetSharpnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetSharpnessUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSharpness(aAsync);
}


class SyncGetRedVideoGainUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetRedVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentRedVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRedVideoGainUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TUint& iCurrentRedVideoGain;
};

SyncGetRedVideoGainUpnpOrgRenderingControl1::SyncGetRedVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentRedVideoGain)
    : iService(aProxy)
    , iCurrentRedVideoGain(aCurrentRedVideoGain)
{
}

void SyncGetRedVideoGainUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRedVideoGain(aAsync, iCurrentRedVideoGain);
}


class SyncSetRedVideoGainUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetRedVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRedVideoGainUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetRedVideoGainUpnpOrgRenderingControl1::SyncSetRedVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetRedVideoGainUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRedVideoGain(aAsync);
}


class SyncGetGreenVideoGainUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetGreenVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentGreenVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetGreenVideoGainUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TUint& iCurrentGreenVideoGain;
};

SyncGetGreenVideoGainUpnpOrgRenderingControl1::SyncGetGreenVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentGreenVideoGain)
    : iService(aProxy)
    , iCurrentGreenVideoGain(aCurrentGreenVideoGain)
{
}

void SyncGetGreenVideoGainUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetGreenVideoGain(aAsync, iCurrentGreenVideoGain);
}


class SyncSetGreenVideoGainUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetGreenVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetGreenVideoGainUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetGreenVideoGainUpnpOrgRenderingControl1::SyncSetGreenVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetGreenVideoGainUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetGreenVideoGain(aAsync);
}


class SyncGetBlueVideoGainUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetBlueVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentBlueVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBlueVideoGainUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TUint& iCurrentBlueVideoGain;
};

SyncGetBlueVideoGainUpnpOrgRenderingControl1::SyncGetBlueVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentBlueVideoGain)
    : iService(aProxy)
    , iCurrentBlueVideoGain(aCurrentBlueVideoGain)
{
}

void SyncGetBlueVideoGainUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBlueVideoGain(aAsync, iCurrentBlueVideoGain);
}


class SyncSetBlueVideoGainUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetBlueVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBlueVideoGainUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetBlueVideoGainUpnpOrgRenderingControl1::SyncSetBlueVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetBlueVideoGainUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBlueVideoGain(aAsync);
}


class SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentRedVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TUint& iCurrentRedVideoBlackLevel;
};

SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1::SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentRedVideoBlackLevel)
    : iService(aProxy)
    , iCurrentRedVideoBlackLevel(aCurrentRedVideoBlackLevel)
{
}

void SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRedVideoBlackLevel(aAsync, iCurrentRedVideoBlackLevel);
}


class SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1::SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRedVideoBlackLevel(aAsync);
}


class SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentGreenVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TUint& iCurrentGreenVideoBlackLevel;
};

SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1::SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentGreenVideoBlackLevel)
    : iService(aProxy)
    , iCurrentGreenVideoBlackLevel(aCurrentGreenVideoBlackLevel)
{
}

void SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetGreenVideoBlackLevel(aAsync, iCurrentGreenVideoBlackLevel);
}


class SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1::SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetGreenVideoBlackLevel(aAsync);
}


class SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentBlueVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TUint& iCurrentBlueVideoBlackLevel;
};

SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1::SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentBlueVideoBlackLevel)
    : iService(aProxy)
    , iCurrentBlueVideoBlackLevel(aCurrentBlueVideoBlackLevel)
{
}

void SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBlueVideoBlackLevel(aAsync, iCurrentBlueVideoBlackLevel);
}


class SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1::SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBlueVideoBlackLevel(aAsync);
}


class SyncGetColorTemperatureUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetColorTemperatureUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentColorTemperature);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetColorTemperatureUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TUint& iCurrentColorTemperature;
};

SyncGetColorTemperatureUpnpOrgRenderingControl1::SyncGetColorTemperatureUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentColorTemperature)
    : iService(aProxy)
    , iCurrentColorTemperature(aCurrentColorTemperature)
{
}

void SyncGetColorTemperatureUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColorTemperature(aAsync, iCurrentColorTemperature);
}


class SyncSetColorTemperatureUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetColorTemperatureUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetColorTemperatureUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetColorTemperatureUpnpOrgRenderingControl1::SyncSetColorTemperatureUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetColorTemperatureUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColorTemperature(aAsync);
}


class SyncGetHorizontalKeystoneUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetHorizontalKeystoneUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TInt& aCurrentHorizontalKeystone);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetHorizontalKeystoneUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TInt& iCurrentHorizontalKeystone;
};

SyncGetHorizontalKeystoneUpnpOrgRenderingControl1::SyncGetHorizontalKeystoneUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TInt& aCurrentHorizontalKeystone)
    : iService(aProxy)
    , iCurrentHorizontalKeystone(aCurrentHorizontalKeystone)
{
}

void SyncGetHorizontalKeystoneUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetHorizontalKeystone(aAsync, iCurrentHorizontalKeystone);
}


class SyncSetHorizontalKeystoneUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetHorizontalKeystoneUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetHorizontalKeystoneUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetHorizontalKeystoneUpnpOrgRenderingControl1::SyncSetHorizontalKeystoneUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetHorizontalKeystoneUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetHorizontalKeystone(aAsync);
}


class SyncGetVerticalKeystoneUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetVerticalKeystoneUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TInt& aCurrentVerticalKeystone);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVerticalKeystoneUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TInt& iCurrentVerticalKeystone;
};

SyncGetVerticalKeystoneUpnpOrgRenderingControl1::SyncGetVerticalKeystoneUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TInt& aCurrentVerticalKeystone)
    : iService(aProxy)
    , iCurrentVerticalKeystone(aCurrentVerticalKeystone)
{
}

void SyncGetVerticalKeystoneUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVerticalKeystone(aAsync, iCurrentVerticalKeystone);
}


class SyncSetVerticalKeystoneUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetVerticalKeystoneUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVerticalKeystoneUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetVerticalKeystoneUpnpOrgRenderingControl1::SyncSetVerticalKeystoneUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetVerticalKeystoneUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVerticalKeystone(aAsync);
}


class SyncGetMuteUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetMuteUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TBool& aCurrentMute);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetMuteUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TBool& iCurrentMute;
};

SyncGetMuteUpnpOrgRenderingControl1::SyncGetMuteUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TBool& aCurrentMute)
    : iService(aProxy)
    , iCurrentMute(aCurrentMute)
{
}

void SyncGetMuteUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMute(aAsync, iCurrentMute);
}


class SyncSetMuteUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetMuteUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetMuteUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetMuteUpnpOrgRenderingControl1::SyncSetMuteUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetMuteUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMute(aAsync);
}


class SyncGetVolumeUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetVolumeUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVolumeUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TUint& iCurrentVolume;
};

SyncGetVolumeUpnpOrgRenderingControl1::SyncGetVolumeUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TUint& aCurrentVolume)
    : iService(aProxy)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetVolumeUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolume(aAsync, iCurrentVolume);
}


class SyncSetVolumeUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetVolumeUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVolumeUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetVolumeUpnpOrgRenderingControl1::SyncSetVolumeUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolume(aAsync);
}


class SyncGetVolumeDBUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetVolumeDBUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TInt& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVolumeDBUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TInt& iCurrentVolume;
};

SyncGetVolumeDBUpnpOrgRenderingControl1::SyncGetVolumeDBUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TInt& aCurrentVolume)
    : iService(aProxy)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetVolumeDBUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolumeDB(aAsync, iCurrentVolume);
}


class SyncSetVolumeDBUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetVolumeDBUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVolumeDBUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetVolumeDBUpnpOrgRenderingControl1::SyncSetVolumeDBUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeDBUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolumeDB(aAsync);
}


class SyncGetVolumeDBRangeUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetVolumeDBRangeUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TInt& aMinValue, TInt& aMaxValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVolumeDBRangeUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TInt& iMinValue;
    TInt& iMaxValue;
};

SyncGetVolumeDBRangeUpnpOrgRenderingControl1::SyncGetVolumeDBRangeUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TInt& aMinValue, TInt& aMaxValue)
    : iService(aProxy)
    , iMinValue(aMinValue)
    , iMaxValue(aMaxValue)
{
}

void SyncGetVolumeDBRangeUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolumeDBRange(aAsync, iMinValue, iMaxValue);
}


class SyncGetLoudnessUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncGetLoudnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TBool& aCurrentLoudness);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetLoudnessUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
    TBool& iCurrentLoudness;
};

SyncGetLoudnessUpnpOrgRenderingControl1::SyncGetLoudnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy, TBool& aCurrentLoudness)
    : iService(aProxy)
    , iCurrentLoudness(aCurrentLoudness)
{
}

void SyncGetLoudnessUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLoudness(aAsync, iCurrentLoudness);
}


class SyncSetLoudnessUpnpOrgRenderingControl1 : public SyncProxyAction
{
public:
    SyncSetLoudnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetLoudnessUpnpOrgRenderingControl1() {}
private:
    CpProxyUpnpOrgRenderingControl1& iService;
};

SyncSetLoudnessUpnpOrgRenderingControl1::SyncSetLoudnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1& aProxy)
    : iService(aProxy)
{
}

void SyncSetLoudnessUpnpOrgRenderingControl1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLoudness(aAsync);
}


CpProxyUpnpOrgRenderingControl1::CpProxyUpnpOrgRenderingControl1(CpDevice& aDevice)
    : CpProxy("schemas-upnp-org", "RenderingControl", 1, aDevice.Device())
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgRenderingControl1::LastChangePropertyChanged);
    iLastChange = new PropertyString(aDevice.Device().GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
}

CpProxyUpnpOrgRenderingControl1::~CpProxyUpnpOrgRenderingControl1()
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

void CpProxyUpnpOrgRenderingControl1::SyncListPresets(TUint aInstanceID, Brh& aCurrentPresetNameList)
{
    SyncListPresetsUpnpOrgRenderingControl1 sync(*this, aCurrentPresetNameList);
    BeginListPresets(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginListPresets(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndListPresets(IAsync& aAsync, Brh& aCurrentPresetNameList)
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

void CpProxyUpnpOrgRenderingControl1::SyncSelectPreset(TUint aInstanceID, const Brx& aPresetName)
{
    SyncSelectPresetUpnpOrgRenderingControl1 sync(*this);
    BeginSelectPreset(aInstanceID, aPresetName, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSelectPreset(TUint aInstanceID, const Brx& aPresetName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSelectPreset, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSelectPreset->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aPresetName));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSelectPreset(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetBrightness(TUint aInstanceID, TUint& aCurrentBrightness)
{
    SyncGetBrightnessUpnpOrgRenderingControl1 sync(*this, aCurrentBrightness);
    BeginGetBrightness(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetBrightness(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetBrightness(IAsync& aAsync, TUint& aCurrentBrightness)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetBrightness(TUint aInstanceID, TUint aDesiredBrightness)
{
    SyncSetBrightnessUpnpOrgRenderingControl1 sync(*this);
    BeginSetBrightness(aInstanceID, aDesiredBrightness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetBrightness(TUint aInstanceID, TUint aDesiredBrightness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBrightness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBrightness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBrightness));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetBrightness(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetContrast(TUint aInstanceID, TUint& aCurrentContrast)
{
    SyncGetContrastUpnpOrgRenderingControl1 sync(*this, aCurrentContrast);
    BeginGetContrast(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetContrast(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetContrast(IAsync& aAsync, TUint& aCurrentContrast)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetContrast(TUint aInstanceID, TUint aDesiredContrast)
{
    SyncSetContrastUpnpOrgRenderingControl1 sync(*this);
    BeginSetContrast(aInstanceID, aDesiredContrast, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetContrast(TUint aInstanceID, TUint aDesiredContrast, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetContrast, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetContrast->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredContrast));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetContrast(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetSharpness(TUint aInstanceID, TUint& aCurrentSharpness)
{
    SyncGetSharpnessUpnpOrgRenderingControl1 sync(*this, aCurrentSharpness);
    BeginGetSharpness(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetSharpness(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetSharpness(IAsync& aAsync, TUint& aCurrentSharpness)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetSharpness(TUint aInstanceID, TUint aDesiredSharpness)
{
    SyncSetSharpnessUpnpOrgRenderingControl1 sync(*this);
    BeginSetSharpness(aInstanceID, aDesiredSharpness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetSharpness(TUint aInstanceID, TUint aDesiredSharpness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSharpness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSharpness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredSharpness));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetSharpness(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetRedVideoGain(TUint aInstanceID, TUint& aCurrentRedVideoGain)
{
    SyncGetRedVideoGainUpnpOrgRenderingControl1 sync(*this, aCurrentRedVideoGain);
    BeginGetRedVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetRedVideoGain(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetRedVideoGain(IAsync& aAsync, TUint& aCurrentRedVideoGain)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetRedVideoGain(TUint aInstanceID, TUint aDesiredRedVideoGain)
{
    SyncSetRedVideoGainUpnpOrgRenderingControl1 sync(*this);
    BeginSetRedVideoGain(aInstanceID, aDesiredRedVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetRedVideoGain(TUint aInstanceID, TUint aDesiredRedVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRedVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRedVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredRedVideoGain));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetRedVideoGain(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetGreenVideoGain(TUint aInstanceID, TUint& aCurrentGreenVideoGain)
{
    SyncGetGreenVideoGainUpnpOrgRenderingControl1 sync(*this, aCurrentGreenVideoGain);
    BeginGetGreenVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetGreenVideoGain(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetGreenVideoGain(IAsync& aAsync, TUint& aCurrentGreenVideoGain)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetGreenVideoGain(TUint aInstanceID, TUint aDesiredGreenVideoGain)
{
    SyncSetGreenVideoGainUpnpOrgRenderingControl1 sync(*this);
    BeginSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetGreenVideoGain(TUint aInstanceID, TUint aDesiredGreenVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetGreenVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetGreenVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredGreenVideoGain));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetGreenVideoGain(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetBlueVideoGain(TUint aInstanceID, TUint& aCurrentBlueVideoGain)
{
    SyncGetBlueVideoGainUpnpOrgRenderingControl1 sync(*this, aCurrentBlueVideoGain);
    BeginGetBlueVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetBlueVideoGain(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetBlueVideoGain(IAsync& aAsync, TUint& aCurrentBlueVideoGain)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetBlueVideoGain(TUint aInstanceID, TUint aDesiredBlueVideoGain)
{
    SyncSetBlueVideoGainUpnpOrgRenderingControl1 sync(*this);
    BeginSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetBlueVideoGain(TUint aInstanceID, TUint aDesiredBlueVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBlueVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBlueVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBlueVideoGain));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetBlueVideoGain(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetRedVideoBlackLevel(TUint aInstanceID, TUint& aCurrentRedVideoBlackLevel)
{
    SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1 sync(*this, aCurrentRedVideoBlackLevel);
    BeginGetRedVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetRedVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetRedVideoBlackLevel(IAsync& aAsync, TUint& aCurrentRedVideoBlackLevel)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetRedVideoBlackLevel(TUint aInstanceID, TUint aDesiredRedVideoBlackLevel)
{
    SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1 sync(*this);
    BeginSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetRedVideoBlackLevel(TUint aInstanceID, TUint aDesiredRedVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRedVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRedVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredRedVideoBlackLevel));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetRedVideoBlackLevel(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetGreenVideoBlackLevel(TUint aInstanceID, TUint& aCurrentGreenVideoBlackLevel)
{
    SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1 sync(*this, aCurrentGreenVideoBlackLevel);
    BeginGetGreenVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetGreenVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetGreenVideoBlackLevel(IAsync& aAsync, TUint& aCurrentGreenVideoBlackLevel)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetGreenVideoBlackLevel(TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel)
{
    SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1 sync(*this);
    BeginSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetGreenVideoBlackLevel(TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetGreenVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetGreenVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredGreenVideoBlackLevel));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetGreenVideoBlackLevel(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetBlueVideoBlackLevel(TUint aInstanceID, TUint& aCurrentBlueVideoBlackLevel)
{
    SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1 sync(*this, aCurrentBlueVideoBlackLevel);
    BeginGetBlueVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetBlueVideoBlackLevel(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetBlueVideoBlackLevel(IAsync& aAsync, TUint& aCurrentBlueVideoBlackLevel)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetBlueVideoBlackLevel(TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel)
{
    SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1 sync(*this);
    BeginSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetBlueVideoBlackLevel(TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBlueVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBlueVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBlueVideoBlackLevel));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetBlueVideoBlackLevel(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetColorTemperature(TUint aInstanceID, TUint& aCurrentColorTemperature)
{
    SyncGetColorTemperatureUpnpOrgRenderingControl1 sync(*this, aCurrentColorTemperature);
    BeginGetColorTemperature(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetColorTemperature(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetColorTemperature(IAsync& aAsync, TUint& aCurrentColorTemperature)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetColorTemperature(TUint aInstanceID, TUint aDesiredColorTemperature)
{
    SyncSetColorTemperatureUpnpOrgRenderingControl1 sync(*this);
    BeginSetColorTemperature(aInstanceID, aDesiredColorTemperature, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetColorTemperature(TUint aInstanceID, TUint aDesiredColorTemperature, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetColorTemperature, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColorTemperature->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredColorTemperature));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetColorTemperature(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetHorizontalKeystone(TUint aInstanceID, TInt& aCurrentHorizontalKeystone)
{
    SyncGetHorizontalKeystoneUpnpOrgRenderingControl1 sync(*this, aCurrentHorizontalKeystone);
    BeginGetHorizontalKeystone(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetHorizontalKeystone(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetHorizontalKeystone(IAsync& aAsync, TInt& aCurrentHorizontalKeystone)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetHorizontalKeystone(TUint aInstanceID, TInt aDesiredHorizontalKeystone)
{
    SyncSetHorizontalKeystoneUpnpOrgRenderingControl1 sync(*this);
    BeginSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetHorizontalKeystone(TUint aInstanceID, TInt aDesiredHorizontalKeystone, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetHorizontalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetHorizontalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredHorizontalKeystone));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetHorizontalKeystone(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetVerticalKeystone(TUint aInstanceID, TInt& aCurrentVerticalKeystone)
{
    SyncGetVerticalKeystoneUpnpOrgRenderingControl1 sync(*this, aCurrentVerticalKeystone);
    BeginGetVerticalKeystone(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetVerticalKeystone(TUint aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetVerticalKeystone(IAsync& aAsync, TInt& aCurrentVerticalKeystone)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetVerticalKeystone(TUint aInstanceID, TInt aDesiredVerticalKeystone)
{
    SyncSetVerticalKeystoneUpnpOrgRenderingControl1 sync(*this);
    BeginSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetVerticalKeystone(TUint aInstanceID, TInt aDesiredVerticalKeystone, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVerticalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVerticalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredVerticalKeystone));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetVerticalKeystone(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetMute(TUint aInstanceID, const Brx& aChannel, TBool& aCurrentMute)
{
    SyncGetMuteUpnpOrgRenderingControl1 sync(*this, aCurrentMute);
    BeginGetMute(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetMute(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetMute(IAsync& aAsync, TBool& aCurrentMute)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetMute(TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute)
{
    SyncSetMuteUpnpOrgRenderingControl1 sync(*this);
    BeginSetMute(aInstanceID, aChannel, aDesiredMute, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetMute(TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredMute));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetMute(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetVolume(TUint aInstanceID, const Brx& aChannel, TUint& aCurrentVolume)
{
    SyncGetVolumeUpnpOrgRenderingControl1 sync(*this, aCurrentVolume);
    BeginGetVolume(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetVolume(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetVolume(IAsync& aAsync, TUint& aCurrentVolume)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetVolume(TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume)
{
    SyncSetVolumeUpnpOrgRenderingControl1 sync(*this);
    BeginSetVolume(aInstanceID, aChannel, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetVolume(TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredVolume));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetVolume(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt& aCurrentVolume)
{
    SyncGetVolumeDBUpnpOrgRenderingControl1 sync(*this, aCurrentVolume);
    BeginGetVolumeDB(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetVolumeDB(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetVolumeDB(IAsync& aAsync, TInt& aCurrentVolume)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume)
{
    SyncSetVolumeDBUpnpOrgRenderingControl1 sync(*this);
    BeginSetVolumeDB(aInstanceID, aChannel, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetVolumeDB(TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolumeDB, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolumeDB->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredVolume));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetVolumeDB(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetVolumeDBRange(TUint aInstanceID, const Brx& aChannel, TInt& aMinValue, TInt& aMaxValue)
{
    SyncGetVolumeDBRangeUpnpOrgRenderingControl1 sync(*this, aMinValue, aMaxValue);
    BeginGetVolumeDBRange(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetVolumeDBRange(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetVolumeDBRange(IAsync& aAsync, TInt& aMinValue, TInt& aMaxValue)
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

void CpProxyUpnpOrgRenderingControl1::SyncGetLoudness(TUint aInstanceID, const Brx& aChannel, TBool& aCurrentLoudness)
{
    SyncGetLoudnessUpnpOrgRenderingControl1 sync(*this, aCurrentLoudness);
    BeginGetLoudness(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginGetLoudness(TUint aInstanceID, const Brx& aChannel, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl1::EndGetLoudness(IAsync& aAsync, TBool& aCurrentLoudness)
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

void CpProxyUpnpOrgRenderingControl1::SyncSetLoudness(TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness)
{
    SyncSetLoudnessUpnpOrgRenderingControl1 sync(*this);
    BeginSetLoudness(aInstanceID, aChannel, aDesiredLoudness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1::BeginSetLoudness(TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetLoudness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLoudness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aChannel));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredLoudness));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl1::EndSetLoudness(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl1::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgRenderingControl1::PropertyLastChange(Brhz& aLastChange) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aLastChange.Set(iLastChange->Value());
}

void CpProxyUpnpOrgRenderingControl1::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}

