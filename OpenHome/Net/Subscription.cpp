#include <OpenHome/Net/Private/Subscription.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Http.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// HeaderSid

const Brn HeaderSid::kHeaderSid("SID");
const Brn HeaderSid::kFieldSidPrefix("uuid:");

Brh& HeaderSid::Sid()
{
    if (!Received()) {
        Brh tmp;
        iSid.TransferTo(tmp);
    }
    return iSid;
}

const Brx& HeaderSid::Value() const
{
    return iSid;
}

TBool HeaderSid::Recognise(const Brx& aHeader)
{
    return (Ascii::CaseInsensitiveEquals(aHeader, kHeaderSid));
}

void HeaderSid::Process(const Brx& aValue)
{
    SetReceived();
    const TUint prefixBytes = kFieldSidPrefix.Bytes();
    if (aValue.Bytes() <= prefixBytes) {
        THROW(HttpError);
    }
    Brn prefix = aValue.Split(0, prefixBytes);
    if (prefix != kFieldSidPrefix) {
        THROW(HttpError);
    }
    Brn value = aValue.Split(prefixBytes, aValue.Bytes() - prefixBytes);
    iSid.Set(value);
}


// HeaderTimeout

const Brn HeaderTimeout::kHeaderTimeout("TIMEOUT");
const Brn HeaderTimeout::kFieldTimeoutPrefix("Second-");

TUint HeaderTimeout::Timeout()
{
    return (Received()? iTimeout : 0);
}

TBool HeaderTimeout::Recognise(const Brx& aHeader)
{
    return (Ascii::CaseInsensitiveEquals(aHeader, kHeaderTimeout));
}

void HeaderTimeout::Process(const Brx& aValue)
{
    iTimeout = 0;
    SetReceived();
    const TUint prefixBytes = kFieldTimeoutPrefix.Bytes();
    if (aValue.Bytes() <= prefixBytes) {
        THROW(HttpError);
    }
    Brn prefix = aValue.Split(0, prefixBytes);
    if (prefix != kFieldTimeoutPrefix) {
        THROW(HttpError);
    }
    Brn value = aValue.Split(prefixBytes, aValue.Bytes() - prefixBytes);
    try {
        iTimeout = Ascii::Uint(value);
    }
    catch (AsciiError&) {
        THROW(HttpError);
    }
}


// HeaderNt

const Brx& HeaderNt::Value() const
{
    return iValue;
}

TBool HeaderNt::Recognise(const Brx& aHeader)
{
    const Brn kHeaderNt("Nt");
    return (Ascii::CaseInsensitiveEquals(aHeader, kHeaderNt));
}

void HeaderNt::Process(const Brx& aValue)
{
    SetReceived();
    iValue.Set(aValue);
}
