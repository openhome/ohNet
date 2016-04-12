#pragma once

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
EXCEPTION(SampleRateUnsupported);

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

enum class AudioDataEndian
{
    Invalid,
    Little,
    Big
};

class AudioData : public Allocated
{
public: 
    static const TUint kMaxBytes = 6 * 1024;
public:
    AudioData(AllocatorBase& aAllocator);
    const TByte* Ptr(TUint aOffsetBytes) const;
    TUint Bytes() const;
private: // from Allocated
    void Clear() override;
protected:
    Bws<kMaxBytes> iData;
};

class EncodedAudio : public AudioData
{
    friend class MsgFactory;
public:
    TUint Append(const Brx& aData); // returns number of bytes appended
private:
    EncodedAudio(AllocatorBase& aAllocator);
    void Construct(const Brx& aData);
};

class DecodedAudio : public AudioData
{
    friend class MsgFactory;
public:
    static const TUint kMaxNumChannels = 8;
public:
    void Aggregate(DecodedAudio& aDecodedAudio);
private:
    DecodedAudio(AllocatorBase& aAllocator);
    void Construct(const Brx& aData, TUint aBitDepth, AudioDataEndian aEndian);
    static void CopyToBigEndian16(const Brx& aData, TByte* aDest);
    static void CopyToBigEndian24(const Brx& aData, TByte* aDest);
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
    static TUint PerSample(TUint aSampleRate);
    static TUint ToBytes(TUint& aJiffies, TUint aJiffiesPerSample, TUint aNumChannels, TUint aBytesPerSubsample);
    static void RoundDown(TUint& aJiffies, TUint aSampleRate);
    static void RoundUp(TUint& aJiffies, TUint aSampleRate);
    static TUint ToSongcastTime(TUint aJiffies, TUint aSampleRate);
    static TUint64 FromSongcastTime(TUint64 aSongcastTime, TUint aSampleRate);
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
    friend class SuiteRamp;
public:
    static const TUint kMax = 1<<30;
    static const TUint kMin = 0;
    enum EDirection
    {
        ENone
       ,EUp
       ,EDown
       ,EMute
    };
public:
    Ramp();
    void Reset();
    TBool Set(TUint aStart, TUint aFragmentSize, TUint aRemainingDuration, EDirection aDirection, Ramp& aSplit, TUint& aSplitPos); // returns true iff aSplit is set
    void SetMuted();
    Ramp Split(TUint aNewSize, TUint aCurrentSize);
    TUint Start() const { return iStart; }
    TUint End() const { return iEnd; }
    EDirection Direction() const { return iDirection; }
    TBool IsEnabled() const { return iEnabled; }
private:
    void SelectLowerRampPoints(TUint aRequestedStart, TUint aRequestedEnd);
    void Validate(const TChar* aId);
    TBool DoValidate();
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
    static TUint MedianMultiplier(const Media::Ramp& aRamp);
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
    void Clear() override;
private:
    BwsTrackUri iUri;
    BwsTrackMetaData iMetaData;
    TUint iId;
};

class MsgMode;
class ModeInfo
{
    friend class MsgMode;
public:
    TBool SupportsLatency() const { return iSupportsLatency; }
    TBool IsRealTime() const      { return iRealTime; }
    TBool SupportsNext() const    { return iSupportsNext; }
    TBool SupportsPrev() const    { return iSupportsPrev; }
private:
    ModeInfo();
    void Set(TBool aSupportsLatency, TBool aRealTime, TBool aSupportsNext, TBool aSupportsPrev);
    void Clear();
private:
    TBool iSupportsLatency;
    TBool iRealTime;
    TBool iSupportsNext;
    TBool iSupportsPrev;
};

class IClockPullerReservoir;
class IClockPullerTimestamp;

class ModeClockPullers
{
public:
    ModeClockPullers();
    ModeClockPullers(IClockPullerReservoir* aReservoirLeft,
                     IClockPullerReservoir* aReservoirRight,
                     IClockPullerTimestamp* aTimestamp);
    IClockPullerReservoir* ReservoirLeft() const;
    IClockPullerReservoir* ReservoirRight() const;
    IClockPullerTimestamp* Timestamp() const;
private:
    IClockPullerReservoir* iReservoirLeft;
    IClockPullerReservoir* iReservoirRight;
    IClockPullerTimestamp* iTimestamp;
};

class IClockPuller;

