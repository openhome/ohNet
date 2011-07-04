#ifndef HEADER_DVIDEVICEUPNP
#define HEADER_DVIDEVICEUPNP

#include <Standard.h>
#include <OhNetTypes.h>
#include <Buffer.h>
#include <DviDevice.h>
#include <Discovery.h>
#include <Thread.h>
#include <OhNet.h>
#include <Timer.h>
#include <Ssdp.h>
#include <Functor.h>
#include <DviServerUpnp.h>

#include <vector>

namespace OpenHome {
namespace Net {

class DeviceMsgScheduler;
class DviDeviceUpnpXmlWriter;
class BonjourWebPage;

class DviDeviceUpnp : public IDvProtocol
{
    friend class DviDeviceUpnpXmlWriter;
public:
    static const Brn kProtocolName;
    static const Brn kDeviceXmlName;
    static const Brn kServiceXmlName;
    static const Brn kControlUrlTail;
    static const Brn kEventUrlTail;
public:
    DviDeviceUpnp(DviDevice& aDevice);
    ~DviDeviceUpnp();
    Brn Domain() const;
    Brn Type() const;
    TUint Version() const;
    void MsgSchedulerComplete(DeviceMsgScheduler* aScheduler);
private:
    void AddInterface(const NetworkAdapter& aNif);
    void SubnetListChanged();
    TInt FindInterface(TIpAddress aInterface, const std::vector<NetworkAdapter*>& aNifList);
    TInt FindListenerForSubnet(TIpAddress aSubnet);
    TInt FindListenerForInterface(TIpAddress aSubnet);
    void SubnetDisabled();
    void SubnetUpdated();
    void SendAliveNotifications();
    void SendUpdateNotifications();
    void GetUriDeviceXml(Bwh& aUri, const Brx& aUriBase);
    void GetDeviceXml(Brh& aXml, TIpAddress aInterface);
    void WriteServiceXml(const DviService& aService, IResourceWriter& aResourceWriter);
    void WriteServiceActionParams(WriterBwh& aWriter, const Action& aAction, TBool aIn);
    void GetRelatedVariableName(Bwh& aName, const Brx& aActionName, const Brx& aParameterName);
    void WriteStateVariable(IWriter& aWriter, const OpenHome::Net::Parameter& aParam, TBool aEvented, const Action* aAction);
    void WriteTechnicalStateVariables(IWriter& aWriter, const Action* aAction, const Action::VectorParameters& aParams);
public:
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter);
    const Brx& ProtocolName() const;
    void Enable();
    void Disable(Functor& aComplete);
    void GetAttribute(const TChar* aKey, const TChar** aValue) const;
    void SetAttribute(const TChar* aKey, const TChar* aValue);
    void SetCustomData(const TChar* aTag, void* aData);
private:
    void SsdpSearchAll(const Endpoint& aEndpoint, TUint aMx, TIpAddress aInterface);
    void SsdpSearchRoot(const Endpoint& aEndpoint, TUint aMx, TIpAddress aInterface);
    void SsdpSearchUuid(const Endpoint& aEndpoint, TUint aMx, TIpAddress aInterface, const Brx& aUuid);
    void SsdpSearchDeviceType(const Endpoint& aEndpoint, TUint aMx, TIpAddress aInterface, const Brx& aDomain, const Brx& aType, TUint aVersion);
    void SsdpSearchServiceType(const Endpoint& aEndpoint, TUint aMx, TIpAddress aInterface, const Brx& aDomain, const Brx& aType, TUint aVersion);
private:
    class Nif : public ISsdpMsearchHandler, public INonCopyable
    {
        friend class DviDeviceUpnp;
    public:
        Nif(DviDeviceUpnp& aDeviceUpnp, DviDevice& aDevice, const NetworkAdapter& aNif, Bwh& aUriBase, TUint aServerPort);
        ~Nif();
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
        void BonjourRegister(const TChar* aName);
        void BonjourDeregister();
    private:
		DviDeviceUpnp* Device();
    private:
        void SsdpSearchAll(const Endpoint& aEndpoint, TUint aMx);
        void SsdpSearchRoot(const Endpoint& aEndpoint, TUint aMx);
        void SsdpSearchUuid(const Endpoint& aEndpoint, TUint aMx, const Brx& aUuid);
        void SsdpSearchDeviceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion);
        void SsdpSearchServiceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion);
    private:
        DviDeviceUpnp* iDeviceUpnp;
        DviDevice& iDevice;
        SsdpListenerMulticast* iListener;
        TInt iId;
        TIpAddress iSubnet;
        TIpAddress iInterface;
        Bwh iUriBase;
        TUint iServerPort;
        Brh iDeviceXml;
        BonjourWebPage* iBonjourWebPage;
    };
private:
    DviDevice& iDevice;
    AttributeMap iAttributeMap;
    Mutex iLock;
    std::vector<Nif*> iInterfaces;
    TInt iSubnetListChangeListenerId;
    std::vector<DeviceMsgScheduler*> iMsgSchedulers;
    TUint iSubnetDisableCount;
    Functor iDisableComplete;
    Timer* iAliveTimer;
    TUint iUpdateCount;
    TBool iSuppressScheduledEvents;
    DviServerUpnp* iServer;
};

