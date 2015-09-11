#include <OpenHome/Net/Private/DviProtocolUpnp.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Net/Private/DviServerUpnp.h>
#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/MimeTypes.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// DviProtocolUpnp

const Brn DviProtocolUpnp::kProtocolName("Upnp");
const Brn DviProtocolUpnp::kDeviceXmlName("device.xml");
const Brn DviProtocolUpnp::kServiceXmlName("service.xml");
const Brn DviProtocolUpnp::kControlUrlTail("control");
const Brn DviProtocolUpnp::kEventUrlTail("event");
static const TChar kAttributeKeyVersionMajor[] = "Version.Major";
static const TChar kAttributeKeyVersionMinor[] = "Version.Minor";

DviProtocolUpnp::DviProtocolUpnp(DviDevice& aDevice)
    : iDevice(aDevice)
    , iDvStack(aDevice.GetDvStack())
    , iLock("DMUP")
    , iUpdateCount(0)
    , iSuppressScheduledEvents(false)
{
    SetAttribute(kAttributeKeyVersionMajor, "1");
    SetAttribute(kAttributeKeyVersionMinor, "1");
    iLock.Wait();
    iServer = &(iDvStack.ServerUpnp());
    NetworkAdapterList& adapterList = iDvStack.Env().NetworkAdapterList();
    Functor functor = MakeFunctor(*this, &DviProtocolUpnp::HandleInterfaceChange);
    iCurrentAdapterChangeListenerId = adapterList.AddCurrentChangeListener(functor);
    iSubnetListChangeListenerId = adapterList.AddSubnetListChangeListener(functor);
    std::vector<NetworkAdapter*>* subnetList = adapterList.CreateSubnetList();
    AutoNetworkAdapterRef ref(iDvStack.Env(), "DviProtocolUpnp ctor");
    const NetworkAdapter* current = ref.Adapter();
    if (current != NULL) {
        AddInterface(*current);
    }
    else {
        for (TUint i=0; i<subnetList->size(); i++) {
            NetworkAdapter* subnet = (*subnetList)[i];
            try {
                AddInterface(*subnet);
            }
            catch (NetworkError& ) {
                // some hosts may have adapters that don't support multicast
                // we can't differentiate between no support ever and transient failure
                // (typical on Windows & Mac after hibernation) so just ignore this exception
                // and trust that we'll get advertised on another interface.
                char* adapterName = subnet->FullName();
                LOG2(kTrace, kError, "DvDevice unable to use adapter %s\n", adapterName);
                delete adapterName;
            }
        }
    }
    NetworkAdapterList::DestroySubnetList(subnetList);
    iAliveTimer = new Timer(iDvStack.Env(), MakeFunctor(*this, &DviProtocolUpnp::SendAliveNotifications), "DviProtocolUpnp");
    iLock.Signal();
}

DviProtocolUpnp::~DviProtocolUpnp()
{
    delete iAliveTimer;
    iLock.Wait();
    iDvStack.Env().NetworkAdapterList().RemoveCurrentChangeListener(iCurrentAdapterChangeListenerId);
    iDvStack.Env().NetworkAdapterList().RemoveSubnetListChangeListener(iSubnetListChangeListenerId);
    // Don't delete elements from iAdapters with iLock held - this risks deadlock with SsdpListenerMulticast's lock
    std::vector<DviProtocolUpnpAdapterSpecificData*> adapters(iAdapters);
    iAdapters.clear();
    iSuppressScheduledEvents = true;
    iLock.Signal();
    for (TUint i=0; i<adapters.size(); i++) {
        adapters[i]->Destroy();
    }
    iDvStack.SsdpNotifierManager().Stop(iDevice.Udn());
}

const Brx& DviProtocolUpnp::Udn() const
{
    return iDevice.Udn();
}

TBool DviProtocolUpnp::IsRoot() const
{
    return iDevice.IsRoot();
}

TUint DviProtocolUpnp::ServiceCount() const
{
    return iDevice.ServiceCount();
}

DviService& DviProtocolUpnp::Service(TUint aIndex)
{
    return iDevice.Service(aIndex);
}

Brn DviProtocolUpnp::Domain() const
{
    const TChar* ptr;
    GetAttribute("Domain", &ptr);
    Brn domain(ptr);
    return domain;
}

Brn DviProtocolUpnp::Type() const
{
    const TChar* ptr;
    GetAttribute("Type", &ptr);
    Brn type(ptr);
    return type;
}

TUint DviProtocolUpnp::Version() const
{
    const TChar* ptr;
    GetAttribute("Version", &ptr);
    Brn verBuf(ptr);
    return Ascii::Uint(verBuf);
}

DviProtocolUpnpAdapterSpecificData* DviProtocolUpnp::AddInterface(const NetworkAdapter& aAdapter)
{
    TIpAddress addr = aAdapter.Address();
    Bws<Uri::kMaxUriBytes> uriBase;
    TUint port = iServer->Port(addr);
    DviDevice* root = (iDevice.IsRoot()? &iDevice : iDevice.Root());
    root->GetUriBase(uriBase, addr, port, *this);
    DviProtocolUpnpAdapterSpecificData* adapter = new DviProtocolUpnpAdapterSpecificData(iDvStack, *this, aAdapter, uriBase, port);
    iAdapters.push_back(adapter);
    return adapter;
}

