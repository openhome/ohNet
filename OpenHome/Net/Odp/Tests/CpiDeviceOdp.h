#pragma once

#include <OpenHome/Net/Odp/CpiOdp.h>
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
    class JsonParser;
namespace Net {
    class CpiSubscription;

class CpiDeviceOdp : private ICpiProtocol
                   , private ICpiDeviceObserver
                   , private ICpiOdpDevice
{
    static const TUint kSubscriptionDurationSecs = 60 * 60 * 24; // arbitrarily chosen largish value
public:
    CpiDeviceOdp(CpStack& aCpStack,
                 Endpoint aLocation,
                 const Brx& aAlias,
                 Functor aStateChanged);
    void Destroy();
    CpiDevice* Device();
    TBool Connected() const;
private:
    ~CpiDeviceOdp();
    void OdpReaderThread();
    void LogError(const TChar* aError);
    void HandleEventedUpdate(JsonParser& aParser);
private: // from ICpiProtocol
    void InvokeAction(Invocation& aInvocation) override;
    TBool GetAttribute(const TChar* aKey, Brh& aValue) const override;
    TUint Subscribe(CpiSubscription& aSubscription, const Uri& aSubscriber) override;
    TUint Renew(CpiSubscription& aSubscription) override;
    void Unsubscribe(CpiSubscription& aSubscription, const Brx& aSid) override;
    TBool OrphanSubscriptionsOnSubnetChange() const override;
    void NotifyRemovedBeforeReady() override;
    TUint Version(const TChar* aDomain, const TChar* aName, TUint aProxyVersion) const override;
private: // from ICpiDeviceObserver
    void Release() override;
private: // from ICpiOdpDevice
    IWriter& WriteLock(ICpiOdpResponse& aResponseHandler) override;
    void WriteUnlock() override;
    void WriteEnd(IWriter& aWriter) override;
    const Brx& Alias() const override;
private:
    static const TUint kMaxReadBufferBytes = 100 * 1024;
    static const TUint kMaxWriteBufferBytes = 12 * 1024;

    CpStack& iCpStack;
    Mutex iLock;
    SocketTcpClient iSocket;
    Srx* iReadBuffer;
    ReaderUntilS<kMaxReadBufferBytes>* iReaderUntil;
    Sws<kMaxWriteBufferBytes>* iWriteBuffer;
    Endpoint iLocation;
    Bws<64> iAlias;
    Functor iStateChanged;
    CpiDevice* iDevice;
    ThreadFunctor* iThread;
    IInvocable* iInvocable;
    ICpiOdpResponse* iResponseHandler;
    TBool iConnected;
    TBool iExiting;
};

} // namespace Net
} // namespace OpenHome
