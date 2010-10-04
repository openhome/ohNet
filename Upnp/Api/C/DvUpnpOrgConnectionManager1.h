#ifndef HEADER_DVUPNPORGCONNECTIONMANAGER1_C
#define HEADER_DVUPNPORGCONNECTIONMANAGER1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackConnectionManager1GetProtocolInfo)(void* aPtr, uint32_t aVersion, char** aSource, char** aSink);
typedef int32_t (*CallbackConnectionManager1PrepareForConnection)(void* aPtr, uint32_t aVersion, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID);
typedef int32_t (*CallbackConnectionManager1ConnectionComplete)(void* aPtr, uint32_t aVersion, int32_t aConnectionID);
typedef int32_t (*CallbackConnectionManager1GetCurrentConnectionIDs)(void* aPtr, uint32_t aVersion, char** aConnectionIDs);
typedef int32_t (*CallbackConnectionManager1GetCurrentConnectionInfo)(void* aPtr, uint32_t aVersion, int32_t aConnectionID, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus);

DllExport THandle DvServiceUpnpOrgConnectionManager1Create(DvDeviceC aDevice);
DllExport void DvServiceUpnpOrgConnectionManager1Destroy(THandle aService);

DllExport void DvServiceUpnpOrgConnectionManager1EnableActionGetProtocolInfo(THandle aService, CallbackConnectionManager1GetProtocolInfo aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgConnectionManager1EnableActionPrepareForConnection(THandle aService, CallbackConnectionManager1PrepareForConnection aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgConnectionManager1EnableActionConnectionComplete(THandle aService, CallbackConnectionManager1ConnectionComplete aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgConnectionManager1EnableActionGetCurrentConnectionIDs(THandle aService, CallbackConnectionManager1GetCurrentConnectionIDs aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgConnectionManager1EnableActionGetCurrentConnectionInfo(THandle aService, CallbackConnectionManager1GetCurrentConnectionInfo aCallback, void* aPtr);

DllExport int32_t DvServiceUpnpOrgConnectionManager1SetPropertySourceProtocolInfo(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgConnectionManager1GetPropertySourceProtocolInfo(THandle aService, char** aValue);
DllExport int32_t DvServiceUpnpOrgConnectionManager1SetPropertySinkProtocolInfo(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgConnectionManager1GetPropertySinkProtocolInfo(THandle aService, char** aValue);
DllExport int32_t DvServiceUpnpOrgConnectionManager1SetPropertyCurrentConnectionIDs(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgConnectionManager1GetPropertyCurrentConnectionIDs(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGCONNECTIONMANAGER1_C

