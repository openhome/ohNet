#include <OpenHome/Private/TestFramework.h>

extern void TestFriendlyNameManager();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestFriendlyNameManager();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
