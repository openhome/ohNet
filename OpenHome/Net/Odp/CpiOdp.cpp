#include <OpenHome/Net/Odp/CpiOdp.h>
#include <OpenHome/Net/Odp/Odp.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Json.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Net/Private/CpiSubscription.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Debug-ohMediaPlayer.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpiOdpInvocable

CpiOdpInvocable::CpiOdpInvocable(ICpiOdpDevice& aDevice)
    : iDevice(aDevice)
    , iSem("OdpA", 0)
    , iInvocation(nullptr)
{
}

void CpiOdpInvocable::InvokeAction(Invocation& aInvocation)
{
    iWriter = &iDevice.WriteLock(*this);
    AutoOdpDevice _(iDevice);
    iInvocation = &aInvocation;
    WriterJsonObject writerAction(*iWriter);
    writerAction.WriteString(Odp::kKeyType, Odp::kTypeAction);
    writerAction.WriteString(Odp::kKeyDevice, iDevice.Alias());
    auto writerService = writerAction.CreateObject(Odp::kKeyService);
    auto& serviceType = aInvocation.ServiceType();
    writerService.WriteString(Odp::kKeyName, serviceType.Name());
    writerService.WriteInt(Odp::kKeyVersion, serviceType.Version());
    writerService.WriteEnd();
    writerAction.WriteString(Odp::kKeyAction, aInvocation.Action().Name());
    auto args = aInvocation.InputArguments();
    if (args.size() > 0) {
        auto writerArgs = writerAction.CreateObject(Odp::kKeyArguments);
        CpiOdpWriterArgs writerArgValues(writerArgs);
        for (auto it=args.begin(); it!=args.end(); ++it) {
            writerArgValues.Process(**it);
        }
        writerArgs.WriteEnd();
    }
    writerAction.WriteEnd();
    iDevice.WriteEnd(*iWriter);

    iSem.Wait();
    iInvocation = nullptr;
}

TBool CpiOdpInvocable::HandleOdpResponse(const JsonParser& aParser)
{
    if (aParser.String(Odp::kKeyType) != Odp::kTypeActionResponse) {
        return false;
    }
    AutoSemaphoreSignal _(iSem);
    if (!aParser.IsNull(Odp::kKeyError)) {
        JsonParser error;
        error.Parse(aParser.String(Odp::kKeyError));
        const TUint code = (TUint)error.Num(Odp::kKeyCode);
        Brn desc = error.String(Odp::kKeyDescription);
        iInvocation->SetError(Error::eUpnp, code, desc); // FIXME - Error::ELevel doesn't have a level for non-UPnP protocol
        return true;
    }
    const auto& outArgs = iInvocation->OutputArguments();
    if (aParser.IsNull(Odp::kKeyArguments)) {
        if (outArgs.size() > 0) {
            THROW(OdpError);
        }
    }
    else {
        JsonParser argsParser;
        argsParser.Parse(aParser.String(Odp::kKeyArguments));
        CpiOdpOutputProcessor outputProcessor;
        for (auto it=outArgs.begin(); it!=outArgs.end(); ++it) {
            Brn val = argsParser.String((*it)->Parameter().Name());
            (*it)->ProcessOutput(outputProcessor, val);
        }
    }
    return true;
}


// CpiOdpWriterArgs

CpiOdpWriterArgs::CpiOdpWriterArgs(WriterJsonObject& aWriterObject)
    : iWriterObject(aWriterObject)
{
}

void CpiOdpWriterArgs::Process(Argument& aArg)
{
    iArg = &aArg;
    iArg->ProcessInput(*this);
}

void CpiOdpWriterArgs::ProcessString(const Brx& aVal)
{
    WriteString(aVal);
}

void CpiOdpWriterArgs::ProcessInt(TInt aVal)
{
    Bws<Ascii::kMaxIntStringBytes> buf;
    (void)Ascii::AppendDec(buf, aVal);
    WriteString(buf);
}

void CpiOdpWriterArgs::ProcessUint(TUint aVal)
{
    Bws<Ascii::kMaxUintStringBytes> buf;
    (void)Ascii::AppendDec(buf, aVal);
    WriteString(buf);
}

void CpiOdpWriterArgs::ProcessBool(TBool aVal)
{
    WriteString(aVal? WriterJson::kBoolTrue : WriterJson::kBoolFalse);
}

void CpiOdpWriterArgs::ProcessBinary(const Brx& aVal)
{
    iWriterObject.WriteBinary(iArg->Parameter().Name(), aVal);
}

