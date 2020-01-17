#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviServerLpec.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Printer.h>

#include <limits.h>

#ifdef _WIN32
# pragma warning(disable:4702) // don't warn about unreachable code (gcc can't figure out it isn't reachable)
#endif

using namespace OpenHome;
using namespace OpenHome::Net;

// Lpec

const Brn Lpec::kMethodAlive("ALIVE");
const Brn Lpec::kMethodByeBye("BYEBYE");
const Brn Lpec::kMethodAction("ACTION");
const Brn Lpec::kMethodSubscribe("SUBSCRIBE");
const Brn Lpec::kMethodUnsubscribe("UNSUBSCRIBE");
const Brn Lpec::kMethodResponse("RESPONSE");
const Brn Lpec::kMethodEvent("EVENT");
const Brn Lpec::kMethodError("ERROR");
const Brn Lpec::kBoolTrue("true");
const Brn Lpec::kBoolFalse("false");
const Brn Lpec::kMsgTerminator("\r\n");


// LpecError

TUint LpecError::Code() const
{
    return iCode;
}

const Brx& LpecError::Description() const
{
    return iDescription;
}

LpecError::LpecError(TUint aCode, const TChar* aDescription)
    : iCode(aCode)
    , iDescription(aDescription)
{
}

class LpecErrorMaker : public LpecError
{
public:
    LpecErrorMaker(TUint aCode, const TChar* aDescription)
        : LpecError(aCode, aDescription)
    {
    }
};

const LpecError LpecError::kCommandNotRecognised = LpecErrorMaker(101, "Command not recognised");
const LpecError LpecError::kServiceNotSpecified = LpecErrorMaker(102, "Service not specified");
const LpecError LpecError::kServiceNotFound = LpecErrorMaker(103, "Service not found");
const LpecError LpecError::kVersionInvalid = LpecErrorMaker(104, "Version invalid");
const LpecError LpecError::kVersionNotSpecified = LpecErrorMaker(105, "Version not specified");
const LpecError LpecError::kVersionNotSupported = LpecErrorMaker(106, "Version not supported");
const LpecError LpecError::kMethodNotSpecified = LpecErrorMaker(107, "Method not specified");
const LpecError LpecError::kMethodExecutionError = LpecErrorMaker(108, "Method execution exception");
const LpecError LpecError::kMethodNotSupported = LpecErrorMaker(109, "Method not supported");
const LpecError LpecError::kInvalidCommandTerminator = LpecErrorMaker(110, "Invalid command terminator (expected CRLF)");
const LpecError LpecError::kDeviceNotFound = LpecErrorMaker(111, "Device not found");
const LpecError LpecError::kInvalidArgBool = LpecErrorMaker(201, "Boolean argument invalid");
const LpecError LpecError::kInvalidArgUint = LpecErrorMaker(203, "Unsigned numeric argument invalid");
const LpecError LpecError::kInvalidArgInt = LpecErrorMaker(204, "Signed numeric invalid");
const LpecError LpecError::kAlreadySubscribed = LpecErrorMaker(401, "Already subscribed");
//const LpecError LpecError::kTooManySubscriptions = LpecErrorMaker(402, "Client has too many subscriptions");
const LpecError LpecError::kSubscriptionNotFound = LpecErrorMaker(404, "Subscription not found");
const LpecError LpecError::kServiceNotSubscribed = LpecErrorMaker(405, "Service not subscribed");


// PropertyWriterFactoryLpec

PropertyWriterFactoryLpec::PropertyWriterFactoryLpec(IEventWriter& aEventWriter)
    : iLock("PFL1")
    , iRefCount(1)
    , iEventWriter(aEventWriter)
    , iEnabled(true)
    , iSubscriptionMapLock("PFL2")
{
}

void PropertyWriterFactoryLpec::SubscriptionAdded(DviSubscription& aSubscription)
{
    iSubscriptionMapLock.Wait();
    Brn sidBuf(aSubscription.Sid());
    iSubscriptionMap.insert(std::pair<Brn,DviSubscription*>(sidBuf, &aSubscription));
    iSubscriptionMapLock.Signal();
    AddRef();
}

