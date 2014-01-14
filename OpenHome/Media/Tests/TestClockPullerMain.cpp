#include <OpenHome/Private/TestFramework.h>

extern void TestClockPuller();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestClockPuller();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
