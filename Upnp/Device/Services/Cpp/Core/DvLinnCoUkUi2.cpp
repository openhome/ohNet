#include <Core/DvLinnCoUkUi2.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkUi2::SetPropertyDisplayBrightness(TUint aValue)
{
    SetPropertyUint(*iPropertyDisplayBrightness, aValue);
}

void DvServiceLinnCoUkUi2::GetPropertyDisplayBrightness(TUint& aValue)
{
    aValue = iPropertyDisplayBrightness->Value();
}

void DvServiceLinnCoUkUi2::SetPropertyDisplayBrightnessAuto(TBool aValue)
{
    SetPropertyBool(*iPropertyDisplayBrightnessAuto, aValue);
}

void DvServiceLinnCoUkUi2::GetPropertyDisplayBrightnessAuto(TBool& aValue)
{
    aValue = iPropertyDisplayBrightnessAuto->Value();
}

void DvServiceLinnCoUkUi2::SetPropertyInfraredCommands(const Brx& aValue)
{
    SetPropertyString(*iPropertyInfraredCommands, aValue);
}

void DvServiceLinnCoUkUi2::GetPropertyInfraredCommands(Brhz& aValue)
{
    aValue.Set(iPropertyInfraredCommands->Value());
}

void DvServiceLinnCoUkUi2::SetPropertyInfraredTerminalCommands(const Brx& aValue)
{
    SetPropertyString(*iPropertyInfraredTerminalCommands, aValue);
}

void DvServiceLinnCoUkUi2::GetPropertyInfraredTerminalCommands(Brhz& aValue)
{
    aValue.Set(iPropertyInfraredTerminalCommands->Value());
}

void DvServiceLinnCoUkUi2::SetPropertyDisplayUpsideDown(TBool aValue)
{
    SetPropertyBool(*iPropertyDisplayUpsideDown, aValue);
}

void DvServiceLinnCoUkUi2::GetPropertyDisplayUpsideDown(TBool& aValue)
{
    aValue = iPropertyDisplayUpsideDown->Value();
}

void DvServiceLinnCoUkUi2::SetPropertyDisplayScrollText(TBool aValue)
{
    SetPropertyBool(*iPropertyDisplayScrollText, aValue);
}

void DvServiceLinnCoUkUi2::GetPropertyDisplayScrollText(TBool& aValue)
{
    aValue = iPropertyDisplayScrollText->Value();
}

void DvServiceLinnCoUkUi2::SetPropertyDisplaySleep(TBool aValue)
{
    SetPropertyBool(*iPropertyDisplaySleep, aValue);
}

void DvServiceLinnCoUkUi2::GetPropertyDisplaySleep(TBool& aValue)
{
    aValue = iPropertyDisplaySleep->Value();
}

void DvServiceLinnCoUkUi2::SetPropertyDisplayLedOff(TBool aValue)
{
    SetPropertyBool(*iPropertyDisplayLedOff, aValue);
}

void DvServiceLinnCoUkUi2::GetPropertyDisplayLedOff(TBool& aValue)
{
    aValue = iPropertyDisplayLedOff->Value();
}

void DvServiceLinnCoUkUi2::SetPropertyTerminalInputCode(TUint aValue)
{
    SetPropertyUint(*iPropertyTerminalInputCode, aValue);
}

void DvServiceLinnCoUkUi2::GetPropertyTerminalInputCode(TUint& aValue)
{
    aValue = iPropertyTerminalInputCode->Value();
}

void DvServiceLinnCoUkUi2::SetPropertyTerminalInputName(const Brx& aValue)
{
    SetPropertyString(*iPropertyTerminalInputName, aValue);
}

void DvServiceLinnCoUkUi2::GetPropertyTerminalInputName(Brhz& aValue)
{
    aValue.Set(iPropertyTerminalInputName->Value());
}

void DvServiceLinnCoUkUi2::SetPropertyDisplayPixels(const Brx& aValue)
{
    SetPropertyBinary(*iPropertyDisplayPixels, aValue);
}

void DvServiceLinnCoUkUi2::GetPropertyDisplayPixels(Brh& aValue)
{
    aValue.Set(iPropertyDisplayPixels->Value());
}

