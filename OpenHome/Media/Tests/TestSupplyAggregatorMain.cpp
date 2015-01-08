#include <OpenHome/Private/TestFramework.h>

extern void TestSupplyAggregator();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestSupplyAggregator();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
