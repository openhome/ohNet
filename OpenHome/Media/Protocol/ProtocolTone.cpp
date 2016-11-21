#include <OpenHome/Media/Protocol/ProtocolTone.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Standard.h>

#include <vector>
#include <cstring>

#include <OpenHome/Private/Printer.h>  // XXX Log::Print()
#include <OpenHome/Media/Pipeline/Msg.h>  // XXX MsgFlush::kIdInvalid
#include <cctype>  // XXX isprint()

#undef TONE_LOG_VERBOSE

using namespace OpenHome;
using namespace OpenHome::Media;;

// static function in ProtocolFactory
Protocol* ProtocolFactory::NewTone(Environment& aEnv)
{
    return new ProtocolTone(aEnv);
}

// ProtocolTone
ProtocolTone::ProtocolTone(Environment& aEnv)
    : Protocol(aEnv)
    , iLock("PRTN")
    , iSupply(nullptr)
    , iToneGenerators()
{
    iToneGenerators.push_back(new ToneGeneratorSilence());
    iToneGenerators.push_back(new ToneGeneratorSquare());
    iToneGenerators.push_back(new ToneGeneratorSawtooth());
    iToneGenerators.push_back(new ToneGeneratorTriangle());
    iToneGenerators.push_back(new ToneGeneratorSine());
    iToneGenerators.push_back(new ToneGeneratorConstant());
#ifdef DEFINE_DEBUG
    iToneGenerators.push_back(new ToneGeneratorPattern);
#endif  // DEFINE_DEBUG
}

ProtocolTone::~ProtocolTone()
{
    while (!iToneGenerators.empty()) {
        delete iToneGenerators.back();
        iToneGenerators.pop_back();
    }
    delete iSupply;
}

void ProtocolTone::Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream)
{
    iSupply = new Supply(aMsgFactory, aDownstream);
}

TUint ProtocolTone::TryStop(TUint aStreamId)
{
    iLock.Wait();
    const TBool stop = (iStreamId == aStreamId && aStreamId != IPipelineIdProvider::kStreamIdInvalid);
    if (stop) {
        iNextFlushId = iFlushIdProvider->NextFlushId();
        iStop = true;
    }
    iLock.Signal();
    return (stop? iNextFlushId : MsgFlush::kIdInvalid);
}

// TUint ProtocolTone::TrySeek(TUint aStreamId, TUint64 aOffset) { }

ToneParams::ToneParams()
    : iBitsPerSample(0)
    , iSampleRate(0)
    , iPitch(0)
    , iNumChannels(0)
    , iDuration(0)
{
}

ToneParams::ToneParams(TUint aBitsPerSample, TUint aSampleRate, TUint aPitch, TUint aNumChannels, TUint aDuration)
    : iBitsPerSample(aBitsPerSample)
    , iSampleRate(aSampleRate)
    , iPitch(aPitch)
    , iNumChannels(aNumChannels)
    , iDuration(aDuration)
{
}

void ToneParams::Set(TUint aBitsPerSample, TUint aSampleRate, TUint aPitch, TUint aNumChannels, TUint aDuration)
{
    iBitsPerSample = aBitsPerSample;
    iSampleRate = aSampleRate;
    iPitch = aPitch;
    iNumChannels = aNumChannels;
    iDuration = aDuration;
}

ToneUriParser::ToneUriParser()
    : iParams()
    , iName(Brx::Empty())
{
} 

