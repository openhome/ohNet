/**
 * Device
 *
 * Has a universally unique name and operates on 0..n protocols.
 * Services are added by constructing DvProvider* instances, passing a handle to a
 * DvDeviceC during construction
 */

#ifndef HEADER_DVDEVICEC
#define HEADER_DVDEVICEC

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/OhNet.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvDevice
 * @ingroup Device
 * @{
 */

/**
 * Opaque handle to a device
 */
typedef THandle DvDeviceC;

/**
 * Callback which is run before serving a file begins
 *
 * @param[in] aWriterData  Opaque pointer passed to OhNetCallbackResourceManager
 * @param[in] aTotalBytes  Size in bytes of the file.  Can be 0 if size is unknown.
 * @param[in] aMimeType    MIME type of the file.  May be NULL if this is unknown.
 *
 * @return  0 on success; non-zero on error.
 */
typedef int32_t (STDCALL *OhNetCallbackWriteResourceBegin)(void* aWriterData, uint32_t aTotalBytes, const char* aMimeType);

/**
 * Callback which runs to serve a chunk of a file
 *
 * Will be called 0..n times after OhNetCallbackWriteResourceBegin and before OhNetCallbackWriteResourceEnd
 *
 * @param[in] aWriterData  Opaque pointer passed to OhNetCallbackResourceManager
 * @param[in] aData        File data to write
 * @param[in] aBytes       Size in bytes of aData
 *
 * @return  0 on success; non-zero on error.
 */
typedef int32_t (STDCALL *OhNetCallbackWriteResource)(void* aWriterData, const uint8_t* aData, uint32_t aBytes);

/**
 * Called when serving of a file is complete
 *
 * Will only be called after a call to OhNetCallbackWriteResourceBegin.
 * An error writing the file can be inferred if OhNetCallbackWriteResource has not been called or
 * if aTotalBytes was non-zero in the Begin callback and the sum of aBytes values in the Write
 * callbacks does not match aTotalBytes.
 *
 * @param[in] aWriterData  Opaque pointer passed to OhNetCallbackResourceManager
 *
 * @return  0 on success; non-zero on error.
 */
typedef int32_t (STDCALL *OhNetCallbackWriteResourceEnd)(void* aWriterData);

/**
 * Callback which runs when a device is asked to serve an unknown file
 *
 * @param[in] aUserData       'aPtr' passed to DvDeviceCreate
 * @param[in] aUriTail        File being requested
 * @param[in] aInterface      IPv4 network interface the file request was made on
 * @param[in] aLanguageList   Handle to a prioritised list of the languages accepted in the resources to
 *                            be written.  This should be passed to DvResourceWriterLanguage*.
 * @param[in] aWriterData     Opaque pointer to be passed to all 3 OhNetCallbackWriteResource* callbacks
 * @param[in] aWriteBegin     Callback to run at the start of serving the file.
 *                            Should not be run if the file cannot be supplied.
 * @param[in] aWriteResource  Callback to run to write file data.  Must be called at least once to
 *                            successfully serve a file.  Can be called repeatedly to allow the file
 *                            to be written in chunks (avoiding the need to read a large file fully
 *                            into memory).
 * @param[in] aWriteEnd       Callback to be run at the end of serving a file.
 *                            Must be called if aWriteBegin is called.
 *
 * @return  0 on success; non-zero on error.
 */
typedef int32_t (STDCALL *OhNetCallbackResourceManager)(void* aUserData, const char* aUriTail, uint32_t aInterface, THandle aLanguageList, void* aWriterData,
                                                        OhNetCallbackWriteResourceBegin aWriteBegin,
                                                        OhNetCallbackWriteResource aWriteResource,
                                                        OhNetCallbackWriteResourceEnd aWriteEnd);


/**
 * Constructor.  Creates a device ready to have services or attributes added.
 * Addition of any protocols to operate over is the responsibility of any sub-classes.
 *
 * @param[in] aUdn    Universally unique identifier.  The caller is responsible for
 *                    calculating/assigning this
 *
 * @return  Handle to the new device
 */
DllExport DvDeviceC STDCALL DvDeviceCreate(const char* aUdn);

/**
 * Destroy a device.
 * Must be called once for each successful call to DvDeviceCreate[NoResources]
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 */
DllExport void STDCALL DvDeviceDestroy(DvDeviceC aDevice);

/**
 * Query the (client-specified) unique device name
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  The name passed to the c'tor
 */
DllExport const char* STDCALL DvDeviceUdn(DvDeviceC aDevice);

/**
 * Query the (client-specified) unique device name
 *
 * @param[in]  aDevice  Handle returned by DvDeviceCreate[NoResources]
 * @param[out] aUdn     The name passed to the c'tor.  Ownership remains with aDevice.
 * @param[out] aLen     Length (in bytes) of aUdn.
 */
DllExport void STDCALL DvDeviceGetUdn(DvDeviceC aDevice, const char** aUdn, uint32_t* aLen);

/**
 * Query whether a device is enabled
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  1 if the device is enabled; 0 otherwise
 */
DllExport int32_t STDCALL DvDeviceEnabled(DvDeviceC aDevice);

/**
 * Set the device ready for external use
 *
 * When this returns, the device will be available for use using any of the protocols
 * the device stack supports.  Services must not be added (DvProvider-derived classes
 * created using this device) and attributes must not be set while a device is enabled.
 * If these need to change in future, the device must first be disabled.
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 */
DllExport void STDCALL DvDeviceSetEnabled(DvDeviceC aDevice);

/**
 * Disable the device, withdrawing its availability for external use
 *
 * Services can be added and attributes can be set once a device is disabled.  The device
 * will not be available for use again until SetEnabled() is called again.
 * This call is asynchronous so returns before the device is fully disabled.  Wait for the
 * aCompleted callback before adding services or setting attributes.
 *
 * @param[in] aDevice     Handle returned by DvDeviceCreate[NoResources]
 * @param[in] aCompleted  Callback which runs when the device is fully disabled.
 *                        Until this runs, the device should be considered to still be enabled.
 * @param[in] aPtr        Data to be passed to the aCompleted callback
 */
DllExport void STDCALL DvDeviceSetDisabled(DvDeviceC aDevice, OhNetCallback aCompleted, void* aPtr);

/**
 * Query the value of an atrribute
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 * @param[in]  aKey    string of the form protocol_name.protocol_specific_key
 *                     Commonly used keys are published ... (!!!! where?)
 * @param[out] aValue  const pointer to the attribute or NULL if the attribute has not been set.
 */
DllExport void STDCALL DvDeviceGetAttribute(DvDeviceC aDevice, const char* aKey, const char** aValue);

/**
 * Set the value of an attribute
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 * @param[in] aKey     string of the form protocol_name.protocol_specific_key
 * @param[in] aValue   attribute will be set to a copy of this string
 */
DllExport void STDCALL DvDeviceSetAttribute(DvDeviceC aDevice, const char* aKey, const char* aValue);

/**
 * Constructor.  Creates a device capable of operating on any of the protocols the device
 * stack supports as standard but with no services or attributes as yet.
 *
 * @param[in] aUdn    Universally unique identifier.  The caller is responsible for
 *                    calculating/assigning this
 *
 * @return  Handle to the new device
 */
DllExport DvDeviceC STDCALL DvDeviceStandardCreateNoResources(const char* aUdn);

/**
 * Constructor.  Creates a device capable of serving UI files and of operating on any of the
 * protocols the device stack supports as standard but with no services or attributes as yet.
 *
 * @param[in] aUdn    Universally unique identifier.  The caller is responsible for
 *                    calculating/assigning this
 * @param[in] aResourceManager  Callback which will be run when a client requests a file the
 *                              device itself cannot deliver
 * @param[in] aPtr    Data to be passed to the aResourceManager callback
 *
 * @return  Handle to the new device
 */
DllExport DvDeviceC STDCALL DvDeviceStandardCreate(const char* aUdn, OhNetCallbackResourceManager aResourceManager, void* aPtr);

/**
 * Query the base uri for the resource manager.
 *
 * @param[in] aDevice   Handle returned by DvDeviceCreate[NoResources]
 * @param[in] aAdapter  The network adapter to return a uri for.
 *
 * @return  The base uri.  May be NULL if there is no resource manager.
 */
DllExport char* STDCALL DvDeviceStandardResourceManagerUri(DvDeviceC aDevice, THandle aAdapter);

/**
 * Query the base uri for the resource manager.
 *
 * @param[in]  aDevice   Handle returned by DvDeviceCreate[NoResources]
 * @param[in]  aAdapter  The network adapter to return a uri for.
 * @param[out] aUri      The base uri.  May be NULL if there is no resource manager.  Use OhNetFree to destroy.
 * @param[out] aLen      Length (in bytes) of *aUri.
 */
DllExport void STDCALL DvDeviceStandardGetResourceManagerUri(DvDeviceC aDevice, THandle aAdapter, char** aUri, uint32_t* aLen);

/**
 * Query the number of languages accepted by the resource writer.
 *
 * @param[in] aLanguageList  Handle passed to OhNetCallbackResourceManager.
 *
 * @return  Number of accepted languages
 */
DllExport uint32_t STDCALL DvResourceWriterLanguageCount(THandle aLanguageList);

/**
 * Query a language accepted by the resource writer.
 *
 * @param[in] aLanguageList  Handle passed to OhNetCallbackResourceManager.
 * @param[in] aIndex         Zero-based index into the list of accepted languages.
 *                           Valid values are [0..DvResourceWriterLanguageCount-1].
 *                           The list is in priority order so index #0 is preferred over #1 etc.
 *
 * @return  ISO 639 style language code (e.g. "en-gb" or "en")
 */
DllExport const char* STDCALL DvResourceWriterLanguage(THandle aLanguageList, uint32_t aIndex);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVDEVICEC
