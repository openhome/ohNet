#include <Std/CpUpnpOrgRenderingControl1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncListPresetsUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncListPresetsUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, std::string& aCurrentPresetNameList);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    std::string& iCurrentPresetNameList;
};

SyncListPresetsUpnpOrgRenderingControl1Cpp::SyncListPresetsUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, std::string& aCurrentPresetNameList)
    : iService(aService)
    , iCurrentPresetNameList(aCurrentPresetNameList)
{
}

void SyncListPresetsUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndListPresets(aAsync, iCurrentPresetNameList);
}


class SyncSelectPresetUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSelectPresetUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSelectPresetUpnpOrgRenderingControl1Cpp::SyncSelectPresetUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSelectPresetUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSelectPreset(aAsync);
}


class SyncGetBrightnessUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetBrightnessUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentBrightness);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    uint32_t& iCurrentBrightness;
};

SyncGetBrightnessUpnpOrgRenderingControl1Cpp::SyncGetBrightnessUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentBrightness)
    : iService(aService)
    , iCurrentBrightness(aCurrentBrightness)
{
}

void SyncGetBrightnessUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBrightness(aAsync, iCurrentBrightness);
}


class SyncSetBrightnessUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetBrightnessUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetBrightnessUpnpOrgRenderingControl1Cpp::SyncSetBrightnessUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetBrightnessUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBrightness(aAsync);
}


class SyncGetContrastUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetContrastUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentContrast);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    uint32_t& iCurrentContrast;
};

SyncGetContrastUpnpOrgRenderingControl1Cpp::SyncGetContrastUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentContrast)
    : iService(aService)
    , iCurrentContrast(aCurrentContrast)
{
}

void SyncGetContrastUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetContrast(aAsync, iCurrentContrast);
}


class SyncSetContrastUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetContrastUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetContrastUpnpOrgRenderingControl1Cpp::SyncSetContrastUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetContrastUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetContrast(aAsync);
}


class SyncGetSharpnessUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetSharpnessUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentSharpness);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    uint32_t& iCurrentSharpness;
};

SyncGetSharpnessUpnpOrgRenderingControl1Cpp::SyncGetSharpnessUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentSharpness)
    : iService(aService)
    , iCurrentSharpness(aCurrentSharpness)
{
}

void SyncGetSharpnessUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSharpness(aAsync, iCurrentSharpness);
}


class SyncSetSharpnessUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetSharpnessUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetSharpnessUpnpOrgRenderingControl1Cpp::SyncSetSharpnessUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetSharpnessUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSharpness(aAsync);
}


class SyncGetRedVideoGainUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetRedVideoGainUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentRedVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    uint32_t& iCurrentRedVideoGain;
};

SyncGetRedVideoGainUpnpOrgRenderingControl1Cpp::SyncGetRedVideoGainUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentRedVideoGain)
    : iService(aService)
    , iCurrentRedVideoGain(aCurrentRedVideoGain)
{
}

void SyncGetRedVideoGainUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRedVideoGain(aAsync, iCurrentRedVideoGain);
}


class SyncSetRedVideoGainUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetRedVideoGainUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetRedVideoGainUpnpOrgRenderingControl1Cpp::SyncSetRedVideoGainUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetRedVideoGainUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRedVideoGain(aAsync);
}


class SyncGetGreenVideoGainUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetGreenVideoGainUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentGreenVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    uint32_t& iCurrentGreenVideoGain;
};

SyncGetGreenVideoGainUpnpOrgRenderingControl1Cpp::SyncGetGreenVideoGainUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentGreenVideoGain)
    : iService(aService)
    , iCurrentGreenVideoGain(aCurrentGreenVideoGain)
{
}

void SyncGetGreenVideoGainUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetGreenVideoGain(aAsync, iCurrentGreenVideoGain);
}


class SyncSetGreenVideoGainUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetGreenVideoGainUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetGreenVideoGainUpnpOrgRenderingControl1Cpp::SyncSetGreenVideoGainUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetGreenVideoGainUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetGreenVideoGain(aAsync);
}


class SyncGetBlueVideoGainUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetBlueVideoGainUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentBlueVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    uint32_t& iCurrentBlueVideoGain;
};

SyncGetBlueVideoGainUpnpOrgRenderingControl1Cpp::SyncGetBlueVideoGainUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentBlueVideoGain)
    : iService(aService)
    , iCurrentBlueVideoGain(aCurrentBlueVideoGain)
{
}

void SyncGetBlueVideoGainUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBlueVideoGain(aAsync, iCurrentBlueVideoGain);
}


class SyncSetBlueVideoGainUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetBlueVideoGainUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetBlueVideoGainUpnpOrgRenderingControl1Cpp::SyncSetBlueVideoGainUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetBlueVideoGainUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBlueVideoGain(aAsync);
}


class SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentRedVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    uint32_t& iCurrentRedVideoBlackLevel;
};

SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1Cpp::SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentRedVideoBlackLevel)
    : iService(aService)
    , iCurrentRedVideoBlackLevel(aCurrentRedVideoBlackLevel)
{
}

void SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRedVideoBlackLevel(aAsync, iCurrentRedVideoBlackLevel);
}


class SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1Cpp::SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRedVideoBlackLevel(aAsync);
}


class SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentGreenVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    uint32_t& iCurrentGreenVideoBlackLevel;
};

SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1Cpp::SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentGreenVideoBlackLevel)
    : iService(aService)
    , iCurrentGreenVideoBlackLevel(aCurrentGreenVideoBlackLevel)
{
}

void SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetGreenVideoBlackLevel(aAsync, iCurrentGreenVideoBlackLevel);
}


class SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1Cpp::SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetGreenVideoBlackLevel(aAsync);
}


class SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentBlueVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    uint32_t& iCurrentBlueVideoBlackLevel;
};

SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1Cpp::SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentBlueVideoBlackLevel)
    : iService(aService)
    , iCurrentBlueVideoBlackLevel(aCurrentBlueVideoBlackLevel)
{
}

void SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBlueVideoBlackLevel(aAsync, iCurrentBlueVideoBlackLevel);
}


class SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1Cpp::SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBlueVideoBlackLevel(aAsync);
}


class SyncGetColorTemperatureUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetColorTemperatureUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentColorTemperature);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    uint32_t& iCurrentColorTemperature;
};

SyncGetColorTemperatureUpnpOrgRenderingControl1Cpp::SyncGetColorTemperatureUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentColorTemperature)
    : iService(aService)
    , iCurrentColorTemperature(aCurrentColorTemperature)
{
}

void SyncGetColorTemperatureUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColorTemperature(aAsync, iCurrentColorTemperature);
}


class SyncSetColorTemperatureUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetColorTemperatureUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetColorTemperatureUpnpOrgRenderingControl1Cpp::SyncSetColorTemperatureUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetColorTemperatureUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColorTemperature(aAsync);
}


class SyncGetHorizontalKeystoneUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetHorizontalKeystoneUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, int32_t& aCurrentHorizontalKeystone);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    int32_t& iCurrentHorizontalKeystone;
};

SyncGetHorizontalKeystoneUpnpOrgRenderingControl1Cpp::SyncGetHorizontalKeystoneUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, int32_t& aCurrentHorizontalKeystone)
    : iService(aService)
    , iCurrentHorizontalKeystone(aCurrentHorizontalKeystone)
{
}

void SyncGetHorizontalKeystoneUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetHorizontalKeystone(aAsync, iCurrentHorizontalKeystone);
}


class SyncSetHorizontalKeystoneUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetHorizontalKeystoneUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetHorizontalKeystoneUpnpOrgRenderingControl1Cpp::SyncSetHorizontalKeystoneUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetHorizontalKeystoneUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetHorizontalKeystone(aAsync);
}


class SyncGetVerticalKeystoneUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetVerticalKeystoneUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, int32_t& aCurrentVerticalKeystone);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    int32_t& iCurrentVerticalKeystone;
};

SyncGetVerticalKeystoneUpnpOrgRenderingControl1Cpp::SyncGetVerticalKeystoneUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, int32_t& aCurrentVerticalKeystone)
    : iService(aService)
    , iCurrentVerticalKeystone(aCurrentVerticalKeystone)
{
}

void SyncGetVerticalKeystoneUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVerticalKeystone(aAsync, iCurrentVerticalKeystone);
}


class SyncSetVerticalKeystoneUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetVerticalKeystoneUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetVerticalKeystoneUpnpOrgRenderingControl1Cpp::SyncSetVerticalKeystoneUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetVerticalKeystoneUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVerticalKeystone(aAsync);
}


class SyncGetMuteUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetMuteUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, bool& aCurrentMute);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    bool& iCurrentMute;
};

SyncGetMuteUpnpOrgRenderingControl1Cpp::SyncGetMuteUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, bool& aCurrentMute)
    : iService(aService)
    , iCurrentMute(aCurrentMute)
{
}

void SyncGetMuteUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMute(aAsync, iCurrentMute);
}


class SyncSetMuteUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetMuteUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetMuteUpnpOrgRenderingControl1Cpp::SyncSetMuteUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetMuteUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMute(aAsync);
}


class SyncGetVolumeUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetVolumeUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    uint32_t& iCurrentVolume;
};

SyncGetVolumeUpnpOrgRenderingControl1Cpp::SyncGetVolumeUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, uint32_t& aCurrentVolume)
    : iService(aService)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetVolumeUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolume(aAsync, iCurrentVolume);
}


class SyncSetVolumeUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetVolumeUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetVolumeUpnpOrgRenderingControl1Cpp::SyncSetVolumeUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetVolumeUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolume(aAsync);
}


class SyncGetVolumeDBUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetVolumeDBUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, int32_t& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    int32_t& iCurrentVolume;
};

SyncGetVolumeDBUpnpOrgRenderingControl1Cpp::SyncGetVolumeDBUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, int32_t& aCurrentVolume)
    : iService(aService)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetVolumeDBUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolumeDB(aAsync, iCurrentVolume);
}


class SyncSetVolumeDBUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetVolumeDBUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetVolumeDBUpnpOrgRenderingControl1Cpp::SyncSetVolumeDBUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetVolumeDBUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolumeDB(aAsync);
}


class SyncGetVolumeDBRangeUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetVolumeDBRangeUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, int32_t& aMinValue, int32_t& aMaxValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    int32_t& iMinValue;
    int32_t& iMaxValue;
};

SyncGetVolumeDBRangeUpnpOrgRenderingControl1Cpp::SyncGetVolumeDBRangeUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, int32_t& aMinValue, int32_t& aMaxValue)
    : iService(aService)
    , iMinValue(aMinValue)
    , iMaxValue(aMaxValue)
{
}

void SyncGetVolumeDBRangeUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolumeDBRange(aAsync, iMinValue, iMaxValue);
}


class SyncGetLoudnessUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncGetLoudnessUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, bool& aCurrentLoudness);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
    bool& iCurrentLoudness;
};

SyncGetLoudnessUpnpOrgRenderingControl1Cpp::SyncGetLoudnessUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService, bool& aCurrentLoudness)
    : iService(aService)
    , iCurrentLoudness(aCurrentLoudness)
{
}

void SyncGetLoudnessUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLoudness(aAsync, iCurrentLoudness);
}


class SyncSetLoudnessUpnpOrgRenderingControl1Cpp : public SyncProxyAction
{
public:
    SyncSetLoudnessUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgRenderingControl1Cpp& iService;
};

SyncSetLoudnessUpnpOrgRenderingControl1Cpp::SyncSetLoudnessUpnpOrgRenderingControl1Cpp(CpProxyUpnpOrgRenderingControl1Cpp& aService)
    : iService(aService)
{
}

void SyncSetLoudnessUpnpOrgRenderingControl1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLoudness(aAsync);
}


