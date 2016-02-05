#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Web/WebAppFramework.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Media/Pipeline/Msg.h>

EXCEPTION(LanguageResourceInvalid);
EXCEPTION(JsonStringError);

namespace OpenHome {
namespace Av {
    class IRebootHandler;
    class Product;
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
    virtual void Process(IResourceFileConsumer& aResourceConsumer) = 0;
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
    virtual ITabMessage* AllocateInt(IConfigUiVal& aUiVal, TInt aUpdatedVal, std::vector<Bws<10>>& aLanguageList) = 0;
    virtual ITabMessage* AllocateUint(IConfigUiVal& aUiVal, TUint aUpdatedVal, std::vector<Bws<10>>& aLanguageList) = 0;
    virtual ITabMessage* AllocateString(IConfigUiVal& aUiVal, const Brx& aUpdatedVal, std::vector<Bws<10>>& aLanguageList) = 0;
    virtual ITabMessage* AllocateStringUnescaped(IConfigUiVal& aUiVal, const Brx& aUpdatedVal, std::vector<Bws<10>>& aLanguageList) = 0;
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

class ConfigMessageInt : public ConfigMessageBase
{
    friend class ConfigMessageAllocator;
public:
    ConfigMessageInt(Media::AllocatorBase& aAllocator);
private:
    void Set(IConfigUiVal& aUiVal, TInt aUpdatedVal, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList);
private: // from ConfigMessageBase
    void Clear() override;
    void Send(IWriter& aWriter) override;
    void WriteValueJson(IWriter& aWriter) override;
private:
    IConfigUiVal* iUiVal;
    TInt iUpdatedVal;
    ILanguageResourceManager* iLanguageResourceManager;
    std::vector<Bws<10>>* iLanguageList;
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

class ConfigMessageUint : public ConfigMessageBase
{
    friend class ConfigMessageAllocator;
public:
    ConfigMessageUint(Media::AllocatorBase& aAllocator);
private:
    void Set(IConfigUiVal& aUiVal, TUint aUpdatedVal, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList);
private: // from ConfigMessageBase
    void Clear() override;
    void Send(IWriter& aWriter) override;
    void WriteValueJson(IWriter& aWriter) override;
private:
    IConfigUiVal* iUiVal;
    TUint iUpdatedVal;
    ILanguageResourceManager* iLanguageResourceManager;
    std::vector<Bws<10>>* iLanguageList;
};

class ConfigMessageStringBase : public ConfigMessageBase
{
    friend class ConfigMessageAllocator;
private:
    static const TUint kMaxBytes = Configuration::ConfigText::kMaxBytes;
public:
    ConfigMessageStringBase(Media::AllocatorBase& aAllocator);
private:
    void Set(IConfigUiVal& aUiVal, const Brx& aUpdatedVal, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList);
protected: // from ConfigMessageBase
    virtual void WriteValueJson(IWriter& aWriter) override = 0;
private: // from ConfigMessageBase
    void Clear() override;
    void Send(IWriter& aWriter) override;
protected:
    IConfigUiVal* iUiVal;
    Bws<kMaxBytes> iUpdatedVal;
private:
    ILanguageResourceManager* iLanguageResourceManager;
    std::vector<Bws<10>>* iLanguageList;
};

class ConfigMessageString : public ConfigMessageStringBase
{
    friend class ConfigMessageAllocator;
public:
    ConfigMessageString(Media::AllocatorBase& aAllocator);
private: // from ConfigMessageBase
    void WriteValueJson(IWriter& aWriter) override;
};

class ConfigMessageStringUnescaped : public ConfigMessageStringBase
{
    friend class ConfigMessageAllocator;
public:
    ConfigMessageStringUnescaped(Media::AllocatorBase& aAllocator);
private: // from ConfigMessageBase
    void WriteValueJson(IWriter& aWriter) override;
};

// FIXME - correct to pass lang resource manager in via constructor, but then pass individual lang vectors in on Allocate()?
class ConfigMessageAllocator : public IConfigMessageAllocator
{
public:
    ConfigMessageAllocator(Media::IInfoAggregator& aInfoAggregator, TUint aMsgCountInt, TUint aMsgCountUint, TUint aMsgCountString, TUint aMsgCountStringUnescaped, ILanguageResourceManager& aLanguageResourceManager);
public: // from IConfigMessageAllocator
    ITabMessage* AllocateInt(IConfigUiVal& aUiVal, TInt aUpdatedVal, std::vector<Bws<10>>& aLanguageList) override;
    ITabMessage* AllocateUint(IConfigUiVal& aUiVal, TUint aUpdatedVal, std::vector<Bws<10>>& aLanguageList) override;
    ITabMessage* AllocateString(IConfigUiVal& aUiVal, const Brx& aUpdatedVal, std::vector<Bws<10>>& aLanguageList) override;
    ITabMessage* AllocateStringUnescaped(IConfigUiVal& aUiVal, const Brx& aUpdatedVal, std::vector<Bws<10>>& aLanguageList) override;
private:
    //Media::Allocator<ConfigMessageReadOnly> iAllocatorMsgReadOnly;
    Media::Allocator<ConfigMessageInt> iAllocatorMsgInt;
    Media::Allocator<ConfigMessageUint> iAllocatorMsgUint;
    Media::Allocator<ConfigMessageString> iAllocatorMsgString;
    Media::Allocator<ConfigMessageStringUnescaped> iAllocatorMsgStringUnescaped;
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

// FIXME - maybe only have a callback that takes a const Brx& as second param here.
class IConfigUiValObserver
{
public:
    virtual void ValueChangedInt(IConfigUiVal& aUiVal, TInt aUpdatedVal) = 0;
    virtual void ValueChangedUint(IConfigUiVal& aUiVal, TUint aUpdatedVal) = 0;
    virtual void ValueChangedString(IConfigUiVal& aUiVal, const Brx& aUpdatedVal) = 0;
    virtual void ValueChangedStringUnescaped(IConfigUiVal& aUiVal, const Brx& aUpdatedVal) = 0;
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
    void ValueChangedInt(IConfigUiVal& aUiVal, TInt aUpdatedVal) override;
    void ValueChangedUint(IConfigUiVal& aUiVal, TUint aUpdatedVal) override;
    void ValueChangedString(IConfigUiVal& aUiVal, const Brx& aUpdatedVal) override;
    void ValueChangedStringUnescaped(IConfigUiVal& aUiVal, const Brx& aUpdatedVal) override;
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
    virtual void WriteJson(IWriter& aWriter, IConfigUiUpdateWriter& aValWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) = 0;
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
    ConfigUiValBase(const IWritable& aAdditionalJson);

