#include <C/DvLinnCoUkPlaylist1.h>
#include <Core/DvLinnCoUkPlaylist1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkPlaylist1C : public DvProviderLinnCoUkPlaylist1
{
public:
    DvProviderLinnCoUkPlaylist1C(DvDevice& aDevice);
    void EnableActionRead(CallbackPlaylist1Read aCallback, void* aPtr);
    void EnableActionReadList(CallbackPlaylist1ReadList aCallback, void* aPtr);
    void EnableActionInsert(CallbackPlaylist1Insert aCallback, void* aPtr);
    void EnableActionDelete(CallbackPlaylist1Delete aCallback, void* aPtr);
    void EnableActionDeleteAll(CallbackPlaylist1DeleteAll aCallback, void* aPtr);
    void EnableActionSetRepeat(CallbackPlaylist1SetRepeat aCallback, void* aPtr);
    void EnableActionRepeat(CallbackPlaylist1Repeat aCallback, void* aPtr);
    void EnableActionSetShuffle(CallbackPlaylist1SetShuffle aCallback, void* aPtr);
    void EnableActionShuffle(CallbackPlaylist1Shuffle aCallback, void* aPtr);
    void EnableActionTracksMax(CallbackPlaylist1TracksMax aCallback, void* aPtr);
    void EnableActionIdArray(CallbackPlaylist1IdArray aCallback, void* aPtr);
    void EnableActionIdArrayChanged(CallbackPlaylist1IdArrayChanged aCallback, void* aPtr);
private:
    void Read(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetaData);
    void ReadList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIdList, IInvocationResponseString& aaMetaDataList);
    void Insert(IInvocationResponse& aResponse, TUint aVersion, TUint aaAfterId, const Brx& aaUri, const Brx& aaMetaData, IInvocationResponseUint& aaNewId);
    void Delete(IInvocationResponse& aResponse, TUint aVersion, TUint aaId);
    void DeleteAll(IInvocationResponse& aResponse, TUint aVersion);
    void SetRepeat(IInvocationResponse& aResponse, TUint aVersion, TBool aaRepeat);
    void Repeat(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaRepeat);
    void SetShuffle(IInvocationResponse& aResponse, TUint aVersion, TBool aaShuffle);
    void Shuffle(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaShuffle);
    void TracksMax(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTracksMax);
    void IdArray(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIdArrayToken, IInvocationResponseBinary& aaIdArray);
    void IdArrayChanged(IInvocationResponse& aResponse, TUint aVersion, TUint aaIdArrayToken, IInvocationResponseBool& aaIdArrayChanged);
private:
    CallbackPlaylist1Read iCallbackRead;
    void* iPtrRead;
    CallbackPlaylist1ReadList iCallbackReadList;
    void* iPtrReadList;
    CallbackPlaylist1Insert iCallbackInsert;
    void* iPtrInsert;
    CallbackPlaylist1Delete iCallbackDelete;
    void* iPtrDelete;
    CallbackPlaylist1DeleteAll iCallbackDeleteAll;
    void* iPtrDeleteAll;
    CallbackPlaylist1SetRepeat iCallbackSetRepeat;
    void* iPtrSetRepeat;
    CallbackPlaylist1Repeat iCallbackRepeat;
    void* iPtrRepeat;
    CallbackPlaylist1SetShuffle iCallbackSetShuffle;
    void* iPtrSetShuffle;
    CallbackPlaylist1Shuffle iCallbackShuffle;
    void* iPtrShuffle;
    CallbackPlaylist1TracksMax iCallbackTracksMax;
    void* iPtrTracksMax;
    CallbackPlaylist1IdArray iCallbackIdArray;
    void* iPtrIdArray;
    CallbackPlaylist1IdArrayChanged iCallbackIdArrayChanged;
    void* iPtrIdArrayChanged;
};

DvProviderLinnCoUkPlaylist1C::DvProviderLinnCoUkPlaylist1C(DvDevice& aDevice)
    : DvProviderLinnCoUkPlaylist1(aDevice)
{
}

