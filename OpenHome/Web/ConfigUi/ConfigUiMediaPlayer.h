#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Web/ConfigUi/ConfigUi.h>

#include <vector>

namespace OpenHome {
namespace Configuration {
    class IConfigManager;
}
namespace Web {

class ConfigAppMediaPlayer : public ConfigAppSources
{
public:
     ConfigAppMediaPlayer(Configuration::IConfigManager& aConfigManager,
                          IConfigAppResourceHandlerFactory& aResourceFactory,
                          const std::vector<const Brx*>& aSources,
                          const Brx& aResourcePrefix, const OpenHome::Brx& aResourceDir,
                          TUint aMaxTabs, TUint aSendQueueSize);
private:
    void AddNumConditional(const Brx& aKey);
    void AddChoiceConditional(const Brx& aKey);
    void AddTextConditional(const Brx& aKey);
};

} // namespace Web
} // namespace OpenHome
