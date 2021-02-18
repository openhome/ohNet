#include <OpenHome/Net/Private/CpiDeviceUpnp.h>
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Optional.h>
#include <OpenHome/Net/Private/XmlFetcher.h>
#include <OpenHome/Net/Private/ProtocolUpnp.h>
#include <OpenHome/Net/Private/XmlParser.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Private/DeviceXml.h>
#include <OpenHome/Net/Private/CpiSubscription.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Private/TIpAddressUtils.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Net;


// CpiDeviceUpnp

CpiDeviceUpnp::CpiDeviceUpnp(CpStack& aCpStack, const Brx& aUdn, const Brx& aLocation, TUint aMaxAgeSecs, IDeviceRemover& aDeviceList, CpiDeviceListUpnp& aList)
    : iCpStack(aCpStack)
    , iLock("CDUP")
    , iLocation(aLocation)
    , iXmlFetch(NULL)
    , iDeviceXmlDocument(NULL)
    , iDeviceXml(NULL)
    , iExpiryTime(0)
    , iMaxAgeSeconds(aMaxAgeSecs)
    , iDeviceList(aDeviceList)
    , iList(&aList)
    , iSemReady("CDUS", 0)
    , iRemoved(false)
    , iNewLocation(NULL)
    , iXmlCheckLocation(NULL)
    , iXmlCheckRefresh(NULL)
{
    Environment& env = aCpStack.Env();
    iHostUdpIsLowQuality = env.InitParams()->IsHostUdpLowQuality();
    iDevice = new CpiDevice(aCpStack, aUdn, *this, *this, this);
    iTimer = new Timer(env, MakeFunctor(*this, &CpiDeviceUpnp::TimerExpired), "CpiDeviceUpnp");
    UpdateMaxAge(aMaxAgeSecs);
    iInvocable = new Invocable(*this);
}

CpiDeviceUpnp::CpiDeviceUpnp(CpStack& aCpStack, const Brx& aLocation, IDeviceRemover& aDeviceList, CpiDeviceListUpnp& aList)
    : iCpStack(aCpStack)
    , iLock("CDUP")
    , iLocation(aLocation)
    , iXmlFetch(NULL)
    , iDeviceXmlDocument(NULL)
    , iDeviceXml(NULL)
    , iExpiryTime(0)
    , iMaxAgeSeconds(0)
    , iDeviceList(aDeviceList)
    , iList(&aList)
    , iSemReady("CDUS", 0)
    , iRemoved(false)
    , iNewLocation(NULL)
    , iXmlCheckLocation(NULL)
    , iXmlCheckRefresh(NULL)
{
    iHostUdpIsLowQuality = true; // device was "discovered" based on old IP address so we have no reason to be confident that UDP is reliable
    iDevice = NULL; // we need to read device XML to find the udn first
    iTimer = NULL; // don't assume we'll receive later ALIVEs
    iInvocable = new Invocable(*this);

    AutoMutex _(iLock);
    XmlFetchManager& xmlFetchManager = aCpStack.XmlFetchManager();
    iXmlFetch = xmlFetchManager.Fetch();
    FunctorAsync functor = MakeFunctorAsync(*this, &CpiDeviceUpnp::XmlFetchReadUdnCompleted);
    iXmlFetch->Set(aLocation, functor);
    xmlFetchManager.Fetch(iXmlFetch);
}

const Brx& CpiDeviceUpnp::Udn() const
{
    return iDevice->Udn();
}

const Brx& CpiDeviceUpnp::Location() const
{
    return iLocation;
}

TUint CpiDeviceUpnp::MaxAgeSeconds() const
{
    return iMaxAgeSeconds;
}

CpiDevice& CpiDeviceUpnp::Device()
{
    return *iDevice;
}

TBool CpiDeviceUpnp::Ready() const
{
    AutoMutex _(iLock);
    return iDeviceXml != NULL;
}

void CpiDeviceUpnp::UpdateMaxAge(TUint aSeconds)
{
    iMaxAgeSeconds = aSeconds;
    if (iTimer == NULL) {
        return;
    }
    TUint delayMs = aSeconds * 1000;
    delayMs += 100; /* allow slightly longer than maxAge to cope with devices which
                       send out Alive messages at the last possible moment */
    OsContext* osCtx = iDevice->GetCpStack().Env().OsCtx();
    TUint expiryTime = Os::TimeInMs(osCtx) + delayMs;
    if (expiryTime >= iExpiryTime) {
        iExpiryTime = expiryTime;
        iTimer->FireAt(iExpiryTime);
    }
}

void CpiDeviceUpnp::FetchXml()
{
    AutoMutex a(iLock);
    if (iXml.Bytes() > 0) {
        // device was constructed based on a previous location. We've already fetched the XML (to get a udn)
        iSemReady.Signal();
        if (iList != NULL) {
            iList->XmlFetchCompleted(*this, true);
        }
        return;
    }
    XmlFetchManager& xmlFetchManager = iDevice->GetCpStack().XmlFetchManager();
    iXmlFetch = xmlFetchManager.Fetch();
    iDevice->AddRef();
    FunctorAsync functor = MakeFunctorAsync(*this, &CpiDeviceUpnp::XmlFetchCompleted);
    iXmlFetch->Set(iLocation, functor);
    xmlFetchManager.Fetch(iXmlFetch);
}

void CpiDeviceUpnp::InterruptXmlFetch()
{
    AutoMutex a(iLock);
    if (iXmlFetch != NULL) {
        iXmlFetch->Interrupt();
        iXmlFetch = NULL;
    }
    if (iXmlCheckLocation != NULL) {
        iXmlCheckLocation->Interrupt();
        iXmlCheckLocation = NULL;
    }
    if (iXmlCheckRefresh != NULL) {
        iXmlCheckRefresh->Interrupt();
        iXmlCheckRefresh = NULL;
    }
    iList = NULL;
}

void CpiDeviceUpnp::CheckStillAvailable(CpiDeviceUpnp* aNewLocation)
{
    iLock.Wait();
    if (iNewLocation != NULL) {
        if (iNewLocation->Location() == aNewLocation->Location()) {
            iLock.Signal();
            aNewLocation->iDevice->RemoveRef();
            return;
        }
        CpiDevice* d = iNewLocation->iDevice;
        iNewLocation = aNewLocation;
        iLock.Signal();
        d->RemoveRef();
        return;
    }
    iNewLocation = aNewLocation;
    XmlFetchManager& xmlFetchManager = iDevice->GetCpStack().XmlFetchManager();
    ASSERT(iXmlCheckLocation == NULL);
    iXmlCheckLocation = xmlFetchManager.Fetch();
    iDevice->AddRef();
    FunctorAsync functor = MakeFunctorAsync(*this, &CpiDeviceUpnp::XmlCheckLocationCompleted);
    iXmlCheckLocation->CheckContactable(iLocation, functor);
    xmlFetchManager.Fetch(iXmlCheckLocation);
    iLock.Signal();
}

void CpiDeviceUpnp::CheckStillAvailable()
{
    AutoMutex _(iLock);
    XmlFetchManager& xmlFetchManager = iDevice->GetCpStack().XmlFetchManager();
    iXmlCheckRefresh = xmlFetchManager.Fetch();
    iDevice->AddRef();
    FunctorAsync functor = MakeFunctorAsync(*this, &CpiDeviceUpnp::XmlCheckRefreshCompleted);
    iXmlCheckRefresh->CheckContactable(iLocation, functor);
    xmlFetchManager.Fetch(iXmlCheckRefresh);
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
                device->GetFriendlyName(aValue);
                return (true);
            }
            if (property == Brn("PresentationUrl")) {
                device->GetPresentationUrl(aValue);
                return (true);
            }
            
            Parser parser2(property);
            
            Brn token = parser2.Next('.');
            
            if (token == Brn("Service")) {
                aValue.Set(device->ServiceVersion(parser2.Remaining()));
                return (true);
            }
        }
        catch (XmlError&) {
        }
    }

    return (false);
}

void CpiDeviceUpnp::InvokeAction(Invocation& aInvocation)
{
    aInvocation.SetInvoker(*iInvocable);
    iDevice->GetCpStack().InvocationManager().Invoke(&aInvocation);
}

TUint CpiDeviceUpnp::Subscribe(CpiSubscription& aSubscription, const Uri& aSubscriber)
{
    TUint durationSecs = iDevice->GetCpStack().Env().InitParams()->SubscriptionDurationSecs();
    Uri uri;
    GetServiceUri(uri, "eventSubURL", aSubscription.ServiceType());
    EventUpnp eventUpnp(iDevice->GetCpStack(), aSubscription);
    eventUpnp.Subscribe(uri, aSubscriber, durationSecs);
    return durationSecs;
}

TUint CpiDeviceUpnp::Renew(CpiSubscription& aSubscription)
{
    TUint durationSecs = iDevice->GetCpStack().Env().InitParams()->SubscriptionDurationSecs();
    Uri uri;
    GetServiceUri(uri, "eventSubURL", aSubscription.ServiceType());
    EventUpnp eventUpnp(iDevice->GetCpStack(), aSubscription);
    eventUpnp.RenewSubscription(uri, durationSecs);
    return durationSecs;
}

void CpiDeviceUpnp::Unsubscribe(CpiSubscription& aSubscription, const Brx& aSid)
{
    Uri uri;
    GetServiceUri(uri, "eventSubURL", aSubscription.ServiceType());
    EventUpnp eventUpnp(iDevice->GetCpStack(), aSubscription);
    eventUpnp.Unsubscribe(uri, aSid);
}

TBool CpiDeviceUpnp::OrphanSubscriptionsOnSubnetChange() const
{
    return true;
}

void CpiDeviceUpnp::NotifyRemovedBeforeReady()
{
    iLock.Wait();
    iRemoved = true;
    iLock.Signal();
    InterruptXmlFetch();
    iSemReady.Wait();
}

