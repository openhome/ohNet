#ifndef HEADER_SUBSCRIPTION
#define HEADER_SUBSCRIPTION

#include <ZappTypes.h>
#include <Buffer.h>
#include <Http.h>

namespace Zapp {

class HeaderSid : public HttpHeader
{
public:
    static const Brn kHeaderSid;
    static const Brn kFieldSidPrefix;
public:
    Brh& Sid();
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

} // namespace Zapp

#endif // HEADER_SUBSCRIPTION
