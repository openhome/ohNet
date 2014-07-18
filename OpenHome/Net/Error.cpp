#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Ascii.h>

using namespace OpenHome;
using namespace OpenHome::Net;

const Brn Error::kDescriptionUnknown("Unknown");
const Brn Error::kDescriptionSocketTimeout("Connection timed out");
const Brn Error::kDescriptionParameterInvalid("Invalid output parameter");
const Brn Error::kDescriptionAsyncInterrupted("Operation interrupted");
const Brn Error::kDescriptionAsyncShutdown("Manager shutdown");

Error::Error()
{
    Clear();
}

void Error::Clear()
{
    iLevel = Error::eNone;
    iCode = kCodeNoError;
    Brhz tmp;
    iDescription.TransferTo(tmp);
}

void Error::Set(ELevel aLevel, TUint aCode, const Brx& aDescription)
{
    iLevel = aLevel;
    iCode = aCode;
    iDescription.Set(aDescription);
}

void Error::Output(IAsyncOutput& aConsole)
{
    aConsole.Output("ErrorLevel", LevelName());
    Bws<Ascii::kMaxUintStringBytes+1> buf;
    (void)Ascii::AppendDec(buf, iCode);
    buf.PtrZ();
    aConsole.Output("ErrorCode", (const TChar*)buf.Ptr());
    aConsole.Output("ErrorDescription", Description());
}    

const TChar* Error::LevelName() const
{
    return LevelName(iLevel);
}

const TChar* Error::LevelName(ELevel aLevel)
{ // static
    switch (aLevel)
    {
    case eSocket:
        return "Socket";
    case eHttp:
        return "HTTP";
    case eUpnp:
        return "UPnP";
    case eService:
        return "Service";
    case eAsync:
        return "Async";
    case eNone:
    default:
        return "None";
    }
}
