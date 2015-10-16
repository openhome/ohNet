#pragma once

#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Types.h>

namespace OpenHome {
namespace Media {

/*
    Element which accepts a "clock_pull" command via Shell to manually test clock pulling.
    Note that this only works for modes which don't support clock pulling (e.g. Playlist).
*/

class ClockPullerManual : public PipelineElement
                        , public IPipelineElementUpstream
                        , private Net::IShellCommandHandler
{
    static const TUint kSupportedMsgTypes;
    static const TChar kShellCommand[];
public:
    ClockPullerManual(IPipelineElementUpstream& aUpstream, Net::IShell& aShell);
    ~ClockPullerManual();
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from PipelineElement
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
private:
    void ProcessAudio(MsgAudio* aAudio);
private: // from Net::IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse) override;
    void DisplayHelp(IWriter& aResponse) override;
private:
    Mutex iLock;
    IPipelineElementUpstream& iUpstream;
    Net::IShell& iShell;
    TBool iEnabled;
    TUint iMultiplier;
};

} // namespace Media
} // namespace OpenHome
