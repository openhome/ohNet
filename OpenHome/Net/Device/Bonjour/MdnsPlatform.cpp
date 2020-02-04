#include <OpenHome/Net/Private/MdnsPlatform.h>
#include <OpenHome/Functor.h>
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
#include <OpenHome/Net/Private/dnssec.h>

using namespace OpenHome;
using namespace OpenHome::Net;

extern "C" {
    mDNS mDNSStorage; // required by dnssd_clientshim.c
}

// MdnsDevice
MdnsDevice::MdnsDevice(const Brx& aType, const Brx& aFriendlyName, const Brx& aUglyName, const Brx& aIpAddress, TUint aPort)
{
    iType.Set(aType);
    iFriendlyName.Set(aFriendlyName);
    iUglyName.Set(aUglyName);
    iIpAddress.Set(aIpAddress);
    iPort = aPort;
}

const Brx& MdnsDevice::Type()
{
    return iType;
}

const Brx& MdnsDevice::FriendlyName()
{
    return iFriendlyName;
}

const Brx& MdnsDevice::UglyName()
{
    return iUglyName;
}

const Brx& MdnsDevice::IpAddress()
{
    return iIpAddress;
}

const TUint MdnsDevice::Port()
{
    return iPort;
}

// MdnsPlatform

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

NetworkInterfaceInfo& MdnsPlatform::Nif::Info()
{
    return *iMdnsInfo;
}

TIpAddress MdnsPlatform::Nif::Address() const
{
    return iNif.Address();
}

TBool MdnsPlatform::Nif::ContainsAddress(TIpAddress aAddress) const
{
    return iNif.ContainsAddress(aAddress);
}


// MdnsPlatform::MdnsService
MdnsPlatform::MdnsService::MdnsService(mDNS& aMdns)
    : iMdns(aMdns)
    , iAction(eInvalid)
{
}

void MdnsPlatform::MdnsService::Set(MdnsServiceAction aAction, TUint aHandle, ServiceRecordSet& aService, const TChar* aName, const TChar* aType, TIpAddress aInterface, TUint aPort, const TChar* aInfo)
{
    iAction = aAction;
    iHandle = aHandle;
    iService = &aService;

    if(aName==NULL)
    {
        iName.Replace(Brx::Empty());
    }
    else
    {
        // truncate the name if necessary
        Brn name(aName);
        TUint maxBytes = iName.MaxBytes()-1; // leave room for NULL terminator

        if (name.Bytes()>maxBytes)
        {
            name.Set((TByte*)aName, maxBytes);
        }

        iName.Replace(name);
    }

    iType.Replace((aType == NULL) ? "" : aType);
    iInterface = aInterface;
    iPort = aPort;
    iInfo.Replace((aInfo == NULL) ? "" : aInfo);
}

TUint MdnsPlatform::MdnsService::PerformAction()
{
    switch (iAction)
    {
    case eRegister:
        return Register();
    case eDeregister:
        return Deregister();
    case eRenameAndReregister:
        return RenameAndReregister();
    case eInvalid:
    default:
        ASSERTS();
        return 0;
    }
}

TUint MdnsPlatform::MdnsService::Register()
{
    domainlabel name;
    domainname type;
    domainname domain;
    domainname host;
    mDNSIPPort port;
    SetDomainLabel(name, iName.PtrZ());
    SetDomainName(type, iType.PtrZ());
    SetDomainName(domain, "local");
    SetDomainName(host, "");
    SetPort(port, iPort);
#ifndef DEFINE_WINDOWS_UNIVERSAL
    return mDNS_RegisterService(&iMdns, iService, &name, &type, &domain, 0, port, (const mDNSu8*)iInfo.PtrZ(), (mDNSu16)strlen(iInfo.PtrZ()), 0, 0, (mDNSInterfaceID)iInterface, &MdnsPlatform::ServiceCallback, this, 0);
#else // DEFINE_WINDOWS_UNIVERSAL
    return 0;
#endif // DEFINE_WINDOWS_UNIVERSAL
}

TUint MdnsPlatform::MdnsService::Deregister()
{
    return mDNS_DeregisterService(&iMdns, iService);
}

TUint MdnsPlatform::MdnsService::RenameAndReregister()
{
    domainlabel name;
    SetDomainLabel(name, iName.PtrZ());
    return mDNS_RenameAndReregisterService(&iMdns, iService, &name);
}


// ReadWriteLock

ReadWriteLock::ReadWriteLock(const TChar* aId)
    : iId(aId)
    , iReaderCount(0)
    , iLockReaders("RWLR")
    , iLockWriter("RWLW")
{
}

void ReadWriteLock::AcquireReadLock()
{
    AutoMutex amx(iLockReaders);
    iReaderCount++;
    if (iReaderCount == 1) {
        iLockWriter.Wait();
    }
}

void ReadWriteLock::ReleaseReadLock()
{
    AutoMutex amx(iLockReaders);
    ASSERT(iReaderCount > 0);
    iReaderCount--;
    if (iReaderCount == 0) {
        iLockWriter.Signal();
    }
}

void ReadWriteLock::AcquireWriteLock()
{
    iLockWriter.Wait();
}

void ReadWriteLock::ReleaseWriteLock()
{
    iLockWriter.Signal();
}


// MulticastListener

const TUint MulticastListener::kMaxMessageBytes;

MulticastListener::MulticastListener(Environment& aEnv, IMdnsMulticastPacketReceiver& aReceiver)
    : iMulticast(5353, Brn("224.0.0.251"))
    , iEnv(aEnv)
    , iReceiver(aReceiver)
    , iReader(NULL)
    , iReaderController(NULL)
    , iMulticastLock("MulticastListener")
    , iSemReader("MLSR", 0)
    , iThreadListen(NULL)
    , iStop(false)
    , iLock("MLLL")
{
    iThreadListen = new ThreadFunctor("MulticastListener", MakeFunctor(*this, &MulticastListener::ThreadListen));
}

MulticastListener::~MulticastListener()
{
    // ::Stop() must have been called prior to this.
    ASSERT(iThreadListen == NULL);
    ASSERT(iStop == true);
    delete iReaderController;
    delete iReader;
}

void MulticastListener::Start()
{
    ASSERT(iThreadListen != NULL);
    iThreadListen->Start();
}

