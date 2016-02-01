#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Web/ConfigUi/ConfigUi.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/Utils/Json.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Av/RebootHandler.h>
#include <OpenHome/Private/Debug.h>

#include <limits>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;
using namespace OpenHome::Web;


// WritableJsonEmpty

void WritableJsonEmpty::Write(IWriter& aWriter) const
{
    aWriter.Write(Brn("{}"));
}


// WritableJsonInfo

WritableJsonInfo::WritableJsonInfo(TBool aRebootRequired)
    : iRebootRequired(aRebootRequired)
{
}

void WritableJsonInfo::Write(IWriter& aWriter) const
{
    aWriter.Write(Brn("{\"reboot-required\":"));
    WriteBool(aWriter, iRebootRequired);
    aWriter.Write(Brn("}"));
}

void WritableJsonInfo::WriteBool(IWriter& aWriter, TBool aValue)
{
    if (aValue) {
        aWriter.Write(Brn("true"));
    }
    else {
        aWriter.Write(Brn("false"));
    }
}


// ConfigMessageBase

ConfigMessageBase::ConfigMessageBase(AllocatorBase& aAllocator)
    : Allocated(aAllocator)
    , iWriterAdditional(nullptr)
{
}

void ConfigMessageBase::Clear()
{
}

void ConfigMessageBase::Destroy()
{
    RemoveRef();
}


// ConfigMessageInt

ConfigMessageInt::ConfigMessageInt(AllocatorBase& aAllocator)
    : ConfigMessageBase(aAllocator)
    , iUiVal(nullptr)
    , iUpdatedVal(std::numeric_limits<TInt>::max())
    , iLanguageResourceManager(nullptr)
    , iLanguageList(nullptr)
{
}

void ConfigMessageInt::Set(IConfigUiVal& aUiVal, TInt aUpdatedVal, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList)
{
    ASSERT(iUiVal == nullptr);
    iUiVal = &aUiVal;
    iUpdatedVal = aUpdatedVal;
    iLanguageResourceManager = &aLanguageResourceManager;
    iLanguageList = &aLanguageList;
}

void ConfigMessageInt::Clear()
{
    ConfigMessageBase::Clear();
    ASSERT(iUiVal != nullptr);
    iUiVal = nullptr;
    iUpdatedVal = std::numeric_limits<TInt>::max();
    iLanguageResourceManager = nullptr;
    iLanguageList = nullptr;
}

void ConfigMessageInt::Send(IWriter& aWriter)
{
    ASSERT(iUiVal != nullptr);
    iUiVal->WriteJson(aWriter, *this, *iLanguageResourceManager, *iLanguageList);
}

void ConfigMessageInt::WriteValueJson(IWriter& aWriter)
{
    ASSERT(iUiVal != nullptr);
    Ascii::StreamWriteInt(aWriter, iUpdatedVal);
}


// ConfigChoiceMappingWriterJson

ConfigChoiceMappingWriterJson::ConfigChoiceMappingWriterJson()
    : iStarted(false)
{
}

void ConfigChoiceMappingWriterJson::Write(IWriter& aWriter, TUint aChoice, const Brx& aMapping)
{
    if (!iStarted) {
        aWriter.Write(Brn("\"options\":["));
    }
    else {
        aWriter.Write(',');
    }

    aWriter.Write(Brn("{"));
    aWriter.Write(Brn("\"id\": "));
    Ascii::StreamWriteUint(aWriter, aChoice);
    aWriter.Write(Brn(",\"value\": \""));
    Json::Escape(aWriter, aMapping);
    aWriter.Write(Brn("\"}"));
    iStarted = true;
}

void ConfigChoiceMappingWriterJson::WriteComplete(IWriter& aWriter)
{
    aWriter.Write(Brn("]"));
}


// ConfigChoiceMapperResourceFile

ConfigChoiceMapperResourceFile::ConfigChoiceMapperResourceFile(const Brx& aKey, const std::vector<TUint>& aChoices, IWriter& aWriter, IConfigChoiceMappingWriter& aMappingWriter)
    : iKey(aKey)
    , iChoices(aChoices)
    , iWriter(aWriter)
    , iMappingWriter(aMappingWriter)
    , iChoicesIndex(0)
    , iFoundKey(false)
{
}

