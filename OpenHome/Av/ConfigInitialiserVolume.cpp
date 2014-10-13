#include <OpenHome/Av/ConfigInitialiserVolume.h>

#include <OpenHome/Buffer.h>
#include <OpenHome/Av/StringIds.h>

#include <OpenHome/Media/VolumeManager.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;


// ConfigInitialiserVolume

const Brn ConfigInitialiserVolume::kBalance("Volume.Balance");
const Brn ConfigInitialiserVolume::kVolumeLimit("Volume.Limit");
const Brn ConfigInitialiserVolume::kVolumeStartup("Volume.Startup");
const Brn ConfigInitialiserVolume::kVolumeStartupEnabled("Volume.Startup.Enabled");

ConfigInitialiserVolume::ConfigInitialiserVolume(IConfigInitialiser& aConfigInit, const IVolumeProfile& aProfile)
{
    TInt maxBalance = aProfile.MaxBalance();
    TUint maxVolume = aProfile.MaxVolume();

    iBalance = new ConfigNum(aConfigInit, kBalance, -(maxBalance), maxBalance, 0);
    iVolumeLimit = new ConfigNum(aConfigInit, kVolumeLimit, 0, maxVolume, maxVolume);
    iVolumeStartup = new ConfigNum(aConfigInit, kVolumeStartup, 0, maxVolume, kVolumeStartupDefault);
    std::vector<TUint> choices;
    choices.push_back(eStringIdYes);
    choices.push_back(eStringIdNo);
    iVolumeStartupEnabled = new ConfigChoice(aConfigInit, kVolumeStartupEnabled, choices, eStringIdYes);
}

ConfigInitialiserVolume::~ConfigInitialiserVolume()
{
    delete iVolumeStartupEnabled;
    delete iVolumeStartup;
    delete iVolumeLimit;
    delete iBalance;
}
