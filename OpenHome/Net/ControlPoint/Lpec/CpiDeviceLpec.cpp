#include <OpenHome/Net/Private/CpiDeviceLpec.h>
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/DviServerLpec.h> // for Lpec class of constants only
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Net/Private/CpiSubscription.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpiDeviceLpec

CpiDeviceLpec::CpiDeviceLpec(CpStack& aCpStack, Endpoint aLocation, const Brx& aLpecName, Functor aStateChanged)
    : iCpStack(aCpStack)
    , iLock("CLP1")
    , iLocation(aLocation)
    , iLpecName(aLpecName)
    , iStateChanged(aStateChanged)
    , iDevice(NULL)
    , iResponseHandler(NULL)
    , iConnected(false)
    , iExiting(false)
{
    iReadBuffer = new Srs<kMaxReadBufferBytes>(iSocket);
    iWriteBuffer = new Sws<kMaxWriteBufferBytes>(iSocket);
    iThread = new ThreadFunctor("LpecClient", MakeFunctor(*this, &CpiDeviceLpec::LpecThread));
    iInvocable = new Invocable(*this);
    iThread->Start();
}

CpiDeviceLpec::~CpiDeviceLpec()
{
    iExiting = true;
    iReadBuffer->ReadInterrupt();
    delete iThread;
    delete iInvocable;
    delete iWriteBuffer;
    delete iReadBuffer;
    iSocket.Close();
}

void CpiDeviceLpec::Destroy()
{
    iLock.Wait();
    iStateChanged = Functor();
    iDevice->RemoveRef();
    iLock.Signal();
}

CpiDevice* CpiDeviceLpec::Device()
{
    return iDevice;
}

TBool CpiDeviceLpec::Connected() const
{
    return iConnected;
}

