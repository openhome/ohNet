#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/OsWrapper.h>
#include <exception>
#include <OpenHome/Net/Private/Globals.h> // FIXME - use of globals should be discouraged
#include <OpenHome/Private/Env.h>

#include <algorithm>

using namespace OpenHome;

static const Brn kThreadNameUnknown("____");

// Semaphore

Semaphore::Semaphore(const TChar* aName, TUint aCount)
{
    iHandle = OpenHome::Os::SemaphoreCreate(OpenHome::gEnv->OsCtx(), aName, aCount);
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
        Wait();
        return;
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


// Mutex

Mutex::Mutex(const TChar* aName)
{
    iHandle = OpenHome::Os::MutexCreate(OpenHome::gEnv->OsCtx(), aName);
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
        Bws<Thread::kMaxNameBytes+1> thName(Thread::CurrentThreadName());
        thName.PtrZ();
        Log::Print("ERROR: %s %s from thread %s\n", msg, iName, thName.Ptr());
        ASSERT(err == 0);
    }
}

const TChar* Mutex::Name() const
{
    return iName;
}

void Mutex::Signal()
{
    OpenHome::Os::MutexUnlock(iHandle);
}


// MutexInstrumented

MutexInstrumented::MutexInstrumented(const TChar* aName, TUint64 aWaitTriggerUs)
    : Mutex(aName)
    , iWaitTriggerUs(aWaitTriggerUs)
{
}

void MutexInstrumented::Wait()
{
    TUint64 timeStart = Os::TimeInUs(OpenHome::gEnv->OsCtx());
    Mutex::Wait();
    TUint64 timeEnd = Os::TimeInUs(OpenHome::gEnv->OsCtx());
    if ((timeEnd - timeStart) > iWaitTriggerUs) {
        Log::Print("Mutex %s in thread %.*s waited for %llu Us.  Start time(Us): %llu, End time(Us): %llu. Mutex was released by thread %s\n",
                Name(), PBUF(Thread::CurrentThreadName()), (timeEnd - timeStart), timeStart, timeEnd, iLastUseThreadName.PtrZ());
    }
}

void MutexInstrumented::Signal()
{
    iLastUseThreadName.Replace(Thread::CurrentThreadName());
    Mutex::Signal();
}


IMutex* MutexFactory::Create(const TChar* aName, TBool aInstrumented, TUint32 aInstrumentedTriggerUs)
{
    if (aInstrumented == false) {
        return new Mutex(aName);
    }
    else
    {
        return new MutexInstrumented(aName, aInstrumentedTriggerUs);
    }
}

// Thread

const TUint OpenHome::Thread::kDefaultStackBytes = 32 * 1024;

Thread::Thread(const TChar* aName, TUint aPriority, TUint aStackBytes)
    : iHandle(kHandleNull)
    , iSema("TSEM", 0)
    , iProceedSema("proceed", 0)
    , iRunningSema("running", 0)
    , iTerminated(aName, 0)
    , iKill(false)
    , iKillMutex("KMTX")
{
    ASSERT(aName != NULL);
    const TUint bytes = std::min(iName.MaxBytes()-1, (TUint)strlen(aName));
    iName.Replace((TByte*)aName, bytes);
    iName.PtrZ();
    const TUint priority = OpenHome::gEnv->PriorityArbitrator().CalculatePriority(aName, aPriority);
    iHandle = OpenHome::Os::ThreadCreate(OpenHome::gEnv->OsCtx(), (TChar*)iName.Ptr(), priority, aStackBytes, &Thread::EntryPoint, this);
    ASSERT(iHandle != kHandleNull);
}

void Thread::NotifyWait()
{
    Os::ThreadWait(iHandle, false);
}

void Thread::NotifyWaitAll()
{
    Os::ThreadWait(iHandle, true);
}

void Thread::NotifySignal()
{
    Os::ThreadSignal(iHandle);
}

void Thread::Run()
{
    /**
     * Does nothing. Allows destructor to be entered before Run() has been
     * called, in which case Run() will not resolve to a pure virtual method if
     * it is subequently called.
     */
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
    iProceedSema.Signal();
    iRunningSema.Wait();
}

