#include <Std/DvLinnCoUkUi2.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

bool DvProviderLinnCoUkUi2Cpp::SetPropertyDisplayBrightness(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyDisplayBrightness, aValue);
}

void DvProviderLinnCoUkUi2Cpp::GetPropertyDisplayBrightness(uint32_t& aValue)
{
    aValue = iPropertyDisplayBrightness->Value();
}

bool DvProviderLinnCoUkUi2Cpp::SetPropertyDisplayBrightnessAuto(bool aValue)
{
    return SetPropertyBool(*iPropertyDisplayBrightnessAuto, aValue);
}

void DvProviderLinnCoUkUi2Cpp::GetPropertyDisplayBrightnessAuto(bool& aValue)
{
    aValue = iPropertyDisplayBrightnessAuto->Value();
}

bool DvProviderLinnCoUkUi2Cpp::SetPropertyInfraredCommands(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyInfraredCommands, buf);
}

void DvProviderLinnCoUkUi2Cpp::GetPropertyInfraredCommands(std::string& aValue)
{
    const Brx& val = iPropertyInfraredCommands->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkUi2Cpp::SetPropertyInfraredTerminalCommands(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyInfraredTerminalCommands, buf);
}

void DvProviderLinnCoUkUi2Cpp::GetPropertyInfraredTerminalCommands(std::string& aValue)
{
    const Brx& val = iPropertyInfraredTerminalCommands->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkUi2Cpp::SetPropertyDisplayUpsideDown(bool aValue)
{
    return SetPropertyBool(*iPropertyDisplayUpsideDown, aValue);
}

void DvProviderLinnCoUkUi2Cpp::GetPropertyDisplayUpsideDown(bool& aValue)
{
    aValue = iPropertyDisplayUpsideDown->Value();
}

bool DvProviderLinnCoUkUi2Cpp::SetPropertyDisplayScrollText(bool aValue)
{
    return SetPropertyBool(*iPropertyDisplayScrollText, aValue);
}

void DvProviderLinnCoUkUi2Cpp::GetPropertyDisplayScrollText(bool& aValue)
{
    aValue = iPropertyDisplayScrollText->Value();
}

bool DvProviderLinnCoUkUi2Cpp::SetPropertyDisplaySleep(bool aValue)
{
    return SetPropertyBool(*iPropertyDisplaySleep, aValue);
}

void DvProviderLinnCoUkUi2Cpp::GetPropertyDisplaySleep(bool& aValue)
{
    aValue = iPropertyDisplaySleep->Value();
}

bool DvProviderLinnCoUkUi2Cpp::SetPropertyDisplayLedOff(bool aValue)
{
    return SetPropertyBool(*iPropertyDisplayLedOff, aValue);
}

void DvProviderLinnCoUkUi2Cpp::GetPropertyDisplayLedOff(bool& aValue)
{
    aValue = iPropertyDisplayLedOff->Value();
}

bool DvProviderLinnCoUkUi2Cpp::SetPropertyTerminalInputCode(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyTerminalInputCode, aValue);
}

void DvProviderLinnCoUkUi2Cpp::GetPropertyTerminalInputCode(uint32_t& aValue)
{
    aValue = iPropertyTerminalInputCode->Value();
}

bool DvProviderLinnCoUkUi2Cpp::SetPropertyTerminalInputName(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyTerminalInputName, buf);
}

