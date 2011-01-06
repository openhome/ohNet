#include "DvLinnCoUkUi2.h"
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkUi2::SetPropertyDisplayBrightness(TUint aValue)
{
    return SetPropertyUint(*iPropertyDisplayBrightness, aValue);
}

void DvProviderLinnCoUkUi2::GetPropertyDisplayBrightness(TUint& aValue)
{
    aValue = iPropertyDisplayBrightness->Value();
}

TBool DvProviderLinnCoUkUi2::SetPropertyDisplayBrightnessAuto(TBool aValue)
{
    return SetPropertyBool(*iPropertyDisplayBrightnessAuto, aValue);
}

void DvProviderLinnCoUkUi2::GetPropertyDisplayBrightnessAuto(TBool& aValue)
{
    aValue = iPropertyDisplayBrightnessAuto->Value();
}

TBool DvProviderLinnCoUkUi2::SetPropertyInfraredCommands(const Brx& aValue)
{
    return SetPropertyString(*iPropertyInfraredCommands, aValue);
}

void DvProviderLinnCoUkUi2::GetPropertyInfraredCommands(Brhz& aValue)
{
    aValue.Set(iPropertyInfraredCommands->Value());
}

TBool DvProviderLinnCoUkUi2::SetPropertyInfraredTerminalCommands(const Brx& aValue)
{
    return SetPropertyString(*iPropertyInfraredTerminalCommands, aValue);
}

void DvProviderLinnCoUkUi2::GetPropertyInfraredTerminalCommands(Brhz& aValue)
{
    aValue.Set(iPropertyInfraredTerminalCommands->Value());
}

TBool DvProviderLinnCoUkUi2::SetPropertyDisplayUpsideDown(TBool aValue)
{
    return SetPropertyBool(*iPropertyDisplayUpsideDown, aValue);
}

void DvProviderLinnCoUkUi2::GetPropertyDisplayUpsideDown(TBool& aValue)
{
    aValue = iPropertyDisplayUpsideDown->Value();
}

TBool DvProviderLinnCoUkUi2::SetPropertyDisplayScrollText(TBool aValue)
{
    return SetPropertyBool(*iPropertyDisplayScrollText, aValue);
}

void DvProviderLinnCoUkUi2::GetPropertyDisplayScrollText(TBool& aValue)
{
    aValue = iPropertyDisplayScrollText->Value();
}

TBool DvProviderLinnCoUkUi2::SetPropertyDisplaySleep(TBool aValue)
{
    return SetPropertyBool(*iPropertyDisplaySleep, aValue);
}

void DvProviderLinnCoUkUi2::GetPropertyDisplaySleep(TBool& aValue)
{
    aValue = iPropertyDisplaySleep->Value();
}

TBool DvProviderLinnCoUkUi2::SetPropertyDisplayLedOff(TBool aValue)
{
    return SetPropertyBool(*iPropertyDisplayLedOff, aValue);
}

void DvProviderLinnCoUkUi2::GetPropertyDisplayLedOff(TBool& aValue)
{
    aValue = iPropertyDisplayLedOff->Value();
}

TBool DvProviderLinnCoUkUi2::SetPropertyTerminalInputCode(TUint aValue)
{
    return SetPropertyUint(*iPropertyTerminalInputCode, aValue);
}

void DvProviderLinnCoUkUi2::GetPropertyTerminalInputCode(TUint& aValue)
{
    aValue = iPropertyTerminalInputCode->Value();
}

TBool DvProviderLinnCoUkUi2::SetPropertyTerminalInputName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTerminalInputName, aValue);
}

void DvProviderLinnCoUkUi2::GetPropertyTerminalInputName(Brhz& aValue)
{
    aValue.Set(iPropertyTerminalInputName->Value());
}

TBool DvProviderLinnCoUkUi2::SetPropertyDisplayPixels(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyDisplayPixels, aValue);
}

