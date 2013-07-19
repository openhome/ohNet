#include <OpenHome/Av/Playlist/ProviderPlaylist.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <Generated/DvAvOpenhomeOrgPlaylist1.h>
#include <OpenHome/Av/Playlist/PlaylistDatabase.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/FaultCode.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Av/ProviderUtils.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Timer.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

static const TUint kIdNotFoundCode = 800;
static const Brn kIdNotFoundMsg("Id not found");
static const TInt kPlaylistFull = 801;
static const Brn kPlaylistFullMsg("Playlist full");

// ProviderPlaylist

ProviderPlaylist::ProviderPlaylist(Net::DvDevice& aDevice, Environment& aEnv, ISourcePlaylist& aSource, IPlaylistDatabase& aDatabase, const TChar* aProtocolInfo)
    : DvProviderAvOpenhomeOrgPlaylist1(aDevice)
    , iLock("PPLY")
    , iSource(aSource)
    , iDatabase(aDatabase)
    , iProtocolInfo(aProtocolInfo)
    , iTimerActive(false)
{
    iTimer = new Timer(aEnv, MakeFunctor(*this, &ProviderPlaylist::TimerCallabck));
    iDatabase.SetObserver(*this);

    EnablePropertyTransportState();
    EnablePropertyRepeat();
    EnablePropertyShuffle();
    EnablePropertyId();
    EnablePropertyIdArray();
    EnablePropertyTracksMax();
    EnablePropertyProtocolInfo();

    EnableActionPlay();
    EnableActionPause();
    EnableActionStop();
    EnableActionNext();
    EnableActionPrevious();
    EnableActionSetRepeat();
    EnableActionRepeat();
    EnableActionSetShuffle();
    EnableActionShuffle();
    EnableActionSeekSecondAbsolute();
    EnableActionSeekSecondRelative();
    EnableActionSeekId();
    EnableActionSeekIndex();
    EnableActionTransportState();
    EnableActionId();
    EnableActionRead();
    EnableActionReadList();
    EnableActionInsert();
    EnableActionDeleteId();
    EnableActionDeleteAll();
    EnableActionTracksMax();
    EnableActionIdArray();
    EnableActionIdArrayChanged();
    EnableActionProtocolInfo();

    NotifyPipelineState(Media::EPipelineStopped);
    SetRepeat(false);
    SetShuffle(false);
    NotifyTrack(IPlaylistDatabase::kTrackIdNone);
    UpdateIdArrayProperty();
    (void)SetPropertyTracksMax(IPlaylistDatabase::kMaxTracks);
    (void)SetPropertyProtocolInfo(iProtocolInfo);
}

ProviderPlaylist::~ProviderPlaylist()
{
    delete iTimer;
}

void ProviderPlaylist::NotifyPipelineState(Media::EPipelineState aState)
{
    Brn state(Media::TransportState::FromPipelineState(aState));
    iLock.Wait();
    iPipelineState = aState;
    (void)SetPropertyTransportState(state);
    iLock.Signal();
}

void ProviderPlaylist::NotifyTrack(TUint aId)
{
    iIdCurrentTrack = aId;
    (void)SetPropertyId(aId);
}

void ProviderPlaylist::PlaylistDatabaseChanged()
{
    AutoMutex a(iLock);
    if (!iTimerActive) {
        iTimerActive = true;
        iTimer->FireIn(kIdArrayUpdateFrequencyMillisecs);
    }
}

