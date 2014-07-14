#include <OpenHome/Private/TestFramework.h>

extern void TestRamper();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestRamper();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
