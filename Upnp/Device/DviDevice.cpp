#include <DviDevice.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Parser.h>
#include <Printer.h>
#include <DviDeviceUpnp.h> // for DviDeviceUpnp ctor only
#include <DviStack.h>

using namespace Zapp;

// DviDevice

const Brn DviDevice::kResourceDir("resource");

DviDevice::DviDevice(const Brx& aUdn)
    : iLock("DDVM")
    , iResourceManager(NULL)
    , iShutdownSem("DVSD", 1)
{
    Construct(aUdn);
}

DviDevice::DviDevice(const Brx& aUdn, IResourceManager& aResourceManager)
    : iLock("DDVM")
    , iResourceManager(&aResourceManager)
    , iShutdownSem("DVSD", 1)
{
    Construct(aUdn);
}

void DviDevice::Construct(const Brx& aUdn)
{
    iRefCount = 1;
    iUdn.Set(aUdn);
    iEnabled = false;
    iConfigId = 0;
    iConfigUpdated = false;
    iParent = NULL;
    iProtocolDisableCount = 0;
    iSubscriptionId = 0;
    iProtocols[0] = new DviDeviceUpnp(*this);
    DviDeviceMap::Add(*this);
}

DviDevice::~DviDevice()
{
    DviDeviceMap::Remove(*this);
    delete iProtocols[0];
    for (TUint i=0; i<iServices.size(); i++) {
        iServices[i]->RemoveRef();;
    }
}

void DviDevice::Destroy()
{
    iLock.Wait();
    for (TUint i=0; i<iDevices.size(); i++) {
        iDevices[i]->Destroy();
    }
    iDevices.clear();
    if (iEnabled) {
        Functor blank;
        SetDisabled(blank);
    }
    iLock.Signal();
    iShutdownSem.Wait();
    RemoveWeakRef();
}

void DviDevice::AddWeakRef()
{
    iLock.Wait();
    iRefCount++;
    iLock.Signal();
}

void DviDevice::RemoveWeakRef()
{
    iLock.Wait();
    iRefCount--;
    TBool dead = (iRefCount == 0);
    iLock.Signal();
    if (dead) {
        delete this;
    }
}

const Brx& DviDevice::Udn() const
{
    return iUdn;
}

TBool DviDevice::Enabled() const
{
    iLock.Wait();
    TBool enabled = iEnabled;
    iLock.Signal();
    return enabled;
}

void DviDevice::SetEnabled()
{
    ASSERT(!iEnabled && iProtocolDisableCount == 0);
    iEnabled = true;
    iConfigUpdated = false;
    iShutdownSem.Clear();
    for (TUint i=0; i<kNumProtocols; i++) {
        iProtocols[i]->Enable();
		// queue updates for all service properties
		// nothing may have changed but individual subscriptions will spot this and skip any update message
		for (TUint j=0; j<iServices.size(); j++) {
			iServices[j]->PublishPropertyUpdates();
		}
    }
}

void DviDevice::SetDisabled(Functor aCompleted)
{
    ASSERT(iEnabled);
    iEnabled = false;
    iDisableComplete = aCompleted;
    iProtocolDisableCount = kNumProtocols;
    Functor functor = MakeFunctor(*this, &DviDevice::ProtocolDisabled);
    for (TUint i=0; i<kNumProtocols; i++) {
        iProtocols[i]->Disable(functor);
    }
}

void DviDevice::GetAttribute(const TChar* aKey, const TChar** aValue) const
{
    Brn key(aKey);
    Parser parser(key);
    Brn name = parser.Next('.');
    for (TUint i=0; i<kNumProtocols; i++) {
        IDvProtocol* protocol = iProtocols[i];
        if (protocol->ProtocolName() == name) {
            aKey += name.Bytes() + 1;
            protocol->GetAttribute(aKey, aValue);
            return;
        }
    }
    *aValue = NULL;
}

void DviDevice::SetAttribute(const TChar* aKey, const TChar* aValue)
{
    Brn key(aKey);
    Parser parser(key);
    Brn name = parser.Next('.');
    aKey += name.Bytes() + 1;
    // assume keys starting 'Test' are a special case which can be updated at any time
    if (strlen(aKey) <4 || strncmp(aKey, "Test", 4) != 0) {
        ASSERT(!iEnabled);
    }
    for (TUint i=0; i<kNumProtocols; i++) {
        IDvProtocol* protocol = iProtocols[i];
        if (protocol->ProtocolName() == name) {
            protocol->SetAttribute(aKey, aValue);
            ConfigChanged();
            break;
        }
    }
}

