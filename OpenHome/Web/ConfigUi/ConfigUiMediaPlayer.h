#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Web/ConfigUi/ConfigUi.h>

#include <vector>

namespace OpenHome {
namespace Av {
        class IRebootHandler;
    }
namespace Configuration {
    class IConfigManager;
}
namespace Media {
    class IInfoAggregator;
}
namespace Web {

class ConfigAppMediaPlayer : public ConfigAppSources
{
public:
    ConfigAppMediaPlayer(Media::IInfoAggregator& aInfoAggregator,
                         Av::Product& aProduct,
                         Configuration::IConfigManager& aConfigManager,
                         IConfigAppResourceHandlerFactory& aResourceFactory,
                         const std::vector<const Brx*>& aSources,
                         const Brx& aResourcePrefix, const OpenHome::Brx& aResourceDir,
                         TUint aMaxTabs, TUint aSendQueueSize, Av::IRebootHandler& aRebootHandler);
private:
    // Convenience helpers.
    void AddNumConditional(const Brx& aKey, TBool aRebootRequired = false);
    void AddChoiceConditional(const Brx& aKey, TBool aRebootRequired = false);
    void AddTextConditional(const Brx& aKey, TBool aRebootRequired = false);
};

} // namespace Web
} // namespace OpenHome
