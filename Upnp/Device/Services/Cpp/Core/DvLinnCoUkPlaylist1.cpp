#include <Core/DvLinnCoUkPlaylist1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkPlaylist1::SetPropertyIdArray(const Brx& aValue)
{
    SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvServiceLinnCoUkPlaylist1::GetPropertyIdArray(Brh& aValue)
{
    aValue.Set(iPropertyIdArray->Value());
}

void DvServiceLinnCoUkPlaylist1::SetPropertyRepeat(TBool aValue)
{
    SetPropertyBool(*iPropertyRepeat, aValue);
}

void DvServiceLinnCoUkPlaylist1::GetPropertyRepeat(TBool& aValue)
{
    aValue = iPropertyRepeat->Value();
}

void DvServiceLinnCoUkPlaylist1::SetPropertyShuffle(TBool aValue)
{
    SetPropertyBool(*iPropertyShuffle, aValue);
}

void DvServiceLinnCoUkPlaylist1::GetPropertyShuffle(TBool& aValue)
{
    aValue = iPropertyShuffle->Value();
}

void DvServiceLinnCoUkPlaylist1::SetPropertyTracksMax(TUint aValue)
{
    SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvServiceLinnCoUkPlaylist1::GetPropertyTracksMax(TUint& aValue)
{
    aValue = iPropertyTracksMax->Value();
}

DvServiceLinnCoUkPlaylist1::DvServiceLinnCoUkPlaylist1(DvDevice& aDevice)
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

void DvServiceLinnCoUkPlaylist1::EnableActionRead()
{
    Zapp::Action* action = new Zapp::Action("Read");
    action->AddInputParameter(new ParameterUint("aId"));
    action->AddOutputParameter(new ParameterString("aUri"));
    action->AddOutputParameter(new ParameterString("aMetaData"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1::DoRead);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1::EnableActionReadList()
{
    Zapp::Action* action = new Zapp::Action("ReadList");
    action->AddInputParameter(new ParameterString("aIdList"));
    action->AddOutputParameter(new ParameterString("aMetaDataList"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1::DoReadList);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1::EnableActionInsert()
{
    Zapp::Action* action = new Zapp::Action("Insert");
    action->AddInputParameter(new ParameterUint("aAfterId"));
    action->AddInputParameter(new ParameterString("aUri"));
    action->AddInputParameter(new ParameterString("aMetaData"));
    action->AddOutputParameter(new ParameterUint("aNewId"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1::DoInsert);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1::EnableActionDelete()
{
    Zapp::Action* action = new Zapp::Action("Delete");
    action->AddInputParameter(new ParameterUint("aId"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1::DoDelete);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1::EnableActionDeleteAll()
{
    Zapp::Action* action = new Zapp::Action("DeleteAll");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1::DoDeleteAll);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1::EnableActionSetRepeat()
{
    Zapp::Action* action = new Zapp::Action("SetRepeat");
    action->AddInputParameter(new ParameterRelated("aRepeat", *iPropertyRepeat));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1::DoSetRepeat);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1::EnableActionRepeat()
{
    Zapp::Action* action = new Zapp::Action("Repeat");
    action->AddOutputParameter(new ParameterRelated("aRepeat", *iPropertyRepeat));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1::DoRepeat);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1::EnableActionSetShuffle()
{
    Zapp::Action* action = new Zapp::Action("SetShuffle");
    action->AddInputParameter(new ParameterRelated("aShuffle", *iPropertyShuffle));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1::DoSetShuffle);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1::EnableActionShuffle()
{
    Zapp::Action* action = new Zapp::Action("Shuffle");
    action->AddOutputParameter(new ParameterRelated("aShuffle", *iPropertyShuffle));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1::DoShuffle);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1::EnableActionTracksMax()
{
    Zapp::Action* action = new Zapp::Action("TracksMax");
    action->AddOutputParameter(new ParameterRelated("aTracksMax", *iPropertyTracksMax));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1::DoTracksMax);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1::EnableActionIdArray()
{
    Zapp::Action* action = new Zapp::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterRelated("aIdArray", *iPropertyIdArray));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1::DoIdArray);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1::EnableActionIdArrayChanged()
{
    Zapp::Action* action = new Zapp::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterBool("aIdArrayChanged"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkPlaylist1::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkPlaylist1::DoRead(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaUri(aInvocation, "aUri");
    InvocationResponseString respaMetaData(aInvocation, "aMetaData");
    Read(resp, aVersion, aId, respaUri, respaMetaData);
}

void DvServiceLinnCoUkPlaylist1::DoReadList(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aIdList;
    aInvocation.InvocationReadString("aIdList", aIdList);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaMetaDataList(aInvocation, "aMetaDataList");
    ReadList(resp, aVersion, aIdList, respaMetaDataList);
}

void DvServiceLinnCoUkPlaylist1::DoInsert(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aAfterId = aInvocation.InvocationReadUint("aAfterId");
    Brhz aUri;
    aInvocation.InvocationReadString("aUri", aUri);
    Brhz aMetaData;
    aInvocation.InvocationReadString("aMetaData", aMetaData);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaNewId(aInvocation, "aNewId");
    Insert(resp, aVersion, aAfterId, aUri, aMetaData, respaNewId);
}

void DvServiceLinnCoUkPlaylist1::DoDelete(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Delete(resp, aVersion, aId);
}

void DvServiceLinnCoUkPlaylist1::DoDeleteAll(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DeleteAll(resp, aVersion);
}

void DvServiceLinnCoUkPlaylist1::DoSetRepeat(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aRepeat = aInvocation.InvocationReadBool("aRepeat");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRepeat(resp, aVersion, aRepeat);
}

void DvServiceLinnCoUkPlaylist1::DoRepeat(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaRepeat(aInvocation, "aRepeat");
    Repeat(resp, aVersion, respaRepeat);
}

void DvServiceLinnCoUkPlaylist1::DoSetShuffle(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aShuffle = aInvocation.InvocationReadBool("aShuffle");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetShuffle(resp, aVersion, aShuffle);
}

void DvServiceLinnCoUkPlaylist1::DoShuffle(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaShuffle(aInvocation, "aShuffle");
    Shuffle(resp, aVersion, respaShuffle);
}

void DvServiceLinnCoUkPlaylist1::DoTracksMax(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaTracksMax(aInvocation, "aTracksMax");
    TracksMax(resp, aVersion, respaTracksMax);
}

void DvServiceLinnCoUkPlaylist1::DoIdArray(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaIdArrayToken(aInvocation, "aIdArrayToken");
    InvocationResponseBinary respaIdArray(aInvocation, "aIdArray");
    IdArray(resp, aVersion, respaIdArrayToken, respaIdArray);
}

void DvServiceLinnCoUkPlaylist1::DoIdArrayChanged(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIdArrayToken = aInvocation.InvocationReadUint("aIdArrayToken");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaIdArrayChanged(aInvocation, "aIdArrayChanged");
    IdArrayChanged(resp, aVersion, aIdArrayToken, respaIdArrayChanged);
}

void DvServiceLinnCoUkPlaylist1::Read(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaId*/, IInvocationResponseString& /*aaUri*/, IInvocationResponseString& /*aaMetaData*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1::ReadList(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaIdList*/, IInvocationResponseString& /*aaMetaDataList*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1::Insert(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaAfterId*/, const Brx& /*aaUri*/, const Brx& /*aaMetaData*/, IInvocationResponseUint& /*aaNewId*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1::Delete(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaId*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1::DeleteAll(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1::SetRepeat(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaRepeat*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1::Repeat(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaRepeat*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1::SetShuffle(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaShuffle*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1::Shuffle(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaShuffle*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1::TracksMax(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaTracksMax*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1::IdArray(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaIdArrayToken*/, IInvocationResponseBinary& /*aaIdArray*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkPlaylist1::IdArrayChanged(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIdArrayToken*/, IInvocationResponseBool& /*aaIdArrayChanged*/)
{
    ASSERTS();
}

