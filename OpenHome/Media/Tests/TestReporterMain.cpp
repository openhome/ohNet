#include <OpenHome/Private/TestFramework.h>

extern void TestReporter();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestReporter();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
