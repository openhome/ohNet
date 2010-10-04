#include <Std/DvLinnCoUkDelay1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkDelay1Cpp::SetPropertyPresetXml(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyPresetXml, buf);
}

void DvServiceLinnCoUkDelay1Cpp::GetPropertyPresetXml(std::string& aValue)
{
    const Brx& val = iPropertyPresetXml->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkDelay1Cpp::SetPropertyPresetIndex(uint32_t aValue)
{
    SetPropertyUint(*iPropertyPresetIndex, aValue);
}

void DvServiceLinnCoUkDelay1Cpp::GetPropertyPresetIndex(uint32_t& aValue)
{
    aValue = iPropertyPresetIndex->Value();
}

DvServiceLinnCoUkDelay1Cpp::DvServiceLinnCoUkDelay1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Delay", 1)
{
    Functor empty;
    iPropertyPresetXml = new PropertyString(new ParameterString("PresetXml"), empty);
    iService->AddProperty(iPropertyPresetXml); // passes ownership
    iPropertyPresetIndex = new PropertyUint(new ParameterUint("PresetIndex"), empty);
    iService->AddProperty(iPropertyPresetIndex); // passes ownership
}

void DvServiceLinnCoUkDelay1Cpp::EnableActionPresetXml()
{
    Zapp::Action* action = new Zapp::Action("PresetXml");
    action->AddOutputParameter(new ParameterRelated("aPresetXml", *iPropertyPresetXml));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1Cpp::DoPresetXml);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1Cpp::EnableActionPresetIndex()
{
    Zapp::Action* action = new Zapp::Action("PresetIndex");
    action->AddOutputParameter(new ParameterRelated("aIndex", *iPropertyPresetIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1Cpp::DoPresetIndex);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1Cpp::EnableActionSetPresetIndex()
{
    Zapp::Action* action = new Zapp::Action("SetPresetIndex");
    action->AddInputParameter(new ParameterRelated("aIndex", *iPropertyPresetIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1Cpp::DoSetPresetIndex);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1Cpp::EnableActionSetPresetDelay()
{
    Zapp::Action* action = new Zapp::Action("SetPresetDelay");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterUint("aDelay"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1Cpp::DoSetPresetDelay);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1Cpp::EnableActionSetPresetVisible()
{
    Zapp::Action* action = new Zapp::Action("SetPresetVisible");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterBool("aVisible"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1Cpp::DoSetPresetVisible);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1Cpp::EnableActionSetPresetName()
{
    Zapp::Action* action = new Zapp::Action("SetPresetName");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterString("aName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1Cpp::DoSetPresetName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1Cpp::EnableActionDelayMinimum()
{
    Zapp::Action* action = new Zapp::Action("DelayMinimum");
    action->AddOutputParameter(new ParameterUint("aDelay"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1Cpp::DoDelayMinimum);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1Cpp::EnableActionDelayMaximum()
{
    Zapp::Action* action = new Zapp::Action("DelayMaximum");
    action->AddOutputParameter(new ParameterUint("aDelay"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1Cpp::DoDelayMaximum);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1Cpp::EnableActionPresetCount()
{
    Zapp::Action* action = new Zapp::Action("PresetCount");
    action->AddOutputParameter(new ParameterUint("aCount"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1Cpp::DoPresetCount);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1Cpp::DoPresetXml(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaPresetXml;
    PresetXml(aVersion, respaPresetXml);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraPresetXml(aInvocation, "aPresetXml");
    Brn buf_aPresetXml((const TByte*)respaPresetXml.c_str(), respaPresetXml.length());
    respWriteraPresetXml.Write(buf_aPresetXml);
    aInvocation.InvocationWriteStringEnd("aPresetXml");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDelay1Cpp::DoPresetIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaIndex;
    PresetIndex(aVersion, respaIndex);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraIndex(aInvocation, "aIndex");
    respWriteraIndex.Write(respaIndex);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDelay1Cpp::DoSetPresetIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    SetPresetIndex(aVersion, aIndex);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDelay1Cpp::DoSetPresetDelay(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aIndex = aInvocation.InvocationReadUint("aIndex");
    uint32_t aDelay = aInvocation.InvocationReadUint("aDelay");
    aInvocation.InvocationReadEnd();
    SetPresetDelay(aVersion, aIndex, aDelay);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDelay1Cpp::DoSetPresetVisible(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aIndex = aInvocation.InvocationReadUint("aIndex");
    bool aVisible = aInvocation.InvocationReadBool("aVisible");
    aInvocation.InvocationReadEnd();
    SetPresetVisible(aVersion, aIndex, aVisible);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDelay1Cpp::DoSetPresetName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aIndex = aInvocation.InvocationReadUint("aIndex");
    Brhz buf_aName;
    aInvocation.InvocationReadString("aName", buf_aName);
    std::string aName((const char*)buf_aName.Ptr(), buf_aName.Bytes());
    aInvocation.InvocationReadEnd();
    SetPresetName(aVersion, aIndex, aName);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDelay1Cpp::DoDelayMinimum(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaDelay;
    DelayMinimum(aVersion, respaDelay);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraDelay(aInvocation, "aDelay");
    respWriteraDelay.Write(respaDelay);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDelay1Cpp::DoDelayMaximum(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaDelay;
    DelayMaximum(aVersion, respaDelay);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraDelay(aInvocation, "aDelay");
    respWriteraDelay.Write(respaDelay);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDelay1Cpp::DoPresetCount(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaCount;
    PresetCount(aVersion, respaCount);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraCount(aInvocation, "aCount");
    respWriteraCount.Write(respaCount);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDelay1Cpp::PresetXml(uint32_t /*aVersion*/, std::string& /*aaPresetXml*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1Cpp::PresetIndex(uint32_t /*aVersion*/, uint32_t& /*aaIndex*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1Cpp::SetPresetIndex(uint32_t /*aVersion*/, uint32_t /*aaIndex*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1Cpp::SetPresetDelay(uint32_t /*aVersion*/, uint32_t /*aaIndex*/, uint32_t /*aaDelay*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1Cpp::SetPresetVisible(uint32_t /*aVersion*/, uint32_t /*aaIndex*/, bool /*aaVisible*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1Cpp::SetPresetName(uint32_t /*aVersion*/, uint32_t /*aaIndex*/, const std::string& /*aaName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1Cpp::DelayMinimum(uint32_t /*aVersion*/, uint32_t& /*aaDelay*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1Cpp::DelayMaximum(uint32_t /*aVersion*/, uint32_t& /*aaDelay*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1Cpp::PresetCount(uint32_t /*aVersion*/, uint32_t& /*aaCount*/)
{
    ASSERTS();
}

