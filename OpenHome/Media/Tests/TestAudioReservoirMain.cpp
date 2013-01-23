#include <OpenHome/Private/TestFramework.h>

extern void TestAudioReservoir();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestAudioReservoir();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
