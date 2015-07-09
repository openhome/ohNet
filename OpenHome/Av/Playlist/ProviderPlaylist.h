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


class ProviderPlaylist : public Net::DvProviderAvOpenhomeOrgPlaylist1, private ITrackDatabaseObserver
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
private: // from Net::DvProviderAvOpenhomeOrgPlaylist1
    void Play(Net::IDvInvocation& aInvocation) override;
    void Pause(Net::IDvInvocation& aInvocation) override;
    void Stop(Net::IDvInvocation& aInvocation) override;
    void Next(Net::IDvInvocation& aInvocation) override;
    void Previous(Net::IDvInvocation& aInvocation) override;
    void SetRepeat(Net::IDvInvocation& aInvocation, TBool aValue) override;
    void Repeat(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aValue) override;
    void SetShuffle(Net::IDvInvocation& aInvocation, TBool aValue) override;
    void Shuffle(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aValue) override;
    void SeekSecondAbsolute(Net::IDvInvocation& aInvocation, TUint aValue) override;
    void SeekSecondRelative(Net::IDvInvocation& aInvocation, TInt aValue) override;
    void SeekId(Net::IDvInvocation& aInvocation, TUint aValue) override;
    void SeekIndex(Net::IDvInvocation& aInvocation, TUint aValue) override;
    void TransportState(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
    void Id(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue) override;
    void Read(Net::IDvInvocation& aInvocation, TUint aId, Net::IDvInvocationResponseString& aUri, Net::IDvInvocationResponseString& aMetadata) override;
    void ReadList(Net::IDvInvocation& aInvocation, const Brx& aIdList, Net::IDvInvocationResponseString& aTrackList) override;
    void Insert(Net::IDvInvocation& aInvocation, TUint aAfterId, const Brx& aUri, const Brx& aMetadata, Net::IDvInvocationResponseUint& aNewId) override;
    void DeleteId(Net::IDvInvocation& aInvocation, TUint aValue) override;
    void DeleteAll(Net::IDvInvocation& aInvocation) override;
    void TracksMax(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue) override;
    void IdArray(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aToken, Net::IDvInvocationResponseBinary& aArray) override;
    void IdArrayChanged(Net::IDvInvocation& aInvocation, TUint aToken, Net::IDvInvocationResponseBool& aValue) override;
    void ProtocolInfo(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
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
