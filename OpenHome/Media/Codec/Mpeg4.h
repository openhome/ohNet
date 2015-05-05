#ifndef HEADER_PIPELINE_CODEC_MPEG4
#define HEADER_PIPELINE_CODEC_MPEG4

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecController.h>

#include <vector>

EXCEPTION(MediaCodecRaopNotFound);
EXCEPTION(MediaMpeg4FileInvalid);
EXCEPTION(MediaMpeg4EndOfData);

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

//class ReaderPassThrough : public IReader, private INonCopyable
//{
//public:
//    ReaderPassThrough(IReader& aReader);
//private: // from IReader
//    Brn Read(TUint aBytes) override;    // Returns [0..aBytes].  0 => stream closed
//    void ReadFlush() override;
//    void ReadInterrupt() override;
//private:
//    IReader& iReader;
//};
//
//class IMpeg4Box
//{
//
//};
//
//
//class Mpeg4BoxStack : IMpeg4Box
//{
//public:
//    Mpeg4BoxStack(IReader& aReader, TUint aNestCount);
//    ~Mpeg4BoxStack();
//    void Push();    // Push a box onto the stack; i.e. start processing a new box and index+1. ASSERTs if box count reached.
//    void Pop();     // Pop a box off the stack.
//private:
//    std::vector<Mpeg4Box> iBoxes;   // FIXME - push aNestCount boxes into here.
//    TUint iIndex;
//};

class Mpeg4Box : public IReader, private INonCopyable
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
    void Clear();   // FIXME - replace with ReadFlush()? - can actually just remove and reset with Set(), or Set() could call this; would make this private, then.
    void ReadHeader();
    TUint Size() const;
    const Brx& Id() const;
    //TUint Offset() const;
    //void Read(Bwx& aBuf, TUint aBytes);
    void SkipRemaining();       // FIXME - req'd? Yes.
    void Skip(TUint aBytes);    // FIXME - req'd? Probably?
public: // from IReader
    Brn Read(TUint aBytes) override;    // Returns [0..aBytes].  0 => stream closed
    void ReadFlush() override;          // Unsupported; will ASSERT.
    void ReadInterrupt() override;      // Unsupported; will ASSERT.
private:
    IReader* iReader;
    TUint iSize;
    Bws<kBoxNameBytes> iId;
    TUint iOffset;
};

//class Mpeg4BoxMdhd
//{
//
//};

class SampleSizeTable
{
public:
    SampleSizeTable();
    ~SampleSizeTable();
    void Init(TUint aMaxEntries);
    void Clear();
    void AddSampleSize(TUint aSampleSize);
    TUint SampleSize(TUint aIndex);
    TUint Count();
private:
    std::vector<TUint> iTable;
};

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
    TUint64 Offset(TUint64& aAudioSample, TUint64& aSample);
    // FIXME - have a TBool Initialised() method that tells us if all 3 parts of seek table have been initialised.
    // FIXME - also see if it's possible to split this class into its 3 separate components, to simplify it.
    TUint64 GetOffset(TUint aChunkIndex) const;
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

class Mpeg4Container : public ContainerBase, public IReader
{
private:
    static const TUint kMaxBufBytes = 4096; // arbitrary
    static const TUint kMaxStreamDescriptorBytes = 50;
public:
    Mpeg4Container();
public: // from ContainerBase
    TBool Recognise(Brx& aBuf);
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
public: // from IReader
    Brn Read(TUint aBytes) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    Msg* Process(); // FIXME - should this do the work of splitting audio and return pointer to it? - Confusing.
    TBool ParseMetadataBox(IReader& aReader, TUint aBytes);  // aBytes is size of moov box.
    void ParseBoxMdhd(Mpeg4Box& aBox, TUint aBytes);
    void ParseBoxMp4a(Mpeg4Box& aBox, TUint aBytes);
    void ParseBoxStts(Mpeg4Box& aBox, TUint aBytes);
    void ParseBoxStsc(Mpeg4Box& aBox, TUint aBytes);
    void ParseBoxStco(Mpeg4Box& aBox, TUint aBytes);
    void ParseBoxCo64(Mpeg4Box& aBox, TUint aBytes);
    void ParseBoxStsz(Mpeg4Box& aBox, TUint aBytes);
    void ParseBoxStreamDescriptor(Mpeg4Box& aBox, TUint aBytes);
private:
    //TUint iSize;
    TUint64 iPos;
    Bws<kMaxBufBytes> iBuf;
    TBool iMetadataRetrieved;
    TBool iProcessingMetadataComplete;  // FIXME - is this the same as iMetadataRetrieved?
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

//class Mpeg4StreamInfo
//{
//public:
//    static const TUint kMaxCodecDataSize = 100;
//public:
//    //Mpeg4StreamInfo(ICodecController& aController);
//    ~Mpeg4StreamInfo();
//    void Process();
//public:
//    const Brx& CodecSpecificData() const;
//    TUint32 SampleRate() const;
//    TUint32 Timescale() const;
//    TUint16 Channels() const;
//    TUint16 BitDepth() const;
//    TUint64 Duration() const;
//protected:
//    ICodecController& iController;
//    Bws<kMaxCodecDataSize> iCodecSpecificData;
//    TUint32 iSampleRate;
//    TUint32 iTimescale;
//    TUint16 iChannels;
//    TUint16 iBitDepth;
//    TUint64 iSamplesTotal;
//};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif //HEADER_PIPELINE_CODEC_MPEG4
