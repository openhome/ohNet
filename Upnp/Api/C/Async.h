#ifndef HEADER_ASYNC_C
#define HEADER_ASYNC_C

#include <OsTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef THandle ZappHandleAsync;

/**
 * Callback which runs when an asynchronous operation completes
 *
 * @param[in] aPtr   Client-specified data
 * @param[in] aAsync Handle to the operation
 */
typedef void (*ZappCallbackAsync)(void* aPtr, ZappHandleAsync aAsync);

/**
 * Callback which runs inside ZappAsyncOutput to output the state of an async object
 */
typedef void (*ZappCallbackAsyncOutput)(const char* aKey, const char* aValue);

/**
 * Output the state of an async object
 *
 * @param[in] aAsync   Handle (probably returned to ZappCallbackAsync)
 * @param[in] aOutput  Callback to run for each key/value pair of aAsync's state
 */
void ZappAsyncOutput(ZappHandleAsync aAsync, ZappCallbackAsyncOutput aOutput);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_ASYNC_C
