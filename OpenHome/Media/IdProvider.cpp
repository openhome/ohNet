#include <OpenHome/Media/IdProvider.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// PipelineIdProvider

PipelineIdProvider::PipelineIdProvider(IStopper& aStopper)
    : iLock("IDPR")
    , iStopper(aStopper)
    , iNextTrackId(0)
    , iNextStreamId(0)
    , iIndexHead(0)
    , iIndexTail(0)
{
}

void PipelineIdProvider::AddStream(const Brx& aStyle, const Brx& aProviderId, TUint aTrackId, TUint aStreamId, TBool aPlayNow)
{
    iLock.Wait();
    iActiveStreams[iIndexTail].Set(aStyle, aProviderId, aTrackId, aStreamId, aPlayNow);
    UpdateIndex(iIndexTail);
    ASSERT(iIndexHead != iIndexTail); // OkToPlay can't tell the difference between a full and empty list
                                      // ...so we assume the list contains at most kMaxActiveStreams-1 elements
    iLock.Signal();
}

TUint PipelineIdProvider::MaxStreams() const
{
    return kMaxActiveStreams;
}

inline void PipelineIdProvider::UpdateIndex(TUint& aIndex)
{ // static
    if (++aIndex == kMaxActiveStreams) {
        aIndex = 0;
    }
}

TUint PipelineIdProvider::UpdateId(TUint& aId)
{
    iLock.Wait();
    TUint id = aId++;
    iLock.Signal();
    return id;
}

TUint PipelineIdProvider::NextTrackId()
{
    return UpdateId(iNextTrackId);
}

TUint PipelineIdProvider::NextStreamId()
{
    return UpdateId(iNextStreamId);
}

EStreamPlay PipelineIdProvider::OkToPlay(TUint aTrackId, TUint aStreamId)
{
    AutoMutex a(iLock);
    if (iIndexHead == iIndexTail) {
        return ePlayNo;
    }
    const ActiveStream& as = iActiveStreams[iIndexHead];
    if (as.TrackId() != aTrackId || as.StreamId() != aStreamId) {
        return ePlayNo;
    }
    iPlaying.Set(as);
    UpdateIndex(iIndexHead);
    return iPlaying.PlayNow()? ePlayYes : ePlayLater;
}

void PipelineIdProvider::InvalidateAt(const Brx& aStyle, const Brx& aProviderId)
{
    AutoMutex a(iLock);

    TBool matched = false;
    if (iPlaying.Matches(aStyle, aProviderId)) {
        matched = true;
        iStopper.RemoveStream(iPlaying.TrackId(), iPlaying.StreamId());
    }
    TBool updateHead = matched;

    if (iIndexHead == iIndexTail) {
        return;
    }
    TUint index = iIndexHead;
    TUint prevIndex = index;
    // find first match
    while (!matched && index != iIndexTail) {
        matched = iActiveStreams[index].Matches(aStyle, aProviderId);
        if (matched && index == iIndexHead) {
            updateHead = true;
        }
        prevIndex = index;
        UpdateIndex(index);
    }

    if (matched) {
        // advance past any additional streams for the same track
        while (index != iIndexTail && iActiveStreams[index].Matches(aStyle, aProviderId)) {
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

void PipelineIdProvider::InvalidateAfter(const Brx& aStyle, const Brx& aProviderId)
{
    // find first matching instance
    TUint index = iIndexHead;
    TBool matched = iPlaying.Matches(aStyle, aProviderId);
    while (!matched && index != iIndexTail) {
        if (iActiveStreams[index].Matches(aStyle, aProviderId)) {
            matched = true;
        }
        else {
            UpdateIndex(index);
        }
    }

    // if matched, advance past any additional streams for the same track
    if (matched) {
        while (index != iIndexTail && iActiveStreams[index].Matches(aStyle, aProviderId)) {
            UpdateIndex(index);
        }
        iIndexTail = index;
    }
}


//  PipelineIdProvider::ActiveStream

PipelineIdProvider::ActiveStream::ActiveStream()
{
}

void PipelineIdProvider::ActiveStream::Set(const Brx& aStyle, const Brx& aProviderId, TUint aTrackId, TUint aStreamId, TBool aPlayNow)
{
    iStyle.Replace(aStyle);
    iProviderId.Replace(aProviderId);
    iTrackId = aTrackId;
    iStreamId = aStreamId;
    iPlayNow = aPlayNow;
}

void PipelineIdProvider::ActiveStream::Set(const ActiveStream& aActiveStream)
{
    Set(aActiveStream.Style(), aActiveStream.ProviderId(), aActiveStream.TrackId(), aActiveStream.StreamId(), aActiveStream.PlayNow());
}

TBool PipelineIdProvider::ActiveStream::Matches(const Brx& aStyle, const Brx& aProviderId) const
{
    return (iStyle == aStyle && iProviderId == aProviderId);
}
