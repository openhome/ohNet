#ifndef HEADER_DVIPROTOCOLUPNP
#define HEADER_DVIPROTOCOLUPNP

#include <OpenHome/Private/Standard.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Private/DviServerUpnp.h>

#include <vector>

namespace OpenHome {
namespace Net {

class DviMsgScheduler;
class DviProtocolUpnpDeviceXmlWriter;
class BonjourWebPage;
class DviProtocolUpnpAdapterSpecificData;

class IUpnpMsearchHandler
{
public:
    virtual void SsdpSearchAll(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter) = 0;
    virtual void SsdpSearchRoot(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter) = 0;
    virtual void SsdpSearchUuid(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter, const Brx& aUuid) = 0;
    virtual void SsdpSearchDeviceType(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter, const Brx& aDomain, const Brx& aType, TUint aVersion) = 0;
    virtual void SsdpSearchServiceType(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter, const Brx& aDomain, const Brx& aType, TUint aVersion) = 0;
};

class IUpnpAnnouncementData
{
public:
    virtual const Brx& Udn() const = 0;
    virtual TBool IsRoot() const = 0;
    virtual TUint ServiceCount() const = 0;
    virtual DviService& Service(TUint aIndex) = 0;
    virtual Brn Domain() const = 0;
    virtual Brn Type() const = 0;
    virtual TUint Version() const = 0;
};

class IUpnpMsgListener
{
public:
    virtual void NotifyMsgSchedulerComplete(DviMsgScheduler* aScheduler) = 0;
};


class DviProtocolUpnp : public IDvProtocol, private IUpnpMsearchHandler, private IUpnpAnnouncementData, private IUpnpMsgListener
{
    friend class DviProtocolUpnpDeviceXmlWriter;
public:
    static const Brn kProtocolName;
    static const Brn kDeviceXmlName;
    static const Brn kServiceXmlName;
    static const Brn kControlUrlTail;
    static const Brn kEventUrlTail;
public:
    DviProtocolUpnp(DviDevice& aDevice);
    ~DviProtocolUpnp();
public: // from IUpnpAnnouncementData
    const Brx& Udn() const;
    TBool IsRoot() const;
    TUint ServiceCount() const;
    DviService& Service(TUint aIndex);
    Brn Domain() const;
    Brn Type() const;
    TUint Version() const;
private: // from IUpnpMsgListener
    void NotifyMsgSchedulerComplete(DviMsgScheduler* aScheduler);
private:
    void AddInterface(const NetworkAdapter& aAdapter);
    void HandleInterfaceChange();
    TInt FindAdapter(TIpAddress aAdapter, const std::vector<NetworkAdapter*>& aAdapterList);
    TInt FindListenerForSubnet(TIpAddress aSubnet);
    TInt FindListenerForInterface(TIpAddress aSubnet);
    void SubnetDisabled();
    void SubnetUpdated();
    void SendAliveNotifications();
    void SendUpdateNotifications();
    void GetUriDeviceXml(Bwh& aUri, const Brx& aUriBase);
    void GetDeviceXml(Brh& aXml, TIpAddress aAdapter);
public: // from IDvProtocol
    void WriteResource(const Brx& aUriTail, TIpAddress aAdapter, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter);
    const Brx& ProtocolName() const;
    void Enable();
    void Disable(Functor& aComplete);
    void GetAttribute(const TChar* aKey, const TChar** aValue) const;
    void SetAttribute(const TChar* aKey, const TChar* aValue);
    void SetCustomData(const TChar* aTag, void* aData);
    void GetResourceManagerUri(const NetworkAdapter& aAdapter, Brh& aUri);
private: // from IUpnpMsearchHandler
    void SsdpSearchAll(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter);
    void SsdpSearchRoot(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter);
    void SsdpSearchUuid(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter, const Brx& aUuid);
    void SsdpSearchDeviceType(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter, const Brx& aDomain, const Brx& aType, TUint aVersion);
    void SsdpSearchServiceType(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter, const Brx& aDomain, const Brx& aType, TUint aVersion);
private:
    DviDevice& iDevice;
    AttributeMap iAttributeMap;
    Mutex iLock;
    std::vector<DviProtocolUpnpAdapterSpecificData*> iAdapters;
    TInt iCurrentAdapterChangeListenerId;
    TInt iSubnetListChangeListenerId;
    std::vector<DviMsgScheduler*> iMsgSchedulers;
    TUint iSubnetDisableCount;
    Functor iDisableComplete;
    Timer* iAliveTimer;
    TUint iUpdateCount;
    TBool iSuppressScheduledEvents;
    DviServerUpnp* iServer;
};

class DviProtocolUpnpAdapterSpecificData : public ISsdpMsearchHandler, public INonCopyable
{
    friend class DviProtocolUpnp;
public:
    DviProtocolUpnpAdapterSpecificData(IUpnpMsearchHandler& aMsearchHandler, const NetworkAdapter& aAdapter, Bwh& aUriBase, TUint aServerPort);
    ~DviProtocolUpnpAdapterSpecificData();
    TIpAddress Interface() const;
    TIpAddress Subnet() const;
    const Brx& UriBase() const;
    void UpdateServerPort(DviServerUpnp& aServer);
    void UpdateUriBase(Bwh& aUriBase);
    TUint ServerPort() const;
    const Brx& DeviceXml() const;
    void SetDeviceXml(Brh& aXml);
    void ClearDeviceXml();
	void SetPendingDelete();
    void BonjourRegister(const TChar* aName, const Brx& aUdn, const Brx& aProtocol, const Brx& aResourceDir);
    void BonjourDeregister();
private:
	IUpnpMsearchHandler* Handler();
private:
    void SsdpSearchAll(const Endpoint& aEndpoint, TUint aMx);
    void SsdpSearchRoot(const Endpoint& aEndpoint, TUint aMx);
    void SsdpSearchUuid(const Endpoint& aEndpoint, TUint aMx, const Brx& aUuid);
    void SsdpSearchDeviceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion);
    void SsdpSearchServiceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion);
private:
    IUpnpMsearchHandler* iMsearchHandler;
    SsdpListenerMulticast* iListener;
    TInt iId;
    TIpAddress iSubnet;
    TIpAddress iAdapter;
    Bwh iUriBase;
    TUint iServerPort;
    Brh iDeviceXml;
    BonjourWebPage* iBonjourWebPage;
};

