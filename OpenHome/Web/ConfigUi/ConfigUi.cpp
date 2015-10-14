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
#include <OpenHome/Private/Debug.h>

#include <limits>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Web;


// LanguageResourceFileReader

LanguageResourceFileReader::LanguageResourceFileReader(const Brx& aRootDir)
    : iRootDir(aRootDir)
    , iReadBuffer(iFileStream)
    , iReaderText(iReadBuffer)
    , iAllocated(false)
    , iLock("LRRL")
{
    ASSERT(iRootDir[iRootDir.Bytes()-1] == '/');    // expect trailing '/'
}

void LanguageResourceFileReader::SetResource(const Brx& aUriTail)
{
    AutoMutex a(iLock);
    Bws<Uri::kMaxUriBytes+1> filename(iRootDir);
    filename.Append(aUriTail);

    try {
        // FIXME - dynamic allocation!
        IFile* file = new FileAnsii(filename.PtrZ(), eFileReadOnly); // asserts if a file is already open
        iFileStream.SetFile(file);
        iAllocated = true;
    }
    catch (FileOpenError&) {
        LOG(kHttp, "LanguageResourceFileReader::SetResource failed to open resource: %.*s\n", PBUF(filename));
        THROW(LanguageResourceInvalid);
    }
}

TBool LanguageResourceFileReader::Allocated() const
{
    AutoMutex a(iLock);
    return iAllocated;
}
Brn LanguageResourceFileReader::ReadLine()
{
    AutoMutex a(iLock);
    return iReaderText.ReadLine();
}

void LanguageResourceFileReader::Destroy()
{
    AutoMutex a(iLock);
    iReaderText.ReadFlush();
    iFileStream.CloseFile();
    iAllocated = false;
}


// ConfigMessage

ConfigMessage::ConfigMessage(IConfigMessageDeallocator& aDeallocator)
    : iDeallocator(aDeallocator)
{
}

void ConfigMessage::Set(const Brx& aAdditionalJson) {
    ASSERT(aAdditionalJson.Bytes() < kMaxAdditionalDataBytes);
    iAdditionalJson.Replace(aAdditionalJson);
}

void ConfigMessage::Set(ConfigNum& /*aNum*/, TInt /*aValue*/, const Brx& /*aAdditionalJson*/)
{
    ASSERTS();
}

void ConfigMessage::Set(ConfigChoice& /*aChoice*/, TUint /*aValue*/, const Brx& /*aAdditionalJson*/, std::vector<const Brx*>& /*aLanguageList*/)
{
    ASSERTS();
}

void ConfigMessage::Set(ConfigText& /*aText*/, const OpenHome::Brx& /*aValue*/, const Brx& /*aAdditionalJson*/)
{
    ASSERTS();
}

void ConfigMessage::Clear()
{
    iAdditionalJson.SetBytes(0);
}

void ConfigMessage::Send(IWriter& aWriter)
{
    // {
    //     "key": aKey,
    //     "value": aValue,
    //     "type": aType,
    //     "meta": {}
    //     "info": {}
    // }

    aWriter.Write(Brn("{"));

    aWriter.Write(Brn("\"key\":"));
    WriteKey(aWriter);
    aWriter.Write(Brn(","));

    aWriter.Write(Brn("\"value\":"));
    WriteValue(aWriter);
    aWriter.Write(Brn(","));

    aWriter.Write(Brn("\"type\":"));
    WriteType(aWriter);
    aWriter.Write(Brn(","));

    aWriter.Write(Brn("\"meta\":{"));
    WriteMeta(aWriter);
    aWriter.Write(Brn("}"));

    // FIXME - write out "additional"/"info" regardless of whether it contains anything?
    //aWriter.Write(Brn("\"info\":{"));
    if (iAdditionalJson != Brx::Empty()) {
        aWriter.Write(Brn(","));
        aWriter.Write(iAdditionalJson); // FIXME - this is going to write out "additional: {<kvps>}"
    }
    //aWriter.Write(Brn("}"));

    aWriter.Write(Brn("}"));
}

void ConfigMessage::Destroy()
{
    Clear();
    iDeallocator.Deallocate(*this);
}


// ConfigMessageNum

