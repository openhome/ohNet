#pragma once

#include <OpenHome/Configuration/BufferPtrCmp.h>
#include <OpenHome/Configuration/IStore.h>
#include <OpenHome/Private/Thread.h>

#include <map>

namespace OpenHome {
namespace Configuration {

/*
 * Class providing a basic implementation of a read/write store for storing
 * configuration in memory (no file writing, so no persistence between runs).
 */
class ConfigRamStore : public IStoreReadWrite
{
public:
    ConfigRamStore();
    virtual ~ConfigRamStore();
    void Print() const;
    TUint WriteCount() const;
public: // from IStoreReadWrite
    void Read(const Brx& aKey, Bwx& aDest) override;
    void Write(const Brx& aKey, const Brx& aSource) override;
    void Delete(const Brx& aKey) override;
private:
    void Clear();
private:
    typedef std::map<const Brx*, const Brx*, BufferPtrCmp> Map;
    Map iMap;
    mutable Mutex iLock;
    TUint iWriteCount;
};

} // namespace Configuration
} // namespace OpenHome