void DviProtocolUpnp::HandleInterfaceChange()
{
    TBool update = false;
    std::vector<DviProtocolUpnpAdapterSpecificData*> pendingDelete;
    {
        AutoMutex a(iLock);
        NetworkAdapterList& adapterList = iDvStack.Env().NetworkAdapterList();
        AutoNetworkAdapterRef ref(iDvStack.Env(), "DviProtocolUpnp::HandleInterfaceChange");
        const NetworkAdapter* current = ref.Adapter();
        TUint i = 0;
        if (adapterList.SingleSubnetModeEnabled()) {
            // remove listeners whose interface is no longer available
            while (i<iAdapters.size()) {
                if (current != NULL && iAdapters[i]->Interface() == current->Address()) {
                    i++;
                }
                else {
                    iAdapters[i]->SetPendingDelete();
                    pendingDelete.push_back(iAdapters[i]);
                    iAdapters.erase(iAdapters.begin() + i);
                }
                // add listener if 'current' is a new subnet
                if (iAdapters.size() == 0 && current != NULL) {
                    iDvStack.SsdpNotifierManager().Stop(iDevice.Udn());
                    DviProtocolUpnpAdapterSpecificData* adapter = AddInterface(*current);
                    if (iDevice.Enabled()) {
                        adapter->SendByeByeThenAlive(*this);
                    }
                }
            }
        }
        else {
            std::vector<NetworkAdapter*>* subnetList = adapterList.CreateSubnetList();
            std::vector<NetworkAdapter*>* adapters = adapterList.CreateNetworkAdapterList();
            // remove listeners whose interface is no longer available
            while (i<iAdapters.size()) {
                if (FindAdapter(iAdapters[i]->Interface(), *adapters) != -1) {
                    i++;
                }
                else {
                    iAdapters[i]->SetPendingDelete();
                    pendingDelete.push_back(iAdapters[i]);
                    iAdapters.erase(iAdapters.begin() + i);
                }
            }

            // add listeners for new subnets
            for (i=0; i<subnetList->size(); i++) {
                NetworkAdapter* subnet = (*subnetList)[i];
                if (FindListenerForSubnet(subnet->Subnet()) == -1) {
                    AddInterface(*subnet);
                    update = iDevice.Enabled();
                }
            }
            NetworkAdapterList::DestroyNetworkAdapterList(adapters);
            NetworkAdapterList::DestroySubnetList(subnetList);
            if (update) {
                // halt any ssdp broadcasts/responses that are currently in progress
                // (in case they're for a subnet that's no longer valid)
                // they'll be advertised again by the SendUpdateNotifications() call below
                iDvStack.SsdpNotifierManager().Stop(iDevice.Udn());
            }
        }
    }

    for (TUint i=0; i<pendingDelete.size(); i++) {
        pendingDelete[i]->Destroy();
    }

    if (update) {
        SendUpdateNotifications();
    }
}

TInt DviProtocolUpnp::FindAdapter(TIpAddress aAdapter, const std::vector<NetworkAdapter*>& aAdapterList)
{
    for (TUint i=0; i<aAdapterList.size(); i++) {
        if (aAdapterList[i]->Address() == aAdapter) {
            return i;
        }
    }
    return -1;
}

TInt DviProtocolUpnp::FindListenerForSubnet(TIpAddress aSubnet)
{
    for (TUint i=0; i<iAdapters.size(); i++) {
        if (iAdapters[i]->Subnet() == aSubnet) {
            return i;
        }
    }
    return -1;
}

TInt DviProtocolUpnp::FindListenerForInterface(TIpAddress aAdapter)
{
    for (TUint i=0; i<iAdapters.size(); i++) {
        if (iAdapters[i]->Interface() == aAdapter) {
            return i;
        }
    }
    return -1;
}

void DviProtocolUpnp::WriteResource(const Brx& aUriTail, TIpAddress aAdapter, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter)
{
    if (aUriTail == kDeviceXmlName) {
        Brh xml;
        Brn xmlBuf;
        iLock.Wait();
        const TInt index = FindListenerForInterface(aAdapter);
        if (index == -1) {
            iLock.Signal();
            return;
        }
        if (iDevice.IsRoot()) {
            const Brx& cachedXml = iAdapters[index]->DeviceXml();
            if (cachedXml.Bytes() > 0) {
                xmlBuf.Set(cachedXml);
            }
        }
        if (xmlBuf.Bytes() == 0) {
            GetDeviceXml(xml, aAdapter);
            if (iDevice.IsRoot()) {
                iAdapters[index]->SetDeviceXml(xml);
                xmlBuf.Set(iAdapters[index]->DeviceXml());
            }
            else {
                xmlBuf.Set(xml);
            }
        }
        iLock.Signal();
        aResourceWriter.WriteResourceBegin(xmlBuf.Bytes(), kOhNetMimeTypeXml);
        aResourceWriter.WriteResource(xmlBuf.Ptr(), xmlBuf.Bytes());
        aResourceWriter.WriteResourceEnd();
    }
    else {
        Parser parser(aUriTail);
        Brn buf = parser.Next('/');
        Brn rem = parser.Remaining();
        if (buf == DviDevice::kResourceDir) {
            IResourceManager* resMgr = iDevice.ResourceManager();
            if (resMgr != NULL) {
                resMgr->WriteResource(rem, aAdapter, aLanguageList, aResourceWriter);
            }
        }
        else if (rem == kServiceXmlName) {
            iLock.Wait();
            DviService* service = 0;
            const TUint count = iDevice.ServiceCount();
            for (TUint i=0; i<count; i++) {
                DviService& s = iDevice.Service(i);
                if (s.ServiceType().PathUpnp() == buf) {
                    service = &s;
                    break;
                }
            }
            iLock.Signal();
            if (service == 0) {
                THROW(ReaderError);
            }
            DviProtocolUpnpServiceXmlWriter::Write(*service, *this, aResourceWriter);
        }
    }
}

const Brx& DviProtocolUpnp::ProtocolName() const
{
    return kProtocolName;
}

void DviProtocolUpnp::Enable()
{
    iLock.Wait();
    
    // check we have at least the basic attributes requried for advertisement
    ASSERT(Domain().Bytes() > 0);
    ASSERT(Type().Bytes() > 0);
    ASSERT(Version() > 0);
    
    for (TUint i=0; i<iAdapters.size(); i++) {
        DviProtocolUpnpAdapterSpecificData* adapter = iAdapters[i];
        Bws<Uri::kMaxUriBytes> uriBase;
        DviDevice* root = (iDevice.IsRoot()? &iDevice : iDevice.Root());
        adapter->UpdateServerPort(*iServer);
        root->GetUriBase(uriBase, adapter->Interface(), adapter->ServerPort(), *this);
        adapter->UpdateUriBase(uriBase);
        adapter->ClearDeviceXml();
        if (iDevice.ResourceManager() != NULL) {
            const TChar* name = 0;
            GetAttribute("FriendlyName", &name);
            adapter->BonjourRegister(name, iDevice.Udn(), kProtocolName, iDevice.kResourceDir);
            /*GetAttribute("MdnsHostName", &name);
            if (name != NULL) {
                iDvStack.MdnsProvider()->MdnsSetHostName(name);
                Bwh redirectedPath(iDevice.Udn().Bytes() + kProtocolName.Bytes() + iDevice.kResourceDir.Bytes() + 4);
                redirectedPath.Append('/');
                Uri::Escape(redirectedPath, iDevice.Udn());
                redirectedPath.Append('/');
                redirectedPath.Append(kProtocolName);
                redirectedPath.Append('/');
                redirectedPath.Append(iDevice.kResourceDir);
                redirectedPath.Append('/');
                iDvStack.ServerUpnp().Redirect(Brn("/"), redirectedPath);
            }*/
        }
    }
    for (TUint i=0; i<iAdapters.size(); i++) {
        iAdapters[i]->SendByeByeThenAlive(*this);
    }
    iLock.Signal();
    QueueAliveTimer();
}

