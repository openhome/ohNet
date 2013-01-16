#include <OpenHome/Media/AudioReservoir.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// AudioReservoir

AudioReservoir::AudioReservoir(TUint aMaxSize)
    : iMaxSize(aMaxSize)
    , iLock("ARES")
    , iSem("ARES", 0)
{
}

AudioReservoir::~AudioReservoir()
{
}

Msg* AudioReservoir::Pull()
{
    Msg* msg;
    do {
        msg = DoDequeue();
        iLock.Wait();
        if (Size() < iMaxSize) {
            iSem.Signal();
        }
        iLock.Signal();
    } while (msg == NULL);
    return msg;
}

void AudioReservoir::Push(Msg* aMsg)
{
    (void)Enqueue(aMsg);
}

TBool AudioReservoir::Enqueue(Msg* aMsg)
{
    // Queue the next msg before checking how much data we already have in the buffer
    // This risks us going over the nominal max size for the buffer but guarantees that
    // we don't deadlock if a single message larger than iMaxSize is queued.

    DoEnqueue(aMsg);
    iLock.Wait();
    const TBool full = (Size() >= iMaxSize);
    (void)iSem.Clear();
    iLock.Signal();
    if (full) {
        iSem.Wait();
    }
    return full;
}
