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
    //Log::Print("~AllocatorBase for %s, freeing...", iName);
    const TUint slots = iFree.Slots();
    for (TUint i=0; i<slots; i++) {
        //Log::Print("  %u", i);
        Allocated* ptr = iFree.Read();
        //Log::Print("(%p)", ptr);
        delete ptr;
    }
    //Log::Print("\n");
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
    ASSERT(aBytes % (kBytesPerSubsample * iChannels) == 0);
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

TUint DecodedAudio::BytesFromJiffies(TUint& aJiffies) const
{
    aJiffies -= aJiffies % iJiffiesPerSample; // round down requested aJiffies to the nearest integer number of samples
    const TUint numSamples = aJiffies / iJiffiesPerSample;
    const TUint numSubsamples = numSamples * iChannels;
    const TUint bytes = numSubsamples * kBytesPerSubsample;
    return bytes;
}

TUint DecodedAudio::JiffiesFromBytes(TUint aBytes) const
{
    ASSERT(aBytes % kBytesPerSubsample == 0);
    const TUint numSubsamples = aBytes / kBytesPerSubsample;
    ASSERT(numSubsamples % iChannels == 0);
    const TUint jiffies = (numSubsamples / iChannels) * iJiffiesPerSample;
    return jiffies;
}

void DecodedAudio::Construct(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian)
{
    iChannels = aChannels;
    iSampleRate = aSampleRate;
    iBitRate = 0xffffffff; // FIXME
    iBitDepth = aBitDepth;
    iJiffiesPerSample = JiffiesPerSample();

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

TUint DecodedAudio::JiffiesPerSample() const
{
    switch (iSampleRate)
    {
    case 7350:
        return kJiffies7350;
    case 8000:
        return kJiffies8000;
    case 11025:
        return kJiffies11025;
    case 12000:
        return kJiffies12000;
    case 14700:
        return kJiffies14700;
    case 16000:
        return kJiffies16000;
    case 22050:
        return kJiffies22050;
    case 24000:
        return kJiffies24000;
    case 29400:
        return kJiffies29400;
    case 32000:
        return kJiffies32000;
    case 44100:
        return kJiffies44100;
    case 48000:
        return kJiffies48000;
    case 88200:
        return kJiffies88200;
    case 96000:
        return kJiffies96000;
    case 176400:
        return kJiffies176400;
    case 192000:
        return kJiffies192000;
    default:
        ASSERTS();
    }
    return 0; // will never get here but compiler doesn't realise that ASSERTS doesn't return
}


// Msg

Msg::Msg(AllocatorBase& aAllocator)
    : Allocated(aAllocator)
    , iNextMsg(NULL)
{
}


// MsgAudio

MsgAudio::MsgAudio(AllocatorBase& aAllocator)
    : Msg(aAllocator)
    , iNextAudio(NULL)
{
}

void MsgAudio::Construct(DecodedAudio* aDecodedAudio)
{
    iAudioData = aDecodedAudio;
    iNextAudio = NULL;
    iPtr = iAudioData->Ptr();
    iBytes = iAudioData->Bytes();
}

MsgAudio* MsgAudio::SplitJiffies(TUint& aAt)
{
    if (aAt > iJiffies) {
        ASSERT(iNextAudio != NULL);
        return iNextAudio->SplitBytes(aAt - iJiffies);
    }
    ASSERT(aAt != iJiffies);
    MsgAudio* remaining = static_cast<Allocator<MsgAudio>&>(iAllocator).Allocate();
    iAudioData->AddRef();
    remaining->iAudioData = iAudioData;
    remaining->iNextAudio = NULL;
    const TUint bytes = iAudioData->BytesFromJiffies(aAt);
    remaining->iPtr = iAudioData->PtrOffsetBytes(iPtr, bytes);
    remaining->iBytes = iBytes - bytes;
    remaining->iJiffies = aAt;
    iBytes = bytes;
    return remaining;
}

MsgAudio* MsgAudio::SplitBytes(TUint aAt)
{
    if (aAt > iBytes) {
        ASSERT(iNextAudio != NULL);
        return iNextAudio->SplitBytes(aAt - iBytes);
    }
    ASSERT(aAt != iBytes);
    MsgAudio* remaining = static_cast<Allocator<MsgAudio>&>(iAllocator).Allocate();
    iAudioData->AddRef();
    remaining->iAudioData = iAudioData;
    remaining->iNextAudio = NULL;
    remaining->iPtr = iAudioData->PtrOffsetBytes(iPtr, aAt);
    remaining->iBytes = iBytes - aAt;
    remaining->iJiffies = iAudioData->JiffiesFromBytes(remaining->iBytes);
    iBytes = aAt;
    iJiffies = iAudioData->JiffiesFromBytes(iBytes);
    return remaining;
}

void MsgAudio::Add(MsgAudio* aMsg)
{
    MsgAudio* end = this;
    MsgAudio* next = iNextAudio;
    while (next != NULL) {
        end = next;
        next = next->iNextAudio;
    }
    end->iNextAudio = aMsg;
}

void MsgAudio::CopyTo(TUint* aDest)
{
    (void)memcpy(aDest, iPtr, iBytes);
    if (iNextAudio != NULL) {
        iNextAudio->CopyTo(aDest + (iBytes / sizeof(TUint)));
        iNextAudio = NULL; // break chain before Clear() gets called and tries removing the reference we remove on function exit
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
    clone->iJiffies = iJiffies;
    clone->iNextAudio = (iNextAudio == NULL? NULL : iNextAudio->Clone());
    return clone;
}

TUint MsgAudio::Bytes() const
{
    TUint bytes = iBytes;
    if (iNextAudio != NULL) {
        bytes += iNextAudio->Bytes();
    }
    return bytes;
}

TUint MsgAudio::Jiffies() const
{
    TUint jiffies = iJiffies;
    if (iNextAudio != NULL) {
        jiffies += iNextAudio->Jiffies();
    }
    return jiffies;
}

void MsgAudio::Clear()
{
    iAudioData->RemoveRef();
    if (iNextAudio != NULL) {
        iNextAudio->RemoveRef();
    }
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


// MsgQueue

MsgQueue::MsgQueue()
    : iLock("MSGQ")
    , iSem("MSGQ", 0)
    , iHead(NULL)
    , iTail(NULL)
{
}

MsgQueue::~MsgQueue()
{
    iLock.Wait();
    Msg* head = iHead;
    while (head != NULL) {
        iHead = head->iNextMsg;
        head->RemoveRef();
        head = iHead;
    }
    iLock.Signal();
}

void MsgQueue::Enqueue(Msg* aMsg)
{
    ASSERT(aMsg != NULL);
    iLock.Wait();
    if (iHead == NULL) {
        iHead = aMsg;
    }
    else {
        iTail->iNextMsg = aMsg;
    }
    iTail = aMsg;
    aMsg->iNextMsg = NULL;
    iSem.Signal();
    iLock.Signal();
}

Msg* MsgQueue::Dequeue()
{
    iSem.Wait();
    iLock.Wait();
    ASSERT(iHead != NULL);
    Msg* head = iHead;
    iHead = iHead->iNextMsg;
    head->iNextMsg = NULL; // not strictly necessary but might make debugging simpler
    if (iHead == NULL) {
        iTail = NULL;
    }
    iLock.Signal();
    return head;
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
