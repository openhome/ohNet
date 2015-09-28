#include <OpenHome/Private/TestFramework.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

extern void TestRaop(OpenHome::Environment& aEnv);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::Library* lib = new Net::Library(aInitParams);
    TestRaop(lib->Env());
    delete lib;
}