class DviDeviceUpnpXmlWriter : public IResourceWriter
{
public:
    DviDeviceUpnpXmlWriter(DviDeviceUpnp& aDeviceUpnp);
    void Write(TIpAddress aInterface);
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
    DviDeviceUpnp& iDeviceUpnp;
    WriterBwh iWriter;
};

class DeviceMsgScheduler : private INonCopyable
{
    static const TInt kMinTimerIntervalMs = 10;
public:
    virtual ~DeviceMsgScheduler();
	void Stop();
protected:
    DeviceMsgScheduler(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp, TUint aEndTimeMs, TUint aTotalMsgs, Bwh& aUri);
    virtual void Next(TUint aIndex);
    void ScheduleNextTimer() const;
private:
    void NextMsg();
protected:
    DviDevice& iDevice;
    DviDeviceUpnp& iDeviceUpnp;
    ISsdpNotify* iNotifier;
    Timer* iTimer;
    Brh iUri;
private:
    TUint iTotal;
    TUint iIndex;
    TUint iEndTimeMs;
	TBool iStop;
};

class DeviceMsgSchedulerMsearch : public DeviceMsgScheduler
{
protected:
    DeviceMsgSchedulerMsearch(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp, const Endpoint& aRemote,
                              TUint aMx, TUint aTotalMsgs, Bwh& aUri, TUint aConfigId);
};

class DeviceMsgSchedulerMsearchAll : public DeviceMsgSchedulerMsearch
{
public:
    DeviceMsgSchedulerMsearchAll(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp, const Endpoint& aRemote,
                                 TUint aMx, Bwh& aUri, TUint aConfigId);
    ~DeviceMsgSchedulerMsearchAll();
};

class DeviceMsgSchedulerMsearchRoot : public DeviceMsgSchedulerMsearch
{
public:
    DeviceMsgSchedulerMsearchRoot(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp, const Endpoint& aRemote,
                                  TUint aMx, Bwh& aUri, TUint aConfigId);
    ~DeviceMsgSchedulerMsearchRoot();
private:
    void Next(TUint aIndex);
};

class DeviceMsgSchedulerMsearchUuid : public DeviceMsgSchedulerMsearch
{
public:
    DeviceMsgSchedulerMsearchUuid(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp, const Endpoint& aRemote,
                                  TUint aMx, Bwh& aUri, TUint aConfigId);
    ~DeviceMsgSchedulerMsearchUuid();
private:
    void Next(TUint aIndex);
};

class DeviceMsgSchedulerMsearchDeviceType : public DeviceMsgSchedulerMsearch
{
public:
    DeviceMsgSchedulerMsearchDeviceType(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp, const Endpoint& aRemote,
                                        TUint aMx, Bwh& aUri, TUint aConfigId);
    ~DeviceMsgSchedulerMsearchDeviceType();
private:
    void Next(TUint aIndex);
};

class DeviceMsgSchedulerMsearchServiceType : public DeviceMsgSchedulerMsearch
{
public:
    DeviceMsgSchedulerMsearchServiceType(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp, const Endpoint& aRemote, TUint aMx,
                                         const OpenHome::Net::ServiceType& aServiceType, Bwh& aUri, TUint aConfigId);
    ~DeviceMsgSchedulerMsearchServiceType();
private:
    void Next(TUint aIndex);
private:
    const OpenHome::Net::ServiceType& iServiceType;
};

class DeviceMsgSchedulerNotify : public DeviceMsgScheduler
{
protected:
    DeviceMsgSchedulerNotify(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp, TUint aIntervalMs, TUint aTotalMsgs,
                             TIpAddress aInterface, Bwh& aUri, TUint aConfigId);
protected:
    SsdpNotifier iSsdpNotifier;
};

class DeviceMsgSchedulerNotifyAlive : public DeviceMsgSchedulerNotify
{
    static const TUint kMsgIntervalMs = 40;
public:
    DeviceMsgSchedulerNotifyAlive(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp,
                                  TIpAddress aInterface, Bwh& aUri, TUint aConfigId);
    ~DeviceMsgSchedulerNotifyAlive();
};

class DeviceMsgSchedulerNotifyByeBye : public DeviceMsgSchedulerNotify
{
    static const TUint kMsgIntervalMs = 10;
public:
    DeviceMsgSchedulerNotifyByeBye(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp,
                                   TIpAddress aInterface, Bwh& aUri, TUint aConfigId,
                                   Functor& aCompleted);
    ~DeviceMsgSchedulerNotifyByeBye();
private:
    Functor iCompleted;
};

class DeviceMsgSchedulerNotifyUpdate : public DeviceMsgSchedulerNotify
{
    static const TUint kMsgIntervalMs = 20;
public:
    DeviceMsgSchedulerNotifyUpdate(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp,
                                   TIpAddress aInterface, Bwh& aUri, TUint aConfigId,
                                   Functor& aCompleted);
    ~DeviceMsgSchedulerNotifyUpdate();
private:
    Functor iCompleted;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVIDEVICEUPNP
