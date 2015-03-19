#ifndef HEADER_WEB_CONFIGUI
#define HEADER_WEB_CONFIGUI

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Web/WebAppFramework.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Fifo.h>

EXCEPTION(LanguageResourceInvalid);

namespace OpenHome {
namespace Av {
    class ISource;
    class Product;
}
}

namespace OpenHome {
namespace Web {

class ILanguageResourceReader
{
public:
    virtual Brn ReadLine() = 0;
    virtual void Destroy() = 0;
    virtual ~ILanguageResourceReader() {}
};

class ILanguageResourceManager
{
public:
    virtual ILanguageResourceReader& CreateLanguageResourceHandler(const Brx& aResourceUriTail, std::vector<const Brx*>& aLanguageList) = 0;  // THROWS LanguageResourceInvalid
    virtual ~ILanguageResourceManager() {}
};

class LanguageResourceFileReader : public ILanguageResourceReader
{
private:
    static const TUint kMaxBufBytes = 1024;
public:
    LanguageResourceFileReader(const Brx& aRootDir);
    void SetResource(const Brx& aUriTail);
    TBool Allocated() const;
public: // from ILanguageResourceReader
    Brn ReadLine() override;
    void Destroy() override;
private:
    Brn iRootDir;
    FileStream iFileStream;
    Srs<512> iReadBuffer;
    ReaderTextS<kMaxBufBytes> iReaderText;
    TBool iAllocated;
    mutable Mutex iLock;
};

class OptionJsonWriter
{
public:
    static void Write(ILanguageResourceReader& aReader, const Brx& aKey, const std::vector<TUint>& aChoices, IWriter& aWriter);   // validates input from aReader against aChoices
    static void WriteChoiceObject(ILanguageResourceReader& aReader, IWriter& aWriter, TUint aId);
};

class IConfigMessage : public ITabMessage
{
public:
    virtual void Set(OpenHome::Configuration::ConfigNum& aNum, TInt aValue, const OpenHome::Brx& aAdditionalJson) = 0;
    virtual void Set(OpenHome::Configuration::ConfigChoice& aChoice, TUint aValue, const OpenHome::Brx& aAdditionalJson, std::vector<const Brx*>& aLanguageList) = 0;
    virtual void Set(OpenHome::Configuration::ConfigText& aText, const OpenHome::Brx& aValue, const OpenHome::Brx& aAdditionalJson) = 0;
public: // from ITabMessage
    virtual void Send(OpenHome::IWriter& aWriter) = 0;
    virtual void Destroy() = 0;
public:
    virtual ~IConfigMessage() {}
};

class IConfigMessageAllocator
{
public:
    virtual IConfigMessage& Allocate(OpenHome::Configuration::ConfigNum& aNum, TInt aValue, const OpenHome::Brx& aAdditionalJson) = 0;
    virtual IConfigMessage& Allocate(OpenHome::Configuration::ConfigChoice& aChoice, TUint aValue, const OpenHome::Brx& aAdditionalJson, std::vector<const Brx*>& aLanguageList) = 0;
    virtual IConfigMessage& Allocate(OpenHome::Configuration::ConfigText& aText, const OpenHome::Brx& aValue, const OpenHome::Brx& aAdditionalJson) = 0;
    virtual ~IConfigMessageAllocator() {}
};

class IConfigMessageDeallocator
{
public:
    virtual void Deallocate(IConfigMessage& aMessage) = 0;
    virtual ~IConfigMessageDeallocator() {}
};

class ConfigMessage : public IConfigMessage, public OpenHome::INonCopyable
{
public:
    static const TUint kMaxAdditionalDataBytes = 512; // FIXME - this needs to be written out somewhere
protected:
    ConfigMessage(IConfigMessageDeallocator& aDeallocator);
    void Set(const OpenHome::Brx& aAdditionalJson);
protected:
    virtual void WriteKey(OpenHome::IWriter& aWriter) = 0;
    virtual void WriteValue(OpenHome::IWriter& aWriter) = 0;
    virtual void WriteType(OpenHome::IWriter& aWriter) = 0;
    virtual void WriteMeta(OpenHome::IWriter& aWriter) = 0;
protected: // from IConfigMessage
    void Clear();
private: // from IConfigMessage
    void Set(OpenHome::Configuration::ConfigNum& aNum, TInt aValue, const OpenHome::Brx& aAdditionalJson);
    void Set(OpenHome::Configuration::ConfigChoice& aChoice, TUint aValue, const OpenHome::Brx& aAdditionalJson, std::vector<const Brx*>& aLanguageList);
    void Set(OpenHome::Configuration::ConfigText& aText, const OpenHome::Brx& aValue, const OpenHome::Brx& aAdditionalJson);
    // FIXME - give this a default impl that calls a virtual method that deriving classes must implement to write out their own values
    void Send(OpenHome::IWriter& aWriter);
    void Destroy();
private:
    OpenHome::Bws<kMaxAdditionalDataBytes> iAdditionalJson;
    IConfigMessageDeallocator& iDeallocator;
};

class ConfigMessageNum : public ConfigMessage
{
    friend class ConfigMessageNumAllocator;
private:
    ConfigMessageNum(IConfigMessageDeallocator& aDeallocator);
private: // from ConfigMessage
    void Set(OpenHome::Configuration::ConfigNum& aNum, TInt aValue, const OpenHome::Brx& aAdditionalJson);
    void Clear();
    void WriteKey(OpenHome::IWriter& aWriter);
    void WriteValue(OpenHome::IWriter& aWriter);
    void WriteType(OpenHome::IWriter& aWriter);
    void WriteMeta(OpenHome::IWriter& aWriter);
private:
    OpenHome::Configuration::ConfigNum* iNum;
    TInt iValue;
};

class ConfigMessageChoice : public ConfigMessage
{
    friend class ConfigMessageChoiceAllocator;
private:
    ConfigMessageChoice(IConfigMessageDeallocator& aDeallocator, ILanguageResourceManager& aLanguageResourceManager);
private: // from ConfigMessage
    void Set(OpenHome::Configuration::ConfigChoice& aChoice, TUint aValue, const OpenHome::Brx& aAdditionalJson, std::vector<const Brx*>& aLanguageList);
    void Clear();
    void WriteKey(OpenHome::IWriter& aWriter);
    void WriteValue(OpenHome::IWriter& aWriter);
    void WriteType(OpenHome::IWriter& aWriter);
    void WriteMeta(OpenHome::IWriter& aWriter);
private:
    ILanguageResourceManager& iLanguageResourceManager;
    OpenHome::Configuration::ConfigChoice* iChoice;
    TUint iValue;
    std::vector<const Brx*>* iLanguageList;
};

class ConfigMessageText : public ConfigMessage
{
    friend class ConfigMessageTextAllocator;
private:
    static const TUint kMaxBytes = 512; //FIXME - use instead: OpenHome::Configuration::ConfigText::kMaxBytes;
private:
    ConfigMessageText(IConfigMessageDeallocator& aDeallocator);
private: // from ConfigMessage
    void Set(OpenHome::Configuration::ConfigText& aText, const OpenHome::Brx& aValue, const OpenHome::Brx& aAdditionalJson);
    void Clear();
    void WriteKey(OpenHome::IWriter& aWriter);
    void WriteValue(OpenHome::IWriter& aWriter);
    void WriteType(OpenHome::IWriter& aWriter);
    void WriteMeta(OpenHome::IWriter& aWriter);
private:
    OpenHome::Configuration::ConfigText* iText;
    OpenHome::Bws<kMaxBytes> iValue;
};

class ConfigMessageAllocatorBase : public IConfigMessageDeallocator
{
protected:
    ConfigMessageAllocatorBase(TUint aMessageCount);
    ~ConfigMessageAllocatorBase();
private: // from IConfigMessageDeallocator
    void Deallocate(IConfigMessage& aMessage);
protected:
    OpenHome::Fifo<IConfigMessage*> iFifo;
    //OpenHome::Mutex iLock; // FIXME - required? - only things that can come from multiple threads are Allocate()
};

class ConfigMessageNumAllocator : public ConfigMessageAllocatorBase
{
public:
    ConfigMessageNumAllocator(TUint aMessageCount);
    IConfigMessage& Allocate(OpenHome::Configuration::ConfigNum& aNum, TInt aValue, const OpenHome::Brx& aAdditionalJson);
};

class ConfigMessageChoiceAllocator : public ConfigMessageAllocatorBase
{
public:
    ConfigMessageChoiceAllocator(TUint aMessageCount, ILanguageResourceManager& aLanguageResourceManager);
    IConfigMessage& Allocate(OpenHome::Configuration::ConfigChoice& aChoice, TUint aValue, const OpenHome::Brx& aAdditionalJson, std::vector<const Brx*>& aLanguageList);
};

class ConfigMessageTextAllocator : public ConfigMessageAllocatorBase
{
public:
    ConfigMessageTextAllocator(TUint aMessageCount);
    IConfigMessage& Allocate(OpenHome::Configuration::ConfigText& aText, const OpenHome::Brx& aValue, const OpenHome::Brx& aAdditionalJson);
};

class ConfigMessageAllocator : public IConfigMessageAllocator
{
public:
    ConfigMessageAllocator(TUint aMessageCount, ILanguageResourceManager& aLanguageResourceManager);
public: // from IConfigMessageAllocator
    IConfigMessage& Allocate(OpenHome::Configuration::ConfigNum& aNum, TInt aValue, const OpenHome::Brx& aAdditionalJson);
    IConfigMessage& Allocate(OpenHome::Configuration::ConfigChoice& aChoice, TUint aValue, const OpenHome::Brx& aAdditionalJson, std::vector<const Brx*>& aLanguageList);
    IConfigMessage& Allocate(OpenHome::Configuration::ConfigText& aText, const OpenHome::Brx& aValue, const OpenHome::Brx& aAdditionalJson);
private:
    ConfigMessageNumAllocator iAllocatorNum;
    ConfigMessageChoiceAllocator iAllocatorChoice;
    ConfigMessageTextAllocator iAllocatorText;
};

/**
 * Abstract class that will receive a string message and attempt to parse it
 * into one or more key-value pair messages.
 */
class ConfigTabReceiver : public ITab
{
protected:
    ConfigTabReceiver();
    virtual void Receive(const OpenHome::Brx& aKey, const OpenHome::Brx& aValue) = 0;
public: // from ITab
    void Receive(const OpenHome::Brx& aMessage);
    virtual void Destroy() = 0;
};

/**
 * Hiearchy of classes that can write objects out as JSON key-value pairs.
 * Store references rather than taking copies of data, so references passed
 * must be valid for lifetime of object.
 *
 * JSON strings (for keys/values) must not contain " or \
 */
class JsonKvp : public OpenHome::INonCopyable
{
public:
    void Serialise(OpenHome::IWriter& aWriter) const;
protected:
    JsonKvp(const OpenHome::Brx& aKey);
    virtual void SerialiseValue(OpenHome::IWriter& aWriter) const = 0;
private:
    void SerialiseKey(OpenHome::IWriter& aWriter) const;
private:
    const OpenHome::Brn iKey;
};

class JsonKvpInt : public JsonKvp
{
public:
    JsonKvpInt(const OpenHome::Brx& aKey, TInt aValue);
private: // from JsonKvp
    void SerialiseValue(OpenHome::IWriter& aWriter) const;
private:
    TInt iValue;
};

class JsonKvpUint : public JsonKvp
{
public:
    JsonKvpUint(const OpenHome::Brx& aKey, TUint aValue);
private: // from JsonKvp
    void SerialiseValue(OpenHome::IWriter& aWriter) const;
private:
    TUint iValue;
};

class JsonKvpString : public JsonKvp
{
public:
    JsonKvpString(const OpenHome::Brx& aKey, const OpenHome::Brx& aValue);
private: // from JsonKvp
    void SerialiseValue(OpenHome::IWriter& aWriter) const;
private:
    const OpenHome::Brx& iValue;
};

class IJsonProvider
{
public:
    virtual const OpenHome::Brx& GetJson(const OpenHome::Brx& aKey) = 0;
    virtual ~IJsonProvider() {}
};

class ConfigTab : public ConfigTabReceiver, public OpenHome::INonCopyable
{
private:
    static const TUint kInvalidSubscription;
    typedef std::pair<OpenHome::Brn,TUint> SubscriptionPair;
    typedef std::vector<SubscriptionPair> SubscriptionVector;
public:
    ConfigTab(TUint aId, IConfigMessageAllocator& aMessageAllocator, OpenHome::Configuration::IConfigManager& aConfigManager, IJsonProvider& aJsonProvider);
    ~ConfigTab();
    void AddKeyNum(const OpenHome::Brx& aKey);
    void AddKeyChoice(const OpenHome::Brx& aKey);
    void AddKeyText(const OpenHome::Brx& aKey);
    void Start();
    TBool Allocated() const;
    void SetHandler(ITabHandler& aHandler, std::vector<const Brx*>& aLanguageList);
private: // from ConfigTabReceiver
    void Receive(const OpenHome::Brx& aKey, const OpenHome::Brx& aValue);
    void Destroy();
private:
    void ConfigNumCallback(OpenHome::Configuration::ConfigNum::KvpNum& aKvp);
    void ConfigChoiceCallback(OpenHome::Configuration::ConfigChoice::KvpChoice& aKvp);
    void ConfigTextCallback(OpenHome::Configuration::ConfigText::KvpText& aKvp);
private:
    const TUint iId;
    IConfigMessageAllocator& iMsgAllocator;
    OpenHome::Configuration::IConfigManager& iConfigManager;
    IJsonProvider& iJsonProvider;
    ITabHandler* iHandler;
    SubscriptionVector iConfigNums;
    SubscriptionVector iConfigChoices;
    SubscriptionVector iConfigTexts;
    TBool iStarted;
    std::vector<const Brx*> iLanguageList;
};

class IConfigApp : public IWebApp
{
public: // from IWebApp
    virtual ITab& Create(ITabHandler& aHandler, std::vector<const Brx*>& aLanguageList) = 0;
    virtual const OpenHome::Brx& ResourcePrefix() const= 0;
    virtual IResourceHandler& CreateResourceHandler(const OpenHome::Brx& aResource) = 0;
public:
    virtual ~IConfigApp() {}
};

class ConfigAppBase : public IConfigApp, public IJsonProvider, public ILanguageResourceManager
{
public:
     typedef std::vector<JsonKvp*> JsonKvpVector;
private:
    static const TUint kMaxResourcePrefixBytes = 25;
    static const Brn kDefaultLanguage;
    typedef std::vector<const OpenHome::Brx*> KeyVector;
    typedef std::pair<OpenHome::Brn, OpenHome::Brx*> JsonPair;
    typedef std::map<OpenHome::Brn, OpenHome::Brx*, OpenHome::BufferCmp> JsonMap;
protected:
    ConfigAppBase(OpenHome::Configuration::IConfigManager& aConfigManager, const OpenHome::Brx& aResourcePrefix, const OpenHome::Brx& aResourceDir, TUint aMaxTabs, TUint aSendQueueSize);
    ~ConfigAppBase();
public: // from IConfigApp
    ITab& Create(ITabHandler& aHandler, std::vector<const Brx*>& aLanguageList) override;
    const OpenHome::Brx& ResourcePrefix() const override;
    IResourceHandler& CreateResourceHandler(const OpenHome::Brx& aResource) override;
public: // from IJsonProvider
    const OpenHome::Brx& GetJson(const OpenHome::Brx& aKey) override;
public: // from ILanguageResourceManager
    ILanguageResourceReader& CreateLanguageResourceHandler(const Brx& aResourceUriTail, std::vector<const Brx*>& aLanguageList) override;
protected:
    void AddNum(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo);
    void AddChoice(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo);
    void AddText(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo);
private:
    void AddJson(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo);
protected:
    OpenHome::Configuration::IConfigManager& iConfigManager;
private:
    ConfigMessageAllocator* iMsgAllocator;
    const OpenHome::Bws<kMaxResourcePrefixBytes> iResourcePrefix;
    std::vector<FileResourceHandler*> iResourceHandlers;
    std::vector<LanguageResourceFileReader*> iLanguageResourceHandlers;
    std::vector<ConfigTab*> iTabs;
    KeyVector iKeysNums;
    KeyVector iKeysChoices;
    KeyVector iKeysTexts;
    JsonMap iJsonMap;       // additional JSON for all ConfigVals
    OpenHome::Mutex iLock;
};

class ConfigAppBasic : public ConfigAppBase
{
public:
     ConfigAppBasic(OpenHome::Configuration::IConfigManager& aConfigManager, const OpenHome::Brx& aResourcePrefix, const OpenHome::Brx& aResourceDir, TUint aMaxTabs, TUint aSendQueueSize);
};

class ConfigAppSources : public ConfigAppBasic
{
public:
     ConfigAppSources(OpenHome::Configuration::IConfigManager& aConfigManager, std::vector<const Brx*>& aSources, const OpenHome::Brx& aResourcePrefix, const OpenHome::Brx& aResourceDir, TUint aMaxTabs, TUint aSendQueueSize);
};

class ConfigAppMediaPlayer : public ConfigAppSources
{
public:
     ConfigAppMediaPlayer(OpenHome::Configuration::IConfigManager& aConfigManager, std::vector<const Brx*>& aSources, const OpenHome::Brx& aResourcePrefix, const OpenHome::Brx& aResourceDir, TUint aMaxTabs, TUint aSendQueueSize);
private:
    void AddNumConditional(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo);
    void AddChoiceConditional(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo);
    void AddTextConditional(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo);
};


} // namespace Web
} // namespace OpenHome

#endif // HEADER_WEB_CONFIGUI
