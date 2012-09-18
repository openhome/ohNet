#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/RampArray.h>
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

#ifndef MIN
# define MIN(a, b) ((a) < (b)? (a) : (b))
#endif // MIN

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

    
// Jiffies

TUint Jiffies::JiffiesPerSample(TUint aSampleRate)
{ // static
    switch (aSampleRate)
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

TUint Jiffies::BytesFromJiffies(TUint& aJiffies, TUint aJiffiesPerSample, TUint aNumChannels, TUint aBytesPerSubsample)
{ // static
    aJiffies -= aJiffies % aJiffiesPerSample; // round down requested aJiffies to the nearest integer number of samples
    const TUint numSamples = aJiffies / aJiffiesPerSample;
    const TUint numSubsamples = numSamples * aNumChannels;
    const TUint bytes = numSubsamples * aBytesPerSubsample;
    return bytes;
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
    return Jiffies::BytesFromJiffies(aJiffies, iJiffiesPerSample, iChannels, kBytesPerSubsample);
}

TUint DecodedAudio::JiffiesFromBytes(TUint aBytes) const
{
    ASSERT(aBytes % kBytesPerSubsample == 0);
    const TUint numSubsamples = aBytes / kBytesPerSubsample;
    ASSERT(numSubsamples % iChannels == 0);
    const TUint jiffies = (numSubsamples / iChannels) * iJiffiesPerSample;
    return jiffies;
}

TUint DecodedAudio::NumChannels() const
{
    return iChannels;
}

void DecodedAudio::Construct(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian)
{
    iChannels = aChannels;
    iSampleRate = aSampleRate;
    iBitRate = 0xffffffff; // FIXME
    iBitDepth = aBitDepth;
    iJiffiesPerSample = Jiffies::JiffiesPerSample(aSampleRate);

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

void DecodedAudio::Clear()
{
#ifdef DEFINE_DEBUG
    // fill in all members with recognisable 'bad' values to make ref counting bugs more obvious
    static const TUint deadByte = 0xde;
    static const TUint deadUint = 0xdead;
    memset(&iSubsamples[0], deadByte, kMaxSubsamples * sizeof(iSubsamples[0]));
    iSubsampleCount = deadUint;
    iChannels = deadUint;
    iSampleRate = deadUint;
    iBitRate = deadUint;
    iBitDepth = deadUint;
    iJiffiesPerSample = deadUint;
#endif // DEFINE_DEBUG
}


// Msg

Msg::Msg(AllocatorBase& aAllocator)
    : Allocated(aAllocator)
    , iNextMsg(NULL)
{
}


// Ramp

Ramp::Ramp()
{
    Reset();

    // confirm some assumptions made elsewhere in this class
    // these could be compile-time or one-off run-time assertions
#ifdef _WIN32
# pragma warning (disable: 4127)
#endif // _WIN32
    ASSERT_DEBUG(kRampMax <= 1<<30); // some 32-bit values in ramp calculations should become 64-bit if this increases
    ASSERT_DEBUG(kRampArrayCount == 512); // <<22 and >>23 code needs review if this changes
}

void Ramp::Reset()
{
    iStart = kRampMax;
    iEnd = kRampMax;
    iDirection = ENone;
    iEnabled = false;
}

TBool Ramp::Set(TUint aStart, TUint aFragmentSize, TUint aRampDuration, EDirection aDirection, Ramp& aSplit, TUint& aSplitPos)
{
    ASSERT(aRampDuration >  aFragmentSize || ((aStart == kRampMax ||aStart == kRampMin) && aRampDuration ==  aFragmentSize));
    ASSERT(aDirection != ENone);
    iEnabled = true;
    aSplit.Reset();
    aSplitPos = 0xffffffff;
    TUint rampDelta = (kRampMax * (TUint64)aFragmentSize) / aRampDuration;
    TUint rampEnd = aDirection == EDown? (TUint)(aStart - rampDelta) : aStart + rampDelta;
    if (aDirection == EDown) {
        ASSERT(rampDelta <= aStart);
    }
    else {
        ASSERT(rampEnd <= kRampMax);
    }
    if (iDirection == ENone) {
        // No previous ramp.  Trivial to apply the suggested values
        iDirection = aDirection;
        iStart = aStart;
        iEnd = rampEnd;
    }
    else if (iDirection == aDirection) {
        // New ramp runs in the same direction as existing one.  Choose the lower start/end points
        SelectLowerRampPoints(aStart, rampEnd);
    }
    else {
        // Previous and new ramps run in opposite directions.
        // Calculate the point at which they intersect.
        // ... if they don't intersect, use the new values
        // ...if they do intersect, split the message, selecting ramp with lower start for first and lower end for second
        /*
        We start with two lines defined by the points
            (0, y1), (aFragmentSize, y2)
            (0, y3), (aFragmentSize, y4)
        ...we can describe these using the equations y=mx+b & y=nx+c
        ...where y=mx+b has the lower initial y pos (start ramp)
        ...we calculate m, n as follows
            m=(y2-y1)/aFragmentSize
            n=(y4-y3)/aFragmentSize
        ... then x, y as follows
            x=(y3-y1)/(m-n)
            y=((iEnd-iStart)/aFragmentSize) * x + iStart
        If x is outside 0..aFragmentSize then the ramps don't intersect during this message
        ...in this case we fall back to choosing the lower values for start/end

        To avoid rounding errors ('slopes' m,n may be fractional) we change the calculations to
            x=(aFragmentSize*(y3-y1))/((y2-y1)-(y4-y3))
            y=((y2-y1)*(y3-y1))/((y2-y1)-(y4-y3)) + y1
        */
        TUint y1, y2, y3, y4;
        if (iStart < aStart) {
            y1 = iStart;
            y2 = iEnd;
            y3 = aStart;
            y4 = rampEnd;
        }
        else {
            y1 = aStart;
            y2 = rampEnd;
            y3 = iStart;
            y4 = iEnd;
        }
        if ((y2-y1) == (y4-y3)) {
            // ramp lines are parallel so won't ever intersect
            SelectLowerRampPoints(aStart, rampEnd);
        }
        else {
            TInt intersectX = ((TInt64)aFragmentSize*(y3-y1))/((y2-y1)-(y4-y3));
            TUint intersectY = (((TUint64)y2-y1)*(y3-y1))/((y2-y1)-(y4-y3)) + y1;
            // calculation of intersectY may overflow a TUint.
            // intersectX will tell us we have no useful intersection in these cases and we'll ignore the Y value.
            if (intersectX < 0 || (TUint)intersectX > aFragmentSize) {
                // ramp lines don't intersect inside this Msg
                SelectLowerRampPoints(aStart, rampEnd);
            }
            else {
                // split this Ramp; the first portion rises to the intersection of the two ramps, the second drops to the lower final value
                aSplitPos = intersectX;
                aSplit.iStart = intersectY;
                aSplit.iEnd = MIN(iEnd, rampEnd);
                aSplit.iDirection = EDown;
                aSplit.iEnabled = true;
                iDirection = EUp;
                iStart = MIN(iStart, aStart);
                iEnd = intersectY;
            }
        }
    }
    return aSplit.IsEnabled();
}

void Ramp::SelectLowerRampPoints(TUint aRequestedStart, TUint aRequestedEnd)
{
    iStart = MIN(iStart, aRequestedStart);
    iEnd = MIN(iEnd, aRequestedEnd);
    if (iStart == iEnd) {
        iDirection = ENone;
    }
    else if (iStart > iEnd) {
        iDirection = EDown;
    }
    else { // iStart < iEnd
        iDirection = EUp;
    }
}

Ramp Ramp::Split(TUint aNewSize, TUint aCurrentSize)
{
    Ramp remaining;
    remaining.iEnd = iEnd;
    remaining.iDirection = iDirection;
    remaining.iEnabled = true;
    TInt ramp = ((iStart-iEnd) * (TInt64)aNewSize) / aCurrentSize;
    iEnd = iStart + ramp;
    remaining.iStart = iEnd;
    return remaining;
}

void Ramp::Apply(Bwx& aData, TUint aChannels)
{
    ASSERT_DEBUG(aData.Bytes() % (DecodedAudio::kBytesPerSubsample * aChannels) == 0);
    TUint* ptr = (TUint*)aData.Ptr(); // looks dodgy but we can safely assume ptr is writable and on a word boundary
    const TUint numSamples = aData.Bytes() / (DecodedAudio::kBytesPerSubsample * aChannels);
    const TInt totalRamp = iStart - iEnd;
    const TUint fullRampSpan = kRampMax - kRampMin;
    for (TUint i=0; i<numSamples; i++) {
        const TUint ramp = (TUint)(iStart - ((i * (TInt64)totalRamp)/(numSamples-1)));
        //Log::Print(" %08x ", ramp);
        TUint rampIndex = (fullRampSpan - ramp + (1<<20)) >> 21; // assumes fullRampSpan==2^31 and kRampArray has 512 items. (1<<20 allows rounding up)
        for (TUint j=0; j<aChannels; j++) { // apply ramp to each subsample
            TUint subSample = *ptr;
            //Log::Print(" %03u ", rampIndex);
            TUint rampedSubsample = (rampIndex==512? 0 : ((TUint64)subSample * kRampArray[rampIndex]) >> 31); // >>31 assumes kRampArray values are 32-bit, signed & positive
            rampedSubsample &= ~0xff; // clear bits which never hold audio data
            //Log::Print("Original=%08x, ramped=%08x, rampIndex=%u\n", *ptr, rampedSubsample, rampIndex);
            *ptr = rampedSubsample;
            ptr++;
        }
    }
}


// MsgAudio

MsgAudio* MsgAudio::Split(TUint aJiffies)
{
    if (aJiffies > iSize) {
        ASSERT(iNextAudio != NULL);
        return iNextAudio->Split(aJiffies - iSize);
    }
    ASSERT(aJiffies > 0);
    ASSERT(aJiffies < iSize);
    MsgAudio* remaining = Allocate();
    remaining->iNextAudio = NULL;
    remaining->iOffset = iOffset + aJiffies;
    remaining->iSize = iSize - aJiffies;
    if (iRamp.IsEnabled()) {
        remaining->iRamp = iRamp.Split(aJiffies, iSize);
    }
    else {
        remaining->iRamp.Reset();
    }
    iSize = aJiffies;
    SplitCompleted(*remaining);
    return remaining;
}
/*
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
*/
MsgAudio* MsgAudio::Clone()
{
    MsgAudio* clone = Allocate();
    clone->iSize = iSize;
    clone->iOffset = iOffset;
    clone->iRamp = iRamp;
    clone->iNextAudio = (iNextAudio == NULL? NULL : iNextAudio->Clone());
    return clone;
}

TUint MsgAudio::Jiffies() const
{
    TUint jiffies = iSize;
    MsgAudio* next = iNextAudio;
    while (next != NULL) {
        jiffies += iNextAudio->iSize;
        next = next->iNextAudio;
    }
    return jiffies;
}

TUint MsgAudio::SetRamp(TUint aStart, TUint aDuration, Ramp::EDirection aDirection, MsgAudio*& aSplit)
{
    Ramp split;
    TUint splitPos;
    TUint rampEnd;
    if (iRamp.Set(aStart, iSize, aDuration, aDirection, split, splitPos)) {
        Ramp ramp = iRamp; // Split() will muck about with ramps.  Allow this to happen then reset the correct values
        aSplit = Split(splitPos);
        iRamp = ramp;
        aSplit->iRamp = split;
        rampEnd = split.End();
        ASSERT_DEBUG(iRamp.End() == split.Start());
        //Log::Print("\nSplit msg at %u jiffies.  First ramp=[%08x...%08x], second ramp=[%08x...%08x]\n",
        //            splitPos, iRamp.Start(), iRamp.End(), split.Start(), split.End());
    }
    else {
        rampEnd = iRamp.End();
    }
    return rampEnd;
}

MsgAudio::MsgAudio(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

void MsgAudio::Initialise()
{
    iNextAudio = NULL;
    iRamp.Reset();
}

void MsgAudio::Clear()
{
    if (iNextAudio != NULL) {
        iNextAudio->RemoveRef();
    }
}

void MsgAudio::SplitCompleted(MsgAudio& /*aMsg*/)
{
    // nothing to do by default
}


// MsgAudioPcm

MsgAudioPcm::MsgAudioPcm(AllocatorBase& aAllocator)
    : MsgAudio(aAllocator)
{
}

MsgPlayable* MsgAudioPcm::CreatePlayable()
{
    TUint offsetJiffies = iOffset;
    const TUint offsetBytes = iAudioData->BytesFromJiffies(offsetJiffies);
    TUint sizeJiffies = iSize + (iOffset - offsetJiffies);
    const TUint sizeBytes = iAudioData->BytesFromJiffies(sizeJiffies);
    // both size & offset will be rounded down if they don't fall on a sample boundary
    // we don't risk losing any data doing this as the start and end of each DecodedAudio's data fall on sample boundaries

    MsgPlayablePcm* playable = iAllocatorPlayable->Allocate();
    playable->Initialise(iAudioData, sizeBytes, offsetBytes, iRamp);
    if (iNextAudio != NULL) {
        MsgPlayable* child = static_cast<MsgAudioPcm*>(iNextAudio)->CreatePlayable();
        playable->Add(child);
    }
    RemoveRef();
    return playable;
}

MsgAudio* MsgAudioPcm::Clone()
{
    MsgAudio* clone = MsgAudio::Clone();
    static_cast<MsgAudioPcm*>(clone)->iAudioData = iAudioData;
    iAudioData->AddRef();
    return clone;
}

void MsgAudioPcm::Initialise(DecodedAudio* aDecodedAudio, Allocator<MsgPlayablePcm>& aAllocatorPlayable)
{
    MsgAudio::Initialise();
    iAllocatorPlayable = &aAllocatorPlayable;
    iAudioData = aDecodedAudio;
    iSize = iAudioData->JiffiesFromBytes(iAudioData->Bytes());
    iOffset = 0;
}

void MsgAudioPcm::SplitCompleted(MsgAudio& aRemaining)
{
    iAudioData->AddRef();
    MsgAudioPcm& remaining = static_cast<MsgAudioPcm&>(aRemaining);
    remaining.iAudioData = iAudioData;
    remaining.iAllocatorPlayable = iAllocatorPlayable;
}

MsgAudio* MsgAudioPcm::Allocate()
{
    return static_cast<Allocator<MsgAudioPcm>&>(iAllocator).Allocate();
}

void MsgAudioPcm::Clear()
{
    MsgAudio::Clear();
    iAudioData->RemoveRef();
}

Msg* MsgAudioPcm::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgSilence

MsgSilence::MsgSilence(AllocatorBase& aAllocator)
    : MsgAudio(aAllocator)
{
}

MsgPlayable* MsgSilence::CreatePlayable(TUint aSampleRate, TUint aNumChannels)
{
    TUint offsetJiffies = iOffset;
    TUint jiffiesPerSample = Jiffies::JiffiesPerSample(aSampleRate);
    TUint sizeJiffies = iSize + (iOffset - offsetJiffies);
    TUint sizeBytes = Jiffies::BytesFromJiffies(sizeJiffies, jiffiesPerSample, aNumChannels, DecodedAudio::kBytesPerSubsample);

    MsgPlayableSilence* playable = iAllocatorPlayable->Allocate();
    playable->Initialise(sizeBytes, iRamp);
    if (iNextAudio != NULL) {
        MsgPlayable* child = static_cast<MsgSilence*>(iNextAudio)->CreatePlayable(aSampleRate, aNumChannels);
        playable->Add(child);
    }
    RemoveRef();
    return playable;
}

MsgAudio* MsgSilence::Allocate()
{
    return static_cast<Allocator<MsgSilence>&>(iAllocator).Allocate();
}

Msg* MsgSilence::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}

void MsgSilence::SplitCompleted(MsgAudio& aRemaining)
{
    static_cast<MsgSilence&>(aRemaining).iAllocatorPlayable = iAllocatorPlayable;
}

void MsgSilence::Initialise(TUint aJiffies, Allocator<MsgPlayableSilence>& aAllocatorPlayable)
{
    MsgAudio::Initialise();
    iAllocatorPlayable = &aAllocatorPlayable;
    iSize = aJiffies;
    iOffset = 0;
}


// MsgPlayable

MsgPlayable* MsgPlayable::Split(TUint aBytes)
{
    if (aBytes > iSize) {
        ASSERT(iNextPlayable != NULL);
        return iNextPlayable->Split(aBytes - iSize);
    }
    ASSERT(aBytes != 0);
    ASSERT(aBytes < iSize);
    MsgPlayable* remaining = Allocate();
    remaining->iNextPlayable = NULL;
    remaining->iOffset = iOffset + aBytes;
    remaining->iSize = iSize - aBytes;
    if (iRamp.IsEnabled()) {
        remaining->iRamp = iRamp.Split(aBytes, iSize);
    }
    else {
        remaining->iRamp.Reset();
    }
    iSize = aBytes;
    SplitCompleted(*remaining);
    return remaining;
}

void MsgPlayable::Add(MsgPlayable* aMsg)
{
    MsgPlayable* end = this;
    MsgPlayable* next = iNextPlayable;
    while (next != NULL) {
        end = next;
        next = next->iNextPlayable;
    }
    end->iNextPlayable = aMsg;
}

MsgPlayable* MsgPlayable::Clone()
{
    MsgPlayable* clone = Allocate();
    clone->iSize = iSize;
    clone->iOffset = iOffset;
    clone->iRamp = iRamp;
    clone->iNextPlayable = (iNextPlayable == NULL? NULL : iNextPlayable->Clone());
    return clone;
}

TUint MsgPlayable::Bytes() const
{
    TUint bytes = iSize;
    MsgPlayable* next = iNextPlayable;
    while (next != NULL) {
        bytes += iNextPlayable->Bytes();
        next = next->iNextPlayable;
    }
    return bytes;
}

MsgPlayable::MsgPlayable(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

void MsgPlayable::Initialise(TUint aSizeBytes, TUint aOffsetBytes, const Ramp& aRamp)
{
    iNextPlayable = NULL;
    iSize = aSizeBytes;
    iOffset = aOffsetBytes;
    iRamp = aRamp;
}

void MsgPlayable::Clear()
{
    if (iNextPlayable != NULL) {
        iNextPlayable->RemoveRef();
    }
}

Msg* MsgPlayable::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}

void MsgPlayable::SplitCompleted(MsgPlayable& /*aMsg*/)
{
    // nothing to do by default
}


// MsgPlayablePcm

MsgPlayablePcm::MsgPlayablePcm(AllocatorBase& aAllocator)
    : MsgPlayable(aAllocator)
{
}

void MsgPlayablePcm::Initialise(DecodedAudio* aDecodedAudio, TUint aSizeBytes, TUint aOffsetBytes, const Ramp& aRamp)
{
    MsgPlayable::Initialise(aSizeBytes, aOffsetBytes, aRamp);
    iAudioData = aDecodedAudio;
    iAudioData->AddRef();
}

MsgPlayable* MsgPlayablePcm::Clone()
{
    MsgPlayable* clone = MsgPlayable::Clone();
    static_cast<MsgPlayablePcm*>(clone)->iAudioData = iAudioData;
    iAudioData->AddRef();
    return clone;
}

void MsgPlayablePcm::Write(IWriter& aWriter)
{
    AutoRef a(*this);
    
    Bwn audioBuf((const TByte*)iAudioData->PtrOffsetBytes(iOffset), iSize, iSize);
    if (iRamp.IsEnabled()) {
        iRamp.Apply(audioBuf, iAudioData->NumChannels());
    }
    aWriter.Write(audioBuf);

    MsgPlayable* next = iNextPlayable;
    iNextPlayable = NULL; // break chain before Clear() gets called and tries removing the reference we remove on function exit
    if (next != NULL) {
        next->Write(aWriter);
    }
}

MsgPlayable* MsgPlayablePcm::Allocate()
{
    return static_cast<Allocator<MsgPlayablePcm>&>(iAllocator).Allocate();
}

void MsgPlayablePcm::SplitCompleted(MsgPlayable& aRemaining)
{
    iAudioData->AddRef();
    static_cast<MsgPlayablePcm&>(aRemaining).iAudioData = iAudioData;
}

void MsgPlayablePcm::Clear()
{
    MsgPlayable::Clear();
    iAudioData->RemoveRef();
}


// MsgPlayableSilence

MsgPlayableSilence::MsgPlayableSilence(AllocatorBase& aAllocator)
    : MsgPlayable(aAllocator)
{
}

void MsgPlayableSilence::Initialise(TUint aSizeBytes, const Ramp& aRamp)
{
    MsgPlayable::Initialise(aSizeBytes, 0, aRamp);
}

void MsgPlayableSilence::Write(IWriter& aWriter)
{
    static const TUint kSizeBufSilence = 4096;
    static const TByte silence[kSizeBufSilence] = { 0 };

    AutoRef a(*this);
    Brn silenceBuf;
    while (iSize > 0) {
        TUint bytes = (iSize > kSizeBufSilence? kSizeBufSilence : iSize);
        silenceBuf.Set(silence, bytes);
        aWriter.Write(silenceBuf);
        iSize -= bytes;
    }
    MsgPlayable* next = iNextPlayable;
    iNextPlayable = NULL; // break chain before Clear() gets called and tries removing the reference we remove on function exit
    if (next != NULL) {
        next->Write(aWriter);
    }
}

MsgPlayable* MsgPlayableSilence::Allocate()
{
    return static_cast<Allocator<MsgPlayableSilence>&>(iAllocator).Allocate();
}


// MsgTrack

MsgTrack::MsgTrack(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

Msg* MsgTrack::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgMetaText

MsgMetaText::MsgMetaText(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

Msg* MsgMetaText::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgHalt

MsgHalt::MsgHalt(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

Msg* MsgHalt::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgFlush

MsgFlush::MsgFlush(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

Msg* MsgFlush::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
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

void MsgQueue::EnqueueAtHead(Msg* aMsg)
{
    ASSERT(aMsg != NULL);
    iLock.Wait();
    aMsg->iNextMsg = iHead;
    iHead = aMsg;
    iSem.Signal();
    iLock.Signal();
}

TBool MsgQueue::IsEmpty() const
{
    iLock.Wait();
    const TBool empty = (iHead == NULL);
    iLock.Signal();
    return empty;
}


// MsgQueueJiffies

MsgQueueJiffies::MsgQueueJiffies()
    : iJiffies(0)
{
}

MsgQueueJiffies::~MsgQueueJiffies()
{
}

void MsgQueueJiffies::DoEnqueue(Msg* aMsg)
{
    ProcessorQueueIn procIn(*this);
    Msg* msg = aMsg->Process(procIn);
    iQueue.Enqueue(msg);
}

Msg* MsgQueueJiffies::DoDequeue()
{
    Msg* msg;
    do {
        msg = iQueue.Dequeue();
        ProcessorQueueOut procOut(*this);
        msg = msg->Process(procOut);
    } while (msg == NULL);
    return msg;
}

void MsgQueueJiffies::EnqueueAtHead(Msg* aMsg)
{
    ProcessorQueueIn procIn(*this);
    Msg* msg = aMsg->Process(procIn);
    iQueue.EnqueueAtHead(msg);
}

TUint MsgQueueJiffies::Jiffies() const
{
    return iJiffies;
}

void MsgQueueJiffies::AddJiffies(TUint aJiffies)
{
    iJiffies += aJiffies;
}

void MsgQueueJiffies::RemoveJiffies(TUint aJiffies)
{
    ASSERT(iJiffies >= aJiffies);
    iJiffies -= aJiffies;
}

void MsgQueueJiffies::ProcessMsgIn(MsgAudioPcm* /*aMsg*/)
{
}

void MsgQueueJiffies::ProcessMsgIn(MsgSilence* /*aMsg*/)
{
}

void MsgQueueJiffies::ProcessMsgIn(MsgTrack* /*aMsg*/)
{
}

void MsgQueueJiffies::ProcessMsgIn(MsgMetaText* /*aMsg*/)
{
}

void MsgQueueJiffies::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
}

void MsgQueueJiffies::ProcessMsgIn(MsgFlush* /*aMsg*/)
{
}

Msg* MsgQueueJiffies::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    return aMsg;
}

Msg* MsgQueueJiffies::ProcessMsgOut(MsgSilence* aMsg)
{
    return aMsg;
}

Msg* MsgQueueJiffies::ProcessMsgOut(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* MsgQueueJiffies::ProcessMsgOut(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* MsgQueueJiffies::ProcessMsgOut(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* MsgQueueJiffies::ProcessMsgOut(MsgFlush* aMsg)
{
    return aMsg;
}


// MsgQueueJiffies::ProcessorQueueIn

MsgQueueJiffies::ProcessorQueueIn::ProcessorQueueIn(MsgQueueJiffies& aQueue)
    : iQueue(aQueue)
{
}

Msg* MsgQueueJiffies::ProcessorQueueIn::ProcessMsg(MsgAudioPcm* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    iQueue.AddJiffies(aMsg->Jiffies());
    return aMsg;
}

Msg* MsgQueueJiffies::ProcessorQueueIn::ProcessMsg(MsgSilence* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    iQueue.AddJiffies(aMsg->Jiffies());
    return aMsg;
}

Msg* MsgQueueJiffies::ProcessorQueueIn::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* MsgQueueJiffies::ProcessorQueueIn::ProcessMsg(MsgTrack* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgQueueJiffies::ProcessorQueueIn::ProcessMsg(MsgMetaText* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgQueueJiffies::ProcessorQueueIn::ProcessMsg(MsgHalt* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgQueueJiffies::ProcessorQueueIn::ProcessMsg(MsgFlush* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}


// MsgQueueJiffies::ProcessorQueueOut

MsgQueueJiffies::ProcessorQueueOut::ProcessorQueueOut(MsgQueueJiffies& aQueue)
    : iQueue(aQueue)
{
}

Msg* MsgQueueJiffies::ProcessorQueueOut::ProcessMsg(MsgAudioPcm* aMsg)
{
    iQueue.RemoveJiffies(aMsg->Jiffies());
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueJiffies::ProcessorQueueOut::ProcessMsg(MsgSilence* aMsg)
{
    iQueue.RemoveJiffies(aMsg->Jiffies());
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueJiffies::ProcessorQueueOut::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* MsgQueueJiffies::ProcessorQueueOut::ProcessMsg(MsgTrack* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueJiffies::ProcessorQueueOut::ProcessMsg(MsgMetaText* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueJiffies::ProcessorQueueOut::ProcessMsg(MsgHalt* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueJiffies::ProcessorQueueOut::ProcessMsg(MsgFlush* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}


// AutoRef

AutoRef::AutoRef(Msg& aMsg)
    : iMsg(aMsg)
{
}

AutoRef::~AutoRef()
{
    iMsg.RemoveRef();
}

    
// MsgFactory

MsgFactory::MsgFactory(Av::IInfoAggregator& aInfoAggregator,
                       TUint aDecodedAudioCount, TUint aMsgAudioPcmCount, TUint aMsgSilenceCount,
                       TUint aMsgPlayablePcmCount, TUint aMsgPlayableSilenceCount, TUint aMsgTrackCount,
                       TUint aMsgMetaTextCount, TUint aMsgHaltCount, TUint aMsgFlushCount)
    : iAllocatorDecodedAudio("DecodedAudio", aDecodedAudioCount, aInfoAggregator)
    , iAllocatorMsgAudioPcm("MsgAudioPcm", aMsgAudioPcmCount, aInfoAggregator)
    , iAllocatorMsgSilence("MsgSilence", aMsgSilenceCount, aInfoAggregator)
    , iAllocatorMsgPlayablePcm("MsgPlayablePcm", aMsgPlayablePcmCount, aInfoAggregator)
    , iAllocatorMsgPlayableSilence("MsgPlayableSilence", aMsgPlayableSilenceCount, aInfoAggregator)
    , iAllocatorMsgTrack("MsgTrack", aMsgTrackCount, aInfoAggregator)
    , iAllocatorMsgMetaText("MsgMetaText", aMsgMetaTextCount, aInfoAggregator)
    , iAllocatorMsgHalt("MsgHalt", aMsgHaltCount, aInfoAggregator)
    , iAllocatorMsgFlush("MsgFlush", aMsgFlushCount, aInfoAggregator)
{
}

MsgAudioPcm* MsgFactory::CreateMsgAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian)
{
    DecodedAudio* decodedAudio = CreateDecodedAudio(aData, aChannels, aSampleRate, aBitDepth, aEndian);
    MsgAudioPcm* msg = iAllocatorMsgAudioPcm.Allocate();
    msg->Initialise(decodedAudio, iAllocatorMsgPlayablePcm);
    return msg;
}

MsgSilence* MsgFactory::CreateMsgSilence(TUint aSizeJiffies)
{
    MsgSilence* msg = iAllocatorMsgSilence.Allocate();
    msg->Initialise(aSizeJiffies, iAllocatorMsgPlayableSilence);
    return msg;
}

MsgTrack* MsgFactory::CreateMsgTrack()
{
    return iAllocatorMsgTrack.Allocate();
}

MsgMetaText* MsgFactory::CreateMsgMetaText()
{
    return iAllocatorMsgMetaText.Allocate();
}

MsgHalt* MsgFactory::CreateMsgHalt()
{
    return iAllocatorMsgHalt.Allocate();
}

MsgFlush* MsgFactory::CreateMsgFlush()
{
    return iAllocatorMsgFlush.Allocate();
}

DecodedAudio* MsgFactory::CreateDecodedAudio(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian)
{
    DecodedAudio* decodedAudio = iAllocatorDecodedAudio.Allocate();
    decodedAudio->Construct(aData, aChannels, aSampleRate, aBitDepth, aEndian);
    return decodedAudio;
}
