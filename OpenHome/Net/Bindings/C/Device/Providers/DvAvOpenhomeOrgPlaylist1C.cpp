#include "DvAvOpenhomeOrgPlaylist1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/C/DvInvocationPrivate.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderAvOpenhomeOrgPlaylist1C : public DvProvider
{
public:
    DvProviderAvOpenhomeOrgPlaylist1C(DvDeviceC aDevice);
    TBool SetPropertyTransportState(const Brx& aValue);
    void GetPropertyTransportState(Brhz& aValue);
    TBool SetPropertyRepeat(TBool aValue);
    void GetPropertyRepeat(TBool& aValue);
    TBool SetPropertyShuffle(TBool aValue);
    void GetPropertyShuffle(TBool& aValue);
    TBool SetPropertyId(TUint aValue);
    void GetPropertyId(TUint& aValue);
    TBool SetPropertyIdArray(const Brx& aValue);
    void GetPropertyIdArray(Brh& aValue);
    TBool SetPropertyTracksMax(TUint aValue);
    void GetPropertyTracksMax(TUint& aValue);
    TBool SetPropertyProtocolInfo(const Brx& aValue);
    void GetPropertyProtocolInfo(Brhz& aValue);
    void EnablePropertyTransportState();
    void EnablePropertyRepeat();
    void EnablePropertyShuffle();
    void EnablePropertyId();
    void EnablePropertyIdArray();
    void EnablePropertyTracksMax();
    void EnablePropertyProtocolInfo();
    void EnableActionPlay(CallbackPlaylist1Play aCallback, void* aPtr);
    void EnableActionPause(CallbackPlaylist1Pause aCallback, void* aPtr);
    void EnableActionStop(CallbackPlaylist1Stop aCallback, void* aPtr);
    void EnableActionNext(CallbackPlaylist1Next aCallback, void* aPtr);
    void EnableActionPrevious(CallbackPlaylist1Previous aCallback, void* aPtr);
    void EnableActionSetRepeat(CallbackPlaylist1SetRepeat aCallback, void* aPtr);
    void EnableActionRepeat(CallbackPlaylist1Repeat aCallback, void* aPtr);
    void EnableActionSetShuffle(CallbackPlaylist1SetShuffle aCallback, void* aPtr);
    void EnableActionShuffle(CallbackPlaylist1Shuffle aCallback, void* aPtr);
    void EnableActionSeekSecondAbsolute(CallbackPlaylist1SeekSecondAbsolute aCallback, void* aPtr);
    void EnableActionSeekSecondRelative(CallbackPlaylist1SeekSecondRelative aCallback, void* aPtr);
    void EnableActionSeekId(CallbackPlaylist1SeekId aCallback, void* aPtr);
    void EnableActionSeekIndex(CallbackPlaylist1SeekIndex aCallback, void* aPtr);
    void EnableActionTransportState(CallbackPlaylist1TransportState aCallback, void* aPtr);
    void EnableActionId(CallbackPlaylist1Id aCallback, void* aPtr);
    void EnableActionRead(CallbackPlaylist1Read aCallback, void* aPtr);
    void EnableActionReadList(CallbackPlaylist1ReadList aCallback, void* aPtr);
    void EnableActionInsert(CallbackPlaylist1Insert aCallback, void* aPtr);
    void EnableActionDeleteId(CallbackPlaylist1DeleteId aCallback, void* aPtr);
    void EnableActionDeleteAll(CallbackPlaylist1DeleteAll aCallback, void* aPtr);
    void EnableActionTracksMax(CallbackPlaylist1TracksMax aCallback, void* aPtr);
    void EnableActionIdArray(CallbackPlaylist1IdArray aCallback, void* aPtr);
    void EnableActionIdArrayChanged(CallbackPlaylist1IdArrayChanged aCallback, void* aPtr);
    void EnableActionProtocolInfo(CallbackPlaylist1ProtocolInfo aCallback, void* aPtr);
private:
    void DoPlay(IDviInvocation& aInvocation);
    void DoPause(IDviInvocation& aInvocation);
    void DoStop(IDviInvocation& aInvocation);
    void DoNext(IDviInvocation& aInvocation);
    void DoPrevious(IDviInvocation& aInvocation);
    void DoSetRepeat(IDviInvocation& aInvocation);
    void DoRepeat(IDviInvocation& aInvocation);
    void DoSetShuffle(IDviInvocation& aInvocation);
    void DoShuffle(IDviInvocation& aInvocation);
    void DoSeekSecondAbsolute(IDviInvocation& aInvocation);
    void DoSeekSecondRelative(IDviInvocation& aInvocation);
    void DoSeekId(IDviInvocation& aInvocation);
    void DoSeekIndex(IDviInvocation& aInvocation);
    void DoTransportState(IDviInvocation& aInvocation);
    void DoId(IDviInvocation& aInvocation);
    void DoRead(IDviInvocation& aInvocation);
    void DoReadList(IDviInvocation& aInvocation);
    void DoInsert(IDviInvocation& aInvocation);
    void DoDeleteId(IDviInvocation& aInvocation);
    void DoDeleteAll(IDviInvocation& aInvocation);
    void DoTracksMax(IDviInvocation& aInvocation);
    void DoIdArray(IDviInvocation& aInvocation);
    void DoIdArrayChanged(IDviInvocation& aInvocation);
    void DoProtocolInfo(IDviInvocation& aInvocation);
private:
    CallbackPlaylist1Play iCallbackPlay;
    void* iPtrPlay;
    CallbackPlaylist1Pause iCallbackPause;
    void* iPtrPause;
    CallbackPlaylist1Stop iCallbackStop;
    void* iPtrStop;
    CallbackPlaylist1Next iCallbackNext;
    void* iPtrNext;
    CallbackPlaylist1Previous iCallbackPrevious;
    void* iPtrPrevious;
    CallbackPlaylist1SetRepeat iCallbackSetRepeat;
    void* iPtrSetRepeat;
    CallbackPlaylist1Repeat iCallbackRepeat;
    void* iPtrRepeat;
    CallbackPlaylist1SetShuffle iCallbackSetShuffle;
    void* iPtrSetShuffle;
    CallbackPlaylist1Shuffle iCallbackShuffle;
    void* iPtrShuffle;
    CallbackPlaylist1SeekSecondAbsolute iCallbackSeekSecondAbsolute;
    void* iPtrSeekSecondAbsolute;
    CallbackPlaylist1SeekSecondRelative iCallbackSeekSecondRelative;
    void* iPtrSeekSecondRelative;
    CallbackPlaylist1SeekId iCallbackSeekId;
    void* iPtrSeekId;
    CallbackPlaylist1SeekIndex iCallbackSeekIndex;
    void* iPtrSeekIndex;
    CallbackPlaylist1TransportState iCallbackTransportState;
    void* iPtrTransportState;
    CallbackPlaylist1Id iCallbackId;
    void* iPtrId;
    CallbackPlaylist1Read iCallbackRead;
    void* iPtrRead;
    CallbackPlaylist1ReadList iCallbackReadList;
    void* iPtrReadList;
    CallbackPlaylist1Insert iCallbackInsert;
    void* iPtrInsert;
    CallbackPlaylist1DeleteId iCallbackDeleteId;
    void* iPtrDeleteId;
    CallbackPlaylist1DeleteAll iCallbackDeleteAll;
    void* iPtrDeleteAll;
    CallbackPlaylist1TracksMax iCallbackTracksMax;
    void* iPtrTracksMax;
    CallbackPlaylist1IdArray iCallbackIdArray;
    void* iPtrIdArray;
    CallbackPlaylist1IdArrayChanged iCallbackIdArrayChanged;
    void* iPtrIdArrayChanged;
    CallbackPlaylist1ProtocolInfo iCallbackProtocolInfo;
    void* iPtrProtocolInfo;
    PropertyString* iPropertyTransportState;
    PropertyBool* iPropertyRepeat;
    PropertyBool* iPropertyShuffle;
    PropertyUint* iPropertyId;
    PropertyBinary* iPropertyIdArray;
    PropertyUint* iPropertyTracksMax;
    PropertyString* iPropertyProtocolInfo;
};