void MulticastListener::Stop()
{
    ASSERT(iThreadListen != NULL);

    {
        AutoMutex amx(iLock);
        iStop = true;
    }

    {
        iMulticastLock.AcquireReadLock();
        if (iReader != NULL) {
            iReaderController->ReadInterrupt();
            iReader->Interrupt(true);
        }
        iMulticastLock.ReleaseReadLock();
    }
    iSemReader.Signal();

    iThreadListen->Kill();
    delete iThreadListen;
    iThreadListen = NULL;
}

void MulticastListener::Clear()
{
    iMulticastLock.AcquireReadLock();
    if (iReader != NULL) {
        iReaderController->ReadInterrupt();
        iReader->Interrupt(true);
    }
    iMulticastLock.ReleaseReadLock();


    iMulticastLock.AcquireWriteLock();
    // iReader no longer available. Clear any signals.
    iSemReader.Clear();

    delete iReaderController;
    iReaderController = NULL;
    delete iReader;
    iReader = NULL;
    iMulticastLock.ReleaseWriteLock();
}

void MulticastListener::Bind(TIpAddress aAddress)
{
    // Throws NetworkError if unable to listen for multicast on aAddress.

    {
        AutoMutex amx(iLock);
        ASSERT(!iStop);
    }

    const Endpoint epAddr(0, aAddress);
    TByte addrOctets[4];
    epAddr.GetAddressOctets(addrOctets);

    iMulticastLock.AcquireWriteLock();

    // This must be first call to Bind(), or Clear() must have been called prior to this.
    ASSERT(iReader == NULL);
    ASSERT(iReaderController == NULL);

    LOG(kBonjour, "MulticastListener::Bind aAddress: %u (%u.%u.%u.%u)\n", aAddress, addrOctets[0], addrOctets[1], addrOctets[2], addrOctets[3]);
    try {
        iReader = new SocketUdpMulticast(iEnv, aAddress, iMulticast);
        iReaderController = new UdpReader(*iReader);
        iSemReader.Signal();
        LOG(kBonjour, "MulticastListener::Bind successfully created multicast socket on %u.%u.%u.%u\n", addrOctets[0], addrOctets[1], addrOctets[2], addrOctets[3]);
    }
    catch (const NetworkError&) {
        LOG(kBonjour, "MulticastListener::Bind NetworkError creating multicast socket on %u.%u.%u.%u\n", addrOctets[0], addrOctets[1], addrOctets[2], addrOctets[3]);
        delete iReaderController;
        iReaderController = NULL;
        delete iReader;
        iReader = NULL;
        iMulticastLock.ReleaseWriteLock();

        throw;
    }

    iMulticastLock.ReleaseWriteLock();
}

void MulticastListener::ThreadListen()
{
    LOG(kBonjour, "MulticastListener::ThreadListen\n");

    TBool waitOnReady = false;

    while (!iStop) {

        if (waitOnReady) {
            iSemReader.Wait();
            waitOnReady = false;
        }

        iMulticastLock.AcquireReadLock();
        if (iReader == NULL) {
            waitOnReady = true;
        }
        else {
            try {
                LOG(kBonjour, "MulticastListener::ThreadListen - Wait For Message\n");
                iReaderController->Read(iMessage);
                LOG(kBonjour, "MulticastListener::ThreadListen - Message Received\n");
                const Endpoint src = iReaderController->Sender();
                iReceiver.ReceiveMulticastPacket(iMessage, src, iMulticast);

                iReaderController->ReadFlush();
            }
            catch (ReaderError) {
                if (!iStop) {
                    LOG(kBonjour, "MulticastListener::ThreadListen - Reader Error\n");
                }
            }
        }
        iMulticastLock.ReleaseReadLock();
    }
}


// MulticastListeners

const TUint MulticastListeners::kPreAllocatedListenerCount;

MulticastListeners::MulticastListeners(Environment& aEnv, IMdnsMulticastPacketReceiver& aReceiver)
    : iEnv(aEnv)
    , iReceiver(aReceiver)
    , iStarted(false)
    , iStopped(false)
    , iLock("MULL")
{
    AutoMutex amx(iLock);
    for (TUint i=0; i<kPreAllocatedListenerCount; i++) {
        iListeners.push_back(new MulticastListener(iEnv, aReceiver));
    }
}

MulticastListeners::~MulticastListeners()
{
    AutoMutex amx(iLock);
    ASSERT(iStopped);
    for (TUint i=0; i<iListeners.size(); i++) {
        delete iListeners[i];
    }
}

void MulticastListeners::Start()
{
    AutoMutex amx(iLock);
    for (TUint i=0; i<iListeners.size(); i++) {
        iListeners[i]->Start();
    }
    iStarted = true;
}

void MulticastListeners::Stop()
{
    AutoMutex amx(iLock);
    for (TUint i=0; i<iListeners.size(); i++) {
        iListeners[i]->Stop();
    }
    iStopped = true;
}

void MulticastListeners::Rebind(std::vector<NetworkAdapter*>& aAdapters)
{
    // For ease, clear all current listeners and rebind later, if appropriate.
    AutoMutex amx(iLock);
    for (TUint i=0; i<iListeners.size(); i++) {
        iListeners[i]->Clear();
    }

    TUint nextListenerIdx = 0;
    for (TUint i=0; i<aAdapters.size(); i++) {
        const TIpAddress addr = aAdapters[i]->Address();
        const Endpoint epAddr(0, addr);
        TByte addrOctets[4];
        epAddr.GetAddressOctets(addrOctets);

        LOG(kBonjour, "MulticastListeners::Rebind aAdapters.size(): %u, i: %u, addrOctets: %u.%u.%u.%u\n", aAdapters.size(), i, addrOctets[0], addrOctets[1], addrOctets[2], addrOctets[3]);
        if (addrOctets[0] != 127) {
            // Found a non-localhost adapter.

            ASSERT(nextListenerIdx <= iListeners.size());   // Check no errors incrementing nextListenerIndex.
            if (nextListenerIdx == iListeners.size()) {
                LOG(kBonjour, "MulticastListeners::Rebind Creating new listener. nextListenerIdx: %u\n", nextListenerIdx);
                // No listener available for use. Create a new one.
                MulticastListener* listener = new MulticastListener(iEnv, iReceiver);
                if (iStarted && !iStopped) {
                    listener->Start();
                }
                iListeners.push_back(listener);
            }

            try {
                // Throws NetworkError if unable to bind to any (non-localhost) adapter.
                iListeners[nextListenerIdx]->Bind(aAdapters[i]->Address());
                nextListenerIdx++;
            }
            catch (const NetworkError&) {
                // Failed to create multicast socket on adapter. Clear all listeners and rethrow exception.
                LOG(kBonjour, "MulticastListeners::Rebind NetworkError creating multicast socket on %u.%u.%u.%u\n", addrOctets[0], addrOctets[1], addrOctets[2], addrOctets[3]);
                for (TUint j=0; j<iListeners.size(); j++) {
                    iListeners[j]->Clear();
                }
                throw;
            }
        }
    }
}


// MdnsPlatform

const TChar* MdnsPlatform::kNifCookie = "Bonjour";

MdnsPlatform::MdnsPlatform(Environment& aEnv, const TChar* aHost, TBool aHasCache)
    : iEnv(aEnv)
    , iHost(aHost)
    , iHasCache(aHasCache)
    , iTimerLock("BNJ4")
    , iListeners(iEnv, *this)
    , iClient(aEnv, 5353)
    , iInterfacesLock("BNJ2")
    , iServicesLock("BNJ3")
    , iFifoFree(kMaxQueueLength)
    , iFifoPending(kMaxQueueLength)
    , iSem("BNJS", 0)
    , iStop(false)
    , iTimerDisabled(false)
    , iDiscoveryLock("BNJ6")
    , iPrevTimerRequest(0)
    , iMulticastReceiveLock("BNJ7")
{
    LOG(kBonjour, "Bonjour             Constructor\n");
    iTimer = new Timer(iEnv, MakeFunctor(*this, &MdnsPlatform::TimerExpired), "MdnsPlatform");
    iNextServiceIndex = 0;
    iMdns = &mDNSStorage;

    Status status = mStatus_NoError;
    if (iHasCache) {
        (void)memset(iMdnsCache, 0, sizeof iMdnsCache);
        status = mDNS_Init(iMdns, (mDNS_PlatformSupport*)this, iMdnsCache, kRRCacheSize, mDNS_Init_AdvertiseLocalAddresses,
                 StatusCallback, mDNS_Init_NoInitCallbackContext);
    }
    else {
        status = mDNS_Init(iMdns, (mDNS_PlatformSupport*)this, mDNS_Init_NoCache, mDNS_Init_ZeroCacheSize, mDNS_Init_AdvertiseLocalAddresses,
                 StatusCallback, mDNS_Init_NoInitCallbackContext);
    }
    LOG(kBonjour, "Bonjour             Init Status %d\n", status);
    ASSERT(status >= 0);
    LOG(kBonjour, "Bonjour             Init - Start listener thread\n");
    iListeners.Start();
    LOG(kBonjour, "Bonjour             Constructor completed\n");

    for (TUint i=0; i<kMaxQueueLength; i++) {
        iFifoFree.Write(new MdnsService(*iMdns));
    }

    LOG(kBonjour, "Bonjour             Init - Start service thread\n");
    iThreadService = new ThreadFunctor("MdnsServiceThread", MakeFunctor(*this, &MdnsPlatform::ServiceThread));
    iThreadService->Start();
}

MdnsPlatform::~MdnsPlatform()
{
    iEnv.NetworkAdapterList().RemoveSubnetListChangeListener(iSubnetListChangeListenerId);
    iEnv.NetworkAdapterList().RemoveCurrentChangeListener(iCurrentAdapterChangeListenerId);
    iTimerLock.Wait();
    iTimerDisabled = true;
    iTimerLock.Signal();
    delete iTimer;
    iTimer = NULL;
#ifndef DEFINE_WINDOWS_UNIVERSAL
    for (TUint i=0; i<iSdRefs.size(); i++) {
        DNSServiceRefDeallocate(*iSdRefs[i]);
    }
#endif // !DEFINE_WINDOWS_UNIVERSAL
    mDNS_Close(iMdns);
    Map::iterator it = iServices.begin();
    while (it != iServices.end()) {
        delete it->second;
        it++;
    }
    for (TUint i=0; i<(TUint)iInterfaces.size(); i++) {
        delete iInterfaces[i];
    }
    for (TUint i=0; i<iDynamicCache.size(); i++) {
        free(iDynamicCache[i]);
    }
    iFifoFree.ReadInterrupt(true);
    iFifoFree.ReadInterrupt(false);
    while (iFifoFree.SlotsUsed() > 0) {
        delete iFifoFree.Read();
    }
    iFifoPending.ReadInterrupt(false);
    while (iFifoPending.SlotsUsed() > 0) {
        delete iFifoPending.Read();
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
    NetworkAdapter* current = iEnv.NetworkAdapterList().CurrentAdapter(kNifCookie).Ptr();
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();
    for (TInt i=(TInt)iInterfaces.size()-1; i>=0; i--) {
        // Remove adapters with subnets no longer available and which don't
        // match the currently selected adapter (if there is one).
        if (InterfaceIndex(iInterfaces[i]->Adapter(), *subnetList) == -1
                || (current != NULL && current->Address() != iInterfaces[i]->Adapter().Address())) {
            mDNS_DeregisterInterface(iMdns, &iInterfaces[i]->Info(), false);
            delete iInterfaces[i];
            iInterfaces.erase(iInterfaces.begin()+i);
        }
    }
    if (current == NULL) { // no adapter selected; add new subnets
        for (TUint i=0; i<(TUint)subnetList->size(); i++) {
            NetworkAdapter* nif = (*subnetList)[i];
            if (InterfaceIndex(*nif) == -1) {
                AddInterface(nif);
            }
        }
    }
    if (current != NULL) {
        if (iInterfaces.size() == 0) { // current adapter is on a newly added subnet
            AddInterface(current);
        }
        // Set multicast iface in case current adapter was previously in a list
        // subnets so no multicast iface was set.
        iClient.SetMulticastIf(current->Address());
        current->RemoveRef(kNifCookie);
    }
    iInterfacesLock.Signal();

    iListeners.Rebind(*subnetList);     // May throw NetworkError.
    nifList.DestroySubnetList(subnetList);
}

void MdnsPlatform::CurrentAdapterChanged()
{
    iInterfacesLock.Wait();
    NetworkAdapter* current = iEnv.NetworkAdapterList().CurrentAdapter(kNifCookie).Ptr();
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();

    if (current != NULL) {
        // Remove existing interface(s) if not belonging to current adapter,
        // then add current adapter if it didn't exist before.
        for (TInt i=(TInt)iInterfaces.size()-1; i>=0; i--) {
            if (InterfaceIndex(iInterfaces[i]->Adapter(), *subnetList) == -1
                || (current != NULL && current->Address() != iInterfaces[i]->Adapter().Address())) {
                mDNS_DeregisterInterface(iMdns, &iInterfaces[i]->Info(), false);
                    delete iInterfaces[i];
                    iInterfaces.erase(iInterfaces.begin()+i);
            }
        }
        if (iInterfaces.size() == 0) { // current adapter is on a newly added subnet
            AddInterface(current);
        }
        // Set multicast iface in case current adapter was previously in a list
        // subnets so no multicast iface was set.
        iClient.SetMulticastIf(current->Address());
        current->RemoveRef(kNifCookie);
    }
    else {
        // No adapter selected.
        // First, check if selected interface should be removed.
        for (TInt i=(TInt)iInterfaces.size()-1; i>=0; i--) {
            if (InterfaceIndex(iInterfaces[i]->Adapter(), *subnetList) == -1) {
                mDNS_DeregisterInterface(iMdns, &iInterfaces[i]->Info(), false);
                delete iInterfaces[i];
                iInterfaces.erase(iInterfaces.begin()+i);
            }
        }

        // Then, re-add all subnets that aren't already added.
        for (TUint i=0; i<(TUint)subnetList->size(); i++) {
            NetworkAdapter* nif = (*subnetList)[i];
            if (InterfaceIndex(*nif) == -1) {
                AddInterface(nif);
            }
        }
    }
    iInterfacesLock.Signal();

    iListeners.Rebind(*subnetList);     // May throw NetworkError.
    nifList.DestroySubnetList(subnetList);
}

MdnsPlatform::Status MdnsPlatform::AddInterface(NetworkAdapter* aNif)
{
    Status status;
    NetworkInterfaceInfo* nifInfo = (NetworkInterfaceInfo*)calloc(1, sizeof(*nifInfo));
#ifndef DEFINE_WINDOWS_UNIVERSAL
    nifInfo->InterfaceID = (mDNSInterfaceID)aNif->Address();
#endif // DEFINE_WINDOWS_UNIVERSAL    
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

void MdnsPlatform::ReceiveMulticastPacket(const Brx& aMsg, const Endpoint aSrc, const Endpoint aDst)
{
    mDNSAddr dst;
    mDNSIPPort dstport;
    SetAddress(dst, aDst);
    SetPort(dstport, aDst);

    mDNSAddr src;
    mDNSIPPort srcport;

    TByte* ptr = (TByte*)aMsg.Ptr();
    TUint bytes = aMsg.Bytes();
    SetAddress(src, aSrc);
    SetPort(srcport, aSrc);

    mDNSInterfaceID interfaceId = (mDNSInterfaceID)0;
    {
        AutoMutex amx(iInterfacesLock);
        TIpAddress senderAddr = aSrc.Address();
        for (TUint i=0; i<(TUint)iInterfaces.size(); i++) {
            if (iInterfaces[i]->ContainsAddress(senderAddr)) {
#ifndef DEFINE_WINDOWS_UNIVERSAL
                interfaceId = (mDNSInterfaceID)iInterfaces[i]->Address();
#endif // DEFINE_WINDOWS_UNIVERSAL
                break;
            }
        }
    }

    if (interfaceId != (mDNSInterfaceID)0) {
        AutoMutex amx(iMulticastReceiveLock);
        DNSMessage* msg = reinterpret_cast<DNSMessage*>(ptr);
        mDNSCoreReceive(iMdns, msg, ptr + bytes, &src, srcport, &dst, dstport, interfaceId);
    }
}

void MdnsPlatform::ServiceThread()
{
    /* mDNS_Register, mDNS_Deregister and mDNS_RenameAndReregister calls are
     * all asynchronous.
     *
     * We need to ensure one call on a service record has been completed before
     * we initiate another call. Otherwise, if we try deregister and register a
     * service the register call may fail as we could still be waiting on the
     * deregister call to respond.
     *
     * From profiling, calls to register can take ~600ms and calls to
     * deregister can take ~4000ms before the callback is made, so we store a
     * queue of pending calls and have a thread that processes them in order.
     */
    while (!iStop) {
        try {
            MdnsService* service = iFifoPending.Read();
            TUint status = service->PerformAction();
            iFifoFree.Write(service);
            if (status == mStatus_NoError) {
                iSem.Wait();
            }
        }
        catch (FifoReadError&)
        {}
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
    void DoSetHostName();
}

void MdnsPlatform::DoSetHostName()
{
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
        MdnsService* mdnsService;
        try {
            mdnsService = iFifoFree.Read();
        }
        catch (FifoReadError&) {
            iServicesLock.Signal();
            return;
        }
        mdnsService->Set(eDeregister, aHandle, *it->second, NULL, NULL, 0, 0, NULL);
        iFifoPending.Write(mdnsService);
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
    MdnsService* mdnsService;

    try {
        mdnsService = iFifoFree.Read();
    }
    catch (FifoReadError&) {
        return;
    }
    mdnsService->Set(eRegister, aHandle, *service, aName, aType, aInterface, aPort, aInfo);
    iFifoPending.Write(mdnsService);

    LOG(kBonjour, "Bonjour             RegisterService - Complete\n");
}

void MdnsPlatform::RenameAndReregisterService(TUint aHandle, const TChar* aName)
{
    LOG(kBonjour, "Bonjour             RenameAndReregisterService\n");
    iServicesLock.Wait();
    ServiceRecordSet* service = iServices[aHandle];
    iServicesLock.Signal();
    MdnsService* mdnsService;

    try {
        mdnsService = iFifoFree.Read();
    }
    catch (FifoReadError) {
        return;
    }
    mdnsService->Set(eRenameAndReregister, aHandle, *service, aName, NULL, 0, 0, NULL);
    iFifoPending.Write(mdnsService);

    LOG(kBonjour, "Bonjour             RenameAndReregisterService - Complete\n");
}

void MdnsPlatform::ServiceCallback(mDNS* m, ServiceRecordSet* aRecordSet, mStatus aStatus)
{
    LOG(kBonjour, "Bonjour             ServiceCallback - aRecordSet: %p, aStatus: %d\n", aRecordSet, aStatus);

    MdnsPlatform& platform = *(MdnsPlatform*) m->p;
    platform.iSem.Signal();
}

void MdnsPlatform::Lock()
{
    iMutex.Lock();
    LOG(kBonjour, "Bonjour             Lock\n");
}

void MdnsPlatform::Unlock()
{
    TInt next = iMdns->NextScheduledEvent - iMdns->timenow_adjust;
    iTimerLock.Wait();
    if (next < 0) {
        LOG(kBonjour, "Bonjour             Ignore Impossible Event: %d\n", next);
    }
    else if (iPrevTimerRequest == next) {
        LOG(kBonjour, "Bonjour             Ignore Duplicate Event %d\n", next);
    }
    else {
        iPrevTimerRequest = next;
        if (!iTimerDisabled) {
            iTimer->FireAt(next);
        }
        LOG(kBonjour, "Bonjour             Next Scheduled Event %d\n", next);
    }
    iTimerLock.Signal();
    LOG(kBonjour, "Bonjour             Unlock\n");
    iMutex.Unlock();
}

MdnsPlatform::Status MdnsPlatform::Init()
{
    LOG(kBonjour, "Bonjour             Init\n");
    LOG(kBonjour, "Bonjour             Init - Set FQDN\n");
    DoSetHostName();
    LOG(kBonjour, "Bonjour             Init - Register Interface\n");

    iInterfacesLock.Wait();
    Status status = mStatus_NoError;
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    Functor functorSubnet = MakeFunctor(*this, &MdnsPlatform::SubnetListChanged);
    iSubnetListChangeListenerId = nifList.AddSubnetListChangeListener(functorSubnet, "MdnsPlatform-subnet");
    Functor functorAdapter = MakeFunctor(*this, &MdnsPlatform::CurrentAdapterChanged);
    iCurrentAdapterChangeListenerId = nifList.AddCurrentChangeListener(functorAdapter, "MdnsPlatform-current");

    // Subnet list changed and current adapter changed callbacks do not happen on registration, so set up interface list here.
    NetworkAdapter* current = iEnv.NetworkAdapterList().CurrentAdapter(kNifCookie).Ptr();
    if (current == NULL) { // Listening on all adapters.
        std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();
        for (TUint i=0; i<(TUint)subnetList->size() && status==mStatus_NoError; i++) {
            status = AddInterface((*subnetList)[i]);
        }
        nifList.DestroySubnetList(subnetList);
    }
    else { // Using a single adapter.
        status = AddInterface(current);
        iClient.SetMulticastIf(current->Address());
        current->RemoveRef(kNifCookie);
    }

    // Attempt initial bind of multicast adapters, as subnet list changed and current adapter changed callbacks do not happen on registration.
    std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();
    // This will throw NetworkAdapter if there is a valid (non-localhost) adapter which is unable to listen for multicast.
    // Allow exception to bubble up, as can't use mDNS without listening for multicast!
    iListeners.Rebind(*subnetList);
    nifList.DestroySubnetList(subnetList);

    iInterfacesLock.Signal();
    if (status == mStatus_NoError) {
        mDNSCoreInitComplete(iMdns, status);
    }
    return status;
}

MdnsPlatform::Status MdnsPlatform::GetPrimaryInterface(TIpAddress& aInterface)
{
    LOG(kBonjour, "Bonjour             GetPrimaryInterface ");
    Status status = mStatus_NoError;
    iInterfacesLock.Wait();
    if (iInterfaces.size() == 0) {
        status = mStatus_NotInitializedErr;
        aInterface = 0;
    }
    if (status != mStatus_NotInitializedErr) {
        aInterface = iInterfaces[0]->Address();
        if (aInterface == 0) {
            status = mStatus_NotInitializedErr;
            aInterface = 0;
        }
    }
    iInterfacesLock.Signal();

    Bws<Endpoint::kMaxAddressBytes> addr;
    Endpoint::AppendAddress(addr, aInterface);
    LOG(kBonjour, addr);
    LOG(kBonjour, "\n");

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
    ASSERT(iTimerDisabled);
    iStop = true;
    iListeners.Stop();

    iThreadService->Kill();
    iFifoPending.ReadInterrupt(true);
    iSem.Signal();
    delete iThreadService;
}

void MdnsPlatform::AppendTxtRecord(Bwx& aBuffer, const TChar* aKey, const TChar* aValue)
{
    ASSERT((strlen(aKey) + strlen(aValue) + 3) <= (aBuffer.MaxBytes()-aBuffer.Bytes()));
    TByte length = (TByte)(strlen(aKey) + strlen(aValue) + 1);
    aBuffer.Append(length);
    aBuffer.Append(aKey);
    aBuffer.Append('=');
    aBuffer.Append(aValue);
}

extern "C" 
void ResolveReply(
    DNSServiceRef       /*sdRef*/,
    DNSServiceFlags     flags,
    uint32_t            interfaceIndex,
    DNSServiceErrorType errorCode,
    const char          *fullname,
    const char          *hosttarget,
    uint16_t            port,        /* In network byte order */
    const unsigned char *ipAddr,
    const char          *regtype,
    uint16_t            txtLen,
    const unsigned char *txtRecord,
    void                *context)
{
    if (errorCode == kDNSServiceErr_NoError) {
        Brn friendlyName(fullname);
        Brn devtype(regtype);
        Brn uglyName(hosttarget);
        Bws<20> ip;
        ip.AppendPrintf("%d.%d.%d.%d", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
        Bwh text(txtLen);
        TUint8 length = 0;
        for (const unsigned char* ptr = txtRecord; ptr < txtRecord + txtLen; ptr += length) {
            length = *ptr;
            if (ptr > txtRecord) {
                text.Append(' ');
            }
            text.Append(++ptr, length);
        }
        LOG(kBonjour, "mDNS Device discovered: %.*s, target=%.*s, ip=%.*s, port=%d, text=%.*s\n", PBUF(friendlyName), PBUF(uglyName), PBUF(ip), port, PBUF(text));
        MdnsPlatform& platform = *(MdnsPlatform*)context;
        platform.DeviceDiscovered(devtype, friendlyName, uglyName, ip, port);
    }
    else {
        LOG_ERROR(kBonjour, "mDNS resolve reply: flags=%d, index=%u, err=%d, fullname=%s, hosttarget=%s, txtRecord=%s, context=%p, port=%d, txtLen=%d\n",
               flags, interfaceIndex, (TInt)errorCode, fullname, hosttarget, txtRecord, context, port, txtLen);
    }
}

#ifdef DEFINE_WINDOWS_UNIVERSAL
TBool MdnsPlatform::FindDevices(const TChar* /*aServiceName*/)
{
    LOG_ERROR(kBonjour, "MdnsPlatform::FindDevices not supported for WINDOW_UNIVERSAL builds\n");
    return false;
}
#else
extern "C" 
void BrowseReply(DNSServiceRef sdRef,
    DNSServiceFlags      flags,
    uint32_t             interfaceIndex,
    DNSServiceErrorType  errorCode,
    const char           *serviceName,
    const char           *regtype,
    const char           *replyDomain,
    void                 *context)
{
    if (errorCode == kDNSServiceErr_NoError) {      
        LOG(kBonjour, "mDNS Browse Reply (%s): %s\n", regtype, serviceName);         
    }
    else {
        LOG_ERROR(kBonjour, "mDNS browse Error: flags=%d, index=%u, err=%d, serviceName=%s, regtype=%s, replyDomain=%s, context=%p\n",
               flags, interfaceIndex, (TInt)errorCode, serviceName, regtype, replyDomain, context);
    }    

    DNSServiceErrorType err = DNSServiceResolve(&sdRef,
                                                flags,
                                                interfaceIndex,
                                                serviceName,
                                                regtype,
                                                replyDomain,
                                                (DNSServiceResolveReply)ResolveReply,
                                                context);
    if (err != kDNSServiceErr_NoError) {
        LOG_ERROR(kBonjour, "DNSServiceResolve returned error code %d\n", (TInt)err);
    }
}

TBool MdnsPlatform::FindDevices(const TChar* aServiceName)
{
    if (!iHasCache) {
        LOG_ERROR(kBonjour, "ERROR: Mdns cache is required for MdnsPlatform::FindDevices. See Env.InitParams.SetDvEnableBonjour\n");
        ASSERTS();
        return false;
    }
    iDiscoveryLock.Wait();
    DNSServiceRef* ref = new DNSServiceRef();
    iSdRefs.push_back(ref);
    iDiscoveryLock.Signal();
    DNSServiceErrorType err = DNSServiceBrowse(ref,
                                               0, /*flags */
                                               0, /*interfaceIndex -- not used (defaults to mDNSInterface_Any instead) */
                                               aServiceName, /*regtype*/
                                               NULL, /*domain*/
                                               (DNSServiceBrowseReply)BrowseReply,
                                               this /*context*/);
    return (err == kDNSServiceErr_NoError);
}
#endif // DEFINE_WINDOWS_UNIVERSAL

void MdnsPlatform::DeviceDiscovered(const Brx& aType, const Brx& aFriendlyName, const Brx& aUglyName, const Brx&  aIpAddress, TUint aPort)
{
    AutoMutex _(iDiscoveryLock);
    MdnsDevice* dev = new MdnsDevice(aType, aFriendlyName, aUglyName, aIpAddress, aPort);
    for (TUint i=0; i<iDeviceListeners.size(); i++) {
        
        iDeviceListeners[i]->DeviceAdded(*dev);
    }
    delete dev;
}

void MdnsPlatform::StatusCallback(mDNS *const m, mStatus aStatus)
{
    LOG(kBonjour, "Bonjour             StatusCallback - aStatus %d\n", aStatus);
    if (aStatus == mStatus_GrowCache && reinterpret_cast<MdnsPlatform*>(m->p)->iHasCache) {
        // Allocate another chunk of cache storage
        (void)m;
        #ifndef DEFINE_WINDOWS_UNIVERSAL
            LOG(kBonjour, "WARNING: mDNS cache size insufficient, GROWING...\n");
            CacheEntity *storage = (CacheEntity*)calloc(MdnsPlatform::kRRCacheSize, sizeof(CacheEntity));
            if (storage) {
                mDNS_GrowCache(m, storage, MdnsPlatform::kRRCacheSize);
                reinterpret_cast<MdnsPlatform*>(m->p)->iDynamicCache.push_back(storage);
            }
        #endif
    }
    else if (aStatus != mStatus_NoError) {
        Log::Print("ERROR: mDNS status=%d\n", aStatus);
        ASSERTS();
    }
}

void MdnsPlatform::AddMdnsDeviceListener(IMdnsDeviceListener* aListener)
{
    // could not use std::reference_wrapper for iDeviceListeners
    // pointer is not owned here
    AutoMutex _(iDiscoveryLock);
    iDeviceListeners.push_back(aListener);
}


// MdnsPlatform::MutexRecursive

MdnsPlatform::MutexRecursive::MutexRecursive()
    : iMutex("MREC")
    , iOwner(Thread_None)
    , iCount(0)
{
}

MdnsPlatform::MutexRecursive::~MutexRecursive()
{
    ASSERT(iOwner == Thread_None);
    ASSERT(iCount == 0);
}

void MdnsPlatform::MutexRecursive::Lock()
{
    Thread* th = Thread::Current();
    if (th == iOwner) {
        iCount++;
    }
    else {
        iMutex.Wait();
        iOwner = th;
        iCount = 1;
    }
}

void MdnsPlatform::MutexRecursive::Unlock()
{
    ASSERT_DEBUG(Thread::Current() == iOwner);
    if (--iCount == 0) {
        iOwner = Thread_None;
        iMutex.Signal();
    }
}


// C APIs expected by mDNSCore

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
        mDNSInterfaceID aInterface, UDPSocket* /*src*/, const mDNSAddr *aAddress, mDNSIPPort aPort, mDNSBool /*useBackgroundTrafficClass*/)
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
    mStatus status;
    try{
        status = platform.SendUdp(buffer, endpoint);
    }
    catch (NetworkError&)
    {
        LOG_ERROR(kBonjour, "mDNSPlatformSendUDP caught NetworkError. Endpoint port %u, address: ", aPort.NotAnInteger);
        LOG_ERROR(kBonjour, address);
        LOG_ERROR(kBonjour, "\n");
        status = mStatus_UnknownErr;
    }
    return status;
}

void* mDNSPlatformMemAllocate(mDNSu32 aLength)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformMemAllocate(%u)\n", aLength);
    return malloc(aLength);
}

void  mDNSPlatformMemFree(void* aPtr)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformMemFree\n");
    free(aPtr);
}

mDNSInterfaceID mDNSPlatformInterfaceIDfromInterfaceIndex(mDNS* /*m*/, mDNSu32 /*aIndex*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformInterfaceIDfromInterfaceIndex\n");
    ASSERTS(); // not sure what an interface index is and can't find any mDNS callers for this function
    return 0;
}

mDNSu32 mDNSPlatformInterfaceIndexfromInterfaceID(mDNS* /*m*/, mDNSInterfaceID /*aId*/, mDNSBool /*suppressNetworkChange*/)
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

void mDNSPlatformStrCopy(void *dst, const void *src)
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

void mDNSPlatformMemCopy(void *dst, const void *src, mDNSu32 len)
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

// If the caller wants to know the exact return of memcmp, then use this instead
// of mDNSPlatformMemSame
int mDNSPlatformMemCmp(const void *dst, const void *src, mDNSu32 len)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformMemCmp\n");
    return (memcmp(dst, src, len));
}

void mDNSPlatformQsort(void *base, int nel, int width, int (*compar)(const void *, const void *))
{
    LOG(kBonjour, "Bonjour             mDNSPlatformQsort\n");
    return (qsort(base, nel, width, compar));
}

// DNSSEC stub functions
void VerifySignature(mDNS *const /*m*/, DNSSECVerifier* /*dv*/, DNSQuestion* /*q*/)
{

}