void ToneUriParser::Parse(const Brx& aUri)
{
    // tone://WAVEFORM.wav?bitdepth=N&samplerate=M&pitch=HZ&channels=K&duration=T
    Uri uri;

    try {
        uri.Replace(aUri);
    } catch (UriError&) {
        // translate exception so as not to expose implementation details
        THROW(ToneUriParseError);
    }

    // BufferOverflow deliberately not caught: programmer error
    iName.ReplaceThrow(uri.Host());

    if (uri.Path() != Brn("/")) {
        THROW(ToneUriParseError);
    }

    if (!uri.Query().BeginsWith(Brn("?"))) {
        THROW(ToneUriParseError);
    }

    // initialise to illegal values to detect missing ones easily below
    TUint bitsPerSample = 0;
    TUint sampleRate = 0;
    TUint pitch = 0;
    TUint numChannels = 0;
    TUint duration = 0;

    Parser parser(uri.Query());
    parser.Forward(1);  // initial "?" already checked

    while (!parser.Finished()) {
        const Brn& keyVal = parser.Next('&');

        Parser kvParser(keyVal);
        const Brn& key = kvParser.Next('=');
        const Brn& val = kvParser.NextToEnd();

        if (key == Brn("bitdepth")) {
            if (bitsPerSample != 0) {
                THROW(ToneUriParseError);  // duplicate parameter
            }
            bitsPerSample = Ascii::Uint(val);
            if ((bitsPerSample != 8) && (bitsPerSample != 16) && (bitsPerSample != 24)) {
                THROW(ToneUriParseError);
            }
        } else if (key == Brn("samplerate")) {
            if (sampleRate != 0) {
                THROW(ToneUriParseError);  // duplicate parameter
            }
            sampleRate = Ascii::Uint(val);
            switch (sampleRate) {
                // from OpenHome/Media/Msg.cpp
                case 7350: case 14700: case 29400:
                case 8000: case 16000: case 32000:
                case 11025: case 22050: case 44100: case 88200: case 176400:
                case 12000: case 24000: case 48000: case 96000: case 192000:
                    break;
                default:
                    THROW(ToneUriParseError);
            }
        } else if (key == Brn("pitch")) {  // [Hz]
            if (pitch != 0) {
                THROW(ToneUriParseError);  // duplicate parameter
            }
            pitch = Ascii::Uint(val);
            // XXX no upper limit, since not necessarily intended for human hearing
            if (0 == pitch) {
                THROW(ToneUriParseError);
            }
        } else if (key == Brn("channels")) {
            if (numChannels != 0) {
                THROW(ToneUriParseError);  // duplicate parameter
            }
            // 1 ... 8 (in practice no more than 7.1 surround sound)
            numChannels = Ascii::Uint(val);
            if (! ((0 < numChannels) && (numChannels <= 8))) {
                THROW(ToneUriParseError);
            }
        } else if (key == Brn("duration")) {  // [s]
            if (duration != 0) {
                THROW(ToneUriParseError);  // duplicate parameter
            }
            // 1 ... 900 (i.e. 15min): arbitrary limit guaranteed to avoid integer overflow in calculations
            duration = Ascii::Uint(val);
            if (! ((0 < duration) && (duration <= 900))) {
                THROW(ToneUriParseError);
            }
        } else {
            THROW(ToneUriParseError);  // unrecognised key-value pair
        }
    }

    // check for missing parameters (separately, to have unique exception line numbers)
    if (bitsPerSample == 0) {
        THROW(ToneUriParseError);
    } else if (sampleRate == 0) {
        THROW(ToneUriParseError);
    } else if (pitch == 0) {
        THROW(ToneUriParseError);
    } else if (numChannels == 0) {
        THROW(ToneUriParseError);
    } else if (duration == 0) {
        THROW(ToneUriParseError);
    }
    
    iParams = ToneParams(bitsPerSample, sampleRate, pitch, numChannels, duration);
}

const ToneParams& ToneUriParser::Params() const
{
    return iParams;
}

const Brx& ToneUriParser::Name() const
{
    return iName;
}

// tone generation
ToneGenerator::ToneGenerator(const TChar* aName)
    : iName(aName)
{
}

TBool ToneGenerator::Recognise(const Brx& aName) const
{
    return aName == iName;
}

#ifdef DEFINE_DEBUG
ToneGeneratorPattern::ToneGeneratorPattern()
    : ToneGenerator("pattern.wav")
{
}

TInt32 ToneGeneratorPattern::Generate(TUint /* aOffset */, TUint /* aMaxOffset */)
{
    static TUint cnt = 0;
    cnt = (cnt + 4) & 0xff;
    return (((cnt + 2) << 16) | ((cnt + 1) << 8) | cnt) & 0x00ffffff;
}
#endif  // DEFINE_DEBUG

ToneGeneratorSilence::ToneGeneratorSilence()
    : ToneGenerator("silence.wav")
{
}

// contract: return at most 24-bit value
TInt32 ToneGeneratorSilence::Generate(TUint aOffset, TUint aMaxOffset)
{
    ASSERT(aOffset < aMaxOffset);
    return 0;
}

ToneGeneratorSquare::ToneGeneratorSquare()
    : ToneGenerator("square.wav")
{
}

// contract: return at most 24-bit value
TInt32 ToneGeneratorSquare::Generate(TUint aOffset, TUint aMaxOffset)
{
    ASSERT(aOffset < aMaxOffset);
    // full-scale signal with 50% duty cycle
    if (aOffset < (aMaxOffset / 2)) {
        return 0x00800000;  // minimum value (24 bits; two's complement)
    } else {
        return 0x007fffff;  // maximum value (24 bits; two's complement)
    }
}

