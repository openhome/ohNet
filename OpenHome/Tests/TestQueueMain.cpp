#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Core/OhNet.h>

extern void TestQueue();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Environment* env = Environment::Create(aInitParams->LogOutput(),
                                           aInitParams->TimerManagerPriority(),
                                           aInitParams->SchedulingPolicy(),
                                           aInitParams->LoopbackNetworkAdapter());
    TestQueue();
    delete env;
    delete aInitParams;
}
