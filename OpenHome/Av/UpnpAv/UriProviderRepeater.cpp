#include <OpenHome/Av/UpnpAv/UriProviderRepeater.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Filler.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

// UriProviderRepeater

UriProviderRepeater::UriProviderRepeater(const TChar* aMode, TrackFactory& aTrackFactory)
    : UriProvider(aMode, LatencyNotSupported, RealTimeNotSupported, NextNotSupported, PrevNotSupported)
    , iLock("UPRP")
    , iTrackFactory(aTrackFactory)
    , iTrack(NULL)
    , iRetrieved(true)
    , iPlayLater(false)
    , iFailed(false)
{
}

UriProviderRepeater::~UriProviderRepeater()
{
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
}

Track* UriProviderRepeater::SetTrack(const Brx& aUri, const Brx& aMetaData)
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
    iFailed = false;
    return iTrack;
}

void UriProviderRepeater::SetTrack(Track* aTrack)
{
    AutoMutex a(iLock);
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
    iTrack = aTrack;
    iFailed = false;
}

void UriProviderRepeater::Begin(TUint aTrackId)
{
    DoBegin(aTrackId, false);
}

void UriProviderRepeater::BeginLater(TUint aTrackId)
{
    DoBegin(aTrackId, true);
}

EStreamPlay UriProviderRepeater::GetNext(Track*& aTrack)
{
    AutoMutex a(iLock);
    if (iTrack == NULL || iFailed) {
        aTrack = NULL;
        return ePlayNo;
    }
    else if (iRetrieved) {
        iPlayLater = true;
    }
    aTrack = iTrack;
    aTrack->AddRef();
    iRetrieved = true;
    return (iPlayLater? ePlayLater : ePlayYes);
}

TUint UriProviderRepeater::CurrentTrackId() const
{
    TUint id = Track::kIdNone;
    iLock.Wait();
    if (iTrack != NULL) {
        id = iTrack->Id();
    }
    iLock.Signal();
    return id;
}

TBool UriProviderRepeater::MoveNext()
{
    return MoveCursor();
}

TBool UriProviderRepeater::MovePrevious()
{
    return MoveCursor();
}

void UriProviderRepeater::NotifyTrackPlay(Media::Track& aTrack)
{
    AutoMutex a(iLock);
    if (iTrack != NULL && iTrack->Id() == aTrack.Id()) {
        iFailed = false;
    }
}

void UriProviderRepeater::NotifyTrackFail(Media::Track& aTrack)
{
    AutoMutex a(iLock);
    if (iTrack != NULL && iTrack->Id() == aTrack.Id()) {
        iFailed = true;
    }
}

void UriProviderRepeater::DoBegin(TUint aTrackId, TBool aLater)
{
    iLock.Wait();
    iRetrieved = (iTrack == NULL || iTrack->Id() != aTrackId);
    iPlayLater = aLater;
    iFailed = false;
    iLock.Signal();
}

TBool UriProviderRepeater::MoveCursor()
{
    AutoMutex a(iLock);
    if (iTrack == NULL || iRetrieved) {
        return false;
    }
    iRetrieved = true;
    return true;
}
