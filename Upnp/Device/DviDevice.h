#ifndef HEADER_DVIDEVICE
#define HEADER_DVIDEVICE

#include <ZappTypes.h>
#include <Buffer.h>
#include <Thread.h>
#include <DviService.h>
#include <Functor.h>
#include <Core/DvDevice.h>

#include <vector>
#include <map>

namespace Zapp {

class IDvProtocol : public IResourceManager
{
public:
    virtual const Brx& ProtocolName() const = 0;
    virtual void Enable() = 0;
    virtual void Disable(Functor& aComplete) = 0;
    virtual void GetAttribute(const TChar* aKey, const TChar** aValue) const = 0;
    virtual void SetAttribute(const TChar* aKey, const TChar* aValue) = 0;
};

class DviSubscription;
class DviDevice : public IResourceManager
{
    static const TUint kNumProtocols = 1;
public:
    static const Brn kResourceDir;
public:
    DviDevice(const Brx& aUdn);
    DviDevice(const Brx& aUdn, IResourceManager& aResourceManager);
    void Destroy();
    void AddWeakRef();
    void RemoveWeakRef();
    const Brx& Udn() const;
    TBool Enabled() const;
    void SetEnabled();
    void SetDisabled(Functor aCompleted);
    void GetAttribute(const TChar* aKey, const TChar** aValue) const;
    void SetAttribute(const TChar* aKey, const TChar* aValue);
    TUint ServiceCount() const;
    DviService& Service(TUint aIndex) const;
    void AddService(DviService* aService);
    void AddDevice(DviDevice* aDevice); // embedded device
    TUint DeviceCount() const;
    DviDevice& Device(TUint aIndex) const;
    TBool IsRoot() const;
    DviDevice* Root() const;
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter);
    void GetUriBase(Bwh& aUriBase, TIpAddress aInterface, TUint aPort, IDvProtocol& aProtocol);
    TUint ConfigId();
    void CreateSid(Brh& aSid);
    IResourceManager* ResourceManager();
private:
    ~DviDevice();
    void Construct(const Brx& aUdn);
    void SetParent(DviDevice* aParent);
    void ProtocolDisabled();
    TBool HasService(const Zapp::ServiceType& aServiceType) const;
    TBool ChildHasService(const Zapp::ServiceType& aServiceType) const;
    void ConfigChanged();
    TUint SubscriptionId();
private:
    mutable Mutex iLock;
    TUint iRefCount;
    Brhz iUdn;
    TBool iEnabled;
    TUint iConfigId;
    TBool iConfigUpdated;
    DviDevice* iParent;
    std::vector<DviService*> iServices;
    std::vector<DviDevice*> iDevices;
    IDvProtocol* iProtocols[kNumProtocols];
    IResourceManager* iResourceManager;
    TUint iProtocolDisableCount;
    Functor iDisableComplete;
    Semaphore iShutdownSem;
    TUint iSubscriptionId;
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
    static void Add(DviDevice& aDevice);
    static void Remove(DviDevice& aDevice);
    static DviDevice* Find(const Brx& aUdn);
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter);
private:
    typedef std::map<Brn,DviDevice*,BufferCmp> Map;
    Mutex iLock;
    Map iMap;
};

} // namespace Zapp

#endif // HEADER_DVIDEVICE
