#include <OpenHome/Private/TestFramework.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

extern void TestShellCommandLogMode(OpenHome::Environment& aEnv);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Environment* env = Net::UpnpLibrary::Initialise(aInitParams);
    TestShellCommandLogMode(*env);
    Net::UpnpLibrary::Close();
}