ToneGeneratorSawtooth::ToneGeneratorSawtooth()
    : ToneGenerator("sawtooth.wav")
{
}

// contract: return at most 24-bit value
TInt32 ToneGeneratorSawtooth::Generate(TUint aOffset, TUint aMaxOffset)
{
    ASSERT(aOffset < aMaxOffset);  // and truncating integer arithmetic
    TUint32 val = 0x00800000;  // minimum value (24 bits; two's complement)
    val += ((1 << 24) / aMaxOffset) * aOffset;  // y = dy/dx * x
    return (val & 0x00ffffff);
}

ToneGeneratorTriangle::ToneGeneratorTriangle()
    : ToneGenerator("triangle.wav")
{
}

// contract: return at most 24-bit value
TInt32 ToneGeneratorTriangle::Generate(TUint aOffset, TUint aMaxOffset)
{
    ASSERT(aOffset < aMaxOffset);  // and truncating integer arithmetic
    const TInt32 kGradient = (1 << 24) / (aMaxOffset / 2);  // slope twice as steep as sawtooth
    TUint32 val = 0;
    // triangle axis symmetrical around half-period,
    // so always (look up | mirror into) first half-period
    val = 0x00800000;  // minimum value (24 bits; two's complement)
    if (aOffset >= aMaxOffset / 2) {
        // e.g. aMaxOffset=6:      2 <- 3
        //                       1   <-   4
        //                     0     <-     5
        aOffset = aOffset - 1 - 2 * (aOffset % (aMaxOffset / 2));
    }
    val += kGradient * aOffset;
    return (val & 0x00ffffff);
}

ToneGeneratorSine::ToneGeneratorSine()
    : ToneGenerator("sine.wav")
{
}

