#include <OpenHome/Private/TestFramework.h>

extern void TestHttp();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    aInitParams->SetUseLoopbackNetworkAdapter();
    Net::Library* lib = new Net::Library(aInitParams);
    TestHttp();
    delete lib;
}