TUint CpiDeviceUpnp::Version(const TChar* aDomain, const TChar* aName, TUint /*aProxyVersion*/) const
{
    ServiceType defaultServiceType(aDomain, aName, 0);
    const Brx& targServiceType = defaultServiceType.FullName();
    // Must have backwards compatibility. Need to compare service type and version separately.
    Parser serviceParser = targServiceType;
    serviceParser.Next(':');    // urn
    serviceParser.Next(':');    // schema url
    serviceParser.Next(':');    // service
    serviceParser.Next(':');    // name
    Brn targServiceTypeNoVer(targServiceType.Ptr(), serviceParser.Index()); // full name minus ":x" (where x is version)

    try {
        Brn root = XmlParserBasic::Find("root", iXml);
        Brn device = XmlParserBasic::Find("device", root);
        Brn udn = XmlParserBasic::Find("UDN", device);
        if (!CpiDeviceUpnp::UdnMatches(udn, Udn())) {
            Brn deviceList = XmlParserBasic::Find("deviceList", device);
            do {
                Brn remaining;
                device.Set(XmlParserBasic::Find("device", deviceList, remaining));
                udn.Set(XmlParserBasic::Find("UDN", device));
                deviceList.Set(remaining);
            } while (!CpiDeviceUpnp::UdnMatches(udn, Udn()));
        }
        Brn serviceList = XmlParserBasic::Find("serviceList", device);
        Brn service;
        Brn serviceType;
        Brn devServiceTypeNoVer;
        for (;;) {
            Brn remaining;
            service.Set(XmlParserBasic::Find("service", serviceList, remaining));
            serviceType.Set(XmlParserBasic::Find("serviceType", service));
            serviceList.Set(remaining);
            // Parse service type and version separately.
            serviceParser.Set(serviceType);
            serviceParser.Next(':');    // urn
            serviceParser.Next(':');    // schema url
            serviceParser.Next(':');    // service
            serviceParser.Next(':');    // name
            devServiceTypeNoVer.Set(serviceType.Ptr(), serviceParser.Index()); // full name minus ":x" (where x is version)
            if (devServiceTypeNoVer == targServiceTypeNoVer) {
                Brn devVersionBuf = serviceParser.NextToEnd();    // version
                try {
                    return Ascii::Uint(devVersionBuf);
                }
                catch (AsciiError&) {
                    THROW(XmlError);
                }
            }
        }
    }
    catch (XmlError&) {
        return 0;
    }
}

void CpiDeviceUpnp::Release()
{
    delete this; // iDevice not deleted here; it'll delete itself when this returns
}

CpiDeviceUpnp::~CpiDeviceUpnp()
{
    delete iDeviceXmlDocument;
    delete iDeviceXml;
    delete iTimer;
    delete iInvocable;
}

void CpiDeviceUpnp::TimerExpired()
{
    if (iHostUdpIsLowQuality) {
        const Brx& udn = Udn();
        LOG(kDevice, "TimerExpired ignored for device %.*s\n", PBUF(udn));
    }
    else {
        iDevice->SetExpired(true);
        iDeviceList.Remove(Udn());
    }
}

