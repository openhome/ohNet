#include <OpenHome/Media/IdManager.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

#include <climits>

using namespace OpenHome;
using namespace OpenHome::Media;

// IdManager

IdManager::IdManager(IStopper& aStopper)
    : iLock("IDPR")
    , iStopper(aStopper)
    , iNextTrackId(0)
    , iNextStreamId(0)
    , iIndexHead(0)
    , iIndexTail(0)
{
}

void IdManager::AddStream(TUint aId, TUint aPipelineTrackId, TUint aStreamId, TBool aPlayNow)
{
    iLock.Wait();
    iActiveStreams[iIndexTail].Set(aId, aPipelineTrackId, aStreamId, aPlayNow);
    UpdateIndex(iIndexTail);
    ASSERT(iIndexHead != iIndexTail); // OkToPlay can't tell the difference between a full and empty list
                                      // ...so we assume the list contains at most kMaxActiveStreams-1 elements
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

TUint IdManager::NextTrackId()
{
    return UpdateId(iNextTrackId);
}

TUint IdManager::NextStreamId()
{
    return UpdateId(iNextStreamId);
}

EStreamPlay IdManager::OkToPlay(TUint aTrackId, TUint aStreamId)
{
    AutoMutex a(iLock);
    if (iIndexHead == iIndexTail) {
        return ePlayNo;
    }
    const ActiveStream& as = iActiveStreams[iIndexHead];
    if (as.PipelineTrackId() != aTrackId || as.StreamId() != aStreamId) {
        return ePlayNo;
    }
    iPlaying.Set(as);
    UpdateIndex(iIndexHead);
    return iPlaying.PlayNow()? ePlayYes : ePlayLater;
}

void IdManager::InvalidateAt(TUint aId)
{
    AutoMutex a(iLock);

    TBool matched = false;
    if (iPlaying.Id() == aId) {
        matched = true;
        iStopper.RemoveStream(iPlaying.PipelineTrackId(), iPlaying.StreamId());
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
}

void IdManager::InvalidateAfter(TUint aId)
{
    AutoMutex a(iLock);

    // find first matching instance
    TUint index = iIndexHead;
    TBool matched = (iPlaying.Id() == aId);
    while (!matched && index != iIndexTail) {
        if (iActiveStreams[index].Id() == aId) {
            matched = true;
        }
        else {
            UpdateIndex(index);
        }
    }

    // if matched, advance past any additional streams for the same track
    if (matched) {
        while (index != iIndexTail && iActiveStreams[index].Id() == aId) {
            UpdateIndex(index);
        }
        iIndexTail = index;
    }
}

void IdManager::InvalidateAll()
{
    AutoMutex a(iLock);
    if (!iPlaying.IsClear()) {
        iStopper.RemoveStream(iPlaying.PipelineTrackId(), iPlaying.StreamId());
        iPlaying.Clear();
    }
    iIndexTail = iIndexHead;
}


//  IdManager::ActiveStream

IdManager::ActiveStream::ActiveStream()
{
    Clear();
}

void IdManager::ActiveStream::Set(TUint aId, TUint aPipelineTrackId, TUint aStreamId, TBool aPlayNow)
{
    iId = aId;
    iPipelineTrackId = aPipelineTrackId;
    iStreamId = aStreamId;
    iPlayNow = aPlayNow;
    iClear = false;
}

void IdManager::ActiveStream::Set(const ActiveStream& aActiveStream)
{
    Set(aActiveStream.Id(), aActiveStream.PipelineTrackId(), aActiveStream.StreamId(), aActiveStream.PlayNow());
}

void IdManager::ActiveStream::Clear()
{
    iId = UINT_MAX;
    iPipelineTrackId = UINT_MAX;
    iStreamId = UINT_MAX;
    iPlayNow = false;
    iClear = true;
}