class MsgMode : public Msg
{
    friend class MsgFactory;
public:
    MsgMode(AllocatorBase& aAllocator);
    const Brx& Mode() const;
    const ModeInfo& Info() const;
    const ModeClockPullers& ClockPullers() const;
private:
    void Initialise(const Brx& aMode, TBool aSupportsLatency, TBool aIsRealTime, ModeClockPullers aClockPullers, TBool aSupportsNext, TBool aSupportsPrev);
private: // from Msg
    void Clear() override;
    Msg* Process(IMsgProcessor& aProcessor) override;
private:
    BwsMode iMode;
    ModeInfo iInfo;
    ModeClockPullers iClockPullers;
};

class MsgTrack : public Msg
{
    friend class MsgFactory;
public:
    static const TUint kMaxUriBytes = 1024;
public:
    MsgTrack(AllocatorBase& aAllocator);
    Media::Track& Track() const;
    TBool StartOfStream() const;
private:
    void Initialise(Media::Track& aTrack, TBool aStartOfStream);
private: // from Msg
    void Clear() override;
    Msg* Process(IMsgProcessor& aProcessor) override;
private:
    Media::Track* iTrack;
    TBool iStartOfStream;
};

class MsgDrain : public Msg
{
    friend class MsgFactory;
public:
    MsgDrain(AllocatorBase& aAllocator);
    void ReportDrained();
    TUint Id() const;
private:
    void Initialise(TUint aId, Functor aCallback);
private: // from Msg
    void Clear() override;
    Msg* Process(IMsgProcessor& aProcessor) override;
private:
    Functor iCallback;
    TUint iId;
    TBool iCallbackPending;
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
    void Clear() override;
    Msg* Process(IMsgProcessor& aProcessor) override;
private:
    TUint iDelayJiffies;
};

class IStreamHandler;

class PcmStreamInfo
{
public:
    PcmStreamInfo();
    void Set(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, AudioDataEndian aEndian, TUint64 aStartSample = 0);
    void SetAnalogBypass();
    void Clear();
    TUint BitDepth() const;
    TUint SampleRate() const;
    TUint NumChannels() const;
    AudioDataEndian Endian() const;
    TUint64 StartSample() const;
    TBool AnalogBypass() const;
private:
    TUint iBitDepth;
    TUint iSampleRate;
    TUint iNumChannels;
    AudioDataEndian iEndian;
    TUint64 iStartSample;
    TBool iAnalogBypass;
};

class MsgMetaText : public Msg
{
    friend class MsgFactory;
public:
    static const TUint kMaxBytes = 4 * 1024;
public:
    MsgMetaText(AllocatorBase& aAllocator);
    const Brx& MetaText() const;
private:
    void Initialise(const Brx& aMetaText);
private: // from Msg
    void Clear() override;
    Msg* Process(IMsgProcessor& aProcessor) override;
private:
    Bws<kMaxBytes> iMetaText;
};

class MsgEncodedStream : public Msg
{
    friend class MsgFactory;
public:
    static const TUint kMaxUriBytes = 1024;
public:
    MsgEncodedStream(AllocatorBase& aAllocator);
    const Brx& Uri() const;
    const Brx& MetaText() const;
    TUint64 TotalBytes() const;
    TUint64 StartPos() const;
    TUint StreamId() const;
    TBool Seekable() const;
    TBool Live() const;
    IStreamHandler* StreamHandler() const;
    TBool RawPcm() const;
    const PcmStreamInfo& PcmStream() const;
private:
    void Initialise(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint64 aStartPos, TUint aStreamId, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler);
    void Initialise(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint64 aStartPos, TUint aStreamId, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler, const PcmStreamInfo& aPcmStream);
private: // from Msg
    void Clear() override;
    Msg* Process(IMsgProcessor& aProcessor) override;
private:
    Bws<kMaxUriBytes> iUri;
    Bws<MsgMetaText::kMaxBytes> iMetaText;
    TUint64 iTotalBytes;
    TUint64 iStartPos;
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
    void RefAdded() override;
    void RefRemoved() override;
    void Clear() override;
    Msg* Process(IMsgProcessor& aProcessor) override;
private:
    MsgAudioEncoded* iNextAudio;
    TUint iSize; // Bytes
    TUint iOffset; // Bytes
    EncodedAudio* iAudioData;
};

class MsgStreamInterrupted : public Msg
{
public:
    MsgStreamInterrupted(AllocatorBase& aAllocator);
private: // from Msg
    Msg* Process(IMsgProcessor& aProcessor) override;
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
    void ReportHalted();
private:
    void Initialise(TUint aId);
    void Initialise(TUint aId, Functor aCallback);
private: // from Msg
    void Clear() override;
    Msg* Process(IMsgProcessor& aProcessor) override;
private:
    TUint iId;
    Functor iCallback;
};