TBool ConfigChoiceMapperResourceFile::ProcessLine(const Brx& aLine)
{
    if (!iFoundKey) {
        iFoundKey = Ascii::Contains(aLine, iKey);
        return true;
    }
    Parser p(aLine);
    Brn idBuf = p.Next();
    Brn valueBuf = p.NextToEnd();
    ASSERT(valueBuf.Bytes() > 0);
    try {
        TUint id = Ascii::Uint(idBuf);
        ASSERT(id == iChoices[iChoicesIndex]);
    }
    catch (AsciiError&) {
        ASSERTS();
    }

    try {
        iMappingWriter.Write(iWriter, iChoices[iChoicesIndex], valueBuf);
        if (++iChoicesIndex == iChoices.size()) {
            iMappingWriter.WriteComplete(iWriter);
            return false;
        }
    }
    catch (WriterError&) {
        LOG(kHttp, "ConfigChoiceMapperResourceFile::ProcessLine WriterError");
        return false;
    }
    return true;
}


// ConfigMessageUint

ConfigMessageUint::ConfigMessageUint(AllocatorBase& aAllocator)
    : ConfigMessageBase(aAllocator)
    , iUiVal(nullptr)
    , iUpdatedVal(std::numeric_limits<TUint>::max())
    , iLanguageResourceManager(nullptr)
    , iLanguageList(nullptr)
{
}

void ConfigMessageUint::Set(IConfigUiVal& aUiVal, TUint aUpdatedVal, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList)
{
    ASSERT(iUiVal == nullptr);
    iUiVal = &aUiVal;
    iUpdatedVal = aUpdatedVal;
    iLanguageResourceManager = &aLanguageResourceManager;
    iLanguageList = &aLanguageList;
}

void ConfigMessageUint::Clear()
{
    ConfigMessageBase::Clear();
    ASSERT(iUiVal != nullptr);
    iUiVal = nullptr;
    iUpdatedVal = std::numeric_limits<TInt>::max();
    iLanguageResourceManager = nullptr;
    iLanguageList = nullptr;
}

void ConfigMessageUint::Send(IWriter& aWriter)
{
    ASSERT(iUiVal != nullptr);
    iUiVal->WriteJson(aWriter, *this, *iLanguageResourceManager, *iLanguageList);
}

void ConfigMessageUint::WriteValueJson(IWriter& aWriter)
{
    ASSERT(iUiVal != nullptr);
    Ascii::StreamWriteUint(aWriter, iUpdatedVal);
}


// ConfigMessageString

ConfigMessageString::ConfigMessageString(AllocatorBase& aAllocator)
    : ConfigMessageBase(aAllocator)
    , iUiVal(nullptr)
    , iLanguageResourceManager(nullptr)
    , iLanguageList(nullptr)
{
}

void ConfigMessageString::Set(IConfigUiVal& aUiVal, const Brx& aUpdatedVal, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList)
{
    ASSERT(iUiVal == nullptr);
    iUiVal = &aUiVal;
    iUpdatedVal.Replace(aUpdatedVal);
    iLanguageResourceManager = &aLanguageResourceManager;
    iLanguageList = &aLanguageList;
}

void ConfigMessageString::Clear()
{
    ConfigMessageBase::Clear();
    ASSERT(iUiVal != nullptr);
    iUiVal = nullptr;
    iUpdatedVal.SetBytes(0);
    iLanguageResourceManager = nullptr;
    iLanguageList = nullptr;
}

void ConfigMessageString::Send(IWriter& aWriter)
{
    ASSERT(iUiVal != nullptr);
    iUiVal->WriteJson(aWriter, *this, *iLanguageResourceManager, *iLanguageList);
}

void ConfigMessageString::WriteValueJson(IWriter& aWriter)
{
    ASSERT(iUiVal != nullptr);
    Json::Escape(aWriter, iUpdatedVal);
}


// ConfigMessageAllocator

ConfigMessageAllocator::ConfigMessageAllocator(IInfoAggregator& aInfoAggregator, TUint aMsgCountInt, TUint aMsgCountUint, TUint aMsgCountString, ILanguageResourceManager& aLanguageResourceManager)
    : iAllocatorMsgInt("ConfigMessageInt", aMsgCountInt, aInfoAggregator)
    , iAllocatorMsgUint("ConfigMessageUint", aMsgCountUint, aInfoAggregator)
    , iAllocatorMsgString("ConfigMessageText", aMsgCountString, aInfoAggregator)
    , iLanguageResourceManager(aLanguageResourceManager)
{
}

ITabMessage* ConfigMessageAllocator::AllocateInt(IConfigUiVal& aUiVal, TInt aUpdatedVal, std::vector<Bws<10>>& aLanguageList)
{
    ConfigMessageInt* msg = iAllocatorMsgInt.Allocate();
    msg->Set(aUiVal, aUpdatedVal, iLanguageResourceManager, aLanguageList);
    return msg;
}

ITabMessage* ConfigMessageAllocator::AllocateUint(IConfigUiVal& aUiVal, TUint aUpdatedVal, std::vector<Bws<10>>& aLanguageList)
{
    ConfigMessageUint* msg = iAllocatorMsgUint.Allocate();
    msg->Set(aUiVal, aUpdatedVal, iLanguageResourceManager, aLanguageList);
    return msg;
}

ITabMessage* ConfigMessageAllocator::AllocateString(IConfigUiVal& aUiVal, const Brx& aUpdatedVal, std::vector<Bws<10>>& aLanguageList)
{
    ConfigMessageString* msg = iAllocatorMsgString.Allocate();
    msg->Set(aUiVal, aUpdatedVal, iLanguageResourceManager, aLanguageList);
    return msg;
}


// JsonStringParser

Brn JsonStringParser::ParseString(const Brx& aBuffer, Brn& aRemaining)
{
    TUint offset = 0;

    // Skip any whitespace.
    for (TUint i=0; i<aBuffer.Bytes(); i++) {
        if (!Ascii::IsWhitespace(aBuffer[i])) {
            offset = i;
            break;
        }
    }

    if (aBuffer[offset] != '"') {
        THROW(JsonStringError);
    }
    offset++;   // Move past opening '"'.

    for (TUint i=offset; i<aBuffer.Bytes(); i++) {
        if (aBuffer[i] == '"') {
            if (aBuffer[i-1] != '\\') {
                const TUint bytes = i-offset;
                i++;
                ASSERT(aBuffer.Bytes() > i);
                if (aBuffer.Bytes()-i == 0) {
                    aRemaining.Set(Brn::Empty());
                }
                else {
                    aRemaining.Set(aBuffer.Ptr()+i, aBuffer.Bytes()-i);
                }

                if (bytes == 0) {
                    return Brn::Empty();
                }
                else {
                    return Brn(aBuffer.Ptr()+offset, bytes);
                }
            }
        }
    }

    THROW(JsonStringError);
}


// ConfigTabReceiver

ConfigTabReceiver::ConfigTabReceiver()
{
}

void ConfigTabReceiver::Receive(const Brx& aMessage)
{
    // FIXME - what if aMessage is malformed? - call some form of error handler?
    // FIXME - this should maybe also take an IWriter to allow writing out of a response (which could be none if successful, and an error description if unsuccessful/malformed request).

    // Parse JSON response.
    Bws<128> keyBuf;
    Bws<1024> valueBuf;
    Brn remaining(aMessage);

    LOG(kHttp, "ConfigTabReceiver::Receive:\n%.*s\n", PBUF(aMessage));

    try {
        Parser p(aMessage);
        (void)p.Next('{');
        Brn request = JsonStringParser::ParseString(p.Remaining(), remaining);

        if (request != Brn("request")) {
            LOG(kHttp, "ConfigTabReceiver::Receive Unknown response.\n");
            return;
        }

        p.Set(remaining);
        (void)p.Next('{');
        (void)JsonStringParser::ParseString(p.Remaining(), remaining);  // "type"
        p.Set(remaining);
        (void)p.Next(':');
        Brn type = JsonStringParser::ParseString(p.Remaining(), remaining);

        if (type == Brn("update")) {
            p.Set(remaining);
            (void)p.Next(',');
            (void)JsonStringParser::ParseString(p.Remaining(), remaining);  // "key"

            p.Set(remaining);
            (void)p.Next(':');
            Brn key = JsonStringParser::ParseString(p.Remaining(), remaining);

            p.Set(remaining);
            (void)p.Next(',');
            (void)JsonStringParser::ParseString(p.Remaining(), remaining);  // "value"

            p.Set(remaining);
            (void)p.Next(':');
            Brn value = JsonStringParser::ParseString(p.Remaining(), remaining);

            keyBuf.Replace(key);
            Json::Unescape(keyBuf);
            valueBuf.Replace(value);
            Json::Unescape(valueBuf);
            Receive(keyBuf, valueBuf);
        }
        else if (type == Brn("reboot")) {
            // FIXME - passing on reboot call here means that the DS may reboot before this call returns, so the WebAppFramework may not get chance to send a response to the UI (but does that matter, as the device is going to abruptly disappear at some point in the near future?).
            Reboot();
        }
    }
    catch (JsonStringError&) {
        LOG(kHttp, "ConfigTabReceiver::Receive caught JsonStringError: %.*s\n", PBUF(aMessage));
    }
}


