#include <OpenHome/Private/TestFramework.h>

extern void TestSkipper();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestSkipper();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
