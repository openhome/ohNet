#include <OpenHome/Private/TestFramework.h>

extern void TestVolumeManager();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestVolumeManager();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
