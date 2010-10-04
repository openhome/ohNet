#include <CpiDeviceUpnp.h>
#include <CpiDevice.h>
#include <Thread.h>
#include <Stack.h>
#include <CpiService.h>
#include <Stream.h>
#include <Zapp.h>
#include <Http.h>
#include <Ascii.h>
#include <Parser.h>
#include <XmlFetcher.h>
#include <ProtocolUpnp.h>
#include <XmlParser.h>
#include <Converter.h>
#include <Debug.h>
#include <DeviceXml.h>
#include <CpiSubscription.h>

#include <string.h>

using namespace Zapp;

// CpiDeviceUpnp

CpiDeviceUpnp::CpiDeviceUpnp(const Brx& aUdn, const Brx& aLocation, TUint aMaxAgeSecs, IDeviceRemover& aDeviceList)
    : CpiDevice(aUdn)
    , iLocation(aLocation)
    , iXmlFetch(NULL)
    , iDeviceXmlDocument(NULL)
    , iDeviceXml(NULL)
    , iExpiryTime(0)
    , iDeviceList(aDeviceList)
{
    iTimer = new Timer(MakeFunctor(*this, &CpiDeviceUpnp::TimerExpired));
    UpdateMaxAge(aMaxAgeSecs);
}

const Brx& CpiDeviceUpnp::Location() const
{
    return iLocation;
}

void CpiDeviceUpnp::UpdateMaxAge(TUint aSeconds)
{
    TUint delayMs = aSeconds * 1000;
    delayMs += 100; /* allow slightly longer than maxAge to cope with devices which
                       send out Alive messages at the last possible moment */
    TUint expiryTime = Os::TimeInMs() + delayMs;
    if (expiryTime >= iExpiryTime) {
        iExpiryTime = expiryTime;
        iTimer->FireAt(iExpiryTime);
    }
}

void CpiDeviceUpnp::FetchXml(CpiDeviceListUpnp& aList)
{
    iList = &aList;
    iXmlFetch = XmlFetchManager::Fetch();
    Uri* uri = new Uri(iLocation);
    AddRef();
    FunctorAsync functor = MakeFunctorAsync(*this, &CpiDeviceUpnp::XmlFetchCompleted);
    iXmlFetch->Set(uri, functor);
    XmlFetchManager::Fetch(iXmlFetch);
}

void CpiDeviceUpnp::InterruptXmlFetch()
{
    if (iXmlFetch != NULL) {
        iXmlFetch->Interrupt();
    }
}

TBool CpiDeviceUpnp::GetAttribute(const char* aKey, Brh& aValue) const
{
	Brn key(aKey);
	
	Parser parser(key);
	
	if (parser.Next('.') == Brn("Upnp")) {
		Brn property = parser.Remaining();

	    if (property == Brn("Location")) {
	        aValue.Set(iLocation);
	        return (true);
	    }
	    if (property == Brn("DeviceXml")) {
	        aValue.Set(iXml);
	        return (true);
	    }

		const DeviceXml* device = iDeviceXml;
		
		if (parser.Next('.') == Brn("Root")) {
			device = &iDeviceXmlDocument->Root();
			property.Set(parser.Remaining());
		}
		
	    try {
		    if (property == Brn("FriendlyName")) {
		        device->FriendlyName(aValue);
		        return (true);
		    }
		    
		    Parser parser(property);
		    
		    Brn token = parser.Next('.');
		    
			if (token == Brn("Service")) {
				aValue.Set(device->ServiceVersion(parser.Remaining()));
				return (true);
			}
		}
		catch (XmlError) {
		}
    }

    return (false);
}

void CpiDeviceUpnp::Invoke(Invocation& aInvocation)
{
    try {
        Uri uri;
        GetControlUri(aInvocation, uri);
        InvocationUpnp invoker(aInvocation);
        invoker.Invoke(uri);
    }
    catch (XmlError&) {
        THROW(ReaderError);
    }
}

void CpiDeviceUpnp::GetControlUri(const Invocation& aInvocation, Uri& aUri)
{
    AutoMutex a(iLock);
    if (iControlUrl.Bytes() != 0) {
        aUri.Replace(iControlUrl);
    }
    else {
        GetServiceUri(aUri, "controlURL", aInvocation.ServiceType());
        iControlUrl.Set(aUri.AbsoluteUri());
    }
}

TUint CpiDeviceUpnp::Subscribe(Subscription& aSubscription, const Uri& aSubscriber)
{
    TUint durationSecs = 30 * 60; // 30 minutes
    Uri uri;
    GetServiceUri(uri, "eventSubURL", aSubscription.ServiceType());
    EventUpnp eventUpnp(aSubscription);
    eventUpnp.Subscribe(uri, aSubscriber, durationSecs);
    return durationSecs;
}

