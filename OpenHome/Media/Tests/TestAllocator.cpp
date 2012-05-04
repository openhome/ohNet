#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Allocator.h>
#include <OpenHome/Av/InfoProvider.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteAllocator : public Suite, private Av::IInfoAggregator, private IWriter
{
public:
    SuiteAllocator();
    void Test();
private: // from IInfoAggregator
    void Register(Av::IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries);
private: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
private:
    Av::IInfoProvider* iInfoProvider;
};

} // namespace Media
} // namespace OpenHome

SuiteAllocator::SuiteAllocator()
    : Suite("Allocator tests")
    , iInfoProvider(NULL)
{
}

void SuiteAllocator::Test()
{
    //Print("Create Allocators with different cell sizes.  Check that size is always >= that requested\n");
    Allocator* allocator;
    for (TUint cellSize = 30; cellSize < 38; cellSize++) {
        allocator = new Allocator("TEST1", cellSize, 100, *this);
        TEST(allocator->iCellBytes >= cellSize);
        TEST(allocator->iCellBytes - cellSize < 8);
        delete allocator;
    }

    //Print("\nCreate Allocator with 10 cells.  Check that 10 cells can be allocated\n");
    allocator = new Allocator("TEST2", 16, 10, *this);
    TAny* cells[10];
    for (TUint i=0; i<10; i++) {
        cells[i] = allocator->Alloc();
        TEST(cells[i] != NULL);
    }
    //Print("\nalloc 11th cell.  Check this throws\n");
    TEST_THROWS(allocator->Alloc(), AllocatorNoMemory);
    //Print("\nuse InfoProvider.  Visually check results\n");
    TEST(iInfoProvider != NULL);
    iInfoProvider->QueryInfo(Allocator::kQueryMemory, *this); // expect to see   capacity == peak == used
    //Print("\nmemset each cell to a different value, check that all can be read back (so cells don't overlap)\n");
    for (TUint i=0; i<10; i++) {
        memset(cells[i], i, 16);
    }
    for (TUint i=0; i<10; i++) {
        TByte* bytes = (TByte*)cells[i];
        for (TUint j=0; j<16; j++) {
            TEST(bytes[j] == i);
        }
    }
    //Print("\nfree all cells.  Check values of iCellsUsed and iCellsUsedMax\n");
    TEST(allocator->iCellsUsed == 10);
    TEST(allocator->iCellsUsedMax == 10);
    for (TUint i=0; i<10; i++) {
        Allocator::Free(cells[i]);
        TEST(allocator->iCellsUsed == 10 - i - 1);
        TEST(allocator->iCellsUsedMax == 10);
    }
    //Print("\nreallocate all cells, confirming that freed cells can be reused\n");
    for (TUint i=0; i<10; i++) {
        cells[i] = allocator->Alloc();
        TEST(cells[i] != NULL);
    }
    TEST(allocator->iCellsUsed == 10);
    //Print("\nfree 9 of the 10 cells then delete allocator.  Check this asserts (due to the memory leak)\n");
    for (TUint i=0; i<9; i++) {
        Allocator::Free(cells[i]);
    }
    TEST(allocator->iCellsUsed == 1);
    TEST_THROWS(delete allocator, AssertionFailed);

    //Print("\nCreate 3 allocators.  Alloc then free from 2nd, check its iCellsUsedMax has increased but others are unchanged\n");
    Allocator* allocators[3];
    for (TUint i=0; i<3; i++) {
        allocators[i] = new Allocator("TEST3", 16, 10, *this);
    }
    Allocator::Free(allocators[1]->Alloc());
    TEST(allocators[0]->iCellsUsedMax == 0);
    TEST(allocators[1]->iCellsUsedMax == 1);
    TEST(allocators[2]->iCellsUsedMax == 0);
    for (TUint i=0; i<3; i++) {
        delete allocators[i];
    }
}

void SuiteAllocator::Register(Av::IInfoProvider& aProvider, std::vector<Brn>& /*aSupportedQueries*/)
{
    iInfoProvider = &aProvider;
}

void SuiteAllocator::Write(TByte aValue)
{
    Print("%c", aValue);
}

void SuiteAllocator::Write(const Brx& aBuffer)
{
    Print(aBuffer);
}

void SuiteAllocator::WriteFlush()
{
}


void TestAllocator()
{
    Runner runner("Allocator testing\n");
    runner.Add(new SuiteAllocator());
    runner.Run();
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestAllocator();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
