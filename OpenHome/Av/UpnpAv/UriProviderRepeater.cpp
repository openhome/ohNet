#include <OpenHome/Av/UpnpAv/UriProviderRepeater.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Filler.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

// UriProviderRepeater

UriProviderRepeater::UriProviderRepeater(const TChar* aMode, TrackFactory& aTrackFactory)
    : UriProvider(aMode, false, false)
    , iLock("UPRP")
    , iTrackFactory(aTrackFactory)
    , iTrack(NULL)
    , iRetrieved(true)
    , iPlayLater(false)
{
}

UriProviderRepeater::~UriProviderRepeater()
{
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
}

Track* UriProviderRepeater::SetTrack(const Brx& aUri, const Brx& aMetaData, TBool aPullable)
{
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
    if (aUri == Brx::Empty()) {
        iTrack = NULL;
    }
    else {
        iTrack = iTrackFactory.CreateTrack(aUri, aMetaData, NULL, aPullable);
        iTrack->AddRef();
    }
    return iTrack;
}

void UriProviderRepeater::SetTrack(Track* aTrack)
{
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
    iTrack = aTrack;
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
    if (iTrack == NULL) {
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

void UriProviderRepeater::DoBegin(TUint aTrackId, TBool aLater)
{
    iLock.Wait();
    iRetrieved = (iTrack == NULL || iTrack->Id() != aTrackId);
    iPlayLater = aLater;
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
