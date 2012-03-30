#include <OpenHome/Private/TestFramework.h>

extern void TestQueue();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::Initialise(aInitParams);
    TestQueue();
    Net::UpnpLibrary::Close();
}