void DvProviderLinnCoUkPlaylist1C::EnableActionRead(CallbackPlaylist1Read aCallback, void* aPtr)
{
    iCallbackRead = aCallback;
    iPtrRead = aPtr;
    DvProviderLinnCoUkPlaylist1::EnableActionRead();
}

void DvProviderLinnCoUkPlaylist1C::EnableActionReadList(CallbackPlaylist1ReadList aCallback, void* aPtr)
{
    iCallbackReadList = aCallback;
    iPtrReadList = aPtr;
    DvProviderLinnCoUkPlaylist1::EnableActionReadList();
}

void DvProviderLinnCoUkPlaylist1C::EnableActionInsert(CallbackPlaylist1Insert aCallback, void* aPtr)
{
    iCallbackInsert = aCallback;
    iPtrInsert = aPtr;
    DvProviderLinnCoUkPlaylist1::EnableActionInsert();
}

void DvProviderLinnCoUkPlaylist1C::EnableActionDelete(CallbackPlaylist1Delete aCallback, void* aPtr)
{
    iCallbackDelete = aCallback;
    iPtrDelete = aPtr;
    DvProviderLinnCoUkPlaylist1::EnableActionDelete();
}

void DvProviderLinnCoUkPlaylist1C::EnableActionDeleteAll(CallbackPlaylist1DeleteAll aCallback, void* aPtr)
{
    iCallbackDeleteAll = aCallback;
    iPtrDeleteAll = aPtr;
    DvProviderLinnCoUkPlaylist1::EnableActionDeleteAll();
}

void DvProviderLinnCoUkPlaylist1C::EnableActionSetRepeat(CallbackPlaylist1SetRepeat aCallback, void* aPtr)
{
    iCallbackSetRepeat = aCallback;
    iPtrSetRepeat = aPtr;
    DvProviderLinnCoUkPlaylist1::EnableActionSetRepeat();
}

void DvProviderLinnCoUkPlaylist1C::EnableActionRepeat(CallbackPlaylist1Repeat aCallback, void* aPtr)
{
    iCallbackRepeat = aCallback;
    iPtrRepeat = aPtr;
    DvProviderLinnCoUkPlaylist1::EnableActionRepeat();
}

void DvProviderLinnCoUkPlaylist1C::EnableActionSetShuffle(CallbackPlaylist1SetShuffle aCallback, void* aPtr)
{
    iCallbackSetShuffle = aCallback;
    iPtrSetShuffle = aPtr;
    DvProviderLinnCoUkPlaylist1::EnableActionSetShuffle();
}

void DvProviderLinnCoUkPlaylist1C::EnableActionShuffle(CallbackPlaylist1Shuffle aCallback, void* aPtr)
{
    iCallbackShuffle = aCallback;
    iPtrShuffle = aPtr;
    DvProviderLinnCoUkPlaylist1::EnableActionShuffle();
}

void DvProviderLinnCoUkPlaylist1C::EnableActionTracksMax(CallbackPlaylist1TracksMax aCallback, void* aPtr)
{
    iCallbackTracksMax = aCallback;
    iPtrTracksMax = aPtr;
    DvProviderLinnCoUkPlaylist1::EnableActionTracksMax();
}

void DvProviderLinnCoUkPlaylist1C::EnableActionIdArray(CallbackPlaylist1IdArray aCallback, void* aPtr)
{
    iCallbackIdArray = aCallback;
    iPtrIdArray = aPtr;
    DvProviderLinnCoUkPlaylist1::EnableActionIdArray();
}

void DvProviderLinnCoUkPlaylist1C::EnableActionIdArrayChanged(CallbackPlaylist1IdArrayChanged aCallback, void* aPtr)
{
    iCallbackIdArrayChanged = aCallback;
    iPtrIdArrayChanged = aPtr;
    DvProviderLinnCoUkPlaylist1::EnableActionIdArrayChanged();
}

