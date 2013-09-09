#include <OpenHome/Private/TestFramework.h>

using namespace OpenHome;

extern void TestUdpServer(Environment& aEnv);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::Library* lib = new Net::Library(aInitParams);
    TestUdpServer(lib->Env());
    delete lib;
}