    void ValueChangedInt(TInt aValue);
    void ValueChangedUint(TUint aValue);
    void ValueChangedString(const Brx& aValue);
    void ValueChangedStringUnescaped(const Brx& aValue);
    virtual void ObserverAdded(IConfigUiValObserver& aObserver) = 0;

    virtual void WriteKey(IWriter& aWriter) = 0;
    virtual void WriteType(IWriter& aWriter) = 0;
    virtual void WriteMeta(IWriter& aWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList) = 0;
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
    static const TUint kMaxValueBytes = 512;
public:
    ConfigUiValRoUpdatable(const Brx& aKey, const Brx& aValue);
    void Update(const Brx& aValue);
private: // from ConfigUiValRoBase
    void ObserverAdded(IConfigUiValObserver& aObserver) override;
private:
    Bws<kMaxValueBytes> iValue;
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

class ConfigAppBase : public IConfigApp, public ILanguageResourceManager
{
private:
    static const TUint kMaxResourcePrefixBytes = 25;
    static const Brn kLangRoot;
    static const Brn kDefaultLanguage;
protected:
    ConfigAppBase(Media::IInfoAggregator& aInfoAggregator, Configuration::IConfigManager& aConfigManager, IConfigAppResourceHandlerFactory& aResourceHandlerFactory, const Brx& aResourcePrefix, const Brx& aResourceDir, TUint aMaxTabs, TUint aSendQueueSize, Av::IRebootHandler& aRebootHandler);
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
    Mutex iLock;
};

class ConfigAppBasic : public ConfigAppBase
{
public:
    ConfigAppBasic(Media::IInfoAggregator& aInfoAggregator,
                   Configuration::IConfigManager& aConfigManager,
                   IConfigAppResourceHandlerFactory& aResourceHandlerFactory,
                   const Brx& aResourcePrefix, const Brx& aResourceDir,
                   TUint aMaxTabs, TUint aSendQueueSize, Av::IRebootHandler& aRebootHandler);
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
                     TUint aMaxTabs, TUint aSendQueueSize, Av::IRebootHandler& aRebootHandler);
};

} // namespace Web
} // namespace OpenHome
