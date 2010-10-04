#ifndef HEADER_DVUPNPORGCONNECTIONMANAGER2_C
#define HEADER_DVUPNPORGCONNECTIONMANAGER2_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackConnectionManager2GetProtocolInfo)(void* aPtr, uint32_t aVersion, char** aSource, char** aSink);
typedef int32_t (*CallbackConnectionManager2PrepareForConnection)(void* aPtr, uint32_t aVersion, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID);
typedef int32_t (*CallbackConnectionManager2ConnectionComplete)(void* aPtr, uint32_t aVersion, int32_t aConnectionID);
typedef int32_t (*CallbackConnectionManager2GetCurrentConnectionIDs)(void* aPtr, uint32_t aVersion, char** aConnectionIDs);
typedef int32_t (*CallbackConnectionManager2GetCurrentConnectionInfo)(void* aPtr, uint32_t aVersion, int32_t aConnectionID, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus);

DllExport THandle DvServiceUpnpOrgConnectionManager2Create(DvDeviceC aDevice);
DllExport void DvServiceUpnpOrgConnectionManager2Destroy(THandle aService);

DllExport void DvServiceUpnpOrgConnectionManager2EnableActionGetProtocolInfo(THandle aService, CallbackConnectionManager2GetProtocolInfo aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgConnectionManager2EnableActionPrepareForConnection(THandle aService, CallbackConnectionManager2PrepareForConnection aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgConnectionManager2EnableActionConnectionComplete(THandle aService, CallbackConnectionManager2ConnectionComplete aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgConnectionManager2EnableActionGetCurrentConnectionIDs(THandle aService, CallbackConnectionManager2GetCurrentConnectionIDs aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgConnectionManager2EnableActionGetCurrentConnectionInfo(THandle aService, CallbackConnectionManager2GetCurrentConnectionInfo aCallback, void* aPtr);

DllExport int32_t DvServiceUpnpOrgConnectionManager2SetPropertySourceProtocolInfo(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgConnectionManager2GetPropertySourceProtocolInfo(THandle aService, char** aValue);
DllExport int32_t DvServiceUpnpOrgConnectionManager2SetPropertySinkProtocolInfo(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgConnectionManager2GetPropertySinkProtocolInfo(THandle aService, char** aValue);
DllExport int32_t DvServiceUpnpOrgConnectionManager2SetPropertyCurrentConnectionIDs(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgConnectionManager2GetPropertyCurrentConnectionIDs(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGCONNECTIONMANAGER2_C

