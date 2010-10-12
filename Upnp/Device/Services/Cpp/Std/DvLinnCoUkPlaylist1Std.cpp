#include <Std/DvLinnCoUkPlaylist1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkPlaylist1Cpp::SetPropertyIdArray(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyBinary(*iPropertyIdArray, buf);
}

void DvServiceLinnCoUkPlaylist1Cpp::GetPropertyIdArray(std::string& aValue)
{
    const Brx& val = iPropertyIdArray->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkPlaylist1Cpp::SetPropertyRepeat(bool aValue)
{
    SetPropertyBool(*iPropertyRepeat, aValue);
}

void DvServiceLinnCoUkPlaylist1Cpp::GetPropertyRepeat(bool& aValue)
{
    aValue = iPropertyRepeat->Value();
}

void DvServiceLinnCoUkPlaylist1Cpp::SetPropertyShuffle(bool aValue)
{
    SetPropertyBool(*iPropertyShuffle, aValue);
}

void DvServiceLinnCoUkPlaylist1Cpp::GetPropertyShuffle(bool& aValue)
{
    aValue = iPropertyShuffle->Value();
}

void DvServiceLinnCoUkPlaylist1Cpp::SetPropertyTracksMax(uint32_t aValue)
{
    SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvServiceLinnCoUkPlaylist1Cpp::GetPropertyTracksMax(uint32_t& aValue)
{
    aValue = iPropertyTracksMax->Value();
}

DvServiceLinnCoUkPlaylist1Cpp::DvServiceLinnCoUkPlaylist1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Playlist", 1)
{
    Functor empty;
    iPropertyIdArray = new PropertyBinary(new ParameterBinary("IdArray"), empty);
    iService->AddProperty(iPropertyIdArray); // passes ownership
    iPropertyRepeat = new PropertyBool(new ParameterBool("Repeat"), empty);
    iService->AddProperty(iPropertyRepeat); // passes ownership
    iPropertyShuffle = new PropertyBool(new ParameterBool("Shuffle"), empty);
    iService->AddProperty(iPropertyShuffle); // passes ownership
    iPropertyTracksMax = new PropertyUint(new ParameterUint("TracksMax"), empty);
    iService->AddProperty(iPropertyTracksMax); // passes ownership
}

void DvServiceLinnCoUkPlaylist1Cpp::EnableActionRead()
{
    Zapp::Action* action = new Zapp::Action("Read");
    action->AddInputParameter(new ParameterUint("aId"));
    action->AddOutputParameter(new ParameterString("aUri"));
    action->AddOutputParameter(new ParameterString("aMetaData"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1Cpp::DoRead);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1Cpp::EnableActionReadList()
{
    Zapp::Action* action = new Zapp::Action("ReadList");
    action->AddInputParameter(new ParameterString("aIdList"));
    action->AddOutputParameter(new ParameterString("aMetaDataList"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1Cpp::DoReadList);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1Cpp::EnableActionInsert()
{
    Zapp::Action* action = new Zapp::Action("Insert");
    action->AddInputParameter(new ParameterUint("aAfterId"));
    action->AddInputParameter(new ParameterString("aUri"));
    action->AddInputParameter(new ParameterString("aMetaData"));
    action->AddOutputParameter(new ParameterUint("aNewId"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1Cpp::DoInsert);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1Cpp::EnableActionDelete()
{
    Zapp::Action* action = new Zapp::Action("Delete");
    action->AddInputParameter(new ParameterUint("aId"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1Cpp::DoDelete);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1Cpp::EnableActionDeleteAll()
{
    Zapp::Action* action = new Zapp::Action("DeleteAll");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1Cpp::DoDeleteAll);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1Cpp::EnableActionSetRepeat()
{
    Zapp::Action* action = new Zapp::Action("SetRepeat");
    action->AddInputParameter(new ParameterRelated("aRepeat", *iPropertyRepeat));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1Cpp::DoSetRepeat);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1Cpp::EnableActionRepeat()
{
    Zapp::Action* action = new Zapp::Action("Repeat");
    action->AddOutputParameter(new ParameterRelated("aRepeat", *iPropertyRepeat));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1Cpp::DoRepeat);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1Cpp::EnableActionSetShuffle()
{
    Zapp::Action* action = new Zapp::Action("SetShuffle");
    action->AddInputParameter(new ParameterRelated("aShuffle", *iPropertyShuffle));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1Cpp::DoSetShuffle);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1Cpp::EnableActionShuffle()
{
    Zapp::Action* action = new Zapp::Action("Shuffle");
    action->AddOutputParameter(new ParameterRelated("aShuffle", *iPropertyShuffle));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1Cpp::DoShuffle);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1Cpp::EnableActionTracksMax()
{
    Zapp::Action* action = new Zapp::Action("TracksMax");
    action->AddOutputParameter(new ParameterRelated("aTracksMax", *iPropertyTracksMax));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1Cpp::DoTracksMax);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1Cpp::EnableActionIdArray()
{
    Zapp::Action* action = new Zapp::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterRelated("aIdArray", *iPropertyIdArray));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1Cpp::DoIdArray);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1Cpp::EnableActionIdArrayChanged()
{
    Zapp::Action* action = new Zapp::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterBool("aIdArrayChanged"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1Cpp::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1Cpp::DoRead(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    std::string respaUri;
    std::string respaMetaData;
    Read(aVersion, aId, respaUri, respaMetaData);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraUri(aInvocation, "aUri");
    Brn buf_aUri((const TByte*)respaUri.c_str(), respaUri.length());
    respWriteraUri.Write(buf_aUri);
    aInvocation.InvocationWriteStringEnd("aUri");
    InvocationResponseString respWriteraMetaData(aInvocation, "aMetaData");
    Brn buf_aMetaData((const TByte*)respaMetaData.c_str(), respaMetaData.length());
    respWriteraMetaData.Write(buf_aMetaData);
    aInvocation.InvocationWriteStringEnd("aMetaData");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPlaylist1Cpp::DoReadList(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_aMetaDataList((const TByte*)respaMetaDataList.c_str(), respaMetaDataList.length());
    respWriteraMetaDataList.Write(buf_aMetaDataList);
    aInvocation.InvocationWriteStringEnd("aMetaDataList");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPlaylist1Cpp::DoInsert(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkPlaylist1Cpp::DoDelete(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    Delete(aVersion, aId);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPlaylist1Cpp::DoDeleteAll(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DeleteAll(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPlaylist1Cpp::DoSetRepeat(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aRepeat = aInvocation.InvocationReadBool("aRepeat");
    aInvocation.InvocationReadEnd();
    SetRepeat(aVersion, aRepeat);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPlaylist1Cpp::DoRepeat(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkPlaylist1Cpp::DoSetShuffle(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aShuffle = aInvocation.InvocationReadBool("aShuffle");
    aInvocation.InvocationReadEnd();
    SetShuffle(aVersion, aShuffle);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPlaylist1Cpp::DoShuffle(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkPlaylist1Cpp::DoTracksMax(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkPlaylist1Cpp::DoIdArray(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_aIdArray((const TByte*)respaIdArray.c_str(), respaIdArray.length());
    respWriteraIdArray.Write(buf_aIdArray);
    aInvocation.InvocationWriteBinaryEnd("aIdArray");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkPlaylist1Cpp::DoIdArrayChanged(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkPlaylist1Cpp::Read(uint32_t /*aVersion*/, uint32_t /*aaId*/, std::string& /*aaUri*/, std::string& /*aaMetaData*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1Cpp::ReadList(uint32_t /*aVersion*/, const std::string& /*aaIdList*/, std::string& /*aaMetaDataList*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1Cpp::Insert(uint32_t /*aVersion*/, uint32_t /*aaAfterId*/, const std::string& /*aaUri*/, const std::string& /*aaMetaData*/, uint32_t& /*aaNewId*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1Cpp::Delete(uint32_t /*aVersion*/, uint32_t /*aaId*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1Cpp::DeleteAll(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1Cpp::SetRepeat(uint32_t /*aVersion*/, bool /*aaRepeat*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1Cpp::Repeat(uint32_t /*aVersion*/, bool& /*aaRepeat*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1Cpp::SetShuffle(uint32_t /*aVersion*/, bool /*aaShuffle*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1Cpp::Shuffle(uint32_t /*aVersion*/, bool& /*aaShuffle*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1Cpp::TracksMax(uint32_t /*aVersion*/, uint32_t& /*aaTracksMax*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1Cpp::IdArray(uint32_t /*aVersion*/, uint32_t& /*aaIdArrayToken*/, std::string& /*aaIdArray*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1Cpp::IdArrayChanged(uint32_t /*aVersion*/, uint32_t /*aaIdArrayToken*/, bool& /*aaIdArrayChanged*/)
{
    ASSERTS();
}