mDNSBool AddNSECSForCacheRecord(mDNS *const /*m*/, CacheRecord* /*crlist*/, CacheRecord* /*negcr*/, mDNSu8 /*rcode*/)
{
    return mDNSfalse;
}

void BumpDNSSECStats(mDNS *const /*m*/, DNSSECStatsAction /*action*/, DNSSECStatsType /*type*/, mDNSu32 /*value*/)
{

}

void DNSSECProbe(mDNS *const /*m*/)
{
    // DarwinOS specific function
    ASSERTS();
}

// Proxy stub functions
mDNSu8 *DNSProxySetAttributes(DNSQuestion* /*q*/, DNSMessageHeader* /*h*/, DNSMessage* /*msg*/, mDNSu8* /*ptr*/, mDNSu8* /*limit*/)
{
    return nullptr;
}

// Logging/debugging

#ifdef DEFINE_TRACE
int mDNS_LoggingEnabled = 1;
int mDNS_PacketLoggingEnabled= 1;
int mDNS_McastTracingEnabled = 1;
#else
int mDNS_LoggingEnabled = 0;
int mDNS_PacketLoggingEnabled= 0;
int mDNS_McastTracingEnabled = 0;
#endif

static const TUint kMaxLogMsgBytes = 200;

void LogMsgWithLevel(mDNSLogLevel_t /*logLevel*/, const char *format, ...)
{
#ifdef DEFINE_TRACE
    va_list args;
    va_start(args, format);
    // not all messages are errors but enough are that its handy to log everything here if we're interested in errors
    if(Debug::TestLevel(Debug::kBonjour) && Debug::TestSeverity(Debug::kSeverityError)) {
        Bws<kMaxLogMsgBytes> msg;
        TUint written = mDNS_vsnprintf((char*)msg.Ptr(), msg.MaxBytes(), format, args);
        msg.SetBytes(written);
        Log::Print(msg);
        Log::Print("\n");
    }
    va_end(args);
#endif
}

