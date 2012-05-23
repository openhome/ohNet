#ifndef HEADER_PIPELINE_MSG
#define HEADER_PIPELINE_MSG

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/InfoProvider.h>

EXCEPTION(AllocatorNoMemory); // heaps are expected to be setup to avoid this.  Any instance of this exception indicates a system design error.

namespace OpenHome {
namespace Media {

class Msg;

class MsgAllocatorBase : private Av::IInfoProvider
{
public:
    ~MsgAllocatorBase();
    void Free(Msg* aPtr);
    TUint CellsTotal() const;
    TUint CellBytes() const;
    TUint CellsUsed() const;
    TUint CellsUsedMax() const;
    void GetStats(TUint& aCellsTotal, TUint& aCellBytes, TUint& aCellsUsed, TUint& aCellsUsedMax) const;
    static const Brn kQueryMemory;
protected:
    MsgAllocatorBase(const TChar* aName, TUint aNumCells, TUint aCellBytes, Av::IInfoAggregator& aInfoAggregator);
    Msg* DoAllocate();
private: // from Av::IInfoProvider
    void QueryInfo(const Brx& aQuery, IWriter& aWriter);
protected:
    Fifo<Msg*> iFree;
private:
    mutable Mutex iLock;
    const TChar* iName;
    TUint iCellsTotal;
    TUint iCellBytes;
    TUint iCellsUsed;
    TUint iCellsUsedMax;
};
    
template <class T> class MsgAllocator : public MsgAllocatorBase
{
public:
    MsgAllocator(const TChar* aName, TUint aNumCells, Av::IInfoAggregator& aInfoAggregator);
    T* Allocate();
};

template <class T> MsgAllocator<T>::MsgAllocator(const TChar* aName, TUint aNumCells, Av::IInfoAggregator& aInfoAggregator)
    : MsgAllocatorBase(aName, aNumCells, sizeof(T), aInfoAggregator)
{
    for (TUint i=0; i<aNumCells; i++) {
        iFree.Write(new T(*this));
    }
}

template <class T> T* MsgAllocator<T>::Allocate()
{
    return static_cast<T*>(DoAllocate());
}

class Msg
{
    friend class MsgAllocatorBase;
public:
    void AddRef();
    void RemoveRef();
   // virtual void Clear() = 0; // ???
protected:
    Msg(MsgAllocatorBase& aAllocator);
protected:
    ~Msg();
protected:
    MsgAllocatorBase& iAllocator;
private:
    Mutex iLock;
    TUint iRefCount;
};

enum EMediaDataEndian
{
    EMediaDataLittleEndian
   ,EMediaDataBigEndian
};

class MsgDecoded : public Msg // decoded audio data
{
    friend class MsgFactory;
public:
    static const TUint kMaxBytes = 100; // FIXME
    static const TUint kMaxSubsamples = kMaxBytes/4;
public:
    MsgDecoded(MsgAllocatorBase& aAllocator);
    const TUint* PtrOffsetSamples(TUint aSamples) const;
    const TUint* PtrOffsetBytes(TUint aBytes) const;
    TUint Bytes() const;
private:
    void Construct(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian); // sample rate, bit-depth, num channels, const brx& (ptr/len), endianness);
    static void UnpackBigEndian(TUint32* aDst, const TUint8* aSrc, TUint aBitDepth, TUint aNumSubsamples);
    static void UnpackLittleEndian(TUint32* aDst, const TUint8* aSrc, TUint aBitDepth, TUint aNumSubsamples);
private:
    TUint iSubsamples[kMaxSubsamples]; // one sub-sample per channel == 1 sample
    TUint iSubsampleCount;
    TUint iChannels;
    //TUint64 iSampleStart; // pos of first sample in iData within the track
    //TUint64 iSamplesTotal; // total num samples in the track
    TUint iSampleRate;
    TUint iBitRate; // what is this ??
    TUint iBitDepth;
    //TBool iLossless;
    //Bws<kMaxCodecNameBytes> iCodecName;
    //TUint iSamples; // bytes/4 - remove
};

class MsgAudio : public Msg // FIXME - needs to be destroyed via CopyTo.  RemoveRef results in iAudioData being leaked
{
    friend class MsgFactory;
public:
    MsgAudio(MsgAllocatorBase& aAllocator);
    MsgAudio* SplitJiffies(TUint64 aAt); // returns block after aAt
    MsgAudio* SplitBytes(TUint aAt); // returns block after aAt
    void Add(MsgAudio* aMsg); // combines MsgAudio instances so they report longer durations etc
    void CopyTo(TUint* aDest); // does a RemoveRef at the end
    MsgAudio* Clone(); // create new MsgAudio, take ref to MsgDecoded, copy ptr/bytes
    TUint Bytes() const;
private:
    void Construct(MsgDecoded* aMsgDecoded, TUint aOffsetBytes = 0);
private:
    MsgDecoded* iAudioData;
    const TUint* iPtr;
    TUint iBytes;
    MsgAudio* iNext;
};

class MsgTrack : public Msg
{
public:
    static const TUint kMaxBytes = 100; // FIXME
public:
    MsgTrack(MsgAllocatorBase& aAllocator);
private:
    // track uri & meta data
};

class MsgStartOfAudio : public Msg
{
public:
    MsgStartOfAudio(MsgAllocatorBase& aAllocator);
private:
    static const TUint kMaxCodecNameBytes = 32;
    //TUint64 iSamplesTotal; // total num samples in the track
    //TBool iLossless;
    //Bws<kMaxCodecNameBytes> iCodecName;
};

class MsgMetaText : public Msg
{
public:
    static const TUint kMaxBytes = 100; // FIXME
public:
    MsgMetaText(MsgAllocatorBase& aAllocator);
};

class MsgFactory // owned by Pipeline object
{
public:
    MsgFactory(Av::IInfoAggregator& aInfoAggregator, TUint aMsgDecodedCount, TUint aMsgAudioCount, TUint aMsgTrackCount, TUint aMsgMetaTextCount);
    MsgAudio* CreateMsgAudio(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian);
    MsgTrack* CreateMsgTrack();
    MsgMetaText* CreateMsgMetaText();
private:
    MsgDecoded* CreateMsgDecoded(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian);
private:
    MsgAllocator<MsgDecoded> iAllocatorMsgDecoded;
    MsgAllocator<MsgAudio> iAllocatorMsgAudio;
    MsgAllocator<MsgTrack> iAllocatorMsgTrack;
    MsgAllocator<MsgMetaText> iAllocatorMsgMetaText;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_MSG