TUint CpiDeviceUpnp::Renew(Subscription& aSubscription)
{
    TUint durationSecs = 30 * 60; // 30 minutes
    Uri uri;
    GetServiceUri(uri, "eventSubURL", aSubscription.ServiceType());
    EventUpnp eventUpnp(aSubscription);
    eventUpnp.RenewSubscription(uri, durationSecs);
    return durationSecs;
}

void CpiDeviceUpnp::Unsubscribe(Subscription& aSubscription, const Brx& aSid)
{
    Uri uri;
    GetServiceUri(uri, "eventSubURL", aSubscription.ServiceType());
    EventUpnp eventUpnp(aSubscription);
    eventUpnp.Unsubscribe(uri, aSid);
}

void CpiDeviceUpnp::ProcessPropertyNotification(const Brx& aNotification, PropertyMap& aProperties)
{
    EventUpnp::ProcessNotification(aNotification, aProperties);
}

CpiDeviceUpnp::~CpiDeviceUpnp()
{
    delete iDeviceXmlDocument;
    delete iDeviceXml;
    delete iTimer;
}

void CpiDeviceUpnp::TimerExpired()
{
    SetExpired(true);
    iDeviceList.Remove(iUdn);
}

void CpiDeviceUpnp::GetServiceUri(Uri& aUri, const TChar* aType, const ServiceType& aServiceType)
{
    Brn root = XmlParserBasic::Find("root", iXml);
    Brn device = XmlParserBasic::Find("device", root);
    Brn udn = XmlParserBasic::Find("UDN", device);
    if (!CpiDeviceUpnp::UdnMatches(udn, iUdn)) {
        Brn deviceList = XmlParserBasic::Find("deviceList", device);
        do {
            Brn remaining;
            device.Set(XmlParserBasic::Find("device", deviceList, remaining));
            udn.Set(XmlParserBasic::Find("UDN", device));
            deviceList.Set(remaining);
        } while (!CpiDeviceUpnp::UdnMatches(udn, iUdn));
    }
    Brn serviceList = XmlParserBasic::Find("serviceList", device);
    Brn service;
    Brn serviceType;
    const Brx& targServiceType = aServiceType.FullName();
    do {
        Brn remaining;
        service.Set(XmlParserBasic::Find("service", serviceList, remaining));
        serviceType.Set(XmlParserBasic::Find("serviceType", service));
        serviceList.Set(remaining);
    } while (serviceType != targServiceType);
    Brn path = XmlParserBasic::Find(aType, service);

    // now create a uri using the scheme/host/port of the device xml location
    // plus the path we've just constructed
    Bws<40> base; // just need space for http://xxx.xxx.xxx.xxx:xxxxx
    aUri.Replace(iLocation);
    base.Append(aUri.Scheme());
    base.Append("://");
    base.Append(aUri.Host());
    base.Append(':');
    Ascii::AppendDec(base, aUri.Port());
    aUri.Replace(base, path);
}

TBool CpiDeviceUpnp::UdnMatches(const Brx& aFound, const Brx& aTarget)
{
    const Brn udnPrefix("uuid:");
    Brn udn(aFound);
    if (udn.Bytes() <= udnPrefix.Bytes()) {
        THROW(XmlError);
    }
    Brn prefix = udn.Split(0, udnPrefix.Bytes());
    if (prefix != udnPrefix) {
        THROW(XmlError);
    }
    udn.Set(udn.Split(udnPrefix.Bytes(), udn.Bytes() - udnPrefix.Bytes()));
    return (udn == aTarget);
}

void CpiDeviceUpnp::XmlFetchCompleted(IAsync& aAsync)
{
    TBool err = false;
    try {
        XmlFetch::Xml(aAsync).TransferTo(iXml);
    }
    catch (XmlFetchError&) {
        err = true;
        LOG2(kDevice, kError, "Error fetching xml for ");
        LOG2(kDevice, kError, iUdn);
        LOG2(kDevice, kError, " from ");
        LOG2(kDevice, kError, iLocation);
        LOG2(kDevice, kError, "\n");
    }
    try {
        iDeviceXmlDocument = new DeviceXmlDocument(iXml);
    	iDeviceXml = new DeviceXml(iDeviceXmlDocument->Find(iUdn));
    }
    catch (XmlError&) {
    	err = true;
        LOG2(kDevice, kError, "Error within xml for ");
        LOG2(kDevice, kError, iUdn);
        LOG2(kDevice, kError, " from ");
        LOG2(kDevice, kError, iLocation);
        LOG2(kDevice, kError, "\n");
    }
    iList->XmlFetchCompleted(*this, err);
    iList = NULL;
    RemoveRef();
}


