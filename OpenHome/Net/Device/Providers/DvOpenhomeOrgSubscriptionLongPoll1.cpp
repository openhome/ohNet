#include "DvOpenhomeOrgSubscriptionLongPoll1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

DvProviderOpenhomeOrgSubscriptionLongPoll1::DvProviderOpenhomeOrgSubscriptionLongPoll1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "openhome.org", "SubscriptionLongPoll", 1)
{
    Construct();
}

DvProviderOpenhomeOrgSubscriptionLongPoll1::DvProviderOpenhomeOrgSubscriptionLongPoll1(DviDevice& aDevice)
    : DvProvider(aDevice, "openhome.org", "SubscriptionLongPoll", 1)
{
    Construct();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1::Construct()
{
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1::EnableActionSubscribe()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Subscribe");
    action->AddInputParameter(new ParameterString("ClientId"));
    action->AddInputParameter(new ParameterString("Udn"));
    action->AddInputParameter(new ParameterString("Service"));
    action->AddInputParameter(new ParameterUint("RequestedDuration"));
    action->AddOutputParameter(new ParameterString("Sid"));
    action->AddOutputParameter(new ParameterUint("Duration"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgSubscriptionLongPoll1::DoSubscribe);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1::EnableActionUnsubscribe()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Unsubscribe");
    action->AddInputParameter(new ParameterString("Sid"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgSubscriptionLongPoll1::DoUnsubscribe);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1::EnableActionRenew()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Renew");
    action->AddInputParameter(new ParameterString("Sid"));
    action->AddInputParameter(new ParameterUint("RequestedDuration"));
    action->AddOutputParameter(new ParameterUint("Duration"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgSubscriptionLongPoll1::DoRenew);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1::EnableActionGetPropertyUpdates()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetPropertyUpdates");
    action->AddInputParameter(new ParameterString("ClientId"));
    action->AddOutputParameter(new ParameterString("Updates"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgSubscriptionLongPoll1::DoGetPropertyUpdates);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1::DoSubscribe(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz ClientId;
    aInvocation.InvocationReadString("ClientId", ClientId);
    Brhz Udn;
    aInvocation.InvocationReadString("Udn", Udn);
    Brhz Service;
    aInvocation.InvocationReadString("Service", Service);
    TUint RequestedDuration = aInvocation.InvocationReadUint("RequestedDuration");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respSid(aInvocation, "Sid");
    DviInvocationResponseUint respDuration(aInvocation, "Duration");
    Subscribe(invocation, ClientId, Udn, Service, RequestedDuration, respSid, respDuration);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1::DoUnsubscribe(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz Sid;
    aInvocation.InvocationReadString("Sid", Sid);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Unsubscribe(invocation, Sid);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1::DoRenew(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz Sid;
    aInvocation.InvocationReadString("Sid", Sid);
    TUint RequestedDuration = aInvocation.InvocationReadUint("RequestedDuration");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respDuration(aInvocation, "Duration");
    Renew(invocation, Sid, RequestedDuration, respDuration);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1::DoGetPropertyUpdates(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz ClientId;
    aInvocation.InvocationReadString("ClientId", ClientId);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respUpdates(aInvocation, "Updates");
    GetPropertyUpdates(invocation, ClientId, respUpdates);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1::Subscribe(IDvInvocation& /*aResponse*/, const Brx& /*aClientId*/, const Brx& /*aUdn*/, const Brx& /*aService*/, TUint /*aRequestedDuration*/, IDvInvocationResponseString& /*aSid*/, IDvInvocationResponseUint& /*aDuration*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1::Unsubscribe(IDvInvocation& /*aResponse*/, const Brx& /*aSid*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1::Renew(IDvInvocation& /*aResponse*/, const Brx& /*aSid*/, TUint /*aRequestedDuration*/, IDvInvocationResponseUint& /*aDuration*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1::GetPropertyUpdates(IDvInvocation& /*aResponse*/, const Brx& /*aClientId*/, IDvInvocationResponseString& /*aUpdates*/)
{
    ASSERTS();
}

