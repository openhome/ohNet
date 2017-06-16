#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/Scd/Receiver/UriProviderScd.h>
#include <OpenHome/Av/Scd/Receiver/ProtocolScd.h>
#include <OpenHome/Media/PipelineManager.h>

namespace OpenHome {
namespace Scd {

class SourceScd : public Av::Source
{
    static const TBool kDefaultVisibility;
public:
    SourceScd(Media::PipelineManager& aPipeline,
              IPowerManager& aPowerManager,
              UriProviderScd& aUriProvider);
private: // from ISource
    void Activate(TBool aAutoPlay) override;
    TBool TryActivateNoPrefetch(const Brx& aMode) override;
    void PipelineStopped() override;
    void StandbyEnabled() override;
private:
    UriProviderScd& iUriProvider;
};

} // namespace Scd
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Scd;
using namespace OpenHome::Av;

Av::ISource* Av::SourceFactory::NewScd(Av::IMediaPlayer& aMediaPlayer)
{
    auto& trackFactory = aMediaPlayer.TrackFactory();
    auto protocol = new ProtocolScd(aMediaPlayer.Env(), trackFactory);
    auto& pipeline =  aMediaPlayer.Pipeline();
    pipeline.Add(protocol);
    auto uriProvider = new UriProviderScd(trackFactory);
    aMediaPlayer.Add(uriProvider);
    return new SourceScd(pipeline, aMediaPlayer.PowerManager(), *uriProvider);
}

const Brn Av::SourceFactory::kSourceNameScd("Scd");
const TChar* Av::SourceFactory::kSourceTypeScd = "Scd";
const TBool SourceScd::kDefaultVisibility = false;

SourceScd::SourceScd(Media::PipelineManager& aPipeline,
                     IPowerManager& aPowerManager,
                     UriProviderScd& aUriProvider)
    : Source(Av::SourceFactory::kSourceNameScd,
             Av::SourceFactory::kSourceTypeScd,
             aPipeline,
             aPowerManager,
             kDefaultVisibility)
    , iUriProvider(aUriProvider)
{
}

void SourceScd::Activate(TBool /*aAutoPlay*/)
{
    iUriProvider.Reset();
}

TBool SourceScd::TryActivateNoPrefetch(const Brx& aMode)
{
    if (iUriProvider.Mode() != aMode) {
        return false;
    }
    EnsureActiveNoPrefetch();
    return true;
}

void SourceScd::PipelineStopped()
{
    // Nothing to do here.
}

void SourceScd::StandbyEnabled()
{
    iPipeline.Stop();
}