void PropertyWriterFactoryLpec::Disable()
{
    iLock.Wait();
    iEnabled = false;
    iLock.Signal();
    iSubscriptionMapLock.Wait();
    std::vector<DviSubscription*> subscriptions(iSubscriptionMap.size());
    SubscriptionMap::iterator it = iSubscriptionMap.begin();
    if (it != iSubscriptionMap.end()) {
        DviSubscription* subscription = it->second;
        if (subscription->TryAddRef()) {
            subscriptions.push_back(subscription);
        }
        it++;
    }
    iSubscriptionMapLock.Signal();
    for (TUint i=0; i<(TUint)subscriptions.size(); i++) {
        DviSubscription* subscription = subscriptions[i];
        subscription->Remove();
        subscription->RemoveRef();
    }
    RemoveRef();
}

IPropertyWriter* PropertyWriterFactoryLpec::ClaimWriter(const IDviSubscriptionUserData* /*aUserData*/, const Brx& aSid, TUint aSequenceNumber)
{
    {
        AutoMutex a(iLock);
        if (!iEnabled) {
            return NULL;
        }
        iEventWriter.Lock();
    }
    try {
        TUint lpecSid = iEventWriter.LpecSid(aSid);
        iEventWriter.Write(Lpec::kMethodEvent);
        iEventWriter.Write(' ');
        Bws<Ascii::kMaxUintStringBytes> lpecSidBuf;
        Ascii::AppendDec(lpecSidBuf, lpecSid);
        iEventWriter.Write(lpecSidBuf);
        iEventWriter.Write(' ');
        Bws<Ascii::kMaxUintStringBytes> seq;
        (void)Ascii::AppendDec(seq, aSequenceNumber);
        iEventWriter.Write(seq);
    }
    catch (WriterError&) {
        iEventWriter.Unlock();
        throw;
    }
    return this;
}

void PropertyWriterFactoryLpec::ReleaseWriter(IPropertyWriter* /*aWriter*/)
{
}

void PropertyWriterFactoryLpec::NotifySubscriptionCreated(const Brx& /*aSid*/)
{
}

void PropertyWriterFactoryLpec::NotifySubscriptionDeleted(const Brx& aSid)
{
    AddRef();
    iSubscriptionMapLock.Wait();
    Brn sid(aSid);
    SubscriptionMap::iterator it = iSubscriptionMap.find(sid);
    if (it != iSubscriptionMap.end()) {
        iSubscriptionMap.erase(it);
        RemoveRef();
    }
    iSubscriptionMapLock.Signal();
    RemoveRef();
}

void PropertyWriterFactoryLpec::NotifySubscriptionExpired(const Brx& /*aSid*/)
{
}

void PropertyWriterFactoryLpec::LogUserData(IWriter& aWriter, const IDviSubscriptionUserData& /*aUserData*/)
{
    aWriter.Write(Brn(", protocol: LPEC"));
}

void PropertyWriterFactoryLpec::PropertyWriteString(const Brx& aName, const Brx& aValue)
{
    try {
        iEventWriter.Write(' ');
        iEventWriter.Write(aName);
        iEventWriter.Write(' ');
        iEventWriter.Write(Lpec::kArgumentDelimiter);
        Converter::ToXmlEscaped(iEventWriter, aValue);
        iEventWriter.Write(Lpec::kArgumentDelimiter);
    }
    catch (WriterError&) {
        iEventWriter.Unlock();
        throw;
    }
}

void PropertyWriterFactoryLpec::PropertyWriteInt(const Brx& aName, TInt aValue)
{
    try {
        iEventWriter.Write(' ');
        iEventWriter.Write(aName);
        iEventWriter.Write(' ');
        iEventWriter.Write(Lpec::kArgumentDelimiter);
        Bws<Ascii::kMaxIntStringBytes> valBuf;
        (void)Ascii::AppendDec(valBuf, aValue);
        iEventWriter.Write(valBuf);
        iEventWriter.Write(Lpec::kArgumentDelimiter);
    }
    catch (WriterError&) {
        iEventWriter.Unlock();
        throw;
    }
}

void PropertyWriterFactoryLpec::PropertyWriteUint(const Brx& aName, TUint aValue)
{
    try {
        iEventWriter.Write(' ');
        iEventWriter.Write(aName);
        iEventWriter.Write(' ');
        iEventWriter.Write(Lpec::kArgumentDelimiter);
        Bws<Ascii::kMaxUintStringBytes> valBuf;
        (void)Ascii::AppendDec(valBuf, aValue);
        iEventWriter.Write(valBuf);
        iEventWriter.Write(Lpec::kArgumentDelimiter);
    }
    catch (WriterError&) {
        iEventWriter.Unlock();
        throw;
    }
}