void CpiDeviceUpnp::GetServiceUri(Uri& aUri, const TChar* aType, const ServiceType& aServiceType)
{
    Brn root = XmlParserBasic::Find("root", iXml);
    Brn device = XmlParserBasic::Find("device", root);
    Brn udn = XmlParserBasic::Find("UDN", device);
    if (!CpiDeviceUpnp::UdnMatches(udn, Udn())) {
        Brn deviceList = XmlParserBasic::Find("deviceList", device);
        do {
            Brn remaining;
            device.Set(XmlParserBasic::Find("device", deviceList, remaining));
            udn.Set(XmlParserBasic::Find("UDN", device));
            deviceList.Set(remaining);
        } while (!CpiDeviceUpnp::UdnMatches(udn, Udn()));
    }
    Brn serviceList = XmlParserBasic::Find("serviceList", device);
    Brn service;
    Brn serviceType;
    Brn devServiceTypeNoVer;
    const Brx& targServiceType = aServiceType.FullName();
    // Must have backwards compatibility. Need to compare service type and version separately.
    Parser serviceParser = targServiceType;
    serviceParser.Next(':');    // urn
    serviceParser.Next(':');    // schema url
    serviceParser.Next(':');    // service
    serviceParser.Next(':');    // name
    Brn targServiceTypeNoVer(targServiceType.Ptr(), serviceParser.Index()); // full name minus ":x" (where x is version)
    do {
        Brn remaining;
        service.Set(XmlParserBasic::Find("service", serviceList, remaining));
        serviceType.Set(XmlParserBasic::Find("serviceType", service));
        serviceList.Set(remaining);
        // Parse service type and version separately.
        serviceParser.Set(serviceType);
        serviceParser.Next(':');    // urn
        serviceParser.Next(':');    // schema url
        serviceParser.Next(':');    // service
        serviceParser.Next(':');    // name
        devServiceTypeNoVer.Set(serviceType.Ptr(), serviceParser.Index()); // full name minus ":x" (where x is version)
        // MUST allow use of device with version >= target version
    } while (devServiceTypeNoVer != targServiceTypeNoVer);
    Brn path = XmlParserBasic::Find(aType, service);
    if (path.Bytes() == 0) {
        // no event url => service doesn't have any evented state variables
        THROW(XmlError);
    }

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

void CpiDeviceUpnp::XmlFetchReadUdnCompleted(IAsync& aAsync)
{
    iLock.Wait();
    iXmlFetch = NULL;
    iLock.Signal();
    TBool err = iRemoved;
    try {
        XmlFetch::Xml(aAsync).TransferTo(iXml);
        iDeviceXmlDocument = new DeviceXmlDocument(iXml);
        iDeviceXml = new DeviceXml(iDeviceXmlDocument->Root());
    }
    catch (XmlFetchError&) {
        err = true;
        LOG_ERROR(kDevice, "Error fetching xml for %.*s\n", PBUF(iLocation));
    }
    catch (XmlError&) {
        err = true;
        LOG_ERROR(kDevice, "Error within xml for %.*s.  Xml is %.*s\n", PBUF(iLocation), PBUF(iXml));
    }
    if (err) {
        delete this; // safe because no associated CpiDevice and not yet part of a device list
        return;
    }
    iDevice = new CpiDevice(iCpStack, iDeviceXml->Udn(), *this, *this, this);
    iDevice->AddRef();
    iLock.Wait();
    CpiDeviceList* list = iList;
    iLock.Signal();
    if (list != NULL) {
        list->Add(iDevice);
    }
    iDevice->RemoveRef();
    // Don't add code after the RemoveRef(), we might have
    // just deleted this object!
}

void CpiDeviceUpnp::XmlFetchCompleted(IAsync& aAsync)
{
    iLock.Wait();
    iXmlFetch = NULL;
    iLock.Signal();
    TBool err = iRemoved;
    if (!err) {
        try {
            XmlFetch::Xml(aAsync).TransferTo(iXml);
        }
        catch (XmlFetchError&) {
            err = true;
            const Brx& udn = Udn();
            LOG_ERROR(kDevice, "Error fetching xml for %.*s from %.*s\n", PBUF(udn), PBUF(iLocation));
        }
    }
    if (!err) {
        try {
            iDeviceXmlDocument = new DeviceXmlDocument(iXml);
            iDeviceXml = new DeviceXml(iDeviceXmlDocument->Find(Udn()));
        }
        catch (XmlError&) {
            err = true;
            const Brx& udn = Udn();
            LOG_ERROR(kDevice, "Error within xml for %.*s from %.*s.  Xml is %.*s\n",
                                  PBUF(udn), PBUF(iLocation), PBUF(iXml));
        }
    }
    iLock.Wait();
    if (iList != NULL) {
        iList->XmlFetchCompleted(*this, err);
    }
    iLock.Signal();
    iSemReady.Signal();
    iDevice->RemoveRef();
    // Don't add code after the RemoveRef(), we might have
    // just deleted this object!
}

void CpiDeviceUpnp::XmlCheckLocationCompleted(IAsync& aAsync)
{
    iLock.Wait();
    iXmlCheckLocation = NULL;
    CpiDeviceUpnp* newLocation = iNewLocation;
    iNewLocation = NULL;
    iLock.Signal();
    if (!iRemoved) {
        TBool contactable = false;
        try {
            contactable = XmlFetch::WasContactable(aAsync);
        }
        catch (XmlFetchError&) {}
        if (!contactable) {
            iLock.Wait();
            if (iList != NULL) {
                iList->DeviceLocationChanged(this, newLocation);
                newLocation = NULL;
            }
            iLock.Signal();
        }
    }
    if (newLocation != NULL) {
        newLocation->Device().RemoveRef();
    }
    iDevice->RemoveRef();
}

void CpiDeviceUpnp::XmlCheckRefreshCompleted(IAsync& aAsync)
{
    iLock.Wait();
    iXmlCheckRefresh = NULL;
    iLock.Signal();
    if (!iRemoved) {
        TBool contactable = false;
        try {
            contactable = XmlFetch::WasContactable(aAsync);
        }
        catch (XmlFetchError&) {
            Log::Print("!!! XmlFetchError\n");
        }
        if (!contactable) {
            Log::Print("XmlCheckRefreshCompleted - FAIL - %.*s\n", PBUF(Udn()));
            iDeviceList.Remove(Udn());
        }
    }
    iDevice->RemoveRef();
}


// class CpiDeviceUpnp::Invocable

CpiDeviceUpnp::Invocable::Invocable(CpiDeviceUpnp& aDevice)
    : iDevice(aDevice)
{
}

void CpiDeviceUpnp::Invocable::InvokeAction(Invocation& aInvocation)
{
    try {
        Uri uri;
        iDevice.GetServiceUri(uri, "controlURL", aInvocation.ServiceType());
        InvocationUpnp invoker(iDevice.Device().GetCpStack(), aInvocation);
        invoker.Invoke(uri);
    }
    catch (XmlError&) {
        THROW(ReaderError);
    }
}


// CpiDeviceListUpnp

CpiDeviceListUpnp::CpiDeviceListUpnp(CpStack& aCpStack, FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : CpiDeviceList(aCpStack, aAdded, aRemoved)
    , iSsdpLock("DLSM")
    , iEnv(aCpStack.Env())
    , iStarted(false)
    , iNoRemovalsFromRefresh(false)
    , iRepeatMsearchMs(30 * 1000)
{
    NetworkAdapterList& ifList = aCpStack.Env().NetworkAdapterList();
    AutoNetworkAdapterRef ref(iEnv, "CpiDeviceListUpnp ctor");
    const NetworkAdapter* current = ref.Adapter();
    iRefreshTimer = new Timer(iEnv, MakeFunctor(*this, &CpiDeviceListUpnp::RefreshTimerComplete), "DeviceListRefresh");
    iResumedTimer = new Timer(iEnv, MakeFunctor(*this, &CpiDeviceListUpnp::ResumedTimerComplete), "DeviceListResume");
    iRepeatMsearchTimer = new Timer(iEnv, MakeFunctor(*this, &CpiDeviceListUpnp::RepeatMsearchTimerComplete), "DeviceListRepeat");
    iRefreshRepeatCount = 0;
    iInterfaceChangeListenerId = ifList.AddCurrentChangeListener(MakeFunctor(*this, &CpiDeviceListUpnp::CurrentNetworkAdapterChanged), "CpiDeviceListUpnp-current");
    iSubnetListChangeListenerId = ifList.AddSubnetListChangeListener(MakeFunctor(*this, &CpiDeviceListUpnp::SubnetListChanged), "CpiDeviceListUpnp-subnet");
    iSsdpLock.Wait();
    if (current == NULL) {
        iInterface = kTIpAddressEmpty;
        iUnicastListener = NULL;
        iMulticastListener = NULL;
        iNotifyHandlerId = 0;
    }
    else {
        iInterface = current->Address();
        iUnicastListener = new SsdpListenerUnicast(iCpStack.Env(), *this, iInterface);
        iMulticastListener = &(iCpStack.Env().MulticastListenerClaim(iInterface));
        iNotifyHandlerId = iMulticastListener->AddNotifyHandler(this);
    }
    iSsdpLock.Signal();
    iCpStack.Env().AddResumeObserver(*this);
}

CpiDeviceListUpnp::~CpiDeviceListUpnp()
{
    iCpStack.Env().RemoveResumeObserver(*this);
    iRepeatMsearchTimer->Cancel();
    iResumedTimer->Cancel();
    iLock.Wait();
    iActive = false;
    iLock.Signal();
    iCpStack.Env().NetworkAdapterList().RemoveCurrentChangeListener(iInterfaceChangeListenerId);
    iCpStack.Env().NetworkAdapterList().RemoveSubnetListChangeListener(iSubnetListChangeListenerId);
    iLock.Wait();
    CpDeviceMap::iterator it = iMap.begin();
    while (it != iMap.end()) {
        reinterpret_cast<CpiDeviceUpnp*>(it->second->OwnerData())->InterruptXmlFetch();
        it++;
    }
    for (TUint i=0; i<(TUint)iPendingRemove.size(); i++) {
        reinterpret_cast<CpiDeviceUpnp*>(iPendingRemove[i]->OwnerData())->InterruptXmlFetch();
    }
    iLock.Signal();
    delete iRepeatMsearchTimer;
    delete iRefreshTimer;
    delete iResumedTimer;
}

void CpiDeviceListUpnp::StopListeners()
{
    iSsdpLock.Wait();
    SsdpListenerUnicast* uListener = iUnicastListener;
    iUnicastListener = NULL;
    iSsdpLock.Signal();
    if (uListener != NULL) {
        delete uListener;
        if (iMulticastListener != NULL) {
            iMulticastListener->RemoveNotifyHandler(iNotifyHandlerId);
            iNotifyHandlerId = 0;
            iCpStack.Env().MulticastListenerRelease(iInterface);
            iMulticastListener = NULL;
        }
    }
}


void CpiDeviceListUpnp::Add(CpiDeviceUpnp* aDevice)
{
    CpiDeviceList::Add(&aDevice->Device());

    const TUint maxAgeMs = aDevice->MaxAgeSeconds() * 1000;
    const TUint repeatMsearchMs = (3 * maxAgeMs) / 4;
    if (repeatMsearchMs > iRepeatMsearchMs) {
        iRepeatMsearchMs = repeatMsearchMs;
        iRepeatMsearchTimer->FireIn(iRepeatMsearchMs); /* Don't worry that the timer might have been due
                                                          in less time - this would only be relevant when
                                                          we can receive unsolicited announcements and we
                                                          don't need to keep repeating MSEARCHes on these
                                                          networks. */
    }
}

void CpiDeviceListUpnp::TryAdd(const Brx& aLocation)
{
    (void)new CpiDeviceUpnp(iCpStack, aLocation, *this, *this);
    // CpiDeviceUpnp will try fetching its own XML and add itself to device list later
    // FIXME - may leak if we shutdown while xml fetch is in progress
}

TBool CpiDeviceListUpnp::Update(const Brx& aUdn, const Brx& aLocation, TUint aMaxAge)
{
    if (!IsLocationReachable(aLocation)) {
        return false;
    }
    iLock.Wait();
    CpiDevice* device = RefDeviceLocked(aUdn);
    if (device != NULL) {
        CpiDeviceUpnp* deviceUpnp = reinterpret_cast<CpiDeviceUpnp*>(device->OwnerData());
        if (deviceUpnp->Location() != aLocation) {
            /* Device appears to have moved to a new location.
               Ask it to check whether the old location is still contactable.  If it is,
               stick with the older location; if it isn't, remove the old device and add
               a new one. */
            iLock.Signal();
            CpiDeviceUpnp* newDevice = new CpiDeviceUpnp(iCpStack, aUdn, aLocation, aMaxAge, *this, *this);
            deviceUpnp->CheckStillAvailable(newDevice);
            device->RemoveRef();
            return true;
        }
        deviceUpnp->UpdateMaxAge(aMaxAge);
        iLock.Signal();
        device->RemoveRef();
        return !iRefreshing;
    }
    iLock.Signal();
    return false;
}

void CpiDeviceListUpnp::DoStart()
{
    iActive = true;
    iLock.Wait();
    TBool needsStart = !iStarted;
    iStarted = true;
    iLock.Signal();
    if (needsStart) {
        AutoMutex a(iSsdpLock);
        if (iUnicastListener != NULL) {
            iUnicastListener->Start();
        }
    }
}

void CpiDeviceListUpnp::Start()
{
    Refresh();
}

void CpiDeviceListUpnp::Refresh()
{
    if (StartRefresh()) {
        return;
    }
    /* Always attempt multiple refreshes.
        Poor quality wifi (particularly on iOS) means that we risk MSEARCHes not being sent otherwise. */
    iRefreshRepeatCount = kRefreshRetries;
    DoRefresh();
}

void CpiDeviceListUpnp::DoRefresh()
{
    Start();
    CpDeviceMap::iterator it = iMap.begin();
    for (; it != iMap.end(); ++it) {
        reinterpret_cast<CpiDeviceUpnp*>(it->second->OwnerData())->CheckStillAvailable();
    }
    TUint delayMs = iCpStack.Env().InitParams()->MsearchTimeSecs() * 1000;
    delayMs += 500; /* allow slightly longer to cope with wifi delays and devices
                       which send out Alive messages at the last possible moment */
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
    CpiDeviceUpnp* deviceUpnp = reinterpret_cast<CpiDeviceUpnp*>(aDevice.OwnerData());
    if (deviceUpnp->Ready()) {
        // device was 'discovered' at last known location => we've already fetched xml
        return true;
    }
    deviceUpnp->FetchXml();
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
    Uri uri;
    try {
        uri.Replace(aLocation);
    }
    catch (UriError&) {
        return false;
    }
    try {
        AutoMutex _(iLock);
        Endpoint endpt(0, uri.Host());
        Optional<NetworkAdapter> onif = iCpStack.Env().NetworkAdapterList().CurrentAdapter("CpiDeviceListUpnp::IsLocationReachable");
        if (onif.Ok()) {
            NetworkAdapter& nif = onif.Unwrap();
            if (TIpAddressUtils::Equal(nif.Address(), iInterface) && nif.ContainsAddress(endpt.Address())) {
                reachable = true;
            }
            nif.RemoveRef("CpiDeviceListUpnp::IsLocationReachable");
        }
    }
    catch (NetworkError&) {}
    return reachable;
}

void CpiDeviceListUpnp::RefreshTimerComplete()
{
    if (--iRefreshRepeatCount == 0) {
        RefreshComplete(!iNoRemovalsFromRefresh);
        iNoRemovalsFromRefresh = false;
    }
    else {
        DoRefresh();
    }
}

void CpiDeviceListUpnp::ResumedTimerComplete()
{
    iNoRemovalsFromRefresh = iEnv.InitParams()->IsHostUdpLowQuality();
    Refresh();
}

void CpiDeviceListUpnp::RepeatMsearchTimerComplete()
{
    Start();
    iRepeatMsearchTimer->FireIn(iRepeatMsearchMs);
}

void CpiDeviceListUpnp::CurrentNetworkAdapterChanged()
{
    HandleInterfaceChange();
}

void CpiDeviceListUpnp::SubnetListChanged()
{
    HandleInterfaceChange();
}

void CpiDeviceListUpnp::HandleInterfaceChange()
{
    NetworkAdapter* current = iCpStack.Env().NetworkAdapterList().CurrentAdapter("CpiDeviceListUpnp::HandleInterfaceChange").Ptr();
    if (current != NULL && TIpAddressUtils::Equal(current->Address(), iInterface)) {
        // list of subnets has changed but our interface is still available so there's nothing for us to do here
        current->RemoveRef("CpiDeviceListUpnp::HandleInterfaceChange");
        return;
    }
    StopListeners();

    if (current == NULL) {
        iLock.Wait();
        iInterface = kTIpAddressEmpty;
        iLock.Signal();
        RemoveAll();
        return;
    }

    // we used to only remove devices for subnet changes
    // its not clear why this was correct - any interface change will result in control/event urls changing
    RemoveAll();
    
    iLock.Wait();
    iInterface = current->Address();
    iLock.Signal();
    current->RemoveRef("CpiDeviceListUpnp::HandleInterfaceChange");

    {
        AutoMutex a(iSsdpLock);
        iUnicastListener = new SsdpListenerUnicast(iCpStack.Env(), *this, iInterface);
        iUnicastListener->Start();
        iMulticastListener = &(iCpStack.Env().MulticastListenerClaim(iInterface));
        iNotifyHandlerId = iMulticastListener->AddNotifyHandler(this);
    }
    Refresh();
}

void CpiDeviceListUpnp::RemoveAll()
{
    iRefreshTimer->Cancel();
    CancelRefresh();
    iLock.Wait();
    std::vector<CpiDevice*> devices;
    CpDeviceMap::iterator it = iMap.begin();
    while (it != iMap.end()) {
        devices.push_back(it->second);
        it->second->AddRef();
        it++;
    }
    iLock.Signal();
    for (TUint i=0; i<(TUint)devices.size(); i++) {
        Remove(devices[i]->Udn());
        devices[i]->RemoveRef();
    }
}

void CpiDeviceListUpnp::XmlFetchCompleted(CpiDeviceUpnp& aDevice, TBool aError)
{
    if (aError) {
        const Brx& udn = aDevice.Udn();
        const Brx& location = aDevice.Location();
        LOG_ERROR(kDevice, "Device xml fetch error {udn{%.*s}, location{%.*s}}\n",
                             PBUF(udn), PBUF(location));
        Remove(aDevice.Udn());
    }
    else {
        SetDeviceReady(aDevice.Device());
    }
}

void CpiDeviceListUpnp::DeviceLocationChanged(CpiDeviceUpnp* aOriginal, CpiDeviceUpnp* aNew)
{
    Remove(aOriginal->Udn());
    Add(aNew);
}

void CpiDeviceListUpnp::SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    (void)Update(aUuid, aLocation, aMaxAge);
}

void CpiDeviceListUpnp::SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    (void)Update(aUuid, aLocation, aMaxAge);
}

