#ifndef HEADER_PROVIDER_RADIO
#define HEADER_PROVIDER_RADIO

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <Generated/DvAvOpenHomeOrgRadio1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Av/Radio/RadioDatabase.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/PipelineObserver.h>

namespace OpenHome {
using namespace Net;
namespace Av {

class ISourceRadio
{
public:
    virtual ~ISourceRadio() {}
    virtual void Fetch(const Brx& aUri, const Brx& aMetaData) = 0;
    virtual void Play() = 0;
    virtual void Pause() = 0;
    virtual void Stop() = 0;
    virtual void Seek(TUint aSecondsAbsolute) = 0;
    virtual void SeekAbsolute(TUint aSeconds) = 0;
    virtual void SeekRelative(TUint aSeconds) = 0;
};

class IRadioDatabaseReader;

class ProviderRadio : public DvProviderAvOpenhomeOrgRadio1, private IRadioDatbaseObserver
{
public:
    ProviderRadio(Net::DvDevice& aDevice, ISourceRadio& aSource, IRadioDatabaseReader& aDbReader, const TChar* aProtocolInfo);
    ~ProviderRadio();
    void SetTransportState(Media::EPipelineState aState);
private: // from IRadioDatbaseObserver
    void RadioDatabaseChanged();
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
    Mutex iLock;
    ISourceRadio& iSource;
    IRadioDatabaseReader& iDbReader;
    Brn iProtocolInfo;
    TUint iDbSeq;
    Media::BwsTrackUri iUri;
    Media::BwsTrackMetaData iMetaData;
    std::array<TUint, IRadioDatabaseReader::kMaxPresets> iIdArray;
    Bws<IRadioDatabaseReader::kMaxPresets * sizeof(TUint32)> iIdArrayBuf;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROVIDER_RADIO
