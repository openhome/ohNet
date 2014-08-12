#include <OpenHome/Private/TestFramework.h>

extern void TestFunctorGeneric();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestFunctorGeneric();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
