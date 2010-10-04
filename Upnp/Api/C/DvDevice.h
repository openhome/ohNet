#ifndef HEADER_DVDEVICEC
#define HEADER_DVDEVICEC

#include <OsTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Opaque handle to a device
 */
typedef THandle DvDeviceC;

typedef void (*ZappCallback)(void* aPtr);

typedef void (*ZappCallbackWriteResourceBegin)(void* aPtr, uint32_t aTotalBytes, const char* aMimeType);
typedef void (*ZappCallbackWriteResource)(void* aPtr, const uint8_t* aData, uint32_t aBytes);
typedef void (*ZappCallbackWriteResourceEnd)(void* aPtr);
typedef void (*ZappCallbackResourceManager)(void* aUserData, const char* aUriTail, TIpAddress aInterface, void* aWriterData,
	                                        ZappCallbackWriteResourceBegin aWriteBegin,
                                            ZappCallbackWriteResource aWriteResource,
                                            ZappCallbackWriteResourceEnd aWriteEnd);

DllExport DvDeviceC DvDeviceCreateNoResources(const char* aUdn);
DllExport DvDeviceC DvDeviceCreate(const char* aUdn, ZappCallbackResourceManager aResourceManager, void* aPtr);
DllExport void DvDeviceDestroy(DvDeviceC aDevice);
DllExport const char* DvDeviceUdn(DvDeviceC aDevice);
DllExport int32_t DvDeviceEnabled(DvDeviceC aDevice);
DllExport void DvDeviceSetEnabled(DvDeviceC aDevice);
DllExport void DvDeviceSetDisabled(DvDeviceC aDevice, ZappCallback aCompleted, void* aPtr);
DllExport void DvDeviceGetAttribute(DvDeviceC aDevice, const char* aKey, const char** aValue);
DllExport void DvDeviceSetAttribute(DvDeviceC aDevice, const char* aKey, const char* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVDEVICEC
