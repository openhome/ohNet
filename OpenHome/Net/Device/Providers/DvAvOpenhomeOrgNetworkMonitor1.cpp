#include "DvAvOpenhomeOrgNetworkMonitor1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgNetworkMonitor1::SetPropertyName(const Brx& aValue)
{
    ASSERT(iPropertyName != NULL);
    return SetPropertyString(*iPropertyName, aValue);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::GetPropertyName(Brhz& aValue)
{
    ASSERT(iPropertyName != NULL);
    aValue.Set(iPropertyName->Value());
}

TBool DvProviderAvOpenhomeOrgNetworkMonitor1::SetPropertySender(TUint aValue)
{
    ASSERT(iPropertySender != NULL);
    return SetPropertyUint(*iPropertySender, aValue);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::GetPropertySender(TUint& aValue)
{
    ASSERT(iPropertySender != NULL);
    aValue = iPropertySender->Value();
}

TBool DvProviderAvOpenhomeOrgNetworkMonitor1::SetPropertyReceiver(TUint aValue)
{
    ASSERT(iPropertyReceiver != NULL);
    return SetPropertyUint(*iPropertyReceiver, aValue);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::GetPropertyReceiver(TUint& aValue)
{
    ASSERT(iPropertyReceiver != NULL);
    aValue = iPropertyReceiver->Value();
}

TBool DvProviderAvOpenhomeOrgNetworkMonitor1::SetPropertyResults(TUint aValue)
{
    ASSERT(iPropertyResults != NULL);
    return SetPropertyUint(*iPropertyResults, aValue);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::GetPropertyResults(TUint& aValue)
{
    ASSERT(iPropertyResults != NULL);
    aValue = iPropertyResults->Value();
}

DvProviderAvOpenhomeOrgNetworkMonitor1::DvProviderAvOpenhomeOrgNetworkMonitor1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "NetworkMonitor", 1)
{
    Construct();
}

DvProviderAvOpenhomeOrgNetworkMonitor1::DvProviderAvOpenhomeOrgNetworkMonitor1(DviDevice& aDevice)
    : DvProvider(aDevice, "av.openhome.org", "NetworkMonitor", 1)
{
    Construct();
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::Construct()
{
    iPropertyName = NULL;
    iPropertySender = NULL;
    iPropertyReceiver = NULL;
    iPropertyResults = NULL;
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::EnablePropertyName()
{
    iPropertyName = new PropertyString(iDvStack.Env(), new ParameterString("Name"));
    iService->AddProperty(iPropertyName); // passes ownership
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::EnablePropertySender()
{
    iPropertySender = new PropertyUint(iDvStack.Env(), new ParameterUint("Sender"));
    iService->AddProperty(iPropertySender); // passes ownership
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::EnablePropertyReceiver()
{
    iPropertyReceiver = new PropertyUint(iDvStack.Env(), new ParameterUint("Receiver"));
    iService->AddProperty(iPropertyReceiver); // passes ownership
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::EnablePropertyResults()
{
    iPropertyResults = new PropertyUint(iDvStack.Env(), new ParameterUint("Results"));
    iService->AddProperty(iPropertyResults); // passes ownership
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::EnableActionName()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Name");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgNetworkMonitor1::DoName);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::EnableActionPorts()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Ports");
    action->AddOutputParameter(new ParameterRelated("Sender", *iPropertySender));
    action->AddOutputParameter(new ParameterRelated("Receiver", *iPropertyReceiver));
    action->AddOutputParameter(new ParameterRelated("Results", *iPropertyResults));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgNetworkMonitor1::DoPorts);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::DoName(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respName(aInvocation, "Name");
    Name(invocation, respName);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::DoPorts(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respSender(aInvocation, "Sender");
    DviInvocationResponseUint respReceiver(aInvocation, "Receiver");
    DviInvocationResponseUint respResults(aInvocation, "Results");
    Ports(invocation, respSender, respReceiver, respResults);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::Name(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aName*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgNetworkMonitor1::Ports(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aSender*/, IDvInvocationResponseUint& /*aReceiver*/, IDvInvocationResponseUint& /*aResults*/)
{
    ASSERTS();
}