void PropertyWriterFactoryLpec::PropertyWriteBool(const Brx& aName, TBool aValue)
{
    try {
        iEventWriter.Write(' ');
        iEventWriter.Write(aName);
        iEventWriter.Write(' ');
        iEventWriter.Write(Lpec::kArgumentDelimiter);
        iEventWriter.Write(aValue? Lpec::kBoolTrue : Lpec::kBoolFalse);
        iEventWriter.Write(Lpec::kArgumentDelimiter);
    }
    catch (WriterError&) {
        iEventWriter.Unlock();
        throw;
    }
}

void PropertyWriterFactoryLpec::PropertyWriteBinary(const Brx& aName, const Brx& aValue)
{
    try {
        iEventWriter.Write(' ');
        iEventWriter.Write(aName);
        iEventWriter.Write(' ');
        iEventWriter.Write(Lpec::kArgumentDelimiter);
        Converter::ToBase64(iEventWriter, aValue);
        iEventWriter.Write(Lpec::kArgumentDelimiter);
    }
    catch (WriterError&) {
        iEventWriter.Unlock();
        throw;
    }
}

void PropertyWriterFactoryLpec::PropertyWriteEnd()
{
    try {
        iEventWriter.Write(Lpec::kMsgTerminator);
        iEventWriter.WriteFlush();
    }
    catch (WriterError&) {
        iEventWriter.Unlock();
        throw;
    }
    iEventWriter.Unlock();
}

void PropertyWriterFactoryLpec::Release()
{
}

PropertyWriterFactoryLpec::~PropertyWriterFactoryLpec()
{
}

void PropertyWriterFactoryLpec::AddRef()
{
    iLock.Wait();
    iRefCount++;
    iLock.Signal();
}

void PropertyWriterFactoryLpec::RemoveRef()
{
    iLock.Wait();
    iRefCount--;
    const TBool dead = (iRefCount == 0);
    iLock.Signal();
    if (dead) {
        delete this;
    }
}


// DviSessionLpec

DviSessionLpec::DviSessionLpec(DvStack& aDvStack, TIpAddress aAdapter, TUint aPort)
    : iDvStack(aDvStack)
    , iAdapter(aAdapter)
    , iPort(aPort)
    , iWriteLock("DLP1")
    , iShutdownSem("DLP2", 1)
    , iSubscriptionLock("DLP3")
    , iByeByeLock("DLP4")
    , iDeviceLock("DLP5")
    , iActive(false)
{
    iReadBuffer = new Srs<1024>(*this);
    iReaderUntil = new ReaderUntilS<kMaxReadBytes>(*iReadBuffer);
    iWriteBuffer = new Sws<kWriteBufferBytes>(*this);
    iEventWriterAdapter = new EventWriterAdapter(*iWriteBuffer, iWriteLock, iSubscriptions);
    iPropertyWriterFactory = new PropertyWriterFactoryLpec(*iEventWriterAdapter);
}

DviSessionLpec::~DviSessionLpec()
{
    iReadBuffer->ReadInterrupt();
    iSubscriptionLock.Wait();
    iPropertyWriterFactory->Disable();
    iSubscriptions.clear();
    iSubscriptionLock.Signal();
    iShutdownSem.Wait();
    iWriteLock.Wait();
    /* nothing to do inside this lock.  Taking it after calling Disable() confirms that
       no evented update is currently using iWriteBuffer. */
    iWriteLock.Signal();
    delete iEventWriterAdapter;
    delete iReaderUntil;
    delete iReadBuffer;
    delete iWriteBuffer;
}

void DviSessionLpec::SendAnnouncement()
{
    if (!iActive) {
        return;
    }
    Announce();
}

void DviSessionLpec::NotifyDeviceDisabled(const Brx& aName, const Brx& aUdn)
{
    AutoMutex a(iByeByeLock);
    if (!iActive) {
        return;
    }
    AutoMutex b(iDeviceLock);
    Brn udn(aUdn);
    std::map<Brn,DviDevice*,BufferCmp>::iterator it = iDeviceMap.find(udn);
    if (it == iDeviceMap.end()) {
        return; // FIXME - assumes that ALIVEs are only sent on connection - not when (if) a device is later enabled
    }
    it->second->RemoveWeakRef();
    iDeviceMap.erase(it);
    try {
        AutoMutex c(iWriteLock);
        iWriteBuffer->Write(Lpec::kMethodByeBye);
        iWriteBuffer->Write(' ');
        iWriteBuffer->Write(aName);
        iWriteBuffer->Write(' ');
        iWriteBuffer->Write(aUdn);
        iWriteBuffer->Write(Lpec::kMsgTerminator);
        iWriteBuffer->WriteFlush();
    }
    catch (WriterError&) {
    }
}

