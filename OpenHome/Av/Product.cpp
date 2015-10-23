#include <OpenHome/Av/Product.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/ProviderProduct.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Printer.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;


// ConfigSourceNameObserver

ConfigSourceNameObserver::ConfigSourceNameObserver(IConfigManager& aConfigReader, const Brx& aSourceName)
    : iLock("CSNO")
{
    Bws<Source::kKeySourceNameMaxBytes> key;
    Source::GetSourceNameKey(aSourceName, key);
    iConfigSourceName = &aConfigReader.GetText(key);
    iListenerId = iConfigSourceName->Subscribe(MakeFunctorConfigText(*this, &ConfigSourceNameObserver::SourceNameChanged));
}

ConfigSourceNameObserver::~ConfigSourceNameObserver()
{
    iConfigSourceName->Unsubscribe(iListenerId);
}

void ConfigSourceNameObserver::Name(Bwx& aBuf) const
{
    AutoMutex a(iLock);
    aBuf.Replace(iName);
}

void ConfigSourceNameObserver::SourceNameChanged(Configuration::KeyValuePair<const Brx&>& aKvp)
{
    AutoMutex a(iLock);
    ASSERT(aKvp.Key() == iConfigSourceName->Key());
    iName.Replace(aKvp.Value());
}


// ConfigStartupSource

const Brn ConfigStartupSource::kKeySource("Source.Startup");
const Brn ConfigStartupSource::kNoneName("Default");
const TUint ConfigStartupSource::kNone = UINT_MAX;

ConfigStartupSource::ConfigStartupSource(Configuration::IConfigInitialiser& aConfigInit, Configuration::IConfigManager& aConfigReader, const std::vector<const Brx*> aSystemNames)
{
    std::vector<TUint> choices;

    // Add dummy source, which must be first in list and represents default/none startup source.
    choices.push_back(kNone);

    // Push real sources on, starting at index 0, which maps directly to product sources.
    for (TUint i=0; i<aSystemNames.size(); i++) {
        choices.push_back(i);
        iObservers.push_back(new ConfigSourceNameObserver(aConfigReader, *aSystemNames[i]));
    }

    iSourceStartup = new ConfigChoice(aConfigInit, kKeySource, choices, kNone, *this);
}

ConfigStartupSource::~ConfigStartupSource()
{
    delete iSourceStartup;
}

void ConfigStartupSource::DeregisterObservers()
{
    for (auto observer : iObservers) {
        delete observer;
    }
    iObservers.clear();
}

void ConfigStartupSource::Write(IWriter& aWriter, Configuration::IConfigChoiceMappingWriter& aMappingWriter)
{
    const std::vector<TUint>& choices = iSourceStartup->Choices();
    Bws<ISource::kMaxSourceNameBytes> sourceName;

    for (auto choice : choices) {
        if (choice == kNone) {
            aMappingWriter.Write(aWriter, choice, kNoneName);
        }
        else {
            iObservers[choice]->Name(sourceName);
            aMappingWriter.Write(aWriter, choice, sourceName);
        }
    }
    aMappingWriter.WriteComplete(aWriter);
}


// Product

const Brn Product::kKeyLastSelectedSource("Last.Source");
const Brn Product::kConfigIdRoomBase("Product.Room");
const Brn Product::kConfigIdNameBase("Product.Name");

Product::Product(Net::DvDevice& aDevice, IReadStore& aReadStore, IStoreReadWrite& aReadWriteStore,
                 IConfigManager& aConfigReader, IConfigInitialiser& aConfigInit,
                 IPowerManager& aPowerManager)
    : iDevice(aDevice)
    , iReadStore(aReadStore)
    , iConfigReader(aConfigReader)
    , iConfigInit(aConfigInit)
    , iLock("PRDM")
    , iLockDetails("PRDD")
    , iStarted(false)
    , iStandby(false)
    , iCurrentSource(UINT_MAX)
    , iSourceXmlChangeCount(0)
    , iConfigStartupSource(nullptr)
    , iListenerIdStartupSource(IConfigManager::kSubscriptionIdInvalid)
    , iStartupSourceVal(ConfigStartupSource::kNone)
{
    iLastSelectedSource = new StoreText(aReadWriteStore, aPowerManager, kPowerPriorityHighest, kKeyLastSelectedSource, Brx::Empty(), ISource::kMaxSourceTypeBytes);
    iConfigProductRoom = &aConfigReader.GetText(kConfigIdRoomBase);
    iListenerIdProductRoom = iConfigProductRoom->Subscribe(MakeFunctorConfigText(*this, &Product::ProductRoomChanged));
    iConfigProductName = &aConfigReader.GetText(kConfigIdNameBase);
    iListenerIdProductName = iConfigProductName->Subscribe(MakeFunctorConfigText(*this, &Product::ProductNameChanged));
    iProviderProduct = new ProviderProduct(aDevice, *this);
}