// ConfigTab

const TUint ConfigTab::kInvalidSubscription = OpenHome::Configuration::IConfigManager::kSubscriptionIdInvalid;

ConfigTab::ConfigTab(TUint aId, IConfigMessageAllocator& aMessageAllocator, IConfigManager& aConfigManager, IRebootHandler& aRebootHandler)
    : iId(aId)
    , iConfigManager(aConfigManager)
    , iMsgAllocator(aMessageAllocator)
    , iRebootHandler(aRebootHandler)
    , iHandler(nullptr)
    , iStarted(false)
{
}

ConfigTab::~ConfigTab()
{
    if (iHandler != nullptr) {
        Destroy();
    }
}

void ConfigTab::AddValue(IConfigUiVal& aValue)
{
    ASSERT(!iStarted);
    iConfigUiVals.push_back(SubscriptionPair(&aValue, kInvalidSubscription));
}

// FIXME - remove?
void ConfigTab::Start()
{
    ASSERT(!iStarted);
    ASSERT(iConfigUiVals.size() > 0);
    iStarted = true;
}

TBool ConfigTab::Allocated() const
{
    TBool allocated = iHandler != nullptr;
    return allocated;
}

void ConfigTab::SetHandler(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList)
{
    LOG(kHttp, "ConfigTab::SetHandler iId: %u\n", iId);
    ASSERT(iHandler == nullptr);
    iLanguageList.clear();
    for (auto it=aLanguageList.begin(); it!=aLanguageList.end(); ++it) {
        iLanguageList.push_back(*it);
    }
    iHandler = &aHandler;
    for (auto val : iConfigUiVals) {
        val.second = val.first->AddObserver(*this);
    }
}

void ConfigTab::Receive(const Brx& aKey, const Brx& aValue)
{
    // FIXME - backdoor trickery going on here. Accessing iConfigManager directly, when should really be updating value via IConfigUiVal object.

    // TabManager in HttpFramework should handle any race between Destroy() and
    // Receive() being called, as it will defer destruction of a tab until all
    // references are removed.
    if (iConfigManager.Has(aKey)) {
        ISerialisable& ser = iConfigManager.Get(aKey);
        try {
            ser.Deserialise(aValue);
        }
        // No exceptions should be thrown because all input verification should
        // be handled by browser side.
        catch (ConfigNotANumber&) {
            ASSERTS();
        }
        catch (ConfigValueOutOfRange&) {
            ASSERTS();
        }
        catch (ConfigValueTooLong&) {
            ASSERTS();
        }
        catch (ConfigInvalidSelection&) {
            ASSERTS();
        }
    }
    else {
        ASSERTS(); // Browser code tried to pass in an invalid ConfigVal. Developer error.
    }
}

void ConfigTab::Reboot()
{
    iRebootHandler.Reboot(Brn("ConfigTab::Reboot"));
}

void ConfigTab::Destroy()
{
    LOG(kHttp, "ConfigTab::Destroy iId: %u\n", iId);
    ASSERT(iHandler != nullptr);
    iHandler = nullptr;

    for (auto val : iConfigUiVals) {
        val.first->RemoveObserver(val.second);
    }
}

void ConfigTab::ValueChangedInt(IConfigUiVal& aUiVal, TInt aUpdatedVal)
{
    ITabMessage* msg = iMsgAllocator.AllocateInt(aUiVal, aUpdatedVal, iLanguageList);
    iHandler->Send(*msg);
}

void ConfigTab::ValueChangedUint(IConfigUiVal& aUiVal, TUint aUpdatedVal)
{
    ITabMessage* msg = iMsgAllocator.AllocateUint(aUiVal, aUpdatedVal, iLanguageList);
    iHandler->Send(*msg);
}

void ConfigTab::ValueChangedString(IConfigUiVal& aUiVal, const Brx& aUpdatedVal)
{
    ITabMessage* msg = iMsgAllocator.AllocateString(aUiVal, aUpdatedVal, iLanguageList);
    iHandler->Send(*msg);
}


// ConfigUiValBase

ConfigUiValBase::ConfigUiValBase(IWritable& aAdditionalJson)
    : iAdditionalJson(aAdditionalJson)
    , iNextObserverId(kObserverIdInvalid+1)
    , iLockObservers("CUVL")
{
}

void ConfigUiValBase::WriteAdditional(IWriter& aWriter)
{
    iAdditionalJson.Write(aWriter);
}

