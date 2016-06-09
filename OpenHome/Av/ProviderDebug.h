#pragma once

#include <OpenHome/Types.h>
#include <Generated/DvAvOpenhomeOrgDebug1.h>
#include <OpenHome/Optional.h>

namespace OpenHome {
    class RingBufferLogger;
namespace Av {
    class ILogPoster;

class ProviderDebug : public Net::DvProviderAvOpenhomeOrgDebug1
{
public:
    ProviderDebug(Net::DvDevice& aDevice, RingBufferLogger& aLogger, Optional<ILogPoster> aLogPoster);
private: // from DvProviderAvOpenhomeOrgDebug1
    void GetLog(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aLog) override;
    void SendLog(Net::IDvInvocation& aInvocation, const Brx& aData) override;
private:
    RingBufferLogger& iLogger;
    Optional<ILogPoster> iLogPoster;
};

} // namespace Av
} // namespace OpenHome
