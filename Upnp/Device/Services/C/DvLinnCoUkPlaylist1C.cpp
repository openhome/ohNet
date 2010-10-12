#include <C/DvLinnCoUkPlaylist1.h>
#include <Core/DvLinnCoUkPlaylist1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkPlaylist1C : public DvServiceLinnCoUkPlaylist1
{
public:
    DvServiceLinnCoUkPlaylist1C(DvDevice& aDevice);
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

DvServiceLinnCoUkPlaylist1C::DvServiceLinnCoUkPlaylist1C(DvDevice& aDevice)
    : DvServiceLinnCoUkPlaylist1(aDevice)
{
}

void DvServiceLinnCoUkPlaylist1C::EnableActionRead(CallbackPlaylist1Read aCallback, void* aPtr)
{
    iCallbackRead = aCallback;
    iPtrRead = aPtr;
    DvServiceLinnCoUkPlaylist1::EnableActionRead();
}

void DvServiceLinnCoUkPlaylist1C::EnableActionReadList(CallbackPlaylist1ReadList aCallback, void* aPtr)
{
    iCallbackReadList = aCallback;
    iPtrReadList = aPtr;
    DvServiceLinnCoUkPlaylist1::EnableActionReadList();
}

void DvServiceLinnCoUkPlaylist1C::EnableActionInsert(CallbackPlaylist1Insert aCallback, void* aPtr)
{
    iCallbackInsert = aCallback;
    iPtrInsert = aPtr;
    DvServiceLinnCoUkPlaylist1::EnableActionInsert();
}

void DvServiceLinnCoUkPlaylist1C::EnableActionDelete(CallbackPlaylist1Delete aCallback, void* aPtr)
{
    iCallbackDelete = aCallback;
    iPtrDelete = aPtr;
    DvServiceLinnCoUkPlaylist1::EnableActionDelete();
}

void DvServiceLinnCoUkPlaylist1C::EnableActionDeleteAll(CallbackPlaylist1DeleteAll aCallback, void* aPtr)
{
    iCallbackDeleteAll = aCallback;
    iPtrDeleteAll = aPtr;
    DvServiceLinnCoUkPlaylist1::EnableActionDeleteAll();
}

void DvServiceLinnCoUkPlaylist1C::EnableActionSetRepeat(CallbackPlaylist1SetRepeat aCallback, void* aPtr)
{
    iCallbackSetRepeat = aCallback;
    iPtrSetRepeat = aPtr;
    DvServiceLinnCoUkPlaylist1::EnableActionSetRepeat();
}

void DvServiceLinnCoUkPlaylist1C::EnableActionRepeat(CallbackPlaylist1Repeat aCallback, void* aPtr)
{
    iCallbackRepeat = aCallback;
    iPtrRepeat = aPtr;
    DvServiceLinnCoUkPlaylist1::EnableActionRepeat();
}

void DvServiceLinnCoUkPlaylist1C::EnableActionSetShuffle(CallbackPlaylist1SetShuffle aCallback, void* aPtr)
{
    iCallbackSetShuffle = aCallback;
    iPtrSetShuffle = aPtr;
    DvServiceLinnCoUkPlaylist1::EnableActionSetShuffle();
}

void DvServiceLinnCoUkPlaylist1C::EnableActionShuffle(CallbackPlaylist1Shuffle aCallback, void* aPtr)
{
    iCallbackShuffle = aCallback;
    iPtrShuffle = aPtr;
    DvServiceLinnCoUkPlaylist1::EnableActionShuffle();
}

void DvServiceLinnCoUkPlaylist1C::EnableActionTracksMax(CallbackPlaylist1TracksMax aCallback, void* aPtr)
{
    iCallbackTracksMax = aCallback;
    iPtrTracksMax = aPtr;
    DvServiceLinnCoUkPlaylist1::EnableActionTracksMax();
}

void DvServiceLinnCoUkPlaylist1C::EnableActionIdArray(CallbackPlaylist1IdArray aCallback, void* aPtr)
{
    iCallbackIdArray = aCallback;
    iPtrIdArray = aPtr;
    DvServiceLinnCoUkPlaylist1::EnableActionIdArray();
}

void DvServiceLinnCoUkPlaylist1C::EnableActionIdArrayChanged(CallbackPlaylist1IdArrayChanged aCallback, void* aPtr)
{
    iCallbackIdArrayChanged = aCallback;
    iPtrIdArrayChanged = aPtr;
    DvServiceLinnCoUkPlaylist1::EnableActionIdArrayChanged();
}

void DvServiceLinnCoUkPlaylist1C::Read(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetaData)
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

void DvServiceLinnCoUkPlaylist1C::ReadList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIdList, IInvocationResponseString& aaMetaDataList)
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

void DvServiceLinnCoUkPlaylist1C::Insert(IInvocationResponse& aResponse, TUint aVersion, TUint aaAfterId, const Brx& aaUri, const Brx& aaMetaData, IInvocationResponseUint& aaNewId)
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