void CpiDeviceListUpnp::SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& /*aDomain*/, const Brx& /*aType*/,
                                                 TUint /*aVersion*/, const Brx& aLocation, TUint aMaxAge)
{
    (void)Update(aUuid, aLocation, aMaxAge);
}

void CpiDeviceListUpnp::SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& /*aDomain*/, const Brx& /*aType*/,
                                                  TUint /*aVersion*/, const Brx& aLocation, TUint aMaxAge)
{
    (void)Update(aUuid, aLocation, aMaxAge);
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

void CpiDeviceListUpnp::NotifyResumed()
{
    /* UDP sockets don't seem usable immediately after we resume
       ...so wait a short while before doing anything */
    iResumedTimer->FireIn(kResumeDelayMs);
}


// CpiDeviceListUpnpAll

CpiDeviceListUpnpAll::CpiDeviceListUpnpAll(CpStack& aCpStack, FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : CpiDeviceListUpnp(aCpStack, aAdded, aRemoved)
{
}

CpiDeviceListUpnpAll::~CpiDeviceListUpnpAll()
{
    StopListeners();
}

void CpiDeviceListUpnpAll::Start()
{
    CpiDeviceListUpnp::DoStart();
    AutoMutex a(iSsdpLock);
    if (iUnicastListener != NULL) {
        try {
            iUnicastListener->MsearchAll();
        }
        catch (NetworkError&) {
            LOG_ERROR(kDevice, "Error sending msearch for CpiDeviceListUpnpAll\n");
        }
        catch (WriterError&) {
            LOG_ERROR(kDevice, "Error sending msearch for CpiDeviceListUpnpAll\n");
        }
    }
}

void CpiDeviceListUpnpAll::SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    SsdpNotification(aUuid, aLocation, aMaxAge);
}

void CpiDeviceListUpnpAll::SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    SsdpNotification(aUuid, aLocation, aMaxAge);
}

