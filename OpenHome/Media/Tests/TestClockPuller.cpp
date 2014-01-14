#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/ClockPuller.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteUtilisationHistory : public Suite
{
    static const TUint kUtilisationHistoryCapacity = 10;
public:
    SuiteUtilisationHistory();
    ~SuiteUtilisationHistory();
private: // from Suite
    void Test();
private:
    void HistoryUpdated();
private:
    UtilisationHistory* iUtilisationHistory;
    IClockPuller* iClockPuller;
    TUint iNumCallbacks;
};

} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;

SuiteUtilisationHistory::SuiteUtilisationHistory()
    : Suite("UtilisationHistory")
    , iNumCallbacks(0)
{
    iUtilisationHistory = new UtilisationHistory(kUtilisationHistoryCapacity, MakeFunctor(*this, &SuiteUtilisationHistory::HistoryUpdated));
    iClockPuller = iUtilisationHistory;
}

SuiteUtilisationHistory::~SuiteUtilisationHistory()
{
    delete iUtilisationHistory;
}

void SuiteUtilisationHistory::Test()
{
    // shouldn't really access History() or StartIndex() outside of callbacks
    // ...but nothing bad happens in a single-threaded test and it makes code much simpler...

    const std::vector<TUint64>& history = iUtilisationHistory->History();
    TEST(history.capacity() == kUtilisationHistoryCapacity);
    TEST(history.size() == 0);
    TEST(iUtilisationHistory->StartIndex() == 0);

    for (TUint i=0; i<kUtilisationHistoryCapacity; i++) {
        iClockPuller->NotifySize(i);
        TEST(iNumCallbacks == i+1);
        const std::vector<TUint64>& history2 = iUtilisationHistory->History();
        TEST(history2.size() == i+1);
        TEST(history2.capacity() == kUtilisationHistoryCapacity);
        for (TUint j=0; j<=i; j++) {
            TEST(history2[j] == j);
        }
        TEST(iUtilisationHistory->StartIndex() == 0);
    }
    
    // history now fully populated.  Check what happens when we keep adding items
    for (TUint i=0; i<kUtilisationHistoryCapacity; i++) {
        iClockPuller->NotifySize(i+kUtilisationHistoryCapacity);
        TEST(iNumCallbacks == i+kUtilisationHistoryCapacity+1);
        const std::vector<TUint64>& history3 = iUtilisationHistory->History();
        TEST(history3.size() == kUtilisationHistoryCapacity);
        TEST(history3.capacity() == kUtilisationHistoryCapacity);
        for (TUint j=0; j<=i; j++) {
            TEST(history3[j] == j+kUtilisationHistoryCapacity);
        }
        if  (i == kUtilisationHistoryCapacity-1) {
            TEST(iUtilisationHistory->StartIndex() == 0);
        }
        else {
            TEST(iUtilisationHistory->StartIndex() == i+1);
        }
    }

    // check that Stop() clears history/index
    iClockPuller->NotifySize(2*kUtilisationHistoryCapacity);
    TEST(iUtilisationHistory->StartIndex() != 0);
    iClockPuller->Stop();
    const std::vector<TUint64>& history4 = iUtilisationHistory->History();
    TEST(history4.capacity() == kUtilisationHistoryCapacity);
    TEST(history4.size() == 0);
    TEST(iUtilisationHistory->StartIndex() == 0);
}

void SuiteUtilisationHistory::HistoryUpdated()
{
    iNumCallbacks++;
}


void TestClockPuller()
{
    Runner runner("Clock Puller tests\n");
    runner.Add(new SuiteUtilisationHistory());
    runner.Run();
}
