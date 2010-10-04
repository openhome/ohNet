#include <Core/CpLinnCoUkUi2.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncDisplayTestPatternLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncDisplayTestPatternLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncDisplayTestPatternLinnCoUkUi2::SyncDisplayTestPatternLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncDisplayTestPatternLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayTestPattern(aAsync);
}


class SyncDisplayFillLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncDisplayFillLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncDisplayFillLinnCoUkUi2::SyncDisplayFillLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncDisplayFillLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayFill(aAsync);
}


class SyncDisplayClearLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncDisplayClearLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncDisplayClearLinnCoUkUi2::SyncDisplayClearLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncDisplayClearLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayClear(aAsync);
}


class SyncSetTestModeEnabledLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncSetTestModeEnabledLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncSetTestModeEnabledLinnCoUkUi2::SyncSetTestModeEnabledLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncSetTestModeEnabledLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetTestModeEnabled(aAsync);
}


class SyncSimulateInfraredInputLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncSimulateInfraredInputLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncSimulateInfraredInputLinnCoUkUi2::SyncSimulateInfraredInputLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncSimulateInfraredInputLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSimulateInfraredInput(aAsync);
}


class SyncSimulateButtonInputLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncSimulateButtonInputLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncSimulateButtonInputLinnCoUkUi2::SyncSimulateButtonInputLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncSimulateButtonInputLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSimulateButtonInput(aAsync);
}


class SyncSimulateLightSensorLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncSimulateLightSensorLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncSimulateLightSensorLinnCoUkUi2::SyncSimulateLightSensorLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncSimulateLightSensorLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSimulateLightSensor(aAsync);
}


class SyncGetLightSensorDataLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncGetLightSensorDataLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TUint& aaLightLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
    TUint& iaLightLevel;
};

SyncGetLightSensorDataLinnCoUkUi2::SyncGetLightSensorDataLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TUint& aaLightLevel)
    : iService(aService)
    , iaLightLevel(aaLightLevel)
{
}

void SyncGetLightSensorDataLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLightSensorData(aAsync, iaLightLevel);
}


class SyncSetDisplayBrightnessLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncSetDisplayBrightnessLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncSetDisplayBrightnessLinnCoUkUi2::SyncSetDisplayBrightnessLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncSetDisplayBrightnessLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayBrightness(aAsync);
}


class SyncSetDisplayBrightnessAutoLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncSetDisplayBrightnessAutoLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncSetDisplayBrightnessAutoLinnCoUkUi2::SyncSetDisplayBrightnessAutoLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncSetDisplayBrightnessAutoLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayBrightnessAuto(aAsync);
}


class SyncSetInfraredCommandsLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncSetInfraredCommandsLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncSetInfraredCommandsLinnCoUkUi2::SyncSetInfraredCommandsLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncSetInfraredCommandsLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetInfraredCommands(aAsync);
}


class SyncInfraredCommandsLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncInfraredCommandsLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, Brh& aaCommands);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
    Brh& iaCommands;
};

SyncInfraredCommandsLinnCoUkUi2::SyncInfraredCommandsLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, Brh& aaCommands)
    : iService(aService)
    , iaCommands(aaCommands)
{
}

void SyncInfraredCommandsLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndInfraredCommands(aAsync, iaCommands);
}


class SyncSetInfraredTerminalCommandsLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncSetInfraredTerminalCommandsLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncSetInfraredTerminalCommandsLinnCoUkUi2::SyncSetInfraredTerminalCommandsLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncSetInfraredTerminalCommandsLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetInfraredTerminalCommands(aAsync);
}


class SyncInfraredTerminalCommandsLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncInfraredTerminalCommandsLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, Brh& aaCommands);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
    Brh& iaCommands;
};

SyncInfraredTerminalCommandsLinnCoUkUi2::SyncInfraredTerminalCommandsLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, Brh& aaCommands)
    : iService(aService)
    , iaCommands(aaCommands)
{
}

void SyncInfraredTerminalCommandsLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndInfraredTerminalCommands(aAsync, iaCommands);
}


class SyncDisplayBrightnessLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncDisplayBrightnessLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TUint& aaBrightness);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
    TUint& iaBrightness;
};

SyncDisplayBrightnessLinnCoUkUi2::SyncDisplayBrightnessLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TUint& aaBrightness)
    : iService(aService)
    , iaBrightness(aaBrightness)
{
}

void SyncDisplayBrightnessLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayBrightness(aAsync, iaBrightness);
}


class SyncDisplayBrightnessAutoLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncDisplayBrightnessAutoLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TBool& aaBrightnessAuto);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
    TBool& iaBrightnessAuto;
};

SyncDisplayBrightnessAutoLinnCoUkUi2::SyncDisplayBrightnessAutoLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TBool& aaBrightnessAuto)
    : iService(aService)
    , iaBrightnessAuto(aaBrightnessAuto)
{
}

void SyncDisplayBrightnessAutoLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayBrightnessAuto(aAsync, iaBrightnessAuto);
}


class SyncDisplayUpsideDownLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncDisplayUpsideDownLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TBool& aaUpsideDown);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
    TBool& iaUpsideDown;
};

SyncDisplayUpsideDownLinnCoUkUi2::SyncDisplayUpsideDownLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TBool& aaUpsideDown)
    : iService(aService)
    , iaUpsideDown(aaUpsideDown)
{
}

void SyncDisplayUpsideDownLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayUpsideDown(aAsync, iaUpsideDown);
}


class SyncSetDisplayUpsideDownLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncSetDisplayUpsideDownLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncSetDisplayUpsideDownLinnCoUkUi2::SyncSetDisplayUpsideDownLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncSetDisplayUpsideDownLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayUpsideDown(aAsync);
}


class SyncSetDisplayScrollTextLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncSetDisplayScrollTextLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncSetDisplayScrollTextLinnCoUkUi2::SyncSetDisplayScrollTextLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncSetDisplayScrollTextLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayScrollText(aAsync);
}


class SyncDisplayScrollTextLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncDisplayScrollTextLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TBool& aaDisplayScrollTextEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
    TBool& iaDisplayScrollTextEnabled;
};

SyncDisplayScrollTextLinnCoUkUi2::SyncDisplayScrollTextLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TBool& aaDisplayScrollTextEnabled)
    : iService(aService)
    , iaDisplayScrollTextEnabled(aaDisplayScrollTextEnabled)
{
}

void SyncDisplayScrollTextLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayScrollText(aAsync, iaDisplayScrollTextEnabled);
}


class SyncSetDisplaySleepLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncSetDisplaySleepLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncSetDisplaySleepLinnCoUkUi2::SyncSetDisplaySleepLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncSetDisplaySleepLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplaySleep(aAsync);
}


class SyncDisplaySleepLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncDisplaySleepLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TBool& aaEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
    TBool& iaEnabled;
};

SyncDisplaySleepLinnCoUkUi2::SyncDisplaySleepLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TBool& aaEnabled)
    : iService(aService)
    , iaEnabled(aaEnabled)
{
}

void SyncDisplaySleepLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplaySleep(aAsync, iaEnabled);
}


class SyncSetDisplayLedOffLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncSetDisplayLedOffLinnCoUkUi2(CpProxyLinnCoUkUi2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
};

SyncSetDisplayLedOffLinnCoUkUi2::SyncSetDisplayLedOffLinnCoUkUi2(CpProxyLinnCoUkUi2& aService)
    : iService(aService)
{
}

void SyncSetDisplayLedOffLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayLedOff(aAsync);
}


class SyncDisplayLedOffLinnCoUkUi2 : public SyncProxyAction
{
public:
    SyncDisplayLedOffLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TBool& aaOff);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2& iService;
    TBool& iaOff;
};

SyncDisplayLedOffLinnCoUkUi2::SyncDisplayLedOffLinnCoUkUi2(CpProxyLinnCoUkUi2& aService, TBool& aaOff)
    : iService(aService)
    , iaOff(aaOff)
{
}

