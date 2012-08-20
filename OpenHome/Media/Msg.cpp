#include <OpenHome/Media/Msg.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Printer.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// AllocatorBase

const Brn AllocatorBase::kQueryMemory = Brn("memory");

AllocatorBase::~AllocatorBase()
{
    const TUint slots = iFree.Slots();
    for (TUint i=0; i<slots; i++) {
        delete iFree.Read();
    }
}

void AllocatorBase::Free(Allocated* aPtr)
{
    iFree.Write(aPtr);
    iLock.Wait();
    iCellsUsed--;
    iLock.Signal();
}

TUint AllocatorBase::CellsTotal() const
{
    iLock.Wait();
    TUint cellsTotal = iCellsTotal;
    iLock.Signal();
    return cellsTotal;
}

TUint AllocatorBase::CellBytes() const
{
    iLock.Wait();
    TUint cellBytes = iCellBytes;
    iLock.Signal();
    return cellBytes;
}

TUint AllocatorBase::CellsUsed() const
{
    iLock.Wait();
    TUint cellsUsed = iCellsUsed;
    iLock.Signal();
    return cellsUsed;
}

TUint AllocatorBase::CellsUsedMax() const
{
    iLock.Wait();
    TUint cellsUsedMax = iCellsUsedMax;
    iLock.Signal();
    return cellsUsedMax;
}

void AllocatorBase::GetStats(TUint& aCellsTotal, TUint& aCellBytes, TUint& aCellsUsed, TUint& aCellsUsedMax) const
{
    iLock.Wait();
    aCellsTotal = iCellsTotal;
    aCellBytes = iCellBytes;
    aCellsUsed = iCellsUsed;
    aCellsUsedMax = iCellsUsedMax;
    iLock.Signal();
}

AllocatorBase::AllocatorBase(const TChar* aName, TUint aNumCells, TUint aCellBytes, Av::IInfoAggregator& aInfoAggregator)
    : iFree(aNumCells)
    , iLock("PLAL")
    , iName(aName)
    , iCellsTotal(aNumCells)
    , iCellBytes(aCellBytes)
    , iCellsUsed(0)
    , iCellsUsedMax(0)
{
    std::vector<Brn> infoQueries;
    infoQueries.push_back(kQueryMemory);
    aInfoAggregator.Register(*this, infoQueries);
}

Allocated* AllocatorBase::DoAllocate()
{
    Allocated* cell;
    try {
        cell = iFree.Read(1); // FIXME - use ReadImmediate instead
        cell->iRefCount = 1;
    }
    catch (Timeout& ) {
        THROW(AllocatorNoMemory);
    }
    iLock.Wait();
    iCellsUsed++;
    if (iCellsUsed > iCellsUsedMax) {
        iCellsUsedMax = iCellsUsed;
    }
    iLock.Signal();
    return cell;
}

void AllocatorBase::QueryInfo(const Brx& aQuery, IWriter& aWriter)
{
    // Note that value of iCellsUsed may be slightly out of date as Allocator doesn't hold any lock while updating its fifo and iCellsUsed
    AutoMutex a(iLock);
    if (aQuery == kQueryMemory) {
        WriterAscii writer(aWriter);
        writer.Write(Brn("Allocator: "));
        writer.Write(Brn(iName));
        writer.Write(Brn(", capacity:"));
        writer.WriteUint(iCellsTotal);
        writer.Write(Brn(" cells x "));
        writer.WriteUint(iCellBytes);
        writer.Write(Brn(" bytes, in use:"));
        writer.WriteUint(iCellsUsed);
        writer.Write(Brn(" cells, peak:"));
        writer.WriteUint(iCellsUsedMax);
        aWriter.Write(Brn(" cells\n"));
    }
}


// Allocated

void Allocated::AddRef()
{
    iLock.Wait();
    iRefCount++;
    iLock.Signal();
}

void Allocated::RemoveRef()
{
    iLock.Wait();
    TBool free = (--iRefCount == 0);
    iLock.Signal();
    if (free) {
        Clear();
        iAllocator.Free(this);
    }
}

void Allocated::Clear()
{
}

Allocated::Allocated(AllocatorBase& aAllocator)
    : iAllocator(aAllocator)
    , iLock("ALOC")
    , iRefCount(1)
{
}

Allocated::~Allocated()
{
}

    
// Msg

Msg::Msg(AllocatorBase& aAllocator)
    : Allocated(aAllocator)
{
}


// DecodedAudio

DecodedAudio::DecodedAudio(AllocatorBase& aAllocator)
    : Allocated(aAllocator)
{
}

const TUint* DecodedAudio::Ptr() const
{
    return &iSubsamples[0];
}

const TUint* DecodedAudio::PtrOffsetSamples(TUint aSamples) const
{
    const TUint index = aSamples * iChannels;
    ASSERT(index < iSubsampleCount);
    return &iSubsamples[index];
}

const TUint* DecodedAudio::PtrOffsetBytes(TUint aBytes) const
{
    ASSERT(aBytes % 4 == 0);
    TUint index = aBytes/4;
    return &iSubsamples[index];
}

const TUint* DecodedAudio::PtrOffsetBytes(const TUint* aFrom, TUint aBytes) const
{
    TUint offset = (TUint)(aFrom - &iSubsamples[0]) * sizeof(iSubsamples[0]);
    offset += aBytes;
    return PtrOffsetBytes(offset);
}

TUint DecodedAudio::Bytes() const
{
    return iSubsampleCount * 4;
}

void DecodedAudio::Construct(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian)
{
    iChannels = aChannels;
    iSampleRate = aSampleRate;
    iBitRate = 0xffffffff; // FIXME
    iBitDepth = aBitDepth;

    ASSERT((aBitDepth & 7) == 0);
    TUint bytesPerSubsample = aBitDepth/8;
    ASSERT(aData.Bytes() % bytesPerSubsample == 0);
    iSubsampleCount = aData.Bytes() / bytesPerSubsample;
    ASSERT(iSubsampleCount <= kMaxSubsamples);
    if (aEndian == EMediaDataLittleEndian) {
        UnpackLittleEndian(iSubsamples, aData.Ptr(), iBitDepth, iSubsampleCount);
    }
    else { // EMediaDataBigEndian
        UnpackBigEndian(iSubsamples, aData.Ptr(), iBitDepth, iSubsampleCount);
    }
}

// FIXME - unpackers are from big-endian volkano codebase.  Do we need little-endian versions too?
void DecodedAudio::UnpackBigEndian(TUint32* aDst, const TUint8* aSrc, TUint aBitDepth, TUint aNumSubsamples)
{ // static
    TUint i = 0;

    switch (aBitDepth)
    {
        case 8:
            for (i=0; i < aNumSubsamples; i++) {
                *aDst++ = (*aSrc++ << 24);
            }
            break;
        case 16:
            for (i=0; i < aNumSubsamples; i++) {
                *aDst++ = (Arch::BigEndian2(*((TUint16*)aSrc)) << 16);
                aSrc += 2;
            }
            break;
        case 24:
            for (i=0; i < aNumSubsamples; i++) {
                *aDst++ = ((aSrc[2] | (aSrc[1]<<8) | (aSrc[0]<<16)) << 8);
                aSrc += 3;
            }
            break;
        default:
            ASSERTS();
    }
}

void DecodedAudio::UnpackLittleEndian(TUint32* aDst, const TUint8* aSrc, TUint aBitDepth, TUint aNumSubsamples)
{ // static
    TUint i = 0;

    switch (aBitDepth)
    {
        case 8:
            for (i=0; i < aNumSubsamples; i++) {
                *aDst++ = (*aSrc++ << 24);
            }
            break;
        case 16:
            for (i=0; i < aNumSubsamples; i++) {
                *aDst++ = (Arch::LittleEndian2(*((TUint16*)aSrc)) << 16);
                aSrc += 2;
            }
            break;
        case 24:
            for (i=0; i < aNumSubsamples; i++) {
                *aDst++ = (((aSrc[2]<<16) | (aSrc[1]<<8) | aSrc[0]) << 8);
                aSrc += 3;
            }
            break;
        default:
            ASSERTS();
    }
}


// MsgAudio

MsgAudio::MsgAudio(AllocatorBase& aAllocator)
    : Msg(aAllocator)
    , iNext(NULL)
{
}

void MsgAudio::Construct(DecodedAudio* aDecodedAudio)
{
    iAudioData = aDecodedAudio;
    iNext = NULL;
    iPtr = iAudioData->Ptr();
    iBytes = iAudioData->Bytes();
}