DvServiceLinnCoUkUi2::DvServiceLinnCoUkUi2(DvDevice& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Ui", 2)
{
    Functor empty;
    TChar** allowedValues;
    TUint index;
    iPropertyDisplayBrightness = new PropertyUint(new ParameterUint("DisplayBrightness"), empty);
    iService->AddProperty(iPropertyDisplayBrightness); // passes ownership
    iPropertyDisplayBrightnessAuto = new PropertyBool(new ParameterBool("DisplayBrightnessAuto"), empty);
    iService->AddProperty(iPropertyDisplayBrightnessAuto); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"All";
    allowedValues[index++] = (TChar*)"Cd";
    allowedValues[index++] = (TChar*)"Dvd";
    iPropertyInfraredCommands = new PropertyString(new ParameterString("InfraredCommands", allowedValues, 4), empty);
    delete[] allowedValues;
    iService->AddProperty(iPropertyInfraredCommands); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"None";
    allowedValues[index++] = (TChar*)"All";
    allowedValues[index++] = (TChar*)"Cd";
    allowedValues[index++] = (TChar*)"Dvd";
    iPropertyInfraredTerminalCommands = new PropertyString(new ParameterString("InfraredTerminalCommands", allowedValues, 4), empty);
    delete[] allowedValues;
    iService->AddProperty(iPropertyInfraredTerminalCommands); // passes ownership
    iPropertyDisplayUpsideDown = new PropertyBool(new ParameterBool("DisplayUpsideDown"), empty);
    iService->AddProperty(iPropertyDisplayUpsideDown); // passes ownership
    iPropertyDisplayScrollText = new PropertyBool(new ParameterBool("DisplayScrollText"), empty);
    iService->AddProperty(iPropertyDisplayScrollText); // passes ownership
    iPropertyDisplaySleep = new PropertyBool(new ParameterBool("DisplaySleep"), empty);
    iService->AddProperty(iPropertyDisplaySleep); // passes ownership
    iPropertyDisplayLedOff = new PropertyBool(new ParameterBool("DisplayLedOff"), empty);
    iService->AddProperty(iPropertyDisplayLedOff); // passes ownership
    iPropertyTerminalInputCode = new PropertyUint(new ParameterUint("TerminalInputCode"), empty);
    iService->AddProperty(iPropertyTerminalInputCode); // passes ownership
    iPropertyTerminalInputName = new PropertyString(new ParameterString("TerminalInputName"), empty);
    iService->AddProperty(iPropertyTerminalInputName); // passes ownership
    iPropertyDisplayPixels = new PropertyBinary(new ParameterBinary("DisplayPixels"), empty);
    iService->AddProperty(iPropertyDisplayPixels); // passes ownership
}

void DvServiceLinnCoUkUi2::EnableActionDisplayTestPattern()
{
    Zapp::Action* action = new Zapp::Action("DisplayTestPattern");
    action->AddInputParameter(new ParameterInt("aTestPattern", 0, 6));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoDisplayTestPattern);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionDisplayFill()
{
    Zapp::Action* action = new Zapp::Action("DisplayFill");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoDisplayFill);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionDisplayClear()
{
    Zapp::Action* action = new Zapp::Action("DisplayClear");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoDisplayClear);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionSetTestModeEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetTestModeEnabled");
    action->AddInputParameter(new ParameterBool("aEnabled"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoSetTestModeEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionSimulateInfraredInput()
{
    Zapp::Action* action = new Zapp::Action("SimulateInfraredInput");
    action->AddInputParameter(new ParameterRelated("aCode", *iPropertyTerminalInputCode));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoSimulateInfraredInput);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionSimulateButtonInput()
{
    Zapp::Action* action = new Zapp::Action("SimulateButtonInput");
    action->AddInputParameter(new ParameterRelated("aCode", *iPropertyTerminalInputCode));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoSimulateButtonInput);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionSimulateLightSensor()
{
    Zapp::Action* action = new Zapp::Action("SimulateLightSensor");
    action->AddInputParameter(new ParameterUint("aLightLevel"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoSimulateLightSensor);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionGetLightSensorData()
{
    Zapp::Action* action = new Zapp::Action("GetLightSensorData");
    action->AddOutputParameter(new ParameterUint("aLightLevel"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoGetLightSensorData);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionSetDisplayBrightness()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayBrightness");
    action->AddInputParameter(new ParameterRelated("aBrightness", *iPropertyDisplayBrightness));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoSetDisplayBrightness);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionSetDisplayBrightnessAuto()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayBrightnessAuto");
    action->AddInputParameter(new ParameterRelated("aBrightnessAuto", *iPropertyDisplayBrightnessAuto));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoSetDisplayBrightnessAuto);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionSetInfraredCommands()
{
    Zapp::Action* action = new Zapp::Action("SetInfraredCommands");
    action->AddInputParameter(new ParameterRelated("aCommands", *iPropertyInfraredCommands));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoSetInfraredCommands);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionInfraredCommands()
{
    Zapp::Action* action = new Zapp::Action("InfraredCommands");
    action->AddOutputParameter(new ParameterRelated("aCommands", *iPropertyInfraredCommands));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoInfraredCommands);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionSetInfraredTerminalCommands()
{
    Zapp::Action* action = new Zapp::Action("SetInfraredTerminalCommands");
    action->AddInputParameter(new ParameterRelated("aCommands", *iPropertyInfraredTerminalCommands));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoSetInfraredTerminalCommands);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionInfraredTerminalCommands()
{
    Zapp::Action* action = new Zapp::Action("InfraredTerminalCommands");
    action->AddOutputParameter(new ParameterRelated("aCommands", *iPropertyInfraredTerminalCommands));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoInfraredTerminalCommands);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionDisplayBrightness()
{
    Zapp::Action* action = new Zapp::Action("DisplayBrightness");
    action->AddOutputParameter(new ParameterRelated("aBrightness", *iPropertyDisplayBrightness));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoDisplayBrightness);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionDisplayBrightnessAuto()
{
    Zapp::Action* action = new Zapp::Action("DisplayBrightnessAuto");
    action->AddOutputParameter(new ParameterRelated("aBrightnessAuto", *iPropertyDisplayBrightnessAuto));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoDisplayBrightnessAuto);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionDisplayUpsideDown()
{
    Zapp::Action* action = new Zapp::Action("DisplayUpsideDown");
    action->AddOutputParameter(new ParameterRelated("aUpsideDown", *iPropertyDisplayUpsideDown));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoDisplayUpsideDown);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionSetDisplayUpsideDown()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayUpsideDown");
    action->AddInputParameter(new ParameterRelated("aUpsideDown", *iPropertyDisplayUpsideDown));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoSetDisplayUpsideDown);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionSetDisplayScrollText()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayScrollText");
    action->AddInputParameter(new ParameterRelated("aDisplayScrollText", *iPropertyDisplayScrollText));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoSetDisplayScrollText);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionDisplayScrollText()
{
    Zapp::Action* action = new Zapp::Action("DisplayScrollText");
    action->AddOutputParameter(new ParameterRelated("aDisplayScrollTextEnabled", *iPropertyDisplayScrollText));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoDisplayScrollText);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionSetDisplaySleep()
{
    Zapp::Action* action = new Zapp::Action("SetDisplaySleep");
    action->AddInputParameter(new ParameterRelated("aEnabled", *iPropertyDisplaySleep));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoSetDisplaySleep);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionDisplaySleep()
{
    Zapp::Action* action = new Zapp::Action("DisplaySleep");
    action->AddOutputParameter(new ParameterRelated("aEnabled", *iPropertyDisplaySleep));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoDisplaySleep);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionSetDisplayLedOff()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayLedOff");
    action->AddInputParameter(new ParameterRelated("aOff", *iPropertyDisplayLedOff));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoSetDisplayLedOff);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::EnableActionDisplayLedOff()
{
    Zapp::Action* action = new Zapp::Action("DisplayLedOff");
    action->AddOutputParameter(new ParameterRelated("aOff", *iPropertyDisplayLedOff));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2::DoDisplayLedOff);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2::DoDisplayTestPattern(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aTestPattern = aInvocation.InvocationReadInt("aTestPattern");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DisplayTestPattern(resp, aVersion, aTestPattern);
}

void DvServiceLinnCoUkUi2::DoDisplayFill(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DisplayFill(resp, aVersion);
}

void DvServiceLinnCoUkUi2::DoDisplayClear(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DisplayClear(resp, aVersion);
}

void DvServiceLinnCoUkUi2::DoSetTestModeEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetTestModeEnabled(resp, aVersion, aEnabled);
}

void DvServiceLinnCoUkUi2::DoSimulateInfraredInput(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aCode = aInvocation.InvocationReadUint("aCode");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SimulateInfraredInput(resp, aVersion, aCode);
}

void DvServiceLinnCoUkUi2::DoSimulateButtonInput(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aCode = aInvocation.InvocationReadUint("aCode");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SimulateButtonInput(resp, aVersion, aCode);
}

void DvServiceLinnCoUkUi2::DoSimulateLightSensor(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aLightLevel = aInvocation.InvocationReadUint("aLightLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SimulateLightSensor(resp, aVersion, aLightLevel);
}

void DvServiceLinnCoUkUi2::DoGetLightSensorData(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaLightLevel(aInvocation, "aLightLevel");
    GetLightSensorData(resp, aVersion, respaLightLevel);
}

void DvServiceLinnCoUkUi2::DoSetDisplayBrightness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aBrightness = aInvocation.InvocationReadUint("aBrightness");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDisplayBrightness(resp, aVersion, aBrightness);
}

void DvServiceLinnCoUkUi2::DoSetDisplayBrightnessAuto(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aBrightnessAuto = aInvocation.InvocationReadBool("aBrightnessAuto");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDisplayBrightnessAuto(resp, aVersion, aBrightnessAuto);
}

void DvServiceLinnCoUkUi2::DoSetInfraredCommands(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aCommands;
    aInvocation.InvocationReadString("aCommands", aCommands);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetInfraredCommands(resp, aVersion, aCommands);
}

void DvServiceLinnCoUkUi2::DoInfraredCommands(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaCommands(aInvocation, "aCommands");
    InfraredCommands(resp, aVersion, respaCommands);
}

void DvServiceLinnCoUkUi2::DoSetInfraredTerminalCommands(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aCommands;
    aInvocation.InvocationReadString("aCommands", aCommands);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetInfraredTerminalCommands(resp, aVersion, aCommands);
}

void DvServiceLinnCoUkUi2::DoInfraredTerminalCommands(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaCommands(aInvocation, "aCommands");
    InfraredTerminalCommands(resp, aVersion, respaCommands);
}

void DvServiceLinnCoUkUi2::DoDisplayBrightness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaBrightness(aInvocation, "aBrightness");
    DisplayBrightness(resp, aVersion, respaBrightness);
}

