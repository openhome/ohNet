#include <OpenHome/Private/TestFramework.h>

extern void TestSampleReporter();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestSampleReporter();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
