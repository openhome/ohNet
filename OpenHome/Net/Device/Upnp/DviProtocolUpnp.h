#ifndef HEADER_DVIPROTOCOLUPNP
#define HEADER_DVIPROTOCOLUPNP

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Uri.h>
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
class DvStack;

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

class DviProtocolUpnp : public IDvProtocol, private IUpnpMsearchHandler, private IUpnpAnnouncementData
{
    friend class DviProtocolUpnpDeviceXmlWriter;
    static const TUint kMaxUriBytes = 256;
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
    void SendByeByes(TIpAddress aAdapter, const Brx& aUriBase, Functor aCompleted);
    void SendAlives(TIpAddress aAdapter, const Brx& aUriBase);
private:
    DviProtocolUpnpAdapterSpecificData* AddInterface(const NetworkAdapter& aAdapter);
    void HandleInterfaceChange();
    TInt FindAdapter(TIpAddress aAdapter, const std::vector<NetworkAdapter*>& aAdapterList);
    TInt FindListenerForSubnet(TIpAddress aSubnet);
    TInt FindListenerForInterface(TIpAddress aSubnet);
    void SubnetDisabled();
    void SubnetUpdated();
    void SendAliveNotifications();
    void QueueAliveTimer();
    void SendUpdateNotifications();
    void GetUriDeviceXml(Bwx& aUri, const Brx& aUriBase);
    void GetDeviceXml(Brh& aXml, TIpAddress aAdapter);
    void LogMulticastNotification(const char* aType);
    void LogUnicastNotification(const char* aType);
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
    DvStack& iDvStack;
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
//    friend class DviProtocolUpnp;
public:
    DviProtocolUpnpAdapterSpecificData(DvStack& aDvStack, IUpnpMsearchHandler& aMsearchHandler, const NetworkAdapter& aAdapter, Bwx& aUriBase, TUint aServerPort);
    void Destroy();
    TIpAddress Interface() const;
    TIpAddress Subnet() const;
    const Brx& UriBase() const;
    void UpdateServerPort(DviServerUpnp& aServer);
    void UpdateUriBase(Bwx& aUriBase);
    TUint ServerPort() const;
    const Brx& DeviceXml() const;
    void SetDeviceXml(Brh& aXml);
    void ClearDeviceXml();
    void SetPendingDelete();
    void BonjourRegister(const TChar* aName, const Brx& aUdn, const Brx& aProtocol, const Brx& aResourceDir);
    void BonjourDeregister();
    void SendByeByeThenAlive(DviProtocolUpnp& aDevice);
private:
    ~DviProtocolUpnpAdapterSpecificData();
    IUpnpMsearchHandler* Handler();
    void ByeByesComplete();
    TBool IsLocationReachable(const Endpoint& aEndpoint);
private: // from ISsdpMsearchHandler
    void SsdpSearchAll(const Endpoint& aEndpoint, TUint aMx);
    void SsdpSearchRoot(const Endpoint& aEndpoint, TUint aMx);
    void SsdpSearchUuid(const Endpoint& aEndpoint, TUint aMx, const Brx& aUuid);
    void SsdpSearchDeviceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion);
    void SsdpSearchServiceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion);
private:
    TUint iRefCount;
    DvStack& iDvStack;
    IUpnpMsearchHandler* iMsearchHandler;
    SsdpListenerMulticast* iListener;
    TInt iId;
    TIpAddress iSubnet;
    TIpAddress iAdapter;
    TIpAddress iMask;
    Bws<Uri::kMaxUriBytes> iUriBase;
    TUint iServerPort;
    Brh iDeviceXml;
    BonjourWebPage* iBonjourWebPage;
    DviProtocolUpnp* iDevice;
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
    enum ETagEscaped
    {
        eTagEscaped
       ,eTagUnescaped
    };
private:
    void WriteTag(const TChar* aTagName, const TChar* aAttributeKey, ETagRequirementLevel aRequirementLevel, ETagEscaped aEscaped = eTagEscaped);
    void WritePresentationUrlTag(TIpAddress aAdapter);
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
    static void Write(const DviService& aService, const DviProtocolUpnp& aDevice, IResourceWriter& aResourceWriter);
private:
    static void WriteServiceXml(WriterBwh& aWriter, const DviService& aService, const DviProtocolUpnp& aDevice);
    static void WriteServiceActionParams(WriterBwh& aWriter, const Action& aAction, TBool aIn);
    static void GetRelatedVariableName(Bwh& aName, const Brx& aActionName, const Brx& aParameterName);
    static void WriteStateVariable(IWriter& aWriter, const OpenHome::Net::Parameter& aParam, TBool aEvented, const Action* aAction);
    static void WriteTechnicalStateVariables(IWriter& aWriter, const Action* aAction, const Action::VectorParameters& aParams);
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVIPROTOCOLUPNP
