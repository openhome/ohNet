#include <OpenHome/Web/ConfigUi/ConfigUiMediaPlayer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Web/ConfigUi/ConfigUi.h>
#include <OpenHome/Web/ConfigUi/FileResourceHandler.h>
#include <OpenHome/Av/VolumeManager.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Web;


ConfigAppMediaPlayer::ConfigAppMediaPlayer(Configuration::IConfigManager& aConfigManager,
                                           IConfigAppResourceHandlerFactory& aResourceFactory,
                                           const std::vector<const Brx*>& aSources,
                                           const Brx& aResourcePrefix, const Brx& aResourceDir,
                                           TUint aMaxTabs, TUint aSendQueueSize)
    : ConfigAppSources(aConfigManager, aResourceFactory, aSources, aResourcePrefix, aResourceDir, aMaxTabs, aSendQueueSize)
{
    JsonKvpVector emptyJsonVector;

    AddNumConditional(Brn("Sender.Channel"), emptyJsonVector);
    AddNumConditional(Brn("Sender.Preset"), emptyJsonVector);
    AddNumConditional(VolumeConfig::kKeyBalance, emptyJsonVector);
    AddNumConditional(VolumeConfig::kKeyLimit, emptyJsonVector);
    AddNumConditional(VolumeConfig::kKeyStartupValue, emptyJsonVector);

    AddChoiceConditional(Brn("Sender.Enabled"), emptyJsonVector);
    AddChoiceConditional(Brn("Sender.Mode"), emptyJsonVector);
    AddChoiceConditional(Brn("Source.NetAux.Auto"), emptyJsonVector);
    AddChoiceConditional(Av::VolumeConfig::kKeyStartupEnabled, emptyJsonVector);
    AddChoiceConditional(Brn("qobuz.com.AudioQuality"), emptyJsonVector);
    AddChoiceConditional(Brn("tidalhifi.com.SoundQuality"), emptyJsonVector);

    AddTextConditional(Brn("Radio.TuneInUserName"), emptyJsonVector);
}

void ConfigAppMediaPlayer::AddNumConditional(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo)
{
    if (iConfigManager.HasNum(aKey)) {
        AddNum(aKey, aAdditionalInfo);
    }
}

void ConfigAppMediaPlayer::AddChoiceConditional(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo)
{
    if (iConfigManager.HasChoice(aKey)) {
        AddChoice(aKey, aAdditionalInfo);
    }
}

void ConfigAppMediaPlayer::AddTextConditional(const OpenHome::Brx& aKey, JsonKvpVector& aAdditionalInfo)
{
    if (iConfigManager.HasText(aKey)) {
        AddText(aKey, aAdditionalInfo);
    }
}
