#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>

#include <map>

using namespace OpenHome;
using namespace OpenHome::Av;

// StaticDataKey

const TChar* StaticDataKey::kManufacturerName     = "Manufacturer.Name";
const TChar* StaticDataKey::kManufacturerInfo     = "Manufacturer.Info";
const TChar* StaticDataKey::kManufacturerUrl      = "Manufacturer.Url";
const TChar* StaticDataKey::kManufacturerImageUrl = "Manufacturer.ImageUrl";
const TChar* StaticDataKey::kModelName            = "Model.Name";
const TChar* StaticDataKey::kModelInfo            = "Model.Info";
const TChar* StaticDataKey::kModelUrl             = "Model.Url";
const TChar* StaticDataKey::kModelImageUrl        = "Model.ImageUrl";
const Brn StaticDataKey::kBufManufacturerName     = Brn(kManufacturerName);
const Brn StaticDataKey::kBufManufacturerInfo     = Brn(kManufacturerInfo);
const Brn StaticDataKey::kBufManufacturerUrl      = Brn(kManufacturerUrl);
const Brn StaticDataKey::kBufManufacturerImageUrl = Brn(kManufacturerImageUrl);
const Brn StaticDataKey::kBufModelName            = Brn(kModelName);
const Brn StaticDataKey::kBufModelInfo            = Brn(kModelInfo);
const Brn StaticDataKey::kBufModelUrl             = Brn(kModelUrl);
const Brn StaticDataKey::kBufModelImageUrl        = Brn(kModelImageUrl);


// KvpStore

KvpStore::KvpStore(IStaticDataSource& aStaticData)
    : iLock("KVPS")
{
    aStaticData.LoadStaticData(*this);
}

KvpStore::~KvpStore()
{
    Map::iterator it = iStaticData.begin();
    while (it != iStaticData.end()) {
        delete it->second;
        it++;
    }
}

TBool KvpStore::TryReadStoreStaticItem(const Brx& aKey, Brn& aValue)
{
    Brn key(aKey);
    AutoMutex a(iLock);
    Map::iterator it = iStaticData.find(key);
    if (it != iStaticData.end()) {
        it->second->GetValue(aValue);
        return true;
    }
    return false;
}

void KvpStore::AddStaticItem(const Brx& aKey, const TChar* aValue)
{
    Brn key(aKey);
    AutoMutex a(iLock);
    Map::iterator it = iStaticData.find(key);
    if (it != iStaticData.end()) {
        THROW(AvStoreKeyAlreadyExists);
    }
    KvpPair* kvp = new KvpPairStatic(aValue);
    iStaticData.insert(std::pair<Brn, KvpPair*>(key, kvp));
}


// KvpStore::KvpPair

KvpStore::KvpPair::~KvpPair()
{
}

KvpStore::KvpPair::KvpPair()
{
}


// KvpStore::KvpPairStatic

KvpStore::KvpPairStatic::KvpPairStatic(const TChar* aValue)
    : iValue(aValue)
{
}

void KvpStore::KvpPairStatic::GetValue(Brn& aValue)
{
    aValue.Set(iValue);
}
