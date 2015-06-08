#include <OpenHome/Private/TestFramework.h>

extern void TestMuter();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestMuter();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
