#pragma once

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
namespace Av {

class IPresetDatabaseReader;

class ProviderRadio : public Net::DvProviderAvOpenhomeOrgRadio1, private IPresetDatabaseObserver
{
public:
    ProviderRadio(Net::DvDevice& aDevice, ISourceRadio& aSource, IPresetDatabaseReader& aDbReader);
    ~ProviderRadio();
    void SetTransportState(Media::EPipelineState aState);
    void NotifyProtocolInfo(const Brx& aProtocolInfo);
private: // from IPresetDatabaseObserver
    void PresetDatabaseChanged() override;
private: // from Net::DvProviderAvOpenhomeOrgRadio1
    void Play(Net::IDvInvocation& aInvocation) override;
    void Pause(Net::IDvInvocation& aInvocation) override;
    void Stop(Net::IDvInvocation& aInvocation) override;
    void SeekSecondAbsolute(Net::IDvInvocation& aInvocation, TUint aValue) override;
    void SeekSecondRelative(Net::IDvInvocation& aInvocation, TInt aValue) override;
    void Channel(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aUri, Net::IDvInvocationResponseString& aMetadata) override;
    void SetChannel(Net::IDvInvocation& aInvocation, const Brx& aUri, const Brx& aMetadata) override;
    void TransportState(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
    void Id(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue) override;
    void SetId(Net::IDvInvocation& aInvocation, TUint aValue, const Brx& aUri) override;
    void Read(Net::IDvInvocation& aInvocation, TUint aId, Net::IDvInvocationResponseString& aMetadata) override;
    void ReadList(Net::IDvInvocation& aInvocation, const Brx& aIdList, Net::IDvInvocationResponseString& aChannelList) override;
    void IdArray(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aToken, Net::IDvInvocationResponseBinary& aArray) override;
    void IdArrayChanged(Net::IDvInvocation& aInvocation, TUint aToken, Net::IDvInvocationResponseBool& aValue) override;
    void ChannelsMax(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseUint& aValue) override;
    void ProtocolInfo(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
private:
    void SetChannel(TUint aPresetId, const Brx& aUri, const Brx& aMetadata);
    void UpdateIdArray();
    void UpdateIdArrayProperty();
private:
    mutable Mutex iLock;
    Mutex iActionLock; // serialise actions that a control point may want to call sequentially (required by Kinsky)
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

