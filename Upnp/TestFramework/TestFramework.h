#ifndef HEADER_TEST_FRAMEWORK
#define HEADER_TEST_FRAMEWORK

#include <Standard.h>
#include <stdio.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <Zapp.h>
#include <Debug.h>
#include <Thread.h>
#include <Timer.h>

namespace Zapp
{

namespace TestFramework
{

void Fail(const TChar* aFile, TUint aLine, const TChar* aExp, const TChar* aMsg);
void Succeed(const TChar* aFile, TUint aLine);
void SucceedQuietly(const TChar* aFile, TUint aLine);

void AssertHandlerTest(const TChar* aFile, TUint aLine);

TUint TimeStart();
TUint TimeStop(TUint aStartTime);

TInt PrintHex(const Brx& aB);
TInt Print(const Brx& aB);
TInt Print(const TChar* aFormat, ...);
TInt Print(const TChar* aFormat, va_list aArgs);

#ifdef _WIN32
// TEST macro generates "conditional expression is constant" warning
# pragma warning(disable:4127)
#endif

#define TEST(aExp) do { \
const TChar* file = __FILE__; \
aExp ? Zapp::TestFramework::Succeed(file, __LINE__) \
    : Zapp::TestFramework::Fail(file, __LINE__, #aExp, 0); \
} while(0)

#define TEST_QUIETLY(aExp) do { \
const TChar* file = __FILE__; \
aExp ? Zapp::TestFramework::SucceedQuietly(file, __LINE__) \
    : Zapp::TestFramework::Fail(file, __LINE__, #aExp, 0); \
} while(0)

#define TEST_THROWS(aExp, aExcept) do { \
const TChar* file = __FILE__; \
try { \
    aExp; \
    Zapp::TestFramework::Fail(file, __LINE__, #aExp, "Exception " #aExcept " expected but not thrown."); \
} \
catch( aExcept& ) { \
    Zapp::TestFramework::Succeed(file, __LINE__); \
} \
} while(0)

#define TEST_THROWS_QUIETLY(aExp, aExcept) do { \
const TChar* file = __FILE__; \
try { \
    aExp; \
    Zapp::TestFramework::Fail(file, __LINE__, #aExp, "Exception " #aExcept " expected but not thrown."); \
} \
catch( aExcept& e ) { \
    Zapp::TestFramework::SucceedQuietly(file, __LINE__); \
} \
} while(0)

class Suite
{
    friend class Runner;
public:
    const TChar* Description() const;
protected:
    Suite(const TChar* aDescription);
    virtual ~Suite();
    virtual void Test() = 0;
private:
    Suite* iNext;
    const TChar* iDesc;
};

class Runner // Test
{
public:
    static void Main(TInt aArgc, TChar* aArgv[], InitialisationParams* aInitParams);
    Runner(const TChar* aDescription);
    void Add(Suite* aSuite);
    void Run();
    ~Runner();
private:
// vector of suites
    Suite* iFirst;
    Suite* iLast;
    const TChar* iDesc;
};

/**
 * Utility for tests which need to wait for e.g. a msearch to complete
 */
class Blocker
{
public:
    Blocker();
    ~Blocker();
    void Wait(TUint aSecs);
private:
    void TimerExpired();
private:
    Semaphore iSem;
    Timer* iTimer;
};

}; //namespace TestFramework

}; //namespace Zapp

#endif // HEADER_TEST
