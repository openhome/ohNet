#include <Std/DvLinnCoUkUi2.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkUi2Cpp::SetPropertyDisplayBrightness(uint32_t aValue)
{
    SetPropertyUint(*iPropertyDisplayBrightness, aValue);
}

void DvServiceLinnCoUkUi2Cpp::GetPropertyDisplayBrightness(uint32_t& aValue)
{
    aValue = iPropertyDisplayBrightness->Value();
}

void DvServiceLinnCoUkUi2Cpp::SetPropertyDisplayBrightnessAuto(bool aValue)
{
    SetPropertyBool(*iPropertyDisplayBrightnessAuto, aValue);
}

void DvServiceLinnCoUkUi2Cpp::GetPropertyDisplayBrightnessAuto(bool& aValue)
{
    aValue = iPropertyDisplayBrightnessAuto->Value();
}

void DvServiceLinnCoUkUi2Cpp::SetPropertyInfraredCommands(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyInfraredCommands, buf);
}

void DvServiceLinnCoUkUi2Cpp::GetPropertyInfraredCommands(std::string& aValue)
{
    const Brx& val = iPropertyInfraredCommands->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkUi2Cpp::SetPropertyInfraredTerminalCommands(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyInfraredTerminalCommands, buf);
}

void DvServiceLinnCoUkUi2Cpp::GetPropertyInfraredTerminalCommands(std::string& aValue)
{
    const Brx& val = iPropertyInfraredTerminalCommands->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkUi2Cpp::SetPropertyDisplayUpsideDown(bool aValue)
{
    SetPropertyBool(*iPropertyDisplayUpsideDown, aValue);
}

void DvServiceLinnCoUkUi2Cpp::GetPropertyDisplayUpsideDown(bool& aValue)
{
    aValue = iPropertyDisplayUpsideDown->Value();
}

void DvServiceLinnCoUkUi2Cpp::SetPropertyDisplayScrollText(bool aValue)
{
    SetPropertyBool(*iPropertyDisplayScrollText, aValue);
}

void DvServiceLinnCoUkUi2Cpp::GetPropertyDisplayScrollText(bool& aValue)
{
    aValue = iPropertyDisplayScrollText->Value();
}

void DvServiceLinnCoUkUi2Cpp::SetPropertyDisplaySleep(bool aValue)
{
    SetPropertyBool(*iPropertyDisplaySleep, aValue);
}

void DvServiceLinnCoUkUi2Cpp::GetPropertyDisplaySleep(bool& aValue)
{
    aValue = iPropertyDisplaySleep->Value();
}

void DvServiceLinnCoUkUi2Cpp::SetPropertyDisplayLedOff(bool aValue)
{
    SetPropertyBool(*iPropertyDisplayLedOff, aValue);
}

void DvServiceLinnCoUkUi2Cpp::GetPropertyDisplayLedOff(bool& aValue)
{
    aValue = iPropertyDisplayLedOff->Value();
}

void DvServiceLinnCoUkUi2Cpp::SetPropertyTerminalInputCode(uint32_t aValue)
{
    SetPropertyUint(*iPropertyTerminalInputCode, aValue);
}

void DvServiceLinnCoUkUi2Cpp::GetPropertyTerminalInputCode(uint32_t& aValue)
{
    aValue = iPropertyTerminalInputCode->Value();
}

void DvServiceLinnCoUkUi2Cpp::SetPropertyTerminalInputName(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyTerminalInputName, buf);
}