void Thread::EntryPoint(void* aArg)
{ // static
    Thread* self = (Thread*)aArg;
    Os::ThreadInstallSignalHandlers();

    try {
        self->iProceedSema.Wait();
        self->CheckForKill();
        self->iRunningSema.Signal();
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
    if (gEnv != NULL) {
        Net::InitialisationParams* initParams = OpenHome::gEnv->InitParams();
        if (initParams != NULL) {
            Functor& handler = initParams->ThreadExitHandler();
            if (handler) {
                handler();
            }
        }
    }

    self->iRunningSema.Signal();
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
    return iSema.Clear();
}

void Thread::Sleep(TUint aMilliSecs)
{ // static
    if (aMilliSecs == 0) {
        // a 0ms sleep will block forever so round up to the smallest delay we can manage (1ms)
        aMilliSecs = 1;
    }
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
    void* th = OpenHome::Os::ThreadTls(OpenHome::gEnv->OsCtx());
    if (th == NULL) {
        return NULL;
    }
    return (Thread*)th;
}

TBool Thread::SupportsPriorities()
{ // static
    return OpenHome::Os::ThreadSupportsPriorities(OpenHome::gEnv->OsCtx());
}

void Thread::CheckCurrentForKill()
{ // static
    Thread* thread = Thread::Current();
    if ( thread != NULL )
        thread->CheckForKill();
}

void Thread::CheckForKill() const
{
    AutoMutex _amtx(iKillMutex);
    if (iKill) {
        THROW(ThreadKill);
    }
}

void Thread::Kill()
{
    LOG(kThread, "Thread::Kill() called for thread: %p\n", this);
    AutoMutex _amtx(iKillMutex);
    iKill = true;
    iProceedSema.Signal();
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


// ThreadFunctor

ThreadFunctor::ThreadFunctor(const TChar* aName, Functor aFunctor, TUint aPriority, TUint aStackBytes)
    : Thread(aName, aPriority, aStackBytes)
    , iFunctor(aFunctor)
{
}

ThreadFunctor::~ThreadFunctor()
{
    Kill();
    Join();
}

void ThreadFunctor::Run()
{
    iFunctor();
}


// ThreadPriorityArbitrator

ThreadPriorityArbitrator::ThreadPriorityArbitrator(TUint aHostMin, TUint aHostMax)
    : iHostMin(aHostMin)
    , iHostMax(aHostMax)
{
}

void ThreadPriorityArbitrator::Add(IPriorityArbitrator& aArbitrator)
{
    std::vector<IPriorityArbitrator*>::iterator it=iArbitrators.begin();
    for (; it!=iArbitrators.end(); ++it) {
        const TUint itMin = (*it)->OpenHomeMin();
        const TUint itMax = (*it)->OpenHomeMax();
        const TUint arbMin = aArbitrator.OpenHomeMin();
        const TUint arbMax = aArbitrator.OpenHomeMax();
        if (itMin <= arbMax && arbMin <= itMax) {
            LOG_ERROR(kThread, "ERROR: ThreadPriorityArbitrator ranges overlap: [%u..%u], [%u..%u]\n",
                                  itMin, itMax, arbMax, arbMin);
            ASSERTS();
        }
        if (arbMax > itMax) {
            break;
        }
    }

    (void)iArbitrators.insert(it, &aArbitrator);
}

void ThreadPriorityArbitrator::Validate()
{
    TUint max = kPrioritySystemHighest + 1;
    for (std::vector<IPriorityArbitrator*>::const_iterator it=iArbitrators.begin(); it!=iArbitrators.end(); ++it) {
        if ((*it)->OpenHomeMax() != max-1) {
            LOG_ERROR(kThread, "ERROR: gaps between thread priority arbitrators are not supported\n");
            ASSERTS();
        }
        max = (*it)->OpenHomeMin();
    }
}

TUint ThreadPriorityArbitrator::CalculatePriority(const char* aId, TUint aRequested) const
{
    /* look for arbitrator that handles aRequested, ask it for priority
       ...or if aRequested is below all arbitrators, use linear division of remaining range */
    TUint hostMin = iHostMin;
    TUint hostMax = iHostMax;
    TUint min = kPrioritySystemLowest;
    TUint max = kPrioritySystemHighest;
    for (std::vector<IPriorityArbitrator*>::const_iterator it=iArbitrators.begin(); it!=iArbitrators.end(); ++it) {
        if ((*it)->OpenHomeMax() < aRequested) {
            ASSERTS();
        }
        else if ((*it)->OpenHomeMin() <= aRequested) {
            return (*it)->Priority(aId, aRequested, hostMax);
        }
        max = (*it)->OpenHomeMin() - 1;
        hostMax -= (*it)->HostRange();
    }
    return DoCalculatePriority(aRequested, min, max, hostMin, hostMax);
}

TUint ThreadPriorityArbitrator::DoCalculatePriority(TUint aRequested, TUint aOpenHomeMin, TUint aOpenHomeMax, TUint aHostMin, TUint aHostMax)
{ // static
    ASSERT(aRequested >= aOpenHomeMin);
    ASSERT(aRequested <= aOpenHomeMax);
    ASSERT(aOpenHomeMin <= aOpenHomeMax);
    ASSERT(aHostMin <= aHostMax);

    const TUint openhomeRange = aOpenHomeMax - aOpenHomeMin;
    const TUint hostRange = aHostMax - aHostMin;
    const TUint priority = aHostMin + ((((aRequested - aOpenHomeMin) * hostRange) + (openhomeRange/2)) / openhomeRange);
    return priority;
}


// AutoMutex

AutoMutex::AutoMutex(IMutex& aMutex)
    : iMutex(aMutex)
{
    iMutex.Wait();
}

AutoMutex::~AutoMutex()
{
    iMutex.Signal();
}


// AutoSemaphore

AutoSemaphore::AutoSemaphore(Semaphore& aSemaphore)
    : iSem(aSemaphore)
{
    iSem.Wait();
}

AutoSemaphore::~AutoSemaphore()
{
    iSem.Signal();
}


// AutoSemaphoreSignal

AutoSemaphoreSignal::AutoSemaphoreSignal(Semaphore& aSemaphore)
    : iSem(aSemaphore)
{
}

AutoSemaphoreSignal::~AutoSemaphoreSignal()
{
    iSem.Signal();
}