void DviSessionLpec::Run()
{
    iShutdownSem.Wait();
    iByeByeLock.Wait();
    iActive = true;
    iByeByeLock.Signal();
    try {
        iDeviceLock.Wait();
        iDeviceMap = iDvStack.DeviceMap().CopyMap();
        iDeviceLock.Signal();

        Announce();
        iDvStack.NotifyControlPointUsed(Brn("Lpec/none"));

        for (;;) {
            Brn req = Ascii::Trim(iReaderUntil->ReadUntil(Ascii::kLf));
            iRequestBuf.Set(req);
            iResponseStarted = iResponseEnded = false;
            iParser.Set(iRequestBuf);
            Brn method = iParser.Next(' ');
            try {
                if (Ascii::CaseInsensitiveEquals(method, Lpec::kMethodAction)) {
                    Action();
                }
                else if (Ascii::CaseInsensitiveEquals(method, Lpec::kMethodSubscribe)) {
                    Subscribe();
                }
                else if (Ascii::CaseInsensitiveEquals(method, Lpec::kMethodUnsubscribe)) {
                    Unsubscribe();
                }
                else if (method.Bytes() == 0) {
                    /* Allow blank lines - these may be entered to make output from
                       manual LPEC session more readable */
                    continue;
                }
                else {
                    ReportErrorNoThrow(LpecError::kCommandNotRecognised);
                }
            }
            catch (LpecParseError&) {
            }
            catch (InvocationError&) {
            }
            if (!iResponseStarted) {
                ASSERT(!iResponseEnded);
                ReportErrorNoThrow(LpecError::kMethodExecutionError);
            }
            if (!iResponseEnded) {
                InvocationWriteEnd();
            }
        }
    }
    catch (ReaderError&) {
    }
    catch (WriterError&) {
    }

    iDeviceLock.Wait();
    std::map<Brn,DviDevice*,BufferCmp>::iterator it = iDeviceMap.begin();
    while (it != iDeviceMap.end()) {
        it->second->RemoveWeakRef();
        it++;
    }
    iDeviceMap.clear();
    iDeviceLock.Signal();
    iSubscriptionLock.Wait();
    while (iSubscriptions.size() != 0) {
        DoUnsubscribe(0, false);
    }
    iSubscriptions.clear();
    iSubscriptionLock.Signal();

    iByeByeLock.Wait();
    iActive = false;
    iByeByeLock.Signal();
    iShutdownSem.Signal();
}

void DviSessionLpec::Announce()
{
    AutoMutex _(iDeviceLock);
    AutoMutex __(iWriteLock);
    for (std::map<Brn, DviDevice*, BufferCmp>::iterator it = iDeviceMap.begin(); it != iDeviceMap.end(); ++it) {
        if (!it->second->Enabled()) {
            continue;
        }
        iWriteBuffer->Write(Lpec::kMethodAlive);
        iWriteBuffer->Write(' ');
        const TChar* name = NULL;
        it->second->GetAttribute("Lpec.Name", &name);
        if (name == NULL) {
            Log::Print("ERROR: device ");
            Log::Print(it->second->Udn());
            Log::Print(" has no Lpec.Name attribute so isn't usable over LPEC\n");
        }
        else {
            iWriteBuffer->Write(Brn(name));
        }
        iWriteBuffer->Write(' ');
        iWriteBuffer->Write(it->second->Udn());
        iWriteBuffer->Write(Lpec::kMsgTerminator);
        iWriteBuffer->WriteFlush();
    }
}

void DviSessionLpec::Action()
{
    try {
        AutoMutex a(iDeviceLock);
        ParseDeviceAndService();
        Brn versionBuf = iParser.Next(' ');
        try {
            iVersion = Ascii::Uint(versionBuf);
        }
        catch (AsciiError&) {
            ReportError(LpecError::kVersionNotSpecified);
        }
        if (iVersion > iTargetService->ServiceType().Version()) {
            ReportError(LpecError::kVersionNotSupported);
        }
        Invoke();
    }
    catch (LpecParseError&) {
    }
    catch (InvocationError&) {
    }
}

