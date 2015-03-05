#include <OpenHome/Private/TestFramework.h>

extern void TestProtocolHls(OpenHome::Environment& aEnv);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    aInitParams->SetUseLoopbackNetworkAdapter();
    Net::Library* lib = new Net::Library(aInitParams);
    TestProtocolHls(lib->Env());
    delete lib;
}
