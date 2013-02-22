#include <OpenHome/Private/TestFramework.h>

extern void TestFile();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestFile();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