void CpiDeviceLpec::LpecThread()
{
    try {
        iSocket.Open(iCpStack.Env());
        iSocket.Connect(iLocation, iCpStack.Env().InitParams()->TcpConnectTimeoutMs());
        TBool starting = true;
        for (;;) {
            Brn line = iReadBuffer->ReadUntil(Ascii::kLf);
            if (line.Bytes() > 0 && line[line.Bytes()-1] == Ascii::kCr) {
                line.Set(line.Ptr(), line.Bytes()-1);
            }
            Parser parser(line);
            Brn method = parser.Next(' ');
            if (starting) {
                if (method != Lpec::kMethodAlive) {
                    LOG2(kLpec, kError, "LPEC: unable to find device ");
                    LOG2(kLpec, kError, iLpecName);
                    LOG2(kLpec, kError, ", exiting thread\n");
                    if (iStateChanged) {
                        iStateChanged();
                    }
                    THROW(ReaderError);
                }
                Brn name = parser.Next(' ');
                if (name == iLpecName) {
                    starting = false;
                    Brn udn = parser.Remaining();
                    iDevice = new CpiDevice(iCpStack, udn, *this, *this, NULL);
                    iConnected = true;
                    if (iStateChanged) {
                        iStateChanged();
                    }
                }
            }
            if (method == Lpec::kMethodAlive) {
                LOG(kLpec, "LPEC: Alive - ");
                LOG(kLpec, parser.Remaining());
                LOG(kLpec, "\n");
            }
            else if (method == Lpec::kMethodByeBye) {
                Brn name = parser.Next(' ');
                if (name == iLpecName) {
                    iConnected = false;
                    {
                        if (iStateChanged) {
                            iStateChanged();
                        }
                    }
                    iExiting = true;
                    THROW(ReaderError);
                }
            }
            else if (method == Lpec::kMethodEvent) {
                HandleEventedUpdate(parser.Remaining());
            }
            else if (iResponseHandler == NULL || !iResponseHandler->HandleLpecResponse(method, parser.Remaining())) {
                LOG2(kLpec, kError, "Unexpected LPEC message: ");
                LOG2(kLpec, kError, line);
                LOG2(kLpec, kError, "\n");
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
}

void CpiDeviceLpec::LogError(const TChar* aError)
{
    LOG2(kLpec, kError, "LPEC: error %s for device ", aError);
    LOG2(kLpec, kError, iLpecName);
    LOG2(kLpec, kError, ", exiting thread\n");
    if (iStateChanged) {
        iStateChanged();
    }
}

void CpiDeviceLpec::HandleEventedUpdate(const Brx& aUpdate)
{
    Parser parser(aUpdate);
    Brn lpecId = parser.Next(' ');
    Bws<128> sid(iDevice->Udn());
    sid.Append('-');
    sid.Append(lpecId);
    CpiSubscription* subscription = iCpStack.SubscriptionManager().FindSubscription(sid);
    if (subscription == NULL) {
        /* There is a very short window between Subscribe() returning and the new
           subscription being added to its manager.  As a lazy workaround for this,
           sleep for a short period and retry before rejecting the update */
        Thread::Sleep(1000);
        subscription = iCpStack.SubscriptionManager().FindSubscription(sid);
    }
    if (subscription == NULL) {
        LOG(kLpec, "LPEC: evented update received for unknown subscription - ");
        LOG(kLpec, sid);
        LOG(kLpec, "\n");
        return;
    }
    Brn seqBuf = parser.Next(' ');
    TUint seq;
    try {
        seq = Ascii::Uint(seqBuf);
    }
    catch (AsciiError&) {
        LOG(kLpec, "LPEC: invalid sequence number - ");
        LOG(kLpec, seqBuf);
        LOG(kLpec, "in evented update\n");
        subscription->RemoveRef();
        return;
    }
    if (!subscription->UpdateSequenceNumber(seq)) {
        LOG(kLpec, "LPEC: out of sequence update (%d) for ", seq);
        LOG(kLpec, sid);
        LOG(kLpec, "\n");
        subscription->SetNotificationError();
        subscription->RemoveRef();
        return;
    }
    IEventProcessor* processor = static_cast<IEventProcessor*>(subscription);
    processor->EventUpdateStart();
    OutputProcessor outputProcessor;
    try {
        for (;;) {
            Brn propName = parser.Next(' ');
            if (propName.Bytes() == 0) {
                // processed entire update
                break;
            }
            (void)parser.Next(Lpec::kArgumentDelimiter);
            Brn propVal = parser.Next(Lpec::kArgumentDelimiter);
            processor->EventUpdate(propName, propVal, outputProcessor);
        }
        processor->EventUpdateEnd();
    }
    catch (AsciiError&) {
        LOG2(kLpec, kError, "LPEC: Invalid evented update - ");
        LOG2(kLpec, kError, aUpdate);
        LOG2(kLpec, kError, "\n");
        processor->EventUpdateError();
    }
    subscription->Unlock();
    subscription->RemoveRef();
}

void CpiDeviceLpec::InvokeAction(Invocation& aInvocation)
{
    aInvocation.SetInvoker(*iInvocable);
    iDevice->GetCpStack().InvocationManager().Invoke(&aInvocation);
}

TBool CpiDeviceLpec::GetAttribute(const char* /*aKey*/, Brh& /*aValue*/) const
{
    // Not obviously required.  The only attribute LPEC devices have is their name and we pass this to the c'tor
    return false;
}

TUint CpiDeviceLpec::Subscribe(CpiSubscription& aSubscription, const OpenHome::Uri& /*aSubscriber*/)
{
    Semaphore sem("CLS2", 0);
    SubscriptionResponse resp(sem);
    AutoMutex a(iLock);
    iResponseHandler = &resp;
    iWriteBuffer->Write(Lpec::kMethodSubscribe);
    iWriteBuffer->Write(' ');
    iWriteBuffer->Write(iLpecName);
    iWriteBuffer->Write('/');
    iWriteBuffer->Write(aSubscription.ServiceType().Name());
    iWriteBuffer->Write(Lpec::kMsgTerminator);
    iWriteBuffer->WriteFlush();

    sem.Wait();
    Bws<128> sid(iDevice->Udn());
    sid.Append('-');
    sid.Append(resp.SidFragment());
    Brh sid2(sid);
    aSubscription.SetSid(sid2);

    iResponseHandler = NULL;
    return UINT_MAX; // subscription never expires so report the longest possible duration
}

TUint CpiDeviceLpec::Renew(CpiSubscription& /*aSubscription*/)
{
    return UINT_MAX; // subscription never expires so report the longest possible duration
}

void CpiDeviceLpec::Unsubscribe(CpiSubscription& aSubscription, const Brx& /*aSid*/)
{
    AutoMutex a(iLock);
    iWriteBuffer->Write(Lpec::kMethodUnsubscribe);
    iWriteBuffer->Write(' ');
    iWriteBuffer->Write(iLpecName);
    iWriteBuffer->Write('/');
    iWriteBuffer->Write(aSubscription.ServiceType().Name());
    iWriteBuffer->Write(Lpec::kMsgTerminator);
    iWriteBuffer->WriteFlush();

    // no great benefit in waiting for a response
}

void CpiDeviceLpec::NotifyRemovedBeforeReady()
{
}

TUint CpiDeviceLpec::Version(const TChar* /*aDomain*/, const TChar* /*aName*/, TUint aProxyVersion) const
{
    return aProxyVersion; // FIXME - could store list of remote services and lookup on that
}

void CpiDeviceLpec::Release()
{
    delete this;
}


// class CpiDeviceLpec::Invocable

CpiDeviceLpec::Invocable::Invocable(CpiDeviceLpec& aDevice)
    : iDevice(aDevice)
    , iSem("CLPS", 0)
    , iInvocation(NULL)
{
}

void CpiDeviceLpec::Invocable::InvokeAction(Invocation& aInvocation)
{
    AutoMutex a(iDevice.iLock);
    iDevice.iResponseHandler = this;
    iInvocation = &aInvocation;
    iDevice.iWriteBuffer->Write(Lpec::kMethodAction);
    iDevice.iWriteBuffer->Write(' ');
    iDevice.iWriteBuffer->Write(iDevice.iLpecName);
    iDevice.iWriteBuffer->Write('/');
    iDevice.iWriteBuffer->Write(aInvocation.ServiceType().Name());
    iDevice.iWriteBuffer->Write(' ');
    Bws<Ascii::kMaxUintStringBytes> verBuf;
    (void)Ascii::AppendDec(verBuf, aInvocation.ServiceType().Version());
    iDevice.iWriteBuffer->Write(verBuf);
    iDevice.iWriteBuffer->Write(' ');
    iDevice.iWriteBuffer->Write(aInvocation.Action().Name());
    std::vector<Argument*> inputArgs = aInvocation.InputArguments();
    for (TUint i=0; i<inputArgs.size(); i++) {
        inputArgs[i]->ProcessInput(*this);
    }
    iDevice.iWriteBuffer->Write(Lpec::kMsgTerminator);
    iDevice.iWriteBuffer->WriteFlush();

    iSem.Wait(); // wait for response
    iInvocation = NULL;
    iDevice.iResponseHandler = NULL;
}

void CpiDeviceLpec::Invocable::ProcessString(const Brx& aVal)
{
    iDevice.iWriteBuffer->Write(' ');
    iDevice.iWriteBuffer->Write(Lpec::kArgumentDelimiter);
    Converter::ToXmlEscaped(*(iDevice.iWriteBuffer), aVal);
    iDevice.iWriteBuffer->Write(Lpec::kArgumentDelimiter);
}

void CpiDeviceLpec::Invocable::ProcessInt(TInt aVal)
{
    iDevice.iWriteBuffer->Write(' ');
    iDevice.iWriteBuffer->Write(Lpec::kArgumentDelimiter);
    Bws<Ascii::kMaxIntStringBytes> valBuf;
    (void)Ascii::AppendDec(valBuf, aVal);
    iDevice.iWriteBuffer->Write(valBuf);
    iDevice.iWriteBuffer->Write(Lpec::kArgumentDelimiter);
}

void CpiDeviceLpec::Invocable::ProcessUint(TUint aVal)
{
    iDevice.iWriteBuffer->Write(' ');
    iDevice.iWriteBuffer->Write(Lpec::kArgumentDelimiter);
    Bws<Ascii::kMaxUintStringBytes> valBuf;
    (void)Ascii::AppendDec(valBuf, aVal);
    iDevice.iWriteBuffer->Write(valBuf);
    iDevice.iWriteBuffer->Write(Lpec::kArgumentDelimiter);
}

void CpiDeviceLpec::Invocable::ProcessBool(TBool aVal)
{
    iDevice.iWriteBuffer->Write(' ');
    iDevice.iWriteBuffer->Write(Lpec::kArgumentDelimiter);
    iDevice.iWriteBuffer->Write(aVal? Lpec::kBoolTrue : Lpec::kBoolFalse);
    iDevice.iWriteBuffer->Write(Lpec::kArgumentDelimiter);
}

void CpiDeviceLpec::Invocable::ProcessBinary(const Brx& aVal)
{
    iDevice.iWriteBuffer->Write(' ');
    iDevice.iWriteBuffer->Write(Lpec::kArgumentDelimiter);
    Converter::ToBase64(*(iDevice.iWriteBuffer), aVal);
    iDevice.iWriteBuffer->Write(Lpec::kArgumentDelimiter);
}

TBool CpiDeviceLpec::Invocable::HandleLpecResponse(const Brx& aMethod, const Brx& aBody)
{
    Brn body = Ascii::Trim(aBody);
    Parser parser(body);
    if (aMethod == Lpec::kMethodError) {
        TUint code = 0;
        try {
            Brn codeBuf = parser.Next(' ');
            code = Ascii::Uint(codeBuf);
        }
        catch (AsciiError&) {
        }
        parser.Next(Lpec::kArgumentDelimiter);
        Brn description = parser.Next(Lpec::kArgumentDelimiter);
        iInvocation->SetError(Error::eUpnp/*nearest alternative to eProtocol*/, code, description);
        iSem.Signal();
        return true;
    }
    else if (aMethod != Lpec::kMethodResponse) {
        return false;
    }

    const std::vector<Argument*>& outArgs = iInvocation->OutputArguments();
    try {
        OutputProcessor outputProcessor;
        for (TUint i=0; i<outArgs.size(); i++) {
            parser.Next(Lpec::kArgumentDelimiter);
            Brn valBuf = parser.Next(Lpec::kArgumentDelimiter);
            outArgs[i]->ProcessOutput(outputProcessor, valBuf);
        }
    }
    catch (Exception&) {
        iSem.Signal();
        THROW(ReaderError);
    }
    iSem.Signal();

    return true;
}


// CpiDeviceLpec::SubscriptionResponse

CpiDeviceLpec::SubscriptionResponse::SubscriptionResponse(Semaphore& aComplete)
    : iComplete(aComplete)
{
}

const Brx& CpiDeviceLpec::SubscriptionResponse::SidFragment() const
{
    return iSidFragment;
}

TBool CpiDeviceLpec::SubscriptionResponse::HandleLpecResponse(const Brx& aMethod, const Brx& aBody)
{
    if (aMethod != Lpec::kMethodSubscribe) {
        return false;
    }
    iSidFragment.Set(Ascii::Trim(aBody));
    iComplete.Signal();
    return true;
}


// CpiDeviceLpec::OutputProcessor

void CpiDeviceLpec::OutputProcessor::ProcessString(const Brx& aBuffer, Brhz& aVal)
{
    // Constructs Bwn over the Brhz in order to save copying twice
    aVal.Set(aBuffer);
    Bwn writeable(aVal.Ptr(), aVal.Bytes(), aVal.Bytes());
    Converter::FromXmlEscaped(writeable);
    aVal.Shrink(writeable.Bytes());
}

void CpiDeviceLpec::OutputProcessor::ProcessInt(const Brx& aBuffer, TInt& aVal)
{
    aVal = Ascii::Int(aBuffer);
}

void CpiDeviceLpec::OutputProcessor::ProcessUint(const Brx& aBuffer, TUint& aVal)
{
    aVal = Ascii::Uint(aBuffer);
}

void CpiDeviceLpec::OutputProcessor::ProcessBool(const Brx& aBuffer, TBool& aVal)
{
    if (aBuffer == Brn("1") || Ascii::CaseInsensitiveEquals(aBuffer, Lpec::kBoolTrue)) {
        aVal = true;
    }
    else if (aBuffer == Brn("0") || Ascii::CaseInsensitiveEquals(aBuffer, Lpec::kBoolFalse)) {
        aVal = false;
    }
    else {
        THROW(AsciiError);
    }
}

void CpiDeviceLpec::OutputProcessor::ProcessBinary(const Brx& aBuffer, Brh& aVal)
{
    Bwh copy(aBuffer);
    Converter::FromBase64(copy);
    copy.TransferTo(aVal);
}
