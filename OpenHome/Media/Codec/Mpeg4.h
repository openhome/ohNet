#ifndef HEADER_PIPELINE_CODEC_MPEG4
#define HEADER_PIPELINE_CODEC_MPEG4

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecController.h>

EXCEPTION(MediaMpeg4FileInvalid);

namespace OpenHome {
namespace Media {
namespace Codec {

class Mpeg4Box
{
public:
    Mpeg4Box(IContainer& aContainer, Mpeg4Box* aParent = NULL, const TChar* aIdName = NULL, TUint aOffset = 0);
    Mpeg4Box(ICodecController& aController, Mpeg4Box* aParent = NULL, const TChar* aIdName = NULL);
    Mpeg4Box(const Brx& aBuffer, Mpeg4Box* aParent = NULL, const TChar* aIdName = NULL, TUint aOffset = 0);
    ~Mpeg4Box();
    void Read(Bwx& aData, TUint aBytes);
    void SkipEntry();
    void Skip(TUint32 aBytes);
    TBool Empty();
    TBool Match(const TChar* aIdName);
    TBool FindBox(const TChar* aIdName);
    const Brx& Id() const;
    TUint BoxSize() const;
    TUint BytesRead() const;
    TUint Offset() const;
    TUint FileOffset() const;
private:
    void ExtractHeaderId();
    void Reset();
    void UpdateBytesRead(TUint aBytes);
private:
    IContainer* iContainer;
    ICodecController* iController;
    const Brx* iInput;
    Mpeg4Box *iParent;
    Bws<4> iId;             // ID of box.
    Bws<32> iBuf;           // Local buffer.
    TUint iBytesRead;       // Bytes read for current entry.
    TUint iBoxSize;         // Size of current box.
    TUint iOffset;          // Read offset from start of file.
};

class SampleSizeTable
{
public:
    SampleSizeTable();
    ~SampleSizeTable();
    void Initialise(TUint aTableSize);
    void Deinitialise();
    void SetSampleSize(TUint32 aSamplesize);
    TUint32 SampleSize(TUint aEntry);
    TUint Count();
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

class Mpeg4Start
{
public:
    Mpeg4Start(IContainer& aContainer);
    ~Mpeg4Start();
    TUint ContainerSize() const;
private:
    TUint iContainerSize;
};

class Mpeg4MediaInfo
{
public:
    static const TUint kMaxCSDSize = 100;    // 100 bytes of code specific data can be stored
public:
    Mpeg4MediaInfo(ICodecController& aController);
    ~Mpeg4MediaInfo();
    const Brx& CodecSpecificData() const;
    SampleSizeTable& GetSampleSizeTable();
    SeekTable& GetSeekTable();
    TUint32 SampleRate() const;
    TUint64 Timescale() const;
    TUint16 Channels() const;
    TUint16 BitDepth() const;
    TUint64 SamplesTotal() const;
private:
    Bws<kMaxCSDSize> iCodecSpecificData;
    SampleSizeTable iSampleSizeTable;
    SeekTable iSeekTable;
    TUint32 iSampleRate;
    TUint64 iTimescale;
    TUint16 iChannels;
    TUint16 iBitDepth;
    TUint64 iSamplesTotal;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif //HEADER_PIPELINE_CODEC_MPEG4
