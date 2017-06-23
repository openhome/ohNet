#include <OpenHome/Net/Odp/Tests/CpiDeviceOdp.h>
#include <OpenHome/Net/Odp/Odp.h>
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Json.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Net/Private/CpiSubscription.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Debug-ohMediaPlayer.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpiDeviceOdp

CpiDeviceOdp::CpiDeviceOdp(CpStack& aCpStack, Endpoint aLocation, const Brx& aAlias, Functor aStateChanged)
    : iCpStack(aCpStack)
    , iLock("CLP1")
    , iLocation(aLocation)
    , iAlias(aAlias)
    , iStateChanged(aStateChanged)
    , iDevice(nullptr)
    , iResponseHandler(nullptr)
    , iConnected(false)
    , iExiting(false)
{
    iReadBuffer = new Srs<1024>(iSocket);
    iReaderUntil = new ReaderUntilS<kMaxReadBufferBytes>(*iReadBuffer);
    iWriteBuffer = new Sws<kMaxWriteBufferBytes>(iSocket);
    iThread = new ThreadFunctor("OdpClient", MakeFunctor(*this, &CpiDeviceOdp::OdpReaderThread));
    iInvocable = new CpiOdpInvocable(*this);
    iThread->Start();
}

CpiDeviceOdp::~CpiDeviceOdp()
{
    iExiting = true;
    iReadBuffer->ReadInterrupt();
    delete iThread;
    delete iInvocable;
    delete iWriteBuffer;
    delete iReaderUntil;
    delete iReadBuffer;
    iSocket.Close();
}

void CpiDeviceOdp::Destroy()
{
    iLock.Wait();
    iStateChanged = Functor();
    iDevice->RemoveRef();
    iLock.Signal();
}

CpiDevice* CpiDeviceOdp::Device()
{
    return iDevice;
}

TBool CpiDeviceOdp::Connected() const
{
    return iConnected;
}

void CpiDeviceOdp::OdpReaderThread()
{
    try {
        iSocket.Open(iCpStack.Env());
        iSocket.Connect(iLocation, iCpStack.Env().InitParams()->TcpConnectTimeoutMs());
        for (;;) {
            Brn line = iReaderUntil->ReadUntil(Ascii::kLf);
            JsonParser parser;
            parser.Parse(line);
            Brn type = parser.String(Odp::kKeyType);
            if (!iConnected) {
                if (type != Odp::kTypeAnnouncement) {
                    LOG2(kOdp, kError, "Odp: no announcement on connect\n");
                    THROW(ReaderError);
                }

                // We don't have a proper parser for json arrays.  Quick/dirty alternative follows...
                // Note that this relies on each device listing "id" before "type"
                Parser p(parser.String(Odp::kKeyDevices));
                Brn udn;
                for (;;) {
                    if (p.Finished()) {
                        LOG2(kOdp, kError, "Odp: unable to find device %.*s, exiting thread\n", PBUF(iAlias));
                        if (iStateChanged) {
                            iStateChanged();
                        }
                        THROW(ReaderError);
                    }
                    Brn buf = p.Next('\"');
                    if (buf == Odp::kKeyId) {
                        (void)p.Next('\"');
                        buf.Set(p.Next('\"'));
                    }
                    else if (buf == Odp::kKeyAlias) {
                        (void)p.Next('\"');
                        buf.Set(p.Next('\"'));
                        if (buf == iAlias) {
                            break;
                        }
                    }
                }

                iDevice = new CpiDevice(iCpStack, udn, *this, *this, nullptr);
                iConnected = true;
                if (iStateChanged) {
                    iStateChanged();
                }
            }
            else if (type == Odp::kTypeNotify) {
                HandleEventedUpdate(parser);
            }
            else if (iResponseHandler == nullptr || !iResponseHandler->HandleOdpResponse(parser)) {
                LOG2(kOdp, kError, "Unexpected Odp message: %.*s\n", PBUF(line));
            }
        }
    }
    catch (NetworkError&) {
        LogError("NetworkError");
    }
    catch (NetworkTimeout&) {
        LogError("NetworkTimeout");
    }
    catch (WriterError&) {
        LogError("WriterError");
    }
    catch (ReaderError&) {
        if (!iExiting) {
            LogError("ReaderError");
        }
    }
    iConnected = false;
}