class MsgFlush : public Msg
{
public:
    static const TUint kIdInvalid;
public:
    MsgFlush(AllocatorBase& aAllocator);
    void Initialise(TUint aId);
    TUint Id() const;
private: // from Msg
    void Clear() override;
    Msg* Process(IMsgProcessor& aProcessor) override;
private:
    TUint iId;
};

class MsgWait : public Msg
{
public:
    MsgWait(AllocatorBase& aAllocator);
private: // from Msg
    Msg* Process(IMsgProcessor& aProcessor) override;
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
    TBool AnalogBypass() const { return iAnalogBypass; }
    IStreamHandler* StreamHandler() const { return iStreamHandler;}
private:
    DecodedStreamInfo();
    void Set(TUint aStreamId, TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless, TBool aSeekable, TBool aLive, TBool aAnalogBypass, IStreamHandler* aStreamHandler);
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
    TBool iAnalogBypass;
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
    void Initialise(TUint aStreamId, TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless, TBool aSeekable, TBool aLive, TBool aAnalogBypass, IStreamHandler* aStreamHandler);
private: // from Msg
    void Clear() override;
    Msg* Process(IMsgProcessor& aProcessor) override;
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
    void SetMuted(); // should only be used with msgs immediately following a ramp down
    const Media::Ramp& Ramp() const;
    void SetClockPull(TUint aMultiplier);
    TUint MedianRampMultiplier(); // 1<<31 => full level.  Note - clears any existing ramp
protected:
    MsgAudio(AllocatorBase& aAllocator);
    void Initialise(TUint aSampleRate, TUint aBitDepth, TUint aChannels);
    void Clear() override;
private:
    virtual MsgAudio* Allocate() = 0;
    MsgAudio* DoSplit(TUint aJiffies);
    virtual void SplitCompleted(MsgAudio& aRemaining);
protected:
    MsgAudio* iNextAudio;
    TUint iSize; // Jiffies
    TUint iOffset; // Jiffies
    Media::Ramp iRamp;
    TUint iClockPullMultiplier;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iNumChannels;
};

class MsgBitRate : public Msg
{
    friend class MsgFactory;
public:
    MsgBitRate(AllocatorBase& aAllocator);
    TUint BitRate() const;
private:
    void Initialise(TUint aBitRate);
private: // from Msg
    void Clear() override;
    Msg* Process(IMsgProcessor& aProcessor) override;
private:
    TUint iBitRate;
};

class MsgPlayable;
class MsgPlayablePcm;
class MsgPlayableSilence;

class MsgAudioPcm : public MsgAudio
{
    friend class MsgFactory;
public:
    static const TUint64 kTrackOffsetInvalid;
public:
    MsgAudioPcm(AllocatorBase& aAllocator);
    TUint64 TrackOffset() const; // offset of the start of this msg from the start of its track.  FIXME no tests for this yet
    MsgPlayable* CreatePlayable(); // removes ref, transfer ownership of DecodedAudio
    void Aggregate(MsgAudioPcm* aMsg); // append aMsg to the end of this msg, removes ref on aMsg
    TBool TryGetTimestamps(TUint& aNetwork, TUint& aRx);
public: // from MsgAudio
    MsgAudio* Clone() override; // create new MsgAudio, take ref to DecodedAudio, copy size/offset
private:
    void Initialise(DecodedAudio* aDecodedAudio, TUint aSampleRate, TUint aBitDepth, TUint aChannels, TUint64 aTrackOffset,
                    Allocator<MsgPlayablePcm>& aAllocatorPlayablePcm,
                    Allocator<MsgPlayableSilence>& aAllocatorPlayableSilence);
    void SetTimestamps(TUint aRx, TUint aNetwork);
private: // from MsgAudio
    MsgAudio* Allocate() override;
    void SplitCompleted(MsgAudio& aRemaining) override;
private: // from Msg
    void Clear() override;
    Msg* Process(IMsgProcessor& aProcessor) override;
private:
    DecodedAudio* iAudioData;
    Allocator<MsgPlayablePcm>* iAllocatorPlayablePcm;
    Allocator<MsgPlayableSilence>* iAllocatorPlayableSilence;
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
    MsgPlayable* CreatePlayable(); // removes ref
public: // from MsgAudio
    MsgAudio* Clone() override;
private:
    void Initialise(TUint& aJiffies, TUint aSampleRate, TUint aBitDepth, TUint aChannels, Allocator<MsgPlayableSilence>& aAllocatorPlayable);
private: // from MsgAudio
    MsgAudio* Allocate() override;
    void SplitCompleted(MsgAudio& aRemaining) override;
private: // from Msg
    Msg* Process(IMsgProcessor& aProcessor) override;
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
    TUint ClockPullMultiplier() const;
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
    void Read(IPcmProcessor& aProcessor);
protected:
    MsgPlayable(AllocatorBase& aAllocator);
    void Initialise(TUint aSizeBytes, TUint aBitDepth, TUint aNumChannels,
                    TUint aOffsetBytes, const Media::Ramp& aRamp, TUint aClockPullMultiplier);
protected: // from Msg
    void RefAdded() override;
    void RefRemoved() override;
    Msg* Process(IMsgProcessor& aProcessor) override;
private:
    virtual MsgPlayable* Allocate() = 0;
    virtual void SplitCompleted(MsgPlayable& aRemaining);
    virtual void ReadBlock(IPcmProcessor& aProcessor) = 0;
protected:
    MsgPlayable* iNextPlayable;
    TUint iSize; // Bytes
    TUint iBitDepth;
    TUint iNumChannels;
    TUint iOffset; // Bytes
    Media::Ramp iRamp;
    TUint iClockPullMultiplier;
};

class MsgPlayablePcm : public MsgPlayable
{
    friend class MsgAudioPcm;
public:
    MsgPlayablePcm(AllocatorBase& aAllocator);
private:
    void Initialise(DecodedAudio* aDecodedAudio, TUint aSizeBytes, TUint aBitDepth, TUint aNumChannels,
                    TUint aOffsetBytes, const Media::Ramp& aRamp, TUint aClockPullMultiplier);
private: // from MsgPlayable
    MsgPlayable* Clone() override; // create new MsgPlayable, take ref to DecodedAudio, copy size/offset
    MsgPlayable* Allocate() override;
    void SplitCompleted(MsgPlayable& aRemaining) override;
    void ReadBlock(IPcmProcessor& aProcessor) override;
private: // from Msg
    void Clear() override;
private:
    DecodedAudio* iAudioData;
};

class MsgPlayableSilence : public MsgPlayable
{
    friend class MsgSilence;
    friend class MsgAudioPcm;
public:
    MsgPlayableSilence(AllocatorBase& aAllocator);
private:
    void Initialise(TUint aSizeBytes, TUint aBitDepth, TUint aNumChannels, const Media::Ramp& aRamp, TUint aClockPullMultiplier);
private: // from MsgPlayable
    MsgPlayable* Allocate() override;
    void SplitCompleted(MsgPlayable& aRemaining) override;
    void ReadBlock(IPcmProcessor& aProcessor) override;
private: // from Msg
    void Clear() override;
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
    Msg* Process(IMsgProcessor& aProcessor) override;
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
    virtual Msg* ProcessMsg(MsgTrack* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgDrain* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgDelay* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgEncodedStream* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgAudioEncoded* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgMetaText* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgStreamInterrupted* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgHalt* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgFlush* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgWait* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgDecodedStream* aMsg) = 0;
    virtual Msg* ProcessMsg(MsgBitRate* aMsg) = 0;
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
     */
    virtual void ProcessFragment8(const Brx& aData, TUint aNumChannels) = 0;
    virtual void ProcessFragment16(const Brx& aData, TUint aNumChannels) = 0;
    virtual void ProcessFragment24(const Brx& aData, TUint aNumChannels) = 0;
    virtual void ProcessFragment32(const Brx& aData, TUint aNumChannels) = 0;
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
    virtual void ProcessSample32(const TByte* aSample, TUint aNumChannels) = 0;
    /**
     * Called once per call to MsgPlayable::Read.
     *
     * No more calls to ProcessFragment or ProcessSample will be made after this.
     */
    virtual void EndBlock() = 0;
    /**
     * If this is called, the processor should pass on any buffered audio.
     */
    virtual void Flush() = 0;
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
    TUint TrackCount() const;
    TUint EncodedStreamCount() const;
    TUint DecodedStreamCount() const;
    TUint EncodedAudioCount() const;
private:
    void Add(TUint& aValue, TUint aAdded);
    void Remove(TUint& aValue, TUint aRemoved);
private:
    virtual void ProcessMsgIn(MsgMode* aMsg);
    virtual void ProcessMsgIn(MsgTrack* aMsg);
    virtual void ProcessMsgIn(MsgDrain* aMsg);
    virtual void ProcessMsgIn(MsgDelay* aMsg);
    virtual void ProcessMsgIn(MsgEncodedStream* aMsg);
    virtual void ProcessMsgIn(MsgAudioEncoded* aMsg);
    virtual void ProcessMsgIn(MsgMetaText* aMsg);
    virtual void ProcessMsgIn(MsgStreamInterrupted* aMsg);
    virtual void ProcessMsgIn(MsgHalt* aMsg);
    virtual void ProcessMsgIn(MsgFlush* aMsg);
    virtual void ProcessMsgIn(MsgWait* aMsg);
    virtual void ProcessMsgIn(MsgDecodedStream* aMsg);
    virtual void ProcessMsgIn(MsgBitRate* aMsg);
    virtual void ProcessMsgIn(MsgAudioPcm* aMsg);
    virtual void ProcessMsgIn(MsgSilence* aMsg);
    virtual void ProcessMsgIn(MsgQuit* aMsg);
    virtual Msg* ProcessMsgOut(MsgMode* aMsg);
    virtual Msg* ProcessMsgOut(MsgTrack* aMsg);
    virtual Msg* ProcessMsgOut(MsgDrain* aMsg);
    virtual Msg* ProcessMsgOut(MsgDelay* aMsg);
    virtual Msg* ProcessMsgOut(MsgEncodedStream* aMsg);
    virtual Msg* ProcessMsgOut(MsgAudioEncoded* aMsg);
    virtual Msg* ProcessMsgOut(MsgMetaText* aMsg);
    virtual Msg* ProcessMsgOut(MsgStreamInterrupted* aMsg);
    virtual Msg* ProcessMsgOut(MsgHalt* aMsg);
    virtual Msg* ProcessMsgOut(MsgFlush* aMsg);
    virtual Msg* ProcessMsgOut(MsgWait* aMsg);
    virtual Msg* ProcessMsgOut(MsgDecodedStream* aMsg);
    virtual Msg* ProcessMsgOut(MsgBitRate* aMsg);
    virtual Msg* ProcessMsgOut(MsgAudioPcm* aMsg);
    virtual Msg* ProcessMsgOut(MsgSilence* aMsg);
    virtual Msg* ProcessMsgOut(MsgQuit* aMsg);
private:
    class ProcessorEnqueue : public IMsgProcessor, private INonCopyable
    {
    public:
        ProcessorEnqueue(MsgReservoir& aQueue);
    protected:
        Msg* ProcessMsg(MsgMode* aMsg) override;
        Msg* ProcessMsg(MsgTrack* aMsg) override;
        Msg* ProcessMsg(MsgDrain* aMsg) override;
        Msg* ProcessMsg(MsgDelay* aMsg) override;
        Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
        Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
        Msg* ProcessMsg(MsgMetaText* aMsg) override;
        Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
        Msg* ProcessMsg(MsgHalt* aMsg) override;
        Msg* ProcessMsg(MsgFlush* aMsg) override;
        Msg* ProcessMsg(MsgWait* aMsg) override;
        Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
        Msg* ProcessMsg(MsgBitRate* aMsg) override;
        Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
        Msg* ProcessMsg(MsgSilence* aMsg) override;
        Msg* ProcessMsg(MsgPlayable* aMsg) override;
        Msg* ProcessMsg(MsgQuit* aMsg) override;
    protected:
        MsgReservoir& iQueue;
    };
    class ProcessorQueueIn : public ProcessorEnqueue
    {
    public:
        ProcessorQueueIn(MsgReservoir& aQueue);
    private:
        Msg* ProcessMsg(MsgMode* aMsg) override;
        Msg* ProcessMsg(MsgTrack* aMsg) override;
        Msg* ProcessMsg(MsgDrain* aMsg) override;
        Msg* ProcessMsg(MsgDelay* aMsg) override;
        Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
        Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
        Msg* ProcessMsg(MsgMetaText* aMsg) override;
        Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
        Msg* ProcessMsg(MsgHalt* aMsg) override;
        Msg* ProcessMsg(MsgFlush* aMsg) override;
        Msg* ProcessMsg(MsgWait* aMsg) override;
        Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
        Msg* ProcessMsg(MsgBitRate* aMsg) override;
        Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
        Msg* ProcessMsg(MsgSilence* aMsg) override;
        Msg* ProcessMsg(MsgPlayable* aMsg) override;
        Msg* ProcessMsg(MsgQuit* aMsg) override;
    };
    class ProcessorQueueOut : public IMsgProcessor, private INonCopyable
    {
    public:
        ProcessorQueueOut(MsgReservoir& aQueue);
    private:
        Msg* ProcessMsg(MsgMode* aMsg) override;
        Msg* ProcessMsg(MsgTrack* aMsg) override;
        Msg* ProcessMsg(MsgDrain* aMsg) override;
        Msg* ProcessMsg(MsgDelay* aMsg) override;
        Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
        Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
        Msg* ProcessMsg(MsgMetaText* aMsg) override;
        Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
        Msg* ProcessMsg(MsgHalt* aMsg) override;
        Msg* ProcessMsg(MsgFlush* aMsg) override;
        Msg* ProcessMsg(MsgWait* aMsg) override;
        Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
        Msg* ProcessMsg(MsgBitRate* aMsg) override;
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
    TUint iTrackCount;
    TUint iEncodedStreamCount;
    TUint iDecodedStreamCount;
    TUint iEncodedAudioCount;
};

class PipelineElement : protected IMsgProcessor
{
protected:
    enum MsgType
    {
        eMode               = 1
       ,eTrack              = 1 <<  1
       ,eDrain              = 1 <<  2
       ,eDelay              = 1 <<  3
       ,eEncodedStream      = 1 <<  4
       ,eAudioEncoded       = 1 <<  5
       ,eMetatext           = 1 <<  6
       ,eStreamInterrupted  = 1 <<  7
       ,eHalt               = 1 <<  8
       ,eFlush              = 1 <<  9
       ,eWait               = 1 << 10
       ,eDecodedStream      = 1 << 11
       ,eBitRate            = 1 << 12
       ,eAudioPcm           = 1 << 13
       ,eSilence            = 1 << 14
       ,ePlayable           = 1 << 15
       ,eQuit               = 1 << 16
    };
protected:
    PipelineElement(TUint aSupportedTypes);
    ~PipelineElement();
protected: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    inline void CheckSupported(MsgType aType) const;
private:
    TUint iSupportedTypes;
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
     * Inform the pipeline that a new track is starting.
     *
     * @param[in] aTrack           Track about to be played.
     * @param[in] aStartOfStream   false if this is called after OutputData.
     */
    virtual void OutputTrack(Track& aTrack, TBool aStartOfStream = true) = 0;
    /**
    * Inform the pipeline that the next stream cannot begin until all pending audio has been played.
    *
    * @param[in] aCallabck        Callback to run when all audio has been processed.
    */
    virtual void OutputDrain(Functor aCallback) = 0;
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
     * @param[in] aStartPos        Any offset from the actual start of the stream (e.g. when seeking)
     * @param[in] aSeekable        Whether the stream supports Seek requests
     * @param[in] aLive            Whether the stream is being broadcast live (and won't support seeking)
     * @param[in] aStreamHandler   Stream handler.  Used to allow pipeline elements to communicate upstream.
     * @param[in] aStreamId        Identifier for the pending stream.  Unique within a single track only.
     */
    virtual void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TUint64 aStartPos, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId) = 0;
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
    * Inform the pipeline of a break in content.
    *
    * This should only be called for 'live' streams which are unable to
    * restart from the point where a connection was dropped.
    */
    virtual void OutputStreamInterrupted() = 0;
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
    static const TUint kStreamIdInvalid = 0;
public:
    virtual ~IPipelineIdProvider() {}
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
     * Inform interested parties of an unexpected break in audio.
     *
     * Sources which are sensitive to latency may need to restart.
     * This may be called from a different thread.  The implementor is responsible for any synchronisation.
     *
     * @param[in] aMode            Reported by the MsgMode which preceded the stream which dropped out.
     *                             i.e. identifier for the UriProvider associated with this stream
     * @param[in] aStreamId        Stream identifier, unique in the context of the current track only.
     * @param[in] aStarving        true if entering starvation; false if starvation is over.
     */
    virtual void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) = 0;
};