void DviProtocolUpnp::Disable(Functor& aComplete)
{
    TBool completeNow = false;
    {
        AutoMutex a(iLock);
        iDisableComplete = aComplete;
        TUint i;
        iDvStack.SsdpNotifierManager().Stop(iDevice.Udn());
        iSubnetDisableCount = (TUint)iAdapters.size();
        Functor functor = MakeFunctor(*this, &DviProtocolUpnp::SubnetDisabled);
        for (i=0; i<iSubnetDisableCount; i++) {
            LogMulticastNotification("byebye");
            Bws<kMaxUriBytes> uri;
            GetUriDeviceXml(uri, iAdapters[i]->UriBase());
            try {
                iDvStack.SsdpNotifierManager().AnnouncementByeBye(*this, iAdapters[i]->Interface(), uri, iDevice.ConfigId(), functor);
            }
            catch (NetworkError&) {
                completeNow = true;
            }
        }
        for (TUint i=0; i<iAdapters.size(); i++) {
            iAdapters[i]->BonjourDeregister();
        }
        const TChar* name = 0;
        GetAttribute("MdnsHostName", &name);
        if (name != NULL) {
            iDvStack.MdnsProvider()->MdnsSetHostName("");
        }
    }
    if (completeNow) {
        iSubnetDisableCount = 0;
        iDisableComplete();
    }
}

void DviProtocolUpnp::GetAttribute(const TChar* aKey, const TChar** aValue) const
{
    *aValue = iAttributeMap.Get(aKey);
}

void DviProtocolUpnp::SetAttribute(const TChar* aKey, const TChar* aValue)
{
    if (strcmp(aKey, "TestUpdate") == 0) {
        SendUpdateNotifications();
        return;
    }
    if (strcmp(aKey, "MdnsHostName") == 0) {
        ASSERT(iDevice.ResourceManager() != NULL);
        ASSERT(iDvStack.MdnsProvider() != NULL);
    }

    iAttributeMap.Set(aKey, aValue);
}

void DviProtocolUpnp::SetCustomData(const TChar* aTag, void* aData)
{
    Brn tag(aTag);
    if (tag == Brn("Server")) {
        iServer = reinterpret_cast<DviServerUpnp*>(aData);
    }
}

void DviProtocolUpnp::GetResourceManagerUri(const NetworkAdapter& aAdapter, Brh& aUri)
{
    if (iDevice.ResourceManager() == NULL) {
        return;
    }
    for (TUint i=0; i<(TUint)iAdapters.size(); i++) {
        if (iAdapters[i]->Interface() == aAdapter.Address()) {
            WriterBwh writer(1024);
            writer.Write("http://");
            Bws<Endpoint::kMaxEndpointBytes> buf;
            Endpoint ep(iAdapters[i]->ServerPort(), aAdapter.Address());
            ep.AppendEndpoint(buf);
            writer.Write(buf);
            writer.Write('/');
            Uri::Escape(writer, iDevice.Udn());
            writer.Write('/');
            writer.Write(kProtocolName);
            writer.Write('/');
            writer.Write(iDevice.kResourceDir);
            writer.Write('/');
            writer.TransferTo(aUri);
            return;
        }
    }
}

void DviProtocolUpnp::SubnetDisabled()
{
    iLock.Wait();
    ASSERT(iSubnetDisableCount != 0);
    TBool signal = (--iSubnetDisableCount == 0);
    iLock.Signal();
    if (signal) {
        iDisableComplete();
    }
}

void DviProtocolUpnp::SubnetUpdated()
{
    iLock.Wait();
    ASSERT(iUpdateCount != 0);
    TBool signal = (--iUpdateCount == 0);
    iLock.Signal();
    if (signal) {
        SendAliveNotifications();
    }
}

void DviProtocolUpnp::SendAliveNotifications()
{
    if(!iDevice.Enabled()) {
        return;
    }
    LogMulticastNotification("alive");
    AutoMutex a(iLock);
    for (TUint i=0; i<iAdapters.size(); i++) {
        Bws<kMaxUriBytes> uri;
        GetUriDeviceXml(uri, iAdapters[i]->UriBase());
        try {
            iDvStack.SsdpNotifierManager().AnnouncementAlive(*this, iAdapters[i]->Interface(), uri, iDevice.ConfigId());
        }
        catch (NetworkError&) {}
    }
    QueueAliveTimer();
}

void DviProtocolUpnp::QueueAliveTimer()
{
    Environment& env = iDvStack.Env();
    TUint maxUpdateTimeMs = env.InitParams()->DvMaxUpdateTimeSecs() * 1000;
    TUint updateTimeMs = env.Random(maxUpdateTimeMs/2, maxUpdateTimeMs/4);
    iAliveTimer->FireIn(updateTimeMs);
}

void DviProtocolUpnp::SendUpdateNotifications()
{
    LogMulticastNotification("update");
    iAliveTimer->Cancel();
    AutoMutex a(iLock);
    iDvStack.UpdateBootId();
    const TUint numAdapters = (TUint)iAdapters.size();
    iUpdateCount += numAdapters; // its possible this'll be called while previous updates are still being processed
    Functor functor = MakeFunctor(*this, &DviProtocolUpnp::SubnetUpdated);
    for (TUint i=0; i<iAdapters.size(); i++) {
        Bws<kMaxUriBytes> uri;
        GetUriDeviceXml(uri, iAdapters[i]->UriBase());
        iDvStack.SsdpNotifierManager().AnnouncementUpdate(*this, iAdapters[i]->Interface() , uri, iDevice.ConfigId(), functor);
    }
}

void DviProtocolUpnp::SendByeByes(TIpAddress aAdapter, const Brx& aUriBase, Functor aCompleted)
{
    Bws<kMaxUriBytes> uri;
    GetUriDeviceXml(uri, aUriBase);
    try {
        iDvStack.SsdpNotifierManager().AnnouncementByeBye(*this, aAdapter, uri, iDevice.ConfigId(), aCompleted);
    }
    catch (NetworkError&) {
        if (aCompleted) {
            aCompleted();
        }
    }
}

void DviProtocolUpnp::SendAlives(TIpAddress aAdapter, const Brx& aUriBase)
{
    AutoMutex a(iLock);
    Bws<kMaxUriBytes> uri;
    GetUriDeviceXml(uri, aUriBase);
    try {
        iDvStack.SsdpNotifierManager().AnnouncementAlive(*this, aAdapter, uri, iDevice.ConfigId());
    }
    catch (NetworkError&) {}
}

void DviProtocolUpnp::GetUriDeviceXml(Bwx& aUri, const Brx& aUriBase)
{
    aUri.Replace(aUriBase);
    aUri.Append(kDeviceXmlName);
}

void DviProtocolUpnp::GetDeviceXml(Brh& aXml, TIpAddress aAdapter)
{
    LOG(kDvDevice, "> DviProtocolUpnp::GetDeviceXml\n");
    DviProtocolUpnpDeviceXmlWriter writer(*this);
    writer.Write(aAdapter);
    writer.TransferTo(aXml);
    LOG(kDvDevice, "< DviProtocolUpnp::GetDeviceXml\n");
}

void DviProtocolUpnp::LogUnicastNotification(const char* aType)
{
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    LOG(kDvDevice, "Device ");
    LOG(kDvDevice, iDevice.Udn());
    LOG(kDvDevice, " starting response to msearch type \'%s\'\n", aType);
    lock.Signal();
}

void DviProtocolUpnp::LogMulticastNotification(const char* aType)
{
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    LOG(kDvDevice, "Device ");
    LOG(kDvDevice, iDevice.Udn());
    LOG(kDvDevice, " starting to send %s notifications.\n", aType);
    lock.Signal();
}

void DviProtocolUpnp::SsdpSearchAll(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter)
{
    if (iDevice.Enabled()) {
        AutoMutex a(iLock);
        TInt index = FindListenerForInterface(aAdapter);
        if (index != -1) {
            LogUnicastNotification("all");
            Bws<kMaxUriBytes> uri;
            GetUriDeviceXml(uri, iAdapters[index]->UriBase());
            iDvStack.SsdpNotifierManager().MsearchResponseAll(*this, aEndpoint, aMx, uri, iDevice.ConfigId(), aAdapter);
        }
    }
}

void DviProtocolUpnp::SsdpSearchRoot(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter)
{
    if (iDevice.Enabled() && iDevice.IsRoot()) {
        AutoMutex a(iLock);
        TInt index = FindListenerForInterface(aAdapter);
        if (index != -1) {
            LogUnicastNotification("root");
            Bws<kMaxUriBytes> uri;
            GetUriDeviceXml(uri, iAdapters[index]->UriBase());
            iDvStack.SsdpNotifierManager().MsearchResponseRoot(*this, aEndpoint, aMx, uri, iDevice.ConfigId(), aAdapter);
        }
    }
}

void DviProtocolUpnp::SsdpSearchUuid(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter, const Brx& aUuid)
{
    if (iDevice.Enabled() && iDevice.Udn() == aUuid) {
        AutoMutex a(iLock);
        TInt index = FindListenerForInterface(aAdapter);
        if (index != -1) {
            LogUnicastNotification("uuid");
            Bws<kMaxUriBytes> uri;
            GetUriDeviceXml(uri, iAdapters[index]->UriBase());
            iDvStack.SsdpNotifierManager().MsearchResponseUuid(*this, aEndpoint, aMx, uri, iDevice.ConfigId(), aAdapter);
        }
    }
}

void DviProtocolUpnp::SsdpSearchDeviceType(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    if (iDevice.Enabled() && Version() >= aVersion && Domain() == aDomain && Type() == aType) {
        AutoMutex a(iLock);
        TInt index = FindListenerForInterface(aAdapter);
        if (index != -1) {
            LogUnicastNotification("device");
            Bws<kMaxUriBytes> uri;
            GetUriDeviceXml(uri, iAdapters[index]->UriBase());
            iDvStack.SsdpNotifierManager().MsearchResponseDeviceType(*this, aEndpoint, aMx, uri, iDevice.ConfigId(), aAdapter);
        }
    }
}

void DviProtocolUpnp::SsdpSearchServiceType(const Endpoint& aEndpoint, TUint aMx, TIpAddress aAdapter, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    AutoMutex a(iLock);
    if (iDevice.Enabled()) {
        const TUint count = iDevice.ServiceCount();
        for (TUint i=0; i<count; i++) {
            const OpenHome::Net::ServiceType& serviceType = iDevice.Service(i).ServiceType();
            if (serviceType.Version() >= aVersion && serviceType.Domain() == aDomain && serviceType.Name() == aType) {
                TInt index = FindListenerForInterface(aAdapter);
                if (index != -1) {
                    LogUnicastNotification("service");
                    Bws<kMaxUriBytes> uri;
                    GetUriDeviceXml(uri, iAdapters[index]->UriBase());
                    iDvStack.SsdpNotifierManager().MsearchResponseServiceType(*this, aEndpoint, aMx, serviceType, uri, iDevice.ConfigId(), aAdapter);
                }
                break;
            }
        }
    }
}


// DviProtocolUpnpAdapterSpecificData

DviProtocolUpnpAdapterSpecificData::DviProtocolUpnpAdapterSpecificData(DvStack& aDvStack, IUpnpMsearchHandler& aMsearchHandler, const NetworkAdapter& aAdapter, Bwx& aUriBase, TUint aServerPort)
    : iRefCount(1)
    , iDvStack(aDvStack)
    , iMsearchHandler(&aMsearchHandler)
    , iId(0x7fffffff)
    , iSubnet(aAdapter.Subnet())
    , iAdapter(aAdapter.Address())
    , iUriBase(aUriBase)
    , iServerPort(aServerPort)
    , iBonjourWebPage(0)
    , iDevice(NULL)
{
    iListener = &(iDvStack.Env().MulticastListenerClaim(aAdapter.Address()));
    iId = iListener->AddMsearchHandler(this);
}

