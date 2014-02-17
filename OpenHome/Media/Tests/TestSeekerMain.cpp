#include <OpenHome/Private/TestFramework.h>

extern void TestSeeker();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestSeeker();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
