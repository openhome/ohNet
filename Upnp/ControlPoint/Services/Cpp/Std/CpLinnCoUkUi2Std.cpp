#include <Std/CpLinnCoUkUi2.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncDisplayTestPatternLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncDisplayTestPatternLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncDisplayTestPatternLinnCoUkUi2Cpp::SyncDisplayTestPatternLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncDisplayTestPatternLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayTestPattern(aAsync);
}


class SyncDisplayFillLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncDisplayFillLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncDisplayFillLinnCoUkUi2Cpp::SyncDisplayFillLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncDisplayFillLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayFill(aAsync);
}


class SyncDisplayClearLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncDisplayClearLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncDisplayClearLinnCoUkUi2Cpp::SyncDisplayClearLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncDisplayClearLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayClear(aAsync);
}


class SyncSetTestModeEnabledLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncSetTestModeEnabledLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncSetTestModeEnabledLinnCoUkUi2Cpp::SyncSetTestModeEnabledLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncSetTestModeEnabledLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetTestModeEnabled(aAsync);
}


class SyncSimulateInfraredInputLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncSimulateInfraredInputLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncSimulateInfraredInputLinnCoUkUi2Cpp::SyncSimulateInfraredInputLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncSimulateInfraredInputLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSimulateInfraredInput(aAsync);
}


class SyncSimulateButtonInputLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncSimulateButtonInputLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncSimulateButtonInputLinnCoUkUi2Cpp::SyncSimulateButtonInputLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncSimulateButtonInputLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSimulateButtonInput(aAsync);
}


class SyncSimulateLightSensorLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncSimulateLightSensorLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncSimulateLightSensorLinnCoUkUi2Cpp::SyncSimulateLightSensorLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncSimulateLightSensorLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSimulateLightSensor(aAsync);
}


class SyncGetLightSensorDataLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncGetLightSensorDataLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, uint32_t& aaLightLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
    uint32_t& iaLightLevel;
};

SyncGetLightSensorDataLinnCoUkUi2Cpp::SyncGetLightSensorDataLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, uint32_t& aaLightLevel)
    : iService(aService)
    , iaLightLevel(aaLightLevel)
{
}

void SyncGetLightSensorDataLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLightSensorData(aAsync, iaLightLevel);
}


class SyncSetDisplayBrightnessLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncSetDisplayBrightnessLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncSetDisplayBrightnessLinnCoUkUi2Cpp::SyncSetDisplayBrightnessLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncSetDisplayBrightnessLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayBrightness(aAsync);
}


class SyncSetDisplayBrightnessAutoLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncSetDisplayBrightnessAutoLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncSetDisplayBrightnessAutoLinnCoUkUi2Cpp::SyncSetDisplayBrightnessAutoLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncSetDisplayBrightnessAutoLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayBrightnessAuto(aAsync);
}


class SyncSetInfraredCommandsLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncSetInfraredCommandsLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncSetInfraredCommandsLinnCoUkUi2Cpp::SyncSetInfraredCommandsLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncSetInfraredCommandsLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetInfraredCommands(aAsync);
}


class SyncInfraredCommandsLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncInfraredCommandsLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, std::string& aaCommands);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
    std::string& iaCommands;
};

SyncInfraredCommandsLinnCoUkUi2Cpp::SyncInfraredCommandsLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, std::string& aaCommands)
    : iService(aService)
    , iaCommands(aaCommands)
{
}

void SyncInfraredCommandsLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndInfraredCommands(aAsync, iaCommands);
}


class SyncSetInfraredTerminalCommandsLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncSetInfraredTerminalCommandsLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncSetInfraredTerminalCommandsLinnCoUkUi2Cpp::SyncSetInfraredTerminalCommandsLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncSetInfraredTerminalCommandsLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetInfraredTerminalCommands(aAsync);
}


class SyncInfraredTerminalCommandsLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncInfraredTerminalCommandsLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, std::string& aaCommands);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
    std::string& iaCommands;
};

SyncInfraredTerminalCommandsLinnCoUkUi2Cpp::SyncInfraredTerminalCommandsLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, std::string& aaCommands)
    : iService(aService)
    , iaCommands(aaCommands)
{
}

void SyncInfraredTerminalCommandsLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndInfraredTerminalCommands(aAsync, iaCommands);
}


class SyncDisplayBrightnessLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncDisplayBrightnessLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, uint32_t& aaBrightness);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
    uint32_t& iaBrightness;
};

SyncDisplayBrightnessLinnCoUkUi2Cpp::SyncDisplayBrightnessLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, uint32_t& aaBrightness)
    : iService(aService)
    , iaBrightness(aaBrightness)
{
}

void SyncDisplayBrightnessLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayBrightness(aAsync, iaBrightness);
}


class SyncDisplayBrightnessAutoLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncDisplayBrightnessAutoLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, bool& aaBrightnessAuto);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
    bool& iaBrightnessAuto;
};

SyncDisplayBrightnessAutoLinnCoUkUi2Cpp::SyncDisplayBrightnessAutoLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, bool& aaBrightnessAuto)
    : iService(aService)
    , iaBrightnessAuto(aaBrightnessAuto)
{
}

void SyncDisplayBrightnessAutoLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayBrightnessAuto(aAsync, iaBrightnessAuto);
}


class SyncDisplayUpsideDownLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncDisplayUpsideDownLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, bool& aaUpsideDown);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
    bool& iaUpsideDown;
};

SyncDisplayUpsideDownLinnCoUkUi2Cpp::SyncDisplayUpsideDownLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, bool& aaUpsideDown)
    : iService(aService)
    , iaUpsideDown(aaUpsideDown)
{
}

void SyncDisplayUpsideDownLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayUpsideDown(aAsync, iaUpsideDown);
}


class SyncSetDisplayUpsideDownLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncSetDisplayUpsideDownLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncSetDisplayUpsideDownLinnCoUkUi2Cpp::SyncSetDisplayUpsideDownLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncSetDisplayUpsideDownLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayUpsideDown(aAsync);
}


class SyncSetDisplayScrollTextLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncSetDisplayScrollTextLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncSetDisplayScrollTextLinnCoUkUi2Cpp::SyncSetDisplayScrollTextLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncSetDisplayScrollTextLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayScrollText(aAsync);
}


class SyncDisplayScrollTextLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncDisplayScrollTextLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, bool& aaDisplayScrollTextEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
    bool& iaDisplayScrollTextEnabled;
};

SyncDisplayScrollTextLinnCoUkUi2Cpp::SyncDisplayScrollTextLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, bool& aaDisplayScrollTextEnabled)
    : iService(aService)
    , iaDisplayScrollTextEnabled(aaDisplayScrollTextEnabled)
{
}

void SyncDisplayScrollTextLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayScrollText(aAsync, iaDisplayScrollTextEnabled);
}


class SyncSetDisplaySleepLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncSetDisplaySleepLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncSetDisplaySleepLinnCoUkUi2Cpp::SyncSetDisplaySleepLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncSetDisplaySleepLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplaySleep(aAsync);
}


class SyncDisplaySleepLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncDisplaySleepLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, bool& aaEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
    bool& iaEnabled;
};

SyncDisplaySleepLinnCoUkUi2Cpp::SyncDisplaySleepLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, bool& aaEnabled)
    : iService(aService)
    , iaEnabled(aaEnabled)
{
}

void SyncDisplaySleepLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplaySleep(aAsync, iaEnabled);
}


class SyncSetDisplayLedOffLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncSetDisplayLedOffLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
};

SyncSetDisplayLedOffLinnCoUkUi2Cpp::SyncSetDisplayLedOffLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService)
    : iService(aService)
{
}

void SyncSetDisplayLedOffLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDisplayLedOff(aAsync);
}


class SyncDisplayLedOffLinnCoUkUi2Cpp : public SyncProxyAction
{
public:
    SyncDisplayLedOffLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, bool& aaOff);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkUi2Cpp& iService;
    bool& iaOff;
};

SyncDisplayLedOffLinnCoUkUi2Cpp::SyncDisplayLedOffLinnCoUkUi2Cpp(CpProxyLinnCoUkUi2Cpp& aService, bool& aaOff)
    : iService(aService)
    , iaOff(aaOff)
{
}

void SyncDisplayLedOffLinnCoUkUi2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDisplayLedOff(aAsync, iaOff);
}


