/**
 * List(s) of UPnP devices suitable for use in control points
 *
 * Cp prefixes show that classes are intended for use in control points
 * Route inside a name implies that a class requires one instance per network interface
 */

#ifndef HEADER_CPIDEVICEUPNP
#define HEADER_CPIDEVICEUPNP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Thread.h>
#include <Discovery.h>
#include <Timer.h>
#include <CpiDevice.h>
#include <CpiService.h>
#include <DeviceXml.h>
#include <XmlFetcher.h>

namespace Zapp {

class CpiDeviceListUpnp;
/**
 * UPnP-specific device
 *
 * Can be created in response to either a msearch request or a multicast alive
 * notification.  Uses a timer to remove itself from ots owning list if no
 * subsequent alive message is received within a specified maxage.
 */
class CpiDeviceUpnp : public CpiDevice
{
public:
    CpiDeviceUpnp(const Brx& aUdn, const Brx& aLocation, TUint aMaxAgeSecs, IDeviceRemover& aDeviceList);
    const Brx& Location() const;

    /**
     * Called to reset the maxage timeout each time an alive message is received.
     * A device should be considered alive while at least one of its services hasn't
     * expired so the underlying timer is only updated if the new max age is later
     * than the current one.
     */
    void UpdateMaxAge(TUint aSeconds);

    void FetchXml(CpiDeviceListUpnp& aList);

    void InterruptXmlFetch();

    TBool GetAttribute(const char* aKey, Brh& aValue) const;
    void Invoke(Invocation& aInvocation);
    TUint Subscribe(Subscription& aSubscription, const Uri& aSubscriber);
    TUint Renew(Subscription& aSubscription);
    void Unsubscribe(Subscription& aSubscription, const Brx& aSid);
    void ProcessPropertyNotification(const Brx& aNotification, PropertyMap& aProperties);
private:
    ~CpiDeviceUpnp();
    void TimerExpired();
    void GetServiceUri(Uri& aUri, const TChar* aType, const ServiceType& aServiceType);
    void GetControlUri(const Invocation& aInvocation, Uri& aUri);
    void XmlFetchCompleted(IAsync& aAsync);
    static TBool UdnMatches(const Brx& aFound, const Brx& aTarget);
private:
    Brhz iLocation;
    XmlFetch* iXmlFetch;
    Brh iXml;
    DeviceXmlDocument* iDeviceXmlDocument;
    DeviceXml* iDeviceXml;
    Timer* iTimer;
    TUint iExpiryTime;
    IDeviceRemover& iDeviceList;
    Brh iControlUrl;
    CpiDeviceListUpnp* iList;
};

/**
 * UPnP-specific list of devices for a single network interface.
 *
 * This class is not intended for use outside this module.
 */
class CpiDeviceListUpnp : public CpiDeviceList, public ISsdpNotifyHandler
{
public:
    void XmlFetchCompleted(CpiDevice& aDevice, TBool aError);
protected:
    CpiDeviceListUpnp(FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved);
    ~CpiDeviceListUpnp();

    /**
     * Checks to see if a device is already in the list and updates its maxage
     * timeout if it is.
     * Returns true if an existing device was found.  Returning false implies
     * that this is a new device which should be added to the list.
     * false will always be returned while a list is being refreshed.
     */
    TBool Update(const Brx& aUdn, TUint aMaxAge);
    // CpiDeviceList
    void Start();
    void Refresh();
    TBool IsDeviceReady(CpiDevice& aDevice);
    TBool IsLocationReachable(const Brx& aLocation) const;
    // ISsdpNotifyHandler
    void SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion,
                                   const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion,
                                    const Brx& aLocation, TUint aMaxAge);
    void SsdpNotifyRootByeBye(const Brx& aUuid);
    void SsdpNotifyUuidByeBye(const Brx& aUuid);
    void SsdpNotifyDeviceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion);
    void SsdpNotifyServiceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion);
private:
    void RefreshTimerComplete();
    void CurrentNetworkInterfaceChanged();
    void SubnetChanged();
    void HandleInterfaceChange(TBool aNewSubnet);
    void RemoveAll();
protected:
    SsdpListenerUnicast* iUnicastListener;
private:
    TIpAddress iInterface;
    SsdpListenerMulticast* iMulticastListener;
    TInt iNotifyHandlerId;
    TUint iInterfaceChangeListenerId;
    TUint iSubnetChangeListenerId;
    TBool iStarted;
    Timer* iRefreshTimer;
    Semaphore iXmlFetchSem;
};

/**
 * List of all UPnP devices for a single network interface.
 *
 * This class is not intended for use outside this module.
 */
class CpiDeviceListUpnpAll : public CpiDeviceListUpnp
{
public:
    CpiDeviceListUpnpAll(FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved);
    void Start();
    void SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge);
};

/**
 * List of all root UPnP devices for a single network interface.
 *
 * This class is not intended for use outside this module.
 */
class CpiDeviceListUpnpRoot : public CpiDeviceListUpnp
{
public:
    CpiDeviceListUpnpRoot(FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved);
    void Start();
    void SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge);
};

/**
 * List of all UPnP devices with a given uuid (udn) for a single network interface.
 *
 * This class is not intended for use outside this module.
 */
class CpiDeviceListUpnpUuid : public CpiDeviceListUpnp
{
public:
    CpiDeviceListUpnpUuid(const Brx& aUuid, FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved);
    void Start();
    void SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge);
private:
    Brh iUuid;
};

/**
 * List of all UPnP devices of a given device type for a single network interface.
 *
 * This class is not intended for use outside this module.
 */
class CpiDeviceListUpnpDeviceType : public CpiDeviceListUpnp
{
public:
    CpiDeviceListUpnpDeviceType(const Brx& aDomainName, const Brx& aDeviceType, TUint aVersion,
                                FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved);
    void Start();
    void SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion,
                                   const Brx& aLocation, TUint aMaxAge);
private:
    Brh iDomainName;
    Brh iDeviceType;
    TUint iVersion;
};

/**
 * List of all UPnP devices of a given service type for a single network interface.
 *
 * This class is not intended for use outside this module.
 */
class CpiDeviceListUpnpServiceType : public CpiDeviceListUpnp
{
public:
    CpiDeviceListUpnpServiceType(const Brx& aDomainName, const Brx& aServiceType, TUint aVersion,
                                 FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved);
    void Start();
    void SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion,
                                    const Brx& aLocation, TUint aMaxAge);
private:
    Brh iDomainName;
    Brh iServiceType;
    TUint iVersion;
};

} // namespace Zapp

#endif // HEADER_CPIDEVICEUPNP