void CpiDeviceListUpnpAll::SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& /*aDomain*/, const Brx& /*aType*/,
                                                     TUint /*aVersion*/, const Brx& aLocation, TUint aMaxAge)
{
    SsdpNotification(aUuid, aLocation, aMaxAge);
}

void CpiDeviceListUpnpAll::SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& /*aDomain*/, const Brx& /*aType*/,
                                                      TUint /*aVersion*/, const Brx& aLocation, TUint aMaxAge)
{
    SsdpNotification(aUuid, aLocation, aMaxAge);
}

void CpiDeviceListUpnpAll::SsdpNotification(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    if (Update(aUuid, aLocation, aMaxAge)) {
        return;
    }
    if (IsLocationReachable(aLocation)) {
        CpiDeviceUpnp* device = new CpiDeviceUpnp(iCpStack, aUuid, aLocation, aMaxAge, *this, *this);
        Add(device);
    }
}


// CpiDeviceListUpnpRoot

CpiDeviceListUpnpRoot::CpiDeviceListUpnpRoot(CpStack& aCpStack, FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : CpiDeviceListUpnp(aCpStack, aAdded, aRemoved)
{
}

CpiDeviceListUpnpRoot::~CpiDeviceListUpnpRoot()
{
    StopListeners();
}

void CpiDeviceListUpnpRoot::Start()
{
    CpiDeviceListUpnp::DoStart();
    AutoMutex a(iSsdpLock);
    if (iUnicastListener != NULL) {
        try {
            iUnicastListener->MsearchRoot();
        }
        catch (NetworkError&) {
            LOG_ERROR(kDevice, "Error sending msearch for CpiDeviceListUpnpRoot\n");
        }
        catch (WriterError&) {
            LOG_ERROR(kDevice, "Error sending msearch for CpiDeviceListUpnpRoot\n");
        }
    }
}

void CpiDeviceListUpnpRoot::SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    if (Update(aUuid, aLocation, aMaxAge)) {
        return;
    }
    if (IsLocationReachable(aLocation)) {
        CpiDeviceUpnp* device = new CpiDeviceUpnp(iCpStack, aUuid, aLocation, aMaxAge, *this, *this);
        Add(device);
    }
}


