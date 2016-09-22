#include <OpenHome/Net/Private/DviProviderSubscriptionLongPoll.h>
#include <OpenHome/Net/Private/DviServerWebSocket.h> // FIXME eugh! Should factor out DviPropertyUpdateCollection and friends
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Thread.h>

using namespace OpenHome;
using namespace OpenHome::Net;


const Brn DviProviderSubscriptionLongPoll::kErrorDescBadDevice("Device does not exist");
const Brn DviProviderSubscriptionLongPoll::kErrorDescBadService("Service does not exist");
const Brn DviProviderSubscriptionLongPoll::kErrorDescBadSubscription("Subscription does not exist");
const Brn DviProviderSubscriptionLongPoll::kErrorDescTooManyRequests("Too many long poll requests already active");

DviProviderSubscriptionLongPoll::DviProviderSubscriptionLongPoll(DviDevice& aDevice)
    : DvProviderOpenhomeOrgSubscriptionLongPoll1(aDevice)
    , iDvStack(aDevice.GetDvStack())
    , iPropertyUpdateCollection(iDvStack.PropertyUpdateCollection())
    , iLock("LPMX")
    , iShutdown("LPSH", 0)
    , iExit(false)
    , iClientCount(0)
{
    EnableActionSubscribe();
    EnableActionUnsubscribe();
    EnableActionRenew();
    EnableActionGetPropertyUpdates();

    iShutdown.Signal();
    iMaxClientCount = iDvStack.Env().InitParams()->DvNumServerThreads() / 2;
    ASSERT(iMaxClientCount > 0);
    UpdateReadySignal empty;
    for (TUint i=0; i<iMaxClientCount; i++) {
        iUpdateReady.push_back(empty);
    }
}

DviProviderSubscriptionLongPoll::~DviProviderSubscriptionLongPoll()
{
    iExit = true;
    for (TUint i=0; i<iMaxClientCount; i++) {
        iUpdateReady[i].Signal();
    }
    iShutdown.Wait();
}

void DviProviderSubscriptionLongPoll::Subscribe(IDvInvocation& aInvocation, const Brx& aClientId, const Brx& aUdn, const Brx& aService, TUint aRequestedDuration,
                                                IDvInvocationResponseString& aSid, IDvInvocationResponseUint& aDuration)
{
    if (aRequestedDuration > kTimeoutLongPollSecs) {
        aRequestedDuration = kTimeoutLongPollSecs;
    }

    DviDevice* device = iDvStack.DeviceMap().Find(aUdn);
    if (device == NULL) {
        aInvocation.Error(kErrorCodeBadDevice, kErrorDescBadDevice);
    }
    AutoDeviceRef d(device);
    DviService* service = device->ServiceReference(aService);
    if (service == NULL) {
        aInvocation.Error(kErrorCodeBadService, kErrorDescBadService);
    }
    AutoServiceRef s(service);
    Brh sid;
    device->CreateSid(sid);
    TUint timeout = aRequestedDuration;
    DviSubscription* subscription = new DviSubscription(iDvStack, *device, iPropertyUpdateCollection, NULL, sid);
    subscription->SetDuration(timeout);

    aInvocation.StartResponse();
    aSid.Write(subscription->Sid());
    aSid.WriteFlush();
    aDuration.Write(timeout);
    aInvocation.EndResponse();

    // Start subscription, prompting availability of the first update (covering all state variables)
    iPropertyUpdateCollection.AddSubscription(aClientId, subscription);
    iDvStack.SubscriptionManager().AddSubscription(*subscription);
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
    DviSubscription* subscription = iDvStack.SubscriptionManager().Find(aSid);
    if (subscription == NULL) {
        aInvocation.Error(kErrorCodeBadSubscription, kErrorDescBadSubscription);
    }
    TUint timeout = aRequestedDuration;
    if (timeout > kTimeoutLongPollSecs) {
        timeout = kTimeoutLongPollSecs;
    }
    subscription->Renew(timeout);
    aInvocation.StartResponse();
    aDuration.Write(timeout);
    aInvocation.EndResponse();
}

void DviProviderSubscriptionLongPoll::GetPropertyUpdates(IDvInvocation& aInvocation, const Brx& aClientId, IDvInvocationResponseString& aUpdates)
{
    StartGetPropertyUpdates(aInvocation);
    AutoGetPropertyUpdatesComplete a(*this);
    Semaphore sem("PSLP", 0);
    UpdateReadySignal* updateReadySignal = NULL;
    Brh response;
    try {
        iPropertyUpdateCollection.SetClientSignal(aClientId, &sem);
        iLock.Wait();
        for (TUint i=0; i<iMaxClientCount; i++) {
            if (iUpdateReady[i].IsFree()) {
                updateReadySignal = &iUpdateReady[i];
                updateReadySignal->Set(sem);
                break;
            }
        }
        ASSERT(updateReadySignal != NULL);
        iLock.Signal();
        sem.Wait(kGetUpdatesMaxDelay);
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
    iLock.Wait();
    updateReadySignal->Clear();
    iLock.Signal();
    aInvocation.StartResponse();
    if (response.Bytes() > 0) {
        aUpdates.Write(response);
    }
    aUpdates.WriteFlush();
    aInvocation.EndResponse();
}

void DviProviderSubscriptionLongPoll::StartGetPropertyUpdates(IDvInvocation& aInvocation)
{
    AutoMutex a(iLock);
    if (iExit) {
        aInvocation.Error(501, Brx::Empty());
    }
    if (iClientCount == iMaxClientCount) {
        aInvocation.Error(kErrorCodeTooManyRequests, kErrorDescTooManyRequests);
    }
    if (iClientCount == 0) {
        iShutdown.Wait();
    }
    iClientCount++;
}

void DviProviderSubscriptionLongPoll::EndGetPropertyUpdates()
{
    iLock.Wait();
    iClientCount--;
    TBool couldShutdown = (iClientCount==0);
    iLock.Signal();
    if (couldShutdown) {
        iShutdown.Signal();
    }
}


DviProviderSubscriptionLongPoll::AutoGetPropertyUpdatesComplete::AutoGetPropertyUpdatesComplete(DviProviderSubscriptionLongPoll& aLongPoll)
    : iLongPoll(aLongPoll)
{
}

DviProviderSubscriptionLongPoll::AutoGetPropertyUpdatesComplete::~AutoGetPropertyUpdatesComplete()
{
    iLongPoll.EndGetPropertyUpdates();
}
