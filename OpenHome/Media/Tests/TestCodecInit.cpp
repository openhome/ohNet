#include <OpenHome/Media/Tests/TestCodec.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

TestCodecMinimalPipeline* CreateTestCodecPipeline(Environment& aEnv, IMsgProcessor& aMsgProcessor)
{
    return new TestCodecMinimalPipeline(aEnv, aMsgProcessor);
}

AudioFileCollection* TestCodecFiles()
{
    // test file vectors
    std::vector<AudioFileDescriptor> minFiles;
    std::vector<AudioFileDescriptor> extraFiles;
    std::vector<AudioFileDescriptor> invalidFiles;
    std::vector<AudioFileDescriptor> streamOnlyFiles;

    // core testing files
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k.wav"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecWav));
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-aiff.aiff"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecAiff));
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-aifc.aifc"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecAifc));
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-l5-16bit.flac"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecFlac));
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-alac.m4a"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecAlac));
    // AAC encoders can add/drop samples from start of files.
    // Need to account for discarded samples from start of AAC files - decoder drops first frame, which is usually 1024 samples.
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-aac.m4a"), 44100, 443392-1024, 16, 2, AudioFileDescriptor::kCodecAac));
    // Vorbis files
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-q5.ogg"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecVorbis));


    // additional valid testing files
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k.wav"), 44100, 441000, 16, 1, AudioFileDescriptor::kCodecWav));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-meta-aiff.aiff"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecAiff));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-aiff.aiff"), 44100, 441000, 16, 1, AudioFileDescriptor::kCodecAiff));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-aifc.aifc"), 44100, 441000, 16, 1, AudioFileDescriptor::kCodecAifc));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-l5-16bit.flac"), 44100, 441000, 16, 1, AudioFileDescriptor::kCodecFlac));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-l5-24bit.flac"), 44100, 441000, 24, 1, AudioFileDescriptor::kCodecFlac));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-l5-24bit.flac"), 44100, 441000, 24, 2, AudioFileDescriptor::kCodecFlac));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-alac.m4a"), 44100, 441000, 16, 1, AudioFileDescriptor::kCodecAlac));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-24bit-alac.m4a"), 44100, 441000, 24, 2, AudioFileDescriptor::kCodecAlac));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-aac.m4a"), 44100, 443392-1024, 16, 1, AudioFileDescriptor::kCodecAac));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-q5.ogg"), 44100, 441000, 16, 1, AudioFileDescriptor::kCodecVorbis));


    // Some files that shouldn't play with any codec.
    invalidFiles.push_back(AudioFileDescriptor(Brn("invalid_long_file"), 0, 0, 16, 1, AudioFileDescriptor::kCodecUnknown));     // Large invalid file.
    invalidFiles.push_back(AudioFileDescriptor(Brn("invalid_short_file"), 0, 0, 16, 1, AudioFileDescriptor::kCodecUnknown));    // Small invalid file.
    // MP4 with moov atom after mdat atom.
    // Currently can't handle this type of file, so check we at least fail to handle them gracefully.
    invalidFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-aac-moov_end.m4a"), 0, 0, 16, 1, AudioFileDescriptor::kCodecUnknown));


    // Files to check behaviour of codec wrappers (and/or container), other than their decoding behaviour.
    // File with embedded cover art
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-q5.ogg"), 44100, 132300, 16, 2, AudioFileDescriptor::kCodecVorbis));
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-q5-coverart.ogg"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecVorbis));
    // 3s-stereo-44k-q5-coverart.ogg currently fails to play as it relies on seeking and ProtocolManager may exhaust stream during Recognise().
    //invalidFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-q5-coverart.ogg"), 44100, 132300, 16, 2, AudioFileDescriptor::kCodecVorbis));

    return new AudioFileCollection(minFiles, extraFiles, invalidFiles, streamOnlyFiles);
}
