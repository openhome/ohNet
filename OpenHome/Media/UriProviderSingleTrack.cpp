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
    , iTrackFactory(aTrackFactory)
{
}

void UriProviderSingleTrack::Begin(const Brx& aProviderId)
{
    iUri.Replace(aProviderId);
}

EStreamPlay UriProviderSingleTrack::GetNext(Track*& aTrack)
{
    if (iUri.Bytes() == 0) {
        aTrack = NULL;
        return ePlayNo;
    }
    aTrack = iTrackFactory.CreateTrack(iUri, Brx::Empty(), Style(), iUri, NULL);
    iUri.SetBytes(0);
    return ePlayYes;
}

EStreamPlay UriProviderSingleTrack::GetPrev(Track*& aTrack)
{
    aTrack = NULL;
    return ePlayNo;
}
