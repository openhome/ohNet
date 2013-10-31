#ifndef HEADER_PRODUCT
#define HEADER_PRODUCT

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/PowerManager.h>

#include <vector>

EXCEPTION(AvSourceNotFound);

namespace OpenHome {
namespace Configuration {
    class ConfigText;
    class IConfigurationManager;
    class IStoreReadWrite;
}
namespace Av {

class IReadStore;
class ISource;
class ProviderProduct;

class IProduct
{
public:
    virtual ~IProduct() {}
    virtual void Activate(ISource& aSource) = 0;
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

class Product : private IProduct, private IInfoProvider, private INonCopyable
{
    static const Brn kStartupSourceKey;
    static const TUint kMaxAttributeBytes = 1024;
public:
    static const Brn ConfigIdRoom;
    static const Brn ConfigIdName;
    static const TUint kMaxNameBytes = 20;
    static const TUint kMaxRoomBytes = 20;
public:
    Product(Net::DvDevice& aDevice, IReadStore& aReadStore, Configuration::IStoreReadWrite& aReadWriteStore, Configuration::IConfigurationManager& aConfigManager, IPowerManager& aPowerManager, IInfoAggregator& aInfoAggregator);
    ~Product();
    void SetObserver(IProductObserver& aObserver);
    void Start();
    void AddSource(ISource* aSource);
    void AddAttribute(const TChar* aAttribute);
    void AddAttribute(const Brx& aAttribute);
    void GetManufacturerDetails(Brn& aName, Brn& aInfo, Brn& aUrl, Brn& aImageUri);
    void GetModelDetails(Brn& aName, Brn& aInfo, Brn& aUrl, Brn& aImageUri);
    void GetProductDetails(Bwx& aRoom, Bwx& aName, Brn& aInfo, Brn& aImageUri);
    TBool StandbyEnabled() const;
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
    void ProductRoomChanged();
    void ProductNameChanged();
private: // from IProduct
    void Activate(ISource& aSource);
private: // from IInfoProvider
    void QueryInfo(const Brx& aQuery, IWriter& aWriter);
private:
    Net::DvDevice& iDevice; // do we need to store this?
    IReadStore& iReadStore;
    Configuration::IConfigurationManager& iConfigManager;
    Mutex iLock;
    ProviderProduct* iProviderProduct;
    IProductObserver* iObserver;
    std::vector<ISource*> iSources;
    Bws<kMaxAttributeBytes> iAttributes;
    TBool iStarted;
    StoreText iStartupSource;
    TUint iCurrentSource;
    TUint iSourceXmlChangeCount; // FIXME - isn't updated when source names/visibility change
    Configuration::ConfigText* iConfigProductRoom;
    Configuration::ConfigText* iConfigProductName;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PRODUCT
