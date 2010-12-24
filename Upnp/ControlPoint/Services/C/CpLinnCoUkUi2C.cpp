#include "CpLinnCoUkUi2.h"
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;

class CpProxyLinnCoUkUi2C : public CpProxyC
{
public:
    CpProxyLinnCoUkUi2C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkUi2C();
    //CpProxyLinnCoUkUi2* Proxy() { return static_cast<CpProxyLinnCoUkUi2*>(iProxy); }

    void SyncDisplayTestPattern(TInt aaTestPattern);
    void BeginDisplayTestPattern(TInt aaTestPattern, FunctorAsync& aFunctor);
    void EndDisplayTestPattern(IAsync& aAsync);

    void SyncDisplayFill();
    void BeginDisplayFill(FunctorAsync& aFunctor);
    void EndDisplayFill(IAsync& aAsync);

    void SyncDisplayClear();
    void BeginDisplayClear(FunctorAsync& aFunctor);
    void EndDisplayClear(IAsync& aAsync);

    void SyncSetTestModeEnabled(TBool aaEnabled);
    void BeginSetTestModeEnabled(TBool aaEnabled, FunctorAsync& aFunctor);
    void EndSetTestModeEnabled(IAsync& aAsync);

    void SyncSimulateInfraredInput(TUint aaCode);
    void BeginSimulateInfraredInput(TUint aaCode, FunctorAsync& aFunctor);
    void EndSimulateInfraredInput(IAsync& aAsync);

    void SyncSimulateButtonInput(TUint aaCode);
    void BeginSimulateButtonInput(TUint aaCode, FunctorAsync& aFunctor);
    void EndSimulateButtonInput(IAsync& aAsync);

    void SyncSimulateLightSensor(TUint aaLightLevel);
    void BeginSimulateLightSensor(TUint aaLightLevel, FunctorAsync& aFunctor);
    void EndSimulateLightSensor(IAsync& aAsync);

    void SyncGetLightSensorData(TUint& aaLightLevel);
    void BeginGetLightSensorData(FunctorAsync& aFunctor);
    void EndGetLightSensorData(IAsync& aAsync, TUint& aaLightLevel);

    void SyncSetDisplayBrightness(TUint aaBrightness);
    void BeginSetDisplayBrightness(TUint aaBrightness, FunctorAsync& aFunctor);
    void EndSetDisplayBrightness(IAsync& aAsync);

    void SyncSetDisplayBrightnessAuto(TBool aaBrightnessAuto);
    void BeginSetDisplayBrightnessAuto(TBool aaBrightnessAuto, FunctorAsync& aFunctor);
    void EndSetDisplayBrightnessAuto(IAsync& aAsync);

    void SyncSetInfraredCommands(const Brx& aaCommands);
    void BeginSetInfraredCommands(const Brx& aaCommands, FunctorAsync& aFunctor);
    void EndSetInfraredCommands(IAsync& aAsync);

    void SyncInfraredCommands(Brh& aaCommands);
    void BeginInfraredCommands(FunctorAsync& aFunctor);
    void EndInfraredCommands(IAsync& aAsync, Brh& aaCommands);

    void SyncSetInfraredTerminalCommands(const Brx& aaCommands);
    void BeginSetInfraredTerminalCommands(const Brx& aaCommands, FunctorAsync& aFunctor);
    void EndSetInfraredTerminalCommands(IAsync& aAsync);

    void SyncInfraredTerminalCommands(Brh& aaCommands);
    void BeginInfraredTerminalCommands(FunctorAsync& aFunctor);
    void EndInfraredTerminalCommands(IAsync& aAsync, Brh& aaCommands);

    void SyncDisplayBrightness(TUint& aaBrightness);
    void BeginDisplayBrightness(FunctorAsync& aFunctor);
    void EndDisplayBrightness(IAsync& aAsync, TUint& aaBrightness);

    void SyncDisplayBrightnessAuto(TBool& aaBrightnessAuto);
    void BeginDisplayBrightnessAuto(FunctorAsync& aFunctor);
    void EndDisplayBrightnessAuto(IAsync& aAsync, TBool& aaBrightnessAuto);

    void SyncDisplayUpsideDown(TBool& aaUpsideDown);
    void BeginDisplayUpsideDown(FunctorAsync& aFunctor);
    void EndDisplayUpsideDown(IAsync& aAsync, TBool& aaUpsideDown);

    void SyncSetDisplayUpsideDown(TBool aaUpsideDown);
    void BeginSetDisplayUpsideDown(TBool aaUpsideDown, FunctorAsync& aFunctor);
    void EndSetDisplayUpsideDown(IAsync& aAsync);

    void SyncSetDisplayScrollText(TBool aaDisplayScrollText);
    void BeginSetDisplayScrollText(TBool aaDisplayScrollText, FunctorAsync& aFunctor);
    void EndSetDisplayScrollText(IAsync& aAsync);

    void SyncDisplayScrollText(TBool& aaDisplayScrollTextEnabled);
    void BeginDisplayScrollText(FunctorAsync& aFunctor);
    void EndDisplayScrollText(IAsync& aAsync, TBool& aaDisplayScrollTextEnabled);

    void SyncSetDisplaySleep(TBool aaEnabled);
    void BeginSetDisplaySleep(TBool aaEnabled, FunctorAsync& aFunctor);
    void EndSetDisplaySleep(IAsync& aAsync);

    void SyncDisplaySleep(TBool& aaEnabled);
    void BeginDisplaySleep(FunctorAsync& aFunctor);
    void EndDisplaySleep(IAsync& aAsync, TBool& aaEnabled);

    void SyncSetDisplayLedOff(TBool aaOff);
    void BeginSetDisplayLedOff(TBool aaOff, FunctorAsync& aFunctor);
    void EndSetDisplayLedOff(IAsync& aAsync);

    void SyncDisplayLedOff(TBool& aaOff);
    void BeginDisplayLedOff(FunctorAsync& aFunctor);
    void EndDisplayLedOff(IAsync& aAsync, TBool& aaOff);

    void SetPropertyDisplayBrightnessChanged(Functor& aFunctor);
    void SetPropertyDisplayBrightnessAutoChanged(Functor& aFunctor);
    void SetPropertyInfraredCommandsChanged(Functor& aFunctor);
    void SetPropertyInfraredTerminalCommandsChanged(Functor& aFunctor);
    void SetPropertyDisplayUpsideDownChanged(Functor& aFunctor);
    void SetPropertyDisplayScrollTextChanged(Functor& aFunctor);
    void SetPropertyDisplaySleepChanged(Functor& aFunctor);
    void SetPropertyDisplayLedOffChanged(Functor& aFunctor);
    void SetPropertyTerminalInputCodeChanged(Functor& aFunctor);
    void SetPropertyTerminalInputNameChanged(Functor& aFunctor);
    void SetPropertyDisplayPixelsChanged(Functor& aFunctor);

