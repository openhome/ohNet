#include <OpenHome/Private/TestFramework.h>

extern void TestCodec();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestCodec();
    //delete aInitParams;
    Net::UpnpLibrary::Close();
}
