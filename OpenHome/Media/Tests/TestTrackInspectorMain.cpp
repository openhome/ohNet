#include <OpenHome/Private/TestFramework.h>

extern void TestTrackInspector();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestTrackInspector();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
