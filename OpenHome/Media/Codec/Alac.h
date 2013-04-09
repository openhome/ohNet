#ifndef HEADER_PIPELINE_CODEC_ALAC
#define HEADER_PIPELINE_CODEC_ALAC

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Msg.h>

#include <alac_decoder/alac.h>

extern void alac_free_buffers(alac_file *alac);

namespace OpenHome {
namespace Media {
namespace Codec {

class SampleSizeTable
{
public:
    SampleSizeTable();
    ~SampleSizeTable();
    void Initialise(TUint aTableSize);
    void Deinitialise();
    void SetSampleSize(TUint32 aSamplesize);
    TUint32 SampleSize(TUint aEntry);
    TUint Count() {return iCount;}
private:
    TUint   iCount;
    TUint   iEntry;
    Bwx*    iTable;
};

class SeekTable
{
public:
    SeekTable();
    ~SeekTable();
    void InitialiseSamplesPerChunk(TUint aEntries);
    void InitialiseAudioSamplesPerSample(TUint aEntries);
    void InitialiseOffsets(TUint aEntries);
    void Deinitialise();
    void SetSamplesPerChunk(TUint aFirstChunk, TUint aSamplesPerChunk);
    void SetAudioSamplesPerSample(TUint32 aSampleCount, TUint32 aAudioSamples);
    void SetOffset(TUint64 aOffset);
    TUint64 Offset(TUint64& aAudioSample, TUint64& aSample);
    typedef struct {
        TUint   iFirstChunk;
        TUint   iSamples;
    } TSamplesPerChunkEntry;
    typedef struct {
        TUint   iSampleCount;
        TUint   iAudioSamples;
    } TAudioSamplesPerSampleEntry;
private:
    TUint   iSPCEntries;
    TUint   iSPCEntry;
    Bwx*    iSamplesPerChunk;
    TUint   iASPSEntries;
    TUint   iASPSEntry;
    Bwx*    iAudioSamplesPerSample;
    TUint   iOffsetEntries;
    TUint   iOffsetEntry;
    Bwx*    iOffsets;
};

class CodecAlac : public CodecBase
{
public:
    static const Brn kCodecAlac;
public:
    CodecAlac();
    ~CodecAlac();
private: // from CodecBase
    TBool Recognise(const Brx& aData);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
    void ProcessHeader();
    void BigEndianData(TUint toWrite, TUint aSamplesWritten);
private:
    static const TUint kMaxCSDSize = 100;    // 100 bytes of code specific data can be stored
    Bws<kMaxCSDSize> iCodecSpecificData;
    Brn iName;
    Bws<4*10240> iInBuf;          // how big can these go and need to go ?
    Bws<16*10240> iDecodedBuf;
    Bws<DecodedAudio::kMaxBytes> iOutBuf;
    alac_file *alac;
    SampleSizeTable iSampleSizeTable;
    SeekTable iSeekTable;

    TUint32 iSampleRate;
    TUint16 iChannels;
    TUint16 iBytesPerSample;
    TUint16 iBitDepth;
    TUint64 iSamplesTotal;
    TUint64 iStartSample;
    TUint64 iCurrentSample;
    TUint64 iSamplesWrittenTotal;
    TUint64 iTimescale;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_CODEC_ALAC
