#ifndef HEADER_DVIDEVICE
#define HEADER_DVIDEVICE

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <vector>
#include <map>

namespace OpenHome {
namespace Net {

class IDvProtocol;
class DviDevice;

class IDvProtocolFactory
{
public:
    virtual IDvProtocol* CreateProtocol(DviDevice& aDevice) = 0;
    virtual ~IDvProtocolFactory() {}
};

class IDvProtocol : public IResourceManager
{
public:
    virtual const Brx& ProtocolName() const = 0;
    virtual void Enable() = 0;
    virtual void Disable(Functor& aComplete) = 0;
    virtual void SendAnnouncements() = 0;
    virtual void GetAttribute(const TChar* aKey, const TChar** aValue) const = 0;
    virtual void SetAttribute(const TChar* aKey, const TChar* aValue) = 0;
    virtual void SetCustomData(const TChar* aTag, void* aData) = 0;
    virtual void GetResourceManagerUri(const NetworkAdapter& aAdapter, Brh& aUri) = 0;
};

class DviSubscription;
class DviProviderSubscriptionLongPoll;
class DvStack;

class DviDevice : public IResourceManager, private IStackObject
{
public:
    static const Brn kResourceDir;
public:
    DviDevice(DvStack& aDvStack, const Brx& aUdn);
    void Destroy();
    void AddWeakRef();
    void RemoveWeakRef();
    const Brx& Udn() const;
    TBool Enabled() const;
    void SetEnabled();
    void SetDisabled(Functor aCompleted);
    void SendAnnouncements();
    void GetAttribute(const TChar* aKey, const TChar** aValue) const;
    void SetAttribute(const TChar* aKey, const TChar* aValue);
    TUint ServiceCount() const;
    DviService& Service(TUint aIndex) const;
    DviService* ServiceReference(const ServiceType& aServiceType);
    DviService* ServiceReference(const Brx& aServiceName);
    void AddService(DviService* aService);
    void AddDevice(DviDevice* aDevice); // embedded device
    TUint DeviceCount() const;
    DviDevice& Device(TUint aIndex) const;
    TBool IsRoot() const;
    DviDevice* Root() const;
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter);
    void GetUriBase(Bwx& aUriBase, TIpAddress aInterface, TUint aPort, IDvProtocol& aProtocol);
    TUint ConfigId();
    void CreateSid(Brh& aSid);
    IResourceManager* ResourceManager();
    DvStack& GetDvStack();
    void SetCustomData(const TChar* aProtocol, const TChar* Tag, void* aData);
    void GetResourceManagerUri(const NetworkAdapter& aAdapter, Brh& aUri);
protected:
    DviDevice(OpenHome::Net::DvStack& aDvStack, const Brx& aUdn, IResourceManager& aResourceManager);
    ~DviDevice();
    void AddProtocol(IDvProtocol* aProtocol);
private:
    void Construct(const Brx& aUdn);
    void SetParent(DviDevice* aParent);
    void SetEnabledLocked();
    void SetDisabled(Functor aCompleted, bool aLocked);
    void ProtocolDisabled();
    TBool HasService(const OpenHome::Net::ServiceType& aServiceType) const;
    TBool ChildHasService(const OpenHome::Net::ServiceType& aServiceType) const;
    void ConfigChanged();
    TUint SubscriptionId();
private: // from IStackObject
    void ListObjectDetails() const;
private:
    enum EEnableState
    {
        eDisabled
       ,eDisabling
       ,eEnabled
    };
protected:
    OpenHome::Net::DvStack& iDvStack;
private:
    mutable Mutex iLock;
    Mutex iServiceLock;
    TUint iRefCount;
    Brhz iUdn;
    EEnableState iEnabled;
    TUint iConfigId;
    TBool iConfigUpdated;
    DviDevice* iParent;
    std::vector<DviService*> iServices;
    std::vector<DviDevice*> iDevices;
    std::vector<IDvProtocol*> iProtocols;
    IResourceManager* iResourceManager;
    TUint iProtocolDisableCount;
    std::vector<Functor> iDisableComplete;
    Mutex iDisableLock;
    Semaphore iShutdownSem;
    TUint iSubscriptionId;
    DviProviderSubscriptionLongPoll* iProviderSubscriptionLongPoll;
};

/**
 * Utility class.
 *
 * Create an AutoDeviceRef on the stack using a reference to a DviDevice. It will
 * automatically call RemoveWeakRef on stack cleanup (ie on return or when an
 * exception passes up).
 */
class AutoDeviceRef : public INonCopyable
{
public:
    AutoDeviceRef(DviDevice*& aDevice);
    ~AutoDeviceRef();
private:
    DviDevice*& iDevice;
};

class DviDeviceStandard : public DviDevice
{
public:
    DviDeviceStandard(OpenHome::Net::DvStack& aDvStack, const Brx& aUdn);
    DviDeviceStandard(OpenHome::Net::DvStack& aDvStack, const Brx& aUdn, IResourceManager& aResourceManager);
private:
    void Construct();
};

class AttributeMap
{
public:
    AttributeMap();
    ~AttributeMap();
    const TChar* Get(const TChar* aKey) const;
    void Set(const TChar* aKey, const TChar* aValue);
private:
    class Attribute
    {
    public:
        Attribute(const TChar* aKey, const TChar* aValue);
        Brn Key() const;
        const TChar* Value() const;
        void UpdateValue(const TChar* aValue);
    private:
        Brh  iKey;
        Brhz iValue;
    };
private:
    typedef std::map<Brn,Attribute*,BufferCmp> Map;
    Map iMap;
    mutable Mutex iLock;
};

class DviDeviceMap : public IResourceManager
{
public:
    DviDeviceMap();
    ~DviDeviceMap();
    void Add(DviDevice& aDevice);
    void Remove(DviDevice& aDevice);
    DviDevice* Find(const Brx& aUdn);
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter);
    std::map<Brn,DviDevice*,BufferCmp> CopyMap() const;
    void ClearMap(std::map<Brn, DviDevice*, BufferCmp>& aMap);
private:
    typedef std::map<Brn,DviDevice*,BufferCmp> Map;
    Mutex iLock;
    Map iMap;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVIDEVICE
