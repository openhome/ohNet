#ifndef HEADER_ASYNC_C
#define HEADER_ASYNC_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef THandle OhNetHandleAsync;

/**
 * Callback which runs when an asynchronous operation completes
 * @ingroup Callbacks
 *
 * @param[in] aPtr   Client-specified data
 * @param[in] aAsync Handle to the operation
 */
typedef void (STDCALL *OhNetCallbackAsync)(void* aPtr, OhNetHandleAsync aAsync);

/**
 * Callback which runs inside OhNetAsyncOutput to output the state of an async object
 * @ingroup Callbacks
 */
typedef void (STDCALL *OhNetCallbackAsyncOutput)(const char* aKey, const char* aValue);

/**
 * Output the state of an async object
 * @ingroup Callbacks
 *
 * @param[in] aAsync   Handle (probably returned to OhNetCallbackAsync)
 * @param[in] aOutput  Callback to run for each key/value pair of aAsync's state
 */
DllExport void STDCALL OhNetAsyncOutput(OhNetHandleAsync aAsync, OhNetCallbackAsyncOutput aOutput);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_ASYNC_C
