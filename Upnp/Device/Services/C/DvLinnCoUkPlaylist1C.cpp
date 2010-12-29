#include "DvLinnCoUkPlaylist1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderLinnCoUkPlaylist1C : public DvProvider
{
public:
    DvProviderLinnCoUkPlaylist1C(DvDeviceC aDevice);
    TBool SetPropertyIdArray(const Brx& aValue);
    void GetPropertyIdArray(Brh& aValue);
    TBool SetPropertyRepeat(TBool aValue);
    void GetPropertyRepeat(TBool& aValue);
    TBool SetPropertyShuffle(TBool aValue);
    void GetPropertyShuffle(TBool& aValue);
    TBool SetPropertyTracksMax(TUint aValue);
    void GetPropertyTracksMax(TUint& aValue);
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
    void DoRead(IDviInvocation& aInvocation, TUint aVersion);
    void DoReadList(IDviInvocation& aInvocation, TUint aVersion);
    void DoInsert(IDviInvocation& aInvocation, TUint aVersion);
    void DoDelete(IDviInvocation& aInvocation, TUint aVersion);
    void DoDeleteAll(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRepeat(IDviInvocation& aInvocation, TUint aVersion);
    void DoRepeat(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetShuffle(IDviInvocation& aInvocation, TUint aVersion);
    void DoShuffle(IDviInvocation& aInvocation, TUint aVersion);
    void DoTracksMax(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdArray(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion);
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
    PropertyBinary* iPropertyIdArray;
    PropertyBool* iPropertyRepeat;
    PropertyBool* iPropertyShuffle;
    PropertyUint* iPropertyTracksMax;
};

DvProviderLinnCoUkPlaylist1C::DvProviderLinnCoUkPlaylist1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Playlist", 1)
{
    
    iPropertyIdArray = new PropertyBinary(new ParameterBinary("IdArray"));
    iService->AddProperty(iPropertyIdArray); // passes ownership
    iPropertyRepeat = new PropertyBool(new ParameterBool("Repeat"));
    iService->AddProperty(iPropertyRepeat); // passes ownership
    iPropertyShuffle = new PropertyBool(new ParameterBool("Shuffle"));
    iService->AddProperty(iPropertyShuffle); // passes ownership
    iPropertyTracksMax = new PropertyUint(new ParameterUint("TracksMax"));
    iService->AddProperty(iPropertyTracksMax); // passes ownership
}

TBool DvProviderLinnCoUkPlaylist1C::SetPropertyIdArray(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvProviderLinnCoUkPlaylist1C::GetPropertyIdArray(Brh& aValue)
{
    aValue.Set(iPropertyIdArray->Value());
}

TBool DvProviderLinnCoUkPlaylist1C::SetPropertyRepeat(TBool aValue)
{
    return SetPropertyBool(*iPropertyRepeat, aValue);
}

void DvProviderLinnCoUkPlaylist1C::GetPropertyRepeat(TBool& aValue)
{
    aValue = iPropertyRepeat->Value();
}

TBool DvProviderLinnCoUkPlaylist1C::SetPropertyShuffle(TBool aValue)
{
    return SetPropertyBool(*iPropertyShuffle, aValue);
}

void DvProviderLinnCoUkPlaylist1C::GetPropertyShuffle(TBool& aValue)
{
    aValue = iPropertyShuffle->Value();
}

TBool DvProviderLinnCoUkPlaylist1C::SetPropertyTracksMax(TUint aValue)
{
    return SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvProviderLinnCoUkPlaylist1C::GetPropertyTracksMax(TUint& aValue)
{
    aValue = iPropertyTracksMax->Value();
}

void DvProviderLinnCoUkPlaylist1C::EnableActionRead(CallbackPlaylist1Read aCallback, void* aPtr)
{
    iCallbackRead = aCallback;
    iPtrRead = aPtr;
    Zapp::Action* action = new Zapp::Action("Read");
    action->AddInputParameter(new ParameterUint("aId"));
    action->AddOutputParameter(new ParameterString("aUri"));
    action->AddOutputParameter(new ParameterString("aMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1C::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1C::EnableActionReadList(CallbackPlaylist1ReadList aCallback, void* aPtr)
{
    iCallbackReadList = aCallback;
    iPtrReadList = aPtr;
    Zapp::Action* action = new Zapp::Action("ReadList");
    action->AddInputParameter(new ParameterString("aIdList"));
    action->AddOutputParameter(new ParameterString("aMetaDataList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1C::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1C::EnableActionInsert(CallbackPlaylist1Insert aCallback, void* aPtr)
{
    iCallbackInsert = aCallback;
    iPtrInsert = aPtr;
    Zapp::Action* action = new Zapp::Action("Insert");
    action->AddInputParameter(new ParameterUint("aAfterId"));
    action->AddInputParameter(new ParameterString("aUri"));
    action->AddInputParameter(new ParameterString("aMetaData"));
    action->AddOutputParameter(new ParameterUint("aNewId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1C::DoInsert);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1C::EnableActionDelete(CallbackPlaylist1Delete aCallback, void* aPtr)
{
    iCallbackDelete = aCallback;
    iPtrDelete = aPtr;
    Zapp::Action* action = new Zapp::Action("Delete");
    action->AddInputParameter(new ParameterUint("aId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1C::DoDelete);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1C::EnableActionDeleteAll(CallbackPlaylist1DeleteAll aCallback, void* aPtr)
{
    iCallbackDeleteAll = aCallback;
    iPtrDeleteAll = aPtr;
    Zapp::Action* action = new Zapp::Action("DeleteAll");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1C::DoDeleteAll);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1C::EnableActionSetRepeat(CallbackPlaylist1SetRepeat aCallback, void* aPtr)
{
    iCallbackSetRepeat = aCallback;
    iPtrSetRepeat = aPtr;
    Zapp::Action* action = new Zapp::Action("SetRepeat");
    action->AddInputParameter(new ParameterRelated("aRepeat", *iPropertyRepeat));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1C::DoSetRepeat);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1C::EnableActionRepeat(CallbackPlaylist1Repeat aCallback, void* aPtr)
{
    iCallbackRepeat = aCallback;
    iPtrRepeat = aPtr;
    Zapp::Action* action = new Zapp::Action("Repeat");
    action->AddOutputParameter(new ParameterRelated("aRepeat", *iPropertyRepeat));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1C::DoRepeat);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1C::EnableActionSetShuffle(CallbackPlaylist1SetShuffle aCallback, void* aPtr)
{
    iCallbackSetShuffle = aCallback;
    iPtrSetShuffle = aPtr;
    Zapp::Action* action = new Zapp::Action("SetShuffle");
    action->AddInputParameter(new ParameterRelated("aShuffle", *iPropertyShuffle));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1C::DoSetShuffle);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1C::EnableActionShuffle(CallbackPlaylist1Shuffle aCallback, void* aPtr)
{
    iCallbackShuffle = aCallback;
    iPtrShuffle = aPtr;
    Zapp::Action* action = new Zapp::Action("Shuffle");
    action->AddOutputParameter(new ParameterRelated("aShuffle", *iPropertyShuffle));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1C::DoShuffle);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1C::EnableActionTracksMax(CallbackPlaylist1TracksMax aCallback, void* aPtr)
{
    iCallbackTracksMax = aCallback;
    iPtrTracksMax = aPtr;
    Zapp::Action* action = new Zapp::Action("TracksMax");
    action->AddOutputParameter(new ParameterRelated("aTracksMax", *iPropertyTracksMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1C::DoTracksMax);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1C::EnableActionIdArray(CallbackPlaylist1IdArray aCallback, void* aPtr)
{
    iCallbackIdArray = aCallback;
    iPtrIdArray = aPtr;
    Zapp::Action* action = new Zapp::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterRelated("aIdArray", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1C::DoIdArray);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1C::EnableActionIdArrayChanged(CallbackPlaylist1IdArrayChanged aCallback, void* aPtr)
{
    iCallbackIdArrayChanged = aCallback;
    iPtrIdArrayChanged = aPtr;
    Zapp::Action* action = new Zapp::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterBool("aIdArrayChanged"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1C::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1C::DoRead(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aUri;
    char* aMetaData;
    ASSERT(iCallbackRead != NULL);
    if (0 != iCallbackRead(iPtrRead, aVersion, aId, &aUri, &aMetaData)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaUri(aInvocation, "aUri");
    InvocationResponseString respaMetaData(aInvocation, "aMetaData");
    resp.Start();
    Brhz bufaUri((const TChar*)aUri);
    ZappFreeExternal(aUri);
    respaUri.Write(bufaUri);
    respaUri.WriteFlush();
    Brhz bufaMetaData((const TChar*)aMetaData);
    ZappFreeExternal(aMetaData);
    respaMetaData.Write(bufaMetaData);
    respaMetaData.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkPlaylist1C::DoReadList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aIdList;
    aInvocation.InvocationReadString("aIdList", aIdList);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aMetaDataList;
    ASSERT(iCallbackReadList != NULL);
    if (0 != iCallbackReadList(iPtrReadList, aVersion, (const char*)aIdList.Ptr(), &aMetaDataList)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaMetaDataList(aInvocation, "aMetaDataList");
    resp.Start();
    Brhz bufaMetaDataList((const TChar*)aMetaDataList);
    ZappFreeExternal(aMetaDataList);
    respaMetaDataList.Write(bufaMetaDataList);
    respaMetaDataList.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkPlaylist1C::DoInsert(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aAfterId = aInvocation.InvocationReadUint("aAfterId");
    Brhz aUri;
    aInvocation.InvocationReadString("aUri", aUri);
    Brhz aMetaData;
    aInvocation.InvocationReadString("aMetaData", aMetaData);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aNewId;
    ASSERT(iCallbackInsert != NULL);
    if (0 != iCallbackInsert(iPtrInsert, aVersion, aAfterId, (const char*)aUri.Ptr(), (const char*)aMetaData.Ptr(), &aNewId)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaNewId(aInvocation, "aNewId");
    resp.Start();
    respaNewId.Write(aNewId);
    resp.End();
}

void DvProviderLinnCoUkPlaylist1C::DoDelete(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackDelete != NULL);
    if (0 != iCallbackDelete(iPtrDelete, aVersion, aId)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkPlaylist1C::DoDeleteAll(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackDeleteAll != NULL);
    if (0 != iCallbackDeleteAll(iPtrDeleteAll, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkPlaylist1C::DoSetRepeat(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aRepeat = aInvocation.InvocationReadBool("aRepeat");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetRepeat != NULL);
    if (0 != iCallbackSetRepeat(iPtrSetRepeat, aVersion, aRepeat)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkPlaylist1C::DoRepeat(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aRepeat;
    ASSERT(iCallbackRepeat != NULL);
    if (0 != iCallbackRepeat(iPtrRepeat, aVersion, &aRepeat)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaRepeat(aInvocation, "aRepeat");
    resp.Start();
    respaRepeat.Write((aRepeat!=0));
    resp.End();
}

void DvProviderLinnCoUkPlaylist1C::DoSetShuffle(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aShuffle = aInvocation.InvocationReadBool("aShuffle");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetShuffle != NULL);
    if (0 != iCallbackSetShuffle(iPtrSetShuffle, aVersion, aShuffle)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkPlaylist1C::DoShuffle(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aShuffle;
    ASSERT(iCallbackShuffle != NULL);
    if (0 != iCallbackShuffle(iPtrShuffle, aVersion, &aShuffle)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaShuffle(aInvocation, "aShuffle");
    resp.Start();
    respaShuffle.Write((aShuffle!=0));
    resp.End();
}

void DvProviderLinnCoUkPlaylist1C::DoTracksMax(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aTracksMax;
    ASSERT(iCallbackTracksMax != NULL);
    if (0 != iCallbackTracksMax(iPtrTracksMax, aVersion, &aTracksMax)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaTracksMax(aInvocation, "aTracksMax");
    resp.Start();
    respaTracksMax.Write(aTracksMax);
    resp.End();
}

void DvProviderLinnCoUkPlaylist1C::DoIdArray(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aIdArrayToken;
    char* aIdArray;
    uint32_t aIdArrayLen;
    ASSERT(iCallbackIdArray != NULL);
    if (0 != iCallbackIdArray(iPtrIdArray, aVersion, &aIdArrayToken, &aIdArray, &aIdArrayLen)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaIdArrayToken(aInvocation, "aIdArrayToken");
    InvocationResponseBinary respaIdArray(aInvocation, "aIdArray");
    resp.Start();
    respaIdArrayToken.Write(aIdArrayToken);
    Brh bufaIdArray;
    bufaIdArray.Set((const TByte*)aIdArray, aIdArrayLen);
    ZappFreeExternal(aIdArray);
    respaIdArray.Write(bufaIdArray);
    respaIdArray.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkPlaylist1C::DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIdArrayToken = aInvocation.InvocationReadUint("aIdArrayToken");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aIdArrayChanged;
    ASSERT(iCallbackIdArrayChanged != NULL);
    if (0 != iCallbackIdArrayChanged(iPtrIdArrayChanged, aVersion, aIdArrayToken, &aIdArrayChanged)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaIdArrayChanged(aInvocation, "aIdArrayChanged");
    resp.Start();
    respaIdArrayChanged.Write((aIdArrayChanged!=0));
    resp.End();
}



THandle DvProviderLinnCoUkPlaylist1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkPlaylist1C(aDevice);
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

