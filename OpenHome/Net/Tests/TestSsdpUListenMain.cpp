#include <OpenHome/Types.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;

extern void TestSsdpUListen(Environment& aStack, const std::vector<Brn>& aArgs);

void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], Net::InitialisationParams* aInitParams)
{
    std::vector<Brn> args = OptionParser::ConvertArgs(aArgc, aArgv);

    OptionParser parser;
    OptionUint mx("-mx", "--mx", 1, "[1..5] number of second to spread response over");
    parser.AddOption(&mx);
    if (!parser.Parse(args, true) || parser.HelpDisplayed()) {
        return;
    }

    if (mx.Value() != 0) {
        aInitParams->SetMsearchTime(mx.Value());
    }
    Library* lib = new Net::Library(aInitParams);

    TestSsdpUListen(lib->Env(), args);

    delete lib;
}