void DviDevice::AddService(DviService* aService)
{
    ASSERT(!iEnabled);
    ASSERT(!Root()->HasService(aService->ServiceType()));
    iServices.push_back(aService);
    ConfigChanged();
}

TUint DviDevice::ServiceCount() const
{
    return iServices.size();
}

DviService& DviDevice::Service(TUint aIndex) const
{
    ASSERT(aIndex < ServiceCount());
    return *(iServices[aIndex]);
}

void DviDevice::AddDevice(DviDevice* aDevice)
{
    ASSERT(!Enabled());
    iDevices.push_back(aDevice);
    aDevice->SetParent(this);
    ConfigChanged();
}

TUint DviDevice::DeviceCount() const
{
    return iDevices.size();
}

DviDevice& DviDevice::Device(TUint aIndex) const
{
    ASSERT(aIndex < DeviceCount());
    return *(iDevices[aIndex]);
}

TBool DviDevice::IsRoot() const
{
    DviDevice* root = Root();
    return (root == this);
}

void DviDevice::WriteResource(const Brx& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter)
{
    Parser parser(aUriTail);
    Brn dir = parser.Next('/');
    if (dir == kResourceDir) {
        if (iResourceManager != NULL) {
            iResourceManager->WriteResource(parser.Remaining(), aInterface, aResourceWriter);
        }
    }
    else {
        for (TUint i=0; i<kNumProtocols; i++) {
            IDvProtocol* protocol = iProtocols[i];
            if (protocol->ProtocolName() == dir) {
                protocol->WriteResource(parser.Remaining(), aInterface, aResourceWriter);
                break;
            }
        }
    }
}

void DviDevice::GetUriBase(Bwh& aUriBase, TIpAddress aInterface, TUint aPort, IDvProtocol& aProtocol)
{
    static const TUint kMaxAddressBytes = 21; // xxx.xxx.xxx.xxx:xxxxx
    const Brx& name = aProtocol.ProtocolName();
    aUriBase.Grow(Http::kUriPrefix.Bytes() + kMaxAddressBytes + iUdn.Bytes() + name.Bytes() + 3); // +2 for slashes after port, udn & name
    aUriBase.Append(Http::kUriPrefix);
    (void)Ascii::AppendDec(aUriBase, aInterface&0xff);
    aUriBase.Append('.');
    (void)Ascii::AppendDec(aUriBase, (aInterface>>8)&0xff);
    aUriBase.Append('.');
    (void)Ascii::AppendDec(aUriBase, (aInterface>>16)&0xff);
    aUriBase.Append('.');
    (void)Ascii::AppendDec(aUriBase, (aInterface>>24)&0xff);
    aUriBase.Append(':');
    (void)Ascii::AppendDec(aUriBase, aPort);
    aUriBase.Append('/');
    aUriBase.Append(iUdn);
    aUriBase.Append('/');
    aUriBase.Append(name);
    aUriBase.Append('/');
}

TUint DviDevice::ConfigId()
{
    return iConfigId;
}

void DviDevice::CreateSid(Brh& aSid)
{
    Bwh sid(iUdn.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1);
    sid.Append(iUdn);
    sid.Append('-');
    Bws<Ascii::kMaxUintStringBytes> buf;
    iLock.Wait();
    (void)Ascii::AppendDec(buf, iSubscriptionId++);
    iLock.Signal();
    sid.Append(buf);
    sid.PtrZ();
    sid.TransferTo(aSid);
}

IResourceManager* DviDevice::ResourceManager()
{
    return iResourceManager;
}

void DviDevice::SetParent(DviDevice* aParent)
{
    ASSERT(!Enabled());
    ASSERT(this != aParent);
    ASSERT(this != aParent->Root());
    iParent = aParent;
}

DviDevice* DviDevice::Root() const
{
    const DviDevice* root = this;
    while (root->iParent != NULL) {
        root = root->iParent;
    }
    return const_cast<DviDevice*>(root);
}

void DviDevice::ProtocolDisabled()
{
    iLock.Wait();
    ASSERT(iProtocolDisableCount != 0);
    if (--iProtocolDisableCount == 0) {
        if (iDisableComplete) {
            iDisableComplete();
        }
        iShutdownSem.Signal();
    }
    iLock.Signal();
}