void DvProviderLinnCoUkPlaylist1C::Read(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetaData)
{
    char* aUri;
    char* aMetaData;
    ASSERT(iCallbackRead != NULL);
    if (0 != iCallbackRead(iPtrRead, aVersion, aaId, &aUri, &aMetaData)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaUri((const TChar*)aUri);
    ZappFreeExternal(aUri);
    aaUri.Write(bufaUri);
    aaUri.WriteFlush();
    Brhz bufaMetaData((const TChar*)aMetaData);
    ZappFreeExternal(aMetaData);
    aaMetaData.Write(bufaMetaData);
    aaMetaData.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkPlaylist1C::ReadList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIdList, IInvocationResponseString& aaMetaDataList)
{
    char* aMetaDataList;
    ASSERT(iCallbackReadList != NULL);
    if (0 != iCallbackReadList(iPtrReadList, aVersion, (const char*)aaIdList.Ptr(), &aMetaDataList)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaMetaDataList((const TChar*)aMetaDataList);
    ZappFreeExternal(aMetaDataList);
    aaMetaDataList.Write(bufaMetaDataList);
    aaMetaDataList.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkPlaylist1C::Insert(IInvocationResponse& aResponse, TUint aVersion, TUint aaAfterId, const Brx& aaUri, const Brx& aaMetaData, IInvocationResponseUint& aaNewId)
{
    uint32_t aNewId;
    ASSERT(iCallbackInsert != NULL);
    if (0 != iCallbackInsert(iPtrInsert, aVersion, aaAfterId, (const char*)aaUri.Ptr(), (const char*)aaMetaData.Ptr(), &aNewId)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaNewId.Write(aNewId);
    aResponse.End();
}

void DvProviderLinnCoUkPlaylist1C::Delete(IInvocationResponse& aResponse, TUint aVersion, TUint aaId)
{
    ASSERT(iCallbackDelete != NULL);
    if (0 != iCallbackDelete(iPtrDelete, aVersion, aaId)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkPlaylist1C::DeleteAll(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackDeleteAll != NULL);
    if (0 != iCallbackDeleteAll(iPtrDeleteAll, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkPlaylist1C::SetRepeat(IInvocationResponse& aResponse, TUint aVersion, TBool aaRepeat)
{
    ASSERT(iCallbackSetRepeat != NULL);
    if (0 != iCallbackSetRepeat(iPtrSetRepeat, aVersion, aaRepeat)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkPlaylist1C::Repeat(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaRepeat)
{
    uint32_t aRepeat;
    ASSERT(iCallbackRepeat != NULL);
    if (0 != iCallbackRepeat(iPtrRepeat, aVersion, &aRepeat)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaRepeat.Write((aRepeat!=0));
    aResponse.End();
}

void DvProviderLinnCoUkPlaylist1C::SetShuffle(IInvocationResponse& aResponse, TUint aVersion, TBool aaShuffle)
{
    ASSERT(iCallbackSetShuffle != NULL);
    if (0 != iCallbackSetShuffle(iPtrSetShuffle, aVersion, aaShuffle)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkPlaylist1C::Shuffle(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaShuffle)
{
    uint32_t aShuffle;
    ASSERT(iCallbackShuffle != NULL);
    if (0 != iCallbackShuffle(iPtrShuffle, aVersion, &aShuffle)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaShuffle.Write((aShuffle!=0));
    aResponse.End();
}

void DvProviderLinnCoUkPlaylist1C::TracksMax(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTracksMax)
{
    uint32_t aTracksMax;
    ASSERT(iCallbackTracksMax != NULL);
    if (0 != iCallbackTracksMax(iPtrTracksMax, aVersion, &aTracksMax)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaTracksMax.Write(aTracksMax);
    aResponse.End();
}

void DvProviderLinnCoUkPlaylist1C::IdArray(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIdArrayToken, IInvocationResponseBinary& aaIdArray)
{
    uint32_t aIdArrayToken;
    char* aIdArray;
    uint32_t aIdArrayLen;
    ASSERT(iCallbackIdArray != NULL);
    if (0 != iCallbackIdArray(iPtrIdArray, aVersion, &aIdArrayToken, &aIdArray, &aIdArrayLen)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaIdArrayToken.Write(aIdArrayToken);
    Brh bufaIdArray;
    bufaIdArray.Set((const TByte*)aIdArray, aIdArrayLen);
    ZappFreeExternal(aIdArray);
    aaIdArray.Write(bufaIdArray);
    aaIdArray.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkPlaylist1C::IdArrayChanged(IInvocationResponse& aResponse, TUint aVersion, TUint aaIdArrayToken, IInvocationResponseBool& aaIdArrayChanged)
{
    uint32_t aIdArrayChanged;
    ASSERT(iCallbackIdArrayChanged != NULL);
    if (0 != iCallbackIdArrayChanged(iPtrIdArrayChanged, aVersion, aaIdArrayToken, &aIdArrayChanged)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaIdArrayChanged.Write((aIdArrayChanged!=0));
    aResponse.End();
}



THandle DvProviderLinnCoUkPlaylist1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkPlaylist1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkPlaylist1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider);
}

void DvProviderLinnCoUkPlaylist1EnableActionRead(THandle aProvider, CallbackPlaylist1Read aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->EnableActionRead(aCallback, aPtr);
}

void DvProviderLinnCoUkPlaylist1EnableActionReadList(THandle aProvider, CallbackPlaylist1ReadList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->EnableActionReadList(aCallback, aPtr);
}

void DvProviderLinnCoUkPlaylist1EnableActionInsert(THandle aProvider, CallbackPlaylist1Insert aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->EnableActionInsert(aCallback, aPtr);
}

void DvProviderLinnCoUkPlaylist1EnableActionDelete(THandle aProvider, CallbackPlaylist1Delete aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->EnableActionDelete(aCallback, aPtr);
}

void DvProviderLinnCoUkPlaylist1EnableActionDeleteAll(THandle aProvider, CallbackPlaylist1DeleteAll aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->EnableActionDeleteAll(aCallback, aPtr);
}

void DvProviderLinnCoUkPlaylist1EnableActionSetRepeat(THandle aProvider, CallbackPlaylist1SetRepeat aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->EnableActionSetRepeat(aCallback, aPtr);
}

void DvProviderLinnCoUkPlaylist1EnableActionRepeat(THandle aProvider, CallbackPlaylist1Repeat aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->EnableActionRepeat(aCallback, aPtr);
}

void DvProviderLinnCoUkPlaylist1EnableActionSetShuffle(THandle aProvider, CallbackPlaylist1SetShuffle aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->EnableActionSetShuffle(aCallback, aPtr);
}

void DvProviderLinnCoUkPlaylist1EnableActionShuffle(THandle aProvider, CallbackPlaylist1Shuffle aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->EnableActionShuffle(aCallback, aPtr);
}

void DvProviderLinnCoUkPlaylist1EnableActionTracksMax(THandle aProvider, CallbackPlaylist1TracksMax aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->EnableActionTracksMax(aCallback, aPtr);
}

void DvProviderLinnCoUkPlaylist1EnableActionIdArray(THandle aProvider, CallbackPlaylist1IdArray aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->EnableActionIdArray(aCallback, aPtr);
}

void DvProviderLinnCoUkPlaylist1EnableActionIdArrayChanged(THandle aProvider, CallbackPlaylist1IdArrayChanged aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->EnableActionIdArrayChanged(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkPlaylist1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->SetPropertyIdArray(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPlaylist1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->GetPropertyIdArray(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

int32_t DvProviderLinnCoUkPlaylist1SetPropertyRepeat(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->SetPropertyRepeat((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPlaylist1GetPropertyRepeat(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->GetPropertyRepeat(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkPlaylist1SetPropertyShuffle(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->SetPropertyShuffle((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPlaylist1GetPropertyShuffle(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->GetPropertyShuffle(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkPlaylist1SetPropertyTracksMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->SetPropertyTracksMax(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkPlaylist1GetPropertyTracksMax(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkPlaylist1C*>(aProvider)->GetPropertyTracksMax(val);
    *aValue = val;
}

