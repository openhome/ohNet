#include <OpenHome/Private/TestFramework.h>

extern void TestTimestampInspector();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestTimestampInspector();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
