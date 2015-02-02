#ifndef HEADER_PIPELINE_MSG
#define HEADER_PIPELINE_MSG

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/InfoProvider.h>

#include <limits.h>

EXCEPTION(SampleRateInvalid);

namespace OpenHome {
namespace Media {

class Allocated;

class AllocatorBase : private IInfoProvider
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
    AllocatorBase(const TChar* aName, TUint aNumCells, TUint aCellBytes, IInfoAggregator& aInfoAggregator);
    Allocated* DoAllocate();
private:
    Allocated* Read();
private: // from IInfoProvider
    void QueryInfo(const Brx& aQuery, IWriter& aWriter);
protected:
    FifoLiteDynamic<Allocated*> iFree;
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
    Allocator(const TChar* aName, TUint aNumCells, IInfoAggregator& aInfoAggregator);
    virtual ~Allocator();
    T* Allocate();
};

template <class T> Allocator<T>::Allocator(const TChar* aName, TUint aNumCells, IInfoAggregator& aInfoAggregator)
    : AllocatorBase(aName, aNumCells, sizeof(T), aInfoAggregator)
{
    for (TUint i=0; i<aNumCells; i++) {
        iFree.Write(new T(*this));
    }
}

template <class T> Allocator<T>::~Allocator()
{
}

template <class T> T* Allocator<T>::Allocate()
{
    return static_cast<T*>(DoAllocate());
}

class Logger;

class Allocated
{
    friend class AllocatorBase;
    friend class SuiteAllocator;
    friend class Logger;
public:
    void AddRef();
    void RemoveRef();
protected:
    Allocated(AllocatorBase& aAllocator);
protected:
    virtual ~Allocated();
private:
    virtual void RefAdded();
    virtual void RefRemoved();
    virtual void Clear();
protected:
    AllocatorBase& iAllocator;
    mutable Mutex iLock;
private:
    TUint iRefCount;
};

class EncodedAudio : public Allocated
{
    friend class MsgFactory;
public:
    static const TUint kMaxBytes = 9 * 1024; // 9k buffer required for Songcast; other codecs are fine with 6k
public:
    EncodedAudio(AllocatorBase& aAllocator);
    const TByte* Ptr(TUint aBytes) const;
    TUint Bytes() const;
    TUint Append(const Brx& aData);
private:
    void Construct(const Brx& aData);
private: // from Allocated
    void Clear();
private:
    Bws<kMaxBytes> iData;
};

enum EMediaDataEndian
{
    EMediaDataEndianInvalid
   ,EMediaDataEndianLittle
   ,EMediaDataEndianBig
};

/**
 * Provides the pipeline's unit of timing.
 *
 * A single sample at any supported rate is representable as an integer number of jiffies.
 */
class Jiffies
{
public:
    static const TUint kPerSecond = 56448000; // lcm(384000, 352800)
    static const TUint kPerMs = kPerSecond / 1000;
public:
    static TBool IsValidSampleRate(TUint aSampleRate);
    static TUint JiffiesPerSample(TUint aSampleRate);
    static TUint BytesFromJiffies(TUint& aJiffies, TUint aJiffiesPerSample, TUint aNumChannels, TUint aBytesPerSubsample);
    static TUint ToSongcastTime(TUint aJiffies, TUint aSampleRate);
    static TUint FromSongcastTime(TUint64 aSongcastTime, TUint aSampleRate);
private:
    static TUint SongcastTicksPerSecond(TUint aSampleRate);
private:
    //Number of jiffies per sample
    static const TUint kJiffies7350   = kPerSecond / 7350;
    static const TUint kJiffies8000   = kPerSecond / 8000;
    static const TUint kJiffies11025  = kPerSecond / 11025;
    static const TUint kJiffies12000  = kPerSecond / 12000;
    static const TUint kJiffies14700  = kPerSecond / 14700;
    static const TUint kJiffies16000  = kPerSecond / 16000;
    static const TUint kJiffies22050  = kPerSecond / 22050;
    static const TUint kJiffies24000  = kPerSecond / 24000;
    static const TUint kJiffies29400  = kPerSecond / 29400;
    static const TUint kJiffies32000  = kPerSecond / 32000;
    static const TUint kJiffies44100  = kPerSecond / 44100;
    static const TUint kJiffies48000  = kPerSecond / 48000;
    static const TUint kJiffies88200  = kPerSecond / 88200;
    static const TUint kJiffies96000  = kPerSecond / 96000;
    static const TUint kJiffies176400 = kPerSecond / 176400;
    static const TUint kJiffies192000 = kPerSecond / 192000;

    static const TUint kSongcastTicksPerSec44k = 44100 * 256;
    static const TUint kSongcastTicksPerSec48k = 48000 * 256;
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
    void Aggregate(DecodedAudio& aDecodedAudio);
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
    static const TUint kMax = 1<<30;
    static const TUint kMin = 0;
    enum EDirection
    {
        ENone
       ,EUp
       ,EDown
    };
public:
    Ramp();
    void Reset();
    TBool Set(TUint aStart, TUint aFragmentSize, TUint aRemainingDuration, EDirection aDirection, Ramp& aSplit, TUint& aSplitPos); // returns true iff aSplit is set
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


static const TUint kModeMaxBytes          = 32;
static const TUint kTrackUriMaxBytes      = 1024;
static const TUint kTrackMetaDataMaxBytes = 5 * 1024;

typedef Bws<kModeMaxBytes>          BwsMode;
typedef Bws<kTrackUriMaxBytes>      BwsTrackUri;
typedef Bws<kTrackMetaDataMaxBytes> BwsTrackMetaData;

class Track : public Allocated
{
    friend class TrackFactory;
public:
    static const TUint kIdNone = 0;
public:
    Track(AllocatorBase& aAllocator);
    const Brx& Uri() const;
    const Brx& MetaData() const;
    TUint Id() const;
private:
    void Initialise(const Brx& aUri, const Brx& aMetaData, TUint aId);
private: // from Allocated
    void Clear();
private:
    BwsTrackUri iUri;
    BwsTrackMetaData iMetaData;
    TUint iId;
};

class IClockPuller;

class MsgMode : public Msg
{
    friend class MsgFactory;
public:
    MsgMode(AllocatorBase& aAllocator);
    const Brx& Mode() const;
    TBool SupportsLatency() const;
    TBool IsRealTime() const;
    IClockPuller* ClockPuller() const;
private:
    void Initialise(const Brx& aMode, TBool aSupportsLatency, TBool aIsRealTime, IClockPuller* aClockPuller);
private: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    BwsMode iMode;
    TBool iSupportsLatency;
    TBool iIsRealTime;
    IClockPuller* iClockPuller;
};

class MsgSession : public Msg
{
public:
    MsgSession(AllocatorBase& aAllocator);
private: // from Msg
    Msg* Process(IMsgProcessor& aProcessor);
};

class MsgTrack : public Msg
{
    friend class MsgFactory;
public:
    static const TUint kMaxUriBytes = 1024;
public:
    MsgTrack(AllocatorBase& aAllocator);
    Media::Track& Track() const;
    TUint IdPipeline() const;
private:
    void Initialise(Media::Track& aTrack, TUint aIdPipeline);
private: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    Media::Track* iTrack;
    TUint iIdPipeline;
};

class MsgDelay : public Msg
{
    friend class MsgFactory;
public:
    MsgDelay(AllocatorBase& aAllocator);
    TUint DelayJiffies() const;
private:
    void Initialise(TUint aDelayJiffies);
private: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    TUint iDelayJiffies;
};

class IStreamHandler;

class PcmStreamInfo
{
public:
    PcmStreamInfo();
    void Set(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, EMediaDataEndian aEndian, TUint64 aStartSample = 0);
    void Clear();
    TUint BitDepth() const;
    TUint SampleRate() const;
    TUint NumChannels() const;
    EMediaDataEndian Endian() const;
    TUint64 StartSample() const;
private:
    TUint iBitDepth;
    TUint iSampleRate;
    TUint iNumChannels;
    EMediaDataEndian iEndian;
    TUint64 iStartSample;
};

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
    TUint64 TotalBytes() const;
    TUint StreamId() const;
    TBool Seekable() const;
    TBool Live() const;
    IStreamHandler* StreamHandler() const;
    TBool RawPcm() const;
    const PcmStreamInfo& PcmStream() const;
private:
    void Initialise(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint aStreamId, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler);
    void Initialise(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint aStreamId, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler, const PcmStreamInfo& aPcmStream);
private: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    Bws<kMaxUriBytes> iUri;
    Bws<kMaxMetaTextBytes> iMetaText;
    TUint64 iTotalBytes;
    TUint iStreamId;
    TBool iSeekable;
    TBool iLive;
    TBool iRawPcm;
    IStreamHandler* iStreamHandler;
    PcmStreamInfo iPcmStreamInfo;
};

class MsgAudioEncoded : public Msg
{
    friend class MsgFactory;
public:
    MsgAudioEncoded(AllocatorBase& aAllocator);
    MsgAudioEncoded* Split(TUint aBytes); // returns block after aBytes
    void Add(MsgAudioEncoded* aMsg); // combines MsgAudioEncoded instances so they report larger sizes etc
    TUint Append(const Brx& aData); // Appends a Data to existing msg.  Returns index into aData where copying terminated.
    TUint Bytes() const;
    void CopyTo(TByte* aPtr);
    MsgAudioEncoded* Clone();
private:
    void Initialise(EncodedAudio* aEncodedAudio);
private: // from Msg
    void RefAdded();
    void RefRemoved();
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    MsgAudioEncoded* iNextAudio;
    TUint iSize; // Bytes
    TUint iOffset; // Bytes
    EncodedAudio* iAudioData;
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

/**
 * Indicates that a break in audio may follow and that this is expected.
 *
 * Audio can be assumed to have already ramped down (either naturally at the end of a
 * stream) or manually from an upstream pipeline element.
 */
class MsgHalt : public Msg
{
    friend class MsgFactory;
public:
    static const TUint kIdNone    = 0;
    static const TUint kIdInvalid = UINT_MAX;
public:
    MsgHalt(AllocatorBase& aAllocator);
    TUint Id() const;
private:
    void Initialise(TUint aId);
private: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    TUint iId;
};

class MsgFlush : public Msg
{
public:
    static const TUint kIdInvalid = 0;
public:
    MsgFlush(AllocatorBase& aAllocator);
    void Initialise(TUint aId);
    TUint Id() const;
private: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    TUint iId;
};

class MsgWait : public Msg
{
public:
    MsgWait(AllocatorBase& aAllocator);
private: // from Msg
    Msg* Process(IMsgProcessor& aProcessor);
};

class DecodedStreamInfo
{
    friend class MsgDecodedStream;
public:
    static const TUint kMaxCodecNameBytes = 32;
public:
    TUint StreamId() const { return iStreamId; }
    TUint BitRate() const { return iBitRate; }
    TUint BitDepth() const { return iBitDepth; }
    TUint SampleRate() const { return iSampleRate; }
    TUint NumChannels() const { return iNumChannels; }
    const Brx& CodecName() const { return iCodecName; }
    TUint64 TrackLength() const { return iTrackLength; }
    TUint64 SampleStart() const { return iSampleStart; }
    TBool Lossless() const { return iLossless; }
    TBool Seekable() const { return iSeekable; }
    TBool Live() const { return iLive; }
    IStreamHandler* StreamHandler() const { return iStreamHandler;}
private:
    DecodedStreamInfo();
    void Set(TUint aStreamId, TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler);
private:
    TUint iStreamId;
    TUint iBitRate;
    TUint iBitDepth;
    TUint iSampleRate;
    TUint iNumChannels;
    Bws<kMaxCodecNameBytes> iCodecName;
    TUint64 iTrackLength; // jiffies
    TUint64 iSampleStart;
    TBool iLossless;
    TBool iSeekable;
    TBool iLive;
    IStreamHandler* iStreamHandler;
};

/**
 * Indicates the start of a new audio stream.
 */
class MsgDecodedStream : public Msg
{
    friend class MsgFactory;
public:
    MsgDecodedStream(AllocatorBase& aAllocator);
    const DecodedStreamInfo& StreamInfo() const;
private:
    void Initialise(TUint aStreamId, TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler);
private: // from Msg
    void Clear();
    Msg* Process(IMsgProcessor& aProcessor);
private:
    DecodedStreamInfo iStreamInfo;
};

class MsgAudio : public Msg
{
    friend class MsgFactory;
public:
    MsgAudio* Split(TUint aJiffies); // returns block after aAt
    void Add(MsgAudio* aMsg); // combines MsgAudio instances so they report longer durations etc
    virtual MsgAudio* Clone(); // create new MsgAudio, copy size/offset
    TUint Jiffies() const;
    TUint SetRamp(TUint aStart, TUint& aRemainingDuration, Ramp::EDirection aDirection, MsgAudio*& aSplit); // returns iRamp.End()
    const Media::Ramp& Ramp() const;
protected:
    MsgAudio(AllocatorBase& aAllocator);
    void Initialise();
    void Clear();
private:
    virtual MsgAudio* Allocate() = 0;
    MsgAudio* DoSplit(TUint aJiffies);
    virtual void SplitCompleted(MsgAudio& aRemaining);
protected:
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
    void Aggregate(MsgAudioPcm& aMsg); // append aMsg to the end of this msg, removes ref on aMsg
    TBool TryGetTimestamps(TUint& aNetwork, TUint& aRx);
public: // from MsgAudio
    MsgAudio* Clone(); // create new MsgAudio, take ref to DecodedAudio, copy size/offset
private:
    void Initialise(DecodedAudio* aDecodedAudio, TUint64 aTrackOffset, Allocator<MsgPlayablePcm>& aAllocatorPlayable);
    void SetTimestamps(TUint aRx, TUint aNetwork);
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
    TBool iTimestamped;
    TUint iRxTimestamp;
    TUint iNetworkTimestamp;
};

class MsgPlayableSilence;

class MsgSilence : public MsgAudio
{
    friend class MsgFactory;
public:
    MsgSilence(AllocatorBase& aAllocator);
    MsgPlayable* CreatePlayable(TUint aSampleRate, TUint aBitDepth, TUint aNumChannels); // removes ref
public: // from MsgAudio
    MsgAudio* Clone();
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

/**
 * Holds decoded audio and can write it to a stream.
 *
 * MsgAudioPcm and MsgSilence can be converted into this.
 */
class MsgPlayable : public Msg
{
public:
    MsgPlayable* Split(TUint aBytes); // returns block after aBytes
    void Add(MsgPlayable* aMsg); // combines MsgPlayable instances so they report longer durations etc
    virtual MsgPlayable* Clone(); // create new MsgPlayable, copy size/offset
    TUint Bytes() const;
    const Media::Ramp& Ramp() const;
    /**
     * Extract pcm data from this msg.
     *
     * Any ramp is applied at the same time.
     *
     * @param[in] aProcessor       PCM data is returned via this interface.  Writing the data
     *                             in a blocks is preferred.  Data may be written sample at a
     *                             time if requested by the processor (say because it'll insert
     *                             padding around each sample) or if a ramp is being applied.
     */
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

/**
 * Indicates that the pipeline is shutting down.
 *
 * Do not attempt to Pull() further messages after receiving this.
 */
class MsgQuit : public Msg
{
public:
    MsgQuit(AllocatorBase& aAllocator);
private: // from Msg
    Msg* Process(IMsgProcessor& aProcessor);
};

/**
 * Utility to allow pipeline elements or clients to determine the type of Msg they've been passed.
 *
 * Derive from IMsgProcessor than call msg->Process(*this) to have the ProcessMsg overload for
 * the appropriate type called.
 */
class IMsgProcessor
{
public:
    virtual ~IMsgProcessor() {}
    virtual Msg* ProcessMsg(MsgMode* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgSession* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgTrack* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgDelay* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgEncodedStream* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgAudioEncoded* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgMetaText* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgHalt* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgFlush* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgWait* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgDecodedStream* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgAudioPcm* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgSilence* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgPlayable* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgQuit* aMsg) = 0;
};

/**
 * Used to retrieve pcm audio data from a MsgPlayable
 */
class IPcmProcessor
{
public:
    virtual ~IPcmProcessor() {}
    /**
     * Called once per call to MsgPlayable::Read.
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
     * Called once per call to MsgPlayable::Read.
     *
     * No more calls to ProcessFragment or ProcessSample will be made after this.
     */
    virtual void EndBlock() = 0;
};

class StreamId
{
public:
    StreamId();
    void SetTrack(TUint aId);
    void SetStream(TUint aId);
    TBool operator ==(const StreamId& aId) const;
    TBool operator !=(const StreamId& aId) const { return !(*this==aId); }
    TUint IdPipeline() const { return iTrackId; }
    TUint IdStream() const { return iStreamId; }
private:
    TUint iTrackId;
    TUint iStreamId;
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
    void Clear();
    TUint NumMsgs() const; // test/debug use only
private:
    void CheckMsgNotQueued(Msg* aMsg) const;
    Msg* DequeueLocked();
private:
    mutable Mutex iLock;
    Semaphore iSem;
    Msg* iHead;
    Msg* iTail;
    TUint iNumMsgs;
};

class MsgReservoir
{
protected:
    MsgReservoir();
    virtual ~MsgReservoir();
    void DoEnqueue(Msg* aMsg);
    Msg* DoDequeue();
    void EnqueueAtHead(Msg* aMsg);
    TUint Jiffies() const;
    TUint EncodedBytes() const;
    TBool IsEmpty() const;
    TUint SessionCount() const;
    TUint EncodedStreamCount() const;
    TUint DecodedStreamCount() const;
private:
    void Add(TUint& aValue, TUint aAdded);
    void Remove(TUint& aValue, TUint aRemoved);
private:
    virtual void ProcessMsgIn(MsgMode* aMsg);
    virtual void ProcessMsgIn(MsgSession* aMsg);
    virtual void ProcessMsgIn(MsgTrack* aMsg);
    virtual void ProcessMsgIn(MsgDelay* aMsg);
    virtual void ProcessMsgIn(MsgEncodedStream* aMsg);
    virtual void ProcessMsgIn(MsgAudioEncoded* aMsg);
    virtual void ProcessMsgIn(MsgMetaText* aMsg);
    virtual void ProcessMsgIn(MsgHalt* aMsg);
    virtual void ProcessMsgIn(MsgFlush* aMsg);
    virtual void ProcessMsgIn(MsgWait* aMsg);
    virtual void ProcessMsgIn(MsgDecodedStream* aMsg);
    virtual void ProcessMsgIn(MsgAudioPcm* aMsg);
    virtual void ProcessMsgIn(MsgSilence* aMsg);
    virtual void ProcessMsgIn(MsgQuit* aMsg);
    virtual Msg* ProcessMsgOut(MsgMode* aMsg);
    virtual Msg* ProcessMsgOut(MsgSession* aMsg);
    virtual Msg* ProcessMsgOut(MsgTrack* aMsg);
    virtual Msg* ProcessMsgOut(MsgDelay* aMsg);
    virtual Msg* ProcessMsgOut(MsgEncodedStream* aMsg);
    virtual Msg* ProcessMsgOut(MsgAudioEncoded* aMsg);
    virtual Msg* ProcessMsgOut(MsgMetaText* aMsg);
    virtual Msg* ProcessMsgOut(MsgHalt* aMsg);
    virtual Msg* ProcessMsgOut(MsgFlush* aMsg);
    virtual Msg* ProcessMsgOut(MsgWait* aMsg);
    virtual Msg* ProcessMsgOut(MsgDecodedStream* aMsg);
    virtual Msg* ProcessMsgOut(MsgAudioPcm* aMsg);
    virtual Msg* ProcessMsgOut(MsgSilence* aMsg);
    virtual Msg* ProcessMsgOut(MsgQuit* aMsg);
private:
    class ProcessorQueueIn : public IMsgProcessor, private INonCopyable
    {
    public:
        ProcessorQueueIn(MsgReservoir& aQueue);
    private:
        Msg* ProcessMsg(MsgMode* aMsg) override;
        Msg* ProcessMsg(MsgSession* aMsg) override;
        Msg* ProcessMsg(MsgTrack* aMsg) override;
        Msg* ProcessMsg(MsgDelay* aMsg) override;
        Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
        Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
        Msg* ProcessMsg(MsgMetaText* aMsg) override;
        Msg* ProcessMsg(MsgHalt* aMsg) override;
        Msg* ProcessMsg(MsgFlush* aMsg) override;
        Msg* ProcessMsg(MsgWait* aMsg) override;
        Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
        Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
        Msg* ProcessMsg(MsgSilence* aMsg) override;
        Msg* ProcessMsg(MsgPlayable* aMsg) override;
        Msg* ProcessMsg(MsgQuit* aMsg) override;
    private:
        MsgReservoir& iQueue;
    };
    class ProcessorQueueOut : public IMsgProcessor, private INonCopyable
    {
    public:
        ProcessorQueueOut(MsgReservoir& aQueue);
    private:
        Msg* ProcessMsg(MsgMode* aMsg) override;
        Msg* ProcessMsg(MsgSession* aMsg) override;
        Msg* ProcessMsg(MsgTrack* aMsg) override;
        Msg* ProcessMsg(MsgDelay* aMsg) override;
        Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
        Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
        Msg* ProcessMsg(MsgMetaText* aMsg) override;
        Msg* ProcessMsg(MsgHalt* aMsg) override;
        Msg* ProcessMsg(MsgFlush* aMsg) override;
        Msg* ProcessMsg(MsgWait* aMsg) override;
        Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
        Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
        Msg* ProcessMsg(MsgSilence* aMsg) override;
        Msg* ProcessMsg(MsgPlayable* aMsg) override;
        Msg* ProcessMsg(MsgQuit* aMsg) override;
    private:
        MsgReservoir& iQueue;
    };
private:
    mutable Mutex iLock;
    MsgQueue iQueue;
    TUint iEncodedBytes;
    TUint iJiffies;
    TUint iSessionCount;
    TUint iEncodedStreamCount;
    TUint iDecodedStreamCount;
};

// removes ref on destruction.  Does NOT claim ref on construction.
class AutoAllocatedRef : private INonCopyable
{
public:
    AutoAllocatedRef(Allocated* aAllocated);
    ~AutoAllocatedRef();
private:
    Allocated* iAllocated;
};

/**
 * Interface to the start of the pipeline.  Use this to push data into the pipeline.
 */
class ISupply
{
public:
    virtual ~ISupply() {}
    /**
     * Inform the pipeline about a discontinuity in audio.
     */
    virtual void OutputSession() = 0;
    /**
     * Inform the pipeline that a new track is starting.
     *
     * @param[in] aTrack           Track about to be played.
     * @param[in] aTrackId         Unique identifier for this particular play of this track.
     */
    virtual void OutputTrack(Track& aTrack, TUint aTrackId) = 0;
    /**
     * Apply a delay to subsequent audio in this stream.
     *
     * Any delay is calculated relative to previous delays for this session.
     * i.e. if you output the same delay twice, the second call has no effect.
     *
     * @param[in] aJiffies         Delay in Jiffies.
     */
    virtual void OutputDelay(TUint aJiffies) = 0;
    /**
     * Inform the pipeline that a new audio stream is starting
     *
     * @param[in] aUri             Uri of the stream
     * @param[in] aTotalBytes      Length in bytes of the stream
     * @param[in] aSeekable        Whether the stream supports Seek requests
     * @param[in] aLive            Whether the stream is being broadcast live (and won't support seeking)
     * @param[in] aStreamHandler   Stream handler.  Used to allow pipeline elements to communicate upstream.
     * @param[in] aStreamId        Identifier for the pending stream.  Unique within a single track only.
     */
    virtual void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId) = 0;
    /**
     * Inform the pipeline that a new (raw PCM) audio stream is starting
     *
     * @param[in] aUri             Uri of the stream
     * @param[in] aTotalBytes      Length in bytes of the stream
     * @param[in] aSeekable        Whether the stream supports Seek requests
     * @param[in] aLive            Whether the stream is being broadcast live (and won't support seeking)
     * @param[in] aStreamHandler   Stream handler.  Used to allow pipeline elements to communicate upstream.
     * @param[in] aStreamId        Identifier for the pending stream.  Unique within a single track only.
     * @param[in] aBitDepth        Number of bits per sample per channel.
     * @param[in] aSampleRate      Number of samples per second.
     * @param[in] aNumChannels     Number of channels.
     */
    virtual void OutputPcmStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId, const PcmStreamInfo& aPcmStream) = 0;
    /**
     * Push a block of encoded audio into the pipeline.
     *
     * Data is copied into the pipeline.  The caller is free to reuse its buffer.
     *
     * @param[in] aData            Encoded audio.  Must be <= EncodedAudio::kMaxBytes
     */
    virtual void OutputData(const Brx& aData) = 0;
    /**
     * Push metadata, describing the current stream, into the pipeline.
     *
     * Use of this is optional.  The pipeline will treat the data as opaque and will merely
     * pass it on to any observers.  Each call to this should pass a complete block of
     * metadata that is capable of being interpreted independantly of any other.
     *
     * @param[in] aMetadata        Metadata.  Must be <= MsgMetaText::kMaxBytes
     */
    virtual void OutputMetadata(const Brx& aMetadata) = 0;
    /**
     * Push a Flush command into the pipeline.
     *
     * This is typically called after a call to TrySeek() or TryStop() from IStreamHandler.
     *
     * @param[in] aFlushId         Unique identifier for this command.  Will normally have
     *                             earlier been returned by TrySeek() or TryStop().
     */
    virtual void OutputFlush(TUint aFlushId) = 0;
    /**
     * Push a Wait command into the pipeline.
     *
     * This causes the pipeline to report state Waiting (no audio, this isn't unexpected)
     * rather than Buffering (no audio, error) until OutputData() or OutputStream() is next
     * called.
     */
    virtual void OutputWait() = 0;
};

class IFlushIdProvider
{
public:
    virtual ~IFlushIdProvider() {}
    virtual TUint NextFlushId() = 0;
};

enum EStreamPlay
{
    ePlayYes
   ,ePlayNo
   ,ePlayLater
};
extern const TChar* kStreamPlayNames[];

class IStreamPlayObserver
{
public:
    virtual ~IStreamPlayObserver() {}
    virtual void NotifyTrackFailed(TUint aTrackId) = 0;
    virtual void NotifyStreamPlayStatus(TUint aTrackId, TUint aStreamId, EStreamPlay aStatus) = 0;
};

class IPipelineIdProvider
{
public:
    static const TUint kTrackIdInvalid = 0;
    static const TUint kStreamIdInvalid = 0;
public:
    virtual ~IPipelineIdProvider() {}
    virtual TUint NextTrackId() = 0;
    virtual TUint NextStreamId() = 0;
    virtual EStreamPlay OkToPlay(TUint aStreamId) = 0;
};

class IPipelineIdManager
{
public:
    virtual ~IPipelineIdManager() {}
    virtual void InvalidateAt(TUint aId) = 0;
    virtual void InvalidateAfter(TUint aId) = 0;
    virtual void InvalidatePending() = 0;
    virtual void InvalidateAll() = 0;
};

class IPipelineIdTracker
{
public:
    virtual ~IPipelineIdTracker() {}
    virtual void AddStream(TUint aId, TUint aStreamId, TBool aPlayNow) = 0;
};

/**
 * Interface to allow pipeline elements to request action from an upstream component
 */
class IStreamHandler
{
public:
    virtual ~IStreamHandler() {}
    /**
     * Request permission to play a stream.
     *
     * @param[in] aStreamId        Unique stream identifier.
     *
     * @return  Whether the stream can be played.  One of
     *            ePlayYes   - play the stream immediately.
     *            ePlayNo    - do not play the stream.  Discard its contents immediately.
     *            ePlayLater - play the stream later.  Do not play yet but also do not discard.
     */
    virtual EStreamPlay OkToPlay(TUint aStreamId) = 0;
    /**
     * Attempt to seek inside the currently playing stream.
     *
     * This may be called from a different thread.  The implementor is responsible for any synchronisation.
     * Note that this may fail if the stream is non-seekable or the entire stream is
     * already in the pipeline
     *
     * @param[in] aStreamId        Stream identifier, unique in the context of the current track only.
     * @param[in] aOffset          Byte offset into the stream.
     *
     * @return  Flush id.  MsgFlush::kIdInvalid if the seek request failed.
     *          Any other value indicates success.  The code which issues the seek request
     *          should discard data until it pulls a MsgFlush with this id.
     */
    virtual TUint TrySeek(TUint aStreamId, TUint64 aOffset) = 0;
    /**
     * Attempt to stop delivery of the currently playing stream.
     *
     * This may be called from a different thread.  The implementor is responsible for any synchronisation.
     * Note that this may report failure if the entire stream is already in the pipeline.
     *
     * @param[in] aStreamId        Stream identifier, unique in the context of the current track only.
     *
     * @return  Flush id.  MsgFlush::kIdInvalid if the stop request failed.
     *          Any other value indicates success.  The code which issues the seek request
     *          should discard data until it pulls a MsgFlush with this id.
     */
    virtual TUint TryStop(TUint aStreamId) = 0;
    /**
     * Read a block of data out of band, without affecting the state of the current stream.
     *
     * This may be called from a different thread.  The implementor is responsible for any synchronisation.
     * This is relatively inefficient so should be used with care.  (It is intended for use
     * during format recognition for a new stream; more frequent use would be questionable.)
     *
     * @param[in] aWriter          Interface used to return the requested data.
     * @param[in] aStreamId        Stream identifier, unique in the context of the current track only.
     * @param[in] aOffset          Byte offset to start reading from
     * @param[in] aBytes           Number of bytes to read
     *
     * @return  true if exactly aBytes were read; false otherwise
     */
    virtual TBool TryGet(IWriter& aWriter, TUint aStreamId, TUint64 aOffset, TUint aBytes) = 0; // return false if we failed to get aBytes
    /**
     * Inform interested parties of an unexpected break in audio.
     *
     * Sources which are sensitive to latency may need to restart.
     * This may be called from a different thread.  The implementor is responsible for any synchronisation.
     *
     * @param[in] aMode            Reported by the MsgMode which preceded the stream which dropped out.
     *                             i.e. identifier for the UriProvider associated with this stream
     * @param[in] aStreamId        Stream identifier, unique in the context of the current track only.
     */
    virtual void NotifyStarving(const Brx& aMode, TUint aStreamId) = 0;
};

class ISeekObserver
{
public:
    virtual void NotifySeekComplete(TUint aHandle, TUint aFlushId) = 0;
};

class ISeeker
{
public:
    static const TUint kHandleError = UINT_MAX;
public:
    virtual void StartSeek(TUint aStreamId, TUint aSecondsAbsolute, ISeekObserver& aObserver, TUint& aHandle) = 0; // aHandle will be set to value that is later passed to NotifySeekComplete.  Or kHandleError.
};

class ISeekRestreamer
{
public:
    virtual ~ISeekRestreamer() {}
    virtual TUint SeekRestream(const Brx& aMode, TUint aTrackId) = 0; // returns flush id that'll preceed restreamed track
};

class IStopper
{
public:
    virtual ~IStopper() {}
    virtual void RemoveStream(TUint aStreamId) = 0;
};

class IPipelineElementUpstream
{
public:
    virtual ~IPipelineElementUpstream() {}
    virtual Msg* Pull() = 0;
};

class IPipelineElementDownstream
{
public:
    virtual ~IPipelineElementDownstream() {}
    virtual void Push(Msg* aMsg) = 0;
};

class TrackFactory
{
public:
    TrackFactory(IInfoAggregator& aInfoAggregator, TUint aTrackCount);
    Track* CreateTrack(const Brx& aUri, const Brx& aMetaData);
private:
    Allocator<Track> iAllocatorTrack;
    Mutex iLock;
    TUint iNextId;
};

class MsgFactory
{
public:
    MsgFactory(IInfoAggregator& aInfoAggregator,
               TUint aEncodedAudioCount, TUint aMsgAudioEncodedCount, 
               TUint aDecodedAudioCount, TUint aMsgAudioPcmCount, TUint aMsgSilenceCount,
               TUint aMsgPlayablePcmCount, TUint aMsgPlayableSilenceCount, TUint aMsgDecodedStreamCount,
               TUint aMsgTrackCount, TUint aMsgEncodedStreamCount, TUint aMsgMetaTextCount,
               TUint aMsgHaltCount, TUint aMsgFlushCount, TUint aMsgWaitCount,
               TUint aMsgModeCount, TUint aMsgSessionCount, TUint aMsgDelayCount, TUint aMsgQuitCount);
    //
    MsgMode* CreateMsgMode(const Brx& aMode, TBool aSupportsLatency, TBool aRealTime, IClockPuller* aClockPuller);
    MsgSession* CreateMsgSession();
    MsgTrack* CreateMsgTrack(Media::Track& aTrack, TUint aIdPipeline);
    MsgDelay* CreateMsgDelay(TUint aDelayJiffies);
    MsgEncodedStream* CreateMsgEncodedStream(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint aStreamId, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler);
    MsgEncodedStream* CreateMsgEncodedStream(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint aStreamId, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler, const PcmStreamInfo& aPcmStream);
    MsgAudioEncoded* CreateMsgAudioEncoded(const Brx& aData);
    MsgMetaText* CreateMsgMetaText(const Brx& aMetaText);
    MsgHalt* CreateMsgHalt(TUint aId = MsgHalt::kIdNone);
    MsgFlush* CreateMsgFlush(TUint aId);
    MsgWait* CreateMsgWait();
    MsgDecodedStream* CreateMsgDecodedStream(TUint aStreamId, TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler);
    MsgAudioPcm* CreateMsgAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset);
    MsgAudioPcm* CreateMsgAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset, TUint aRxTimestamp, TUint aNetworkTimestamp);
    MsgSilence* CreateMsgSilence(TUint aSizeJiffies);
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
    Allocator<MsgDecodedStream> iAllocatorMsgDecodedStream;
    Allocator<MsgTrack> iAllocatorMsgTrack;
    Allocator<MsgEncodedStream> iAllocatorMsgEncodedStream;
    Allocator<MsgMetaText> iAllocatorMsgMetaText;
    Allocator<MsgHalt> iAllocatorMsgHalt;
    Allocator<MsgFlush> iAllocatorMsgFlush;
    Allocator<MsgWait> iAllocatorMsgWait;
    Allocator<MsgMode> iAllocatorMsgMode;
    Allocator<MsgSession> iAllocatorMsgSession;
    Allocator<MsgDelay> iAllocatorMsgDelay;
    Allocator<MsgQuit> iAllocatorMsgQuit;
    TUint iNextFlushId;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_MSG
