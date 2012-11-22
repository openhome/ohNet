#include <OpenHome/Media/DecodedAudioReservoir.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DecodedAudioReservoir

DecodedAudioReservoir::DecodedAudioReservoir(TUint aMaxSize)
    : iMaxSize(aMaxSize)
    , iLock("ARES")
    , iSem("ARES", 0)
{
}

DecodedAudioReservoir::~DecodedAudioReservoir()
{
}

Msg* DecodedAudioReservoir::Pull()
{
    Msg* msg;
    do {
        iLock.Wait();
        TUint sizeBefore = Jiffies();
        iLock.Signal();
        msg = DoDequeue();
        iLock.Wait();
        TUint sizeAfter = Jiffies();
        if (sizeBefore >= iMaxSize && sizeAfter < iMaxSize) {
            iSem.Signal();
        }
        iLock.Signal();
    } while (msg == NULL);
    return msg;
}

void DecodedAudioReservoir::Push(Msg* aMsg)
{
    (void)Enqueue(aMsg);
}

TBool DecodedAudioReservoir::Enqueue(Msg* aMsg)
{
    // Queue the next msg before checking how much data we already have in the buffer
    // This risks us going over the nominal max size for the buffer but guarantees that
    // we don't deadlock if a single message larger than iMaxSize is queued.

    DoEnqueue(aMsg);
    iLock.Wait();
    const TBool full = (Jiffies() >= iMaxSize);
    iLock.Signal();
    if (full) {
        iSem.Wait();
    }
    return full;
}
