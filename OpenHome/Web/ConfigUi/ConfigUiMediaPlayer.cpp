#include <OpenHome/Web/ConfigUi/ConfigUiMediaPlayer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Web/ConfigUi/ConfigUi.h>
#include <OpenHome/Web/ConfigUi/FileResourceHandler.h>
#include <OpenHome/Av/VolumeManager.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Av/RebootHandler.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Web;


ConfigAppMediaPlayer::ConfigAppMediaPlayer(Media::IInfoAggregator& aInfoAggregator,
                                           Environment& aEnv,
                                           Product& aProduct,
                                           Configuration::IConfigManager& aConfigManager,
                                           IConfigAppResourceHandlerFactory& aResourceFactory,
                                           const std::vector<const Brx*>& aSources,
                                           const Brx& aResourcePrefix, const Brx& aResourceDir,
                                           TUint aMaxTabs, TUint aSendQueueSize, IRebootHandler& aRebootHandler)
                                           : ConfigAppSources(aInfoAggregator, aConfigManager, aResourceFactory, aSources, aResourcePrefix, aResourceDir, aMaxTabs, aSendQueueSize, aRebootHandler)
{
    AddValue(new ConfigUiValRoManufacturerName(aProduct));
    AddValue(new ConfigUiValRoModelName(aProduct));
    AddValue(new ConfigUiValRoIpAddress(aEnv.NetworkAdapterList()));

    AddConfigNumConditional(Brn("Sender.Channel"));
    AddConfigNumConditional(Brn("Sender.Preset"));
    AddConfigNumConditional(VolumeConfig::kKeyBalance);
    AddConfigNumConditional(VolumeConfig::kKeyLimit);
    AddConfigNumConditional(VolumeConfig::kKeyStartupValue);

    AddConfigChoiceConditional(Brn("Sender.Enabled"));
    AddConfigChoiceConditional(Brn("Sender.Mode"));
    AddConfigChoiceConditional(Brn("Source.NetAux.Auto"));
    AddConfigChoiceConditional(Av::VolumeConfig::kKeyStartupEnabled);
    AddConfigChoiceConditional(Brn("qobuz.com.AudioQuality"));
    AddConfigChoiceConditional(Brn("tidalhifi.com.SoundQuality"));

    AddConfigTextConditional(Brn("Radio.TuneInUserName"));
}
