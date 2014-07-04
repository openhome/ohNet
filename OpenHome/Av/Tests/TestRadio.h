#ifndef HEADER_TESTRADIO
#define HEADER_TESTRADIO

#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>

namespace OpenHome {
namespace Net {
    class DvStack;
}
namespace Media {
    class UriProviderSingleTrack;
}
namespace Av {
    class PresetDatabase;
    class DriverSongcastSender;

namespace Test {
class TestRadio : private OpenHome::Media::IPipelineObserver
{
    static const TUint kTrackCount = 3;
public:
    TestRadio(Net::DvStack& aDvStack, const Brx& aSenderUdn, TUint aSenderChannel);
    ~TestRadio();
    void Run(PresetDatabase& aDb);
protected:
    virtual void RegisterPlugins(Environment& aEnv);
private: // from Media::IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState);
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo);
protected:
    Media::PipelineManager* iPipeline;
private:
    Environment* iEnv;
    Media::AllocatorInfoLogger iInfoLogger;
    Media::TrackFactory* iTrackFactory;
    DriverSongcastSender* iDriver;
    Media::UriProviderSingleTrack* iUriProvider;
    //DummySourceUpnpAv* iSourceUpnpAv;
};

typedef TestRadio* (*CreateRadioFunc)(Net::DvStack& aDvStack, const Brx& aSenderUdn, TUint aSenderChannel);
int ExecuteTestRadio(int aArgc, char* aArgv[], CreateRadioFunc aFunc, std::vector<const TChar*> aPresets);

} // namespace Test
} // namespace Av
} // namespace OpenHome

#endif // HEADER_TESTRADIO
