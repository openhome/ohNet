#include <OpenHome/Private/TestFramework.h>

extern void TestWebAppFramework();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::Initialise(aInitParams);
    TestWebAppFramework();
    Net::UpnpLibrary::Close();
}