void DvProviderLinnCoUkUi2::GetPropertyDisplayPixels(Brh& aValue)
{
    aValue.Set(iPropertyDisplayPixels->Value());
}

DvProviderLinnCoUkUi2::DvProviderLinnCoUkUi2(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Ui", 2)
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

void DvProviderLinnCoUkUi2::EnableActionDisplayTestPattern()
{
    Zapp::Action* action = new Zapp::Action("DisplayTestPattern");
    action->AddInputParameter(new ParameterInt("aTestPattern", 0, 6));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoDisplayTestPattern);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionDisplayFill()
{
    Zapp::Action* action = new Zapp::Action("DisplayFill");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoDisplayFill);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionDisplayClear()
{
    Zapp::Action* action = new Zapp::Action("DisplayClear");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoDisplayClear);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionSetTestModeEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetTestModeEnabled");
    action->AddInputParameter(new ParameterBool("aEnabled"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoSetTestModeEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionSimulateInfraredInput()
{
    Zapp::Action* action = new Zapp::Action("SimulateInfraredInput");
    action->AddInputParameter(new ParameterRelated("aCode", *iPropertyTerminalInputCode));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoSimulateInfraredInput);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionSimulateButtonInput()
{
    Zapp::Action* action = new Zapp::Action("SimulateButtonInput");
    action->AddInputParameter(new ParameterRelated("aCode", *iPropertyTerminalInputCode));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoSimulateButtonInput);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionSimulateLightSensor()
{
    Zapp::Action* action = new Zapp::Action("SimulateLightSensor");
    action->AddInputParameter(new ParameterUint("aLightLevel"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoSimulateLightSensor);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionGetLightSensorData()
{
    Zapp::Action* action = new Zapp::Action("GetLightSensorData");
    action->AddOutputParameter(new ParameterUint("aLightLevel"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoGetLightSensorData);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionSetDisplayBrightness()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayBrightness");
    action->AddInputParameter(new ParameterRelated("aBrightness", *iPropertyDisplayBrightness));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoSetDisplayBrightness);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionSetDisplayBrightnessAuto()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayBrightnessAuto");
    action->AddInputParameter(new ParameterRelated("aBrightnessAuto", *iPropertyDisplayBrightnessAuto));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoSetDisplayBrightnessAuto);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionSetInfraredCommands()
{
    Zapp::Action* action = new Zapp::Action("SetInfraredCommands");
    action->AddInputParameter(new ParameterRelated("aCommands", *iPropertyInfraredCommands));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoSetInfraredCommands);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionInfraredCommands()
{
    Zapp::Action* action = new Zapp::Action("InfraredCommands");
    action->AddOutputParameter(new ParameterRelated("aCommands", *iPropertyInfraredCommands));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoInfraredCommands);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionSetInfraredTerminalCommands()
{
    Zapp::Action* action = new Zapp::Action("SetInfraredTerminalCommands");
    action->AddInputParameter(new ParameterRelated("aCommands", *iPropertyInfraredTerminalCommands));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoSetInfraredTerminalCommands);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionInfraredTerminalCommands()
{
    Zapp::Action* action = new Zapp::Action("InfraredTerminalCommands");
    action->AddOutputParameter(new ParameterRelated("aCommands", *iPropertyInfraredTerminalCommands));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoInfraredTerminalCommands);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionDisplayBrightness()
{
    Zapp::Action* action = new Zapp::Action("DisplayBrightness");
    action->AddOutputParameter(new ParameterRelated("aBrightness", *iPropertyDisplayBrightness));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoDisplayBrightness);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionDisplayBrightnessAuto()
{
    Zapp::Action* action = new Zapp::Action("DisplayBrightnessAuto");
    action->AddOutputParameter(new ParameterRelated("aBrightnessAuto", *iPropertyDisplayBrightnessAuto));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoDisplayBrightnessAuto);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionDisplayUpsideDown()
{
    Zapp::Action* action = new Zapp::Action("DisplayUpsideDown");
    action->AddOutputParameter(new ParameterRelated("aUpsideDown", *iPropertyDisplayUpsideDown));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoDisplayUpsideDown);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionSetDisplayUpsideDown()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayUpsideDown");
    action->AddInputParameter(new ParameterRelated("aUpsideDown", *iPropertyDisplayUpsideDown));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoSetDisplayUpsideDown);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionSetDisplayScrollText()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayScrollText");
    action->AddInputParameter(new ParameterRelated("aDisplayScrollText", *iPropertyDisplayScrollText));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoSetDisplayScrollText);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionDisplayScrollText()
{
    Zapp::Action* action = new Zapp::Action("DisplayScrollText");
    action->AddOutputParameter(new ParameterRelated("aDisplayScrollTextEnabled", *iPropertyDisplayScrollText));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoDisplayScrollText);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionSetDisplaySleep()
{
    Zapp::Action* action = new Zapp::Action("SetDisplaySleep");
    action->AddInputParameter(new ParameterRelated("aEnabled", *iPropertyDisplaySleep));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoSetDisplaySleep);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionDisplaySleep()
{
    Zapp::Action* action = new Zapp::Action("DisplaySleep");
    action->AddOutputParameter(new ParameterRelated("aEnabled", *iPropertyDisplaySleep));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoDisplaySleep);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionSetDisplayLedOff()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayLedOff");
    action->AddInputParameter(new ParameterRelated("aOff", *iPropertyDisplayLedOff));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoSetDisplayLedOff);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::EnableActionDisplayLedOff()
{
    Zapp::Action* action = new Zapp::Action("DisplayLedOff");
    action->AddOutputParameter(new ParameterRelated("aOff", *iPropertyDisplayLedOff));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2::DoDisplayLedOff);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2::DoDisplayTestPattern(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aTestPattern = aInvocation.InvocationReadInt("aTestPattern");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DisplayTestPattern(resp, aVersion, aTestPattern);
}

void DvProviderLinnCoUkUi2::DoDisplayFill(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DisplayFill(resp, aVersion);
}

void DvProviderLinnCoUkUi2::DoDisplayClear(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DisplayClear(resp, aVersion);
}

void DvProviderLinnCoUkUi2::DoSetTestModeEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetTestModeEnabled(resp, aVersion, aEnabled);
}

void DvProviderLinnCoUkUi2::DoSimulateInfraredInput(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aCode = aInvocation.InvocationReadUint("aCode");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SimulateInfraredInput(resp, aVersion, aCode);
}

void DvProviderLinnCoUkUi2::DoSimulateButtonInput(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aCode = aInvocation.InvocationReadUint("aCode");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SimulateButtonInput(resp, aVersion, aCode);
}

void DvProviderLinnCoUkUi2::DoSimulateLightSensor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aLightLevel = aInvocation.InvocationReadUint("aLightLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SimulateLightSensor(resp, aVersion, aLightLevel);
}

void DvProviderLinnCoUkUi2::DoGetLightSensorData(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaLightLevel(aInvocation, "aLightLevel");
    GetLightSensorData(resp, aVersion, respaLightLevel);
}

void DvProviderLinnCoUkUi2::DoSetDisplayBrightness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aBrightness = aInvocation.InvocationReadUint("aBrightness");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDisplayBrightness(resp, aVersion, aBrightness);
}

