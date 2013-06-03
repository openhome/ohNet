#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Protocol/ProtocolTone.h>
#include <OpenHome/Buffer.h>

#include "SuiteUnitTest.h"

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

//
// declaration of test suites
//

namespace OpenHome {
namespace Media {

class SuiteLimits : public Suite
{
public:
    SuiteLimits();
    ~SuiteLimits();
    void Test();
private:
    ToneUriParser* iParser;
};

} // namespace Media
} // namespace OpenHome

//
// implementation of test suites
//

SuiteLimits::SuiteLimits() : Suite("enforcement of tone parameter limits")
{
    iParser = new ToneUriParser();
}

SuiteLimits::~SuiteLimits()
{
    delete iParser;
}

void SuiteLimits::Test()
{
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav"));
    TEST(iParser->Params() == ToneParams(16, 44100, 50, 2, 360));
}

//
// sequential execution of test suites
//

void TestToneUriParser()
{
    Runner runner("ToneUriParser tests\n");
    runner.Add(new SuiteLimits());
    // TODO ...
    runner.Run();
}