MsgAudio* MsgAudio::SplitJiffies(TUint64 /*aAt*/)
{
    return NULL;
}

MsgAudio* MsgAudio::SplitBytes(TUint aAt)
{
    if (aAt > iBytes) {
        ASSERT(iNext != NULL);
        return iNext->SplitBytes(aAt - iBytes);
    }
    ASSERT(aAt != iBytes);
    MsgAudio* remaining = static_cast<Allocator<MsgAudio>&>(iAllocator).Allocate();
    iAudioData->AddRef();
    remaining->iAudioData = iAudioData;
    remaining->iNext = NULL;
    remaining->iPtr = iAudioData->PtrOffsetBytes(iPtr, aAt);
    remaining->iBytes = iBytes - aAt;
    iBytes = aAt;
    return remaining;
}

void MsgAudio::Add(MsgAudio* aMsg)
{
    MsgAudio* end = this;
    MsgAudio* next = iNext;
    while (next != NULL) {
        end = next;
        next = next->iNext;
    }
    end->iNext = aMsg;
}

void MsgAudio::CopyTo(TUint* aDest)
{
    (void)memcpy(aDest, iPtr, iBytes);
    if (iNext != NULL) {
        iNext->CopyTo(aDest + (iBytes / sizeof(TUint)));
    }
    RemoveRef();
}

MsgAudio* MsgAudio::Clone()
{
    MsgAudio* clone = static_cast<Allocator<MsgAudio>&>(iAllocator).Allocate();
    clone->iAudioData = iAudioData;
    iAudioData->AddRef();
    clone->iPtr = iPtr;
    clone->iBytes = iBytes;
    clone->iNext = (iNext == NULL? NULL : iNext->Clone());
    return clone;
}

TUint MsgAudio::Bytes() const
{
    TUint bytes = iBytes;
    if (iNext != NULL) {
        bytes += iNext->Bytes();
    }
    return bytes;
}

void MsgAudio::Clear()
{
    iAudioData->RemoveRef();
}

void MsgAudio::Process(IMsgProcessor& aProcessor)
{
    aProcessor.ProcessMsg(*this);
}


// MsgTrack

MsgTrack::MsgTrack(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

void MsgTrack::Process(IMsgProcessor& aProcessor)
{
    aProcessor.ProcessMsg(*this);
}


// MsgStartOfAudio

MsgStartOfAudio::MsgStartOfAudio(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

void MsgStartOfAudio::Process(IMsgProcessor& aProcessor)
{
    aProcessor.ProcessMsg(*this);
}


// MsgMetaText

MsgMetaText::MsgMetaText(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

void MsgMetaText::Process(IMsgProcessor& aProcessor)
{
    aProcessor.ProcessMsg(*this);
}


// MsgFactory

MsgFactory::MsgFactory(Av::IInfoAggregator& aInfoAggregator, TUint aDecodedAudioCount, TUint aMsgAudioCount, TUint aMsgTrackCount, TUint aMsgMetaTextCount)
    : iAllocatorDecodedAudio("DecodedAudio", aDecodedAudioCount, aInfoAggregator)
    , iAllocatorMsgAudio("MsgAudio", aMsgAudioCount, aInfoAggregator)
    , iAllocatorMsgTrack("MsgTrack", aMsgTrackCount, aInfoAggregator)
    , iAllocatorMsgMetaText("MsgMetaText", aMsgMetaTextCount, aInfoAggregator)
{
}

MsgAudio* MsgFactory::CreateMsgAudio(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian)
{
    DecodedAudio* DecodedAudio = CreateDecodedAudio(aData, aChannels, aSampleRate, aBitDepth, aEndian);
    MsgAudio* msgAudio = iAllocatorMsgAudio.Allocate();
    msgAudio->Construct(DecodedAudio);
    return msgAudio;
}

MsgTrack* MsgFactory::CreateMsgTrack()
{
    return iAllocatorMsgTrack.Allocate();
}

MsgMetaText* MsgFactory::CreateMsgMetaText()
{
    return iAllocatorMsgMetaText.Allocate();
}

DecodedAudio* MsgFactory::CreateDecodedAudio(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian)
{
    DecodedAudio* DecodedAudio = iAllocatorDecodedAudio.Allocate();
    DecodedAudio->Construct(aData, aChannels, aSampleRate, aBitDepth, aEndian);
    return DecodedAudio;
}
