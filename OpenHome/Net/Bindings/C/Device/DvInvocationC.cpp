#include <OpenHome/Net/C/DvInvocationPrivate.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/Private/DviService.h>

using namespace OpenHome;
using namespace OpenHome::Net;

DvInvocationCPrivate::DvInvocationCPrivate(IDviInvocation& aInvocation)
    : iInvocation(aInvocation)
{
    iFnTable.iVersion = &Version;
    iFnTable.iAdapter = &Adapter;
    iFnTable.iResourceUriPrefix = &ResourceUriPrefix;
}

void DvInvocationCPrivate::GetInvocationC(IDvInvocationC** aInvocation, void** aPtr)
{
    *aInvocation = &iFnTable;
    *aPtr = this;
}

IDviInvocation& DvInvocationCPrivate::Invocation(void* aPtr)
{
    DvInvocationCPrivate* self = reinterpret_cast<DvInvocationCPrivate*>(aPtr);
    ASSERT(self != NULL);
    return self->iInvocation;
}

uint32_t DvInvocationCPrivate::Version(void* aPtr)
{
    return DvInvocationCPrivate::Invocation(aPtr).Version();
}

TIpAddress DvInvocationCPrivate::Adapter(void* aPtr)
{
    return DvInvocationCPrivate::Invocation(aPtr).Adapter();
}

const char* DvInvocationCPrivate::ResourceUriPrefix(void* aPtr)
{
    return DvInvocationCPrivate::Invocation(aPtr).ResourceUriPrefix();
}

void DvInvocationCPrivate::ClientEndpoint(void* aPtr, TIpAddress* aClientAddress, uint32_t* aClientPort)
{
    Endpoint ep = DvInvocationCPrivate::Invocation(aPtr).ClientEndpoint();
    *aClientAddress = ep.Address();
    *aClientPort = ep.Port();
}

void DvInvocationCPrivate::ClientUserAgent(void* aPtr, const char** aUserAgent, uint32_t* aLen)
{
    const Brx& userAgent = DvInvocationCPrivate::Invocation(aPtr).ClientUserAgent();
    *aUserAgent = (const char*)userAgent.Ptr();
    if (*aUserAgent == NULL) {
        *aLen = 0;
    }
    else {
        *aLen = (uint32_t)userAgent.Bytes();
    }
}