void DvProviderLinnCoUkUi2Cpp::GetPropertyTerminalInputName(std::string& aValue)
{
    const Brx& val = iPropertyTerminalInputName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkUi2Cpp::SetPropertyDisplayPixels(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyBinary(*iPropertyDisplayPixels, buf);
}

void DvProviderLinnCoUkUi2Cpp::GetPropertyDisplayPixels(std::string& aValue)
{
    const Brx& val = iPropertyDisplayPixels->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderLinnCoUkUi2Cpp::DvProviderLinnCoUkUi2Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Ui", 2)
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

void DvProviderLinnCoUkUi2Cpp::EnableActionDisplayTestPattern()
{
    Zapp::Action* action = new Zapp::Action("DisplayTestPattern");
    action->AddInputParameter(new ParameterInt("aTestPattern", 0, 6));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoDisplayTestPattern);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionDisplayFill()
{
    Zapp::Action* action = new Zapp::Action("DisplayFill");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoDisplayFill);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionDisplayClear()
{
    Zapp::Action* action = new Zapp::Action("DisplayClear");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoDisplayClear);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionSetTestModeEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetTestModeEnabled");
    action->AddInputParameter(new ParameterBool("aEnabled"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoSetTestModeEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionSimulateInfraredInput()
{
    Zapp::Action* action = new Zapp::Action("SimulateInfraredInput");
    action->AddInputParameter(new ParameterRelated("aCode", *iPropertyTerminalInputCode));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoSimulateInfraredInput);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionSimulateButtonInput()
{
    Zapp::Action* action = new Zapp::Action("SimulateButtonInput");
    action->AddInputParameter(new ParameterRelated("aCode", *iPropertyTerminalInputCode));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoSimulateButtonInput);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionSimulateLightSensor()
{
    Zapp::Action* action = new Zapp::Action("SimulateLightSensor");
    action->AddInputParameter(new ParameterUint("aLightLevel"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoSimulateLightSensor);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionGetLightSensorData()
{
    Zapp::Action* action = new Zapp::Action("GetLightSensorData");
    action->AddOutputParameter(new ParameterUint("aLightLevel"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoGetLightSensorData);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionSetDisplayBrightness()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayBrightness");
    action->AddInputParameter(new ParameterRelated("aBrightness", *iPropertyDisplayBrightness));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoSetDisplayBrightness);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionSetDisplayBrightnessAuto()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayBrightnessAuto");
    action->AddInputParameter(new ParameterRelated("aBrightnessAuto", *iPropertyDisplayBrightnessAuto));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoSetDisplayBrightnessAuto);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionSetInfraredCommands()
{
    Zapp::Action* action = new Zapp::Action("SetInfraredCommands");
    action->AddInputParameter(new ParameterRelated("aCommands", *iPropertyInfraredCommands));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoSetInfraredCommands);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionInfraredCommands()
{
    Zapp::Action* action = new Zapp::Action("InfraredCommands");
    action->AddOutputParameter(new ParameterRelated("aCommands", *iPropertyInfraredCommands));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoInfraredCommands);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionSetInfraredTerminalCommands()
{
    Zapp::Action* action = new Zapp::Action("SetInfraredTerminalCommands");
    action->AddInputParameter(new ParameterRelated("aCommands", *iPropertyInfraredTerminalCommands));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoSetInfraredTerminalCommands);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionInfraredTerminalCommands()
{
    Zapp::Action* action = new Zapp::Action("InfraredTerminalCommands");
    action->AddOutputParameter(new ParameterRelated("aCommands", *iPropertyInfraredTerminalCommands));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoInfraredTerminalCommands);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionDisplayBrightness()
{
    Zapp::Action* action = new Zapp::Action("DisplayBrightness");
    action->AddOutputParameter(new ParameterRelated("aBrightness", *iPropertyDisplayBrightness));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoDisplayBrightness);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionDisplayBrightnessAuto()
{
    Zapp::Action* action = new Zapp::Action("DisplayBrightnessAuto");
    action->AddOutputParameter(new ParameterRelated("aBrightnessAuto", *iPropertyDisplayBrightnessAuto));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoDisplayBrightnessAuto);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionDisplayUpsideDown()
{
    Zapp::Action* action = new Zapp::Action("DisplayUpsideDown");
    action->AddOutputParameter(new ParameterRelated("aUpsideDown", *iPropertyDisplayUpsideDown));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoDisplayUpsideDown);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionSetDisplayUpsideDown()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayUpsideDown");
    action->AddInputParameter(new ParameterRelated("aUpsideDown", *iPropertyDisplayUpsideDown));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoSetDisplayUpsideDown);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionSetDisplayScrollText()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayScrollText");
    action->AddInputParameter(new ParameterRelated("aDisplayScrollText", *iPropertyDisplayScrollText));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoSetDisplayScrollText);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionDisplayScrollText()
{
    Zapp::Action* action = new Zapp::Action("DisplayScrollText");
    action->AddOutputParameter(new ParameterRelated("aDisplayScrollTextEnabled", *iPropertyDisplayScrollText));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoDisplayScrollText);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionSetDisplaySleep()
{
    Zapp::Action* action = new Zapp::Action("SetDisplaySleep");
    action->AddInputParameter(new ParameterRelated("aEnabled", *iPropertyDisplaySleep));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoSetDisplaySleep);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionDisplaySleep()
{
    Zapp::Action* action = new Zapp::Action("DisplaySleep");
    action->AddOutputParameter(new ParameterRelated("aEnabled", *iPropertyDisplaySleep));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoDisplaySleep);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionSetDisplayLedOff()
{
    Zapp::Action* action = new Zapp::Action("SetDisplayLedOff");
    action->AddInputParameter(new ParameterRelated("aOff", *iPropertyDisplayLedOff));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoSetDisplayLedOff);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::EnableActionDisplayLedOff()
{
    Zapp::Action* action = new Zapp::Action("DisplayLedOff");
    action->AddOutputParameter(new ParameterRelated("aOff", *iPropertyDisplayLedOff));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkUi2Cpp::DoDisplayLedOff);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkUi2Cpp::DoDisplayTestPattern(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t aTestPattern = aInvocation.InvocationReadInt("aTestPattern");
    aInvocation.InvocationReadEnd();
    DisplayTestPattern(aVersion, aTestPattern);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoDisplayFill(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DisplayFill(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoDisplayClear(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DisplayClear(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoSetTestModeEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    SetTestModeEnabled(aVersion, aEnabled);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoSimulateInfraredInput(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aCode = aInvocation.InvocationReadUint("aCode");
    aInvocation.InvocationReadEnd();
    SimulateInfraredInput(aVersion, aCode);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoSimulateButtonInput(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aCode = aInvocation.InvocationReadUint("aCode");
    aInvocation.InvocationReadEnd();
    SimulateButtonInput(aVersion, aCode);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoSimulateLightSensor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aLightLevel = aInvocation.InvocationReadUint("aLightLevel");
    aInvocation.InvocationReadEnd();
    SimulateLightSensor(aVersion, aLightLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoGetLightSensorData(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkUi2Cpp::DoSetDisplayBrightness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aBrightness = aInvocation.InvocationReadUint("aBrightness");
    aInvocation.InvocationReadEnd();
    SetDisplayBrightness(aVersion, aBrightness);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoSetDisplayBrightnessAuto(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aBrightnessAuto = aInvocation.InvocationReadBool("aBrightnessAuto");
    aInvocation.InvocationReadEnd();
    SetDisplayBrightnessAuto(aVersion, aBrightnessAuto);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoSetInfraredCommands(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkUi2Cpp::DoInfraredCommands(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaCommands;
    InfraredCommands(aVersion, respaCommands);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraCommands(aInvocation, "aCommands");
    Brn buf_aCommands((const TByte*)respaCommands.c_str(), (TUint)respaCommands.length());
    respWriteraCommands.Write(buf_aCommands);
    aInvocation.InvocationWriteStringEnd("aCommands");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoSetInfraredTerminalCommands(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkUi2Cpp::DoInfraredTerminalCommands(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaCommands;
    InfraredTerminalCommands(aVersion, respaCommands);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraCommands(aInvocation, "aCommands");
    Brn buf_aCommands((const TByte*)respaCommands.c_str(), (TUint)respaCommands.length());
    respWriteraCommands.Write(buf_aCommands);
    aInvocation.InvocationWriteStringEnd("aCommands");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoDisplayBrightness(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkUi2Cpp::DoDisplayBrightnessAuto(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkUi2Cpp::DoDisplayUpsideDown(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkUi2Cpp::DoSetDisplayUpsideDown(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aUpsideDown = aInvocation.InvocationReadBool("aUpsideDown");
    aInvocation.InvocationReadEnd();
    SetDisplayUpsideDown(aVersion, aUpsideDown);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoSetDisplayScrollText(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aDisplayScrollText = aInvocation.InvocationReadBool("aDisplayScrollText");
    aInvocation.InvocationReadEnd();
    SetDisplayScrollText(aVersion, aDisplayScrollText);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoDisplayScrollText(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkUi2Cpp::DoSetDisplaySleep(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    SetDisplaySleep(aVersion, aEnabled);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoDisplaySleep(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkUi2Cpp::DoSetDisplayLedOff(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aOff = aInvocation.InvocationReadBool("aOff");
    aInvocation.InvocationReadEnd();
    SetDisplayLedOff(aVersion, aOff);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkUi2Cpp::DoDisplayLedOff(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkUi2Cpp::DisplayTestPattern(uint32_t /*aVersion*/, int32_t /*aaTestPattern*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::DisplayFill(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::DisplayClear(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::SetTestModeEnabled(uint32_t /*aVersion*/, bool /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::SimulateInfraredInput(uint32_t /*aVersion*/, uint32_t /*aaCode*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::SimulateButtonInput(uint32_t /*aVersion*/, uint32_t /*aaCode*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::SimulateLightSensor(uint32_t /*aVersion*/, uint32_t /*aaLightLevel*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::GetLightSensorData(uint32_t /*aVersion*/, uint32_t& /*aaLightLevel*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::SetDisplayBrightness(uint32_t /*aVersion*/, uint32_t /*aaBrightness*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::SetDisplayBrightnessAuto(uint32_t /*aVersion*/, bool /*aaBrightnessAuto*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::SetInfraredCommands(uint32_t /*aVersion*/, const std::string& /*aaCommands*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::InfraredCommands(uint32_t /*aVersion*/, std::string& /*aaCommands*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::SetInfraredTerminalCommands(uint32_t /*aVersion*/, const std::string& /*aaCommands*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::InfraredTerminalCommands(uint32_t /*aVersion*/, std::string& /*aaCommands*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::DisplayBrightness(uint32_t /*aVersion*/, uint32_t& /*aaBrightness*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::DisplayBrightnessAuto(uint32_t /*aVersion*/, bool& /*aaBrightnessAuto*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::DisplayUpsideDown(uint32_t /*aVersion*/, bool& /*aaUpsideDown*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::SetDisplayUpsideDown(uint32_t /*aVersion*/, bool /*aaUpsideDown*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::SetDisplayScrollText(uint32_t /*aVersion*/, bool /*aaDisplayScrollText*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::DisplayScrollText(uint32_t /*aVersion*/, bool& /*aaDisplayScrollTextEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::SetDisplaySleep(uint32_t /*aVersion*/, bool /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::DisplaySleep(uint32_t /*aVersion*/, bool& /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::SetDisplayLedOff(uint32_t /*aVersion*/, bool /*aaOff*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkUi2Cpp::DisplayLedOff(uint32_t /*aVersion*/, bool& /*aaOff*/)
{
    ASSERTS();
}

