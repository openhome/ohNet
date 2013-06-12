#include <OpenHome/Private/TestFramework.h>

#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/ProtocolTone.h>
#include <OpenHome/Media/Supply.h>
#include <OpenHome/Media/EncodedAudioReservoir.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Buffer.h>

#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/Globals.h>  // dummy Environment

#include "AllocatorInfoLogger.h"
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

class SuiteDuplicate : public Suite
{
public:
    SuiteDuplicate();
    ~SuiteDuplicate();
    void Test();
private:
    ToneUriParser* iParser;
};

class SuiteMissing : public Suite
{
public:
    SuiteMissing();
    ~SuiteMissing();
    void Test();
private:
    ToneUriParser* iParser;
};

class SuiteSpurious : public Suite
{
public:
    SuiteSpurious();
    ~SuiteSpurious();
    void Test();
private:
    ToneUriParser* iParser;
};

class SuiteSyntaxError : public Suite
{
public:
    SuiteSyntaxError();
    ~SuiteSyntaxError();
    void Test();
private:
    ToneUriParser* iParser;
};

enum EToneMsgType
{
    eMsgTrack,
    eMsgEncodedStream,
    eMsgDecodedStream,
    eMsgAudioPcm,
    eMsgQuit,
    eMsgNone,
};

class SuiteGeneratorSilence : public Suite,
     private IPipelineIdProvider, private IFlushIdProvider, private IPipelineElementDownstream, private IMsgProcessor
{
public:
    SuiteGeneratorSilence();
    ~SuiteGeneratorSilence();
    void Test();

private:  // from IPipelineIdProvider
    TUint NextTrackId();
    TUint NextStreamId();
    EStreamPlay OkToPlay(TUint, TUint);

private:  // from IFlushIdProvider
    TUint NextFlushId();

private:  // from IPipelineElementDownstream
    void Push(Msg* aMsg);

private:  // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);

private:
    // as per Pipeline.h
    static const TUint kMsgCountEncodedAudio    = 512;
    static const TUint kMsgCountAudioEncoded    = 768;
    static const TUint kMsgCountDecodedAudio    = 512;
    static const TUint kMsgCountAudioPcm        = 768;
    static const TUint kMsgCountSilence         = 512;
    static const TUint kMsgCountPlayablePcm     = 1024;
    static const TUint kMsgCountPlayableSilence = 1024;
    static const TUint kMsgCountEncodedStream   = 20;
    static const TUint kMsgCountTrack           = 20;
    static const TUint kMsgCountDecodedStream   = 20;
    static const TUint kMsgCountMetaText        = 20;
    static const TUint kMsgCountHalt            = 20;
    static const TUint kMsgCountFlush           = 1;
    static const TUint kMsgCountQuit            = 1;
    static const TUint kEncodedReservoirSizeBytes = 20 * 1024;

    TrackFactory* iTrackFactory;
    ProtocolManager* iProtocolManager;
    AllocatorInfoLogger* iAllocatorInfoLogger;
    MsgFactory* iMsgFactory;
    EncodedAudioReservoir* iEncodedAudioReservoir;
    Supply* iSupply;
    Codec::Container* iContainer;
    Codec::CodecController* iCodecController;

    TUint iNextFlushId;
    TUint iNextTrackId;
    TUint iNextStreamId;
    bool iQuit;
    Semaphore iSemaphore;

    ToneParams iExpectedToneParams;
    EToneMsgType iExpectedMsgType;
};

} // namespace Media
} // namespace OpenHome

//
// implementation of test suites
//

// SuiteLimits
SuiteLimits::SuiteLimits()
    : Suite("enforcement of tone parameter limits")
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
SuiteDuplicate::SuiteDuplicate()
    : Suite("detection of duplicate tone parameters")
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
SuiteMissing::SuiteMissing()
    : Suite("detection of missing tone parameters")
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
SuiteSpurious::SuiteSpurious()
    : Suite("detection of spurious tone parameters")
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
SuiteSyntaxError::SuiteSyntaxError()
    : Suite("detection of syntactically defective tone URL")
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

SuiteGeneratorSilence::SuiteGeneratorSilence()
    : Suite("tone generator: silence")
    , iNextFlushId(1)
    , iNextTrackId(1)
    , iNextStreamId(1)
    , iQuit(false)
    , iSemaphore("TONE", 0)
{
    iAllocatorInfoLogger = new AllocatorInfoLogger();
    iMsgFactory = new MsgFactory(*iAllocatorInfoLogger,
                             kMsgCountEncodedAudio, kMsgCountAudioEncoded,
                             kMsgCountDecodedAudio, kMsgCountAudioPcm, kMsgCountSilence,
                             kMsgCountPlayablePcm, kMsgCountPlayableSilence, kMsgCountEncodedStream,
                             kMsgCountTrack, kMsgCountDecodedStream, kMsgCountMetaText,
                             kMsgCountHalt, kMsgCountFlush, kMsgCountQuit);
    iEncodedAudioReservoir = new EncodedAudioReservoir(kEncodedReservoirSizeBytes);
    iSupply = new Supply(*iMsgFactory, *iEncodedAudioReservoir);
    iContainer = new Codec::Container(*iMsgFactory, *iEncodedAudioReservoir);
    iCodecController = new Codec::CodecController(*iMsgFactory, *iContainer, /*IPipelineElementDownstream*/ *this);
    iCodecController->AddCodec(Codec::CodecFactory::NewWav());
    iCodecController->Start();

    iProtocolManager = new ProtocolManager(*iSupply, /*IPipelineIdProvider*/ *this, /*IFlushIdProvider*/ *this);
    iProtocolManager->Add(ProtocolFactory::NewTone(*gEnv));  // (dummy) environment not really needed

    // only single test track (tone:// URL) in existence at any given time
    iTrackFactory = new TrackFactory(*iAllocatorInfoLogger, 1);
}

