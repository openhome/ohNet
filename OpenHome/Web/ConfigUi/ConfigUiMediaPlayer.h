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
    void AddNumConditional(const Brx& aKey, JsonKvpVector& aAdditionalInfo);
    void AddChoiceConditional(const Brx& aKey, JsonKvpVector& aAdditionalInfo);
    void AddTextConditional(const Brx& aKey, JsonKvpVector& aAdditionalInfo);
};

} // namespace Web
} // namespace OpenHome
