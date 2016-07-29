#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Thread.h>

#include <array>
#include <vector>

EXCEPTION(TrackDbIdNotFound);
EXCEPTION(TrackDbFull);

namespace OpenHome {
    class Environment;
namespace Media {
    class Track;
    class TrackFactory;
}
namespace Av {
    
class ITrackDatabaseObserver
{
public:
    virtual ~ITrackDatabaseObserver() {}
    virtual void NotifyTrackInserted(Media::Track& aTrack, TUint aIdBefore, TUint aIdAfter) = 0;
    virtual void NotifyTrackDeleted(TUint aId, Media::Track* aBefore, Media::Track* aAfter) = 0;
    virtual void NotifyAllDeleted() = 0;
};

class ITrackDatabase
{
public:
    static const TUint kMaxTracks = 1000;
    static const TUint kTrackIdNone = 0;
public:
    virtual ~ITrackDatabase() {}
    virtual void AddObserver(ITrackDatabaseObserver& aObserver) = 0;
    virtual void GetIdArray(std::array<TUint32, kMaxTracks>& aIdArray, TUint& aSeq) const = 0;
    virtual void GetTrackById(TUint aId, Media::Track*& aTrack) const = 0;
    virtual void GetTrackById(TUint aId, TUint aSeq, Media::Track*& aTrack, TUint& aIndex) const = 0;
    virtual void Insert(TUint aIdAfter, const Brx& aUri, const Brx& aMetaData, TUint& aIdInserted) = 0;
    virtual void DeleteId(TUint aId) = 0;
    virtual void DeleteAll() = 0;
    virtual TUint TrackCount() const = 0;
};

class ITrackDatabaseReader
{
public:
    virtual ~ITrackDatabaseReader() {}
    virtual void SetObserver(ITrackDatabaseObserver& aObserver) = 0;
    virtual Media::Track* TrackRef(TUint aId) = 0;
    virtual Media::Track* NextTrackRef(TUint aId) = 0;
    virtual Media::Track* PrevTrackRef(TUint aId) = 0;
    virtual Media::Track* TrackRefByIndex(TUint aIndex) = 0;
    virtual Media::Track* TrackRefByIndexSorted(TUint aIndex) = 0;
    virtual TBool IsValid(TUint aId) const = 0;
};

class IRepeater
{
public:
    virtual ~IRepeater() {}
    virtual void SetRepeat(TBool aRepeat) = 0;
};

class TrackDatabase : public ITrackDatabase, public ITrackDatabaseReader
{
public:
    TrackDatabase(Media::TrackFactory& aTrackFactory);
    ~TrackDatabase();
private: // from ITrackDatabase
    void AddObserver(ITrackDatabaseObserver& aObserver) override;
    void GetIdArray(std::array<TUint32, kMaxTracks>& aIdArray, TUint& aSeq) const override;
    void GetTrackById(TUint aId, Media::Track*& aTrack) const override;
    void GetTrackById(TUint aId, TUint aSeq, Media::Track*& aTrack, TUint& aIndex) const override;
    void Insert(TUint aIdAfter, const Brx& aUri, const Brx& aMetaData, TUint& aIdInserted) override;
    void DeleteId(TUint aId) override;
    void DeleteAll() override;
    TUint TrackCount() const override;
private: // from ITrackDatabaseReader
    void SetObserver(ITrackDatabaseObserver& aObserver) override;
    Media::Track* TrackRef(TUint aId) override;
    Media::Track* NextTrackRef(TUint aId) override;
    Media::Track* PrevTrackRef(TUint aId) override;
    Media::Track* TrackRefByIndex(TUint aIndex) override;
    Media::Track* TrackRefByIndexSorted(TUint aIndex) override;
    TBool IsValid(TUint aId) const override;
private:
    void GetTrackByIdLocked(TUint aId, Media::Track*& aTrack) const;
    TBool TryGetTrackById(TUint aId, Media::Track*& aTrack, TUint aStartIndex, TUint aEndIndex, TUint& aFoundIndex) const;
private:
    mutable Mutex iLock;
    Mutex iObserverLock;
    Media::TrackFactory& iTrackFactory;
    std::vector<ITrackDatabaseObserver*> iObservers;
    std::vector<Media::Track*> iTrackList;
    TUint iSeq;
};

class Shuffler : public ITrackDatabaseReader, public ITrackDatabaseObserver
{
    friend class SuiteShuffler;
public:
    Shuffler(Environment& aEnv, ITrackDatabaseReader& aReader);
    ~Shuffler();
    TBool Enabled() const;
    void SetShuffle(TBool aShuffle);
    void Reshuffle();
    TBool TryMoveToStart(TUint aId); // moves aId to follow iPrevTrackId iff Enabled()
private: // from ITrackDatabaseReader
    void SetObserver(ITrackDatabaseObserver& aObserver) override;
    Media::Track* TrackRef(TUint aId) override;
    Media::Track* NextTrackRef(TUint aId) override;
    Media::Track* PrevTrackRef(TUint aId) override;
    Media::Track* TrackRefByIndex(TUint aIndex) override;
    Media::Track* TrackRefByIndexSorted(TUint aIndex) override;
    TBool IsValid(TUint aId) const override;
private: // from ITrackDatabaseObserver
    void NotifyTrackInserted(Media::Track& aTrack, TUint aIdBefore, TUint aIdAfter) override;
    void NotifyTrackDeleted(TUint aId, Media::Track* aBefore, Media::Track* aAfter) override;
    void NotifyAllDeleted() override;
private:
    void DoReshuffle(const TChar* aLogPrefix);
    void MoveToStartOfUnplayed(Media::Track* aTrack, const TChar* aLogPrefix);
    void LogIds(const TChar* aPrefix);
private:
    mutable Mutex iLock;
    Environment& iEnv;
    ITrackDatabaseReader& iReader;
    ITrackDatabaseObserver* iObserver;
    std::vector<Media::Track*> iShuffleList;
    TUint iPrevTrackId;
    TBool iShuffle;
};

class Repeater : public IRepeater, public ITrackDatabaseReader, public ITrackDatabaseObserver
{
public:
    Repeater(ITrackDatabaseReader& aReader);
private: // from IRepeater
    void SetRepeat(TBool aRepeat) override;
private: // from ITrackDatabaseReader
    void SetObserver(ITrackDatabaseObserver& aObserver) override;
    Media::Track* TrackRef(TUint aId) override;
    Media::Track* NextTrackRef(TUint aId) override;
    Media::Track* PrevTrackRef(TUint aId) override;
    Media::Track* TrackRefByIndex(TUint aIndex) override;
    Media::Track* TrackRefByIndexSorted(TUint aIndex) override;
    TBool IsValid(TUint aId) const override;
private: // from ITrackDatabaseObserver
    void NotifyTrackInserted(Media::Track& aTrack, TUint aIdBefore, TUint aIdAfter) override;
    void NotifyTrackDeleted(TUint aId, Media::Track* aBefore, Media::Track* aAfter) override;
    void NotifyAllDeleted() override;
private:
    Mutex iLock;
    ITrackDatabaseReader& iReader;
    ITrackDatabaseObserver* iObserver;
    TBool iRepeat;
    TUint iTrackCount;
};

class TrackListUtils
{
public:
    static TUint IndexFromId(const std::vector<Media::Track*>& aList, TUint aId);
    static void Clear(std::vector<Media::Track*>& aList);
};

} // namespace Av
} // namespace OpenHome

