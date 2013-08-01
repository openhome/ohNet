#include "SuiteUnitTest.h"
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Functor.h>

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
    iTests.push_back(aTest);
}

void SuiteUnitTest::Test()
{
    for (TUint i=0; i<iTests.size(); i++) {
        Setup();
        iTests[i]();
        TearDown();
    }
}
