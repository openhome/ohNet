#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Filler.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// UriProviderSingleTrack

UriProviderSingleTrack::UriProviderSingleTrack(const TChar* aMode, TBool aSupportsLatency, TBool aRealTime, TrackFactory& aTrackFactory)
    : UriProvider(aMode, aSupportsLatency, aRealTime)
    , iLock("UPST")
    , iTrackFactory(aTrackFactory)
    , iTrack(NULL)
    , iIgnoreNext(true)
    , iPlayLater(false)
{
}

UriProviderSingleTrack::~UriProviderSingleTrack()
{
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
}

Track* UriProviderSingleTrack::SetTrack(const Brx& aUri, const Brx& aMetaData)
{
    AutoMutex a(iLock);
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
    if (aUri == Brx::Empty()) {
        iTrack = NULL;
    }
    else {
        iTrack = iTrackFactory.CreateTrack(aUri, aMetaData);
        iTrack->AddRef();
    }
    return iTrack;
}

void UriProviderSingleTrack::SetTrack(Track* aTrack)
{
    AutoMutex a(iLock);
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
    iTrack = aTrack;
}

void UriProviderSingleTrack::Begin(TUint aTrackId)
{
    DoBegin(aTrackId, false);
}

void UriProviderSingleTrack::BeginLater(TUint aTrackId)
{
    DoBegin(aTrackId, true);
}

EStreamPlay UriProviderSingleTrack::GetNext(Track*& aTrack)
{
    AutoMutex a(iLock);
    if (iIgnoreNext || iTrack == NULL) {
        aTrack = NULL;
        return ePlayNo;
    }
    aTrack = iTrack;
    aTrack->AddRef();
    iIgnoreNext = true;
    return (iPlayLater? ePlayLater : ePlayYes);
}

TUint UriProviderSingleTrack::CurrentTrackId() const
{
    TUint id = Track::kIdNone;
    iLock.Wait();
    if (iTrack != NULL) {
        id = iTrack->Id();
    }
    iLock.Signal();
    return id;
}

TBool UriProviderSingleTrack::MoveNext()
{
    return MoveCursor();
}

TBool UriProviderSingleTrack::MovePrevious()
{
    return MoveCursor();
}

void UriProviderSingleTrack::DoBegin(TUint aTrackId, TBool aLater)
{
    iLock.Wait();
    iIgnoreNext = (iTrack == NULL || iTrack->Id() != aTrackId);
    iPlayLater = aLater;
    iLock.Signal();
}

TBool UriProviderSingleTrack::MoveCursor()
{
    AutoMutex a(iLock);
    if (iTrack == NULL || iIgnoreNext) {
        return false;
    }
    iIgnoreNext = true;
    return true;
}
