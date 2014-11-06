#include <OpenHome/Private/TestFramework.h>

extern void TestSsl(OpenHome::Environment& aEnv);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Environment* env = Net::UpnpLibrary::Initialise(aInitParams);
    TestSsl(*env);
    Net::UpnpLibrary::Close();
}