    void PropertyDisplayBrightness(TUint& aDisplayBrightness) const;
    void PropertyDisplayBrightnessAuto(TBool& aDisplayBrightnessAuto) const;
    void PropertyInfraredCommands(Brhz& aInfraredCommands) const;
    void PropertyInfraredTerminalCommands(Brhz& aInfraredTerminalCommands) const;
    void PropertyDisplayUpsideDown(TBool& aDisplayUpsideDown) const;
    void PropertyDisplayScrollText(TBool& aDisplayScrollText) const;
    void PropertyDisplaySleep(TBool& aDisplaySleep) const;
    void PropertyDisplayLedOff(TBool& aDisplayLedOff) const;
    void PropertyTerminalInputCode(TUint& aTerminalInputCode) const;
    void PropertyTerminalInputName(Brhz& aTerminalInputName) const;
    void PropertyDisplayPixels(Brh& aDisplayPixels) const;
private:
    void DisplayBrightnessPropertyChanged();
    void DisplayBrightnessAutoPropertyChanged();
    void InfraredCommandsPropertyChanged();
    void InfraredTerminalCommandsPropertyChanged();
    void DisplayUpsideDownPropertyChanged();
    void DisplayScrollTextPropertyChanged();
    void DisplaySleepPropertyChanged();
    void DisplayLedOffPropertyChanged();
    void TerminalInputCodePropertyChanged();
    void TerminalInputNamePropertyChanged();
    void DisplayPixelsPropertyChanged();
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionDisplayTestPattern;
    Action* iActionDisplayFill;
    Action* iActionDisplayClear;
    Action* iActionSetTestModeEnabled;
    Action* iActionSimulateInfraredInput;
    Action* iActionSimulateButtonInput;
    Action* iActionSimulateLightSensor;
    Action* iActionGetLightSensorData;
    Action* iActionSetDisplayBrightness;
    Action* iActionSetDisplayBrightnessAuto;
    Action* iActionSetInfraredCommands;
    Action* iActionInfraredCommands;
    Action* iActionSetInfraredTerminalCommands;
    Action* iActionInfraredTerminalCommands;
    Action* iActionDisplayBrightness;
    Action* iActionDisplayBrightnessAuto;
    Action* iActionDisplayUpsideDown;
    Action* iActionSetDisplayUpsideDown;
    Action* iActionSetDisplayScrollText;
    Action* iActionDisplayScrollText;
    Action* iActionSetDisplaySleep;
    Action* iActionDisplaySleep;
    Action* iActionSetDisplayLedOff;
    Action* iActionDisplayLedOff;
    PropertyUint* iDisplayBrightness;
    PropertyBool* iDisplayBrightnessAuto;
    PropertyString* iInfraredCommands;
    PropertyString* iInfraredTerminalCommands;
    PropertyBool* iDisplayUpsideDown;
    PropertyBool* iDisplayScrollText;
    PropertyBool* iDisplaySleep;
    PropertyBool* iDisplayLedOff;
    PropertyUint* iTerminalInputCode;
    PropertyString* iTerminalInputName;
    PropertyBinary* iDisplayPixels;
    Functor iDisplayBrightnessChanged;
    Functor iDisplayBrightnessAutoChanged;
    Functor iInfraredCommandsChanged;
    Functor iInfraredTerminalCommandsChanged;
    Functor iDisplayUpsideDownChanged;
    Functor iDisplayScrollTextChanged;
    Functor iDisplaySleepChanged;
    Functor iDisplayLedOffChanged;
    Functor iTerminalInputCodeChanged;
    Functor iTerminalInputNameChanged;
    Functor iDisplayPixelsChanged;
};


class SyncDisplayTestPatternLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncDisplayTestPatternLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncDisplayTestPatternLinnCoUkUi2C::SyncDisplayTestPatternLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncDisplayTestPatternLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayTestPattern(aAsync);
}


class SyncDisplayFillLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncDisplayFillLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncDisplayFillLinnCoUkUi2C::SyncDisplayFillLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncDisplayFillLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayFill(aAsync);
}


class SyncDisplayClearLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncDisplayClearLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncDisplayClearLinnCoUkUi2C::SyncDisplayClearLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncDisplayClearLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayClear(aAsync);
}


class SyncSetTestModeEnabledLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncSetTestModeEnabledLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncSetTestModeEnabledLinnCoUkUi2C::SyncSetTestModeEnabledLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetTestModeEnabledLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetTestModeEnabled(aAsync);
}


class SyncSimulateInfraredInputLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncSimulateInfraredInputLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncSimulateInfraredInputLinnCoUkUi2C::SyncSimulateInfraredInputLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncSimulateInfraredInputLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSimulateInfraredInput(aAsync);
}


class SyncSimulateButtonInputLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncSimulateButtonInputLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncSimulateButtonInputLinnCoUkUi2C::SyncSimulateButtonInputLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncSimulateButtonInputLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSimulateButtonInput(aAsync);
}


class SyncSimulateLightSensorLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncSimulateLightSensorLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncSimulateLightSensorLinnCoUkUi2C::SyncSimulateLightSensorLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncSimulateLightSensorLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSimulateLightSensor(aAsync);
}


class SyncGetLightSensorDataLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncGetLightSensorDataLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TUint& aaLightLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
    TUint& iaLightLevel;
};

SyncGetLightSensorDataLinnCoUkUi2C::SyncGetLightSensorDataLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TUint& aaLightLevel)
    : iService(aProxy)
    , iaLightLevel(aaLightLevel)
{
}

void SyncGetLightSensorDataLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLightSensorData(aAsync, iaLightLevel);
}


class SyncSetDisplayBrightnessLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncSetDisplayBrightnessLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncSetDisplayBrightnessLinnCoUkUi2C::SyncSetDisplayBrightnessLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetDisplayBrightnessLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayBrightness(aAsync);
}


class SyncSetDisplayBrightnessAutoLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncSetDisplayBrightnessAutoLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncSetDisplayBrightnessAutoLinnCoUkUi2C::SyncSetDisplayBrightnessAutoLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetDisplayBrightnessAutoLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayBrightnessAuto(aAsync);
}


class SyncSetInfraredCommandsLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncSetInfraredCommandsLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncSetInfraredCommandsLinnCoUkUi2C::SyncSetInfraredCommandsLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetInfraredCommandsLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetInfraredCommands(aAsync);
}


class SyncInfraredCommandsLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncInfraredCommandsLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, Brh& aaCommands);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
    Brh& iaCommands;
};

SyncInfraredCommandsLinnCoUkUi2C::SyncInfraredCommandsLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, Brh& aaCommands)
    : iService(aProxy)
    , iaCommands(aaCommands)
{
}

void SyncInfraredCommandsLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndInfraredCommands(aAsync, iaCommands);
}


class SyncSetInfraredTerminalCommandsLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncSetInfraredTerminalCommandsLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncSetInfraredTerminalCommandsLinnCoUkUi2C::SyncSetInfraredTerminalCommandsLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetInfraredTerminalCommandsLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetInfraredTerminalCommands(aAsync);
}


class SyncInfraredTerminalCommandsLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncInfraredTerminalCommandsLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, Brh& aaCommands);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
    Brh& iaCommands;
};

SyncInfraredTerminalCommandsLinnCoUkUi2C::SyncInfraredTerminalCommandsLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, Brh& aaCommands)
    : iService(aProxy)
    , iaCommands(aaCommands)
{
}

void SyncInfraredTerminalCommandsLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndInfraredTerminalCommands(aAsync, iaCommands);
}


class SyncDisplayBrightnessLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncDisplayBrightnessLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TUint& aaBrightness);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
    TUint& iaBrightness;
};

SyncDisplayBrightnessLinnCoUkUi2C::SyncDisplayBrightnessLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TUint& aaBrightness)
    : iService(aProxy)
    , iaBrightness(aaBrightness)
{
}

void SyncDisplayBrightnessLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayBrightness(aAsync, iaBrightness);
}


class SyncDisplayBrightnessAutoLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncDisplayBrightnessAutoLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TBool& aaBrightnessAuto);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
    TBool& iaBrightnessAuto;
};

SyncDisplayBrightnessAutoLinnCoUkUi2C::SyncDisplayBrightnessAutoLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TBool& aaBrightnessAuto)
    : iService(aProxy)
    , iaBrightnessAuto(aaBrightnessAuto)
{
}

void SyncDisplayBrightnessAutoLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayBrightnessAuto(aAsync, iaBrightnessAuto);
}


class SyncDisplayUpsideDownLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncDisplayUpsideDownLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TBool& aaUpsideDown);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
    TBool& iaUpsideDown;
};

SyncDisplayUpsideDownLinnCoUkUi2C::SyncDisplayUpsideDownLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TBool& aaUpsideDown)
    : iService(aProxy)
    , iaUpsideDown(aaUpsideDown)
{
}

void SyncDisplayUpsideDownLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayUpsideDown(aAsync, iaUpsideDown);
}


class SyncSetDisplayUpsideDownLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncSetDisplayUpsideDownLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncSetDisplayUpsideDownLinnCoUkUi2C::SyncSetDisplayUpsideDownLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetDisplayUpsideDownLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayUpsideDown(aAsync);
}


class SyncSetDisplayScrollTextLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncSetDisplayScrollTextLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncSetDisplayScrollTextLinnCoUkUi2C::SyncSetDisplayScrollTextLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetDisplayScrollTextLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayScrollText(aAsync);
}


class SyncDisplayScrollTextLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncDisplayScrollTextLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TBool& aaDisplayScrollTextEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
    TBool& iaDisplayScrollTextEnabled;
};

SyncDisplayScrollTextLinnCoUkUi2C::SyncDisplayScrollTextLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TBool& aaDisplayScrollTextEnabled)
    : iService(aProxy)
    , iaDisplayScrollTextEnabled(aaDisplayScrollTextEnabled)
{
}

void SyncDisplayScrollTextLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayScrollText(aAsync, iaDisplayScrollTextEnabled);
}


class SyncSetDisplaySleepLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncSetDisplaySleepLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncSetDisplaySleepLinnCoUkUi2C::SyncSetDisplaySleepLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetDisplaySleepLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplaySleep(aAsync);
}


class SyncDisplaySleepLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncDisplaySleepLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TBool& aaEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
    TBool& iaEnabled;
};

SyncDisplaySleepLinnCoUkUi2C::SyncDisplaySleepLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TBool& aaEnabled)
    : iService(aProxy)
    , iaEnabled(aaEnabled)
{
}

void SyncDisplaySleepLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplaySleep(aAsync, iaEnabled);
}


class SyncSetDisplayLedOffLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncSetDisplayLedOffLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
};

SyncSetDisplayLedOffLinnCoUkUi2C::SyncSetDisplayLedOffLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetDisplayLedOffLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayLedOff(aAsync);
}


class SyncDisplayLedOffLinnCoUkUi2C : public SyncProxyAction
{
public:
    SyncDisplayLedOffLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TBool& aaOff);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2C& iService;
    TBool& iaOff;
};

SyncDisplayLedOffLinnCoUkUi2C::SyncDisplayLedOffLinnCoUkUi2C(CpProxyLinnCoUkUi2C& aProxy, TBool& aaOff)
    : iService(aProxy)
    , iaOff(aaOff)
{
}

void SyncDisplayLedOffLinnCoUkUi2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayLedOff(aAsync, iaOff);
}

