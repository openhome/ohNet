#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Os.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Env.h>

using namespace OpenHome;

THandle Os::StackTraceInitialise(OsContext* aContext)
{
    /* this function and StackTraceCopy below could be inlined but Exception strips out
       the functions above THROW and that'd be harder to do reliably with inline functions
       (which may or may not be actually inlined depending on compiler optimisations) */
    return OsStackTraceInitialise(aContext);
}

THandle Os::StackTraceCopy(THandle aStackTrace)
{
    return OsStackTraceCopy(aStackTrace);
}

Brn Os::GetPlatformNameAndVersion(OsContext* aContext, TUint& aMajor, TUint& aMinor)
{
    char* name;
    OsGetPlatformNameAndVersion(aContext, &name, &aMajor, &aMinor);
    Brn nameBuf(name);
    return nameBuf;
}

void Os::ThreadGetPriorityRange(OsContext* aContext, TUint& aHostMin, TUint& aHostMax)
{
    uint32_t hostMin, hostMax;
    OsThreadGetPriorityRange(aContext, &hostMin, &hostMax);
    aHostMin = (TUint)hostMin;
    aHostMax = (TUint)hostMax;
}

THandle Os::NetworkCreate(OsContext* aContext, ESocketType aSocketType)
{
    THandle handle = OsNetworkCreate(aContext, (OsNetworkSocketType)aSocketType);
    if (handle == kHandleNull) {
        THROW(NetworkError);
    }
    return handle;
}

TInt Os::NetworkBind(THandle aHandle, const Endpoint& aEndpoint)
{
    TInt ret = OsNetworkBind(aHandle, aEndpoint.Address(), aEndpoint.Port());
    return ret;
}

TInt Os::NetworkBindMulticast(THandle aHandle, TIpAddress aAdapter, const Endpoint& aMulticast)
{
    TInt ret = OsNetworkBindMulticast(aHandle, aAdapter, aMulticast.Address(), aMulticast.Port());
    return ret;
}

TInt Os::NetworkPort(THandle aHandle, TUint& aPort)
{
    TUint port;
    TInt ret = OsNetworkPort(aHandle, &port);
    if (ret == 0) {
        aPort = port;
    }
    return ret;
}

THandle Os::NetworkAccept(THandle aHandle, Endpoint& aClient)
{
    TIpAddress clientAddress;
    TUint32 clientPort;
    THandle handle = OsNetworkAccept(aHandle, &clientAddress, &clientPort);
    aClient.SetAddress(clientAddress);
    aClient.SetPort(clientPort);
    return handle;
}

TUint32 OpenHome::Os::NetworkGetHostByName(const Brx& aAddress)
{
    TUint32 addr;
    const TInt len = aAddress.Bytes();
    char* name = new char[len+1];
    (void)memcpy(name, aAddress.Ptr(), len);
    name[len] = '\0';
    int32_t ret = OsNetworkGetHostByName(name, &addr);
    delete[] name;
    if (ret == -1) {
        THROW(NetworkError);
    }
    return addr;
}

void OpenHome::Os::NetworkConnect(THandle aHandle, const Endpoint& aEndpoint, TUint aTimeoutMs)
{
    int32_t err = OsNetworkConnect(aHandle, aEndpoint.Address(), aEndpoint.Port(), aTimeoutMs);
    if (err != 0) {
        LOG2F(kNetwork, kError, "Os::NetworkConnect H = %d, RETURN VALUE = %d\n", aHandle, err);
        if (err == -1)  // Timeout
            THROW(NetworkTimeout);
        if (err == -2)  // Connection refused
            THROW(NetworkError);
        ASSERTS(); // invalid error
    }
}

TInt OpenHome::Os::NetworkReceiveFrom(THandle aHandle, Bwx& aBuffer, Endpoint& aEndpoint)
{
    TIpAddress address;
    TUint16 port;
    TInt ret = OsNetworkReceiveFrom(aHandle, (uint8_t*)aBuffer.Ptr(), aBuffer.MaxBytes(), &address, &port);
    if (ret != -1) {
        aEndpoint.SetAddress(address);
        aEndpoint.SetPort(port);
    }
    return ret;
}

void OpenHome::Os::NetworkSocketSetSendBufBytes(THandle aHandle, TUint aBytes)
{
    int32_t err = OsNetworkSocketSetSendBufBytes(aHandle, aBytes);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::NetworkSocketSetSendBufBytes H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkSocketSetRecvBufBytes(THandle aHandle, TUint aBytes)
{
    int32_t err = OsNetworkSocketSetRecvBufBytes(aHandle, aBytes);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::NetworkSocketSetRecvBufBytes H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkSocketSetReceiveTimeout(THandle aHandle, TUint aMilliSeconds)
{
    int32_t err = OsNetworkSocketSetReceiveTimeout(aHandle, aMilliSeconds);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketSetReceiveTimeout H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkTcpSetNoDelay(THandle aHandle)
{
    int32_t err = OsNetworkTcpSetNoDelay(aHandle);
    if(err != 0) {
        //LOG2F(kNetwork, kError, "Os::OsNetworkTcpSetNoDelay H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkSocketSetReuseAddress(THandle aHandle)
{
    int32_t err = OsNetworkSocketSetReuseAddress(aHandle);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketSetReuseAddress H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkSocketSetMulticastTtl(THandle aHandle, TUint8 aTtl)
{
    int32_t err = OsNetworkSocketSetMulticastTtl(aHandle, aTtl);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketSetMulticastTtl H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkSocketMulticastAddMembership(THandle aHandle, TIpAddress aInterface, TIpAddress aAddress)
{
    int32_t err = OsNetworkSocketMulticastAddMembership(aHandle, aInterface, aAddress);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketMulticastAddMembership H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkSocketMulticastDropMembership(THandle aHandle, TIpAddress aInterface, TIpAddress aAddress)
{
    int32_t err = OsNetworkSocketMulticastDropMembership(aHandle, aInterface, aAddress);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketMulticastDropMembership H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkSocketSetMulticastIf(THandle aHandle, TIpAddress aInterface)
{
    int32_t err = OsNetworkSocketSetMulticastIf(aHandle, aInterface);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketSetMulticastIf H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

std::vector<NetworkAdapter*>* OpenHome::Os::NetworkListAdapters(Environment& aEnv,
                                                                Net::InitialisationParams::ELoopback aUseLoopback,
                                                                const TChar* aCookie)
{
    OsNetworkAdapter* cIfs = NULL;
    int32_t err = OsNetworkListAdapters(aEnv.OsCtx(), &cIfs, (uint32_t)aUseLoopback);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::NetworkListAdapters RETURN VALUE = %d\n", err);
        THROW(NetworkError);
    }
    std::vector<NetworkAdapter*>* ifs = new std::vector<NetworkAdapter*>;
    OsNetworkAdapter* ptr = cIfs;
    while (ptr != NULL) {
        NetworkAdapter* iface = new NetworkAdapter(aEnv, ptr->iAddress, ptr->iNetMask,
                                                   ptr->iDhcpServer, ptr->iGateway,
                                                   ptr->iName, aCookie);
        ifs->push_back(iface);
        ptr = ptr->iNext;
    }
    OsNetworkFreeInterfaces(cIfs);
    return ifs;
}
