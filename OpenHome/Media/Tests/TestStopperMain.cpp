#include <OpenHome/Private/TestFramework.h>

extern void TestStopper();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestStopper();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
