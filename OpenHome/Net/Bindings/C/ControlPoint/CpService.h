#ifndef HEADER_CPSERVICEC
#define HEADER_CPSERVICEC

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/CpDevice.h>
#include <OpenHome/Net/C/Service.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CpService
 * @ingroup ControlPoint
 * @{
 */

/**
 * Opaque handle to a service
 */
typedef THandle CpService;
/**
 * Opaque handle to an invocation
 */
typedef THandle CpInvocationC;

/**
 * Create a service for use by a client of the control point stack
 *
 * @param[in] aDomain   Domain for the vendor who defined the service
 * @param[in] aName     Name of the service
 * @param[in] aVersion  Version number of the service
 * @param[in] aDevice   Device which advertised the service
 *
 * @return  Handle to the service
 */
DllExport CpService STDCALL CpServiceCreate(const char* aDomain, const char* aName, uint32_t aVersion, CpDeviceC aDevice);

/**
 * Destroy a service
 *
 * @param[in] aService  Returned by CpServiceCreate
 */
DllExport void STDCALL CpServiceDestroy(CpService aService);

/**
 * Begin invocation of an action on a service
 *
 * Population of the invocation is handled by CpInvocation*
 *
 * @param[in] aService   Returned by CpServiceCreate
 * @param[in] aAction    The action to invoke.  Returned by ServiceActionCreate
 * @param[in] aCallback  Callback to run when the invocation completes
 * @param[in] aPtr       Data to pass to the callback
 *
 * @return   Invocation handle
 */
DllExport CpInvocationC STDCALL CpServiceInvocation(CpService aService, ServiceAction aAction, OhNetCallbackAsync aCallback, void* aPtr);

/**
 * Invoke an action
 *
 * This function returns immediately.  Invocation of the action on a remote device is asynchronous.
 * 'aCallback' passed to CpServiceInvocation is run when the invocation completes.
 *
 * @param[in] aService     Returned by CpServiceCreate
 * @param[in] aInvocation  Returned by CpServiceInvocation
 */
DllExport void STDCALL CpServiceInvokeAction(CpService aService, CpInvocationC aInvocation);

/**
 * @addtogroup Argument
 * @ingroup CpService
 * @{
 */
/**
 * Opaque handle to an argument
 *
 * One Argument will be created per [in/out]put Parameter for the Action
 * Input parameters should construct arguments using the (Parameter, Val) constructor.
 * Output parameters should construct arguments using only the parameter and should
 * read the value when the invocation completes.
 */
typedef THandle ActionArgument;

/**
 * Create an integer input argument for an action
 *
 * Intended to be write only (its value is written on construction and not be later read)
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateInt.  Defines the name plus any bounds to the value for the argument.
 *                        Handle must have been previously added to the action using ServiceActionAddInputParameter
 * @param[in] aValue      Value for the argument
 *
 * @return  Handle for the newly created integer type input argument
 */
DllExport ActionArgument STDCALL ActionArgumentCreateIntInput(ServiceParameter aParameter, int32_t aValue);

/**
 * Create an integer output argument for an action
 *
 * Intended to be created without any value.  The value is later set after CpServiceInvokeAction is called
 * but before the invocation's callback is run)
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateInt.  Defines the name plus any bounds to the value for the argument.
 *                        Handle must have been previously added to the action using ServiceActionAddOutputParameter
 *
 * @return  Handle for the newly created integer type output argument
 */
DllExport ActionArgument STDCALL ActionArgumentCreateIntOutput(ServiceParameter aParameter);

/**
 * Create an unsigned integer input argument for an action
 *
 * Intended to be write only (its value is written on construction and not be later read)
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateUint.  Defines the name plus any bounds to the value for the argument.
 *                        Handle must have been previously added to the action using ServiceActionAddInputParameter
 * @param[in] aValue      Value for the argument
 *
 * @return  Handle for the newly created unsigned integer type input argument
 */
DllExport ActionArgument STDCALL ActionArgumentCreateUintInput(ServiceParameter aParameter, uint32_t aValue);

/**
 * Create an unsigned integer output argument for an action
 *
 * Intended to be created without any value.  The value is later set after CpServiceInvokeAction is called
 * but before the invocation's callback is run)
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateUint.  Defines the name plus any bounds to the value for the argument.
 *                        Handle must have been previously added to the action using ServiceActionAddOutputParameter
 *
 * @return  Handle for the newly created unsigned integer type output argument
 */
DllExport ActionArgument STDCALL ActionArgumentCreateUintOutput(ServiceParameter aParameter);

/**
 * Create a boolean input argument for an action
 *
 * Intended to be write only (its value is written on construction and not be later read)
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateBool.  Defines the name for the argument.
 *                        Handle must have been previously added to the action using ServiceActionAddInputParameter
 * @param[in] aValue      Value for the argument
 *
 * @return  Handle for the newly created boolean type input argument
 */
DllExport ActionArgument STDCALL ActionArgumentCreateBoolInput(ServiceParameter aParameter, uint32_t aValue);

/**
 * Create a boolean output argument for an action
 *
 * Intended to be created without any value.  The value is later set after CpServiceInvokeAction is called
 * but before the invocation's callback is run)
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateBool.  Defines the name for the argument.
 *                        Handle must have been previously added to the action using ServiceActionAddOutputParameter
 *
 * @return  Handle for the newly created boolean type output argument
 */
DllExport ActionArgument STDCALL ActionArgumentCreateBoolOutput(ServiceParameter aParameter);

/**
 * Create a string input argument for an action
 *
 * Intended to be write only (its value is written on construction and not be later read)
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateString.  Defines the name plus any set of allowed values for the argument.
 *                        Handle must have been previously added to the action using ServiceActionAddInputParameter
 * @param[in] aValue      Value for the argument
 *
 * @return  Handle for the newly created string type input argument
 */
DllExport ActionArgument STDCALL ActionArgumentCreateStringInput(ServiceParameter aParameter, const char* aValue);

/**
 * Create a string output argument for an action
 *
 * Intended to be created without any value.  The value is later set after CpServiceInvokeAction is called
 * but before the invocation's callback is run)
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateString.  Defines the name plus any set of allowed values for the argument.
 *                        Handle must have been previously added to the action using ServiceActionAddOutputParameter
 *
 * @return  Handle for the newly created string type output argument
 */
DllExport ActionArgument STDCALL ActionArgumentCreateStringOutput(ServiceParameter aParameter);

/**
 * Create a binary input argument for an action
 *
 * Intended to be write only (its value is written on construction and not be later read)
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateBinary.  Defines the name for the argument.
 *                        Handle must have been previously added to the action using ServiceActionAddInputParameter
 * @param[in] aData       Value for the argument
 * @param[in] aLen        Length (in bytes) of aData
 *
 * @return  Handle for the newly created binary type input argument
 */
DllExport ActionArgument STDCALL ActionArgumentCreateBinaryInput(ServiceParameter aParameter, const uint8_t* aData, uint32_t aLen);

/**
 * Create a binary output argument for an action
 *
 * Intended to be created without any value.  The value is later set after CpServiceInvokeAction is called
 * but before the invocation's callback is run)
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateBinary.  Defines the name for the argument.
 *                        Handle must have been previously added to the action using ServiceActionAddOutputParameter
 *
 * @return  Handle for the newly created boolean type output argument
 */
DllExport ActionArgument STDCALL ActionArgumentCreateBinaryOutput(ServiceParameter aParameter);

/**
 * Read the value of an integer argument.
 *
 * Only intended for use with output arguments inside the invocation completed callback.
 *
 * @param[in] aArgument  Returned by ActionArgumentCreateIntOutput
 *
 * @return  Current value of the argument
 */
DllExport int32_t STDCALL ActionArgumentValueInt(ActionArgument aArgument);

/**
 * Read the value of an unsigned integer argument.
 *
 * Only intended for use with output arguments inside the invocation completed callback.
 *
 * @param[in] aArgument  Returned by ActionArgumentCreateUintOutput
 *
 * @return  Current value of the argument
 */
DllExport uint32_t STDCALL ActionArgumentValueUint(ActionArgument aArgument);

/**
 * Read the value of a boolean argument.
 *
 * Only intended for use with output arguments inside the invocation completed callback.
 *
 * @param[in] aArgument  Returned by ActionArgumentCreateBoolOutput
 *
 * @return  Current value of the argument.  0 for false; non-zero for true
 */
DllExport uint32_t STDCALL ActionArgumentValueBool(ActionArgument aArgument);

/**
 * Read the value of a string argument.
 *
 * Only intended for use with output arguments inside the invocation completed callback.
 *
 * @param[in] aArgument  Returned by ActionArgumentCreateStringOutput
 *
 * @return  Current value of the argument.  Ownership passes to the client.  Use OhNetFree() to later destroy it.
 */
DllExport char* STDCALL ActionArgumentValueString(ActionArgument aArgument);

/**
 * Read the value of a string argument.
 *
 * Only intended for use with output arguments inside the invocation completed callback.
 *
 * @param[in]  aArgument  Returned by ActionArgumentCreateStringOutput
 * @param[out] aData      Current value of the argument.  Ownership passes to the client.
 *                        Use OhNetFree() to later destroy it.
 * @param[out] aLen       Length (in bytes) of aData
 */
DllExport void STDCALL ActionArgumentGetValueString(ActionArgument aArgument, char** aData, uint32_t* aLen);

/**
 * Read the value of a binary argument.
 *
 * Only intended for use with output arguments inside the invocation completed callback.
 *
 * @param[in]  aArgument  Returned by ActionArgumentCreateBinaryOutput
 * @param[out] aData      Current value of the argument.  Ownership passes to the client.
 *                        Use OhNetFree() to later destroy it.
 * @param[out] aLen       Length (in bytes) of aData
 */
DllExport void STDCALL ActionArgumentGetValueBinary(ActionArgument aArgument, uint8_t** aData, uint32_t* aLen);

/* @} */

/**
 * @addtogroup Invocation
 * @ingroup CpService
 * @{
 */

/**
 * Add an input argument to an invocation
 *
 * @param[in] aInvocation  Returned by CpServiceInvocation
 * @param[in] aArgument    Returned by ActionArgumentCreate[Type]Input.  Ownership passes to aInvocation
 */
DllExport void STDCALL CpInvocationAddInput(CpInvocationC aInvocation, ActionArgument aArgument);

/**
 * Add an output argument to an invocation
 *
 * @param[in] aInvocation  Returned by CpServiceInvocation
 * @param[in] aArgument    Returned by ActionArgumentCreate[Type]Output.  Ownership passes to aInvocation
 */
DllExport void STDCALL CpInvocationAddOutput(CpInvocationC aInvocation, ActionArgument aArgument);

/**
 * Query whether the invocation completed successfully
 *
 * @param[in]  aInvocation  Returned by CpServiceInvocation
 * @param[out] aErrorCode   Error code
 * @param[out] aErrorDesc   Error description
 *
 * @return  0 for success; non-zero for error
 */
DllExport uint32_t STDCALL CpInvocationError(CpInvocationC aInvocation, uint32_t* aErrorCode, const char** aErrorDesc);

/**
 * Read the value of an integer output argument.  Only intended for use inside the invocation completed callback.
 *
 * @param[in] aInvocation  Returned by CpServiceInvocation
 * @param[in] aIndex       Zero-based index into array of output arguments.  Must refer to an integer argument.
 *
 * @return  Value of the integer output argument
 */
DllExport int32_t STDCALL CpInvocationOutputInt(CpInvocationC aInvocation, uint32_t aIndex);

/**
 * Read the value of an unsigned integer output argument.  Only intended for use inside the invocation completed callback.
 *
 * @param[in] aInvocation  Returned by CpServiceInvocation
 * @param[in] aIndex       Zero-based index into array of output arguments.  Must refer to an unsigned integer argument.
 *
 * @return  Value of the unsigned integer output argument
 */
DllExport uint32_t STDCALL CpInvocationOutputUint(CpInvocationC aInvocation, uint32_t aIndex);

/**
 * Read the value of a boolean output argument.  Only intended for use inside the invocation completed callback.
 *
 * @param[in] aInvocation  Returned by CpServiceInvocation
 * @param[in] aIndex       Zero-based index into array of output arguments.  Must refer to a boolean argument.
 *
 * @return  Value of the boolean output argument.  0 for false; non-zero for true
 */
DllExport uint32_t STDCALL CpInvocationOutputBool(CpInvocationC aInvocation, uint32_t aIndex);

/**
 * Read the value of a string output argument.  Only intended for use inside the invocation completed callback.
 *
 * @param[in] aInvocation  Returned by CpServiceInvocation
 * @param[in] aIndex       Zero-based index into array of output arguments.  Must refer to a string argument.
 *
 * @return  Value of the string output argument.  Ownership passes to the caller.  Use OhNetFree() to destroy this.
 */
DllExport char* STDCALL CpInvocationOutputString(CpInvocationC aInvocation, uint32_t aIndex);

/**
 * Read the value of a string output argument.  Only intended for use inside the invocation completed callback.
 *
 * @param[in]  aInvocation  Returned by CpServiceInvocation
 * @param[in]  aIndex       Zero-based index into array of output arguments.  Must refer to a binary argument.
 * @param[out] aData        Value of the string output argument.  Ownership passes to the caller.  Use OhNetFree() to destroy this.
 * @param[out] aLen         Length (in bytes) of aData
 */
DllExport void STDCALL CpInvocationGetOutputString(CpInvocationC aInvocation, uint32_t aIndex, char** aData, uint32_t* aLen);

/**
 * Read the value of a binary output argument.  Only intended for use inside the invocation completed callback.
 *
 * @param[in]  aInvocation  Returned by CpServiceInvocation
 * @param[in]  aIndex       Zero-based index into array of output arguments.  Must refer to a binary argument.
 * @param[out] aData        Value of the binary output argument.  Ownership passes to the caller.  Use OhNetFree() to destroy this.
 * @param[out] aLen         Length (in bytes) of aData
 */
DllExport void STDCALL CpInvocationGetOutputBinary(CpInvocationC aInvocation, uint32_t aIndex, char** aData, uint32_t* aLen);

/* @} */

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_CPSERVICEC
