#ifndef HEADER_DV_INVOCATION_RESPONSE
#define HEADER_DV_INVOCATION_RESPONSE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>

namespace OpenHome {
namespace Net {

/**
 * @addtogroup Device
 * @{
 */

class IDvInvocationResponse
{
public:
	virtual void Error(TInt aCode, const Brx& aReason) = 0;
	virtual void Start() = 0;
	virtual void End() = 0;
    virtual ~IDvInvocationResponse() {}
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
