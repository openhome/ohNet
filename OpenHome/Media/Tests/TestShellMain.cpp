#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Tests/TestCodec.h>
#include <OpenHome/Media/Tests/TestShell.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

SIMPLE_TEST_DECLARATION(TestAggregator);
SIMPLE_TEST_DECLARATION(TestAudioReservoir);
SIMPLE_TEST_DECLARATION(TestCodecController);
SIMPLE_TEST_DECLARATION(TestConfigManager);
SIMPLE_TEST_DECLARATION(TestContainer);
SIMPLE_TEST_DECLARATION(TestContentProcessor);
SIMPLE_TEST_DECLARATION(TestIdProvider);
SIMPLE_TEST_DECLARATION(TestFiller);
SIMPLE_TEST_DECLARATION(TestToneGenerator);
SIMPLE_TEST_DECLARATION(TestMuteManager);
SIMPLE_TEST_DECLARATION(TestVolumeManager);
SIMPLE_TEST_DECLARATION(TestMsg);
SIMPLE_TEST_DECLARATION(TestPipeline);
SIMPLE_TEST_DECLARATION(TestPreDriver);
SIMPLE_TEST_DECLARATION(TestProtocolHttp);
SIMPLE_TEST_DECLARATION(TestReporter);
SIMPLE_TEST_DECLARATION(TestRewinder);
SIMPLE_TEST_DECLARATION(TestSeeker);
SIMPLE_TEST_DECLARATION(TestSkipper);
SIMPLE_TEST_DECLARATION(TestGorger);
SIMPLE_TEST_DECLARATION(TestPruner);
SIMPLE_TEST_DECLARATION(TestStarvationMonitor);
SIMPLE_TEST_DECLARATION(TestStopper);
SIMPLE_TEST_DECLARATION(TestStore);
SIMPLE_TEST_DECLARATION(TestSupply);
SIMPLE_TEST_DECLARATION(TestTrackDatabase);
SIMPLE_TEST_DECLARATION(TestTrackInspector);
SIMPLE_TEST_DECLARATION(TestUriProviderRepeater);
SIMPLE_TEST_DECLARATION(TestVariableDelay);
SIMPLE_TEST_DECLARATION(TestWaiter);
ENV_TEST_DECLARATION(TestUdpServer);
ENV_TEST_DECLARATION(TestPowerManager);


extern void TestCodec(OpenHome::Environment& aEnv, CreateTestCodecPipelineFunc aFunc, GetTestFiles aFiles, const std::vector<Brn>& aArgs);
extern TestCodecMinimalPipeline* CreateTestCodecPipeline(Environment& aEnv, IMsgProcessor& aMsgProcessor);
extern AudioFileCollection* TestCodecFiles();

static void ShellTestCodec(CpStack& aCpStack, DvStack& /*aDvStack*/, const std::vector<Brn>& aArgs)
{
    TestCodec(aCpStack.Env(), CreateTestCodecPipeline, TestCodecFiles, aArgs);
}

extern void TestUpnpErrors(CpStack& aCpStack, DvStack& aDvStack);
static void ShellTestUpnpErrors(CpStack& aCpStack, DvStack& aDvStack, const std::vector<Brn>& /*aArgs*/)
{
    TestUpnpErrors(aCpStack, aDvStack);
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    std::vector<ShellTest> shellTests;
    shellTests.push_back(ShellTest("TestAggregator", ShellTestAggregator));
    shellTests.push_back(ShellTest("TestAudioReservoir", ShellTestAudioReservoir));
    shellTests.push_back(ShellTest("TestCodecController", ShellTestCodecController));
    shellTests.push_back(ShellTest("TestConfigManager", ShellTestConfigManager));
    shellTests.push_back(ShellTest("TestContainer", ShellTestContainer));
    shellTests.push_back(ShellTest("TestContentProcessor", ShellTestContentProcessor));
    shellTests.push_back(ShellTest("TestIdProvider", ShellTestIdProvider));
    shellTests.push_back(ShellTest("TestFiller", ShellTestFiller));
    shellTests.push_back(ShellTest("TestToneGenerator", ShellTestToneGenerator));
    shellTests.push_back(ShellTest("TestMuteManager", ShellTestMuteManager));
    shellTests.push_back(ShellTest("TestVolumeManager", ShellTestVolumeManager));
    shellTests.push_back(ShellTest("TestMsg", ShellTestMsg));
    shellTests.push_back(ShellTest("TestPipeline", ShellTestPipeline));
    shellTests.push_back(ShellTest("TestPowerManager", ShellTestPowerManager));
    shellTests.push_back(ShellTest("TestPreDriver", ShellTestPreDriver));
    shellTests.push_back(ShellTest("TestProtocolHttp", ShellTestProtocolHttp));
    shellTests.push_back(ShellTest("TestReporter", ShellTestReporter));
    shellTests.push_back(ShellTest("TestSeeker", ShellTestSeeker));
    shellTests.push_back(ShellTest("TestSkipper", ShellTestSkipper));
    shellTests.push_back(ShellTest("TestPruner", ShellTestPruner));
    shellTests.push_back(ShellTest("TestGorger", ShellTestGorger));
    shellTests.push_back(ShellTest("TestStarvationMonitor", ShellTestStarvationMonitor));
    shellTests.push_back(ShellTest("TestStopper", ShellTestStopper));
    shellTests.push_back(ShellTest("TestStore", ShellTestStore));
    shellTests.push_back(ShellTest("TestSupply", ShellTestSupply));
    shellTests.push_back(ShellTest("TestTrackDatabase", ShellTestTrackDatabase));
    shellTests.push_back(ShellTest("TestTrackInspector", ShellTestTrackInspector));
    shellTests.push_back(ShellTest("TestUriProviderRepeater", ShellTestUriProviderRepeater));
    shellTests.push_back(ShellTest("TestVariableDelay", ShellTestVariableDelay));
    shellTests.push_back(ShellTest("TestWaiter", ShellTestWaiter));
    shellTests.push_back(ShellTest("TestRewinder", ShellTestRewinder));
    shellTests.push_back(ShellTest("TestCodec", ShellTestCodec));
    shellTests.push_back(ShellTest("TestUdpServer", ShellTestUdpServer));
    shellTests.push_back(ShellTest("TestUpnpErrors", ShellTestUpnpErrors));

    OpenHome::Media::ExecuteTestShell(aInitParams, shellTests);
}