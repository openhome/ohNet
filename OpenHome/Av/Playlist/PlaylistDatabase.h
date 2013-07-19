#ifndef HEADER_PLAYLIST_DATABASE
#define HEADER_PLAYLIST_DATABASE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Thread.h>

#include <array>
#include <vector>

EXCEPTION(PlaylistDbIdNotFound);
EXCEPTION(PlaylistDbFull);

namespace OpenHome {
namespace Media {
    class TrackFactory;
    class IPipelineIdManager;
    class Track;
}
namespace Av {

class IPlaylistDatabaseObserver
{
public:
    ~IPlaylistDatabaseObserver() {}
    virtual void PlaylistDatabaseChanged() = 0;
};

class IPlaylistDatabaseReader
{
public:
    virtual void MoveCursorTo(TUint aId) = 0;
    virtual Media::Track* NextTrack() = 0;
    virtual TBool TryMoveCursorAfter(TUint aId) = 0;
    virtual TBool TryMoveCursorBefore(TUint aId) = 0;
};

class IPlaylistDatabase
{
public:
    static const TUint kMaxTracks = 1000;
    static const TUint kTrackIdNone = 0;
public:
    virtual ~IPlaylistDatabase() {}
    virtual void SetObserver(IPlaylistDatabaseObserver& aObserver) = 0;
    virtual void GetIdArray(std::array<TUint32, kMaxTracks>& aIdArray, TUint& aSeq) const = 0;
    virtual void SetRepeat(TBool aRepeat) = 0;
    virtual void SetShuffle(TBool aShuffle) = 0;
    virtual void GetTrackById(TUint aId, Media::Track*& aTrack) const = 0;
    virtual void GetTrackById(TUint aId, TUint aSeq, Media::Track*& aTrack, TUint& aIndex) const = 0;
    virtual void Insert(TUint aIdAfter, const Brx& aUri, const Brx& aMetaData, TUint& aIdInserted) = 0;
    virtual void DeleteId(TUint aId) = 0;
    virtual void DeleteAll() = 0;
};

class PlaylistDatabase : public IPlaylistDatabase, public IPlaylistDatabaseReader
{
public:
    PlaylistDatabase(Media::TrackFactory& aTrackFactory, Media::IPipelineIdManager& aIdManager);
public: // from IPlaylistDatabase
    void SetObserver(IPlaylistDatabaseObserver& aObserver);
    void GetIdArray(std::array<TUint32, kMaxTracks>& aIdArray, TUint& aSeq) const;
    void SetRepeat(TBool aRepeat);
    void SetShuffle(TBool aShuffle);
    void GetTrackById(TUint aId, Media::Track*& aTrack) const;
    void GetTrackById(TUint aId, TUint aSeq, Media::Track*& aTrack, TUint& aIndex) const;
    void Insert(TUint aIdAfter, const Brx& aUri, const Brx& aMetaData, TUint& aIdInserted);
    void DeleteId(TUint aId);
    void DeleteAll();
private: // from IPlaylistDatabaseReader
    void MoveCursorTo(TUint aId);
    Media::Track* NextTrack();
    TBool TryMoveCursorAfter(TUint aId);
    TBool TryMoveCursorBefore(TUint aId);
private:
    TBool TryMoveCursor(TUint aId, TBool aAfter);
    TUint IndexFromId(std::vector<Media::Track*>& aList, TUint aId);
    TUint TrackIndexFromId(TUint aId) { return IndexFromId(iTrackList, aId); }
    TUint ShuffleIndexFromId(TUint aId) { return IndexFromId(iShuffleList, aId); }
    void Clear(std::vector<Media::Track*>& aList);
private:
    mutable Mutex iLock;
    Media::TrackFactory& iTrackFactory;
    Media::IPipelineIdManager& iIdManager;
    IPlaylistDatabaseObserver* iObserver;
    TBool iRepeat;
    TBool iShuffle;
    TUint iSeq;
    std::vector<Media::Track*> iTrackList;
    std::vector<Media::Track*> iShuffleList;
    TUint iCursorIndex;
};


} // namespace Av
} // namespace OpenHome

#endif // HEADER_PLAYLIST_DATABASE