Product::~Product()
{
    iConfigStartupSource->Unsubscribe(iListenerIdStartupSource);
    iConfigStartupSource = nullptr; // Didn't have ownership.
    for (TUint i=0; i<(TUint)iSources.size(); i++) {
        delete iSources[i];
    }
    iSources.clear();
    delete iProviderProduct;
    iConfigProductName->Unsubscribe(iListenerIdProductName);
    iConfigProductRoom->Unsubscribe(iListenerIdProductRoom);
    delete iLastSelectedSource;
}

void Product::AddObserver(IProductObserver& aObserver)
{
    iObservers.push_back(&aObserver);
}

void Product::Start()
{
    // All sources must have been registered; construct startup source config val.
    iConfigStartupSource = &iConfigReader.GetChoice(ConfigStartupSource::kKeySource);
    iListenerIdStartupSource = iConfigStartupSource->Subscribe(MakeFunctorConfigChoice(*this, &Product::StartupSourceChanged));

    iLock.Wait();
    const TUint startupSourceVal = iStartupSourceVal;
    iLock.Signal();

    if (startupSourceVal != ConfigStartupSource::kNone) {
        SetCurrentSource(startupSourceVal);
    }
    else { // No startup source selected; use last selected source.
        Bws<ISource::kMaxSystemNameBytes> startupSource;
        iLastSelectedSource->Get(startupSource);
        if (startupSource == Brx::Empty()) {
            // If there is no stored startup source, select the first added source.
            SetCurrentSource(0);
        }
        else {
            SetCurrentSource(startupSource);
        }
    }

    iStarted = true;
    iSourceXmlChangeCount++;
    for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
        (*it)->Started();
    }
}

void Product::Stop()
{
    auto it = iSources.begin();
    while (it != iSources.end()) {
        (*it)->PipelineStopped();
        it++;
    }
}

void Product::AddSource(ISource* aSource)
{
    ASSERT(!iStarted);
    iSources.push_back(aSource);
    aSource->Initialise(*this, iConfigInit, iConfigReader, iSources.size()-1);
}

void Product::AddAttribute(const TChar* aAttribute)
{
    ASSERT(!iStarted);
    Brn attr(aAttribute);
    AddAttribute(attr);
}

void Product::AddAttribute(const Brx& aAttribute)
{
    if (iAttributes.Bytes() > 0) {
        iAttributes.Append(' ');
    }
    iAttributes.Append(aAttribute);
}

void Product::GetManufacturerDetails(Brn& aName, Brn& aInfo, Brn& aUrl, Brn& aImageUri)
{
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufManufacturerName, aName));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufManufacturerInfo, aInfo));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufManufacturerUrl, aUrl));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufManufacturerImageUrl, aImageUri)); // FIXME - generate (at least partially) dynamically
}

void Product::GetModelDetails(Brn& aName, Brn& aInfo, Brn& aUrl, Brn& aImageUri)
{
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufModelName, aName));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufModelInfo, aInfo));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufModelUrl, aUrl));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufModelImageUrl, aImageUri)); // FIXME - generate (at least partially) dynamically
}

void Product::GetProductDetails(Bwx& aRoom, Bwx& aName, Brn& aInfo, Brn& aImageUri)
{
    iLockDetails.Wait();
    aRoom.Append(iProductRoom);
    aName.Append(iProductName);
    iLockDetails.Signal();
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufModelInfo, aInfo));
    // presentation url
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufModelImageUrl, aImageUri));
}

TBool Product::StandbyEnabled() const
{
    AutoMutex a(iLock);
    return iStandby;
}

