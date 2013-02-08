#include <OpenHome/Private/TestFramework.h>

extern void TestPipeline();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestPipeline();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
