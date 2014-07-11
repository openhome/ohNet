#include <OpenHome/Private/TestFramework.h>

extern void TestSilencer();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestSilencer();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
