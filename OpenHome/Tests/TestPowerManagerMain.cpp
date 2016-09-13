#include <OpenHome/Private/TestFramework.h>

extern void TestPowerManager();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    (void)Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestPowerManager();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
