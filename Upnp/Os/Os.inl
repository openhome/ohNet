#ifndef HEADER_OS_INL
#define HEADER_OS_INL

inline TInt Os::Create()
{ return OsCreate(); }
inline void Os::Destroy()
{ OsDestroy(); }
inline void Os::Quit()
{ OsQuit(); }
inline TUint64 Os::TimeInUs()
{ return OsTimeInUs(); }
inline TUint Os::TimeInMs()
{ return (TUint)TimeInUs()/1000; }
inline void Os::ConsoleWrite(const TChar* aStr)
{ OsConsoleWrite(aStr); }
inline TInt Os::SemaphoreCreate(const TChar* aName, TUint aCount, THandle* aHandle)
{ return OsSemaphoreCreate(aName, aCount, aHandle); }
inline void Os::SemaphoreDestroy(THandle aSem)
{ OsSemaphoreDestroy(aSem); }
inline void Os::SemaphoreWait(THandle aSem)
{
    ASSERT(!HandleIsNull(&aSem));
    int status = OsSemaphoreWait(aSem);
    ASSERT(status == 0);
}
inline TBool Os::SemaphoreTimedWait(THandle aSem, TUint aTimeoutMs)
{
    int ret = OsSemaphoreTimedWait(aSem, aTimeoutMs);
    ASSERT(ret >= 0);
    return (ret != 0);
}
inline TBool Os::SemaphoreClear(THandle aSem)
{ return (OsSemaphoreClear(aSem) == 1); }
inline void Os::SemaphoreSignal(THandle aSem)
{
    ASSERT(!HandleIsNull(&aSem));
    int status = OsSemaphoreSignal(aSem);
    ASSERT(status == 0);
}
inline TInt Os::MutexCreate(const TChar* aName, THandle* aHandle)
{ return OsMutexCreate(aName, aHandle); }
inline void Os::MutexDestroy(THandle aMutex)
{ OsMutexDestroy(aMutex); }
inline void Os::MutexLock(THandle aMutex)
{
    ASSERT(!HandleIsNull(&aMutex));
    int status = OsMutexLock(aMutex);
    ASSERT(status == 0);
}
inline void Os::MutexUnlock(THandle aMutex)
{
    ASSERT(!HandleIsNull(&aMutex));
    int status = OsMutexUnlock(aMutex);
    ASSERT(status == 0);
}
inline TInt Os::ThreadCreate(const TChar* aName, TUint aPriority, TUint aStackBytes,
                             ThreadEntryPoint aEntryPoint, void* aArg, THandle* aHandle)
{ return OsThreadCreate(aName, aPriority, aStackBytes, aEntryPoint, aArg, aHandle); }
inline void* Os::ThreadTls()
{ return OsThreadTls(); }
inline void Os::ThreadDestroy(THandle aThread)
{ OsThreadDestroy(aThread); }
inline TBool Os::ThreadSupportsPriorities()
{ return (OsThreadSupportsPriorities() != 0); }

inline TInt Os::NetworkSend(THandle aHandle, const Brx& aBuffer)
{ return OsNetworkSend(aHandle, aBuffer.Ptr(), aBuffer.Bytes()); }
inline TInt Os::NetworkSendTo(THandle aHandle, const Brx& aBuffer, const Endpoint& aEndpoint)
{ return OsNetworkSendTo(aHandle, aBuffer.Ptr(), aBuffer.Bytes(), aEndpoint.Address(), aEndpoint.Port()); }
inline TInt Os::NetworkReceive(THandle aHandle, Bwx& aBuffer)
{ return OsNetworkReceive(aHandle, (uint8_t*)aBuffer.Ptr(), aBuffer.MaxBytes()); }
inline TInt Os::NetworkInterrupt(THandle aHandle, TBool aInterrupt)
{ return OsNetworkInterrupt(aHandle, (aInterrupt? 1:0)); }
inline TInt Os::NetworkClose(THandle aHandle)
{ return OsNetworkClose(aHandle); }
inline TInt Os::NetworkListen(THandle aHandle, TUint aSlots)
{ return OsNetworkListen(aHandle, aSlots); }
inline TInt Os::NetworkAccept(THandle aHandle, THandle* aNewHandle)
{ return OsNetworkAccept(aHandle, aNewHandle); }
void Os::NetworkSetInterfaceChangedObserver(InterfaceListChanged aCallback, void* aArg)
{ OsNetworkSetInterfaceChangedObserver(aCallback, aArg); }

#endif // HEADER_OS_INL
