#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/RampArray.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Printer.h>

#include <string.h>
#include <climits>
#include <algorithm>

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
        Allocated* ptr = Read();
        //Log::Print("(%p)", ptr);
        delete ptr;
    }
    //Log::Print("\n");
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
    Allocated* p = NULL;
    try {
        p = iFree.Read();
    }
    catch (FifoReadError&) {
        Log::Print("Allocator error for %s\n", iName);
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
    iLock.Wait();
    iRefCount++;
    iLock.Signal();
    RefAdded();
}

void Allocated::RemoveRef()
{
    ASSERT_DEBUG(iRefCount != 0);
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
    , iRefCount(0)
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

TBool Jiffies::IsValidSampleRate(TUint aSampleRate)
{ // static
    try {
        JiffiesPerSample(aSampleRate); // only want to check if sample rate is supported
    }
    catch (MsgInvalidSampleRate) {
        return false;
    }
    return true;
}

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
        THROW(MsgInvalidSampleRate);
    }
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

void DecodedAudio::Aggregate(DecodedAudio& aDecodedAudio)
{
    ASSERT(Bytes()+aDecodedAudio.Bytes() <= kMaxBytes);
    ASSERT(aDecodedAudio.iChannels == iChannels);
    ASSERT(aDecodedAudio.iSampleRate == iSampleRate);
    ASSERT(aDecodedAudio.iBitDepth == iBitDepth);
    ASSERT(aDecodedAudio.iByteDepth == iByteDepth);
    ASSERT(aDecodedAudio.iJiffiesPerSample == iJiffiesPerSample);

    memcpy(&iData[iSubsampleCount*iByteDepth], aDecodedAudio.iData, aDecodedAudio.Bytes());
    iSubsampleCount += aDecodedAudio.Bytes() / iByteDepth;
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
    /*Log::Print("Ramp::Set (");
    Log::Print(Thread::CurrentThreadName());
    Log::Print("), aDirection=%d, aStart=%08x, aFragmentSize=%08x, aRemainingDuration=%08x\n", aDirection, aStart, aFragmentSize, aRemainingDuration);*/
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
            if (intersectX <= 0 || (TUint)intersectX >= aFragmentSize) {
                // ramp lines don't intersect inside this Msg
                SelectLowerRampPoints(aStart, rampEnd);
            }
            else {
                // split this Ramp; the first portion rises to the intersection of the two ramps, the second drops to the lower final value
                aSplitPos = intersectX;
                aSplit.iStart = intersectY;
                aSplit.iEnd = std::min(iEnd, rampEnd);
                aSplit.iDirection = (aSplit.iStart == aSplit.iEnd? ENone : EDown);
                aSplit.iEnabled = true;
                iStart = std::min(iStart, aStart);
                iEnd = intersectY;
                iDirection = (iStart == iEnd? ENone : EUp);
            }
        }
    }
    Validate();
    return aSplit.IsEnabled();
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