void DviSessionLpec::Subscribe()
{
    DviSubscription* subscription = NULL;
    TUint lpecSid = UINT_MAX;
    {
        AutoMutex a(iSubscriptionLock);
        AutoMutex b(iDeviceLock);
        ParseDeviceAndService();

        // check we don't already have a subscription for this service
        for (TUint i=0; i<iSubscriptions.size(); i++) {
            if (iSubscriptions[i].Matches(*iTargetDevice, *iTargetService)) {
                ReportError(LpecError::kAlreadySubscribed);
            }
        }

        Brh sid;
        iTargetDevice->CreateSid(sid);
        subscription = new DviSubscription(iDvStack, *iTargetDevice, *iPropertyWriterFactory, NULL, sid);
        iPropertyWriterFactory->SubscriptionAdded(*subscription);
        iDvStack.SubscriptionManager().AddSubscription(*subscription);
        lpecSid = iDvStack.Env().SequenceNumber();

        SubscriptionData data(*iTargetDevice, *iTargetService, *subscription, lpecSid);
        iSubscriptions.push_back(data);
    }

    // respond to subscription request
    {
        AutoMutex a(iWriteLock);
        iResponseStarted = true;
        iWriteBuffer->Write(Lpec::kMethodSubscribe);
        iWriteBuffer->Write(' ');
        Bws<Ascii::kMaxUintStringBytes> lpecSidBuf;
        (void)Ascii::AppendDec(lpecSidBuf, lpecSid);
        iWriteBuffer->Write(lpecSidBuf); // a 2012 doc from service team commits us to using integer sids for LPEC
        iWriteBuffer->Write(Lpec::kMsgTerminator);
        iWriteBuffer->WriteFlush();
        iResponseEnded = true;
    }

    // Start subscription, prompting delivery of the first update (covering all state variables)
    iTargetService->AddSubscription(subscription);
}

void DviSessionLpec::Unsubscribe()
{
    AutoMutex a(iSubscriptionLock);
    Brn cmd = Ascii::Trim(iParser.Remaining());
    if (cmd.Bytes() == 0) {
        for (TUint i=0; i<iSubscriptions.size(); i++) {
            DoUnsubscribe(0);
        }
        return;
    }

    try {
        const TUint lpecSid = Ascii::Uint(cmd);
        for (TUint i=0; i<iSubscriptions.size(); i++) {
            if (iSubscriptions[i].LpecSid() == lpecSid) {
                DoUnsubscribe(i);
                return;
            }
        }
        ReportError(LpecError::kSubscriptionNotFound);
    }
    catch (AsciiError&) {
        // not a sid, fall through to below to check for device/service
    }

    AutoMutex b(iDeviceLock);
    ParseDeviceAndService();
    for (TUint i=0; i<iSubscriptions.size(); i++) {
        if (iSubscriptions[i].Matches(*iTargetDevice, *iTargetService)) {
            DoUnsubscribe(i);
            return;
        }
    }
    ReportError(LpecError::kServiceNotSubscribed);
}

void DviSessionLpec::ParseDeviceAndService()
{
    iTargetDevice = NULL;
    iTargetService = NULL;

    Brn deviceName = iParser.Next('/');
    std::map<Brn,DviDevice*,BufferCmp>::iterator it = iDeviceMap.begin();
    while (it != iDeviceMap.end()) {
        const TChar* name = NULL;
        it->second->GetAttribute("Lpec.Name", &name);
        if (name != NULL && Brn(name) == deviceName) {
            iTargetDevice = it->second;
            break;
        }
        it++;
    }
    if (iTargetDevice == NULL) {
        ReportErrorNoThrow(LpecError::kDeviceNotFound);
        THROW(LpecParseError);
    }

    Brn serviceName = iParser.Next(' ');
    const TUint count = iTargetDevice->ServiceCount();
    for (TUint i=0; i<count; i++) {
        DviService& service = iTargetDevice->Service(i);
        if (service.ServiceType().Name() == serviceName) {
            iTargetService = &service;
            break;
        }
    }
    if (iTargetService == NULL) {
        ReportErrorNoThrow(LpecError::kServiceNotFound);
        THROW(LpecParseError);
    }
}

void DviSessionLpec::DoUnsubscribe(TUint aIndex, TBool aRespond)
{
    DviSubscription* subscription = iSubscriptions[aIndex].Subscription();
    ASSERT(subscription != NULL);
    iSubscriptions[aIndex].Service().RemoveSubscription(subscription->Sid());

    if (aRespond) {
        AutoMutex a(iWriteLock);
        iResponseStarted = true;
        iWriteBuffer->Write(Lpec::kMethodUnsubscribe);
        iWriteBuffer->Write(' ');
        Bws<Ascii::kMaxUintStringBytes> lpecSidBuf;
        (void)Ascii::AppendDec(lpecSidBuf, iSubscriptions[aIndex].LpecSid());
        iWriteBuffer->Write(lpecSidBuf);
        iWriteBuffer->Write(Lpec::kMsgTerminator);
        iWriteBuffer->WriteFlush();
        iResponseEnded = true;
    }

    iSubscriptions.erase(iSubscriptions.begin()+aIndex);
}

