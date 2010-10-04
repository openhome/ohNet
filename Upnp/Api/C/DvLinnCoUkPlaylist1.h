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

DllExport THandle DvServiceLinnCoUkPlaylist1Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkPlaylist1Destroy(THandle aService);

DllExport void DvServiceLinnCoUkPlaylist1EnableActionRead(THandle aService, CallbackPlaylist1Read aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPlaylist1EnableActionReadList(THandle aService, CallbackPlaylist1ReadList aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPlaylist1EnableActionInsert(THandle aService, CallbackPlaylist1Insert aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPlaylist1EnableActionDelete(THandle aService, CallbackPlaylist1Delete aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPlaylist1EnableActionDeleteAll(THandle aService, CallbackPlaylist1DeleteAll aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPlaylist1EnableActionSetRepeat(THandle aService, CallbackPlaylist1SetRepeat aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPlaylist1EnableActionRepeat(THandle aService, CallbackPlaylist1Repeat aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPlaylist1EnableActionSetShuffle(THandle aService, CallbackPlaylist1SetShuffle aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPlaylist1EnableActionShuffle(THandle aService, CallbackPlaylist1Shuffle aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPlaylist1EnableActionTracksMax(THandle aService, CallbackPlaylist1TracksMax aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPlaylist1EnableActionIdArray(THandle aService, CallbackPlaylist1IdArray aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPlaylist1EnableActionIdArrayChanged(THandle aService, CallbackPlaylist1IdArrayChanged aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkPlaylist1SetPropertyIdArray(THandle aService, const char* aValue, uint32_t aValueLen);
DllExport void DvServiceLinnCoUkPlaylist1GetPropertyIdArray(THandle aService, char** aValue, uint32_t* aValueLen);
DllExport int32_t DvServiceLinnCoUkPlaylist1SetPropertyRepeat(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkPlaylist1GetPropertyRepeat(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkPlaylist1SetPropertyShuffle(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkPlaylist1GetPropertyShuffle(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkPlaylist1SetPropertyTracksMax(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkPlaylist1GetPropertyTracksMax(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPLAYLIST1_C

