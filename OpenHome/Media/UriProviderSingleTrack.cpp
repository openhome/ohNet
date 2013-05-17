#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Filler.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// UriProviderSingleTrack

UriProviderSingleTrack::UriProviderSingleTrack(TrackFactory& aTrackFactory)
    : UriProvider("SingleTrack")
    , iLock("UPST")
    , iTrackFactory(aTrackFactory)
    , iIgnoreNext(true)
{
}

void UriProviderSingleTrack::Begin(const Brx& aProviderId)
{
    iLock.Wait();
    iUri.Replace(aProviderId);
    iIgnoreNext = false;
    iLock.Signal();
}

EStreamPlay UriProviderSingleTrack::GetNext(Track*& aTrack)
{
    AutoMutex a(iLock);
    if (iIgnoreNext || iUri.Bytes() == 0) {
        aTrack = NULL;
        return ePlayNo;
    }
    aTrack = iTrackFactory.CreateTrack(iUri, Brx::Empty(), Style(), iUri, NULL);
    iIgnoreNext = true;
    return ePlayYes;
}

TBool UriProviderSingleTrack::MoveCursorAfter(const Brx& aProviderId)
{
    return MoveCursor(aProviderId);
}

TBool UriProviderSingleTrack::MoveCursorBefore(const Brx& aProviderId)
{
    return MoveCursor(aProviderId);
}

TBool UriProviderSingleTrack::MoveCursor(const Brx& aProviderId)
{
    AutoMutex a(iLock);
    if (iUri != aProviderId) {
        return false;
    }
    iIgnoreNext = true;
    return true;
}
