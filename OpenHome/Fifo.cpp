#include <OpenHome/Private/Fifo.h>

using namespace OpenHome;

// FifoBase

FifoBase::FifoBase(TUint aSlots)
    : iSlots(aSlots)
    , iSlotsUsed(0)
    , iMutexWrite("FIMW")
    , iMutexRead("FIMR")
    , iMutexInterrupt("FIMI")
    , iSemaRead("FISR", 0)
    , iSemaWrite("FISW", aSlots)
    , iReadIndex(0)
    , iWriteIndex(0)
    , iInterrupted(false)
    , iInterruptEnabled(false)
{
    ASSERT(iSlots > 0);
}

TUint FifoBase::Slots() const
{
    return iSlots;
}

TUint FifoBase::SlotsFree() const
{
    return iSlots - SlotsUsed();
}

TUint FifoBase::SlotsUsed() const
{
    AutoMutex a(iMutexWrite);
    return iSlotsUsed;
}

void FifoBase::ReadInterrupt(TBool aInterrupt)
{
    // An interrupt should ALWAYS be signalled, as this allows distinguishing
    // between when iSemaRead.Signal() was called normally or by interrupt,
    // even in the case of ReadInterrupt(false) being subsequently called.
    AutoMutex a(iMutexInterrupt);
    if (!iInterrupted) { // don't repeat when interrupt already pending
        iSemaRead.Signal();
        iInterrupted = true;
    }
    // This extra flag lets us know whether we should take any special
    // action (i.e., throw) after an interrupt caused iSemaRead.Signal(), or
    // just go back and try read again.
    iInterruptEnabled = aInterrupt;
}

TUint FifoBase::WriteOpen(TUint aTimeoutMs)
{
    iSemaWrite.Wait(aTimeoutMs);
    iMutexWrite.Wait();
    TUint index = iWriteIndex++;
    if (iWriteIndex == Slots()) {
        iWriteIndex = 0;
    }
    return (index);
}

void FifoBase::WriteClose()
{
    iSlotsUsed++;
    iMutexWrite.Signal();
    iSemaRead.Signal();
}

TUint FifoBase::ReadOpen(TUint aTimeoutMs)
{
    TBool readAllowed = false;
    while (!readAllowed) {  // handle multiple (erroneous) calls to ReadInterrupt(false) when Read() waiting
        iSemaRead.Wait(aTimeoutMs);
        // check if iSemaRead was signalled legitimately or by interrupt
        AutoMutex a(iMutexInterrupt);
        if (iInterrupted) {
            iInterrupted = false;
            if (iInterruptEnabled) {
                iInterruptEnabled = false;
                THROW(FifoReadError);
            }
        }
        else {
            readAllowed = true;
        }
    }
    iMutexRead.Wait();
    TUint index = iReadIndex++;
    if(iReadIndex == Slots()) {
        iReadIndex = 0;
    }
    iMutexRead.Signal();
    return (index);
}

void FifoBase::ReadClose()
{
    iMutexWrite.Wait();
    iSlotsUsed--;
    iMutexWrite.Signal();
    iSemaWrite.Signal();
}

TUint FifoBase::DoPeek()
{
    return iReadIndex;
}

// FifoByte

FifoByte::FifoByte(TUint aSlots) : Fifo<TByte>(aSlots)
{
}

void FifoByte::Write(const Brx& aBuffer)
{
    for (TUint i = 0; i < aBuffer.Bytes(); i++) {
        Fifo<TByte>::Write(aBuffer.At(i));
    }
}

void FifoByte::Read(Bwx& aBuffer)
{
    Read(aBuffer, aBuffer.MaxBytes());
}

void FifoByte::Read(Bwx& aBuffer, TUint aBytes)
{
    aBuffer.SetBytes(0);
    for (TUint i = 0; i < aBytes; i++) {
        aBuffer.Append(Fifo<TByte>::Read());
    }
}

// FifoLiteBase

FifoLiteBase::FifoLiteBase(TUint aSlots) : iSlots(aSlots), iSlotsUsed(0),
    iReadIndex(0), iWriteIndex(0)
{
}

TUint FifoLiteBase::Slots() const
{
    return iSlots;
}

TUint FifoLiteBase::SlotsFree() const
{
    return iSlots - iSlotsUsed;
}

TUint FifoLiteBase::SlotsUsed() const
{
    return iSlotsUsed;
}

TUint FifoLiteBase::Write()
{
    ASSERT(iSlots > iSlotsUsed);
    TUint index = iWriteIndex++;
    if(iWriteIndex == iSlots) {
        iWriteIndex = 0;
    }
    iSlotsUsed++;
    return (index);
}

TUint FifoLiteBase::WriteBack()
{
    ASSERT(iSlots > iSlotsUsed);
    if(iReadIndex == 0) {
        iReadIndex = iSlots - 1;;
    }
    else {
        iReadIndex--;
    }
    iSlotsUsed++;
    return (iReadIndex);
}

TUint FifoLiteBase::Read()
{
    ASSERT(iSlotsUsed > 0);
    TUint index = iReadIndex++;
    if(iReadIndex == iSlots) {
        iReadIndex = 0;
    }
    iSlotsUsed--;
    return index;
}