class IUrlBlockWriter
{
public:
    /**
     * Read a block of data out of band, without affecting the state of the current stream.
     *
     * This may be called from a different thread.  The implementor is responsible for any synchronisation.
     * This is relatively inefficient so should be used with care.  (It is intended for use
     * during format recognition for a new stream; more frequent use would be questionable.)
     *
     * @param[in] aWriter          Interface used to return the requested data.
     * @param[in] aUrl             Uri to read from.
     * @param[in] aOffset          Byte offset to start reading from
     * @param[in] aBytes           Number of bytes to read
     *
     * @return  true if exactly aBytes were read; false otherwise
     */
    virtual TBool TryGet(IWriter& aWriter, const Brx& aUrl, TUint64 aOffset, TUint aBytes) = 0; // return false if we failed to get aBytes
    virtual ~IUrlBlockWriter() {}
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


/**
 * Should be implemented by the object that animates (calls Pull() on) Pipeline.
 */
class IPipelineAnimator
{
public:
    virtual ~IPipelineAnimator() {}
    /**
     * Query how much (if any) buffering is performed post-pipeline
     *
     * @return     Delay applied beyond the pipeline in Jiffies.
     *             See Jiffies class for time conversion utilities.
     */
    virtual TUint PipelineAnimatorBufferJiffies() = 0;
    /**
     * Report any post-pipeline delay.
     *
     * Throws SampleRateUnsupported is aSampleRateTo is not supported.
     *
     * @param[in] aSampleRateFrom   Previous sample rate (in Hz).  0 implies pipeline startup.
     * @param[in] aSampleRateTo     New sample rate (in Hz).
     *
     * @return     Delay applied beyond the pipeline in Jiffies.
     *             See Jiffies class for time conversion utilities.
     */
    virtual TUint PipelineDriverDelayJiffies(TUint aSampleRateFrom, TUint aSampleRateTo) = 0;
};

class IPipeline : public IPipelineElementUpstream
{
public:
    virtual ~IPipeline() {}
    virtual void SetAnimator(IPipelineAnimator& aAnimator) = 0;
};

class IPostPipelineLatency
{
public:
    virtual void SetPostPipelineLatency(TUint aLatencyJiffies) = 0;
    virtual ~IPostPipelineLatency() {}
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

class MsgFactory;
class MsgFactoryInitParams
{
    friend class MsgFactory;
public:
    MsgFactoryInitParams()
        : iMsgModeCount(1)
        , iMsgTrackCount(1)
        , iMsgDrainCount(1)
        , iMsgDelayCount(1)
        , iMsgEncodedStreamCount(1)
        , iEncodedAudioCount(1)
        , iMsgAudioEncodedCount(1)
        , iMsgMetaTextCount(1)
        , iMsgStreamInterruptedCount(1)
        , iMsgHaltCount(1)
        , iMsgFlushCount(1)
        , iMsgWaitCount(1)
        , iMsgDecodedStreamCount(1)
        , iMsgBitRateCount(1)
        , iDecodedAudioCount(1)
        , iMsgAudioPcmCount(1)
        , iMsgSilenceCount(1)
        , iMsgPlayablePcmCount(1)
        , iMsgPlayableSilenceCount(1)
        , iMsgQuitCount(1)
    {}
    void SetMsgModeCount(TUint aCount)                                      { iMsgModeCount = aCount; }
    void SetMsgTrackCount(TUint aCount)                                     { iMsgTrackCount = aCount; }
    void SetMsgDrainCount(TUint aCount)                                     { iMsgDrainCount = aCount; }
    void SetMsgDelayCount(TUint aCount)                                     { iMsgDelayCount = aCount; }
    void SetMsgEncodedStreamCount(TUint aCount)                             { iMsgEncodedStreamCount = aCount; }
    void SetMsgAudioEncodedCount(TUint aCount, TUint aEncodedAudioCount)    { iMsgAudioEncodedCount = aCount; iEncodedAudioCount = aEncodedAudioCount; }
    void SetMsgMetaTextCount(TUint aCount)                                  { iMsgMetaTextCount = aCount; }
    void SetMsgStreamInterruptedCount(TUint aCount)                         { iMsgStreamInterruptedCount = aCount; }
    void SetMsgHaltCount(TUint aCount)                                      { iMsgHaltCount = aCount; }
    void SetMsgFlushCount(TUint aCount)                                     { iMsgFlushCount = aCount; }
    void SetMsgWaitCount(TUint aCount)                                      { iMsgWaitCount = aCount; }
    void SetMsgDecodedStreamCount(TUint aCount)                             { iMsgDecodedStreamCount = aCount; }
    void SetMsgBitRateCount(TUint aCount)                                   { iMsgBitRateCount = aCount; }
    void SetMsgAudioPcmCount(TUint aCount, TUint aDecodedAudioCount)        { iMsgAudioPcmCount = aCount; iDecodedAudioCount = aDecodedAudioCount; }
    void SetMsgSilenceCount(TUint aCount)                                   { iMsgSilenceCount = aCount; }
    void SetMsgPlayableCount(TUint aPcmCount, TUint aSilenceCount)          { iMsgPlayablePcmCount = aPcmCount; iMsgPlayableSilenceCount = aSilenceCount; }
    void SetMsgQuitCount(TUint aCount)                                      { iMsgQuitCount = aCount; }
private:
    TUint iMsgModeCount;
    TUint iMsgTrackCount;
    TUint iMsgDrainCount;
    TUint iMsgDelayCount;
    TUint iMsgEncodedStreamCount;
    TUint iEncodedAudioCount;
    TUint iMsgAudioEncodedCount;
    TUint iMsgMetaTextCount;
    TUint iMsgStreamInterruptedCount;
    TUint iMsgHaltCount;
    TUint iMsgFlushCount;
    TUint iMsgWaitCount;
    TUint iMsgDecodedStreamCount;
    TUint iMsgBitRateCount;
    TUint iDecodedAudioCount;
    TUint iMsgAudioPcmCount;
    TUint iMsgSilenceCount;
    TUint iMsgPlayablePcmCount;
    TUint iMsgPlayableSilenceCount;
    TUint iMsgQuitCount;
};

class MsgFactory
{
public:
    MsgFactory(IInfoAggregator& aInfoAggregator, const MsgFactoryInitParams& aInitParams);

