#include <OpenHome/Av/Scd/Receiver/UriProviderScd.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Thread.h>

using namespace OpenHome;
using namespace OpenHome::Scd;
using namespace OpenHome::Media;

const Brn UriProviderScd::kCommandUri("uri");

UriProviderScd::UriProviderScd(TrackFactory& aTrackFactory)
    : UriProvider("SCD",
                  Latency::NotSupported,
                  Next::NotSupported,
                  Prev::NotSupported,
                  Repeat::NotSupported,
                  Random::NotSupported)
    , iTrackFactory(aTrackFactory)
    , iLock("upsd")
    , iTrack(nullptr)
    , iCanPlay(ePlayNo)
{
}

UriProviderScd::~UriProviderScd()
{
    if (iTrack) {
        iTrack->RemoveRef();
    }
}

void UriProviderScd::Reset()
{
    AutoMutex _(iLock);
    if (iTrack) {
        iTrack->RemoveRef();
        iTrack = nullptr;
    }
}

void UriProviderScd::Begin(TUint aTrackId)
{
    ASSERT(aTrackId == iTrack->Id());
    iCanPlay = ePlayYes;
}

void UriProviderScd::BeginLater(TUint aTrackId)
{
    ASSERT(aTrackId == iTrack->Id());
    iCanPlay = ePlayLater;
}

EStreamPlay UriProviderScd::GetNext(Track*& aTrack)
{
    AutoMutex _(iLock);
    aTrack = iTrack;
    if (aTrack != nullptr) {
        aTrack->AddRef();
    }
    return (iTrack == nullptr) ? ePlayNo : iCanPlay;
}

TUint UriProviderScd::CurrentTrackId() const
{
    AutoMutex _(iLock);
    return (iTrack == nullptr) ? Track::kIdNone : iTrack->Id();
}

void UriProviderScd::MoveNext()
{
}

void UriProviderScd::MovePrevious()
{
}

void UriProviderScd::MoveTo(const Brx& aCommand)
{
    if (!aCommand.BeginsWith(kCommandUri)) {
        THROW(FillerInvalidCommand);
    }

    Parser parser(aCommand);
    (void)parser.Next('=');
    Brn uri = parser.Remaining();
    auto track = iTrackFactory.CreateTrack(uri, Brx::Empty());

    AutoMutex _(iLock);
    if (iTrack != nullptr) {
        iTrack->RemoveRef();
    }
    iTrack = track;
    iCanPlay = ePlayYes;
}