void DvProviderLinnCoUkUi2::DoSetDisplayBrightnessAuto(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aBrightnessAuto = aInvocation.InvocationReadBool("aBrightnessAuto");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDisplayBrightnessAuto(resp, aVersion, aBrightnessAuto);
}

void DvProviderLinnCoUkUi2::DoSetInfraredCommands(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aCommands;
    aInvocation.InvocationReadString("aCommands", aCommands);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetInfraredCommands(resp, aVersion, aCommands);
}

void DvProviderLinnCoUkUi2::DoInfraredCommands(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaCommands(aInvocation, "aCommands");
    InfraredCommands(resp, aVersion, respaCommands);
}

void DvProviderLinnCoUkUi2::DoSetInfraredTerminalCommands(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aCommands;
    aInvocation.InvocationReadString("aCommands", aCommands);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetInfraredTerminalCommands(resp, aVersion, aCommands);
}

void DvProviderLinnCoUkUi2::DoInfraredTerminalCommands(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaCommands(aInvocation, "aCommands");
    InfraredTerminalCommands(resp, aVersion, respaCommands);
}

void DvProviderLinnCoUkUi2::DoDisplayBrightness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaBrightness(aInvocation, "aBrightness");
    DisplayBrightness(resp, aVersion, respaBrightness);
}

