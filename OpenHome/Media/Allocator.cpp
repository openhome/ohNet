#include <OpenHome/Media/Allocator.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Av;

#ifdef DEFINE_TRACE
# define MARK_MEMORY
#else
# undef  MARK_MEMORY
#endif

const Brn Allocator::kQueryMemory = Brn("memory");

Allocator::Allocator(const TChar* aName, TUint aCellSizeBytes, TUint aNumCells, Av::IInfoAggregator& aInfoAggregator)
    : iName(aName)
    , iLock("ALOC")
    , iNumCells(aNumCells)
    , iUsed(NULL)
    , iCellsUsed(0)
    , iCellsUsedMax(0)

{
    iCellBytesTotal = aCellSizeBytes + sizeof(Cell);
    iCellBytesTotal = (iCellBytesTotal + 7) & ~7; // round up to multiple of 8
    iCellBytes = iCellBytesTotal - sizeof(Cell);
    iCells = new TUint8[iCellBytesTotal * iNumCells];
    Cell* cell = (Cell*)iCells;
    Cell* prev = 0;
    for(TUint i=0; i<aNumCells; i++) {
        cell->iNext = (Cell*)((TUint8*)cell + iCellBytesTotal);
        cell->iPrev = prev;
        cell->iAllocator = this;
#ifdef MARK_MEMORY
        memset(cell->Ptr(), kByteUninitialised, iCellBytes);
#endif
        if(i == iNumCells - 1) {
            cell->iNext = NULL;
        } else {
            prev = cell;
            cell = cell->iNext;
        }
    }
    iFree = (Cell*)iCells;

    std::vector<Brn> infoQueries;
    infoQueries.push_back(kQueryMemory);
    aInfoAggregator.Register(*this, infoQueries);
}

Allocator::~Allocator()
{
    ASSERT(iUsed == NULL);
    ASSERT(iCellsUsed == 0);
    delete iCells;
}

TAny* Allocator::Alloc()
{
    iLock.Wait();
    if(iFree == NULL) { // out of memory -- system design error
        iLock.Signal();
        THROW(AllocatorNoMemory);
    }

    Cell* cell = iFree;
    iFree = iFree->iNext;
    if (iFree != NULL) {
        iFree->iPrev = NULL;
    }

    cell->iNext = iUsed;
    ASSERT(cell->iPrev == NULL);
    iUsed = cell;
    iCellsUsed++;
    if(iCellsUsed > iCellsUsedMax) {
    	iCellsUsedMax = iCellsUsed;
    }

    iLock.Signal();

    return cell->Ptr();
}

void Allocator::Free(TAny* aCell)
{ // static 
    Cell* cell = Cell::PtrToCell(aCell);
    cell->iAllocator->DoFree(cell);
}

TUint Allocator::CellSizeBytes() const
{
    return iCellBytes;
}

void Allocator::DoFree(Cell* aCell)
{
    iLock.Wait();
#ifdef MARK_MEMORY
    memset(aCell->Ptr(), kByteFreed, iCellBytes);
#endif
    if(aCell->iPrev) {
        aCell->iPrev->iNext = aCell->iNext;
    } else {
        iUsed = 0;
    }   
    if(aCell->iNext) {
        aCell->iNext->iPrev = aCell->iPrev;
    }

    aCell->iNext = iFree;
    aCell->iPrev = 0;
    iFree = aCell;
    --iCellsUsed;
    iLock.Signal();
}

void Allocator::QueryInfo(const Brx& aQuery, IWriter& aWriter)
{
    if (aQuery == kQueryMemory) {
        aWriter.Write(Brn("Allocator: "));
        aWriter.Write(Brn(iName));
        aWriter.Write(Brn(", capacity:"));
        Bws<Ascii::kMaxUintStringBytes> uintBuf;
        Ascii::AppendDec(uintBuf, iNumCells * iCellBytesTotal);
        aWriter.Write(uintBuf);
        aWriter.Write(Brn(" bytes, used:"));
        uintBuf.SetBytes(0);
        Ascii::AppendDec(uintBuf, iCellsUsed * iCellBytesTotal);
        aWriter.Write(uintBuf);
        aWriter.Write(Brn(" bytes, peak:"));
        uintBuf.SetBytes(0);
        Ascii::AppendDec(uintBuf, iCellsUsedMax * iCellBytesTotal);
        aWriter.Write(uintBuf);
        aWriter.Write(Brn(" bytes\n"));
    }
}