class DviProtocolUpnpDeviceXmlWriter : public IResourceWriter
{
public:
    DviProtocolUpnpDeviceXmlWriter(DviProtocolUpnp& aDeviceUpnp);
    void Write(TIpAddress aAdapter);
    void TransferTo(Brh& aBuf);
private:
    enum ETagRequirementLevel
    {
        eTagMandatory
       ,eTagRecommended
       ,eTagOptional
    };
private:
    void WriteTag(const TChar* aTagName, const TChar* aAttributeKey, ETagRequirementLevel aRequirementLevel);
    void WriteResourceBegin(TUint aTotalBytes, const TChar* aMimeType);
    void WriteResource(const TByte* aData, TUint aBytes);
    void WriteResourceEnd();
private:
    DviProtocolUpnp& iDeviceUpnp;
    WriterBwh iWriter;
};

class DviProtocolUpnpServiceXmlWriter
{
public:
    static void Write(const DviService& aService, IResourceWriter& aResourceWriter);
private:
    static void WriteServiceXml(WriterBwh& aWriter, const DviService& aService);
    static void WriteServiceActionParams(WriterBwh& aWriter, const Action& aAction, TBool aIn);
    static void GetRelatedVariableName(Bwh& aName, const Brx& aActionName, const Brx& aParameterName);
    static void WriteStateVariable(IWriter& aWriter, const OpenHome::Net::Parameter& aParam, TBool aEvented, const Action* aAction);
    static void WriteTechnicalStateVariables(IWriter& aWriter, const Action* aAction, const Action::VectorParameters& aParams);
};

class DviMsg;

class DviMsgScheduler : private INonCopyable
{
    static const TInt kMinTimerIntervalMs   = 10;
    static const TUint kMsgIntervalMsAlive  = 40;
    static const TUint kMsgIntervalMsByeBye = 10;
    static const TUint kMsgIntervalMsUpdate = 20;
public:
    static DviMsgScheduler* NewMsearchAll(IUpnpAnnouncementData& aAnnouncementData, IUpnpMsgListener& aListener,
                                          const Endpoint& aRemote, TUint aMx, Bwh& aUri, TUint aConfigId);
    static DviMsgScheduler* NewMsearchRoot(IUpnpAnnouncementData& aAnnouncementData, IUpnpMsgListener& aListener,
                                           const Endpoint& aRemote, TUint aMx, Bwh& aUri, TUint aConfigId);
    static DviMsgScheduler* NewMsearchUuid(IUpnpAnnouncementData& aAnnouncementData, IUpnpMsgListener& aListener,
                                           const Endpoint& aRemote, TUint aMx, Bwh& aUri, TUint aConfigId);
    static DviMsgScheduler* NewMsearchDeviceType(IUpnpAnnouncementData& aAnnouncementData, IUpnpMsgListener& aListener,
                                                 const Endpoint& aRemote, TUint aMx, Bwh& aUri, TUint aConfigId);
    static DviMsgScheduler* NewMsearchServiceType(IUpnpAnnouncementData& aAnnouncementData, IUpnpMsgListener& aListener, const Endpoint& aRemote,
                                                  TUint aMx, const OpenHome::Net::ServiceType& aServiceType, Bwh& aUri, TUint aConfigId);
    static DviMsgScheduler* NewNotifyAlive(IUpnpAnnouncementData& aAnnouncementData, IUpnpMsgListener& aListener,
                                           TIpAddress aAdapter, Bwh& aUri, TUint aConfigId);
    static DviMsgScheduler* NewNotifyByeBye(IUpnpAnnouncementData& aAnnouncementData, IUpnpMsgListener& aListener,
                                            TIpAddress aAdapter, Bwh& aUri, TUint aConfigId, Functor& aCompleted);
    static DviMsgScheduler* NewNotifyUpdate(IUpnpAnnouncementData& aAnnouncementData, IUpnpMsgListener& aListener,
                                            TIpAddress aAdapter, Bwh& aUri, TUint aConfigId, Functor& aCompleted);
    ~DviMsgScheduler();
	void Stop();
private:
    DviMsgScheduler(IUpnpMsgListener& aListener, TUint aMx);
    DviMsgScheduler(IUpnpMsgListener& aListener);
    void Construct();
    void SetDuration(TUint aDuration);
    void NextMsg();
    void ScheduleNextTimer(TUint aRemainingMsgs) const;
private:
    DviMsg* iMsg;
    Timer* iTimer;
    TUint iEndTimeMs;
    IUpnpMsgListener& iListener;
	TBool iStop;
};

