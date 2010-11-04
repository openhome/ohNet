#ifndef HEADER_DVLINNCOUKPLAYLIST1_C
#define HEADER_DVLINNCOUKPLAYLIST1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackPlaylist1Read)(void* aPtr, uint32_t aVersion, uint32_t aaId, char** aaUri, char** aaMetaData);
typedef int32_t (*CallbackPlaylist1ReadList)(void* aPtr, uint32_t aVersion, const char* aaIdList, char** aaMetaDataList);
typedef int32_t (*CallbackPlaylist1Insert)(void* aPtr, uint32_t aVersion, uint32_t aaAfterId, const char* aaUri, const char* aaMetaData, uint32_t* aaNewId);
typedef int32_t (*CallbackPlaylist1Delete)(void* aPtr, uint32_t aVersion, uint32_t aaId);
typedef int32_t (*CallbackPlaylist1DeleteAll)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackPlaylist1SetRepeat)(void* aPtr, uint32_t aVersion, uint32_t aaRepeat);
typedef int32_t (*CallbackPlaylist1Repeat)(void* aPtr, uint32_t aVersion, uint32_t* aaRepeat);
typedef int32_t (*CallbackPlaylist1SetShuffle)(void* aPtr, uint32_t aVersion, uint32_t aaShuffle);
typedef int32_t (*CallbackPlaylist1Shuffle)(void* aPtr, uint32_t aVersion, uint32_t* aaShuffle);
typedef int32_t (*CallbackPlaylist1TracksMax)(void* aPtr, uint32_t aVersion, uint32_t* aaTracksMax);
typedef int32_t (*CallbackPlaylist1IdArray)(void* aPtr, uint32_t aVersion, uint32_t* aaIdArrayToken, char** aaIdArray, uint32_t* aaIdArrayLen);
typedef int32_t (*CallbackPlaylist1IdArrayChanged)(void* aPtr, uint32_t aVersion, uint32_t aaIdArrayToken, uint32_t* aaIdArrayChanged);

DllExport THandle DvProviderLinnCoUkPlaylist1Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkPlaylist1Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkPlaylist1EnableActionRead(THandle aProvider, CallbackPlaylist1Read aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPlaylist1EnableActionReadList(THandle aProvider, CallbackPlaylist1ReadList aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPlaylist1EnableActionInsert(THandle aProvider, CallbackPlaylist1Insert aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPlaylist1EnableActionDelete(THandle aProvider, CallbackPlaylist1Delete aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPlaylist1EnableActionDeleteAll(THandle aProvider, CallbackPlaylist1DeleteAll aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPlaylist1EnableActionSetRepeat(THandle aProvider, CallbackPlaylist1SetRepeat aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPlaylist1EnableActionRepeat(THandle aProvider, CallbackPlaylist1Repeat aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPlaylist1EnableActionSetShuffle(THandle aProvider, CallbackPlaylist1SetShuffle aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPlaylist1EnableActionShuffle(THandle aProvider, CallbackPlaylist1Shuffle aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPlaylist1EnableActionTracksMax(THandle aProvider, CallbackPlaylist1TracksMax aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPlaylist1EnableActionIdArray(THandle aProvider, CallbackPlaylist1IdArray aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPlaylist1EnableActionIdArrayChanged(THandle aProvider, CallbackPlaylist1IdArrayChanged aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkPlaylist1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkPlaylist1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen);
DllExport int32_t DvProviderLinnCoUkPlaylist1SetPropertyRepeat(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkPlaylist1GetPropertyRepeat(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkPlaylist1SetPropertyShuffle(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkPlaylist1GetPropertyShuffle(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkPlaylist1SetPropertyTracksMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkPlaylist1GetPropertyTracksMax(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPLAYLIST1_C