void DviSessionLpec::ReportError(const LpecError& aError)
{
    ReportErrorNoThrow(aError);
    THROW(InvocationError);
}

void DviSessionLpec::ReportErrorNoThrow(const LpecError& aError)
{
    ReportErrorNoThrow(aError.Code(), aError.Description());
}

void DviSessionLpec::ReportErrorNoThrow(TUint aCode, const Brx& aDescription)
{
    if (!iResponseStarted) {
        ASSERT(!iResponseEnded);
        iWriteLock.Wait();
        iWriteBuffer->Write(Lpec::kMethodError);
        iWriteBuffer->Write(' ');
        Bws<Ascii::kMaxUintStringBytes> code;
        (void)Ascii::AppendDec(code, aCode);
        iWriteBuffer->Write(code);
        iWriteBuffer->Write(' ');
        iWriteBuffer->Write(Lpec::kArgumentDelimiter);
        iWriteBuffer->Write(aDescription);
        iWriteBuffer->Write(Lpec::kArgumentDelimiter);
    }
    iResponseStarted = true;
}

void DviSessionLpec::Invoke()
{
    Brn actionName = iParser.Next(' ');
    iTargetService->InvokeDirect(*this, actionName);
}

TUint DviSessionLpec::Version() const
{
    return iVersion;
}

TIpAddress DviSessionLpec::Adapter() const
{
    return iAdapter;
}

const char* DviSessionLpec::ResourceUriPrefix() const
{
    // FIXME - duplicated from DviProtocolUpnp and DviServerUpnp
    iResourceUriPrefix.SetBytes(0);
    iResourceUriPrefix.Append("http://");
    Endpoint ep(iPort, iAdapter);
    ep.AppendEndpoint(iResourceUriPrefix);
    iResourceUriPrefix.Append("/");
    iResourceUriPrefix.Append(iTargetDevice->Udn());
    iResourceUriPrefix.Append("/");
    iResourceUriPrefix.Append("Upnp");
    iResourceUriPrefix.Append("/");
    iResourceUriPrefix.Append("resource");
    iResourceUriPrefix.Append("/");
    iResourceUriPrefix.PtrZ();
    return (const char*)iResourceUriPrefix.Ptr();
}

Endpoint DviSessionLpec::ClientEndpoint() const
{
    Endpoint ep(SocketTcpSession::ClientEndpoint());
    return ep;
}

const Brx& DviSessionLpec::ClientUserAgent() const
{
    return Brx::Empty();
}

void DviSessionLpec::InvocationReadStart()
{
    // nothing to do here
}

TBool DviSessionLpec::InvocationReadBool(const TChar* /*aName*/)
{
    (void)iParser.Next(Lpec::kArgumentDelimiter);
    Brn val = iParser.Next(Lpec::kArgumentDelimiter);
    if (Ascii::CaseInsensitiveEquals(val, Lpec::kBoolFalse) ||
        (val.Bytes() == 1 && val[0] == '0')) {
        return false;
    }
    if (Ascii::CaseInsensitiveEquals(val, Lpec::kBoolTrue) ||
        (val.Bytes() == 1 && val[0] == '1')) {
        return true;
    }
    ReportError(LpecError::kInvalidArgBool);
    return false; // never reached
}

void DviSessionLpec::InvocationReadString(const TChar* /*aName*/, Brhz& aString)
{
    (void)iParser.Next(Lpec::kArgumentDelimiter);
    Brn val = iParser.NextNoTrim(Lpec::kArgumentDelimiter);
    Bwh writable(val.Bytes()+1);
    if (val.Bytes()) {
        writable.Append(val);
        Converter::FromXmlEscaped(writable);
    }
    writable.PtrZ();
    writable.TransferTo(aString);
}

TInt DviSessionLpec::InvocationReadInt(const TChar* /*aName*/)
{
    (void)iParser.Next(Lpec::kArgumentDelimiter);
    try {
        Brn val = iParser.Next(Lpec::kArgumentDelimiter);
        return Ascii::Int(val);
    }
    catch (AsciiError&) {
        ReportError(LpecError::kInvalidArgInt);
    }
    return 0; // never reached
}

