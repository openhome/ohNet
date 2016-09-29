#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Web/WebAppFramework.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Standard.h>

EXCEPTION(LanguageResourceInvalid);
EXCEPTION(JsonStringError);

namespace OpenHome {
namespace Av {
    class IRebootHandler;
}
namespace Media {
    class IInfoAggregator;
}
namespace Web {

class IResourceFileConsumer;

// FIXME - how to deallocate this resource reader?
class ILanguageResourceReader
{
public:
    virtual void SetResource(const Brx& aUriTail) = 0;
    virtual TBool Allocated() const = 0;
    virtual void Process(const Brx& aKey, IResourceFileConsumer& aResourceConsumer) = 0;
    virtual ~ILanguageResourceReader() {}
};

class ILanguageResourceManager
{
public:
    virtual ILanguageResourceReader& CreateLanguageResourceHandler(const Brx& aResourceUriTail, std::vector<Bws<10>>& aLanguageList) = 0;  // THROWS LanguageResourceInvalid
    virtual ~ILanguageResourceManager() {}
};

class IWritable
{
public:
    virtual void Write(IWriter& aWriter) const = 0;
    virtual ~IWritable() {}
};

/**
 * Dummy writable that writes an empty object out.
 */
class WritableJsonEmpty : public IWritable
{
public: // from IWritable
    void Write(IWriter& aWriter) const override;
};

class JsonWriterBool : private INonCopyable
{
public:
    JsonWriterBool(IWriter& aWriter);
    void Write(TBool aValue) const;
private:
    IWriter& iWriter;
};

class JsonWriterString : private INonCopyable
{
public:
    JsonWriterString(IWriter& aWriter);
    void Write(const Brx& aValue) const;
private:
    IWriter& iWriter;
};

class JsonWriterReboot : private INonCopyable
{
public:
    JsonWriterReboot(TBool aRebootRequired = false);
    void Write(IWriter& aWriter) const;
private:
    static void WriteBool(IWriter& aWriter, TBool aValue);
private:
    const TBool iRebootRequired;
};

class WritableJsonInfo : public IWritable, private INonCopyable
{
public:
    WritableJsonInfo(TBool aRebootRequired = false);
public: //from IWritable
    void Write(IWriter& aWriter) const override;
private:
    const TBool iRebootRequired;
};

class IConfigUiVal;

class IConfigMessageAllocator
{
public:
    virtual ITabMessage* AllocateMessage(IConfigUiVal& aUiVal, const Brx& aUpdatedVal, std::vector<Bws<10>>& aLanguageList) = 0;
    virtual ~IConfigMessageAllocator() {}
};

// FIXME - why not just reuse IWritable?
class IConfigUiUpdateWriter
{
public:
    virtual void WriteValueJson(IWriter& aWriter) = 0;
    virtual ~IConfigUiUpdateWriter() {}
};

class ConfigMessageBase : public Media::Allocated, public ITabMessage, public IConfigUiUpdateWriter, public INonCopyable
{
protected:
    ConfigMessageBase(Media::AllocatorBase& aAllocator);
protected: // from Allocated
    void Clear() override;
private: // from ITabMessage
    virtual void Send(IWriter& aWriter) override = 0;
    void Destroy() override;
private: // from IConfigUiUpdateWriter
    virtual void WriteValueJson(IWriter& aWriter) override = 0;
};

class ConfigChoiceMappingWriterJson : public Configuration::IConfigChoiceMappingWriter, private INonCopyable
{
public:
    ConfigChoiceMappingWriterJson();
public: // from IConfigChoiceMappingWriter
    void Write(IWriter& aWriter, TUint aChoice, const Brx& aMapping) override;
    void WriteComplete(IWriter& aWriter) override;
private:
    TBool iStarted;
};

class IResourceFileConsumer
{
public:
    virtual ~IResourceFileConsumer() {}
    virtual TBool ProcessLine(const Brx& aLine) = 0; // true => continue (more lines required)
};

class ConfigChoiceMapperResourceFile : public IResourceFileConsumer,
                                       private INonCopyable
{
public:
    ConfigChoiceMapperResourceFile(const Brx& aKey,
                                   const std::vector<TUint>& aChoices,
                                   IWriter& aWriter,
                                   Configuration::IConfigChoiceMappingWriter& aMappingWriter);
private: // from IResourceFileConsumer
    TBool ProcessLine(const Brx& aLine) override;
private:
    const Brx& iKey;
    const std::vector<TUint>& iChoices;
    IWriter& iWriter;
    Configuration::IConfigChoiceMappingWriter& iMappingWriter;
    TUint iChoicesIndex;
    TBool iFoundKey;
};

class ConfigMessage : public ConfigMessageBase
{
    friend class ConfigMessageAllocator;
private:
    static const TUint kMaxBytes = Configuration::ConfigText::kMaxBytes;
public:
    ConfigMessage(Media::AllocatorBase& aAllocator);
private:
    void Set(IConfigUiVal& aUiVal, const Brx& aUpdatedVal, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList);
private: // from ConfigMessageBase
    void Clear() override;
    void Send(IWriter& aWriter) override;
    void WriteValueJson(IWriter& aWriter) override;
private:
    IConfigUiVal* iUiVal;
    Bws<kMaxBytes> iUpdatedVal;
    ILanguageResourceManager* iLanguageResourceManager;
    std::vector<Bws<10>>* iLanguageList;
};

// FIXME - correct to pass lang resource manager in via constructor, but then pass individual lang vectors in on Allocate()?
class ConfigMessageAllocator : public IConfigMessageAllocator
{
public:
    ConfigMessageAllocator(Media::IInfoAggregator& aInfoAggregator, TUint aMsgCount, ILanguageResourceManager& aLanguageResourceManager);
public: // from IConfigMessageAllocator
    ITabMessage* AllocateMessage(IConfigUiVal& aUiVal, const Brx& aUpdatedVal, std::vector<Bws<10>>& aLanguageList) override;
private:
    Media::Allocator<ConfigMessage> iAllocatorMsg;
    ILanguageResourceManager& iLanguageResourceManager;
};

class JsonStringParser
{
public:
    static Brn ParseString(const Brx& aBuffer, Brn& aRemaining);
};

/**
 * Abstract class that will receive a string message and attempt to parse it
 * into one or more key-value pair messages.
 */
class ConfigTabReceiver : public ITab
{
protected:
    ConfigTabReceiver();
    virtual void Receive(const Brx& aKey, const Brx& aValue) = 0;
    virtual void Reboot() = 0;
public: // from ITab
    void Receive(const Brx& aMessage) override;
    virtual void Destroy() override = 0;
};

class IConfigUiVal;

class IConfigUiValObserver
{
public:
    virtual void ValueChanged(IConfigUiVal& aUiVal, const Brx& aUpdatedVal) = 0;
    virtual ~IConfigUiValObserver() {}
};

class ConfigTab : public ConfigTabReceiver, public IConfigUiValObserver, public INonCopyable
{
private:
    static const TUint kInvalidSubscription;
    typedef std::pair<IConfigUiVal*, TUint> SubscriptionPair;   // Not taking ownership.
    typedef std::vector<SubscriptionPair> SubscriptionVector;
public:
    ConfigTab(TUint aId, IConfigMessageAllocator& aMessageAllocator, Configuration::IConfigManager& aConfigManager, Av::IRebootHandler& aRebootHandler);
    ~ConfigTab();
    void AddValue(IConfigUiVal& aValue);    // aValue must persist for lifetime of this object.
    void Start();
    TBool Allocated() const;
    void SetHandler(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList);
private: // from ConfigTabReceiver
    void Receive(const Brx& aKey, const Brx& aValue) override;
    void Reboot() override;
    void Destroy() override;
private: // from IConfigUiValObserver
    void ValueChanged(IConfigUiVal& aUiVal, const Brx& aUpdatedVal) override;
private:
    const TUint iId;
    Configuration::IConfigManager& iConfigManager;
    IConfigMessageAllocator& iMsgAllocator;
    Av::IRebootHandler& iRebootHandler;
    ITabHandler* iHandler;
    TBool iStarted;
    SubscriptionVector iConfigUiVals;
    std::vector<Bws<10>> iLanguageList;
};

class IConfigApp : public IWebApp
{
public: // from IWebApp
    virtual ITab& Create(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList) override = 0;
    virtual const Brx& ResourcePrefix() const override = 0;
    virtual IResourceHandler& CreateResourceHandler(const Brx& aResource) override = 0;
public:
    virtual ~IConfigApp() {}
};

class IConfigAppResourceHandlerFactory
{
public:
    virtual ~IConfigAppResourceHandlerFactory() {}
    virtual IResourceHandler* NewResourceHandler(const Brx& aResourceDir) = 0;
    virtual ILanguageResourceReader* NewLanguageReader(const Brx& aResourceDir) = 0;
};

class IConfigUiVal
{
public:
    virtual void WriteJson(IWriter& aWriter, IConfigUiUpdateWriter& aValWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) = 0;   // THROWS WriterError
    virtual TUint AddObserver(IConfigUiValObserver& aObserver) = 0;
    virtual void RemoveObserver(TUint aObserverId) = 0;
    virtual ~IConfigUiVal() {}
};

class ConfigUiValBase : public IConfigUiVal, private INonCopyable
{
private:
    static const TUint kObserverIdInvalid = 0;
    typedef std::map<TUint, IConfigUiValObserver*> Map;
protected:
    static const TUint kMaxValueBytes = 512;
protected:
    ConfigUiValBase(const IWritable& aAdditionalJson);
    void ValueChanged(const Brx& aValue);
    virtual void ObserverAdded(IConfigUiValObserver& aObserver) = 0;

