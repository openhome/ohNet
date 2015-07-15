#ifndef HEADER_PIPELINE_CODEC_MPEG4
#define HEADER_PIPELINE_CODEC_MPEG4

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Private/Uri.h>

#include <vector>

EXCEPTION(MediaMpeg4FileInvalid);
EXCEPTION(MediaMpeg4EndOfData);
EXCEPTION(MediaMpeg4InvalidSample);

namespace OpenHome {
namespace Media {
namespace Codec {


class IMpeg4InfoReadable
{
public:
    virtual const Brx& Codec() const = 0;
    virtual TUint SampleRate() const = 0;
    virtual TUint Timescale() const = 0;
    virtual TUint Channels() const = 0;
    virtual TUint BitDepth() const = 0;
    virtual TUint64 Duration() const = 0;
    virtual const Brx& StreamDescriptor() const = 0;
    virtual ~IMpeg4InfoReadable() {}
};

class IMpeg4InfoWritable
{
public:
    static const TUint kCodecBytes = 4;
    static const TUint kMaxStreamDescriptorBytes = 50;  // Empirically chosen; can be increased.
public:
    virtual void SetCodec(const Brx& aCodec) = 0;
    virtual void SetSampleRate(TUint aSampleRate) = 0;
    virtual void SetTimescale(TUint aTimescale) = 0;
    virtual void SetChannels(TUint aChannels) = 0;
    virtual void SetBitDepth(TUint aBitDepth) = 0;
    virtual void SetDuration(TUint64 aDuration) = 0;
    virtual void SetStreamDescriptor(const Brx& aDescriptor) = 0;
    virtual ~IMpeg4InfoWritable() {}
};

class Mpeg4Info : public IMpeg4InfoReadable, public IMpeg4InfoWritable
{
public:
    Mpeg4Info();
    Mpeg4Info(const Brx& aCodec, TUint aSampleRate, TUint aTimescale, TUint aChannels, TUint aBitDepth, TUint64 aDuration, const Brx& aStreamDescriptor);   // FIXME - remove this constructor - maybe?
    TBool Initialised() const;
    void Clear();
public: // from IMpeg4InfoReadable
    const Brx& Codec() const override;
    TUint SampleRate() const override;
    TUint Timescale() const override;
    TUint Channels() const override;
    TUint BitDepth() const override;
    TUint64 Duration() const override;
    const Brx& StreamDescriptor() const override;
public: // from IMpeg4InfoWritable
    void SetCodec(const Brx& aCodec) override;
    void SetSampleRate(TUint aSampleRate) override;
    void SetTimescale(TUint aTimescale) override;
    void SetChannels(TUint aChannels) override;
    void SetBitDepth(TUint aBitDepth) override;
    void SetDuration(TUint64 aDuration) override;
    void SetStreamDescriptor(const Brx& aDescriptor) override;
private:
    Bws<kCodecBytes> iCodec;    // FIXME - not really good enough for recognition; MP3 can also be contained in mp4a
    TUint iSampleRate;
    TUint iTimescale;
    TUint iChannels;
    TUint iBitDepth;
    TUint64 iDuration;
    //TUint64 iSamplesTotal;
    Bws<kMaxStreamDescriptorBytes> iStreamDescriptor;   // FIXME - could actually parse esds before storing here - would allow us to get codec type. However, would depend on what needs to be passed on from ALAC.
};

class Mpeg4InfoReader : public INonCopyable
{
public:
    Mpeg4InfoReader(IReader& aReader);
    void Read(IMpeg4InfoWritable& aInfo);
private:
    IReader& iReader;
};

class Mpeg4InfoWriter : public INonCopyable
{
public:
    static const TUint kMaxBytes = Mpeg4Info::kCodecBytes+4+4+4+4+8+4+Mpeg4Info::kMaxStreamDescriptorBytes;
public:
    Mpeg4InfoWriter(const IMpeg4InfoReadable& aInfo);
    void Write(IWriter& aWriter) const;
private:
    const IMpeg4InfoReadable& iInfo;
};

class IMpeg4Box : public IReader
{
public:
    virtual void Clear() = 0;   // FIXME - replace with ReadFlush()?
    virtual void ReadHeader() = 0;
    virtual TUint Size() const = 0;
    virtual const Brx& Id() const = 0;
    virtual void SkipRemaining() = 0;
    virtual void Skip(TUint aBytes) = 0;
public: // from IReader
    virtual Brn Read(TUint aBytes) = 0;    // Returns [0..aBytes].  0 => stream closed
    virtual void ReadFlush() = 0;          // Unsupported; will ASSERT.
    virtual void ReadInterrupt() = 0;      // Unsupported; will ASSERT.
public:
    virtual ~IMpeg4Box() {}
};

class Mpeg4Box : public IMpeg4Box, private INonCopyable
{
public:
    static const TUint kBoxSizeBytes = 4;
    static const TUint kBoxNameBytes = 4;
    static const TUint kBoxHeaderBytes = kBoxSizeBytes+kBoxNameBytes;
public:
    Mpeg4Box();
private:
    Mpeg4Box(const Mpeg4Box& aBox);
public:
    ~Mpeg4Box();
    void Set(IReader& aReader); // Two-stage construction. If attempting to pass an Mpeg4Box into its constructor as an IReader, compiler will try to use copy constructor instead.
public: // from IMpeg4Box
    void Clear() override;
    void ReadHeader() override;
    TUint Size() const override;
    const Brx& Id() const override;
    void SkipRemaining() override;
    void Skip(TUint aBytes) override;
    Brn Read(TUint aBytes) override;    // Returns [0..aBytes].  0 => stream closed
    void ReadFlush() override;          // Unsupported; will ASSERT.
    void ReadInterrupt() override;      // Unsupported; will ASSERT.
private:
    IReader* iReader;
    TUint iSize;
    Bws<kBoxNameBytes> iId;
    TUint iOffset;
};

class Mpeg4BoxStack : public IMpeg4Box
{
public:
    //Mpeg4BoxStack(IReader& aReader, TUint aNestCount);
    Mpeg4BoxStack(TUint aNestCount);
    ~Mpeg4BoxStack();
    void Set(IReader& aReader);
    void Push();    // Push a box onto the stack; i.e., start processing a new box at index+1. ASSERTs if box count reached.
    void Pop();     // Pop a box off the stack.
    void Reset();
public: // from IMpeg4Box
    void Clear() override;  // FIXME - ever called?
    void ReadHeader() override;
    TUint Size() const override;
    const Brx& Id() const override;
    void SkipRemaining() override;
    void Skip(TUint aBytes) override;
    Brn Read(TUint aBytes) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    std::vector<Mpeg4Box*> iBoxes;
    IReader* iReader;
    TUint iIndex;   // 0 == invalid
};

class SampleSizeTable
{
public:
    SampleSizeTable();
    ~SampleSizeTable();
    void Init(TUint aMaxEntries);
    void Clear();
    void AddSampleSize(TUint aSampleSize);
    TUint SampleSize(TUint aIndex) const;
    TUint Count() const;
private:
    std::vector<TUint> iTable;
};

// FIXME - should probably also include stss here.
// If stss box is present, it means that not all samples are sync samples, and the stss box is consulted to find the first sync sample prior to specified time.
// If stss not present, all samples are sync samples.
class SeekTable
{
public:
    SeekTable();
    ~SeekTable();
    // FIXME - rename the below to Init() and Clear(), respectively.
    void InitialiseSamplesPerChunk(TUint aEntries);
    void InitialiseAudioSamplesPerSample(TUint aEntries);
    void InitialiseOffsets(TUint aEntries);
    TBool Initialised() const;
    void Deinitialise();
    void SetSamplesPerChunk(TUint aFirstChunk, TUint aSamplesPerChunk, TUint aSampleDescriptionIndex);
    void SetAudioSamplesPerSample(TUint32 aSampleCount, TUint32 aAudioSamples);
    void SetOffset(TUint64 aOffset);    // FIXME - rename to AddOffset()? and similar with above methods?
    TUint ChunkCount() const;
    TUint SamplesPerChunk(TUint aChunkIndex) const;
    TUint StartSample(TUint aChunkIndex) const;
    TUint64 Offset(TUint64& aAudioSample, TUint64& aSample);    // FIXME - aSample should be TUint.
    // FIXME - See if it's possible to split this class into its 3 separate components, to simplify it.
    TUint64 GetOffset(TUint aChunkIndex) const;

