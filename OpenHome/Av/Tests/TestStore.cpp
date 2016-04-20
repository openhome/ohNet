#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Av/KvpStore.h>
#include "RamStore.h"
#include <OpenHome/Buffer.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;

namespace OpenHome {
namespace Av {

class SuiteStore : public Suite
{
public:
    SuiteStore();
    void Test();
};

} // namespace Av
} // namespace OpenHome


SuiteStore::SuiteStore()
    : Suite("Kvp store tests")
{
}

void SuiteStore::Test()
{
    RamStore* ramStore = new RamStore(Brx::Empty());
    KvpStore* kvpStore = new KvpStore(*ramStore);
    IReadStore* rStore = (IReadStore*)kvpStore;

    // check static items can be read as static
    Brn value;
    TEST(rStore->TryReadStoreStaticItem(StaticDataKey::kBufModelInfo, value));
    TEST(value == Brn("Test implementation of ohMediaPlayer")); // slightly dodgy duplicating ro data from RamStore

    // check other (missing) item cannot be read
    Brn missing("missing");
    TEST(!rStore->TryReadStoreStaticItem(missing, value));

    // delete then recreate KvpStore
    // check static items can be read as before
    delete kvpStore;
    kvpStore = new KvpStore(*ramStore);
    rStore = (IReadStore*)kvpStore;
    TEST(rStore->TryReadStoreStaticItem(StaticDataKey::kBufModelInfo, value));
    TEST(value == Brn("Test implementation of ohMediaPlayer")); // slightly dodgy duplicating ro data from RamStore

    delete kvpStore;
    delete ramStore;
}


void TestStore()
{
    Runner runner("KvpStore tests\n");
    runner.Add(new SuiteStore());
    runner.Run();
}

