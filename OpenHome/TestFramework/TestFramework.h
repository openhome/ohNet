#ifndef HEADER_TEST_FRAMEWORK
#define HEADER_TEST_FRAMEWORK

#include <OpenHome/Private/Standard.h>
#include <stdio.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/FunctorMsg.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>

namespace OpenHome {
namespace TestFramework {

void Fail(const TChar* aFile, TUint aLine, const TChar* aExp, const TChar* aMsg);
void Succeed(const TChar* aFile, TUint aLine);
void SucceedQuietly(const TChar* aFile, TUint aLine);

void AssertHandlerTest(const TChar* aFile, TUint aLine);

TUint TimeStart();
TUint TimeStop(TUint aStartTime);

void SetPrinter(FunctorMsg& aPrinter);
TInt PrintHex(const Brx& aB);
TInt Print(const Brx& aB);
TInt Print(const TChar* aFormat, ...);
TInt Print(const TChar* aFormat, va_list aArgs);

void RandomiseUdn(Environment& aEnv, Bwh& aUdn);

#ifdef _WIN32
// TEST macro generates "conditional expression is constant" warning
# pragma warning(disable:4127)
#endif

#define TEST(aExp) do { \
const TChar* file = __FILE__; \
aExp ? OpenHome::TestFramework::Succeed(file, __LINE__) \
    : OpenHome::TestFramework::Fail(file, __LINE__, #aExp, 0); \
} while(0)

#define TEST_QUIETLY(aExp) do { \
const TChar* file = __FILE__; \
aExp ? OpenHome::TestFramework::SucceedQuietly(file, __LINE__) \
    : OpenHome::TestFramework::Fail(file, __LINE__, #aExp, 0); \
} while(0)

#define TEST_THROWS(aExp, aExcept) do { \
const TChar* file = __FILE__; \
try { \
    aExp; \
    OpenHome::TestFramework::Fail(file, __LINE__, #aExp, "Exception " #aExcept " expected but not thrown."); \
} \
catch( aExcept& ) { \
    OpenHome::TestFramework::Succeed(file, __LINE__); \
} \
} while(0)

#define TEST_THROWS_QUIETLY(aExp, aExcept) do { \
const TChar* file = __FILE__; \
try { \
    aExp; \
    OpenHome::TestFramework::Fail(file, __LINE__, #aExp, "Exception " #aExcept " expected but not thrown."); \
} \
catch( aExcept& e ) { \
    OpenHome::TestFramework::SucceedQuietly(file, __LINE__); \
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

class Runner
{
public:
    static void Main(TInt aArgc, TChar* aArgv[], OpenHome::Net::InitialisationParams* aInitParams);
    Runner(const TChar* aDescription);
    void Add(Suite* aSuite);
    void Run();
    ~Runner();
private:
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
    Blocker(Environment& aStack);
    ~Blocker();
    void Wait(TUint aSecs);
private:
    void TimerExpired();
private:
    Semaphore iSem;
    Timer* iTimer;
};

} // namespace TestFramework
} // namespace OpenHome

#endif // HEADER_TEST
