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

class IInvocationResponse
{
public:
	virtual void Error(TInt aCode, const Brx& aReason) = 0;
	virtual void Start() = 0;
	virtual void End() = 0;
    virtual ~IInvocationResponse() {}
};

class IInvocationResponseBool
{
public:
	virtual void Write(TBool aValue) = 0;
    virtual ~IInvocationResponseBool() {}
};

class IInvocationResponseUint
{
public:
	virtual void Write(TUint aValue) = 0;
    virtual ~IInvocationResponseUint() {}
};

class IInvocationResponseInt
{
public:
	virtual void Write(TInt aValue) = 0;
    virtual ~IInvocationResponseInt() {}
};

class IInvocationResponseBinary : public IWriter
{
public:
    virtual void Write(TByte aValue) = 0;
    virtual void Write(const Brx& aBuffer) = 0;
    virtual void WriteFlush() = 0;
	virtual ~IInvocationResponseBinary() {}
};

class IInvocationResponseString : public IWriter
{
public:
    virtual void Write(TByte aValue) = 0;
    virtual void Write(const Brx& aBuffer) = 0;
    virtual void WriteFlush() = 0;
	virtual ~IInvocationResponseString() {}
};

/* @} */

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DV_INVOCATION_RESPONSE