    virtual void WriteKey(IWriter& aWriter) = 0;
    virtual void WriteType(IWriter& aWriter) = 0;
    virtual void WriteMeta(IWriter& aWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) = 0;
    virtual void WriteHidden(IWriter& aWriter); // Writes "false" by default. Override to write "true".
private:
    void WriteAdditional(IWriter& aWriter);
public: // from IConfigUiVal
    void WriteJson(IWriter& aWriter, IConfigUiUpdateWriter& aValWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
    TUint AddObserver(IConfigUiValObserver& aObserver) override;
    void RemoveObserver(TUint aObserverId) override;
protected:
    Map iObservers; // Not taking ownership.
private:
    const IWritable& iAdditionalJson;
    TUint iNextObserverId;
    Mutex iLockObservers;
};

class ConfigUiValRoBase : public ConfigUiValBase
{
public:
    ConfigUiValRoBase(const Brx& aKey);
private: // from ConfigUiValBase
    void WriteKey(IWriter& aWriter) override;
    void WriteType(IWriter& aWriter) override;
    void WriteMeta(IWriter& aWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
private:
    WritableJsonEmpty iAdditional;
    const Bwh iKey;
};

class ConfigUiValRo : public ConfigUiValRoBase
{
public:
    ConfigUiValRo(const Brx& aKey, Brn aValue);
private: // from ConfigUiValRoBase
    void ObserverAdded(IConfigUiValObserver& aObserver) override;
private:
    const Brn iValue;
    Bws<kMaxValueBytes> iJsonValue;
};

class ConfigUiValRoList : public OpenHome::Web::ConfigUiValRoBase
{
public:
    ConfigUiValRoList(const OpenHome::Brx& aKey, OpenHome::Brn aValue);
private: // from ConfigUiValRo
    void ObserverAdded(IConfigUiValObserver& aObserver) override;
    void WriteType(OpenHome::IWriter& aWriter) override;
private:
    const Brn iValue;
};

class ConfigUiValRoUpdatable : public ConfigUiValRoBase
{
public:
    ConfigUiValRoUpdatable(const Brx& aKey, const Brx& aValue);
    void Update(const Brx& aValue);
private: // from ConfigUiValRoBase
    void ObserverAdded(IConfigUiValObserver& aObserver) override;
private:
    void UpdateJsonValLocked();
private:
    Bws<kMaxValueBytes> iValue;
    Bws<kMaxValueBytes> iJsonValue;
    Mutex iLock;
};

class ConfigUiValNum : public ConfigUiValBase
{
public:
    ConfigUiValNum(Configuration::ConfigNum& aNum, const IWritable& aAdditionalJson);
    ~ConfigUiValNum();
private: // from ConfigUiValBase
    void ObserverAdded(IConfigUiValObserver& aObserver) override;
    void WriteKey(IWriter& aWriter) override;
    void WriteType(IWriter& aWriter) override;
    void WriteMeta(IWriter& aWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
private:
    void Update(Configuration::ConfigNum::KvpNum& aKvp);
private:
    Configuration::ConfigNum& iNum;
    TUint iListenerId;
    TInt iVal;
    Mutex iLock;
};

class ConfigUiValChoice : public ConfigUiValBase
{
public:
    ConfigUiValChoice(Configuration::ConfigChoice& aChoice, const IWritable& aAdditionalJson);
    ~ConfigUiValChoice();
private: // from ConfigUiValBase
    void ObserverAdded(IConfigUiValObserver& aObserver) override;
    void WriteKey(IWriter& aWriter) override;
    void WriteType(IWriter& aWriter) override;
    void WriteMeta(IWriter& aWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
private:
    void Update(Configuration::ConfigChoice::KvpChoice& aKvp);
private:
    Configuration::ConfigChoice& iChoice;
    TUint iListenerId;
    TUint iVal;
    Mutex iLock;
};

class ConfigUiValText : public ConfigUiValBase
{
public:
    ConfigUiValText(Configuration::ConfigText& aText, const IWritable& aAdditionalJson);
    ~ConfigUiValText();
private: // from ConfigUiValBase
    void ObserverAdded(IConfigUiValObserver& aObserver) override;
    void WriteKey(IWriter& aWriter) override;
    void WriteType(IWriter& aWriter) override;
    void WriteMeta(IWriter& aWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
private:
    void Update(Configuration::ConfigText::KvpText& aKvp);
private:
    Configuration::ConfigText& iText;
    TUint iListenerId;
    Bws<Configuration::ConfigText::kMaxBytes> iVal;
    Bws<kMaxValueBytes> iJsonValue;
    Mutex iLock;
};

/**
 * Custom class for ConfigChoice values that do not exist in ConfigManager when
 * ConfigApp is initialised (i.e., supports delayed instantiation of ConfigVals).
 */
class ConfigUiValChoiceDelayed : public IConfigUiVal
{
public:
    ConfigUiValChoiceDelayed(Configuration::IConfigManager& aConfigManager, const Brx& aKey, IWritable& aAdditionalJson);
    ~ConfigUiValChoiceDelayed();
private: // from IConfigValUi
    void WriteJson(IWriter& aWriter, IConfigUiUpdateWriter& aValWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
    TUint AddObserver(IConfigUiValObserver& aObserver) override;
    void RemoveObserver(TUint aObserverId) override;
private:
    Configuration::IConfigManager& iConfigManager;
    Bwh iKey;
    IWritable& iAdditionalJson;
    Configuration::ConfigChoice* iChoice;
    ConfigUiValChoice* iUiChoice;
    Mutex iLock;
};

class ConfigUiValRoModelIcon : public IConfigUiVal, private Av::IProductObserver, private INonCopyable
{
public:
    static const Brn kKey;
public:
    ConfigUiValRoModelIcon(Av::Product& aProduct);
    ~ConfigUiValRoModelIcon();
private: // from IConfigUiValReadOnly
    void WriteJson(IWriter& aWriter, IConfigUiUpdateWriter& aValWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
    TUint AddObserver(IConfigUiValObserver& aObserver) override;
    void RemoveObserver(TUint aObserverId) override;
private: // from IProductObserver
    void Started() override;
    void SourceIndexChanged() override;
    void SourceXmlChanged() override;
    void ProductUrisChanged() override;
private:
    Av::Product& iProduct;
    ConfigUiValRoUpdatable* iUiVal;
};

class ConfigUiValRoModelName : public IConfigUiVal
{
public:
    static const Brn kKey;
public:
    ConfigUiValRoModelName(Av::Product& aProduct);
    ~ConfigUiValRoModelName();
private: // from IConfigUiValReadOnly
    void WriteJson(IWriter& aWriter, IConfigUiUpdateWriter& aValWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
    TUint AddObserver(IConfigUiValObserver& aObserver) override;
    void RemoveObserver(TUint aObserverId) override;
private:
    ConfigUiValRo* iUiVal;
};

class ConfigUiValRoModelUrl : public IConfigUiVal, private Av::IProductObserver, private INonCopyable
{
public:
    static const Brn kKey;
public:
    ConfigUiValRoModelUrl(Av::Product& aProduct);
    ~ConfigUiValRoModelUrl();
private: // from IConfigUiValReadOnly
    void WriteJson(IWriter& aWriter, IConfigUiUpdateWriter& aValWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
    TUint AddObserver(IConfigUiValObserver& aObserver) override;
    void RemoveObserver(TUint aObserverId) override;
private: // from IProductObserver
    void Started() override;
    void SourceIndexChanged() override;
    void SourceXmlChanged() override;
    void ProductUrisChanged() override;
private:
    Av::Product& iProduct;
    ConfigUiValRoUpdatable* iUiVal;
};

class ConfigUiValRoManufacturerName : public IConfigUiVal
{
public:
    static const Brn kKey;
public:
    ConfigUiValRoManufacturerName(Av::Product& aProduct);
    ~ConfigUiValRoManufacturerName();
private: // from IConfigUiValReadOnly
    void WriteJson(IWriter& aWriter, IConfigUiUpdateWriter& aValWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
    TUint AddObserver(IConfigUiValObserver& aObserver) override;
    void RemoveObserver(TUint aObserverId) override;
private:
    ConfigUiValRo* iUiVal;
};

class ConfigUiValRoManufacturerUrl : public IConfigUiVal, private Av::IProductObserver, private INonCopyable
{
public:
    static const Brn kKey;
public:
    ConfigUiValRoManufacturerUrl(Av::Product& aProduct);
    ~ConfigUiValRoManufacturerUrl();
private: // from IConfigUiValReadOnly
    void WriteJson(IWriter& aWriter, IConfigUiUpdateWriter& aValWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
    TUint AddObserver(IConfigUiValObserver& aObserver) override;
    void RemoveObserver(TUint aObserverId) override;
private: // from IProductObserver
    void Started() override;
    void SourceIndexChanged() override;
    void SourceXmlChanged() override;
    void ProductUrisChanged() override;
private:
    Av::Product& iProduct;
    ConfigUiValRoUpdatable* iUiVal;
};

class ConfigUiValRoIpAddress : public IConfigUiVal, private INonCopyable
{
public:
    static const Brn kKey;
    static const TChar* kCookie;
public:
    ConfigUiValRoIpAddress(NetworkAdapterList& aAdapterList);
    ~ConfigUiValRoIpAddress();
private: // from IConfigUiValReadOnly
    void WriteJson(IWriter& aWriter, IConfigUiUpdateWriter& aValWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
    TUint AddObserver(IConfigUiValObserver& aObserver) override;
    void RemoveObserver(TUint aObserverId) override;
private:
    void CurrentAdapterChanged();
private:
    NetworkAdapterList& iAdapterList;
    TUint iListenerId;
    Endpoint::AddressBuf iAddress;
    ConfigUiValRoUpdatable* iUiVal;
};

class ConfigUiValStartupSource : public ConfigUiValBase
{
public:
    ConfigUiValStartupSource(Configuration::IConfigManager& aConfigManager, Configuration::ConfigText& aText, const std::vector<const Brx*>& aSources, const OpenHome::Web::IWritable& aAdditionalJson);
    ~ConfigUiValStartupSource();
private: // from ConfigUiValBase
    void ObserverAdded(IConfigUiValObserver& aObserver) override;
    void WriteKey(IWriter& aWriter) override;
    void WriteType(IWriter& aWriter) override;
    void WriteMeta(IWriter& aWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
private:
    class SourceNameObserver
    {
    public:
        SourceNameObserver(const Brx& aSystemName, Configuration::ConfigText& aConfigText, Functor aObserver);
        ~SourceNameObserver();
        const Brx& SystemName() const;
        void WriteSystemNameJson(IWriter& aWriter) const;
        void WriteNameJson(IWriter& aWriter) const;
    private:
        void SourceNameChanged(Configuration::KeyValuePair<const Brx&>& aKvp);
    private:
        Configuration::ConfigText& iConfigText;
        Functor iFunctor;
        TUint iSubscriberId;
        const Bws<Av::ISource::kMaxSystemNameBytes> iSystemName;
        Bws<Av::ISource::kMaxSourceNameBytes> iName;
        mutable Mutex iLock;
    };
private:
    static void WriteMetaOption(IWriter& aWriter, SourceNameObserver& aObserver);
    void WriteMetaOptions(IWriter& aWriter);
    void Update(Configuration::ConfigText::KvpText& aKvp);
    void SourceNameChanged();
private:
    Configuration::ConfigText& iText;
    TUint iListenerId;
    Bws<Configuration::ConfigText::kMaxBytes> iVal;
    Bws<kMaxValueBytes> iJsonValue;
    std::vector<SourceNameObserver*> iObservers;
    Mutex iLock;
};

class ConfigUiValStartupSourceDelayed : public IConfigUiVal
{
public:
    ConfigUiValStartupSourceDelayed(Configuration::IConfigManager& aConfigManager, const std::vector<const Brx*>& aSources, const OpenHome::Web::IWritable& aAdditionalJson);
    ~ConfigUiValStartupSourceDelayed();
private: // from IConfigValUi
    void WriteJson(IWriter& aWriter, IConfigUiUpdateWriter& aValWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) override;
    TUint AddObserver(IConfigUiValObserver& aObserver) override;
    void RemoveObserver(TUint aObserverId) override;
private:
    Configuration::IConfigManager& iConfigManager;
    std::vector<const Brx*> iSources;
    const IWritable& iAdditionalJson;
    ConfigUiValStartupSource* iUiVal;
    Mutex iLock;
};

class ConfigAppBase : public IConfigApp, public ILanguageResourceManager
{
private:
    static const TUint kMaxResourcePrefixBytes = 25;
    static const Brn kLangRoot;
    static const Brn kDefaultLanguage;
    typedef std::pair<Brn, Brn> ResourcePair;
    typedef std::map<Brn, Brn, BufferCmp> ResourceMap;
protected:
    ConfigAppBase(Media::IInfoAggregator& aInfoAggregator, Configuration::IConfigManager& aConfigManager, IConfigAppResourceHandlerFactory& aResourceHandlerFactory, const Brx& aResourcePrefix, const Brx& aResourceDir, TUint aResourceHandlersCount, TUint aMaxTabs, TUint aSendQueueSize, Av::IRebootHandler& aRebootHandler);
    ~ConfigAppBase();
public: // from IConfigApp
    ITab& Create(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList) override;
    const Brx& ResourcePrefix() const override;
    IResourceHandler& CreateResourceHandler(const Brx& aResource) override;
public: // from ILanguageResourceManager
    ILanguageResourceReader& CreateLanguageResourceHandler(const Brx& aResourceUriTail, std::vector<Bws<10>>& aLanguageList) override;
protected:
    void AddValue(IConfigUiVal* aValue);    // Takes ownership.

    // Convenience methods for adding ConfigVals to config app.
    void AddConfigNum(const Brx& aKey, TBool aRebootRequired = false);
    void AddConfigChoice(const Brx& aKey, TBool aRebootRequired = false);
    void AddConfigText(const Brx& aKey, TBool aRebootRequired = false);

    void AddConfigNumConditional(const Brx& aKey, TBool aRebootRequired = false);
    void AddConfigChoiceConditional(const Brx& aKey, TBool aRebootRequired = false);
    void AddConfigTextConditional(const Brx& aKey, TBool aRebootRequired = false);
protected:
    Configuration::IConfigManager& iConfigManager;
    // Helper additional JSON info writers for use in deriving classes.
    WritableJsonInfo iRebootRequired;
    WritableJsonInfo iRebootNotRequired;
private:
    ConfigMessageAllocator* iMsgAllocator;
    Bwh iLangResourceDir;
    const Bws<kMaxResourcePrefixBytes> iResourcePrefix;
    std::vector<IResourceHandler*> iResourceHandlers;
    std::vector<ILanguageResourceReader*> iLanguageResourceHandlers;
    std::vector<ConfigTab*> iTabs;
    std::vector<IConfigUiVal*> iUiVals;
    ResourceMap iResourceMappings;
    Mutex iLock;
};

class ConfigAppBasic : public ConfigAppBase
{
public:
    ConfigAppBasic(Media::IInfoAggregator& aInfoAggregator,
                   Configuration::IConfigManager& aConfigManager,
                   IConfigAppResourceHandlerFactory& aResourceHandlerFactory,
                   const Brx& aResourcePrefix, const Brx& aResourceDir,
                   TUint aResourceHandlersCount, TUint aMaxTabs, TUint aSendQueueSize, Av::IRebootHandler& aRebootHandler);
};

class ConfigAppSources : public ConfigAppBasic
{
private:
    static const TUint kMaxSourceNameBytes = Av::ISource::kMaxSourceNameBytes;
public:
    ConfigAppSources(Media::IInfoAggregator& aInfoAggregator,
                     Configuration::IConfigManager& aConfigManager,
                     IConfigAppResourceHandlerFactory& aResourceHandlerFactory,
                     const std::vector<const Brx*>& aSources,
                     const Brx& aResourcePrefix, const Brx& aResourceDir,
                     TUint aResourceHandlersCount, TUint aMaxTabs, TUint aSendQueueSize, Av::IRebootHandler& aRebootHandler);
};

} // namespace Web
} // namespace OpenHome
