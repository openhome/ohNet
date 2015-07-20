#include <OpenHome/Private/TestFramework.h>

extern void TestWebAppFramework(OpenHome::Environment& aEnv);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::Library* lib = new Net::Library(aInitParams);
    TestWebAppFramework(lib->Env());
    delete lib;
}
