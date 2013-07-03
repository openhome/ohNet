#ifndef HEADER_PROVIDER_PLAYLIST
#define HEADER_PROVIDER_PLAYLIST

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <Generated/DvAvOpenhomeOrgPlaylist1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>

namespace OpenHome {
using namespace Net;
namespace Av {

class ProviderPlaylist : public DvProviderAvOpenhomeOrgPlaylist1
{
public:
    ProviderPlaylist(Net::DvDevice& aDevice);
private: // from DvProviderAvOpenhomeOrgPlaylist1
    void Play(IDvInvocation& aInvocation);
    void Pause(IDvInvocation& aInvocation);
    void Stop(IDvInvocation& aInvocation);
    void Next(IDvInvocation& aInvocation);
    void Previous(IDvInvocation& aInvocation);
    void SetRepeat(IDvInvocation& aInvocation, TBool aValue);
    void Repeat(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue);
    void SetShuffle(IDvInvocation& aInvocation, TBool aValue);
    void Shuffle(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue);
    void SeekSecondAbsolute(IDvInvocation& aInvocation, TUint aValue);
    void SeekSecondRelative(IDvInvocation& aInvocation, TInt aValue);
    void SeekId(IDvInvocation& aInvocation, TUint aValue);
    void SeekIndex(IDvInvocation& aInvocation, TUint aValue);
    void TransportState(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
    void Id(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
    void Read(IDvInvocation& aInvocation, TUint aId, IDvInvocationResponseString& aUri, IDvInvocationResponseString& aMetadata);
    void ReadList(IDvInvocation& aInvocation, const Brx& aIdList, IDvInvocationResponseString& aTrackList);
    void Insert(IDvInvocation& aInvocation, TUint aAfterId, const Brx& aUri, const Brx& aMetadata, IDvInvocationResponseUint& aNewId);
    void DeleteId(IDvInvocation& aInvocation, TUint aValue);
    void DeleteAll(IDvInvocation& aInvocation);
    void TracksMax(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
    void IdArray(IDvInvocation& aInvocation, IDvInvocationResponseUint& aToken, IDvInvocationResponseBinary& aArray);
    void IdArrayChanged(IDvInvocation& aInvocation, TUint aToken, IDvInvocationResponseBool& aValue);
    void ProtocolInfo(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_PLAYLIST
