#include <OpenHome/Private/TestFramework.h>

extern void TestStore();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestStore();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
