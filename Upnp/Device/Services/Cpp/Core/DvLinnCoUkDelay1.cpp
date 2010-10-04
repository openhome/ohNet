#include <Core/DvLinnCoUkDelay1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkDelay1::SetPropertyPresetXml(const Brx& aValue)
{
    SetPropertyString(*iPropertyPresetXml, aValue);
}

void DvServiceLinnCoUkDelay1::GetPropertyPresetXml(Brhz& aValue)
{
    aValue.Set(iPropertyPresetXml->Value());
}

void DvServiceLinnCoUkDelay1::SetPropertyPresetIndex(TUint aValue)
{
    SetPropertyUint(*iPropertyPresetIndex, aValue);
}

void DvServiceLinnCoUkDelay1::GetPropertyPresetIndex(TUint& aValue)
{
    aValue = iPropertyPresetIndex->Value();
}

DvServiceLinnCoUkDelay1::DvServiceLinnCoUkDelay1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Delay", 1)
{
    Functor empty;
    iPropertyPresetXml = new PropertyString(new ParameterString("PresetXml"), empty);
    iService->AddProperty(iPropertyPresetXml); // passes ownership
    iPropertyPresetIndex = new PropertyUint(new ParameterUint("PresetIndex"), empty);
    iService->AddProperty(iPropertyPresetIndex); // passes ownership
}

void DvServiceLinnCoUkDelay1::EnableActionPresetXml()
{
    Zapp::Action* action = new Zapp::Action("PresetXml");
    action->AddOutputParameter(new ParameterRelated("aPresetXml", *iPropertyPresetXml));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1::DoPresetXml);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1::EnableActionPresetIndex()
{
    Zapp::Action* action = new Zapp::Action("PresetIndex");
    action->AddOutputParameter(new ParameterRelated("aIndex", *iPropertyPresetIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1::DoPresetIndex);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1::EnableActionSetPresetIndex()
{
    Zapp::Action* action = new Zapp::Action("SetPresetIndex");
    action->AddInputParameter(new ParameterRelated("aIndex", *iPropertyPresetIndex));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1::DoSetPresetIndex);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1::EnableActionSetPresetDelay()
{
    Zapp::Action* action = new Zapp::Action("SetPresetDelay");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterUint("aDelay"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1::DoSetPresetDelay);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1::EnableActionSetPresetVisible()
{
    Zapp::Action* action = new Zapp::Action("SetPresetVisible");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterBool("aVisible"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1::DoSetPresetVisible);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1::EnableActionSetPresetName()
{
    Zapp::Action* action = new Zapp::Action("SetPresetName");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterString("aName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1::DoSetPresetName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1::EnableActionDelayMinimum()
{
    Zapp::Action* action = new Zapp::Action("DelayMinimum");
    action->AddOutputParameter(new ParameterUint("aDelay"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1::DoDelayMinimum);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1::EnableActionDelayMaximum()
{
    Zapp::Action* action = new Zapp::Action("DelayMaximum");
    action->AddOutputParameter(new ParameterUint("aDelay"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1::DoDelayMaximum);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1::EnableActionPresetCount()
{
    Zapp::Action* action = new Zapp::Action("PresetCount");
    action->AddOutputParameter(new ParameterUint("aCount"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDelay1::DoPresetCount);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDelay1::DoPresetXml(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaPresetXml(aInvocation, "aPresetXml");
    PresetXml(resp, aVersion, respaPresetXml);
}

void DvServiceLinnCoUkDelay1::DoPresetIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaIndex(aInvocation, "aIndex");
    PresetIndex(resp, aVersion, respaIndex);
}

void DvServiceLinnCoUkDelay1::DoSetPresetIndex(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetPresetIndex(resp, aVersion, aIndex);
}

void DvServiceLinnCoUkDelay1::DoSetPresetDelay(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    TUint aDelay = aInvocation.InvocationReadUint("aDelay");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetPresetDelay(resp, aVersion, aIndex, aDelay);
}

void DvServiceLinnCoUkDelay1::DoSetPresetVisible(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    TBool aVisible = aInvocation.InvocationReadBool("aVisible");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetPresetVisible(resp, aVersion, aIndex, aVisible);
}

void DvServiceLinnCoUkDelay1::DoSetPresetName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    Brhz aName;
    aInvocation.InvocationReadString("aName", aName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetPresetName(resp, aVersion, aIndex, aName);
}

void DvServiceLinnCoUkDelay1::DoDelayMinimum(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaDelay(aInvocation, "aDelay");
    DelayMinimum(resp, aVersion, respaDelay);
}

void DvServiceLinnCoUkDelay1::DoDelayMaximum(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaDelay(aInvocation, "aDelay");
    DelayMaximum(resp, aVersion, respaDelay);
}

void DvServiceLinnCoUkDelay1::DoPresetCount(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaCount(aInvocation, "aCount");
    PresetCount(resp, aVersion, respaCount);
}

void DvServiceLinnCoUkDelay1::PresetXml(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaPresetXml*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1::PresetIndex(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaIndex*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1::SetPresetIndex(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIndex*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1::SetPresetDelay(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIndex*/, TUint /*aaDelay*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1::SetPresetVisible(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIndex*/, TBool /*aaVisible*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1::SetPresetName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIndex*/, const Brx& /*aaName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1::DelayMinimum(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaDelay*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1::DelayMaximum(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaDelay*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDelay1::PresetCount(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaCount*/)
{
    ASSERTS();
}