    void Write(IWriter& aWriter) const;   // Serialise.
private:
    typedef struct {
        TUint   iFirstChunk;
        TUint   iSamples;
        TUint   iSampleDescriptionIndex;
    } TSamplesPerChunkEntry;
    typedef struct {
        TUint   iSampleCount;
        TUint   iAudioSamples;
    } TAudioSamplesPerSampleEntry;
private:
    std::vector<TSamplesPerChunkEntry> iSamplesPerChunk;
    std::vector<TAudioSamplesPerSampleEntry> iAudioSamplesPerSample;
    std::vector<TUint64> iOffsets;
};

class SeekTableInitialiser : public INonCopyable
{
public:
    SeekTableInitialiser(SeekTable& aSeekTable, IReader& aReader);
    void Init();
private:
    SeekTable& iSeekTable;
    IReader& iReader;
    TBool iInitialised;
};

class MsgAudioEncodedWriter : public IWriter
{
public:
    MsgAudioEncodedWriter(MsgFactory& aMsgFactory);
    ~MsgAudioEncodedWriter();
    MsgAudioEncoded* Msg();
public: // from IWriter
    void Write(TByte aValue) override;
    void Write(const Brx& aBuffer) override;
    void WriteFlush() override; // Flush any buffered data to a MsgAudioEncoded.
private:
    void AllocateMsg();
private:
    MsgFactory& iMsgFactory;
    MsgAudioEncoded* iMsg;
    Bws<EncodedAudio::kMaxBytes> iBuf;
};

class OutOfBandReaderSource : public IReaderSource, private INonCopyable
{
public:
    OutOfBandReaderSource(IContainerUrlBlockWriter& aBlockWriter, TUint64 aStartOffset);
public: // from IReaderSource
    void Read(Bwx& aBuffer) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    IContainerUrlBlockWriter& iBlockWriter;
    const TUint64 iStartOffset;
    TUint64 iOffset;
    TBool iLastReadSuccessful;
};

/**
 * IReader that uses an Srs to perform efficient reads from an underlying
 * out-of-band reader.
 */
class OutOfBandReader : public IReader
{
private:
    static const TUint kBufBytes = 1024;
public:
    OutOfBandReader(IContainerUrlBlockWriter& aBlockWriter, TUint64 aStartOffset);
public: // from IReader
    Brn Read(TUint aBytes) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    OutOfBandReaderSource iReaderSource;
    Srs<kBufBytes> iSrs;
};

class Mpeg4Container : public ContainerBase, public IReader
{
private:
    static const TUint kMetadataBoxDepth = 7;
    static const TUint kMaxBufBytes = 4096; // arbitrary
    static const TUint kMaxStreamDescriptorBytes = 50;
    static const TUint kMaxEncodedAudioBytes = EncodedAudio::kMaxBytes;
public:
    Mpeg4Container();
public: // from ContainerBase
    TBool Recognise(Brx& aBuf) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
public: // from IReader
    Brn Read(TUint aBytes) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    void Clear();
    MsgAudioEncoded* Process();                 // May return NULL.
    MsgAudioEncoded* WriteSampleSizeTable() const;
    MsgAudioEncoded* WriteSeekTable() const;    // FIXME - codec shouldn't require this, it should be able to pass a seek request to a sample up and container can handle it. However, CodecController and IStreamHandler require seek pos in bytes, so codec must query SeekTable itself.
    MsgAudioEncoded* ProcessNextAudioBlock();   // May return NULL.
    void ParseMetadataBox(IReader& aReader, TUint aBytes);  // aBytes is size of moov box.
    void ParseBoxMdhd(IMpeg4Box& aBox, TUint aBytes);
    void ParseBoxCodec(IMpeg4Box& aBox, TUint aBytes, const Brx& aCodec);
    void ParseBoxStts(IMpeg4Box& aBox, TUint aBytes);
    void ParseBoxStsc(IMpeg4Box& aBox, TUint aBytes);
    void ParseBoxStco(IMpeg4Box& aBox, TUint aBytes);
    void ParseBoxCo64(IMpeg4Box& aBox, TUint aBytes);
    void ParseBoxStsz(IMpeg4Box& aBox, TUint aBytes);
    void ParseBoxStreamDescriptor(IMpeg4Box& aBox, TUint aBytes);
    void ParseBoxAlac(IMpeg4Box& aBox, TUint aBytes);
private:
    Mpeg4BoxStack iBoxStack;
    //TUint iSize;
    TUint64 iPos;
    Bws<kMaxBufBytes> iBuf;
    TBool iPreProcessingComplete;
    TBool iMetadataRetrieved;
    TUint iChunkIndex;
    TUint iChunkBytesRemaining;
    TUint iBytesToDiscard;
    Bws<4> iCodec;
    TUint iSampleRate;
    TUint iTimescale;
    TUint iChannels;
    TUint iBitDepth;
    TUint64 iDuration;
    //TUint64 iSamplesTotal;
    Bws<kMaxStreamDescriptorBytes> iStreamDescriptor;
    SampleSizeTable iSampleSizeTable;
    SeekTable iSeekTable;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif //HEADER_PIPELINE_CODEC_MPEG4
