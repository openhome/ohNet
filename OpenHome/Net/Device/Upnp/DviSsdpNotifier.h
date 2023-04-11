#ifndef HEADER_DVI_SSDP_NOTIFIER
#define HEADER_DVI_SSDP_NOTIFIER

#include <OpenHome/Net/Private/DviProtocolUpnp.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Net/Private/Ssdp.h>

#include <vector>

EXCEPTION(MsearchResponseLimit)

namespace OpenHome {
namespace Net {

class SsdpNotifierScheduler;
class ISsdpNotifyListener
{
public:
    virtual ~ISsdpNotifyListener() {}
    virtual void NotifySchedulerComplete(SsdpNotifierScheduler* aScheduler) = 0;
};

class SsdpNotifierScheduler : private INonCopyable
{
    static const TInt kMinTimerIntervalMs   = 10;
public:
    virtual ~SsdpNotifierScheduler();
    void Stop();
    void SetUdn(const Brx& aUdn);
protected:
    SsdpNotifierScheduler(DvStack& aDvStack, ISsdpNotifyListener& aListener, const TChar* aId);
    void Start(TUint aDuration, TUint aMsgCount);
    virtual void NotifyComplete(TBool aCancelled);
private:
    virtual TUint NextMsg() = 0;
    void SendNextMsg();
    void ScheduleNextTimer(TUint aRemainingMsgs) const;
protected:
    void LogNotifierStart(const TChar* aType, TIpAddress aAddress);
    const TChar* iType;
    const TChar* iId;
private:
    Timer* iTimer;
    DvStack& iDvStack;
    TUint iEndTimeMs;
    ISsdpNotifyListener& iListener;
    TBool iStop;
    Brn iUdn;
};


class MsearchResponse : public SsdpNotifierScheduler
{
public:
    MsearchResponse(DvStack& aDvStack, ISsdpNotifyListener& aListener);
    ~MsearchResponse();
    void StartAll(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId, TIpAddress aAdapter);
    void StartRoot(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId, TIpAddress aAdapter);
    void StartUuid(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId, TIpAddress aAdapter);
    void StartDeviceType(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId, TIpAddress aAdapter);
    void StartServiceType(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const OpenHome::Net::ServiceType& aServiceType, const Brx& aUri, TUint aConfigId, TIpAddress aAdapter);
    Endpoint Remote() const;
private:
    void Start(IUpnpAnnouncementData& aAnnouncementData, TUint aTotalMsgs, TUint aNextMsgIndex, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId, TIpAddress aAdapter);
private: // from DviMsg
    TUint NextMsg();
private:
    static const TUint kMaxUriBytes = 256;
    IUpnpAnnouncementData* iAnnouncementData;
    ISsdpNotify* iNotifier;
    Endpoint iRemote;
    Bws<kMaxUriBytes> iUri;
    TUint iRemainingMsgs;
    TUint iNextMsgIndex;
};

class DeviceAnnouncement : public SsdpNotifierScheduler
{
    static const TUint kMsgIntervalMsUpdate = 20;
public:
    DeviceAnnouncement(DvStack& aDvStack, ISsdpNotifyListener& aListener, TUint aMsgIntervalAlive, TUint aMsgIntervalByeBye);
    void StartAlive(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId);
    void StartByeBye(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId, FunctorGeneric<TBool>& aCompleted);
    void StartUpdate(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId, FunctorGeneric<TBool>& aCompleted);
private:
    void Start(ISsdpNotify& aNotifier, IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId, TUint aMsgInterval);
private: // from DviMsg
    TUint NextMsg();
    void NotifyComplete(TBool aCancelled);
private:
    static const TUint kMaxUriBytes = 256;
    SsdpNotifier iSsdpNotifier;
    SsdpNotifierAlive iNotifierAlive;
    SsdpNotifierByeBye iNotifierByeBye;
    SsdpNotifierUpdate iNotifierUpdate;
    TUint iMsgIntervalAlive;
    TUint iMsgIntervalByeBye;
    IUpnpAnnouncementData* iAnnouncementData;
    Bws<kMaxUriBytes> iUri;
    ISsdpNotify* iCurrentNotifier;
    FunctorGeneric<TBool> iCompleted;
    TUint iTotalMsgs;
    TUint iNextMsgIndex;
};

class DviSsdpNotifierManager : private ISsdpNotifyListener
{
    static const TUint kMaxMsearchResponses; // Maximum number of pending m-search responses per device per endpoint.
public:
    DviSsdpNotifierManager(DvStack& aDvStack);
    ~DviSsdpNotifierManager();
    void AnnouncementAlive(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId);
    void AnnouncementByeBye(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId, FunctorGeneric<TBool>& aCompleted);
    void AnnouncementUpdate(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId, FunctorGeneric<TBool>& aCompleted);
    void MsearchResponseAll(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId, TIpAddress aAdapter);
    void MsearchResponseRoot(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId, TIpAddress aAdapter);
    void MsearchResponseUuid(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId, TIpAddress aAdapter);
    void MsearchResponseDeviceType(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId, TIpAddress aAdapter);
    void MsearchResponseServiceType(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const OpenHome::Net::ServiceType& aServiceType, const Brx& aUri, TUint aConfigId, TIpAddress aAdapter);
    void Stop(const Brx& aUdn);
private:
    class Notifier
    {
    public:
        virtual ~Notifier();
        SsdpNotifierScheduler* Scheduler();
        TBool MatchesDevice(const Brx& aUdn) const;
        void SetActive(const Brx& aUdn);
        void SetInactive();
    protected:
        Notifier(SsdpNotifierScheduler* aScheduler);
    protected:
        SsdpNotifierScheduler* iScheduler;
    private:
        Brn iUdn;
    };
    class Responder : public Notifier
    {
    public:
        Responder(MsearchResponse* aResponder);
        MsearchResponse& Response();
    };
    class Announcer : public Notifier
    {
    public:
        Announcer(DeviceAnnouncement* aAnnouncer);
        DeviceAnnouncement& Announcement();
    };
private:
    void Stop(std::list<Notifier*>& aList, const Brx& aUdn);
    void Delete(std::list<Notifier*>& aList);
    Responder* GetResponder(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote);
    Announcer* GetAnnouncer(IUpnpAnnouncementData& aAnnouncementData);
    TBool TryMove(SsdpNotifierScheduler* aScheduler, std::list<Notifier*>& aFrom, std::list<Notifier*>& aTo);
private: // from ISsdpNotifyListener
    void NotifySchedulerComplete(SsdpNotifierScheduler* aScheduler);
private:
    DvStack& iDvStack;
    Mutex iLock;
    Semaphore iShutdownSem;
    std::list<Notifier*> iFreeResponders;
    std::list<Notifier*> iActiveResponders;
    std::list<Notifier*> iFreeAnnouncers;
    std::list<Notifier*> iActiveAnnouncers;
    TUint iAnnounceIntervalAlive;
    TUint iAnnounceIntervalByeBye;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_SSDP_NOTIFIER
