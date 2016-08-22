#include <OpenHome/Private/TestFramework.h>

extern void TestUriProviderRepeater();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestUriProviderRepeater();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