// CpiDeviceListUpnpUuid

CpiDeviceListUpnpUuid::CpiDeviceListUpnpUuid(CpStack& aCpStack, const Brx& aUuid, FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : CpiDeviceListUpnp(aCpStack, aAdded, aRemoved)
    , iUuid(aUuid)
{
}

CpiDeviceListUpnpUuid::~CpiDeviceListUpnpUuid()
{
    StopListeners();
}

void CpiDeviceListUpnpUuid::Start()
{
    CpiDeviceListUpnp::DoStart();
    AutoMutex a(iSsdpLock);
    if (iUnicastListener != NULL) {
        try {
            iUnicastListener->MsearchUuid(iUuid);
        }
        catch (NetworkError&) {
            LOG_ERROR(kDevice, "Error sending msearch for CpiDeviceListUpnpUuid\n");
        }
        catch (WriterError&) {
            LOG_ERROR(kDevice, "Error sending msearch for CpiDeviceListUpnpUuid\n");
        }
    }
}

void CpiDeviceListUpnpUuid::SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge)
{
    if (aUuid != iUuid) {
        return;
    }
    if (Update(aUuid, aLocation, aMaxAge)) {
        return;
    }
    if (IsLocationReachable(aLocation)) {
        CpiDeviceUpnp* device = new CpiDeviceUpnp(iCpStack, aUuid, aLocation, aMaxAge, *this, *this);
        Add(device);
    }
}


