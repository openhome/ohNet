#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/PowerManager.h>
#include <OpenHome/Av/Source.h>

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
    virtual void NotifySourceNameChanged(ISource& aSource) = 0;
};

class IProductObserver
{
public:
    virtual ~IProductObserver() {}
    virtual void Started() = 0;
    virtual void RoomChanged() = 0;
    virtual void NameChanged() = 0;
    virtual void StandbyChanged() = 0;
    virtual void SourceIndexChanged() = 0;
    virtual void SourceXmlChanged() = 0;
};

class DummySourceDefault : public ISource
{
private:
    static const Brn kName;
public: // from ISource
    const Brx& SystemName() const override;
    const Brx& Type() const override;
    void Name(Bwx& aBuf) const override;
    TBool IsVisible() const override;
    void Activate() override;
    void Deactivate() override;
    void SetVisible(TBool aVisible) override;
    void PipelineStopped() override;
    void Initialise(IProduct& aProduct, Configuration::IConfigInitialiser& aConfigInit, Configuration::IConfigManager& aConfigManagerReader, TUint aId) override;
};

class StartupSourceMapper : public Configuration::IConfigChoiceMapper
{
private:
    typedef std::pair<TUint, ISource*> ChoiceSourcePair;
public:
    void AddSource(TUint aChoice, ISource& aSource);
public: // from StartupSourceMapper
    void Write(IWriter& aWriter, Configuration::IConfigChoiceMappingWriter& aMappingWriter) override;
private:
    std::vector<ChoiceSourcePair> iSources;
};

class ConfigStartupSource
{
public:
    static const Brn kKeySource;
    static const TUint kDefault = 0;
public:
    ConfigStartupSource(Configuration::IConfigInitialiser& aConfigInit, const std::vector<ISource*> aSources);
    ~ConfigStartupSource();
    TUint Subscribe(Configuration::ConfigChoice::FunctorConfigChoice aFunctor);
    void Unsubscribe(TUint aId);
    TUint SourceIndex(TUint aChoiceId) const;
private:
    DummySourceDefault iDummySource;
    StartupSourceMapper iMapper;
    Configuration::ConfigChoice* iChoice;
    TUint iSourceCount;
};

class Product : private IProduct, private Media::IInfoProvider, private INonCopyable
{
private:
    static const Brn kKeyLastSelectedSource;
    static const TUint kMaxAttributeBytes = 1024;
public:
    static const Brn kConfigIdRoomBase;
    static const Brn kConfigIdNameBase;
    static const TUint kMaxNameBytes = 20;
    static const TUint kMaxRoomBytes = 20;
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
    TBool StandbyEnabled() const;
    void SetStandby(TBool aStandby);
    TUint SourceCount() const;
    TUint CurrentSourceIndex() const;
    void GetSourceXml(Bwx& aXml);
    void SetCurrentSource(TUint aIndex);
    void SetCurrentSource(const Brx& aName);
    void GetSourceDetails(TUint aIndex, Bwx& aSystemName, Bwx& aType, Bwx& aName, TBool& aVisible);
    const Brx& Attributes() const; // not thread-safe.  Assumes attributes are all set on a single thread during startup
    TUint SourceXmlChangeCount();
private:
    void AppendTag(Bwx& aXml, const TChar* aTag, const Brx& aValue);
    void GetConfigText(const Brx& aId, Bwx& aDest, const Brx& aDefault);
    void ProductRoomChanged(Configuration::KeyValuePair<const Brx&>& aKvp);
    void ProductNameChanged(Configuration::KeyValuePair<const Brx&>& aKvp);
    void StartupSourceChanged(Configuration::KeyValuePair<TUint>& aKvp);
private: // from IProduct
    void Activate(ISource& aSource) override;
    void NotifySourceNameChanged(ISource& aSource) override;
private: // from Media::IInfoProvider
    void QueryInfo(const Brx& aQuery, IWriter& aWriter) override;
private:
    Net::DvDevice& iDevice; // do we need to store this?
    IReadStore& iReadStore;
    Configuration::IConfigManager& iConfigReader;
    Configuration::IConfigInitialiser& iConfigInit;
    mutable Mutex iLock;
    Mutex iLockDetails;
    ProviderProduct* iProviderProduct;
    std::vector<IProductObserver*> iObservers;
    std::vector<ISource*> iSources;
    Bws<kMaxAttributeBytes> iAttributes;
    TBool iStarted;
    TBool iStandby;
    StoreText* iLastSelectedSource;
    TUint iCurrentSource;
    TUint iSourceXmlChangeCount; // FIXME - isn't updated when source names/visibility change
    Configuration::ConfigText* iConfigProductRoom;
    Configuration::ConfigText* iConfigProductName;
    Bws<kMaxRoomBytes> iProductRoom;
    TUint iListenerIdProductRoom;
    Bws<kMaxNameBytes> iProductName;
    TUint iListenerIdProductName;
    ConfigStartupSource* iConfigStartupSource;
    TUint iListenerIdStartupSource;
    TUint iStartupSourceVal;
};

} // namespace Av
} // namespace OpenHome

