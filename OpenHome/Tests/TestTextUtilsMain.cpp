#include <OpenHome/Private/TestFramework.h>

extern void TestTextUtils();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::Initialise(aInitParams);
    TestTextUtils();
    Net::UpnpLibrary::Close();
}
