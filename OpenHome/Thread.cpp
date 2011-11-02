#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/OsWrapper.h>
#include <exception>
#include <OpenHome/Net/Private/Stack.h>

using namespace OpenHome;

static const Brn kThreadNameUnknown("____");

//
// Semaphore
//

Semaphore::Semaphore(const TChar* aName, TUint aCount)
{
    iHandle = OpenHome::Os::SemaphoreCreate(aName, aCount);
    if (iHandle == kHandleNull) {
        throw std::bad_alloc();
    }
}

Semaphore::~Semaphore()
{
    OpenHome::Os::SemaphoreDestroy(iHandle);
}

void Semaphore::Wait()
{
    OpenHome::Os::SemaphoreWait(iHandle);
}

void Semaphore::Wait(TUint aTimeoutMs)
{
    if (aTimeoutMs == 0) {
        return (Wait());
    }
    ASSERT(iHandle != kHandleNull);
    if (!OpenHome::Os::SemaphoreTimedWait(iHandle, aTimeoutMs)) {
        THROW(Timeout);
    }
}

TBool Semaphore::Clear()
{
    ASSERT(iHandle != kHandleNull);
    return OpenHome::Os::SemaphoreClear(iHandle);
}

void Semaphore::Signal()
{
    OpenHome::Os::SemaphoreSignal(iHandle);
}

//
// Mutex
//

Mutex::Mutex(const TChar* aName)
{
    iHandle = OpenHome::Os::MutexCreate(aName);
    if (iHandle == kHandleNull) {
        throw std::bad_alloc();
    }
    (void)strncpy(iName, aName, 4);
    iName[4] = 0;
}

Mutex::~Mutex()
{
    OpenHome::Os::MutexDestroy(iHandle);
}

void Mutex::Wait()
{
    TInt err = OpenHome::Os::MutexLock(iHandle);
    if (err != 0) {
        const char* msg;
        if (err == -1) {
            msg = "Recursive lock attempted on mutex";
        }
        else {
            msg = "Lock attempted on uninitialised mutex";
        }    
        Brhz thBuf;
        Bws<5> thName(Thread::CurrentThreadName());
        thName.PtrZ();
        Log::Print("ERROR: %s %s from thread %s\n", msg, iName, thName.Ptr());
        ASSERT(err == 0);
    }
}

void Mutex::Signal()
{
    OpenHome::Os::MutexUnlock(iHandle);
}

//
// SemaphoreActive
//

SemaphoreActive::SemaphoreActive(Semaphore& aSema)
    : iSema(aSema)
    , iLock("SMAC")
    , iCount(0)
{
}

SemaphoreActive::SemaphoreActive(Thread& aThread)
    : iSema(aThread.iSema)
    , iLock("SMAC")
    , iCount(0)
{
}

void SemaphoreActive::Signal()
{
    iLock.Wait();
    iCount++;
    iLock.Signal();
    iSema.Signal();
}

//This function presumes that there's only _ever_ one thread who calls ::Signalled()
TBool SemaphoreActive::Signalled()
{
    TBool ret = false;

    iLock.Wait();
    TInt count = iCount--;
    if(count >= 0) {
        ret = true;
    }
    else {
        iCount++;
    }
    iLock.Signal();

    return ret;
}

void SemaphoreActive::ConsumeOne()
{
    ASSERT(Signalled());
    ASSERT(iSema.Clear());
}

void SemaphoreActive::ConsumeAll()
{
    while(Signalled()) {
        ASSERT(iSema.Clear());
    }
}

//
// Thread
//

const TUint OpenHome::Thread::kDefaultStackBytes = 16 * 1024;

Thread::Thread(const TChar* aName, TUint aPriority, TUint aStackBytes)
    : iHandle(kHandleNull)
    , iSema("TSEM", 0)
    , iTerminated(aName, 0)
    , iKill(false)
    , iStackBytes(aStackBytes)
    , iPriority(aPriority)
{
    ASSERT(aName != NULL);
    iName.SetBytes(iName.MaxBytes());
    iName.Fill(0);
    TUint bytes = (TUint)strlen(aName);
    if (bytes > kNameBytes) {
        bytes = kNameBytes;
    }
    iName.Replace((TByte*)aName, bytes);
}

