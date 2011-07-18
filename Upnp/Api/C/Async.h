#ifndef HEADER_ASYNC_C
#define HEADER_ASYNC_C

#include <OhNetDefines.h>
#include <OsTypes.h>

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
typedef void (*OhNetCallbackAsync)(void* aPtr, OhNetHandleAsync aAsync);

/**
 * Callback which runs inside OhNetAsyncOutput to output the state of an async object
 * @ingroup Callbacks
 */
typedef void (*OhNetCallbackAsyncOutput)(const char* aKey, const char* aValue);

/**
 * Output the state of an async object
 * @ingroup Callbacks
 *
 * @param[in] aAsync   Handle (probably returned to OhNetCallbackAsync)
 * @param[in] aOutput  Callback to run for each key/value pair of aAsync's state
 */
void OhNetAsyncOutput(OhNetHandleAsync aAsync, OhNetCallbackAsyncOutput aOutput);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_ASYNC_C
