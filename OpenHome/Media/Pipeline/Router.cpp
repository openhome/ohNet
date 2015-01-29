#include <OpenHome/Media/Pipeline/Router.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Router

Router::Router(IPipelineElementUpstream& aUpstream)
    : iUpstream(aUpstream)
    , iBranch(NULL)
{
}

IPipelineElementUpstream& Router::InsertElements(IPipelineElementUpstream& aTail)
{
    iBranch = &aTail;
    return iUpstream;
}

Msg* Router::Pull()
{
    if (iBranch != NULL) {
        return iBranch->Pull();
    }
    return iUpstream.Pull();
}
