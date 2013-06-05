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

void UriProviderSingleTrack::Begin(TUint aTrackId)
{
    iLock.Wait();
    ASSERT(iTrack != NULL);
    ASSERT(iTrack->Id() == aTrackId);
    iIgnoreNext = true;
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

TBool UriProviderSingleTrack::MoveCursorAfter(TUint aTrackId)
{
    return MoveCursor(aTrackId);
}

TBool UriProviderSingleTrack::MoveCursorBefore(TUint aTrackId)
{
    return MoveCursor(aTrackId);
}

TUint UriProviderSingleTrack::SetTrack(const Brx& aUri, const Brx& aMetaData)
{
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
    iTrack = iTrackFactory.CreateTrack(aUri, aMetaData, NULL);
    return iTrack->Id();
}

void UriProviderSingleTrack::SetTrack(Track* aTrack)
{
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
    iTrack = aTrack;
}

TBool UriProviderSingleTrack::MoveCursor(TUint aTrackId)
{
    AutoMutex a(iLock);
    if (iTrack == NULL || iTrack->Id() != aTrackId) {
        return false;
    }
    iIgnoreNext = true;
    return true;
}