void CpiDeviceOdp::LogError(const TChar* aError)
{
    LOG2(kOdp, kError, "Odp: error %s for device %.*s, exiting thread\n", aError, PBUF(iAlias));
    if (iStateChanged) {
        iStateChanged();
    }
}

void CpiDeviceOdp::HandleEventedUpdate(JsonParser& aParser)
{
    Brn sid = aParser.String(Odp::kKeySid);
    CpiSubscription* subscription = iCpStack.SubscriptionManager().FindSubscription(sid);
    if (subscription == nullptr) {
        LOG2(kOdp, kError, "Odp: event from unknown subscription - %.*s\n", PBUF(sid));
        return;
    }
    JsonParser parserProps;
    parserProps.Parse(aParser.String(Odp::kKeyProperties));
    subscription->UpdateSequenceNumber();
    IEventProcessor* processor = static_cast<IEventProcessor*>(subscription);
    processor->EventUpdateStart();
    CpiOdpOutputProcessor outputProcessor;
    std::vector<Brn> props;
    parserProps.GetKeys(props);
    for (auto it=props.begin(); it!=props.end(); ++it) {
        Brn propVal;
        if (!parserProps.IsNull(*it)) {
            propVal.Set(parserProps.String(*it));
        }
        processor->EventUpdate(*it, propVal, outputProcessor);
    }
    processor->EventUpdateEnd();
    subscription->Unlock();
    subscription->RemoveRef();
}

void CpiDeviceOdp::InvokeAction(Invocation& aInvocation)
{
    aInvocation.SetInvoker(*iInvocable);
    iCpStack.InvocationManager().Invoke(&aInvocation);
}

TBool CpiDeviceOdp::GetAttribute(const TChar* /*aKey*/, Brh& /*aValue*/) const
{
    // Not obviously required.  The only attribute Odp devices have is their name and we pass this to the c'tor
    return false;
}

TUint CpiDeviceOdp::Subscribe(CpiSubscription& aSubscription, const Uri& /*aSubscriber*/)
{
    CpiOdpSubscriber subscriber(*this);
    subscriber.Subscribe(aSubscription);
    return kSubscriptionDurationSecs;
}

TUint CpiDeviceOdp::Renew(CpiSubscription& /*aSubscription*/)
{
    return kSubscriptionDurationSecs;
}

void CpiDeviceOdp::Unsubscribe(CpiSubscription& /*aSubscription*/, const Brx& aSid)
{
    CpiOdpUnsubscriber unsubscriber(*this);
    unsubscriber.Unsubscribe(aSid);
}

TBool CpiDeviceOdp::OrphanSubscriptionsOnSubnetChange() const
{
    return true;
}

void CpiDeviceOdp::NotifyRemovedBeforeReady()
{
}

TUint CpiDeviceOdp::Version(const TChar* /*aDomain*/, const TChar* /*aName*/, TUint aProxyVersion) const
{
    return aProxyVersion; // FIXME - could store list of remote services and lookup on that
}

void CpiDeviceOdp::Release()
{
    delete this;
}

IWriter& CpiDeviceOdp::WriteLock(ICpiOdpResponse& aResponseHandler)
{
    iLock.Wait();
    iResponseHandler = &aResponseHandler;
    return *iWriteBuffer;
}

void CpiDeviceOdp::WriteUnlock()
{
    iResponseHandler = nullptr;
    iLock.Signal();
}

void CpiDeviceOdp::WriteEnd(IWriter& aWriter)
{
    aWriter.Write(Ascii::kLf);
    aWriter.WriteFlush();
}

const Brx& CpiDeviceOdp::Alias() const
{
    return iAlias;
}
