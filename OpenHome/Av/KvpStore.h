#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>

#include <map>

EXCEPTION(AvStoreKeyAlreadyExists);

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
    // FIXME - why aren't all keys string literals?
    virtual TBool TryReadStoreStaticItem(const Brx& aKey, Brn& aValue) = 0; // read item whose value is fixed at compile time.  Returned values are nul-terminated.
};

class IStoreLoaderStatic
{
public:
    virtual void AddStaticItem(const Brx& aKey, const TChar* aValue) = 0;
};

class StaticDataKey
{
public:
    static const TChar* kManufacturerName;
    static const TChar* kManufacturerInfo;
    static const TChar* kManufacturerUrl;
    static const TChar* kManufacturerImageUrl;
    static const TChar* kModelName;
    static const TChar* kModelInfo;
    static const TChar* kModelUrl;
    static const TChar* kModelImageUrl;
    static const Brn kBufManufacturerName;
    static const Brn kBufManufacturerInfo;
    static const Brn kBufManufacturerUrl;
    static const Brn kBufManufacturerImageUrl;
    static const Brn kBufModelName;
    static const Brn kBufModelInfo;
    static const Brn kBufModelUrl;
    static const Brn kBufModelImageUrl;
};

// data that is hard-coded for a device so doesn't need to be written to disk
class IStaticDataSource
{
public:
    // the following keys must be present
    // ...
    // other keys may have their values hard-coded
    virtual void LoadStaticData(IStoreLoaderStatic& aLoader) = 0;
    virtual ~IStaticDataSource() {}
};

class KvpStore : public IReadStore,
                 private IStoreLoaderStatic
{
public:
    KvpStore(IStaticDataSource& aStaticData);
    virtual ~KvpStore();
private: // from IReadStore
    TBool TryReadStoreStaticItem(const Brx& aKey, Brn& aValue) override;
private: // from IStoreLoaderStatic
    void AddStaticItem(const Brx& aKey, const TChar* aValue) override;
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
private:
    Mutex iLock;
    typedef std::map<Brn, KvpPair*, BufferCmp> Map;
    Map iStaticData;
};

} // namespace Av
} // namespace OpenHome