void ConfigUiValBase::WriteJson(IWriter& aWriter, IConfigUiUpdateWriter& aValWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList)
{
    aWriter.Write(Brn("\"key\":"));
    WriteKey(aWriter);
    aWriter.Write(Brn(","));

    aWriter.Write(Brn("\"value\":"));
    aValWriter.WriteValueJson(aWriter);
    aWriter.Write(Brn(","));

    aWriter.Write(Brn("\"meta\":"));
    WriteMeta(aWriter, aLanguageResourceManager, aLanguageList);
    aWriter.Write(Brn(","));

    aWriter.Write(Brn("\"info\":"));
    WriteAdditional(aWriter);
}

void ConfigUiValBase::ValueChangedInt(TInt aValue)
{
    AutoMutex a(iLockObservers);
    for (auto it : iObservers) {
        it.second->ValueChangedInt(*this, aValue);
    }
}

void ConfigUiValBase::ValueChangedUint(TUint aValue)
{
    AutoMutex a(iLockObservers);
    for (auto it : iObservers) {
        it.second->ValueChangedUint(*this, aValue);
    }
}

void ConfigUiValBase::ValueChangedString(const Brx& aValue)
{
    AutoMutex a(iLockObservers);
    for (auto it : iObservers) {
        it.second->ValueChangedString(*this, aValue);
    }
}

TUint ConfigUiValBase::AddObserver(IConfigUiValObserver& aObserver)
{
    AutoMutex a(iLockObservers);
    const TUint id = iNextObserverId++;
    iObservers.insert(std::pair<TUint, IConfigUiValObserver*>(id, &aObserver));
    NotifyObserver(aObserver);
    return id;
}

void ConfigUiValBase::RemoveObserver(TUint aObserverId)
{
    AutoMutex a(iLockObservers);
    auto it = iObservers.find(aObserverId);
    if (it != iObservers.end()) {
        iObservers.erase(it);
    }
}


// ConfigUiValReadOnly

ConfigUiValReadOnly::ConfigUiValReadOnly(const Brx& aKey, const Brx& aValue)
    : ConfigUiValBase(iAdditional)
    , iKey(aKey)
    , iValue(aValue)
{
}

void ConfigUiValReadOnly::NotifyObserver(IConfigUiValObserver& aObserver)
{
    aObserver.ValueChangedString(*this, iValue);
}

void ConfigUiValReadOnly::WriteKey(IWriter& aWriter)
{
    Json::Escape(aWriter, iKey);
}

void ConfigUiValReadOnly::WriteType(IWriter& aWriter)
{
    aWriter.Write(Brn("\"read-only\""));
}

void ConfigUiValReadOnly::WriteMeta(IWriter& aWriter, ILanguageResourceManager& /*aLanguageResourceManager*/, std::vector<Bws<10>>& /*aLanguageList*/)
{
    aWriter.Write(Brn("{}"));
}


// ConfigUiValNum

ConfigUiValNum::ConfigUiValNum(Configuration::ConfigNum& aNum, IWritable& aAdditionalJson)
    : ConfigUiValBase(aAdditionalJson)
    , iNum(aNum)
    , iListenerId(IConfigManager::kSubscriptionIdInvalid)
    , iVal(0)
    , iLock("CUNL")
{
    iListenerId = iNum.Subscribe(MakeFunctorConfigNum(*this, &ConfigUiValNum::Update));
}

ConfigUiValNum::~ConfigUiValNum()
{
    iNum.Unsubscribe(iListenerId);
}

void ConfigUiValNum::NotifyObserver(IConfigUiValObserver& aObserver)
{
    AutoMutex a(iLock);
    aObserver.ValueChangedInt(*this, iVal);
}

void ConfigUiValNum::WriteKey(IWriter& aWriter)
{
    Json::Escape(aWriter, iNum.Key());
}

void ConfigUiValNum::WriteType(IWriter& aWriter)
{
    aWriter.Write(Brn("\"numeric\""));
}

void ConfigUiValNum::WriteMeta(IWriter& aWriter, ILanguageResourceManager& /*aLanguageResourceManager*/, std::vector<Bws<10>>& /*aLanguageList*/)
{
    aWriter.Write('{');
    aWriter.Write(Brn("\"default\":"));
    Ascii::StreamWriteInt(aWriter, iNum.Default());
    aWriter.Write(Brn(","));
    aWriter.Write(Brn("\"min\":"));
    Ascii::StreamWriteInt(aWriter, iNum.Min());
    aWriter.Write(Brn(","));
    aWriter.Write(Brn("\"max\":"));
    Ascii::StreamWriteInt(aWriter, iNum.Max());
    aWriter.Write('}');
}

