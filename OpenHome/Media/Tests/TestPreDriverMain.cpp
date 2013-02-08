#include <OpenHome/Private/TestFramework.h>

extern void TestPreDriver();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestPreDriver();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
