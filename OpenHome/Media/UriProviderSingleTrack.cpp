#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Filler.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// UriProviderSingleTrack

UriProviderSingleTrack::UriProviderSingleTrack(const TChar* aMode, TrackFactory& aTrackFactory)
    : UriProvider(aMode)
    , iLock("UPST")
    , iTrackFactory(aTrackFactory)
    , iTrack(NULL)
    , iIgnoreNext(true)
{
}

Track* UriProviderSingleTrack::SetTrack(const Brx& aUri, const Brx& aMetaData)
{
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
    iTrack = iTrackFactory.CreateTrack(aUri, aMetaData, NULL);
    iTrack->AddRef();
    return iTrack;
}

void UriProviderSingleTrack::SetTrack(Track* aTrack)
{
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
    iTrack = aTrack;
}

void UriProviderSingleTrack::Begin(TUint aTrackId)
{
    iLock.Wait();
    ASSERT(iTrack != NULL);
    ASSERT(iTrack->Id() == aTrackId);
    iIgnoreNext = false;
    iLock.Signal();
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
    return ePlayYes;
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

TBool UriProviderSingleTrack::MoveCursor()
{
    AutoMutex a(iLock);
    if (iTrack == NULL || iIgnoreNext) {
        return false;
    }
    iIgnoreNext = true;
    return true;
}