void Product::SetStandby(TBool aStandby)
{
    iLock.Wait();
    const TBool changed = ((aStandby && !iStandby) || (!aStandby && iStandby));
    if (changed) {
        iStandby = aStandby;
    }
    const TUint startupSourceVal = iStartupSourceVal;
    iLock.Signal();

    if (changed) {
        // Activate startup source (if one set) if coming out of standby.
        if (!aStandby && startupSourceVal != ConfigStartupSource::kNone) {
            SetCurrentSource(startupSourceVal);
        }

        for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
            (*it)->StandbyChanged();
            // FIXME - other observers to notify. (e.g. to disable any hardware)
        }

        if (aStandby) {
            AutoMutex _(iLock);
            iSources[iCurrentSource]->StandbyEnabled();
        }
    }
}

TUint Product::SourceCount() const
{
    return (TUint)iSources.size();
}

TUint Product::CurrentSourceIndex() const
{
    return iCurrentSource;
}

void Product::GetSourceXml(Bwx& aXml)
{
    aXml.Append("<SourceList>");
    iLock.Wait();
    for (TUint i=0; i<iSources.size(); i++) {
        ISource* src = iSources[i];
        Bws<ISource::kMaxSourceNameBytes> name;
        src->Name(name);
        aXml.Append("<Source>");
        AppendTag(aXml, "Name", name);
        AppendTag(aXml, "Type", src->Type());
        AppendTag(aXml, "Visible", src->IsVisible()? Brn("true") : Brn("false"));
        aXml.Append("</Source>");
    }
    iLock.Signal();
    aXml.Append("</SourceList>");
}

void Product::AppendTag(Bwx& aXml, const TChar* aTag, const Brx& aValue)
{
    aXml.Append('<');
    aXml.Append(aTag);
    aXml.Append('>');
    aXml.Append(aValue);
    aXml.Append("</");
    aXml.Append(aTag);
    aXml.Append('>');
}

void Product::ProductRoomChanged(KeyValuePair<const Brx&>& aKvp)
{
    AutoMutex a(iLockDetails);
    if (iProductRoom != aKvp.Value()) {
        iProductRoom.Replace(aKvp.Value());
        for (auto it=iNameObservers.begin(); it!=iNameObservers.end(); ++it) {
            (*it)->RoomChanged(iProductRoom);
        }
    }
}

void Product::ProductNameChanged(KeyValuePair<const Brx&>& aKvp)
{
    AutoMutex a(iLockDetails);
    if (iProductName != aKvp.Value()) {
        iProductName.Replace(aKvp.Value());
        for (auto it=iNameObservers.begin(); it!=iNameObservers.end(); ++it) {
            (*it)->NameChanged(iProductName);
        }
    }
}

void Product::StartupSourceChanged(KeyValuePair<TUint>& aKvp)
{
    ASSERT(aKvp.Key() == ConfigStartupSource::kKeySource);
    AutoMutex a(iLock);
    iStartupSourceVal = aKvp.Value();
}

void Product::SetCurrentSource(TUint aIndex)
{
    AutoMutex a(iLock);
    if (aIndex >= (TUint)iSources.size()) {
        THROW(AvSourceNotFound);
    }
    if (iCurrentSource == aIndex) {
        return;
    }
    if (iCurrentSource != UINT_MAX) {
        iSources[iCurrentSource]->Deactivate();
    }
    iCurrentSource = aIndex;
    iLastSelectedSource->Set(iSources[iCurrentSource]->SystemName());
    iSources[iCurrentSource]->Activate();

    for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
        (*it)->SourceIndexChanged();
    }
}

void Product::SetCurrentSource(const Brx& aName)
{
    AutoMutex a(iLock);
    // volkano treats [name] as a system name and anything else as a user-defined name.  Do we need to do the same?
    Bws<ISource::kMaxSourceNameBytes> name;
    for (TUint i=0; i<(TUint)iSources.size(); i++) {
        iSources[i]->Name(name);
        if (name == aName) {
            if (iCurrentSource != UINT_MAX) {
                iSources[iCurrentSource]->Deactivate();
            }
            iCurrentSource = i;
            iLastSelectedSource->Set(iSources[iCurrentSource]->SystemName());
            iSources[iCurrentSource]->Activate();
            for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
                (*it)->SourceIndexChanged();
            }
            return;
        }
    }
    THROW(AvSourceNotFound);
}

