#ifndef HEADER_RAM_STORE
#define HEADER_RAM_STORE

#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>

#include <map>

namespace OpenHome {
namespace Av {

/**
 * Helper class for test code.  Not intended for client use.
 */
class RamStore : public IStaticDataSource, public IPersister
{
public:
    ~RamStore();
    void AddItem(const TChar* aKey, const TChar* aValue);
    void List();
private: // from IStaticDataSource
    void LoadStaticData(IStoreLoaderStatic& aLoader);
private: // from IPersister
    void LoadPersistedData(IStoreLoaderDynamic& aLoader);
    void Save(IStoreIterator& aIterator);
private:
    typedef std::map<Brn, Brh*, BufferCmp> Map;
    Map iItems;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_RAM_STORE