void DvServiceLinnCoUkPlaylist1C::Delete(IInvocationResponse& aResponse, TUint aVersion, TUint aaId)
{
    ASSERT(iCallbackDelete != NULL);
    if (0 != iCallbackDelete(iPtrDelete, aVersion, aaId)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkPlaylist1C::DeleteAll(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackDeleteAll != NULL);
    if (0 != iCallbackDeleteAll(iPtrDeleteAll, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkPlaylist1C::SetRepeat(IInvocationResponse& aResponse, TUint aVersion, TBool aaRepeat)
{
    ASSERT(iCallbackSetRepeat != NULL);
    if (0 != iCallbackSetRepeat(iPtrSetRepeat, aVersion, aaRepeat)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkPlaylist1C::Repeat(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaRepeat)
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

void DvServiceLinnCoUkPlaylist1C::SetShuffle(IInvocationResponse& aResponse, TUint aVersion, TBool aaShuffle)
{
    ASSERT(iCallbackSetShuffle != NULL);
    if (0 != iCallbackSetShuffle(iPtrSetShuffle, aVersion, aaShuffle)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkPlaylist1C::Shuffle(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaShuffle)
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

void DvServiceLinnCoUkPlaylist1C::TracksMax(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTracksMax)
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

void DvServiceLinnCoUkPlaylist1C::IdArray(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIdArrayToken, IInvocationResponseBinary& aaIdArray)
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

void DvServiceLinnCoUkPlaylist1C::IdArrayChanged(IInvocationResponse& aResponse, TUint aVersion, TUint aaIdArrayToken, IInvocationResponseBool& aaIdArrayChanged)
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



THandle DvServiceLinnCoUkPlaylist1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkPlaylist1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkPlaylist1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService);
}

void DvServiceLinnCoUkPlaylist1EnableActionRead(THandle aService, CallbackPlaylist1Read aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->EnableActionRead(aCallback, aPtr);
}

void DvServiceLinnCoUkPlaylist1EnableActionReadList(THandle aService, CallbackPlaylist1ReadList aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->EnableActionReadList(aCallback, aPtr);
}

void DvServiceLinnCoUkPlaylist1EnableActionInsert(THandle aService, CallbackPlaylist1Insert aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->EnableActionInsert(aCallback, aPtr);
}

void DvServiceLinnCoUkPlaylist1EnableActionDelete(THandle aService, CallbackPlaylist1Delete aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->EnableActionDelete(aCallback, aPtr);
}

void DvServiceLinnCoUkPlaylist1EnableActionDeleteAll(THandle aService, CallbackPlaylist1DeleteAll aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->EnableActionDeleteAll(aCallback, aPtr);
}

void DvServiceLinnCoUkPlaylist1EnableActionSetRepeat(THandle aService, CallbackPlaylist1SetRepeat aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->EnableActionSetRepeat(aCallback, aPtr);
}

void DvServiceLinnCoUkPlaylist1EnableActionRepeat(THandle aService, CallbackPlaylist1Repeat aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->EnableActionRepeat(aCallback, aPtr);
}

void DvServiceLinnCoUkPlaylist1EnableActionSetShuffle(THandle aService, CallbackPlaylist1SetShuffle aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->EnableActionSetShuffle(aCallback, aPtr);
}

void DvServiceLinnCoUkPlaylist1EnableActionShuffle(THandle aService, CallbackPlaylist1Shuffle aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->EnableActionShuffle(aCallback, aPtr);
}

void DvServiceLinnCoUkPlaylist1EnableActionTracksMax(THandle aService, CallbackPlaylist1TracksMax aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->EnableActionTracksMax(aCallback, aPtr);
}

void DvServiceLinnCoUkPlaylist1EnableActionIdArray(THandle aService, CallbackPlaylist1IdArray aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->EnableActionIdArray(aCallback, aPtr);
}

void DvServiceLinnCoUkPlaylist1EnableActionIdArrayChanged(THandle aService, CallbackPlaylist1IdArrayChanged aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->EnableActionIdArrayChanged(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkPlaylist1SetPropertyIdArray(THandle aService, const char* aValue, uint32_t aValueLen)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->SetPropertyIdArray(buf);
    return 0;
}

void DvServiceLinnCoUkPlaylist1GetPropertyIdArray(THandle aService, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->GetPropertyIdArray(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

int32_t DvServiceLinnCoUkPlaylist1SetPropertyRepeat(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->SetPropertyRepeat((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkPlaylist1GetPropertyRepeat(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->GetPropertyRepeat(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkPlaylist1SetPropertyShuffle(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->SetPropertyShuffle((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkPlaylist1GetPropertyShuffle(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->GetPropertyShuffle(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkPlaylist1SetPropertyTracksMax(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->SetPropertyTracksMax(aValue);
    return 0;
}

void DvServiceLinnCoUkPlaylist1GetPropertyTracksMax(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkPlaylist1C*>(aService)->GetPropertyTracksMax(val);
    *aValue = val;
}

