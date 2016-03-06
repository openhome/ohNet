#ifndef HEADER_DVINVOCATION_C
#define HEADER_DVINVOCATION_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read the version of the action being invoked.
 *
 * @param[in] aPtr  aInvocationPtr passed to the action
 *
 * @return  The version of the action being invoked.
 */
typedef uint32_t (STDCALL *DvInvocationVersion)(void* aPtr);

/**
 * Read the network adapter an action has been invoked on.
 *
 * @param[in] aPtr  aInvocationPtr passed to the action
 *
 * @return  The network adapter an action has been invoked on.
 */
typedef TIpAddress (STDCALL *DvInvocationAdapter)(void* aPtr);

/**
 * Read the prefix for all resource uris for the adapter/protocol an action has been invoked using.
 *
 * @param[in] aPtr  aInvocationPtr passed to the action
 *
 * @return  The prefix to resource uris.
 */
typedef const char* (STDCALL *DvInvocationResourceUriPrefix)(void* aPtr);

/**
 * Read the address of the client socket which has invoked this action.
 *
 * @param[in]  aPtr  aInvocationPtr passed to the action
 * @param[out] aClientAddress  IPv4 address of client; 0 if this cannot be determined.
 * @param[out] aClientPort     Port [1..65535] of client; 0 if this cannot be determined.
 *
 * @return  The prefix to resource uris.
 */
typedef void (STDCALL *DvInvocationClientEndpoint)(void* aPtr, TIpAddress* aClientAddress, uint32_t* aClientPort);

/**
 * Read the user agent of the client which has invoked this action.
 *
 * @param[in]  aPtr  aInvocationPtr passed to the action
 * @param[out] aUserAgent  User agent of client
 * @param[out] aLen  Length (in bytes) of aUserAgent.
 */
typedef void (STDCALL *DvInvocationClientUserAgent)(void* aPtr, const char** aUserAgent, uint32_t* aLen);

/**
 * Table of function pointers passed to invoked actions.
 */
typedef struct IDvInvocationC
{
    DvInvocationVersion iVersion;
    DvInvocationAdapter iAdapter;
    DvInvocationResourceUriPrefix iResourceUriPrefix;
    DvInvocationClientEndpoint iClientEndpoint;
    DvInvocationClientUserAgent iClientUserAgent;
}
IDvInvocationC;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVINVOCATION_C
