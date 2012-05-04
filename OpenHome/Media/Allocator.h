#ifndef HEADER_ALLOCATOR
#define HEADER_ALLOCATOR

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>

EXCEPTION(AllocatorNoMemory); // heaps are expected to be setup to avoid this.  Any instance of this exception indicates a system design error.

namespace OpenHome {
namespace Media {

class Allocator : private Av::IInfoProvider
{
    static const Brn kQueryMemory;
    static const TUint8 kByteUninitialised = 0xcc;
    static const TUint kByteFreed = 0xde;
    friend class SuiteAllocator; // test code
public:
    Allocator(const TChar* aName, TUint aCellSizeBytes, TUint aNumCells, Av::IInfoAggregator& aInfoAggregator);
    ~Allocator();
    TAny* Alloc();
    static void Free(TAny* aCell);
    TUint CellSizeBytes() const;
private:
    class Cell
    {
    public:
        TUint8* Ptr() const { return ((TUint8*)this) + sizeof(Cell); }
        TUint Bytes() const { return (iAllocator->CellSizeBytes()); }
        static Cell* PtrToCell(TAny* aPtr) { return (Cell*)(((TUint8*)aPtr) - sizeof(Cell)); }
    public:
        Cell* iNext;
        Cell* iPrev;
        Allocator* iAllocator;
    };
private:
    void DoFree(Cell* aCell);
private: // from Av::IInfoProvider
    void QueryInfo(const Brx& aQuery, IWriter& aWriter);
private:
    const TChar* iName;
    Mutex iLock;
    TUint iNumCells;
    TUint iCellBytes;
    TUint iCellBytesTotal;
    TByte* iCells;
    Cell* iUsed;
    Cell* iFree;
    TUint iCellsUsed;
    TUint iCellsUsedMax;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_ALLOCATOR
