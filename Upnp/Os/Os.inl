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
inline THandle Os::SemaphoreCreate(const TChar* aName, TUint aCount)
{ return OsSemaphoreCreate(aName, aCount); }
inline void Os::SemaphoreDestroy(THandle aSem)
{ OsSemaphoreDestroy(aSem); }
inline void Os::SemaphoreWait(THandle aSem)
{
    ASSERT(aSem != kHandleNull);
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
    ASSERT(aSem != kHandleNull);
    int status = OsSemaphoreSignal(aSem);
    ASSERT(status == 0);
}
inline THandle Os::MutexCreate(const TChar* aName)
{ return OsMutexCreate(aName); }
inline void Os::MutexDestroy(THandle aMutex)
{ OsMutexDestroy(aMutex); }
inline void Os::MutexLock(THandle aMutex)
{
    ASSERT(aMutex != kHandleNull);
    int status = OsMutexLock(aMutex);
    ASSERT(status == 0);
}
inline void Os::MutexUnlock(THandle aMutex)
{
    ASSERT(aMutex != kHandleNull);
    int status = OsMutexUnlock(aMutex);
    ASSERT(status == 0);
}
inline THandle Os::ThreadCreate(const TChar* aName, TUint aPriority, TUint aStackBytes,
                                ThreadEntryPoint aEntryPoint, void* aArg)
{ return OsThreadCreate(aName, aPriority, aStackBytes, aEntryPoint, aArg); }
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
inline THandle Os::NetworkAccept(THandle aHandle)
{ return OsNetworkAccept(aHandle); }
void Os::NetworkSetInterfaceChangedObserver(InterfaceListChanged aCallback, void* aArg)
{ OsNetworkSetInterfaceChangedObserver(aCallback, aArg); }

#endif // HEADER_OS_INL
