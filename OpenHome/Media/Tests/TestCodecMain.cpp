#include <OpenHome/Media/Tests/TestCodec.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>

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

    Log::Print(
        "\n"
        "======================================================\n"
        "TestCodecMain overriding server name to 'localhost'\n"
        "This is a temporary hack to avoid DNS issues with OSX\n"
        "======================================================\n"
        "\n");
    args.emplace_back("-s");
    args.emplace_back("localhost");

    TestCodec(lib->Env(), CreateTestCodecPipeline, TestCodecFiles, args);
    delete lib;
}