void ConfigUiValNum::Update(Configuration::ConfigNum::KvpNum& aKvp)
{
    AutoMutex a(iLock);
    iVal = aKvp.Value();
    ValueChangedInt(iVal);
}


// ConfigUiValChoice

ConfigUiValChoice::ConfigUiValChoice(Configuration::ConfigChoice& aChoice, IWritable& aAdditionalJson)
    : ConfigUiValBase(aAdditionalJson)
    , iChoice(aChoice)
    , iListenerId(IConfigManager::kSubscriptionIdInvalid)
    , iVal(0)
    , iLock("CUCL")
{
    iListenerId = iChoice.Subscribe(MakeFunctorConfigChoice(*this, &ConfigUiValChoice::Update));
}

ConfigUiValChoice::~ConfigUiValChoice()
{
    iChoice.Unsubscribe(iListenerId);
}

void ConfigUiValChoice::NotifyObserver(IConfigUiValObserver& aObserver)
{
    AutoMutex a(iLock);
    aObserver.ValueChangedUint(*this, iVal);
}

void ConfigUiValChoice::WriteKey(IWriter& aWriter)
{
    Json::Escape(aWriter, iChoice.Key());
}

void ConfigUiValChoice::WriteType(IWriter& aWriter)
{
    aWriter.Write(Brn("\"choice\""));
}

void ConfigUiValChoice::WriteMeta(IWriter& aWriter, ILanguageResourceManager& aLanguageResourceManager, std::vector<Bws<10>>& aLanguageList)
{
    aWriter.Write('{');
    aWriter.Write(Brn("\"default\":"));
    Ascii::StreamWriteUint(aWriter, iChoice.Default());
    aWriter.Write(Brn(","));
    if (iChoice.HasInternalMapping()) {
        IConfigChoiceMapper& mapper = iChoice.Mapper();
        ConfigChoiceMappingWriterJson mappingWriter;
        mapper.Write(aWriter, mappingWriter);
    }
    else {
        // Read mapping from file.
        static const Brn kConfigOptionsFile("ConfigOptions.txt");
        const std::vector<TUint>& choices = iChoice.Choices();
        ConfigChoiceMappingWriterJson mappingWriter;
        ConfigChoiceMapperResourceFile mapper(iChoice.Key(), choices, aWriter, mappingWriter);
        ILanguageResourceReader* resourceHandler = &aLanguageResourceManager.CreateLanguageResourceHandler(kConfigOptionsFile, aLanguageList);
        resourceHandler->Process(mapper);
        //resourceHandler->Destroy();
    }
    aWriter.Write('}');
}

void ConfigUiValChoice::Update(Configuration::ConfigChoice::KvpChoice& aKvp)
{
    AutoMutex a(iLock);
    iVal = aKvp.Value();
    ValueChangedUint(iVal);
}


// ConfigUiValText

ConfigUiValText::ConfigUiValText(Configuration::ConfigText& aText, IWritable& aAdditionalJson)
    : ConfigUiValBase(aAdditionalJson)
    , iText(aText)
    , iListenerId(IConfigManager::kSubscriptionIdInvalid)
    , iLock("CUTL")
{
    iListenerId = iText.Subscribe(MakeFunctorConfigText(*this, &ConfigUiValText::Update));
}

ConfigUiValText::~ConfigUiValText()
{
    iText.Unsubscribe(iListenerId);
}

void ConfigUiValText::NotifyObserver(IConfigUiValObserver& aObserver)
{
    AutoMutex a(iLock);
    aObserver.ValueChangedString(*this, iVal);
}

void ConfigUiValText::WriteKey(IWriter& aWriter)
{
    Json::Escape(aWriter, iText.Key());
}

void ConfigUiValText::WriteType(IWriter& aWriter)
{
    aWriter.Write(Brn("\"text\""));
}

void ConfigUiValText::WriteMeta(IWriter& aWriter, ILanguageResourceManager& /*aLanguageResourceManager*/, std::vector<Bws<10>>& /*aLanguageList*/)
{
    aWriter.Write('{');
    aWriter.Write(Brn("\"default\":"));
    aWriter.Write(Brn("\""));
    Json::Escape(aWriter, iText.Default());
    aWriter.Write(Brn("\""));
    aWriter.Write(Brn(","));
    aWriter.Write(Brn("\"maxlength\":"));
    Ascii::StreamWriteUint(aWriter, iText.MaxLength());
    aWriter.Write('}');
}

