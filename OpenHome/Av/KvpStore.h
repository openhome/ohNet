#ifndef HEADER_KVPSTORE
#define HEADER_KVPSTORE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>

#include <map>

EXCEPTION(AvStoreKeyTooLong);
EXCEPTION(AvStoreValueTooLong);
EXCEPTION(AvStoreKeyAlreadyExists);
EXCEPTION(AvStoreValueIsReadOnly);

namespace OpenHome {
namespace Av {

enum
{
    StoreMaxKeyLength = 32
   ,StoreMaxValueLength = 32
};

class IReadStore
{
public:
    virtual TBool TryReadStoreItem(const Brx& aKey, Bwx& aValue) = 0; // take copy of item (which may change at any time).  Returned values may not be nul-terminated.
    virtual TBool TryReadStoreStaticItem(const Brx& aKey, Brn& aValue) = 0; // read item whose value is fixed at compile time.  Returned values are nul-terminated.
};

class IReadWriteStore : public IReadStore
{
public:
    virtual TBool WriteStoreItem(const Brx& aKey, const Brx& aValue) = 0; // returns true if aValue is different from previous value
};

class IStoreLoaderDynamic
{
public:
    virtual void AddStaticItem(const Brx& aKey, const TChar* aValue) = 0;
};

class IStoreLoaderStatic
{
public:
    virtual void AddPersistedItem(const Brx& aKey, const Brx& aValue) = 0;
};

class IStoreIterator
{
public:
    virtual TBool TryReadNextPersistedItem(Brn& aKey, Brn& aValue) = 0;
};

class IPersistor
{
public:
    virtual void LoadPersistedData(IStoreLoaderDynamic& aLoader) = 0;
    virtual void Save(IStoreIterator& aIterator) = 0;
};

class StaticDataKey
{
public:
    static const Brn kManufacturerName;
    static const Brn kManufacturerInfo;
    static const Brn kManufacturerUrl;
    static const Brn kManufacturerImageUrl;
    static const Brn kModelName;
    static const Brn kModelInfo;
    static const Brn kModelUrl;
    static const Brn kModelImageUrl;
};

// data that is hard-coded for a device so doesn't need to be written to disk
class IStaticDataSource
{
public:
    // the following keys must be present
    // ...
    // other keys may have their values hard-coded
    virtual void LoadStaticData(IStoreLoaderStatic& aLoader) = 0;
};

class KvpStore : public IReadWriteStore,
                 private IStoreLoaderStatic, private IStoreLoaderDynamic, private IStoreIterator
{
public:
    KvpStore(IStaticDataSource& aStaticData, IPersistor& aPersistedData);
    ~KvpStore();
private: // from IReadWriteStore
    TBool TryReadStoreItem(const Brx& aKey, Bwx& aValue);
    TBool TryReadStoreStaticItem(const Brx& aKey, Brn& aValue);
    TBool WriteStoreItem(const Brx& aKey, const Brx& aValue);
private: // from IStoreLoaderStatic
    void AddStaticItem(const Brx& aKey, const TChar* aValue);
private: // from IStoreLoaderDynamic
    void AddPersistedItem(const Brx& aKey, const Brx& aValue);
private: // from IStoreIterator
    TBool TryReadNextPersistedItem(Brn& aKey, Brn& aValue);
private:
    class KvpPair
    {
    public:
        virtual ~KvpPair();
        virtual void GetValue(Brn& aValue) = 0;
    protected:
        KvpPair();
    };
    class KvpPairStatic : public KvpPair
    {
    public:
        KvpPairStatic(const TChar* aValue);
    private:
        void GetValue(Brn& aValue);
    private:
        const TChar* iValue;
    };
    class KvpPairPersisted : public KvpPair
    {
    public:
        KvpPairPersisted(const Brx& aKey, const Brx& aValue);
        TBool UpdateValue(const Brx& aValue);
    private:
        void GetValue(Brn& aValue);
    private:
        Bws<StoreMaxKeyLength> iKey;
        Bws<StoreMaxValueLength> iValue;
    };
private:
    IPersistor& iPersistor;
    Mutex iLock;
    typedef std::map<Brn, KvpPair*, BufferCmp> Map;
    Map iStaticData;
    Map iPersistedData;
    Map::iterator iPersistorIterator;
    TBool iSaving;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_KVPSTORE
