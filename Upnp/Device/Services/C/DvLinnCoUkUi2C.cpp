#include "DvLinnCoUkUi2.h"
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

class DvProviderLinnCoUkUi2C : public DvProvider
{
public:
    DvProviderLinnCoUkUi2C(DvDeviceC aDevice);
    TBool SetPropertyDisplayBrightness(TUint aValue);
    void GetPropertyDisplayBrightness(TUint& aValue);
    TBool SetPropertyDisplayBrightnessAuto(TBool aValue);
    void GetPropertyDisplayBrightnessAuto(TBool& aValue);
    TBool SetPropertyInfraredCommands(const Brx& aValue);
    void GetPropertyInfraredCommands(Brhz& aValue);
    TBool SetPropertyInfraredTerminalCommands(const Brx& aValue);
    void GetPropertyInfraredTerminalCommands(Brhz& aValue);
    TBool SetPropertyDisplayUpsideDown(TBool aValue);
    void GetPropertyDisplayUpsideDown(TBool& aValue);
    TBool SetPropertyDisplayScrollText(TBool aValue);
    void GetPropertyDisplayScrollText(TBool& aValue);
    TBool SetPropertyDisplaySleep(TBool aValue);
    void GetPropertyDisplaySleep(TBool& aValue);
    TBool SetPropertyDisplayLedOff(TBool aValue);
    void GetPropertyDisplayLedOff(TBool& aValue);
    TBool SetPropertyTerminalInputCode(TUint aValue);
    void GetPropertyTerminalInputCode(TUint& aValue);
    TBool SetPropertyTerminalInputName(const Brx& aValue);
    void GetPropertyTerminalInputName(Brhz& aValue);
    TBool SetPropertyDisplayPixels(const Brx& aValue);
    void GetPropertyDisplayPixels(Brh& aValue);
    void EnableActionDisplayTestPattern(CallbackUi2DisplayTestPattern aCallback, void* aPtr);
    void EnableActionDisplayFill(CallbackUi2DisplayFill aCallback, void* aPtr);
    void EnableActionDisplayClear(CallbackUi2DisplayClear aCallback, void* aPtr);
    void EnableActionSetTestModeEnabled(CallbackUi2SetTestModeEnabled aCallback, void* aPtr);
    void EnableActionSimulateInfraredInput(CallbackUi2SimulateInfraredInput aCallback, void* aPtr);
    void EnableActionSimulateButtonInput(CallbackUi2SimulateButtonInput aCallback, void* aPtr);
    void EnableActionSimulateLightSensor(CallbackUi2SimulateLightSensor aCallback, void* aPtr);
    void EnableActionGetLightSensorData(CallbackUi2GetLightSensorData aCallback, void* aPtr);
    void EnableActionSetDisplayBrightness(CallbackUi2SetDisplayBrightness aCallback, void* aPtr);
    void EnableActionSetDisplayBrightnessAuto(CallbackUi2SetDisplayBrightnessAuto aCallback, void* aPtr);
    void EnableActionSetInfraredCommands(CallbackUi2SetInfraredCommands aCallback, void* aPtr);
    void EnableActionInfraredCommands(CallbackUi2InfraredCommands aCallback, void* aPtr);
    void EnableActionSetInfraredTerminalCommands(CallbackUi2SetInfraredTerminalCommands aCallback, void* aPtr);
    void EnableActionInfraredTerminalCommands(CallbackUi2InfraredTerminalCommands aCallback, void* aPtr);
    void EnableActionDisplayBrightness(CallbackUi2DisplayBrightness aCallback, void* aPtr);
    void EnableActionDisplayBrightnessAuto(CallbackUi2DisplayBrightnessAuto aCallback, void* aPtr);
    void EnableActionDisplayUpsideDown(CallbackUi2DisplayUpsideDown aCallback, void* aPtr);
    void EnableActionSetDisplayUpsideDown(CallbackUi2SetDisplayUpsideDown aCallback, void* aPtr);
    void EnableActionSetDisplayScrollText(CallbackUi2SetDisplayScrollText aCallback, void* aPtr);
    void EnableActionDisplayScrollText(CallbackUi2DisplayScrollText aCallback, void* aPtr);
    void EnableActionSetDisplaySleep(CallbackUi2SetDisplaySleep aCallback, void* aPtr);
    void EnableActionDisplaySleep(CallbackUi2DisplaySleep aCallback, void* aPtr);
    void EnableActionSetDisplayLedOff(CallbackUi2SetDisplayLedOff aCallback, void* aPtr);
    void EnableActionDisplayLedOff(CallbackUi2DisplayLedOff aCallback, void* aPtr);
private:
    void DoDisplayTestPattern(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayFill(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayClear(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetTestModeEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoSimulateInfraredInput(IDviInvocation& aInvocation, TUint aVersion);
    void DoSimulateButtonInput(IDviInvocation& aInvocation, TUint aVersion);
    void DoSimulateLightSensor(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetLightSensorData(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayBrightness(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayBrightnessAuto(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetInfraredCommands(IDviInvocation& aInvocation, TUint aVersion);
    void DoInfraredCommands(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetInfraredTerminalCommands(IDviInvocation& aInvocation, TUint aVersion);
    void DoInfraredTerminalCommands(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayBrightness(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayBrightnessAuto(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayUpsideDown(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayUpsideDown(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayScrollText(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayScrollText(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDisplaySleep(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplaySleep(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayLedOff(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayLedOff(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackUi2DisplayTestPattern iCallbackDisplayTestPattern;
    void* iPtrDisplayTestPattern;
    CallbackUi2DisplayFill iCallbackDisplayFill;
    void* iPtrDisplayFill;
    CallbackUi2DisplayClear iCallbackDisplayClear;
    void* iPtrDisplayClear;
    CallbackUi2SetTestModeEnabled iCallbackSetTestModeEnabled;
    void* iPtrSetTestModeEnabled;
    CallbackUi2SimulateInfraredInput iCallbackSimulateInfraredInput;
    void* iPtrSimulateInfraredInput;
    CallbackUi2SimulateButtonInput iCallbackSimulateButtonInput;
    void* iPtrSimulateButtonInput;
    CallbackUi2SimulateLightSensor iCallbackSimulateLightSensor;
    void* iPtrSimulateLightSensor;
    CallbackUi2GetLightSensorData iCallbackGetLightSensorData;
    void* iPtrGetLightSensorData;
    CallbackUi2SetDisplayBrightness iCallbackSetDisplayBrightness;
    void* iPtrSetDisplayBrightness;
    CallbackUi2SetDisplayBrightnessAuto iCallbackSetDisplayBrightnessAuto;
    void* iPtrSetDisplayBrightnessAuto;
    CallbackUi2SetInfraredCommands iCallbackSetInfraredCommands;
    void* iPtrSetInfraredCommands;
    CallbackUi2InfraredCommands iCallbackInfraredCommands;
    void* iPtrInfraredCommands;
    CallbackUi2SetInfraredTerminalCommands iCallbackSetInfraredTerminalCommands;
    void* iPtrSetInfraredTerminalCommands;
    CallbackUi2InfraredTerminalCommands iCallbackInfraredTerminalCommands;
    void* iPtrInfraredTerminalCommands;
    CallbackUi2DisplayBrightness iCallbackDisplayBrightness;
    void* iPtrDisplayBrightness;
    CallbackUi2DisplayBrightnessAuto iCallbackDisplayBrightnessAuto;
    void* iPtrDisplayBrightnessAuto;
    CallbackUi2DisplayUpsideDown iCallbackDisplayUpsideDown;
    void* iPtrDisplayUpsideDown;
    CallbackUi2SetDisplayUpsideDown iCallbackSetDisplayUpsideDown;
    void* iPtrSetDisplayUpsideDown;
    CallbackUi2SetDisplayScrollText iCallbackSetDisplayScrollText;
    void* iPtrSetDisplayScrollText;
    CallbackUi2DisplayScrollText iCallbackDisplayScrollText;
    void* iPtrDisplayScrollText;
    CallbackUi2SetDisplaySleep iCallbackSetDisplaySleep;
    void* iPtrSetDisplaySleep;
    CallbackUi2DisplaySleep iCallbackDisplaySleep;
    void* iPtrDisplaySleep;
    CallbackUi2SetDisplayLedOff iCallbackSetDisplayLedOff;
    void* iPtrSetDisplayLedOff;
    CallbackUi2DisplayLedOff iCallbackDisplayLedOff;
    void* iPtrDisplayLedOff;
    PropertyUint* iPropertyDisplayBrightness;
    PropertyBool* iPropertyDisplayBrightnessAuto;
    PropertyString* iPropertyInfraredCommands;
    PropertyString* iPropertyInfraredTerminalCommands;
    PropertyBool* iPropertyDisplayUpsideDown;
    PropertyBool* iPropertyDisplayScrollText;
    PropertyBool* iPropertyDisplaySleep;
    PropertyBool* iPropertyDisplayLedOff;
    PropertyUint* iPropertyTerminalInputCode;
    PropertyString* iPropertyTerminalInputName;
    PropertyBinary* iPropertyDisplayPixels;
};

DvProviderLinnCoUkUi2C::DvProviderLinnCoUkUi2C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Ui", 2)
{
    
    TChar** allowedValues;
    TUint index;
    iPropertyDisplayBrightness = new PropertyUint(new ParameterUint("DisplayBrightness"));
    iService->AddProperty(iPropertyDisplayBrightness); // passes ownership
    iPropertyDisplayBrightnessAuto = new PropertyBool(new ParameterBool("DisplayBrightnessAuto"));
    iService->AddProperty(iPropertyDisplayBrightnessAuto); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"All";
    allowedValues[index++] = (TChar*)"Cd";
    allowedValues[index++] = (TChar*)"Dvd";
    iPropertyInfraredCommands = new PropertyString(new ParameterString("InfraredCommands", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyInfraredCommands); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"All";
    allowedValues[index++] = (TChar*)"Cd";
    allowedValues[index++] = (TChar*)"Dvd";
    iPropertyInfraredTerminalCommands = new PropertyString(new ParameterString("InfraredTerminalCommands", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyInfraredTerminalCommands); // passes ownership
    iPropertyDisplayUpsideDown = new PropertyBool(new ParameterBool("DisplayUpsideDown"));
    iService->AddProperty(iPropertyDisplayUpsideDown); // passes ownership
    iPropertyDisplayScrollText = new PropertyBool(new ParameterBool("DisplayScrollText"));
    iService->AddProperty(iPropertyDisplayScrollText); // passes ownership
    iPropertyDisplaySleep = new PropertyBool(new ParameterBool("DisplaySleep"));
    iService->AddProperty(iPropertyDisplaySleep); // passes ownership
    iPropertyDisplayLedOff = new PropertyBool(new ParameterBool("DisplayLedOff"));
    iService->AddProperty(iPropertyDisplayLedOff); // passes ownership
    iPropertyTerminalInputCode = new PropertyUint(new ParameterUint("TerminalInputCode"));
    iService->AddProperty(iPropertyTerminalInputCode); // passes ownership
    iPropertyTerminalInputName = new PropertyString(new ParameterString("TerminalInputName"));
    iService->AddProperty(iPropertyTerminalInputName); // passes ownership
    iPropertyDisplayPixels = new PropertyBinary(new ParameterBinary("DisplayPixels"));
    iService->AddProperty(iPropertyDisplayPixels); // passes ownership
}

TBool DvProviderLinnCoUkUi2C::SetPropertyDisplayBrightness(TUint aValue)
{
    return SetPropertyUint(*iPropertyDisplayBrightness, aValue);
}

void DvProviderLinnCoUkUi2C::GetPropertyDisplayBrightness(TUint& aValue)
{
    aValue = iPropertyDisplayBrightness->Value();
}

TBool DvProviderLinnCoUkUi2C::SetPropertyDisplayBrightnessAuto(TBool aValue)
{
    return SetPropertyBool(*iPropertyDisplayBrightnessAuto, aValue);
}

void DvProviderLinnCoUkUi2C::GetPropertyDisplayBrightnessAuto(TBool& aValue)
{
    aValue = iPropertyDisplayBrightnessAuto->Value();
}

TBool DvProviderLinnCoUkUi2C::SetPropertyInfraredCommands(const Brx& aValue)
{
    return SetPropertyString(*iPropertyInfraredCommands, aValue);
}

void DvProviderLinnCoUkUi2C::GetPropertyInfraredCommands(Brhz& aValue)
{
    aValue.Set(iPropertyInfraredCommands->Value());
}

TBool DvProviderLinnCoUkUi2C::SetPropertyInfraredTerminalCommands(const Brx& aValue)
{
    return SetPropertyString(*iPropertyInfraredTerminalCommands, aValue);
}

void DvProviderLinnCoUkUi2C::GetPropertyInfraredTerminalCommands(Brhz& aValue)
{
    aValue.Set(iPropertyInfraredTerminalCommands->Value());
}

TBool DvProviderLinnCoUkUi2C::SetPropertyDisplayUpsideDown(TBool aValue)
{
    return SetPropertyBool(*iPropertyDisplayUpsideDown, aValue);
}

void DvProviderLinnCoUkUi2C::GetPropertyDisplayUpsideDown(TBool& aValue)
{
    aValue = iPropertyDisplayUpsideDown->Value();
}

TBool DvProviderLinnCoUkUi2C::SetPropertyDisplayScrollText(TBool aValue)
{
    return SetPropertyBool(*iPropertyDisplayScrollText, aValue);
}

void DvProviderLinnCoUkUi2C::GetPropertyDisplayScrollText(TBool& aValue)
{
    aValue = iPropertyDisplayScrollText->Value();
}

TBool DvProviderLinnCoUkUi2C::SetPropertyDisplaySleep(TBool aValue)
{
    return SetPropertyBool(*iPropertyDisplaySleep, aValue);
}

void DvProviderLinnCoUkUi2C::GetPropertyDisplaySleep(TBool& aValue)
{
    aValue = iPropertyDisplaySleep->Value();
}

TBool DvProviderLinnCoUkUi2C::SetPropertyDisplayLedOff(TBool aValue)
{
    return SetPropertyBool(*iPropertyDisplayLedOff, aValue);
}

void DvProviderLinnCoUkUi2C::GetPropertyDisplayLedOff(TBool& aValue)
{
    aValue = iPropertyDisplayLedOff->Value();
}

TBool DvProviderLinnCoUkUi2C::SetPropertyTerminalInputCode(TUint aValue)
{
    return SetPropertyUint(*iPropertyTerminalInputCode, aValue);
}

void DvProviderLinnCoUkUi2C::GetPropertyTerminalInputCode(TUint& aValue)
{
    aValue = iPropertyTerminalInputCode->Value();
}

TBool DvProviderLinnCoUkUi2C::SetPropertyTerminalInputName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTerminalInputName, aValue);
}

void DvProviderLinnCoUkUi2C::GetPropertyTerminalInputName(Brhz& aValue)
{
    aValue.Set(iPropertyTerminalInputName->Value());
}

TBool DvProviderLinnCoUkUi2C::SetPropertyDisplayPixels(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyDisplayPixels, aValue);
}

void DvProviderLinnCoUkUi2C::GetPropertyDisplayPixels(Brh& aValue)
{
    aValue.Set(iPropertyDisplayPixels->Value());
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayTestPattern(CallbackUi2DisplayTestPattern aCallback, void* aPtr)
{
    iCallbackDisplayTestPattern = aCallback;
    iPtrDisplayTestPattern = aPtr;
    Zapp::Action* action = new Zapp::Action("DisplayTestPattern");
    action->AddInputParameter(new ParameterInt("aTestPattern", 0, 6));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoDisplayTestPattern);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayFill(CallbackUi2DisplayFill aCallback, void* aPtr)
{
    iCallbackDisplayFill = aCallback;
    iPtrDisplayFill = aPtr;
    Zapp::Action* action = new Zapp::Action("DisplayFill");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoDisplayFill);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayClear(CallbackUi2DisplayClear aCallback, void* aPtr)
{
    iCallbackDisplayClear = aCallback;
    iPtrDisplayClear = aPtr;
    Zapp::Action* action = new Zapp::Action("DisplayClear");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoDisplayClear);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionSetTestModeEnabled(CallbackUi2SetTestModeEnabled aCallback, void* aPtr)
{
    iCallbackSetTestModeEnabled = aCallback;
    iPtrSetTestModeEnabled = aPtr;
    Zapp::Action* action = new Zapp::Action("SetTestModeEnabled");
    action->AddInputParameter(new ParameterBool("aEnabled"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoSetTestModeEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionSimulateInfraredInput(CallbackUi2SimulateInfraredInput aCallback, void* aPtr)
{
    iCallbackSimulateInfraredInput = aCallback;
    iPtrSimulateInfraredInput = aPtr;
    Zapp::Action* action = new Zapp::Action("SimulateInfraredInput");
    action->AddInputParameter(new ParameterRelated("aCode", *iPropertyTerminalInputCode));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoSimulateInfraredInput);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionSimulateButtonInput(CallbackUi2SimulateButtonInput aCallback, void* aPtr)
{
    iCallbackSimulateButtonInput = aCallback;
    iPtrSimulateButtonInput = aPtr;
    Zapp::Action* action = new Zapp::Action("SimulateButtonInput");
    action->AddInputParameter(new ParameterRelated("aCode", *iPropertyTerminalInputCode));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoSimulateButtonInput);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionSimulateLightSensor(CallbackUi2SimulateLightSensor aCallback, void* aPtr)
{
    iCallbackSimulateLightSensor = aCallback;
    iPtrSimulateLightSensor = aPtr;
    Zapp::Action* action = new Zapp::Action("SimulateLightSensor");
    action->AddInputParameter(new ParameterUint("aLightLevel"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoSimulateLightSensor);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionGetLightSensorData(CallbackUi2GetLightSensorData aCallback, void* aPtr)
{
    iCallbackGetLightSensorData = aCallback;
    iPtrGetLightSensorData = aPtr;
    Zapp::Action* action = new Zapp::Action("GetLightSensorData");
    action->AddOutputParameter(new ParameterUint("aLightLevel"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoGetLightSensorData);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionSetDisplayBrightness(CallbackUi2SetDisplayBrightness aCallback, void* aPtr)
{
    iCallbackSetDisplayBrightness = aCallback;
    iPtrSetDisplayBrightness = aPtr;
    Zapp::Action* action = new Zapp::Action("SetDisplayBrightness");
    action->AddInputParameter(new ParameterRelated("aBrightness", *iPropertyDisplayBrightness));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoSetDisplayBrightness);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionSetDisplayBrightnessAuto(CallbackUi2SetDisplayBrightnessAuto aCallback, void* aPtr)
{
    iCallbackSetDisplayBrightnessAuto = aCallback;
    iPtrSetDisplayBrightnessAuto = aPtr;
    Zapp::Action* action = new Zapp::Action("SetDisplayBrightnessAuto");
    action->AddInputParameter(new ParameterRelated("aBrightnessAuto", *iPropertyDisplayBrightnessAuto));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoSetDisplayBrightnessAuto);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionSetInfraredCommands(CallbackUi2SetInfraredCommands aCallback, void* aPtr)
{
    iCallbackSetInfraredCommands = aCallback;
    iPtrSetInfraredCommands = aPtr;
    Zapp::Action* action = new Zapp::Action("SetInfraredCommands");
    action->AddInputParameter(new ParameterRelated("aCommands", *iPropertyInfraredCommands));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoSetInfraredCommands);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionInfraredCommands(CallbackUi2InfraredCommands aCallback, void* aPtr)
{
    iCallbackInfraredCommands = aCallback;
    iPtrInfraredCommands = aPtr;
    Zapp::Action* action = new Zapp::Action("InfraredCommands");
    action->AddOutputParameter(new ParameterRelated("aCommands", *iPropertyInfraredCommands));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoInfraredCommands);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionSetInfraredTerminalCommands(CallbackUi2SetInfraredTerminalCommands aCallback, void* aPtr)
{
    iCallbackSetInfraredTerminalCommands = aCallback;
    iPtrSetInfraredTerminalCommands = aPtr;
    Zapp::Action* action = new Zapp::Action("SetInfraredTerminalCommands");
    action->AddInputParameter(new ParameterRelated("aCommands", *iPropertyInfraredTerminalCommands));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoSetInfraredTerminalCommands);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionInfraredTerminalCommands(CallbackUi2InfraredTerminalCommands aCallback, void* aPtr)
{
    iCallbackInfraredTerminalCommands = aCallback;
    iPtrInfraredTerminalCommands = aPtr;
    Zapp::Action* action = new Zapp::Action("InfraredTerminalCommands");
    action->AddOutputParameter(new ParameterRelated("aCommands", *iPropertyInfraredTerminalCommands));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoInfraredTerminalCommands);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayBrightness(CallbackUi2DisplayBrightness aCallback, void* aPtr)
{
    iCallbackDisplayBrightness = aCallback;
    iPtrDisplayBrightness = aPtr;
    Zapp::Action* action = new Zapp::Action("DisplayBrightness");
    action->AddOutputParameter(new ParameterRelated("aBrightness", *iPropertyDisplayBrightness));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoDisplayBrightness);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayBrightnessAuto(CallbackUi2DisplayBrightnessAuto aCallback, void* aPtr)
{
    iCallbackDisplayBrightnessAuto = aCallback;
    iPtrDisplayBrightnessAuto = aPtr;
    Zapp::Action* action = new Zapp::Action("DisplayBrightnessAuto");
    action->AddOutputParameter(new ParameterRelated("aBrightnessAuto", *iPropertyDisplayBrightnessAuto));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoDisplayBrightnessAuto);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayUpsideDown(CallbackUi2DisplayUpsideDown aCallback, void* aPtr)
{
    iCallbackDisplayUpsideDown = aCallback;
    iPtrDisplayUpsideDown = aPtr;
    Zapp::Action* action = new Zapp::Action("DisplayUpsideDown");
    action->AddOutputParameter(new ParameterRelated("aUpsideDown", *iPropertyDisplayUpsideDown));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoDisplayUpsideDown);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionSetDisplayUpsideDown(CallbackUi2SetDisplayUpsideDown aCallback, void* aPtr)
{
    iCallbackSetDisplayUpsideDown = aCallback;
    iPtrSetDisplayUpsideDown = aPtr;
    Zapp::Action* action = new Zapp::Action("SetDisplayUpsideDown");
    action->AddInputParameter(new ParameterRelated("aUpsideDown", *iPropertyDisplayUpsideDown));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoSetDisplayUpsideDown);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionSetDisplayScrollText(CallbackUi2SetDisplayScrollText aCallback, void* aPtr)
{
    iCallbackSetDisplayScrollText = aCallback;
    iPtrSetDisplayScrollText = aPtr;
    Zapp::Action* action = new Zapp::Action("SetDisplayScrollText");
    action->AddInputParameter(new ParameterRelated("aDisplayScrollText", *iPropertyDisplayScrollText));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoSetDisplayScrollText);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayScrollText(CallbackUi2DisplayScrollText aCallback, void* aPtr)
{
    iCallbackDisplayScrollText = aCallback;
    iPtrDisplayScrollText = aPtr;
    Zapp::Action* action = new Zapp::Action("DisplayScrollText");
    action->AddOutputParameter(new ParameterRelated("aDisplayScrollTextEnabled", *iPropertyDisplayScrollText));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoDisplayScrollText);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionSetDisplaySleep(CallbackUi2SetDisplaySleep aCallback, void* aPtr)
{
    iCallbackSetDisplaySleep = aCallback;
    iPtrSetDisplaySleep = aPtr;
    Zapp::Action* action = new Zapp::Action("SetDisplaySleep");
    action->AddInputParameter(new ParameterRelated("aEnabled", *iPropertyDisplaySleep));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoSetDisplaySleep);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionDisplaySleep(CallbackUi2DisplaySleep aCallback, void* aPtr)
{
    iCallbackDisplaySleep = aCallback;
    iPtrDisplaySleep = aPtr;
    Zapp::Action* action = new Zapp::Action("DisplaySleep");
    action->AddOutputParameter(new ParameterRelated("aEnabled", *iPropertyDisplaySleep));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoDisplaySleep);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionSetDisplayLedOff(CallbackUi2SetDisplayLedOff aCallback, void* aPtr)
{
    iCallbackSetDisplayLedOff = aCallback;
    iPtrSetDisplayLedOff = aPtr;
    Zapp::Action* action = new Zapp::Action("SetDisplayLedOff");
    action->AddInputParameter(new ParameterRelated("aOff", *iPropertyDisplayLedOff));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoSetDisplayLedOff);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayLedOff(CallbackUi2DisplayLedOff aCallback, void* aPtr)
{
    iCallbackDisplayLedOff = aCallback;
    iPtrDisplayLedOff = aPtr;
    Zapp::Action* action = new Zapp::Action("DisplayLedOff");
    action->AddOutputParameter(new ParameterRelated("aOff", *iPropertyDisplayLedOff));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2C::DoDisplayLedOff);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2C::DoDisplayTestPattern(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aTestPattern = aInvocation.InvocationReadInt("aTestPattern");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackDisplayTestPattern != NULL);
    if (0 != iCallbackDisplayTestPattern(iPtrDisplayTestPattern, aVersion, aTestPattern)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoDisplayFill(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackDisplayFill != NULL);
    if (0 != iCallbackDisplayFill(iPtrDisplayFill, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoDisplayClear(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackDisplayClear != NULL);
    if (0 != iCallbackDisplayClear(iPtrDisplayClear, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoSetTestModeEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetTestModeEnabled != NULL);
    if (0 != iCallbackSetTestModeEnabled(iPtrSetTestModeEnabled, aVersion, aEnabled)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoSimulateInfraredInput(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aCode = aInvocation.InvocationReadUint("aCode");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSimulateInfraredInput != NULL);
    if (0 != iCallbackSimulateInfraredInput(iPtrSimulateInfraredInput, aVersion, aCode)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoSimulateButtonInput(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aCode = aInvocation.InvocationReadUint("aCode");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSimulateButtonInput != NULL);
    if (0 != iCallbackSimulateButtonInput(iPtrSimulateButtonInput, aVersion, aCode)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoSimulateLightSensor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aLightLevel = aInvocation.InvocationReadUint("aLightLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSimulateLightSensor != NULL);
    if (0 != iCallbackSimulateLightSensor(iPtrSimulateLightSensor, aVersion, aLightLevel)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoGetLightSensorData(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aLightLevel;
    ASSERT(iCallbackGetLightSensorData != NULL);
    if (0 != iCallbackGetLightSensorData(iPtrGetLightSensorData, aVersion, &aLightLevel)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaLightLevel(aInvocation, "aLightLevel");
    resp.Start();
    respaLightLevel.Write(aLightLevel);
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoSetDisplayBrightness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aBrightness = aInvocation.InvocationReadUint("aBrightness");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetDisplayBrightness != NULL);
    if (0 != iCallbackSetDisplayBrightness(iPtrSetDisplayBrightness, aVersion, aBrightness)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoSetDisplayBrightnessAuto(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aBrightnessAuto = aInvocation.InvocationReadBool("aBrightnessAuto");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetDisplayBrightnessAuto != NULL);
    if (0 != iCallbackSetDisplayBrightnessAuto(iPtrSetDisplayBrightnessAuto, aVersion, aBrightnessAuto)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoSetInfraredCommands(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aCommands;
    aInvocation.InvocationReadString("aCommands", aCommands);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetInfraredCommands != NULL);
    if (0 != iCallbackSetInfraredCommands(iPtrSetInfraredCommands, aVersion, (const char*)aCommands.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoInfraredCommands(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aCommands;
    ASSERT(iCallbackInfraredCommands != NULL);
    if (0 != iCallbackInfraredCommands(iPtrInfraredCommands, aVersion, &aCommands)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaCommands(aInvocation, "aCommands");
    resp.Start();
    Brhz bufaCommands((const TChar*)aCommands);
    ZappFreeExternal(aCommands);
    respaCommands.Write(bufaCommands);
    respaCommands.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoSetInfraredTerminalCommands(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aCommands;
    aInvocation.InvocationReadString("aCommands", aCommands);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetInfraredTerminalCommands != NULL);
    if (0 != iCallbackSetInfraredTerminalCommands(iPtrSetInfraredTerminalCommands, aVersion, (const char*)aCommands.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoInfraredTerminalCommands(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aCommands;
    ASSERT(iCallbackInfraredTerminalCommands != NULL);
    if (0 != iCallbackInfraredTerminalCommands(iPtrInfraredTerminalCommands, aVersion, &aCommands)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaCommands(aInvocation, "aCommands");
    resp.Start();
    Brhz bufaCommands((const TChar*)aCommands);
    ZappFreeExternal(aCommands);
    respaCommands.Write(bufaCommands);
    respaCommands.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoDisplayBrightness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aBrightness;
    ASSERT(iCallbackDisplayBrightness != NULL);
    if (0 != iCallbackDisplayBrightness(iPtrDisplayBrightness, aVersion, &aBrightness)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaBrightness(aInvocation, "aBrightness");
    resp.Start();
    respaBrightness.Write(aBrightness);
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoDisplayBrightnessAuto(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aBrightnessAuto;
    ASSERT(iCallbackDisplayBrightnessAuto != NULL);
    if (0 != iCallbackDisplayBrightnessAuto(iPtrDisplayBrightnessAuto, aVersion, &aBrightnessAuto)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaBrightnessAuto(aInvocation, "aBrightnessAuto");
    resp.Start();
    respaBrightnessAuto.Write((aBrightnessAuto!=0));
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoDisplayUpsideDown(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aUpsideDown;
    ASSERT(iCallbackDisplayUpsideDown != NULL);
    if (0 != iCallbackDisplayUpsideDown(iPtrDisplayUpsideDown, aVersion, &aUpsideDown)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaUpsideDown(aInvocation, "aUpsideDown");
    resp.Start();
    respaUpsideDown.Write((aUpsideDown!=0));
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoSetDisplayUpsideDown(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aUpsideDown = aInvocation.InvocationReadBool("aUpsideDown");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetDisplayUpsideDown != NULL);
    if (0 != iCallbackSetDisplayUpsideDown(iPtrSetDisplayUpsideDown, aVersion, aUpsideDown)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoSetDisplayScrollText(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aDisplayScrollText = aInvocation.InvocationReadBool("aDisplayScrollText");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetDisplayScrollText != NULL);
    if (0 != iCallbackSetDisplayScrollText(iPtrSetDisplayScrollText, aVersion, aDisplayScrollText)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoDisplayScrollText(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aDisplayScrollTextEnabled;
    ASSERT(iCallbackDisplayScrollText != NULL);
    if (0 != iCallbackDisplayScrollText(iPtrDisplayScrollText, aVersion, &aDisplayScrollTextEnabled)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaDisplayScrollTextEnabled(aInvocation, "aDisplayScrollTextEnabled");
    resp.Start();
    respaDisplayScrollTextEnabled.Write((aDisplayScrollTextEnabled!=0));
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoSetDisplaySleep(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetDisplaySleep != NULL);
    if (0 != iCallbackSetDisplaySleep(iPtrSetDisplaySleep, aVersion, aEnabled)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoDisplaySleep(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aEnabled;
    ASSERT(iCallbackDisplaySleep != NULL);
    if (0 != iCallbackDisplaySleep(iPtrDisplaySleep, aVersion, &aEnabled)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaEnabled(aInvocation, "aEnabled");
    resp.Start();
    respaEnabled.Write((aEnabled!=0));
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoSetDisplayLedOff(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aOff = aInvocation.InvocationReadBool("aOff");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetDisplayLedOff != NULL);
    if (0 != iCallbackSetDisplayLedOff(iPtrSetDisplayLedOff, aVersion, aOff)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkUi2C::DoDisplayLedOff(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aOff;
    ASSERT(iCallbackDisplayLedOff != NULL);
    if (0 != iCallbackDisplayLedOff(iPtrDisplayLedOff, aVersion, &aOff)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaOff(aInvocation, "aOff");
    resp.Start();
    respaOff.Write((aOff!=0));
    resp.End();
}



THandle DvProviderLinnCoUkUi2Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkUi2C(aDevice);
}

void DvProviderLinnCoUkUi2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider);
}

void DvProviderLinnCoUkUi2EnableActionDisplayTestPattern(THandle aProvider, CallbackUi2DisplayTestPattern aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayTestPattern(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayFill(THandle aProvider, CallbackUi2DisplayFill aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayFill(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayClear(THandle aProvider, CallbackUi2DisplayClear aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayClear(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetTestModeEnabled(THandle aProvider, CallbackUi2SetTestModeEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetTestModeEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSimulateInfraredInput(THandle aProvider, CallbackUi2SimulateInfraredInput aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSimulateInfraredInput(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSimulateButtonInput(THandle aProvider, CallbackUi2SimulateButtonInput aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSimulateButtonInput(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSimulateLightSensor(THandle aProvider, CallbackUi2SimulateLightSensor aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSimulateLightSensor(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionGetLightSensorData(THandle aProvider, CallbackUi2GetLightSensorData aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionGetLightSensorData(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetDisplayBrightness(THandle aProvider, CallbackUi2SetDisplayBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetDisplayBrightness(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetDisplayBrightnessAuto(THandle aProvider, CallbackUi2SetDisplayBrightnessAuto aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetDisplayBrightnessAuto(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetInfraredCommands(THandle aProvider, CallbackUi2SetInfraredCommands aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetInfraredCommands(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionInfraredCommands(THandle aProvider, CallbackUi2InfraredCommands aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionInfraredCommands(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetInfraredTerminalCommands(THandle aProvider, CallbackUi2SetInfraredTerminalCommands aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetInfraredTerminalCommands(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionInfraredTerminalCommands(THandle aProvider, CallbackUi2InfraredTerminalCommands aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionInfraredTerminalCommands(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayBrightness(THandle aProvider, CallbackUi2DisplayBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayBrightness(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayBrightnessAuto(THandle aProvider, CallbackUi2DisplayBrightnessAuto aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayBrightnessAuto(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayUpsideDown(THandle aProvider, CallbackUi2DisplayUpsideDown aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayUpsideDown(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetDisplayUpsideDown(THandle aProvider, CallbackUi2SetDisplayUpsideDown aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetDisplayUpsideDown(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetDisplayScrollText(THandle aProvider, CallbackUi2SetDisplayScrollText aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetDisplayScrollText(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayScrollText(THandle aProvider, CallbackUi2DisplayScrollText aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayScrollText(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetDisplaySleep(THandle aProvider, CallbackUi2SetDisplaySleep aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetDisplaySleep(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplaySleep(THandle aProvider, CallbackUi2DisplaySleep aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplaySleep(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetDisplayLedOff(THandle aProvider, CallbackUi2SetDisplayLedOff aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetDisplayLedOff(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayLedOff(THandle aProvider, CallbackUi2DisplayLedOff aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayLedOff(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplayBrightness(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplayBrightness(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplayBrightness(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplayBrightness(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplayBrightnessAuto(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplayBrightnessAuto((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplayBrightnessAuto(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplayBrightnessAuto(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkUi2SetPropertyInfraredCommands(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyInfraredCommands(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyInfraredCommands(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyInfraredCommands(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkUi2SetPropertyInfraredTerminalCommands(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyInfraredTerminalCommands(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyInfraredTerminalCommands(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyInfraredTerminalCommands(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplayUpsideDown(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplayUpsideDown((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplayUpsideDown(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplayUpsideDown(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplayScrollText(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplayScrollText((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplayScrollText(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplayScrollText(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplaySleep(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplaySleep((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplaySleep(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplaySleep(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplayLedOff(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplayLedOff((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplayLedOff(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplayLedOff(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkUi2SetPropertyTerminalInputCode(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyTerminalInputCode(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyTerminalInputCode(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyTerminalInputCode(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkUi2SetPropertyTerminalInputName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyTerminalInputName(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyTerminalInputName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyTerminalInputName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplayPixels(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplayPixels(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplayPixels(THandle aProvider, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplayPixels(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

