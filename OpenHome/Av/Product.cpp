#include <OpenHome/Av/Product.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/ProviderProduct.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Av/InfoProvider.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;


Product::Product(Net::DvDevice& aDevice, IReadStore& aReadStore, IInfoAggregator& /*aInfoAggregator*/)
    : iDevice(aDevice)
    , iReadStore(aReadStore)
    , iLock("PRDM")
    , iObserver(NULL)
    , iStarted(false)
    , iCurrentSource(UINT_MAX)
    , iSourceXmlChangeCount(0)
{
    iProviderProduct = new ProviderProduct(aDevice, *this);
}

Product::~Product()
{
    for (TUint i=0; i<(TUint)iSources.size(); i++) {
        delete iSources[i];
    }
    iSources.clear();
    delete iProviderProduct;
}

void Product::SetObserver(IProductObserver& aObserver)
{
    iObserver = &aObserver;
}

void Product::Start()
{
    iStarted = true;
    iSourceXmlChangeCount++;
    if (iObserver != NULL) {
        iObserver->Started();
    }
}

void Product::AddSource(ISource* aSource)
{
    ASSERT(!iStarted);
    iSources.push_back(aSource);
    aSource->Initialise(*this);
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
    if (!iReadStore.TryReadStoreItem(Brn("Product.Room"), aRoom)) {
        aRoom.Append(Brn("Main Room"));
    }
    if (!iReadStore.TryReadStoreItem(Brn("Product.Name"), aName)) {
        aName.Append(Brn("SoftPlayer")); // FIXME
    }
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufModelInfo, aInfo));
    // presentation url
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kBufModelImageUrl, aImageUri));
}

TBool Product::StandbyEnabled() const
{
    return false; // FIXME
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
        aXml.Append("<Source>");
        AppendTag(aXml, "Name", src->Name());
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
    iSources[iCurrentSource]->Activate();
    if (iObserver != NULL) {
        iObserver->SourceIndexChanged();
    }
}

void Product::SetCurrentSource(const Brx& aName)
{
    AutoMutex a(iLock);
    // volkano treats [name] as a system name and anything else as a user-defined name.  Do we need to do the same?
    for (TUint i=0; i<(TUint)iSources.size(); i++) {
        if (iSources[i]->Name() == aName) {
            iCurrentSource = i;
            // FIXME - activate new current source
            if (iObserver != NULL) {
                iObserver->SourceIndexChanged();
            }
            return;
        }
    }
    THROW(AvSourceNotFound);
}

void Product::GetSourceDetails(TUint aIndex, Bwx& aSystemName, Bwx& aType, Bwx& aName, TBool& aVisible)
{
    AutoMutex a(iLock);
    if (aIndex >= (TUint)iSources.size()) {
        THROW(AvSourceNotFound);
    }
    ISource* source = iSources[aIndex];
    aSystemName.Append(source->SystemName());
    aType.Append(source->Type());
    aName.Append(source->Name());
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
    ISource* srcNew = NULL;
    ISource* srcOld = NULL;

    AutoMutex a(iLock);
    // deactivate current (old) source, if one exists
    if (iCurrentSource != UINT_MAX) {
        srcOld = iSources[iCurrentSource];
        srcOld->Deactivate();
    }

    // find and activate new source
    for (TUint i=0; i<(TUint)iSources.size(); i++) {
        if (iSources[i]->Name() == aSource.Name()) {
            iCurrentSource = i;
            srcNew = iSources[i];
            srcNew->Activate();
            if (iObserver != NULL) {
                iObserver->SourceIndexChanged();
            }
            return;
        }
    }
    THROW(AvSourceNotFound);
}

void Product::QueryInfo(const Brx& /*aQuery*/, IWriter& /*aWriter*/)
{
}
