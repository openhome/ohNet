#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/PowerManager.h>
#include <OpenHome/Av/Source.h>

#include <map>
#include <vector>

EXCEPTION(AvSourceNotFound);

namespace OpenHome {
namespace Av {

class IReadStore;
class ISource;
class ProviderProduct;

class IProduct
{
public:
    virtual ~IProduct() {}
    virtual void Activate(ISource& aSource) = 0;
    virtual void NotifySourceChanged(ISource& aSource) = 0;
};

class IProductNameObserver
{
public:
    virtual void RoomChanged(const Brx& aRoom) = 0;
    virtual void NameChanged(const Brx& aName) = 0;
    virtual ~IProductNameObserver() {}
};

class IProductNameObservable
{
public:
    virtual void AddNameObserver(IProductNameObserver& aObserver) = 0;
    virtual ~IProductNameObservable() {}
};

class IProductObserver
{
public:
    virtual ~IProductObserver() {}
    virtual void Started() = 0;
    virtual void SourceIndexChanged() = 0;
    virtual void SourceXmlChanged() = 0;
};

class ConfigStartupSource : private INonCopyable
{
public:
    static const Brn kKeySource;
    static const Brn kLastUsed;
public:
    ConfigStartupSource(Configuration::IConfigInitialiser& aConfigInit);
    ~ConfigStartupSource();
private:
    Configuration::ConfigText* iSourceStartup;
};

class Product : private IProduct
              , public IProductNameObservable
              , private IStandbyHandler
              , private Media::IInfoProvider
              , private INonCopyable
{
private:
    static const Brn kKeyLastSelectedSource;
    static const TUint kMaxAttributeBytes = 1024;
    static const TUint kCurrentSourceNone;
public:
    static const Brn kConfigIdRoomBase;
    static const Brn kConfigIdNameBase;
    static const Brn kConfigIdAutoPlay;
    static const TUint kAutoPlayDisable;
    static const TUint kAutoPlayEnable;
    static const TUint kMaxNameBytes = 20;
    static const TUint kMaxRoomBytes = 40;
    static const TUint kMaxSourceXmlBytes = 1024 * 3;
public:
    Product(Net::DvDevice& aDevice, IReadStore& aReadStore, Configuration::IStoreReadWrite& aReadWriteStore,
            Configuration::IConfigManager& aConfigReader, Configuration::IConfigInitialiser& aConfigInit,
            IPowerManager& aPowerManager);
    ~Product();
    void AddObserver(IProductObserver& aObserver);
    void Start();
    void Stop();
    void AddSource(ISource* aSource);
    void AddAttribute(const TChar* aAttribute);
    void AddAttribute(const Brx& aAttribute);
    void GetManufacturerDetails(Brn& aName, Brn& aInfo, Brn& aUrl, Brn& aImageUri);
    void GetModelDetails(Brn& aName, Brn& aInfo, Brn& aUrl, Brn& aImageUri);
    void GetProductDetails(Bwx& aRoom, Bwx& aName, Brn& aInfo, Brn& aImageUri);
    TUint SourceCount() const;
    TUint CurrentSourceIndex() const;
    void GetSourceXml(Bwx& aXml);
    void SetCurrentSource(TUint aIndex);
    void SetCurrentSource(const Brx& aName);
    void GetSourceDetails(TUint aIndex, Bwx& aSystemName, Bwx& aType, Bwx& aName, TBool& aVisible) const;
    void GetSourceDetails(const Brx& aSystemName, Bwx& aType, Bwx& aName, TBool& aVisible) const;
    const Brx& Attributes() const; // not thread-safe.  Assumes attributes are all set on a single thread during startup
    TUint SourceXmlChangeCount();
private:
    TBool DoSetCurrentSourceLocked(TUint aIndex); // returns true if aIndex wasn't already active
    TBool DoSetCurrentSource(TUint aIndex);
    TBool DoSetCurrentSource(const Brx& aName);
    void AppendTag(IWriter& aWriter, const TChar* aTag, const Brx& aValue);
    void GetConfigText(const Brx& aId, Bwx& aDest, const Brx& aDefault);
    void ProductRoomChanged(Configuration::KeyValuePair<const Brx&>& aKvp);
    void ProductNameChanged(Configuration::KeyValuePair<const Brx&>& aKvp);
    void StartupSourceChanged(Configuration::KeyValuePair<const Brx&>& aKvp);
    void AutoPlayChanged(Configuration::KeyValuePair<TUint>& aKvp);
private: // from IProduct
    void Activate(ISource& aSource) override;
    void NotifySourceChanged(ISource& aSource) override;
public: // from IProductNameObservable
    void AddNameObserver(IProductNameObserver& aObserver) override;
private: // from IStandbyHandler
    void StandbyEnabled() override;
    void StandbyDisabled(StandbyDisableReason aReason) override;
private: // from Media::IInfoProvider
    void QueryInfo(const Brx& aQuery, IWriter& aWriter) override;
private:
    Net::DvDevice& iDevice; // do we need to store this?
    IReadStore& iReadStore;
    Configuration::IConfigManager& iConfigReader;
    Configuration::IConfigInitialiser& iConfigInit;
    IPowerManager& iPowerManager;
    mutable Mutex iLock;
    Mutex iLockDetails;
    ProviderProduct* iProviderProduct;
    IStandbyObserver* iStandbyObserver;
    std::vector<IProductObserver*> iObservers;
    std::vector<IProductNameObserver*> iNameObservers;
    std::vector<ISource*> iSources;
    Bws<kMaxAttributeBytes> iAttributes;
    TBool iStarted;
    TBool iStandby;
    TBool iAutoPlay;
    StoreText* iLastSelectedSource;
    TUint iCurrentSource;
    TUint iSourceXmlChangeCount; // FIXME - isn't updated when source names/visibility change
    Configuration::ConfigText* iConfigProductRoom;
    Configuration::ConfigText* iConfigProductName;
    Bws<kMaxRoomBytes> iProductRoom;
    TUint iListenerIdProductRoom;
    Bws<kMaxNameBytes> iProductName;
    TUint iListenerIdProductName;
    Configuration::ConfigText* iConfigStartupSource;
    TUint iListenerIdStartupSource;
    Bws<ISource::kMaxSystemNameBytes> iStartupSourceVal;
    Configuration::ConfigChoice* iConfigAutoPlay;
    TUint iListenerIdAutoPlay;
};

class IFriendlyNameObservable
{
public:
    static const TUint kMaxFriendlyNameBytes = Product::kMaxRoomBytes+1+Product::kMaxNameBytes;
public:
    virtual TUint RegisterFriendlyNameObserver(FunctorGeneric<const Brx&> aObserver) = 0;
    virtual void DeregisterFriendlyNameObserver(TUint aId) = 0;
    virtual ~IFriendlyNameObservable() {}
};

class FriendlyNameManager : public IFriendlyNameObservable, public IProductNameObserver
{
public:
    FriendlyNameManager(IProductNameObservable& aProduct);
    ~FriendlyNameManager();
private: // from IFriendlyNameObservable
    TUint RegisterFriendlyNameObserver(FunctorGeneric<const Brx&> aObserver) override;
    void DeregisterFriendlyNameObserver(TUint aId) override;
private: // from IProductNameObserver
    void RoomChanged(const Brx& aRoom) override;
    void NameChanged(const Brx& aName) override;
private:
    void UpdateDetails();
    void ConstructFriendlyNameLocked();
    void NotifyObserversLocked();
private:
    Bws<Product::kMaxRoomBytes> iRoom;
    Bws<Product::kMaxNameBytes> iName;
    Bws<kMaxFriendlyNameBytes> iFriendlyName;
    TUint iNextObserverId;
    std::map<TUint, FunctorGeneric<const Brx&>> iObservers;
    Mutex iMutex;
};

} // namespace Av
} // namespace OpenHome