    MsgMode* CreateMsgMode(const Brx& aMode, TBool aSupportsLatency, TBool aRealTime, ModeClockPullers aClockPullers, TBool aSupportsNext, TBool aSupportsPrev);
    MsgTrack* CreateMsgTrack(Media::Track& aTrack, TBool aStartOfStream = true);
    MsgDrain* CreateMsgDrain(Functor aCallback);
    MsgDelay* CreateMsgDelay(TUint aDelayJiffies);
    MsgEncodedStream* CreateMsgEncodedStream(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint64 aOffset, TUint aStreamId, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler);
    MsgEncodedStream* CreateMsgEncodedStream(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint64 aOffset, TUint aStreamId, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler, const PcmStreamInfo& aPcmStream);
    MsgEncodedStream* CreateMsgEncodedStream(MsgEncodedStream* aMsg, IStreamHandler* aStreamHandler);
    MsgAudioEncoded* CreateMsgAudioEncoded(const Brx& aData);
    MsgMetaText* CreateMsgMetaText(const Brx& aMetaText);
    MsgStreamInterrupted* CreateMsgStreamInterrupted();
    MsgHalt* CreateMsgHalt(TUint aId = MsgHalt::kIdNone);
    MsgHalt* CreateMsgHalt(TUint aId, Functor aCallback);
    MsgFlush* CreateMsgFlush(TUint aId);
    MsgWait* CreateMsgWait();
    MsgDecodedStream* CreateMsgDecodedStream(TUint aStreamId, TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless, TBool aSeekable, TBool aLive, TBool aAnalogBypass, IStreamHandler* aStreamHandler);
    MsgDecodedStream* CreateMsgDecodedStream(MsgDecodedStream* aMsg, IStreamHandler* aStreamHandler);
    MsgBitRate* CreateMsgBitRate(TUint aBitRate);
    MsgAudioPcm* CreateMsgAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, AudioDataEndian aEndian, TUint64 aTrackOffset);
    MsgAudioPcm* CreateMsgAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, AudioDataEndian aEndian, TUint64 aTrackOffset, TUint aRxTimestamp, TUint aNetworkTimestamp);
    MsgAudioPcm* CreateMsgAudioPcm(MsgAudioEncoded* aAudio, TUint aChannels, TUint aSampleRate, TUint aBitDepth, TUint64 aTrackOffset); // aAudio must contain big endian pcm data
    MsgSilence* CreateMsgSilence(TUint& aSizeJiffies, TUint aSampleRate, TUint aBitDepth, TUint aChannels);
    MsgQuit* CreateMsgQuit();
private:
    EncodedAudio* CreateEncodedAudio(const Brx& aData);
    DecodedAudio* CreateDecodedAudio(const Brx& aData, TUint aBitDepth, AudioDataEndian aEndian);
    MsgAudioPcm* CreateMsgAudioPcm(DecodedAudio* aAudioData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, TUint64 aTrackOffset);
private:
    Allocator<MsgMode> iAllocatorMsgMode;
    Allocator<MsgTrack> iAllocatorMsgTrack;
    Allocator<MsgDrain> iAllocatorMsgDrain;
    TUint iDrainId;
    Allocator<MsgDelay> iAllocatorMsgDelay;
    Allocator<MsgEncodedStream> iAllocatorMsgEncodedStream;
    Allocator<AudioData> iAllocatorAudioData;
    Allocator<MsgAudioEncoded> iAllocatorMsgAudioEncoded;
    Allocator<MsgMetaText> iAllocatorMsgMetaText;
    Allocator<MsgStreamInterrupted> iAllocatorMsgStreamInterrupted;
    Allocator<MsgHalt> iAllocatorMsgHalt;
    Allocator<MsgFlush> iAllocatorMsgFlush;
    Allocator<MsgWait> iAllocatorMsgWait;
    Allocator<MsgDecodedStream> iAllocatorMsgDecodedStream;
    Allocator<MsgBitRate> iAllocatorMsgBitRate;
    Allocator<MsgAudioPcm> iAllocatorMsgAudioPcm;
    Allocator<MsgSilence> iAllocatorMsgSilence;
    Allocator<MsgPlayablePcm> iAllocatorMsgPlayablePcm;
    Allocator<MsgPlayableSilence> iAllocatorMsgPlayableSilence;
    Allocator<MsgQuit> iAllocatorMsgQuit;
};

} // namespace Media
} // namespace OpenHome

