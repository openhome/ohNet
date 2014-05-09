#include <OpenHome/Private/TestFramework.h>

extern void TestGorger();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestGorger();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
