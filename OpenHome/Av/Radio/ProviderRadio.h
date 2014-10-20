#ifndef HEADER_PROVIDER_RADIO
#define HEADER_PROVIDER_RADIO

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <Generated/DvAvOpenhomeOrgRadio1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Av/Radio/PresetDatabase.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Av/Radio/SourceRadio.h>

namespace OpenHome {
using namespace Net;
namespace Av {

class IPresetDatabaseReader;

class ProviderRadio : public DvProviderAvOpenhomeOrgRadio1, private IPresetDatabaseObserver
{
public:
    ProviderRadio(Net::DvDevice& aDevice, ISourceRadio& aSource, IPresetDatabaseReader& aDbReader, const Brx& aProtocolInfo);
    ~ProviderRadio();
    void SetTransportState(Media::EPipelineState aState);
private: // from IPresetDatabaseObserver
    void PresetDatabaseChanged();
private: // from DvProviderAvOpenhomeOrgRadio1
    void Play(IDvInvocation& aInvocation);
    void Pause(IDvInvocation& aInvocation);
    void Stop(IDvInvocation& aInvocation);
    void SeekSecondAbsolute(IDvInvocation& aInvocation, TUint aValue);
    void SeekSecondRelative(IDvInvocation& aInvocation, TInt aValue);
    void Channel(IDvInvocation& aInvocation, IDvInvocationResponseString& aUri, IDvInvocationResponseString& aMetadata);
    void SetChannel(IDvInvocation& aInvocation, const Brx& aUri, const Brx& aMetadata);
    void TransportState(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
    void Id(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
    void SetId(IDvInvocation& aInvocation, TUint aValue, const Brx& aUri);
    void Read(IDvInvocation& aInvocation, TUint aId, IDvInvocationResponseString& aMetadata);
    void ReadList(IDvInvocation& aInvocation, const Brx& aIdList, IDvInvocationResponseString& aChannelList);
    void IdArray(IDvInvocation& aInvocation, IDvInvocationResponseUint& aToken, IDvInvocationResponseBinary& aArray);
    void IdArrayChanged(IDvInvocation& aInvocation, TUint aToken, IDvInvocationResponseBool& aValue);
    void ChannelsMax(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
    void ProtocolInfo(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
private:
    void SetChannel(TUint aPresetId, const Brx& aUri, const Brx& aMetadata);
    void UpdateIdArray();
    void UpdateIdArrayProperty();
private:
    mutable Mutex iLock;
    ISourceRadio& iSource;
    IPresetDatabaseReader& iDbReader;
    Brn iProtocolInfo;
    TUint iDbSeq;
    Media::BwsTrackUri iUri;
    Media::BwsTrackMetaData iMetaData;
    std::array<TUint, IPresetDatabaseReader::kMaxPresets> iIdArray;
    Bws<IPresetDatabaseReader::kMaxPresets * sizeof(TUint32)> iIdArrayBuf;
    // only required locally by certain functions but too large for the stack
    Mutex iTempVarLock;
    Media::BwsTrackUri iTempUri;
    Media::BwsTrackMetaData iTempMetadata;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_RADIO
