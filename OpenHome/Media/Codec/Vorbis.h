#ifndef HEADER_PIPELINE_CODEC_VORBIS
#define HEADER_PIPELINE_CODEC_VORBIS

extern "C" {

#include <ogg.h>
#include <os_types.h>
#include <config_types.h>
#include <ivorbisfile.h>
#include <ivorbiscodec.h>
}

#include <OpenHome/Media/Codec/CodecController.h>


namespace OpenHome {
namespace Media {
namespace Codec {

class CodecVorbis : public CodecBase
{
public:
    static const Brn kCodecVorbis;
public:
    CodecVorbis();
    ~CodecVorbis();
private: // from CodecBase
    TBool Recognise(const Brx& aData);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
public:
    size_t ReadCallback(void *ptr, size_t size, size_t nmemb);
    int SeekCallback(ogg_int64_t offset, int whence);
    int CloseCallback();
    long TellCallback();
    void PrintCallback(char *message);
private:
    void BigEndian(TInt16* aDst, TInt16* aSrc, TUint aSamples);
    void FlushOutput();

    ov_callbacks iCallbacks;

    void *iDataSource; // dummy stream identifier
    OggVorbis_File iVf;
    vorbis_info* iInfo;

    Bws<EncodedAudio::kMaxBytes> iRecogBuf;
    Bws<DecodedAudio::kMaxBytes> iInBuf;
    Bws<DecodedAudio::kMaxBytes> iOutBuf;
    TUint32 iAudioBytes;
 
    TUint32 iSampleRate;
    TUint32 iBytesPerSec;
    TUint32 iBitrateMax;
    TUint32 iBitrateAverage;
    TUint16 iChannels;
    TUint16 iBytesPerSample;
    TUint16 iBitDepth;
    TUint64 iSamplesTotal;
    TUint64 iTotalSamplesOutput;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;
    TBool iRecognising;
    TUint64 iPeekOffset;
    TInt iLink;

    TBool iStreamEnded;
    TBool iNewStreamStarted;
};

} //namespace Codec
} //namespace Media
} //namespace OpenHome

#endif //HEADER_PIPELINE_CODEC_VORBIS
