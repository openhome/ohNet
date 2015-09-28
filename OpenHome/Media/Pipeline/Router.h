#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

class Router : public IPipelineElementUpstream, private INonCopyable
{
public:
    Router(IPipelineElementUpstream& aUpstream);
    IPipelineElementUpstream& InsertElements(IPipelineElementUpstream& aTail);
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private:
    IPipelineElementUpstream& iUpstream;
    IPipelineElementUpstream* iBranch;
};

} // namespace Media
} // namespace OpenHome