void DviProtocolUpnpAdapterSpecificData::Destroy()
{
    if (--iRefCount == 0) {
        delete this;
    }
    // if iRefCount>0 this object is now orphaned
    // ...there is a tiny risk of it being leaked if the stack is immediately shut down
}

DviProtocolUpnpAdapterSpecificData::~DviProtocolUpnpAdapterSpecificData()
{
    if (iBonjourWebPage != NULL) {
        iBonjourWebPage->SetDisabled();
        delete iBonjourWebPage;
    }
    iListener->RemoveMsearchHandler(iId);
    iDvStack.Env().MulticastListenerRelease(iAdapter);
}

TIpAddress DviProtocolUpnpAdapterSpecificData::Interface() const
{
    return iListener->Interface();
}

TIpAddress DviProtocolUpnpAdapterSpecificData::Subnet() const
{
    return iSubnet;
}

const Brx& DviProtocolUpnpAdapterSpecificData::UriBase() const
{
    ASSERT(iUriBase.Bytes() > 0);
    return iUriBase;
}

void DviProtocolUpnpAdapterSpecificData::UpdateServerPort(DviServerUpnp& aServer)
{
    iServerPort = aServer.Port(iAdapter);
}

void DviProtocolUpnpAdapterSpecificData::UpdateUriBase(Bwx& aUriBase)
{
    iUriBase.Replace(aUriBase);
}

TUint DviProtocolUpnpAdapterSpecificData::ServerPort() const
{
    return iServerPort;
}

const Brx& DviProtocolUpnpAdapterSpecificData::DeviceXml() const
{
    return iDeviceXml;
}

void DviProtocolUpnpAdapterSpecificData::SetDeviceXml(Brh& aXml)
{
    aXml.TransferTo(iDeviceXml);
}

void DviProtocolUpnpAdapterSpecificData::ClearDeviceXml()
{
    Brh tmp;
    iDeviceXml.TransferTo(tmp);
}

void DviProtocolUpnpAdapterSpecificData::SetPendingDelete()
{
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    iMsearchHandler = 0;
    lock.Signal();
}

void DviProtocolUpnpAdapterSpecificData::BonjourRegister(const TChar* aName, const Brx& aUdn, const Brx& aProtocol, const Brx& aResourceDir)
{
    if (aName != NULL) {
        if (iBonjourWebPage == 0) {
            IMdnsProvider* mdnsProvider = iDvStack.MdnsProvider();
            if (mdnsProvider != NULL) {
                iBonjourWebPage = new BonjourWebPage(*mdnsProvider);
            }
        }
        if (iBonjourWebPage != NULL) {
            Bwh path(aUdn.Bytes() + aProtocol.Bytes() + aResourceDir.Bytes() + 5);
            path.Append('/');
            path.Append(aUdn);
            path.Append('/');
            path.Append(aProtocol);
            path.Append('/');
            path.Append(aResourceDir);
            path.Append('/');
            path.PtrZ();
            iBonjourWebPage->SetEnabled(aName, iAdapter, iServerPort, (const TChar*)path.Ptr());
        }
    }
}

void DviProtocolUpnpAdapterSpecificData::BonjourDeregister()
{
    if (iBonjourWebPage != NULL) {
        iBonjourWebPage->SetDisabled();
    }
}

void DviProtocolUpnpAdapterSpecificData::SendByeByeThenAlive(DviProtocolUpnp& aDevice)
{
    iDevice = &aDevice;
    iRefCount++;
    Functor functor = MakeFunctor(*this, &DviProtocolUpnpAdapterSpecificData::ByeByesComplete);
    iDevice->SendByeByes(iAdapter, iUriBase, functor);
}

void DviProtocolUpnpAdapterSpecificData::ByeByesComplete()
{
    if (--iRefCount == 0) {
        delete this;
    }
    else {
        iDevice->SendAlives(iAdapter, iUriBase);
    }
}

IUpnpMsearchHandler* DviProtocolUpnpAdapterSpecificData::Handler()
{
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    IUpnpMsearchHandler* device = iMsearchHandler;
    lock.Signal();
    return device;
}

void DviProtocolUpnpAdapterSpecificData::SsdpSearchAll(const Endpoint& aEndpoint, TUint aMx)
{
    IUpnpMsearchHandler* handler = Handler();
    if (handler != NULL) {
        handler->SsdpSearchAll(aEndpoint, aMx, iListener->Interface());
    }
}

void DviProtocolUpnpAdapterSpecificData::SsdpSearchRoot(const Endpoint& aEndpoint, TUint aMx)
{
    IUpnpMsearchHandler* handler = Handler();
    if (handler != NULL) {
        handler->SsdpSearchRoot(aEndpoint, aMx, iListener->Interface());
    }
}

void DviProtocolUpnpAdapterSpecificData::SsdpSearchUuid(const Endpoint& aEndpoint, TUint aMx, const Brx& aUuid)
{
    IUpnpMsearchHandler* handler = Handler();
    if (handler != NULL) {
        handler->SsdpSearchUuid(aEndpoint, aMx, iListener->Interface(), aUuid);
    }
}

void DviProtocolUpnpAdapterSpecificData::SsdpSearchDeviceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    IUpnpMsearchHandler* handler = Handler();
    if (handler != NULL) {
        handler->SsdpSearchDeviceType(aEndpoint, aMx, iListener->Interface(), aDomain, aType, aVersion);
    }
}

void DviProtocolUpnpAdapterSpecificData::SsdpSearchServiceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    IUpnpMsearchHandler* handler = Handler();
    if (handler != NULL) {
        handler->SsdpSearchServiceType(aEndpoint, aMx, iListener->Interface(), aDomain, aType, aVersion);
    }
}


