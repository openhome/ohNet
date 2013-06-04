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

class SuiteDuplicate: public Suite
{
public:
    SuiteDuplicate();
    ~SuiteDuplicate();
    void Test();
private:
    ToneUriParser* iParser;
};

class SuiteMissing: public Suite
{
public:
    SuiteMissing();
    ~SuiteMissing();
    void Test();
private:
    ToneUriParser* iParser;
};

class SuiteSpurious: public Suite
{
public:
    SuiteSpurious();
    ~SuiteSpurious();
    void Test();
private:
    ToneUriParser* iParser;
};

class SuiteSyntaxError: public Suite
{
public:
    SuiteSyntaxError();
    ~SuiteSyntaxError();
    void Test();
private:
    ToneUriParser* iParser;
};

} // namespace Media
} // namespace OpenHome

//
// implementation of test suites
//

// SuiteLimits
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
    // bitdepth
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=0&samplerate=44100&pitch=50&channels=2&duration=360")), ToneUriParseError);
    iParser->Parse(Brn("tone://square.wav?bitdepth=8&samplerate=44100&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(8, 44100, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 44100, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=24&samplerate=44100&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(24, 44100, 50, 2, 360));
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=32&samplerate=44100&pitch=50&channels=2&duration=360")), ToneUriParseError);
    // samplerate
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=0&pitch=50&channels=2&duration=360")), ToneUriParseError);
                // case 12000: case 24000: case 48000: case 96000: case 192000:
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=7350&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 7350, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=14700&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 14700, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=29400&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 29400, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=8000&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 8000, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=16000&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 16000, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=32000&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 32000, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=11025&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 11025, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=22050&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 22050, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 44100, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=88200&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 88200, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=176400&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 176400, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=12000&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 12000, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=24000&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 24000, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=48000&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 48000, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=96000&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 96000, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=192000&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 192000, 50, 2, 360));
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=384000&pitch=50&channels=2&duration=360")), ToneUriParseError);
    // pitch
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=0&channels=2&duration=360")), ToneUriParseError);
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=1&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 44100, 1, 2, 360));
    // channels
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=0&channels=0&duration=360")), ToneUriParseError);
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=1&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 44100, 50, 1, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=2&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 44100, 50, 2, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=3&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 44100, 50, 3, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=4&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 44100, 50, 4, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=5&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 44100, 50, 5, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=6&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 44100, 50, 6, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=7&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 44100, 50, 7, 360));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=8&duration=360"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 44100, 50, 8, 360));
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=0&channels=9&duration=360")), ToneUriParseError);
    // duration
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=0&channels=2&duration=0")), ToneUriParseError);
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=2&duration=1"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 44100, 50, 2, 1));
    iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=2&duration=900"));
    TEST(iParser->Name() == Brn("square.wav") && iParser->Params() == ToneParams(16, 44100, 50, 2, 900));
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=0&channels=2&duration=901")), ToneUriParseError);
}

// SuiteDuplicate
SuiteDuplicate::SuiteDuplicate() : Suite("detection of duplicate tone parameters")
{
    iParser = new ToneUriParser();
}

SuiteDuplicate::~SuiteDuplicate()
{
    delete iParser;
}

void SuiteDuplicate::Test()
{
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=2&duration=360&bitdepth=8")), ToneUriParseError);
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=2&duration=360&samplerate=96000")), ToneUriParseError);
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=2&duration=360&pitch=440")), ToneUriParseError);
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=2&duration=360&channels=8")), ToneUriParseError);
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=2&duration=360&duration=300")), ToneUriParseError);
}

// SuiteMissing
SuiteMissing::SuiteMissing() : Suite("detection of missing tone parameters")
{
    iParser = new ToneUriParser();
}

SuiteMissing::~SuiteMissing()
{
    delete iParser;
}

void SuiteMissing::Test()
{
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?samplerate=44100&pitch=50&channels=2&duration=360")), ToneUriParseError);
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&pitch=50&channels=2&duration=360")), ToneUriParseError);
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&channels=2&duration=360")), ToneUriParseError);
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&duration=360")), ToneUriParseError);
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth=16&samplerate=44100&pitch=50&channels=2")), ToneUriParseError);
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav/")), ToneUriParseError);
}

// SuiteSpurious
SuiteSpurious::SuiteSpurious() : Suite("detection of spurious tone parameters")
{
    iParser = new ToneUriParser();
}

SuiteSpurious::~SuiteSpurious()
{
    delete iParser;
}

void SuiteSpurious::Test()
{
    // extraneous path component in URL
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav/fnord.xml?samplerate=44100&pitch=50&channels=2&duration=360")), ToneUriParseError);
    // unrecognised key-value pair
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?fnord=42&samplerate=44100&pitch=50&channels=2&duration=360")), ToneUriParseError);
}

// SuiteSyntaxError
SuiteSyntaxError::SuiteSyntaxError() : Suite("detection of syntactically defective tone URL")
{
    iParser = new ToneUriParser();
}

SuiteSyntaxError::~SuiteSyntaxError()
{
    delete iParser;
}

void SuiteSyntaxError::Test()
{
    // malformed waveform
    TEST_THROWS(iParser->Parse(Brn("tone://.wav?bitdepth=16&samplerate=44100&pitch=50&channels2&duration=360")), ToneUriParseError);
    // missing equals sign in key-value pair
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav?bitdepth16&samplerate=44100&pitch=50&channels=2&duration=360")), ToneUriParseError);
    // malformed query ('/' instead of '?')
    TEST_THROWS(iParser->Parse(Brn("tone://square.wav/bitdepth=16&samplerate=44100&pitch=50&channels2&duration=360")), ToneUriParseError);
    // missing waveform  XXX UriError
    TEST_THROWS(iParser->Parse(Brn("tone://?bitdepth=16&samplerate=44100&pitch=50&channels2&duration=360")), ToneUriParseError);
    // malformed scheme (extra colons or only single forward slash)  XXX UriError
    TEST_THROWS(iParser->Parse(Brn("tone:://square.wav?samplerate=44100&pitch=50&channels2&duration=360")), ToneUriParseError);
    TEST_THROWS(iParser->Parse(Brn("tone:/square.wav?samplerate=44100&pitch=50&channels2&duration=360")), ToneUriParseError);
}

//
// sequential execution of test suites
//

void TestToneUriParser()
{
    Runner runner("ToneUriParser tests\n");
    runner.Add(new SuiteLimits());
    runner.Add(new SuiteDuplicate());
    runner.Add(new SuiteMissing());
    runner.Add(new SuiteSpurious());
    runner.Add(new SuiteSyntaxError());
    runner.Run();
}
