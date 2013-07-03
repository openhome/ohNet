#include <OpenHome/Av/Playlist/ProviderPlaylist.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <Generated/DvAvOpenhomeOrgPlaylist1.h>
#include <OpenHome/Av/Radio/PresetDatabase.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/FaultCode.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;

// ProviderPlaylist

ProviderPlaylist::ProviderPlaylist(Net::DvDevice& aDevice)
    : DvProviderAvOpenhomeOrgPlaylist1(aDevice)
{
    EnablePropertyTransportState();
    EnablePropertyRepeat();
    EnablePropertyShuffle();
    EnablePropertyId();
    EnablePropertyIdArray();
    EnablePropertyTracksMax();
    EnablePropertyProtocolInfo();

    EnableActionPlay();
    EnableActionPause();
    EnableActionStop();
    EnableActionNext();
    EnableActionPrevious();
    EnableActionSetRepeat();
    EnableActionRepeat();
    EnableActionSetShuffle();
    EnableActionShuffle();
    EnableActionSeekSecondAbsolute();
    EnableActionSeekSecondRelative();
    EnableActionSeekId();
    EnableActionSeekIndex();
    EnableActionTransportState();
    EnableActionId();
    EnableActionRead();
    EnableActionReadList();
    EnableActionInsert();
    EnableActionDeleteId();
    EnableActionDeleteAll();
    EnableActionTracksMax();
    EnableActionIdArray();
    EnableActionIdArrayChanged();
    EnableActionProtocolInfo();
}

void ProviderPlaylist::Play(IDvInvocation& aInvocation)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::Pause(IDvInvocation& aInvocation)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::Stop(IDvInvocation& aInvocation)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::Next(IDvInvocation& aInvocation)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::Previous(IDvInvocation& aInvocation)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::SetRepeat(IDvInvocation& aInvocation, TBool /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::Repeat(IDvInvocation& aInvocation, IDvInvocationResponseBool& /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::SetShuffle(IDvInvocation& aInvocation, TBool /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::Shuffle(IDvInvocation& aInvocation, IDvInvocationResponseBool& /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::SeekSecondAbsolute(IDvInvocation& aInvocation, TUint /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::SeekSecondRelative(IDvInvocation& aInvocation, TInt /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::SeekId(IDvInvocation& aInvocation, TUint /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::SeekIndex(IDvInvocation& aInvocation, TUint /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::TransportState(IDvInvocation& aInvocation, IDvInvocationResponseString& /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::Id(IDvInvocation& aInvocation, IDvInvocationResponseUint& /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::Read(IDvInvocation& aInvocation, TUint /*aId*/, IDvInvocationResponseString& /*aUri*/, IDvInvocationResponseString& /*aMetadata*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::ReadList(IDvInvocation& aInvocation, const Brx& /*aIdList*/, IDvInvocationResponseString& /*aTrackList*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::Insert(IDvInvocation& aInvocation, TUint /*aAfterId*/, const Brx& /*aUri*/, const Brx& /*aMetadata*/, IDvInvocationResponseUint& /*aNewId*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::DeleteId(IDvInvocation& aInvocation, TUint /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::DeleteAll(IDvInvocation& aInvocation)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::TracksMax(IDvInvocation& aInvocation, IDvInvocationResponseUint& /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::IdArray(IDvInvocation& aInvocation, IDvInvocationResponseUint& /*aToken*/, IDvInvocationResponseBinary& /*aArray*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::IdArrayChanged(IDvInvocation& aInvocation, TUint /*aToken*/, IDvInvocationResponseBool& /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}

void ProviderPlaylist::ProtocolInfo(IDvInvocation& aInvocation, IDvInvocationResponseString& /*aValue*/)
{
    FaultCode::Report(aInvocation, FaultCode::kActionNotImplemented); // FIXME
}
