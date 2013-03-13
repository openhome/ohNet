#include <OpenHome/Private/TestFramework.h>

extern void TestContentProcessor();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestContentProcessor();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
