#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Private/Globals.h>

extern void TestPipelineConfig();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::Library* lib = new Net::Library(aInitParams);
    TestPipelineConfig();
    delete lib;
}
