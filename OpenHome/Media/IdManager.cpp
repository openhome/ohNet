#include <OpenHome/Media/IdManager.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Printer.h>

#include <climits>

using namespace OpenHome;
using namespace OpenHome::Media;

#undef ID_MANAGER_LOG_ENABLE

// IdManager

IdManager::IdManager(IStopper& aStopper)
    : iLock("IDPR")
    , iStopper(aStopper)
    , iNextTrackId(kTrackIdInvalid+1)
    , iNextStreamId(kStreamIdInvalid+1)
    , iIndexHead(0)
    , iIndexTail(0)
{
}

void IdManager::AddStream(TUint aId, TUint aStreamId, TBool aPlayNow)
{
    iLock.Wait();
    iActiveStreams[iIndexTail].Set(aId, aStreamId, aPlayNow);
    UpdateIndex(iIndexTail);
    ASSERT(iIndexHead != iIndexTail); // OkToPlay can't tell the difference between a full and empty list
                                      // ...so we assume the list contains at most kMaxActiveStreams-1 elements
    Log("AddStream");
    iLock.Signal();
}

TUint IdManager::MaxStreams() const
{
    return kMaxActiveStreams;
}

inline void IdManager::UpdateIndex(TUint& aIndex)
{ // static
    if (++aIndex == kMaxActiveStreams) {
        aIndex = 0;
    }
}

TUint IdManager::UpdateId(TUint& aId)
{
    iLock.Wait();
    TUint id = aId++;
    iLock.Signal();
    return id;
}

void IdManager::Log(
#ifdef ID_MANAGER_LOG_ENABLE
                    const TChar* aPrefix
#else
                    const TChar* /*aPrefix*/
#endif
                    )
{
#ifdef ID_MANAGER_LOG_ENABLE
    Log::Print("IdManager: %s.  Pending items are:\n", aPrefix);
    TUint index = iIndexHead;
    while (index != iIndexTail) {
        ActiveStream& as = iActiveStreams[index];
        Log::Print("    trackId:%u streamId:%u, playNow=%u\n", as.Id(), as.StreamId(), as.PlayNow());
        if (++index == kMaxActiveStreams) {
            index = 0;
        }
    }
#endif
}

TUint IdManager::NextTrackId()
{
    return UpdateId(iNextTrackId);
}

TUint IdManager::NextStreamId()
{
    return UpdateId(iNextStreamId);
}

EStreamPlay IdManager::OkToPlay(TUint aStreamId)
{
    AutoMutex a(iLock);
    if (iIndexHead == iIndexTail) {
        Log("OkToPlay (fail - empty)");
        return ePlayNo;
    }
    const ActiveStream& as = iActiveStreams[iIndexHead];
    if (as.StreamId() != aStreamId) {
        Log("OkToPlay (fail - wrong stream)");
        return ePlayNo;
    }
    iPlaying.Set(as);
    UpdateIndex(iIndexHead);
    Log("OkToPlay");
    return iPlaying.PlayNow()? ePlayYes : ePlayLater;
}

void IdManager::InvalidateAt(TUint aId)
{
    AutoMutex a(iLock);

    TBool matched = false;
    if (iPlaying.Id() == aId) {
        matched = true;
        iStopper.RemoveStream(UINT_MAX, iPlaying.StreamId()); // FIXME
        iPlaying.Clear();
    }
    TBool updateHead = matched;

    if (iIndexHead == iIndexTail) {
        return;
    }
    TUint index = iIndexHead;
    TUint prevIndex = index;
    // find first match
    while (!matched && index != iIndexTail) {
        matched = (iActiveStreams[index].Id() == aId);
        if (matched && index == iIndexHead) {
            updateHead = true;
        }
        prevIndex = index;
        UpdateIndex(index);
    }

    if (matched) {
        // advance past any additional streams for the same track
        while (index != iIndexTail && iActiveStreams[index].Id() == aId) {
            UpdateIndex(index);
        }

        if (updateHead) {
            iIndexHead = index;
        }
        else { // shuffle remainder of buffer down
            ASSERT(prevIndex != index);
            for (;;) {
                if (index == iIndexTail) {
                    break;
                }
                iActiveStreams[prevIndex].Set(iActiveStreams[index]);
                UpdateIndex(prevIndex);
                UpdateIndex(index);
            }
            iIndexTail = prevIndex;
        }
    }
    Log("InvalidateAt");
}

void IdManager::InvalidateAfter(TUint aId)
{
    AutoMutex a(iLock);

    // find first matching instance
    TUint index = iIndexHead;
    TUint streamId = kStreamIdInvalid;
    TBool matched = (iPlaying.Id() == aId);
    if (matched) {
        streamId = iPlaying.StreamId();
    }
    while (!matched && index != iIndexTail) {
        if (iActiveStreams[index].Id() == aId) {
            matched = true;
            streamId = iActiveStreams[index].StreamId();
        }
        UpdateIndex(index);
    }

    // if matched, advance past any additional streams for the same track
    if (matched) {
        while (index != iIndexTail && iActiveStreams[index].Id() == aId && streamId < iActiveStreams[index].StreamId()) {
            streamId = iActiveStreams[index].StreamId();
            UpdateIndex(index);
        }
        iIndexTail = index;
    }
    Log("InvalidateAfter");
}

void IdManager::InvalidatePending()
{
    iLock.Wait();
    iIndexTail = iIndexHead;
    Log("InvalidatePending");
    iLock.Signal();
}

void IdManager::InvalidateAll()
{
    AutoMutex a(iLock);
    if (!iPlaying.IsClear()) {
        iStopper.RemoveStream(UINT_MAX, iPlaying.StreamId()); // FIXME
        iPlaying.Clear();
    }
    iIndexTail = iIndexHead;
    Log("InvalidateAll");
}


//  IdManager::ActiveStream

IdManager::ActiveStream::ActiveStream()
{
    Clear();
}

void IdManager::ActiveStream::Set(TUint aId, TUint aStreamId, TBool aPlayNow)
{
    iId = aId;
    iStreamId = aStreamId;
    iPlayNow = aPlayNow;
    iClear = false;
}

void IdManager::ActiveStream::Set(const ActiveStream& aActiveStream)
{
    Set(aActiveStream.Id(), aActiveStream.StreamId(), aActiveStream.PlayNow());
}

void IdManager::ActiveStream::Clear()
{
    iId = UINT_MAX;
    iStreamId = UINT_MAX;
    iPlayNow = false;
    iClear = true;
}