class DviMsg : private INonCopyable
{
public:
    virtual ~DviMsg();
    virtual TUint TotalMsgCount() const;
    virtual TUint NextMsg();
protected:
    DviMsg(IUpnpAnnouncementData& aAnnouncementData, Bwh& aUri);
protected:
    IUpnpAnnouncementData& iAnnouncementData;
    ISsdpNotify* iNotifier;
    Brh iUri;
private:
    TUint iTotal;
    TUint iIndex;
    TUint iEndTimeMs;
	TBool iStop;
};

class DviMsgMsearch : public DviMsg
{
protected:
    DviMsgMsearch(IUpnpAnnouncementData& aAnnouncementData,
                  const Endpoint& aRemote, Bwh& aUri, TUint aConfigId);
};

class DviMsgMsearchAll : public DviMsgMsearch
{
private:
    friend class DviMsgScheduler;
    DviMsgMsearchAll(IUpnpAnnouncementData& aAnnouncementData,
                     const Endpoint& aRemote, Bwh& aUri, TUint aConfigId);
};

class DviMsgMsearchRoot : public DviMsgMsearch
{
private:
    friend class DviMsgScheduler;
    DviMsgMsearchRoot(IUpnpAnnouncementData& aAnnouncementData,
                      const Endpoint& aRemote, Bwh& aUri, TUint aConfigId);
private: // from DviMsg
    TUint TotalMsgCount() const;
    TUint NextMsg();
};

class DviMsgMsearchUuid : public DviMsgMsearch
{
private:
    friend class DviMsgScheduler;
    DviMsgMsearchUuid(IUpnpAnnouncementData& aAnnouncementData,
                      const Endpoint& aRemote, Bwh& aUri, TUint aConfigId);
private: // from DviMsg
    TUint TotalMsgCount() const;
    TUint NextMsg();
};

class DviMsgMsearchDeviceType : public DviMsgMsearch
{
private:
    friend class DviMsgScheduler;
    DviMsgMsearchDeviceType(IUpnpAnnouncementData& aAnnouncementData,
                            const Endpoint& aRemote, Bwh& aUri, TUint aConfigId);
private: // from DviMsg
    TUint TotalMsgCount() const;
    TUint NextMsg();
};

class DviMsgMsearchServiceType : public DviMsgMsearch
{
private:
    friend class DviMsgScheduler;
    DviMsgMsearchServiceType(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote,
                             const OpenHome::Net::ServiceType& aServiceType, Bwh& aUri, TUint aConfigId);
private: // from DviMsg
    TUint TotalMsgCount() const;
    TUint NextMsg();
private:
    const OpenHome::Net::ServiceType& iServiceType;
};

class DviMsgNotify : public DviMsg
{
private:
    friend class DviMsgScheduler;
    static DviMsgNotify* NewAlive(IUpnpAnnouncementData& aAnnouncementData,
                                  TIpAddress aAdapter, Bwh& aUri, TUint aConfigId);
    static DviMsgNotify* NewByeBye(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter,
                                   Bwh& aUri, TUint aConfigId, Functor& aCompleted);
    static DviMsgNotify* NewUpdate(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter,
                                   Bwh& aUri, TUint aConfigId, Functor& aCompleted);
    DviMsgNotify(IUpnpAnnouncementData& aAnnouncementData,
                 TIpAddress aAdapter, Bwh& aUri, TUint aConfigId);
private: // from DviMsg
    TUint NextMsg();
private:
    SsdpNotifier iSsdpNotifier;
    Functor iCompleted;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVIPROTOCOLUPNP
