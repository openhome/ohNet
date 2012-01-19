#include <OpenHome/Net/Private/DviProviderSubscriptionLongPoll.h>
#include <OpenHome/Net/Private/DviServerWebSocket.h> // FIXME eugh! Should factor out DviPropertyUpdateCollection and friends
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/DviSubscription.h>

using namespace OpenHome;
using namespace OpenHome::Net;

DviProviderSubscriptionLongPoll::DviProviderSubscriptionLongPoll(DvDevice& aDevice)
    : DvProviderOpenhomeOrgSubscriptionLongPoll1(aDevice)
    , iPropertyUpdateCollection(DviStack::PropertyUpdateCollection())
    , iUpdatesReady("LPUR", 0)
    , iShutdown("LPSH", 0)
{
    EnableActionSubscribe();
    EnableActionUnsubscribe();
    EnableActionRenew();
    EnableActionGetPropertyUpdates();
    iShutdown.Signal();
}

DviProviderSubscriptionLongPoll::~DviProviderSubscriptionLongPoll()
{
    iExit = true;
    iUpdatesReady.Signal();
    iShutdown.Wait();
}

void DviProviderSubscriptionLongPoll::Subscribe(IDvInvocation& aInvocation, const Brx& aClientId, const Brx& aUdn, const Brx& aService, TUint aRequestedDuration,
                                                IDvInvocationResponseString& aSid, IDvInvocationResponseUint& aDuration)
{
    if (aRequestedDuration > kTimeoutLongPollSecs) {
        aRequestedDuration = kTimeoutLongPollSecs;
    }

    DviDevice* device = DviStack::DeviceMap().Find(aUdn);
    if (device == NULL) {
        aInvocation.Error(501, Brn("Subscribe: no such device"));
    }
    DviService* service = NULL;
    const TUint serviceCount = device->ServiceCount();
    for (TUint i=0; i<serviceCount; i++) {
        DviService* s = &device->Service(i);
        if (s->ServiceType().PathUpnp() == aService) {
            service = s;
            break;
        }
    }
    if (service == NULL) {
        aInvocation.Error(501, Brn("Subscribe: no such service"));
    }
    Brh sid;
    device->CreateSid(sid);
    TUint timeout = aRequestedDuration;
    DviSubscription* subscription = new DviSubscription(*device, iPropertyUpdateCollection, NULL, sid, timeout);

    aInvocation.StartResponse();
    aSid.Write(subscription->Sid());
    aSid.WriteFlush();
    aDuration.Write(timeout);
    aInvocation.EndResponse();

    // Start subscription, prompting delivery of the first update (covering all state variables)
    iPropertyUpdateCollection.AddSubscription(aClientId, subscription);
    DviSubscriptionManager::AddSubscription(*subscription);
    service->AddSubscription(subscription);
}

void DviProviderSubscriptionLongPoll::Unsubscribe(IDvInvocation& aInvocation, const Brx& aSid)
{
    iPropertyUpdateCollection.RemoveSubscription(aSid);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void DviProviderSubscriptionLongPoll::Renew(IDvInvocation& aInvocation, const Brx& aSid, TUint aRequestedDuration, IDvInvocationResponseUint& aDuration)
{
    DviSubscription* subscription = DviSubscriptionManager::Find(aSid);
    if (subscription == NULL) {
        aInvocation.Error(501, Brn("Renew: no such subscription"));
    }
    TUint timeout = aRequestedDuration;
    subscription->Renew(timeout);
    aInvocation.StartResponse();
    aDuration.Write(timeout);
    aInvocation.EndResponse();
}

void DviProviderSubscriptionLongPoll::GetPropertyUpdates(IDvInvocation& aInvocation, const Brx& aClientId, IDvInvocationResponseString& aUpdates)
{
    // FIXME - limit number of concurrent requests, leaving some provider threads for regular (much shorter running) actions
    iShutdown.Wait();
    Brh response;
    try {
        iPropertyUpdateCollection.SetClientSignal(aClientId, &iUpdatesReady);
        iUpdatesReady.Wait(kGetUpdatesMaxDelay);
        iPropertyUpdateCollection.SetClientSignal(aClientId, NULL);
        if (!iExit) {
            WriterBwh writer(1024);
            iPropertyUpdateCollection.WriteUpdates(aClientId, writer);
            writer.TransferTo(response);
        }
    }
    catch (Timeout&) {
        iPropertyUpdateCollection.SetClientSignal(aClientId, NULL);
    }
    aInvocation.StartResponse();
    if (response.Bytes() > 0) {
        aUpdates.Write(response);
    }
    aUpdates.WriteFlush();
    aInvocation.EndResponse();
    iShutdown.Signal(); // FIXME - needs to be called in event of any exception too
}
