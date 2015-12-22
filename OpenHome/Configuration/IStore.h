#pragma once

#include <OpenHome/Exception.h>

EXCEPTION(StoreKeyNotFound);
EXCEPTION(StoreReadBufferUndersized);
EXCEPTION(StoreWriteAllocationFailed);

namespace OpenHome {
    class Brx;
    class Bwx;

namespace Configuration {

/*
The zero-length key is considered invalid. API usage with a zero-length key
should throw StoreKeyNotFound
*/

class IStoreReadOnly
{
public:
    virtual ~IStoreReadOnly() {}
    virtual void Read(const Brx& aKey, Bwx& aDest) = 0;
};

/**
 * Interface onto persistent storage for configuration data.
 *
 * Data is arranged in key/value pairs.  Each key will map onto exactly one value.
 */
class IStoreReadWrite : public IStoreReadOnly
{
public:
    /**
     * Read an existing key from the store.
     *
     * @param[in]  aKey      Unique key.  Throws StoreKeyNotFound if this doesn't exist.
     * @param[out] aDest     Persisted value is written to this, replacing any existing content.
     *                       Throws StoreReadBufferUndersized if aDest is too small.  (This is
     *                       treated as a design-time error so the required size isn't reported.)
     */
    virtual void Read(const Brx& aKey, Bwx& aDest) = 0;
    /**
     * Write a new key to the store or replace the value for an existing key.
     *
     * @param[in]  aKey      Key.  A new entry is created if this doesn't already exist.
     *                       An existing value will be replaced if this does exist.
     *                       There is no limit on key size.
     * @param[in]  aSource   Value to be written.  There is no limit to the value's size.
     */
    virtual void Write(const Brx& aKey, const Brx& aSource) = 0;
    /**
     * Delete an existing key/value pair.
     *
     * @param[in]  aKey      Unique key.  Throws StoreKeyNotFound if this doesn't exist.
     */
    virtual void Delete(const Brx& aKey) = 0;
    virtual ~IStoreReadWrite() {}
};

} // namespace Configuration
} // namespace OpenHome

