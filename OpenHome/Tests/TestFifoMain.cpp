#include <OpenHome/Private/TestFramework.h>

extern void TestFifo();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestFifo();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