CpProxyLinnCoUkUi2C::CpProxyLinnCoUkUi2C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Ui", 2, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
    Zapp::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionDisplayTestPattern = new Action("DisplayTestPattern");
    param = new Zapp::ParameterInt("aTestPattern", 0, 6);
    iActionDisplayTestPattern->AddInputParameter(param);

    iActionDisplayFill = new Action("DisplayFill");

    iActionDisplayClear = new Action("DisplayClear");

    iActionSetTestModeEnabled = new Action("SetTestModeEnabled");
    param = new Zapp::ParameterBool("aEnabled");
    iActionSetTestModeEnabled->AddInputParameter(param);

    iActionSimulateInfraredInput = new Action("SimulateInfraredInput");
    param = new Zapp::ParameterUint("aCode");
    iActionSimulateInfraredInput->AddInputParameter(param);

    iActionSimulateButtonInput = new Action("SimulateButtonInput");
    param = new Zapp::ParameterUint("aCode");
    iActionSimulateButtonInput->AddInputParameter(param);

    iActionSimulateLightSensor = new Action("SimulateLightSensor");
    param = new Zapp::ParameterUint("aLightLevel");
    iActionSimulateLightSensor->AddInputParameter(param);

    iActionGetLightSensorData = new Action("GetLightSensorData");
    param = new Zapp::ParameterUint("aLightLevel");
    iActionGetLightSensorData->AddOutputParameter(param);

    iActionSetDisplayBrightness = new Action("SetDisplayBrightness");
    param = new Zapp::ParameterUint("aBrightness");
    iActionSetDisplayBrightness->AddInputParameter(param);

    iActionSetDisplayBrightnessAuto = new Action("SetDisplayBrightnessAuto");
    param = new Zapp::ParameterBool("aBrightnessAuto");
    iActionSetDisplayBrightnessAuto->AddInputParameter(param);

    iActionSetInfraredCommands = new Action("SetInfraredCommands");
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"All";
    allowedValues[index++] = (TChar*)"Cd";
    allowedValues[index++] = (TChar*)"Dvd";
    param = new Zapp::ParameterString("aCommands", allowedValues, 4);
    iActionSetInfraredCommands->AddInputParameter(param);
    delete[] allowedValues;

    iActionInfraredCommands = new Action("InfraredCommands");
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"All";
    allowedValues[index++] = (TChar*)"Cd";
    allowedValues[index++] = (TChar*)"Dvd";
    param = new Zapp::ParameterString("aCommands", allowedValues, 4);
    iActionInfraredCommands->AddOutputParameter(param);
    delete[] allowedValues;

    iActionSetInfraredTerminalCommands = new Action("SetInfraredTerminalCommands");
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"All";
    allowedValues[index++] = (TChar*)"Cd";
    allowedValues[index++] = (TChar*)"Dvd";
    param = new Zapp::ParameterString("aCommands", allowedValues, 4);
    iActionSetInfraredTerminalCommands->AddInputParameter(param);
    delete[] allowedValues;

    iActionInfraredTerminalCommands = new Action("InfraredTerminalCommands");
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"All";
    allowedValues[index++] = (TChar*)"Cd";
    allowedValues[index++] = (TChar*)"Dvd";
    param = new Zapp::ParameterString("aCommands", allowedValues, 4);
    iActionInfraredTerminalCommands->AddOutputParameter(param);
    delete[] allowedValues;

    iActionDisplayBrightness = new Action("DisplayBrightness");
    param = new Zapp::ParameterUint("aBrightness");
    iActionDisplayBrightness->AddOutputParameter(param);

    iActionDisplayBrightnessAuto = new Action("DisplayBrightnessAuto");
    param = new Zapp::ParameterBool("aBrightnessAuto");
    iActionDisplayBrightnessAuto->AddOutputParameter(param);

    iActionDisplayUpsideDown = new Action("DisplayUpsideDown");
    param = new Zapp::ParameterBool("aUpsideDown");
    iActionDisplayUpsideDown->AddOutputParameter(param);

    iActionSetDisplayUpsideDown = new Action("SetDisplayUpsideDown");
    param = new Zapp::ParameterBool("aUpsideDown");
    iActionSetDisplayUpsideDown->AddInputParameter(param);

    iActionSetDisplayScrollText = new Action("SetDisplayScrollText");
    param = new Zapp::ParameterBool("aDisplayScrollText");
    iActionSetDisplayScrollText->AddInputParameter(param);

    iActionDisplayScrollText = new Action("DisplayScrollText");
    param = new Zapp::ParameterBool("aDisplayScrollTextEnabled");
    iActionDisplayScrollText->AddOutputParameter(param);

    iActionSetDisplaySleep = new Action("SetDisplaySleep");
    param = new Zapp::ParameterBool("aEnabled");
    iActionSetDisplaySleep->AddInputParameter(param);

    iActionDisplaySleep = new Action("DisplaySleep");
    param = new Zapp::ParameterBool("aEnabled");
    iActionDisplaySleep->AddOutputParameter(param);

    iActionSetDisplayLedOff = new Action("SetDisplayLedOff");
    param = new Zapp::ParameterBool("aOff");
    iActionSetDisplayLedOff->AddInputParameter(param);

    iActionDisplayLedOff = new Action("DisplayLedOff");
    param = new Zapp::ParameterBool("aOff");
    iActionDisplayLedOff->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2C::DisplayBrightnessPropertyChanged);
    iDisplayBrightness = new PropertyUint("DisplayBrightness", functor);
    AddProperty(iDisplayBrightness);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2C::DisplayBrightnessAutoPropertyChanged);
    iDisplayBrightnessAuto = new PropertyBool("DisplayBrightnessAuto", functor);
    AddProperty(iDisplayBrightnessAuto);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2C::InfraredCommandsPropertyChanged);
    iInfraredCommands = new PropertyString("InfraredCommands", functor);
    AddProperty(iInfraredCommands);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2C::InfraredTerminalCommandsPropertyChanged);
    iInfraredTerminalCommands = new PropertyString("InfraredTerminalCommands", functor);
    AddProperty(iInfraredTerminalCommands);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2C::DisplayUpsideDownPropertyChanged);
    iDisplayUpsideDown = new PropertyBool("DisplayUpsideDown", functor);
    AddProperty(iDisplayUpsideDown);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2C::DisplayScrollTextPropertyChanged);
    iDisplayScrollText = new PropertyBool("DisplayScrollText", functor);
    AddProperty(iDisplayScrollText);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2C::DisplaySleepPropertyChanged);
    iDisplaySleep = new PropertyBool("DisplaySleep", functor);
    AddProperty(iDisplaySleep);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2C::DisplayLedOffPropertyChanged);
    iDisplayLedOff = new PropertyBool("DisplayLedOff", functor);
    AddProperty(iDisplayLedOff);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2C::TerminalInputCodePropertyChanged);
    iTerminalInputCode = new PropertyUint("TerminalInputCode", functor);
    AddProperty(iTerminalInputCode);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2C::TerminalInputNamePropertyChanged);
    iTerminalInputName = new PropertyString("TerminalInputName", functor);
    AddProperty(iTerminalInputName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2C::DisplayPixelsPropertyChanged);
    iDisplayPixels = new PropertyBinary("DisplayPixels", functor);
    AddProperty(iDisplayPixels);
}

CpProxyLinnCoUkUi2C::~CpProxyLinnCoUkUi2C()
{
    delete iActionDisplayTestPattern;
    delete iActionDisplayFill;
    delete iActionDisplayClear;
    delete iActionSetTestModeEnabled;
    delete iActionSimulateInfraredInput;
    delete iActionSimulateButtonInput;
    delete iActionSimulateLightSensor;
    delete iActionGetLightSensorData;
    delete iActionSetDisplayBrightness;
    delete iActionSetDisplayBrightnessAuto;
    delete iActionSetInfraredCommands;
    delete iActionInfraredCommands;
    delete iActionSetInfraredTerminalCommands;
    delete iActionInfraredTerminalCommands;
    delete iActionDisplayBrightness;
    delete iActionDisplayBrightnessAuto;
    delete iActionDisplayUpsideDown;
    delete iActionSetDisplayUpsideDown;
    delete iActionSetDisplayScrollText;
    delete iActionDisplayScrollText;
    delete iActionSetDisplaySleep;
    delete iActionDisplaySleep;
    delete iActionSetDisplayLedOff;
    delete iActionDisplayLedOff;
}

