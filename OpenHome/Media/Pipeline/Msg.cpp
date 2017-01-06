#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/RampArray.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Optional.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/InfoProvider.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Debug.h>

#include <string.h>
#include <climits>
#include <algorithm>
#include <cstdint>

using namespace OpenHome;
using namespace OpenHome::Media;

const TChar* OpenHome::Media::kStreamPlayNames[] = { "Yes", "No", "Later" };


// AllocatorBase

const Brn AllocatorBase::kQueryMemory = Brn("memory");

AllocatorBase::~AllocatorBase()
{
    LOG(kPipeline, "> ~AllocatorBase for %s. (Peak %u/%u)\n", iName, iCellsUsedMax, iFree.Slots());
    const TUint slots = iFree.Slots();
    for (TUint i=0; i<slots; i++) {
        //Log::Print("  %u", i);
        try {
            Allocated* ptr = Read();
            //Log::Print("(%p)", ptr);
            delete ptr;
        }
        catch (AssertionFailed&) {
            Log::Print("...leak at %u of %u\n", i+1, slots);
            throw;
        }
    }
    LOG(kPipeline, "< ~AllocatorBase for %s\n", iName);
}

void AllocatorBase::Free(Allocated* aPtr)
{
    iLock.Wait();
    iCellsUsed--;
    iFree.Write(aPtr);
    iLock.Signal();
}

TUint AllocatorBase::CellsTotal() const
{
    return iCellsTotal;
}

TUint AllocatorBase::CellBytes() const
{
    return iCellBytes;
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
    aCellsTotal = iCellsTotal;
    aCellBytes = iCellBytes;
    iLock.Wait();
    aCellsUsed = iCellsUsed;
    aCellsUsedMax = iCellsUsedMax;
    iLock.Signal();
}

AllocatorBase::AllocatorBase(const TChar* aName, TUint aNumCells, TUint aCellBytes, IInfoAggregator& aInfoAggregator)
    : iFree(aNumCells)
    , iLock("PAL1")
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
    iLock.Wait();
    Allocated* cell = Read();
    ASSERT_DEBUG(cell->iRefCount == 0);
    cell->iRefCount = 1;
    iCellsUsed++;
    if (iCellsUsed > iCellsUsedMax) {
        iCellsUsedMax = iCellsUsed;
    }
    iLock.Signal();
    return cell;
}

Allocated* AllocatorBase::Read()
{
    Allocated* p = nullptr;
    try {
        p = iFree.Read();
    }
    catch (FifoReadError&) {
        Log::Print("Warning: Allocator error for %s\n", iName);
        ASSERTS();
    }
    return p;
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
    iRefCount++;
    RefAdded();
}

void Allocated::RemoveRef()
{
    ASSERT_DEBUG(iRefCount != 0);
    TBool free = (--iRefCount == 0);
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
    , iRefCount(0)
{
    ASSERT(iRefCount.is_lock_free());
}

Allocated::~Allocated()
{
}


// AudioData

AudioData::AudioData(AllocatorBase& aAllocator)
    : Allocated(aAllocator)
{
}

const TByte* AudioData::Ptr(TUint aBytes) const
{
    ASSERT(aBytes < iData.Bytes());
    return iData.Ptr() + aBytes;
}

TUint AudioData::Bytes() const
{
    return iData.Bytes();
}

void AudioData::Clear()
{
#ifdef DEFINE_DEBUG
    // fill in all members with recognisable 'bad' values to make ref counting bugs more obvious
    memset(const_cast<TByte*>(iData.Ptr()), 0xde, iData.Bytes());
#endif // DEFINE_DEBUG
    iData.SetBytes(0);
}


// EncodedAudio

EncodedAudio::EncodedAudio(AllocatorBase& aAllocator)
    : AudioData(aAllocator)
{
}

TUint EncodedAudio::Append(const Brx& aData)
{
    const TUint avail = iData.MaxBytes() - iData.Bytes();
    if (avail < aData.Bytes()) {
        Brn data(aData.Ptr(), avail);
        iData.Append(data);
        return avail;
    }
    iData.Append(aData);
    return aData.Bytes();
}

void EncodedAudio::Construct(const Brx& aData)
{
    ASSERT(Append(aData) == aData.Bytes());
}


// DecodedAudio

DecodedAudio::DecodedAudio(AllocatorBase& aAllocator)
    : AudioData(aAllocator)
{
}

void DecodedAudio::Aggregate(DecodedAudio& aDecodedAudio)
{
    iData.Append(aDecodedAudio.iData);
}

void DecodedAudio::Construct(const Brx& aData, TUint aBitDepth, AudioDataEndian aEndian)
{
    ASSERT((aBitDepth & 7) == 0);
    ASSERT(aData.Bytes() % (aBitDepth/8) == 0);
    TByte* ptr = const_cast<TByte*>(iData.Ptr());
    if (aEndian == AudioDataEndian::Big || aBitDepth == 8) {
        (void)memcpy(ptr, aData.Ptr(), aData.Bytes());
    }
    else if (aBitDepth == 16) {
        CopyToBigEndian16(aData, ptr);
    }
    else if (aBitDepth == 24) {
        CopyToBigEndian24(aData, ptr);
    }
    else if (aBitDepth == 32) {
        CopyToBigEndian32(aData, ptr);
    }
    else { // unsupported bit depth
        ASSERTS();
    }
    iData.SetBytes(aData.Bytes());
}

void DecodedAudio::CopyToBigEndian16(const Brx& aData, TByte* aDest)
{ // static
    const TByte* src = aData.Ptr();
    for (TUint i=0; i<aData.Bytes(); i+=2) {
        *aDest++ = src[i+1];
        *aDest++ = src[i];
    }
}

void DecodedAudio::CopyToBigEndian24(const Brx& aData, TByte* aDest)
{ // static
    const TByte* src = aData.Ptr();
    for (TUint i=0; i<aData.Bytes(); i+=3) {
        *aDest++ = src[i+2];
        *aDest++ = src[i+1];
        *aDest++ = src[i];
    }
}

void DecodedAudio::CopyToBigEndian32(const Brx& aData, TByte* aDest)
{ // static
    const TByte* src = aData.Ptr();
    for (TUint i=0; i<aData.Bytes(); i+=4) {
        *aDest++ = src[i+3];
        *aDest++ = src[i+2];
        *aDest++ = src[i+1];
        *aDest++ = src[i];
    }
}


// Jiffies

TBool Jiffies::IsValidSampleRate(TUint aSampleRate)
{ // static
    try {
        PerSample(aSampleRate); // only want to check if sample rate is supported
    }
    catch (SampleRateInvalid&) {
        return false;
    }
    return true;
}

TUint Jiffies::PerSample(TUint aSampleRate)
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
        LOG(kError, "JiffiesPerSample - invalid sample rate: %u\n", aSampleRate);
        THROW(SampleRateInvalid);
    }
}

TUint Jiffies::ToBytes(TUint& aJiffies, TUint aJiffiesPerSample, TUint aNumChannels, TUint aBytesPerSubsample)
{ // static
    aJiffies -= aJiffies % aJiffiesPerSample; // round down requested aJiffies to the nearest integer number of samples
    const TUint numSamples = aJiffies / aJiffiesPerSample;
    const TUint numSubsamples = numSamples * aNumChannels;
    const TUint bytes = numSubsamples * aBytesPerSubsample;
    return bytes;
}

void Jiffies::RoundDown(TUint& aJiffies, TUint aSampleRate)
{
    const TUint jiffiesPerSample = PerSample(aSampleRate);
    aJiffies -= aJiffies % jiffiesPerSample;
}

void Jiffies::RoundUp(TUint& aJiffies, TUint aSampleRate)
{
    const TUint jiffiesPerSample = PerSample(aSampleRate);
    aJiffies += jiffiesPerSample - 1;
    aJiffies -= aJiffies % jiffiesPerSample;
}

TUint Jiffies::ToSongcastTime(TUint aJiffies, TUint aSampleRate)
{ // static
    return static_cast<TUint>((static_cast<TUint64>(aJiffies) * SongcastTicksPerSecond(aSampleRate)) / kPerSecond);
}

TUint64 Jiffies::FromSongcastTime(TUint64 aSongcastTime, TUint aSampleRate)
{ // static
    return (aSongcastTime * kPerSecond) / SongcastTicksPerSecond(aSampleRate);
}

TUint Jiffies::SongcastTicksPerSecond(TUint aSampleRate)
{ // static
    switch (aSampleRate)
    {
    case 7350:
    case 11025:
    case 14700:
    case 22050:
    case 29400:
    case 44100:
    case 88200:
    case 176400:
        return kSongcastTicksPerSec44k;

    case 8000:
    case 12000:
    case 16000:
    case 24000:
    case 32000:
    case 48000:
    case 96000:
    case 192000:
        return kSongcastTicksPerSec48k;

    default:
        THROW(SampleRateInvalid);
    }
}


// Msg

Msg::Msg(AllocatorBase& aAllocator)
    : Allocated(aAllocator)
    , iNextMsg(nullptr)
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
    ASSERT_DEBUG(kMax <= 1<<30); // some 32-bit values in ramp calculations should become 64-bit if this increases
    ASSERT_DEBUG(kRampArrayCount == 512); // <<22 and >>23 code needs review if this changes
}

void Ramp::Reset()
{
    iStart = kMax;
    iEnd = kMax;
    iDirection = ENone;
    iEnabled = false;
}