// contract: return at most 24-bit value
TInt32 ToneGeneratorSine::Generate(TUint aOffset, TUint aMaxOffset)
{
    ASSERT(aOffset < aMaxOffset);
    const TInt32 kWave[] = {
               0,    52706,   105411,   158112,   210806,   263492,   316168,   368831, 
          421479,   474111,   526725,   579317,   631887,   684431,   736949,   789437, 
          841895,   894319,   946707,   999059,  1051371,  1103641,  1155868,  1208050, 
         1260183,  1312267,  1364299,  1416277,  1468199,  1520064,  1571868,  1623610, 
         1675288,  1726900,  1778444,  1829918,  1881319,  1932646,  1983897,  2035069, 
         2086161,  2137171,  2188097,  2238936,  2289686,  2340347,  2390914,  2441388, 
         2491765,  2542044,  2592222,  2642298,  2692270,  2742135,  2791892,  2841539, 
         2891074,  2940495,  2989799,  3038986,  3088052,  3136997,  3185817,  3234512, 
         3283080,  3331517,  3379824,  3427996,  3476034,  3523934,  3571695,  3619315, 
         3666792,  3714125,  3761311,  3808348,  3855235,  3901970,  3948550,  3994975, 
         4041242,  4087350,  4133296,  4179079,  4224697,  4270148,  4315431,  4360543, 
         4405484,  4450250,  4494840,  4539254,  4583487,  4627540,  4671411,  4715097, 
         4758596,  4801908,  4845031,  4887962,  4930700,  4973243,  5015590,  5057739, 
         5099688,  5141437,  5182982,  5224322,  5265456,  5306383,  5347099,  5387605, 
         5427898,  5467977,  5507840,  5547486,  5586912,  5626118,  5665102,  5703862, 
         5742397,  5780705,  5818785,  5856636,  5894255,  5931641,  5968793,  6005710, 
         6042390,  6078831,  6115032,  6150991,  6186708,  6222180,  6257407,  6292387, 
         6327119,  6361600,  6395831,  6429809,  6463533,  6497002,  6530215,  6563169, 
         6595865,  6628300,  6660474,  6692384,  6724031,  6755412,  6786526,  6817372, 
         6847949,  6878256,  6908292,  6938054,  6967543,  6996757,  7025694,  7054354, 
         7082735,  7110837,  7138659,  7166198,  7193454,  7220427,  7247114,  7273516, 
         7299630,  7325456,  7350993,  7376239,  7401195,  7425858,  7450228,  7474304, 
         7498085,  7521570,  7544758,  7567648,  7590239,  7612531,  7634522,  7656211, 
         7677599,  7698683,  7719464,  7739939,  7760110,  7779973,  7799530,  7818779, 
         7837719,  7856349,  7874670,  7892679,  7910377,  7927763,  7944836,  7961595, 
         7978040,  7994170,  8009984,  8025482,  8040663,  8055527,  8070073,  8084300, 
         8098208,  8111796,  8125064,  8138011,  8150637,  8162941,  8174923,  8186583, 
         8197919,  8208931,  8219619,  8229983,  8240022,  8249736,  8259124,  8268186, 
         8276921,  8285330,  8293411,  8301166,  8308592,  8315691,  8322461,  8328902, 
         8335015,  8340799,  8346254,  8351379,  8356174,  8360639,  8364775,  8368580, 
         8372054,  8375199,  8378012,  8380495,  8382647,  8384468,  8385958,  8387117, 
         8387945,  8388442,  8388608,  8388442,  8387945,  8387117,  8385958,  8384468, 
         8382647,  8380495,  8378012,  8375199,  8372054,  8368580,  8364775,  8360639, 
         8356174,  8351379,  8346254,  8340799,  8335015,  8328902,  8322461,  8315691, 
         8308592,  8301166,  8293411,  8285330,  8276921,  8268186,  8259124,  8249736, 
         8240022,  8229983,  8219619,  8208931,  8197919,  8186583,  8174923,  8162941, 
         8150637,  8138011,  8125064,  8111796,  8098208,  8084300,  8070073,  8055527, 
         8040663,  8025482,  8009984,  7994170,  7978040,  7961595,  7944836,  7927763, 
         7910377,  7892679,  7874670,  7856349,  7837719,  7818779,  7799530,  7779973, 
         7760110,  7739939,  7719464,  7698683,  7677599,  7656211,  7634522,  7612531, 
         7590239,  7567648,  7544758,  7521570,  7498085,  7474304,  7450228,  7425858, 
         7401195,  7376239,  7350993,  7325456,  7299630,  7273516,  7247114,  7220427, 
         7193454,  7166198,  7138659,  7110837,  7082735,  7054354,  7025694,  6996757, 
         6967543,  6938054,  6908292,  6878256,  6847949,  6817372,  6786526,  6755412, 
         6724031,  6692384,  6660474,  6628300,  6595865,  6563169,  6530215,  6497002, 
         6463533,  6429809,  6395831,  6361600,  6327119,  6292387,  6257407,  6222180, 
         6186708,  6150991,  6115032,  6078831,  6042390,  6005710,  5968793,  5931641, 
         5894255,  5856636,  5818785,  5780705,  5742397,  5703862,  5665102,  5626118, 
         5586912,  5547486,  5507840,  5467977,  5427898,  5387605,  5347099,  5306383, 
         5265456,  5224322,  5182982,  5141437,  5099688,  5057739,  5015590,  4973243, 
         4930700,  4887962,  4845031,  4801908,  4758596,  4715097,  4671411,  4627540, 
         4583487,  4539254,  4494840,  4450250,  4405484,  4360543,  4315431,  4270148, 
         4224697,  4179079,  4133296,  4087350,  4041242,  3994975,  3948550,  3901970, 
         3855235,  3808348,  3761311,  3714125,  3666792,  3619315,  3571695,  3523934, 
         3476034,  3427996,  3379824,  3331517,  3283080,  3234512,  3185817,  3136997, 
         3088052,  3038986,  2989799,  2940495,  2891074,  2841539,  2791892,  2742135, 
         2692270,  2642298,  2592222,  2542044,  2491765,  2441388,  2390914,  2340347, 
         2289686,  2238936,  2188097,  2137171,  2086161,  2035069,  1983897,  1932646, 
         1881319,  1829918,  1778444,  1726900,  1675288,  1623610,  1571868,  1520064, 
         1468199,  1416277,  1364299,  1312267,  1260183,  1208050,  1155868,  1103641, 
         1051371,   999059,   946707,   894319,   841895,   789437,   736949,   684431, 
          631887,   579317,   526725,   474111,   421479,   368831,   316168,   263492, 
          210806,   158112,   105411,    52706,        0,   -52706,  -105411,  -158112, 
         -210806,  -263492,  -316168,  -368831,  -421479,  -474111,  -526725,  -579317, 
         -631887,  -684431,  -736949,  -789437,  -841895,  -894319,  -946707,  -999059, 
        -1051371, -1103641, -1155868, -1208050, -1260183, -1312267, -1364299, -1416277, 
        -1468199, -1520064, -1571868, -1623610, -1675288, -1726900, -1778444, -1829918, 
        -1881319, -1932646, -1983897, -2035069, -2086161, -2137171, -2188097, -2238936, 
        -2289686, -2340347, -2390914, -2441388, -2491765, -2542044, -2592222, -2642298, 
        -2692270, -2742135, -2791892, -2841539, -2891074, -2940495, -2989799, -3038986, 
        -3088052, -3136997, -3185817, -3234512, -3283080, -3331517, -3379824, -3427996, 
        -3476034, -3523934, -3571695, -3619315, -3666792, -3714125, -3761311, -3808348, 
        -3855235, -3901970, -3948550, -3994975, -4041242, -4087350, -4133296, -4179079, 
        -4224697, -4270148, -4315431, -4360543, -4405484, -4450250, -4494840, -4539254, 
        -4583487, -4627540, -4671411, -4715097, -4758596, -4801908, -4845031, -4887962, 
        -4930700, -4973243, -5015590, -5057739, -5099688, -5141437, -5182982, -5224322, 
        -5265456, -5306383, -5347099, -5387605, -5427898, -5467977, -5507840, -5547486, 
        -5586912, -5626118, -5665102, -5703862, -5742397, -5780705, -5818785, -5856636, 
        -5894255, -5931641, -5968793, -6005710, -6042390, -6078831, -6115032, -6150991, 
        -6186708, -6222180, -6257407, -6292387, -6327119, -6361600, -6395831, -6429809, 
        -6463533, -6497002, -6530215, -6563169, -6595865, -6628300, -6660474, -6692384, 
        -6724031, -6755412, -6786526, -6817372, -6847949, -6878256, -6908292, -6938054, 
        -6967543, -6996757, -7025694, -7054354, -7082735, -7110837, -7138659, -7166198, 
        -7193454, -7220427, -7247114, -7273516, -7299630, -7325456, -7350993, -7376239, 
        -7401195, -7425858, -7450228, -7474304, -7498085, -7521570, -7544758, -7567648, 
        -7590239, -7612531, -7634522, -7656211, -7677599, -7698683, -7719464, -7739939, 
        -7760110, -7779973, -7799530, -7818779, -7837719, -7856349, -7874670, -7892679, 
        -7910377, -7927763, -7944836, -7961595, -7978040, -7994170, -8009984, -8025482, 
        -8040663, -8055527, -8070073, -8084300, -8098208, -8111796, -8125064, -8138011, 
        -8150637, -8162941, -8174923, -8186583, -8197919, -8208931, -8219619, -8229983, 
        -8240022, -8249736, -8259124, -8268186, -8276921, -8285330, -8293411, -8301166, 
        -8308592, -8315691, -8322461, -8328902, -8335015, -8340799, -8346254, -8351379, 
        -8356174, -8360639, -8364775, -8368580, -8372054, -8375199, -8378012, -8380495, 
        -8382647, -8384468, -8385958, -8387117, -8387945, -8388442, -8388608, -8388442, 
        -8387945, -8387117, -8385958, -8384468, -8382647, -8380495, -8378012, -8375199, 
        -8372054, -8368580, -8364775, -8360639, -8356174, -8351379, -8346254, -8340799, 
        -8335015, -8328902, -8322461, -8315691, -8308592, -8301166, -8293411, -8285330, 
        -8276921, -8268186, -8259124, -8249736, -8240022, -8229983, -8219619, -8208931, 
        -8197919, -8186583, -8174923, -8162941, -8150637, -8138011, -8125064, -8111796, 
        -8098208, -8084300, -8070073, -8055527, -8040663, -8025482, -8009984, -7994170, 
        -7978040, -7961595, -7944836, -7927763, -7910377, -7892679, -7874670, -7856349, 
        -7837719, -7818779, -7799530, -7779973, -7760110, -7739939, -7719464, -7698683, 
        -7677599, -7656211, -7634522, -7612531, -7590239, -7567648, -7544758, -7521570, 
        -7498085, -7474304, -7450228, -7425858, -7401195, -7376239, -7350993, -7325456, 
        -7299630, -7273516, -7247114, -7220427, -7193454, -7166198, -7138659, -7110837, 
        -7082735, -7054354, -7025694, -6996757, -6967543, -6938054, -6908292, -6878256, 
        -6847949, -6817372, -6786526, -6755412, -6724031, -6692384, -6660474, -6628300, 
        -6595865, -6563169, -6530215, -6497002, -6463533, -6429809, -6395831, -6361600, 
        -6327119, -6292387, -6257407, -6222180, -6186708, -6150991, -6115032, -6078831, 
        -6042390, -6005710, -5968793, -5931641, -5894255, -5856636, -5818785, -5780705, 
        -5742397, -5703862, -5665102, -5626118, -5586912, -5547486, -5507840, -5467977, 
        -5427898, -5387605, -5347099, -5306383, -5265456, -5224322, -5182982, -5141437, 
        -5099688, -5057739, -5015590, -4973243, -4930700, -4887962, -4845031, -4801908, 
        -4758596, -4715097, -4671411, -4627540, -4583487, -4539254, -4494840, -4450250, 
        -4405484, -4360543, -4315431, -4270148, -4224697, -4179079, -4133296, -4087350, 
        -4041242, -3994975, -3948550, -3901970, -3855235, -3808348, -3761311, -3714125, 
        -3666792, -3619315, -3571695, -3523934, -3476034, -3427996, -3379824, -3331517, 
        -3283080, -3234512, -3185817, -3136997, -3088052, -3038986, -2989799, -2940495, 
        -2891074, -2841539, -2791892, -2742135, -2692270, -2642298, -2592222, -2542044, 
        -2491765, -2441388, -2390914, -2340347, -2289686, -2238936, -2188097, -2137171, 
        -2086161, -2035069, -1983897, -1932646, -1881319, -1829918, -1778444, -1726900, 
        -1675288, -1623610, -1571868, -1520064, -1468199, -1416277, -1364299, -1312267, 
        -1260183, -1208050, -1155868, -1103641, -1051371,  -999059,  -946707,  -894319, 
         -841895,  -789437,  -736949,  -684431,  -631887,  -579317,  -526725,  -474111, 
         -421479,  -368831,  -316168,  -263492,  -210806,  -158112,  -105411,   -52706, 
    };
    // idx / numValues "proportional to" aOffset / kMaxOffset
    TUint idx = (aOffset * (sizeof(kWave) / sizeof(TInt32))) / aMaxOffset;
    return kWave[idx];
}