void ProviderPlaylist::Play(IDvInvocation& aInvocation)
{
    iSource.Play();
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::Pause(IDvInvocation& aInvocation)
{
    iSource.Pause();
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::Stop(IDvInvocation& aInvocation)
{
    iSource.Stop();
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::Next(IDvInvocation& aInvocation)
{
    iSource.Next();
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::Previous(IDvInvocation& aInvocation)
{
    iSource.Prev();
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::SetRepeat(IDvInvocation& aInvocation, TBool aValue)
{
    SetRepeat(aValue);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::Repeat(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue)
{
    aInvocation.StartResponse();
    TBool repeat;
    GetPropertyRepeat(repeat);
    aValue.Write(repeat);
    aInvocation.EndResponse();
}

void ProviderPlaylist::SetShuffle(IDvInvocation& aInvocation, TBool aValue)
{
    SetShuffle(aValue);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::Shuffle(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue)
{
    aInvocation.StartResponse();
    TBool shuffle;
    GetPropertyShuffle(shuffle);
    aValue.Write(shuffle);
    aInvocation.EndResponse();
}

void ProviderPlaylist::SeekSecondAbsolute(IDvInvocation& aInvocation, TUint aValue)
{
    iSource.SeekAbsolute(aValue);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::SeekSecondRelative(IDvInvocation& aInvocation, TInt aValue)
{
    iSource.SeekRelative(aValue);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::SeekId(IDvInvocation& aInvocation, TUint aValue)
{
    iSource.SeekToTrackId(aValue);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::SeekIndex(IDvInvocation& aInvocation, TUint aValue)
{
    iSource.SeekToTrackIndex(aValue);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::TransportState(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue)
{
    iLock.Wait();
    Brn state(Media::TransportState::FromPipelineState(iPipelineState));
    iLock.Signal();
    aInvocation.StartResponse();
    aValue.Write(state);
    aValue.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderPlaylist::Id(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue)
{
    TUint id;
    GetPropertyId(id);
    aInvocation.StartResponse();
    aValue.Write(id);
    aInvocation.EndResponse();
}

void ProviderPlaylist::Read(IDvInvocation& aInvocation, TUint aId, IDvInvocationResponseString& aUri, IDvInvocationResponseString& aMetadata)
{
    {
        AutoMutex a(iLock);
        Track* track = NULL;
        try {
            iDatabase.GetTrackById(aId, track);
        }
        catch (PlaylistDbIdNotFound&) {
            aInvocation.Error(kIdNotFoundCode, kIdNotFoundMsg);
        }
        AutoAllocatedRef t(*track);
        aInvocation.StartResponse();
        aUri.Write(track->Uri());
        aUri.WriteFlush();
        aMetadata.Write(track->MetaData());
        aMetadata.WriteFlush();
    }
    aInvocation.EndResponse();
}

void ProviderPlaylist::ReadList(IDvInvocation& aInvocation, const Brx& aIdList, IDvInvocationResponseString& aTrackList)
{
    iLock.Wait();
    const TUint seq = iDbSeq;
    iLock.Signal();
    Parser parser(aIdList);
    TUint index = 0;
    const Brn entryStart("<Entry>");
    const Brn entryEnd("</Entry>");
    const Brn idStart("<Id>");
    const Brn idEnd("</Id>");
    const Brn uriStart("<Uri>");
    const Brn uriEnd("</Uri>");
    const Brn metaStart("<Metadata>");
    const Brn metaEnd("</Metadata>");
    Brn idBuf;
    idBuf.Set(parser.Next(' '));

    aInvocation.StartResponse();
    aTrackList.Write(Brn("<TrackList>"));
    do {
        try {
            TUint id = Ascii::Uint(idBuf);
            try {
                Track* track;
                iDatabase.GetTrackById(id, seq, track, index);
                AutoAllocatedRef a(*track);
                aTrackList.Write(entryStart);
                aTrackList.Write(idStart);
                aTrackList.Write(idBuf);
                aTrackList.Write(idEnd);
                aTrackList.Write(uriStart);
                WriterInvocationResponseString writer(aTrackList);
                Converter::ToXmlEscaped(writer, track->Uri());
                aTrackList.Write(uriEnd);
                aTrackList.Write(metaStart);
                Converter::ToXmlEscaped(writer, track->MetaData());
                aTrackList.Write(metaEnd);
                aTrackList.Write(entryEnd);
            }
            catch (PlaylistDbIdNotFound&) { }
        }
        catch (AsciiError&) { }
        idBuf.Set(parser.Next(' '));
    } while (idBuf != Brx::Empty());
    aTrackList.Write(Brn("</TrackList>"));
    aTrackList.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderPlaylist::Insert(IDvInvocation& aInvocation, TUint aAfterId, const Brx& aUri, const Brx& aMetadata, IDvInvocationResponseUint& aNewId)
{
    TUint newId;
    try {
        iDatabase.Insert(aAfterId, aUri, aMetadata, newId);
    }
    catch (PlaylistDbIdNotFound&) {
        aInvocation.Error(kIdNotFoundCode, kIdNotFoundMsg);
    }
    catch (PlaylistDbFull&) {
        aInvocation.Error(kPlaylistFull, kPlaylistFullMsg);
    }
    aInvocation.StartResponse();
    aNewId.Write(newId);
    aInvocation.EndResponse();
}

void ProviderPlaylist::DeleteId(IDvInvocation& aInvocation, TUint aValue)
{
    try {
        iDatabase.DeleteId(aValue);
    }
    catch (PlaylistDbIdNotFound&) {
        aInvocation.Error(kIdNotFoundCode, kIdNotFoundMsg);
    }
    // FIXME - if track with id aValue is playing, need to also remove it
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::DeleteAll(IDvInvocation& aInvocation)
{
    // FIXME - also have to stop current track(s) if source is active
    iDatabase.DeleteAll();
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::TracksMax(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue)
{
    aInvocation.StartResponse();
    TUint maxTracks;
    GetPropertyTracksMax(maxTracks);
    aValue.Write(maxTracks);
    aInvocation.EndResponse();
}

void ProviderPlaylist::IdArray(IDvInvocation& aInvocation, IDvInvocationResponseUint& aToken, IDvInvocationResponseBinary& aArray)
{
    AutoMutex a(iLock);
    UpdateIdArray(); // can't rely on iIdArrayBuf being up to date since we defer acting on PlaylistDatabaseChanged() calls
    aInvocation.StartResponse();
    aToken.Write(iDbSeq);
    aArray.Write(iIdArrayBuf);
    aArray.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderPlaylist::IdArrayChanged(IDvInvocation& aInvocation, TUint aToken, IDvInvocationResponseBool& aValue)
{
    iLock.Wait();
    const bool changed = (aToken!=iDbSeq);
    iLock.Signal();
    aInvocation.StartResponse();
    aValue.Write(changed);
    aInvocation.EndResponse();
}

void ProviderPlaylist::ProtocolInfo(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue)
{
    aInvocation.StartResponse();
    aValue.Write(iProtocolInfo);
    aValue.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderPlaylist::SetRepeat(TBool aRepeat)
{
    (void)SetPropertyRepeat(aRepeat);
    iDatabase.SetRepeat(aRepeat);
}

void ProviderPlaylist::SetShuffle(TBool aShuffle)
{
    (void)SetPropertyShuffle(aShuffle);
    iDatabase.SetShuffle(aShuffle);
}

void ProviderPlaylist::UpdateIdArray()
{
    iDatabase.GetIdArray(iIdArray, iDbSeq);
    iIdArrayBuf.SetBytes(0);
    for (TUint i=0; i<IPlaylistDatabase::kMaxTracks; i++) {
        if (iIdArray[i] == IPlaylistDatabase::kTrackIdNone) {
            break;
        }
        TUint32 bigEndianId = Arch::BigEndian4(iIdArray[i]);
        Brn idBuf(reinterpret_cast<const TByte*>(&bigEndianId), sizeof(bigEndianId));
        iIdArrayBuf.Append(idBuf);
    }
}

void ProviderPlaylist::UpdateIdArrayProperty()
{
    UpdateIdArray();
    (void)SetPropertyIdArray(iIdArrayBuf);
}

void ProviderPlaylist::TimerCallabck()
{
    AutoMutex a(iLock);
    iTimerActive = false;
    UpdateIdArrayProperty();
}
