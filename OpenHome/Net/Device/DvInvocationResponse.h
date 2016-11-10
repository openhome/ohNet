#ifndef HEADER_DV_INVOCATION_RESPONSE
#define HEADER_DV_INVOCATION_RESPONSE

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>

namespace OpenHome {
namespace Net {

/**
 * @addtogroup Device
 * @{
 */

class IDvInvocation
{
public:
    virtual TUint Version() const = 0;
    virtual void Error(TInt aCode, const Brx& aReason) = 0;
    virtual void StartResponse() = 0;
    virtual void EndResponse() = 0;
    virtual TIpAddress Adapter() const = 0;
    virtual const char* ResourceUriPrefix() const = 0;
    virtual const Brx& ClientUserAgent() const = 0;
    virtual ~IDvInvocation() {}
};

class IDvInvocationResponseBool
{
public:
    virtual void Write(TBool aValue) = 0;
    virtual ~IDvInvocationResponseBool() {}
};

class IDvInvocationResponseUint
{
public:
    virtual void Write(TUint aValue) = 0;
    virtual ~IDvInvocationResponseUint() {}
};

class IDvInvocationResponseInt
{
public:
    virtual void Write(TInt aValue) = 0;
    virtual ~IDvInvocationResponseInt() {}
};

class IDvInvocationResponseBinary : public IWriter
{
public:
    virtual void Write(TByte aValue) = 0;
    virtual void Write(const Brx& aBuffer) = 0;
    virtual void WriteFlush() = 0;
    virtual ~IDvInvocationResponseBinary() {}
};

class IDvInvocationResponseString : public IWriter
{
public:
    virtual void Write(TByte aValue) = 0;
    virtual void Write(const Brx& aBuffer) = 0;
    virtual void WriteFlush() = 0;
    virtual ~IDvInvocationResponseString() {}
};

/* @} */

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DV_INVOCATION_RESPONSE
