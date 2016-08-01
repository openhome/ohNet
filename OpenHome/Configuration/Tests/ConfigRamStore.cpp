#include <OpenHome/Configuration/Tests/ConfigRamStore.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Configuration;

// ConfigRamStore

ConfigRamStore::ConfigRamStore()
    : iLock("RAMS")
    , iWriteCount(0)
{
}

ConfigRamStore::~ConfigRamStore()
{
    Clear();
}

void ConfigRamStore::Print() const
{
    Log::Print("RamStore: [\n");
    AutoMutex a(iLock);
    Map::const_iterator it = iMap.begin();
    while (it!= iMap.end()) {
        Log::Print("   {");
        Log::Print(*it->first);
        Log::Print(", ");
        const Brx& valBuf = *it->second;
        if (valBuf.Bytes() == sizeof(TUint32)) {
            TUint32 val = Converter::BeUint32At(valBuf, 0);
            Log::Print("%u/", val);
            Log::Print(valBuf);
        }
        else {
            Log::Print(valBuf);
        }
        Log::Print("}\n");
        it++;
    }
    Log::Print("]\n");
}

TUint ConfigRamStore::WriteCount() const
{
    AutoMutex _(iLock);
    return iWriteCount;
}

void ConfigRamStore::Read(const Brx& aKey, Bwx& aDest)
{
    Brn key(aKey);
    AutoMutex a(iLock);
    Map::iterator it = iMap.find(&key);
    if (it == iMap.end()) {
        THROW(StoreKeyNotFound);
    }

    if (it->second->Bytes() > aDest.MaxBytes()) {
        THROW(StoreReadBufferUndersized);
    }

    aDest.Replace(*(it->second));
}

void ConfigRamStore::Write(const Brx& aKey, const Brx& aSource)
{
    Brh* key = new Brh(aKey);
    Brh* val = new Brh(aSource);

    AutoMutex a(iLock);

    iWriteCount++;

    // std::map doesn't insert a value if key exists, so first remove existing
    // key-value pair, if new value is different
    Map::iterator it = iMap.find(key);
    if (it != iMap.end()) {
        if (*(it->second) == aSource) {
            // new value is the same; free memory
            delete key;
            delete val;
            return;
        }
        else {
            // new value is different; remove old value
            delete it->first;
            delete it->second;
            iMap.erase(it);
        }
    }

    iMap.insert(std::pair<const Brx*, const Brx*>(key, val));
}

void ConfigRamStore::Delete(const Brx& aKey)
{
    Brn key(aKey);
    AutoMutex a(iLock);
    Map::iterator it = iMap.find(&key);
    if (it == iMap.end()) {
        THROW(StoreKeyNotFound);
    }

    delete it->first;
    delete it->second;
    iMap.erase(it);
}

void ConfigRamStore::Clear()
{
    AutoMutex a(iLock);
    Map::iterator it = iMap.begin();
    while (it != iMap.end()) {
        delete it->first;
        delete it->second;
        it++;
    }
    iMap.clear();
}
