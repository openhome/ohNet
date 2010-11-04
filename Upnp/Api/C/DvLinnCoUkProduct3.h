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

DllExport THandle DvProviderLinnCoUkProduct3Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkProduct3Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkProduct3EnableActionType(THandle aProvider, CallbackProduct3Type aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionModel(THandle aProvider, CallbackProduct3Model aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionName(THandle aProvider, CallbackProduct3Name aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSetName(THandle aProvider, CallbackProduct3SetName aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionRoom(THandle aProvider, CallbackProduct3Room aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSetRoom(THandle aProvider, CallbackProduct3SetRoom aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionStandby(THandle aProvider, CallbackProduct3Standby aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSetStandby(THandle aProvider, CallbackProduct3SetStandby aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceCount(THandle aProvider, CallbackProduct3SourceCount aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceXml(THandle aProvider, CallbackProduct3SourceXml aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceIndex(THandle aProvider, CallbackProduct3SourceIndex aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSetSourceIndex(THandle aProvider, CallbackProduct3SetSourceIndex aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSetSourceIndexByName(THandle aProvider, CallbackProduct3SetSourceIndexByName aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndexByName(THandle aProvider, CallbackProduct3SetStartupSourceIndexByName aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionStartupSourceIndex(THandle aProvider, CallbackProduct3StartupSourceIndex aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndex(THandle aProvider, CallbackProduct3SetStartupSourceIndex aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionStartupSourceEnabled(THandle aProvider, CallbackProduct3StartupSourceEnabled aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceEnabled(THandle aProvider, CallbackProduct3SetStartupSourceEnabled aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceSystemName(THandle aProvider, CallbackProduct3SourceSystemName aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceName(THandle aProvider, CallbackProduct3SourceName aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSetSourceName(THandle aProvider, CallbackProduct3SetSourceName aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceType(THandle aProvider, CallbackProduct3SourceType aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceVisible(THandle aProvider, CallbackProduct3SourceVisible aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct3EnableActionSetSourceVisible(THandle aProvider, CallbackProduct3SetSourceVisible aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductType(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductType(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductModel(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductModel(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductName(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductName(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductRoom(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductRoom(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductStandby(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductStandby(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductSourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductSourceIndex(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductSourceCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductSourceCount(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductSourceXml(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductSourceXml(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyStartupSourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct3GetPropertyStartupSourceIndex(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyStartupSourceEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct3GetPropertyStartupSourceEnabled(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductAnySourceName(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceName(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductAnySourceVisible(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceVisible(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductAnySourceType(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceType(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPRODUCT3_C

