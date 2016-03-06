#ifndef HEADER_DVPROVIDER_C
#define HEADER_DVPROVIDER_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/Service.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvInvocation
 * @ingroup Device
 * @{
 */
/**
 * Opaque handle to an (action) invocation
 */
typedef THandle DvInvocationC;
/* @} */
/**
 * @addtogroup DvProvider
 * @ingroup Device
 * @{
 */

/**
 * Opaque handle to a provider
 */
typedef THandle DvProviderC;
    
/**
 * Callback which runs when an action is invoked
 */
typedef void (STDCALL *OhNetCallbackDvInvocation)(void* aPtr, DvInvocationC aInvocation);

/**
 * Create a provider (of a service)
 *
 * @param[in] aDevice   Device the service is being offered by
 * @param[in] aDomain   Vendor domain of the service being provided
 * @param[in] aType     Name of the service being provided
 * @param[in] aVersion  Version of the service being provided
 */
DllExport DvProviderC STDCALL DvProviderCreate(DvDeviceC aDevice, const char* aDomain, const char* aType, uint32_t aVersion);

/**
 * Destroy a provider
 *
 * @param[in] aProvider   Handle to a provider
 */
DllExport void STDCALL DvProviderDestroy(DvProviderC aProvider);

/**
 * Add an action to the provider
 *
 * @param[in] aProvider  Handle to a provider
 * @param[in] aAction    Returned by ServiceActionCreate.  Ownership passes to aProvider
 * @param[in] aCallback  Callback to run when the action is invoked
 * @param[in] aPtr       Pointer to pass to the above callback
 */
DllExport void STDCALL DvProviderAddAction(DvProviderC aProvider, ServiceAction aAction, OhNetCallbackDvInvocation aCallback, void* aPtr);

/**
 * Lock the provider's properties, blocking publication of updates.
 *
 * This is not necessary when updating a single property but is used by providers that have
 * >1 properties whose values are related.  Without locking, updates to some properties may
 * be published, leaving related properties in their old (now incompatible) states.
 *
 * Every call to this must be followed by (exactly) one call to DvProviderPropertiesUnlock().
 *
 * @param[in] aProvider   Handle to a provider
 */
DllExport void STDCALL DvProviderPropertiesLock(DvProviderC aProvider);

/**
 * Unlock the provider's properties, allowing publication of updates.
 *
 * Any pending updates will automatically be scheduled.
 * This must only be called following a call to DvProviderPropertiesLock().
 *
 * @param[in] aProvider   Handle to a provider
 */
DllExport void STDCALL DvProviderPropertiesUnlock(DvProviderC aProvider);

/**
 * Add a property (passing ownership) to a provider
 *
 * @param[in] aProvider   Handle to a provider
 * @param[in] aProperty   Returned by ServicePropertyCreate[type]Dv.  Ownership passes to aProvider.
 */
DllExport void STDCALL DvProviderAddProperty(DvProviderC aProvider, ServiceProperty aProperty);

/**
 * Utility function which updates the value of a PropertyInt.
 *
 * If the property value has changed and the properties are not locked (DvProviderPropertiesLock()
 * called more recently than DvProviderPropertiesUnlock()), publication of an update is scheduled.
 *
 * Throws ParameterValidationError if the property has a range of allowed values and
 * the new value is not in this range
 *
 * @param[in]  aProvider   Handle to a provider
 * @param[in]  aProperty   Returned by ServicePropertyCreateIntDv
 * @param[in]  aValue      New value for the property
 * @param[out] aChanged    1 if the property's value has changed (aValue was different to
 *                         the previous value); 0 otherwise
 *
 * @return  0 if the set succeeded; none-zero otherwise
 */
DllExport int32_t STDCALL DvProviderSetPropertyInt(DvProviderC aProvider, ServiceProperty aProperty, int32_t aValue, uint32_t* aChanged);

/**
 * Utility function which updates the value of a PropertyUint. (Not intended for external use)
 *
 * If the property value has changed and the properties are not locked (DvProviderPropertiesLock()
 * called more recently than DvProviderPropertiesUnlock()), publication of an update is scheduled.
 *
 * Throws ParameterValidationError if the property has a range of allowed values and
 * the new value is not in this range
 *
 * @param[in]  aProvider   Handle to a provider
 * @param[in]  aProperty   Returned by ServicePropertyCreateUintDv
 * @param[in]  aValue      New value for the property
 * @param[out] aChanged    1 if the property's value has changed (aValue was different to
 *                         the previous value); 0 otherwise
 *
 * @return  0 if the set succeeded; none-zero otherwise
 */
DllExport int32_t STDCALL DvProviderSetPropertyUint(DvProviderC aProvider, ServiceProperty aProperty, uint32_t aValue, uint32_t* aChanged);

/**
 * Utility function which updates the value of a PropertyBool. (Not intended for external use)
 *
 * If the property value has changed and the properties are not locked (DvProviderPropertiesLock()
 * called more recently than DvProviderPropertiesUnlock()), publication of an update is scheduled.
 *
 * Throws ParameterValidationError if the property has a range of allowed values and
 * the new value is not in this range
 *
 * @param[in]  aProvider   Handle to a provider
 * @param[in]  aProperty   Returned by ServicePropertyCreateBoolDv
 * @param[in]  aValue      New value for the property
 * @param[out] aChanged    1 if the property's value has changed (aValue was different to
 *                         the previous value); 0 otherwise
 *
 * @return  0 if the set succeeded; none-zero otherwise
 */
DllExport int32_t STDCALL DvProviderSetPropertyBool(DvProviderC aProvider, ServiceProperty aProperty, uint32_t aValue, uint32_t* aChanged);

/**
 * Utility function which updates the value of a PropertyString. (Not intended for external use)
 *
 * If the property value has changed and the properties are not locked (DvProviderPropertiesLock()
 * called more recently than DvProviderPropertiesUnlock()), publication of an update is scheduled.
 *
 * Throws ParameterValidationError if the property has a range of allowed values and
 * the new value is not in this range
 *
 * @param[in]  aProvider   Handle to a provider
 * @param[in]  aProperty   Returned by ServicePropertyCreateStringDv
 * @param[in]  aValue      New value for the property
 * @param[out] aChanged    1 if the property's value has changed (aValue was different to
 *                         the previous value); 0 otherwise
 *
 * @return  0 if the set succeeded; none-zero otherwise
 */
DllExport int32_t STDCALL DvProviderSetPropertyString(DvProviderC aProvider, ServiceProperty aProperty, const char* aValue, uint32_t* aChanged);

/**
 * Utility function which updates the value of a PropertyBinary. (Not intended for external use)
 *
 * If the property value has changed and the properties are not locked (DvProviderPropertiesLock()
 * called more recently than DvProviderPropertiesUnlock()), publication of an update is scheduled.
 *
 * Throws ParameterValidationError if the property has a range of allowed values and
 * the new value is not in this range
 *
 * @param[in]  aProvider   Handle to a provider
 * @param[in]  aProperty   Returned by ServicePropertyCreateBinaryDv
 * @param[in]  aData       New data for the property
 * @param[in]  aLen        Length of the new data
 * @param[out] aChanged    1 if the property's value has changed (aValue was different to
 *                         the previous value); 0 otherwise
 *
 * @return  0 if the set succeeded; none-zero otherwise
 */
DllExport int32_t STDCALL DvProviderSetPropertyBinary(DvProviderC aProvider, ServiceProperty aProperty, const uint8_t* aData, uint32_t aLen, uint32_t* aChanged);

/* @} */
/**
 * @addtogroup DvInvocation
 * @ingroup Device
 * @{
 */

/**
 * Get the version number of the service requested by the caller.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation.
 * @param[out] aVersion     The version number of the service the caller expects.
 */
DllExport void STDCALL DvInvocationGetVersion(DvInvocationC aInvocation, uint32_t* aVersion);

/**
 * Get the network adapter an action was invoked using.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation.
 * @param[out] aAdapter     The network adapter used to invoke this action.
 */
DllExport void STDCALL DvInvocationGetAdapter(DvInvocationC aInvocation, TIpAddress* aAdapter);

/**
 * Get the prefix to use on any uris to resources offered by the provider.
 *
 * (This will change depending on which network adapter was used to invoke an action.)
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation.
 * @param[out] aPrefix      The prefix to resource uris.
 * @param[out] aLen         Length (in bytes) of aPrefix.
 */
DllExport void STDCALL DvInvocationGetResourceUriPrefix(DvInvocationC aInvocation, const char** aPrefix, uint32_t* aLen);

/**
 * Get client socket's address.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation.
 * @param[out] aAddress     IPv4 address in network byte order.
 * @param[out] aLen         Port [1..65535].
 */
DllExport void STDCALL DvInvocationGetClientEndpoint(DvInvocationC aInvocation, TIpAddress* aAddress, uint32_t* aPort);

/**
 * Get the client's user agent.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation.
 * @param[out] aUserAgent   User agent of client.
 * @param[out] aLen         Length (in bytes) of aUserAgent.
 */
DllExport void STDCALL DvInvocationGetClientUserAgent(DvInvocationC aInvocation, const char** aUserAgent, uint32_t* aLen);

/**
 * Begin reading (input arguments for) an invocation
 *
 * Must be called before the values of any input arguments are read.
 * Must be called for invocations with no input arguments.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationReadStart(DvInvocationC aInvocation);

/**
 * Read the value of an integer input argument for an invocation
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aName        Name of the parameter associated with this input argument
 * @param[out] aValue       Value of the input argument
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationReadInt(DvInvocationC aInvocation, const char* aName, int32_t* aValue);

/**
 * Read the value of an unsigned integer input argument for an invocation
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aName        Name of the parameter associated with this input argument
 * @param[out] aValue       Value of the input argument
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationReadUint(DvInvocationC aInvocation, const char* aName, uint32_t* aValue);

/**
 * Read the value of a boolean input argument for an invocation
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aName        Name of the parameter associated with this input argument
 * @param[out] aValue       Value of the input argument.  0 for false; non-zero for true
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationReadBool(DvInvocationC aInvocation, const char* aName, uint32_t* aValue);

/**
 * Read the value of a string input argument for an invocation
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aName        Name of the parameter associated with this input argument
 * @param[out] aValue       Value of the input argument.  Ownership passes to caller.  Use OhNetFree() to destroy.
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationReadString(DvInvocationC aInvocation, const char* aName, char** aValue);

/**
 * Read the value of a string input argument for an invocation
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aName        Name of the parameter associated with this input argument
 * @param[out] aValue       Value of the input argument.  Ownership passes to caller.  Use OhNetFree() to destroy.
 * @param[out] aLen         Length (in bytes) of aData
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationReadStringAsBuffer(DvInvocationC aInvocation, const char* aName, char** aValue, uint32_t* aLen);

/**
 * Read the value of an integer input argument for an invocation
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aName        Name of the parameter associated with this input argument
 * @param[out] aData        Value of the input argument.  Ownership passes to caller.  Use OhNetFree() to destroy.
 * @param[out] aLen         Length (in bytes) of aData
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationReadBinary(DvInvocationC aInvocation, const char* aName, uint8_t** aData, uint32_t* aLen);

/**
 * Complete reading (input arguments for) an invocation
 *
 * Must be called after the values of all input arguments are read.
 * Must be called for invocations with no input arguments.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationReadEnd(DvInvocationC aInvocation);

/**
 * Report an error reading or writing an invocation
 *
 * Must be called if DvInvocationReadEnd() isn't reached.
 * May be called if DvInvocationWriteStart() or later have been called.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aCode        Error code
 * @param[in]  aDescription Error description
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationReportError(DvInvocationC aInvocation, uint32_t aCode, const char* aDescription);

/**
 * Begin reading (output arguments for) an invocation
 *
 * Must be called before the values of any output arguments are written.
 * Must be called for invocations with no output arguments.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationWriteStart(DvInvocationC aInvocation);

/**
 * Set the value of an integer output argument for an invocation.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aName        Name of the parameter associated with this output argument
 * @param[out] aValue       Value of the output argument
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationWriteInt(DvInvocationC aInvocation, const char* aName, int32_t aValue);

/**
 * Set the value of an unsigned integer output argument for an invocation.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aName        Name of the parameter associated with this output argument
 * @param[out] aValue       Value of the output argument
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationWriteUint(DvInvocationC aInvocation, const char* aName, uint32_t aValue);

/**
 * Set the value of a boolean output argument for an invocation.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aName        Name of the parameter associated with this output argument
 * @param[out] aValue       Value of the output argument.  0 for false; non-zero for true
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationWriteBool(DvInvocationC aInvocation, const char* aName, uint32_t aValue);

/**
 * Prepare to write a string output argument for an invocation.
 *
 * The string content will be set by one or more calls to DvInvocationWriteString.
 * This allows for the possibility of large arguments being streamed rather than
 * requiring the memory to buffer them locally.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aName        Name of the parameter associated with this output argument
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationWriteStringStart(DvInvocationC aInvocation, const char* aName);

/**
 * Write a chunk of content for a string output argument.
 *
 * DvInvocationWriteStringStart must be called first.  This function can be called one or more times.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aValue       String (or string fragment) to be output
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationWriteString(DvInvocationC aInvocation, const char* aValue);

/**
 * Write a chunk of content for a string output argument.
 *
 * DvInvocationWriteStringStart must be called first.  This function can be called one or more times.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aValue       String (or string fragment) to be output
 * @param[in]  aLen         Length (in bytes) of aValue
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationWriteStringAsBuffer(DvInvocationC aInvocation, const char* aValue, uint32_t aLen);

/**
 * Complete writing of a string output argument for an invocation.
 *
 * Must be called once for every call to DvInvocationWriteStringStart (and any subsequent
 * calls to DvInvocationWriteString).
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aName        Name of the parameter associated with this output argument
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationWriteStringEnd(DvInvocationC aInvocation, const char* aName);

/**
 * Prepare to write a binary output argument for an invocation.
 *
 * The string content will be set by one or more calls to DvInvocationWriteString.
 * This allows for the possibility of large arguments being streamed rather than
 * requiring the memory to buffer them locally.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aName        Name of the parameter associated with this output argument
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationWriteBinaryStart(DvInvocationC aInvocation, const char* aName);

/**
 * Write a chunk of content for a binary output argument.
 *
 * DvInvocationWriteStringStart must be called first.  This function can be called one or more times.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aData        Data (or data fragment) to be output
 * @param[in]  aLen         Length (in bytes) of aData
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationWriteBinary(DvInvocationC aInvocation, const uint8_t* aData, uint32_t aLen);

/**
 * Complete writing of a binary output argument for an invocation.
 *
 * Must be called once for every call to DvInvocationWriteStringStart (and any subsequent
 * calls to DvInvocationWriteString).
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 * @param[in]  aName        Name of the parameter associated with this output argument
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationWriteBinaryEnd(DvInvocationC aInvocation, const char* aName);

/**
 * Complete writing (output arguments for) an invocation
 *
 * Must be called after the values of all output arguments are written.
 * Must be called for invocations with no output arguments.
 *
 * @param[in]  aInvocation  Invocation handle.  Passed to OhNetCallbackDvInvocation
 *
 * @return  0 on success; non-zero on error
 */
DllExport int32_t STDCALL DvInvocationWriteEnd(DvInvocationC aInvocation);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVPROVIDER_C
