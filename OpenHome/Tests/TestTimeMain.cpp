#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Core/OhNet.h>

using namespace OpenHome;

extern void TestTime(Environment& aEnv);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::Library* lib = new Net::Library(aInitParams);
    TestTime(lib->Env());
    delete lib;
}
