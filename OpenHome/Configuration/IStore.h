#ifndef HEADER_ISTORE
#define HEADER_ISTORE

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
    virtual void Read(const Brx& aKey, Bwx& aDest) = 0;
};

class IStoreReadWrite : public IStoreReadOnly
{
public:
    virtual void Read(const Brx& aKey, Bwx& aDest) = 0;
    virtual void Write(const Brx& aKey, const Brx& aSource) = 0;
    virtual void Delete(const Brx& aKey) = 0;
    virtual ~IStoreReadWrite() {}
};

} // namespace Configuration
} // namespace OpenHome

#endif // HEADER_ISTORE
