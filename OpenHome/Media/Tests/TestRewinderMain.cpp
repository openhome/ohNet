#include <OpenHome/Private/TestFramework.h>

extern void TestRewinder();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestRewinder();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