CpProxyUpnpOrgRenderingControl1Cpp::CpProxyUpnpOrgRenderingControl1Cpp(CpDeviceCpp& aDevice)
{
    iService = new CpiService("schemas-upnp-org", "RenderingControl", 1, aDevice.Device());
    Zapp::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionListPresets = new Action("ListPresets");
    param = new Zapp::ParameterUint("InstanceID");
    iActionListPresets->AddInputParameter(param);
    param = new Zapp::ParameterString("CurrentPresetNameList");
    iActionListPresets->AddOutputParameter(param);

    iActionSelectPreset = new Action("SelectPreset");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSelectPreset->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"FactoryDefaults";
    param = new Zapp::ParameterString("PresetName", allowedValues, 1);
    iActionSelectPreset->AddInputParameter(param);
    delete[] allowedValues;

    iActionGetBrightness = new Action("GetBrightness");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetBrightness->AddInputParameter(param);
    param = new Zapp::ParameterUint("CurrentBrightness", 0, 0, 1);
    iActionGetBrightness->AddOutputParameter(param);

    iActionSetBrightness = new Action("SetBrightness");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetBrightness->AddInputParameter(param);
    param = new Zapp::ParameterUint("DesiredBrightness", 0, 0, 1);
    iActionSetBrightness->AddInputParameter(param);

    iActionGetContrast = new Action("GetContrast");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetContrast->AddInputParameter(param);
    param = new Zapp::ParameterUint("CurrentContrast", 0, 0, 1);
    iActionGetContrast->AddOutputParameter(param);

    iActionSetContrast = new Action("SetContrast");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetContrast->AddInputParameter(param);
    param = new Zapp::ParameterUint("DesiredContrast", 0, 0, 1);
    iActionSetContrast->AddInputParameter(param);

    iActionGetSharpness = new Action("GetSharpness");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetSharpness->AddInputParameter(param);
    param = new Zapp::ParameterUint("CurrentSharpness", 0, 0, 1);
    iActionGetSharpness->AddOutputParameter(param);

    iActionSetSharpness = new Action("SetSharpness");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetSharpness->AddInputParameter(param);
    param = new Zapp::ParameterUint("DesiredSharpness", 0, 0, 1);
    iActionSetSharpness->AddInputParameter(param);

    iActionGetRedVideoGain = new Action("GetRedVideoGain");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetRedVideoGain->AddInputParameter(param);
    param = new Zapp::ParameterUint("CurrentRedVideoGain");
    iActionGetRedVideoGain->AddOutputParameter(param);

    iActionSetRedVideoGain = new Action("SetRedVideoGain");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetRedVideoGain->AddInputParameter(param);
    param = new Zapp::ParameterUint("DesiredRedVideoGain");
    iActionSetRedVideoGain->AddInputParameter(param);

    iActionGetGreenVideoGain = new Action("GetGreenVideoGain");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetGreenVideoGain->AddInputParameter(param);
    param = new Zapp::ParameterUint("CurrentGreenVideoGain", 0, 0, 1);
    iActionGetGreenVideoGain->AddOutputParameter(param);

    iActionSetGreenVideoGain = new Action("SetGreenVideoGain");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetGreenVideoGain->AddInputParameter(param);
    param = new Zapp::ParameterUint("DesiredGreenVideoGain", 0, 0, 1);
    iActionSetGreenVideoGain->AddInputParameter(param);

    iActionGetBlueVideoGain = new Action("GetBlueVideoGain");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetBlueVideoGain->AddInputParameter(param);
    param = new Zapp::ParameterUint("CurrentBlueVideoGain", 0, 0, 1);
    iActionGetBlueVideoGain->AddOutputParameter(param);

    iActionSetBlueVideoGain = new Action("SetBlueVideoGain");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetBlueVideoGain->AddInputParameter(param);
    param = new Zapp::ParameterUint("DesiredBlueVideoGain", 0, 0, 1);
    iActionSetBlueVideoGain->AddInputParameter(param);

    iActionGetRedVideoBlackLevel = new Action("GetRedVideoBlackLevel");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetRedVideoBlackLevel->AddInputParameter(param);
    param = new Zapp::ParameterUint("CurrentRedVideoBlackLevel", 0, 0, 1);
    iActionGetRedVideoBlackLevel->AddOutputParameter(param);

    iActionSetRedVideoBlackLevel = new Action("SetRedVideoBlackLevel");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetRedVideoBlackLevel->AddInputParameter(param);
    param = new Zapp::ParameterUint("DesiredRedVideoBlackLevel", 0, 0, 1);
    iActionSetRedVideoBlackLevel->AddInputParameter(param);

    iActionGetGreenVideoBlackLevel = new Action("GetGreenVideoBlackLevel");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetGreenVideoBlackLevel->AddInputParameter(param);
    param = new Zapp::ParameterUint("CurrentGreenVideoBlackLevel", 0, 0, 1);
    iActionGetGreenVideoBlackLevel->AddOutputParameter(param);

    iActionSetGreenVideoBlackLevel = new Action("SetGreenVideoBlackLevel");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetGreenVideoBlackLevel->AddInputParameter(param);
    param = new Zapp::ParameterUint("DesiredGreenVideoBlackLevel", 0, 0, 1);
    iActionSetGreenVideoBlackLevel->AddInputParameter(param);

    iActionGetBlueVideoBlackLevel = new Action("GetBlueVideoBlackLevel");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetBlueVideoBlackLevel->AddInputParameter(param);
    param = new Zapp::ParameterUint("CurrentBlueVideoBlackLevel", 0, 0, 1);
    iActionGetBlueVideoBlackLevel->AddOutputParameter(param);

    iActionSetBlueVideoBlackLevel = new Action("SetBlueVideoBlackLevel");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetBlueVideoBlackLevel->AddInputParameter(param);
    param = new Zapp::ParameterUint("DesiredBlueVideoBlackLevel", 0, 0, 1);
    iActionSetBlueVideoBlackLevel->AddInputParameter(param);

    iActionGetColorTemperature = new Action("GetColorTemperature");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetColorTemperature->AddInputParameter(param);
    param = new Zapp::ParameterUint("CurrentColorTemperature", 0, 0, 1);
    iActionGetColorTemperature->AddOutputParameter(param);

    iActionSetColorTemperature = new Action("SetColorTemperature");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetColorTemperature->AddInputParameter(param);
    param = new Zapp::ParameterUint("DesiredColorTemperature", 0, 0, 1);
    iActionSetColorTemperature->AddInputParameter(param);

    iActionGetHorizontalKeystone = new Action("GetHorizontalKeystone");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetHorizontalKeystone->AddInputParameter(param);
    param = new Zapp::ParameterInt("CurrentHorizontalKeystone");
    iActionGetHorizontalKeystone->AddOutputParameter(param);

    iActionSetHorizontalKeystone = new Action("SetHorizontalKeystone");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetHorizontalKeystone->AddInputParameter(param);
    param = new Zapp::ParameterInt("DesiredHorizontalKeystone");
    iActionSetHorizontalKeystone->AddInputParameter(param);

    iActionGetVerticalKeystone = new Action("GetVerticalKeystone");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetVerticalKeystone->AddInputParameter(param);
    param = new Zapp::ParameterInt("CurrentVerticalKeystone");
    iActionGetVerticalKeystone->AddOutputParameter(param);

    iActionSetVerticalKeystone = new Action("SetVerticalKeystone");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetVerticalKeystone->AddInputParameter(param);
    param = new Zapp::ParameterInt("DesiredVerticalKeystone");
    iActionSetVerticalKeystone->AddInputParameter(param);

    iActionGetMute = new Action("GetMute");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetMute->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new Zapp::ParameterString("Channel", allowedValues, 1);
    iActionGetMute->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterBool("CurrentMute");
    iActionGetMute->AddOutputParameter(param);

    iActionSetMute = new Action("SetMute");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetMute->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new Zapp::ParameterString("Channel", allowedValues, 1);
    iActionSetMute->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterBool("DesiredMute");
    iActionSetMute->AddInputParameter(param);

    iActionGetVolume = new Action("GetVolume");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetVolume->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new Zapp::ParameterString("Channel", allowedValues, 1);
    iActionGetVolume->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterUint("CurrentVolume", 0, 0, 1);
    iActionGetVolume->AddOutputParameter(param);

    iActionSetVolume = new Action("SetVolume");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetVolume->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new Zapp::ParameterString("Channel", allowedValues, 1);
    iActionSetVolume->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterUint("DesiredVolume", 0, 0, 1);
    iActionSetVolume->AddInputParameter(param);

    iActionGetVolumeDB = new Action("GetVolumeDB");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetVolumeDB->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new Zapp::ParameterString("Channel", allowedValues, 1);
    iActionGetVolumeDB->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterInt("CurrentVolume");
    iActionGetVolumeDB->AddOutputParameter(param);

    iActionSetVolumeDB = new Action("SetVolumeDB");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetVolumeDB->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new Zapp::ParameterString("Channel", allowedValues, 1);
    iActionSetVolumeDB->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterInt("DesiredVolume");
    iActionSetVolumeDB->AddInputParameter(param);

    iActionGetVolumeDBRange = new Action("GetVolumeDBRange");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetVolumeDBRange->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new Zapp::ParameterString("Channel", allowedValues, 1);
    iActionGetVolumeDBRange->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterInt("MinValue");
    iActionGetVolumeDBRange->AddOutputParameter(param);
    param = new Zapp::ParameterInt("MaxValue");
    iActionGetVolumeDBRange->AddOutputParameter(param);

    iActionGetLoudness = new Action("GetLoudness");
    param = new Zapp::ParameterUint("InstanceID");
    iActionGetLoudness->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new Zapp::ParameterString("Channel", allowedValues, 1);
    iActionGetLoudness->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterBool("CurrentLoudness");
    iActionGetLoudness->AddOutputParameter(param);

    iActionSetLoudness = new Action("SetLoudness");
    param = new Zapp::ParameterUint("InstanceID");
    iActionSetLoudness->AddInputParameter(param);
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    param = new Zapp::ParameterString("Channel", allowedValues, 1);
    iActionSetLoudness->AddInputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterBool("DesiredLoudness");
    iActionSetLoudness->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgRenderingControl1Cpp::LastChangePropertyChanged);
    iLastChange = new PropertyString("LastChange", functor);
    iService->AddProperty(iLastChange);
}