TBool Ramp::Set(TUint aStart, TUint aFragmentSize, TUint aRemainingDuration, EDirection aDirection, Ramp& aSplit, TUint& aSplitPos)
{
    /*Bws<256> buf("Ramp::Set (");
    buf.Append(Thread::CurrentThreadName());
    buf.AppendPrintf("), aDirection=%d, aStart=%08x, aFragmentSize=%08x, aRemainingDuration=%08x, current=[%08x..%08x]\n",
                     aDirection, aStart, aFragmentSize, aRemainingDuration, iStart, iEnd);
    Log::Print(buf);*/
    Ramp before(*this);
    ASSERT(aRemainingDuration >=  aFragmentSize);
    ASSERT(aDirection != ENone);
    iEnabled = true;
    aSplit.Reset();
    aSplitPos = 0xffffffff;
    const TUint rampRemaining = (aDirection == EDown? aStart : kMax-aStart);
    // Always round up rampDelta values to avoid rounding errors leading to a ramp failing to complete in its duration
    TUint rampDelta = ((rampRemaining * (TUint64)aFragmentSize) + aRemainingDuration - 1) / aRemainingDuration;
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
        if (aStart + rampDelta > kMax) {
            ASSERT(aStart + rampDelta - kMax <= aFragmentSize - 1); // anything larger must be the result of programming rather than rounding error
            rampEnd = kMax;
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
        TInt64 y1, y2, y3, y4;
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
            TInt64 intersectX = (aFragmentSize*(y3-y1))/((y2-y1)-(y4-y3));
            TInt64 intersectY = (((y2-y1)*(y3-y1))/((y2-y1)-(y4-y3))) + y1;
            // calculation of intersectY may overflow a TUint.
            // intersectX will tell us we have no useful intersection in these cases and we'll ignore the Y value.
            if (intersectX <= 0 || (TUint)intersectX >= aFragmentSize) {
                // ramp lines don't intersect inside this Msg
                SelectLowerRampPoints(aStart, rampEnd);
            }
            else {
                // split this Ramp; the first portion rises to the intersection of the two ramps, the second drops to the lower final value
                aSplitPos = (TUint)intersectX;
                aSplit.iStart = (TUint)intersectY;
                aSplit.iEnd = std::min(iEnd, rampEnd);
                aSplit.iDirection = (aSplit.iStart == aSplit.iEnd? ENone : EDown);
                aSplit.iEnabled = true;
                const TUint start = std::min(iStart, aStart);
                const TUint end = (TUint)intersectY;
                iDirection = (start == end? ENone : EUp);
                /*Log::Print("Split [%08x : %08x] ramp into [%08x : %08x] and [%08x : %08x]\n",
                           iStart, iEnd, start, end, aSplit.iStart, aSplit.iEnd);*/
                iStart = start;
                iEnd = end;
            }
        }
    }
    if (!DoValidate()) {
        Log::Print("Ramp::Set(%04x, %u, %u, %u) created invalid ramp.\n", aStart, aFragmentSize, aRemainingDuration, aDirection);
        Log::Print("  before: [%04x..%04x], direction=%u\n", before.iStart, before.iEnd, before.iDirection);
        Log::Print("  after:  [%04x..%04x], direction=%u\n", iStart, iEnd, iDirection);
        Log::Print("  split:  [%04x..%04x], direction=%u\n", aSplit.iStart, aSplit.iEnd, aSplit.iDirection);
        ASSERTS();
    }
    return aSplit.IsEnabled();
}

void Ramp::SetMuted()
{
    iStart = iEnd = kMin;
    iDirection = EMute;
    iEnabled = true;
}

