#include <OpenHome/Av/Product.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/ProviderProduct.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;


// ConfigStartupSource

const Brn ConfigStartupSource::kKeySource("Source.StartupName");
const Brn ConfigStartupSource::kLastUsed("Last Used");

ConfigStartupSource::ConfigStartupSource(Configuration::IConfigInitialiser& aConfigInit)
{
    iSourceStartup = new ConfigText(aConfigInit, kKeySource, Product::kMaxNameBytes, kLastUsed);
}

ConfigStartupSource::~ConfigStartupSource()
{
    delete iSourceStartup;
}


// Product

const Brn Product::kKeyLastSelectedSource("Last.Source");
const Brn Product::kConfigIdRoomBase("Product.Room");
const Brn Product::kConfigIdNameBase("Product.Name");
const Brn Product::kConfigIdAutoPlay("Device.AutoPlay");
const TUint Product::kAutoPlayDisable = 0;
const TUint Product::kAutoPlayEnable  = 1;
const TUint Product::kCurrentSourceNone = UINT_MAX;

Product::Product(Environment& aEnv, Net::DvDeviceStandard& aDevice, IReadStore& aReadStore,
                 Configuration::IStoreReadWrite& aReadWriteStore, Configuration::IConfigManager& aConfigReader,
                 Configuration::IConfigInitialiser& aConfigInit, IPowerManager& aPowerManager)
    : iEnv(aEnv)
    , iDevice(aDevice)
    , iReadStore(aReadStore)
    , iConfigReader(aConfigReader)
    , iConfigInit(aConfigInit)
    , iPowerManager(aPowerManager)
    , iLock("PRDM")
    , iLockDetails("PRDD")
    , iStarted(false)
    , iStandby(true)
    , iAutoPlay(false)
    , iCurrentSource(kCurrentSourceNone)
    , iSourceXmlChangeCount(0)
    , iConfigStartupSource(nullptr)
    , iListenerIdStartupSource(IConfigManager::kSubscriptionIdInvalid)
    , iStartupSourceVal(ConfigStartupSource::kLastUsed)
    , iConfigAutoPlay(nullptr)
    , iListenerIdAutoPlay(IConfigManager::kSubscriptionIdInvalid)
    , iAdapterChangeListenerId(NetworkAdapterList::kListenerIdNull)
{
    iStandbyObserver = aPowerManager.RegisterStandbyHandler(*this, kStandbyHandlerPriorityLowest, "Product");
    iLastSelectedSource = new StoreText(aReadWriteStore, aPowerManager, kPowerPriorityHighest, kKeyLastSelectedSource, Brx::Empty(), ISource::kMaxSourceTypeBytes);
    iConfigProductRoom = &aConfigReader.GetText(kConfigIdRoomBase);
    iListenerIdProductRoom = iConfigProductRoom->Subscribe(MakeFunctorConfigText(*this, &Product::ProductRoomChanged));
    iConfigProductName = &aConfigReader.GetText(kConfigIdNameBase);
    iListenerIdProductName = iConfigProductName->Subscribe(MakeFunctorConfigText(*this, &Product::ProductNameChanged));
    if (aConfigReader.HasChoice(kConfigIdAutoPlay)) {
        iConfigAutoPlay = &aConfigReader.GetChoice(kConfigIdAutoPlay);
        iListenerIdAutoPlay = iConfigAutoPlay->Subscribe(MakeFunctorConfigChoice(*this, &Product::AutoPlayChanged));
    }
    iProviderProduct = new ProviderProduct(aDevice, *this, aPowerManager);
}

Product::~Product()
{
    iEnv.NetworkAdapterList().RemoveCurrentChangeListener(iAdapterChangeListenerId);
    delete iStandbyObserver;
    iConfigStartupSource->Unsubscribe(iListenerIdStartupSource);
    iConfigStartupSource = nullptr; // Didn't have ownership.
    for (TUint i=0; i<(TUint)iSources.size(); i++) {
        delete iSources[i];
    }
    iSources.clear();
    delete iProviderProduct;
    iConfigProductName->Unsubscribe(iListenerIdProductName);
    iConfigProductRoom->Unsubscribe(iListenerIdProductRoom);
    if (iConfigAutoPlay != nullptr) {
        iConfigAutoPlay->Unsubscribe(iListenerIdAutoPlay);
    }
    delete iLastSelectedSource;
}

