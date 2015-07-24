#include <OpenHome/Av/Playlist/ProviderPlaylist.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <Generated/DvAvOpenhomeOrgPlaylist1.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Thread.h>
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
static const TUint kIndexNotFoundCode = 802;
static const Brn kIndexNotFoundMsg("Index not found");

// ProviderPlaylist

ProviderPlaylist::ProviderPlaylist(Net::DvDevice& aDevice, Environment& aEnv, ISourcePlaylist& aSource, ITrackDatabase& aDatabase, IRepeater& aRepeater, const Brx& aProtocolInfo)
    : DvProviderAvOpenhomeOrgPlaylist1(aDevice)
    , iLock("PPLY")
    , iSource(aSource)
    , iDatabase(aDatabase)
    , iRepeater(aRepeater)
    , iProtocolInfo(aProtocolInfo)
    , iTimerLock("PPL2")
    , iTimerActive(false)
{
    iTimer = new Timer(aEnv, MakeFunctor(*this, &ProviderPlaylist::TimerCallback), "ProviderPlaylist");
    iDatabase.AddObserver(*this);

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
    NotifyTrack(ITrackDatabase::kTrackIdNone);
    UpdateIdArrayProperty();
    (void)SetPropertyTracksMax(ITrackDatabase::kMaxTracks);
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
    (void)SetPropertyId(aId);
}

void ProviderPlaylist::NotifyTrackInserted(Track& /*aTrack*/, TUint /*aIdBefore*/, TUint /*aIdAfter*/)
{
    TrackDatabaseChanged();
}

void ProviderPlaylist::NotifyTrackDeleted(TUint /*aId*/, Track* aBefore, Track* aAfter)
{
    /* Deleting one of many tracks in a playlist will result in a new track starting to play
       and NotifyTrack() being called.  If we've just deleted the last track, we'll stop
       receiving pipeline events so will need to manually reset the current track id. */
    if (aBefore == nullptr && aAfter == nullptr) {
        NotifyTrack(ITrackDatabase::kTrackIdNone);
    }
    TrackDatabaseChanged();
}

void ProviderPlaylist::NotifyAllDeleted()
{
    NotifyTrack(ITrackDatabase::kTrackIdNone);
    TrackDatabaseChanged();
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
    try {
        iSource.SeekToTrackId(aValue);
    }
    catch (TrackDbIdNotFound&) {
        aInvocation.Error(kIdNotFoundCode, kIdNotFoundMsg);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::SeekIndex(IDvInvocation& aInvocation, TUint aValue)
{
    if (!iSource.SeekToTrackIndex(aValue)) {
        aInvocation.Error(kIndexNotFoundCode, kIndexNotFoundMsg);
    }
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
        Track* track = nullptr;
        try {
            iDatabase.GetTrackById(aId, track);
        }
        catch (TrackDbIdNotFound&) {
            aInvocation.Error(kIdNotFoundCode, kIdNotFoundMsg);
        }
        AutoAllocatedRef t(track);
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
                AutoAllocatedRef a(track);
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
            catch (TrackDbIdNotFound&) { }
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
    TUint newId = 0;
    try {
        iDatabase.Insert(aAfterId, aUri, aMetadata, newId);
    }
    catch (TrackDbIdNotFound&) {
        aInvocation.Error(kIdNotFoundCode, kIdNotFoundMsg);
    }
    catch (TrackDbFull&) {
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
        if (iDatabase.TrackCount() == 0) {
            iSource.Stop();
        }
    }
    catch (TrackDbIdNotFound&) {
        aInvocation.Error(kIdNotFoundCode, kIdNotFoundMsg);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderPlaylist::DeleteAll(IDvInvocation& aInvocation)
{
    iSource.Stop(); // we want TransportState == Stopped after this
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

void ProviderPlaylist::TrackDatabaseChanged()
{
    iTimerLock.Wait();
    if (!iTimerActive) {
        iTimerActive = true;
        iTimer->FireIn(kIdArrayUpdateFrequencyMillisecs);
    }
    iTimerLock.Signal();
}

void ProviderPlaylist::SetRepeat(TBool aRepeat)
{
    (void)SetPropertyRepeat(aRepeat);
    iRepeater.SetRepeat(aRepeat);
}

void ProviderPlaylist::SetShuffle(TBool aShuffle)
{
    (void)SetPropertyShuffle(aShuffle);
    iSource.SetShuffle(aShuffle);
}

void ProviderPlaylist::UpdateIdArray()
{
    iDatabase.GetIdArray(iIdArray, iDbSeq);
    iIdArrayBuf.SetBytes(0);
    for (TUint i=0; i<ITrackDatabase::kMaxTracks; i++) {
        if (iIdArray[i] == ITrackDatabase::kTrackIdNone) {
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

void ProviderPlaylist::TimerCallback()
{
    iTimerLock.Wait();
    iTimerActive = false;
    iTimerLock.Signal();
    AutoMutex a(iLock);
    UpdateIdArrayProperty();
}
