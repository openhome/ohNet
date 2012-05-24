#include "RamStore.h"
#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Private/Printer.h>

#include <map>

using namespace OpenHome;
using namespace OpenHome::Av;

RamStore::~RamStore()
{
    Map::iterator it = iItems.begin();
    while (it != iItems.end()) {
        delete it->second;
        it++;
    }
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
    aLoader.AddStaticItem(StaticDataKey::kManufacturerName, "OpenHome");
    aLoader.AddStaticItem(StaticDataKey::kManufacturerInfo, "insert oh info here...");
    aLoader.AddStaticItem(StaticDataKey::kManufacturerUrl, "http://www.openhome.org");
    aLoader.AddStaticItem(StaticDataKey::kManufacturerImageUrl, "http://www.openhome.org/common/images/core/open-home-logo.png");
    aLoader.AddStaticItem(StaticDataKey::kModelName, "OpenHome Media Player (test)");
    aLoader.AddStaticItem(StaticDataKey::kModelInfo, "Test implementation of ohMediaPlayer");
    aLoader.AddStaticItem(StaticDataKey::kModelUrl, "http://www.openhome.org/wiki/OhMedia");
    aLoader.AddStaticItem(StaticDataKey::kModelImageUrl, "http://www.openhome.org/common/images/core/open-home-logo.png");
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
    iItems.clear();
    Brn key;
    Brn value;
    while (aIterator.TryReadNextPersistedItem(key, value)) {
        Brh* val = new Brh(value);
        iItems.insert(std::pair<Brn,Brh*>(key, val));
    }
}