TUint DviSessionLpec::InvocationReadUint(const TChar* /*aName*/)
{
    (void)iParser.Next(Lpec::kArgumentDelimiter);
    try {
        Brn val = iParser.Next(Lpec::kArgumentDelimiter);
        return Ascii::Uint(val);
    }
    catch (AsciiError&) {
        ReportError(LpecError::kInvalidArgUint);
    }
    return 0; // never reached
}

void DviSessionLpec::InvocationReadBinary(const TChar* /*aName*/, Brh& aData)
{
    (void)iParser.Next(Lpec::kArgumentDelimiter);
    Brn val = iParser.NextNoTrim(Lpec::kArgumentDelimiter);
    if (val.Bytes() != 0) {
        Bwh writable(val.Bytes()+1);
        writable.Append(val);
        Converter::FromBase64(writable);
        writable.TransferTo(aData);
    }
}

void DviSessionLpec::InvocationReadEnd()
{
    // nothing to do here
}

void DviSessionLpec::InvocationReportError(TUint aCode, const Brx& aDescription)
{
    ReportErrorNoThrow(aCode, aDescription);
    THROW(InvocationError);
}

void DviSessionLpec::InvocationWriteStart()
{
    iWriteLock.Wait();
    iWriteBuffer->Write(Lpec::kMethodResponse);
    iResponseStarted = true;
}

void DviSessionLpec::InvocationWriteBool(const TChar* /*aName*/, TBool aValue)
{
    iWriteBuffer->Write(' ');
    iWriteBuffer->Write(Lpec::kArgumentDelimiter);
    iWriteBuffer->Write(aValue? Lpec::kBoolTrue : Lpec::kBoolFalse);
    iWriteBuffer->Write(Lpec::kArgumentDelimiter);
}

void DviSessionLpec::InvocationWriteInt(const TChar* /*aName*/, TInt aValue)
{
    iWriteBuffer->Write(' ');
    iWriteBuffer->Write(Lpec::kArgumentDelimiter);
    Bws<Ascii::kMaxIntStringBytes> val;
    (void)Ascii::AppendDec(val, aValue);
    iWriteBuffer->Write(val);
    iWriteBuffer->Write(Lpec::kArgumentDelimiter);
}

void DviSessionLpec::InvocationWriteUint(const TChar* /*aName*/, TUint aValue)
{
    iWriteBuffer->Write(' ');
    iWriteBuffer->Write(Lpec::kArgumentDelimiter);
    Bws<Ascii::kMaxUintStringBytes> val;
    (void)Ascii::AppendDec(val, aValue);
    iWriteBuffer->Write(val);
    iWriteBuffer->Write(Lpec::kArgumentDelimiter);
}

void DviSessionLpec::InvocationWriteBinaryStart(const TChar* /*aName*/)
{
    iWriteBuffer->Write(' ');
    iWriteBuffer->Write(Lpec::kArgumentDelimiter);
}

void DviSessionLpec::InvocationWriteBinary(TByte aValue)
{
    iWriteBuffer->Write(aValue);
}

void DviSessionLpec::InvocationWriteBinary(const Brx& aValue)
{
    Converter::ToBase64(*iWriteBuffer, aValue);
}

void DviSessionLpec::InvocationWriteBinaryEnd(const TChar* /*aName*/)
{
    iWriteBuffer->Write(Lpec::kArgumentDelimiter);
}

void DviSessionLpec::InvocationWriteStringStart(const TChar* /*aName*/)
{
    iWriteBuffer->Write(' ');
    iWriteBuffer->Write(Lpec::kArgumentDelimiter);
}

void DviSessionLpec::InvocationWriteString(TByte aValue)
{
    Brn buf(&aValue, 1);
    InvocationWriteString(buf);
}

void DviSessionLpec::InvocationWriteString(const Brx& aValue)
{
    Converter::ToXmlEscaped(*iWriteBuffer, aValue);
}

void DviSessionLpec::InvocationWriteStringEnd(const TChar* /*aName*/)
{
    iWriteBuffer->Write(Lpec::kArgumentDelimiter);
}

void DviSessionLpec::InvocationWriteEnd()
{
    ASSERT(iResponseStarted);
    iResponseEnded = true;
    try {
        iWriteBuffer->Write(Lpec::kMsgTerminator);
        iWriteBuffer->WriteFlush();
    }
    catch (WriterError&) {
    }
    iWriteLock.Signal();
}


// DviSessionLpec::SubscriptionData

