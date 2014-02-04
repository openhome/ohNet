#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>

extern void TestHttpReader(OpenHome::Environment& aEnv);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::Library* lib = new Net::Library(aInitParams);
    TestHttpReader(lib->Env());
    delete lib;
}
