#ifndef HEADER_DEVICE_LPEC
#define HEADER_DEVICE_LPEC

#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
    class Uri;
namespace Net {

class CpStack;
class CpiSubscription;
class IEventProcessor;

class ILpecResponse
{
public:
    virtual TBool HandleLpecResponse(const Brx& aMethod, const Brx& aBody) = 0;
    virtual ~ILpecResponse() {}
};

class CpiDeviceLpec : private ICpiProtocol, private ICpiDeviceObserver
{
public:
    CpiDeviceLpec(CpStack& aCpStack, Endpoint aLocation, const Brx& aLpecName, Functor aStateChanged);
    void Destroy();
    CpiDevice* Device();
    TBool Connected() const;
private:
    ~CpiDeviceLpec();
    void LpecThread();
    void LogError(const TChar* aError);
    void HandleEventedUpdate(const Brx& aUpdate);
private: // from ICpiProtocol
    void InvokeAction(Invocation& aInvocation);
    TBool GetAttribute(const TChar* aKey, Brh& aValue) const;
    TUint Subscribe(CpiSubscription& aSubscription, const OpenHome::Uri& aSubscriber);
    TUint Renew(CpiSubscription& aSubscription);
    void Unsubscribe(CpiSubscription& aSubscription, const Brx& aSid);
    void NotifyRemovedBeforeReady();
    TUint Version(const TChar* aDomain, const TChar* aName, TUint aProxyVersion) const;
private: // from ICpiDeviceObserver
    void Release();
private:
    class Invocable : public IInvocable, private IInputArgumentProcessor, private ILpecResponse, private INonCopyable
    {
    public:
        Invocable(CpiDeviceLpec& aDevice);
    private: // from IInvocable
        void InvokeAction(Invocation& aInvocation);
    private: // from IInputArgumentProcessor
        void ProcessString(const Brx& aVal);
        void ProcessInt(TInt aVal);
        void ProcessUint(TUint aVal);
        void ProcessBool(TBool aVal);
        void ProcessBinary(const Brx& aVal);
    private: // from ILpecResponse
        TBool HandleLpecResponse(const Brx& aMethod, const Brx& aBody);
    private:
        CpiDeviceLpec& iDevice;
        Semaphore iSem;
        Invocation* iInvocation;
    };
    class SubscriptionResponse : public ILpecResponse, private INonCopyable
    {
    public:
        SubscriptionResponse(Semaphore& aComplete);
        const Brx& SidFragment() const;
    private: // from ILpecResponse
        TBool HandleLpecResponse(const Brx& aMethod, const Brx& aBody);
    private:
        Semaphore& iComplete;
        Brn iSidFragment;
    };
    class OutputProcessor : public IOutputProcessor
    {
    private: // from IOutputProcessor
        void ProcessString(const Brx& aBuffer, Brhz& aVal);
        void ProcessInt(const Brx& aBuffer, TInt& aVal);
        void ProcessUint(const Brx& aBuffer, TUint& aVal);
        void ProcessBool(const Brx& aBuffer, TBool& aVal);
        void ProcessBinary(const Brx& aBuffer, Brh& aVal);
    };
private:
    static const TUint kMaxReadBufferBytes = 12000;
    static const TUint kMaxWriteBufferBytes = 4000;

    CpStack& iCpStack;
    Mutex iLock;
    SocketTcpClient iSocket;
    Srs<kMaxReadBufferBytes>* iReadBuffer;
    Sws<kMaxWriteBufferBytes>* iWriteBuffer;
    Endpoint iLocation;
    Bws<64> iLpecName;
    Functor iStateChanged;
    CpiDevice* iDevice;
    ThreadFunctor* iThread;
    Invocable* iInvocable;
    ILpecResponse* iResponseHandler;
    TBool iConnected;
    TBool iExiting;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DEVICE_LPEC
