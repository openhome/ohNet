#include <OpenHome/Web/ConfigUi/ConfigUiMediaPlayer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Web/ConfigUi/ConfigUi.h>
#include <OpenHome/Web/ConfigUi/FileResourceHandler.h>
#include <OpenHome/Av/VolumeManager.h>
#include <OpenHome/Media/InfoProvider.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Web;


ConfigAppMediaPlayer::ConfigAppMediaPlayer(Media::IInfoAggregator& aInfoAggregator,
                                           Configuration::IConfigManager& aConfigManager,
                                           IConfigAppResourceHandlerFactory& aResourceFactory,
                                           const std::vector<const Brx*>& aSources,
                                           const Brx& aResourcePrefix, const Brx& aResourceDir,
                                           TUint aMaxTabs, TUint aSendQueueSize)
    : ConfigAppSources(aInfoAggregator, aConfigManager, aResourceFactory, aSources, aResourcePrefix, aResourceDir, aMaxTabs, aSendQueueSize)
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

void ConfigAppMediaPlayer::AddNumConditional(const OpenHome::Brx& aKey)
{
    if (iConfigManager.HasNum(aKey)) {
        AddNum(aKey);
    }
}

void ConfigAppMediaPlayer::AddChoiceConditional(const OpenHome::Brx& aKey)
{
    if (iConfigManager.HasChoice(aKey)) {
        AddChoice(aKey);
    }
}

void ConfigAppMediaPlayer::AddTextConditional(const OpenHome::Brx& aKey)
{
    if (iConfigManager.HasText(aKey)) {
        AddText(aKey);
    }
}
