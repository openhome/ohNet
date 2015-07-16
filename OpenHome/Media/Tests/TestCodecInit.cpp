#include <OpenHome/Media/Tests/TestCodec.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

#undef MP3_ENABLE

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
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k.wav"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecWav, true));
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-aiff.aiff"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecAiff, true));
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-aifc.aifc"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecAifc, true));
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-l5-16bit.flac"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecFlac, true));
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-l5-16bit-ogg.flac"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecFlac, true));
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-alac.m4a"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecAlac, true));
    // AAC encoders can add/drop samples from start of files.
    // Need to account for discarded samples from start of AAC files - decoder drops first frame, which is usually 1024 samples.
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-aac.m4a"), 44100, 443392-1024, 16, 2, AudioFileDescriptor::kCodecAac, true));
    // AAC stream, wrapped in ADTS header, inside MPEG transport stream packets (i.e., HLS)
    // File is short of ~680 samples.
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-adts-mpegts.ts"), 44100, 441000-680, 16, 2, AudioFileDescriptor::kCodecAdts, false));
    // MP3 encoders/decoders can add extra samples at start of tracks, which are used for their routines.
#ifdef MP3_ENABLE
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-128k.mp3"), 44100, 442368, 24, 2, AudioFileDescriptor::kCodecMp3, true));
#endif
    // Vorbis files
    minFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-q5.ogg"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecVorbis, true));


    // additional valid testing files
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k.wav"), 44100, 441000, 16, 1, AudioFileDescriptor::kCodecWav, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-24bit.wav"), 44100, 441000, 24, 1, AudioFileDescriptor::kCodecWav, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-24bit.wav"), 44100, 441000, 24, 2, AudioFileDescriptor::kCodecWav, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-48k.wav"), 48000, 480000, 16, 1, AudioFileDescriptor::kCodecWav, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-48k.wav"), 48000, 480000, 16, 2, AudioFileDescriptor::kCodecWav, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-meta-aiff.aiff"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecAiff, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-aiff.aiff"), 44100, 441000, 16, 1, AudioFileDescriptor::kCodecAiff, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-aifc.aifc"), 44100, 441000, 16, 1, AudioFileDescriptor::kCodecAifc, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-l5-16bit.flac"), 44100, 441000, 16, 1, AudioFileDescriptor::kCodecFlac, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-l5-16bit-ogg.flac"), 44100, 441000, 16, 1, AudioFileDescriptor::kCodecFlac, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-l5-24bit.flac"), 44100, 441000, 24, 1, AudioFileDescriptor::kCodecFlac, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-l5-24bit-ogg.flac"), 44100, 441000, 24, 1, AudioFileDescriptor::kCodecFlac, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-l5-24bit.flac"), 44100, 441000, 24, 2, AudioFileDescriptor::kCodecFlac, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-l5-24bit-ogg.flac"), 44100, 441000, 24, 2, AudioFileDescriptor::kCodecFlac, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-alac.m4a"), 44100, 441000, 16, 1, AudioFileDescriptor::kCodecAlac, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-24bit-alac.m4a"), 44100, 441000, 24, 2, AudioFileDescriptor::kCodecAlac, true));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-aac.m4a"), 44100, 443392-1024, 16, 1, AudioFileDescriptor::kCodecAac, true));
#ifdef MP3_ENABLE
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-128k.mp3"), 44100, 442368, 24, 1, AudioFileDescriptor::kCodecMp3, true));
#endif
    //extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-q5.ogg"), 44100, 441000, 16, 1, AudioFileDescriptor::kCodecVorbis, true)); // Too short for seek tests; gets pulled through pipeline before a seek can happen.
    extraFiles.push_back(AudioFileDescriptor(Brn("20s-mono-44k-q5.ogg"), 44100, 882000, 16, 1, AudioFileDescriptor::kCodecVorbis, true));   // Longer mono vorbis file that seek tests can work with.
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-adts-mpegts.ts"), 44100, 441000-680, 16, 1, AudioFileDescriptor::kCodecAdts, false));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-mono-48k-adts-mpegts.ts"), 48000, 480000-768, 16, 1, AudioFileDescriptor::kCodecAdts, false));
    extraFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-48k-adts-mpegts.ts"), 48000, 480000-768, 16, 2, AudioFileDescriptor::kCodecAdts, false));


    // Some files that shouldn't play with any codec.
    invalidFiles.push_back(AudioFileDescriptor(Brn("invalid_long_file"), 0, 0, 16, 1, AudioFileDescriptor::kCodecUnknown, false));     // Large invalid file.
    invalidFiles.push_back(AudioFileDescriptor(Brn("invalid_short_file"), 0, 0, 16, 1, AudioFileDescriptor::kCodecUnknown, false));    // Small invalid file.
    // MP4 with moov atom after mdat atom.
    // Currently can't handle this type of file, so check we at least fail to handle them gracefully.
    invalidFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-aac-moov_end.m4a"), 0, 0, 16, 1, AudioFileDescriptor::kCodecUnknown, false));


    // Files to check behaviour of codec wrappers (and/or container), other than their decoding behaviour.
#ifdef MP3_ENABLE
    // Test different combinations of ID3 tags
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-no_tags.mp3"), 44100, 133632, 24, 2, AudioFileDescriptor::kCodecMp3, true));
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-id3v1.mp3"), 44100, 133632, 24, 2, AudioFileDescriptor::kCodecMp3, true));
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-id3v2.mp3"), 44100, 133632, 24, 2, AudioFileDescriptor::kCodecMp3, true));
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-dual_tags.mp3"), 44100, 133632, 24, 2, AudioFileDescriptor::kCodecMp3, true));
    // Files with two sets of ID3v2 tags
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-two_id3v2_headers.mp3"), 44100, 133632, 24, 2, AudioFileDescriptor::kCodecMp3, true));
    // Second ID3v2 header on a msg boundary (assuming MsgAudioEncoded is normally 6144 bytes) to test container checking/pulling on demand
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-two_id3v2_headers_msg_boundary.mp3"), 44100, 133632, 24, 2, AudioFileDescriptor::kCodecMp3, true));
    // A file that does not play on existing DS's (is recognised as AAC ADTS)
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("mp3-8~24-stereo.mp3"), 24000, 4834944, 24, 2, AudioFileDescriptor::kCodecMp3, true));
#endif
    // File with embedded cover art
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-q5.ogg"), 44100, 132300, 16, 2, AudioFileDescriptor::kCodecVorbis, true));
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-q5-coverart.ogg"), 44100, 441000, 16, 2, AudioFileDescriptor::kCodecVorbis, true));
    // 3s-stereo-44k-q5-coverart.ogg currently used to fail to play as it relies on seeking and ProtocolManager may exhaust stream during Recognise().
    // However, the combination of out-of-band seeking and Rewinder element should now avoid that problem for small files.
    streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-q5-coverart.ogg"), 44100, 132300, 16, 2, AudioFileDescriptor::kCodecVorbis, true));

    return new AudioFileCollection(minFiles, extraFiles, invalidFiles, streamOnlyFiles);
}
