#include <Error.h>
#include <Buffer.h>
#include <ZappTypes.h>
#include <Standard.h>
#include <Ascii.h>

using namespace Zapp;

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
    switch (iLevel)
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
        ASSERTS();
        return NULL;
    }
}
