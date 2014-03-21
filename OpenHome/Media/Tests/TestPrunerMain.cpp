#include <OpenHome/Private/TestFramework.h>

extern void TestPruner();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestPruner();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