void Product::GetSourceDetails(TUint aIndex, Bwx& aSystemName, Bwx& aType, Bwx& aName, TBool& aVisible) const
{
    AutoMutex a(iLock);
    if (aIndex >= (TUint)iSources.size()) {
        THROW(AvSourceNotFound);
    }
    ISource* source = iSources[aIndex];
    Bws<ISource::kMaxSourceNameBytes> name;
    source->Name(name);
    aSystemName.Append(source->SystemName());
    aType.Append(source->Type());
    aName.Append(name);
    aVisible = source->IsVisible();
}

const Brx& Product::Attributes() const
{
    return iAttributes;
}

TUint Product::SourceXmlChangeCount()
{
    return iSourceXmlChangeCount;
}

void Product::Activate(ISource& aSource)
{
    ISource* srcNew = nullptr;
    ISource* srcOld = nullptr;

    AutoMutex a(iLock);
    // deactivate current (old) source, if one exists
    if (iCurrentSource != UINT_MAX) {
        srcOld = iSources[iCurrentSource];
        srcOld->Deactivate();
    }

    // find and activate new source
    Bws<ISource::kMaxSourceNameBytes> name;
    Bws<ISource::kMaxSourceNameBytes> nameExpected;
    aSource.Name(nameExpected);
    for (TUint i=0; i<(TUint)iSources.size(); i++) {
        iSources[i]->Name(name);
        if (name == nameExpected) {
            iCurrentSource = i;
            iLastSelectedSource->Set(iSources[iCurrentSource]->SystemName());
            srcNew = iSources[i];
            srcNew->Activate();
            for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
                (*it)->SourceIndexChanged();
            }
            return;
        }
    }
    THROW(AvSourceNotFound);
}

void Product::NotifySourceNameChanged(ISource& /*aSource*/)
{
    iLock.Wait();
    iSourceXmlChangeCount++;
    iLock.Signal();
    for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
        (*it)->SourceXmlChanged();
    }
}

void Product::AddNameObserver(IProductNameObserver& aObserver)
{
    AutoMutex a(iLockDetails);
    iNameObservers.push_back(&aObserver);
    // Notify new observer immediately with its initial values.
    aObserver.RoomChanged(iProductRoom);
    aObserver.NameChanged(iProductName);
}

void Product::QueryInfo(const Brx& /*aQuery*/, IWriter& /*aWriter*/)
{
}


// FriendlyNameManager

FriendlyNameManager::FriendlyNameManager(IProductNameObservable& aProduct)
    : iNextObserverId(1)
    , iMutex("FNHM")
{
    aProduct.AddNameObserver(*this);    // Observer methods called during registration.
}

FriendlyNameManager::~FriendlyNameManager()
{
    AutoMutex a(iMutex);
    ASSERT(iObservers.size() == 0);
}

TUint FriendlyNameManager::RegisterFriendlyNameObserver(FunctorGeneric<const Brx&> aObserver)
{
    AutoMutex a(iMutex);
    const TUint id = iNextObserverId++;
    auto it = iObservers.emplace(id, aObserver);
    ASSERT(it.second);
    aObserver(iFriendlyName);
    return id;
}

void FriendlyNameManager::DeregisterFriendlyNameObserver(TUint aId)
{
    const TUint count = iObservers.erase(aId);
    ASSERT(count == 1);
}

void FriendlyNameManager::RoomChanged(const Brx& aRoom)
{
    AutoMutex a(iMutex);
    iRoom.Replace(aRoom);
    ConstructFriendlyNameLocked();
    NotifyObserversLocked();
}

void FriendlyNameManager::NameChanged(const Brx& aName)
{
    AutoMutex a(iMutex);
    iName.Replace(aName);
    ConstructFriendlyNameLocked();
    NotifyObserversLocked();
}

void FriendlyNameManager::ConstructFriendlyNameLocked()
{
    iFriendlyName.Replace(iRoom);
    iFriendlyName.Append(':');
    iFriendlyName.Append(iName);
}

void FriendlyNameManager::NotifyObserversLocked()
{
    for (auto observer : iObservers) {
        observer.second(iFriendlyName);
    }
}
