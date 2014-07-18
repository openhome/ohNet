#ifndef HEADER_DVI_PROVIDER_SUBSCRIPTION_LONGPOLL
#define HEADER_DVI_PROVIDER_SUBSCRIPTION_LONGPOLL

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvOpenhomeOrgSubscriptionLongPoll1.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Private/Thread.h>

#include <vector>
#include <map>
#include <list>

namespace OpenHome {
namespace Net {

class DvStack;
class DviPropertyUpdateCollection;
    
class DviProviderSubscriptionLongPoll : public DvProviderOpenhomeOrgSubscriptionLongPoll1
{
public:
    DviProviderSubscriptionLongPoll(DviDevice& aDevice);
    ~DviProviderSubscriptionLongPoll();
private: // DvProviderOpenhomeOrgSubscriptionLongPoll1
    void Subscribe(IDvInvocation& aInvocation, const Brx& aClientId, const Brx& aUdn, const Brx& aService, TUint aRequestedDuration, IDvInvocationResponseString& aSid, IDvInvocationResponseUint& aDuration);
    void Unsubscribe(IDvInvocation& aInvocation, const Brx& aSid);
    void Renew(IDvInvocation& aInvocation, const Brx& aSid, TUint aRequestedDuration, IDvInvocationResponseUint& aDuration);
    void GetPropertyUpdates(IDvInvocation& aInvocation, const Brx& aClientId, IDvInvocationResponseString& aUpdates);
private:
    void StartGetPropertyUpdates(IDvInvocation& aInvocation);
    void EndGetPropertyUpdates();
private:
    // cleans up when GetPropertyUpdates exits
    class AutoGetPropertyUpdatesComplete : private INonCopyable
    {
    public:
        AutoGetPropertyUpdatesComplete(DviProviderSubscriptionLongPoll& aLongPoll);
        ~AutoGetPropertyUpdatesComplete();
    private:
        DviProviderSubscriptionLongPoll& iLongPoll;
    };

    class UpdateReadySignal
    {
    public:
        UpdateReadySignal() : iSem(NULL) {}
        TBool IsFree() const { return (iSem == NULL); }
        void Signal() { if (iSem != NULL) iSem->Signal(); }
        void Set(Semaphore& aSem) { iSem = &aSem; }
        void Clear() { iSem = NULL; }
    private:
        Semaphore* iSem;
    };
private:
    static const TUint kTimeoutLongPollSecs = 5 * 60; // 5 mins
    static const TUint kGetUpdatesMaxDelay = 30 * 1000; // 30 secs
    static const TUint kErrorCodeBadDevice = 810;
    static const TUint kErrorCodeBadService = 811;
    static const TUint kErrorCodeBadSubscription = 812;
    static const TUint kErrorCodeTooManyRequests = 813;
    static const Brn kErrorDescBadDevice;
    static const Brn kErrorDescBadService;
    static const Brn kErrorDescBadSubscription;
    static const Brn kErrorDescTooManyRequests;
    friend class AutoGetPropertyUpdatesComplete;
private:
    DvStack& iDvStack;
    DviPropertyUpdateCollection& iPropertyUpdateCollection;
    Mutex iLock;
    std::vector<UpdateReadySignal> iUpdateReady;
    Semaphore iShutdown;
    TBool iExit;
    TUint iMaxClientCount;
    TUint iClientCount;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_PROVIDER_SUBSCRIPTION_LONGPOLL
