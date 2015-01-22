#include <OpenHome/Private/TestFramework.h>

extern void TestSpotifyReporter();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestSpotifyReporter();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
