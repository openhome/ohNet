#ifndef HEADER_TESTPROTOCOL
#define HEADER_TESTPROTOCOL

#include <OpenHome/Media/Pipeline.h>
#include <OpenHome/Media/Tests/AllocatorInfoLogger.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Net {
    class DvStack;
}
namespace Av {
    class OhmMsgFactory;
    class DefaultTimestamper;
}
namespace Media {
class ProtocolManager;
class SimpleSongcastingDriver;

class DummyFiller : public Thread, private IPipelineIdProvider
{
public:
    DummyFiller(Environment& aEnv, Pipeline& aPipeline, IFlushIdProvider& aFlushIdProvider, Av::IInfoAggregator& aInfoAggregator);
    ~DummyFiller();
    void Start(const Brx& aUrl);
private: // from Thread
    void Run();
private: // from IPipelineIdProvider
    TUint NextTrackId();
    TUint NextStreamId();
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
private:
    ProtocolManager* iProtocolManager;
    TrackFactory* iTrackFactory;
    Av::OhmMsgFactory* iOhmMsgFactory;
    Av::DefaultTimestamper* iTimestamper;
    Brn iUrl;
    TUint iNextTrackId;
    TUint iNextStreamId;
    static const TUint kInvalidPipelineId = 0;
};

class TestProtocol : private IPipelineObserver
{
    static const TUint kMaxDriverJiffies = Jiffies::kJiffiesPerMs * 5;
    static const TUint kSeekStepSeconds = 10;
public:
    TestProtocol(Environment& aEnv, Net::DvStack& aDvStack, const Brx& aUrl, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel);
    virtual ~TestProtocol();
    int Run();
protected:
    virtual void RegisterPlugins();
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
protected:
    Pipeline* iPipeline;
private:
    DummyFiller* iFiller;
    AllocatorInfoLogger iInfoAggregator;
    SimpleSongcastingDriver* iDriver;
    Brh iUrl;
    TUint iSeconds;
    TUint iTrackDurationSeconds;
    TUint iStreamId;
};

typedef TestProtocol* (*CreateProtocolFunc)(Environment& aEnv, Net::DvStack& aDvStack, const Brx& aUrl, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel);
int ExecuteTestProtocol(int aArgc, char* aArgv[], CreateProtocolFunc aFunc);

} // namespace Media
} // namespace OpenHome

#endif // HEADER_TESTPROTOCOL
