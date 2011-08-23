#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviService.h>

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
