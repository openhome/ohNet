#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Web/ConfigUi/ConfigUi.h>

#include <vector>

namespace OpenHome {
    class IInfoAggregator;
namespace Av {
    class IRebootHandler;
}
namespace Configuration {
    class IConfigManager;
}
namespace Web {

class ConfigAppMediaPlayer : public ConfigAppSources
{
public:
    ConfigAppMediaPlayer(IInfoAggregator& aInfoAggregator,
                         Environment& aEnv,
                         Av::Product& aProduct,
                         Configuration::IConfigManager& aConfigManager,
                         IConfigAppResourceHandlerFactory& aResourceFactory,
                         const std::vector<const Brx*>& aSources,
                         const Brx& aResourcePrefix, const OpenHome::Brx& aResourceDir,
                         TUint aResourceHandlerCount, TUint aMaxTabs, TUint aSendQueueSize, Av::IRebootHandler& aRebootHandler);
};

} // namespace Web
} // namespace OpenHome