void Product::AddObserver(IProductObserver& aObserver)
{
    iObservers.push_back(&aObserver);
}

void Product::AddAttributesObserver(IProductAttributesObserver& aObserver)
{
    iAttributeObservers.push_back(&aObserver);
}

void Product::Start()
{
    // All sources must have been registered; construct startup source config val.
    iConfigStartupSource = &iConfigReader.GetText(ConfigStartupSource::kKeySource);
    iListenerIdStartupSource = iConfigStartupSource->Subscribe(MakeFunctorConfigText(*this, &Product::StartupSourceChanged));

    iLock.Wait();
    const Bws<ISource::kMaxSystemNameBytes> startupSourceVal(iStartupSourceVal);
    iAdapterChangeListenerId = iEnv.NetworkAdapterList().AddCurrentChangeListener(MakeFunctor(*this, &Product::CurrentAdapterChanged), "OpenHome::Av::Product", false);
    iLock.Signal();
    CurrentAdapterChanged(); // NetworkAdapterList doesn't run callbacks on registration

    TBool sourceSelected = false;
    if (startupSourceVal != ConfigStartupSource::kLastUsed) {
        try {
            (void)DoSetCurrentSource(startupSourceVal);
            sourceSelected = true;
        }
        catch (AvSourceNotFound&) {
            // Invalid content in iStartupSourceVal.
        }
    }

    if (!sourceSelected) { // No startup source selected; use last selected source.
        Bws<ISource::kMaxSystemNameBytes> startupSource;
        iLastSelectedSource->Get(startupSource);
        if (startupSource == Brx::Empty()) {
            // If there is no stored startup source, select the first added source.
            (void)DoSetCurrentSource(0);
        }
        else {
            try {
                DoSetCurrentSource(startupSource);
            }
            catch (AvSourceNotFound&) {
                (void)DoSetCurrentSource(0);
                iLastSelectedSource->Set(Brx::Empty());
            }
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

void Product::SetConfigAppUrl(const Brx& aUrl)
{
    iLock.Wait();
    iConfigAppUrlTail.Replace(aUrl);
    iLock.Signal();
    for (auto it=iAttributeObservers.begin(); it!=iAttributeObservers.end(); ++it) {
        (*it)->AttributesChanged();
    }
}

void Product::GetManufacturerDetails(Brn& aName, Brn& aInfo, Bwx& aUrl, Bwx& aImageUri)
{
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufManufacturerName, aName));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufManufacturerInfo, aInfo));
    GetUri(StaticDataKey::kBufManufacturerUrl, aUrl);
    GetUri(StaticDataKey::kBufManufacturerImageUrl, aImageUri);
}

void Product::GetModelDetails(Brn& aName, Brn& aInfo, Bwx& aUrl, Bwx& aImageUri)
{
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufModelName, aName));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufModelInfo, aInfo));
    GetUri(StaticDataKey::kBufModelUrl, aUrl);
    GetUri(StaticDataKey::kBufModelImageUrl, aImageUri);
}

void Product::GetProductDetails(Bwx& aRoom, Bwx& aName, Brn& aInfo, Bwx& aImageUri)
{
    iLockDetails.Wait();
    aRoom.Append(iProductRoom);
    aName.Append(iProductName);
    iLockDetails.Signal();
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufModelInfo, aInfo));
    // presentation url
    GetUri(StaticDataKey::kBufModelImageUrl, aImageUri);
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
    WriterBuffer writer(aXml);
    writer.Write(Brn("<SourceList>"));
    iLock.Wait();
    for (TUint i=0; i<iSources.size(); i++) {
        ISource* src = iSources[i];
        Bws<ISource::kMaxSourceNameBytes> name;
        src->Name(name);
        writer.Write(Brn("<Source>"));
        AppendTag(writer, "Name", name);
        AppendTag(writer, "Type", src->Type());
        AppendTag(writer, "Visible", src->IsVisible()? Brn("true") : Brn("false"));
        AppendTag(writer, "SystemName", src->SystemName());
        writer.Write(Brn("</Source>"));
    }
    iLock.Signal();
    writer.Write(Brn("</SourceList>"));
    writer.WriteFlush();
}

