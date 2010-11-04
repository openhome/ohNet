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

DllExport THandle DvProviderUpnpOrgConnectionManager2Create(DvDeviceC aDevice);
DllExport void DvProviderUpnpOrgConnectionManager2Destroy(THandle aService);

DllExport void DvProviderUpnpOrgConnectionManager2EnableActionGetProtocolInfo(THandle aService, CallbackConnectionManager2GetProtocolInfo aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgConnectionManager2EnableActionPrepareForConnection(THandle aService, CallbackConnectionManager2PrepareForConnection aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgConnectionManager2EnableActionConnectionComplete(THandle aService, CallbackConnectionManager2ConnectionComplete aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgConnectionManager2EnableActionGetCurrentConnectionIDs(THandle aService, CallbackConnectionManager2GetCurrentConnectionIDs aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgConnectionManager2EnableActionGetCurrentConnectionInfo(THandle aService, CallbackConnectionManager2GetCurrentConnectionInfo aCallback, void* aPtr);

DllExport int32_t DvProviderUpnpOrgConnectionManager2SetPropertySourceProtocolInfo(THandle aService, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgConnectionManager2GetPropertySourceProtocolInfo(THandle aService, char** aValue);
DllExport int32_t DvProviderUpnpOrgConnectionManager2SetPropertySinkProtocolInfo(THandle aService, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgConnectionManager2GetPropertySinkProtocolInfo(THandle aService, char** aValue);
DllExport int32_t DvProviderUpnpOrgConnectionManager2SetPropertyCurrentConnectionIDs(THandle aService, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgConnectionManager2GetPropertyCurrentConnectionIDs(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGCONNECTIONMANAGER2_C

