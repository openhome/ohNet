#include <OpenHome/Private/TestFramework.h>

extern void TestPrinter();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestPrinter();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