void ConfigUiValText::Update(Configuration::ConfigText::KvpText& aKvp)
{
    AutoMutex a(iLock);
    iVal.Replace(aKvp.Value());
    ValueChangedString(iVal);
}


// ConfigAppBase

const Brn ConfigAppBase::kLangRoot("lang");
const Brn ConfigAppBase::kDefaultLanguage("en-gb");

ConfigAppBase::ConfigAppBase(IInfoAggregator& aInfoAggregator, IConfigManager& aConfigManager, IConfigAppResourceHandlerFactory& aResourceHandlerFactory, const Brx& aResourcePrefix, const Brx& aResourceDir, TUint aMaxTabs, TUint aSendQueueSize, IRebootHandler& aRebootHandler)
    : iConfigManager(aConfigManager)
    , iLangResourceDir(aResourceDir.Bytes()+1+kLangRoot.Bytes()+1)  // "<aResourceDir>/<kLangRoot>/"
    , iResourcePrefix(aResourcePrefix)
    , iLock("COAL")
{
    Log::Print("ConfigAppBase::ConfigAppBase iResourcePrefix: ");
    Log::Print(iResourcePrefix);
    Log::Print("\n");

    iLangResourceDir.Replace(aResourceDir);
    if (iLangResourceDir.Bytes() == 0 || iLangResourceDir[iLangResourceDir.Bytes()-1] != '/') {
        iLangResourceDir.Append('/');
    }
    iLangResourceDir.Append(kLangRoot);
    iLangResourceDir.Append('/');

    iMsgAllocator = new ConfigMessageAllocator(aInfoAggregator, aSendQueueSize, aSendQueueSize, aSendQueueSize, *this);

    for (TUint i=0; i<aMaxTabs; i++) {
        iResourceHandlers.push_back(aResourceHandlerFactory.NewResourceHandler(aResourceDir));
        iTabs.push_back(new ConfigTab(i, *iMsgAllocator, iConfigManager, aRebootHandler));
    }

    for (TUint i=0; i<aMaxTabs; i++) {
        iLanguageResourceHandlers.push_back(aResourceHandlerFactory.NewLanguageReader(iLangResourceDir));
    }
}

ConfigAppBase::~ConfigAppBase()
{
    for (TUint i=0; i<iLanguageResourceHandlers.size(); i++) {
        delete iLanguageResourceHandlers[i];
    }

    for (TUint i=0; i<iTabs.size(); i++) {
        delete iTabs[i];
        delete iResourceHandlers[i];
    }

    for (auto val : iUiVals) {
        delete val;
    }

    delete iMsgAllocator;
}

// FIXME - is this really required? If so, app framework should call it when it is started
//void ConfigAppBase::Start()
//{
//    for (TUint i=0; i<iTabs.size(); i++) {
//        iTabs[i]->Start();
//    }
//}

ITab& ConfigAppBase::Create(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList)
{
    AutoMutex a(iLock);
    for (TUint i=0; i<iTabs.size(); i++) {
        if (!iTabs[i]->Allocated()) {
            // FIXME - won't be cleared until a new handler is set.
            // Shouldn't matter as only thing that can call tab handler is the
            // tab, which gets destroyed when it is no longer in use.
            iTabs[i]->SetHandler(aHandler, aLanguageList);
            return *iTabs[i];
        }
    }
    THROW(TabAllocatorFull);
}

const Brx& ConfigAppBase::ResourcePrefix() const
{
    return iResourcePrefix;
}

IResourceHandler& ConfigAppBase::CreateResourceHandler(const OpenHome::Brx& aResource)
{
    AutoMutex a(iLock);
    for (TUint i=0; i<iResourceHandlers.size(); i++) {
        if (!iResourceHandlers[i]->Allocated()) {
            IResourceHandler& handler = *iResourceHandlers[i];
            handler.SetResource(aResource);
            return handler;
        }
    }
    ASSERTS();  // FIXME - throw exception instead?
    // Could throw a ResourceHandlerFull if temporarily unavailable, and send an appropriate error response to browser.
    // However, in most cases, this should never happen. If it does (repeatedly) it likely means resource handlers aren't being returned/Destroy()ed.
    return *iResourceHandlers[0];   // unreachable
}

