#include <OpenHome/Private/TestFramework.h>
extern void TestVariableDelay();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestVariableDelay();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
