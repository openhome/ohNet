#ifndef HEADER_TESTPROTOCOL
#define HEADER_TESTPROTOCOL

#include <OpenHome/Media/Pipeline/Pipeline.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/PowerManager.h>

namespace OpenHome {
namespace Net {
    class DvStack;
}
namespace Av {
    class OhmMsgFactory;
}
namespace Media {
class ProtocolManager;
class DriverBasic;

class DummyFiller : public Thread, private IPipelineIdProvider
{
public:
    DummyFiller(Environment& aEnv, Pipeline& aPipeline, IFlushIdProvider& aFlushIdProvider, IInfoAggregator& aInfoAggregator, IPowerManager& aPowerManager);
    ~DummyFiller();
    void Start(const Brx& aUrl);
private: // from Thread
    void Run() override;
private: // from IPipelineIdProvider
    TUint NextStreamId() override;
    EStreamPlay OkToPlay(TUint aStreamId) override;
private:
    Pipeline& iPipeline;
    ProtocolManager* iProtocolManager;
    TrackFactory* iTrackFactory;
    Brn iUrl;
    TUint iNextStreamId;
    static const TUint kInvalidPipelineId = 0;
};

class TestProtocol : private IPipelineObserver, private IStreamPlayObserver, private ISeekRestreamer
{
    static const TUint kSeekStepSeconds = 10;
public:
    TestProtocol(Environment& aEnv, Net::DvStack& aDvStack, const Brx& aUrl, const Brx& aSenderUdn, TUint aSenderChannel);
    virtual ~TestProtocol();
    int Run();
protected:
    virtual void RegisterPlugins();
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack(Track& aTrack, const Brx& aMode);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private: // from IStreamPlayObserver
    void NotifyTrackFailed(TUint aTrackId);
    void NotifyStreamPlayStatus(TUint aTrackId, TUint aStreamId, EStreamPlay aStatus);
private: // from ISeekRestreamer
    TUint SeekRestream(const Brx& aMode, TUint aTrackId);
protected:
    Pipeline* iPipeline;
private:
    PowerManager iPowerManager;
    DummyFiller* iFiller;
    AllocatorInfoLogger iInfoAggregator;
    DriverBasic* iDriver; /* DriverSongcastSender allows us to listen to audio
                             but we'd prefer not to depend on the Av namespace */
    Brh iUrl;
    TUint iSeconds;
    TUint iTrackDurationSeconds;
    TUint iStreamId;
};

typedef TestProtocol* (*CreateProtocolFunc)(Environment& aEnv, Net::DvStack& aDvStack, const Brx& aUrl, const Brx& aSenderUdn, TUint aSenderChannel);
int ExecuteTestProtocol(int aArgc, char* aArgv[], CreateProtocolFunc aFunc);

} // namespace Media
} // namespace OpenHome

#endif // HEADER_TESTPROTOCOL