ILanguageResourceReader& ConfigAppBase::CreateLanguageResourceHandler(const Brx& aResourceUriTail, std::vector<Bws<10>>& aLanguageList)
{
    // If no desired language can be found, should default to English.
    // Developer error if English mappings don't exist.
    std::vector<Bws<10>> languages(aLanguageList);
    Bws<10> def(kDefaultLanguage);
    languages.push_back(def);

    AutoMutex a(iLock);
    for (TUint i=0; i<iLanguageResourceHandlers.size(); i++) {
        if (!iLanguageResourceHandlers[i]->Allocated()) {
            for (TUint j=0; j<languages.size(); j++) {
                Bws<Uri::kMaxUriBytes> resource(languages[j]);
                resource.Append("/");
                resource.Append(aResourceUriTail);
                try {
                    ILanguageResourceReader& handler = *iLanguageResourceHandlers[i];
                    handler.SetResource(resource);
                    return handler;
                }
                catch (LanguageResourceInvalid&) {
                    LOG(kHttp, "ConfigAppBase::CreateLanguageResourceHandler no mapping found for: %.*s\n", PBUF(resource));
                }
            }
            ASSERTS();  // No mapping found; should have been able to find kDefaultLanguage
        }
    }
    ASSERTS();  // No free handler available. // FIXME - throw exception instead?
    return *iLanguageResourceHandlers[0];   // unreachable
}

void ConfigAppBase::AddValue(IConfigUiVal* aValue)
{
    iUiVals.push_back(aValue);
    for (auto tab : iTabs) {
        tab->AddValue(*aValue);
    }
}


// ConfigAppBasic

ConfigAppBasic::ConfigAppBasic(IInfoAggregator& aInfoAggregator, IConfigManager& aConfigManager, IConfigAppResourceHandlerFactory& aResourceHandlerFactory, const Brx& aResourcePrefix, const Brx& aResourceDir, TUint aMaxTabs, TUint aSendQueueSize, IRebootHandler& aRebootHandler)
    : ConfigAppBase(aInfoAggregator, aConfigManager, aResourceHandlerFactory, aResourcePrefix, aResourceDir, aMaxTabs, aSendQueueSize, aRebootHandler)
    , iRebootRequired(true)
{
    AddConfigText(Brn("Product.Name"));
    AddConfigText(Brn("Product.Room"));
}

void ConfigAppBasic::AddConfigNum(const Brx& aKey, TBool aRebootRequired)
{
    if (aRebootRequired) {
        AddValue(new ConfigUiValNum(iConfigManager.GetNum(aKey), iRebootRequired));
    }
    else {
        AddValue(new ConfigUiValNum(iConfigManager.GetNum(aKey), iRebootNotRequired));
    }
}

void ConfigAppBasic::AddConfigChoice(const Brx& aKey, TBool aRebootRequired)
{
    if (aRebootRequired) {
        AddValue(new ConfigUiValChoice(iConfigManager.GetChoice(aKey), iRebootRequired));
    }
    else {
        AddValue(new ConfigUiValChoice(iConfigManager.GetChoice(aKey), iRebootNotRequired));
    }
}

void ConfigAppBasic::AddConfigText(const Brx& aKey, TBool aRebootRequired)
{
    if (aRebootRequired) {
        AddValue(new ConfigUiValText(iConfigManager.GetText(aKey), iRebootRequired));
    }
    else {
        AddValue(new ConfigUiValText(iConfigManager.GetText(aKey), iRebootNotRequired));
    }
}


// ConfigAppSources

ConfigAppSources::ConfigAppSources(IInfoAggregator& aInfoAggregator, IConfigManager& aConfigManager, IConfigAppResourceHandlerFactory& aResourceHandlerFactory, const std::vector<const Brx*>& aSources, const Brx& aResourcePrefix, const Brx& aResourceDir, TUint aMaxTabs, TUint aSendQueueSize, IRebootHandler& aRebootHandler)
    : ConfigAppBasic(aInfoAggregator, aConfigManager, aResourceHandlerFactory, aResourcePrefix, aResourceDir, aMaxTabs, aSendQueueSize, aRebootHandler)
{
    // Get all product names.
    for (TUint i=0; i<aSources.size(); i++) {

        Bws<Av::Source::kKeySourceNameMaxBytes> key;
        Av::Source::GetSourceNameKey(*aSources[i], key);
        AddConfigText(key);

        Av::Source::GetSourceVisibleKey(*aSources[i], key);
        AddConfigNum(key); // FIXME - why not a ConfigChoice?
        //AddChoice(key);
    }

    AddConfigChoice(ConfigStartupSource::kKeySource);
}