Thread::~Thread()
{
    LOG(kThread, "> Thread::~Thread() called for thread: %p\n", this);
    Kill();
    Join();
    OpenHome::Os::ThreadDestroy(iHandle);
    LOG(kThread, "< Thread::~Thread() called for thread: %p\n", this);
}

void Thread::Start()
{
    iHandle = OpenHome::Os::ThreadCreate((TChar*)iName.Ptr(), iPriority, iStackBytes, &Thread::EntryPoint, this);
}

void Thread::EntryPoint(void* aArg)
{ // static
    Thread* self = (Thread*)aArg;
    try {
        self->Run();
    }
    catch(ThreadKill&) {
        LOG(kThread, "Thread::Entry() caught ThreadKill for %s(%p)\n", self->iName.Ptr(), self);
    }
    catch(Exception& e) {
        UnhandledExceptionHandler(e);
    }
    catch(std::exception& e) {
        UnhandledExceptionHandler(e);
    }
    catch(...) {
        UnhandledExceptionHandler( "Unknown Exception", "Unknown File", 0 );
    }
    LOG(kThread, "Thread::Entry(): Thread::Run returned, exiting thread %s(%p)\n", self->iName.Ptr(), self);
    self->iTerminated.Signal();
}

void Thread::Wait()
{
    iSema.Wait();
    CheckForKill();
}

void Thread::Signal()
{
    iSema.Signal();
}

TBool Thread::TryWait()
{
    CheckForKill();
    return (iSema.Clear());
}

void Thread::Sleep(TUint aMilliSecs)
{ // static
    Semaphore sem("", 0);
    try {
        sem.Wait(aMilliSecs);
    }
    catch(Timeout&) {}
}

const Brx& Thread::CurrentThreadName()
{ // static
    Thread* th = Current();
    if (th == NULL) {
        return kThreadNameUnknown;
    }
    return th->iName;
}

Thread* Thread::Current()
{ // static
    void* th = OpenHome::Os::ThreadTls();
    if (th == NULL) {
        return NULL;
    }
    return (Thread*)th;
}

TBool Thread::SupportsPriorities()
{ // static
    return OpenHome::Os::ThreadSupportsPriorities();
}

void Thread::CheckForKill() const
{
    Net::Stack::Mutex().Wait();
    TBool kill = iKill;
    Net::Stack::Mutex().Signal();
    if (kill) {
        THROW(ThreadKill);
    }
}

void Thread::Kill()
{
    LOG(kThread, "Thread::Kill() called for thread: %p\n", this);
    Net::Stack::Mutex().Wait();
    iKill = true;
    Net::Stack::Mutex().Signal();
    Signal();
}

const Brx& Thread::Name() const
{
    return iName;
}

bool Thread::operator== (const Thread& other) const {
    return (Thread*) this == (Thread*) &other;
}

bool Thread::operator!= (const Thread& other) const {
    return !(*this == other);
}

void Thread::Join()
{
    LOG(kThread, "Thread::Join() called for thread: %p\n", this);
    
    iTerminated.Wait();
    iTerminated.Signal();
}

//
// ThreadFunctor
//

ThreadFunctor::ThreadFunctor(const TChar* aName, Functor aFunctor, TUint aPriority,
    TUint aStackBytes) : Thread(aName, aPriority, aStackBytes), iFunctor(aFunctor), iStarted("TFSM", 0)
{
}

ThreadFunctor::~ThreadFunctor()
{
    iStarted.Wait();
}

void ThreadFunctor::Run()
{
    iStarted.Signal();
    iFunctor();
}

//
// AutoMutex
//

AutoMutex::AutoMutex(Mutex& aMutex)
 : iMutex(aMutex)
{
    iMutex.Wait();
}

AutoMutex::~AutoMutex()
{
    iMutex.Signal();
}

//
// AtomicInt
//

AtomicInt::AtomicInt(TInt aInitialValue)
    : iInt(aInitialValue)
{
}

AtomicInt::AtomicInt()
    : iInt(0)
{
}

TInt AtomicInt::Inc()
{
    Net::Stack::Mutex().Wait();
    TInt value = ++iInt;
    Net::Stack::Mutex().Signal();
    return value;
}

TInt AtomicInt::Dec()
{
    Net::Stack::Mutex().Wait();
    TInt value = --iInt;
    Net::Stack::Mutex().Signal();
    return value;
}

