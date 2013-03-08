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
#include <climits>

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
    RefAdded();
}

void Allocated::RemoveRef()
{
    iLock.Wait();
    TBool free = (--iRefCount == 0);
    iLock.Signal();
    RefRemoved();
    if (free) {
        Clear();
        iAllocator.Free(this);
    }
}

void Allocated::RefAdded()
{
}

void Allocated::RefRemoved()
{
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


// EncodedAudio

EncodedAudio::EncodedAudio(AllocatorBase& aAllocator)
    : Allocated(aAllocator)
{
}

const TByte* EncodedAudio::Ptr(TUint aBytes) const
{
    ASSERT(aBytes < iBytes);
    return &iData[aBytes];
}

TUint EncodedAudio::Bytes() const
{
    return iBytes;
}

void EncodedAudio::Construct(const Brx& aData)
{
    ASSERT(aData.Bytes() <= kMaxBytes);
    (void)memcpy(iData, aData.Ptr(), aData.Bytes());
    iBytes = aData.Bytes();
}

void EncodedAudio::Clear()
{
#ifdef DEFINE_DEBUG
    // fill in all members with recognisable 'bad' values to make ref counting bugs more obvious
    static const TByte deadByte = 0xde;
    static const TUint deadUint = 0xdead;
    memset(&iData[0], deadByte, sizeof(iData));
    iBytes = deadUint;
#endif // DEFINE_DEBUG
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
        ASSERTS(); // FIXME - should throw rather than assert in response to unexpected externally provided data
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

const TByte* DecodedAudio::PtrOffsetBytes(TUint aBytes) const
{
    ASSERT(aBytes % ((iBitDepth/8) * iChannels) == 0);
    return &iData[aBytes];
}

TUint DecodedAudio::Bytes() const
{
    return iSubsampleCount * iByteDepth;
}

TUint DecodedAudio::BytesFromJiffies(TUint& aJiffies) const
{
    return Jiffies::BytesFromJiffies(aJiffies, iJiffiesPerSample, iChannels, iByteDepth);
}

TUint DecodedAudio::JiffiesFromBytes(TUint aBytes) const
{
    ASSERT(aBytes % iByteDepth == 0);
    const TUint numSubsamples = aBytes / iByteDepth;
    ASSERT(numSubsamples % iChannels == 0);
    const TUint jiffies = (numSubsamples / iChannels) * iJiffiesPerSample;
    return jiffies;
}

TUint DecodedAudio::NumChannels() const
{
    return iChannels;
}

TUint DecodedAudio::BitDepth() const
{
    return iBitDepth;
}

void DecodedAudio::Construct(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian)
{
    iChannels = aChannels;
    iSampleRate = aSampleRate;
    iBitDepth = aBitDepth;
    iByteDepth = iBitDepth/8;
    iJiffiesPerSample = Jiffies::JiffiesPerSample(aSampleRate);

    ASSERT((aBitDepth & 7) == 0);
    ASSERT(aData.Bytes() % iByteDepth == 0);
    iSubsampleCount = aData.Bytes() / iByteDepth;
    ASSERT(aData.Bytes() <= kMaxBytes);
    if (aEndian == EMediaDataBigEndian || aBitDepth == 8) {
        (void)memcpy(iData, aData.Ptr(), aData.Bytes());
    }
    else if (aBitDepth == 16) {
        CopyToBigEndian16(aData);
    }
    else if (aBitDepth == 24) {
        CopyToBigEndian24(aData);
    }
    else { // unsupported bit depth
        ASSERTS();
    }
    /*for (TUint i=0; i<Bytes(); i++) {
        if (iData[i] == 0xcd) {
            _asm int 3;
        }
    }*/
}

void DecodedAudio::CopyToBigEndian16(const Brx& aData)
{
    const TByte* src = aData.Ptr();
    for (TUint i=0; i<aData.Bytes(); i+=2) {
        iData[i]   = src[i+1];
        iData[i+1] = src[i];
    }
}

void DecodedAudio::CopyToBigEndian24(const Brx& aData)
{
    const TByte* src = aData.Ptr();
    for (TUint i=0; i<aData.Bytes(); i+=3) {
        iData[i]   = src[i+2];
        iData[i+1] = src[i+1];
        iData[i+2] = src[i];
    }
}

void DecodedAudio::Clear()
{
#ifdef DEFINE_DEBUG
    // fill in all members with recognisable 'bad' values to make ref counting bugs more obvious
    static const TByte deadByte = 0xde;
    static const TUint deadUint = 0xdead;
    memset(&iData[0], deadByte, sizeof(iData));
    iSubsampleCount = deadUint;
    iChannels = deadUint;
    iSampleRate = deadUint;
    iBitDepth = deadUint;
    iByteDepth = deadUint;
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
    ASSERT(aRampDuration >  aFragmentSize || ((aStart == kRampMax || aStart == kRampMin) && aRampDuration == aFragmentSize));
    ASSERT(aDirection != ENone);
    iEnabled = true;
    aSplit.Reset();
    aSplitPos = 0xffffffff;
    // Always round up rampDelta values to avoid rounding errors leading to a ramp failing to complete in its duration 
    TUint rampDelta = ((kRampMax * (TUint64)aFragmentSize) + aRampDuration - 1) / aRampDuration;
    // Rounding up rampDelta means that a ramp may overshoot.
    // ...check for this and clamp end values to min/max dependent on direction
    TUint rampEnd;
    if (aDirection == EDown) {
        if (rampDelta > aStart) {
            ASSERT(rampDelta - aStart <= aFragmentSize - 1); // anything larger must be the result of programming rather than rounding error
            rampEnd = 0;
        }
        else {
            rampEnd = (TUint)(aStart - rampDelta);
        }
    }
    else { // aDirection == EUp
        if (aStart + rampDelta > kRampMax) {
            ASSERT(aStart + rampDelta - kRampMax <= aFragmentSize - 1); // anything larger must be the result of programming rather than rounding error
            rampEnd = kRampMax;
        }
        else {
            rampEnd = aStart + rampDelta;
        }
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
    Validate();
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

void Ramp::Validate()
{
    ASSERT(iStart <= kRampMax);
    ASSERT(iEnd <= kRampMax);
    if (iDirection == EUp) {
        ASSERT(iStart < iEnd);
    }
    else {
        ASSERT(iStart > iEnd);
    }
}

Ramp Ramp::Split(TUint aNewSize, TUint aCurrentSize)
{
    //TUint start = iStart, end = iEnd;
    Ramp remaining;
    remaining.iEnd = iEnd;
    remaining.iDirection = iDirection;
    remaining.iEnabled = true;
    if (iDirection == EUp) {
        TUint ramp = ((iEnd-iStart) * (TUint64)aNewSize) / aCurrentSize;
        iEnd = iStart + ramp;
    }
    else {
        TUint ramp = ((iStart-iEnd) * (TUint64)aNewSize) / aCurrentSize;
        iEnd = iStart - ramp;
    }
    remaining.iStart = iEnd; // FIXME - remaining.iStart is one sample on from iEnd so should have a ramp value that progresses one 'step'
    //Log::Print("Split [%08x : %08x] ramp into [%08x : %08x] and [%08x : %08x]\n", start, end, iStart, iEnd, remaining.iStart, remaining.iEnd);
    Validate();
    remaining.Validate();
    return remaining;
}


// RampApplicator

RampApplicator::RampApplicator(const Media::Ramp& aRamp)
    : iRamp(aRamp)
    , iPtr(NULL)
{
}

TUint RampApplicator::Start(const Brx& aData, TUint aBitDepth, TUint aNumChannels)
{
    iPtr = aData.Ptr();
    iBitDepth = aBitDepth;
    iNumChannels = aNumChannels;
    ASSERT_DEBUG(aData.Bytes() % ((iBitDepth/8) * iNumChannels) == 0);
    iNumSamples = aData.Bytes() / ((iBitDepth/8) * iNumChannels);
    iTotalRamp = iRamp.Start() - iRamp.End();
    iFullRampSpan = Ramp::kRampMax - Ramp::kRampMin;
    iLoopCount = 0;
    return iNumSamples;
}

void RampApplicator::GetNextSample(TByte* aDest)
{
    ASSERT_DEBUG(iPtr != NULL);
    const TUint ramp = (iNumSamples==1? iRamp.Start() : (TUint)(iRamp.Start() - ((iLoopCount * (TInt64)iTotalRamp)/(iNumSamples-1))));
    //Log::Print(" %08x ", ramp);
    const TUint rampIndex = (iFullRampSpan - ramp + (1<<20)) >> 21; // assumes fullRampSpan==2^31 and kRampArray has 512 items. (1<<20 allows rounding up)
    TInt subsample = 0;
    switch (iBitDepth)
    {
    case 8:
        subsample = *iPtr << 24;
        iPtr++;
        break;
    case 16:
        subsample = *iPtr << 24;
        iPtr++;
        subsample += *iPtr << 16;
        iPtr++;
        break;
    case 24:
        subsample = *iPtr << 24;
        iPtr++;
        subsample += *iPtr << 16;
        iPtr++;
        subsample += *iPtr << 8;
        iPtr++;
        break;
    default:
        ASSERTS();
    }
    //Log::Print(" %03u ", rampIndex);
    TInt rampedSubsample = (rampIndex==512? 0 : ((TInt64)subsample * kRampArray[rampIndex]) >> 31); // >>31 assumes kRampArray values are 32-bit, signed & positive
    //Log::Print("Original=%08x, ramped=%08x, rampIndex=%u\n", subsample, rampedSubsample, rampIndex);

    for (TUint i=0; i<iNumChannels; i++) { // apply ramp to each subsample
        switch (iBitDepth)
        {
        case 8:
            *aDest++ = (TByte)(rampedSubsample >> 24);
            break;
        case 16:
            *aDest++ = (TByte)(rampedSubsample >> 24);
            *aDest++ = (TByte)(rampedSubsample >> 16);
            break;
        case 24:
            *aDest++ = (TByte)(rampedSubsample >> 24);
            *aDest++ = (TByte)(rampedSubsample >> 16);
            *aDest++ = (TByte)(rampedSubsample >> 8);
            break;
        default:
            ASSERTS();
        }
    }

    iLoopCount++;
}


// MsgAudioEncoded

MsgAudioEncoded::MsgAudioEncoded(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

MsgAudioEncoded* MsgAudioEncoded::Split(TUint aBytes)
{
    if (aBytes > iSize) {
        ASSERT(iNextAudio != NULL);
        return iNextAudio->Split(aBytes - iSize);
    }
    ASSERT(aBytes > 0);
    ASSERT(aBytes < iSize);
    MsgAudioEncoded* remaining = static_cast<Allocator<MsgAudioEncoded>&>(iAllocator).Allocate();
    remaining->iNextAudio = iNextAudio;
    remaining->iOffset = iOffset + aBytes;
    remaining->iSize = iSize - aBytes;
    remaining->iAudioData = iAudioData;
    remaining->iAudioData->AddRef();
    iSize = aBytes;
    iNextAudio = NULL;
    return remaining;
}

void MsgAudioEncoded::Add(MsgAudioEncoded* aMsg)
{
    MsgAudioEncoded* end = this;
    MsgAudioEncoded* next = iNextAudio;
    while (next != NULL) {
        end = next;
        next = next->iNextAudio;
    }
    end->iNextAudio = aMsg;
}

TUint MsgAudioEncoded::Bytes() const
{
    TUint bytes = iSize;
    MsgAudioEncoded* next = iNextAudio;
    while (next != NULL) {
        bytes += next->iSize;
        next = next->iNextAudio;
    }
    return bytes;
}

void MsgAudioEncoded::CopyTo(TByte* aPtr)
{
    const TByte* src = iAudioData->Ptr(iOffset);
    (void)memcpy(aPtr, src, iSize);
    if (iNextAudio != NULL) {
        iNextAudio->CopyTo(aPtr + iSize);
    }
}

void MsgAudioEncoded::Initialise(EncodedAudio* aEncodedAudio)
{
    iAudioData = aEncodedAudio;
    iSize = iAudioData->Bytes();
    iOffset = 0;
    iNextAudio = NULL;
}

void MsgAudioEncoded::Clear()
{
    if (iNextAudio != NULL) {
        iNextAudio->RemoveRef();
    }
    iAudioData->RemoveRef();
}

Msg* MsgAudioEncoded::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
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
    remaining->iNextAudio = iNextAudio;
    remaining->iOffset = iOffset + aJiffies;
    remaining->iSize = iSize - aJiffies;
    if (iRamp.IsEnabled()) {
        remaining->iRamp = iRamp.Split(aJiffies, iSize);
    }
    else {
        remaining->iRamp.Reset();
    }
    iSize = aJiffies;
    iNextAudio = NULL;
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
        jiffies += next->iSize;
        next = next->iNextAudio;
    }
    return jiffies;
}

TUint MsgAudio::SetRamp(TUint aStart, TUint aDuration, Ramp::EDirection aDirection, MsgAudio*& aSplit)
{
    Media::Ramp split;
    TUint splitPos;
    TUint rampEnd;
    aSplit = NULL;
    if (iRamp.Set(aStart, iSize, aDuration, aDirection, split, splitPos)) {
        Media::Ramp ramp = iRamp; // Split() will muck about with ramps.  Allow this to happen then reset the correct values
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

const Media::Ramp& MsgAudio::Ramp() const
{
    return iRamp;
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

TUint64 MsgAudioPcm::TrackOffset() const
{
    return iTrackOffset;
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
    static_cast<MsgAudioPcm*>(clone)->iAllocatorPlayable = iAllocatorPlayable;
    static_cast<MsgAudioPcm*>(clone)->iTrackOffset = iTrackOffset;
    iAudioData->AddRef();
    return clone;
}

void MsgAudioPcm::Initialise(DecodedAudio* aDecodedAudio, TUint64 aTrackOffset, Allocator<MsgPlayablePcm>& aAllocatorPlayable)
{
    MsgAudio::Initialise();
    iAllocatorPlayable = &aAllocatorPlayable;
    iAudioData = aDecodedAudio;
    iTrackOffset = aTrackOffset;
    iSize = iAudioData->JiffiesFromBytes(iAudioData->Bytes());
    iOffset = 0;
}

void MsgAudioPcm::SplitCompleted(MsgAudio& aRemaining)
{
    iAudioData->AddRef();
    MsgAudioPcm& remaining = static_cast<MsgAudioPcm&>(aRemaining);
    remaining.iAudioData = iAudioData;
    remaining.iTrackOffset = iTrackOffset + iSize;
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

MsgPlayable* MsgSilence::CreatePlayable(TUint aSampleRate, TUint aBitDepth, TUint aNumChannels)
{
    TUint offsetJiffies = iOffset;
    TUint jiffiesPerSample = Jiffies::JiffiesPerSample(aSampleRate);
    TUint sizeJiffies = iSize + (iOffset - offsetJiffies);
    TUint sizeBytes = Jiffies::BytesFromJiffies(sizeJiffies, jiffiesPerSample, aNumChannels, aBitDepth/8);

    MsgPlayableSilence* playable = iAllocatorPlayable->Allocate();
    playable->Initialise(sizeBytes, aBitDepth, aNumChannels, iRamp);
    if (iNextAudio != NULL) {
        MsgPlayable* child = static_cast<MsgSilence*>(iNextAudio)->CreatePlayable(aSampleRate, aBitDepth, aNumChannels);
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
    if (aBytes == iSize) {
        MsgPlayable* remaining = iNextPlayable;
        iNextPlayable = NULL;
        return remaining;
    }
    MsgPlayable* remaining = Allocate();
    remaining->iNextPlayable = iNextPlayable;
    remaining->iOffset = iOffset + aBytes;
    remaining->iSize = iSize - aBytes;
    if (iRamp.IsEnabled()) {
        remaining->iRamp = iRamp.Split(aBytes, iSize);
    }
    else {
        remaining->iRamp.Reset();
    }
    iSize = aBytes;
    iNextPlayable = NULL;
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
        bytes += next->iSize;
        next = next->iNextPlayable;
    }
    return bytes;
}

const Media::Ramp& MsgPlayable::Ramp() const
{
    return iRamp;
}

MsgPlayable::MsgPlayable(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

void MsgPlayable::Initialise(TUint aSizeBytes, TUint aOffsetBytes, const Media::Ramp& aRamp)
{
    iNextPlayable = NULL;
    iSize = aSizeBytes;
    iOffset = aOffsetBytes;
    iRamp = aRamp;
}

void MsgPlayable::RefAdded()
{
    if (iNextPlayable != NULL) {
        iNextPlayable->AddRef();
    }
}

void MsgPlayable::RefRemoved()
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

void MsgPlayablePcm::Initialise(DecodedAudio* aDecodedAudio, TUint aSizeBytes, TUint aOffsetBytes, const Media::Ramp& aRamp)
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

void MsgPlayablePcm::Read(IPcmProcessor& aProcessor)
{
    aProcessor.BeginBlock();
    MsgPlayablePcm* playable = this;
    while (playable != NULL) {
        Brn audioBuf(playable->iAudioData->PtrOffsetBytes(playable->iOffset), playable->iSize);
        /*{
            const TUint testBytes = audioBuf.Bytes();
            for (TUint i=0; i<testBytes; i++) {
                if (audioBuf[i] == 0xcd) {
                    _asm int 3;
                }
            }
        }*/
        const TUint numChannels = playable->iAudioData->NumChannels();
        const TUint bitDepth = playable->iAudioData->BitDepth();
        const TUint byteDepth = bitDepth / 8;
        if (playable->iRamp.IsEnabled()) {
            // we need calculate each subsample value when ramped so there is no option to process as a single fragment
            TByte sample[DecodedAudio::kMaxNumChannels * 3]; // largest possible sample - 24-bit, 8 channel
            RampApplicator ra(playable->iRamp);
            const TUint numSamples = ra.Start(audioBuf, bitDepth, numChannels);
            for (TUint i=0; i<numSamples; i++) {
                ra.GetNextSample(sample);
                switch (byteDepth)
                {
                case 1:
                    aProcessor.ProcessSample8(sample, numChannels);
                    break;
                case 2:
                    aProcessor.ProcessSample16(sample, numChannels);
                    break;
                case 3:
                    aProcessor.ProcessSample24(sample, numChannels);
                    break;
                default:
                    ASSERTS();
                }
            }
        }
        else {
            TBool fragmentProcessed = false;
            switch (byteDepth)
            {
            case 1:
                 fragmentProcessed = aProcessor.ProcessFragment8(audioBuf, numChannels);
                break;
            case 2:
                 fragmentProcessed = aProcessor.ProcessFragment16(audioBuf, numChannels);
                break;
            case 3:
                 fragmentProcessed = aProcessor.ProcessFragment24(audioBuf, numChannels);
                break;
            default:
                ASSERTS();
            }
            if (!fragmentProcessed) {
                const TUint numSamples = playable->iSize / (byteDepth * numChannels);
                const TByte* ptr = audioBuf.Ptr();
                const TUint sampleLen = byteDepth * numChannels;
                switch (byteDepth)
                {
                case 1:
                    for (TUint i=0; i<numSamples; i++) {
                        aProcessor.ProcessSample8(ptr, numChannels);
                        ptr += sampleLen;
                    }
                    break;
                case 2:
                    for (TUint i=0; i<numSamples; i++) {
                        aProcessor.ProcessSample16(ptr, numChannels);
                        ptr += sampleLen;
                    }
                    break;
                case 3:
                    for (TUint i=0; i<numSamples; i++) {
                        aProcessor.ProcessSample24(ptr, numChannels);
                        ptr += sampleLen;
                    }
                    break;
                default:
                    ASSERTS();
                }
            }
        }
        playable = reinterpret_cast<MsgPlayablePcm*>(playable->iNextPlayable);
    }
    aProcessor.EndBlock();
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
    iAudioData->RemoveRef();
}


// MsgPlayableSilence

MsgPlayableSilence::MsgPlayableSilence(AllocatorBase& aAllocator)
    : MsgPlayable(aAllocator)
{
}

void MsgPlayableSilence::Initialise(TUint aSizeBytes, TUint aBitDepth, TUint aNumChannels, const Media::Ramp& aRamp)
{
    MsgPlayable::Initialise(aSizeBytes, 0, aRamp);
    iBitDepth = aBitDepth;
    iNumChannels = aNumChannels;
}

void MsgPlayableSilence::Read(IPcmProcessor& aProcessor)
{
    static const TByte silence[DecodedAudio::kMaxBytes] = { 0 };
    aProcessor.BeginBlock();
    MsgPlayableSilence* playable = this;
    while (playable != NULL) {
        TBool fragmentProcessed = false;
        TUint remainingBytes = playable->iSize;
        do {
            TUint bytes = (remainingBytes > DecodedAudio::kMaxBytes? DecodedAudio::kMaxBytes : remainingBytes);
            Brn audioBuf(silence, bytes);
            switch (iBitDepth)
            {
            case 8:
                fragmentProcessed = aProcessor.ProcessFragment8(audioBuf, iNumChannels);
                break;
            case 16:
                fragmentProcessed = aProcessor.ProcessFragment16(audioBuf, iNumChannels);
                break;
            case 24:
                fragmentProcessed = aProcessor.ProcessFragment24(audioBuf, iNumChannels);
                break;
            default:
                ASSERTS();
            }
            if (fragmentProcessed) {
                remainingBytes -= bytes;
            }
        } while (fragmentProcessed && remainingBytes > 0);
        if (!fragmentProcessed) {
            const TUint numSamples = remainingBytes / ((iBitDepth/8) * iNumChannels);
            switch (iBitDepth)
            {
            case 8:
                for (TUint i=0; i<numSamples; i++) {
                    aProcessor.ProcessSample8(silence, iNumChannels);
                }
                break;
            case 16:
                for (TUint i=0; i<numSamples; i++) {
                    aProcessor.ProcessSample16(silence, iNumChannels);
                }
                break;
            case 24:
                for (TUint i=0; i<numSamples; i++) {
                    aProcessor.ProcessSample24(silence, iNumChannels);
                }
                break;
            default:
                ASSERTS();
            }
        }
        playable = reinterpret_cast<MsgPlayableSilence*>(playable->iNextPlayable);
    }
    aProcessor.EndBlock();
}

MsgPlayable* MsgPlayableSilence::Allocate()
{
    return static_cast<Allocator<MsgPlayableSilence>&>(iAllocator).Allocate();
}


// DecodedStreamInfo

DecodedStreamInfo::DecodedStreamInfo()
    : iBitRate(0)
    , iBitDepth(0)
    , iSampleRate(0)
    , iNumChannels(0)
    , iCodecName("")
    , iTrackLength(0)
    , iLossless(false)
{
}

void DecodedStreamInfo::Set(TUint aStreamId, TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler)
{
    iStreamId = aStreamId;
    iBitRate = aBitRate;
    iBitDepth = aBitDepth;
    iSampleRate = aSampleRate;
    iNumChannels = aNumChannels;
    iCodecName.Replace(aCodecName);
    iTrackLength = aTrackLength;
    iSampleStart = aSampleStart;
    iLossless = aLossless;
    iSeekable = aSeekable;
    iLive = aLive;
    iStreamHandler = aStreamHandler;
}


// MsgDecodedStream

MsgDecodedStream::MsgDecodedStream(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

const DecodedStreamInfo& MsgDecodedStream::StreamInfo() const
{
    return iStreamInfo;
}

void MsgDecodedStream::Initialise(TUint aStreamId, TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler)
{
    iStreamInfo.Set(aStreamId, aBitRate, aBitDepth, aSampleRate, aNumChannels, aCodecName, aTrackLength, aSampleStart, aLossless, aSeekable, aLive, aStreamHandler);
}

void MsgDecodedStream::Clear()
{
#ifdef DEFINE_DEBUG
    iStreamInfo.Set(UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, Brx::Empty(), ULONG_MAX, ULONG_MAX, false, false, false, NULL);
#endif
}

Msg* MsgDecodedStream::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
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


// MsgEncodedStream

MsgEncodedStream::MsgEncodedStream(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

const Brx& MsgEncodedStream::Uri() const
{
    return iUri;
}

const Brx& MsgEncodedStream::MetaText() const
{
    return iMetaText;
}

TUint64 MsgEncodedStream::TotalBytes() const
{
    return iTotalBytes;
}

TUint MsgEncodedStream::StreamId() const
{
    return iStreamId;
}

TBool MsgEncodedStream::Seekable() const
{
    return iSeekable;
}

TBool MsgEncodedStream::Live() const
{
    return iLive;
}

IStreamHandler* MsgEncodedStream::StreamHandler() const
{
    return iStreamHandler;
}

void MsgEncodedStream::Initialise(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint aStreamId, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler)
{
    iUri.Replace(aUri);
    iMetaText.Replace(aMetaText);
    iTotalBytes = aTotalBytes;
    iStreamId = aStreamId;
    iSeekable = aSeekable;
    iLive = aLive;
    iStreamHandler = aStreamHandler;
}

void MsgEncodedStream::Clear()
{
#ifdef DEFINE_DEBUG
    iUri.SetBytes(0);
    iMetaText.SetBytes(0);
    iTotalBytes = UINT_MAX;
    iStreamId = UINT_MAX;
    iSeekable = false;
    iLive = false;
    iStreamHandler = NULL;
#endif
}

Msg* MsgEncodedStream::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgMetaText

MsgMetaText::MsgMetaText(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

const Brx& MsgMetaText::MetaText() const
{
    return iMetaText;
}

void MsgMetaText::Initialise(const Brx& aMetaText)
{
    iMetaText.Replace(aMetaText);
}

void MsgMetaText::Clear()
{
#ifdef DEFINE_DEBUG
    iMetaText.SetBytes(0);
#endif
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

void MsgFlush::Initialise(TUint aId)
{
    iId = aId;
}

TUint MsgFlush::Id() const
{
    return iId;
}

void MsgFlush::Clear()
{
    iId = kIdInvalid;
}

Msg* MsgFlush::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgQuit

MsgQuit::MsgQuit(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

Msg* MsgQuit::Process(IMsgProcessor& aProcessor)
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


// MsgQueueFlushable

MsgQueueFlushable::MsgQueueFlushable()
    : iLock("MQJF")
    , iEncodedBytes(0)
    , iJiffies(0)
    , iFlushing(false)
{
}

MsgQueueFlushable::~MsgQueueFlushable()
{
}

void MsgQueueFlushable::DoEnqueue(Msg* aMsg)
{
    ProcessorQueueIn procIn(*this);
    Msg* msg = aMsg->Process(procIn);
    iQueue.Enqueue(msg);
}

Msg* MsgQueueFlushable::DoDequeue()
{
    Msg* msg;
    do {
        msg = iQueue.Dequeue();
        ProcessorQueueOut procOut(*this);
        msg = msg->Process(procOut);
        iLock.Wait();
        if (iFlushing) {
            msg->RemoveRef();
            msg = NULL;
        }
        iLock.Signal();
    } while (msg == NULL);
    return msg;
}

void MsgQueueFlushable::EnqueueAtHead(Msg* aMsg)
{
    ProcessorQueueIn procIn(*this);
    Msg* msg = aMsg->Process(procIn);
    iQueue.EnqueueAtHead(msg);
}

TUint MsgQueueFlushable::Jiffies() const
{
    return iJiffies;
}

TUint MsgQueueFlushable::EncodedBytes() const
{
    return iEncodedBytes;
}

TBool MsgQueueFlushable::IsEmpty() const
{
    return iQueue.IsEmpty();
}

void MsgQueueFlushable::Add(TUint& aValue, TUint aAdded)
{
    iLock.Wait();
    aValue += aAdded;
    iLock.Signal();
}

void MsgQueueFlushable::Remove(TUint& aValue, TUint aRemoved)
{
    iLock.Wait();
    ASSERT(aValue >= aRemoved);
    aValue -= aRemoved;
    iLock.Signal();
}

void MsgQueueFlushable::StartFlushing()
{
    iLock.Wait();
    iFlushing = true;
    iLock.Signal();
}

void MsgQueueFlushable::StopFlushing()
{
    iLock.Wait();
    iFlushing = false;
    iLock.Signal();
}

void MsgQueueFlushable::ProcessMsgIn(MsgAudioEncoded* /*aMsg*/)
{
}

void MsgQueueFlushable::ProcessMsgIn(MsgAudioPcm* /*aMsg*/)
{
}

void MsgQueueFlushable::ProcessMsgIn(MsgSilence* /*aMsg*/)
{
}

void MsgQueueFlushable::ProcessMsgIn(MsgDecodedStream* /*aMsg*/)
{
}

void MsgQueueFlushable::ProcessMsgIn(MsgTrack* /*aMsg*/)
{
}

void MsgQueueFlushable::ProcessMsgIn(MsgEncodedStream* /*aMsg*/)
{
}

void MsgQueueFlushable::ProcessMsgIn(MsgMetaText* /*aMsg*/)
{
}

void MsgQueueFlushable::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
}

void MsgQueueFlushable::ProcessMsgIn(MsgFlush* /*aMsg*/)
{
}

void MsgQueueFlushable::ProcessMsgIn(MsgQuit* /*aMsg*/)
{
}

Msg* MsgQueueFlushable::ProcessMsgOut(MsgAudioEncoded* aMsg)
{
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessMsgOut(MsgSilence* aMsg)
{
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessMsgOut(MsgDecodedStream* aMsg)
{
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessMsgOut(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessMsgOut(MsgEncodedStream* aMsg)
{
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessMsgOut(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessMsgOut(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessMsgOut(MsgFlush* aMsg)
{
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessMsgOut(MsgQuit* aMsg)
{
    return aMsg;
}


// MsgQueueFlushable::ProcessorQueueIn

MsgQueueFlushable::ProcessorQueueIn::ProcessorQueueIn(MsgQueueFlushable& aQueue)
    : iQueue(aQueue)
{
}

Msg* MsgQueueFlushable::ProcessorQueueIn::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iQueue.Add(iQueue.iEncodedBytes, aMsg->Bytes());
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessorQueueIn::ProcessMsg(MsgAudioPcm* aMsg)
{
    iQueue.Add(iQueue.iJiffies, aMsg->Jiffies());
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessorQueueIn::ProcessMsg(MsgSilence* aMsg)
{
    iQueue.Add(iQueue.iJiffies, aMsg->Jiffies());
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessorQueueIn::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* MsgQueueFlushable::ProcessorQueueIn::ProcessMsg(MsgDecodedStream* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessorQueueIn::ProcessMsg(MsgTrack* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessorQueueIn::ProcessMsg(MsgEncodedStream* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessorQueueIn::ProcessMsg(MsgMetaText* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessorQueueIn::ProcessMsg(MsgHalt* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessorQueueIn::ProcessMsg(MsgFlush* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    iQueue.StartFlushing();
    return aMsg;
}

Msg* MsgQueueFlushable::ProcessorQueueIn::ProcessMsg(MsgQuit* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}


// MsgQueueFlushable::ProcessorQueueOut

MsgQueueFlushable::ProcessorQueueOut::ProcessorQueueOut(MsgQueueFlushable& aQueue)
    : iQueue(aQueue)
{
}

Msg* MsgQueueFlushable::ProcessorQueueOut::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iQueue.Remove(iQueue.iEncodedBytes, aMsg->Bytes());
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueFlushable::ProcessorQueueOut::ProcessMsg(MsgAudioPcm* aMsg)
{
    iQueue.Remove(iQueue.iJiffies, aMsg->Jiffies());
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueFlushable::ProcessorQueueOut::ProcessMsg(MsgSilence* aMsg)
{
    iQueue.Remove(iQueue.iJiffies, aMsg->Jiffies());
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueFlushable::ProcessorQueueOut::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* MsgQueueFlushable::ProcessorQueueOut::ProcessMsg(MsgDecodedStream* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueFlushable::ProcessorQueueOut::ProcessMsg(MsgTrack* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueFlushable::ProcessorQueueOut::ProcessMsg(MsgEncodedStream* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueFlushable::ProcessorQueueOut::ProcessMsg(MsgMetaText* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueFlushable::ProcessorQueueOut::ProcessMsg(MsgHalt* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueFlushable::ProcessorQueueOut::ProcessMsg(MsgFlush* aMsg)
{
    iQueue.StopFlushing();
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgQueueFlushable::ProcessorQueueOut::ProcessMsg(MsgQuit* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}


// AutoMsgRef

AutoMsgRef::AutoMsgRef(Msg& aMsg)
    : iMsg(aMsg)
{
}

AutoMsgRef::~AutoMsgRef()
{
    iMsg.RemoveRef();
}

    
// MsgFactory

MsgFactory::MsgFactory(Av::IInfoAggregator& aInfoAggregator,
                       TUint aEncodedAudioCount, TUint aMsgAudioEncodedCount, 
                       TUint aDecodedAudioCount, TUint aMsgAudioPcmCount, TUint aMsgSilenceCount,
                       TUint aMsgPlayablePcmCount, TUint aMsgPlayableSilenceCount, TUint aMsgDecodedStreamCount,
                       TUint aMsgTrackCount, TUint aMsgEncodedStreamCount, TUint aMsgMetaTextCount,
                       TUint aMsgHaltCount, TUint aMsgFlushCount, TUint aMsgQuitCount)
    : iAllocatorEncodedAudio("EncodedAudio", aEncodedAudioCount, aInfoAggregator)
    , iAllocatorMsgAudioEncoded("MsgAudioEncoded", aMsgAudioEncodedCount, aInfoAggregator)
    , iAllocatorDecodedAudio("DecodedAudio", aDecodedAudioCount, aInfoAggregator)
    , iAllocatorMsgAudioPcm("MsgAudioPcm", aMsgAudioPcmCount, aInfoAggregator)
    , iAllocatorMsgSilence("MsgSilence", aMsgSilenceCount, aInfoAggregator)
    , iAllocatorMsgPlayablePcm("MsgPlayablePcm", aMsgPlayablePcmCount, aInfoAggregator)
    , iAllocatorMsgPlayableSilence("MsgPlayableSilence", aMsgPlayableSilenceCount, aInfoAggregator)
    , iAllocatorMsgDecodedStream("MsgDecodedStream", aMsgDecodedStreamCount, aInfoAggregator)
    , iAllocatorMsgTrack("MsgTrack", aMsgTrackCount, aInfoAggregator)
    , iAllocatorMsgEncodedStream("MsgEncodedStream", aMsgEncodedStreamCount, aInfoAggregator)
    , iAllocatorMsgMetaText("MsgMetaText", aMsgMetaTextCount, aInfoAggregator)
    , iAllocatorMsgHalt("MsgHalt", aMsgHaltCount, aInfoAggregator)
    , iAllocatorMsgFlush("MsgFlush", aMsgFlushCount, aInfoAggregator)
    , iAllocatorMsgQuit("MsgQuit", aMsgQuitCount, aInfoAggregator)
{
    iNextFlushId = MsgFlush::kIdInvalid + 1;
}

MsgAudioEncoded* MsgFactory::CreateMsgAudioEncoded(const Brx& aData)
{
    EncodedAudio* encodedAudio = CreateEncodedAudio(aData);
    MsgAudioEncoded* msg = iAllocatorMsgAudioEncoded.Allocate();
    msg->Initialise(encodedAudio);
    return msg;
}

MsgAudioPcm* MsgFactory::CreateMsgAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset)
{
    DecodedAudio* decodedAudio = CreateDecodedAudio(aData, aChannels, aSampleRate, aBitDepth, aEndian);
    MsgAudioPcm* msg = iAllocatorMsgAudioPcm.Allocate();
    msg->Initialise(decodedAudio, aTrackOffset, iAllocatorMsgPlayablePcm);
    return msg;
}

MsgSilence* MsgFactory::CreateMsgSilence(TUint aSizeJiffies)
{
    MsgSilence* msg = iAllocatorMsgSilence.Allocate();
    msg->Initialise(aSizeJiffies, iAllocatorMsgPlayableSilence);
    return msg;
}

MsgDecodedStream* MsgFactory::CreateMsgDecodedStream(TUint aStreamId, TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler)
{
    MsgDecodedStream* msg = iAllocatorMsgDecodedStream.Allocate();
    msg->Initialise(aStreamId, aBitRate, aBitDepth, aSampleRate, aNumChannels, aCodecName, aTrackLength, aSampleStart, aLossless, aSeekable, aLive, aStreamHandler);
    return msg;
}

MsgTrack* MsgFactory::CreateMsgTrack()
{
    return iAllocatorMsgTrack.Allocate();
}

MsgEncodedStream* MsgFactory::CreateMsgEncodedStream(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint aStreamId, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler)
{
    MsgEncodedStream* msg = iAllocatorMsgEncodedStream.Allocate();
    msg->Initialise(aUri, aMetaText, aTotalBytes, aStreamId, aSeekable, aLive, aStreamHandler);
    return msg;
}

MsgMetaText* MsgFactory::CreateMsgMetaText(const Brx& aMetaText)
{
    MsgMetaText* msg = iAllocatorMsgMetaText.Allocate();
    msg->Initialise(aMetaText);
    return msg;
}

MsgHalt* MsgFactory::CreateMsgHalt()
{
    return iAllocatorMsgHalt.Allocate();
}

MsgFlush* MsgFactory::CreateMsgFlush(TUint aId)
{
    MsgFlush* flush = iAllocatorMsgFlush.Allocate();
    flush->Initialise(aId);
    return flush;
}

MsgQuit* MsgFactory::CreateMsgQuit()
{
    return iAllocatorMsgQuit.Allocate();
}

EncodedAudio* MsgFactory::CreateEncodedAudio(const Brx& aData)
{
    EncodedAudio* encodedAudio = iAllocatorEncodedAudio.Allocate();
    encodedAudio->Construct(aData);
    return encodedAudio;
}

DecodedAudio* MsgFactory::CreateDecodedAudio(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian)
{
    DecodedAudio* decodedAudio = iAllocatorDecodedAudio.Allocate();
    decodedAudio->Construct(aData, aChannels, aSampleRate, aBitDepth, aEndian);
    return decodedAudio;
}
