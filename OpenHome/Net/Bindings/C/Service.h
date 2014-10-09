#ifndef HEADER_SERVICEC
#define HEADER_SERVICEC

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/OhNet.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup Service
 * @ingroup Core
 * @{
 */

/**
 * Opaque handle to a service
 */
typedef THandle HandleService;

/**
 * @addtogroup Parameter
 * @ingroup Service
 * @{
 */
/**
 * Opaque handle to a parameter.
 * Each action owns 0..n of these.
 */
typedef THandle ServiceParameter;

#define kServiceParameterIntDefaultMin   INT32_MIN;
#define kServiceParameterIntDefaultMax   INT32_MAX;
#define kServiceParameterIntDefaultStep  1;
#define kServiceParameterUintDefaultMin  0;
#define kServiceParameterUintDefaultMax  UINT32_MAX;
#define kServiceParameterUintDefaultStep 1;

/**
 * Create an integer parameter
 *
 * Note that no destructor exists.  Parameters should be added to an action or property which takes ownership of them.
 *
 * @param[in] aName      Name to assign to this parameter
 * @param[in] aMinValue  Minimum allowed value.  Use kServiceParameterIntDefaultMin by default.
 * @param[in] aMaxValue  Maximum allowed value.  Use kServiceParameterIntDefaultMax by default.
 * @param[in] aStep      Non-negative increment between allowed values.  Use kServiceParameterIntDefaultStep by default
 *
 * @return   Handle to the newly created service
 */
DllExport ServiceParameter STDCALL ServiceParameterCreateInt(const char* aName, int32_t aMinValue, int32_t aMaxValue, int32_t aStep);

/**
 * Create an unsigned integer parameter
 *
 * Note that no destructor exists.  Parameters should be added to an action or property which takes ownership of them.
 *
 * @param[in] aName      Name to assign to this parameter
 * @param[in] aMinValue  Minimum allowed value.  Use kServiceParameterUintDefaultMin by default.
 * @param[in] aMaxValue  Maximum allowed value.  Use kServiceParameterUintDefaultMax by default.
 * @param[in] aStep      Non-negative increment between allowed values.  Use kServiceParameterUintDefaultStep by default
 *
 * @return   Handle to the newly created service
 */
DllExport ServiceParameter STDCALL ServiceParameterCreateUint(const char* aName, uint32_t aMinValue, uint32_t aMaxValue, uint32_t aStep);

/**
 * Create a boolean parameter
 *
 * Note that no destructor exists.  Parameters should be added to an action or property which takes ownership of them.
 *
 * @param[in] aName      Name to assign to this parameter
 *
 * @return   Handle to the newly created service
 */
DllExport ServiceParameter STDCALL ServiceParameterCreateBool(const char* aName);

/**
 * Create a string parameter
 *
 * Note that no destructor exists.  Parameters should be added to an action or property which takes ownership of them.
 *
 * @param[in] aName           Name to assign to this parameter
 * @param[in] aAllowedValues  Array of strings limiting the permitted values of this parameter.  May be NULL.
 * @param[in] aCount          Number of allowed values.  Must be 0 if aAllowedValues is NULL.
 *
 * @return   Handle to the newly created service
 */
DllExport ServiceParameter STDCALL ServiceParameterCreateString(const char* aName, char** aAllowedValues, uint32_t aCount);

/**
 * Create a binary parameter
 *
 * Note that no destructor exists.  Parameters should be added to an action or property which takes ownership of them.
 *
 * @param[in] aName      Name to assign to this parameter
 *
 * @return   Handle to the newly created service
 */
DllExport ServiceParameter STDCALL ServiceParameterCreateBinary(const char* aName);
/* @} */
/**
 * @addtogroup Property
 * @ingroup Service
 * @{
 */
/**
 * Opaque handle to a property. One property will exist for each property (state variable) of a service.
 */
typedef THandle ServiceProperty;
/* @} */
/**
 * @addtogroup Parameter
 * @ingroup Service
 * @{
 */
/**
 * Create a related parameter
 *
 * A related parameter reads its allowed values from an existing ServiceProperty.  It is normally useful
 * to users of the device stack.  Any type of property can be used.  However, since only int, uint and
 * string types can have bounds applied, it only makes sense to use these types of property.
 * Note that no destructor exists.  Parameters should be added to an action or property which takes ownership of them.
 *
 * @param[in] aName      Name to assign to this parameter
 * @param[in] aProperty  Property to supply this parameter's value bounds
 *
 * @return   Handle to the newly created service
 */
DllExport ServiceParameter STDCALL ServiceParameterCreateRelated(const char* aName, ServiceProperty aProperty);
/* @} */

/**
 * @addtogroup Property
 * @ingroup Service
 * @{
 */

/**
 * Destroy a property instance, freeing all memory associated with it.
 *
 * @param[in] aProperty  Property handle returned from ServicePropertyCreate[Type][Cp|Dv]
 */
DllExport void STDCALL ServicePropertyDestroy(ServiceProperty aProperty);

/**
 * Create an integer property suitable for use by a client of the control point stack
 *
 * Note that no destructor exists.  Properties must be added to proxies or providers, which take ownership of them
 *
 * @param[in] aName      Name to assign to the property
 * @param[in] aCallback  Function to run when the value of the property changes
 * @param[in] aPtr       Data to pass to the callback.  May be NULL.
 *
 * @return   Handle to the newly created property
 */
DllExport ServiceProperty STDCALL ServicePropertyCreateIntCp(const char* aName, OhNetCallback aCallback, void* aPtr);

/**
 * Create an integer property suitable for use by a client of the device stack
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateInt.  Ownership passed to this property.
 *
 * @return   Handle to the newly created property
 */
DllExport ServiceProperty STDCALL ServicePropertyCreateIntDv(ServiceParameter aParameter);

/**
 * Create an integer property suitable for use by a client of the control point stack
 *
 * Note that no destructor exists.  Properties must be added to proxies or providers, which take ownership of them
 *
 * @param[in] aName      Name to assign to the property
 * @param[in] aCallback  Function to run when the value of the property changes
 * @param[in] aPtr       Data to pass to the callback.  May be NULL.
 *
 * @return   Handle to the newly created property
 */
DllExport ServiceProperty STDCALL ServicePropertyCreateUintCp(const char* aName, OhNetCallback aCallback, void* aPtr);

/**
 * Create an unsigned integer property suitable for use by a client of the device stack
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateUint.  Ownership passed to this property.
 *
 * @return   Handle to the newly created property
 */
DllExport ServiceProperty STDCALL ServicePropertyCreateUintDv(ServiceParameter aParameter);

/**
 * Create a boolean property suitable for use by a control point
 *
 * Note that no destructor exists.  Properties must be added to proxies or providers, which take ownership of them
 *
 * @param[in] aName      Name to assign to the property
 * @param[in] aCallback  Function to run when the value of the property changes
 * @param[in] aPtr       Data to pass to the callback.  May be NULL.
 *
 * @return   Handle to the newly created property
 */
DllExport ServiceProperty STDCALL ServicePropertyCreateBoolCp(const char* aName, OhNetCallback aCallback, void* aPtr);

/**
 * Create a boolean property suitable for use by a client of the device stack
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateBool.  Ownership passed to this property.
 *
 * @return   Handle to the newly created property
 */
DllExport ServiceProperty STDCALL ServicePropertyCreateBoolDv(ServiceParameter aParameter);

/**
 * Create an integer property suitable for use by a client of the control point stack
 *
 * Note that no destructor exists.  Properties must be added to proxies or providers, which take ownership of them
 *
 * @param[in] aName      Name to assign to the property
 * @param[in] aCallback  Function to run when the value of the property changes
 * @param[in] aPtr       Data to pass to the callback.  May be NULL.
 *
 * @return   Handle to the newly created property
 */
DllExport ServiceProperty STDCALL ServicePropertyCreateStringCp(const char* aName, OhNetCallback aCallback, void* aPtr);

/**
 * Create a string property suitable for use by a client of the device stack
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateString.  Ownership passed to this property.
 *
 * @return   Handle to the newly created property
 */
DllExport ServiceProperty STDCALL ServicePropertyCreateStringDv(ServiceParameter aParameter);

/**
 * Create an integer property suitable for use by a client of the control point stack
 *
 * Note that no destructor exists.  Properties must be added to proxies or providers, which take ownership of them
 *
 * @param[in] aName      Name to assign to the property
 * @param[in] aCallback  Function to run when the value of the property changes
 * @param[in] aPtr       Data to pass to the callback.  May be NULL.
 *
 * @return   Handle to the newly created property
 */
DllExport ServiceProperty STDCALL ServicePropertyCreateBinaryCp(const char* aName, OhNetCallback aCallback, void* aPtr);

/**
 * Create a binary property suitable for use by a client of the device stack
 *
 * @param[in] aParameter  Returned by ServiceParameterCreateBinary.  Ownership passed to this property.
 *
 * @return   Handle to the newly created property
 */
DllExport ServiceProperty STDCALL ServicePropertyCreateBinaryDv(ServiceParameter aParameter);

/**
 * Read the current value of an integer property
 *
 * @param[in]  aProperty Returned by ServicePropertyCreateInt[Cp|Dv]
 * @param[out] aValue    Current value of the property
 *
 * @return   0 if the property value was read.  -1 if it is not available (no value has ever been set)
 */
DllExport int32_t STDCALL ServicePropertyValueInt(ServiceProperty aProperty, int32_t* aValue);

/**
 * Read the current value of an unsigned integer property
 *
 * @param[in] aProperty  Returned by ServicePropertyCreateUint[Cp|Dv]
 * @param[out] aValue    Current value of the property
 *
 * @return   0 if the property value was read.  -1 if it is not available (no value has ever been set)
 */
DllExport int32_t STDCALL ServicePropertyValueUint(ServiceProperty aProperty, uint32_t* aValue);

/**
 * Read the current value of a boolean property
 *
 * @param[in] aProperty  Returned by ServicePropertyCreateBool[Cp|Dv]
 * @param[out] aValue    Current value of the property.  0 for false; non-zero for true
 *
 * @return   0 if the property value was read.  -1 if it is not available (no value has ever been set)
 */
DllExport int32_t STDCALL ServicePropertyValueBool(ServiceProperty aProperty, uint32_t* aValue);

/**
 * Read the current value of a string property
 *
 * @param[in] aProperty  Returned by ServicePropertyCreateString[Cp|Dv]
 *
 * @return   Copy of the current value of the property.  Ownership is passed to the caller.
 *           Use OhNetFree to later free it
 *
 * @return   0 if the property value was read.  -1 if it is not available (no value has ever been set)
 */
DllExport const char* STDCALL ServicePropertyValueString(ServiceProperty aProperty);

/**
 * Read the current value of a string property
 *
 * @param[in]  aProperty  Returned by ServicePropertyCreateString[Cp|Dv]
 * @param[out] aData      Copy of the current value of the property.  Ownership is passed to the caller.
 *                        Use OhNetFree to later free it
 * @param[out] aLen       Number of bytes of data returned
 *
 * @return   0 if the property value was read.  -1 if it is not available (no value has ever been set)
 */
DllExport int32_t STDCALL ServicePropertyGetValueString(ServiceProperty aProperty, const char** aData, uint32_t* aLen);

/**
 * Read the current value of a binary property
 *
 * @param[in]  aProperty  Returned by ServicePropertyCreateBinary[Cp|Dv]
 * @param[out] aData      Copy of the current value of the property.  Ownership is passed to the caller.
 *                        Use OhNetFree to later free it
 * @param[out] aLen       Number of bytes of data returned
 *
 * @return   0 if the property value was read.  -1 if it is not available (no value has ever been set)
 */
DllExport int32_t STDCALL ServicePropertyGetValueBinary(ServiceProperty aProperty, const uint8_t** aData, uint32_t* aLen);

/**
 * Set the current value of an integer property
 *
 * @param[in] aProperty  Returned by ServicePropertyCreateString[Cp|Dv]
 * @param[in] aValue     New value for the property
 *
 * @return    1 if the value of the property has changed; 0 otherwise
 */
DllExport uint32_t STDCALL ServicePropertySetValueInt(ServiceProperty aProperty, int32_t aValue);

/**
 * Set the current value of an unsigned integer property
 *
 * @param[in] aProperty  Returned by ServicePropertyCreateString[Cp|Dv]
 * @param[in] aValue     New value for the property
 *
 * @return    1 if the value of the property has changed; 0 otherwise
 */
DllExport uint32_t STDCALL ServicePropertySetValueUint(ServiceProperty aProperty, uint32_t aValue);

/**
 * Set the current value of a boolean property
 *
 * @param[in] aProperty  Returned by ServicePropertyCreateString[Cp|Dv]
 * @param[in] aValue     New value for the property (non-zero for true)
 *
 * @return    1 if the value of the property has changed; 0 otherwise
 */
DllExport uint32_t STDCALL ServicePropertySetValueBool(ServiceProperty aProperty, uint32_t aValue);

/**
 * Set the current value of a string property
 *
 * @param[in] aProperty  Returned by ServicePropertyCreateString[Cp|Dv]
 * @param[in] aValue     New value for the property
 *
 * @return    1 if the value of the property has changed; 0 otherwise
 */
DllExport uint32_t STDCALL ServicePropertySetValueString(ServiceProperty aProperty, const char* aValue);

/**
 * Set the current value of a string property
 *
 * @param[in] aProperty  Returned by ServicePropertyCreateString[Cp|Dv]
 * @param[in] aValue     Pointer to new value for the property
 * @param[in] aLen       Length of data pointed to by aValue
 *
 * @return    1 if the value of the property has changed; 0 otherwise
 */
DllExport uint32_t STDCALL ServicePropertySetValueStringAsBuffer(ServiceProperty aProperty, const char* aValue, uint32_t aLen);

/**
 * Set the current value of a binary property
 *
 * @param[in] aProperty  Returned by ServicePropertyCreateString[Cp|Dv]
 * @param[in] aValue     Pointer to new value for the property
 * @param[in] aLen       Length of data pointed to by aValue
 *
 * @return    1 if the value of the property has changed; 0 otherwise
 */
DllExport uint32_t STDCALL ServicePropertySetValueBinary(ServiceProperty aProperty, uint8_t* aValue, uint32_t aLen);

/* @} */

/**
 * @addtogroup Action
 * @ingroup Service
 * @{
 */
/**
 * Opaque handle to an action
 *
 * Each service has 0..n of these.  Each action has 0..n input parameters and
 * 0..m output parameters.  Each parameter must be either input or output.
 */
typedef THandle ServiceAction;

/**
 * Create an action
 *
 * @param[in] aName  Name of the action
 *
 * @return   Handle to the newly created action
 */
DllExport ServiceAction STDCALL ServiceActionCreate(const char* aName);

/**
 * Destroy an action
 *
 * @param[in] aAction     Returned by ServiceActionCreate
 */
DllExport void STDCALL ServiceActionDestroy(ServiceAction aAction);

/**
 * Add an input parameter to an action
 *
 * @param[in] aAction     Returned by ServiceActionCreate
 * @param[in] aParameter  Input parameter to be added.  Ownership passes to the action
 */
DllExport void STDCALL ServiceActionAddInputParameter(ServiceAction aAction, ServiceParameter aParameter);

/**
 * Add an output parameter to an action
 *
 * @param[in] aAction     Returned by ServiceActionCreate
 * @param[in] aParameter  Input parameter to be added.  Ownership passes to the action
 */
DllExport void STDCALL ServiceActionAddOutputParameter(ServiceAction aAction, ServiceParameter aParameter);

/**
 * Query the action name
 *
 * @param[in] aAction     Returned by ServiceActionCreate
 *
 * @return   The action name
 */
DllExport const char* STDCALL ServiceActionName(ServiceAction aAction);

/**
 * Query the action name
 *
 * @param[in] aAction     Returned by ServiceActionCreate
 * @param[out] aName      Copy of the current value of the property.  Ownership remains with aAction.
 * @param[out] aLen       Number of bytes of data returned
 *
 * @return   The action name
 */
DllExport void STDCALL ServiceActionGetName(ServiceAction aAction, const char** aName, uint32_t* aLen);

/* @} */

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_SERVICEC
