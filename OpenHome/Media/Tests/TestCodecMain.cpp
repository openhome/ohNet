#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Buffer.h>

#include <vector>

using namespace OpenHome;

extern void TestCodec(OpenHome::Environment& aEnv, const std::vector<Brn>& aArgs);

void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], Net::InitialisationParams* aInitParams)
{
    Net::Library* lib = new Net::Library(aInitParams);
    std::vector<Brn> args = OptionParser::ConvertArgs(aArgc, aArgv);
    TestCodec(lib->Env(), args);
    delete lib;
}