CpProxyUpnpOrgRenderingControl1Cpp::~CpProxyUpnpOrgRenderingControl1Cpp()
{
    delete iService;
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncListPresets(uint32_t aInstanceID, std::string& aCurrentPresetNameList)
{
    SyncListPresetsUpnpOrgRenderingControl1Cpp sync(*this, aCurrentPresetNameList);
    BeginListPresets(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginListPresets(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionListPresets, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionListPresets->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionListPresets->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndListPresets(IAsync& aAsync, std::string& aCurrentPresetNameList)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ListPresets"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentPresetNameList.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSelectPreset(uint32_t aInstanceID, const std::string& aPresetName)
{
    SyncSelectPresetUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSelectPreset(aInstanceID, aPresetName, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSelectPreset(uint32_t aInstanceID, const std::string& aPresetName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSelectPreset, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSelectPreset->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aPresetName.c_str(), aPresetName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSelectPreset(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SelectPreset"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetBrightness(uint32_t aInstanceID, uint32_t& aCurrentBrightness)
{
    SyncGetBrightnessUpnpOrgRenderingControl1Cpp sync(*this, aCurrentBrightness);
    BeginGetBrightness(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetBrightness(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetBrightness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetBrightness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBrightness->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetBrightness(IAsync& aAsync, uint32_t& aCurrentBrightness)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetBrightness(uint32_t aInstanceID, uint32_t aDesiredBrightness)
{
    SyncSetBrightnessUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetBrightness(aInstanceID, aDesiredBrightness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetBrightness(uint32_t aInstanceID, uint32_t aDesiredBrightness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBrightness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBrightness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBrightness));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetBrightness(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBrightness"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetContrast(uint32_t aInstanceID, uint32_t& aCurrentContrast)
{
    SyncGetContrastUpnpOrgRenderingControl1Cpp sync(*this, aCurrentContrast);
    BeginGetContrast(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetContrast(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetContrast, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetContrast->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetContrast->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetContrast(IAsync& aAsync, uint32_t& aCurrentContrast)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetContrast(uint32_t aInstanceID, uint32_t aDesiredContrast)
{
    SyncSetContrastUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetContrast(aInstanceID, aDesiredContrast, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetContrast(uint32_t aInstanceID, uint32_t aDesiredContrast, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetContrast, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetContrast->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredContrast));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetContrast(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetContrast"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetSharpness(uint32_t aInstanceID, uint32_t& aCurrentSharpness)
{
    SyncGetSharpnessUpnpOrgRenderingControl1Cpp sync(*this, aCurrentSharpness);
    BeginGetSharpness(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetSharpness(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetSharpness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetSharpness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetSharpness->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetSharpness(IAsync& aAsync, uint32_t& aCurrentSharpness)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetSharpness(uint32_t aInstanceID, uint32_t aDesiredSharpness)
{
    SyncSetSharpnessUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetSharpness(aInstanceID, aDesiredSharpness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetSharpness(uint32_t aInstanceID, uint32_t aDesiredSharpness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSharpness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSharpness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredSharpness));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetSharpness(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSharpness"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetRedVideoGain(uint32_t aInstanceID, uint32_t& aCurrentRedVideoGain)
{
    SyncGetRedVideoGainUpnpOrgRenderingControl1Cpp sync(*this, aCurrentRedVideoGain);
    BeginGetRedVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetRedVideoGain(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRedVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRedVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRedVideoGain->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetRedVideoGain(IAsync& aAsync, uint32_t& aCurrentRedVideoGain)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetRedVideoGain(uint32_t aInstanceID, uint32_t aDesiredRedVideoGain)
{
    SyncSetRedVideoGainUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetRedVideoGain(aInstanceID, aDesiredRedVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetRedVideoGain(uint32_t aInstanceID, uint32_t aDesiredRedVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRedVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRedVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredRedVideoGain));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetRedVideoGain(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRedVideoGain"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetGreenVideoGain(uint32_t aInstanceID, uint32_t& aCurrentGreenVideoGain)
{
    SyncGetGreenVideoGainUpnpOrgRenderingControl1Cpp sync(*this, aCurrentGreenVideoGain);
    BeginGetGreenVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetGreenVideoGain(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetGreenVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetGreenVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetGreenVideoGain->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetGreenVideoGain(IAsync& aAsync, uint32_t& aCurrentGreenVideoGain)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetGreenVideoGain(uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain)
{
    SyncSetGreenVideoGainUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetGreenVideoGain(uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetGreenVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetGreenVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredGreenVideoGain));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetGreenVideoGain(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetGreenVideoGain"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetBlueVideoGain(uint32_t aInstanceID, uint32_t& aCurrentBlueVideoGain)
{
    SyncGetBlueVideoGainUpnpOrgRenderingControl1Cpp sync(*this, aCurrentBlueVideoGain);
    BeginGetBlueVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetBlueVideoGain(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetBlueVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetBlueVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBlueVideoGain->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetBlueVideoGain(IAsync& aAsync, uint32_t& aCurrentBlueVideoGain)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetBlueVideoGain(uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain)
{
    SyncSetBlueVideoGainUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetBlueVideoGain(uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBlueVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBlueVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBlueVideoGain));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetBlueVideoGain(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBlueVideoGain"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetRedVideoBlackLevel(uint32_t aInstanceID, uint32_t& aCurrentRedVideoBlackLevel)
{
    SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1Cpp sync(*this, aCurrentRedVideoBlackLevel);
    BeginGetRedVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetRedVideoBlackLevel(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRedVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRedVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRedVideoBlackLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetRedVideoBlackLevel(IAsync& aAsync, uint32_t& aCurrentRedVideoBlackLevel)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetRedVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel)
{
    SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetRedVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRedVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRedVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredRedVideoBlackLevel));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetRedVideoBlackLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRedVideoBlackLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetGreenVideoBlackLevel(uint32_t aInstanceID, uint32_t& aCurrentGreenVideoBlackLevel)
{
    SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1Cpp sync(*this, aCurrentGreenVideoBlackLevel);
    BeginGetGreenVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetGreenVideoBlackLevel(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetGreenVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetGreenVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetGreenVideoBlackLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetGreenVideoBlackLevel(IAsync& aAsync, uint32_t& aCurrentGreenVideoBlackLevel)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetGreenVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel)
{
    SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetGreenVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetGreenVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetGreenVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredGreenVideoBlackLevel));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetGreenVideoBlackLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetGreenVideoBlackLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetBlueVideoBlackLevel(uint32_t aInstanceID, uint32_t& aCurrentBlueVideoBlackLevel)
{
    SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1Cpp sync(*this, aCurrentBlueVideoBlackLevel);
    BeginGetBlueVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetBlueVideoBlackLevel(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetBlueVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetBlueVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetBlueVideoBlackLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetBlueVideoBlackLevel(IAsync& aAsync, uint32_t& aCurrentBlueVideoBlackLevel)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetBlueVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel)
{
    SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetBlueVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBlueVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBlueVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBlueVideoBlackLevel));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetBlueVideoBlackLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBlueVideoBlackLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetColorTemperature(uint32_t aInstanceID, uint32_t& aCurrentColorTemperature)
{
    SyncGetColorTemperatureUpnpOrgRenderingControl1Cpp sync(*this, aCurrentColorTemperature);
    BeginGetColorTemperature(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetColorTemperature(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetColorTemperature, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetColorTemperature->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetColorTemperature->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetColorTemperature(IAsync& aAsync, uint32_t& aCurrentColorTemperature)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetColorTemperature(uint32_t aInstanceID, uint32_t aDesiredColorTemperature)
{
    SyncSetColorTemperatureUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetColorTemperature(aInstanceID, aDesiredColorTemperature, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetColorTemperature(uint32_t aInstanceID, uint32_t aDesiredColorTemperature, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetColorTemperature, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColorTemperature->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredColorTemperature));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetColorTemperature(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetColorTemperature"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetHorizontalKeystone(uint32_t aInstanceID, int32_t& aCurrentHorizontalKeystone)
{
    SyncGetHorizontalKeystoneUpnpOrgRenderingControl1Cpp sync(*this, aCurrentHorizontalKeystone);
    BeginGetHorizontalKeystone(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetHorizontalKeystone(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetHorizontalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetHorizontalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetHorizontalKeystone->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetHorizontalKeystone(IAsync& aAsync, int32_t& aCurrentHorizontalKeystone)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetHorizontalKeystone(uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone)
{
    SyncSetHorizontalKeystoneUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetHorizontalKeystone(uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetHorizontalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetHorizontalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredHorizontalKeystone));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetHorizontalKeystone(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetHorizontalKeystone"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetVerticalKeystone(uint32_t aInstanceID, int32_t& aCurrentVerticalKeystone)
{
    SyncGetVerticalKeystoneUpnpOrgRenderingControl1Cpp sync(*this, aCurrentVerticalKeystone);
    BeginGetVerticalKeystone(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetVerticalKeystone(uint32_t aInstanceID, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetVerticalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVerticalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVerticalKeystone->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetVerticalKeystone(IAsync& aAsync, int32_t& aCurrentVerticalKeystone)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetVerticalKeystone(uint32_t aInstanceID, int32_t aDesiredVerticalKeystone)
{
    SyncSetVerticalKeystoneUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetVerticalKeystone(uint32_t aInstanceID, int32_t aDesiredVerticalKeystone, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVerticalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVerticalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredVerticalKeystone));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetVerticalKeystone(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVerticalKeystone"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetMute(uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentMute)
{
    SyncGetMuteUpnpOrgRenderingControl1Cpp sync(*this, aCurrentMute);
    BeginGetMute(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetMute(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetMute->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetMute(IAsync& aAsync, bool& aCurrentMute)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetMute(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredMute)
{
    SyncSetMuteUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetMute(aInstanceID, aChannel, aDesiredMute, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetMute(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredMute, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredMute));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetMute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t& aCurrentVolume)
{
    SyncGetVolumeUpnpOrgRenderingControl1Cpp sync(*this, aCurrentVolume);
    BeginGetVolume(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetVolume(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetVolume(IAsync& aAsync, uint32_t& aCurrentVolume)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t aDesiredVolume)
{
    SyncSetVolumeUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetVolume(aInstanceID, aChannel, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredVolume));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolume"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetVolumeDB(uint32_t aInstanceID, const std::string& aChannel, int32_t& aCurrentVolume)
{
    SyncGetVolumeDBUpnpOrgRenderingControl1Cpp sync(*this, aCurrentVolume);
    BeginGetVolumeDB(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetVolumeDB(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetVolumeDB, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVolumeDB->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVolumeDB->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetVolumeDB(IAsync& aAsync, int32_t& aCurrentVolume)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetVolumeDB(uint32_t aInstanceID, const std::string& aChannel, int32_t aDesiredVolume)
{
    SyncSetVolumeDBUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetVolumeDB(aInstanceID, aChannel, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetVolumeDB(uint32_t aInstanceID, const std::string& aChannel, int32_t aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolumeDB, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolumeDB->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredVolume));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetVolumeDB(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolumeDB"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetVolumeDBRange(uint32_t aInstanceID, const std::string& aChannel, int32_t& aMinValue, int32_t& aMaxValue)
{
    SyncGetVolumeDBRangeUpnpOrgRenderingControl1Cpp sync(*this, aMinValue, aMaxValue);
    BeginGetVolumeDBRange(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetVolumeDBRange(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetVolumeDBRange, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVolumeDBRange->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVolumeDBRange->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetVolumeDBRange(IAsync& aAsync, int32_t& aMinValue, int32_t& aMaxValue)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncGetLoudness(uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentLoudness)
{
    SyncGetLoudnessUpnpOrgRenderingControl1Cpp sync(*this, aCurrentLoudness);
    BeginGetLoudness(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginGetLoudness(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetLoudness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetLoudness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLoudness->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndGetLoudness(IAsync& aAsync, bool& aCurrentLoudness)
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

void CpProxyUpnpOrgRenderingControl1Cpp::SyncSetLoudness(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredLoudness)
{
    SyncSetLoudnessUpnpOrgRenderingControl1Cpp sync(*this);
    BeginSetLoudness(aInstanceID, aChannel, aDesiredLoudness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl1Cpp::BeginSetLoudness(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredLoudness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetLoudness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLoudness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredLoudness));
    invocation->Invoke();
}

void CpProxyUpnpOrgRenderingControl1Cpp::EndSetLoudness(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetLoudness"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgRenderingControl1Cpp::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgRenderingControl1Cpp::PropertyLastChange(std::string& aLastChange) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iLastChange->Value();
    aLastChange.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgRenderingControl1Cpp::LastChangePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iLastChangeChanged != NULL) {
        iLastChangeChanged();
    }
}