void CpiOdpWriterArgs::WriteString(const Brx& aVal)
{
    iWriterObject.WriteString(iArg->Parameter().Name(), aVal);
}


// CpiOdpOutputProcessor

void CpiOdpOutputProcessor::ProcessString(const Brx& aBuffer, Brhz& aVal)
{
    // Constructs Bwn over the Brhz in order to save copying twice
    aVal.Set(aBuffer);
    Bwn writeable(aVal.Ptr(), aVal.Bytes(), aVal.Bytes());
    Json::Unescape(writeable);
    aVal.Shrink(writeable.Bytes());
}

void CpiOdpOutputProcessor::ProcessInt(const Brx& aBuffer, TInt& aVal)
{
    aVal = Ascii::Int(aBuffer);
}

void CpiOdpOutputProcessor::ProcessUint(const Brx& aBuffer, TUint& aVal)
{
    aVal = Ascii::Uint(aBuffer);
}

void CpiOdpOutputProcessor::ProcessBool(const Brx& aBuffer, TBool& aVal)
{
    if (aBuffer == WriterJson::kBoolTrue) {
        aVal = true;
    }
    else if (aBuffer == WriterJson::kBoolFalse) {
        aVal = false;
    }
    else {
        THROW(JsonInvalid);
    }
}

void CpiOdpOutputProcessor::ProcessBinary(const Brx& aBuffer, Brh& aVal)
{
    Bwh copy(aBuffer);
    Converter::FromBase64(copy);
    copy.TransferTo(aVal);
}


// CpiOdpSubscriber

CpiOdpSubscriber::CpiOdpSubscriber(ICpiOdpDevice& aDevice)
    : iDevice(aDevice)
    , iSem("OdpS", 0)
    , iSubscription(nullptr)
{
}

void CpiOdpSubscriber::Subscribe(CpiSubscription& aSubscription)
{
    iSubscription = &aSubscription;
    auto& writer = iDevice.WriteLock(*this);
    AutoOdpDevice _(iDevice);
    WriterJsonObject writerSubs(writer);
    writerSubs.WriteString(Odp::kKeyType, Odp::kTypeSubscribe);
    writerSubs.WriteString(Odp::kKeyDevice, iDevice.Alias());
    auto writerService = writerSubs.CreateObject(Odp::kKeyService);
    auto& serviceType = aSubscription.ServiceType();
    writerService.WriteString(Odp::kKeyName, serviceType.Name());
    writerService.WriteInt(Odp::kKeyVersion, serviceType.Version());
    writerService.WriteEnd();
    writerSubs.WriteEnd();
    iDevice.WriteEnd(writer);

    iSem.Wait();
    iSubscription = nullptr;
}

TBool CpiOdpSubscriber::HandleOdpResponse(const JsonParser& aParser)
{
    if (aParser.String(Odp::kKeyType) != Odp::kTypeSubscribeResponse) {
        return false;
    }
    AutoSemaphoreSignal _(iSem);
    if (!aParser.IsNull(Odp::kKeyError)) {
        THROW(OdpError);
    }
    Brh sid(aParser.String(Odp::kKeySid));
    iSubscription->SetSid(sid);
    return true;
}


// CpiOdpUnsubscriber

CpiOdpUnsubscriber::CpiOdpUnsubscriber(ICpiOdpDevice& aDevice)
    : iDevice(aDevice)
    , iSem("OdpU", 0)
{
}

void CpiOdpUnsubscriber::Unsubscribe(const Brx& aSid)
{
    auto& writer = iDevice.WriteLock(*this);
    AutoOdpDevice _(iDevice);
    WriterJsonObject writerUnsubs(writer);
    writerUnsubs.WriteString(Odp::kKeyType, Odp::kTypeUnsubscribe);
    writerUnsubs.WriteString(Odp::kKeySid, aSid);
    writerUnsubs.WriteEnd();
    iDevice.WriteEnd(writer);

    iSem.Wait();
}

TBool CpiOdpUnsubscriber::HandleOdpResponse(const JsonParser& aParser)
{
    if (aParser.String(Odp::kKeyType) != Odp::kTypeUnsubscribeResponse) {
        return false;
    }
    iSem.Signal();
    return true;
}


// AutoOdpDevice

AutoOdpDevice::AutoOdpDevice(ICpiOdpDevice& aDevice)
    : iDevice(aDevice)
{
}

AutoOdpDevice::~AutoOdpDevice()
{
    iDevice.WriteUnlock();
}