void DvServiceLinnCoUkUi2::DoDisplayBrightnessAuto(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaBrightnessAuto(aInvocation, "aBrightnessAuto");
    DisplayBrightnessAuto(resp, aVersion, respaBrightnessAuto);
}

void DvServiceLinnCoUkUi2::DoDisplayUpsideDown(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaUpsideDown(aInvocation, "aUpsideDown");
    DisplayUpsideDown(resp, aVersion, respaUpsideDown);
}

void DvServiceLinnCoUkUi2::DoSetDisplayUpsideDown(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aUpsideDown = aInvocation.InvocationReadBool("aUpsideDown");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDisplayUpsideDown(resp, aVersion, aUpsideDown);
}

void DvServiceLinnCoUkUi2::DoSetDisplayScrollText(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aDisplayScrollText = aInvocation.InvocationReadBool("aDisplayScrollText");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDisplayScrollText(resp, aVersion, aDisplayScrollText);
}

void DvServiceLinnCoUkUi2::DoDisplayScrollText(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaDisplayScrollTextEnabled(aInvocation, "aDisplayScrollTextEnabled");
    DisplayScrollText(resp, aVersion, respaDisplayScrollTextEnabled);
}

void DvServiceLinnCoUkUi2::DoSetDisplaySleep(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDisplaySleep(resp, aVersion, aEnabled);
}

