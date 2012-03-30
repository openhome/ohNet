#include <OpenHome/Private/TestFramework.h>

extern void TestBuffer();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestBuffer();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