// CpiDeviceListUpnp

CpiDeviceListUpnp::CpiDeviceListUpnp(FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : CpiDeviceList(aAdded, aRemoved)
    , iStarted(false)
    , iXmlFetchSem("DRLS", 0)
{
    NetworkInterfaceList& ifList = Stack::NetworkInterfaceList();
    NetworkInterface* current = ifList.CurrentInterface();
    iRefreshTimer = new Timer(MakeFunctor(*this, &CpiDeviceListUpnp::RefreshTimerComplete));
    iInterfaceChangeListenerId = ifList.AddCurrentChangeListener(MakeFunctor(*this, &CpiDeviceListUpnp::CurrentNetworkInterfaceChanged));
    iSubnetChangeListenerId = ifList.AddSubnetChangeListener(MakeFunctor(*this, &CpiDeviceListUpnp::SubnetChanged));
    if (current == NULL) {
        iInterface = 0;
        iUnicastListener = NULL;
        iMulticastListener = NULL;
        iNotifyHandlerId = 0;
    }
    else {
        iInterface = current->Address();
        iUnicastListener = new SsdpListenerUnicast(*this, iInterface);
        iMulticastListener = &Stack::MulticastListenerClaim(iInterface);
        iNotifyHandlerId = iMulticastListener->AddNotifyHandler(this);
        delete current;
    }
}

CpiDeviceListUpnp::~CpiDeviceListUpnp()
{
    TUint xmlWaitCount = 0;
    iLock.Wait();
    iActive = false;
    Stack::NetworkInterfaceList().RemoveCurrentChangeListener(iInterfaceChangeListenerId);
    Stack::NetworkInterfaceList().RemoveSubnetChangeListener(iSubnetChangeListenerId);
    if (iMulticastListener != NULL) {
        iMulticastListener->RemoveNotifyHandler(iNotifyHandlerId);
        Stack::MulticastListenerRelease(iInterface);
    }
    Map::iterator it = iMap.begin();
    while (it != iMap.end()) {
        CpiDeviceUpnp* device = (CpiDeviceUpnp*)it->second;
        if (!device->IsReady()) {
            device->InterruptXmlFetch();
            xmlWaitCount++;
        }
        it++;
    }
    iXmlFetchSem.Clear();
    iLock.Signal();
    while (xmlWaitCount > 0) {
        iXmlFetchSem.Wait();
        xmlWaitCount--;
    }
    delete iUnicastListener;
    delete iRefreshTimer;
}

TBool CpiDeviceListUpnp::Update(const Brx& aUdn, TUint aMaxAge)
{
    AutoMutex a(iLock);
    CpiDevice* device = RefDeviceLocked(aUdn);
    if (device != NULL) {
        static_cast<CpiDeviceUpnp*>(device)->UpdateMaxAge(aMaxAge);
        device->RemoveRef();
        return !iRefreshing;
    }
    return false;
}

void CpiDeviceListUpnp::Start()
{
    iActive = true;
    if (!iStarted) {
        iUnicastListener->Start();
        iStarted = true;
    }
    else {
        // clear list (without notification)
        ClearMap(iMap);
    }
}

void CpiDeviceListUpnp::Refresh()
{
    if (StartRefresh()) {
        return;
    }
    Start();
    TUint delayMs = Stack::InitParams().MsearchTimeSecs() * 1000;
    delayMs += 100; /* allow slightly longer to cope with devices which send
                       out Alive messages at the last possible moment */
    iRefreshTimer->FireIn(delayMs);
    /*  during refresh...
            on every Add():
                add to iRefreshMap
                check device against iMap, adding it and reporting as new if necessary
        on completion...
            on timer expiry:
                check each item in iMap
                    if it appears in iRefreshMap do nowt
                    else remove it from iMap and report this to observer */
}

TBool CpiDeviceListUpnp::IsDeviceReady(CpiDevice& aDevice)
{
    ((CpiDeviceUpnp&)aDevice).FetchXml(*this);
    return false;
}

TBool CpiDeviceListUpnp::IsLocationReachable(const Brx& aLocation) const
{
    /* linux's filtering of multicast messages appears to be buggy and messages
       received by all interfaces are sometimes delivered to sockets which are
       bound to / members of a group on a single (different) interface.  It'd be
       more correct to filter these out in SsdpListenerMulticast but that would
       require API changes which would be more inconvenient than just moving the
       filtering here.
       This should be reconsidered if we ever add more clients of SsdpListenerMulticast */
    TBool reachable = false;
    Uri uri(aLocation);
    iLock.Wait();
    Endpoint endpt(0, uri.Host());
    NetworkInterface* nif = Stack::NetworkInterfaceList().CurrentInterface();
    if (nif->Address() == iInterface && nif->ContainsAddress(endpt.Address())) {
        reachable = true;
    }
    delete nif;
    iLock.Signal();
    return reachable;
}

void CpiDeviceListUpnp::RefreshTimerComplete()
{
    RefreshComplete();
}

void CpiDeviceListUpnp::CurrentNetworkInterfaceChanged()
{
    HandleInterfaceChange(false);
}

void CpiDeviceListUpnp::SubnetChanged()
{
    HandleInterfaceChange(true);
}

void CpiDeviceListUpnp::HandleInterfaceChange(TBool aNewSubnet)
{
    NetworkInterface* current = Stack::NetworkInterfaceList().CurrentInterface();
    iLock.Wait();
    delete iUnicastListener;
    iUnicastListener = NULL;
    if (iMulticastListener != NULL) {
        iMulticastListener->RemoveNotifyHandler(iNotifyHandlerId);
        iNotifyHandlerId = 0;
        Stack::MulticastListenerRelease(iInterface);
        iMulticastListener = NULL;
    }

    if (current == NULL) {
        iInterface = NULL;
        RemoveAll();
        iLock.Signal();
        return;
    }

    iInterface = current->Address();
    delete current;
    if (aNewSubnet) {
        RemoveAll();
    }
    iUnicastListener = new SsdpListenerUnicast(*this, iInterface);
    iUnicastListener->Start();
    iMulticastListener = &Stack::MulticastListenerClaim(iInterface);
    iNotifyHandlerId = iMulticastListener->AddNotifyHandler(this);
    iLock.Signal();
    Refresh();
}

void CpiDeviceListUpnp::RemoveAll()
{
    iRefreshTimer->Cancel();
    while (iMap.size() > 0) {
        Brn udn = iMap.begin()->first;
        iLock.Signal();
        Remove(udn);
        iLock.Wait();
    }
}

void CpiDeviceListUpnp::XmlFetchCompleted(CpiDevice& aDevice, TBool aError)
{
    if (aError) {
        Remove(aDevice.Udn());
    }
    else {
        SetDeviceReady(aDevice);
    }
    iXmlFetchSem.Signal();
}

void CpiDeviceListUpnp::SsdpNotifyRootAlive(const Brx& /*aUuid*/, const Brx& /*aLocation*/, TUint /*aMaxAge*/)
{
}

void CpiDeviceListUpnp::SsdpNotifyUuidAlive(const Brx& /*aUuid*/, const Brx& /*aLocation*/, TUint /*aMaxAge*/)
{
}

void CpiDeviceListUpnp::SsdpNotifyDeviceTypeAlive(const Brx& /*aUuid*/, const Brx& /*aDomain*/, const Brx& /*aType*/,
                                                 TUint /*aVersion*/, const Brx& /*aLocation*/, TUint /*aMaxAge*/)
{
}

void CpiDeviceListUpnp::SsdpNotifyServiceTypeAlive(const Brx& /*aUuid*/, const Brx& /*aDomain*/, const Brx& /*aType*/,
                                                  TUint /*aVersion*/, const Brx& /*aLocation*/, TUint /*aMaxAge*/)
{
}

void CpiDeviceListUpnp::SsdpNotifyRootByeBye(const Brx& aUuid)
{
    Remove(aUuid);
}

void CpiDeviceListUpnp::SsdpNotifyUuidByeBye(const Brx& aUuid)
{
    Remove(aUuid);
}

void CpiDeviceListUpnp::SsdpNotifyDeviceTypeByeBye(const Brx& aUuid, const Brx& /*aDomain*/, const Brx& /*aType*/, TUint /*aVersion*/)
{
    Remove(aUuid);
}

void CpiDeviceListUpnp::SsdpNotifyServiceTypeByeBye(const Brx& aUuid, const Brx& /*aDomain*/, const Brx& /*aType*/, TUint /*aVersion*/)
{
    Remove(aUuid);
}


// CpiDeviceListUpnpAll

CpiDeviceListUpnpAll::CpiDeviceListUpnpAll(FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : CpiDeviceListUpnp(aAdded, aRemoved)
{
}

void CpiDeviceListUpnpAll::Start()
{
    iLock.Wait();
    if (!iRefreshing) {
        CpiDeviceListUpnp::Start();
    }
    iUnicastListener->MsearchAll();
    iLock.Signal();
}

void CpiDeviceListUpnpAll::SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    if (Update(aUuid, aMaxAge)) {
        return;
    }
    if (IsLocationReachable(aLocation)) {
        CpiDevice* device = new CpiDeviceUpnp(aUuid, aLocation, aMaxAge, *this);
        Add(device);
    }
}


// CpiDeviceListUpnpRoot

CpiDeviceListUpnpRoot::CpiDeviceListUpnpRoot(FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : CpiDeviceListUpnp(aAdded, aRemoved)
{
}

void CpiDeviceListUpnpRoot::Start()
{
    iLock.Wait();
    if (!iRefreshing) {
        CpiDeviceListUpnp::Start();
    }
    iUnicastListener->MsearchRoot();
    iLock.Signal();
}

void CpiDeviceListUpnpRoot::SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    if (Update(aUuid, aMaxAge)) {
        return;
    }
    if (IsLocationReachable(aLocation)) {
        CpiDevice* device = new CpiDeviceUpnp(aUuid, aLocation, aMaxAge, *this);
        Add(device);
    }
}


// CpiDeviceListUpnpUuid

CpiDeviceListUpnpUuid::CpiDeviceListUpnpUuid(const Brx& aUuid, FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : CpiDeviceListUpnp(aAdded, aRemoved)
    , iUuid(aUuid)
{
}

void CpiDeviceListUpnpUuid::Start()
{
    iLock.Wait();
    if (!iRefreshing) {
        CpiDeviceListUpnp::Start();
    }
    iUnicastListener->MsearchUuid(iUuid);
    iLock.Signal();
}

void CpiDeviceListUpnpUuid::SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    if (aUuid != iUuid) {
        return;
    }
    if (Update(aUuid, aMaxAge)) {
        return;
    }
    if (IsLocationReachable(aLocation)) {
        CpiDevice* device = new CpiDeviceUpnp(aUuid, aLocation, aMaxAge, *this);
        Add(device);
    }
}


// CpiDeviceListUpnpDeviceType

CpiDeviceListUpnpDeviceType::CpiDeviceListUpnpDeviceType(const Brx& aDomainName, const Brx& aDeviceType, TUint aVersion,
                                                         FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : CpiDeviceListUpnp(aAdded, aRemoved)
    , iDomainName(aDomainName)
    , iDeviceType(aDeviceType)
    , iVersion(aVersion)
{
}

void CpiDeviceListUpnpDeviceType::Start()
{
    iLock.Wait();
    if (!iRefreshing) {
        CpiDeviceListUpnp::Start();
    }
    iUnicastListener->MsearchDeviceType(iDomainName, iDeviceType, iVersion);
    iLock.Signal();
}

void CpiDeviceListUpnpDeviceType::SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType,
                                                            TUint aVersion, const Brx& aLocation, TUint aMaxAge)
{
    if (aVersion<iVersion || aDomain!=iDomainName || aType!=iDeviceType) {
        return;
    }
    if (Update(aUuid, aMaxAge)) {
        return;
    }
    if (IsLocationReachable(aLocation)) {
        CpiDevice* device = new CpiDeviceUpnp(aUuid, aLocation, aMaxAge, *this);
        Add(device);
    }
}


// CpiDeviceListUpnpServiceType

CpiDeviceListUpnpServiceType::CpiDeviceListUpnpServiceType(const Brx& aDomainName, const Brx& aServiceType, TUint aVersion,
                                                           FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : CpiDeviceListUpnp(aAdded, aRemoved)
    , iDomainName(aDomainName)
    , iServiceType(aServiceType)
    , iVersion(aVersion)
{
}

void CpiDeviceListUpnpServiceType::Start()
{
    iLock.Wait();
    if (!iRefreshing) {
        CpiDeviceListUpnp::Start();
    }
    iUnicastListener->MsearchServiceType(iDomainName, iServiceType, iVersion);
    iLock.Signal();
}

void CpiDeviceListUpnpServiceType::SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType,
                                                              TUint aVersion, const Brx& aLocation, TUint aMaxAge)
{
    if (aVersion<iVersion || aDomain!=iDomainName || aType!=iServiceType) {
        return;
    }
    if (Update(aUuid, aMaxAge)) {
        return;
    }
    if (IsLocationReachable(aLocation)) {
        CpiDevice* device = new CpiDeviceUpnp(aUuid, aLocation, aMaxAge, *this);
        Add(device);
    }
}
