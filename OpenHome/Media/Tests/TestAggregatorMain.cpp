#include <OpenHome/Private/TestFramework.h>

extern void TestAggregator();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestAggregator();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
