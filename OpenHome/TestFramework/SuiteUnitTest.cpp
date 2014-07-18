#include "SuiteUnitTest.h"
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Types.h>
#include <OpenHome/Functor.h>

#include <string.h>
#include <utility>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

// SuiteUnitTest

SuiteUnitTest::SuiteUnitTest(const TChar* aName)
    : Suite(aName)
{
}

void SuiteUnitTest::AddTest(Functor aTest)
{
    iTests.push_back(std::make_pair(aTest, ""));
}

void SuiteUnitTest::AddTest(Functor aTest, const TChar* aName)
{
    iTests.push_back(std::make_pair(aTest, aName));
}

void SuiteUnitTest::Test()
{
    for (TUint i=0; i<iTests.size(); i++) {
        const TChar* name = iTests[i].second;
        if (name != NULL && strcmp(name, "") != 0) {
            Print("Test %d: %s ", i+1, name);
        }
        else {
            Print("Test %d: ", i+1);
        }
        Setup();
        iTests[i].first();
        TearDown();
        Print("\n");
    }
}