CpProxyLinnCoUkUi2Cpp::CpProxyLinnCoUkUi2Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2Cpp::DisplayBrightnessPropertyChanged);
    iDisplayBrightness = new PropertyUint("DisplayBrightness", functor);
    iService->AddProperty(iDisplayBrightness);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2Cpp::DisplayBrightnessAutoPropertyChanged);
    iDisplayBrightnessAuto = new PropertyBool("DisplayBrightnessAuto", functor);
    iService->AddProperty(iDisplayBrightnessAuto);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2Cpp::InfraredCommandsPropertyChanged);
    iInfraredCommands = new PropertyString("InfraredCommands", functor);
    iService->AddProperty(iInfraredCommands);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2Cpp::InfraredTerminalCommandsPropertyChanged);
    iInfraredTerminalCommands = new PropertyString("InfraredTerminalCommands", functor);
    iService->AddProperty(iInfraredTerminalCommands);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2Cpp::DisplayUpsideDownPropertyChanged);
    iDisplayUpsideDown = new PropertyBool("DisplayUpsideDown", functor);
    iService->AddProperty(iDisplayUpsideDown);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2Cpp::DisplayScrollTextPropertyChanged);
    iDisplayScrollText = new PropertyBool("DisplayScrollText", functor);
    iService->AddProperty(iDisplayScrollText);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2Cpp::DisplaySleepPropertyChanged);
    iDisplaySleep = new PropertyBool("DisplaySleep", functor);
    iService->AddProperty(iDisplaySleep);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2Cpp::DisplayLedOffPropertyChanged);
    iDisplayLedOff = new PropertyBool("DisplayLedOff", functor);
    iService->AddProperty(iDisplayLedOff);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2Cpp::TerminalInputCodePropertyChanged);
    iTerminalInputCode = new PropertyUint("TerminalInputCode", functor);
    iService->AddProperty(iTerminalInputCode);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2Cpp::TerminalInputNamePropertyChanged);
    iTerminalInputName = new PropertyString("TerminalInputName", functor);
    iService->AddProperty(iTerminalInputName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkUi2Cpp::DisplayPixelsPropertyChanged);
    iDisplayPixels = new PropertyBinary("DisplayPixels", functor);
    iService->AddProperty(iDisplayPixels);
}

CpProxyLinnCoUkUi2Cpp::~CpProxyLinnCoUkUi2Cpp()
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

