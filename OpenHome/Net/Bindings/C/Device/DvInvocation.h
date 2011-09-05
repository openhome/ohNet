#ifndef HEADER_DVINVOCATION_C
#define HEADER_DVINVOCATION_C

#include <OpenHome/OhNetDefines.h>
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
 * Table of function pointers passed to invoked actions.
 */
typedef struct IDvInvocationC
{
    DvInvocationVersion iVersion;
    DvInvocationAdapter iAdapter;
    DvInvocationResourceUriPrefix iResourceUriPrefix;
}
IDvInvocationC;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVINVOCATION_C
