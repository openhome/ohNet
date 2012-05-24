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
    RamStore* ramStore = new RamStore();
    KvpStore* kvpStore = new KvpStore(*ramStore, *ramStore);
    IReadWriteStore* rwStore = (IReadWriteStore*)kvpStore;

    // check static items can be read as static
    Brn value;
    TEST(rwStore->TryReadStoreStaticItem(StaticDataKey::kModelInfo, value));
    TEST(value == Brn("Test implementation of ohMediaPlayer")); // slightly dodgy duplicating ro data from RamStore
    
    // check static items cannot be read as dynamic
    Bws<StoreMaxValueLength> value2;
    TEST(!rwStore->TryReadStoreItem(StaticDataKey::kModelInfo, value2));

    // check other (missing) item cannot be read via either route
    Brn missing("missing");
    TEST(!rwStore->TryReadStoreStaticItem(missing, value));
    TEST(!rwStore->TryReadStoreItem(missing, value2));

    // add dynamic item.  Check it can be read as dynamic but not as static
    Brn dynamicKey("newKey");
    Brn dynamicValue("dynamicValue");
    TEST(rwStore->WriteStoreItem(dynamicKey, dynamicValue));
    TEST(!rwStore->TryReadStoreStaticItem(dynamicKey, value));
    TEST(rwStore->TryReadStoreItem(dynamicKey, value2));
    TEST(value2 == dynamicValue);

    // try add dynamic value with over-long key.  Check this throws
    Brn longKey("longKeyThatGoesOnAndOnUntilWellOverTheThirtyTwoCharLimit");
    TEST_THROWS(rwStore->WriteStoreItem(longKey, dynamicValue), AvStoreKeyTooLong);

    // try add dynamic value with over-long value.  Check this throws
    Brn longValue("longValueThatGoesOnAndOnUntilWellOverTheThirtyTwoCharLimit");
    TEST_THROWS(rwStore->WriteStoreItem(dynamicKey, longValue), AvStoreValueTooLong);

    // add same item with same value.  Check 'no change' is returned
    TEST(!rwStore->WriteStoreItem(dynamicKey, dynamicValue));

    // update dynamic item.  Check new value can be read
    Brn dynamicValue2("newDynamicValue");
    TEST(rwStore->WriteStoreItem(dynamicKey, dynamicValue2));
    TEST(rwStore->TryReadStoreItem(dynamicKey, value2));
    TEST(value2 == dynamicValue2);

    // try update static item.  Check this throws
    TEST_THROWS(rwStore->WriteStoreItem(StaticDataKey::kModelInfo, dynamicValue2), AvStoreValueIsReadOnly);
    
    // delete then recreate KvpStore
    // check both dynamic and static items can be read as before
    delete kvpStore;
    kvpStore = new KvpStore(*ramStore, *ramStore);
    rwStore = (IReadWriteStore*)kvpStore;
    TEST(rwStore->TryReadStoreStaticItem(StaticDataKey::kModelInfo, value));
    TEST(value == Brn("Test implementation of ohMediaPlayer")); // slightly dodgy duplicating ro data from RamStore
    TEST(!rwStore->TryReadStoreItem(StaticDataKey::kModelInfo, value2));
    TEST(rwStore->TryReadStoreItem(dynamicKey, value2));
    TEST(value2 == dynamicValue2);
    
    delete kvpStore;
    delete ramStore;
}


void TestStore()
{
    Runner runner("KvpStore tests\n");
    runner.Add(new SuiteStore());
    runner.Run();
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestStore();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