void SyncDisplayLedOffLinnCoUkUi2::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayLedOff(aAsync, iaOff);
}


CpProxyLinnCoUkUi2::CpProxyLinnCoUkUi2(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Ui", 2, aDevice.Device());
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2::DisplayBrightnessPropertyChanged);
    iDisplayBrightness = new PropertyUint("DisplayBrightness", functor);
    iService->AddProperty(iDisplayBrightness);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2::DisplayBrightnessAutoPropertyChanged);
    iDisplayBrightnessAuto = new PropertyBool("DisplayBrightnessAuto", functor);
    iService->AddProperty(iDisplayBrightnessAuto);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2::InfraredCommandsPropertyChanged);
    iInfraredCommands = new PropertyString("InfraredCommands", functor);
    iService->AddProperty(iInfraredCommands);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2::InfraredTerminalCommandsPropertyChanged);
    iInfraredTerminalCommands = new PropertyString("InfraredTerminalCommands", functor);
    iService->AddProperty(iInfraredTerminalCommands);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2::DisplayUpsideDownPropertyChanged);
    iDisplayUpsideDown = new PropertyBool("DisplayUpsideDown", functor);
    iService->AddProperty(iDisplayUpsideDown);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2::DisplayScrollTextPropertyChanged);
    iDisplayScrollText = new PropertyBool("DisplayScrollText", functor);
    iService->AddProperty(iDisplayScrollText);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2::DisplaySleepPropertyChanged);
    iDisplaySleep = new PropertyBool("DisplaySleep", functor);
    iService->AddProperty(iDisplaySleep);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2::DisplayLedOffPropertyChanged);
    iDisplayLedOff = new PropertyBool("DisplayLedOff", functor);
    iService->AddProperty(iDisplayLedOff);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2::TerminalInputCodePropertyChanged);
    iTerminalInputCode = new PropertyUint("TerminalInputCode", functor);
    iService->AddProperty(iTerminalInputCode);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2::TerminalInputNamePropertyChanged);
    iTerminalInputName = new PropertyString("TerminalInputName", functor);
    iService->AddProperty(iTerminalInputName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2::DisplayPixelsPropertyChanged);
    iDisplayPixels = new PropertyBinary("DisplayPixels", functor);
    iService->AddProperty(iDisplayPixels);
}

