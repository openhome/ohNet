#include "CpUpnpOrgRenderingControl2.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncListPresetsUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncListPresetsUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, std::string& aCurrentPresetNameList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncListPresetsUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    std::string& iCurrentPresetNameList;
};

SyncListPresetsUpnpOrgRenderingControl2Cpp::SyncListPresetsUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, std::string& aCurrentPresetNameList)
    : iService(aProxy)
    , iCurrentPresetNameList(aCurrentPresetNameList)
{
}

void SyncListPresetsUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndListPresets(aAsync, iCurrentPresetNameList);
}


class SyncSelectPresetUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSelectPresetUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSelectPresetUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSelectPresetUpnpOrgRenderingControl2Cpp::SyncSelectPresetUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSelectPresetUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSelectPreset(aAsync);
}


class SyncGetBrightnessUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetBrightnessUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentBrightness);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBrightnessUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    uint32_t& iCurrentBrightness;
};

SyncGetBrightnessUpnpOrgRenderingControl2Cpp::SyncGetBrightnessUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentBrightness)
    : iService(aProxy)
    , iCurrentBrightness(aCurrentBrightness)
{
}

void SyncGetBrightnessUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBrightness(aAsync, iCurrentBrightness);
}


class SyncSetBrightnessUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetBrightnessUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBrightnessUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetBrightnessUpnpOrgRenderingControl2Cpp::SyncSetBrightnessUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetBrightnessUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBrightness(aAsync);
}


class SyncGetContrastUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetContrastUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentContrast);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetContrastUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    uint32_t& iCurrentContrast;
};

SyncGetContrastUpnpOrgRenderingControl2Cpp::SyncGetContrastUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentContrast)
    : iService(aProxy)
    , iCurrentContrast(aCurrentContrast)
{
}

void SyncGetContrastUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetContrast(aAsync, iCurrentContrast);
}


class SyncSetContrastUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetContrastUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetContrastUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetContrastUpnpOrgRenderingControl2Cpp::SyncSetContrastUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetContrastUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetContrast(aAsync);
}


class SyncGetSharpnessUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetSharpnessUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentSharpness);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetSharpnessUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    uint32_t& iCurrentSharpness;
};

SyncGetSharpnessUpnpOrgRenderingControl2Cpp::SyncGetSharpnessUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentSharpness)
    : iService(aProxy)
    , iCurrentSharpness(aCurrentSharpness)
{
}

void SyncGetSharpnessUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetSharpness(aAsync, iCurrentSharpness);
}


class SyncSetSharpnessUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetSharpnessUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetSharpnessUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetSharpnessUpnpOrgRenderingControl2Cpp::SyncSetSharpnessUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetSharpnessUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSharpness(aAsync);
}


class SyncGetRedVideoGainUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetRedVideoGainUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentRedVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRedVideoGainUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    uint32_t& iCurrentRedVideoGain;
};

SyncGetRedVideoGainUpnpOrgRenderingControl2Cpp::SyncGetRedVideoGainUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentRedVideoGain)
    : iService(aProxy)
    , iCurrentRedVideoGain(aCurrentRedVideoGain)
{
}

void SyncGetRedVideoGainUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRedVideoGain(aAsync, iCurrentRedVideoGain);
}


class SyncSetRedVideoGainUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetRedVideoGainUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRedVideoGainUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetRedVideoGainUpnpOrgRenderingControl2Cpp::SyncSetRedVideoGainUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetRedVideoGainUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRedVideoGain(aAsync);
}


class SyncGetGreenVideoGainUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetGreenVideoGainUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentGreenVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetGreenVideoGainUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    uint32_t& iCurrentGreenVideoGain;
};

SyncGetGreenVideoGainUpnpOrgRenderingControl2Cpp::SyncGetGreenVideoGainUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentGreenVideoGain)
    : iService(aProxy)
    , iCurrentGreenVideoGain(aCurrentGreenVideoGain)
{
}

void SyncGetGreenVideoGainUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetGreenVideoGain(aAsync, iCurrentGreenVideoGain);
}


class SyncSetGreenVideoGainUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetGreenVideoGainUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetGreenVideoGainUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetGreenVideoGainUpnpOrgRenderingControl2Cpp::SyncSetGreenVideoGainUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetGreenVideoGainUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetGreenVideoGain(aAsync);
}


class SyncGetBlueVideoGainUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetBlueVideoGainUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentBlueVideoGain);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBlueVideoGainUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    uint32_t& iCurrentBlueVideoGain;
};

SyncGetBlueVideoGainUpnpOrgRenderingControl2Cpp::SyncGetBlueVideoGainUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentBlueVideoGain)
    : iService(aProxy)
    , iCurrentBlueVideoGain(aCurrentBlueVideoGain)
{
}

void SyncGetBlueVideoGainUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBlueVideoGain(aAsync, iCurrentBlueVideoGain);
}


class SyncSetBlueVideoGainUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetBlueVideoGainUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBlueVideoGainUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetBlueVideoGainUpnpOrgRenderingControl2Cpp::SyncSetBlueVideoGainUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetBlueVideoGainUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBlueVideoGain(aAsync);
}


class SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentRedVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    uint32_t& iCurrentRedVideoBlackLevel;
};

SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp::SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentRedVideoBlackLevel)
    : iService(aProxy)
    , iCurrentRedVideoBlackLevel(aCurrentRedVideoBlackLevel)
{
}

void SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRedVideoBlackLevel(aAsync, iCurrentRedVideoBlackLevel);
}


class SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp::SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRedVideoBlackLevel(aAsync);
}


class SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentGreenVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    uint32_t& iCurrentGreenVideoBlackLevel;
};

SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp::SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentGreenVideoBlackLevel)
    : iService(aProxy)
    , iCurrentGreenVideoBlackLevel(aCurrentGreenVideoBlackLevel)
{
}

void SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetGreenVideoBlackLevel(aAsync, iCurrentGreenVideoBlackLevel);
}


class SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp::SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetGreenVideoBlackLevel(aAsync);
}


class SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentBlueVideoBlackLevel);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    uint32_t& iCurrentBlueVideoBlackLevel;
};

SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp::SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentBlueVideoBlackLevel)
    : iService(aProxy)
    , iCurrentBlueVideoBlackLevel(aCurrentBlueVideoBlackLevel)
{
}

void SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetBlueVideoBlackLevel(aAsync, iCurrentBlueVideoBlackLevel);
}


class SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp::SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBlueVideoBlackLevel(aAsync);
}


class SyncGetColorTemperatureUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetColorTemperatureUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentColorTemperature);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetColorTemperatureUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    uint32_t& iCurrentColorTemperature;
};

SyncGetColorTemperatureUpnpOrgRenderingControl2Cpp::SyncGetColorTemperatureUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentColorTemperature)
    : iService(aProxy)
    , iCurrentColorTemperature(aCurrentColorTemperature)
{
}

void SyncGetColorTemperatureUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColorTemperature(aAsync, iCurrentColorTemperature);
}


class SyncSetColorTemperatureUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetColorTemperatureUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetColorTemperatureUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetColorTemperatureUpnpOrgRenderingControl2Cpp::SyncSetColorTemperatureUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetColorTemperatureUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColorTemperature(aAsync);
}


class SyncGetHorizontalKeystoneUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetHorizontalKeystoneUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, int32_t& aCurrentHorizontalKeystone);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetHorizontalKeystoneUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    int32_t& iCurrentHorizontalKeystone;
};

SyncGetHorizontalKeystoneUpnpOrgRenderingControl2Cpp::SyncGetHorizontalKeystoneUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, int32_t& aCurrentHorizontalKeystone)
    : iService(aProxy)
    , iCurrentHorizontalKeystone(aCurrentHorizontalKeystone)
{
}

void SyncGetHorizontalKeystoneUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetHorizontalKeystone(aAsync, iCurrentHorizontalKeystone);
}


class SyncSetHorizontalKeystoneUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetHorizontalKeystoneUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetHorizontalKeystoneUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetHorizontalKeystoneUpnpOrgRenderingControl2Cpp::SyncSetHorizontalKeystoneUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetHorizontalKeystoneUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetHorizontalKeystone(aAsync);
}


class SyncGetVerticalKeystoneUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetVerticalKeystoneUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, int32_t& aCurrentVerticalKeystone);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVerticalKeystoneUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    int32_t& iCurrentVerticalKeystone;
};

SyncGetVerticalKeystoneUpnpOrgRenderingControl2Cpp::SyncGetVerticalKeystoneUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, int32_t& aCurrentVerticalKeystone)
    : iService(aProxy)
    , iCurrentVerticalKeystone(aCurrentVerticalKeystone)
{
}

void SyncGetVerticalKeystoneUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVerticalKeystone(aAsync, iCurrentVerticalKeystone);
}


class SyncSetVerticalKeystoneUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetVerticalKeystoneUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVerticalKeystoneUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetVerticalKeystoneUpnpOrgRenderingControl2Cpp::SyncSetVerticalKeystoneUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetVerticalKeystoneUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVerticalKeystone(aAsync);
}


class SyncGetMuteUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetMuteUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, bool& aCurrentMute);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetMuteUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    bool& iCurrentMute;
};

SyncGetMuteUpnpOrgRenderingControl2Cpp::SyncGetMuteUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, bool& aCurrentMute)
    : iService(aProxy)
    , iCurrentMute(aCurrentMute)
{
}

void SyncGetMuteUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMute(aAsync, iCurrentMute);
}


class SyncSetMuteUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetMuteUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetMuteUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetMuteUpnpOrgRenderingControl2Cpp::SyncSetMuteUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetMuteUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMute(aAsync);
}


class SyncGetVolumeUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetVolumeUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVolumeUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    uint32_t& iCurrentVolume;
};

SyncGetVolumeUpnpOrgRenderingControl2Cpp::SyncGetVolumeUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, uint32_t& aCurrentVolume)
    : iService(aProxy)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetVolumeUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolume(aAsync, iCurrentVolume);
}


class SyncSetVolumeUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetVolumeUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVolumeUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetVolumeUpnpOrgRenderingControl2Cpp::SyncSetVolumeUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolume(aAsync);
}


class SyncGetVolumeDBUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetVolumeDBUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, int32_t& aCurrentVolume);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVolumeDBUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    int32_t& iCurrentVolume;
};

SyncGetVolumeDBUpnpOrgRenderingControl2Cpp::SyncGetVolumeDBUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, int32_t& aCurrentVolume)
    : iService(aProxy)
    , iCurrentVolume(aCurrentVolume)
{
}

void SyncGetVolumeDBUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolumeDB(aAsync, iCurrentVolume);
}


class SyncSetVolumeDBUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetVolumeDBUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVolumeDBUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetVolumeDBUpnpOrgRenderingControl2Cpp::SyncSetVolumeDBUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeDBUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolumeDB(aAsync);
}


class SyncGetVolumeDBRangeUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetVolumeDBRangeUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, int32_t& aMinValue, int32_t& aMaxValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetVolumeDBRangeUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    int32_t& iMinValue;
    int32_t& iMaxValue;
};

SyncGetVolumeDBRangeUpnpOrgRenderingControl2Cpp::SyncGetVolumeDBRangeUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, int32_t& aMinValue, int32_t& aMaxValue)
    : iService(aProxy)
    , iMinValue(aMinValue)
    , iMaxValue(aMaxValue)
{
}

void SyncGetVolumeDBRangeUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetVolumeDBRange(aAsync, iMinValue, iMaxValue);
}


class SyncGetLoudnessUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetLoudnessUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, bool& aCurrentLoudness);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetLoudnessUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    bool& iCurrentLoudness;
};

SyncGetLoudnessUpnpOrgRenderingControl2Cpp::SyncGetLoudnessUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, bool& aCurrentLoudness)
    : iService(aProxy)
    , iCurrentLoudness(aCurrentLoudness)
{
}

void SyncGetLoudnessUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLoudness(aAsync, iCurrentLoudness);
}


class SyncSetLoudnessUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetLoudnessUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetLoudnessUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
};

SyncSetLoudnessUpnpOrgRenderingControl2Cpp::SyncSetLoudnessUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetLoudnessUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLoudness(aAsync);
}


class SyncGetStateVariablesUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncGetStateVariablesUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, std::string& aStateVariableValuePairs);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStateVariablesUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    std::string& iStateVariableValuePairs;
};

SyncGetStateVariablesUpnpOrgRenderingControl2Cpp::SyncGetStateVariablesUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, std::string& aStateVariableValuePairs)
    : iService(aProxy)
    , iStateVariableValuePairs(aStateVariableValuePairs)
{
}

void SyncGetStateVariablesUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStateVariables(aAsync, iStateVariableValuePairs);
}


class SyncSetStateVariablesUpnpOrgRenderingControl2Cpp : public SyncProxyAction
{
public:
    SyncSetStateVariablesUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, std::string& aStateVariableList);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetStateVariablesUpnpOrgRenderingControl2Cpp() {}
private:
    CpProxyUpnpOrgRenderingControl2Cpp& iService;
    std::string& iStateVariableList;
};

SyncSetStateVariablesUpnpOrgRenderingControl2Cpp::SyncSetStateVariablesUpnpOrgRenderingControl2Cpp(CpProxyUpnpOrgRenderingControl2Cpp& aProxy, std::string& aStateVariableList)
    : iService(aProxy)
    , iStateVariableList(aStateVariableList)
{
}

void SyncSetStateVariablesUpnpOrgRenderingControl2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStateVariables(aAsync, iStateVariableList);
}


CpProxyUpnpOrgRenderingControl2Cpp::CpProxyUpnpOrgRenderingControl2Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgRenderingControl2Cpp::LastChangePropertyChanged);
    iLastChange = new PropertyString(aDevice.Device().GetCpStack().Env(), "LastChange", functor);
    AddProperty(iLastChange);
}

CpProxyUpnpOrgRenderingControl2Cpp::~CpProxyUpnpOrgRenderingControl2Cpp()
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncListPresets(uint32_t aInstanceID, std::string& aCurrentPresetNameList)
{
    SyncListPresetsUpnpOrgRenderingControl2Cpp sync(*this, aCurrentPresetNameList);
    BeginListPresets(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginListPresets(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl2Cpp::EndListPresets(IAsync& aAsync, std::string& aCurrentPresetNameList)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCurrentPresetNameList.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSelectPreset(uint32_t aInstanceID, const std::string& aPresetName)
{
    SyncSelectPresetUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSelectPreset(aInstanceID, aPresetName, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSelectPreset(uint32_t aInstanceID, const std::string& aPresetName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSelectPreset, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSelectPreset->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aPresetName.c_str(), (TUint)aPresetName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSelectPreset(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetBrightness(uint32_t aInstanceID, uint32_t& aCurrentBrightness)
{
    SyncGetBrightnessUpnpOrgRenderingControl2Cpp sync(*this, aCurrentBrightness);
    BeginGetBrightness(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetBrightness(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetBrightness(IAsync& aAsync, uint32_t& aCurrentBrightness)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetBrightness(uint32_t aInstanceID, uint32_t aDesiredBrightness)
{
    SyncSetBrightnessUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetBrightness(aInstanceID, aDesiredBrightness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetBrightness(uint32_t aInstanceID, uint32_t aDesiredBrightness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBrightness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBrightness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBrightness));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetBrightness(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetContrast(uint32_t aInstanceID, uint32_t& aCurrentContrast)
{
    SyncGetContrastUpnpOrgRenderingControl2Cpp sync(*this, aCurrentContrast);
    BeginGetContrast(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetContrast(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetContrast(IAsync& aAsync, uint32_t& aCurrentContrast)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetContrast(uint32_t aInstanceID, uint32_t aDesiredContrast)
{
    SyncSetContrastUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetContrast(aInstanceID, aDesiredContrast, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetContrast(uint32_t aInstanceID, uint32_t aDesiredContrast, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetContrast, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetContrast->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredContrast));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetContrast(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetSharpness(uint32_t aInstanceID, uint32_t& aCurrentSharpness)
{
    SyncGetSharpnessUpnpOrgRenderingControl2Cpp sync(*this, aCurrentSharpness);
    BeginGetSharpness(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetSharpness(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetSharpness(IAsync& aAsync, uint32_t& aCurrentSharpness)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetSharpness(uint32_t aInstanceID, uint32_t aDesiredSharpness)
{
    SyncSetSharpnessUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetSharpness(aInstanceID, aDesiredSharpness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetSharpness(uint32_t aInstanceID, uint32_t aDesiredSharpness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSharpness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSharpness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredSharpness));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetSharpness(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetRedVideoGain(uint32_t aInstanceID, uint32_t& aCurrentRedVideoGain)
{
    SyncGetRedVideoGainUpnpOrgRenderingControl2Cpp sync(*this, aCurrentRedVideoGain);
    BeginGetRedVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetRedVideoGain(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetRedVideoGain(IAsync& aAsync, uint32_t& aCurrentRedVideoGain)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetRedVideoGain(uint32_t aInstanceID, uint32_t aDesiredRedVideoGain)
{
    SyncSetRedVideoGainUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetRedVideoGain(aInstanceID, aDesiredRedVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetRedVideoGain(uint32_t aInstanceID, uint32_t aDesiredRedVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRedVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRedVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredRedVideoGain));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetRedVideoGain(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetGreenVideoGain(uint32_t aInstanceID, uint32_t& aCurrentGreenVideoGain)
{
    SyncGetGreenVideoGainUpnpOrgRenderingControl2Cpp sync(*this, aCurrentGreenVideoGain);
    BeginGetGreenVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetGreenVideoGain(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetGreenVideoGain(IAsync& aAsync, uint32_t& aCurrentGreenVideoGain)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetGreenVideoGain(uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain)
{
    SyncSetGreenVideoGainUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetGreenVideoGain(uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetGreenVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetGreenVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredGreenVideoGain));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetGreenVideoGain(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetBlueVideoGain(uint32_t aInstanceID, uint32_t& aCurrentBlueVideoGain)
{
    SyncGetBlueVideoGainUpnpOrgRenderingControl2Cpp sync(*this, aCurrentBlueVideoGain);
    BeginGetBlueVideoGain(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetBlueVideoGain(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetBlueVideoGain(IAsync& aAsync, uint32_t& aCurrentBlueVideoGain)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetBlueVideoGain(uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain)
{
    SyncSetBlueVideoGainUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetBlueVideoGain(uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBlueVideoGain, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBlueVideoGain->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBlueVideoGain));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetBlueVideoGain(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetRedVideoBlackLevel(uint32_t aInstanceID, uint32_t& aCurrentRedVideoBlackLevel)
{
    SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp sync(*this, aCurrentRedVideoBlackLevel);
    BeginGetRedVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetRedVideoBlackLevel(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetRedVideoBlackLevel(IAsync& aAsync, uint32_t& aCurrentRedVideoBlackLevel)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetRedVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel)
{
    SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetRedVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRedVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRedVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredRedVideoBlackLevel));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetRedVideoBlackLevel(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetGreenVideoBlackLevel(uint32_t aInstanceID, uint32_t& aCurrentGreenVideoBlackLevel)
{
    SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp sync(*this, aCurrentGreenVideoBlackLevel);
    BeginGetGreenVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetGreenVideoBlackLevel(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetGreenVideoBlackLevel(IAsync& aAsync, uint32_t& aCurrentGreenVideoBlackLevel)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetGreenVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel)
{
    SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetGreenVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetGreenVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetGreenVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredGreenVideoBlackLevel));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetGreenVideoBlackLevel(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetBlueVideoBlackLevel(uint32_t aInstanceID, uint32_t& aCurrentBlueVideoBlackLevel)
{
    SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp sync(*this, aCurrentBlueVideoBlackLevel);
    BeginGetBlueVideoBlackLevel(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetBlueVideoBlackLevel(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetBlueVideoBlackLevel(IAsync& aAsync, uint32_t& aCurrentBlueVideoBlackLevel)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetBlueVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel)
{
    SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetBlueVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBlueVideoBlackLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBlueVideoBlackLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredBlueVideoBlackLevel));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetBlueVideoBlackLevel(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetColorTemperature(uint32_t aInstanceID, uint32_t& aCurrentColorTemperature)
{
    SyncGetColorTemperatureUpnpOrgRenderingControl2Cpp sync(*this, aCurrentColorTemperature);
    BeginGetColorTemperature(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetColorTemperature(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetColorTemperature(IAsync& aAsync, uint32_t& aCurrentColorTemperature)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetColorTemperature(uint32_t aInstanceID, uint32_t aDesiredColorTemperature)
{
    SyncSetColorTemperatureUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetColorTemperature(aInstanceID, aDesiredColorTemperature, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetColorTemperature(uint32_t aInstanceID, uint32_t aDesiredColorTemperature, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetColorTemperature, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColorTemperature->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredColorTemperature));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetColorTemperature(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetHorizontalKeystone(uint32_t aInstanceID, int32_t& aCurrentHorizontalKeystone)
{
    SyncGetHorizontalKeystoneUpnpOrgRenderingControl2Cpp sync(*this, aCurrentHorizontalKeystone);
    BeginGetHorizontalKeystone(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetHorizontalKeystone(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetHorizontalKeystone(IAsync& aAsync, int32_t& aCurrentHorizontalKeystone)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetHorizontalKeystone(uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone)
{
    SyncSetHorizontalKeystoneUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetHorizontalKeystone(uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetHorizontalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetHorizontalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredHorizontalKeystone));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetHorizontalKeystone(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetVerticalKeystone(uint32_t aInstanceID, int32_t& aCurrentVerticalKeystone)
{
    SyncGetVerticalKeystoneUpnpOrgRenderingControl2Cpp sync(*this, aCurrentVerticalKeystone);
    BeginGetVerticalKeystone(aInstanceID, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetVerticalKeystone(uint32_t aInstanceID, FunctorAsync& aFunctor)
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

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetVerticalKeystone(IAsync& aAsync, int32_t& aCurrentVerticalKeystone)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetVerticalKeystone(uint32_t aInstanceID, int32_t aDesiredVerticalKeystone)
{
    SyncSetVerticalKeystoneUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetVerticalKeystone(uint32_t aInstanceID, int32_t aDesiredVerticalKeystone, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVerticalKeystone, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVerticalKeystone->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredVerticalKeystone));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetVerticalKeystone(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetMute(uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentMute)
{
    SyncGetMuteUpnpOrgRenderingControl2Cpp sync(*this, aCurrentMute);
    BeginGetMute(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetMute(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), (TUint)aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetMute->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetMute(IAsync& aAsync, bool& aCurrentMute)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetMute(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredMute)
{
    SyncSetMuteUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetMute(aInstanceID, aChannel, aDesiredMute, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetMute(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredMute, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), (TUint)aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredMute));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetMute(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t& aCurrentVolume)
{
    SyncGetVolumeUpnpOrgRenderingControl2Cpp sync(*this, aCurrentVolume);
    BeginGetVolume(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetVolume(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), (TUint)aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetVolume(IAsync& aAsync, uint32_t& aCurrentVolume)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t aDesiredVolume)
{
    SyncSetVolumeUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetVolume(aInstanceID, aChannel, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), (TUint)aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aDesiredVolume));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetVolume(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetVolumeDB(uint32_t aInstanceID, const std::string& aChannel, int32_t& aCurrentVolume)
{
    SyncGetVolumeDBUpnpOrgRenderingControl2Cpp sync(*this, aCurrentVolume);
    BeginGetVolumeDB(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetVolumeDB(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetVolumeDB, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVolumeDB->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), (TUint)aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVolumeDB->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetVolumeDB(IAsync& aAsync, int32_t& aCurrentVolume)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetVolumeDB(uint32_t aInstanceID, const std::string& aChannel, int32_t aDesiredVolume)
{
    SyncSetVolumeDBUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetVolumeDB(aInstanceID, aChannel, aDesiredVolume, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetVolumeDB(uint32_t aInstanceID, const std::string& aChannel, int32_t aDesiredVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolumeDB, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolumeDB->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), (TUint)aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aDesiredVolume));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetVolumeDB(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetVolumeDBRange(uint32_t aInstanceID, const std::string& aChannel, int32_t& aMinValue, int32_t& aMaxValue)
{
    SyncGetVolumeDBRangeUpnpOrgRenderingControl2Cpp sync(*this, aMinValue, aMaxValue);
    BeginGetVolumeDBRange(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetVolumeDBRange(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetVolumeDBRange, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetVolumeDBRange->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), (TUint)aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetVolumeDBRange->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetVolumeDBRange(IAsync& aAsync, int32_t& aMinValue, int32_t& aMaxValue)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetLoudness(uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentLoudness)
{
    SyncGetLoudnessUpnpOrgRenderingControl2Cpp sync(*this, aCurrentLoudness);
    BeginGetLoudness(aInstanceID, aChannel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetLoudness(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetLoudness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetLoudness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), (TUint)aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLoudness->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetLoudness(IAsync& aAsync, bool& aCurrentLoudness)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetLoudness(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredLoudness)
{
    SyncSetLoudnessUpnpOrgRenderingControl2Cpp sync(*this);
    BeginSetLoudness(aInstanceID, aChannel, aDesiredLoudness, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetLoudness(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredLoudness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetLoudness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLoudness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aChannel.c_str(), (TUint)aChannel.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aDesiredLoudness));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetLoudness(IAsync& aAsync)
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

void CpProxyUpnpOrgRenderingControl2Cpp::SyncGetStateVariables(uint32_t aInstanceID, const std::string& aStateVariableList, std::string& aStateVariableValuePairs)
{
    SyncGetStateVariablesUpnpOrgRenderingControl2Cpp sync(*this, aStateVariableValuePairs);
    BeginGetStateVariables(aInstanceID, aStateVariableList, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginGetStateVariables(uint32_t aInstanceID, const std::string& aStateVariableList, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetStateVariables, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetStateVariables->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aStateVariableList.c_str(), (TUint)aStateVariableList.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStateVariables->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndGetStateVariables(IAsync& aAsync, std::string& aStateVariableValuePairs)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aStateVariableValuePairs.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgRenderingControl2Cpp::SyncSetStateVariables(uint32_t aInstanceID, const std::string& aRenderingControlUDN, const std::string& aServiceType, const std::string& aServiceId, const std::string& aStateVariableValuePairs, std::string& aStateVariableList)
{
    SyncSetStateVariablesUpnpOrgRenderingControl2Cpp sync(*this, aStateVariableList);
    BeginSetStateVariables(aInstanceID, aRenderingControlUDN, aServiceType, aServiceId, aStateVariableValuePairs, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgRenderingControl2Cpp::BeginSetStateVariables(uint32_t aInstanceID, const std::string& aRenderingControlUDN, const std::string& aServiceType, const std::string& aServiceId, const std::string& aStateVariableValuePairs, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStateVariables, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStateVariables->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aInstanceID));
    {
        Brn buf((const TByte*)aRenderingControlUDN.c_str(), (TUint)aRenderingControlUDN.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aServiceType.c_str(), (TUint)aServiceType.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aServiceId.c_str(), (TUint)aServiceId.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aStateVariableValuePairs.c_str(), (TUint)aStateVariableValuePairs.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSetStateVariables->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgRenderingControl2Cpp::EndSetStateVariables(IAsync& aAsync, std::string& aStateVariableList)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aStateVariableList.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyUpnpOrgRenderingControl2Cpp::SetPropertyLastChangeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLastChangeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgRenderingControl2Cpp::PropertyLastChange(std::string& aLastChange) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iLastChange->Value();
    aLastChange.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyUpnpOrgRenderingControl2Cpp::LastChangePropertyChanged()
{
    ReportEvent(iLastChangeChanged);
}

