#pragma once

#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Types.h>

namespace OpenHome {
namespace Media {

class IPullableClock;

class ClockPullerManual : private Net::IShellCommandHandler
{
    static const TUint kSupportedMsgTypes;
    static const TChar kShellCommand[];
public:
    ClockPullerManual(IPullableClock& aPullableClock, Net::IShell& aShell);
    ~ClockPullerManual();
private: // from Net::IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse) override;
    void DisplayHelp(IWriter& aResponse) override;
private:
    IPullableClock& iPullableClock;
    Net::IShell& iShell;
};

} // namespace Media
} // namespace OpenHome
