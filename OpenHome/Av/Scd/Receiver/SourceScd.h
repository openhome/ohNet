#pragma once

#include <Linn/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Source.h>

namespace OpenHome {
    namespace Av {
        class IMediaPlayer;
    }
}
namespace Scd {

class UriProviderScd;
class ICloudWriteScheduler;
class ICloudMsgConsumable;

class SourceCloud : public Av::Source
{
    static const Brn kSystemName;
    static const TChar* kType;
    static const TBool kDefaultVisibility;
public:
    static Av::ISource* New(Av::IMediaPlayer& aMediaPlayer,
                            ICloudWriteScheduler& aCloudScheduler,
                            ICloudMsgConsumable& aMsgConsumable);
private:
    SourceCloud(Av::IMediaPlayer& aMediaPlayer,
                ICloudWriteScheduler& aCloudScheduler,
                ICloudMsgConsumable& aMsgConsumable);
private: // from ISource
    void Activate(TBool aAutoPlay) override;
    TBool TryActivateNoPrefetch(const Brx& aMode) override;
    void PipelineStopped() override;
    void StandbyEnabled() override;
private:
    UriProviderScd* iUriProvider;
};

} // namespace Linn
