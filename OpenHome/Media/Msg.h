#ifndef HEADER_PIPELINE_MSG
#define HEADER_PIPELINE_MSG

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/InfoProvider.h>

EXCEPTION(AllocatorNoMemory); // heaps are expected to be setup to avoid this.  Any instance of this exception indicates a system design error.

namespace OpenHome {
namespace Media {

class Allocated;

class AllocatorBase : private Av::IInfoProvider
{
public:
    ~AllocatorBase();
    void Free(Allocated* aPtr);
    TUint CellsTotal() const;
    TUint CellBytes() const;
    TUint CellsUsed() const;
    TUint CellsUsedMax() const;
    void GetStats(TUint& aCellsTotal, TUint& aCellBytes, TUint& aCellsUsed, TUint& aCellsUsedMax) const;
    static const Brn kQueryMemory;
protected:
    AllocatorBase(const TChar* aName, TUint aNumCells, TUint aCellBytes, Av::IInfoAggregator& aInfoAggregator);
    Allocated* DoAllocate();
private: // from Av::IInfoProvider
    void QueryInfo(const Brx& aQuery, IWriter& aWriter);
protected:
    Fifo<Allocated*> iFree;
private:
    mutable Mutex iLock;
    const TChar* iName;
    TUint iCellsTotal;
    TUint iCellBytes;
    TUint iCellsUsed;
    TUint iCellsUsedMax;
};
    
template <class T> class Allocator : public AllocatorBase
{
public:
    Allocator(const TChar* aName, TUint aNumCells, Av::IInfoAggregator& aInfoAggregator);
    T* Allocate();
};

template <class T> Allocator<T>::Allocator(const TChar* aName, TUint aNumCells, Av::IInfoAggregator& aInfoAggregator)
    : AllocatorBase(aName, aNumCells, sizeof(T), aInfoAggregator)
{
    for (TUint i=0; i<aNumCells; i++) {
        iFree.Write(new T(*this));
    }
}

template <class T> T* Allocator<T>::Allocate()
{
    return static_cast<T*>(DoAllocate());
}

class Allocated
{
    friend class AllocatorBase;
public:
    void AddRef();
    void RemoveRef();
protected:
    Allocated(AllocatorBase& aAllocator);
protected:
    ~Allocated();
private:
    virtual void RefAdded();
    virtual void RefRemoved();
    virtual void Clear();
protected:
    AllocatorBase& iAllocator;
private:
    Mutex iLock;
    TUint iRefCount;
};

class EncodedAudio : public Allocated
{
    friend class MsgFactory;
public:
    static const TUint kMaxBytes = 6 * 1024;
public:
    EncodedAudio(AllocatorBase& aAllocator);
    const TByte* Ptr(TUint aBytes) const;
    TUint Bytes() const;
private:
    void Construct(const Brx& aData);
private: // from Allocated
    void Clear();
private:
    TByte iData[kMaxBytes];
    TUint iBytes;
};

enum EMediaDataEndian
{
    EMediaDataLittleEndian
   ,EMediaDataBigEndian
};

class Jiffies
{
public:
    static const TUint kJiffiesPerSecond = 56448000; // lcm(384000, 352800)
    static const TUint kJiffiesPerMs = kJiffiesPerSecond / 1000;
public:
    static TUint JiffiesPerSample(TUint aSampleRate);
    static TUint BytesFromJiffies(TUint& aJiffies, TUint aJiffiesPerSample, TUint aNumChannels, TUint aBytesPerSubsample);
private:
    //Number of jiffies per sample
    static const TUint kJiffies7350   = kJiffiesPerSecond / 7350;
    static const TUint kJiffies8000   = kJiffiesPerSecond / 8000;
    static const TUint kJiffies11025  = kJiffiesPerSecond / 11025;
    static const TUint kJiffies12000  = kJiffiesPerSecond / 12000;
    static const TUint kJiffies14700  = kJiffiesPerSecond / 14700;
    static const TUint kJiffies16000  = kJiffiesPerSecond / 16000;
    static const TUint kJiffies22050  = kJiffiesPerSecond / 22050;
    static const TUint kJiffies24000  = kJiffiesPerSecond / 24000;
    static const TUint kJiffies29400  = kJiffiesPerSecond / 29400;
    static const TUint kJiffies32000  = kJiffiesPerSecond / 32000;
    static const TUint kJiffies44100  = kJiffiesPerSecond / 44100;
    static const TUint kJiffies48000  = kJiffiesPerSecond / 48000;
    static const TUint kJiffies88200  = kJiffiesPerSecond / 88200;
    static const TUint kJiffies96000  = kJiffiesPerSecond / 96000;
    static const TUint kJiffies176400 = kJiffiesPerSecond / 176400;
    static const TUint kJiffies192000 = kJiffiesPerSecond / 192000;
};

class DecodedAudio : public Allocated
{
    friend class MsgFactory;
public:
    static const TUint kMaxBytes = 6 * 1024;
    static const TUint kMaxNumChannels = 8;
public:
    DecodedAudio(AllocatorBase& aAllocator);
    const TByte* PtrOffsetBytes(TUint aBytes) const;
    TUint Bytes() const;
    TUint BytesFromJiffies(TUint& aJiffies) const;
    TUint JiffiesFromBytes(TUint aBytes) const;
    TUint NumChannels() const;
    TUint BitDepth() const;
private:
    void Construct(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian);
    void CopyToBigEndian16(const Brx& aData);
    void CopyToBigEndian24(const Brx& aData);
private: // from Allocated
    void Clear();
private:
    TByte iData[kMaxBytes];
    TUint iSubsampleCount;
    TUint iChannels;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iByteDepth;
    TUint iJiffiesPerSample; // cached on construction for convenience
};

class IMsgProcessor;

class Msg : public Allocated
{
    friend class MsgQueue;
public:
    virtual Msg* Process(IMsgProcessor& aProcessor) = 0;
protected:
    Msg(AllocatorBase& aAllocator);
private:
    Msg* iNextMsg;
};

class Ramp
{
public:
    static const TUint kRampMax = 1<<30;
    static const TUint kRampMin = 0;
    enum EDirection
    {
        ENone
       ,EUp
       ,EDown
    };
public:
    Ramp();
    void Reset();
    TBool Set(TUint aStart, TUint aFragmentSize, TUint aRampDuration, EDirection aDirection, Ramp& aSplit, TUint& aSplitPos); // returns true iff aSplit is set
    Ramp Split(TUint aNewSize, TUint aCurrentSize);
    TUint Start() const { return iStart; }
    TUint End() const { return iEnd; }
    EDirection Direction() const { return iDirection; }
    TBool IsEnabled() const { return iEnabled; }
private:
    void SelectLowerRampPoints(TUint aRequestedStart, TUint aRequestedEnd);
    void Validate();
private:
    TUint iStart;
    TUint iEnd;
    EDirection iDirection;
    TBool iEnabled;
};

class RampApplicator : private INonCopyable
{
public:
    RampApplicator(const Media::Ramp& aRamp);
    TUint Start(const Brx& aData, TUint aBitDepth, TUint aNumChannels); // returns number of samples
    void GetNextSample(TByte* aDest);
private:
    const Media::Ramp& iRamp;
    const TByte* iPtr;
    TUint iBitDepth;
    TUint iNumChannels;
    TUint iNumSamples;
    TInt iTotalRamp;
    TUint iFullRampSpan;
    TUint iLoopCount;
};


class MsgFactory;

class MsgAudioEncoded : public Msg
{
    friend class MsgFactory;
public:
    MsgAudioEncoded(AllocatorBase& aAllocator);
    MsgAudioEncoded* Split(TUint aBytes); // returns block after aBytes
    void Add(MsgAudioEncoded* aMsg); // combines MsgAudioEncoded instances so they report larger sizes etc
    TUint Bytes() const;
    void CopyTo(TByte* aPtr);
private:
    void Initialise(EncodedAudio* aEncodedAudio);
private: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    MsgAudioEncoded* iNextAudio;
    TUint iSize; // Bytes
    TUint iOffset; // Bytes
    EncodedAudio* iAudioData;
};

class MsgAudio : public Msg
{
    friend class MsgFactory;
public:
    MsgAudio* Split(TUint aJiffies); // returns block after aAt
    //void Add(MsgAudio* aMsg); // combines MsgAudio instances so they report longer durations etc
    virtual MsgAudio* Clone(); // create new MsgAudio, copy size/offset
    TUint Jiffies() const;
    TUint SetRamp(TUint aStart, TUint aDuration, Ramp::EDirection aDirection, MsgAudio*& aSplit); // returns iRamp.End()
    const Media::Ramp& Ramp() const;
protected:
    MsgAudio(AllocatorBase& aAllocator);
    void Initialise();
protected: // from Msg
    void Clear();
private:
    virtual MsgAudio* Allocate() = 0;
    virtual void SplitCompleted(MsgAudio& aRemaining);
protected:
    MsgFactory* iMsgFactory;
    MsgAudio* iNextAudio;
    TUint iSize; // Jiffies
    TUint iOffset; // Jiffies
    Media::Ramp iRamp;
};

class MsgPlayable;
class MsgPlayablePcm;

class MsgAudioPcm : public MsgAudio
{
    friend class MsgFactory;
public:
    MsgAudioPcm(AllocatorBase& aAllocator);
    TUint64 TrackOffset() const; // offset of the start of this msg from the start of its track.  FIXME no tests for this yet
    MsgPlayable* CreatePlayable(); // removes ref, transfer ownership of DecodedAudio
public: // from MsgAudio
    MsgAudio* Clone(); // create new MsgAudio, take ref to DecodedAudio, copy size/offset
private:
    void Initialise(DecodedAudio* aDecodedAudio, TUint64 aTrackOffset, Allocator<MsgPlayablePcm>& aAllocatorPlayable);
private: // from MsgAudio
    MsgAudio* Allocate();
    void SplitCompleted(MsgAudio& aRemaining);
private: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    DecodedAudio* iAudioData;
    Allocator<MsgPlayablePcm>* iAllocatorPlayable;
    TUint64 iTrackOffset;
};

class MsgPlayableSilence;

class MsgSilence : public MsgAudio
{
    friend class MsgFactory;
public:
    MsgSilence(AllocatorBase& aAllocator);
    MsgPlayable* CreatePlayable(TUint aSampleRate, TUint aBitDepth, TUint aNumChannels); // removes ref
private:
    void Initialise(TUint aJiffies, Allocator<MsgPlayableSilence>& aAllocatorPlayable);
private: // from MsgAudio
    MsgAudio* Allocate();
    void SplitCompleted(MsgAudio& aRemaining);
private: // from Msg
    Msg* Process(IMsgProcessor& aProcessor);
private:
    Allocator<MsgPlayableSilence>* iAllocatorPlayable;
};

class IPcmProcessor;

class MsgPlayable : public Msg
{
public:
    MsgPlayable* Split(TUint aBytes); // returns block after aAt
    void Add(MsgPlayable* aMsg); // combines MsgAudio instances so they report longer durations etc
    virtual MsgPlayable* Clone(); // create new MsgPlayable, copy size/offset
    TUint Bytes() const;
    const Media::Ramp& Ramp() const;
    virtual void Read(IPcmProcessor& aProcessor) = 0;
protected:
    MsgPlayable(AllocatorBase& aAllocator);
    void Initialise(TUint aSizeBytes, TUint aOffsetBytes, const Media::Ramp& aRamp);
protected: // from Msg
    void RefAdded();
    void RefRemoved();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    virtual MsgPlayable* Allocate() = 0;
    virtual void SplitCompleted(MsgPlayable& aRemaining);
protected:
    MsgPlayable* iNextPlayable;
    TUint iSize; // Bytes
    TUint iOffset; // Bytes
    Media::Ramp iRamp;
};

class MsgPlayablePcm : public MsgPlayable
{
    friend class MsgAudioPcm;
public:
    MsgPlayablePcm(AllocatorBase& aAllocator);
private:
    void Initialise(DecodedAudio* aDecodedAudio, TUint aSizeBytes, TUint aOffsetBytes, const Media::Ramp& aRamp);
private: // from MsgPlayable
    MsgPlayable* Clone(); // create new MsgPlayable, take ref to DecodedAudio, copy size/offset
    void Read(IPcmProcessor& aProcessor);
    MsgPlayable* Allocate();
    void SplitCompleted(MsgPlayable& aRemaining);
private: // from Msg
    void Clear();
private:
    DecodedAudio* iAudioData;
};

class MsgPlayableSilence : public MsgPlayable
{
    friend class MsgSilence;
public:
    MsgPlayableSilence(AllocatorBase& aAllocator);
private:
    void Initialise(TUint aSizeBytes, TUint aBitDepth, TUint aNumChannels, const Media::Ramp& aRamp);
private: // from MsgPlayable
    void Read(IPcmProcessor& aProcessor);
    MsgPlayable* Allocate();
private:
    TUint iBitDepth;
    TUint iNumChannels;
};

class AudioFormat
{
    friend class MsgAudioFormat;
public:
    static const TUint kMaxCodecNameBytes = 32;
public:
    TUint BitRate() const { return iBitRate; }
    TUint BitDepth() const { return iBitDepth; }
    TUint SampleRate() const { return iSampleRate; }
    TUint NumChannels() const { return iNumChannels; }
    const Brx& CodecName() const { return iCodecName; }
    TUint64 TrackLength() const { return iTrackLength; }
    TBool Lossless() const { return iLossless; }
private:
    AudioFormat();
    void Set(TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TBool aLossless);
private:
    TUint iBitRate;
    TUint iBitDepth;
    TUint iSampleRate;
    TUint iNumChannels;
    Bws<kMaxCodecNameBytes> iCodecName;
    TUint64 iTrackLength; // jiffies
    TBool iLossless;
};

class MsgAudioFormat : public Msg
{
    friend class MsgFactory;
public:
    MsgAudioFormat(AllocatorBase& aAllocator);
    const AudioFormat& Format() const;
private:
    void Initialise(TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TBool aLossless);
private: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    AudioFormat iAudioFormat;
};

class MsgTrack : public Msg
{
public:
    static const TUint kMaxBytes = 100; // FIXME
public:
    MsgTrack(AllocatorBase& aAllocator);
private: // from Msg
    Msg* Process(IMsgProcessor& aProcessor);
private:
    // track uri & meta data
};

class IRestreamer;

class MsgEncodedStream : public Msg
{
    friend class MsgFactory;
public:
    static const TUint kMaxUriBytes = 1024;
    static const TUint kMaxMetaTextBytes = 1024;
public:
    MsgEncodedStream(AllocatorBase& aAllocator);
    const Brx& Uri() const;
    const Brx& MetaText() const;
    TUint TotalBytes() const;
    TBool IsSeekable() const;
    TBool IsLive() const;
    TUint StreamId() const;
    IRestreamer* Restreamer() const;
private:
    void Initialise(const Brx& aUri, const Brx& aMetaText, TUint aTotalBytes, TBool aSeekable, TBool aLive, TUint aStreamId, IRestreamer* aRestreamer);
private: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    Bws<kMaxUriBytes> iUri;
    Bws<kMaxMetaTextBytes> iMetaText;
    TUint iTotalBytes;
    TBool iSeekable;
    TBool iLive;
    TUint iStreamId;
    IRestreamer* iRestreamer;
};

class MsgMetaText : public Msg
{
    friend class MsgFactory;
public:
    static const TUint kMaxBytes = 1024;
public:
    MsgMetaText(AllocatorBase& aAllocator);
    const Brx& MetaText() const;
private:
    void Initialise(const Brx& aMetaText);
private: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    Bws<kMaxBytes> iMetaText;
};

class MsgHalt : public Msg
{
public:
    MsgHalt(AllocatorBase& aAllocator);
private: // from Msg
    Msg* Process(IMsgProcessor& aProcessor);
};

class MsgFlush : public Msg
{
public:
    MsgFlush(AllocatorBase& aAllocator);
private: // from Msg
    Msg* Process(IMsgProcessor& aProcessor);
};

class MsgQuit : public Msg
{
public:
    MsgQuit(AllocatorBase& aAllocator);
private: // from Msg
    Msg* Process(IMsgProcessor& aProcessor);
};

class IMsgProcessor
{
public:
    virtual Msg* ProcessMsg(MsgAudioEncoded* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgAudioPcm* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgSilence* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgPlayable* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgAudioFormat* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgTrack* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgEncodedStream* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgMetaText* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgHalt* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgFlush* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgQuit* aMsg) = 0;
};

/**
 * Used to retrieve pcm audio data from a MsgPlayable
 */
class IPcmProcessor
{
public:
    /**
     * Called once per call to MsgPlayable::ProcessAudio.
     *
     * Will be called before any calls to ProcessFragment or ProcessSample.
     */
    virtual void BeginBlock() = 0;
    /**
     * Optional function.  Gives the processor a chance to copy memory in a single block.
     *
     * Is not guaranteed to be called so all processors must implement ProcessSample.
     * Bit depth is indicated in function name; number of channels is passed as a parameter.
     *
     * @param aData         Packed big endian pcm data.  Will always be a complete number of samples.
     * @param aNumChannels  Number of channels.
     *
     * @return  true if the fragment was processed (meaning that ProcessSample will not be called for aData);
     *          false otherwise (meaning that ProcessSample will be called for each sample in aData).
     */
    virtual TBool ProcessFragment8(const Brx& aData, TUint aNumChannels) = 0;
    virtual TBool ProcessFragment16(const Brx& aData, TUint aNumChannels) = 0;
    virtual TBool ProcessFragment24(const Brx& aData, TUint aNumChannels) = 0;
    /**
     * Process a single sample of audio.
     *
     * Data is packed and big endian.
     * Bit depth is indicated in function name; number of channels is passed as a parameter.
     *
     * @param aSample  Pcm data for a single sample.  Length will be (bitDepth * numChannels).
     */
    virtual void ProcessSample8(const TByte* aSample, TUint aNumChannels) = 0;
    virtual void ProcessSample16(const TByte* aSample, TUint aNumChannels) = 0;
    virtual void ProcessSample24(const TByte* aSample, TUint aNumChannels) = 0;
    /**
     * Called once per call to MsgPlayable::ProcessAudio.
     *
     * No more calls to ProcessFragment or ProcessSample will be made after this.
     */
    virtual void EndBlock() = 0;
};

class MsgQueue
{
public:
    MsgQueue();
    ~MsgQueue();
    void Enqueue(Msg* aMsg);
    Msg* Dequeue();
    void EnqueueAtHead(Msg* aMsg);
    TBool IsEmpty() const;
private:
    mutable Mutex iLock;
    Semaphore iSem;
    Msg* iHead;
    Msg* iTail;
};

class MsgQueueFlushable
{
protected:
    MsgQueueFlushable();
    virtual ~MsgQueueFlushable();
    void DoEnqueue(Msg* aMsg);
    Msg* DoDequeue();
    void EnqueueAtHead(Msg* aMsg);
    TUint Jiffies() const;
    TUint EncodedBytes() const;
    TBool IsEmpty() const;
private:
    void Add(TUint& aValue, TUint aAdded);
    void Remove(TUint& aValue, TUint aRemoved);
    void StartFlushing();
    void StopFlushing();
private:
    virtual void ProcessMsgIn(MsgAudioEncoded* aMsg);
    virtual void ProcessMsgIn(MsgAudioPcm* aMsg);
    virtual void ProcessMsgIn(MsgSilence* aMsg);
    virtual void ProcessMsgIn(MsgAudioFormat* aMsg);
    virtual void ProcessMsgIn(MsgTrack* aMsg);
    virtual void ProcessMsgIn(MsgEncodedStream* aMsg);
    virtual void ProcessMsgIn(MsgMetaText* aMsg);
    virtual void ProcessMsgIn(MsgHalt* aMsg);
    virtual void ProcessMsgIn(MsgFlush* aMsg);
    virtual void ProcessMsgIn(MsgQuit* aMsg);
    virtual Msg* ProcessMsgOut(MsgAudioEncoded* aMsg);
    virtual Msg* ProcessMsgOut(MsgAudioPcm* aMsg);
    virtual Msg* ProcessMsgOut(MsgSilence* aMsg);
    virtual Msg* ProcessMsgOut(MsgAudioFormat* aMsg);
    virtual Msg* ProcessMsgOut(MsgTrack* aMsg);
    virtual Msg* ProcessMsgOut(MsgEncodedStream* aMsg);
    virtual Msg* ProcessMsgOut(MsgMetaText* aMsg);
    virtual Msg* ProcessMsgOut(MsgHalt* aMsg);
    virtual Msg* ProcessMsgOut(MsgFlush* aMsg);
    virtual Msg* ProcessMsgOut(MsgQuit* aMsg);
private:
    class ProcessorQueueIn : public IMsgProcessor, private INonCopyable
    {
    public:
        ProcessorQueueIn(MsgQueueFlushable& aQueue);
    private:
        Msg* ProcessMsg(MsgAudioEncoded* aMsg);
        Msg* ProcessMsg(MsgAudioPcm* aMsg);
        Msg* ProcessMsg(MsgSilence* aMsg);
        Msg* ProcessMsg(MsgPlayable* aMsg);
        Msg* ProcessMsg(MsgAudioFormat* aMsg);
        Msg* ProcessMsg(MsgTrack* aMsg);
        Msg* ProcessMsg(MsgEncodedStream* aMsg);
        Msg* ProcessMsg(MsgMetaText* aMsg);
        Msg* ProcessMsg(MsgHalt* aMsg);
        Msg* ProcessMsg(MsgFlush* aMsg);
        Msg* ProcessMsg(MsgQuit* aMsg);
    private:
        MsgQueueFlushable& iQueue;
    };
    class ProcessorQueueOut : public IMsgProcessor, private INonCopyable
    {
    public:
        ProcessorQueueOut(MsgQueueFlushable& aQueue);
    private:
        Msg* ProcessMsg(MsgAudioEncoded* aMsg);
        Msg* ProcessMsg(MsgAudioPcm* aMsg);
        Msg* ProcessMsg(MsgSilence* aMsg);
        Msg* ProcessMsg(MsgPlayable* aMsg);
        Msg* ProcessMsg(MsgAudioFormat* aMsg);
        Msg* ProcessMsg(MsgTrack* aMsg);
        Msg* ProcessMsg(MsgEncodedStream* aMsg);
        Msg* ProcessMsg(MsgMetaText* aMsg);
        Msg* ProcessMsg(MsgHalt* aMsg);
        Msg* ProcessMsg(MsgFlush* aMsg);
        Msg* ProcessMsg(MsgQuit* aMsg);
    private:
        MsgQueueFlushable& iQueue;
    };
private:
    Mutex iLock;
    MsgQueue iQueue;
    TUint iEncodedBytes;
    TUint iJiffies;
    TBool iFlushing;
};

class AutoMsgRef : private INonCopyable
{
public:
    AutoMsgRef(Msg& aMsg);
    ~AutoMsgRef();
private:
    Msg& iMsg;
};

class IPipelineElementUpstream
{
public:
    virtual Msg* Pull() = 0;
};

class IPipelineElementDownstream
{
public:
    virtual void Push(Msg* aMsg) = 0;
};

class MsgFactory
{
public:
    MsgFactory(Av::IInfoAggregator& aInfoAggregator,
               TUint aEncodedAudioCount, TUint aMsgAudioEncodedCount, 
               TUint aDecodedAudioCount, TUint aMsgAudioPcmCount, TUint aMsgSilenceCount,
               TUint aMsgPlayablePcmCount, TUint aMsgPlayableSilenceCount, TUint aMsgAudioFormatCount,
               TUint aMsgTrackCount, TUint aMsgEncodedStreamCount, TUint aMsgMetaTextCount,
               TUint aMsgHaltCount, TUint aMsgFlushCount, TUint aMsgQuitCount);
    //
    MsgAudioEncoded* CreateMsgAudioEncoded(const Brx& aData);
    MsgAudioPcm* CreateMsgAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset);
    MsgSilence* CreateMsgSilence(TUint aSizeJiffies);
    MsgAudioFormat* CreateMsgAudioFormat(TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TBool aLossless);
    MsgTrack* CreateMsgTrack();
    MsgEncodedStream* CreateMsgEncodedStream(const Brx& aUri, const Brx& aMetaText, TUint aTotalBytes, TBool aSeekable, TBool aLive, TUint aStreamId, IRestreamer* aRestreamer);
    MsgMetaText* CreateMsgMetaText(const Brx& aMetaText);
    MsgHalt* CreateMsgHalt();
    MsgFlush* CreateMsgFlush();
    MsgQuit* CreateMsgQuit();
private:
    EncodedAudio* CreateEncodedAudio(const Brx& aData);
    DecodedAudio* CreateDecodedAudio(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian);
private:
    Allocator<EncodedAudio> iAllocatorEncodedAudio;
    Allocator<MsgAudioEncoded> iAllocatorMsgAudioEncoded;
    Allocator<DecodedAudio> iAllocatorDecodedAudio;
    Allocator<MsgAudioPcm> iAllocatorMsgAudioPcm;
    Allocator<MsgSilence> iAllocatorMsgSilence;
    Allocator<MsgPlayablePcm> iAllocatorMsgPlayablePcm;
    Allocator<MsgPlayableSilence> iAllocatorMsgPlayableSilence;
    Allocator<MsgAudioFormat> iAllocatorMsgAudioFormat;
    Allocator<MsgTrack> iAllocatorMsgTrack;
    Allocator<MsgEncodedStream> iAllocatorMsgEncodedStream;
    Allocator<MsgMetaText> iAllocatorMsgMetaText;
    Allocator<MsgHalt> iAllocatorMsgHalt;
    Allocator<MsgFlush> iAllocatorMsgFlush;
    Allocator<MsgQuit> iAllocatorMsgQuit;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_MSG
