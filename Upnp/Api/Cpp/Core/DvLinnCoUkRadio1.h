#ifndef HEADER_DVLINNCOUKRADIO1
#define HEADER_DVLINNCOUKRADIO1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Radio:1
 */
class DvServiceLinnCoUkRadio1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkRadio1() {}
    void SetPropertyChannelUri(const Brx& aValue);
    void GetPropertyChannelUri(Brhz& aValue);
    void SetPropertyChannelMetadata(const Brx& aValue);
    void GetPropertyChannelMetadata(Brhz& aValue);
    void SetPropertyTransportState(const Brx& aValue);
    void GetPropertyTransportState(Brhz& aValue);
    void SetPropertyProtocolInfo(const Brx& aValue);
    void GetPropertyProtocolInfo(Brhz& aValue);
    void SetPropertyId(TUint aValue);
    void GetPropertyId(TUint& aValue);
    void SetPropertyIdArray(const Brx& aValue);
    void GetPropertyIdArray(Brh& aValue);
    void SetPropertyIdsMax(TUint aValue);
    void GetPropertyIdsMax(TUint& aValue);
protected:
    DvServiceLinnCoUkRadio1(DvDevice& aDevice);
    void EnableActionPlay();
    void EnableActionPause();
    void EnableActionStop();
    void EnableActionSeekSecondAbsolute();
    void EnableActionSeekSecondRelative();
    void EnableActionChannel();
    void EnableActionSetChannel();
    void EnableActionProtocolInfo();
    void EnableActionTransportState();
    void EnableActionId();
    void EnableActionSetId();
    void EnableActionRead();
    void EnableActionReadList();
    void EnableActionIdArray();
    void EnableActionIdArrayChanged();
    void EnableActionIdsMax();
private:
    virtual void Play(IInvocationResponse& aResponse, TUint aVersion);
    virtual void Pause(IInvocationResponse& aResponse, TUint aVersion);
    virtual void Stop(IInvocationResponse& aResponse, TUint aVersion);
    virtual void SeekSecondAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaSecond);
    virtual void SeekSecondRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaSecond);
    virtual void Channel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetadata);
    virtual void SetChannel(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaUri, const Brx& aaMetadata);
    virtual void ProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaInfo);
    virtual void TransportState(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaState);
    virtual void Id(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaId);
    virtual void SetId(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, const Brx& aaUri);
    virtual void Read(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, IInvocationResponseString& aaMetadata);
    virtual void ReadList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIdList, IInvocationResponseString& aaMetadataList);
    virtual void IdArray(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIdArrayToken, IInvocationResponseBinary& aaIdArray);
    virtual void IdArrayChanged(IInvocationResponse& aResponse, TUint aVersion, TUint aaIdArrayToken, IInvocationResponseBool& aaIdArrayChanged);
    virtual void IdsMax(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIdsMax);
private:
    DvServiceLinnCoUkRadio1();
    void DoPlay(IDvInvocation& aInvocation, TUint aVersion);
    void DoPause(IDvInvocation& aInvocation, TUint aVersion);
    void DoStop(IDvInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondAbsolute(IDvInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondRelative(IDvInvocation& aInvocation, TUint aVersion);
    void DoChannel(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetChannel(IDvInvocation& aInvocation, TUint aVersion);
    void DoProtocolInfo(IDvInvocation& aInvocation, TUint aVersion);
    void DoTransportState(IDvInvocation& aInvocation, TUint aVersion);
    void DoId(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetId(IDvInvocation& aInvocation, TUint aVersion);
    void DoRead(IDvInvocation& aInvocation, TUint aVersion);
    void DoReadList(IDvInvocation& aInvocation, TUint aVersion);
    void DoIdArray(IDvInvocation& aInvocation, TUint aVersion);
    void DoIdArrayChanged(IDvInvocation& aInvocation, TUint aVersion);
    void DoIdsMax(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyChannelUri;
    PropertyString* iPropertyChannelMetadata;
    PropertyString* iPropertyTransportState;
    PropertyString* iPropertyProtocolInfo;
    PropertyUint* iPropertyId;
    PropertyBinary* iPropertyIdArray;
    PropertyUint* iPropertyIdsMax;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKRADIO1

