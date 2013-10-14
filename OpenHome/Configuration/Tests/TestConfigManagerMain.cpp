#include <OpenHome/Private/TestFramework.h>

extern void TestConfigManager();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestConfigManager();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
