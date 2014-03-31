#include <OpenHome/Private/TestFramework.h>

extern void TestWaiter();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestWaiter();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
