#ifndef HEADER_FIFO
#define HEADER_FIFO

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Exception.h>

EXCEPTION(FifoReadError)

namespace OpenHome {

// Fifo provides fully thread-aware first in first out buffering
//
// Writer threads are blocked while the fifo is full
// Reader threads are blocked while the fifo is empty

class FifoBase : public INonCopyable
{
public:
    TUint Slots() const;
    TUint SlotsFree() const;
    TUint SlotsUsed() const;
    void ReadInterrupt(TBool aInterrupt=true);
protected:
    FifoBase(TUint aSlots);
    TUint WriteOpen(); // return index of entry to write
    void WriteClose(); // complete the write
    TUint ReadOpen();  // return index of entry to read
    void ReadClose();  // complete the read
protected:
    const TUint iSlots;
    TUint iSlotsUsed;  // protected by iMutexWrite
    mutable Mutex iMutexWrite;
    Mutex iMutexRead;
    Mutex iMutexInterrupt;
    Semaphore iSemaRead;
    Semaphore iSemaWrite;
    TUint iReadIndex;
    TUint iWriteIndex;
    TBool iInterrupted;
    TBool iInterruptEnabled;
};

template <class T> class Fifo : public FifoBase
{
public:
    inline Fifo(TUint aSlots) : FifoBase(aSlots) { iBuf = new T[aSlots]; }
    inline ~Fifo() { delete [] iBuf; }
    void Write(T aEntry);
    T Read();
private:
    T* iBuf;
};

template <class T> void Fifo<T>::Write(T aEntry)
{
    iBuf[WriteOpen()] = aEntry;
    WriteClose();
}

template <class T> T Fifo<T>::Read()
{
    T value = iBuf[ReadOpen()];
    ReadClose();
    return value;
}


// FifoLite provides lightweight thread unaware first in first out buffering
//
// Writes assert if the fifo is full (use SlotsFree() to check before writing)
// Reads from an empty fifo assert (use SlotsUsed() to check before reading)
 
class FifoLiteBase : public INonCopyable
{
public:
    TUint Slots() const;
    TUint SlotsFree() const;
    TUint SlotsUsed() const;
protected:
    FifoLiteBase(TUint aSlots);
    TUint Write();          // return index of entry to write
    TUint Read();           // return index of entry to read
private:
    TUint iSlots;
    TUint iSlotsUsed;
    TUint iReadIndex; 
    TUint iWriteIndex;
};

template <class T, TUint S> class FifoLite : public FifoLiteBase 
{
public:
    inline FifoLite() : FifoLiteBase(S) {}
    inline void Write(T aEntry) { iBuf[FifoLiteBase::Write()] = aEntry; }
    inline T Read() { return (iBuf[FifoLiteBase::Read()]); }
private:
    T iBuf[S];
};

template <class T> class FifoLiteDynamic : public FifoLiteBase
{
public:
    inline FifoLiteDynamic(TUint aSlots) : FifoLiteBase(aSlots) { iBuf = new T[aSlots]; }
    inline ~FifoLiteDynamic() { delete [] iBuf; }
    inline void Write(T aEntry) { iBuf[FifoLiteBase::Write()] = aEntry; }
    inline T Read() { return (iBuf[FifoLiteBase::Read()]); }
private:
    T* iBuf;
};

} // namespace OpenHome

#endif //HEADER_FIFO
