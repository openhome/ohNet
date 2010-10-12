#include <ZappTypes.h>
#include <Exception.h>
#include <Os.h>
#include <C/Os.h>
#include <Network.h>
#include <Debug.h>

using namespace Zapp;

Brn Os::GetPlatformNameAndVersion(TUint& aMajor, TUint& aMinor)
{
	char* name;
	OsGetPlatformNameAndVersion(&name, &aMajor, &aMinor);
	Brn nameBuf(name);
	return nameBuf;
}

THandle Os::NetworkCreate(ESocketType aSocketType)
{
    THandle handle = OsNetworkCreate((OsNetworkSocketType)aSocketType);
    if (handle == kHandleNull) {
        THROW(NetworkError);
    }
    return handle;
}

TInt Os::NetworkBind(THandle aHandle, Endpoint& aEndpoint)
{
    TUint16 port = aEndpoint.Port();
	TInt ret = OsNetworkBind(aHandle, aEndpoint.Address(), &port);
	if (ret == 0) {
	    aEndpoint.SetPort(port);
	}
	return ret;
}

TUint32 Zapp::Os::NetworkGetHostByName(const Brx& aAddress)
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

void Zapp::Os::NetworkConnect(THandle aHandle, const Endpoint& aEndpoint, TUint aTimeoutMs)
{
    int32_t err = OsNetworkConnect(aHandle, aEndpoint.Address(), aEndpoint.Port(), aTimeoutMs);
    if (err != 0) {
        LOG2F(kNetwork, kError, "Os::NetworkConnect H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

TInt Zapp::Os::NetworkReceiveFrom(THandle aHandle, Bwx& aBuffer, Endpoint& aEndpoint)
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

void Zapp::Os::NetworkSocketSetSendBufBytes(THandle aHandle, TUint aBytes)
{
    int32_t err = OsNetworkSocketSetSendBufBytes(aHandle, aBytes);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::NetworkSocketSetSendBufBytes H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void Zapp::Os::NetworkSocketSetReceiveTimeout(THandle aHandle, TUint aMilliSeconds)
{
    int32_t err = OsNetworkSocketSetReceiveTimeout(aHandle, aMilliSeconds);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketSetReceiveTimeout H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void Zapp::Os::NetworkTcpSetNoDelay(THandle aHandle)
{
    int32_t err = OsNetworkTcpSetNoDelay(aHandle);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkTcpSetNoDelay H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void Zapp::Os::NetworkSocketSetReuseAddress(THandle aHandle)
{
    int32_t err = OsNetworkSocketSetReuseAddress(aHandle);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketSetReuseAddress H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void Zapp::Os::NetworkSocketSetMulticastTtl(THandle aHandle, TUint8 aTtl)
{
    int32_t err = OsNetworkSocketSetMulticastTtl(aHandle, aTtl);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketSetMulticastTtl H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void Zapp::Os::NetworkSocketMulticastAddMembership(THandle aHandle, TIpAddress aAddress, TIpAddress aInterface)
{
    int32_t err = OsNetworkSocketMulticastAddMembership(aHandle, aAddress, aInterface);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketMulticastAddMembership H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void Zapp::Os::NetworkSocketMulticastDropMembership(THandle aHandle, TIpAddress aAddress, TIpAddress aInterface)
{
    int32_t err = OsNetworkSocketMulticastDropMembership(aHandle, aAddress, aInterface);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketMulticastDropMembership H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

std::vector<NetworkInterface*>* Zapp::Os::NetworkListInterfaces()
{
    OsNetworkInterface* cIfs = NULL;
    int32_t err = OsNetworkListInterfaces(&cIfs);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::NetworkListInterfaces RETURN VALUE = %d\n", err);
        THROW(NetworkError);
    }
    std::vector<NetworkInterface*>* ifs = new std::vector<NetworkInterface*>;
    OsNetworkInterface* ptr = cIfs;
    while (ptr != NULL) {
        NetworkInterface* iface = new NetworkInterface(ptr->iAddress, ptr->iNetMask, ptr->iName);
        ifs->push_back(iface);
        ptr = ptr->iNext;
    }
    OsNetworkFreeInterfaces(cIfs);
    return ifs;
}
