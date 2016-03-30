#include <OpenHome/Private/TestFramework.h>

extern void TestStarvationRamper();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestStarvationRamper();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
