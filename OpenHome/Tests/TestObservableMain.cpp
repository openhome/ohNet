#include <OpenHome/Private/TestFramework.h>

extern void TestObservable();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestObservable();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
