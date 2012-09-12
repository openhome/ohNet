#include <OpenHome/Av/Product.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/ProviderProduct.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Av/InfoProvider.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;


Product::Product(Net::DvDevice& aDevice, IReadStore& aReadStore, IInfoAggregator& /*aInfoAggregator*/)
    : iDevice(aDevice)
    , iReadStore(aReadStore)
    , iLock("PRDM")
    , iStarted(false)
    , iCurrentSource(0xffffffff)
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

void Product::Start()
{
    iStarted = true;
}

void Product::AddSource(Source* aSource)
{
    ASSERT(!iStarted);
    iSources.push_back(aSource);
}

void Product::GetManufacturerDetails(Brn& aName, Brn& aInfo, Brn& aUrl, Brn& aImageUri)
{
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kManufacturerName, aName));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kManufacturerInfo, aInfo));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kManufacturerUrl, aUrl));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kManufacturerImageUrl, aImageUri));
}

void Product::GetModelDetails(Brn& aName, Brn& aInfo, Brn& aUrl, Brn& aImageUri)
{
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kModelName, aName));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kModelInfo, aInfo));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kModelUrl, aUrl));
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kModelImageUrl, aImageUri));
}

void Product::GetProductDetails(Bwx& aRoom, Bwx& aName, Brn& aInfo, Brn& aImageUri)
{
    aRoom.SetBytes(0); // FIXME
    aName.SetBytes(0); // FIXME
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kModelInfo, aInfo));
    // presentation url
    ASSERT(iReadStore.TryReadStoreStaticItem(StaticDataKey::kModelImageUrl, aImageUri));
}

TUint Product::SourceCount() const
{
    return (TUint)iSources.size();
}

TUint Product::CurrentSourceIndex() const
{
    return iCurrentSource;
}

void Product::SetCurrentSource(TUint aIndex)
{
    AutoMutex a(iLock);
    if (aIndex >= (TUint)iSources.size()) {
        THROW(AvSourceNotFound);
    }
    iCurrentSource = aIndex;
}

void Product::SetCurrentSource(const Brx& aName)
{
    AutoMutex a(iLock);
    // volkano treats [name] as a system name and anything else as a user-defined name.  Do we need to do the same?
    for (TUint i=0; i<(TUint)iSources.size(); i++) {
        if (iSources[i]->Name() == aName) {
            iCurrentSource = i;
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
    Source* source = iSources[aIndex];
    aSystemName.Append(source->SystemName());
    aType.Append(source->Type());
    aName.Append(source->Name());
    aVisible = source->IsVisible();
}

TUint Product::SourceXmlChangeCount()
{
    ASSERTS();
    return 0xffffffff;
}

void Product::QueryInfo(const Brx& /*aQuery*/, IWriter& /*aWriter*/)
{
}