// CpiDeviceListUpnpDeviceType

CpiDeviceListUpnpDeviceType::CpiDeviceListUpnpDeviceType(CpStack& aCpStack, const Brx& aDomainName, const Brx& aDeviceType,
                                                         TUint aVersion, FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : CpiDeviceListUpnp(aCpStack, aAdded, aRemoved)
    , iDomainName(aDomainName)
    , iDeviceType(aDeviceType)
    , iVersion(aVersion)
{
}

CpiDeviceListUpnpDeviceType::~CpiDeviceListUpnpDeviceType()
{
    StopListeners();
}

void CpiDeviceListUpnpDeviceType::Start()
{
    CpiDeviceListUpnp::DoStart();
    AutoMutex a(iSsdpLock);
    if (iUnicastListener != NULL) {
        try {
            iUnicastListener->MsearchDeviceType(iDomainName, iDeviceType, iVersion);
        }
        catch (NetworkError&) {
            LOG_ERROR(kDevice, "Error sending msearch for CpiDeviceListUpnpDeviceType\n");
        }
        catch (WriterError&) {
            LOG_ERROR(kDevice, "Error sending msearch for CpiDeviceListUpnpDeviceType\n");
        }
    }
}

void CpiDeviceListUpnpDeviceType::SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType,
                                                            TUint aVersion, const Brx& aLocation, TUint aMaxAge)
{
    if (aVersion<iVersion || aDomain!=iDomainName || aType!=iDeviceType) {
        return;
    }
    if (Update(aUuid, aLocation, aMaxAge)) {
        return;
    }
    if (IsLocationReachable(aLocation)) {
        CpiDeviceUpnp* device = new CpiDeviceUpnp(iCpStack, aUuid, aLocation, aMaxAge, *this, *this);
        Add(device);
    }
}


// CpiDeviceListUpnpServiceType

CpiDeviceListUpnpServiceType::CpiDeviceListUpnpServiceType(CpStack& aCpStack, const Brx& aDomainName, const Brx& aServiceType,
                                                           TUint aVersion, FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : CpiDeviceListUpnp(aCpStack, aAdded, aRemoved)
    , iDomainName(aDomainName)
    , iServiceType(aServiceType)
    , iVersion(aVersion)
{
}

CpiDeviceListUpnpServiceType::~CpiDeviceListUpnpServiceType()
{
    StopListeners();
}

void CpiDeviceListUpnpServiceType::Start()
{
    CpiDeviceListUpnp::DoStart();
    AutoMutex a(iSsdpLock);
    if (iUnicastListener != NULL) {
        try {
            iUnicastListener->MsearchServiceType(iDomainName, iServiceType, iVersion);
        }
        catch (NetworkError&) {
            LOG_ERROR(kDevice, "Error sending msearch for CpiDeviceListUpnpServiceType\n");
        }
        catch (WriterError&) {
            LOG_ERROR(kDevice, "Error sending msearch for CpiDeviceListUpnpServiceType\n");
        }
    }
}

void CpiDeviceListUpnpServiceType::SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType,
                                                              TUint aVersion, const Brx& aLocation, TUint aMaxAge)
{
    if (aVersion<iVersion || aDomain!=iDomainName || aType!=iServiceType) {
        return;
    }
    if (Update(aUuid, aLocation, aMaxAge)) {
        return;
    }
    if (IsLocationReachable(aLocation)) {
        CpiDeviceUpnp* device = new CpiDeviceUpnp(iCpStack, aUuid, aLocation, aMaxAge, *this, *this);
        Add(device);
    }
}