static void writeSpecVersionNumber(WriterBwh& aWriter, const DviProtocolUpnp& aDevice, const TChar* aTag, const TChar* aKey)
{
    aWriter.Write('<');
    aWriter.Write(aTag);
    aWriter.Write('>');
    const TChar* version;
    (void)aDevice.GetAttribute(aKey, &version);
    aWriter.Write(version);
    aWriter.Write("</");
    aWriter.Write(aTag);
    aWriter.Write('>');
}

static void writeSpecVersion(WriterBwh& aWriter, const DviProtocolUpnp& aDevice)
{
    aWriter.Write("<specVersion>");
    writeSpecVersionNumber(aWriter, aDevice, "major", kAttributeKeyVersionMajor);
    writeSpecVersionNumber(aWriter, aDevice, "minor", kAttributeKeyVersionMinor);
    aWriter.Write("</specVersion>");
}

// DviProtocolUpnpDeviceXmlWriter

DviProtocolUpnpDeviceXmlWriter::DviProtocolUpnpDeviceXmlWriter(DviProtocolUpnp& aDeviceUpnp)
    : iDeviceUpnp(aDeviceUpnp)
    , iWriter(1024)
{
}

void DviProtocolUpnpDeviceXmlWriter::Write(TIpAddress aAdapter)
{
    if (iDeviceUpnp.iDevice.IsRoot()) { // root device header
        iWriter.Write("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
        iWriter.Write("<root xmlns=\"urn:schemas-upnp-org:device-1-0\">");
        writeSpecVersion(iWriter, iDeviceUpnp);
    }

    iWriter.Write(Brn("<device>"));
    iWriter.Write(Brn("<deviceType>"));
    iWriter.Write(Ssdp::kUrn);
    Brn canonicalDomain = iDeviceUpnp.Domain();
    Bwh upnpDomain(canonicalDomain.Bytes() + 10);
    Ssdp::CanonicalDomainToUpnp(canonicalDomain, upnpDomain);
    iWriter.Write(upnpDomain);
    iWriter.Write(Ssdp::kDeviceSeparator);
    Brn type = iDeviceUpnp.Type();
    iWriter.Write(type);
    iWriter.Write(Ssdp::kUrnSeparator);
    Bws<Ascii::kMaxUintStringBytes> verBuf;
    (void)Ascii::AppendDec(verBuf, iDeviceUpnp.Version());
    iWriter.Write(verBuf);
    iWriter.Write(Brn("</deviceType>"));
    const TChar* xmlExtension;
    iDeviceUpnp.GetAttribute("DeviceXmlExtension", &xmlExtension);
    if (xmlExtension != NULL) {
        iWriter.Write(xmlExtension);
    }

    WriteTag("friendlyName", "FriendlyName", eTagMandatory);
    WriteTag("manufacturer", "Manufacturer", eTagMandatory);
    WriteTag("manufacturerURL", "ManufacturerUrl", eTagOptional);
    WriteTag("modelDescription", "ModelDescription", eTagRecommended);
    WriteTag("modelName", "ModelName", eTagMandatory);
    WriteTag("modelNumber", "ModelNumber", eTagRecommended);
    WriteTag("modelURL", "ModelUrl", eTagOptional);
    WriteTag("serialNumber", "SerialNumber", eTagRecommended);

    iWriter.Write("<UDN>");
    iWriter.Write("uuid:");
    iWriter.Write(iDeviceUpnp.iDevice.Udn());
    iWriter.Write("</UDN>");

    WriteTag("UPC", "Upc", eTagOptional);
    WriteTag("iconList", "IconList", eTagOptional, eTagUnescaped);

    const TUint serviceCount = iDeviceUpnp.iDevice.ServiceCount();
    if (serviceCount > 0) {
        iWriter.Write("<serviceList>");
        for (TUint i=0; i<serviceCount; i++) {
            const OpenHome::Net::ServiceType& serviceType = iDeviceUpnp.iDevice.Service(i).ServiceType();
            iWriter.Write("<service>");
            iWriter.Write("<serviceType>");
            iWriter.Write(serviceType.FullNameUpnp());
            iWriter.Write("</serviceType>");
            iWriter.Write("<serviceId>");
            iWriter.Write(serviceType.ServiceId());
            iWriter.Write("</serviceId>");
            iWriter.Write("<SCPDURL>");
            iWriter.Write('/');
            Uri::Escape(iWriter, iDeviceUpnp.iDevice.Udn());
            iWriter.Write('/');
            iWriter.Write(iDeviceUpnp.ProtocolName());
            iWriter.Write('/');
            iWriter.Write(serviceType.PathUpnp());
            iWriter.Write('/');
            iWriter.Write(DviProtocolUpnp::kServiceXmlName);
            iWriter.Write("</SCPDURL>");
            iWriter.Write("<controlURL>");
            iWriter.Write('/');
            Uri::Escape(iWriter, iDeviceUpnp.iDevice.Udn());
            iWriter.Write('/');
            iWriter.Write(serviceType.PathUpnp());
            iWriter.Write('/');
            iWriter.Write(DviProtocolUpnp::kControlUrlTail);
            iWriter.Write("</controlURL>");
            iWriter.Write("<eventSubURL>");
            iWriter.Write('/');
            Uri::Escape(iWriter, iDeviceUpnp.iDevice.Udn());
            iWriter.Write('/');
            iWriter.Write(serviceType.PathUpnp());
            iWriter.Write('/');
            iWriter.Write(DviProtocolUpnp::kEventUrlTail);
            iWriter.Write("</eventSubURL>");
            iWriter.Write("</service>");
        }
        iWriter.Write("</serviceList>");
    }

    const TUint deviceCount = iDeviceUpnp.iDevice.DeviceCount();
    if (deviceCount > 0) {
        iWriter.Write("<deviceList>");
        std::vector<char*> emptyLanguageList;
        for (TUint i=0; i<deviceCount; i++) {
            TUint len = iDeviceUpnp.kProtocolName.Bytes() + 1 + iDeviceUpnp.kDeviceXmlName.Bytes();
            Bwh uri(len);
            uri.Append(iDeviceUpnp.kProtocolName);
            uri.Append('/');
            uri.Append(iDeviceUpnp.kDeviceXmlName);
            iDeviceUpnp.iDevice.Device(i).WriteResource(uri, aAdapter, emptyLanguageList, *this);
        }
        iWriter.Write("</deviceList>");
    }
    WritePresentationUrlTag(aAdapter);
    iWriter.Write("</device>");
    if (iDeviceUpnp.iDevice.IsRoot()) {
        iWriter.Write("</root>");
    }
}

void DviProtocolUpnpDeviceXmlWriter::TransferTo(Brh& aBuf)
{
    iWriter.TransferTo(aBuf);
}

void DviProtocolUpnpDeviceXmlWriter::WriteTag(const TChar* aTagName, const TChar* aAttributeKey, ETagRequirementLevel aRequirementLevel, ETagEscaped aEscaped)
{
    const TChar* val;
    iDeviceUpnp.GetAttribute(aAttributeKey, &val);
    if (val != NULL) {
        iWriter.Write('<');
        iWriter.Write(aTagName);
        iWriter.Write('>');
        Brn buf(val);
        if (aEscaped == eTagEscaped) {
            Converter::ToXmlEscaped(iWriter, buf);
        }
        else {
            iWriter.Write(buf);
        }
        iWriter.Write("</");
        iWriter.Write(aTagName);
        iWriter.Write('>');
    }
    else if (aRequirementLevel == eTagMandatory) {
        iWriter.Write('<');
        iWriter.Write(aTagName);
        iWriter.Write("/>");
    }
}

void DviProtocolUpnpDeviceXmlWriter::WritePresentationUrlTag(TIpAddress aAdapter)
{
    const TChar* attributeVal;
    iDeviceUpnp.GetAttribute("PresentationUrl", &attributeVal);

    bool hasAttribute = attributeVal != NULL;
    bool hasResMgr = iDeviceUpnp.iDevice.ResourceManager() != NULL;

    if (!hasAttribute && !hasResMgr)
    {
        return;
    }

    iWriter.Write("<presentationURL>");

    if (hasAttribute) {
        if (attributeVal[0]==':' || attributeVal[0]=='/') {
            // If the provided URL starts with a port or a
            // path, prefix it with the adapter's IP address
            // in the format 'http://0.0.0.0'. Otherwise, use
            // it as-is.
            // Note: What if client wants to use https?
            Bws<32> ipAddress;
            Endpoint::AppendAddress(ipAddress, aAdapter);
            iWriter.Write("http://");
            iWriter.Write(ipAddress);
        }
        Brn buf(attributeVal);
        Converter::ToXmlEscaped(iWriter, buf);
    } else if (hasResMgr){
        /* UPnP spec says to publish a relative url
           Intel device spy messes up resolution of this against the base
           (device xml) url so publish an absolute url instead */
        for (TUint i=0; i<iDeviceUpnp.iAdapters.size(); i++) {
            if (iDeviceUpnp.iAdapters[i]->Interface() == aAdapter) {
                iWriter.Write(iDeviceUpnp.iAdapters[i]->UriBase());
                break;
            }
        }
        iWriter.Write(DviDevice::kResourceDir);
        iWriter.Write('/');
    }
    iWriter.Write("</presentationURL>");
}

void DviProtocolUpnpDeviceXmlWriter::WriteResourceBegin(TUint /*aTotalBytes*/, const TChar* /*aMimeType*/)
{
}

void DviProtocolUpnpDeviceXmlWriter::WriteResource(const TByte* aData, TUint aBytes)
{
    Brn buf(aData, aBytes);
    iWriter.Write(buf);
}

void DviProtocolUpnpDeviceXmlWriter::WriteResourceEnd()
{
}


// DviProtocolUpnpServiceXmlWriter

void DviProtocolUpnpServiceXmlWriter::Write(const DviService& aService, const DviProtocolUpnp& aDevice, IResourceWriter& aResourceWriter)
{
    WriterBwh writer(1024);
    WriteServiceXml(writer, aService, aDevice);
    Brh xml;
    writer.TransferTo(xml);
    aResourceWriter.WriteResourceBegin(xml.Bytes(), kOhNetMimeTypeXml);
    aResourceWriter.WriteResource(xml.Ptr(), xml.Bytes());
    aResourceWriter.WriteResourceEnd();
}

void DviProtocolUpnpServiceXmlWriter::WriteServiceXml(WriterBwh& aWriter, const DviService& aService, const DviProtocolUpnp& aDevice)
{
    aWriter.Write("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
    aWriter.Write("<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">");
    writeSpecVersion(aWriter, aDevice);
    aWriter.Write("<actionList>");
    const std::vector<DvAction>& actions = aService.DvActions();
    for (TUint i=0; i<actions.size(); i++) {
        const Action* action = actions[i].Action();
        aWriter.Write("<action>");
        aWriter.Write("<name>");
        aWriter.Write(action->Name());
        aWriter.Write("</name>");
        if (action->InputParameters().size() > 0 || action->OutputParameters().size() > 0) {
            aWriter.Write("<argumentList>");
            WriteServiceActionParams(aWriter, *action, true);
            WriteServiceActionParams(aWriter, *action, false);
            aWriter.Write("</argumentList>");
        }
        aWriter.Write("</action>");
    }
    aWriter.Write("</actionList>");
    aWriter.Write("<serviceStateTable>");
    const std::vector<Property*>& properties = aService.Properties();
    for (TUint i=0; i<properties.size(); i++) {
        WriteStateVariable(aWriter, properties[i]->Parameter(), true, 0);
    }
    for (TUint i=0; i<actions.size(); i++) {
        const Action* action = actions[i].Action();
        WriteTechnicalStateVariables(aWriter, action, action->InputParameters());
        WriteTechnicalStateVariables(aWriter, action, action->OutputParameters());
    }
    aWriter.Write("</serviceStateTable>");
    aWriter.Write("</scpd>");
}

void DviProtocolUpnpServiceXmlWriter::WriteServiceActionParams(WriterBwh& aWriter, const Action& aAction, TBool aIn)
{
    const Action::VectorParameters& params = (aIn? aAction.InputParameters() : aAction.OutputParameters());
    for (TUint i=0; i<params.size(); i++) {
        OpenHome::Net::Parameter* param = params[i];
        aWriter.Write("<argument>");
        aWriter.Write("<name>");
        aWriter.Write(param->Name());
        aWriter.Write("</name>");
        aWriter.Write("<direction>");
        aWriter.Write(aIn? "in" : "out");
        aWriter.Write("</direction>");
        aWriter.Write("<relatedStateVariable>");
        if (param->Type() == OpenHome::Net::Parameter::eTypeRelated) {
            const Brx& relatedVar = static_cast<ParameterRelated*>(param)->Related().Parameter().Name();
            aWriter.Write(relatedVar);
        }
        else {
            Bwh relatedVar;
            GetRelatedVariableName(relatedVar, aAction.Name(), param->Name());
            aWriter.Write(relatedVar);
        }
        aWriter.Write("</relatedStateVariable>");
        aWriter.Write("</argument>");
    }
}

void DviProtocolUpnpServiceXmlWriter::GetRelatedVariableName(Bwh& aName, const Brx& aActionName, const Brx& aParameterName)
{
    static const Brn prefix("A_ARG_TYPE_");
    const TUint len = prefix.Bytes() + aActionName.Bytes() + 1 + aParameterName.Bytes();
    aName.Grow(len);
    aName.Append(prefix);
    aName.Append(aActionName);
    aName.Append('_');
    aName.Append(aParameterName);
}


void DviProtocolUpnpServiceXmlWriter::WriteStateVariable(IWriter& aWriter, const OpenHome::Net::Parameter& aParam, TBool aEvented, const Action* aAction)
{
    aWriter.Write(Brn("<stateVariable sendEvents="));
    if (aEvented) {
        aWriter.Write(Brn("\"yes\">"));
    }
    else {
        aWriter.Write(Brn("\"no\">"));
    }
    aWriter.Write(Brn("<name>"));
    if (aEvented) {
        aWriter.Write(aParam.Name());
    }
    else {
        Bwh name;
        GetRelatedVariableName(name, aAction->Name(), aParam.Name());
        aWriter.Write(name);
    }
    aWriter.Write(Brn("</name>"));
    aWriter.Write(Brn("<dataType>"));
    switch (aParam.Type())
    {
    case OpenHome::Net::Parameter::eTypeBool:
        aWriter.Write(Brn("boolean"));
        break;
    case OpenHome::Net::Parameter::eTypeInt:
        aWriter.Write(Brn("i4"));
        break;
    case OpenHome::Net::Parameter::eTypeUint:
        aWriter.Write(Brn("ui4"));
        break;
    case OpenHome::Net::Parameter::eTypeString:
        aWriter.Write(Brn("string"));
        break;
    case OpenHome::Net::Parameter::eTypeBinary:
        aWriter.Write(Brn("bin.base64"));
        break;
    case OpenHome::Net::Parameter::eTypeRelated:
        ASSERTS();
        break;
    }
    aWriter.Write(Brn("</dataType>"));
    switch (aParam.Type())
    {
    case OpenHome::Net::Parameter::eTypeBool:
    case OpenHome::Net::Parameter::eTypeBinary:
        break;
    case OpenHome::Net::Parameter::eTypeInt:
    {
        const OpenHome::Net::ParameterInt& paramInt = static_cast<const OpenHome::Net::ParameterInt&>(aParam);
        if (paramInt.MinValue() != ParameterInt::kValueMin ||
            paramInt.MaxValue() != ParameterInt::kValueMax ||
            paramInt.Step()     != ParameterInt::kStep) {
            aWriter.Write(Brn("<allowedValueRange>"));
            aWriter.Write(Brn("<minimum>"));
            WriterAscii writerAscii(aWriter);
            writerAscii.WriteInt(paramInt.MinValue());
            aWriter.Write(Brn("</minimum>"));
            aWriter.Write(Brn("<maximum>"));
            writerAscii.WriteInt(paramInt.MaxValue());
            aWriter.Write(Brn("</maximum>"));
            aWriter.Write(Brn("<step>"));
            writerAscii.WriteInt(paramInt.Step());
            aWriter.Write(Brn("</step>"));
            aWriter.Write(Brn("</allowedValueRange>"));
            }
    }
        break;
    case OpenHome::Net::Parameter::eTypeUint:
    {
        const OpenHome::Net::ParameterUint& paramUint = static_cast<const OpenHome::Net::ParameterUint&>(aParam);
        if (paramUint.MinValue() != ParameterUint::kValueMin ||
            paramUint.MaxValue() != ParameterUint::kValueMax ||
            paramUint.Step()     != ParameterUint::kStep) {
            aWriter.Write(Brn("<allowedValueRange>"));
            aWriter.Write(Brn("<minimum>"));
            WriterAscii writerAscii(aWriter);
            writerAscii.WriteUint(paramUint.MinValue());
            aWriter.Write(Brn("</minimum>"));
            aWriter.Write(Brn("<maximum>"));
            writerAscii.WriteUint(paramUint.MaxValue());
            aWriter.Write(Brn("</maximum>"));
            aWriter.Write(Brn("<step>"));
            writerAscii.WriteUint(paramUint.Step());
            aWriter.Write(Brn("</step>"));
            aWriter.Write(Brn("</allowedValueRange>"));
            }
    }
        break;
    case OpenHome::Net::Parameter::eTypeString:
    {
        const OpenHome::Net::ParameterString& paramStr = static_cast<const OpenHome::Net::ParameterString&>(aParam);
        const ParameterString::Map& allowedVals = paramStr.AllowedValues();
        if (allowedVals.size() > 0) {
            aWriter.Write(Brn("<allowedValueList>"));
            ParameterString::Map::const_iterator it = allowedVals.begin();
            while (it != allowedVals.end()) {
                aWriter.Write(Brn("<allowedValue>"));
                aWriter.Write(*(it->second));
                aWriter.Write(Brn("</allowedValue>"));
                it++;
            }
            aWriter.Write(Brn("</allowedValueList>"));
        }
    }
        break;
    case OpenHome::Net::Parameter::eTypeRelated:
        ASSERTS();
        break;
    }
    aWriter.Write(Brn("</stateVariable>"));
}

void DviProtocolUpnpServiceXmlWriter::WriteTechnicalStateVariables(IWriter& aWriter, const Action* aAction, const Action::VectorParameters& aParams)
{
    for (TUint i=0; i<aParams.size(); i++) {
        if (aParams[i]->Type() != OpenHome::Net::Parameter::eTypeRelated) {
            WriteStateVariable(aWriter, *(aParams[i]), false, aAction);
        }
    }
}