SuiteGeneratorSilence::~SuiteGeneratorSilence()
{
    delete iCodecController;
    delete iContainer;
    delete iEncodedAudioReservoir;
    delete iSupply;
    delete iProtocolManager;
    delete iTrackFactory;
    delete iMsgFactory;
    delete iAllocatorInfoLogger;
}

TUint SuiteGeneratorSilence::NextFlushId()
{
    return iNextFlushId++;
}

TUint SuiteGeneratorSilence::NextTrackId()
{
    return iNextTrackId++;
}

TUint SuiteGeneratorSilence::NextStreamId()
{
    return iNextStreamId++;
}

EStreamPlay SuiteGeneratorSilence::OkToPlay(TUint, TUint)
{
    ASSERTS();
    return ePlayNo;
}

void SuiteGeneratorSilence::Push(Msg* aMsg)
{
    Msg* origMsg = aMsg->Process(/*IMsgProcessor*/ *this);
    if (NULL != origMsg) {
        ASSERT(origMsg == aMsg);
        // only if callback has not already taken care of ref counting / memory management
        origMsg->RemoveRef();
    }
    if  (iQuit) {
        // callback for MsgQuit is done (as all others return original msg)
        // this IMsgProcessor (etc.) object will never be needed again,
        // so destruction may proceed in main (test) thread
        iSemaphore.Signal();
    }
}

// callbacks from aMsg->Process; actually check output (TEST)
Msg* SuiteGeneratorSilence::ProcessMsg(MsgAudioEncoded* aMsg)
{
    ASSERTS();
    return aMsg;  // unreachable, but required to acquiesce compiler
}

Msg* SuiteGeneratorSilence::ProcessMsg(MsgAudioPcm* aMsg)
{
    // TODO: capture and analyse actual PCM audio data
    TEST(eMsgAudioPcm == iExpectedMsgType);
    iExpectedMsgType = eMsgAudioPcm;  // usually more to follow, but MsgQuit also acceptable
    return aMsg;
}

Msg* SuiteGeneratorSilence::ProcessMsg(MsgSilence* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* SuiteGeneratorSilence::ProcessMsg(MsgPlayable* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* SuiteGeneratorSilence::ProcessMsg(MsgDecodedStream* aMsg)
{
    TEST(eMsgDecodedStream == iExpectedMsgType);
    iExpectedMsgType = eMsgAudioPcm;
    return aMsg;
}

Msg* SuiteGeneratorSilence::ProcessMsg(MsgTrack* aMsg)
{
    TEST(eMsgTrack == iExpectedMsgType);
    iExpectedMsgType = eMsgEncodedStream;
    return aMsg;
}

Msg* SuiteGeneratorSilence::ProcessMsg(MsgEncodedStream* aMsg)
{
    TEST(eMsgEncodedStream== iExpectedMsgType);
    iExpectedMsgType = eMsgDecodedStream;
    return aMsg;
}

Msg* SuiteGeneratorSilence::ProcessMsg(MsgMetaText* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* SuiteGeneratorSilence::ProcessMsg(MsgHalt* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* SuiteGeneratorSilence::ProcessMsg(MsgFlush* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* SuiteGeneratorSilence::ProcessMsg(MsgQuit* aMsg)
{
    TEST(eMsgAudioPcm == iExpectedMsgType);
    iExpectedMsgType = eMsgNone;  // final msg: none more expected
    iQuit = true;
    return aMsg;
}

void SuiteGeneratorSilence::Test()
{
    iExpectedMsgType = eMsgTrack;
    iExpectedToneParams.Set(16, 44100, 50, 2, 1);
    Track& trk = *iTrackFactory->CreateTrack(Brn("tone://silence.wav?bitdepth=16&samplerate=44100&pitch=50&channels=2&duration=1"), Brx::Empty(), NULL);
    iProtocolManager->DoStream(trk, Brx::Empty());
    trk.RemoveRef();
    iSupply->OutputQuit();  // ensure no audio remains in pipeline
    iSemaphore.Wait();
}

//
// sequential execution of test suites
//

void TestToneGenerator()
{
    Runner runner("ToneGenerator tests\n");
    runner.Add(new SuiteLimits());
    runner.Add(new SuiteDuplicate());
    runner.Add(new SuiteMissing());
    runner.Add(new SuiteSpurious());
    runner.Add(new SuiteSyntaxError());
    runner.Add(new SuiteGeneratorSilence());
    runner.Run();
}