mDNSu32 mDNSPlatformRandomNumber()
{
    LOG(kBonjour, "Bonjour             mDNSPlatformRandomNumber\n");
    return gEnv->Random();
}

mDNSu32 mDNSPlatformRandomSeed()
{
    LOG(kBonjour, "Bonjour             mDNSPlatformRandomSeed\n");
    return gEnv->Random();
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

TCPSocket* mDNSPlatformTCPSocket(mDNS* const /*m*/, TCPSocketFlags /*flags*/, mDNSIPPort* /*port*/, mDNSBool /*useBackgroundTrafficClass*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformTCPSocket\n");
    ASSERTS();
    return NULL;
}

TCPSocket* mDNSPlatformTCPAccept(TCPSocketFlags /*flags*/, int /*sd*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformTCPAccept\n");
    ASSERTS();
    return NULL;
}

int mDNSPlatformTCPGetFD(TCPSocket* /*sock*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformTCPGetFD\n");
    ASSERTS();
    return 0;
}

mStatus mDNSPlatformTCPConnect(TCPSocket* /*sock*/, const mDNSAddr* /*dst*/, mDNSOpaque16 /*dstport*/, domainname* /*hostname*/,
                               mDNSInterfaceID /*InterfaceID*/, TCPConnectionCallback /*callback*/, void* /*context*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformTCPConnect\n");
    ASSERTS();
    return mStatus_UnsupportedErr;
}

void mDNSPlatformTCPCloseConnection(TCPSocket*)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformTCPCloseConnection\n");
    ASSERTS();
}

long mDNSPlatformReadTCP(TCPSocket* /*sock*/, void* /*buf*/, unsigned long /*buflen*/, mDNSBool* /*closed*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformReadTCP\n");
    ASSERTS();
    return 0;
}

long mDNSPlatformWriteTCP(TCPSocket* /*sock*/, const char* /*msg*/, unsigned long /*len*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformWriteTCP\n");
    ASSERTS();
    return 0;
}

// unused UDP handlers

UDPSocket* mDNSPlatformUDPSocket(mDNS* const /*m*/, const mDNSIPPort /*requestedport*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformUDPSocket\n");
    ASSERTS();
    return NULL;
}

void mDNSPlatformUDPClose(UDPSocket* /*sock*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformUDPClose\n");
    ASSERTS();
}

// unused misc socket handlers

void mDNSPlatformReceiveBPF_fd(mDNS* const /*m*/, int /*fd*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformReceiveBPF_fd\n");
    ASSERTS();
}

void mDNSPlatformUpdateProxyList(mDNS* const /*m*/, const mDNSInterfaceID /*InterfaceID*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformUpdateProxyList\n");
    ASSERTS();
}

void mDNSPlatformSendRawPacket(const void* const /*msg*/, const mDNSu8* const /*end*/, mDNSInterfaceID /*InterfaceID*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformSendRawPacket\n");
    ASSERTS();
}

void mDNSPlatformSetLocalAddressCacheEntry(mDNS* const /*m*/, const mDNSAddr* const /*tpa*/, const mDNSEthAddr* const /*tha*/, mDNSInterfaceID /*InterfaceID*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformSetLocalAddressCacheEntry\n");
    ASSERTS();
}

void mDNSPlatformSourceAddrForDest(mDNSAddr* const /*src*/, const mDNSAddr* const /*dst*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformSourceAddrForDest\n");
    ASSERTS();
}

// dnsextd handlers

mStatus mDNSPlatformTLSSetupCerts()
{
    LOG(kBonjour, "Bonjour             mDNSPlatformTLSSetupCerts\n");
    ASSERTS();
    return mStatus_UnsupportedErr;
}

void mDNSPlatformTLSTearDownCerts()
{
    LOG(kBonjour, "Bonjour             mDNSPlatformTLSTearDownCerts\n");
    ASSERTS();
}

// Handlers for unicast browsing/dynamic update for clients who do not specify a domain
// in browse/registration

mDNSBool mDNSPlatformSetDNSConfig(mDNS* const /*m*/, mDNSBool /*setservers*/, mDNSBool /*setsearch*/, domainname* const fqdn,
                              DNameListElem** /*RegDomains*/, DNameListElem** /*BrowseDomains*/, mDNSBool /*ackConfig*/)

{
    // unused, but called by Bonjour
    LOG(kBonjour, "Bonjour             mDNSPlatformSetDNSConfig\n");
    if (fqdn != mDNSNULL) {
        (void)memset(fqdn, 0, sizeof(*fqdn));
    }
    return true;
}

mStatus mDNSPlatformGetPrimaryInterface(mDNS* const m, mDNSAddr* v4, mDNSAddr* v6, mDNSAddr* router)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformGetPrimaryInterface\n");
    mStatus err = mStatus_NoError;
    MdnsPlatform& platform = *(MdnsPlatform*)m->p;
    *v6 = zeroAddr;
    *router = zeroAddr;
    *v4 = zeroAddr;
    err = platform.GetPrimaryInterface((TIpAddress&)*v4);

    return err;
}