void Ramp::Validate()
{
    ASSERT(iStart <= kMax);
    ASSERT(iEnd <= kMax);
    switch (iDirection)
    {
    case ENone:
        ASSERT(iStart == iEnd);
        break;
    case EUp:
        ASSERT(iStart < iEnd);
        break;
    case EDown:
        ASSERT(iStart > iEnd);
        break;
    default:
        ASSERTS();
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
    if (iStart == iEnd) {
        iDirection = ENone;
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
    iFullRampSpan = Ramp::kMax - Ramp::kMin;
    iLoopCount = 0;
    return iNumSamples;
}

void RampApplicator::GetNextSample(TByte* aDest)
{
    ASSERT_DEBUG(iPtr != NULL);
    const TUint ramp = (iNumSamples==1? iRamp.Start() : (TUint)(iRamp.Start() - ((iLoopCount * (TInt64)iTotalRamp)/(iNumSamples-1))));
    //Log::Print(" %08x ", ramp);
    const TUint rampIndex = (iFullRampSpan - ramp + (1<<20)) >> 21; // assumes fullRampSpan==2^31 and kRampArray has 512 items. (1<<20 allows rounding up)
    for (TUint i=0; i<iNumChannels; i++) {
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
        //Log::Print("Original=%08x (%d), ramped=%08x (%d), rampIndex=%u\n", subsample, subsample, rampedSubsample, rampedSubsample, rampIndex);

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

    
// MsgMode

MsgMode::MsgMode(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

const Brx& MsgMode::Mode() const
{
    return iMode;
}

TBool MsgMode::SupportsLatency() const
{
    return iSupportsLatency;
}

TBool MsgMode::IsRealTime() const
{
    return iIsRealTime;
}

IClockPuller* MsgMode::ClockPuller() const
{
    return iClockPuller;
}

void MsgMode::Initialise(const Brx& aMode, TBool aSupportsLatency, TBool aIsRealTime, IClockPuller* aClockPuller)
{
    iMode.Replace(aMode);
    iSupportsLatency = aSupportsLatency;
    iIsRealTime = aIsRealTime;
    iClockPuller = aClockPuller;
}

void MsgMode::Clear()
{
    iMode.Replace(Brx::Empty());
    iSupportsLatency = iIsRealTime = false;
    iClockPuller = NULL;
}

Msg* MsgMode::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// MsgSession

MsgSession::MsgSession(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

Msg* MsgSession::Process(IMsgProcessor& aProcessor)
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
    ASSERT(iTrack != NULL);
    return *iTrack;
}

TUint MsgTrack::IdPipeline() const
{
    return iIdPipeline;
}

void MsgTrack::Initialise(Media::Track& aTrack, TUint aIdPipeline)
{
    iTrack = &aTrack;
    iTrack->AddRef();
    iIdPipeline = aIdPipeline;}

void MsgTrack::Clear()
{
    iTrack->RemoveRef();
    iTrack = NULL;
    iIdPipeline = UINT_MAX;
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
    if (aBytes == iSize) {
        ASSERT(iNextAudio != NULL);
        MsgAudioEncoded* next = iNextAudio;
        iNextAudio = NULL;
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

MsgAudioEncoded* MsgAudioEncoded::Clone()
{
    MsgAudioEncoded* clone = static_cast<Allocator<MsgAudioEncoded>&>(iAllocator).Allocate();
    AutoMutex a(iLock);
    clone->iNextAudio = NULL;
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
    iNextAudio = NULL;
}

void MsgAudioEncoded::RefAdded()
{
    /* FIXME - not clear that its correct to Add/Remove refs down a chain like this
       it might be better to modify the head msg only then RemoveRef down the chain when
       the head is Clear()ed */
    if (iNextAudio != NULL) {
        iNextAudio->AddRef();
    }
}

void MsgAudioEncoded::RefRemoved()
{
    if (iNextAudio != NULL) {
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


// MsgHalt

MsgHalt::MsgHalt(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

TUint MsgHalt::Id() const
{
    return iId;
}

void MsgHalt::Initialise(TUint aId)
{
    iId = aId;
}

void MsgHalt::Clear()
{
    iId = UINT_MAX;
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
    , iStreamHandler(NULL)
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


// MsgAudio

MsgAudio* MsgAudio::Split(TUint aJiffies)
{
    AutoMutex a(iLock);
    if (aJiffies > iSize && iNextAudio != NULL) {
        return iNextAudio->Split(aJiffies - iSize);
    }
    else if (aJiffies == iSize && iNextAudio != NULL) {
        MsgAudio* split = iNextAudio;
        iNextAudio = NULL;
        return split;
    }
    return DoSplit(aJiffies);
}

MsgAudio* MsgAudio::DoSplit(TUint aJiffies)
{
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

void MsgAudio::Add(MsgAudio* aMsg)
{
    iLock.Wait();
    MsgAudio* end = this;
    MsgAudio* next = iNextAudio;
    while (next != NULL) {
        end = next;
        next = next->iNextAudio;
    }
    end->iNextAudio = aMsg;
    iLock.Signal();
}

MsgAudio* MsgAudio::Clone()
{
    MsgAudio* clone = Allocate();
    AutoMutex a(iLock);
    clone->iSize = iSize;
    clone->iOffset = iOffset;
    clone->iRamp = iRamp;
    clone->iNextAudio = (iNextAudio == NULL? NULL : iNextAudio->Clone());
    return clone;
}

TUint MsgAudio::Jiffies() const
{
    iLock.Wait();
    TUint jiffies = iSize; 
    MsgAudio* next = iNextAudio; 
    while (next != NULL) { 
        jiffies += next->iSize; 
        next = next->iNextAudio; 
    }
    iLock.Signal();
    return jiffies;
}

TUint MsgAudio::SetRamp(TUint aStart, TUint& aRemainingDuration, Ramp::EDirection aDirection, MsgAudio*& aSplit)  // FIXME
{
    AutoMutex a(iLock);
    ASSERT(iNextAudio == NULL);
    const TUint remainingDuration = aRemainingDuration;
    Media::Ramp split;
    TUint splitPos;
    TUint rampEnd;
    aRemainingDuration -= iSize;
    aSplit = NULL;
    if (iRamp.Set(aStart, iSize, remainingDuration, aDirection, split, splitPos)) {
        if (splitPos == 0) {
            iRamp = split;
            rampEnd = iRamp.End();
        }
        else if (splitPos == iSize) {
            rampEnd = iRamp.End();
        }
        else {
            Media::Ramp ramp = iRamp; // Split() will muck about with ramps.  Allow this to happen then reset the correct values
            aSplit = DoSplit(splitPos);
            iRamp = ramp;
            aSplit->iRamp = split;
            rampEnd = split.End();
            ASSERT_DEBUG(iRamp.End() == split.Start());
            //Log::Print("\nSplit msg at %u jiffies.  First ramp=[%08x...%08x], second ramp=[%08x...%08x]\n",
            //            splitPos, iRamp.Start(), iRamp.End(), split.Start(), split.End());
        }
    }
    else {
        rampEnd = iRamp.End();
    }

    // It may be possible to terminate ramps down early if the msg had previously been ramped
    if (aDirection == Ramp::EDown && rampEnd == Ramp::kMin) {
        aRemainingDuration = 0;
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
    iSize = 0;
    if (iNextAudio != NULL) { 
        iNextAudio->RemoveRef(); 
        iNextAudio = NULL;
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
        iNextAudio = NULL;
    }
    RemoveRef();
    return playable;
}

void MsgAudioPcm::Aggregate(MsgAudioPcm& aMsg)
{
    ASSERT(aMsg.iTrackOffset == iTrackOffset+Jiffies());   // aMsg must logically follow this one
    ASSERT(!iRamp.IsEnabled() && !aMsg.iRamp.IsEnabled()); // no ramps allowed
    ASSERT(iNextAudio == NULL && aMsg.iNextAudio == NULL); // no chained msgs allowed

    iAudioData->Aggregate(*aMsg.iAudioData);
    iSize += aMsg.Jiffies();
    aMsg.RemoveRef();
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
    ASSERT(iSize > 0);
    iOffset = 0;
}

void MsgAudioPcm::SetTimestamps(TUint aRxTimestamp, TUint aLatency, TUint aNetworkTimestamp, TUint aMediaTimestamp)
{
    iReceiveTimestamp = aRxTimestamp;
    iMediaLatency = aLatency;
    iNetworkTimestamp = aNetworkTimestamp;
    iMediaTimestamp = aMediaTimestamp;
    iFlags = 0; // FIXME
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
    iFlags = 0xffffffff;
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

MsgAudio* MsgSilence::Clone()
{
    MsgAudio* clone = MsgAudio::Clone();
    static_cast<MsgSilence*>(clone)->iAllocatorPlayable = iAllocatorPlayable;
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


// MsgQuit

MsgQuit::MsgQuit(AllocatorBase& aAllocator)
    : Msg(aAllocator)
{
}

Msg* MsgQuit::Process(IMsgProcessor& aProcessor)
{
    return aProcessor.ProcessMsg(this);
}


// StreamId

StreamId::StreamId()
    : iTrackId(IPipelineIdProvider::kTrackIdInvalid)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
{
}

void StreamId::SetTrack(TUint aId)
{
    iTrackId = aId;
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
}

void StreamId::SetStream(TUint aId)
{
    ASSERT(iTrackId != IPipelineIdProvider::kTrackIdInvalid);
    iStreamId = aId;
}

TBool StreamId::operator ==(const StreamId& aId) const
{
    return (iTrackId == aId.iTrackId && iStreamId == aId.iStreamId);
}


// MsgQueue

MsgQueue::MsgQueue()
    : iLock("MSGQ")
    , iSem("MSGQ", 0)
    , iHead(NULL)
    , iTail(NULL)
    , iNumMsgs(0)
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
    AutoMutex a(iLock);
    CheckMsgNotQueued(aMsg); // duplicate checking
    if (iHead == NULL) {
        iHead = aMsg;
    }
    else {
        iTail->iNextMsg = aMsg;
    }
    iTail = aMsg;
    aMsg->iNextMsg = NULL;
    iNumMsgs++;
    iSem.Signal();
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
    iNumMsgs--;
    iLock.Signal();
    return head;
}

void MsgQueue::EnqueueAtHead(Msg* aMsg)
{
    ASSERT(aMsg != NULL);
    AutoMutex a(iLock);
    CheckMsgNotQueued(aMsg); // duplicate checking
    aMsg->iNextMsg = iHead;
    iHead = aMsg;
    if (iTail == NULL) {
        iTail = aMsg;
    }
    iNumMsgs++;
    iSem.Signal();
}

TBool MsgQueue::IsEmpty() const
{
    iLock.Wait();
    const TBool empty = (iHead == NULL);
    iLock.Signal();
    return empty;
}

TUint MsgQueue::NumMsgs() const
{
    AutoMutex a(iLock);
    return iNumMsgs;
}

void MsgQueue::CheckMsgNotQueued(Msg* aMsg) const
{
    // iLock must be held (using an AutoMutex)
    ASSERT(aMsg != iTail);
    ASSERT(aMsg != iHead);
#ifdef DEFINE_DEBUG // iterate over queue, comparing aMsg to all msg pointers
    TUint count = 0;
    for (Msg* msg = iHead; msg != NULL; msg = msg->iNextMsg) {
        ASSERT(aMsg != msg);
        count++;
    }
    if (count != iNumMsgs) {    // ensure a msg mid-queue hasn't had iNextMsg
                                // modified elsewhere
        ASSERTS();
    }
#endif
}


// MsgReservoir

MsgReservoir::MsgReservoir()
    : iLock("MQJF")
    , iEncodedBytes(0)
    , iJiffies(0)
    , iEncodedStreamCount(0)
    , iDecodedStreamCount(0)
{
}

MsgReservoir::~MsgReservoir()
{
}

void MsgReservoir::DoEnqueue(Msg* aMsg)
{
    ProcessorQueueIn procIn(*this);
    Msg* msg = aMsg->Process(procIn);
    iQueue.Enqueue(msg);
}

Msg* MsgReservoir::DoDequeue()
{
    Msg* msg;
    do {
        msg = iQueue.Dequeue();
        ProcessorQueueOut procOut(*this);
        msg = msg->Process(procOut);
    } while (msg == NULL);
    return msg;
}

void MsgReservoir::EnqueueAtHead(Msg* aMsg)
{
    ProcessorQueueIn procIn(*this);
    Msg* msg = aMsg->Process(procIn);
    iQueue.EnqueueAtHead(msg);
}

TUint MsgReservoir::Jiffies() const
{
    AutoMutex a(iLock);
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

TUint MsgReservoir::EncodedStreamCount() const
{
    AutoMutex a(iLock);
    return iEncodedStreamCount;
}

TUint MsgReservoir::DecodedStreamCount() const
{
    AutoMutex a(iLock);
    return iDecodedStreamCount;
}

void MsgReservoir::Add(TUint& aValue, TUint aAdded)
{
    iLock.Wait();
    aValue += aAdded;
    iLock.Signal();
}

void MsgReservoir::Remove(TUint& aValue, TUint aRemoved)
{
    iLock.Wait();
    ASSERT(aValue >= aRemoved);
    aValue -= aRemoved;
    iLock.Signal();
}

void MsgReservoir::ProcessMsgIn(MsgMode* /*aMsg*/)
{
}

void MsgReservoir::ProcessMsgIn(MsgSession* /*aMsg*/)
{
}

void MsgReservoir::ProcessMsgIn(MsgTrack* /*aMsg*/)
{
}

void MsgReservoir::ProcessMsgIn(MsgDelay* /*aMsg*/)
{
}

void MsgReservoir::ProcessMsgIn(MsgEncodedStream* /*aMsg*/)
{
}

void MsgReservoir::ProcessMsgIn(MsgAudioEncoded* /*aMsg*/)
{
}

void MsgReservoir::ProcessMsgIn(MsgMetaText* /*aMsg*/)
{
}

void MsgReservoir::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
}

void MsgReservoir::ProcessMsgIn(MsgFlush* /*aMsg*/)
{
}

void MsgReservoir::ProcessMsgIn(MsgWait* /*aMsg*/)
{
}

void MsgReservoir::ProcessMsgIn(MsgDecodedStream* /*aMsg*/)
{
}

void MsgReservoir::ProcessMsgIn(MsgAudioPcm* /*aMsg*/)
{
}

void MsgReservoir::ProcessMsgIn(MsgSilence* /*aMsg*/)
{
}

void MsgReservoir::ProcessMsgIn(MsgQuit* /*aMsg*/)
{
}

Msg* MsgReservoir::ProcessMsgOut(MsgMode* aMsg)
{
    return aMsg;
}

Msg* MsgReservoir::ProcessMsgOut(MsgSession* aMsg)
{
    return aMsg;
}

Msg* MsgReservoir::ProcessMsgOut(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* MsgReservoir::ProcessMsgOut(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* MsgReservoir::ProcessMsgOut(MsgEncodedStream* aMsg)
{
    return aMsg;
}

Msg* MsgReservoir::ProcessMsgOut(MsgAudioEncoded* aMsg)
{
    return aMsg;
}

Msg* MsgReservoir::ProcessMsgOut(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* MsgReservoir::ProcessMsgOut(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* MsgReservoir::ProcessMsgOut(MsgFlush* aMsg)
{
    return aMsg;
}

Msg* MsgReservoir::ProcessMsgOut(MsgWait* aMsg)
{
    return aMsg;
}

Msg* MsgReservoir::ProcessMsgOut(MsgDecodedStream* aMsg)
{
    return aMsg;
}

Msg* MsgReservoir::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    return aMsg;
}

Msg* MsgReservoir::ProcessMsgOut(MsgSilence* aMsg)
{
    return aMsg;
}

Msg* MsgReservoir::ProcessMsgOut(MsgQuit* aMsg)
{
    return aMsg;
}


// MsgReservoir::ProcessorQueueIn

MsgReservoir::ProcessorQueueIn::ProcessorQueueIn(MsgReservoir& aQueue)
    : iQueue(aQueue)
{
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgMode* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgSession* aMsg)
{
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgTrack* aMsg)
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
    iQueue.iLock.Wait();
    iQueue.iEncodedStreamCount++;
    iQueue.iLock.Signal();
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iQueue.Add(iQueue.iEncodedBytes, aMsg->Bytes());
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgMetaText* aMsg)
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
    iQueue.iLock.Wait();
    iQueue.iDecodedStreamCount++;
    iQueue.iLock.Signal();
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgAudioPcm* aMsg)
{
    iQueue.Add(iQueue.iJiffies, aMsg->Jiffies());
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgSilence* aMsg)
{
    iQueue.Add(iQueue.iJiffies, aMsg->Jiffies());
    iQueue.ProcessMsgIn(aMsg);
    return aMsg;
}

Msg* MsgReservoir::ProcessorQueueIn::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
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

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgSession* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgTrack* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgDelay* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgEncodedStream* aMsg)
{
    iQueue.iLock.Wait();
    iQueue.iEncodedStreamCount--;
    iQueue.iLock.Signal();
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iQueue.Remove(iQueue.iEncodedBytes, aMsg->Bytes());
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgMetaText* aMsg)
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
    iQueue.iLock.Wait();
    iQueue.iDecodedStreamCount--;
    iQueue.iLock.Signal();
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgAudioPcm* aMsg)
{
    iQueue.Remove(iQueue.iJiffies, aMsg->Jiffies());
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgSilence* aMsg)
{
    iQueue.Remove(iQueue.iJiffies, aMsg->Jiffies());
    return iQueue.ProcessMsgOut(aMsg);
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* MsgReservoir::ProcessorQueueOut::ProcessMsg(MsgQuit* aMsg)
{
    return iQueue.ProcessMsgOut(aMsg);
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

MsgFactory::MsgFactory(IInfoAggregator& aInfoAggregator,
                       TUint aEncodedAudioCount, TUint aMsgAudioEncodedCount, 
                       TUint aDecodedAudioCount, TUint aMsgAudioPcmCount, TUint aMsgSilenceCount,
                       TUint aMsgPlayablePcmCount, TUint aMsgPlayableSilenceCount, TUint aMsgDecodedStreamCount,
                       TUint aMsgTrackCount, TUint aMsgEncodedStreamCount, TUint aMsgMetaTextCount,
                       TUint aMsgHaltCount, TUint aMsgFlushCount, TUint aMsgWaitCount,
                       TUint aMsgModeCount, TUint aMsgSessionCount, TUint aMsgDelayCount, TUint aMsgQuitCount)
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
    , iAllocatorMsgWait("MsgWait", aMsgWaitCount, aInfoAggregator)
    , iAllocatorMsgMode("MsgMode", aMsgModeCount, aInfoAggregator)
    , iAllocatorMsgSession("MsgSession", aMsgSessionCount, aInfoAggregator)
    , iAllocatorMsgDelay("MsgDelay", aMsgDelayCount, aInfoAggregator)
    , iAllocatorMsgQuit("MsgQuit", aMsgQuitCount, aInfoAggregator)
{
    iNextFlushId = MsgFlush::kIdInvalid + 1;
}

MsgMode* MsgFactory::CreateMsgMode(const Brx& aMode, TBool aSupportsLatency, TBool aRealTime, IClockPuller* aClockPuller)
{
    MsgMode* msg = iAllocatorMsgMode.Allocate();
    msg->Initialise(aMode, aSupportsLatency, aRealTime, aClockPuller);
    return msg;
}

MsgSession* MsgFactory::CreateMsgSession()
{
    return iAllocatorMsgSession.Allocate();
}

MsgTrack* MsgFactory::CreateMsgTrack(Media::Track& aTrack, TUint aIdPipeline)
{
    MsgTrack* msg = iAllocatorMsgTrack.Allocate();
    msg->Initialise(aTrack, aIdPipeline);
    return msg;
}

MsgDelay* MsgFactory::CreateMsgDelay(TUint aDelayJiffies)
{
    MsgDelay* msg = iAllocatorMsgDelay.Allocate();
    msg->Initialise(aDelayJiffies);
    return msg;
}

MsgEncodedStream* MsgFactory::CreateMsgEncodedStream(const Brx& aUri, const Brx& aMetaText, TUint64 aTotalBytes, TUint aStreamId, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler)
{
    MsgEncodedStream* msg = iAllocatorMsgEncodedStream.Allocate();
    msg->Initialise(aUri, aMetaText, aTotalBytes, aStreamId, aSeekable, aLive, aStreamHandler);
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

MsgHalt* MsgFactory::CreateMsgHalt(TUint aId)
{
    MsgHalt* msg = iAllocatorMsgHalt.Allocate();
    msg->Initialise(aId);
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

MsgDecodedStream* MsgFactory::CreateMsgDecodedStream(TUint aStreamId, TUint aBitRate, TUint aBitDepth, TUint aSampleRate, TUint aNumChannels, const Brx& aCodecName, TUint64 aTrackLength, TUint64 aSampleStart, TBool aLossless, TBool aSeekable, TBool aLive, IStreamHandler* aStreamHandler)
{
    MsgDecodedStream* msg = iAllocatorMsgDecodedStream.Allocate();
    msg->Initialise(aStreamId, aBitRate, aBitDepth, aSampleRate, aNumChannels, aCodecName, aTrackLength, aSampleStart, aLossless, aSeekable, aLive, aStreamHandler);
    return msg;
}

MsgAudioPcm* MsgFactory::CreateMsgAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset)
{
    DecodedAudio* decodedAudio = CreateDecodedAudio(aData, aChannels, aSampleRate, aBitDepth, aEndian);
    MsgAudioPcm* msg = iAllocatorMsgAudioPcm.Allocate();
    try {
        msg->Initialise(decodedAudio, aTrackOffset, iAllocatorMsgPlayablePcm);
    }
    catch (AssertionFailed&) { // test code helper
        msg->RemoveRef();
        throw;
    }
    return msg;
}

MsgAudioPcm* MsgFactory::CreateMsgAudioPcm(const Brx& aData, TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian, TUint64 aTrackOffset, TUint aRxTimestamp, TUint aLatency, TUint aNetworkTimestamp, TUint aMediaTimestamp)
{
    MsgAudioPcm* msg = CreateMsgAudioPcm(aData, aChannels, aSampleRate, aBitDepth, aEndian, aTrackOffset);
    msg->SetTimestamps(aRxTimestamp, aLatency, aNetworkTimestamp, aMediaTimestamp);
    return msg;
}

MsgSilence* MsgFactory::CreateMsgSilence(TUint aSizeJiffies)
{
    MsgSilence* msg = iAllocatorMsgSilence.Allocate();
    msg->Initialise(aSizeJiffies, iAllocatorMsgPlayableSilence);
    return msg;
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
