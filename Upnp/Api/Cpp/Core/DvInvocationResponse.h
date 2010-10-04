#ifndef HEADER_DV_INVOCATION_RESPONSE
#define HEADER_DV_INVOCATION_RESPONSE

#include <ZappTypes.h>
#include <Buffer.h>

namespace Zapp {

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

class IInvocationResponseBinary
{
public:
    virtual void Write(TByte aValue) = 0;
    virtual void Write(const Brx& aBuffer) = 0;
    virtual void WriteFlush() = 0;
	virtual ~IInvocationResponseBinary() {}
};

class IInvocationResponseString
{
public:
    virtual void Write(TByte aValue) = 0;
    virtual void Write(const Brx& aBuffer) = 0;
    virtual void WriteFlush() = 0;
	virtual ~IInvocationResponseString() {}
};

} // namespace Zapp

#endif // HEADER_DV_INVOCATION_RESPONSE
