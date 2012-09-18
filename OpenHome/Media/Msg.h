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
    virtual void Clear();
protected:
    AllocatorBase& iAllocator;
private:
    Mutex iLock;
    TUint iRefCount;
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
    static const TUint kBytesPerSubsample = sizeof(TUint);
    static const TUint kMaxSubsamples = kMaxBytes/kBytesPerSubsample;
public:
    DecodedAudio(AllocatorBase& aAllocator);
    const TUint* PtrOffsetBytes(TUint aBytes) const;
    TUint Bytes() const;
    TUint BytesFromJiffies(TUint& aJiffies) const;
    TUint JiffiesFromBytes(TUint aBytes) const;
    TUint NumChannels() const;
private:
    void Construct(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian); // sample rate, bit-depth, num channels, const brx& (ptr/len), endianness);
    static void UnpackBigEndian(TUint32* aDst, const TUint8* aSrc, TUint aBitDepth, TUint aNumSubsamples);
    static void UnpackLittleEndian(TUint32* aDst, const TUint8* aSrc, TUint aBitDepth, TUint aNumSubsamples);
private: // from Allocated
    void Clear();
private:
    TUint iSubsamples[kMaxSubsamples]; // one sub-sample per channel == 1 sample
    TUint iSubsampleCount;
    TUint iChannels;
    //TUint64 iSampleStart; // pos of first sample in iData within the track
    //TUint64 iSamplesTotal; // total num samples in the track
    TUint iSampleRate;
    TUint iBitRate; // what is this ??
    TUint iBitDepth;
    TUint iJiffiesPerSample; // cached on construction for convenience
    //TBool iLossless;
    //Bws<kMaxCodecNameBytes> iCodecName;
    //TUint iSamples; // bytes/4 - remove
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
    void Apply(Bwx& aData, TUint aChannels);
    TUint Start() const { return iStart; }
    TUint End() const { return iEnd; }
    EDirection Direction() const { return iDirection; }
    TBool IsEnabled() const { return iEnabled; }
private:
    void SelectLowerRampPoints(TUint aRequestedStart, TUint aRequestedEnd);
private:
    TUint iStart;
    TUint iEnd;
    EDirection iDirection;
    TBool iEnabled;
};


class MsgFactory;

class MsgAudio : public Msg
{
    friend class MsgFactory;
public:
    MsgAudio* Split(TUint aJiffies); // returns block after aAt
    //void Add(MsgAudio* aMsg); // combines MsgAudio instances so they report longer durations etc
    virtual MsgAudio* Clone(); // create new MsgAudio, copy size/offset
    TUint Jiffies() const;
    TUint SetRamp(TUint aStart, TUint aDuration, Ramp::EDirection aDirection, MsgAudio*& aSplit); // returns iRamp.End()
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
    Ramp iRamp;
};

class MsgPlayable;
class MsgPlayablePcm;

class MsgAudioPcm : public MsgAudio
{
    friend class MsgFactory;
public:
    MsgAudioPcm(AllocatorBase& aAllocator);
    MsgPlayable* CreatePlayable(); // removes ref, transfer ownership of DecodedAudio
public: // from MsgAudio
    MsgAudio* Clone(); // create new MsgAudio, take ref to DecodedAudio, copy size/offset
private:
    void Initialise(DecodedAudio* aDecodedAudio, Allocator<MsgPlayablePcm>& aAllocatorPlayable);
private: // from MsgAudio
    MsgAudio* Allocate();
    void SplitCompleted(MsgAudio& aRemaining);
private: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    DecodedAudio* iAudioData;
    Allocator<MsgPlayablePcm>* iAllocatorPlayable;
};

class MsgPlayableSilence;

class MsgSilence : public MsgAudio
{
    friend class MsgFactory;
public:
    MsgSilence(AllocatorBase& aAllocator);
    MsgPlayable* CreatePlayable(TUint aSampleRate, TUint aNumChannels); // removes ref
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

class MsgPlayable : public Msg
{
public:
    MsgPlayable* Split(TUint aBytes); // returns block after aAt
    void Add(MsgPlayable* aMsg); // combines MsgAudio instances so they report longer durations etc
    virtual MsgPlayable* Clone(); // create new MsgPlayable, copy size/offset
    TUint Bytes() const;
    virtual void Write(IWriter& aWriter) = 0; // calls RemoveRef on exit - FIXME: needs handling for ErrorWriter exception then
protected:
    MsgPlayable(AllocatorBase& aAllocator);
    void Initialise(TUint aSizeBytes, TUint aOffsetBytes, const Ramp& aRamp);
protected: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    virtual MsgPlayable* Allocate() = 0;
    virtual void SplitCompleted(MsgPlayable& aRemaining);
protected:
    MsgPlayable* iNextPlayable;
    TUint iSize; // Bytes
    TUint iOffset; // Bytes
    Ramp iRamp;
};

class MsgPlayablePcm : public MsgPlayable
{
    friend class MsgAudioPcm;
public:
    MsgPlayablePcm(AllocatorBase& aAllocator);
private:
    void Initialise(DecodedAudio* aDecodedAudio, TUint aSizeBytes, TUint aOffsetBytes, const Ramp& aRamp);
private: // from MsgPlayable
    MsgPlayable* Clone(); // create new MsgPlayable, take ref to DecodedAudio, copy size/offset
    void Write(IWriter& aWriter); // calls RemoveRef on exit - FIXME: needs handling for ErrorWriter exception then
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
    void Initialise(TUint aSizeBytes, const Ramp& aRamp);
private: // from MsgPlayable
    void Write(IWriter& aWriter); // calls RemoveRef on exit
    MsgPlayable* Allocate();
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

class MsgMetaText : public Msg
{
public:
    static const TUint kMaxBytes = 100; // FIXME
public:
    MsgMetaText(AllocatorBase& aAllocator);
private: // from Msg
    Msg* Process(IMsgProcessor& aProcessor);
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

class IMsgProcessor
{
public:
    virtual Msg* ProcessMsg(MsgAudioPcm* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgSilence* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgPlayable* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgTrack* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgMetaText* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgHalt* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgFlush* aMsg) = 0;
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

class MsgQueueJiffies
{
protected:
    MsgQueueJiffies();
    virtual ~MsgQueueJiffies();
    void DoEnqueue(Msg* aMsg);
    Msg* DoDequeue();
    void EnqueueAtHead(Msg* aMsg);
    TUint Jiffies() const;
private:
    void AddJiffies(TUint aJiffies);
    void RemoveJiffies(TUint aJiffies);
private:
    virtual void ProcessMsgIn(MsgAudioPcm* aMsg);
    virtual void ProcessMsgIn(MsgSilence* aMsg);
    virtual void ProcessMsgIn(MsgTrack* aMsg);
    virtual void ProcessMsgIn(MsgMetaText* aMsg);
    virtual void ProcessMsgIn(MsgHalt* aMsg);
    virtual void ProcessMsgIn(MsgFlush* aMsg);
    virtual Msg* ProcessMsgOut(MsgAudioPcm* aMsg);
    virtual Msg* ProcessMsgOut(MsgSilence* aMsg);
    virtual Msg* ProcessMsgOut(MsgTrack* aMsg);
    virtual Msg* ProcessMsgOut(MsgMetaText* aMsg);
    virtual Msg* ProcessMsgOut(MsgHalt* aMsg);
    virtual Msg* ProcessMsgOut(MsgFlush* aMsg);
private:
    class ProcessorQueueIn : public IMsgProcessor, private INonCopyable
    {
    public:
        ProcessorQueueIn(MsgQueueJiffies& aQueue);
    private:
        Msg* ProcessMsg(MsgAudioPcm* aMsg);
        Msg* ProcessMsg(MsgSilence* aMsg);
        Msg* ProcessMsg(MsgPlayable* aMsg);
        Msg* ProcessMsg(MsgTrack* aMsg);
        Msg* ProcessMsg(MsgMetaText* aMsg);
        Msg* ProcessMsg(MsgHalt* aMsg);
        Msg* ProcessMsg(MsgFlush* aMsg);
    private:
        MsgQueueJiffies& iQueue;
    };
    class ProcessorQueueOut : public IMsgProcessor, private INonCopyable
    {
    public:
        ProcessorQueueOut(MsgQueueJiffies& aQueue);
    private:
        Msg* ProcessMsg(MsgAudioPcm* aMsg);
        Msg* ProcessMsg(MsgSilence* aMsg);
        Msg* ProcessMsg(MsgPlayable* aMsg);
        Msg* ProcessMsg(MsgTrack* aMsg);
        Msg* ProcessMsg(MsgMetaText* aMsg);
        Msg* ProcessMsg(MsgHalt* aMsg);
        Msg* ProcessMsg(MsgFlush* aMsg);
    private:
        MsgQueueJiffies& iQueue;
    };
private:
    MsgQueue iQueue;
    TUint iJiffies;
};

class AutoRef : private INonCopyable
{
public:
    AutoRef(Msg& aMsg);
    ~AutoRef();
private:
    Msg& iMsg;
};

class MsgFactory // owned by Pipeline object
{
public:
    MsgFactory(Av::IInfoAggregator& aInfoAggregator,
               TUint aDecodedAudioCount, TUint aMsgAudioPcmCount, TUint aMsgSilenceCount,
               TUint aMsgPlayablePcmCount, TUint aMsgPlayableSilenceCount, TUint aMsgTrackCount,
               TUint aMsgMetaTextCount, TUint aMsgHaltCount, TUint aMsgFlushCount);
    //
    MsgAudioPcm* CreateMsgAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian);
    MsgSilence* CreateMsgSilence(TUint aSizeJiffies);
    MsgTrack* CreateMsgTrack();
    MsgMetaText* CreateMsgMetaText();
    MsgHalt* CreateMsgHalt();
    MsgFlush* CreateMsgFlush();
private:
    DecodedAudio* CreateDecodedAudio(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian);
private:
    Allocator<DecodedAudio> iAllocatorDecodedAudio;
    Allocator<MsgAudioPcm> iAllocatorMsgAudioPcm;
    Allocator<MsgSilence> iAllocatorMsgSilence;
    Allocator<MsgPlayablePcm> iAllocatorMsgPlayablePcm;
    Allocator<MsgPlayableSilence> iAllocatorMsgPlayableSilence;
    Allocator<MsgTrack> iAllocatorMsgTrack;
    Allocator<MsgMetaText> iAllocatorMsgMetaText;
    Allocator<MsgHalt> iAllocatorMsgHalt;
    Allocator<MsgFlush> iAllocatorMsgFlush;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_MSG
