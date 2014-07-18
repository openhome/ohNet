#include <OpenHome/Private/TestFramework.h>

extern void TestStream();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestStream();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