ConfigMessageNum::ConfigMessageNum(IConfigMessageDeallocator& aDeallocator)
    : ConfigMessage(aDeallocator)
    , iNum(nullptr)
    , iValue(std::numeric_limits<TInt>::max())
{
}

void ConfigMessageNum::Set(ConfigNum& aNum, TInt aValue, const Brx& aAdditionalJson)
{
    ConfigMessage::Set(aAdditionalJson);
    ASSERT(iNum == nullptr);
    iNum = &aNum;
    iValue = aValue;
}

void ConfigMessageNum::Clear()
{
    ASSERT(iNum != nullptr);
    ConfigMessage::Clear();
    iNum = nullptr;
    iValue = std::numeric_limits<TInt>::max();
}

void ConfigMessageNum::WriteKey(IWriter& aWriter)
{
    aWriter.Write(Brn("\""));
    Json::Escape(aWriter, iNum->Key());
    aWriter.Write(Brn("\""));
}

void ConfigMessageNum::WriteValue(IWriter& aWriter)
{
    Ascii::StreamWriteInt(aWriter, iValue);
}

void ConfigMessageNum::WriteType(IWriter& aWriter)
{
    aWriter.Write(Brn("\"numeric\""));
}

void ConfigMessageNum::WriteMeta(IWriter& aWriter)
{
    aWriter.Write(Brn("\"min\":"));
    Ascii::StreamWriteInt(aWriter, iNum->Min());
    aWriter.Write(Brn(","));
    aWriter.Write(Brn("\"max\":"));
    Ascii::StreamWriteInt(aWriter, iNum->Max());
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

ConfigChoiceMapperResourceFile::ConfigChoiceMapperResourceFile(ILanguageResourceReader& aReader, const Brx& aKey, const std::vector<TUint>& aChoices)
    : iReader(aReader)
    , iKey(aKey)
    , iChoices(aChoices)
{
}

void ConfigChoiceMapperResourceFile::Write(IWriter& aWriter, IConfigChoiceMappingWriter& aMappingWriter)
{
    TBool found = false;
    try {
        try {
            while (!found) {
                Brn line = iReader.ReadLine();
                if (Ascii::Contains(line, iKey)) {
                    found = true;
                }
            }
            ASSERT(found);

            for (TUint i=0; i<iChoices.size(); i++) {
                // Get next choice entry from file.
                Brn line = iReader.ReadLine();
                Parser p(line);
                Brn idBuf = p.Next();
                Brn valueBuf = p.NextToEnd();
                ASSERT(valueBuf.Bytes() > 0);
                try {
                    TUint id = Ascii::Uint(idBuf);
                    ASSERT(id == iChoices[i]);
                }
                catch (AsciiError&) {
                    ASSERTS();
                }

                aMappingWriter.Write(aWriter, iChoices[i], valueBuf);
            }
            aMappingWriter.WriteComplete(aWriter);
        }
        catch (ReaderError&) {
            LOG(kHttp, "ConfigChoiceMapperResourceFile::Write ReaderError");
            // This is reading from file, so shouldn't fail.
            // Indicative of reading beyond end of file (i.e., couldn't find desired value).
            ASSERTS();
        }

    }
    catch (WriterError&) {
        LOG(kHttp, "ConfigChoiceMapperResourceFile::Write WriterError");
        throw;
    }
}


// ConfigMessageChoice

ConfigMessageChoice::ConfigMessageChoice(IConfigMessageDeallocator& aDeallocator, ILanguageResourceManager& aLanguageResourceManager)
    : ConfigMessage(aDeallocator)
    , iLanguageResourceManager(aLanguageResourceManager)
    , iChoice(nullptr)
    , iValue(std::numeric_limits<TUint>::max())
{
}

void ConfigMessageChoice::Set(ConfigChoice& aChoice, TUint aValue, const Brx& aAdditionalJson, std::vector<const Brx*>& aLanguageList)
{
    ConfigMessage::Set(aAdditionalJson);
    ASSERT(iChoice == nullptr);
    iChoice = &aChoice;
    iValue = aValue;
    iLanguageList = &aLanguageList;
}

void ConfigMessageChoice::Clear()
{
    ASSERT(iChoice != nullptr);
    ConfigMessage::Clear();
    iChoice = nullptr;
    iValue = std::numeric_limits<TUint>::max();
    iLanguageList = nullptr;
}

void ConfigMessageChoice::WriteKey(IWriter& aWriter)
{
    aWriter.Write(Brn("\""));
    Json::Escape(aWriter, iChoice->Key());
    aWriter.Write(Brn("\""));
}

void ConfigMessageChoice::WriteValue(IWriter& aWriter)
{
    Ascii::StreamWriteUint(aWriter, iValue);
}

void ConfigMessageChoice::WriteType(IWriter& aWriter)
{
    aWriter.Write(Brn("\"choice\""));
}

void ConfigMessageChoice::WriteMeta(IWriter& aWriter)
{
    ILanguageResourceReader* resourceHandler = nullptr;
    try {
        if (iChoice->HasInternalMapping()) {
            IConfigChoiceMapper& mapper = iChoice->Mapper();
            ConfigChoiceMappingWriterJson mappingWriter;
            mapper.Write(aWriter, mappingWriter);
        }
        else {
            // Read mapping from file.
            static const Brn kConfigOptionsFile("ConfigOptions.txt");
            const std::vector<TUint>& choices = iChoice->Choices();
            resourceHandler = &iLanguageResourceManager.CreateLanguageResourceHandler(kConfigOptionsFile, *iLanguageList);
            ConfigChoiceMapperResourceFile mapper(*resourceHandler, iChoice->Key(), choices);
            ConfigChoiceMappingWriterJson mappingWriter;
            mapper.Write(aWriter, mappingWriter);
            resourceHandler->Destroy();
        }
    }
    catch (WriterError&) {
        resourceHandler->Destroy();
        // Convert (back) to WriterError.
        throw;
    }
}


// ConfigMessageText

ConfigMessageText::ConfigMessageText(IConfigMessageDeallocator& aDeallocator)
    : ConfigMessage(aDeallocator)
    , iText(nullptr)
    , iValue(kMaxBytes)
{
}

void ConfigMessageText::Set(ConfigText& aText, const OpenHome::Brx& aValue, const Brx& aAdditionalJson)
{
    ConfigMessage::Set(aAdditionalJson);
    ASSERT(iText == nullptr);
    iText = &aText;
    iValue.Replace(aValue);
}

void ConfigMessageText::Clear()
{
    ASSERT(iText != nullptr);
    ConfigMessage::Clear();
    iText = nullptr;
    iValue.SetBytes(0);
}

void ConfigMessageText::WriteKey(IWriter& aWriter)
{
    aWriter.Write(Brn("\""));
    Json::Escape(aWriter, iText->Key());
    aWriter.Write(Brn("\""));
}

void ConfigMessageText::WriteValue(IWriter& aWriter)
{
    aWriter.Write(Brn("\""));
    Json::Escape(aWriter, iValue);
    aWriter.Write(Brn("\""));
}

void ConfigMessageText::WriteType(IWriter& aWriter)
{
    aWriter.Write(Brn("\"text\""));
}

void ConfigMessageText::WriteMeta(IWriter& aWriter)
{
    aWriter.Write(Brn("\"maxlength\":"));
    Ascii::StreamWriteUint(aWriter, iText->MaxLength());
}


// ConfigMessageAllocatorBase

ConfigMessageAllocatorBase::ConfigMessageAllocatorBase(TUint aMessageCount)
    : iFifo(aMessageCount)
{
}

ConfigMessageAllocatorBase::~ConfigMessageAllocatorBase()
{
    ASSERT(iFifo.SlotsFree() == 0); // all allocated messages must have been Destroy()ed
    while (iFifo.SlotsUsed() > 0) {
        IConfigMessage* msg = iFifo.Read();
        delete msg;
    }
}

void ConfigMessageAllocatorBase::Deallocate(IConfigMessage& aMessage)
{
    // This should never have to block - only msgs written are msgs that have
    // previously been read from iFifo - so there should always be a slot.
    iFifo.Write(&aMessage);
}


// ConfigMessageNumAllocator

ConfigMessageNumAllocator::ConfigMessageNumAllocator(TUint aMessageCount)
    : ConfigMessageAllocatorBase(aMessageCount)
{
    for (TUint i=0; i<aMessageCount; i++) {
        iFifo.Write(new ConfigMessageNum(*this));
    }
}

IConfigMessage& ConfigMessageNumAllocator::Allocate(ConfigNum& aNum, TInt aValue, const Brx& aAdditionalJson)
{
    IConfigMessage& msg = *iFifo.Read();
    msg.Set(aNum, aValue, aAdditionalJson);
    return msg;
}


// ConfigMessageChoiceAllocator

ConfigMessageChoiceAllocator::ConfigMessageChoiceAllocator(TUint aMessageCount, ILanguageResourceManager& aLanguageResourceManager)
    : ConfigMessageAllocatorBase(aMessageCount)
{
    for (TUint i=0; i<aMessageCount; i++) {
        iFifo.Write(new ConfigMessageChoice(*this, aLanguageResourceManager));
    }
}

IConfigMessage& ConfigMessageChoiceAllocator::Allocate(ConfigChoice& aChoice, TUint aValue, const Brx& aAdditionalJson, std::vector<const Brx*>& aLanguageList)
{
    IConfigMessage& msg = *iFifo.Read();
    msg.Set(aChoice, aValue, aAdditionalJson, aLanguageList);
    return msg;
}


// ConfigMessageTextAllocator

ConfigMessageTextAllocator::ConfigMessageTextAllocator(TUint aMessageCount)
    : ConfigMessageAllocatorBase(aMessageCount)
{
    for (TUint i=0; i<aMessageCount; i++) {
        iFifo.Write(new ConfigMessageText(*this));
    }
}

IConfigMessage& ConfigMessageTextAllocator::Allocate(ConfigText& aText, const Brx& aValue, const Brx& aAdditionalJson)
{
    IConfigMessage& msg = *iFifo.Read();
    msg.Set(aText, aValue, aAdditionalJson);
    return msg;
}


// ConfigMessageAllocator

ConfigMessageAllocator::ConfigMessageAllocator(TUint aMessageCount, ILanguageResourceManager& aLanguageResourceManager)
    : iAllocatorNum(aMessageCount)
    , iAllocatorChoice(aMessageCount, aLanguageResourceManager)
    , iAllocatorText(aMessageCount)
{
}

IConfigMessage& ConfigMessageAllocator::Allocate(ConfigNum& aNum, TInt aValue, const Brx& aAdditionalJson)
{
    return iAllocatorNum.Allocate(aNum, aValue, aAdditionalJson);
}

IConfigMessage& ConfigMessageAllocator::Allocate(ConfigChoice& aChoice, TUint aValue, const Brx& aAdditionalJson, std::vector<const Brx*>& aLanguageList)
{
    return iAllocatorChoice.Allocate(aChoice, aValue, aAdditionalJson, aLanguageList);
}

IConfigMessage& ConfigMessageAllocator::Allocate(ConfigText& aText, const Brx& aValue, const Brx& aAdditionalJson)
{
    return iAllocatorText.Allocate(aText, aValue, aAdditionalJson);
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

    // Parse JSON response.
    Bws<128> key;
    Bws<1024> value;
    Brn remaining(aMessage);

    LOG(kHttp, "ConfigTabReceiver::Receive\n%.*s\n", PBUF(aMessage));

    try {
        Parser p(aMessage);
        (void)p.Next(':');  // {"key:
        key.Replace(JsonStringParser::ParseString(Brn(remaining.Ptr()+p.Index(), remaining.Bytes()-p.Index()+1), remaining));
        Json::Unescape(key);

        p.Set(remaining);
        (void)p.Next(':');  // ", value":
        value.Replace(JsonStringParser::ParseString(Brn(remaining.Ptr()+p.Index(), remaining.Bytes()-p.Index()+1), remaining));
        Json::Unescape(value);
        Receive(key, value);
    }
    catch (JsonStringError&) {
        LOG(kHttp, "ConfigTabReceiver::Receive caught JsonStringError: %.*s\n", PBUF(aMessage));
    }
}


// JsonKvp

void JsonKvp::Serialise(IWriter& aWriter) const
{
    SerialiseKey(aWriter);
    aWriter.Write(':');
    SerialiseValue(aWriter);
}

JsonKvp::JsonKvp(const Brx& aKey)
    : iKey(aKey)
{
}

void JsonKvp::SerialiseKey(IWriter& aWriter) const
{
    aWriter.Write('\"');
    aWriter.Write(iKey);
    aWriter.Write('\"');
}


// JsonKvpInt

JsonKvpInt::JsonKvpInt(const Brx& aKey, TInt aValue)
    : JsonKvp(aKey)
    , iValue(aValue)
{
}

void JsonKvpInt::SerialiseValue(IWriter& aWriter) const
{
    Ascii::StreamWriteInt(aWriter, iValue);
}


// JsonKvpUint

JsonKvpUint::JsonKvpUint(const Brx& aKey, TUint aValue)
    : JsonKvp(aKey)
    , iValue(aValue)
{
}

void JsonKvpUint::SerialiseValue(IWriter& aWriter) const
{
     Ascii::StreamWriteUint(aWriter, iValue);
}


// JsonKvpString

JsonKvpString::JsonKvpString(const Brx& aKey, const Brx& aValue)
    : JsonKvp(aKey)
    , iValue(aValue)
{
}

void JsonKvpString::SerialiseValue(IWriter& aWriter) const
{
    aWriter.Write('\"');
    aWriter.Write(iValue);
    aWriter.Write('\"');
}


// ConfigTab

const TUint ConfigTab::kInvalidSubscription = OpenHome::Configuration::IConfigManager::kSubscriptionIdInvalid;

ConfigTab::ConfigTab(TUint aId, IConfigMessageAllocator& aMessageAllocator, IConfigManager& aConfigManager, IJsonProvider& aJsonProvider)
    : iId(aId)
    , iMsgAllocator(aMessageAllocator)
    , iConfigManager(aConfigManager)
    , iJsonProvider(aJsonProvider)
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

void ConfigTab::AddKeyNum(const Brx& aKey)
{
    ASSERT(!iStarted);
    iConfigNums.push_back(SubscriptionPair(Brn(aKey),kInvalidSubscription));
}

void ConfigTab::AddKeyChoice(const Brx& aKey)
{
    ASSERT(!iStarted);
    iConfigChoices.push_back(SubscriptionPair(Brn(aKey),kInvalidSubscription));
}

void ConfigTab::AddKeyText(const Brx& aKey)
{
    ASSERT(!iStarted);
    iConfigTexts.push_back(SubscriptionPair(Brn(aKey),kInvalidSubscription));
}

// FIXME - remove?
void ConfigTab::Start()
{
    ASSERT(!iStarted);
    ASSERT(iConfigNums.size()>0 || iConfigChoices.size()>0 || iConfigTexts.size() > 0);
    iStarted = true;
}

TBool ConfigTab::Allocated() const
{
    TBool allocated = iHandler != nullptr;
    return allocated;
}

void ConfigTab::SetHandler(ITabHandler& aHandler, const std::vector<const Brx*>& aLanguageList)
{
    LOG(kHttp, "ConfigTab::SetHandler iId: %u\n", iId);
    ASSERT(iHandler == nullptr);
    iLanguageList = aLanguageList;
    iHandler = &aHandler;
    for (TUint i=0; i<iConfigNums.size(); i++) {
        const Brx& key = iConfigNums[i].first;
        ConfigNum& num = iConfigManager.GetNum(key);
        TUint subscription = num.Subscribe(MakeFunctorConfigNum(*this, &ConfigTab::ConfigNumCallback));
        iConfigNums[i].second = subscription;
    }
    for (TUint i=0; i<iConfigChoices.size(); i++) {
        const Brx& key = iConfigChoices[i].first;
        ConfigChoice& choice = iConfigManager.GetChoice(key);
        TUint subscription = choice.Subscribe(MakeFunctorConfigChoice(*this, &ConfigTab::ConfigChoiceCallback));
        iConfigChoices[i].second = subscription;
    }
    for (TUint i=0; i<iConfigTexts.size(); i++) {
        const Brx& key = iConfigTexts[i].first;
        ConfigText& text = iConfigManager.GetText(key);
        TUint subscription = text.Subscribe(MakeFunctorConfigText(*this, &ConfigTab::ConfigTextCallback));
        iConfigTexts[i].second = subscription;
    }
}

void ConfigTab::Receive(const Brx& aKey, const Brx& aValue)
{
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

void ConfigTab::Destroy()
{
    LOG(kHttp, "ConfigTab::Destroy iId: %u\n", iId);
    ASSERT(iHandler != nullptr);
    iHandler = nullptr;

    for (TUint i=0; i<iConfigNums.size(); i++) {
        const Brx& key = iConfigNums[i].first;
        ConfigNum& num = iConfigManager.GetNum(key);
        num.Unsubscribe(iConfigNums[i].second);
        iConfigNums[i].second = kInvalidSubscription;
    }
    for (TUint i=0; i<iConfigChoices.size(); i++) {
        const Brx& key = iConfigChoices[i].first;
        ConfigChoice& choice = iConfigManager.GetChoice(key);
        choice.Unsubscribe(iConfigChoices[i].second);
        iConfigChoices[i].second = kInvalidSubscription;
    }
    for (TUint i=0; i<iConfigTexts.size(); i++) {
        const Brx& key = iConfigTexts[i].first;
        ConfigText& text = iConfigManager.GetText(key);
        text.Unsubscribe(iConfigTexts[i].second);
        iConfigTexts[i].second = kInvalidSubscription;
    }
}

void ConfigTab::ConfigNumCallback(ConfigNum::KvpNum& aKvp)
{
    ASSERT(iHandler != nullptr);
    ConfigNum& num = iConfigManager.GetNum(aKvp.Key());
    const Brx& json = iJsonProvider.GetJson(aKvp.Key());
    // FIXME - because JSON is static and now stored in ConfigApp, it means
    // that ConfigMessages can also now just take a reference to the JSON
    // instead of copying it.
    IConfigMessage& msg = iMsgAllocator.Allocate(num, aKvp.Value(), json);
    iHandler->Send(msg);
}

void ConfigTab::ConfigChoiceCallback(ConfigChoice::KvpChoice& aKvp)
{
    ASSERT(iHandler != nullptr);
    ConfigChoice& choice = iConfigManager.GetChoice(aKvp.Key());
    const Brx& json = iJsonProvider.GetJson(aKvp.Key());
    IConfigMessage& msg = iMsgAllocator.Allocate(choice, aKvp.Value(), json, iLanguageList);
    iHandler->Send(msg);
}

void ConfigTab::ConfigTextCallback(ConfigText::KvpText& aKvp)
{
    ASSERT(iHandler != nullptr);
    ConfigText& text = iConfigManager.GetText(aKvp.Key());
    const Brx& json = iJsonProvider.GetJson(aKvp.Key());
    IConfigMessage& msg = iMsgAllocator.Allocate(text, aKvp.Value(), json);
    iHandler->Send(msg);
}


// ConfigAppBase

const Brn ConfigAppBase::kLangRoot("lang");
const Brn ConfigAppBase::kDefaultLanguage("en-gb");

ConfigAppBase::ConfigAppBase(IConfigManager& aConfigManager, const Brx& aResourcePrefix, const Brx& aResourceDir, TUint aMaxTabs, TUint aSendQueueSize)
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

    iMsgAllocator = new ConfigMessageAllocator(aSendQueueSize, *this);

    for (TUint i=0; i<aMaxTabs; i++) {
        iResourceHandlers.push_back(new FileResourceHandler(aResourceDir));
        iTabs.push_back(new ConfigTab(i, *iMsgAllocator, iConfigManager, *this));
    }

    for (TUint i=0; i<aMaxTabs; i++) {
        iLanguageResourceHandlers.push_back(new LanguageResourceFileReader(iLangResourceDir));
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
    for (TUint i=0; i<iKeysNums.size(); i++) {
        delete iKeysNums[i];
    }
    for (TUint i=0; i<iKeysChoices.size(); i++) {
        delete iKeysChoices[i];
    }
    for (TUint i=0; i<iKeysTexts.size(); i++) {
        delete iKeysTexts[i];
    }

    JsonMap::iterator it;
    for (it = iJsonMap.begin(); it != iJsonMap.end(); ++it) {
        delete it->second;
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

ITab& ConfigAppBase::Create(ITabHandler& aHandler, const std::vector<const Brx*>& aLanguageList)
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
            FileResourceHandler& handler = *iResourceHandlers[i];
            handler.SetResource(aResource);
            return handler;
        }
    }
    ASSERTS();  // FIXME - throw exception instead?
    // Could throw a ResourceHandlerFull if temporarily unavailable, and send an appropriate error response to browser.
    // However, in most cases, this should never happen. If it does (repeatedly) it likely means resource handlers aren't being returned/Destroy()ed.
    return *iResourceHandlers[0];   // unreachable
}

const Brx& ConfigAppBase::GetJson(const OpenHome::Brx& aKey)
{
    JsonMap::iterator it = iJsonMap.find(Brn(aKey));
    ASSERT(it != iJsonMap.end());
    return *it->second;
}

ILanguageResourceReader& ConfigAppBase::CreateLanguageResourceHandler(const Brx& aResourceUriTail, std::vector<const Brx*>& aLanguageList)
{
    // If no desired language can be found, should default to English.
    // Developer error if English mappings don't exist.
    std::vector<const Brx*> languages(aLanguageList);
    languages.push_back(&kDefaultLanguage);

    AutoMutex a(iLock);
    for (TUint i=0; i<iLanguageResourceHandlers.size(); i++) {
        if (!iLanguageResourceHandlers[i]->Allocated()) {
            for (TUint j=0; j<languages.size(); j++) {
                Bws<Uri::kMaxUriBytes> resource(*languages[j]);
                resource.Append("/");
                resource.Append(aResourceUriTail);
                try {
                    LanguageResourceFileReader& handler = *iLanguageResourceHandlers[i];
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

void ConfigAppBase::AddNum(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo)
{
    Brh* key = new Brh(aKey);
    iKeysNums.push_back(key);
    AddJson(*key, aAdditionalInfo);

    for (TUint i=0; i<iTabs.size(); i++) {
        iTabs[i]->AddKeyNum(aKey);
    }
}

void ConfigAppBase::AddChoice(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo)
{
    Brh* key = new Brh(aKey);
    iKeysChoices.push_back(key);
    AddJson(*key, aAdditionalInfo);

    for (TUint i=0; i<iTabs.size(); i++) {
        iTabs[i]->AddKeyChoice(aKey);
    }
}

void ConfigAppBase::AddText(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo)
{
    Brh* key = new Brh(aKey);
    iKeysTexts.push_back(key);
    AddJson(*key, aAdditionalInfo);

    for (TUint i=0; i<iTabs.size(); i++) {
        iTabs[i]->AddKeyText(*key);
    }
}

void ConfigAppBase::AddJson(const Brx& aKey, JsonKvpVector& aAdditionalInfo)
{
    //ASSERT(!iStarted);
    Bwh* json = new Bwh(ConfigMessage::kMaxAdditionalDataBytes);
    WriterBuffer writerBuf(*json);

    // Will only write the "additional" object if any key-value pairs exist.
    // FIXME - should write out "additional" (or "info") object even if it contains no values
    // FIXME - maybe JsonKvpVector should have its own Serialise() method? - why should the ConfigTab know how to serialise the values?
    if (aAdditionalInfo.size() > 0) {
        writerBuf.Write(Brn("\"additional\":{"));
        for (TUint i=0; i<aAdditionalInfo.size(); i++) {
            aAdditionalInfo[i]->Serialise(writerBuf);
            if (i < aAdditionalInfo.size()-1) {
                writerBuf.Write(Brn(","));
            }
        }
        writerBuf.Write(Brn("}"));
    }

    iJsonMap.insert(JsonPair(Brn(aKey), json));
}


// ConfigAppBasic

ConfigAppBasic::ConfigAppBasic(IConfigManager& aConfigManager, const Brx& aResourcePrefix, const Brx& aResourceDir, TUint aMaxTabs, TUint aSendQueueSize)
    : ConfigAppBase(aConfigManager, aResourcePrefix, aResourceDir, aMaxTabs, aSendQueueSize)
{
    JsonKvpVector emptyJsonVector;
    AddText(Brn("Product.Name"), emptyJsonVector);
    AddText(Brn("Product.Room"), emptyJsonVector);
}


// ConfigAppSources

ConfigAppSources::ConfigAppSources(IConfigManager& aConfigManager, std::vector<const Brx*>& aSources, const Brx& aResourcePrefix, const Brx& aResourceDir, TUint aMaxTabs, TUint aSendQueueSize)
    : ConfigAppBasic(aConfigManager, aResourcePrefix, aResourceDir, aMaxTabs, aSendQueueSize)
{
    // Get all product names.
    for (TUint i=0; i<aSources.size(); i++) {
        Brn suffix(".Name");
        Bws<kMaxSourceNameBytes> key("Source.");
        Ascii::AppendDec(key, i);
        key.Append(suffix);

        JsonKvpVector sourceInfoVector;
        // FIXME - enable this
        //Bws<Av::ISource::kMaxSystemNameBytes> systemName;
        //Bws<Av::ISource::kMaxSourceTypeBytes> type;
        //Bws<Av::ISource::kMaxSourceNameBytes> sourceName;
        //TBool visible;
        //aProduct.GetSourceDetails(i, systemName, type, sourceName, visible);

        // FIXME - no sources have been added when this is called - why?
        //sourceInfoVector.push_back(new JsonKvpString(Brn("type"), type));
        //sourceInfoVector.push_back(new JsonKvpString(Brn("name"), systemName));

        AddText(key, sourceInfoVector);
    }

    JsonKvpVector emptyJsonVector;
    AddChoice(Brn("Source.Startup"), emptyJsonVector);
}

// ConfigAppMediaPlayer

ConfigAppMediaPlayer::ConfigAppMediaPlayer(IConfigManager& aConfigManager, std::vector<const Brx*>& aSources, const Brx& aResourcePrefix, const Brx& aResourceDir, TUint aMaxTabs, TUint aSendQueueSize)
    : ConfigAppSources(aConfigManager, aSources, aResourcePrefix, aResourceDir, aMaxTabs, aSendQueueSize)
{
    JsonKvpVector emptyJsonVector;

    AddNumConditional(Brn("Sender.Channel"), emptyJsonVector);
    AddNumConditional(Brn("Sender.Preset"), emptyJsonVector);
    AddNumConditional(Brn("Volume.Balance"), emptyJsonVector);
    AddNumConditional(Brn("Volume.Limit"), emptyJsonVector);
    AddNumConditional(Brn("Volume.Startup"), emptyJsonVector);

    AddChoiceConditional(Brn("Sender.Enabled"), emptyJsonVector);
    AddChoiceConditional(Brn("Sender.Mode"), emptyJsonVector);
    AddChoiceConditional(Brn("Source.NetAux.Auto"), emptyJsonVector);
    AddChoiceConditional(Brn("Volume.Startup.Enabled"), emptyJsonVector);
    AddChoiceConditional(Brn("qobuz.com.SoundQuality"), emptyJsonVector);
    AddChoiceConditional(Brn("tidalhifi.com.SoundQuality"), emptyJsonVector);

    AddTextConditional(Brn("Radio.TuneInUserName"), emptyJsonVector);
    //AddTextConditional(Brn("qobuz.com.Password"), emptyJsonVector);
    AddTextConditional(Brn("qobuz.com.Username"), emptyJsonVector);
    //AddTextConditional(Brn("tidalhifi.com.Password"), emptyJsonVector);
    AddTextConditional(Brn("tidalhifi.com.Username"), emptyJsonVector);
}

void ConfigAppMediaPlayer::AddNumConditional(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo)
{
    if (iConfigManager.HasNum(aKey)) {
        AddNum(aKey, aAdditionalInfo);
    }
}

void ConfigAppMediaPlayer::AddChoiceConditional(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo)
{
    if (iConfigManager.HasChoice(aKey)) {
        AddChoice(aKey, aAdditionalInfo);
    }
}

void ConfigAppMediaPlayer::AddTextConditional(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo)
{
    if (iConfigManager.HasText(aKey)) {
        AddText(aKey, aAdditionalInfo);
    }
}
