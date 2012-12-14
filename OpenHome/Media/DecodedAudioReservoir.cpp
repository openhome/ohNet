#include <OpenHome/Media/DecodedAudioReservoir.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DecodedAudioReservoir

DecodedAudioReservoir::DecodedAudioReservoir(IPipelineElementUpstream& aUpstreamElement, TUint aMaxSize)
    : AudioReservoir(aMaxSize)
    , iUpstreamElement(aUpstreamElement)
    , iQuit(false)
{
    iThread = new ThreadFunctor("STRV", MakeFunctor(*this, &DecodedAudioReservoir::PullerThread), kPriorityNormal); // FIXME - want a priority that's higher that ohNet's threads
    iThread->Start();
}

DecodedAudioReservoir::~DecodedAudioReservoir()
{
    delete iThread;
}

void DecodedAudioReservoir::ProcessMsgIn(MsgQuit* /*aMsg*/)
{
    iQuit = true;
}

void DecodedAudioReservoir::PullerThread()
{
    do {
        Msg* msg = iUpstreamElement.Pull();
        (void)Enqueue(msg);
    } while (!iQuit);
}

TUint DecodedAudioReservoir::Size() const
{
    return Jiffies();
}
