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
                                           Configuration::IConfigManager& aConfigManager,
                                           IConfigAppResourceHandlerFactory& aResourceFactory,
                                           const std::vector<const Brx*>& aSources,
                                           const Brx& aResourcePrefix, const Brx& aResourceDir,
                                           TUint aMaxTabs, TUint aSendQueueSize, IRebootHandler& aRebootHandler)
                                           : ConfigAppSources(aInfoAggregator, aConfigManager, aResourceFactory, aSources, aResourcePrefix, aResourceDir, aMaxTabs, aSendQueueSize, aRebootHandler)
{
    AddNumConditional(Brn("Sender.Channel"));
    AddNumConditional(Brn("Sender.Preset"));
    AddNumConditional(VolumeConfig::kKeyBalance);
    AddNumConditional(VolumeConfig::kKeyLimit);
    AddNumConditional(VolumeConfig::kKeyStartupValue);

    AddChoiceConditional(Brn("Sender.Enabled"));
    AddChoiceConditional(Brn("Sender.Mode"));
    AddChoiceConditional(Brn("Source.NetAux.Auto"));
    AddChoiceConditional(Av::VolumeConfig::kKeyStartupEnabled);
    AddChoiceConditional(Brn("qobuz.com.AudioQuality"));
    AddChoiceConditional(Brn("tidalhifi.com.SoundQuality"));

    AddTextConditional(Brn("Radio.TuneInUserName"));
}

void ConfigAppMediaPlayer::AddNumConditional(const Brx& aKey, TBool aRebootRequired)
{
    if (iConfigManager.HasNum(aKey)) {
        AddConfigNum(aKey, aRebootRequired);
    }
}

void ConfigAppMediaPlayer::AddChoiceConditional(const Brx& aKey, TBool aRebootRequired)
{
    if (iConfigManager.HasChoice(aKey)) {
        AddConfigChoice(aKey, aRebootRequired);
    }
}

void ConfigAppMediaPlayer::AddTextConditional(const Brx& aKey, TBool aRebootRequired)
{
    if (iConfigManager.HasText(aKey)) {
        AddConfigText(aKey, aRebootRequired);
    }
}
