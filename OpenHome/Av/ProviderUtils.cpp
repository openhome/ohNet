#include <OpenHome/Av/ProviderUtils.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Net;

// WriterInvocationResponseString

WriterInvocationResponseString::WriterInvocationResponseString(IDvInvocationResponseString& aIrs)
    : iIrs(aIrs)
{
}

WriterInvocationResponseString::~WriterInvocationResponseString()
{
}

void WriterInvocationResponseString::Write(TByte aValue)
{
    Brn buf(&aValue, sizeof(TByte));
    Write(buf);
}

void WriterInvocationResponseString::Write(const Brx& aBuffer)
{
    iIrs.Write(aBuffer);
}

void WriterInvocationResponseString::WriteFlush()
{
    iIrs.WriteFlush();
}
