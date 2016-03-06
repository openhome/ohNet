#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Private/Network.h>

using namespace OpenHome;
using namespace OpenHome::Net;

DvInvocationStd::DvInvocationStd(IDviInvocation& aInvocation)
    : iInvocation(aInvocation)
{
}

uint32_t DvInvocationStd::Version() const
{
    return iInvocation.Version();
}

TIpAddress DvInvocationStd::Adapter() const
{
    return iInvocation.Adapter();
}

const char* DvInvocationStd::ResourceUriPrefix() const
{
    return iInvocation.ResourceUriPrefix();
}

void DvInvocationStd::GetClientEndpoint(TIpAddress& aClientAddress, uint32_t& aClientPort) const
{
    Endpoint ep = iInvocation.ClientEndpoint();
    aClientAddress = ep.Address();
    aClientPort = ep.Port();
}

std::string DvInvocationStd::ClientUserAgent() const
{
    return std::string((const char*)iInvocation.ClientUserAgent().Ptr(), iInvocation.ClientUserAgent().Bytes());
}

void DvInvocationStd::ReportError(uint32_t aCode, const std::string& aDescription)
{
    Brn desc((const TByte*)aDescription.c_str(), (TUint)aDescription.length());
    iInvocation.InvocationReportError((TUint)aCode, desc);
}