void Ramp::SelectLowerRampPoints(TUint aRequestedStart, TUint aRequestedEnd)
{
    iStart = std::min(iStart, aRequestedStart);
    iEnd = std::min(iEnd, aRequestedEnd);
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

void Ramp::Validate(const TChar* aId)
{
    if (!DoValidate()) {
        Log::Print("Ramp::Validate failure %s)\n", aId);
        Log::Print("  ramp: [%04x..%04x], direction=%u\n", iStart, iEnd, iDirection);
        ASSERTS();
    }
}

TBool Ramp::DoValidate()
{
    if (iStart > kMax) {
        return false;
    }
    if (iEnd > kMax) {
        return false;
    }
    switch (iDirection)
    {
    case ENone:
        if (iStart != iEnd) {
            return false;
        }
        break;
    case EUp:
        if (iStart >= iEnd) {
            return false;
        }
        break;
    case EDown:
        if (iStart <= iEnd) {
            return false;
        }
        break;
    case EMute:
        if (iStart != iEnd) {
            return false;
        }
        if (iStart != kMin) {
            return false;
        }
        break;
    default:
        ASSERTS();
    }
    return true;
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
    if (iStart == iEnd) {
        iDirection = ENone;
    }
    remaining.iStart = iEnd; // FIXME - remaining.iStart is one sample on from iEnd so should have a ramp value that progresses one 'step'
    //Log::Print("Split [%04x : %04x] ramp into [%04x : %04x] and [%04x : %04x]\n", start, end, iStart, iEnd, remaining.iStart, remaining.iEnd);
    Validate("Split");
    remaining.Validate("Split - remaining");
    return remaining;
}


// RampApplicator

const TUint RampApplicator::kFullRampSpan = Ramp::kMax - Ramp::kMin;

RampApplicator::RampApplicator(const Media::Ramp& aRamp)
    : iRamp(aRamp)
    , iPtr(nullptr)
{
}

TUint RampApplicator::Start(const Brx& aData, TUint aBitDepth, TUint aNumChannels)
{
    iPtr = aData.Ptr();
    iBitDepth = aBitDepth;
    iNumChannels = aNumChannels;
    ASSERT_DEBUG(aData.Bytes() % ((iBitDepth/8) * iNumChannels) == 0);
    iNumSamples = (TInt)(aData.Bytes() / ((iBitDepth/8) * iNumChannels));
    iTotalRamp = (iRamp.Start() - iRamp.End());
    iLoopCount = 0;
    return iNumSamples;
}

void RampApplicator::GetNextSample(TByte* aDest)
{
    ASSERT_DEBUG(iPtr != nullptr);
    const TUint16 ramp = (iNumSamples==1? (TUint16)iRamp.Start() : (TUint16)(iRamp.Start() - ((iLoopCount * iTotalRamp)/(iNumSamples-1))));
    //Log::Print(" %04x ", ramp);
    const TUint rampIndex = std::min(kRampArrayCount-1, (kFullRampSpan - ramp + (1<<4)) >> 5); // assumes fullRampSpan==2^14 and kRampArray has 512 (2^9) items. (1<<4 allows rounding up)
    for (TUint i=0; i<iNumChannels; i++) {
        TInt16 subsample16 = 0;
        switch (iBitDepth)
        {
        case 8:
            subsample16 = *iPtr++ << 8;
            break;
        case 16:
            subsample16 = *iPtr++ << 8;
            subsample16 += *iPtr++;
            break;
        case 24:
            subsample16 = *iPtr++ << 8;
            subsample16 += *iPtr++;
            iPtr++;
            break;
        case 32:
            subsample16 = *iPtr++ << 8;
            subsample16 += *iPtr++;
            iPtr++;
            iPtr++;
            break;
        default:
            ASSERTS();
        }
        //Log::Print(" %03u ", rampIndex);
        const TUint16 rampMult = static_cast<TUint16>(kRampArray[rampIndex]);
        TInt rampedSubsample = (rampIndex==512? 0 : (subsample16 * rampMult) >> 15);
        //Log::Print("Original=%04x (%d), ramped=%04x (%d), rampIndex=%u\n", subsample, subsample, rampedSubsample, rampedSubsample, rampIndex);

        switch (iBitDepth)
        {
        case 8:
            *aDest++ = (TByte)(rampedSubsample >> 8);
            break;
        case 16:
            *aDest++ = (TByte)(rampedSubsample >> 8);
            *aDest++ = (TByte)rampedSubsample;
            break;
        case 24:
            *aDest++ = (TByte)(rampedSubsample >> 8);
            *aDest++ = (TByte)rampedSubsample;
            *aDest++ = (TByte)0;
            break;
        case 32:
            *aDest++ = (TByte)(rampedSubsample >> 8);
            *aDest++ = (TByte)rampedSubsample;
            *aDest++ = (TByte)0;
            *aDest++ = (TByte)0;
            break;
        default:
            ASSERTS();
        }
    }

    iLoopCount++;
}

TUint RampApplicator::MedianMultiplier(const Media::Ramp& aRamp)
{ // static
    TUint medRamp;
    switch (aRamp.Direction())
    {
    case Ramp::EUp:
        medRamp = aRamp.Start() + ((aRamp.End() - aRamp.Start()) / 2);
        break;
    case Ramp::EDown:
        medRamp = aRamp.Start() - ((aRamp.Start() - aRamp.End()) / 2);
        break;
    case Ramp::EMute:
        return 0;
    default:
        medRamp = aRamp.Start();
        break;
    }
    const TUint rampIndex = (Ramp::kMax - Ramp::kMin - medRamp + (1<<4)) >> 5; // assumes (Ramp::kMax - Ramp::kMin)==2^14 and kRampArray has 512 (2^9) items. (1<<4 allows rounding up)
    return kRampArray[rampIndex];
}


// Track

Track::Track(AllocatorBase& aAllocator)
    : Allocated(aAllocator)
{
    Clear();
}

const Brx& Track::Uri() const
{
    return iUri;
}

const Brx& Track::MetaData() const
{
    return iMetaData;
}

TUint Track::Id() const
{
    return iId;
}

void Track::Initialise(const Brx& aUri, const Brx& aMetaData, TUint aId)
{
    iUri.ReplaceThrow(aUri);
    if (aMetaData.Bytes() > iMetaData.MaxBytes()) {
        iMetaData.Replace(aMetaData.Split(0, iMetaData.MaxBytes()));
    }
    else {
        iMetaData.Replace(aMetaData);
    }
    iId = aId;
}

void Track::Clear()
{
#ifdef DEFINE_DEBUG
    iUri.SetBytes(0);
    iMetaData.SetBytes(0);
    iId = UINT_MAX;
#endif // DEFINE_DEBUG
}


// ModeInfo

ModeInfo::ModeInfo()
{
    Clear();
}

void ModeInfo::Set(TBool aSupportsLatency, TBool aSupportsNext, TBool aSupportsPrev)
{
    iSupportsLatency = aSupportsLatency;
    iSupportsNext    = aSupportsNext;
    iSupportsPrev    = aSupportsPrev;
}

void ModeInfo::Clear()
{
    iSupportsLatency = false;
    iSupportsNext    = false;
    iSupportsPrev    = false;
}


// ModeClockPullers

ModeClockPullers::ModeClockPullers()
    : iEnabled(false)
    , iPipelineBuffer(nullptr)
{
}

ModeClockPullers::ModeClockPullers(TBool aEnabled)
    : iEnabled(aEnabled)
    , iPipelineBuffer(nullptr)
{
}

ModeClockPullers::ModeClockPullers(IClockPuller* aPipelineBuffer)
    : iEnabled(aPipelineBuffer != nullptr)
    , iPipelineBuffer(aPipelineBuffer)
{
}

TBool ModeClockPullers::Enabled() const
{
    return iEnabled;
}

IClockPuller* ModeClockPullers::PipelineBuffer() const
{
    return iPipelineBuffer;
}


// MsgMode

MsgMode::MsgMode(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

const Brx& MsgMode::Mode() const
{
    return iMode;
}

const ModeInfo& MsgMode::Info() const
{
    return iInfo;
}

const ModeClockPullers& MsgMode::ClockPullers() const
{
    return iClockPullers;
}

void MsgMode::Initialise(const Brx& aMode, TBool aSupportsLatency, ModeClockPullers aClockPullers, TBool aSupportsNext, TBool aSupportsPrev)
{
    iMode.Replace(aMode);
    iInfo.Set(aSupportsLatency, aSupportsNext, aSupportsPrev);
    iClockPullers = aClockPullers;
}

void MsgMode::Clear()
{
    iMode.Replace(Brx::Empty());
    iInfo.Clear();
    iClockPullers = ModeClockPullers();
}

Msg* MsgMode::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgDrain

MsgDrain::MsgDrain(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

void MsgDrain::ReportDrained()
{
    if (iCallback) {
        iCallback();
        iCallbackPending = false;
    }
}

TUint MsgDrain::Id() const
{
    return iId;
}

void MsgDrain::Initialise(TUint aId, Functor aCallback)
{
    iId = aId;
    iCallback = aCallback;
    iCallbackPending = iCallback? true : false;
}

void MsgDrain::Clear()
{
    ASSERT(!iCallbackPending);
    iCallback = Functor();
}



Msg* MsgDrain::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgTrack

MsgTrack::MsgTrack(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

Media::Track& MsgTrack::Track() const
{
    ASSERT(iTrack != nullptr);
    return *iTrack;
}

TBool MsgTrack::StartOfStream() const
{
    return iStartOfStream;
}

void MsgTrack::Initialise(Media::Track& aTrack, TBool aStartOfStream)
{
    iTrack = &aTrack;
    iTrack->AddRef();
    iStartOfStream = aStartOfStream;
}

void MsgTrack::Clear()
{
    iTrack->RemoveRef();
    iTrack = nullptr;
    iStartOfStream = false;
}

Msg* MsgTrack::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgDelay

MsgDelay::MsgDelay(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

TUint MsgDelay::DelayJiffies() const
{
    return iDelayJiffies;
}

void MsgDelay::Initialise(TUint aDelayJiffies)
{
    iDelayJiffies = aDelayJiffies;
}

void MsgDelay::Clear()
{
    iDelayJiffies = UINT_MAX;
}

Msg* MsgDelay::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}

// SpeakerProfile
SpeakerProfile::SpeakerProfile(TUint aNumFronts)
    : SpeakerProfile(aNumFronts, 0, 0)
{
}

SpeakerProfile::SpeakerProfile(TUint aNumFronts, TUint aNumSurrounds, TUint aNumSubs)
    : iNumFronts(aNumFronts)
    , iNumSurrounds(aNumSurrounds)
    , iNumSubs(aNumSubs)
{
    ASSERT(iNumFronts <= 3);
    ASSERT(iNumSurrounds <= 4);
    ASSERT(iNumSubs <= 2);

    // Create the string representation
    iName.AppendPrintf("%u/%u.%u", iNumFronts, iNumSurrounds, iNumSubs);
}

TUint SpeakerProfile::NumFronts() const         { return iNumFronts; }
TUint SpeakerProfile::NumSurrounds() const      { return iNumSurrounds; }
TUint SpeakerProfile::NumSubs() const           { return iNumSubs; }
const TChar* SpeakerProfile::ToString() const   { return iName.PtrZ(); }

TBool SpeakerProfile::operator==(const SpeakerProfile& aOther) const
{
    return (iNumFronts == aOther.iNumFronts) &&
           (iNumSurrounds == aOther.iNumSurrounds) &&
           (iNumSubs == aOther.iNumSubs);
}

TBool SpeakerProfile::operator!=(const SpeakerProfile& aOther) const
{
    return !(*this == aOther);
}

const SpeakerProfile& SpeakerProfile::operator=(const SpeakerProfile& aOther)
{
    iNumFronts = aOther.iNumFronts;
    iNumSurrounds = aOther.iNumSurrounds;
    iNumSubs = aOther.iNumSubs;
    iName.Replace(aOther.iName);
    return *this;
}

// PcmStreamInfo

PcmStreamInfo::PcmStreamInfo()
{
    Clear();
}

void PcmStreamInfo::Set(TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, AudioDataEndian aEndian, const SpeakerProfile& aProfile, TUint64 aStartSample)
{
    iBitDepth = aBitDepth;
    iSampleRate = aSampleRate;
    iNumChannels = aNumChannels;
    iEndian = aEndian;
    iProfile = aProfile;
    iStartSample = aStartSample;
    iCodecName.Replace(Brn("PCM"));
    iLossless = true;
}

void PcmStreamInfo::SetAnalogBypass()
{
    iAnalogBypass = true;
}

void PcmStreamInfo::SetCodec(const Brx& aCodecName, TBool aLossless)
{
    iCodecName.Replace(aCodecName);
    iLossless = aLossless;
}

void PcmStreamInfo::Clear()
{
    iBitDepth = iSampleRate = iNumChannels = UINT_MAX;
    iEndian = AudioDataEndian::Invalid;
    iAnalogBypass = false;
    iCodecName.Replace(Brx::Empty());
    iLossless = true;
}

TUint PcmStreamInfo::BitDepth() const
{
    return iBitDepth;
}

TUint PcmStreamInfo::SampleRate() const
{
    return iSampleRate;
}

TUint PcmStreamInfo::NumChannels() const
{
    return iNumChannels;
}

AudioDataEndian PcmStreamInfo::Endian() const
{
    return iEndian;
}

const SpeakerProfile& PcmStreamInfo::Profile() const
{
    return iProfile;
}

TUint64 PcmStreamInfo::StartSample() const
{
    return iStartSample;
}

TBool PcmStreamInfo::AnalogBypass() const
{
    return iAnalogBypass;
}

const Brx& PcmStreamInfo::CodecName() const
{
    return iCodecName;
}

TBool PcmStreamInfo::Lossless() const
{
    return iLossless;
}

void PcmStreamInfo::operator=(const PcmStreamInfo& aPcmStream)
{
    iBitDepth = aPcmStream.BitDepth();
    iSampleRate = aPcmStream.SampleRate();
    iNumChannels = aPcmStream.NumChannels();
    iEndian = aPcmStream.Endian();
    iProfile = aPcmStream.Profile();
    iStartSample = aPcmStream.StartSample();
    iAnalogBypass = aPcmStream.AnalogBypass();
    iCodecName.Replace(aPcmStream.CodecName());
    iLossless = aPcmStream.Lossless();
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

TUint64 MsgEncodedStream::StartPos() const
{
    return iStartPos;
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

Multiroom MsgEncodedStream::Multiroom() const
{
    return iMultiroom;
}

IStreamHandler* MsgEncodedStream::StreamHandler() const
{
    return iStreamHandler;
}

TBool MsgEncodedStream::RawPcm() const
{
    return iRawPcm;
}

const PcmStreamInfo& MsgEncodedStream::PcmStream() const
{
    ASSERT(iRawPcm);
    return iPcmStreamInfo;
}

void MsgEncodedStream::Initialise(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint64 aStartPos, TUint aStreamId, TBool aSeekable, TBool aLive, Media::Multiroom aMultiroom, IStreamHandler* aStreamHandler)
{
    iUri.Replace(aUri);
    iMetaText.Replace(aMetaText);
    iTotalBytes = aTotalBytes;
    iStartPos= aStartPos;
    iStreamId = aStreamId;
    iSeekable = aSeekable;
    iLive = aLive;
    iMultiroom = aMultiroom;
    iStreamHandler = aStreamHandler;
    iRawPcm = false;
    iPcmStreamInfo.Clear();
}

void MsgEncodedStream::Initialise(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint64 aStartPos, TUint aStreamId, TBool aSeekable, TBool aLive, Media::Multiroom aMultiroom, IStreamHandler* aStreamHandler, const PcmStreamInfo& aPcmStream)
{
    iUri.Replace(aUri);
    iMetaText.Replace(aMetaText);
    iTotalBytes = aTotalBytes;
    iStartPos= aStartPos;
    iStreamId = aStreamId;
    iSeekable = aSeekable;
    iLive = aLive;
    iMultiroom = aMultiroom;
    iStreamHandler = aStreamHandler;
    iRawPcm = true;
    iPcmStreamInfo = aPcmStream;
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
    iRawPcm = false;
    iStreamHandler = nullptr;
    iPcmStreamInfo.Clear();
#endif
}

Msg* MsgEncodedStream::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgAudioEncoded

MsgAudioEncoded::MsgAudioEncoded(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

MsgAudioEncoded* MsgAudioEncoded::Split(TUint aBytes)
{
    if (aBytes > iSize) {
        ASSERT(iNextAudio != nullptr);
        return iNextAudio->Split(aBytes - iSize);
    }
    if (aBytes == iSize) {
        ASSERT(iNextAudio != nullptr);
        MsgAudioEncoded* next = iNextAudio;
        iNextAudio = nullptr;
        return next;
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
    iNextAudio = nullptr;
    return remaining;
}

void MsgAudioEncoded::Add(MsgAudioEncoded* aMsg)
{
    MsgAudioEncoded* end = this;
    MsgAudioEncoded* next = iNextAudio;
    while (next != nullptr) {
        end = next;
        next = next->iNextAudio;
    }
    end->iNextAudio = aMsg;
}

TUint MsgAudioEncoded::Append(const Brx& aData)
{
    ASSERT(iNextAudio == nullptr);
    const TUint consumed = iAudioData->Append(aData);
    iSize += consumed;
    return consumed;
}

TUint MsgAudioEncoded::Bytes() const
{
    TUint bytes = iSize;
    MsgAudioEncoded* next = iNextAudio;
    while (next != nullptr) {
        bytes += next->iSize;
        next = next->iNextAudio;
    }
    return bytes;
}

void MsgAudioEncoded::CopyTo(TByte* aPtr)
{
    const TByte* src = iAudioData->Ptr(iOffset);
    (void)memcpy(aPtr, src, iSize);
    if (iNextAudio != nullptr) {
        iNextAudio->CopyTo(aPtr + iSize);
    }
}

MsgAudioEncoded* MsgAudioEncoded::Clone()
{
    MsgAudioEncoded* clone = static_cast<Allocator<MsgAudioEncoded>&>(iAllocator).Allocate();
    clone->iNextAudio = nullptr;
    if (iNextAudio) {
        clone->iNextAudio = iNextAudio->Clone();
    }
    clone->iSize = iSize;
    clone->iOffset = iOffset;
    clone->iAudioData = iAudioData;
    iAudioData->AddRef();
    return clone;
}

void MsgAudioEncoded::Initialise(EncodedAudio* aEncodedAudio)
{
    iAudioData = aEncodedAudio;
    iSize = iAudioData->Bytes();
    iOffset = 0;
    iNextAudio = nullptr;
}

void MsgAudioEncoded::RefAdded()
{
    /* FIXME - not clear that its correct to Add/Remove refs down a chain like this
       it might be better to modify the head msg only then RemoveRef down the chain when
       the head is Clear()ed */
    if (iNextAudio != nullptr) {
        iNextAudio->AddRef();
    }
}

void MsgAudioEncoded::RefRemoved()
{
    if (iNextAudio != nullptr) {
        iNextAudio->RemoveRef();
    }
}

void MsgAudioEncoded::Clear()
{
    iAudioData->RemoveRef();
}

Msg* MsgAudioEncoded::Process(IMsgProcessor& aProcessor)
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


// MsgStreamInterrupted

MsgStreamInterrupted::MsgStreamInterrupted(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

Msg* MsgStreamInterrupted::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgHalt

MsgHalt::MsgHalt(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

TUint MsgHalt::Id() const
{
    return iId;
}

void MsgHalt::ReportHalted()
{
    if (iCallback) {
        iCallback();
        iCallback = Functor();
    }
}

void MsgHalt::Initialise(TUint aId)
{
    Initialise(aId, Functor());
}

void MsgHalt::Initialise(TUint aId, Functor aCallback)
{
    iId = aId;
    iCallback = aCallback;
}

void MsgHalt::Clear()
{
    iId = UINT_MAX;
    iCallback = Functor();
}

Msg* MsgHalt::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgFlush

const TUint MsgFlush::kIdInvalid  = 0;

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


// MsgWait

MsgWait::MsgWait(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

Msg* MsgWait::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
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
    , iStreamHandler(nullptr)
{
}

void DecodedStreamInfo::Set(TUint aStreamId, TUint aBitRate, TUint aBitDepth, TUint aSampleRate,
                            TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength,
                            TUint64 aSampleStart, TBool aLossless, TBool aSeekable, TBool aLive,
                            TBool aAnalogBypass, Media::Multiroom aMultiroom,
                            const SpeakerProfile& aProfile, IStreamHandler* aStreamHandler)
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
    iAnalogBypass = aAnalogBypass;
    iMultiroom = aMultiroom;
    iProfile = aProfile;
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

void MsgDecodedStream::Initialise(TUint aStreamId, TUint aBitRate, TUint aBitDepth, TUint aSampleRate,
                                  TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength,
                                  TUint64 aSampleStart, TBool aLossless, TBool aSeekable, TBool aLive,
                                  TBool aAnalogBypass, Media::Multiroom aMultiroom,
                                  const SpeakerProfile& aProfile, IStreamHandler* aStreamHandler)
{
    iStreamInfo.Set(aStreamId, aBitRate, aBitDepth, aSampleRate, aNumChannels, aCodecName, aTrackLength, aSampleStart, aLossless, aSeekable, aLive, aAnalogBypass, aMultiroom, aProfile, aStreamHandler);
}

void MsgDecodedStream::Clear()
{
#ifdef DEFINE_DEBUG
    iStreamInfo.Set(UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, Brx::Empty(), ULONG_MAX, ULONG_MAX, false, false, false, false, Multiroom::Allowed, SpeakerProfile(), nullptr);
#endif
}

Msg* MsgDecodedStream::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgBitRate

MsgBitRate::MsgBitRate(AllocatorBase& aAllocator)
    : Msg(aAllocator)
    , iBitRate(0)
{
}

TUint MsgBitRate::BitRate() const
{
    return iBitRate;
}

void MsgBitRate::Initialise(TUint aBitRate)
{
    iBitRate = aBitRate;
}

void MsgBitRate::Clear()
{
    iBitRate = 0;
}

Msg* MsgBitRate::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgAudio

void MsgAudio::SetObserver(IPipelineBufferObserver& aPipelineBufferObserver)
{
    ASSERT(iPipelineBufferObserver == nullptr);
    iPipelineBufferObserver = &aPipelineBufferObserver;
    iPipelineBufferObserver->Update((TInt)iSize);
}

MsgAudio* MsgAudio::Split(TUint aJiffies)
{
    ASSERT(aJiffies > 0);
    ASSERT(aJiffies < iSize);
    MsgAudio* remaining = Allocate();
    remaining->iOffset = iOffset + aJiffies;
    remaining->iSize = iSize - aJiffies;
    remaining->iSampleRate = iSampleRate;
    remaining->iBitDepth = iBitDepth;
    remaining->iNumChannels = iNumChannels;
    remaining->iPipelineBufferObserver = iPipelineBufferObserver;
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

MsgAudio* MsgAudio::Clone()
{
    MsgAudio* clone = Allocate();
    clone->iSize = iSize;
    clone->iOffset = iOffset;
    clone->iRamp = iRamp;
    clone->iSampleRate = iSampleRate;
    clone->iBitDepth = iBitDepth;
    clone->iNumChannels = iNumChannels;
    clone->iPipelineBufferObserver = nullptr;
    return clone;
}

TUint MsgAudio::Jiffies() const
{
    return iSize;
}

TUint MsgAudio::SetRamp(TUint aStart, TUint& aRemainingDuration, Ramp::EDirection aDirection, MsgAudio*& aSplit)  // FIXME
{
    const TUint remainingDuration = aRemainingDuration;
    Media::Ramp split;
    TUint splitPos;
    aSplit = nullptr;

    ASSERT(aDirection == Ramp::EUp || aDirection == Ramp::EDown);
    if (iRamp.IsEnabled() && iRamp.Direction() == Ramp::EMute) {
        if (aDirection == Ramp::EDown) {
            aRemainingDuration = 0;
        }
        return iRamp.End();
    }

    /*TBool logAppliedRamp = false;
    if (iRamp.IsEnabled()) {
        Log::Print("++ MsgAudio::SetRamp(%08x, %u, %u): Existing ramp is [%08x...%08x]\n", aStart, aRemainingDuration, aDirection, iRamp.Start(), iRamp.End());
        logAppliedRamp = true;
    }*/
    if (iRamp.Set(aStart, iSize, remainingDuration, aDirection, split, splitPos)) {
        if (splitPos == 0) {
            iRamp = split;
        }
        else if (splitPos != iSize) {
            Media::Ramp ramp = iRamp; // Split() will muck about with ramps.  Allow this to happen then reset the correct values
            aSplit = Split(splitPos);
            iRamp = ramp;
            aSplit->iRamp = split;
            ASSERT_DEBUG(iRamp.End() == split.Start());
            //Log::Print("\nSplit msg at %u jiffies.  First ramp=[%08x...%08x], second ramp=[%08x...%08x]\n",
            //            splitPos, iRamp.Start(), iRamp.End(), split.Start(), split.End());
        }
    }
    /*if (logAppliedRamp) {
        Log::Print("++ final ramp: [%08x...%08x]", iRamp.Start(), iRamp.End());
        if (aSplit != nullptr) {
            Log::Print("   split: [%08x...%08x]", aSplit->iRamp.Start(), aSplit->iRamp.End());
        }
        Log::Print("\n");
    }*/

    aRemainingDuration -= iSize;
    if (aSplit != nullptr && aSplit->Ramp().Direction() != aDirection && aDirection == Ramp::EUp) {
        aRemainingDuration += aSplit->iSize; // roughly compensate for split running in opposite direction to requested ramp
    }

    // It may be possible to terminate ramps down early if the msg had previously been ramped
    if (aDirection == Ramp::EDown && iRamp.End() == Ramp::kMin) {
        aRemainingDuration = 0;
    }
    else if (aDirection == Ramp::EUp && iRamp.End() == Ramp::kMax) {
        // shorter ramp range now allows ramps up to complete a few samples early
        aRemainingDuration = 0;
    }

    return iRamp.End();
}

void MsgAudio::ClearRamp()
{
    iRamp.Reset();
}

void MsgAudio::SetMuted()
{
    iRamp.SetMuted();
}

const Media::Ramp& MsgAudio::Ramp() const
{
    return iRamp;
}

TUint MsgAudio::MedianRampMultiplier()
{
    if (!iRamp.IsEnabled()) {
        return 0x8000; // see RampArray.h
    }
    else if (iRamp.Direction() == Ramp::EMute) {
        return 0;
    }
    const TUint mult = RampApplicator::MedianMultiplier(iRamp);
    iRamp.Reset();
    return mult;
}

MsgAudio::MsgAudio(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

void MsgAudio::Initialise(TUint aSampleRate, TUint aBitDepth, TUint aChannels)
{
    iRamp.Reset();
    iSampleRate = aSampleRate;
    iBitDepth = aBitDepth;
    iNumChannels = aChannels;
    iPipelineBufferObserver = nullptr;
}

void MsgAudio::Clear()
{
    if (iPipelineBufferObserver != nullptr) {
        TInt jiffies = (TInt)iSize;
        iPipelineBufferObserver->Update(-jiffies);
    }
    iSize = 0;
}

void MsgAudio::SplitCompleted(MsgAudio& /*aMsg*/)
{
    // nothing to do by default
}


// MsgAudioPcm

const TUint64 MsgAudioPcm::kTrackOffsetInvalid = UINT64_MAX;
const TUint MsgAudioPcm::kUnityAttenuation = 256;

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
    const TUint jiffiesPerSample = Jiffies::PerSample(iSampleRate);
    const TUint offsetBytes = Jiffies::ToBytes(offsetJiffies, jiffiesPerSample, iNumChannels, iBitDepth/8);
    TUint sizeJiffies = iSize + (iOffset - offsetJiffies);
    const TUint sizeBytes = Jiffies::ToBytes(sizeJiffies, jiffiesPerSample, iNumChannels, iBitDepth/8);
    // both size & offset will be rounded down if they don't fall on a sample boundary
    // we don't risk losing any data doing this as the start and end of each DecodedAudio's data fall on sample boundaries

    Optional<IPipelineBufferObserver> bufferObserver(iPipelineBufferObserver);
    MsgPlayable* playable;
    if (iRamp.Direction() != Ramp::EMute) {
        MsgPlayablePcm* pcm = iAllocatorPlayablePcm->Allocate();
        pcm->Initialise(iAudioData, sizeBytes, iSampleRate, iBitDepth, iNumChannels, offsetBytes, iAttenuation, iRamp, bufferObserver);
        playable = pcm;
    }
    else {
        MsgPlayableSilence* silence = iAllocatorPlayableSilence->Allocate();
        Media::Ramp noRamp;
        silence->Initialise(sizeBytes, iSampleRate, iBitDepth, iNumChannels, noRamp, bufferObserver);
        playable = silence;
    }
    iPipelineBufferObserver = nullptr;
    RemoveRef();
    return playable;
}

void MsgAudioPcm::Aggregate(MsgAudioPcm* aMsg)
{
    ASSERT(aMsg->iSampleRate == iSampleRate);
    ASSERT(aMsg->iBitDepth == iBitDepth);
    ASSERT(aMsg->iNumChannels == iNumChannels);
    ASSERT(aMsg->iTrackOffset == iTrackOffset+Jiffies());   // aMsg must logically follow this one
    ASSERT(!iRamp.IsEnabled() && !aMsg->iRamp.IsEnabled()); // no ramps allowed

    iAudioData->Aggregate(*(aMsg->iAudioData));
    iSize += aMsg->Jiffies();
    aMsg->RemoveRef();
}

MsgAudio* MsgAudioPcm::Clone()
{
    MsgAudioPcm* clone = static_cast<MsgAudioPcm*>(MsgAudio::Clone());
    clone->iAudioData = iAudioData;
    clone->iAllocatorPlayablePcm = iAllocatorPlayablePcm;
    clone->iAllocatorPlayableSilence = iAllocatorPlayableSilence;
    clone->iTrackOffset = iTrackOffset;
    clone->iAttenuation = iAttenuation;
    iAudioData->AddRef();
    return clone;
}

void MsgAudioPcm::Initialise(DecodedAudio* aDecodedAudio, TUint aSampleRate, TUint aBitDepth, TUint aChannels, TUint64 aTrackOffset,
                             Allocator<MsgPlayablePcm>& aAllocatorPlayablePcm,
                             Allocator<MsgPlayableSilence>& aAllocatorPlayableSilence)
{
    MsgAudio::Initialise(aSampleRate, aBitDepth, aChannels);
    iAllocatorPlayablePcm = &aAllocatorPlayablePcm;
    iAllocatorPlayableSilence = &aAllocatorPlayableSilence;
    iAudioData = aDecodedAudio;
    iTrackOffset = aTrackOffset;
    iAttenuation = MsgAudioPcm::kUnityAttenuation;
    const TUint bytes = iAudioData->Bytes();
    const TUint byteDepth = iBitDepth / 8;
    ASSERT(bytes % byteDepth == 0);
    const TUint numSubsamples = bytes / byteDepth;
    ASSERT(numSubsamples % iNumChannels == 0);
    iSize = (numSubsamples / iNumChannels) * Jiffies::PerSample(iSampleRate);
    ASSERT(iSize > 0);
    iOffset = 0;
}

void MsgAudioPcm::SplitCompleted(MsgAudio& aRemaining)
{
    iAudioData->AddRef();
    MsgAudioPcm& remaining = static_cast<MsgAudioPcm&>(aRemaining);
    remaining.iAudioData = iAudioData;
    remaining.iTrackOffset = iTrackOffset + iSize;
    remaining.iAllocatorPlayablePcm = iAllocatorPlayablePcm;
    remaining.iAllocatorPlayableSilence = iAllocatorPlayableSilence;
    remaining.iAttenuation = iAttenuation;
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

void MsgAudioPcm::SetAttenuation(TUint aAttenuation)
{
    iAttenuation = aAttenuation;
}

// MsgSilence

MsgSilence::MsgSilence(AllocatorBase& aAllocator)
    : MsgAudio(aAllocator)
{
}

MsgPlayable* MsgSilence::CreatePlayable()
{
    TUint offsetJiffies = iOffset;
    const TUint jiffiesPerSample = Jiffies::PerSample(iSampleRate);
    const TUint bytesPerSubsample = iBitDepth/8;
    (void)Jiffies::ToBytes(offsetJiffies, jiffiesPerSample, iNumChannels, bytesPerSubsample);
    TUint sizeJiffies = iSize + (iOffset - offsetJiffies);
    const TUint sizeBytes = Jiffies::ToBytes(sizeJiffies, jiffiesPerSample, iNumChannels, bytesPerSubsample);
    // both size & offset will be rounded down if they don't fall on a sample boundary
    // we don't risk losing any data doing this as each original MsgSilence had an integer number of samples

    MsgPlayableSilence* playable = iAllocatorPlayable->Allocate();
    Optional<IPipelineBufferObserver> bufferObserver(nullptr);
    playable->Initialise(sizeBytes, iSampleRate, iBitDepth, iNumChannels, iRamp, bufferObserver);
    RemoveRef();
    return playable;
}

MsgAudio* MsgSilence::Clone()
{
    MsgSilence* clone = static_cast<MsgSilence*>(MsgAudio::Clone());
    clone->iAllocatorPlayable = iAllocatorPlayable;
    return clone;
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
    MsgSilence& remaining = static_cast<MsgSilence&>(aRemaining);
    remaining.iAllocatorPlayable = iAllocatorPlayable;
}

void MsgSilence::Initialise(TUint& aJiffies, TUint aSampleRate, TUint aBitDepth, TUint aChannels, Allocator<MsgPlayableSilence>& aAllocatorPlayable)
{
    MsgAudio::Initialise(aSampleRate, aBitDepth, aChannels);
    iAllocatorPlayable = &aAllocatorPlayable;
    TUint jiffies = aJiffies;
    Jiffies::RoundDown(jiffies, aSampleRate);
    if (jiffies == 0) {
        Jiffies::RoundUp(aJiffies, aSampleRate);
    }
    else {
        aJiffies = jiffies;
    }
    iSize = aJiffies;
    iOffset = 0;
}


// MsgPlayable

MsgPlayable* MsgPlayable::Split(TUint aBytes)
{
    if (aBytes > iSize) {
        ASSERT(iNextPlayable != nullptr);
        return iNextPlayable->Split(aBytes - iSize);
    }
    ASSERT(aBytes != 0);
    if (aBytes == iSize) {
        MsgPlayable* remaining = iNextPlayable;
        iNextPlayable = nullptr;
        return remaining;
    }
    MsgPlayable* remaining = Allocate();
    remaining->iNextPlayable = iNextPlayable;
    remaining->iOffset = iOffset + aBytes;
    remaining->iSize = iSize - aBytes;
    remaining->iSampleRate = iSampleRate;
    remaining->iBitDepth = iBitDepth;
    remaining->iNumChannels = iNumChannels;
    if (iRamp.IsEnabled()) {
        remaining->iRamp = iRamp.Split(aBytes, iSize);
    }
    else {
        remaining->iRamp.Reset();
    }
    remaining->iPipelineBufferObserver = iPipelineBufferObserver;
    iSize = aBytes;
    iNextPlayable = nullptr;
    SplitCompleted(*remaining);
    return remaining;
}

void MsgPlayable::Add(MsgPlayable* aMsg)
{
    MsgPlayable* end = this;
    MsgPlayable* next = iNextPlayable;
    while (next != nullptr) {
        end = next;
        next = next->iNextPlayable;
    }
    end->iNextPlayable = aMsg;
}

TUint MsgPlayable::Bytes() const
{
    TUint bytes = iSize;
    MsgPlayable* next = iNextPlayable;
    while (next != nullptr) {
        bytes += next->iSize;
        next = next->iNextPlayable;
    }
    return bytes;
}

TUint MsgPlayable::Jiffies() const
{
    TUint jiffies = MsgJiffies();
    MsgPlayable* next = iNextPlayable;
    while (next != nullptr) {
        jiffies += next->MsgJiffies();
        next = next->iNextPlayable;
    }
    return jiffies;
}

TUint MsgPlayable::MsgJiffies() const
{
    const TUint numSamples = iSize / ((iBitDepth/8) * iNumChannels);
    return numSamples * Jiffies::PerSample(iSampleRate);
}

const Media::Ramp& MsgPlayable::Ramp() const
{
    return iRamp;
}

void MsgPlayable::Read(IPcmProcessor& aProcessor)
{
    aProcessor.BeginBlock();
    MsgPlayable* playable = this;
    while (playable != nullptr) {
        playable->ReadBlock(aProcessor);
        playable = playable->iNextPlayable;
    }
    aProcessor.EndBlock();
}

MsgPlayable::MsgPlayable(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

void MsgPlayable::Initialise(TUint aSizeBytes, TUint aSampleRate, TUint aBitDepth,
                             TUint aNumChannels, TUint aOffsetBytes, const Media::Ramp& aRamp,
                             Optional<IPipelineBufferObserver> aPipelineBufferObserver)
{
    iNextPlayable = nullptr;
    iSize = aSizeBytes;
    iSampleRate = aSampleRate;
    iBitDepth = aBitDepth;
    iNumChannels = aNumChannels;
    iOffset = aOffsetBytes;
    iRamp = aRamp;
    iPipelineBufferObserver = aPipelineBufferObserver.Ptr();
}

void MsgPlayable::RefAdded()
{
    if (iNextPlayable != nullptr) {
        iNextPlayable->AddRef();
    }
}

void MsgPlayable::RefRemoved()
{
    if (iNextPlayable != nullptr) {
        iNextPlayable->RemoveRef();
    }
}

Msg* MsgPlayable::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}

void MsgPlayable::Clear()
{
    if (iPipelineBufferObserver != nullptr) {
        TInt jiffies = MsgJiffies();
        iPipelineBufferObserver->Update(-jiffies);
        iPipelineBufferObserver = nullptr;
    }
    iNextPlayable = nullptr;
    iSize = iSampleRate = iBitDepth = iNumChannels = iOffset = 0;
    iRamp.Reset();
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

void MsgPlayablePcm::Initialise(DecodedAudio* aDecodedAudio, TUint aSizeBytes, TUint aSampleRate, TUint aBitDepth,
                                TUint aNumChannels, TUint aOffsetBytes, TUint aAttenuation, const Media::Ramp& aRamp,
                                Optional<IPipelineBufferObserver> aPipelineBufferObserver)
{
    MsgPlayable::Initialise(aSizeBytes, aSampleRate, aBitDepth, aNumChannels,
                            aOffsetBytes, aRamp, aPipelineBufferObserver);
    iAudioData = aDecodedAudio;
    iAudioData->AddRef();
    iAttenuation = aAttenuation;
}

Brn MsgPlayablePcm::ApplyAttenuation(Brn aData)
{
    // Note: A static buffer is used here for performance reasons.
    // This method must only be called from a single thread to ensure data validity.
    static Bws<AudioData::kMaxBytes> attenuatedData;

    if(iAttenuation != MsgAudioPcm::kUnityAttenuation) {
        switch (iBitDepth) {
        case 16:
            {
                TInt16* source = (TInt16*)aData.Ptr();
                TInt16* dest = (TInt16*)attenuatedData.Ptr();
                TUint samples = aData.Bytes()/2;
                attenuatedData.SetBytes(aData.Bytes());
                for(TUint i = 0; i < samples; i++) {
                    dest[i] = (TInt16)((TInt32)source[i] * iAttenuation / MsgAudioPcm::kUnityAttenuation);
                }
            }
            break;

        default:
            ASSERTS();  //only supports 16 bit data (for AirPlay)
            break;
        }
        return Brn(attenuatedData);  // return modified data buffer
    }
    else {
        return aData;           // return original data buffer
    }
}

void MsgPlayablePcm::ReadBlock(IPcmProcessor& aProcessor)
{
    Brn audioBuf = ApplyAttenuation(Brn(iAudioData->Ptr(iOffset), iSize));

    const TUint numChannels = iNumChannels;
    const TUint bitDepth = iBitDepth;
    if (iRamp.IsEnabled()) {
        Bws<256> rampedBuf;
        RampApplicator ra(iRamp);
        const TUint numSamples = ra.Start(audioBuf, bitDepth, numChannels);
        const TUint bytesPerSample = (bitDepth/8) * numChannels;
        const TUint samplesPerFragment = rampedBuf.MaxBytes() / bytesPerSample;
        TByte* ptr = (TByte*)rampedBuf.Ptr();
        TUint fragmentSamples = 0;
        for (TUint i=0; i<numSamples; i++) {
            ra.GetNextSample(ptr);

            fragmentSamples++;
            ptr += bytesPerSample;
            if (fragmentSamples == samplesPerFragment || i == numSamples-1) {
                rampedBuf.SetBytes(fragmentSamples * bytesPerSample);
                switch (bitDepth)
                {
                case 8:
                    aProcessor.ProcessFragment8(rampedBuf, numChannels);
                    break;
                case 16:
                    aProcessor.ProcessFragment16(rampedBuf, numChannels);
                    break;
                case 24:
                    aProcessor.ProcessFragment24(rampedBuf, numChannels);
                    break;
                case 32:
                    aProcessor.ProcessFragment32(rampedBuf, numChannels);
                    break;
                default:
                    ASSERTS();
                }
                ptr = (TByte*)rampedBuf.Ptr();
                fragmentSamples = 0;
            }
        }
    }
    else {
        switch (bitDepth)
        {
        case 8:
            aProcessor.ProcessFragment8(audioBuf, numChannels);
            break;
        case 16:
            aProcessor.ProcessFragment16(audioBuf, numChannels);
            break;
        case 24:
            aProcessor.ProcessFragment24(audioBuf, numChannels);
            break;
        case 32:
            aProcessor.ProcessFragment32(audioBuf, numChannels);
            break;
        default:
            ASSERTS();
        }
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

void MsgPlayableSilence::Initialise(TUint aSizeBytes, TUint aSampleRate, TUint aBitDepth,
                                    TUint aNumChannels, const Media::Ramp& aRamp,
                                    Optional<IPipelineBufferObserver> aPipelineBufferObserver)
{
    MsgPlayable::Initialise(aSizeBytes, aSampleRate, aBitDepth,
                            aNumChannels, 0, aRamp, aPipelineBufferObserver);
    iBitDepth = aBitDepth;
    iNumChannels = aNumChannels;
}

void MsgPlayableSilence::ReadBlock(IPcmProcessor& aProcessor)
{
    static const TByte silence[DecodedAudio::kMaxBytes] = { 0 };
    TUint remainingBytes = iSize;
    do {
        TUint bytes = (remainingBytes > DecodedAudio::kMaxBytes? DecodedAudio::kMaxBytes : remainingBytes);
        Brn audioBuf(silence, bytes);
        switch (iBitDepth)
        {
        case 8:
            aProcessor.ProcessFragment8(audioBuf, iNumChannels);
            break;
        case 16:
            aProcessor.ProcessFragment16(audioBuf, iNumChannels);
            break;
        case 24:
            aProcessor.ProcessFragment24(audioBuf, iNumChannels);
            break;
        case 32:
            aProcessor.ProcessFragment32(audioBuf, iNumChannels);
            break;
        default:
            ASSERTS();
        }
        remainingBytes -= bytes;
    } while (remainingBytes > 0);
}

MsgPlayable* MsgPlayableSilence::Allocate()
{
    return static_cast<Allocator<MsgPlayableSilence>&>(iAllocator).Allocate();
}

void MsgPlayableSilence::SplitCompleted(MsgPlayable& aRemaining)
{
    MsgPlayableSilence& remaining = static_cast<MsgPlayableSilence&>(aRemaining);
    remaining.iBitDepth = iBitDepth;
    remaining.iNumChannels = iNumChannels;
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


// MsgQueueBase

MsgQueueBase::MsgQueueBase()
    : iHead(nullptr)
    , iTail(nullptr)
    , iNumMsgs(0)
{
}

MsgQueueBase::~MsgQueueBase()
{
    Msg* head = iHead;
    while (head != nullptr) {
        iHead = head->iNextMsg;
        head->RemoveRef();
        head = iHead;
    }
}

void MsgQueueBase::DoEnqueue(Msg* aMsg)
{
    ASSERT(aMsg != nullptr);
    CheckMsgNotQueued(aMsg); // duplicate checking
    if (iHead == nullptr) {
        iHead = aMsg;
    }
    else {
        iTail->iNextMsg = aMsg;
    }
    iTail = aMsg;
    aMsg->iNextMsg = nullptr;
    iNumMsgs++;
}

Msg* MsgQueueBase::DoDequeue()
{
    ASSERT(iHead != nullptr);
    Msg* head = iHead;
    iHead = iHead->iNextMsg;
    head->iNextMsg = nullptr; // not strictly necessary but might make debugging simpler
    if (iHead == nullptr) {
        iTail = nullptr;
    }
    iNumMsgs--;
    return head;
}

void MsgQueueBase::DoEnqueueAtHead(Msg* aMsg)
{
    ASSERT(aMsg != nullptr);
    CheckMsgNotQueued(aMsg); // duplicate checking
    aMsg->iNextMsg = iHead;
    iHead = aMsg;
    if (iTail == nullptr) {
        iTail = aMsg;
    }
    iNumMsgs++;
}

TBool MsgQueueBase::IsEmpty() const
{
    const TBool empty = (iHead == nullptr);
    return empty;
}

void MsgQueueBase::DoClear()
{
    while (iHead != nullptr) {
        Msg* msg = DoDequeue();
        msg->RemoveRef();
    }
}

TUint MsgQueueBase::NumMsgs() const
{
    return iNumMsgs;
}

void MsgQueueBase::CheckMsgNotQueued(Msg* aMsg) const
{
    ASSERT(aMsg != iTail);
    ASSERT(aMsg != iHead);
#ifdef DEFINE_DEBUG // iterate over queue, comparing aMsg to all msg pointers
    TUint count = 0;
    for (Msg* msg = iHead; msg != nullptr; msg = msg->iNextMsg) {
        ASSERT(aMsg != msg);
        count++;
    }
    if (count != iNumMsgs) {
        Log::Print("MsgQueueBase::CheckMsgNotQueued - iNumMsgs=%u, found %u\n",
                   iNumMsgs, count);
        ASSERTS();
    }
#endif
}


// MsgQueue

MsgQueue::MsgQueue()
    : iLock("MSGQ")
    , iSem("MSGQ", 0)
{
}

void MsgQueue::Enqueue(Msg* aMsg)
{
    AutoMutex _(iLock);
    DoEnqueue(aMsg);
    iSem.Signal();
}

Msg* MsgQueue::Dequeue()
{
    iSem.Wait();
    AutoMutex _(iLock);
    return MsgQueueBase::DoDequeue();
}

void MsgQueue::EnqueueAtHead(Msg* aMsg)
{
    AutoMutex _(iLock);
    DoEnqueueAtHead(aMsg);
    iSem.Signal();
}

TBool MsgQueue::IsEmpty() const
{
    AutoMutex _(iLock);
    return MsgQueueBase::IsEmpty();
}

void MsgQueue::Clear()
{
    AutoMutex _(iLock);
    DoClear();
    (void)iSem.Clear();
}

TUint MsgQueue::NumMsgs() const
{
    AutoMutex _(iLock);
    return MsgQueueBase::NumMsgs();
}


// MsgReservoir

MsgReservoir::MsgReservoir()
    : iEncodedBytes(0)
    , iJiffies(0)
    , iTrackCount(0)
    , iEncodedStreamCount(0)
    , iDecodedStreamCount(0)
    , iEncodedAudioCount(0)
    , iDecodedAudioCount(0)
{
    ASSERT(iEncodedBytes.is_lock_free());
    ASSERT(iJiffies.is_lock_free());
    ASSERT(iTrackCount.is_lock_free());
    ASSERT(iEncodedStreamCount.is_lock_free());
    ASSERT(iDecodedStreamCount.is_lock_free());
    ASSERT(iEncodedAudioCount.is_lock_free());
    ASSERT(iDecodedAudioCount.is_lock_free());
}

MsgReservoir::~MsgReservoir()
{
}

void MsgReservoir::DoEnqueue(Msg* aMsg)
{
    ASSERT(aMsg != nullptr);
    ProcessorQueueIn procIn(*this);
    Msg* msg = aMsg->Process(procIn);
    iQueue.Enqueue(msg);
}

Msg* MsgReservoir::DoDequeue(TBool aAllowNull)
{
    Msg* msg;
    do {
        msg = iQueue.Dequeue();
        ProcessorQueueOut procOut(*this);
        msg = msg->Process(procOut);
    } while (!aAllowNull && msg == nullptr);
    return msg;
}

void MsgReservoir::EnqueueAtHead(Msg* aMsg)
{
    ProcessorEnqueue proc(*this);
    Msg* msg = aMsg->Process(proc);
    iQueue.EnqueueAtHead(msg);
}

TUint MsgReservoir::Jiffies() const
{
    return iJiffies;
}

TUint MsgReservoir::EncodedBytes() const
{
    return iEncodedBytes;
}

TBool MsgReservoir::IsEmpty() const
{
    return iQueue.IsEmpty();
}

TUint MsgReservoir::TrackCount() const
{
    return iTrackCount;
}

TUint MsgReservoir::EncodedStreamCount() const
{
    return iEncodedStreamCount;
}

TUint MsgReservoir::DecodedStreamCount() const
{
    return iDecodedStreamCount;
}

TUint MsgReservoir::EncodedAudioCount() const
{
    return iEncodedAudioCount;
}

TUint MsgReservoir::DecodedAudioCount() const
{
    return iDecodedAudioCount;
}

void MsgReservoir::ProcessMsgIn(MsgMode* /*aMsg*/)              { }
void MsgReservoir::ProcessMsgIn(MsgTrack* /*aMsg*/)             { }
void MsgReservoir::ProcessMsgIn(MsgDrain* /*aMsg*/)             { }
void MsgReservoir::ProcessMsgIn(MsgDelay* /*aMsg*/)             { }
void MsgReservoir::ProcessMsgIn(MsgEncodedStream* /*aMsg*/)     { }
void MsgReservoir::ProcessMsgIn(MsgAudioEncoded* /*aMsg*/)      { }
void MsgReservoir::ProcessMsgIn(MsgMetaText* /*aMsg*/)          { }
void MsgReservoir::ProcessMsgIn(MsgStreamInterrupted* /*aMsg*/) { }
void MsgReservoir::ProcessMsgIn(MsgHalt* /*aMsg*/)              { }
void MsgReservoir::ProcessMsgIn(MsgFlush* /*aMsg*/)             { }
void MsgReservoir::ProcessMsgIn(MsgWait* /*aMsg*/)              { }
void MsgReservoir::ProcessMsgIn(MsgDecodedStream* /*aMsg*/)     { }
void MsgReservoir::ProcessMsgIn(MsgBitRate* /*aMsg*/)           { }
void MsgReservoir::ProcessMsgIn(MsgAudioPcm* /*aMsg*/)          { }
void MsgReservoir::ProcessMsgIn(MsgSilence* /*aMsg*/)           { }
void MsgReservoir::ProcessMsgIn(MsgQuit* /*aMsg*/)              { }

Msg* MsgReservoir::ProcessMsgOut(MsgMode* aMsg)                 { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgTrack* aMsg)                { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgDrain* aMsg)                { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgDelay* aMsg)                { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgEncodedStream* aMsg)        { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgAudioEncoded* aMsg)         { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgMetaText* aMsg)             { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgStreamInterrupted* aMsg)    { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgHalt* aMsg)                 { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgFlush* aMsg)                { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgWait* aMsg)                 { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgDecodedStream* aMsg)        { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgBitRate* aMsg)              { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgAudioPcm* aMsg)             { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgSilence* aMsg)              { return aMsg; }
Msg* MsgReservoir::ProcessMsgOut(MsgQuit* aMsg)                 { return aMsg; }


// MsgReservoir::ProcessorEnqueue

MsgReservoir::ProcessorEnqueue::ProcessorEnqueue(MsgReservoir& aQueue)
    : iQueue(aQueue)
{
}

Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgMode* aMsg)               { return aMsg; }

Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgTrack* aMsg)
{
    iQueue.iTrackCount++;
    return aMsg;
}

Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgDrain* aMsg)              { return aMsg; }
Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgDelay* aMsg)              { return aMsg; }

Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgEncodedStream* aMsg)
{
    iQueue.iEncodedStreamCount++;
    return aMsg;
}

Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iQueue.iEncodedAudioCount++;
    iQueue.iEncodedBytes += aMsg->Bytes();
    return aMsg;
}

Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgMetaText* aMsg)           { return aMsg; }
Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgStreamInterrupted* aMsg)  { return aMsg; }
Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgHalt* aMsg)               { return aMsg; }
Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgFlush* aMsg)              { return aMsg; }
Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgWait* aMsg)               { return aMsg; }

Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgDecodedStream* aMsg)
{
    iQueue.iDecodedStreamCount++;
    return aMsg;
}

Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgBitRate* aMsg)            { return aMsg; }

Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgAudioPcm* aMsg)
{
    iQueue.iDecodedAudioCount++;
    iQueue.iJiffies += aMsg->Jiffies();
    return aMsg;
}

Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgSilence* aMsg)
{
    iQueue.iDecodedAudioCount++;
    iQueue.iJiffies += aMsg->Jiffies();
    return aMsg;
}

Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* MsgReservoir::ProcessorEnqueue::ProcessMsg(MsgQuit* aMsg)               { return aMsg; }


// MsgReservoir::ProcessorQueueIn

MsgReservoir::ProcessorQueueIn::ProcessorQueueIn(MsgReservoir& aQueue)
    : ProcessorEnqueue(aQueue)
{
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgMode* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgTrack* aMsg)
{
    (void)ProcessorEnqueue::ProcessMsg(aMsg);
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgDrain* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgDelay* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgEncodedStream* aMsg)
{
    (void)ProcessorEnqueue::ProcessMsg(aMsg);
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgAudioEncoded* aMsg)
{
    (void)ProcessorEnqueue::ProcessMsg(aMsg);
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgMetaText* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgHalt* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgFlush* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgWait* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgDecodedStream* aMsg)
{
    (void)ProcessorEnqueue::ProcessMsg(aMsg);
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgBitRate* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgAudioPcm* aMsg)
{
    (void)ProcessorEnqueue::ProcessMsg(aMsg);
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgSilence* aMsg)
{
    (void)ProcessorEnqueue::ProcessMsg(aMsg);
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgQuit* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}


// MsgReservoir::ProcessorQueueOut

MsgReservoir::ProcessorQueueOut::ProcessorQueueOut(MsgReservoir& aQueue)
    : iQueue(aQueue)
{
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgMode* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgTrack* aMsg)
{
    iQueue.iTrackCount--;
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgDrain* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgDelay* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgEncodedStream* aMsg)
{
    iQueue.iEncodedStreamCount--;
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iQueue.iEncodedAudioCount--;
    iQueue.iEncodedBytes -= aMsg->Bytes();
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgMetaText* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgHalt* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgFlush* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgWait* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgDecodedStream* aMsg)
{
    iQueue.iDecodedStreamCount--;
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgBitRate* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgAudioPcm* aMsg)
{
    iQueue.iDecodedAudioCount--;
    iQueue.iJiffies -= aMsg->Jiffies();
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgSilence* aMsg)
{
    iQueue.iDecodedAudioCount--;
    iQueue.iJiffies -= aMsg->Jiffies();
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgQuit* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}


// PipelineElement

PipelineElement::PipelineElement(TUint aSupportedTypes)
    : iSupportedTypes(aSupportedTypes)
{
}

PipelineElement::~PipelineElement()
{
}

inline void PipelineElement::CheckSupported(MsgType aType) const
{
    ASSERT((iSupportedTypes & aType) == (TUint)aType);
}

Msg* PipelineElement::ProcessMsg(MsgMode* aMsg)
{
    CheckSupported(eMode);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgTrack* aMsg)
{
    CheckSupported(eTrack);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgDrain* aMsg)
{
    CheckSupported(eDrain);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgDelay* aMsg)
{
    CheckSupported(eDelay);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgEncodedStream* aMsg)
{
    CheckSupported(eEncodedStream);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgAudioEncoded* aMsg)
{
    CheckSupported(eAudioEncoded);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgMetaText* aMsg)
{
    CheckSupported(eMetatext);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    CheckSupported(eStreamInterrupted);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgHalt* aMsg)
{
    CheckSupported(eHalt);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgFlush* aMsg)
{
    CheckSupported(eFlush);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgWait* aMsg)
{
    CheckSupported(eWait);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgDecodedStream* aMsg)
{
    CheckSupported(eDecodedStream);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgBitRate* aMsg)
{
    CheckSupported(eBitRate);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgAudioPcm* aMsg)
{
    CheckSupported(eAudioPcm);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgSilence* aMsg)
{
    CheckSupported(eSilence);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgPlayable* aMsg)
{
    CheckSupported(ePlayable);
    return aMsg;
}

Msg* PipelineElement::ProcessMsg(MsgQuit* aMsg)
{
    CheckSupported(eQuit);
    return aMsg;
}


// AutoAllocatedRef

AutoAllocatedRef::AutoAllocatedRef(Allocated* aAllocated)
    : iAllocated(aAllocated)
{
}

AutoAllocatedRef::~AutoAllocatedRef()
{
    iAllocated->RemoveRef();
}


// TrackFactory

TrackFactory::TrackFactory(IInfoAggregator& aInfoAggregator, TUint aTrackCount)
    : iAllocatorTrack("Track", aTrackCount, aInfoAggregator)
    , iLock("TRKF")
    , iNextId(1)
{
}

Track* TrackFactory::CreateTrack(const Brx& aUri, const Brx& aMetaData)
{
    Track* track = iAllocatorTrack.Allocate();
    iLock.Wait();
    TUint id = iNextId++;
    iLock.Signal();
    track->Initialise(aUri, aMetaData, id);
    return track;
}


// MsgFactory

MsgFactory::MsgFactory(IInfoAggregator& aInfoAggregator, const MsgFactoryInitParams& aInitParams)
    : iAllocatorMsgMode("MsgMode", aInitParams.iMsgModeCount, aInfoAggregator)
    , iAllocatorMsgTrack("MsgTrack", aInitParams.iMsgTrackCount, aInfoAggregator)
    , iAllocatorMsgDrain("MsgDrain", aInitParams.iMsgDrainCount, aInfoAggregator)
    , iDrainId(0)
    , iAllocatorMsgDelay("MsgDelay", aInitParams.iMsgDelayCount, aInfoAggregator)
    , iAllocatorMsgEncodedStream("MsgEncodedStream", aInitParams.iMsgEncodedStreamCount, aInfoAggregator)
    , iAllocatorAudioData("AudioData", aInitParams.iEncodedAudioCount + aInitParams.iDecodedAudioCount, aInfoAggregator)
    , iAllocatorMsgAudioEncoded("MsgAudioEncoded", aInitParams.iMsgAudioEncodedCount, aInfoAggregator)
    , iAllocatorMsgMetaText("MsgMetaText", aInitParams.iMsgMetaTextCount, aInfoAggregator)
    , iAllocatorMsgStreamInterrupted("MsgStreamInterrupted", aInitParams.iMsgStreamInterruptedCount, aInfoAggregator)
    , iAllocatorMsgHalt("MsgHalt", aInitParams.iMsgHaltCount, aInfoAggregator)
    , iAllocatorMsgFlush("MsgFlush", aInitParams.iMsgFlushCount, aInfoAggregator)
    , iAllocatorMsgWait("MsgWait", aInitParams.iMsgWaitCount, aInfoAggregator)
    , iAllocatorMsgDecodedStream("MsgDecodedStream", aInitParams.iMsgDecodedStreamCount, aInfoAggregator)
    , iAllocatorMsgBitRate("MsgBitRate", aInitParams.iMsgBitRateCount, aInfoAggregator)
    , iAllocatorMsgAudioPcm("MsgAudioPcm", aInitParams.iMsgAudioPcmCount, aInfoAggregator)
    , iAllocatorMsgSilence("MsgSilence", aInitParams.iMsgSilenceCount, aInfoAggregator)
    , iAllocatorMsgPlayablePcm("MsgPlayablePcm", aInitParams.iMsgPlayablePcmCount, aInfoAggregator)
    , iAllocatorMsgPlayableSilence("MsgPlayableSilence", aInitParams.iMsgPlayableSilenceCount, aInfoAggregator)
    , iAllocatorMsgQuit("MsgQuit", aInitParams.iMsgQuitCount, aInfoAggregator)
{
}

MsgMode* MsgFactory::CreateMsgMode(const Brx& aMode, TBool aSupportsLatency, ModeClockPullers aClockPullers, TBool aSupportsNext, TBool aSupportsPrev)
{
    MsgMode* msg = iAllocatorMsgMode.Allocate();
    msg->Initialise(aMode, aSupportsLatency, aClockPullers, aSupportsNext, aSupportsPrev);
    return msg;
}

MsgTrack* MsgFactory::CreateMsgTrack(Media::Track& aTrack, TBool aStartOfStream)
{
    MsgTrack* msg = iAllocatorMsgTrack.Allocate();
    msg->Initialise(aTrack, aStartOfStream);
    return msg;
}

MsgDrain* MsgFactory::CreateMsgDrain(Functor aCallback)
{
    MsgDrain* msg = iAllocatorMsgDrain.Allocate();
    msg->Initialise(iDrainId++, aCallback);
    return msg;
}

MsgDelay* MsgFactory::CreateMsgDelay(TUint aDelayJiffies)
{
    MsgDelay* msg = iAllocatorMsgDelay.Allocate();
    msg->Initialise(aDelayJiffies);
    return msg;
}

MsgEncodedStream* MsgFactory::CreateMsgEncodedStream(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint64 aStartPos, TUint aStreamId, TBool aSeekable, TBool aLive, Media::Multiroom aMultiroom, IStreamHandler* aStreamHandler)
{
    MsgEncodedStream* msg = iAllocatorMsgEncodedStream.Allocate();
    msg->Initialise(aUri, aMetaText, aTotalBytes, aStartPos, aStreamId, aSeekable, aLive, aMultiroom, aStreamHandler);
    return msg;
}

MsgEncodedStream* MsgFactory::CreateMsgEncodedStream(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint64 aStartPos, TUint aStreamId, TBool aSeekable, TBool aLive, Media::Multiroom aMultiroom, IStreamHandler* aStreamHandler, const PcmStreamInfo& aPcmStream)
{
    MsgEncodedStream* msg = iAllocatorMsgEncodedStream.Allocate();
    msg->Initialise(aUri, aMetaText, aTotalBytes, aStartPos, aStreamId, aSeekable, aLive, aMultiroom, aStreamHandler, aPcmStream);
    return msg;
}

MsgEncodedStream* MsgFactory::CreateMsgEncodedStream(MsgEncodedStream* aMsg, IStreamHandler* aStreamHandler)
{
    MsgEncodedStream* msg = iAllocatorMsgEncodedStream.Allocate();
    if (aMsg->RawPcm()) {
        msg->Initialise(aMsg->Uri(), aMsg->MetaText(), aMsg->TotalBytes(), aMsg->StartPos(), aMsg->StreamId(), aMsg->Seekable(), aMsg->Live(), aMsg->Multiroom(), aStreamHandler, aMsg->PcmStream());
    }
    else {
        msg->Initialise(aMsg->Uri(), aMsg->MetaText(), aMsg->TotalBytes(), aMsg->StartPos(), aMsg->StreamId(), aMsg->Seekable(), aMsg->Live(), aMsg->Multiroom(), aStreamHandler);
    }
    return msg;
}

MsgAudioEncoded* MsgFactory::CreateMsgAudioEncoded(const Brx& aData)
{
    EncodedAudio* encodedAudio = CreateEncodedAudio(aData);
    MsgAudioEncoded* msg = iAllocatorMsgAudioEncoded.Allocate();
    msg->Initialise(encodedAudio);
    return msg;
}

MsgMetaText* MsgFactory::CreateMsgMetaText(const Brx& aMetaText)
{
    MsgMetaText* msg = iAllocatorMsgMetaText.Allocate();
    msg->Initialise(aMetaText);
    return msg;
}

MsgStreamInterrupted* MsgFactory::CreateMsgStreamInterrupted()
{
    return iAllocatorMsgStreamInterrupted.Allocate();
}

MsgHalt* MsgFactory::CreateMsgHalt(TUint aId)
{
    MsgHalt* msg = iAllocatorMsgHalt.Allocate();
    msg->Initialise(aId);
    return msg;
}

MsgHalt* MsgFactory::CreateMsgHalt(TUint aId, Functor aCallback)
{
    MsgHalt* msg = iAllocatorMsgHalt.Allocate();
    msg->Initialise(aId, aCallback);
    return msg;
}

MsgFlush* MsgFactory::CreateMsgFlush(TUint aId)
{
    MsgFlush* flush = iAllocatorMsgFlush.Allocate();
    flush->Initialise(aId);
    return flush;
}

MsgWait* MsgFactory::CreateMsgWait()
{
    return iAllocatorMsgWait.Allocate();
}

MsgDecodedStream* MsgFactory::CreateMsgDecodedStream(TUint aStreamId, TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless, TBool aSeekable, TBool aLive, TBool aAnalogBypass, Media::Multiroom aMultiroom, const SpeakerProfile& aProfile, IStreamHandler* aStreamHandler)
{
    MsgDecodedStream* msg = iAllocatorMsgDecodedStream.Allocate();
    msg->Initialise(aStreamId, aBitRate, aBitDepth, aSampleRate, aNumChannels, aCodecName, aTrackLength, aSampleStart, aLossless, aSeekable, aLive, aAnalogBypass, aMultiroom, aProfile, aStreamHandler);
    return msg;
}

MsgDecodedStream* MsgFactory::CreateMsgDecodedStream(MsgDecodedStream* aMsg, IStreamHandler* aStreamHandler)
{
    auto stream = aMsg->StreamInfo();
    auto msg = CreateMsgDecodedStream(stream.StreamId(), stream.BitRate(), stream.BitDepth(),
        stream.SampleRate(), stream.NumChannels(), stream.CodecName(),
        stream.TrackLength(), stream.SampleStart(), stream.Lossless(),
        stream.Seekable(), stream.Live(), stream.AnalogBypass(),
        stream.Multiroom(), stream.Profile(), aStreamHandler);
    return msg;
}

MsgBitRate* MsgFactory::CreateMsgBitRate(TUint aBitRate)
{
    auto msg = iAllocatorMsgBitRate.Allocate();
    msg->Initialise(aBitRate);
    return msg;
}

MsgAudioPcm* MsgFactory::CreateMsgAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, AudioDataEndian aEndian, TUint64 aTrackOffset)
{
    DecodedAudio* decodedAudio = CreateDecodedAudio(aData, aBitDepth, aEndian);
    return CreateMsgAudioPcm(decodedAudio, aChannels, aSampleRate, aBitDepth, aTrackOffset);
}

MsgAudioPcm* MsgFactory::CreateMsgAudioPcm(MsgAudioEncoded* aAudio, TUint aChannels, TUint aSampleRate, TUint aBitDepth, TUint64 aTrackOffset)
{
    AudioData* audioData = aAudio->iAudioData;
    audioData->AddRef();
    return CreateMsgAudioPcm(static_cast<DecodedAudio*>(audioData),
                             aChannels, aSampleRate, aBitDepth, aTrackOffset);
}

MsgSilence* MsgFactory::CreateMsgSilence(TUint& aSizeJiffies, TUint aSampleRate, TUint aBitDepth, TUint aChannels)
{
    MsgSilence* msg = iAllocatorMsgSilence.Allocate();
    msg->Initialise(aSizeJiffies, aSampleRate, aBitDepth, aChannels, iAllocatorMsgPlayableSilence);
    return msg;
}

MsgQuit* MsgFactory::CreateMsgQuit()
{
    return iAllocatorMsgQuit.Allocate();
}

EncodedAudio* MsgFactory::CreateEncodedAudio(const Brx& aData)
{
    EncodedAudio* encodedAudio = static_cast<EncodedAudio*>(iAllocatorAudioData.Allocate());
    encodedAudio->Construct(aData);
    return encodedAudio;
}

DecodedAudio* MsgFactory::CreateDecodedAudio(const Brx& aData, TUint aBitDepth, AudioDataEndian aEndian)
{
    DecodedAudio* decodedAudio = static_cast<DecodedAudio*>(iAllocatorAudioData.Allocate());
    decodedAudio->Construct(aData, aBitDepth, aEndian);
    return decodedAudio;
}

MsgAudioPcm* MsgFactory::CreateMsgAudioPcm(DecodedAudio* aAudioData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, TUint64 aTrackOffset)
{
    MsgAudioPcm* msg = iAllocatorMsgAudioPcm.Allocate();
    try {
        msg->Initialise(aAudioData, aSampleRate, aBitDepth, aChannels, aTrackOffset,
                        iAllocatorMsgPlayablePcm, iAllocatorMsgPlayableSilence);
    }
    catch (AssertionFailed&) { // test code helper
        msg->RemoveRef();
        throw;
    }
    return msg;
}
