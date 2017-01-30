#include <OpenHome/Private/TestFramework.h>

extern void TestMuterVolume();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestMuterVolume();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