CpProxyLinnCoUkUi2::~CpProxyLinnCoUkUi2()
{
    delete iService;
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

void CpProxyLinnCoUkUi2::SyncDisplayTestPattern(TInt aaTestPattern)
{
    SyncDisplayTestPatternLinnCoUkUi2 sync(*this);
    BeginDisplayTestPattern(aaTestPattern, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginDisplayTestPattern(TInt aaTestPattern, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayTestPattern, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDisplayTestPattern->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaTestPattern));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndDisplayTestPattern(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayTestPattern"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncDisplayFill()
{
    SyncDisplayFillLinnCoUkUi2 sync(*this);
    BeginDisplayFill(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginDisplayFill(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayFill, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndDisplayFill(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayFill"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncDisplayClear()
{
    SyncDisplayClearLinnCoUkUi2 sync(*this);
    BeginDisplayClear(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginDisplayClear(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayClear, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndDisplayClear(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayClear"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncSetTestModeEnabled(TBool aaEnabled)
{
    SyncSetTestModeEnabledLinnCoUkUi2 sync(*this);
    BeginSetTestModeEnabled(aaEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginSetTestModeEnabled(TBool aaEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetTestModeEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetTestModeEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaEnabled));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndSetTestModeEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetTestModeEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncSimulateInfraredInput(TUint aaCode)
{
    SyncSimulateInfraredInputLinnCoUkUi2 sync(*this);
    BeginSimulateInfraredInput(aaCode, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginSimulateInfraredInput(TUint aaCode, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSimulateInfraredInput, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSimulateInfraredInput->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaCode));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndSimulateInfraredInput(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SimulateInfraredInput"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncSimulateButtonInput(TUint aaCode)
{
    SyncSimulateButtonInputLinnCoUkUi2 sync(*this);
    BeginSimulateButtonInput(aaCode, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginSimulateButtonInput(TUint aaCode, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSimulateButtonInput, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSimulateButtonInput->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaCode));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndSimulateButtonInput(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SimulateButtonInput"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncSimulateLightSensor(TUint aaLightLevel)
{
    SyncSimulateLightSensorLinnCoUkUi2 sync(*this);
    BeginSimulateLightSensor(aaLightLevel, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginSimulateLightSensor(TUint aaLightLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSimulateLightSensor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSimulateLightSensor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaLightLevel));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndSimulateLightSensor(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SimulateLightSensor"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncGetLightSensorData(TUint& aaLightLevel)
{
    SyncGetLightSensorDataLinnCoUkUi2 sync(*this, aaLightLevel);
    BeginGetLightSensorData(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginGetLightSensorData(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetLightSensorData, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLightSensorData->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndGetLightSensorData(IAsync& aAsync, TUint& aaLightLevel)
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

void CpProxyLinnCoUkUi2::SyncSetDisplayBrightness(TUint aaBrightness)
{
    SyncSetDisplayBrightnessLinnCoUkUi2 sync(*this);
    BeginSetDisplayBrightness(aaBrightness, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginSetDisplayBrightness(TUint aaBrightness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDisplayBrightness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayBrightness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaBrightness));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndSetDisplayBrightness(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayBrightness"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncSetDisplayBrightnessAuto(TBool aaBrightnessAuto)
{
    SyncSetDisplayBrightnessAutoLinnCoUkUi2 sync(*this);
    BeginSetDisplayBrightnessAuto(aaBrightnessAuto, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginSetDisplayBrightnessAuto(TBool aaBrightnessAuto, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDisplayBrightnessAuto, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayBrightnessAuto->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaBrightnessAuto));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndSetDisplayBrightnessAuto(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayBrightnessAuto"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncSetInfraredCommands(const Brx& aaCommands)
{
    SyncSetInfraredCommandsLinnCoUkUi2 sync(*this);
    BeginSetInfraredCommands(aaCommands, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginSetInfraredCommands(const Brx& aaCommands, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetInfraredCommands, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetInfraredCommands->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaCommands));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndSetInfraredCommands(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetInfraredCommands"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncInfraredCommands(Brh& aaCommands)
{
    SyncInfraredCommandsLinnCoUkUi2 sync(*this, aaCommands);
    BeginInfraredCommands(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginInfraredCommands(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionInfraredCommands, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInfraredCommands->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndInfraredCommands(IAsync& aAsync, Brh& aaCommands)
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

void CpProxyLinnCoUkUi2::SyncSetInfraredTerminalCommands(const Brx& aaCommands)
{
    SyncSetInfraredTerminalCommandsLinnCoUkUi2 sync(*this);
    BeginSetInfraredTerminalCommands(aaCommands, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginSetInfraredTerminalCommands(const Brx& aaCommands, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetInfraredTerminalCommands, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetInfraredTerminalCommands->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaCommands));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndSetInfraredTerminalCommands(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetInfraredTerminalCommands"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncInfraredTerminalCommands(Brh& aaCommands)
{
    SyncInfraredTerminalCommandsLinnCoUkUi2 sync(*this, aaCommands);
    BeginInfraredTerminalCommands(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginInfraredTerminalCommands(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionInfraredTerminalCommands, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInfraredTerminalCommands->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndInfraredTerminalCommands(IAsync& aAsync, Brh& aaCommands)
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

void CpProxyLinnCoUkUi2::SyncDisplayBrightness(TUint& aaBrightness)
{
    SyncDisplayBrightnessLinnCoUkUi2 sync(*this, aaBrightness);
    BeginDisplayBrightness(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginDisplayBrightness(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayBrightness, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayBrightness->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndDisplayBrightness(IAsync& aAsync, TUint& aaBrightness)
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

void CpProxyLinnCoUkUi2::SyncDisplayBrightnessAuto(TBool& aaBrightnessAuto)
{
    SyncDisplayBrightnessAutoLinnCoUkUi2 sync(*this, aaBrightnessAuto);
    BeginDisplayBrightnessAuto(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginDisplayBrightnessAuto(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayBrightnessAuto, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayBrightnessAuto->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndDisplayBrightnessAuto(IAsync& aAsync, TBool& aaBrightnessAuto)
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

void CpProxyLinnCoUkUi2::SyncDisplayUpsideDown(TBool& aaUpsideDown)
{
    SyncDisplayUpsideDownLinnCoUkUi2 sync(*this, aaUpsideDown);
    BeginDisplayUpsideDown(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginDisplayUpsideDown(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayUpsideDown, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayUpsideDown->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndDisplayUpsideDown(IAsync& aAsync, TBool& aaUpsideDown)
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

void CpProxyLinnCoUkUi2::SyncSetDisplayUpsideDown(TBool aaUpsideDown)
{
    SyncSetDisplayUpsideDownLinnCoUkUi2 sync(*this);
    BeginSetDisplayUpsideDown(aaUpsideDown, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginSetDisplayUpsideDown(TBool aaUpsideDown, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDisplayUpsideDown, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayUpsideDown->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaUpsideDown));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndSetDisplayUpsideDown(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayUpsideDown"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncSetDisplayScrollText(TBool aaDisplayScrollText)
{
    SyncSetDisplayScrollTextLinnCoUkUi2 sync(*this);
    BeginSetDisplayScrollText(aaDisplayScrollText, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginSetDisplayScrollText(TBool aaDisplayScrollText, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDisplayScrollText, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayScrollText->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaDisplayScrollText));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndSetDisplayScrollText(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayScrollText"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncDisplayScrollText(TBool& aaDisplayScrollTextEnabled)
{
    SyncDisplayScrollTextLinnCoUkUi2 sync(*this, aaDisplayScrollTextEnabled);
    BeginDisplayScrollText(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginDisplayScrollText(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayScrollText, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayScrollText->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndDisplayScrollText(IAsync& aAsync, TBool& aaDisplayScrollTextEnabled)
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

void CpProxyLinnCoUkUi2::SyncSetDisplaySleep(TBool aaEnabled)
{
    SyncSetDisplaySleepLinnCoUkUi2 sync(*this);
    BeginSetDisplaySleep(aaEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginSetDisplaySleep(TBool aaEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDisplaySleep, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplaySleep->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaEnabled));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndSetDisplaySleep(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplaySleep"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncDisplaySleep(TBool& aaEnabled)
{
    SyncDisplaySleepLinnCoUkUi2 sync(*this, aaEnabled);
    BeginDisplaySleep(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginDisplaySleep(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplaySleep, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplaySleep->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndDisplaySleep(IAsync& aAsync, TBool& aaEnabled)
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

void CpProxyLinnCoUkUi2::SyncSetDisplayLedOff(TBool aaOff)
{
    SyncSetDisplayLedOffLinnCoUkUi2 sync(*this);
    BeginSetDisplayLedOff(aaOff, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginSetDisplayLedOff(TBool aaOff, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDisplayLedOff, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayLedOff->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaOff));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndSetDisplayLedOff(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayLedOff"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2::SyncDisplayLedOff(TBool& aaOff)
{
    SyncDisplayLedOffLinnCoUkUi2 sync(*this, aaOff);
    BeginDisplayLedOff(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2::BeginDisplayLedOff(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayLedOff, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayLedOff->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2::EndDisplayLedOff(IAsync& aAsync, TBool& aaOff)
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

void CpProxyLinnCoUkUi2::SetPropertyDisplayBrightnessChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplayBrightnessChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2::SetPropertyDisplayBrightnessAutoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplayBrightnessAutoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2::SetPropertyInfraredCommandsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iInfraredCommandsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2::SetPropertyInfraredTerminalCommandsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iInfraredTerminalCommandsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2::SetPropertyDisplayUpsideDownChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplayUpsideDownChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2::SetPropertyDisplayScrollTextChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplayScrollTextChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2::SetPropertyDisplaySleepChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplaySleepChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2::SetPropertyDisplayLedOffChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplayLedOffChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2::SetPropertyTerminalInputCodeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTerminalInputCodeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2::SetPropertyTerminalInputNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTerminalInputNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2::SetPropertyDisplayPixelsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplayPixelsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2::PropertyDisplayBrightness(TUint& aDisplayBrightness) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDisplayBrightness = iDisplayBrightness->Value();
}

void CpProxyLinnCoUkUi2::PropertyDisplayBrightnessAuto(TBool& aDisplayBrightnessAuto) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDisplayBrightnessAuto = iDisplayBrightnessAuto->Value();
}

void CpProxyLinnCoUkUi2::PropertyInfraredCommands(Brhz& aInfraredCommands) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aInfraredCommands.Set(iInfraredCommands->Value());
}

void CpProxyLinnCoUkUi2::PropertyInfraredTerminalCommands(Brhz& aInfraredTerminalCommands) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aInfraredTerminalCommands.Set(iInfraredTerminalCommands->Value());
}

void CpProxyLinnCoUkUi2::PropertyDisplayUpsideDown(TBool& aDisplayUpsideDown) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDisplayUpsideDown = iDisplayUpsideDown->Value();
}

void CpProxyLinnCoUkUi2::PropertyDisplayScrollText(TBool& aDisplayScrollText) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDisplayScrollText = iDisplayScrollText->Value();
}

void CpProxyLinnCoUkUi2::PropertyDisplaySleep(TBool& aDisplaySleep) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDisplaySleep = iDisplaySleep->Value();
}

void CpProxyLinnCoUkUi2::PropertyDisplayLedOff(TBool& aDisplayLedOff) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDisplayLedOff = iDisplayLedOff->Value();
}

void CpProxyLinnCoUkUi2::PropertyTerminalInputCode(TUint& aTerminalInputCode) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTerminalInputCode = iTerminalInputCode->Value();
}

void CpProxyLinnCoUkUi2::PropertyTerminalInputName(Brhz& aTerminalInputName) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTerminalInputName.Set(iTerminalInputName->Value());
}

void CpProxyLinnCoUkUi2::PropertyDisplayPixels(Brh& aDisplayPixels) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDisplayPixels.Set(iDisplayPixels->Value());
}

void CpProxyLinnCoUkUi2::DisplayBrightnessPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplayBrightnessChanged != NULL) {
        iDisplayBrightnessChanged();
    }
}

void CpProxyLinnCoUkUi2::DisplayBrightnessAutoPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplayBrightnessAutoChanged != NULL) {
        iDisplayBrightnessAutoChanged();
    }
}

void CpProxyLinnCoUkUi2::InfraredCommandsPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iInfraredCommandsChanged != NULL) {
        iInfraredCommandsChanged();
    }
}

void CpProxyLinnCoUkUi2::InfraredTerminalCommandsPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iInfraredTerminalCommandsChanged != NULL) {
        iInfraredTerminalCommandsChanged();
    }
}

void CpProxyLinnCoUkUi2::DisplayUpsideDownPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplayUpsideDownChanged != NULL) {
        iDisplayUpsideDownChanged();
    }
}

void CpProxyLinnCoUkUi2::DisplayScrollTextPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplayScrollTextChanged != NULL) {
        iDisplayScrollTextChanged();
    }
}

void CpProxyLinnCoUkUi2::DisplaySleepPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplaySleepChanged != NULL) {
        iDisplaySleepChanged();
    }
}

void CpProxyLinnCoUkUi2::DisplayLedOffPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplayLedOffChanged != NULL) {
        iDisplayLedOffChanged();
    }
}

void CpProxyLinnCoUkUi2::TerminalInputCodePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTerminalInputCodeChanged != NULL) {
        iTerminalInputCodeChanged();
    }
}

void CpProxyLinnCoUkUi2::TerminalInputNamePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTerminalInputNameChanged != NULL) {
        iTerminalInputNameChanged();
    }
}

void CpProxyLinnCoUkUi2::DisplayPixelsPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplayPixelsChanged != NULL) {
        iDisplayPixelsChanged();
    }
}

