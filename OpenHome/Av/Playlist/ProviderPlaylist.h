#ifndef HEADER_PROVIDER_PLAYLIST
#define HEADER_PROVIDER_PLAYLIST

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <Generated/DvAvOpenhomeOrgPlaylist1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Av/Playlist/TrackDatabase.h>

#include <array>

namespace OpenHome {
using namespace Net;
    class Environment;
    class Timer;
namespace Av {

class ISourcePlaylist
{
public:
    virtual ~ISourcePlaylist() {}
    virtual void Play() = 0;
    virtual void Pause() = 0;
    virtual void Stop() = 0;
    virtual void Next() = 0;
    virtual void Prev() = 0;
    virtual void SeekAbsolute(TUint aSeconds) = 0;
    virtual void SeekRelative(TInt aSeconds) = 0;
    virtual void SeekToTrackId(TUint aId) = 0;
    virtual TBool SeekToTrackIndex(TUint aIndex) = 0;
    virtual void SetShuffle(TBool aShuffle) = 0;
};


class ProviderPlaylist : public DvProviderAvOpenhomeOrgPlaylist1, private ITrackDatabaseObserver
{
    static const TUint kIdArrayUpdateFrequencyMillisecs = 300;
public:
    ProviderPlaylist(Net::DvDevice& aDevice, Environment& aEnv, ISourcePlaylist& aSource, ITrackDatabase& aDatabase, IRepeater& aRepeater, const Brx& aProtocolInfo);
    ~ProviderPlaylist();
    void NotifyPipelineState(Media::EPipelineState aState);
    void NotifyTrack(TUint aId);
private: // from ITrackDatabaseObserver
    void NotifyTrackInserted(Media::Track& aTrack, TUint aIdBefore, TUint aIdAfter) override;
    void NotifyTrackDeleted(TUint aId, Media::Track* aBefore, Media::Track* aAfter) override;
    void NotifyAllDeleted() override;
private: // from DvProviderAvOpenhomeOrgPlaylist1
    void Play(IDvInvocation& aInvocation) override;
    void Pause(IDvInvocation& aInvocation) override;
    void Stop(IDvInvocation& aInvocation) override;
    void Next(IDvInvocation& aInvocation) override;
    void Previous(IDvInvocation& aInvocation) override;
    void SetRepeat(IDvInvocation& aInvocation, TBool aValue) override;
    void Repeat(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue) override;
    void SetShuffle(IDvInvocation& aInvocation, TBool aValue) override;
    void Shuffle(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue) override;
    void SeekSecondAbsolute(IDvInvocation& aInvocation, TUint aValue) override;
    void SeekSecondRelative(IDvInvocation& aInvocation, TInt aValue) override;
    void SeekId(IDvInvocation& aInvocation, TUint aValue) override;
    void SeekIndex(IDvInvocation& aInvocation, TUint aValue) override;
    void TransportState(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue) override;
    void Id(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue) override;
    void Read(IDvInvocation& aInvocation, TUint aId, IDvInvocationResponseString& aUri, IDvInvocationResponseString& aMetadata) override;
    void ReadList(IDvInvocation& aInvocation, const Brx& aIdList, IDvInvocationResponseString& aTrackList) override;
    void Insert(IDvInvocation& aInvocation, TUint aAfterId, const Brx& aUri, const Brx& aMetadata, IDvInvocationResponseUint& aNewId) override;
    void DeleteId(IDvInvocation& aInvocation, TUint aValue) override;
    void DeleteAll(IDvInvocation& aInvocation) override;
    void TracksMax(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue) override;
    void IdArray(IDvInvocation& aInvocation, IDvInvocationResponseUint& aToken, IDvInvocationResponseBinary& aArray) override;
    void IdArrayChanged(IDvInvocation& aInvocation, TUint aToken, IDvInvocationResponseBool& aValue) override;
    void ProtocolInfo(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue) override;
private:
    void TrackDatabaseChanged();
    void SetRepeat(TBool aRepeat);
    void SetShuffle(TBool aShuffle);
    void UpdateIdArray();
    void UpdateIdArrayProperty();
    void TimerCallback();
private:
    Mutex iLock;
    ISourcePlaylist& iSource;
    ITrackDatabase& iDatabase;
    IRepeater& iRepeater;
    Brn iProtocolInfo;
    Media::EPipelineState iPipelineState;
    TUint iDbSeq;
    std::array<TUint, ITrackDatabase::kMaxTracks> iIdArray;
    Bws<ITrackDatabase::kMaxTracks * sizeof(TUint32)> iIdArrayBuf;
    Timer* iTimer;
    Mutex iTimerLock;
    TBool iTimerActive;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_PLAYLIST
