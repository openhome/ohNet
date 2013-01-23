#include <OpenHome/Private/TestFramework.h>

extern void TestStarvationMonitor();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestStarvationMonitor();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