void Product::AppendTag(IWriter& aWriter, const TChar* aTag, const Brx& aValue)
{
    Brn tag(aTag);
    aWriter.Write('<');
    aWriter.Write(tag);
    aWriter.Write('>');
    Converter::ToXmlEscaped(aWriter, aValue);
    aWriter.Write(Brn("</"));
    aWriter.Write(tag);
    aWriter.Write('>');
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

void Product::StartupSourceChanged(KeyValuePair<const Brx&>& aKvp)
{
    ASSERT(aKvp.Key() == ConfigStartupSource::kKeySource);
    AutoMutex a(iLock);
    iStartupSourceVal.Replace(aKvp.Value());
}

void Product::AutoPlayChanged(KeyValuePair<TUint>& aKvp)
{
    iLock.Wait();
    iAutoPlay = (aKvp.Value() == kAutoPlayEnable);
    iLock.Signal();
}

void Product::CurrentAdapterChanged()
{
    {
        AutoMutex _(iLock);
        AutoNetworkAdapterRef ar(iEnv, "Av::Product");
        iConfigAppAddress.Replace(Brx::Empty());
        auto current = ar.Adapter();
        if (current == nullptr) {
            iUriPrefix.Set("");
        }
        else {
            iDevice.GetResourceManagerUri(*current, iUriPrefix);
            Endpoint ep(0, current->Address());
            ep.AppendAddress(iConfigAppAddress);
        }
    }

    for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
        (*it)->ProductUrisChanged();
    }
    for (auto it=iAttributeObservers.begin(); it!=iAttributeObservers.end(); ++it) {
        (*it)->AttributesChanged();
    }
}

void Product::GetUri(const Brx& aStaticDataKey, Bwx& aUri)
{
    Brn uri;
    ASSERT(iReadStore.TryReadStoreStaticItem(aStaticDataKey, uri));
    static const Brn kPrefixHttp("http://");
    if (uri.BeginsWith(kPrefixHttp)) {
        aUri.Replace(uri);
    }
    else {
        iLock.Wait();
        aUri.Replace(iUriPrefix);
        iLock.Signal();
        aUri.Append(uri);
    }
}

void Product::SetCurrentSource(TUint aIndex)
{
    iPowerManager.StandbyDisable(StandbyDisableReason::User);
    (void)DoSetCurrentSource(aIndex);
}

TBool Product::DoSetCurrentSourceLocked(TUint aIndex)
{
    if (aIndex >= (TUint)iSources.size()) {
        THROW(AvSourceNotFound);
    }
    if (iCurrentSource == aIndex) {
        return false;
    }
    if (iCurrentSource != kCurrentSourceNone) {
        iSources[iCurrentSource]->Deactivate();
    }
    iCurrentSource = aIndex;
    iLastSelectedSource->Set(iSources[iCurrentSource]->SystemName());
    if (!iStandby) {
        iSources[iCurrentSource]->Activate(iAutoPlay);
    }

    for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
        (*it)->SourceIndexChanged();
    }
    return true;
}

TBool Product::DoSetCurrentSource(TUint aIndex)
{
    AutoMutex a(iLock);
    return DoSetCurrentSourceLocked(aIndex);
}

void Product::SetCurrentSourceByName(const Brx& aName)
{
    iPowerManager.StandbyDisable(StandbyDisableReason::User);
    AutoMutex a(iLock);
    Bws<ISource::kMaxSourceNameBytes> name;
    TUint i = 0;
    for (i = 0; i < (TUint)iSources.size(); i++) {
        iSources[i]->Name(name);
        if (name == aName) {
            break;
        }
    }
    (void)DoSetCurrentSourceLocked(i);
}

