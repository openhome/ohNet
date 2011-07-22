/**
 * Provider for the av.openhome.org:Product:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGPRODUCT1_C
#define HEADER_DVAVOPENHOMEORGPRODUCT1_C

#include <OpenHome/OhNetDefines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderAvOpenhomeOrgProduct1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Manufacturer action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionManufacturer
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aName
 * @param[out] aInfo
 * @param[out] aUrl
 * @param[out] aImageUri
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1Manufacturer)(void* aPtr, uint32_t aVersion, char** aName, char** aInfo, char** aUrl, char** aImageUri);
/**
 * Callback which runs when the Model action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionModel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aName
 * @param[out] aInfo
 * @param[out] aUrl
 * @param[out] aImageUri
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1Model)(void* aPtr, uint32_t aVersion, char** aName, char** aInfo, char** aUrl, char** aImageUri);
/**
 * Callback which runs when the Product action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionProduct
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aRoom
 * @param[out] aName
 * @param[out] aInfo
 * @param[out] aUrl
 * @param[out] aImageUri
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1Product)(void* aPtr, uint32_t aVersion, char** aRoom, char** aName, char** aInfo, char** aUrl, char** aImageUri);
/**
 * Callback which runs when the Standby action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionStandby
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1Standby)(void* aPtr, uint32_t aVersion, uint32_t* aValue);
/**
 * Callback which runs when the SetStandby action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSetStandby
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SetStandby)(void* aPtr, uint32_t aVersion, uint32_t aValue);
/**
 * Callback which runs when the SourceCount action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSourceCount
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SourceCount)(void* aPtr, uint32_t aVersion, uint32_t* aValue);
/**
 * Callback which runs when the SourceXml action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSourceXml
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SourceXml)(void* aPtr, uint32_t aVersion, char** aValue);
/**
 * Callback which runs when the SourceIndex action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSourceIndex
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SourceIndex)(void* aPtr, uint32_t aVersion, uint32_t* aValue);
/**
 * Callback which runs when the SetSourceIndex action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSetSourceIndex
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SetSourceIndex)(void* aPtr, uint32_t aVersion, uint32_t aValue);
/**
 * Callback which runs when the SetSourceIndexByName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSetSourceIndexByName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SetSourceIndexByName)(void* aPtr, uint32_t aVersion, const char* aValue);
/**
 * Callback which runs when the Source action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSource
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aIndex
 * @param[out] aSystemName
 * @param[out] aType
 * @param[out] aName
 * @param[out] aVisible
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1Source)(void* aPtr, uint32_t aVersion, uint32_t aIndex, char** aSystemName, char** aType, char** aName, uint32_t* aVisible);
/**
 * Callback which runs when the Attributes action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionAttributes
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1Attributes)(void* aPtr, uint32_t aVersion, char** aValue);
/**
 * Callback which runs when the SourceXmlChangeCount action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSourceXmlChangeCount
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SourceXmlChangeCount)(void* aPtr, uint32_t aVersion, uint32_t* aValue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderAvOpenhomeOrgProduct1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1Destroy(THandle aProvider);

/**
 * Register a callback for the action Manufacturer
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionManufacturer(THandle aProvider, CallbackProduct1Manufacturer aCallback, void* aPtr);
/**
 * Register a callback for the action Model
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionModel(THandle aProvider, CallbackProduct1Model aCallback, void* aPtr);
/**
 * Register a callback for the action Product
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionProduct(THandle aProvider, CallbackProduct1Product aCallback, void* aPtr);
/**
 * Register a callback for the action Standby
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionStandby(THandle aProvider, CallbackProduct1Standby aCallback, void* aPtr);
/**
 * Register a callback for the action SetStandby
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSetStandby(THandle aProvider, CallbackProduct1SetStandby aCallback, void* aPtr);
/**
 * Register a callback for the action SourceCount
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSourceCount(THandle aProvider, CallbackProduct1SourceCount aCallback, void* aPtr);
/**
 * Register a callback for the action SourceXml
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSourceXml(THandle aProvider, CallbackProduct1SourceXml aCallback, void* aPtr);
/**
 * Register a callback for the action SourceIndex
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSourceIndex(THandle aProvider, CallbackProduct1SourceIndex aCallback, void* aPtr);
/**
 * Register a callback for the action SetSourceIndex
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSetSourceIndex(THandle aProvider, CallbackProduct1SetSourceIndex aCallback, void* aPtr);
/**
 * Register a callback for the action SetSourceIndexByName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSetSourceIndexByName(THandle aProvider, CallbackProduct1SetSourceIndexByName aCallback, void* aPtr);
/**
 * Register a callback for the action Source
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSource(THandle aProvider, CallbackProduct1Source aCallback, void* aPtr);
/**
 * Register a callback for the action Attributes
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionAttributes(THandle aProvider, CallbackProduct1Attributes aCallback, void* aPtr);
/**
 * Register a callback for the action SourceXmlChangeCount
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSourceXmlChangeCount(THandle aProvider, CallbackProduct1SourceXmlChangeCount aCallback, void* aPtr);

/**
 * Set the value of the ManufacturerName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyManufacturerName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ManufacturerName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyManufacturerName(THandle aProvider, char** aValue);
/**
 * Set the value of the ManufacturerInfo property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyManufacturerInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ManufacturerInfo property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyManufacturerInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the ManufacturerUrl property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyManufacturerUrl(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ManufacturerUrl property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyManufacturerUrl(THandle aProvider, char** aValue);
/**
 * Set the value of the ManufacturerImageUri property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyManufacturerImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ManufacturerImageUri property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyManufacturerImageUri(THandle aProvider, char** aValue);
/**
 * Set the value of the ModelName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyModelName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ModelName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyModelName(THandle aProvider, char** aValue);
/**
 * Set the value of the ModelInfo property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyModelInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ModelInfo property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyModelInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the ModelUrl property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyModelUrl(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ModelUrl property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyModelUrl(THandle aProvider, char** aValue);
/**
 * Set the value of the ModelImageUri property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyModelImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ModelImageUri property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyModelImageUri(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductRoom property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductRoom(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductRoom property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductRoom(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductName(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductInfo property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductInfo property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductUrl property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductUrl(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductUrl property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductUrl(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductImageUri property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductImageUri property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductImageUri(THandle aProvider, char** aValue);
/**
 * Set the value of the Standby property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyStandby(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Standby property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyStandby(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the SourceIndex property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertySourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SourceIndex property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertySourceIndex(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the SourceCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertySourceCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SourceCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertySourceCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the SourceXml property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertySourceXml(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SourceXml property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertySourceXml(THandle aProvider, char** aValue);
/**
 * Set the value of the Attributes property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyAttributes(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Attributes property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyAttributes(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGPRODUCT1_C

