#ifndef HEADER_DVLINNCOUKPRODUCT3_C
#define HEADER_DVLINNCOUKPRODUCT3_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackProduct3Type)(void* aPtr, uint32_t aVersion, char** aaType);
typedef int32_t (*CallbackProduct3Model)(void* aPtr, uint32_t aVersion, char** aaModel);
typedef int32_t (*CallbackProduct3Name)(void* aPtr, uint32_t aVersion, char** aaName);
typedef int32_t (*CallbackProduct3SetName)(void* aPtr, uint32_t aVersion, const char* aaName);
typedef int32_t (*CallbackProduct3Room)(void* aPtr, uint32_t aVersion, char** aaRoom);
typedef int32_t (*CallbackProduct3SetRoom)(void* aPtr, uint32_t aVersion, const char* aaRoom);
typedef int32_t (*CallbackProduct3Standby)(void* aPtr, uint32_t aVersion, uint32_t* aaStandby);
typedef int32_t (*CallbackProduct3SetStandby)(void* aPtr, uint32_t aVersion, uint32_t aaStandby);
typedef int32_t (*CallbackProduct3SourceCount)(void* aPtr, uint32_t aVersion, uint32_t* aaSourceCount);
typedef int32_t (*CallbackProduct3SourceXml)(void* aPtr, uint32_t aVersion, char** aaSourceXml);
typedef int32_t (*CallbackProduct3SourceIndex)(void* aPtr, uint32_t aVersion, uint32_t* aaSourceIndex);
typedef int32_t (*CallbackProduct3SetSourceIndex)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex);
typedef int32_t (*CallbackProduct3SetSourceIndexByName)(void* aPtr, uint32_t aVersion, const char* aaSourceName);
typedef int32_t (*CallbackProduct3SetStartupSourceIndexByName)(void* aPtr, uint32_t aVersion, const char* aaSourceName);
typedef int32_t (*CallbackProduct3StartupSourceIndex)(void* aPtr, uint32_t aVersion, uint32_t* aaSourceIndex);
typedef int32_t (*CallbackProduct3SetStartupSourceIndex)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex);
typedef int32_t (*CallbackProduct3StartupSourceEnabled)(void* aPtr, uint32_t aVersion, uint32_t* aaStartupSourceEnabled);
typedef int32_t (*CallbackProduct3SetStartupSourceEnabled)(void* aPtr, uint32_t aVersion, uint32_t aaStartupSourceEnabled);
typedef int32_t (*CallbackProduct3SourceSystemName)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, char** aaSourceName);
typedef int32_t (*CallbackProduct3SourceName)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, char** aaSourceName);
typedef int32_t (*CallbackProduct3SetSourceName)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, const char* aaSourceName);
typedef int32_t (*CallbackProduct3SourceType)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, char** aaSourceType);
typedef int32_t (*CallbackProduct3SourceVisible)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, uint32_t* aaSourceVisible);
typedef int32_t (*CallbackProduct3SetSourceVisible)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, uint32_t aaSourceVisible);

DllExport THandle DvServiceLinnCoUkProduct3Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkProduct3Destroy(THandle aService);

DllExport void DvServiceLinnCoUkProduct3EnableActionType(THandle aService, CallbackProduct3Type aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionModel(THandle aService, CallbackProduct3Model aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionName(THandle aService, CallbackProduct3Name aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSetName(THandle aService, CallbackProduct3SetName aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionRoom(THandle aService, CallbackProduct3Room aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSetRoom(THandle aService, CallbackProduct3SetRoom aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionStandby(THandle aService, CallbackProduct3Standby aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSetStandby(THandle aService, CallbackProduct3SetStandby aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSourceCount(THandle aService, CallbackProduct3SourceCount aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSourceXml(THandle aService, CallbackProduct3SourceXml aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSourceIndex(THandle aService, CallbackProduct3SourceIndex aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSetSourceIndex(THandle aService, CallbackProduct3SetSourceIndex aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSetSourceIndexByName(THandle aService, CallbackProduct3SetSourceIndexByName aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSetStartupSourceIndexByName(THandle aService, CallbackProduct3SetStartupSourceIndexByName aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionStartupSourceIndex(THandle aService, CallbackProduct3StartupSourceIndex aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSetStartupSourceIndex(THandle aService, CallbackProduct3SetStartupSourceIndex aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionStartupSourceEnabled(THandle aService, CallbackProduct3StartupSourceEnabled aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSetStartupSourceEnabled(THandle aService, CallbackProduct3SetStartupSourceEnabled aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSourceSystemName(THandle aService, CallbackProduct3SourceSystemName aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSourceName(THandle aService, CallbackProduct3SourceName aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSetSourceName(THandle aService, CallbackProduct3SetSourceName aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSourceType(THandle aService, CallbackProduct3SourceType aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSourceVisible(THandle aService, CallbackProduct3SourceVisible aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct3EnableActionSetSourceVisible(THandle aService, CallbackProduct3SetSourceVisible aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkProduct3SetPropertyProductType(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkProduct3GetPropertyProductType(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkProduct3SetPropertyProductModel(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkProduct3GetPropertyProductModel(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkProduct3SetPropertyProductName(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkProduct3GetPropertyProductName(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkProduct3SetPropertyProductRoom(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkProduct3GetPropertyProductRoom(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkProduct3SetPropertyProductStandby(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkProduct3GetPropertyProductStandby(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkProduct3SetPropertyProductSourceIndex(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkProduct3GetPropertyProductSourceIndex(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkProduct3SetPropertyProductSourceCount(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkProduct3GetPropertyProductSourceCount(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkProduct3SetPropertyProductSourceXml(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkProduct3GetPropertyProductSourceXml(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkProduct3SetPropertyStartupSourceIndex(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkProduct3GetPropertyStartupSourceIndex(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkProduct3SetPropertyStartupSourceEnabled(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkProduct3GetPropertyStartupSourceEnabled(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkProduct3SetPropertyProductAnySourceName(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkProduct3GetPropertyProductAnySourceName(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkProduct3SetPropertyProductAnySourceVisible(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkProduct3GetPropertyProductAnySourceVisible(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkProduct3SetPropertyProductAnySourceType(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkProduct3GetPropertyProductAnySourceType(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPRODUCT3_C

