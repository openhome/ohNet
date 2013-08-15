#include <OpenHome/Private/TestFramework.h>

extern void TestException();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestException();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