void DvProviderLinnCoUkUi2::DoDisplayBrightnessAuto(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaBrightnessAuto(aInvocation, "aBrightnessAuto");
    DisplayBrightnessAuto(resp, aVersion, respaBrightnessAuto);
}

void DvProviderLinnCoUkUi2::DoDisplayUpsideDown(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaUpsideDown(aInvocation, "aUpsideDown");
    DisplayUpsideDown(resp, aVersion, respaUpsideDown);
}

void DvProviderLinnCoUkUi2::DoSetDisplayUpsideDown(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aUpsideDown = aInvocation.InvocationReadBool("aUpsideDown");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDisplayUpsideDown(resp, aVersion, aUpsideDown);
}

void DvProviderLinnCoUkUi2::DoSetDisplayScrollText(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aDisplayScrollText = aInvocation.InvocationReadBool("aDisplayScrollText");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDisplayScrollText(resp, aVersion, aDisplayScrollText);
}

void DvProviderLinnCoUkUi2::DoDisplayScrollText(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaDisplayScrollTextEnabled(aInvocation, "aDisplayScrollTextEnabled");
    DisplayScrollText(resp, aVersion, respaDisplayScrollTextEnabled);
}

void DvProviderLinnCoUkUi2::DoSetDisplaySleep(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDisplaySleep(resp, aVersion, aEnabled);
}

void DvProviderLinnCoUkUi2::DoDisplaySleep(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaEnabled(aInvocation, "aEnabled");
    DisplaySleep(resp, aVersion, respaEnabled);
}

void DvProviderLinnCoUkUi2::DoSetDisplayLedOff(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aOff = aInvocation.InvocationReadBool("aOff");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDisplayLedOff(resp, aVersion, aOff);
}

void DvProviderLinnCoUkUi2::DoDisplayLedOff(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaOff(aInvocation, "aOff");
    DisplayLedOff(resp, aVersion, respaOff);
}

void DvProviderLinnCoUkUi2::DisplayTestPattern(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aaTestPattern*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::DisplayFill(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::DisplayClear(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::SetTestModeEnabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::SimulateInfraredInput(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaCode*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::SimulateButtonInput(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaCode*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::SimulateLightSensor(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaLightLevel*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::GetLightSensorData(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaLightLevel*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::SetDisplayBrightness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaBrightness*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::SetDisplayBrightnessAuto(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaBrightnessAuto*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::SetInfraredCommands(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaCommands*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::InfraredCommands(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaCommands*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::SetInfraredTerminalCommands(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaCommands*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::InfraredTerminalCommands(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaCommands*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::DisplayBrightness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaBrightness*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::DisplayBrightnessAuto(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaBrightnessAuto*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::DisplayUpsideDown(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaUpsideDown*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::SetDisplayUpsideDown(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaUpsideDown*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::SetDisplayScrollText(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaDisplayScrollText*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::DisplayScrollText(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaDisplayScrollTextEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::SetDisplaySleep(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::DisplaySleep(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::SetDisplayLedOff(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaOff*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2::DisplayLedOff(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaOff*/)
{
    ASSERTS();
}