DviSessionLpec::SubscriptionData::SubscriptionData(DviDevice& aDevice, DviService& aService, DviSubscription& aSubscription, TUint aLpecSubscriptionId)
    : iDevice(&aDevice)
    , iService(&aService)
    , iSubscription(&aSubscription)
    , iLpecSubscriptionId(aLpecSubscriptionId)
{
}

TBool DviSessionLpec::SubscriptionData::Matches(DviDevice& aDevice, DviService& aService) const
{
    return (iDevice->Udn() == aDevice.Udn() && iService->ServiceType().FullName() == aService.ServiceType().FullName());
}

DviService& DviSessionLpec::SubscriptionData::Service()
{
    return *iService;
}

DviSubscription* DviSessionLpec::SubscriptionData::Subscription()
{
    return iSubscription;
}

TUint DviSessionLpec::SubscriptionData::LpecSid() const
{
    return iLpecSubscriptionId;
}


// DviServerLpec

DviServerLpec::DviServerLpec(DvStack& aDvStack, TUint aPort)
    : DviServer(aDvStack)
    , iPort(aPort)
{
    Initialise();
}

void DviServerLpec::SendAnnouncement()
{
    for (TUint i = 0; i < iAdapterData.size(); i++) {
        AdapterData* ad = iAdapterData[i];
        for (TUint j = 0; j < ad->iSessions.size(); j++) {
            ad->iSessions[j]->SendAnnouncement();
        }
    }
}

void DviServerLpec::NotifyDeviceDisabled(const Brx& aName, const Brx& aUdn)
{
    for (TUint i=0; i<iAdapterData.size(); i++) {
        AdapterData* ad = iAdapterData[i];
        for (TUint j=0; j<ad->iSessions.size(); j++) {
            ad->iSessions[j]->NotifyDeviceDisabled(aName, aUdn);
        }
    }
}

TUint DviServerLpec::Port() const
{
    return iPort;
}

SocketTcpServer* DviServerLpec::CreateServer(const NetworkAdapter& aNif)
{
    SocketTcpServer* server = new SocketTcpServer(iDvStack.Env(), "LpecServer", iPort, aNif.Address());
    const TUint numThreads = iDvStack.Env().InitParams()->DvNumLpecThreads();
    AdapterData* ad = new AdapterData(aNif.Address());
    iAdapterData.push_back(ad);
    for (TUint i=0; i<numThreads; i++) {
        Bws<Thread::kMaxNameBytes+1> thName;
        thName.AppendPrintf("LpecSession %d", i);
        thName.PtrZ();
        DviSessionLpec* session = new DviSessionLpec(iDvStack, aNif.Address(), iPort);
        server->Add((const TChar*)thName.Ptr(), session);
        ad->iSessions.push_back(session);
    }
    return server;
}

DviServerLpec::~DviServerLpec()
{
    Deinitialise();
}

void DviServerLpec::NotifyServerDeleted(TIpAddress aInterface)
{
    for (TUint i=0; i<iAdapterData.size(); i++) {
        AdapterData* ad = iAdapterData[i];
        if (ad->iInterface == aInterface) {
            iAdapterData.erase(iAdapterData.begin() + i);
            delete ad;
            break;
        }
    }
}


// DviServerLpec::AdapterData

DviServerLpec::AdapterData::AdapterData(TIpAddress aInterface)
    : iInterface(aInterface)
{
}



// DviSessionLpec::EventWriterAdapter

DviSessionLpec::EventWriterAdapter::EventWriterAdapter(IWriter& aWriter, Mutex& aLock, std::vector<SubscriptionData>& aSubscriptions)
    : iWriter(aWriter)
    , iLock(aLock)
    , iSubscriptions(aSubscriptions)
{
}

void DviSessionLpec::EventWriterAdapter::Write(TByte aValue)
{
    iWriter.Write(aValue);
}

void DviSessionLpec::EventWriterAdapter::Write(const Brx& aBuffer)
{
    iWriter.Write(aBuffer);
}

void DviSessionLpec::EventWriterAdapter::WriteFlush()
{
    iWriter.WriteFlush();
}

void DviSessionLpec::EventWriterAdapter::Lock()
{
    iLock.Wait();
}

void DviSessionLpec::EventWriterAdapter::Unlock()
{
    iLock.Signal();
}

TUint DviSessionLpec::EventWriterAdapter::LpecSid(const Brx& aSid)
{
    for (TUint i=0; i<iSubscriptions.size(); i++) {
        if (iSubscriptions[i].Subscription()->Sid() == aSid) {
            return iSubscriptions[i].LpecSid();
        }
    }
    ASSERTS();
    return 0; // never reached
}
