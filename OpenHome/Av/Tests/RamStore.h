#ifndef HEADER_RAM_STORE
#define HEADER_RAM_STORE

#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

#include <map>

namespace OpenHome {
namespace Av {

/**
 * Helper class for test code.  Not intended for client use.
 */
class RamStore : public IStaticDataSource
{
public:
    virtual ~RamStore();
private: // from IStaticDataSource
    void LoadStaticData(IStoreLoaderStatic& aLoader) override;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_RAM_STORE