DvProviderAvOpenhomeOrgPlaylist1C::DvProviderAvOpenhomeOrgPlaylist1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "Playlist", 1)
{
    iPropertyTransportState = NULL;
    iPropertyRepeat = NULL;
    iPropertyShuffle = NULL;
    iPropertyId = NULL;
    iPropertyIdArray = NULL;
    iPropertyTracksMax = NULL;
    iPropertyProtocolInfo = NULL;
}

TBool DvProviderAvOpenhomeOrgPlaylist1C::SetPropertyTransportState(const Brx& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    return SetPropertyString(*iPropertyTransportState, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1C::GetPropertyTransportState(Brhz& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    aValue.Set(iPropertyTransportState->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylist1C::SetPropertyRepeat(TBool aValue)
{
    ASSERT(iPropertyRepeat != NULL);
    return SetPropertyBool(*iPropertyRepeat, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1C::GetPropertyRepeat(TBool& aValue)
{
    ASSERT(iPropertyRepeat != NULL);
    aValue = iPropertyRepeat->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylist1C::SetPropertyShuffle(TBool aValue)
{
    ASSERT(iPropertyShuffle != NULL);
    return SetPropertyBool(*iPropertyShuffle, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1C::GetPropertyShuffle(TBool& aValue)
{
    ASSERT(iPropertyShuffle != NULL);
    aValue = iPropertyShuffle->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylist1C::SetPropertyId(TUint aValue)
{
    ASSERT(iPropertyId != NULL);
    return SetPropertyUint(*iPropertyId, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1C::GetPropertyId(TUint& aValue)
{
    ASSERT(iPropertyId != NULL);
    aValue = iPropertyId->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylist1C::SetPropertyIdArray(const Brx& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    return SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1C::GetPropertyIdArray(Brh& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    aValue.Set(iPropertyIdArray->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylist1C::SetPropertyTracksMax(TUint aValue)
{
    ASSERT(iPropertyTracksMax != NULL);
    return SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1C::GetPropertyTracksMax(TUint& aValue)
{
    ASSERT(iPropertyTracksMax != NULL);
    aValue = iPropertyTracksMax->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylist1C::SetPropertyProtocolInfo(const Brx& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    return SetPropertyString(*iPropertyProtocolInfo, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1C::GetPropertyProtocolInfo(Brhz& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    aValue.Set(iPropertyProtocolInfo->Value());
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnablePropertyTransportState()
{
    TChar** allowedValues;
    TUint index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(iDvStack.Env(), new ParameterString("TransportState", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnablePropertyRepeat()
{
    iPropertyRepeat = new PropertyBool(iDvStack.Env(), new ParameterBool("Repeat"));
    iService->AddProperty(iPropertyRepeat); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnablePropertyShuffle()
{
    iPropertyShuffle = new PropertyBool(iDvStack.Env(), new ParameterBool("Shuffle"));
    iService->AddProperty(iPropertyShuffle); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnablePropertyId()
{
    iPropertyId = new PropertyUint(iDvStack.Env(), new ParameterUint("Id"));
    iService->AddProperty(iPropertyId); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnablePropertyIdArray()
{
    iPropertyIdArray = new PropertyBinary(iDvStack.Env(), new ParameterBinary("IdArray"));
    iService->AddProperty(iPropertyIdArray); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnablePropertyTracksMax()
{
    iPropertyTracksMax = new PropertyUint(iDvStack.Env(), new ParameterUint("TracksMax"));
    iService->AddProperty(iPropertyTracksMax); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnablePropertyProtocolInfo()
{
    iPropertyProtocolInfo = new PropertyString(iDvStack.Env(), new ParameterString("ProtocolInfo"));
    iService->AddProperty(iPropertyProtocolInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionPlay(CallbackPlaylist1Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionPause(CallbackPlaylist1Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Pause");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionStop(CallbackPlaylist1Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionNext(CallbackPlaylist1Next aCallback, void* aPtr)
{
    iCallbackNext = aCallback;
    iPtrNext = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Next");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoNext);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionPrevious(CallbackPlaylist1Previous aCallback, void* aPtr)
{
    iCallbackPrevious = aCallback;
    iPtrPrevious = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Previous");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoPrevious);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionSetRepeat(CallbackPlaylist1SetRepeat aCallback, void* aPtr)
{
    iCallbackSetRepeat = aCallback;
    iPtrSetRepeat = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRepeat");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyRepeat));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoSetRepeat);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionRepeat(CallbackPlaylist1Repeat aCallback, void* aPtr)
{
    iCallbackRepeat = aCallback;
    iPtrRepeat = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Repeat");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyRepeat));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoRepeat);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionSetShuffle(CallbackPlaylist1SetShuffle aCallback, void* aPtr)
{
    iCallbackSetShuffle = aCallback;
    iPtrSetShuffle = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetShuffle");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyShuffle));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoSetShuffle);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionShuffle(CallbackPlaylist1Shuffle aCallback, void* aPtr)
{
    iCallbackShuffle = aCallback;
    iPtrShuffle = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Shuffle");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyShuffle));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoShuffle);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionSeekSecondAbsolute(CallbackPlaylist1SeekSecondAbsolute aCallback, void* aPtr)
{
    iCallbackSeekSecondAbsolute = aCallback;
    iPtrSeekSecondAbsolute = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionSeekSecondRelative(CallbackPlaylist1SeekSecondRelative aCallback, void* aPtr)
{
    iCallbackSeekSecondRelative = aCallback;
    iPtrSeekSecondRelative = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionSeekId(CallbackPlaylist1SeekId aCallback, void* aPtr)
{
    iCallbackSeekId = aCallback;
    iPtrSeekId = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekId");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoSeekId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionSeekIndex(CallbackPlaylist1SeekIndex aCallback, void* aPtr)
{
    iCallbackSeekIndex = aCallback;
    iPtrSeekIndex = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekIndex");
    action->AddInputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoSeekIndex);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionTransportState(CallbackPlaylist1TransportState aCallback, void* aPtr)
{
    iCallbackTransportState = aCallback;
    iPtrTransportState = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTransportState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoTransportState);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionId(CallbackPlaylist1Id aCallback, void* aPtr)
{
    iCallbackId = aCallback;
    iPtrId = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Id");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionRead(CallbackPlaylist1Read aCallback, void* aPtr)
{
    iCallbackRead = aCallback;
    iPtrRead = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Read");
    action->AddInputParameter(new ParameterRelated("Id", *iPropertyId));
    action->AddOutputParameter(new ParameterString("Uri"));
    action->AddOutputParameter(new ParameterString("Metadata"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionReadList(CallbackPlaylist1ReadList aCallback, void* aPtr)
{
    iCallbackReadList = aCallback;
    iPtrReadList = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ReadList");
    action->AddInputParameter(new ParameterString("IdList"));
    action->AddOutputParameter(new ParameterString("TrackList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionInsert(CallbackPlaylist1Insert aCallback, void* aPtr)
{
    iCallbackInsert = aCallback;
    iPtrInsert = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Insert");
    action->AddInputParameter(new ParameterRelated("AfterId", *iPropertyId));
    action->AddInputParameter(new ParameterString("Uri"));
    action->AddInputParameter(new ParameterString("Metadata"));
    action->AddOutputParameter(new ParameterRelated("NewId", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoInsert);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionDeleteId(CallbackPlaylist1DeleteId aCallback, void* aPtr)
{
    iCallbackDeleteId = aCallback;
    iPtrDeleteId = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteId");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoDeleteId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionDeleteAll(CallbackPlaylist1DeleteAll aCallback, void* aPtr)
{
    iCallbackDeleteAll = aCallback;
    iPtrDeleteAll = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteAll");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoDeleteAll);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionTracksMax(CallbackPlaylist1TracksMax aCallback, void* aPtr)
{
    iCallbackTracksMax = aCallback;
    iPtrTracksMax = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TracksMax");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTracksMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoTracksMax);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionIdArray(CallbackPlaylist1IdArray aCallback, void* aPtr)
{
    iCallbackIdArray = aCallback;
    iPtrIdArray = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterRelated("Array", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoIdArray);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionIdArrayChanged(CallbackPlaylist1IdArrayChanged aCallback, void* aPtr)
{
    iCallbackIdArrayChanged = aCallback;
    iPtrIdArrayChanged = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterBool("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::EnableActionProtocolInfo(CallbackPlaylist1ProtocolInfo aCallback, void* aPtr)
{
    iCallbackProtocolInfo = aCallback;
    iPtrProtocolInfo = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1C::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoPlay(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoPause(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoStop(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoNext(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackNext != NULL);
    if (0 != iCallbackNext(iPtrNext, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoPrevious(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPrevious != NULL);
    if (0 != iCallbackPrevious(iPtrPrevious, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoSetRepeat(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetRepeat != NULL);
    if (0 != iCallbackSetRepeat(iPtrSetRepeat, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoRepeat(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackRepeat != NULL);
    if (0 != iCallbackRepeat(iPtrRepeat, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write((Value!=0));
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoSetShuffle(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetShuffle != NULL);
    if (0 != iCallbackSetShuffle(iPtrSetShuffle, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoShuffle(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackShuffle != NULL);
    if (0 != iCallbackShuffle(iPtrShuffle, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write((Value!=0));
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoSeekSecondAbsolute(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSeekSecondAbsolute != NULL);
    if (0 != iCallbackSeekSecondAbsolute(iPtrSeekSecondAbsolute, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoSeekSecondRelative(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSeekSecondRelative != NULL);
    if (0 != iCallbackSeekSecondRelative(iPtrSeekSecondRelative, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoSeekId(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSeekId != NULL);
    if (0 != iCallbackSeekId(iPtrSeekId, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoSeekIndex(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSeekIndex != NULL);
    if (0 != iCallbackSeekIndex(iPtrSeekIndex, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoTransportState(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Value;
    ASSERT(iCallbackTransportState != NULL);
    if (0 != iCallbackTransportState(iPtrTransportState, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respValue(aInvocation, "Value");
    invocation.StartResponse();
    Brhz bufValue((const TChar*)Value);
    OhNetFreeExternal(Value);
    respValue.Write(bufValue);
    respValue.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoId(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackId != NULL);
    if (0 != iCallbackId(iPtrId, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoRead(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Uri;
    char* Metadata;
    ASSERT(iCallbackRead != NULL);
    if (0 != iCallbackRead(iPtrRead, invocationC, invocationCPtr, Id, &Uri, &Metadata)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respUri(aInvocation, "Uri");
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    invocation.StartResponse();
    Brhz bufUri((const TChar*)Uri);
    OhNetFreeExternal(Uri);
    respUri.Write(bufUri);
    respUri.WriteFlush();
    Brhz bufMetadata((const TChar*)Metadata);
    OhNetFreeExternal(Metadata);
    respMetadata.Write(bufMetadata);
    respMetadata.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoReadList(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz IdList;
    aInvocation.InvocationReadString("IdList", IdList);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* TrackList;
    ASSERT(iCallbackReadList != NULL);
    if (0 != iCallbackReadList(iPtrReadList, invocationC, invocationCPtr, (const char*)IdList.Ptr(), &TrackList)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respTrackList(aInvocation, "TrackList");
    invocation.StartResponse();
    Brhz bufTrackList((const TChar*)TrackList);
    OhNetFreeExternal(TrackList);
    respTrackList.Write(bufTrackList);
    respTrackList.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoInsert(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint AfterId = aInvocation.InvocationReadUint("AfterId");
    Brhz Uri;
    aInvocation.InvocationReadString("Uri", Uri);
    Brhz Metadata;
    aInvocation.InvocationReadString("Metadata", Metadata);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t NewId;
    ASSERT(iCallbackInsert != NULL);
    if (0 != iCallbackInsert(iPtrInsert, invocationC, invocationCPtr, AfterId, (const char*)Uri.Ptr(), (const char*)Metadata.Ptr(), &NewId)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respNewId(aInvocation, "NewId");
    invocation.StartResponse();
    respNewId.Write(NewId);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoDeleteId(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackDeleteId != NULL);
    if (0 != iCallbackDeleteId(iPtrDeleteId, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoDeleteAll(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackDeleteAll != NULL);
    if (0 != iCallbackDeleteAll(iPtrDeleteAll, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoTracksMax(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackTracksMax != NULL);
    if (0 != iCallbackTracksMax(iPtrTracksMax, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoIdArray(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Token;
    char* Array;
    uint32_t ArrayLen;
    ASSERT(iCallbackIdArray != NULL);
    if (0 != iCallbackIdArray(iPtrIdArray, invocationC, invocationCPtr, &Token, &Array, &ArrayLen)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respToken(aInvocation, "Token");
    DviInvocationResponseBinary respArray(aInvocation, "Array");
    invocation.StartResponse();
    respToken.Write(Token);
    Brh bufArray;
    bufArray.Set((const TByte*)Array, ArrayLen);
    OhNetFreeExternal(Array);
    respArray.Write(bufArray);
    respArray.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoIdArrayChanged(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackIdArrayChanged != NULL);
    if (0 != iCallbackIdArrayChanged(iPtrIdArrayChanged, invocationC, invocationCPtr, Token, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write((Value!=0));
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylist1C::DoProtocolInfo(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Value;
    ASSERT(iCallbackProtocolInfo != NULL);
    if (0 != iCallbackProtocolInfo(iPtrProtocolInfo, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respValue(aInvocation, "Value");
    invocation.StartResponse();
    Brhz bufValue((const TChar*)Value);
    OhNetFreeExternal(Value);
    respValue.Write(bufValue);
    respValue.WriteFlush();
    invocation.EndResponse();
}



THandle STDCALL DvProviderAvOpenhomeOrgPlaylist1Create(DvDeviceC aDevice)
{
    return new DvProviderAvOpenhomeOrgPlaylist1C(aDevice);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionPlay(THandle aProvider, CallbackPlaylist1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionPlay(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionPause(THandle aProvider, CallbackPlaylist1Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionPause(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionStop(THandle aProvider, CallbackPlaylist1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionStop(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionNext(THandle aProvider, CallbackPlaylist1Next aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionNext(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionPrevious(THandle aProvider, CallbackPlaylist1Previous aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionPrevious(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionSetRepeat(THandle aProvider, CallbackPlaylist1SetRepeat aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionSetRepeat(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionRepeat(THandle aProvider, CallbackPlaylist1Repeat aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionRepeat(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionSetShuffle(THandle aProvider, CallbackPlaylist1SetShuffle aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionSetShuffle(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionShuffle(THandle aProvider, CallbackPlaylist1Shuffle aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionShuffle(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekSecondAbsolute(THandle aProvider, CallbackPlaylist1SeekSecondAbsolute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionSeekSecondAbsolute(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekSecondRelative(THandle aProvider, CallbackPlaylist1SeekSecondRelative aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionSeekSecondRelative(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekId(THandle aProvider, CallbackPlaylist1SeekId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionSeekId(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekIndex(THandle aProvider, CallbackPlaylist1SeekIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionSeekIndex(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionTransportState(THandle aProvider, CallbackPlaylist1TransportState aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionTransportState(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionId(THandle aProvider, CallbackPlaylist1Id aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionId(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionRead(THandle aProvider, CallbackPlaylist1Read aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionRead(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionReadList(THandle aProvider, CallbackPlaylist1ReadList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionReadList(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionInsert(THandle aProvider, CallbackPlaylist1Insert aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionInsert(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionDeleteId(THandle aProvider, CallbackPlaylist1DeleteId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionDeleteId(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionDeleteAll(THandle aProvider, CallbackPlaylist1DeleteAll aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionDeleteAll(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionTracksMax(THandle aProvider, CallbackPlaylist1TracksMax aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionTracksMax(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionIdArray(THandle aProvider, CallbackPlaylist1IdArray aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionIdArray(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionIdArrayChanged(THandle aProvider, CallbackPlaylist1IdArrayChanged aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionIdArrayChanged(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionProtocolInfo(THandle aProvider, CallbackPlaylist1ProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnableActionProtocolInfo(aCallback, aPtr);
}

int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->SetPropertyTransportState(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyTransportState(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->GetPropertyTransportState(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyRepeat(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->SetPropertyRepeat((aValue!=0))? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyRepeat(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->GetPropertyRepeat(val);
    *aValue = (val? 1 : 0);
}

int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyShuffle(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->SetPropertyShuffle((aValue!=0))? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyShuffle(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->GetPropertyShuffle(val);
    *aValue = (val? 1 : 0);
}

int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyId(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->SetPropertyId(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyId(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->GetPropertyId(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->SetPropertyIdArray(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->GetPropertyIdArray(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyTracksMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->SetPropertyTracksMax(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyTracksMax(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->GetPropertyTracksMax(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->SetPropertyProtocolInfo(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->GetPropertyProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyTransportState(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnablePropertyTransportState();
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyRepeat(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnablePropertyRepeat();
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyShuffle(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnablePropertyShuffle();
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyId(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnablePropertyId();
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyIdArray(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnablePropertyIdArray();
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyTracksMax(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnablePropertyTracksMax();
}

void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyProtocolInfo(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylist1C*>(aProvider)->EnablePropertyProtocolInfo();
}