void CpProxyLinnCoUkUi2C::SyncDisplayTestPattern(TInt aaTestPattern)
{
    SyncDisplayTestPatternLinnCoUkUi2C sync(*this);
    BeginDisplayTestPattern(aaTestPattern, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginDisplayTestPattern(TInt aaTestPattern, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDisplayTestPattern, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDisplayTestPattern->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaTestPattern));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndDisplayTestPattern(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayTestPattern"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncDisplayFill()
{
    SyncDisplayFillLinnCoUkUi2C sync(*this);
    BeginDisplayFill(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginDisplayFill(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDisplayFill, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndDisplayFill(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayFill"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncDisplayClear()
{
    SyncDisplayClearLinnCoUkUi2C sync(*this);
    BeginDisplayClear(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginDisplayClear(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDisplayClear, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndDisplayClear(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayClear"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncSetTestModeEnabled(TBool aaEnabled)
{
    SyncSetTestModeEnabledLinnCoUkUi2C sync(*this);
    BeginSetTestModeEnabled(aaEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginSetTestModeEnabled(TBool aaEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetTestModeEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetTestModeEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaEnabled));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndSetTestModeEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetTestModeEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncSimulateInfraredInput(TUint aaCode)
{
    SyncSimulateInfraredInputLinnCoUkUi2C sync(*this);
    BeginSimulateInfraredInput(aaCode, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginSimulateInfraredInput(TUint aaCode, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSimulateInfraredInput, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSimulateInfraredInput->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaCode));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndSimulateInfraredInput(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SimulateInfraredInput"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncSimulateButtonInput(TUint aaCode)
{
    SyncSimulateButtonInputLinnCoUkUi2C sync(*this);
    BeginSimulateButtonInput(aaCode, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginSimulateButtonInput(TUint aaCode, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSimulateButtonInput, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSimulateButtonInput->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaCode));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndSimulateButtonInput(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SimulateButtonInput"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncSimulateLightSensor(TUint aaLightLevel)
{
    SyncSimulateLightSensorLinnCoUkUi2C sync(*this);
    BeginSimulateLightSensor(aaLightLevel, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginSimulateLightSensor(TUint aaLightLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSimulateLightSensor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSimulateLightSensor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaLightLevel));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndSimulateLightSensor(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SimulateLightSensor"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncGetLightSensorData(TUint& aaLightLevel)
{
    SyncGetLightSensorDataLinnCoUkUi2C sync(*this, aaLightLevel);
    BeginGetLightSensorData(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginGetLightSensorData(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetLightSensorData, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLightSensorData->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndGetLightSensorData(IAsync& aAsync, TUint& aaLightLevel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetLightSensorData"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaLightLevel = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkUi2C::SyncSetDisplayBrightness(TUint aaBrightness)
{
    SyncSetDisplayBrightnessLinnCoUkUi2C sync(*this);
    BeginSetDisplayBrightness(aaBrightness, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginSetDisplayBrightness(TUint aaBrightness, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetDisplayBrightness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayBrightness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaBrightness));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndSetDisplayBrightness(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayBrightness"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncSetDisplayBrightnessAuto(TBool aaBrightnessAuto)
{
    SyncSetDisplayBrightnessAutoLinnCoUkUi2C sync(*this);
    BeginSetDisplayBrightnessAuto(aaBrightnessAuto, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginSetDisplayBrightnessAuto(TBool aaBrightnessAuto, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetDisplayBrightnessAuto, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayBrightnessAuto->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaBrightnessAuto));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndSetDisplayBrightnessAuto(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayBrightnessAuto"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncSetInfraredCommands(const Brx& aaCommands)
{
    SyncSetInfraredCommandsLinnCoUkUi2C sync(*this);
    BeginSetInfraredCommands(aaCommands, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginSetInfraredCommands(const Brx& aaCommands, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetInfraredCommands, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetInfraredCommands->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaCommands));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndSetInfraredCommands(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetInfraredCommands"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncInfraredCommands(Brh& aaCommands)
{
    SyncInfraredCommandsLinnCoUkUi2C sync(*this, aaCommands);
    BeginInfraredCommands(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginInfraredCommands(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionInfraredCommands, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInfraredCommands->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndInfraredCommands(IAsync& aAsync, Brh& aaCommands)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("InfraredCommands"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaCommands);
}

void CpProxyLinnCoUkUi2C::SyncSetInfraredTerminalCommands(const Brx& aaCommands)
{
    SyncSetInfraredTerminalCommandsLinnCoUkUi2C sync(*this);
    BeginSetInfraredTerminalCommands(aaCommands, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginSetInfraredTerminalCommands(const Brx& aaCommands, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetInfraredTerminalCommands, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetInfraredTerminalCommands->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaCommands));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndSetInfraredTerminalCommands(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetInfraredTerminalCommands"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncInfraredTerminalCommands(Brh& aaCommands)
{
    SyncInfraredTerminalCommandsLinnCoUkUi2C sync(*this, aaCommands);
    BeginInfraredTerminalCommands(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginInfraredTerminalCommands(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionInfraredTerminalCommands, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInfraredTerminalCommands->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndInfraredTerminalCommands(IAsync& aAsync, Brh& aaCommands)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("InfraredTerminalCommands"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaCommands);
}

void CpProxyLinnCoUkUi2C::SyncDisplayBrightness(TUint& aaBrightness)
{
    SyncDisplayBrightnessLinnCoUkUi2C sync(*this, aaBrightness);
    BeginDisplayBrightness(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginDisplayBrightness(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDisplayBrightness, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayBrightness->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndDisplayBrightness(IAsync& aAsync, TUint& aaBrightness)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayBrightness"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaBrightness = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkUi2C::SyncDisplayBrightnessAuto(TBool& aaBrightnessAuto)
{
    SyncDisplayBrightnessAutoLinnCoUkUi2C sync(*this, aaBrightnessAuto);
    BeginDisplayBrightnessAuto(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginDisplayBrightnessAuto(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDisplayBrightnessAuto, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayBrightnessAuto->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndDisplayBrightnessAuto(IAsync& aAsync, TBool& aaBrightnessAuto)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayBrightnessAuto"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaBrightnessAuto = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkUi2C::SyncDisplayUpsideDown(TBool& aaUpsideDown)
{
    SyncDisplayUpsideDownLinnCoUkUi2C sync(*this, aaUpsideDown);
    BeginDisplayUpsideDown(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginDisplayUpsideDown(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDisplayUpsideDown, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayUpsideDown->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndDisplayUpsideDown(IAsync& aAsync, TBool& aaUpsideDown)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayUpsideDown"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaUpsideDown = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkUi2C::SyncSetDisplayUpsideDown(TBool aaUpsideDown)
{
    SyncSetDisplayUpsideDownLinnCoUkUi2C sync(*this);
    BeginSetDisplayUpsideDown(aaUpsideDown, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginSetDisplayUpsideDown(TBool aaUpsideDown, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetDisplayUpsideDown, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayUpsideDown->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaUpsideDown));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndSetDisplayUpsideDown(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayUpsideDown"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncSetDisplayScrollText(TBool aaDisplayScrollText)
{
    SyncSetDisplayScrollTextLinnCoUkUi2C sync(*this);
    BeginSetDisplayScrollText(aaDisplayScrollText, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginSetDisplayScrollText(TBool aaDisplayScrollText, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetDisplayScrollText, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayScrollText->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaDisplayScrollText));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndSetDisplayScrollText(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayScrollText"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncDisplayScrollText(TBool& aaDisplayScrollTextEnabled)
{
    SyncDisplayScrollTextLinnCoUkUi2C sync(*this, aaDisplayScrollTextEnabled);
    BeginDisplayScrollText(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginDisplayScrollText(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDisplayScrollText, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayScrollText->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndDisplayScrollText(IAsync& aAsync, TBool& aaDisplayScrollTextEnabled)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayScrollText"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaDisplayScrollTextEnabled = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkUi2C::SyncSetDisplaySleep(TBool aaEnabled)
{
    SyncSetDisplaySleepLinnCoUkUi2C sync(*this);
    BeginSetDisplaySleep(aaEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginSetDisplaySleep(TBool aaEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetDisplaySleep, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplaySleep->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaEnabled));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndSetDisplaySleep(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplaySleep"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncDisplaySleep(TBool& aaEnabled)
{
    SyncDisplaySleepLinnCoUkUi2C sync(*this, aaEnabled);
    BeginDisplaySleep(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginDisplaySleep(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDisplaySleep, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplaySleep->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndDisplaySleep(IAsync& aAsync, TBool& aaEnabled)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplaySleep"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaEnabled = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkUi2C::SyncSetDisplayLedOff(TBool aaOff)
{
    SyncSetDisplayLedOffLinnCoUkUi2C sync(*this);
    BeginSetDisplayLedOff(aaOff, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginSetDisplayLedOff(TBool aaOff, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetDisplayLedOff, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayLedOff->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaOff));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndSetDisplayLedOff(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayLedOff"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2C::SyncDisplayLedOff(TBool& aaOff)
{
    SyncDisplayLedOffLinnCoUkUi2C sync(*this, aaOff);
    BeginDisplayLedOff(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2C::BeginDisplayLedOff(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDisplayLedOff, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayLedOff->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkUi2C::EndDisplayLedOff(IAsync& aAsync, TBool& aaOff)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayLedOff"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaOff = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkUi2C::SetPropertyDisplayBrightnessChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDisplayBrightnessChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkUi2C::SetPropertyDisplayBrightnessAutoChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDisplayBrightnessAutoChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkUi2C::SetPropertyInfraredCommandsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iInfraredCommandsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkUi2C::SetPropertyInfraredTerminalCommandsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iInfraredTerminalCommandsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkUi2C::SetPropertyDisplayUpsideDownChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDisplayUpsideDownChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkUi2C::SetPropertyDisplayScrollTextChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDisplayScrollTextChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkUi2C::SetPropertyDisplaySleepChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDisplaySleepChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkUi2C::SetPropertyDisplayLedOffChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDisplayLedOffChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkUi2C::SetPropertyTerminalInputCodeChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTerminalInputCodeChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkUi2C::SetPropertyTerminalInputNameChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTerminalInputNameChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkUi2C::SetPropertyDisplayPixelsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDisplayPixelsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkUi2C::PropertyDisplayBrightness(TUint& aDisplayBrightness) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aDisplayBrightness = iDisplayBrightness->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkUi2C::PropertyDisplayBrightnessAuto(TBool& aDisplayBrightnessAuto) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aDisplayBrightnessAuto = iDisplayBrightnessAuto->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkUi2C::PropertyInfraredCommands(Brhz& aInfraredCommands) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aInfraredCommands.Set(iInfraredCommands->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkUi2C::PropertyInfraredTerminalCommands(Brhz& aInfraredTerminalCommands) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aInfraredTerminalCommands.Set(iInfraredTerminalCommands->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkUi2C::PropertyDisplayUpsideDown(TBool& aDisplayUpsideDown) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aDisplayUpsideDown = iDisplayUpsideDown->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkUi2C::PropertyDisplayScrollText(TBool& aDisplayScrollText) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aDisplayScrollText = iDisplayScrollText->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkUi2C::PropertyDisplaySleep(TBool& aDisplaySleep) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aDisplaySleep = iDisplaySleep->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkUi2C::PropertyDisplayLedOff(TBool& aDisplayLedOff) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aDisplayLedOff = iDisplayLedOff->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkUi2C::PropertyTerminalInputCode(TUint& aTerminalInputCode) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aTerminalInputCode = iTerminalInputCode->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkUi2C::PropertyTerminalInputName(Brhz& aTerminalInputName) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aTerminalInputName.Set(iTerminalInputName->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkUi2C::PropertyDisplayPixels(Brh& aDisplayPixels) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aDisplayPixels.Set(iDisplayPixels->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkUi2C::DisplayBrightnessPropertyChanged()
{
    ReportEvent(iDisplayBrightnessChanged);
}

void CpProxyLinnCoUkUi2C::DisplayBrightnessAutoPropertyChanged()
{
    ReportEvent(iDisplayBrightnessAutoChanged);
}

void CpProxyLinnCoUkUi2C::InfraredCommandsPropertyChanged()
{
    ReportEvent(iInfraredCommandsChanged);
}

void CpProxyLinnCoUkUi2C::InfraredTerminalCommandsPropertyChanged()
{
    ReportEvent(iInfraredTerminalCommandsChanged);
}

void CpProxyLinnCoUkUi2C::DisplayUpsideDownPropertyChanged()
{
    ReportEvent(iDisplayUpsideDownChanged);
}

void CpProxyLinnCoUkUi2C::DisplayScrollTextPropertyChanged()
{
    ReportEvent(iDisplayScrollTextChanged);
}

void CpProxyLinnCoUkUi2C::DisplaySleepPropertyChanged()
{
    ReportEvent(iDisplaySleepChanged);
}

void CpProxyLinnCoUkUi2C::DisplayLedOffPropertyChanged()
{
    ReportEvent(iDisplayLedOffChanged);
}

void CpProxyLinnCoUkUi2C::TerminalInputCodePropertyChanged()
{
    ReportEvent(iTerminalInputCodeChanged);
}

void CpProxyLinnCoUkUi2C::TerminalInputNamePropertyChanged()
{
    ReportEvent(iTerminalInputNameChanged);
}

void CpProxyLinnCoUkUi2C::DisplayPixelsPropertyChanged()
{
    ReportEvent(iDisplayPixelsChanged);
}


THandle CpProxyLinnCoUkUi2Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkUi2C(aDevice);
}

void CpProxyLinnCoUkUi2Destroy(THandle aHandle)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkUi2SyncDisplayTestPattern(THandle aHandle, int32_t aaTestPattern)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncDisplayTestPattern(aaTestPattern);
}

void CpProxyLinnCoUkUi2BeginDisplayTestPattern(THandle aHandle, int32_t aaTestPattern, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDisplayTestPattern(aaTestPattern, functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayTestPattern(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDisplayTestPattern(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayFill(THandle aHandle)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncDisplayFill();
}

void CpProxyLinnCoUkUi2BeginDisplayFill(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDisplayFill(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayFill(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDisplayFill(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayClear(THandle aHandle)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncDisplayClear();
}

void CpProxyLinnCoUkUi2BeginDisplayClear(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDisplayClear(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayClear(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDisplayClear(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetTestModeEnabled(THandle aHandle, uint32_t aaEnabled)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetTestModeEnabled((aaEnabled==0? false : true));
}

void CpProxyLinnCoUkUi2BeginSetTestModeEnabled(THandle aHandle, uint32_t aaEnabled, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetTestModeEnabled((aaEnabled==0? false : true), functor);
}

int32_t CpProxyLinnCoUkUi2EndSetTestModeEnabled(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetTestModeEnabled(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSimulateInfraredInput(THandle aHandle, uint32_t aaCode)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSimulateInfraredInput(aaCode);
}

void CpProxyLinnCoUkUi2BeginSimulateInfraredInput(THandle aHandle, uint32_t aaCode, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSimulateInfraredInput(aaCode, functor);
}

int32_t CpProxyLinnCoUkUi2EndSimulateInfraredInput(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSimulateInfraredInput(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSimulateButtonInput(THandle aHandle, uint32_t aaCode)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSimulateButtonInput(aaCode);
}

void CpProxyLinnCoUkUi2BeginSimulateButtonInput(THandle aHandle, uint32_t aaCode, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSimulateButtonInput(aaCode, functor);
}

int32_t CpProxyLinnCoUkUi2EndSimulateButtonInput(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSimulateButtonInput(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSimulateLightSensor(THandle aHandle, uint32_t aaLightLevel)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSimulateLightSensor(aaLightLevel);
}

void CpProxyLinnCoUkUi2BeginSimulateLightSensor(THandle aHandle, uint32_t aaLightLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSimulateLightSensor(aaLightLevel, functor);
}

int32_t CpProxyLinnCoUkUi2EndSimulateLightSensor(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSimulateLightSensor(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncGetLightSensorData(THandle aHandle, uint32_t* aaLightLevel)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetLightSensorData(*aaLightLevel);
}

void CpProxyLinnCoUkUi2BeginGetLightSensorData(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetLightSensorData(functor);
}

int32_t CpProxyLinnCoUkUi2EndGetLightSensorData(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaLightLevel)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetLightSensorData(*async, *aaLightLevel);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetDisplayBrightness(THandle aHandle, uint32_t aaBrightness)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetDisplayBrightness(aaBrightness);
}

void CpProxyLinnCoUkUi2BeginSetDisplayBrightness(THandle aHandle, uint32_t aaBrightness, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetDisplayBrightness(aaBrightness, functor);
}

int32_t CpProxyLinnCoUkUi2EndSetDisplayBrightness(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetDisplayBrightness(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetDisplayBrightnessAuto(THandle aHandle, uint32_t aaBrightnessAuto)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetDisplayBrightnessAuto((aaBrightnessAuto==0? false : true));
}

void CpProxyLinnCoUkUi2BeginSetDisplayBrightnessAuto(THandle aHandle, uint32_t aaBrightnessAuto, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetDisplayBrightnessAuto((aaBrightnessAuto==0? false : true), functor);
}

int32_t CpProxyLinnCoUkUi2EndSetDisplayBrightnessAuto(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetDisplayBrightnessAuto(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetInfraredCommands(THandle aHandle, const char* aaCommands)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCommands(aaCommands);
    proxyC->SyncSetInfraredCommands(buf_aaCommands);
}

void CpProxyLinnCoUkUi2BeginSetInfraredCommands(THandle aHandle, const char* aaCommands, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCommands(aaCommands);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetInfraredCommands(buf_aaCommands, functor);
}

int32_t CpProxyLinnCoUkUi2EndSetInfraredCommands(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetInfraredCommands(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncInfraredCommands(THandle aHandle, char** aaCommands)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCommands;
    proxyC->SyncInfraredCommands(buf_aaCommands);
    *aaCommands = buf_aaCommands.Extract();
}

void CpProxyLinnCoUkUi2BeginInfraredCommands(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginInfraredCommands(functor);
}

int32_t CpProxyLinnCoUkUi2EndInfraredCommands(THandle aHandle, ZappHandleAsync aAsync, char** aaCommands)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaCommands;
    *aaCommands = NULL;
    try {
        proxyC->EndInfraredCommands(*async, buf_aaCommands);
        *aaCommands = buf_aaCommands.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetInfraredTerminalCommands(THandle aHandle, const char* aaCommands)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCommands(aaCommands);
    proxyC->SyncSetInfraredTerminalCommands(buf_aaCommands);
}

void CpProxyLinnCoUkUi2BeginSetInfraredTerminalCommands(THandle aHandle, const char* aaCommands, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCommands(aaCommands);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetInfraredTerminalCommands(buf_aaCommands, functor);
}

int32_t CpProxyLinnCoUkUi2EndSetInfraredTerminalCommands(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetInfraredTerminalCommands(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncInfraredTerminalCommands(THandle aHandle, char** aaCommands)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCommands;
    proxyC->SyncInfraredTerminalCommands(buf_aaCommands);
    *aaCommands = buf_aaCommands.Extract();
}

void CpProxyLinnCoUkUi2BeginInfraredTerminalCommands(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginInfraredTerminalCommands(functor);
}

int32_t CpProxyLinnCoUkUi2EndInfraredTerminalCommands(THandle aHandle, ZappHandleAsync aAsync, char** aaCommands)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaCommands;
    *aaCommands = NULL;
    try {
        proxyC->EndInfraredTerminalCommands(*async, buf_aaCommands);
        *aaCommands = buf_aaCommands.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayBrightness(THandle aHandle, uint32_t* aaBrightness)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncDisplayBrightness(*aaBrightness);
}

void CpProxyLinnCoUkUi2BeginDisplayBrightness(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDisplayBrightness(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayBrightness(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaBrightness)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDisplayBrightness(*async, *aaBrightness);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayBrightnessAuto(THandle aHandle, uint32_t* aaBrightnessAuto)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaBrightnessAuto = 0;
    proxyC->SyncDisplayBrightnessAuto(*(TBool*)aaBrightnessAuto);
}

void CpProxyLinnCoUkUi2BeginDisplayBrightnessAuto(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDisplayBrightnessAuto(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayBrightnessAuto(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaBrightnessAuto)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaBrightnessAuto = 0;
    try {
        proxyC->EndDisplayBrightnessAuto(*async, *(TBool*)aaBrightnessAuto);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayUpsideDown(THandle aHandle, uint32_t* aaUpsideDown)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaUpsideDown = 0;
    proxyC->SyncDisplayUpsideDown(*(TBool*)aaUpsideDown);
}

void CpProxyLinnCoUkUi2BeginDisplayUpsideDown(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDisplayUpsideDown(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayUpsideDown(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaUpsideDown)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaUpsideDown = 0;
    try {
        proxyC->EndDisplayUpsideDown(*async, *(TBool*)aaUpsideDown);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetDisplayUpsideDown(THandle aHandle, uint32_t aaUpsideDown)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetDisplayUpsideDown((aaUpsideDown==0? false : true));
}

void CpProxyLinnCoUkUi2BeginSetDisplayUpsideDown(THandle aHandle, uint32_t aaUpsideDown, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetDisplayUpsideDown((aaUpsideDown==0? false : true), functor);
}

int32_t CpProxyLinnCoUkUi2EndSetDisplayUpsideDown(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetDisplayUpsideDown(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetDisplayScrollText(THandle aHandle, uint32_t aaDisplayScrollText)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetDisplayScrollText((aaDisplayScrollText==0? false : true));
}

void CpProxyLinnCoUkUi2BeginSetDisplayScrollText(THandle aHandle, uint32_t aaDisplayScrollText, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetDisplayScrollText((aaDisplayScrollText==0? false : true), functor);
}

int32_t CpProxyLinnCoUkUi2EndSetDisplayScrollText(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetDisplayScrollText(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayScrollText(THandle aHandle, uint32_t* aaDisplayScrollTextEnabled)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaDisplayScrollTextEnabled = 0;
    proxyC->SyncDisplayScrollText(*(TBool*)aaDisplayScrollTextEnabled);
}

void CpProxyLinnCoUkUi2BeginDisplayScrollText(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDisplayScrollText(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayScrollText(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaDisplayScrollTextEnabled)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaDisplayScrollTextEnabled = 0;
    try {
        proxyC->EndDisplayScrollText(*async, *(TBool*)aaDisplayScrollTextEnabled);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetDisplaySleep(THandle aHandle, uint32_t aaEnabled)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetDisplaySleep((aaEnabled==0? false : true));
}

void CpProxyLinnCoUkUi2BeginSetDisplaySleep(THandle aHandle, uint32_t aaEnabled, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetDisplaySleep((aaEnabled==0? false : true), functor);
}

int32_t CpProxyLinnCoUkUi2EndSetDisplaySleep(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetDisplaySleep(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplaySleep(THandle aHandle, uint32_t* aaEnabled)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaEnabled = 0;
    proxyC->SyncDisplaySleep(*(TBool*)aaEnabled);
}

void CpProxyLinnCoUkUi2BeginDisplaySleep(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDisplaySleep(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplaySleep(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaEnabled)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaEnabled = 0;
    try {
        proxyC->EndDisplaySleep(*async, *(TBool*)aaEnabled);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetDisplayLedOff(THandle aHandle, uint32_t aaOff)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetDisplayLedOff((aaOff==0? false : true));
}

void CpProxyLinnCoUkUi2BeginSetDisplayLedOff(THandle aHandle, uint32_t aaOff, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetDisplayLedOff((aaOff==0? false : true), functor);
}

int32_t CpProxyLinnCoUkUi2EndSetDisplayLedOff(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetDisplayLedOff(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayLedOff(THandle aHandle, uint32_t* aaOff)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaOff = 0;
    proxyC->SyncDisplayLedOff(*(TBool*)aaOff);
}

void CpProxyLinnCoUkUi2BeginDisplayLedOff(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDisplayLedOff(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayLedOff(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaOff)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaOff = 0;
    try {
        proxyC->EndDisplayLedOff(*async, *(TBool*)aaOff);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SetPropertyDisplayBrightnessChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDisplayBrightnessChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyDisplayBrightnessAutoChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDisplayBrightnessAutoChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyInfraredCommandsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyInfraredCommandsChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyInfraredTerminalCommandsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyInfraredTerminalCommandsChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyDisplayUpsideDownChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDisplayUpsideDownChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyDisplayScrollTextChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDisplayScrollTextChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyDisplaySleepChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDisplaySleepChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyDisplayLedOffChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDisplayLedOffChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyTerminalInputCodeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTerminalInputCodeChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyTerminalInputNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTerminalInputNameChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyDisplayPixelsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDisplayPixelsChanged(functor);
}

void CpProxyLinnCoUkUi2PropertyDisplayBrightness(THandle aHandle, uint32_t* aDisplayBrightness)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyDisplayBrightness(*aDisplayBrightness);
}

void CpProxyLinnCoUkUi2PropertyDisplayBrightnessAuto(THandle aHandle, uint32_t* aDisplayBrightnessAuto)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aDisplayBrightnessAuto = false;
    proxyC->PropertyDisplayBrightnessAuto(*(TBool*)aDisplayBrightnessAuto);
}

void CpProxyLinnCoUkUi2PropertyInfraredCommands(THandle aHandle, char** aInfraredCommands)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aInfraredCommands;
    proxyC->PropertyInfraredCommands(buf_aInfraredCommands);
    *aInfraredCommands = buf_aInfraredCommands.Transfer();
}

void CpProxyLinnCoUkUi2PropertyInfraredTerminalCommands(THandle aHandle, char** aInfraredTerminalCommands)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aInfraredTerminalCommands;
    proxyC->PropertyInfraredTerminalCommands(buf_aInfraredTerminalCommands);
    *aInfraredTerminalCommands = buf_aInfraredTerminalCommands.Transfer();
}

void CpProxyLinnCoUkUi2PropertyDisplayUpsideDown(THandle aHandle, uint32_t* aDisplayUpsideDown)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aDisplayUpsideDown = false;
    proxyC->PropertyDisplayUpsideDown(*(TBool*)aDisplayUpsideDown);
}

void CpProxyLinnCoUkUi2PropertyDisplayScrollText(THandle aHandle, uint32_t* aDisplayScrollText)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aDisplayScrollText = false;
    proxyC->PropertyDisplayScrollText(*(TBool*)aDisplayScrollText);
}

void CpProxyLinnCoUkUi2PropertyDisplaySleep(THandle aHandle, uint32_t* aDisplaySleep)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aDisplaySleep = false;
    proxyC->PropertyDisplaySleep(*(TBool*)aDisplaySleep);
}

void CpProxyLinnCoUkUi2PropertyDisplayLedOff(THandle aHandle, uint32_t* aDisplayLedOff)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aDisplayLedOff = false;
    proxyC->PropertyDisplayLedOff(*(TBool*)aDisplayLedOff);
}

void CpProxyLinnCoUkUi2PropertyTerminalInputCode(THandle aHandle, uint32_t* aTerminalInputCode)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTerminalInputCode(*aTerminalInputCode);
}

void CpProxyLinnCoUkUi2PropertyTerminalInputName(THandle aHandle, char** aTerminalInputName)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTerminalInputName;
    proxyC->PropertyTerminalInputName(buf_aTerminalInputName);
    *aTerminalInputName = buf_aTerminalInputName.Transfer();
}

void CpProxyLinnCoUkUi2PropertyDisplayPixels(THandle aHandle, char** aDisplayPixels, uint32_t* aLen)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDisplayPixels;
    proxyC->PropertyDisplayPixels(buf_aDisplayPixels);
    *aLen = buf_aDisplayPixels.Bytes();
    *aDisplayPixels = buf_aDisplayPixels.Extract();
}

