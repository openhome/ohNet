#include <Std/DvLinnCoUkPlaylist1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

bool DvProviderLinnCoUkPlaylist1Cpp::SetPropertyIdArray(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyBinary(*iPropertyIdArray, buf);
}

void DvProviderLinnCoUkPlaylist1Cpp::GetPropertyIdArray(std::string& aValue)
{
    const Brx& val = iPropertyIdArray->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkPlaylist1Cpp::SetPropertyRepeat(bool aValue)
{
    return SetPropertyBool(*iPropertyRepeat, aValue);
}

void DvProviderLinnCoUkPlaylist1Cpp::GetPropertyRepeat(bool& aValue)
{
    aValue = iPropertyRepeat->Value();
}

bool DvProviderLinnCoUkPlaylist1Cpp::SetPropertyShuffle(bool aValue)
{
    return SetPropertyBool(*iPropertyShuffle, aValue);
}

void DvProviderLinnCoUkPlaylist1Cpp::GetPropertyShuffle(bool& aValue)
{
    aValue = iPropertyShuffle->Value();
}

bool DvProviderLinnCoUkPlaylist1Cpp::SetPropertyTracksMax(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvProviderLinnCoUkPlaylist1Cpp::GetPropertyTracksMax(uint32_t& aValue)
{
    aValue = iPropertyTracksMax->Value();
}

DvProviderLinnCoUkPlaylist1Cpp::DvProviderLinnCoUkPlaylist1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Playlist", 1)
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

void DvProviderLinnCoUkPlaylist1Cpp::EnableActionRead()
{
    Zapp::Action* action = new Zapp::Action("Read");
    action->AddInputParameter(new ParameterUint("aId"));
    action->AddOutputParameter(new ParameterString("aUri"));
    action->AddOutputParameter(new ParameterString("aMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1Cpp::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1Cpp::EnableActionReadList()
{
    Zapp::Action* action = new Zapp::Action("ReadList");
    action->AddInputParameter(new ParameterString("aIdList"));
    action->AddOutputParameter(new ParameterString("aMetaDataList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1Cpp::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1Cpp::EnableActionInsert()
{
    Zapp::Action* action = new Zapp::Action("Insert");
    action->AddInputParameter(new ParameterUint("aAfterId"));
    action->AddInputParameter(new ParameterString("aUri"));
    action->AddInputParameter(new ParameterString("aMetaData"));
    action->AddOutputParameter(new ParameterUint("aNewId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1Cpp::DoInsert);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1Cpp::EnableActionDelete()
{
    Zapp::Action* action = new Zapp::Action("Delete");
    action->AddInputParameter(new ParameterUint("aId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1Cpp::DoDelete);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1Cpp::EnableActionDeleteAll()
{
    Zapp::Action* action = new Zapp::Action("DeleteAll");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1Cpp::DoDeleteAll);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1Cpp::EnableActionSetRepeat()
{
    Zapp::Action* action = new Zapp::Action("SetRepeat");
    action->AddInputParameter(new ParameterRelated("aRepeat", *iPropertyRepeat));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1Cpp::DoSetRepeat);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1Cpp::EnableActionRepeat()
{
    Zapp::Action* action = new Zapp::Action("Repeat");
    action->AddOutputParameter(new ParameterRelated("aRepeat", *iPropertyRepeat));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1Cpp::DoRepeat);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1Cpp::EnableActionSetShuffle()
{
    Zapp::Action* action = new Zapp::Action("SetShuffle");
    action->AddInputParameter(new ParameterRelated("aShuffle", *iPropertyShuffle));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1Cpp::DoSetShuffle);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1Cpp::EnableActionShuffle()
{
    Zapp::Action* action = new Zapp::Action("Shuffle");
    action->AddOutputParameter(new ParameterRelated("aShuffle", *iPropertyShuffle));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1Cpp::DoShuffle);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1Cpp::EnableActionTracksMax()
{
    Zapp::Action* action = new Zapp::Action("TracksMax");
    action->AddOutputParameter(new ParameterRelated("aTracksMax", *iPropertyTracksMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1Cpp::DoTracksMax);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1Cpp::EnableActionIdArray()
{
    Zapp::Action* action = new Zapp::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterRelated("aIdArray", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1Cpp::DoIdArray);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1Cpp::EnableActionIdArrayChanged()
{
    Zapp::Action* action = new Zapp::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterBool("aIdArrayChanged"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1Cpp::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1Cpp::DoRead(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    std::string respaUri;
    std::string respaMetaData;
    Read(aVersion, aId, respaUri, respaMetaData);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraUri(aInvocation, "aUri");
    Brn buf_aUri((const TByte*)respaUri.c_str(), (TUint)respaUri.length());
    respWriteraUri.Write(buf_aUri);
    aInvocation.InvocationWriteStringEnd("aUri");
    InvocationResponseString respWriteraMetaData(aInvocation, "aMetaData");
    Brn buf_aMetaData((const TByte*)respaMetaData.c_str(), (TUint)respaMetaData.length());
    respWriteraMetaData.Write(buf_aMetaData);
    aInvocation.InvocationWriteStringEnd("aMetaData");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPlaylist1Cpp::DoReadList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aIdList;
    aInvocation.InvocationReadString("aIdList", buf_aIdList);
    std::string aIdList((const char*)buf_aIdList.Ptr(), buf_aIdList.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respaMetaDataList;
    ReadList(aVersion, aIdList, respaMetaDataList);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraMetaDataList(aInvocation, "aMetaDataList");
    Brn buf_aMetaDataList((const TByte*)respaMetaDataList.c_str(), (TUint)respaMetaDataList.length());
    respWriteraMetaDataList.Write(buf_aMetaDataList);
    aInvocation.InvocationWriteStringEnd("aMetaDataList");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPlaylist1Cpp::DoInsert(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aAfterId = aInvocation.InvocationReadUint("aAfterId");
    Brhz buf_aUri;
    aInvocation.InvocationReadString("aUri", buf_aUri);
    std::string aUri((const char*)buf_aUri.Ptr(), buf_aUri.Bytes());
    Brhz buf_aMetaData;
    aInvocation.InvocationReadString("aMetaData", buf_aMetaData);
    std::string aMetaData((const char*)buf_aMetaData.Ptr(), buf_aMetaData.Bytes());
    aInvocation.InvocationReadEnd();
    uint32_t respaNewId;
    Insert(aVersion, aAfterId, aUri, aMetaData, respaNewId);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraNewId(aInvocation, "aNewId");
    respWriteraNewId.Write(respaNewId);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPlaylist1Cpp::DoDelete(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    Delete(aVersion, aId);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPlaylist1Cpp::DoDeleteAll(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DeleteAll(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPlaylist1Cpp::DoSetRepeat(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aRepeat = aInvocation.InvocationReadBool("aRepeat");
    aInvocation.InvocationReadEnd();
    SetRepeat(aVersion, aRepeat);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPlaylist1Cpp::DoRepeat(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaRepeat;
    Repeat(aVersion, respaRepeat);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraRepeat(aInvocation, "aRepeat");
    respWriteraRepeat.Write(respaRepeat);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPlaylist1Cpp::DoSetShuffle(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aShuffle = aInvocation.InvocationReadBool("aShuffle");
    aInvocation.InvocationReadEnd();
    SetShuffle(aVersion, aShuffle);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPlaylist1Cpp::DoShuffle(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaShuffle;
    Shuffle(aVersion, respaShuffle);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraShuffle(aInvocation, "aShuffle");
    respWriteraShuffle.Write(respaShuffle);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPlaylist1Cpp::DoTracksMax(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaTracksMax;
    TracksMax(aVersion, respaTracksMax);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraTracksMax(aInvocation, "aTracksMax");
    respWriteraTracksMax.Write(respaTracksMax);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPlaylist1Cpp::DoIdArray(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaIdArrayToken;
    std::string respaIdArray;
    IdArray(aVersion, respaIdArrayToken, respaIdArray);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraIdArrayToken(aInvocation, "aIdArrayToken");
    respWriteraIdArrayToken.Write(respaIdArrayToken);
    InvocationResponseBinary respWriteraIdArray(aInvocation, "aIdArray");
    Brn buf_aIdArray((const TByte*)respaIdArray.c_str(), (TUint)respaIdArray.length());
    respWriteraIdArray.Write(buf_aIdArray);
    aInvocation.InvocationWriteBinaryEnd("aIdArray");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPlaylist1Cpp::DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aIdArrayToken = aInvocation.InvocationReadUint("aIdArrayToken");
    aInvocation.InvocationReadEnd();
    bool respaIdArrayChanged;
    IdArrayChanged(aVersion, aIdArrayToken, respaIdArrayChanged);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraIdArrayChanged(aInvocation, "aIdArrayChanged");
    respWriteraIdArrayChanged.Write(respaIdArrayChanged);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkPlaylist1Cpp::Read(uint32_t /*aVersion*/, uint32_t /*aaId*/, std::string& /*aaUri*/, std::string& /*aaMetaData*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1Cpp::ReadList(uint32_t /*aVersion*/, const std::string& /*aaIdList*/, std::string& /*aaMetaDataList*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1Cpp::Insert(uint32_t /*aVersion*/, uint32_t /*aaAfterId*/, const std::string& /*aaUri*/, const std::string& /*aaMetaData*/, uint32_t& /*aaNewId*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1Cpp::Delete(uint32_t /*aVersion*/, uint32_t /*aaId*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1Cpp::DeleteAll(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1Cpp::SetRepeat(uint32_t /*aVersion*/, bool /*aaRepeat*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1Cpp::Repeat(uint32_t /*aVersion*/, bool& /*aaRepeat*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1Cpp::SetShuffle(uint32_t /*aVersion*/, bool /*aaShuffle*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1Cpp::Shuffle(uint32_t /*aVersion*/, bool& /*aaShuffle*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1Cpp::TracksMax(uint32_t /*aVersion*/, uint32_t& /*aaTracksMax*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1Cpp::IdArray(uint32_t /*aVersion*/, uint32_t& /*aaIdArrayToken*/, std::string& /*aaIdArray*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1Cpp::IdArrayChanged(uint32_t /*aVersion*/, uint32_t /*aaIdArrayToken*/, bool& /*aaIdArrayChanged*/)
{
    ASSERTS();
}

