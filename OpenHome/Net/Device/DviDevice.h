#ifndef HEADER_DVIDEVICE
#define HEADER_DVIDEVICE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/DvDevice.h>

#include <vector>
#include <map>

namespace OpenHome {
namespace Net {

class IDvProtocol : public IResourceManager
{
public:
    virtual const Brx& ProtocolName() const = 0;
    virtual void Enable() = 0;
    virtual void Disable(Functor& aComplete) = 0;
    virtual void GetAttribute(const TChar* aKey, const TChar** aValue) const = 0;
    virtual void SetAttribute(const TChar* aKey, const TChar* aValue) = 0;
    virtual void SetCustomData(const TChar* aTag, void* aData) = 0;
};

class DviSubscription;
class DviDevice : public IResourceManager
{
public:
    static const Brn kResourceDir;
public:
    DviDevice(const Brx& aUdn);
    void Destroy();
    void AddWeakRef();
    void RemoveWeakRef();
    const Brx& Udn() const;
    TBool Enabled() const;
    void SetEnabled();
    void SetDisabled(Functor aCompleted);
    void GetAttribute(const TChar* aKey, const TChar** aValue) const;
    void SetAttribute(const TChar* aKey, const TChar* aValue);
    void SetXmlExtension(const TChar* aXml);
    const Brx& XmlExtension() const;
    TUint ServiceCount() const;
    DviService& Service(TUint aIndex) const;
    void AddService(DviService* aService);
    void AddDevice(DviDevice* aDevice); // embedded device
    TUint DeviceCount() const;
    DviDevice& Device(TUint aIndex) const;
    TBool IsRoot() const;
    DviDevice* Root() const;
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter);
    void GetUriBase(Bwh& aUriBase, TIpAddress aInterface, TUint aPort, IDvProtocol& aProtocol);
    TUint ConfigId();
    void CreateSid(Brh& aSid);
    IResourceManager* ResourceManager();
    void SetCustomData(const TChar* aProtocol, const TChar* Tag, void* aData);
protected:
    DviDevice(const Brx& aUdn, IResourceManager& aResourceManager);
    ~DviDevice();
    void AddProtocol(IDvProtocol* aProtocol);
private:
    void Construct(const Brx& aUdn);
    void SetParent(DviDevice* aParent);
    void SetDisabled(Functor aCompleted, bool aLocked);
    void ProtocolDisabled();
    TBool HasService(const OpenHome::Net::ServiceType& aServiceType) const;
    TBool ChildHasService(const OpenHome::Net::ServiceType& aServiceType) const;
    void ConfigChanged();
    TUint SubscriptionId();
private:
    enum EEnableState
    {
        eDisabled
       ,eDisabling
       ,eEnabled
    };
private:
    mutable Mutex iLock;
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
    Functor iDisableComplete;
    Semaphore iShutdownSem;
    TUint iSubscriptionId;
    Brh iXmlExtension;
};

class DviDeviceStandard : public DviDevice
{
public:
    DviDeviceStandard(const Brx& aUdn);
    DviDeviceStandard(const Brx& aUdn, IResourceManager& aResourceManager);
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
    static void Add(DviDevice& aDevice);
    static void Remove(DviDevice& aDevice);
    static DviDevice* Find(const Brx& aUdn);
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter);
private:
    typedef std::map<Brn,DviDevice*,BufferCmp> Map;
    Mutex iLock;
    Map iMap;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVIDEVICE
