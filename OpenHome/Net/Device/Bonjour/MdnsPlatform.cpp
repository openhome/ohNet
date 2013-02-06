#include <OpenHome/Net/Private/MdnsPlatform.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Os.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/Globals.h>

#include <stdlib.h>
#include <string.h>

#include <OpenHome/Net/Private/mDNSEmbeddedAPI.h>

using namespace OpenHome;
using namespace OpenHome::Net;

static const mDNSInterfaceID kInterfaceId = (mDNSInterfaceID)2;

MdnsPlatform::Nif::Nif(NetworkAdapter& aNif, NetworkInterfaceInfo* aMdnsInfo)
    : iNif(aNif)
    , iMdnsInfo(aMdnsInfo)
{
    iNif.AddRef("MdnsPlatform::Nif");
}

MdnsPlatform::Nif::~Nif()
{
    iNif.RemoveRef("MdnsPlatform::Nif");
    free(iMdnsInfo);
}

NetworkAdapter& MdnsPlatform::Nif::Adapter()
{
    return iNif;
}

TIpAddress MdnsPlatform::Nif::Address() const
{
    return iNif.Address();
}

TBool MdnsPlatform::Nif::ContainsAddress(TIpAddress aAddress) const
{
    return iNif.ContainsAddress(aAddress);
}


MdnsPlatform::MdnsPlatform(Environment& aEnv, const TChar* aHost)
    : iEnv(aEnv)
    , iHost(aHost)
    , iMutex("BNJ1")
    , iMulticast(5353, Brn("224.0.0.251"))
    , iReader(aEnv, 0, iMulticast)
    , iReaderController(iReader)
    , iClient(aEnv, 5353)
    , iInterfacesLock("BNJ2")
    , iServicesLock("BNJ3")
    , iStop(false)
{
    LOG(kBonjour, "Bonjour             Constructor\n");
    iTimer = new Timer(iEnv, MakeFunctor(*this, &MdnsPlatform::TimerExpired));
    iThreadListen = new ThreadFunctor("BONJ", MakeFunctor(*this, &MdnsPlatform::Listen));
    iNextServiceIndex = 0;
    iMdns = new mDNS();
    Status status = mDNS_Init(iMdns, (mDNS_PlatformSupport*)this, mDNS_Init_NoCache, mDNS_Init_ZeroCacheSize,
                              mDNS_Init_AdvertiseLocalAddresses, InitCallback, mDNS_Init_NoInitCallbackContext);
    LOG(kBonjour, "Bonjour             Init Status %d\n", status);
    ASSERT(status >= 0);
    LOG(kBonjour, "Bonjour             Init - Start listener thread\n");
    iThreadListen->Start();
    LOG(kBonjour, "Bonjour             Constructor completed\n");
}

MdnsPlatform::~MdnsPlatform()
{
    iEnv.NetworkAdapterList().RemoveSubnetListChangeListener(iSubnetListChangeListenerId);
    mDNS_Close(iMdns);
    delete iMdns;
    delete iTimer;
    for (TUint i=0; i<(TUint)iInterfaces.size(); i++) {
        delete iInterfaces[i];
    }
}

void MdnsPlatform::TimerExpired()
{
    LOG(kBonjour, "Bonjour             Timer Expired\n");
    mDNS_Execute(iMdns);
}

void MdnsPlatform::SubnetListChanged()
{
    iInterfacesLock.Wait();
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();
    for (TInt i=(TInt)iInterfaces.size()-1; i>=0; i--) {
        if (InterfaceIndex(iInterfaces[i]->Adapter(), *subnetList) == -1) {
            delete iInterfaces[i];
            iInterfaces.erase(iInterfaces.begin()+i);
        }
    }
    for (TUint i=0; i<(TUint)subnetList->size(); i++) {
        NetworkAdapter* nif = (*subnetList)[i];
        if (InterfaceIndex(*nif) == -1) {
            AddInterface(nif);
        }
    }
    iInterfacesLock.Signal();
    nifList.DestroySubnetList(subnetList);
}

MdnsPlatform::Status MdnsPlatform::AddInterface(NetworkAdapter* aNif)
{
    Status status;
    NetworkInterfaceInfo* nifInfo = (NetworkInterfaceInfo*)calloc(1, sizeof(*nifInfo));
    nifInfo->InterfaceID = (mDNSInterfaceID)aNif->Address();
    SetAddress(nifInfo->ip, Endpoint(0, aNif->Address()));
    SetAddress(nifInfo->mask, Endpoint(0, aNif->Mask()));
    size_t len = strlen(aNif->Name());
    if (len > 64) { // max length of mDNS' interface name
        len = 64;
    }
    strncpy(nifInfo->ifname, aNif->Name(), len);
    nifInfo->Advertise = mDNStrue;
    nifInfo->McastTxRx = mDNStrue;
    status = mDNS_RegisterInterface(iMdns, nifInfo, false);
    if (status == mStatus_NoError) {
        iInterfaces.push_back(new MdnsPlatform::Nif(*aNif, nifInfo));
    }
    else {
        free(nifInfo);
    }
    return status;
}

TInt MdnsPlatform::InterfaceIndex(const NetworkAdapter& aNif)
{
    for (TUint i=0; i<(TUint)iInterfaces.size(); i++) {
        if (NifsMatch(iInterfaces[i]->Adapter(), aNif)) {
            return i;
        }
    }
    return -1;
}

TInt MdnsPlatform::InterfaceIndex(const NetworkAdapter& aNif, const std::vector<NetworkAdapter*>& aList)
{
    for (TUint i=0; i<(TUint)aList.size(); i++) {
        if (NifsMatch(*(aList[i]), aNif)) {
            return i;
        }
    }
    return -1;
}

TBool MdnsPlatform::NifsMatch(const NetworkAdapter& aNif1, const NetworkAdapter& aNif2)
{
    if (aNif1.Address() == aNif2.Address() && aNif1.Subnet() == aNif2.Subnet() && strcmp(aNif1.Name(), aNif2.Name()) == 0) {
        return true;
    }
    return false;
}

void MdnsPlatform::Listen()
{
    LOG(kBonjour, "Bonjour             Listen\n");
    
    mDNSAddr dst;
    mDNSIPPort dstport;
    SetAddress(dst, iMulticast);
    SetPort(dstport, iMulticast);
    
    mDNSAddr src;
    mDNSIPPort srcport;
    while (!iStop) {
        try {
            LOG(kBonjour, "Bonjour             Listen - Wait For Message\n");
            iReaderController.Read(iMessage);
            LOG(kBonjour, "Bonjour             Listen - Message Received\n");

            TByte* ptr = (TByte*)iMessage.Ptr();
            TUint bytes = iMessage.Bytes();
            Endpoint sender = iReaderController.Sender();
            SetAddress(src, sender);
            SetPort(srcport, sender);
            iInterfacesLock.Wait();
            TIpAddress senderAddr = sender.Address();
            mDNSInterfaceID interfaceId = (mDNSInterfaceID)0;
            for (TUint i=0; i<(TUint)iInterfaces.size(); i++) {
                if (iInterfaces[i]->ContainsAddress(senderAddr)) {
                    interfaceId = (mDNSInterfaceID)iInterfaces[i]->Address();
                    break;
                }
            }
            iInterfacesLock.Signal();
            if (interfaceId != (mDNSInterfaceID)0) {
                mDNSCoreReceive(iMdns, ptr, ptr + bytes, &src, srcport, &dst, dstport, interfaceId);
            }
            iReaderController.ReadFlush();
        }
        catch (ReaderError) {
            if (!iStop) {
                LOG(kBonjour, "Bonjour             Listen - Reader Error\n");
            }
        }
    }
}

void MdnsPlatform::SetAddress(mDNSAddr& aAddress, const Endpoint& aEndpoint)
{
    LOG(kBonjour, "Bonjour             SetAddress ");
    TByte ipv4Octets[4];
    aEndpoint.GetAddressOctets(ipv4Octets);
    aAddress.type = mDNSAddrType_IPv4;
    aAddress.ip.v4.b[0] = ipv4Octets[0];
    aAddress.ip.v4.b[1] = ipv4Octets[1];
    aAddress.ip.v4.b[2] = ipv4Octets[2];
    aAddress.ip.v4.b[3] = ipv4Octets[3];
    LOG(kBonjour, "%d.%d.%d.%d\n", aAddress.ip.v4.b[0], aAddress.ip.v4.b[1], aAddress.ip.v4.b[2], aAddress.ip.v4.b[3]);
}

void MdnsPlatform::SetPort(mDNSIPPort& aPort, const Endpoint& aEndpoint)
{
    LOG(kBonjour, "Bonjour             SetPort From Endpoint\n");
    SetPort(aPort, aEndpoint.Port());
}

void MdnsPlatform::SetPort(mDNSIPPort& aPort, TUint aValue)
{
    LOG(kBonjour, "Bonjour             SetPort %d\n", aValue);
    aPort.NotAnInteger = Arch::BigEndian2((TUint16)aValue);
}