void Product::SetCurrentSourceBySystemName(const Brx& aSystemName)
{
    iPowerManager.StandbyDisable(StandbyDisableReason::User);
    DoSetCurrentSource(aSystemName);
}

TBool Product::DoSetCurrentSource(const Brx& aSystemName)
{
    AutoMutex a(iLock);
    TUint i = 0;
    for (i = 0; i < (TUint)iSources.size(); i++) {
        if (iSources[i]->SystemName() == aSystemName) {
            break;
        }
    }
    return DoSetCurrentSourceLocked(i);
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
    aSystemName.Replace(source->SystemName());
    aType.Replace(source->Type());
    aName.Replace(name);
    aVisible = source->IsVisible();
}

void Product::GetSourceDetails(const Brx& aSystemName, Bwx& aType, Bwx& aName, TBool& aVisible) const
{
    AutoMutex a(iLock);
    for (TUint i=0; i<(TUint)iSources.size(); i++) {
        ISource* source = iSources[i];
        if (source->SystemName() == aSystemName) {
            Bws<ISource::kMaxSourceNameBytes> name;
            source->Name(name);
            aType.Replace(source->Type());
            aName.Replace(name);
            aVisible = source->IsVisible();
            return;
        }
    }
    THROW(AvSourceNotFound);
}

void Product::GetAttributes(Bwx& aAttributes) const
{
    AutoMutex _(iLock);
    aAttributes.Replace(iAttributes);
    if (iConfigAppAddress.Bytes() > 0) {
        aAttributes.Append(" App:Config=");
        aAttributes.Append("http://");
        aAttributes.Append(iConfigAppAddress);
        aAttributes.Append(iConfigAppUrlTail);
    }
}

TUint Product::SourceXmlChangeCount()
{
    return iSourceXmlChangeCount;
}

void Product::Activate(ISource& aSource)
{
    iPowerManager.StandbyDisable(StandbyDisableReason::User);

    ISource* srcNew = nullptr;
    ISource* srcOld = nullptr;

    AutoMutex a(iLock);
    // deactivate current (old) source, if one exists
    if (iCurrentSource != kCurrentSourceNone) {
        srcOld = iSources[iCurrentSource];

        if (&aSource == srcOld) {
            // This source is already active. Do nothing.
            return;
        }

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
            srcNew->Activate(iAutoPlay);
            for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
                (*it)->SourceIndexChanged();
            }
            return;
        }
    }
    THROW(AvSourceNotFound);
}

void Product::NotifySourceChanged(ISource& /*aSource*/)
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

void Product::StandbyEnabled()
{
    AutoMutex _(iLock);
    iStandby = true;
    if (iCurrentSource != kCurrentSourceNone) {
        iSources[iCurrentSource]->StandbyEnabled();
    }
}

void Product::StandbyDisabled(StandbyDisableReason aReason)
{
    iLock.Wait();
    iStandby = false;
    iLock.Signal();

    TBool activated = false;
    if (aReason != StandbyDisableReason::Alarm) {
        iLock.Wait();
        const Bws<ISource::kMaxSystemNameBytes> startupSourceVal(iStartupSourceVal);
        iLock.Signal();
        if (startupSourceVal != ConfigStartupSource::kLastUsed) {
            try {
                activated = DoSetCurrentSource(startupSourceVal);
            }
            catch (AvSourceNotFound&) {
                // Invalid content in iStartupSourceVal. Leave last source set.
            }
        }
    }
    if (!activated) {
        AutoMutex _(iLock);
        if (iCurrentSource != kCurrentSourceNone) {
            iSources[iCurrentSource]->Activate(iAutoPlay);
        }
    }
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
    auto it = iObservers.insert(std::pair<TUint,FunctorGeneric<const Brx&>>(id, aObserver));
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