void mDNSPlatformDynDNSHostNameStatusChanged(const domainname* const /*dname*/, const mStatus /*status*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformDynDNSHostNameStatusChanged\n");
    ASSERTS();
}

void mDNSPlatformSetAllowSleep(mDNS* const /*m*/, mDNSBool /*allowSleep*/, const char* /*reason*/)
{
    // unused, but called by Bonjour
    LOG(kBonjour, "Bonjour             mDNSPlatformSetAllowSleep\n");
}

void mDNSPlatformSendWakeupPacket(mDNS* const /*m*/, mDNSInterfaceID /*InterfaceID*/, char* /*EthAddr*/, char* /*IPAddr*/, int /*iteration*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformSendWakeupPacket\n");
    ASSERTS();
}

mDNSBool mDNSPlatformValidRecordForInterface(const AuthRecord* /*rr*/, mDNSInterfaceID /*InterfaceID*/)
{
    LOG(kBonjour, "Bonjour             mDNSPlatformValidRecordForInterface\n");
    ASSERTS();
    return false;
}

mDNSBool mDNSPlatformValidQuestionForInterface(DNSQuestion* /*q*/, const NetworkInterfaceInfo* /*intf*/)
{
    return true;
}

// Used for debugging purposes. For now, just set the buffer to zero
void mDNSPlatformFormatTime(unsigned long /*te*/, mDNSu8 *buf, int bufsize)
{
    if (bufsize) buf[0] = 0;
}

void mDNSPlatformSendKeepalive(mDNSAddr* /*sadd*/, mDNSAddr* /*dadd*/, mDNSIPPort* /*lport*/, mDNSIPPort* /*rport*/, mDNSu32 /*seq*/, mDNSu32 /*ack*/, mDNSu16 /*win*/)
{

}

mStatus mDNSPlatformRetrieveTCPInfo(mDNS *const /*m*/, mDNSAddr *laddr, mDNSIPPort* /*lport*/, mDNSAddr* /*raddr*/, mDNSIPPort* /*rport*/, mDNSTCPInfo* /*mti*/)
{
    return mStatus_NoError;
}

mStatus mDNSPlatformGetRemoteMacAddr(mDNS *const /*m*/, mDNSAddr* /*raddr*/)
{
    return mStatus_NoError;
}

mStatus mDNSPlatformStoreSPSMACAddr(mDNSAddr* /*spsaddr*/, char* /*ifname*/)
{
    return mStatus_NoError;
}

mStatus mDNSPlatformClearSPSData(void)
{
    return mStatus_NoError;
}

mStatus mDNSPlatformStoreOwnerOptRecord(char* /*ifname*/, DNSMessage* /*msg*/, int /*length*/)
{
    return mStatus_UnsupportedErr;
}

mDNSBool mDNSPlatformInterfaceIsD2D(mDNSInterfaceID /*InterfaceID*/)
{
    return mDNSfalse;
}

void mDNSPlatformSetSocktOpt(void* /*sock*/, mDNSTransport_Type /*transType*/, mDNSAddr_Type /*addrType*/, const DNSQuestion* /*q*/)
{

}

mDNSs32 mDNSPlatformGetPID()
{
    return 0;
}


} // extern "C"

