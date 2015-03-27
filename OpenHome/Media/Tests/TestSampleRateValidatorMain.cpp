#include <OpenHome/Private/TestFramework.h>

extern void TestSampleRateValidator();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestSampleRateValidator();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
