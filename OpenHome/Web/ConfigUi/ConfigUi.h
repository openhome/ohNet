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
    class Product;
}
namespace Media {
    class IInfoAggregator;
}
namespace Web {

class IResourceFileConsumer;

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

class WritableJsonInfo : public IWritable, private INonCopyable
{
public:
    WritableJsonInfo(TBool aRebootRequired = false);
public: //from IWritable
    void Write(IWriter& aWriter) const override;
private:
    static void WriteBool(IWriter& aWriter, TBool aValue);
private:
    const TBool iRebootRequired;
};

//class IConfigUiValObserverReadOnly
//{
//public:
//    virtual void NotifyValueReadOnly(const Brx& aKey, const Brx& aValue, const Brx& aDisplayName);
//    virtual ~IConfigUiValObserverReadOnly() {}
//};
//
//class IConfigUiValObserverNum
//{
//public:
//    virtual void NotifyValueNum(Configuration::ConfigNum& aConfigVal, TUint aValue, const IWritable& aJsonWriter);
//    virtual ~IConfigUiValObserverNum() {}
//};
//
//class IConfigUiValObserverChoice
//{
//public:
//    virtual void NotifyValueChoice(Configuration::ConfigChoice& aConfigVal, TUint aValue, std::vector<Bws<10>>& aLanguageList, const IWritable& aJsonWriter);
//    virtual ~IConfigUiValObserverChoice() {}
//};
//
//class IConfigUiValObserverText
//{
//public:
//    virtual void NotifyValueText(Configuration::ConfigText& aConfigVal, const Brx& aValue, const IWritable& aJsonWriter);
//    virtual ~IConfigUiValObserverText() {}
//};
//
//class ConfigUiValReadOnly : private INonCopyable
//{
//public:
//    ConfigUiValReadOnly(const Brx& aKey, IConfigUiValObserverReadOnly& aObserver, const Brx& aDisplayName);
//};
//
//class ConfigUiValNum
//{
//public:
//    ConfigUiValNum(Configuration::ConfigNum& aConfigVal, IConfigUiValObserverNum& aObserver, const Brx& aDisplayName, const Brx& aHelpText, TBool aRebootRequired = false, TBool aRefreshRequired = false);
//    ~ConfigUiValNum();
//private:
//    Configuration::ConfigNum& iConfigVal;
//    TUint iSubscriberId;
//    IConfigUiValObserverNum& iObserver;
//    const WritableAdditionalJson iAdditional;
//};
//
//class ConfigUiValChoice
//{
//public:
//    ConfigUiValChoice(Configuration::ConfigChoice& aConfigVal, IConfigUiValObserverChoice& aObserver, const Brx& aDisplayName, const Brx& aHelpText, TBool aRebootRequired = false, TBool aRefreshRequired = false);
//    ~ConfigUiValChoice();
//private:
//    Configuration::ConfigChoice& iConfigVal;
//    TUint iSubscriberId;
//    IConfigUiValObserverChoice& iObserver;
//    const WritableAdditionalJson iAdditional;
//};
//
//class ConfigUiValText
//{
//public:
//    ConfigUiValText(Configuration::ConfigText& aConfigVal, IConfigUiValObserverText& aObserver, const Brx& aDisplayName, const Brx& aHelpText, TBool aRebootRequired = false, TBool aRefreshRequired = false);
//    ~ConfigUiValText();
//private:
//    Configuration::ConfigText& iConfigVal;
//    TUint iSubscriberId;
//    IConfigUiValObserverText& iObserver;
//    const WritableAdditionalJson iAdditional;
//};

class IConfigMessageAllocator
{
public:
    virtual ITabMessage* AllocateReadOnly(const Brx& aKey, const Brx& aValue) = 0;
    virtual ITabMessage* AllocateNum(Configuration::ConfigNum& aNum, TInt aValue, const IWritable& aJsonWriter) = 0;
    virtual ITabMessage* AllocateChoice(Configuration::ConfigChoice& aChoice, TUint aValue, const IWritable& aJsonWriter, std::vector<Bws<10>>& aLanguageList) = 0;
    virtual ITabMessage* AllocateText(Configuration::ConfigText& aText, const Brx& aValue, const IWritable& aJsonWriter) = 0;
    virtual ~IConfigMessageAllocator() {}
};

class ConfigMessageBase : public Media::Allocated, public ITabMessage, public INonCopyable
{
protected:
    ConfigMessageBase(Media::AllocatorBase& aAllocator);
    void Set(const IWritable& aJsonWriter);
protected:
    virtual void WriteKey(IWriter& aWriter) = 0;
    virtual void WriteValue(IWriter& aWriter) = 0;
    virtual void WriteType(IWriter& aWriter) = 0;
    virtual void WriteMeta(IWriter& aWriter) = 0;
protected: // from Allocated
    void Clear() override;
private: // from ITabMessage
    void Send(IWriter& aWriter);
    void Destroy();
private:
    const IWritable* iWriterAdditional;
};

class ConfigMessageNum : public ConfigMessageBase
{
    friend class ConfigMessageAllocator;
public:
    ConfigMessageNum(Media::AllocatorBase& aAllocator);
private:
    void Set(Configuration::ConfigNum& aNum, TInt aValue, const IWritable& aJsonWriter);
private: // from ConfigMessageBase
    void Clear() override;
    void WriteKey(IWriter& aWriter) override;
    void WriteValue(IWriter& aWriter) override;
    void WriteType(IWriter& aWriter) override;
    void WriteMeta(IWriter& aWriter) override;
private:
    Configuration::ConfigNum* iNum;
    TInt iValue;
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

class ConfigMessageChoice : public ConfigMessageBase
{
    friend class ConfigMessageAllocator;
public:
    ConfigMessageChoice(Media::AllocatorBase& aAllocator);
private:
    void Set(Configuration::ConfigChoice& aChoice, TUint aValue, const IWritable& aJsonWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList);
private: // from ConfigMessageBase
    void Clear() override;
    void WriteKey(IWriter& aWriter) override;
    void WriteValue(IWriter& aWriter) override;
    void WriteType(IWriter& aWriter) override;
    void WriteMeta(IWriter& aWriter) override;
private:
    ILanguageResourceManager* iLanguageResourceManager;
    Configuration::ConfigChoice* iChoice;
    TUint iValue;
    std::vector<Bws<10>>* iLanguageList;
};

class ConfigMessageText : public ConfigMessageBase
{
    friend class ConfigMessageAllocator;
private:
    static const TUint kMaxBytes = Configuration::ConfigText::kMaxBytes;
public:
    ConfigMessageText(Media::AllocatorBase& aAllocator);
private:
    void Set(Configuration::ConfigText& aText, const Brx& aValue, const IWritable& aJsonWriter);
private: // from ConfigMessageBase
    void Clear() override;
    void WriteKey(IWriter& aWriter) override;
    void WriteValue(IWriter& aWriter) override;
    void WriteType(IWriter& aWriter) override;
    void WriteMeta(IWriter& aWriter) override;
private:
    Configuration::ConfigText* iText;
    Bws<kMaxBytes> iValue;
};

class ConfigMessageAllocator : public IConfigMessageAllocator
{
public:
    ConfigMessageAllocator(Media::IInfoAggregator& aInfoAggregator, TUint aMsgCountReadOnly, TUint aMsgCountNum, TUint aMsgCountChoice, TUint aMsgCountText, ILanguageResourceManager& aLanguageResourceManager);
public: // from IConfigMessageAllocator
    ITabMessage* AllocateReadOnly(const Brx& aKey, const Brx& aValue) override;
    ITabMessage* AllocateNum(Configuration::ConfigNum& aNum, TInt aValue, const IWritable& aJsonWriter) override;
    ITabMessage* AllocateChoice(Configuration::ConfigChoice& aChoice, TUint aValue, const IWritable& aJsonWriter, std::vector<Bws<10>>& aLanguageList) override;
    ITabMessage* AllocateText(Configuration::ConfigText& aText, const Brx& aValue, const IWritable& aJsonWriter) override;
private:
    //Media::Allocator<ConfigMessageReadOnly> iAllocatorMsgReadOnly;
    Media::Allocator<ConfigMessageNum> iAllocatorMsgNum;
    Media::Allocator<ConfigMessageChoice> iAllocatorMsgChoice;
    Media::Allocator<ConfigMessageText> iAllocatorMsgText;
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
public: // from ITab
    void Receive(const Brx& aMessage);
    virtual void Destroy() = 0;
};

/**
 * Hiearchy of classes that can write objects out as JSON key-value pairs.
 * Store references rather than taking copies of data, so references passed
 * must be valid for lifetime of object.
 *
 * JSON strings (for keys/values) must not contain " or \
 */

// FIXME - MUST ensure all strings are JSON escaped correctly when written out (into additional json blob/string).
// FIXME - are any of these classes required now?
class JsonKvp : public INonCopyable
{
public:
    void Serialise(IWriter& aWriter) const;
protected:
    JsonKvp(const Brx& aKey);
    virtual void SerialiseValue(IWriter& aWriter) const = 0;
private:
    void SerialiseKey(IWriter& aWriter) const;
private:
    const Brn iKey;
};

class JsonKvpInt : public JsonKvp
{
public:
    JsonKvpInt(const Brx& aKey, TInt aValue);
private: // from JsonKvp
    void SerialiseValue(IWriter& aWriter) const;
private:
    TInt iValue;
};

class JsonKvpUint : public JsonKvp
{
public:
    JsonKvpUint(const Brx& aKey, TUint aValue);
private: // from JsonKvp
    void SerialiseValue(IWriter& aWriter) const;
private:
    TUint iValue;
};

class JsonKvpString : public JsonKvp
{
public:
    JsonKvpString(const Brx& aKey, const Brx& aValue);
private: // from JsonKvp
    void SerialiseValue(IWriter& aWriter) const;
private:
    const Brx& iValue;
};

class IJsonInfoProvider
{
public:
    virtual const WritableJsonInfo& GetInfo(const Brx& aKey) = 0;
    virtual ~IJsonInfoProvider() {}
};

class ConfigTab : public ConfigTabReceiver, public INonCopyable
{
private:
    static const TUint kInvalidSubscription;
    typedef std::pair<Brn,TUint> SubscriptionPair;
    typedef std::vector<SubscriptionPair> SubscriptionVector;
public:
    ConfigTab(TUint aId, IConfigMessageAllocator& aMessageAllocator, Configuration::IConfigManager& aConfigManager, IJsonInfoProvider& aInfoProvider);
    ~ConfigTab();
    void AddKeyNum(const Brx& aKey);
    void AddKeyChoice(const Brx& aKey);
    void AddKeyText(const Brx& aKey);
    void Start();
    TBool Allocated() const;
    void SetHandler(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList);
private: // from ConfigTabReceiver
    void Receive(const Brx& aKey, const Brx& aValue);
    void Destroy();
private:
    void ConfigNumCallback(Configuration::ConfigNum::KvpNum& aKvp);
    void ConfigChoiceCallback(Configuration::ConfigChoice::KvpChoice& aKvp);
    void ConfigTextCallback(Configuration::ConfigText::KvpText& aKvp);
private:
    const TUint iId;
    IConfigMessageAllocator& iMsgAllocator;
    Configuration::IConfigManager& iConfigManager;
    IJsonInfoProvider& iInfoProvider;
    ITabHandler* iHandler;
    SubscriptionVector iConfigNums;
    SubscriptionVector iConfigChoices;
    SubscriptionVector iConfigTexts;
    TBool iStarted;
    std::vector<Bws<10>> iLanguageList;
};

class IConfigApp : public IWebApp
{
public: // from IWebApp
    virtual ITab& Create(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList) = 0;
    virtual const Brx& ResourcePrefix() const= 0;
    virtual IResourceHandler& CreateResourceHandler(const Brx& aResource) = 0;
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

class ConfigAppBase : public IConfigApp, public IJsonInfoProvider, public ILanguageResourceManager
{
public:
     typedef std::vector<JsonKvp*> JsonKvpVector;
private:
    static const TUint kMaxResourcePrefixBytes = 25;
    static const Brn kLangRoot;
    static const Brn kDefaultLanguage;
    typedef std::vector<const Brx*> KeyVector;
    typedef std::pair<Brn, const WritableJsonInfo*> InfoPair;
    typedef std::map<Brn, const WritableJsonInfo*, BufferCmp> InfoMap;
protected:
    ConfigAppBase(Media::IInfoAggregator& aInfoAggregator, Configuration::IConfigManager& aConfigManager, IConfigAppResourceHandlerFactory& aResourceHandlerFactory, const Brx& aResourcePrefix, const Brx& aResourceDir, TUint aMaxTabs, TUint aSendQueueSize);
    ~ConfigAppBase();
public: // from IConfigApp
    ITab& Create(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList) override;
    const Brx& ResourcePrefix() const override;
    IResourceHandler& CreateResourceHandler(const Brx& aResource) override;
public: // from IJsonInfoProvider
    const WritableJsonInfo& GetInfo(const Brx& aKey) override;
public: // from ILanguageResourceManager
    ILanguageResourceReader& CreateLanguageResourceHandler(const Brx& aResourceUriTail, std::vector<Bws<10>>& aLanguageList) override;
protected:
    void AddReadOnly(const Brx& aKey);
    void AddNum(const Brx& aKey, TBool aRebootRequired = false);
    void AddChoice(const Brx& aKey, TBool aRebootRequired = false);
    void AddText(const Brx& aKey, TBool aRebootRequired = false);
private:
    void AddInfo(const Brx& aKey, TBool aRebootRequired);
protected:
    Configuration::IConfigManager& iConfigManager;
private:
    ConfigMessageAllocator* iMsgAllocator;
    Bwh iLangResourceDir;
    const Bws<kMaxResourcePrefixBytes> iResourcePrefix;
    std::vector<IResourceHandler*> iResourceHandlers;
    std::vector<ILanguageResourceReader*> iLanguageResourceHandlers;
    std::vector<ConfigTab*> iTabs;
    KeyVector iKeysNums;
    KeyVector iKeysChoices;
    KeyVector iKeysTexts;
    InfoMap iInfoMap;       // Additional info for ConfigVals.
    Mutex iLock;
};

class ConfigAppBasic : public ConfigAppBase
{
public:
    ConfigAppBasic(Media::IInfoAggregator& aInfoAggregator,
                   Configuration::IConfigManager& aConfigManager,
                   IConfigAppResourceHandlerFactory& aResourceHandlerFactory,
                   const Brx& aResourcePrefix, const Brx& aResourceDir,
                   TUint aMaxTabs, TUint aSendQueueSize);
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
                     TUint aMaxTabs, TUint aSendQueueSize);
};

} // namespace Web
} // namespace OpenHome
