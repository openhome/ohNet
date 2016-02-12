#pragma once

#include <Generated/DvAvOpenhomeOrgDebug1.h>

namespace OpenHome {
    class RingBufferLogger;
namespace Av {

class ProviderDebug : public Net::DvProviderAvOpenhomeOrgDebug1
{
public:
    ProviderDebug(Net::DvDevice& aDevice, RingBufferLogger& aLogger);
private: // from DvProviderAvOpenhomeOrgDebug1
    void GetLog(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aLog) override;
private:
    RingBufferLogger& iLogger;
};

} // namespace Av
}  // namespace OpenHome
