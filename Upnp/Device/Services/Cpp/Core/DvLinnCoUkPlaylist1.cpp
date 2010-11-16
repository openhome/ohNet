#include <Core/DvLinnCoUkPlaylist1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkPlaylist1::SetPropertyIdArray(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvProviderLinnCoUkPlaylist1::GetPropertyIdArray(Brh& aValue)
{
    aValue.Set(iPropertyIdArray->Value());
}

TBool DvProviderLinnCoUkPlaylist1::SetPropertyRepeat(TBool aValue)
{
    return SetPropertyBool(*iPropertyRepeat, aValue);
}

void DvProviderLinnCoUkPlaylist1::GetPropertyRepeat(TBool& aValue)
{
    aValue = iPropertyRepeat->Value();
}

TBool DvProviderLinnCoUkPlaylist1::SetPropertyShuffle(TBool aValue)
{
    return SetPropertyBool(*iPropertyShuffle, aValue);
}

void DvProviderLinnCoUkPlaylist1::GetPropertyShuffle(TBool& aValue)
{
    aValue = iPropertyShuffle->Value();
}

TBool DvProviderLinnCoUkPlaylist1::SetPropertyTracksMax(TUint aValue)
{
    return SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvProviderLinnCoUkPlaylist1::GetPropertyTracksMax(TUint& aValue)
{
    aValue = iPropertyTracksMax->Value();
}

DvProviderLinnCoUkPlaylist1::DvProviderLinnCoUkPlaylist1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Playlist", 1)
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

void DvProviderLinnCoUkPlaylist1::EnableActionRead()
{
    Zapp::Action* action = new Zapp::Action("Read");
    action->AddInputParameter(new ParameterUint("aId"));
    action->AddOutputParameter(new ParameterString("aUri"));
    action->AddOutputParameter(new ParameterString("aMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1::EnableActionReadList()
{
    Zapp::Action* action = new Zapp::Action("ReadList");
    action->AddInputParameter(new ParameterString("aIdList"));
    action->AddOutputParameter(new ParameterString("aMetaDataList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1::EnableActionInsert()
{
    Zapp::Action* action = new Zapp::Action("Insert");
    action->AddInputParameter(new ParameterUint("aAfterId"));
    action->AddInputParameter(new ParameterString("aUri"));
    action->AddInputParameter(new ParameterString("aMetaData"));
    action->AddOutputParameter(new ParameterUint("aNewId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1::DoInsert);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1::EnableActionDelete()
{
    Zapp::Action* action = new Zapp::Action("Delete");
    action->AddInputParameter(new ParameterUint("aId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1::DoDelete);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1::EnableActionDeleteAll()
{
    Zapp::Action* action = new Zapp::Action("DeleteAll");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1::DoDeleteAll);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1::EnableActionSetRepeat()
{
    Zapp::Action* action = new Zapp::Action("SetRepeat");
    action->AddInputParameter(new ParameterRelated("aRepeat", *iPropertyRepeat));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1::DoSetRepeat);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1::EnableActionRepeat()
{
    Zapp::Action* action = new Zapp::Action("Repeat");
    action->AddOutputParameter(new ParameterRelated("aRepeat", *iPropertyRepeat));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1::DoRepeat);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1::EnableActionSetShuffle()
{
    Zapp::Action* action = new Zapp::Action("SetShuffle");
    action->AddInputParameter(new ParameterRelated("aShuffle", *iPropertyShuffle));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1::DoSetShuffle);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1::EnableActionShuffle()
{
    Zapp::Action* action = new Zapp::Action("Shuffle");
    action->AddOutputParameter(new ParameterRelated("aShuffle", *iPropertyShuffle));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1::DoShuffle);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1::EnableActionTracksMax()
{
    Zapp::Action* action = new Zapp::Action("TracksMax");
    action->AddOutputParameter(new ParameterRelated("aTracksMax", *iPropertyTracksMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1::DoTracksMax);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1::EnableActionIdArray()
{
    Zapp::Action* action = new Zapp::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterRelated("aIdArray", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1::DoIdArray);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1::EnableActionIdArrayChanged()
{
    Zapp::Action* action = new Zapp::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("aIdArrayToken"));
    action->AddOutputParameter(new ParameterBool("aIdArrayChanged"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkPlaylist1::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkPlaylist1::DoRead(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaUri(aInvocation, "aUri");
    InvocationResponseString respaMetaData(aInvocation, "aMetaData");
    Read(resp, aVersion, aId, respaUri, respaMetaData);
}

void DvProviderLinnCoUkPlaylist1::DoReadList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aIdList;
    aInvocation.InvocationReadString("aIdList", aIdList);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaMetaDataList(aInvocation, "aMetaDataList");
    ReadList(resp, aVersion, aIdList, respaMetaDataList);
}

void DvProviderLinnCoUkPlaylist1::DoInsert(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkPlaylist1::DoDelete(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aId = aInvocation.InvocationReadUint("aId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Delete(resp, aVersion, aId);
}

void DvProviderLinnCoUkPlaylist1::DoDeleteAll(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DeleteAll(resp, aVersion);
}

void DvProviderLinnCoUkPlaylist1::DoSetRepeat(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aRepeat = aInvocation.InvocationReadBool("aRepeat");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRepeat(resp, aVersion, aRepeat);
}

void DvProviderLinnCoUkPlaylist1::DoRepeat(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaRepeat(aInvocation, "aRepeat");
    Repeat(resp, aVersion, respaRepeat);
}

void DvProviderLinnCoUkPlaylist1::DoSetShuffle(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aShuffle = aInvocation.InvocationReadBool("aShuffle");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetShuffle(resp, aVersion, aShuffle);
}

void DvProviderLinnCoUkPlaylist1::DoShuffle(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaShuffle(aInvocation, "aShuffle");
    Shuffle(resp, aVersion, respaShuffle);
}

void DvProviderLinnCoUkPlaylist1::DoTracksMax(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaTracksMax(aInvocation, "aTracksMax");
    TracksMax(resp, aVersion, respaTracksMax);
}

void DvProviderLinnCoUkPlaylist1::DoIdArray(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaIdArrayToken(aInvocation, "aIdArrayToken");
    InvocationResponseBinary respaIdArray(aInvocation, "aIdArray");
    IdArray(resp, aVersion, respaIdArrayToken, respaIdArray);
}

void DvProviderLinnCoUkPlaylist1::DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIdArrayToken = aInvocation.InvocationReadUint("aIdArrayToken");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaIdArrayChanged(aInvocation, "aIdArrayChanged");
    IdArrayChanged(resp, aVersion, aIdArrayToken, respaIdArrayChanged);
}

void DvProviderLinnCoUkPlaylist1::Read(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaId*/, IInvocationResponseString& /*aaUri*/, IInvocationResponseString& /*aaMetaData*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1::ReadList(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaIdList*/, IInvocationResponseString& /*aaMetaDataList*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1::Insert(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaAfterId*/, const Brx& /*aaUri*/, const Brx& /*aaMetaData*/, IInvocationResponseUint& /*aaNewId*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1::Delete(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaId*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1::DeleteAll(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1::SetRepeat(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaRepeat*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1::Repeat(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaRepeat*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1::SetShuffle(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaShuffle*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1::Shuffle(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaShuffle*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1::TracksMax(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaTracksMax*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1::IdArray(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaIdArrayToken*/, IInvocationResponseBinary& /*aaIdArray*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkPlaylist1::IdArrayChanged(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaIdArrayToken*/, IInvocationResponseBool& /*aaIdArrayChanged*/)
{
    ASSERTS();
}

