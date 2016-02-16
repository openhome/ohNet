#include <OpenHome/Private/TestFramework.h>

extern void TestAnalogBypassRamper();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestAnalogBypassRamper();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
