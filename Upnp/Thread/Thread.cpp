#include <Thread.h>
#include <Debug.h>
#include <Os.h>
#include <exception>

using namespace Zapp;

//
// Semaphore
//

Semaphore::Semaphore(const TChar* aName, TUint aCount)
{
    iHandle = Zapp::Os::SemaphoreCreate(aName, aCount);
    if (iHandle == kHandleNull) {
        throw std::bad_alloc();
    }
}

Semaphore::~Semaphore()
{
    Zapp::Os::SemaphoreDestroy(iHandle);
}

void Semaphore::Wait()
{
    Zapp::Os::SemaphoreWait(iHandle);
}

void Semaphore::Wait(TUint aTimeoutMs)
{
    if (aTimeoutMs == 0) {
        return (Wait());
    }
    ASSERT(iHandle != kHandleNull);
    if (!Zapp::Os::SemaphoreTimedWait(iHandle, aTimeoutMs)) {
        THROW(Timeout);
    }
}

TBool Semaphore::Clear()
{
    ASSERT(iHandle != kHandleNull);
    return Zapp::Os::SemaphoreClear(iHandle);
}

void Semaphore::Signal()
{
    Zapp::Os::SemaphoreSignal(iHandle);
}

//
// Mutex
//

Mutex::Mutex(const TChar* aName)
{
    iHandle = Zapp::Os::MutexCreate(aName);
    if (iHandle == kHandleNull) {
        throw std::bad_alloc();
    }
}

Mutex::~Mutex()
{
    Zapp::Os::MutexDestroy(iHandle);
}

void Mutex::Wait()
{
    Zapp::Os::MutexLock(iHandle);
}

void Mutex::Signal()
{
    Zapp::Os::MutexUnlock(iHandle);
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

const TUint Zapp::Thread::kDefaultStackBytes = 16 * 1024;

Thread::Thread(const TChar* aName, TUint aPriority, TUint aStackBytes)
    : iHandle(kHandleNull)
    , iSema("TSEM", 0)
    , iTerminated(aName, 0)
    , iKill(false)
    , iStackBytes(aStackBytes)
    , iPriority(aPriority)
{
    ASSERT(aName != NULL);
    TUint bytes = strlen(aName);
    if (bytes > kNameBytes) {
        bytes = kNameBytes;
    }
    iName.Replace((TByte*)aName, bytes);
    iName.PtrZ();
}

Thread::~Thread()
{
    LOG(kThread, "> Thread::~Thread() called for thread: %p\n", this);
    Kill();
    Join();
    Zapp::Os::ThreadDestroy(iHandle);
    LOG(kThread, "< Thread::~Thread() called for thread: %p\n", this);
}

void Thread::Start()
{
    TChar name[kNameBytes+1] = {0};
    (void)memcpy(name, iName.Ptr(), iName.Bytes());
    iHandle = Zapp::Os::ThreadCreate(name, iPriority, iStackBytes, &Thread::EntryPoint, this);
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

Thread* Thread::Current()
{ // static
    return (Thread*)Zapp::Os::ThreadTls();
}

TBool Thread::SupportsPriorities()
{ // static
    return Zapp::Os::ThreadSupportsPriorities();
}

void Thread::CheckForKill() const
{
    // iKill is read/written from multiple threads but doesn't need to be locked
    // the only read is here and this function is polled.  If callers just miss
    // the thread being killed, they'll get an exception next time round...
    if (iKill) {
        THROW(ThreadKill);
    }
}

void Thread::Kill()
{
    LOG(kThread, "Thread::Kill() called for thread: %p\n", this);
    iKill = true;
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
