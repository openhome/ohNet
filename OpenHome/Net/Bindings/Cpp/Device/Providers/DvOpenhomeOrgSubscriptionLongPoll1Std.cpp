#include "DvOpenhomeOrgSubscriptionLongPoll1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "openhome.org", "SubscriptionLongPoll", 1)
{
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::EnableActionSubscribe()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Subscribe");
    action->AddInputParameter(new ParameterString("ClientId"));
    action->AddInputParameter(new ParameterString("Udn"));
    action->AddInputParameter(new ParameterString("Service"));
    action->AddInputParameter(new ParameterUint("RequestedDuration"));
    action->AddOutputParameter(new ParameterString("Sid"));
    action->AddOutputParameter(new ParameterUint("Duration"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::DoSubscribe);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::EnableActionUnsubscribe()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Unsubscribe");
    action->AddInputParameter(new ParameterString("Sid"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::DoUnsubscribe);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::EnableActionRenew()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Renew");
    action->AddInputParameter(new ParameterString("Sid"));
    action->AddInputParameter(new ParameterUint("RequestedDuration"));
    action->AddOutputParameter(new ParameterUint("Duration"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::DoRenew);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::EnableActionGetPropertyUpdates()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetPropertyUpdates");
    action->AddInputParameter(new ParameterString("ClientId"));
    action->AddOutputParameter(new ParameterString("Updates"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::DoGetPropertyUpdates);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::DoSubscribe(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ClientId;
    aInvocation.InvocationReadString("ClientId", buf_ClientId);
    std::string ClientId((const char*)buf_ClientId.Ptr(), buf_ClientId.Bytes());
    Brhz buf_Udn;
    aInvocation.InvocationReadString("Udn", buf_Udn);
    std::string Udn((const char*)buf_Udn.Ptr(), buf_Udn.Bytes());
    Brhz buf_Service;
    aInvocation.InvocationReadString("Service", buf_Service);
    std::string Service((const char*)buf_Service.Ptr(), buf_Service.Bytes());
    uint32_t RequestedDuration = aInvocation.InvocationReadUint("RequestedDuration");
    aInvocation.InvocationReadEnd();
    std::string respSid;
    uint32_t respDuration;
    DvInvocationStd invocation(aInvocation);
    Subscribe(invocation, ClientId, Udn, Service, RequestedDuration, respSid, respDuration);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterSid(aInvocation, "Sid");
    Brn buf_Sid((const TByte*)respSid.c_str(), (TUint)respSid.length());
    respWriterSid.Write(buf_Sid);
    aInvocation.InvocationWriteStringEnd("Sid");
    DviInvocationResponseUint respWriterDuration(aInvocation, "Duration");
    respWriterDuration.Write(respDuration);
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::DoUnsubscribe(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Sid;
    aInvocation.InvocationReadString("Sid", buf_Sid);
    std::string Sid((const char*)buf_Sid.Ptr(), buf_Sid.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Unsubscribe(invocation, Sid);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::DoRenew(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Sid;
    aInvocation.InvocationReadString("Sid", buf_Sid);
    std::string Sid((const char*)buf_Sid.Ptr(), buf_Sid.Bytes());
    uint32_t RequestedDuration = aInvocation.InvocationReadUint("RequestedDuration");
    aInvocation.InvocationReadEnd();
    uint32_t respDuration;
    DvInvocationStd invocation(aInvocation);
    Renew(invocation, Sid, RequestedDuration, respDuration);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterDuration(aInvocation, "Duration");
    respWriterDuration.Write(respDuration);
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::DoGetPropertyUpdates(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ClientId;
    aInvocation.InvocationReadString("ClientId", buf_ClientId);
    std::string ClientId((const char*)buf_ClientId.Ptr(), buf_ClientId.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respUpdates;
    DvInvocationStd invocation(aInvocation);
    GetPropertyUpdates(invocation, ClientId, respUpdates);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterUpdates(aInvocation, "Updates");
    Brn buf_Updates((const TByte*)respUpdates.c_str(), (TUint)respUpdates.length());
    respWriterUpdates.Write(buf_Updates);
    aInvocation.InvocationWriteStringEnd("Updates");
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::Subscribe(IDvInvocationStd& /*aInvocation*/, const std::string& /*aClientId*/, const std::string& /*aUdn*/, const std::string& /*aService*/, uint32_t /*aRequestedDuration*/, std::string& /*aSid*/, uint32_t& /*aDuration*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::Unsubscribe(IDvInvocationStd& /*aInvocation*/, const std::string& /*aSid*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::Renew(IDvInvocationStd& /*aInvocation*/, const std::string& /*aSid*/, uint32_t /*aRequestedDuration*/, uint32_t& /*aDuration*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1Cpp::GetPropertyUpdates(IDvInvocationStd& /*aInvocation*/, const std::string& /*aClientId*/, std::string& /*aUpdates*/)
{
    ASSERTS();
}

