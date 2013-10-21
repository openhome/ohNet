#include <OpenHome/Private/TestFramework.h>

extern void TestPowerManager(OpenHome::Environment& aEnv);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Environment* env = Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestPowerManager(*env);
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
