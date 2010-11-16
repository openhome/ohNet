#include <Std/DvLinnCoUkDelay1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

bool DvProviderLinnCoUkDelay1Cpp::SetPropertyPresetXml(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyPresetXml, buf);
}

void DvProviderLinnCoUkDelay1Cpp::GetPropertyPresetXml(std::string& aValue)
{
    const Brx& val = iPropertyPresetXml->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkDelay1Cpp::SetPropertyPresetIndex(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyPresetIndex, aValue);
}

void DvProviderLinnCoUkDelay1Cpp::GetPropertyPresetIndex(uint32_t& aValue)
{
    aValue = iPropertyPresetIndex->Value();
}

DvProviderLinnCoUkDelay1Cpp::DvProviderLinnCoUkDelay1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Delay", 1)
{
    Functor empty;
    iPropertyPresetXml = new PropertyString(new ParameterString("PresetXml"), empty);
    iService->AddProperty(iPropertyPresetXml); // passes ownership
    iPropertyPresetIndex = new PropertyUint(new ParameterUint("PresetIndex"), empty);
    iService->AddProperty(iPropertyPresetIndex); // passes ownership
}

void DvProviderLinnCoUkDelay1Cpp::EnableActionPresetXml()
{
    Zapp::Action* action = new Zapp::Action("PresetXml");
    action->AddOutputParameter(new ParameterRelated("aPresetXml", *iPropertyPresetXml));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1Cpp::DoPresetXml);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1Cpp::EnableActionPresetIndex()
{
    Zapp::Action* action = new Zapp::Action("PresetIndex");
    action->AddOutputParameter(new ParameterRelated("aIndex", *iPropertyPresetIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1Cpp::DoPresetIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1Cpp::EnableActionSetPresetIndex()
{
    Zapp::Action* action = new Zapp::Action("SetPresetIndex");
    action->AddInputParameter(new ParameterRelated("aIndex", *iPropertyPresetIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1Cpp::DoSetPresetIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1Cpp::EnableActionSetPresetDelay()
{
    Zapp::Action* action = new Zapp::Action("SetPresetDelay");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterUint("aDelay"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1Cpp::DoSetPresetDelay);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1Cpp::EnableActionSetPresetVisible()
{
    Zapp::Action* action = new Zapp::Action("SetPresetVisible");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterBool("aVisible"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1Cpp::DoSetPresetVisible);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1Cpp::EnableActionSetPresetName()
{
    Zapp::Action* action = new Zapp::Action("SetPresetName");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterString("aName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1Cpp::DoSetPresetName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1Cpp::EnableActionDelayMinimum()
{
    Zapp::Action* action = new Zapp::Action("DelayMinimum");
    action->AddOutputParameter(new ParameterUint("aDelay"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1Cpp::DoDelayMinimum);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1Cpp::EnableActionDelayMaximum()
{
    Zapp::Action* action = new Zapp::Action("DelayMaximum");
    action->AddOutputParameter(new ParameterUint("aDelay"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1Cpp::DoDelayMaximum);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1Cpp::EnableActionPresetCount()
{
    Zapp::Action* action = new Zapp::Action("PresetCount");
    action->AddOutputParameter(new ParameterUint("aCount"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1Cpp::DoPresetCount);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1Cpp::DoPresetXml(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaPresetXml;
    PresetXml(aVersion, respaPresetXml);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraPresetXml(aInvocation, "aPresetXml");
    Brn buf_aPresetXml((const TByte*)respaPresetXml.c_str(), (TUint)respaPresetXml.length());
    respWriteraPresetXml.Write(buf_aPresetXml);
    aInvocation.InvocationWriteStringEnd("aPresetXml");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDelay1Cpp::DoPresetIndex(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkDelay1Cpp::DoSetPresetIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    SetPresetIndex(aVersion, aIndex);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDelay1Cpp::DoSetPresetDelay(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aIndex = aInvocation.InvocationReadUint("aIndex");
    uint32_t aDelay = aInvocation.InvocationReadUint("aDelay");
    aInvocation.InvocationReadEnd();
    SetPresetDelay(aVersion, aIndex, aDelay);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDelay1Cpp::DoSetPresetVisible(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aIndex = aInvocation.InvocationReadUint("aIndex");
    bool aVisible = aInvocation.InvocationReadBool("aVisible");
    aInvocation.InvocationReadEnd();
    SetPresetVisible(aVersion, aIndex, aVisible);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDelay1Cpp::DoSetPresetName(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkDelay1Cpp::DoDelayMinimum(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkDelay1Cpp::DoDelayMaximum(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkDelay1Cpp::DoPresetCount(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkDelay1Cpp::PresetXml(uint32_t /*aVersion*/, std::string& /*aaPresetXml*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1Cpp::PresetIndex(uint32_t /*aVersion*/, uint32_t& /*aaIndex*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1Cpp::SetPresetIndex(uint32_t /*aVersion*/, uint32_t /*aaIndex*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1Cpp::SetPresetDelay(uint32_t /*aVersion*/, uint32_t /*aaIndex*/, uint32_t /*aaDelay*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1Cpp::SetPresetVisible(uint32_t /*aVersion*/, uint32_t /*aaIndex*/, bool /*aaVisible*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1Cpp::SetPresetName(uint32_t /*aVersion*/, uint32_t /*aaIndex*/, const std::string& /*aaName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1Cpp::DelayMinimum(uint32_t /*aVersion*/, uint32_t& /*aaDelay*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1Cpp::DelayMaximum(uint32_t /*aVersion*/, uint32_t& /*aaDelay*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1Cpp::PresetCount(uint32_t /*aVersion*/, uint32_t& /*aaCount*/)
{
    ASSERTS();
}