void DvServiceLinnCoUkUi2Cpp::GetPropertyTerminalInputName(std::string& aValue)
{
    const Brx& val = iPropertyTerminalInputName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkUi2Cpp::SetPropertyDisplayPixels(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyBinary(*iPropertyDisplayPixels, buf);
}

void DvServiceLinnCoUkUi2Cpp::GetPropertyDisplayPixels(std::string& aValue)
{
    const Brx& val = iPropertyDisplayPixels->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvServiceLinnCoUkUi2Cpp::DvServiceLinnCoUkUi2Cpp(DvDeviceStd& aDevice)
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

void DvServiceLinnCoUkUi2Cpp::EnableActionDisplayTestPattern()
{
    Zapp::Action* action = new Zapp::Action("DisplayTestPattern");
    action->AddInputParameter(new ParameterInt("aTestPattern", 0, 6));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoDisplayTestPattern);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionDisplayFill()
{
    Zapp::Action* action = new Zapp::Action("DisplayFill");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoDisplayFill);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionDisplayClear()
{
    Zapp::Action* action = new Zapp::Action("DisplayClear");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoDisplayClear);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionSetTestModeEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetTestModeEnabled");
    action->AddInputParameter(new ParameterBool("aEnabled"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoSetTestModeEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionSimulateInfraredInput()
{
    Zapp::Action* action = new Zapp::Action("SimulateInfraredInput");
    action->AddInputParameter(new ParameterRelated("aCode", *iPropertyTerminalInputCode));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoSimulateInfraredInput);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionSimulateButtonInput()
{
    Zapp::Action* action = new Zapp::Action("SimulateButtonInput");
    action->AddInputParameter(new ParameterRelated("aCode", *iPropertyTerminalInputCode));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoSimulateButtonInput);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionSimulateLightSensor()
{
    Zapp::Action* action = new Zapp::Action("SimulateLightSensor");
    action->AddInputParameter(new ParameterUint("aLightLevel"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoSimulateLightSensor);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionGetLightSensorData()
{
    Zapp::Action* action = new Zapp::Action("GetLightSensorData");
    action->AddOutputParameter(new ParameterUint("aLightLevel"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoGetLightSensorData);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionSetDisplayBrightness()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayBrightness");
    action->AddInputParameter(new ParameterRelated("aBrightness", *iPropertyDisplayBrightness));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoSetDisplayBrightness);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionSetDisplayBrightnessAuto()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayBrightnessAuto");
    action->AddInputParameter(new ParameterRelated("aBrightnessAuto", *iPropertyDisplayBrightnessAuto));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoSetDisplayBrightnessAuto);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionSetInfraredCommands()
{
    Zapp::Action* action = new Zapp::Action("SetInfraredCommands");
    action->AddInputParameter(new ParameterRelated("aCommands", *iPropertyInfraredCommands));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoSetInfraredCommands);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionInfraredCommands()
{
    Zapp::Action* action = new Zapp::Action("InfraredCommands");
    action->AddOutputParameter(new ParameterRelated("aCommands", *iPropertyInfraredCommands));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoInfraredCommands);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionSetInfraredTerminalCommands()
{
    Zapp::Action* action = new Zapp::Action("SetInfraredTerminalCommands");
    action->AddInputParameter(new ParameterRelated("aCommands", *iPropertyInfraredTerminalCommands));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoSetInfraredTerminalCommands);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionInfraredTerminalCommands()
{
    Zapp::Action* action = new Zapp::Action("InfraredTerminalCommands");
    action->AddOutputParameter(new ParameterRelated("aCommands", *iPropertyInfraredTerminalCommands));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoInfraredTerminalCommands);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionDisplayBrightness()
{
    Zapp::Action* action = new Zapp::Action("DisplayBrightness");
    action->AddOutputParameter(new ParameterRelated("aBrightness", *iPropertyDisplayBrightness));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoDisplayBrightness);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionDisplayBrightnessAuto()
{
    Zapp::Action* action = new Zapp::Action("DisplayBrightnessAuto");
    action->AddOutputParameter(new ParameterRelated("aBrightnessAuto", *iPropertyDisplayBrightnessAuto));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoDisplayBrightnessAuto);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionDisplayUpsideDown()
{
    Zapp::Action* action = new Zapp::Action("DisplayUpsideDown");
    action->AddOutputParameter(new ParameterRelated("aUpsideDown", *iPropertyDisplayUpsideDown));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoDisplayUpsideDown);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionSetDisplayUpsideDown()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayUpsideDown");
    action->AddInputParameter(new ParameterRelated("aUpsideDown", *iPropertyDisplayUpsideDown));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoSetDisplayUpsideDown);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionSetDisplayScrollText()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayScrollText");
    action->AddInputParameter(new ParameterRelated("aDisplayScrollText", *iPropertyDisplayScrollText));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoSetDisplayScrollText);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionDisplayScrollText()
{
    Zapp::Action* action = new Zapp::Action("DisplayScrollText");
    action->AddOutputParameter(new ParameterRelated("aDisplayScrollTextEnabled", *iPropertyDisplayScrollText));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoDisplayScrollText);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionSetDisplaySleep()
{
    Zapp::Action* action = new Zapp::Action("SetDisplaySleep");
    action->AddInputParameter(new ParameterRelated("aEnabled", *iPropertyDisplaySleep));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoSetDisplaySleep);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionDisplaySleep()
{
    Zapp::Action* action = new Zapp::Action("DisplaySleep");
    action->AddOutputParameter(new ParameterRelated("aEnabled", *iPropertyDisplaySleep));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoDisplaySleep);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionSetDisplayLedOff()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayLedOff");
    action->AddInputParameter(new ParameterRelated("aOff", *iPropertyDisplayLedOff));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoSetDisplayLedOff);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::EnableActionDisplayLedOff()
{
    Zapp::Action* action = new Zapp::Action("DisplayLedOff");
    action->AddOutputParameter(new ParameterRelated("aOff", *iPropertyDisplayLedOff));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkUi2Cpp::DoDisplayLedOff);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkUi2Cpp::DoDisplayTestPattern(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t aTestPattern = aInvocation.InvocationReadInt("aTestPattern");
    aInvocation.InvocationReadEnd();
    DisplayTestPattern(aVersion, aTestPattern);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoDisplayFill(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DisplayFill(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoDisplayClear(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DisplayClear(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoSetTestModeEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    SetTestModeEnabled(aVersion, aEnabled);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoSimulateInfraredInput(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aCode = aInvocation.InvocationReadUint("aCode");
    aInvocation.InvocationReadEnd();
    SimulateInfraredInput(aVersion, aCode);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoSimulateButtonInput(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aCode = aInvocation.InvocationReadUint("aCode");
    aInvocation.InvocationReadEnd();
    SimulateButtonInput(aVersion, aCode);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoSimulateLightSensor(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aLightLevel = aInvocation.InvocationReadUint("aLightLevel");
    aInvocation.InvocationReadEnd();
    SimulateLightSensor(aVersion, aLightLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoGetLightSensorData(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaLightLevel;
    GetLightSensorData(aVersion, respaLightLevel);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraLightLevel(aInvocation, "aLightLevel");
    respWriteraLightLevel.Write(respaLightLevel);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoSetDisplayBrightness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aBrightness = aInvocation.InvocationReadUint("aBrightness");
    aInvocation.InvocationReadEnd();
    SetDisplayBrightness(aVersion, aBrightness);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoSetDisplayBrightnessAuto(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aBrightnessAuto = aInvocation.InvocationReadBool("aBrightnessAuto");
    aInvocation.InvocationReadEnd();
    SetDisplayBrightnessAuto(aVersion, aBrightnessAuto);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoSetInfraredCommands(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aCommands;
    aInvocation.InvocationReadString("aCommands", buf_aCommands);
    std::string aCommands((const char*)buf_aCommands.Ptr(), buf_aCommands.Bytes());
    aInvocation.InvocationReadEnd();
    SetInfraredCommands(aVersion, aCommands);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoInfraredCommands(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaCommands;
    InfraredCommands(aVersion, respaCommands);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraCommands(aInvocation, "aCommands");
    Brn buf_aCommands((const TByte*)respaCommands.c_str(), respaCommands.length());
    respWriteraCommands.Write(buf_aCommands);
    aInvocation.InvocationWriteStringEnd("aCommands");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoSetInfraredTerminalCommands(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aCommands;
    aInvocation.InvocationReadString("aCommands", buf_aCommands);
    std::string aCommands((const char*)buf_aCommands.Ptr(), buf_aCommands.Bytes());
    aInvocation.InvocationReadEnd();
    SetInfraredTerminalCommands(aVersion, aCommands);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoInfraredTerminalCommands(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaCommands;
    InfraredTerminalCommands(aVersion, respaCommands);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraCommands(aInvocation, "aCommands");
    Brn buf_aCommands((const TByte*)respaCommands.c_str(), respaCommands.length());
    respWriteraCommands.Write(buf_aCommands);
    aInvocation.InvocationWriteStringEnd("aCommands");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoDisplayBrightness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaBrightness;
    DisplayBrightness(aVersion, respaBrightness);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraBrightness(aInvocation, "aBrightness");
    respWriteraBrightness.Write(respaBrightness);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoDisplayBrightnessAuto(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaBrightnessAuto;
    DisplayBrightnessAuto(aVersion, respaBrightnessAuto);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraBrightnessAuto(aInvocation, "aBrightnessAuto");
    respWriteraBrightnessAuto.Write(respaBrightnessAuto);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoDisplayUpsideDown(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaUpsideDown;
    DisplayUpsideDown(aVersion, respaUpsideDown);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraUpsideDown(aInvocation, "aUpsideDown");
    respWriteraUpsideDown.Write(respaUpsideDown);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoSetDisplayUpsideDown(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aUpsideDown = aInvocation.InvocationReadBool("aUpsideDown");
    aInvocation.InvocationReadEnd();
    SetDisplayUpsideDown(aVersion, aUpsideDown);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoSetDisplayScrollText(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aDisplayScrollText = aInvocation.InvocationReadBool("aDisplayScrollText");
    aInvocation.InvocationReadEnd();
    SetDisplayScrollText(aVersion, aDisplayScrollText);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoDisplayScrollText(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaDisplayScrollTextEnabled;
    DisplayScrollText(aVersion, respaDisplayScrollTextEnabled);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraDisplayScrollTextEnabled(aInvocation, "aDisplayScrollTextEnabled");
    respWriteraDisplayScrollTextEnabled.Write(respaDisplayScrollTextEnabled);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoSetDisplaySleep(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    SetDisplaySleep(aVersion, aEnabled);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoDisplaySleep(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaEnabled;
    DisplaySleep(aVersion, respaEnabled);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraEnabled(aInvocation, "aEnabled");
    respWriteraEnabled.Write(respaEnabled);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoSetDisplayLedOff(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aOff = aInvocation.InvocationReadBool("aOff");
    aInvocation.InvocationReadEnd();
    SetDisplayLedOff(aVersion, aOff);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DoDisplayLedOff(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaOff;
    DisplayLedOff(aVersion, respaOff);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraOff(aInvocation, "aOff");
    respWriteraOff.Write(respaOff);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkUi2Cpp::DisplayTestPattern(uint32_t /*aVersion*/, int32_t /*aaTestPattern*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::DisplayFill(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::DisplayClear(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::SetTestModeEnabled(uint32_t /*aVersion*/, bool /*aaEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::SimulateInfraredInput(uint32_t /*aVersion*/, uint32_t /*aaCode*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::SimulateButtonInput(uint32_t /*aVersion*/, uint32_t /*aaCode*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::SimulateLightSensor(uint32_t /*aVersion*/, uint32_t /*aaLightLevel*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::GetLightSensorData(uint32_t /*aVersion*/, uint32_t& /*aaLightLevel*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::SetDisplayBrightness(uint32_t /*aVersion*/, uint32_t /*aaBrightness*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::SetDisplayBrightnessAuto(uint32_t /*aVersion*/, bool /*aaBrightnessAuto*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::SetInfraredCommands(uint32_t /*aVersion*/, const std::string& /*aaCommands*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::InfraredCommands(uint32_t /*aVersion*/, std::string& /*aaCommands*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::SetInfraredTerminalCommands(uint32_t /*aVersion*/, const std::string& /*aaCommands*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::InfraredTerminalCommands(uint32_t /*aVersion*/, std::string& /*aaCommands*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::DisplayBrightness(uint32_t /*aVersion*/, uint32_t& /*aaBrightness*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::DisplayBrightnessAuto(uint32_t /*aVersion*/, bool& /*aaBrightnessAuto*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::DisplayUpsideDown(uint32_t /*aVersion*/, bool& /*aaUpsideDown*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::SetDisplayUpsideDown(uint32_t /*aVersion*/, bool /*aaUpsideDown*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::SetDisplayScrollText(uint32_t /*aVersion*/, bool /*aaDisplayScrollText*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::DisplayScrollText(uint32_t /*aVersion*/, bool& /*aaDisplayScrollTextEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::SetDisplaySleep(uint32_t /*aVersion*/, bool /*aaEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::DisplaySleep(uint32_t /*aVersion*/, bool& /*aaEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::SetDisplayLedOff(uint32_t /*aVersion*/, bool /*aaOff*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkUi2Cpp::DisplayLedOff(uint32_t /*aVersion*/, bool& /*aaOff*/)
{
    ASSERTS();
}

