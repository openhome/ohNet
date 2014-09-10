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
    static const Brn kLocalhost("127.0.0.1");
    Net::Library* lib = new Net::Library(aInitParams);
    std::vector<Brn> args = OptionParser::ConvertArgs(aArgc, aArgv);

    // This is an override to force all instantiations to run via localhost
    // regardless of '-s' arg.
    // (Core platforms are not instantiated via this Main() method, so they
    // remain unaffected.)
    for (TUint i=0; i<args.size(); i++) {
        if (args[i] == Brn("-s")) {
            TUint hostIdx = i+1;
            ASSERT(hostIdx < args.size());
            Brn hostOld = args[hostIdx];
            args[hostIdx] = kLocalhost;
            Log::Print("OVERRIDE: TestCodec using '127.0.0.1' instead of argument '");
            Log::Print(hostOld);
            Log::Print("'\n");
            break;
        }
    }
    TestCodec(lib->Env(), CreateTestCodecPipeline, TestCodecFiles, args);
    delete lib;
}
