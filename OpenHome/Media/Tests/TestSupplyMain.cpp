#include <OpenHome/Private/TestFramework.h>

extern void TestSupply();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestSupply();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
