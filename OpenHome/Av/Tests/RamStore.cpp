#include "RamStore.h"
#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Private/Printer.h>

#include <map>

using namespace OpenHome;
using namespace OpenHome::Av;

RamStore::~RamStore()
{
    Clear();
}

void RamStore::AddItem(const TChar* aKey, const TChar* aValue)
{
    Brn key(aKey);
    Map::iterator it = iItems.find(key);
    if (it != iItems.end()) {
        delete it->second;
        it->second = new Brh(aValue);
    }
    else {
        Brh* val = new Brh(aValue);
        iItems.insert(std::pair<Brn,Brh*>(key, val));
    }
}

void RamStore::List()
{
    Log::Print("RamStore: [\n");
    Map::iterator it = iItems.begin();
    while (it != iItems.end()) {
        Log::Print("   {");
        Log::Print(it->first);
        Log::Print(", ");
        Log::Print(*it->second);
        Log::Print("}\n");
        it++;
    }
    Log::Print("]\n");
}

void RamStore::LoadStaticData(IStoreLoaderStatic& aLoader)
{
    aLoader.AddStaticItem(StaticDataKey::kBufManufacturerName, "OpenHome");
    aLoader.AddStaticItem(StaticDataKey::kBufManufacturerInfo, "insert oh info here...");
    aLoader.AddStaticItem(StaticDataKey::kBufManufacturerUrl, "http://www.openhome.org");
    aLoader.AddStaticItem(StaticDataKey::kBufManufacturerImageUrl, "http://www.openhome.org/common/images/core/open-home-logo.png");
    aLoader.AddStaticItem(StaticDataKey::kBufModelName, "OpenHome Media Player (test)");
    aLoader.AddStaticItem(StaticDataKey::kBufModelInfo, "Test implementation of ohMediaPlayer");
    aLoader.AddStaticItem(StaticDataKey::kBufModelUrl, "http://www.openhome.org/wiki/OhMedia");
    aLoader.AddStaticItem(StaticDataKey::kBufModelImageUrl, "http://www.openhome.org/common/images/core/open-home-logo.png");
}

void RamStore::LoadPersistedData(IStoreLoaderDynamic& aLoader)
{
    Map::iterator it = iItems.begin();
    while (it != iItems.end()) {
        aLoader.AddPersistedItem(it->first, *it->second);
        it++;
    }
}

void RamStore::Save(IStoreIterator& aIterator)
{
    Clear();
    Brn key;
    Brn value;
    while (aIterator.TryReadNextPersistedItem(key, value)) {
        Brh* val = new Brh(value);
        iItems.insert(std::pair<Brn,Brh*>(key, val));
    }
}

void RamStore::Clear()
{
    Map::iterator it = iItems.begin();
    while (it != iItems.end()) {
        delete it->second;
        it++;
    }
    iItems.clear();
}
