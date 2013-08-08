#include "TestCodec.h"
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

extern void TestCodec(OpenHome::Environment& aEnv, CreateTestCodecPipelineFunc aFunc, GetTestFiles aFileFunc, const std::vector<Brn>& aArgs);
extern TestCodecMinimalPipeline* CreateTestCodecPipeline(Environment& aEnv, IMsgProcessor& aMsgProcessor);
extern AudioFileCollection* TestCodecFiles();

void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], Net::InitialisationParams* aInitParams)
{
    Net::Library* lib = new Net::Library(aInitParams);
    std::vector<Brn> args = OptionParser::ConvertArgs(aArgc, aArgv);
    TestCodec(lib->Env(), CreateTestCodecPipeline, TestCodecFiles, args);
    delete lib;
}
