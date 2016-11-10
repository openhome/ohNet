#ifndef HEADER_DVINVOCATION_STD
#define HEADER_DVINVOCATION_STD

#include <OpenHome/OsTypes.h>

#include <stdint.h>
#include <string>

namespace OpenHome {
namespace Net {

class IDvInvocationStd
{
public:
    virtual uint32_t Version() const = 0;
    virtual TIpAddress Adapter() const = 0;
    virtual const char* ResourceUriPrefix() const = 0;
    virtual void GetClientEndpoint(TIpAddress& aClientAddress, uint32_t& aClientPort) const = 0;
    virtual std::string ClientUserAgent() const = 0;
    virtual void ReportError(uint32_t aCode, const std::string& aDescription) = 0; // throws
    virtual ~IDvInvocationStd() {}
};

class IDviInvocation;
class DvInvocationStd : public IDvInvocationStd
{
public:
    DvInvocationStd(IDviInvocation& aInvocation);
private:
    uint32_t Version() const;
    TIpAddress Adapter() const;
    const char* ResourceUriPrefix() const;
    void GetClientEndpoint(TIpAddress& aClientAddress, uint32_t& aClientPort) const;
    std::string ClientUserAgent() const;
    void ReportError(uint32_t aCode, const std::string& aDescription);
private:
    DvInvocationStd(const DvInvocationStd &);
    void operator=(const DvInvocationStd &);
private:
    IDviInvocation& iInvocation;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVINVOCATION_STD
