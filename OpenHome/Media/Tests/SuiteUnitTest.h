#ifndef HEADER_SUITE_UNIT_TEST
#define HEADER_SUITE_UNIT_TEST

#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Functor.h>

#include <vector>

namespace OpenHome {
namespace TestFramework {

class SuiteUnitTest : public Suite
{
protected:
    SuiteUnitTest(const TChar* aName);
    void AddTest(Functor aTest);
private: // from Suite
    void Test();
private:
    virtual void Setup() = 0;
    virtual void TearDown() = 0;
private:
    std::vector<Functor> iTests;
};
    
} // namespace TestFramework
} // namespace OpenHome

#endif // HEADER_SUITE_UNIT_TEST