// ToneGeneratorConstant

ToneGeneratorConstant::ToneGeneratorConstant()
    : ToneGenerator("constant.wav")
{
}

TBool ToneGeneratorConstant::Recognise(const Brx& aName) const
{
    if (!aName.BeginsWith(Brn("constant-"))) {
        return false;
    }
    Parser parser(aName);
    parser.Next('-');
    Brn buf = parser.Next('.');
    if (buf.Bytes() == 0) {
        return false;
    }
    try {
        iValue = Ascii::Int(buf);
    }
    catch (AsciiError&) {
        return false;
    }
    return true;
}

TInt32 ToneGeneratorConstant::Generate(TUint /*aOffset*/, TUint /*aMaxOffset*/)
{
    return iValue<<16;
}

void ProtocolTone::Interrupt(TBool aInterrupt)
{
    iLock.Wait();
    if (aInterrupt) {
        iStop = aInterrupt;
    }
    iLock.Signal();
}

ProtocolStreamResult ProtocolTone::Stream(const Brx& aUri)
{
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iStop = false;
    iNextFlushId = MsgFlush::kIdInvalid;
    iAudioBuf.SetBytes(0);

    if (!aUri.BeginsWith(Brn("tone://"))) {
        // quietly decline offer to handle other URL schemes; leave it to other protocol modules
        return EProtocolErrorNotSupported;
    }

    ToneUriParser uriParser;
    try {
        uriParser.Parse(aUri);
    } catch (ToneUriParseError&) {
        return EProtocolErrorNotSupported;
    } catch (UriError&) {
        return EProtocolErrorNotSupported;
    }

    // dynamically select waveform generator
    ToneGenerator *generator = nullptr;
    for (TUint i = 0; i < iToneGenerators.size(); ++i) {
        if (iToneGenerators[i]->Recognise(uriParser.Name())) {
            generator = iToneGenerators[i];
            break;
        }
    }
    if (nullptr == generator) {
        return EProtocolStreamErrorUnrecoverable;
    }

    const ToneParams& params = uriParser.Params();

#ifdef TONE_LOG_VERBOSE
    Log::Print("@@  bitdepth =   %6u\n", params.BitsPerSample());
    Log::Print("@@  samplerate = %6u\n", params.SampleRate());
    Log::Print("@@  pitch =      %6u\n", params.Pitch());
    Log::Print("@@  channels =   %6u\n", params.NumChannels());
    Log::Print("@@  duration =   %6u\n", params.DurationSeconds());
    Log::Print("\n");
#endif  // TONE_LOG_VERBOSE

    //
    // output WAV header:  https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
    //

    const TUint nSamples = params.SampleRate() * params.DurationSeconds();
    // precondition enforced above: bitsPerSample % 8 == 0

    // chunkId: "RIFF" = 0x52494646 (BE)
    // chunkSize: see below
    // format: "WAVE" = 0x57415645 (BE)
    // subchunkOneId: "fmt " = 0x664d7420 (BE)
    const TUint subchunkOneSize = 16;  // for PCM data, no extra parameters in "fmt " subchunnk
    const TUint audioFormat = 1;  // PCM (linear quantisation, no compression)
    // TUint numChannels: see above (parsing)
    // TUint sampleRate: see above (parsing)
    const TUint byteRate = params.SampleRate() * params.NumChannels() * (params.BitsPerSample() / 8);
    const TUint blockAlign = params.NumChannels() * (params.BitsPerSample() / 8);
    // TUint bitsPerSample: see above (parsing)
    // subchunkTwoId: "data" = 0x64617461 (BE)
    const TUint subchunkTwoSize = nSamples * params.NumChannels() * (params.BitsPerSample() / 8);

    // no integer overflow in worst case: 4 + 8 + 16 + 8 + (192000 * 900 * 8 * 3) < 2^32-1
    const TUint chunkSize = 4 + (8 + subchunkOneSize) + (8 + subchunkTwoSize);

    #define LE2(x) iAudioBuf.Append(static_cast<TByte>((x) & 0x00ff)); iAudioBuf.Append(static_cast<TByte>(((x) & 0xff00) >> 8));
    #define LE4(x) iAudioBuf.Append(static_cast<TByte>((x) & 0x000000ff)); iAudioBuf.Append(static_cast<TByte>(((x) & 0x0000ff00) >> 8)); iAudioBuf.Append(static_cast<TByte>(((x) & 0x00ff0000) >> 16)); iAudioBuf.Append(static_cast<TByte>(((x) & 0xff000000) >> 24));
    iAudioBuf.SetBytes(0);  // reset audio buffer
    iAudioBuf.Append("RIFF");  // != RIFX, i.e. all integer values in little endian format
    LE4(chunkSize)
    iAudioBuf.Append("WAVE");
    iAudioBuf.Append("fmt ");  // trailing space significant
    LE4(subchunkOneSize)
    LE2(audioFormat)
    LE2(params.NumChannels())
    LE4(params.SampleRate())
    LE4(byteRate)
    LE2(blockAlign)
    LE2(params.BitsPerSample())
    iAudioBuf.Append("data");
    LE4(subchunkTwoSize)

#ifdef TONE_LOG_VERBOSE
    HexDump(iAudioBuf.Ptr(), iAudioBuf.Bytes());
#endif  // TONE_LOG_VERBOSE

    //
    // output audio data (data members inherited from Protocol)
    // N.B. assuming only periodic waveforms and identical output on all channels
    //

    // chosen max number of samples that can be Generate()d for any waveform;
    // esp. for LUT-based implementation: trade-off between (on-device) space and audio resolution;
    // pitch more likely to be N x 10[Hz] rather than N x 2^r[Hz]
    // XXX 64000 = 2^6 x 10^3, i.e. plenty of factors from binary and decimal world;
    //     also fits into TUint16;  sizeof(int) x 64000 < 256kB
    const TUint kMaxVirtualSamplesPerPeriod = 64000;  // Nyquist limit: assuming pitch <= 32kHz (beyond audible range)

    // 64000 < 2^16 and (worst case) 32000 < 2^15, so multiplication cannot overflow unsigned 32-bit value
    const TUint virtualSamplesStep = (kMaxVirtualSamplesPerPeriod * params.Pitch()) / params.SampleRate();
    // need integer arithmetic, but cannot ignore potentially 5% error (e.g. 44100Hz sample rate with 13Hz pitch)
    const TInt virtualSamplesRemainder = (kMaxVirtualSamplesPerPeriod * params.Pitch()) % params.SampleRate();

    iLock.Wait();
    iStreamId = iIdProvider->NextStreamId();
    iLock.Signal();
    iSupply->OutputStream(aUri, iAudioBuf.Bytes() + nSamples * blockAlign, 0, /*aSeekable*/ false, /*aLive*/ false, Multiroom::Allowed, /*IStreamHandler*/ *this, iStreamId);

    TUint x = 0;
    TInt accRemain = 0;  // accumulation of error may tmp'ly be negative
    for (TUint i = 0; i < nSamples; ++i) {
        iLock.Wait();
        if (iStop) {
            iSupply->OutputFlush(iNextFlushId);
            iStop = false;
            iLock.Signal();
            break;
        }
        iLock.Signal();
        // ensure sufficient capacity for another (multi-channel) audio sample
        if (iAudioBuf.Bytes() + blockAlign > iAudioBuf.MaxBytes()) {
#ifdef TONE_LOG_VERBOSE
            Log::Print("flushing audio buffer: %u[B]\n", iAudioBuf.Bytes());
            HexDump(iAudioBuf.Ptr(), iAudioBuf.Bytes());
#endif  // TONE_LOG_VERBOSE
            iSupply->OutputData(iAudioBuf);
            iAudioBuf.SetBytes(0);  // reset audio buffer
        }

        // contract: generator to produce at most 24-bit values
        TInt32 audioSample = generator->Generate(x, kMaxVirtualSamplesPerPeriod);
        switch (params.BitsPerSample()) {
            case 8:
                audioSample >>= 16;
                for (TUint ch = 0; ch < params.NumChannels(); ++ch) {
                    iAudioBuf.Append(static_cast<TByte>(audioSample));
                }
                break;
            case 16:
                audioSample >>= 8;  // correct sign extension guaranteed
                for (TUint ch = 0; ch < params.NumChannels(); ++ch) {
                    iAudioBuf.Append(static_cast<TByte>((audioSample & 0x00ff)));  // LE
                    iAudioBuf.Append(static_cast<TByte>((audioSample & 0xff00) >> 8));
                }
                break;
            case 24:
                for (TUint ch = 0; ch < params.NumChannels(); ++ch) {
                    iAudioBuf.Append(static_cast<TByte>((audioSample & 0x0000ff)));  // LE
                    iAudioBuf.Append(static_cast<TByte>((audioSample & 0x00ff00) >> 8));
                    iAudioBuf.Append(static_cast<TByte>((audioSample & 0xff0000) >> 16));
                }
                break;
            default:
                ASSERTS();
        }
        x += virtualSamplesStep;
        accRemain += virtualSamplesRemainder;
        // same signedness for comparison: sample rate always representable w/o loss in signed 32-bit int
        if (accRemain >= static_cast<TInt>(params.SampleRate())) {
            ++x;
            accRemain -= params.SampleRate();
        }
        x = x % kMaxVirtualSamplesPerPeriod;
    }


    iLock.Wait();
    if (iStop) {
        iSupply->OutputFlush(iNextFlushId);
        iStop = false;
    }
    else {
        // flush final audio data (if any) from (partially) filled audio buffer
#ifdef TONE_LOG_VERBOSE
        Log::Print("flushing final audio buffer: %u[B]\n", iAudioBuf.Bytes());
        HexDump(iAudioBuf.Ptr(), iAudioBuf.Bytes());
#endif  // TONE_LOG_VERBOSE
        iSupply->OutputData(iAudioBuf);
    }
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iLock.Signal();

    return EProtocolStreamSuccess;
}

ProtocolGetResult ProtocolTone::Get(IWriter& /*aWriter*/, const Brx& /*aUri*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return EProtocolGetErrorNotSupported;
}

#ifdef DEFINE_DEBUG
void ProtocolTone::HexDump(const TByte *aBase, TUint aSize) const
{
    const TByte *p = aBase;
    const int kBytesPerLine = 16;  // 16 x 3 chars + 2 chars + 16 chars < 80
    do {
        int maxBytes = kBytesPerLine;
        if ((p + maxBytes) > (aBase + aSize)) {
            maxBytes = aSize % kBytesPerLine;
        }

        for (int i = 0; i < maxBytes; ++i) {
            Log::Print("%02x ", *(p + i));
        }
        for (int i = 0; i < (kBytesPerLine - maxBytes); ++i) {
            Log::Print("   ");  // optical filler for last line
        }
        Log::Print(" ");
        for (int i = 0; i < maxBytes; ++i) {
            Log::Print("%c", isprint(*(p + i)) ? *(p + i) : '.');
        }
        Log::Print("\n");

        p += kBytesPerLine;
    } while (p < (aBase + aSize));
}
#endif  // DEFINE_DEBUG
