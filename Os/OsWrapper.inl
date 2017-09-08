#ifndef HEADER_OSWRAPPER_INL
#define HEADER_OSWRAPPER_INL

inline OsContext* Os::Create(Net::InitialisationParams::EThreadScheduling aSchedulerPolicy)
{ return OsCreate((OsThreadSchedulePolicy)aSchedulerPolicy); }
inline void Os::Destroy(OsContext* aContext)
{ OsDestroy(aContext); }
inline void Os::Quit(OsContext* aContext)
{ OsQuit(aContext); }
inline TUint Os::StackTraceNumEntries(THandle aStackTrace)
{ return OsStackTraceNumEntries(aStackTrace); }
inline const char* Os::StackTraceEntry(THandle aStackTrace, TUint aIndex)
{ return OsStackTraceEntry(aStackTrace, aIndex); }
inline void Os::StackTraceFinalise(THandle aStackTrace)
{ OsStackTraceFinalise(aStackTrace); }
inline TUint64 Os::TimeInUs(OsContext* aContext)
{ return OsTimeInUs(aContext); }
inline TUint Os::TimeInMs(OsContext* aContext)
{ return (TUint)(TimeInUs(aContext)/1000); }
inline void Os::ConsoleWrite(const TChar* aStr)
{ OsConsoleWrite(aStr); }
inline THandle Os::SemaphoreCreate(OsContext* aContext, const TChar* aName, TUint aCount)
{ return OsSemaphoreCreate(aContext, aName, aCount); }
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
inline THandle Os::MutexCreate(OsContext* aContext, const TChar* aName)
{ return OsMutexCreate(aContext, aName); }
inline void Os::MutexDestroy(THandle aMutex)
{ OsMutexDestroy(aMutex); }
inline TInt Os::MutexLock(THandle aMutex)
{
    ASSERT(aMutex != kHandleNull);
    return OsMutexLock(aMutex);
}
inline void Os::MutexUnlock(THandle aMutex)
{
    ASSERT(aMutex != kHandleNull);
    int status = OsMutexUnlock(aMutex);
    ASSERT(status == 0);
}
inline THandle Os::ThreadCreate(OsContext* aContext, const TChar* aName, TUint aPriority,
                                TUint aStackBytes, ThreadEntryPoint aEntryPoint, void* aArg)
{ return OsThreadCreate(aContext, aName, aPriority, aStackBytes, aEntryPoint, aArg); }
inline void Os::ThreadInstallSignalHandlers()
{ OsThreadInstallSignalHandlers(); }
inline void* Os::ThreadTls(OsContext* aContext)
{ return OsThreadTls(aContext); }
inline void Os::ThreadWait(THandle aHandle, TBool aConsumeAll)
{ OsThreadWait(aHandle, aConsumeAll ? eConsumeAll : eConsumeSingle); }
inline void Os::ThreadSignal(THandle aHandle)
{ OsThreadSignal(aHandle); }
inline void Os::ThreadDestroy(THandle aThread)
{ OsThreadDestroy(aThread); }
inline TBool Os::ThreadSupportsPriorities(OsContext* aContext)
{ return (OsThreadSupportsPriorities(aContext) != 0); }

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
void Os::NetworkSetInterfaceChangedObserver(OsContext* aContext, InterfaceListChanged aCallback, void* aArg)
{ OsNetworkSetInterfaceChangedObserver(aContext, aCallback, aArg); }

#endif // HEADER_OSWRAPPER_INL