void MdnsPlatform::SetDomainLabel(domainlabel& aLabel, const TChar* aBuffer)
{
    LOG(kBonjour, "Bonjour             SetDomainLabel: %s\n", aBuffer);
    MakeDomainLabelFromLiteralString(&aLabel, aBuffer);   
    LOG(kBonjour, "Bonjour             SetDomainLabel Length: %d\n", aLabel.c[0]);
}

void MdnsPlatform::SetDomainName(domainname& aName, const TChar* aBuffer)
{
    LOG(kBonjour, "Bonjour             SetDomainName: %s\n", aBuffer);
    MakeDomainNameFromDNSNameString(&aName, aBuffer);
    LOG(kBonjour, "Bonjour             SetDomainName Length: %d\n", aName.c[0]);
}

void MdnsPlatform::SetHostName(const TChar* aName)
{
    iHost.Set(aName);
    if (iHost.Bytes() > 0) {
        SetDomainLabel(iMdns->nicelabel, (const TChar*)iHost.Ptr());
        SetDomainLabel(iMdns->hostlabel, (const TChar*)iHost.Ptr());
    }
    else {
        SetDomainLabel(iMdns->nicelabel, "");
        SetDomainLabel(iMdns->hostlabel, "");
    }
    mDNS_SetFQDN(iMdns);
}

TUint MdnsPlatform::CreateService()
{
    LOG(kBonjour, "Bonjour             CreateService\n");
    ServiceRecordSet* service = new ServiceRecordSet();
    iServicesLock.Wait();
    TUint handle = iNextServiceIndex;
    iServices.insert(std::pair<TUint, ServiceRecordSet*>(handle, service));
    iNextServiceIndex++;
    iServicesLock.Signal();
    LOG(kBonjour, "Bonjour             CreateService - Complete\n");
    return handle;
}

void MdnsPlatform::DeregisterService(TUint aHandle)
{
    LOG(kBonjour, "Bonjour             DeregisterService\n");
    iServicesLock.Wait();
    Map::iterator it = iServices.find(aHandle);
    if (it != iServices.end()) {
        mDNS_DeregisterService(iMdns, it->second);
        iServices.erase(it);
    }
    iServicesLock.Signal();
    LOG(kBonjour, "Bonjour             DeregisterService - Complete\n");
}
    
void MdnsPlatform::RegisterService(TUint aHandle, const TChar* aName, const TChar* aType, TIpAddress aInterface, TUint aPort, const TChar* aInfo)
{
    LOG(kBonjour, "Bonjour             RegisterService\n");

    iServicesLock.Wait();
    Map::iterator it = iServices.find(aHandle);
    ASSERT(it != iServices.end());
    ServiceRecordSet* service = it->second;
    iServicesLock.Signal();
    
    domainlabel name;
    domainname type;
    domainname domain;
    domainname host;
    mDNSIPPort port;
    SetDomainLabel(name, aName);
    SetDomainName(type, aType);
    SetDomainName(domain, "local");
    SetDomainName(host, "");
    SetPort(port, aPort);
    
    mDNS_RegisterService(iMdns, service, &name, &type, &domain, 0, port, (const mDNSu8*)aInfo, (mDNSu16)strlen(aInfo), 0, 0, (mDNSInterfaceID)aInterface, ServiceCallback, this);

    LOG(kBonjour, "Bonjour             RegisterService - Complete\n");
}

void MdnsPlatform::RenameAndReregisterService(TUint aHandle, const TChar* aName)
{
    LOG(kBonjour, "Bonjour             RenameService\n");
    ServiceRecordSet* service = iServices[aHandle];
    domainlabel name;
    SetDomainLabel(name, aName);
    mDNS_RenameAndReregisterService(iMdns, service, &name);
    LOG(kBonjour, "Bonjour             RenameService - Complete\n");
}

void MdnsPlatform::InitCallback(mDNS* m, mStatus aStatus)
{
    LOG(kBonjour, "Bonjour             InitCallback\n");
    m->mDNSPlatformStatus = aStatus;
    ASSERT(aStatus == mStatus_NoError);
}

void MdnsPlatform::ServiceCallback(mDNS* /*m*/, ServiceRecordSet* /*aRecordSet*/, mStatus /*aStatus*/)
{
    LOG(kBonjour, "Bonjour             ServiceCallback\n");
}

void MdnsPlatform::Lock()
{
    iMutex.Wait();
    LOG(kBonjour, "Bonjour             Lock\n");
}