TBool DviDevice::HasService(const Zapp::ServiceType& aServiceType) const
{
    for (TUint i=0; i<iServices.size(); i++) {
        const Zapp::ServiceType& serviceType = iServices[i]->ServiceType();
        if (serviceType.Version() == aServiceType.Version() &&
            serviceType.Domain()  == aServiceType.Domain() &&
            serviceType.Name()    == aServiceType.Name()) {
            return true;
        }
    }
    return ChildHasService(aServiceType);
}

TBool DviDevice::ChildHasService(const Zapp::ServiceType& aServiceType) const
{
    for (TUint i=0; i<iDevices.size(); i++) {
        if (iDevices[i]->HasService(aServiceType)) {
            return true;
        }
    }
    return false;
}

void DviDevice::ConfigChanged()
{
    if (!iConfigUpdated) {
        iConfigId++;
        iConfigUpdated = true;
    }
}

TUint DviDevice::SubscriptionId()
{
    iLock.Wait();
    TUint id = iSubscriptionId++;
    iLock.Signal();
    return id;
}


// AttributeMap

AttributeMap::AttributeMap()
    : iLock("ATRM")
{
}

AttributeMap::~AttributeMap()
{
    Map::iterator it = iMap.begin();
    while (it != iMap.end()) {
        delete it->second;
        it++;
    }
}

const TChar* AttributeMap::Get(const TChar* aKey) const
{
    AutoMutex a(iLock);
    Brn key(aKey);
    Map::const_iterator it = iMap.find(key);
    if (it == iMap.end()) {
        return NULL;
    }
    AttributeMap::Attribute* attr = it->second;
    return attr->Value();
}

void AttributeMap::Set(const TChar* aKey, const TChar* aValue)
{
    iLock.Wait();
    Brn key(aKey);
    Map::iterator it = iMap.find(key);
    if (it != iMap.end()) {
        it->second->UpdateValue(aValue);
    }
    else {
        AttributeMap::Attribute* attr = new AttributeMap::Attribute(aKey, aValue);
        iMap.insert(std::pair<Brn, AttributeMap::Attribute*>(attr->Key(), attr));
    }
    iLock.Signal();
}


// AttributeMap::Attribute

AttributeMap::Attribute::Attribute(const TChar* aKey, const TChar* aValue)
    : iKey(aKey)
    , iValue(aValue)
{
}

Brn AttributeMap::Attribute::Key() const
{
	Brn buf(iKey);
	return buf;
}

const TChar* AttributeMap::Attribute::Value() const
{
    return iValue.CString();
}

void AttributeMap::Attribute::UpdateValue(const TChar* aValue)
{
    iValue.Set(aValue);
}


// DviDeviceMap

DviDeviceMap::DviDeviceMap()
    : iLock("DVDM")
{
}

DviDeviceMap::~DviDeviceMap()
{
    ASSERT(iMap.size() == 0);
}

void DviDeviceMap::Add(DviDevice& aDevice)
{
    DviDeviceMap& self = DviStack::DeviceMap();
    self.iLock.Wait();
    Brn udn(aDevice.Udn());
    self.iMap.insert(std::pair<Brn,DviDevice*>(udn, &aDevice));
    self.iLock.Signal();
}

void DviDeviceMap::Remove(DviDevice& aDevice)
{
    DviDeviceMap& self = DviStack::DeviceMap();
    self.iLock.Wait();
    Brn udn(aDevice.Udn());
    Map::iterator it = self.iMap.find(udn);
    if (it != self.iMap.end()) {
        self.iMap.erase(it);
    }
    self.iLock.Signal();
}

DviDevice* DviDeviceMap::Find(const Brx& aUdn)
{
    DviDevice* device = NULL;
    DviDeviceMap& self = DviStack::DeviceMap();
    self.iLock.Wait();
    Brn udn(aUdn);
    Map::iterator it = self.iMap.find(udn);
    if (it != self.iMap.end()) {
        device = it->second;
    }
    self.iLock.Signal();
    return device;
}

void DviDeviceMap::WriteResource(const Brx& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter)
{
    AutoMutex a(iLock);
    Parser parser(aUriTail);
    (void)parser.Next('/'); // skip leading slash
    Brn dir = parser.Next('/');
    if (dir.Bytes() > 0) {
        Map::iterator it = iMap.find(dir);
        if (it != iMap.end()) {
            it->second->WriteResource(parser.Remaining(), aInterface, aResourceWriter);
        }
    }
}
