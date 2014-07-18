#include "DvAvOpenhomeOrgNetworkMonitor1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::SetPropertyName(const std::string& aValue)
{
    ASSERT(iPropertyName != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyName, buf);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::GetPropertyName(std::string& aValue)
{
    ASSERT(iPropertyName != NULL);
    const Brx& val = iPropertyName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::SetPropertySender(uint32_t aValue)
{
    ASSERT(iPropertySender != NULL);
    return SetPropertyUint(*iPropertySender, aValue);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::GetPropertySender(uint32_t& aValue)
{
    ASSERT(iPropertySender != NULL);
    aValue = iPropertySender->Value();
}

bool DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::SetPropertyReceiver(uint32_t aValue)
{
    ASSERT(iPropertyReceiver != NULL);
    return SetPropertyUint(*iPropertyReceiver, aValue);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::GetPropertyReceiver(uint32_t& aValue)
{
    ASSERT(iPropertyReceiver != NULL);
    aValue = iPropertyReceiver->Value();
}

bool DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::SetPropertyResults(uint32_t aValue)
{
    ASSERT(iPropertyResults != NULL);
    return SetPropertyUint(*iPropertyResults, aValue);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::GetPropertyResults(uint32_t& aValue)
{
    ASSERT(iPropertyResults != NULL);
    aValue = iPropertyResults->Value();
}

DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::DvProviderAvOpenhomeOrgNetworkMonitor1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "NetworkMonitor", 1)
{
    iPropertyName = NULL;
    iPropertySender = NULL;
    iPropertyReceiver = NULL;
    iPropertyResults = NULL;
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::EnablePropertyName()
{
    iPropertyName = new PropertyString(iDvStack.Env(), new ParameterString("Name"));
    iService->AddProperty(iPropertyName); // passes ownership
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::EnablePropertySender()
{
    iPropertySender = new PropertyUint(iDvStack.Env(), new ParameterUint("Sender"));
    iService->AddProperty(iPropertySender); // passes ownership
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::EnablePropertyReceiver()
{
    iPropertyReceiver = new PropertyUint(iDvStack.Env(), new ParameterUint("Receiver"));
    iService->AddProperty(iPropertyReceiver); // passes ownership
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::EnablePropertyResults()
{
    iPropertyResults = new PropertyUint(iDvStack.Env(), new ParameterUint("Results"));
    iService->AddProperty(iPropertyResults); // passes ownership
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::EnableActionName()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Name");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::DoName);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::EnableActionPorts()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Ports");
    action->AddOutputParameter(new ParameterRelated("Sender", *iPropertySender));
    action->AddOutputParameter(new ParameterRelated("Receiver", *iPropertyReceiver));
    action->AddOutputParameter(new ParameterRelated("Results", *iPropertyResults));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::DoPorts);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::DoName(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respName;
    DvInvocationStd invocation(aInvocation);
    Name(invocation, respName);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterName(aInvocation, "Name");
    Brn buf_Name((const TByte*)respName.c_str(), (TUint)respName.length());
    respWriterName.Write(buf_Name);
    aInvocation.InvocationWriteStringEnd("Name");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::DoPorts(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respSender;
    uint32_t respReceiver;
    uint32_t respResults;
    DvInvocationStd invocation(aInvocation);
    Ports(invocation, respSender, respReceiver, respResults);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterSender(aInvocation, "Sender");
    respWriterSender.Write(respSender);
    DviInvocationResponseUint respWriterReceiver(aInvocation, "Receiver");
    respWriterReceiver.Write(respReceiver);
    DviInvocationResponseUint respWriterResults(aInvocation, "Results");
    respWriterResults.Write(respResults);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::Name(IDvInvocationStd& /*aInvocation*/, std::string& /*aName*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgNetworkMonitor1Cpp::Ports(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aSender*/, uint32_t& /*aReceiver*/, uint32_t& /*aResults*/)
{
    ASSERTS();
}