void CpProxyLinnCoUkUi2Cpp::SyncDisplayTestPattern(int32_t aaTestPattern)
{
    SyncDisplayTestPatternLinnCoUkUi2Cpp sync(*this);
    BeginDisplayTestPattern(aaTestPattern, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginDisplayTestPattern(int32_t aaTestPattern, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayTestPattern, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDisplayTestPattern->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaTestPattern));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndDisplayTestPattern(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayTestPattern"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncDisplayFill()
{
    SyncDisplayFillLinnCoUkUi2Cpp sync(*this);
    BeginDisplayFill(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginDisplayFill(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayFill, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndDisplayFill(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayFill"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncDisplayClear()
{
    SyncDisplayClearLinnCoUkUi2Cpp sync(*this);
    BeginDisplayClear(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginDisplayClear(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayClear, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndDisplayClear(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DisplayClear"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncSetTestModeEnabled(bool aaEnabled)
{
    SyncSetTestModeEnabledLinnCoUkUi2Cpp sync(*this);
    BeginSetTestModeEnabled(aaEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginSetTestModeEnabled(bool aaEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetTestModeEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetTestModeEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaEnabled));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndSetTestModeEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetTestModeEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncSimulateInfraredInput(uint32_t aaCode)
{
    SyncSimulateInfraredInputLinnCoUkUi2Cpp sync(*this);
    BeginSimulateInfraredInput(aaCode, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginSimulateInfraredInput(uint32_t aaCode, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSimulateInfraredInput, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSimulateInfraredInput->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaCode));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndSimulateInfraredInput(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SimulateInfraredInput"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncSimulateButtonInput(uint32_t aaCode)
{
    SyncSimulateButtonInputLinnCoUkUi2Cpp sync(*this);
    BeginSimulateButtonInput(aaCode, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginSimulateButtonInput(uint32_t aaCode, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSimulateButtonInput, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSimulateButtonInput->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaCode));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndSimulateButtonInput(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SimulateButtonInput"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncSimulateLightSensor(uint32_t aaLightLevel)
{
    SyncSimulateLightSensorLinnCoUkUi2Cpp sync(*this);
    BeginSimulateLightSensor(aaLightLevel, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginSimulateLightSensor(uint32_t aaLightLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSimulateLightSensor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSimulateLightSensor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaLightLevel));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndSimulateLightSensor(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SimulateLightSensor"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncGetLightSensorData(uint32_t& aaLightLevel)
{
    SyncGetLightSensorDataLinnCoUkUi2Cpp sync(*this, aaLightLevel);
    BeginGetLightSensorData(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginGetLightSensorData(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetLightSensorData, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLightSensorData->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndGetLightSensorData(IAsync& aAsync, uint32_t& aaLightLevel)
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

void CpProxyLinnCoUkUi2Cpp::SyncSetDisplayBrightness(uint32_t aaBrightness)
{
    SyncSetDisplayBrightnessLinnCoUkUi2Cpp sync(*this);
    BeginSetDisplayBrightness(aaBrightness, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginSetDisplayBrightness(uint32_t aaBrightness, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDisplayBrightness, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayBrightness->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaBrightness));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndSetDisplayBrightness(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayBrightness"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncSetDisplayBrightnessAuto(bool aaBrightnessAuto)
{
    SyncSetDisplayBrightnessAutoLinnCoUkUi2Cpp sync(*this);
    BeginSetDisplayBrightnessAuto(aaBrightnessAuto, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginSetDisplayBrightnessAuto(bool aaBrightnessAuto, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDisplayBrightnessAuto, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayBrightnessAuto->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaBrightnessAuto));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndSetDisplayBrightnessAuto(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayBrightnessAuto"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncSetInfraredCommands(const std::string& aaCommands)
{
    SyncSetInfraredCommandsLinnCoUkUi2Cpp sync(*this);
    BeginSetInfraredCommands(aaCommands, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginSetInfraredCommands(const std::string& aaCommands, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetInfraredCommands, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetInfraredCommands->InputParameters();
    {
        Brn buf((const TByte*)aaCommands.c_str(), aaCommands.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndSetInfraredCommands(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetInfraredCommands"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncInfraredCommands(std::string& aaCommands)
{
    SyncInfraredCommandsLinnCoUkUi2Cpp sync(*this, aaCommands);
    BeginInfraredCommands(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginInfraredCommands(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionInfraredCommands, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInfraredCommands->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndInfraredCommands(IAsync& aAsync, std::string& aaCommands)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("InfraredCommands"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaCommands.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncSetInfraredTerminalCommands(const std::string& aaCommands)
{
    SyncSetInfraredTerminalCommandsLinnCoUkUi2Cpp sync(*this);
    BeginSetInfraredTerminalCommands(aaCommands, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginSetInfraredTerminalCommands(const std::string& aaCommands, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetInfraredTerminalCommands, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetInfraredTerminalCommands->InputParameters();
    {
        Brn buf((const TByte*)aaCommands.c_str(), aaCommands.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndSetInfraredTerminalCommands(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetInfraredTerminalCommands"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncInfraredTerminalCommands(std::string& aaCommands)
{
    SyncInfraredTerminalCommandsLinnCoUkUi2Cpp sync(*this, aaCommands);
    BeginInfraredTerminalCommands(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginInfraredTerminalCommands(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionInfraredTerminalCommands, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionInfraredTerminalCommands->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndInfraredTerminalCommands(IAsync& aAsync, std::string& aaCommands)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("InfraredTerminalCommands"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaCommands.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncDisplayBrightness(uint32_t& aaBrightness)
{
    SyncDisplayBrightnessLinnCoUkUi2Cpp sync(*this, aaBrightness);
    BeginDisplayBrightness(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginDisplayBrightness(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayBrightness, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayBrightness->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndDisplayBrightness(IAsync& aAsync, uint32_t& aaBrightness)
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

void CpProxyLinnCoUkUi2Cpp::SyncDisplayBrightnessAuto(bool& aaBrightnessAuto)
{
    SyncDisplayBrightnessAutoLinnCoUkUi2Cpp sync(*this, aaBrightnessAuto);
    BeginDisplayBrightnessAuto(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginDisplayBrightnessAuto(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayBrightnessAuto, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayBrightnessAuto->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndDisplayBrightnessAuto(IAsync& aAsync, bool& aaBrightnessAuto)
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

void CpProxyLinnCoUkUi2Cpp::SyncDisplayUpsideDown(bool& aaUpsideDown)
{
    SyncDisplayUpsideDownLinnCoUkUi2Cpp sync(*this, aaUpsideDown);
    BeginDisplayUpsideDown(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginDisplayUpsideDown(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayUpsideDown, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayUpsideDown->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndDisplayUpsideDown(IAsync& aAsync, bool& aaUpsideDown)
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

void CpProxyLinnCoUkUi2Cpp::SyncSetDisplayUpsideDown(bool aaUpsideDown)
{
    SyncSetDisplayUpsideDownLinnCoUkUi2Cpp sync(*this);
    BeginSetDisplayUpsideDown(aaUpsideDown, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginSetDisplayUpsideDown(bool aaUpsideDown, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDisplayUpsideDown, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayUpsideDown->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaUpsideDown));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndSetDisplayUpsideDown(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayUpsideDown"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncSetDisplayScrollText(bool aaDisplayScrollText)
{
    SyncSetDisplayScrollTextLinnCoUkUi2Cpp sync(*this);
    BeginSetDisplayScrollText(aaDisplayScrollText, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginSetDisplayScrollText(bool aaDisplayScrollText, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDisplayScrollText, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayScrollText->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaDisplayScrollText));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndSetDisplayScrollText(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayScrollText"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncDisplayScrollText(bool& aaDisplayScrollTextEnabled)
{
    SyncDisplayScrollTextLinnCoUkUi2Cpp sync(*this, aaDisplayScrollTextEnabled);
    BeginDisplayScrollText(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginDisplayScrollText(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayScrollText, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayScrollText->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndDisplayScrollText(IAsync& aAsync, bool& aaDisplayScrollTextEnabled)
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

void CpProxyLinnCoUkUi2Cpp::SyncSetDisplaySleep(bool aaEnabled)
{
    SyncSetDisplaySleepLinnCoUkUi2Cpp sync(*this);
    BeginSetDisplaySleep(aaEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginSetDisplaySleep(bool aaEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDisplaySleep, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplaySleep->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaEnabled));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndSetDisplaySleep(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplaySleep"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncDisplaySleep(bool& aaEnabled)
{
    SyncDisplaySleepLinnCoUkUi2Cpp sync(*this, aaEnabled);
    BeginDisplaySleep(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginDisplaySleep(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplaySleep, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplaySleep->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndDisplaySleep(IAsync& aAsync, bool& aaEnabled)
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

void CpProxyLinnCoUkUi2Cpp::SyncSetDisplayLedOff(bool aaOff)
{
    SyncSetDisplayLedOffLinnCoUkUi2Cpp sync(*this);
    BeginSetDisplayLedOff(aaOff, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginSetDisplayLedOff(bool aaOff, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDisplayLedOff, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDisplayLedOff->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaOff));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndSetDisplayLedOff(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDisplayLedOff"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkUi2Cpp::SyncDisplayLedOff(bool& aaOff)
{
    SyncDisplayLedOffLinnCoUkUi2Cpp sync(*this, aaOff);
    BeginDisplayLedOff(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkUi2Cpp::BeginDisplayLedOff(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDisplayLedOff, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDisplayLedOff->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkUi2Cpp::EndDisplayLedOff(IAsync& aAsync, bool& aaOff)
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

void CpProxyLinnCoUkUi2Cpp::SetPropertyDisplayBrightnessChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplayBrightnessChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2Cpp::SetPropertyDisplayBrightnessAutoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplayBrightnessAutoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2Cpp::SetPropertyInfraredCommandsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iInfraredCommandsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2Cpp::SetPropertyInfraredTerminalCommandsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iInfraredTerminalCommandsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2Cpp::SetPropertyDisplayUpsideDownChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplayUpsideDownChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2Cpp::SetPropertyDisplayScrollTextChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplayScrollTextChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2Cpp::SetPropertyDisplaySleepChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplaySleepChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2Cpp::SetPropertyDisplayLedOffChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplayLedOffChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2Cpp::SetPropertyTerminalInputCodeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTerminalInputCodeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2Cpp::SetPropertyTerminalInputNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTerminalInputNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2Cpp::SetPropertyDisplayPixelsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDisplayPixelsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkUi2Cpp::PropertyDisplayBrightness(uint32_t& aDisplayBrightness) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDisplayBrightness = iDisplayBrightness->Value();
}

void CpProxyLinnCoUkUi2Cpp::PropertyDisplayBrightnessAuto(bool& aDisplayBrightnessAuto) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDisplayBrightnessAuto = iDisplayBrightnessAuto->Value();
}

void CpProxyLinnCoUkUi2Cpp::PropertyInfraredCommands(std::string& aInfraredCommands) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iInfraredCommands->Value();
    aInfraredCommands.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkUi2Cpp::PropertyInfraredTerminalCommands(std::string& aInfraredTerminalCommands) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iInfraredTerminalCommands->Value();
    aInfraredTerminalCommands.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkUi2Cpp::PropertyDisplayUpsideDown(bool& aDisplayUpsideDown) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDisplayUpsideDown = iDisplayUpsideDown->Value();
}

void CpProxyLinnCoUkUi2Cpp::PropertyDisplayScrollText(bool& aDisplayScrollText) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDisplayScrollText = iDisplayScrollText->Value();
}

void CpProxyLinnCoUkUi2Cpp::PropertyDisplaySleep(bool& aDisplaySleep) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDisplaySleep = iDisplaySleep->Value();
}

void CpProxyLinnCoUkUi2Cpp::PropertyDisplayLedOff(bool& aDisplayLedOff) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDisplayLedOff = iDisplayLedOff->Value();
}

void CpProxyLinnCoUkUi2Cpp::PropertyTerminalInputCode(uint32_t& aTerminalInputCode) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTerminalInputCode = iTerminalInputCode->Value();
}

void CpProxyLinnCoUkUi2Cpp::PropertyTerminalInputName(std::string& aTerminalInputName) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iTerminalInputName->Value();
    aTerminalInputName.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkUi2Cpp::PropertyDisplayPixels(std::string& aDisplayPixels) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iDisplayPixels->Value();
    aDisplayPixels.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkUi2Cpp::DisplayBrightnessPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplayBrightnessChanged != NULL) {
        iDisplayBrightnessChanged();
    }
}

void CpProxyLinnCoUkUi2Cpp::DisplayBrightnessAutoPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplayBrightnessAutoChanged != NULL) {
        iDisplayBrightnessAutoChanged();
    }
}

void CpProxyLinnCoUkUi2Cpp::InfraredCommandsPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iInfraredCommandsChanged != NULL) {
        iInfraredCommandsChanged();
    }
}

void CpProxyLinnCoUkUi2Cpp::InfraredTerminalCommandsPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iInfraredTerminalCommandsChanged != NULL) {
        iInfraredTerminalCommandsChanged();
    }
}

void CpProxyLinnCoUkUi2Cpp::DisplayUpsideDownPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplayUpsideDownChanged != NULL) {
        iDisplayUpsideDownChanged();
    }
}

void CpProxyLinnCoUkUi2Cpp::DisplayScrollTextPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplayScrollTextChanged != NULL) {
        iDisplayScrollTextChanged();
    }
}

void CpProxyLinnCoUkUi2Cpp::DisplaySleepPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplaySleepChanged != NULL) {
        iDisplaySleepChanged();
    }
}

void CpProxyLinnCoUkUi2Cpp::DisplayLedOffPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplayLedOffChanged != NULL) {
        iDisplayLedOffChanged();
    }
}

void CpProxyLinnCoUkUi2Cpp::TerminalInputCodePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTerminalInputCodeChanged != NULL) {
        iTerminalInputCodeChanged();
    }
}

void CpProxyLinnCoUkUi2Cpp::TerminalInputNamePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTerminalInputNameChanged != NULL) {
        iTerminalInputNameChanged();
    }
}

void CpProxyLinnCoUkUi2Cpp::DisplayPixelsPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDisplayPixelsChanged != NULL) {
        iDisplayPixelsChanged();
    }
}

