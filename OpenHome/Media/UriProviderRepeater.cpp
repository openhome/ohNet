#include <OpenHome/Media/UriProviderRepeater.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Filler.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// UriProviderRepeater

UriProviderRepeater::UriProviderRepeater(const TChar* aMode, TBool aSupportsLatency, TrackFactory& aTrackFactory)
    : UriProvider(aMode,
                  aSupportsLatency? Latency::Supported : Latency::NotSupported,
                  Next::NotSupported, Prev::NotSupported)
    , iLock("UPRP")
    , iTrackFactory(aTrackFactory)
    , iTrack(nullptr)
    , iRetrieved(true)
    , iPlayLater(false)
    , iFailed(false)
{
}

UriProviderRepeater::~UriProviderRepeater()
{
    if (iTrack != nullptr) {
        iTrack->RemoveRef();
    }
}

Track* UriProviderRepeater::SetTrack(const Brx& aUri, const Brx& aMetaData)
{
    AutoMutex a(iLock);
    if (iTrack != nullptr) {
        iTrack->RemoveRef();
    }
    if (aUri == Brx::Empty()) {
        iTrack = nullptr;
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
    if (iTrack != nullptr) {
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
    if (iTrack == nullptr || iFailed) {
        aTrack = nullptr;
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
    if (iTrack != nullptr) {
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

TBool UriProviderRepeater::MoveTo(const Brx& aCommand)
{
    if (aCommand.Bytes() != 0) {
        THROW(FillerInvalidCommand);
    }
    AutoMutex a(iLock);
    if (iTrack == nullptr) {
        return false;
    }
    iRetrieved = false;
    iPlayLater = false;
    return true;
}

void UriProviderRepeater::NotifyTrackPlay(Media::Track& aTrack)
{
    AutoMutex a(iLock);
    if (iTrack != nullptr && iTrack->Id() == aTrack.Id()) {
        iFailed = false;
    }
}

void UriProviderRepeater::NotifyTrackFail(Media::Track& aTrack)
{
    AutoMutex a(iLock);
    if (iTrack != nullptr && iTrack->Id() == aTrack.Id()) {
        iFailed = true;
    }
}

void UriProviderRepeater::DoBegin(TUint aTrackId, TBool aLater)
{
    iLock.Wait();
    iRetrieved = (iTrack == nullptr || iTrack->Id() != aTrackId);
    iPlayLater = aLater;
    iFailed = false;
    iLock.Signal();
}

TBool UriProviderRepeater::MoveCursor()
{
    AutoMutex a(iLock);
    if (iTrack == nullptr || iRetrieved) {
        return false;
    }
    iRetrieved = true;
    return true;
}
