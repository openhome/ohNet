#ifndef HEADER_CONFIG_INITIALISER_VOLUME
#define HEADER_CONFIG_INITIALISER_VOLUME

#include <OpenHome/Configuration/ConfigManager.h>

namespace OpenHome {

namespace Media {
    class IVolumeProfile;
}

namespace Av {

/**
 * Class that instantiates ConfigVals that will later be retrieved and used by
 * ProviderVolume.
 *
 * Must outlive ProviderVolume, and any other class that wishes to use volume-
 * related ConfigVals.
 */
class ConfigInitialiserVolume
{
public:
    static const TUint kVolumeStartupDefault = 0;
    static const TBool kMuteStartupDefault = false;
public:
    static const Brn kBalance;
    static const Brn kVolumeLimit;
    static const Brn kVolumeStartup;
    static const Brn kVolumeStartupEnabled;
public:
    ConfigInitialiserVolume(Configuration::IConfigInitialiser& aConfigInit, const Media::IVolumeProfile& aProfile);
    ~ConfigInitialiserVolume();
private:
    Configuration::ConfigNum* iBalance;
    Configuration::ConfigNum* iVolumeLimit;
    Configuration::ConfigNum* iVolumeStartup;
    Configuration::ConfigChoice* iVolumeStartupEnabled;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_CONFIG_INITIALISER_VOLUME