void MdnsPlatform::Unlock()
{
    TInt next = iMdns->NextScheduledEvent - iMdns->timenow_adjust;
    iTimer->FireAt(next);
    LOG(kBonjour, "Bonjour             Next Scheduled Event %d\n", next);
    LOG(kBonjour, "Bonjour             Unlock\n");
    iMutex.Signal();
}

MdnsPlatform::Status MdnsPlatform::Init()
{
    LOG(kBonjour, "Bonjour             Init\n");
    LOG(kBonjour, "Bonjour             Init - Set FQDN\n");
    SetHostName((const char*)iHost.Ptr());
    LOG(kBonjour, "Bonjour             Init - Register Interface\n");

    iInterfacesLock.Wait();
    Status status = mStatus_NoError;
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    Functor functor = MakeFunctor(*this, &MdnsPlatform::SubnetListChanged);
    iSubnetListChangeListenerId = nifList.AddSubnetListChangeListener(functor);
    std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();
    for (TUint i=0; i<(TUint)subnetList->size() && status==mStatus_NoError; i++) {
        status = AddInterface((*subnetList)[i]);
    }
    iInterfacesLock.Signal();
    nifList.DestroySubnetList(subnetList);
    if (status == mStatus_NoError) {
        mDNSCoreInitComplete(iMdns, status);
    }
    return status;
}

MdnsPlatform::Status MdnsPlatform::SendUdp(const Brx& aBuffer, const Endpoint& aEndpoint)
{
    LOG(kBonjour, "Bonjour             SendUdp\n");
    iClient.Send(aBuffer, aEndpoint);
    return 0;
}

void MdnsPlatform::Close()
{
    iTimer->Cancel();
    iStop = true;
    iThreadListen->Kill();
    iReader.Interrupt(true);
    delete iThreadListen;
}

void MdnsPlatform::AppendTxtRecord(TChar* aBuffer, TUint aLength, const TChar* aKey, const TChar* aValue)
{
    ASSERT(strlen(aKey) + strlen(aValue) + 3 <= aLength);
    *aBuffer = (TByte)(strlen(aKey) + strlen(aValue) + 1);
    aBuffer++;
    (void)strcpy(aBuffer, aKey);
    (void)strncat(aBuffer, "=", 1);
    (void)strcat(aBuffer, aValue);
}

extern "C" {    

mStatus mDNSPlatformInit(mDNS* m)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformInit\n");
    MdnsPlatform& platform = *(MdnsPlatform*)m->p;
    return platform.Init();
}

void mDNSPlatformClose(mDNS* m)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformClose\n");
    MdnsPlatform& platform = *(MdnsPlatform*)m->p;
    platform.Close();
}

mStatus mDNSPlatformSendUDP(const mDNS* m, const void* const aMessage, const mDNSu8* const aEnd,
        mDNSInterfaceID aInterface, const mDNSAddr *aAddress, mDNSIPPort aPort)
{
    if (aInterface ==  mDNSInterface_LocalOnly) {
        LOG(kBonjour, "Bonjour             mDNSPlatformSendUDP - local only, ignore\n");
        return 0;
    }
    
    LOG(kBonjour, "Bonjour             mDNSPlatformSendUDP\n");
    
    MdnsPlatform& platform = *(MdnsPlatform*)m->p;
    Brn buffer((const TByte*)aMessage, (TUint)((const TByte*)aEnd - (const TByte*)aMessage));
    ASSERT(aAddress->type == mDNSAddrType_IPv4);
    Bws<16> address;
    address.AppendPrintf("%d.%d.%d.%d",
        aAddress->ip.v4.b[0],
        aAddress->ip.v4.b[1],
        aAddress->ip.v4.b[2],
        aAddress->ip.v4.b[3] );
    
    Endpoint endpoint(Arch::BigEndian2(aPort.NotAnInteger), address);
    return platform.SendUdp(buffer, endpoint);
}

