#include "TestCodec.h"
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Buffer.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Media::Codec;

extern void TestCodec(OpenHome::Environment& aEnv
                      , std::vector<AudioFileDescriptor> aMinFiles
                      , std::vector<AudioFileDescriptor> aExtraFiles
                      , std::vector<AudioFileDescriptor> aInvalidFiles
                      , std::vector<AudioFileDescriptor> aStreamOnlyFiles
                      ,const std::vector<Brn>& aArgs
                      );

void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], Net::InitialisationParams* aInitParams)
{
    // test file vectors
    std::vector<AudioFileDescriptor> minFiles;
    std::vector<AudioFileDescriptor> extraFiles;
    std::vector<AudioFileDescriptor> invalidFiles;
    std::vector<AudioFileDescriptor> streamOnlyFiles;

    // core testing files
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k.wav"), 44100, 441000, 16, 2, AudioFileDescriptor::eCodecWav));
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-l5-16bit.flac"), 44100, 441000, 16, 2, AudioFileDescriptor::eCodecFlac));
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-alac.m4a"), 44100, 441000, 16, 2, AudioFileDescriptor::eCodecAlac));
    // AAC encoders can add/drop samples from start of files.
    // Need to account for discarded samples from start of AAC files - decoder drops first frame, which is usually 1024 samples.
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-aac.m4a"), 44100, 443392-1024, 16, 2, AudioFileDescriptor::eCodecAac));
    // Vorbis files
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-q5.ogg"), 44100, 441000, 16, 2, AudioFileDescriptor::eCodecVorbis));


    // additional valid testing files
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k.wav"), 44100, 441000, 16, 1, AudioFileDescriptor::eCodecWav));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-l5-16bit.flac"), 44100, 441000, 16, 1, AudioFileDescriptor::eCodecFlac));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-l5-24bit.flac"), 44100, 441000, 24, 1, AudioFileDescriptor::eCodecFlac));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-l5-24bit.flac"), 44100, 441000, 24, 2, AudioFileDescriptor::eCodecFlac));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-alac.m4a"), 44100, 441000, 16, 1, AudioFileDescriptor::eCodecAlac));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-24bit-alac.m4a"), 44100, 441000, 24, 2, AudioFileDescriptor::eCodecAlac));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-aac.m4a"), 44100, 443392-1024, 16, 1, AudioFileDescriptor::eCodecAac));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-q5.ogg"), 44100, 441000, 16, 1, AudioFileDescriptor::eCodecVorbis));


    // Some files that shouldn't play with any codec.
    invalidFiles.push_back(AudioFileDescriptor(Brn("invalid_long_file"), 0, 0, 16, 1, AudioFileDescriptor::eCodecUnknown));            // Large invalid file.
    invalidFiles.push_back(AudioFileDescriptor(Brn("invalid_short_file"), 0, 0, 16, 1, AudioFileDescriptor::eCodecUnknown));       // Small invalid file.
    // MP4 with moov atom after mdat atom.
    // Currently can't handle this type of file, so check we at least fail to handle them gracefully.
    invalidFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-aac-moov_end.m4a"), 0, 0, 16, 1, AudioFileDescriptor::eCodecUnknown));


    // Files to check behaviour of codec wrappers (and/or container), other than their decoding behaviour.
    // File with embedded cover art
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-q5.ogg"), 44100, 132300, 16, 2, AudioFileDescriptor::eCodecVorbis));
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-q5-coverart.ogg"), 44100, 441000, 16, 2, AudioFileDescriptor::eCodecVorbis));
    // 3s-stereo-44k-q5-coverart.ogg currently fails to play as it relies on seeking and ProtocolManager may exhaust stream during Recognise().
    //invalidFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-q5-coverart.ogg"), 44100, 132300, 16, 2, AudioFileDescriptor::eCodecVorbis));

    Net::Library* lib = new Net::Library(aInitParams);
    std::vector<Brn> args = OptionParser::ConvertArgs(aArgc, aArgv);
    TestCodec(lib->Env(), minFiles, extraFiles, invalidFiles, streamOnlyFiles, args);
    delete lib;
}
