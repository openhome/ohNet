#include <OpenHome/Av/Radio/UriProviderRadio.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Av/Radio/PresetDatabase.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

// UriProviderRadio

const Brn UriProviderRadio::kCommandId("id");

UriProviderRadio::UriProviderRadio(TrackFactory& aTrackFactory,
                                   IPresetDatabaseReaderTrack& aDbReader)
    : UriProvider("Radio",
                  Latency::NotSupported,
                  Next::Supported,
                  Prev::Supported)
    , iLock("UPRD")
    , iTrackFactory(aTrackFactory)
    , iDbReader(aDbReader)
    , iTrack(nullptr)
    , iIgnoreNext(true)
    , iPlayLater(false)
{
}

UriProviderRadio::~UriProviderRadio()
{
    if (iTrack != nullptr) {
        iTrack->RemoveRef();
    }
}

Track* UriProviderRadio::SetTrack(const Brx& aUri, const Brx& aMetaData)
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
    return iTrack;
}

void UriProviderRadio::Begin(TUint aTrackId)
{
    DoBegin(aTrackId, false);
}

void UriProviderRadio::BeginLater(TUint aTrackId)
{
    DoBegin(aTrackId, true);
}

EStreamPlay UriProviderRadio::GetNext(Track*& aTrack)
{
    AutoMutex a(iLock);
    if (iIgnoreNext || iTrack == nullptr) {
        aTrack = nullptr;
        return ePlayNo;
    }
    aTrack = iTrack;
    aTrack->AddRef();
    iIgnoreNext = true;
    return (iPlayLater? ePlayLater : ePlayYes);
}

TUint UriProviderRadio::CurrentTrackId() const
{
    TUint id = Track::kIdNone;
    iLock.Wait();
    if (iTrack != nullptr) {
        id = iTrack->Id();
    }
    iLock.Signal();
    return id;
}

void UriProviderRadio::MoveNext()
{
    AutoMutex _(iLock);
    if (iTrack == nullptr) {
        return;
    }
    auto track = iDbReader.NextTrackRef(iTrack->Id());
    iPlayLater = (track == nullptr);
    if (track == nullptr) {
        track = iDbReader.FirstTrackRef();
    }
    iIgnoreNext = false;
    iTrack->RemoveRef();
    iTrack = track;
}

void UriProviderRadio::MovePrevious()
{
    AutoMutex _(iLock);
    if (iTrack == nullptr) {
        return;
    }
    auto track = iDbReader.PrevTrackRef(iTrack->Id());
    iPlayLater = (track == nullptr);
    if (track == nullptr) {
        track = iDbReader.LastTrackRef();
    }
    iIgnoreNext = false;
    iTrack->RemoveRef();
    iTrack = track;
}

void UriProviderRadio::MoveTo(const Brx& aCommand)
{
    if (!aCommand.BeginsWith(kCommandId)) {
        THROW(FillerInvalidCommand);
    }

    Parser parser(aCommand);
    Brn buf = parser.Next('=');
    TUint id = IPresetDatabaseReader::kPresetIdNone;
    try {
        id = Ascii::Uint(buf);
    }
    catch (AsciiError&) {
        THROW(FillerInvalidCommand);
    }
    auto track = iDbReader.TrackRefById(id);
    if (track == nullptr) {
        THROW(FillerInvalidCommand);
    }

    AutoMutex _(iLock);
    if (iTrack != nullptr) {
        iTrack->RemoveRef();
    }
    iTrack = track;
    iIgnoreNext = false;
    iPlayLater = false;
}

void UriProviderRadio::DoBegin(TUint aTrackId, TBool aLater)
{
    iLock.Wait();
    iIgnoreNext = (iTrack == nullptr || iTrack->Id() != aTrackId);
    iPlayLater = aLater;
    iLock.Signal();
}
