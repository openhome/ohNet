#include <OpenHome/Media/Pipeline/AudioReservoir.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// AudioReservoir

AudioReservoir::AudioReservoir()
    : iLock("ARES")
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
        UnblockIfNotFull();
    } while (msg == nullptr);
    return msg;
}

void AudioReservoir::Push(Msg* aMsg)
{
    DoEnqueue(aMsg);
}

void AudioReservoir::BlockIfFull()
{
    iLock.Wait();
    const TBool full = IsFull();
    (void)iSem.Clear();
    iLock.Signal();
    if (full) {
        HandleBlocked();
        iSem.Wait();
    }
}

void AudioReservoir::UnblockIfNotFull()
{
    AutoMutex _(iLock);
    if (!IsFull()) {
        iSem.Signal();
    }
}

void AudioReservoir::HandleBlocked()
{
}
