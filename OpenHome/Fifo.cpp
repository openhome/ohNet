#include <OpenHome/Private/Fifo.h>

using namespace OpenHome;

// FifoBase

FifoBase::FifoBase(TUint aSlots)
    : iSlots(aSlots)
    , iSlotsUsed(0)
    , iMutexWrite("FIMW")
    , iMutexRead("FIMR")
    , iSemaRead("FISR", 0)
    , iSemaWrite("FISW", aSlots)
    , iReadIndex(0)
    , iWriteIndex(0)
    , iInterrupted(false)
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
    iInterrupted = aInterrupt;
    if (aInterrupt) {
        iSemaRead.Signal();
    }
}

TUint FifoBase::WriteOpen(TUint aTimeoutMs)
{
    iSemaWrite.Wait(aTimeoutMs);
    iMutexWrite.Wait();
    TUint index = iWriteIndex++;
    if(iWriteIndex == Slots()) {
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
    iSemaRead.Wait(aTimeoutMs);
    if (iInterrupted) {
    	iInterrupted = false;
        THROW(FifoReadError);
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

// FifoThresholdBase

FifoThresholdBase::FifoThresholdBase(TUint aSlots, FifoThresholdObserver& aObserver)
    : FifoBase(aSlots)
    , iObserver(aObserver)
    , iThresholdLow(0)
    , iThresholdHigh(aSlots)
    , iThresholdLowActive(false)
    , iThresholdHighActive(false)
{
}

void FifoThresholdBase::SetThresholdLow(TUint aSlot)
{
    ASSERT(aSlot <= Slots());
    iThresholdLow = aSlot;
    CheckThresholdLow();
}

void FifoThresholdBase::SetThresholdHigh(TUint aSlot)
{
    ASSERT(aSlot <= Slots());
    iThresholdHigh = aSlot;
    CheckThresholdHigh();
}

void FifoThresholdBase::CheckThresholdHigh()
{
    if(iThresholdHighActive) {
        if(SlotsUsed() < iThresholdHigh) {
            iThresholdHighActive = false;
        }
    } else if(SlotsUsed() >= iThresholdHigh) {
        iThresholdHighActive = true;
        iObserver.NotifyThresholdHigh(*this);
    }
}

void FifoThresholdBase::CheckThresholdLow()
{
    if(iThresholdLowActive) {
        if(SlotsUsed() > iThresholdLow) {
            iThresholdLowActive = false;
        }
    } else if(SlotsUsed() <= iThresholdLow) {
        iThresholdLowActive = true;
        iObserver.NotifyThresholdLow(*this);
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
