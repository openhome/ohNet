#include <OpenHome/Private/TestFramework.h>

extern void Test();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    Test();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
