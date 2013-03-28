#ifndef HEADER_FIFO
#define HEADER_FIFO

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Exception.h>

EXCEPTION(FifoReadError);

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
    TUint WriteOpen(TUint aTimeoutMs);// return index of entry to write
    void WriteClose();                // complete the write
    TUint ReadOpen(TUint aTimeoutMs); // return index of entry to read
    void ReadClose();                 // complete the read
    TUint DoPeek();                   // return index of entry without removing it
protected:
    const TUint iSlots;
    TUint iSlotsUsed;                 // protected by iMutexWrite
    mutable Mutex iMutexWrite;
    Mutex iMutexRead;
    Semaphore iSemaRead;
    Semaphore iSemaWrite;
    TUint iReadIndex;
    TUint iWriteIndex;
    TBool iInterrupted;
};

template <class T> class Fifo : public FifoBase
{
public:
    inline Fifo(TUint aSlots) : FifoBase(aSlots) { iBuf = new T[aSlots]; }
    inline ~Fifo() { delete [] iBuf; }
    void Write(T aEntry);
    void Write(T aEntry, TUint aTimeoutMs);
    T Read();
    T Read(TUint aTimeoutMs);
    T Peek();
private:
    T* iBuf;
};

template <class T> void Fifo<T>::Write(T aEntry)
{
    Write(aEntry, 0);
}

template <class T> void Fifo<T>::Write(T aEntry, TUint aTimeoutMs)
{
    iBuf[WriteOpen(aTimeoutMs)] = aEntry;
    WriteClose();
}

template <class T> T Fifo<T>::Read()
{
    return Read(0);
}

template <class T> T Fifo<T>::Read(TUint aTimeoutMs)
{
    T value = iBuf[ReadOpen(aTimeoutMs)];
    ReadClose();
    return (value);
}

template <class T> T Fifo<T>::Peek()
{
    T value = iBuf[DoPeek()];
    return (value);
}

// FifoByte provides a specific TByte Fifo instantiation
// with additional buffer write and read functions

class FifoByte : public Fifo<TByte>
{
public:
    FifoByte(TUint aSlots);
    void Write(const Brx& aBuffer);
    void Read(Bwx& aBuffer);
    void Read(Bwx& aBuffer, TUint aBytes);
};

// FifoThreshold adds low and high threshold monitoring to a standard Fifo object
//
// Thresholds are initially set to 0 (Low) and aSlots (High).

class FifoThresholdBase;
class FifoThresholdObserver
{
public:
    virtual void NotifyThresholdLow(FifoThresholdBase& aFifo) = 0;
    virtual void NotifyThresholdHigh(FifoThresholdBase& aFifo) = 0;
};

class FifoThresholdBase : public FifoBase
{
public:
    void SetThresholdLow(TUint aSlot);
    void SetThresholdHigh(TUint aSlot);
protected:
    FifoThresholdBase(TUint aSlots, FifoThresholdObserver& aObserver);
    void CheckThresholdLow();
    void CheckThresholdHigh();
private:
    FifoThresholdObserver& iObserver;
    TUint iThresholdLow;
    TUint iThresholdHigh;
    TBool iThresholdLowActive;
    TBool iThresholdHighActive;
};

template <class T> class FifoThreshold : public FifoThresholdBase
{
public:
    inline FifoThreshold(TUint aSlots, FifoThresholdObserver& aObserver): FifoThresholdBase(aSlots, aObserver) { iBuf = new T[aSlots]; }
    inline ~FifoThreshold() { delete [] iBuf; }
    void Write(T aEntry);
    T Read();
private:
    T* iBuf;
};

template <class T> void FifoThreshold<T>::Write(T aEntry)
{
    iBuf[WriteOpen()] = aEntry;
    WriteClose();
    CheckThresholdLow();
}

template <class T> T FifoThreshold<T>::Read()
{
    T value = iBuf[ReadOpen(0)];
    ReadClose();
    CheckThresholdHigh();
    return (value);
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
    TUint WriteBack();      // return index of entry to write at rhs of fifo
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
    inline void WriteBack(T aEntry) { iBuf[FifoLiteBase::WriteBack()] = aEntry; }
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
    inline void WriteBack(T aEntry) { iBuf[FifoLiteBase::WriteBack()] = aEntry; }
    inline T Read() { return (iBuf[FifoLiteBase::Read()]); }
private:
    T* iBuf;
};

} // namespace OpenHome

#endif //HEADER_FIFO
