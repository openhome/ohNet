#include <OpenHome/Private/TestFramework.h>

extern void TestThread();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestThread();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
