#ifndef HEADER_DVINVOCATION_PRIVATE_C
#define HEADER_DVINVOCATION_PRIVATE_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Net/C/DvInvocation.h>

namespace OpenHome {
namespace Net {

class IDviInvocation;
class DllExportClass DvInvocationCPrivate : private INonCopyable
{
public:
    DllExport DvInvocationCPrivate(IDviInvocation& aInvocation);
    DllExport void GetInvocationC(IDvInvocationC** aInvocation, void** aPtr);
private:
    static IDviInvocation& Invocation(void* aPtr);
    static uint32_t STDCALL Version(void* aPtr);
    static TIpAddress STDCALL Adapter(void* aPtr);
    static const char* STDCALL ResourceUriPrefix(void* aPtr);
    static void STDCALL ClientEndpoint(void* aPtr, TIpAddress* aClientAddress, uint32_t* aClientPort);
    static void STDCALL ClientUserAgent(void* aPtr, const char** aUserAgent, uint32_t* aLen);
private:
    IDviInvocation& iInvocation;
    IDvInvocationC iFnTable;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVINVOCATION_PRIVATE_C
