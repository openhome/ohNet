#ifndef HEADER_SUBSCRIPTION
#define HEADER_SUBSCRIPTION

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Http.h>

namespace OpenHome {
namespace Net {

class HeaderSid : public HttpHeader
{
public:
    static const Brn kHeaderSid;
    static const Brn kFieldSidPrefix;
public:
    Brh& Sid();
    const Brx& Value() const;
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    Brh iSid;
};

class HeaderTimeout : public HttpHeader
{
public:
    static const Brn kHeaderTimeout;
    static const Brn kFieldTimeoutPrefix;
public:
    TUint Timeout();
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    TUint iTimeout;
};

class HeaderNt : public HttpHeader
{
public:
    const Brx& Value() const;
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    Brh iValue;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_SUBSCRIPTION