void DvServiceLinnCoUkUi2::DoDisplaySleep(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaEnabled(aInvocation, "aEnabled");
    DisplaySleep(resp, aVersion, respaEnabled);
}

void DvServiceLinnCoUkUi2::DoSetDisplayLedOff(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aOff = aInvocation.InvocationReadBool("aOff");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDisplayLedOff(resp, aVersion, aOff);
}

void DvServiceLinnCoUkUi2::DoDisplayLedOff(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaOff(aInvocation, "aOff");
    DisplayLedOff(resp, aVersion, respaOff);
}

void DvServiceLinnCoUkUi2::DisplayTestPattern(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aaTestPattern*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::DisplayFill(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::DisplayClear(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::SetTestModeEnabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::SimulateInfraredInput(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaCode*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::SimulateButtonInput(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaCode*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::SimulateLightSensor(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaLightLevel*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::GetLightSensorData(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaLightLevel*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::SetDisplayBrightness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaBrightness*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::SetDisplayBrightnessAuto(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaBrightnessAuto*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::SetInfraredCommands(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaCommands*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::InfraredCommands(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaCommands*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::SetInfraredTerminalCommands(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaCommands*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::InfraredTerminalCommands(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaCommands*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::DisplayBrightness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaBrightness*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::DisplayBrightnessAuto(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaBrightnessAuto*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::DisplayUpsideDown(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaUpsideDown*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::SetDisplayUpsideDown(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaUpsideDown*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::SetDisplayScrollText(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaDisplayScrollText*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::DisplayScrollText(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaDisplayScrollTextEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::SetDisplaySleep(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::DisplaySleep(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::SetDisplayLedOff(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaOff*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2::DisplayLedOff(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaOff*/)
{
    ASSERTS();
}

