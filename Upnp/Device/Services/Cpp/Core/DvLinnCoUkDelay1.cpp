#include "DvLinnCoUkDelay1.h"
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkDelay1::SetPropertyPresetXml(const Brx& aValue)
{
    return SetPropertyString(*iPropertyPresetXml, aValue);
}

void DvProviderLinnCoUkDelay1::GetPropertyPresetXml(Brhz& aValue)
{
    aValue.Set(iPropertyPresetXml->Value());
}

TBool DvProviderLinnCoUkDelay1::SetPropertyPresetIndex(TUint aValue)
{
    return SetPropertyUint(*iPropertyPresetIndex, aValue);
}

void DvProviderLinnCoUkDelay1::GetPropertyPresetIndex(TUint& aValue)
{
    aValue = iPropertyPresetIndex->Value();
}

DvProviderLinnCoUkDelay1::DvProviderLinnCoUkDelay1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Delay", 1)
{
    
    iPropertyPresetXml = new PropertyString(new ParameterString("PresetXml"));
    iService->AddProperty(iPropertyPresetXml); // passes ownership
    iPropertyPresetIndex = new PropertyUint(new ParameterUint("PresetIndex"));
    iService->AddProperty(iPropertyPresetIndex); // passes ownership
}

void DvProviderLinnCoUkDelay1::EnableActionPresetXml()
{
    Zapp::Action* action = new Zapp::Action("PresetXml");
    action->AddOutputParameter(new ParameterRelated("aPresetXml", *iPropertyPresetXml));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1::DoPresetXml);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1::EnableActionPresetIndex()
{
    Zapp::Action* action = new Zapp::Action("PresetIndex");
    action->AddOutputParameter(new ParameterRelated("aIndex", *iPropertyPresetIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1::DoPresetIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1::EnableActionSetPresetIndex()
{
    Zapp::Action* action = new Zapp::Action("SetPresetIndex");
    action->AddInputParameter(new ParameterRelated("aIndex", *iPropertyPresetIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1::DoSetPresetIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1::EnableActionSetPresetDelay()
{
    Zapp::Action* action = new Zapp::Action("SetPresetDelay");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterUint("aDelay"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1::DoSetPresetDelay);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1::EnableActionSetPresetVisible()
{
    Zapp::Action* action = new Zapp::Action("SetPresetVisible");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterBool("aVisible"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1::DoSetPresetVisible);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1::EnableActionSetPresetName()
{
    Zapp::Action* action = new Zapp::Action("SetPresetName");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterString("aName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1::DoSetPresetName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1::EnableActionDelayMinimum()
{
    Zapp::Action* action = new Zapp::Action("DelayMinimum");
    action->AddOutputParameter(new ParameterUint("aDelay"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1::DoDelayMinimum);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1::EnableActionDelayMaximum()
{
    Zapp::Action* action = new Zapp::Action("DelayMaximum");
    action->AddOutputParameter(new ParameterUint("aDelay"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1::DoDelayMaximum);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1::EnableActionPresetCount()
{
    Zapp::Action* action = new Zapp::Action("PresetCount");
    action->AddOutputParameter(new ParameterUint("aCount"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1::DoPresetCount);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1::DoPresetXml(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaPresetXml(aInvocation, "aPresetXml");
    PresetXml(resp, aVersion, respaPresetXml);
}

void DvProviderLinnCoUkDelay1::DoPresetIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaIndex(aInvocation, "aIndex");
    PresetIndex(resp, aVersion, respaIndex);
}

void DvProviderLinnCoUkDelay1::DoSetPresetIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetPresetIndex(resp, aVersion, aIndex);
}

void DvProviderLinnCoUkDelay1::DoSetPresetDelay(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    TUint aDelay = aInvocation.InvocationReadUint("aDelay");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetPresetDelay(resp, aVersion, aIndex, aDelay);
}

void DvProviderLinnCoUkDelay1::DoSetPresetVisible(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    TBool aVisible = aInvocation.InvocationReadBool("aVisible");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetPresetVisible(resp, aVersion, aIndex, aVisible);
}

void DvProviderLinnCoUkDelay1::DoSetPresetName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    Brhz aName;
    aInvocation.InvocationReadString("aName", aName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetPresetName(resp, aVersion, aIndex, aName);
}

void DvProviderLinnCoUkDelay1::DoDelayMinimum(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaDelay(aInvocation, "aDelay");
    DelayMinimum(resp, aVersion, respaDelay);
}

void DvProviderLinnCoUkDelay1::DoDelayMaximum(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaDelay(aInvocation, "aDelay");
    DelayMaximum(resp, aVersion, respaDelay);
}

void DvProviderLinnCoUkDelay1::DoPresetCount(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaCount(aInvocation, "aCount");
    PresetCount(resp, aVersion, respaCount);
}

void DvProviderLinnCoUkDelay1::PresetXml(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaPresetXml*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1::PresetIndex(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaIndex*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1::SetPresetIndex(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIndex*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1::SetPresetDelay(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIndex*/, TUint /*aaDelay*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1::SetPresetVisible(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIndex*/, TBool /*aaVisible*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1::SetPresetName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIndex*/, const Brx& /*aaName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1::DelayMinimum(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaDelay*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1::DelayMaximum(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaDelay*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDelay1::PresetCount(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaCount*/)
{
    ASSERTS();
}