void* mDNSPlatformMemAllocate(mDNSu32 /*aLength*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformMemAllocate\n");
    return 0;
}

void  mDNSPlatformMemFree(void* /*aPtr*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformMemFree\n");
    ASSERTS();
}

mDNSInterfaceID mDNSPlatformInterfaceIDfromInterfaceIndex(mDNS* /*m*/, mDNSu32 /*aIndex*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformInterfaceIDfromInterfaceIndex\n");
    ASSERTS(); // not sure what an interface index is and can't find any mDNS callers for this function
    return 0;
}

mDNSu32 mDNSPlatformInterfaceIndexfromInterfaceID(mDNS* /*m*/, mDNSInterfaceID /*aId*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformInterfaceIndexFromInterfaceID\n");
    ASSERTS(); // not sure what an interface index is and can't find any mDNS callers for this function
    return 0;
}

// mDNS core calls this routine when it wants to prevent
// the platform from reentering mDNS core code.

void mDNSPlatformLock(const mDNS* m)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformLock\n");
    MdnsPlatform& platform = *(MdnsPlatform*)m->p;
    platform.Lock();
}

// mDNS core calls this routine when it release the lock taken by
// mDNSPlatformLock and allow the platform to reenter mDNS core code.

void mDNSPlatformUnlock (const mDNS* m)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformUnlock\n");
    MdnsPlatform& platform = *(MdnsPlatform*)m->p;
    platform.Unlock();
}

// mDNS core calls this routine to copy C strings.
// On the Posix platform this maps directly to the ANSI C strcpy.

void mDNSPlatformStrCopy(const void *src, void *dst)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformStrCopy\n");
    strcpy((char*)dst, (char*)src);
}

// mDNS core calls this routine to get the length of a C string.
// On the Posix platform this maps directly to the ANSI C strlen.

mDNSu32 mDNSPlatformStrLen(const void *src)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformStrLen\n");
    return (mDNSu32)strlen((char*)src);
}

// mDNS core calls this routine to copy memory.
// On the Posix platform this maps directly to the ANSI C memcpy.

void mDNSPlatformMemCopy(const void *src, void *dst, mDNSu32 len)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformMemCopy\n");
    memcpy(dst, src, len);
}

// mDNS core calls this routine to test whether blocks of memory are byte-for-byte
// identical. On the Posix platform this is a simple wrapper around ANSI C memcmp.

mDNSBool mDNSPlatformMemSame(const void *src, const void *dst, mDNSu32 len)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformMemSame\n");
    return (memcmp(dst, src, len) == 0);
}

// mDNS core calls this routine to clear blocks of memory.
// On the Posix platform this is a simple wrapper around ANSI C memset.

void mDNSPlatformMemZero(void *dst, mDNSu32 len)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformMemZero\n");
    memset(dst, 0, len);
}

static const TUint kMaxLogMsgBytes = 200;

void LogMsg(const char *format, ...)
{
#ifdef DEFINE_TRACE
    va_list args;
    va_start(args, format);
    // not all messages are errors but enough are that its handy to log everything here if we're interested in errors
    if(Debug::TestLevel(Debug::kBonjour) || Debug::TestLevel(Debug::kError)) {
        Bws<kMaxLogMsgBytes> msg;
        TUint written = mDNS_vsnprintf((char*)msg.Ptr(), msg.MaxBytes(), format, args);
        msg.SetBytes(written);
        Log::Print(msg);
        Log::Print("\n");
    }
    va_end(args);
#endif
}

mDNSu32 mDNSPlatformRandomSeed()
{
    LOG(kBonjour, "Bonjour             mDNSPlatformRandomSeed\n");
    return 0xdeadbeef;
}

// Time handlers

mDNSs32  mDNSPlatformOneSecond = 1000;

mStatus mDNSPlatformTimeInit()
{
    LOG(kBonjour, "Bonjour             mDNSPlatformTimeInit\n");
    return mStatus_NoError;
}

mDNSs32  mDNSPlatformRawTime()
{
    TUint time = Os::TimeInMs(OpenHome::gEnv->OsCtx());
    LOG(kBonjour, "Bonjour             mDNSPlatformRawTime: %d\n", time);
    return time;
}

mDNSs32 mDNSPlatformUTC()
{
    TUint time = (Os::TimeInMs(OpenHome::gEnv->OsCtx()) / 1000) + 1229904000; // 1st Jan 2009
    LOG(kBonjour, "Bonjour             mDNSPlatformUTC: %d\n", time);
    return time;
}

// TCP handlers

mStatus mDNSPlatformTCPConnect(const mDNSAddr*, mDNSOpaque16, mDNSInterfaceID, TCPConnectionCallback, void*, int*)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformTCPConnect\n");
    return mStatus_UnsupportedErr;
}

void mDNSPlatformTCPCloseConnection(int)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformTCPCloseConnection\n");
}

int mDNSPlatformReadTCP(int, void*, int)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformReadTCP\n");
    return 0;
}

int mDNSPlatformWriteTCP(int, const char*, int)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformWriteTCP\n");
    return 0;
}

} // extern "C"

