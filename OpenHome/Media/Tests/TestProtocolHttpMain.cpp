#include <OpenHome/Private/TestFramework.h>

extern void TestProtocolHttp();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    aInitParams->SetUseLoopbackNetworkAdapter();
    Net::Library* lib = new Net::Library(aInitParams);
    TestProtocolHttp();
    delete lib;
}
