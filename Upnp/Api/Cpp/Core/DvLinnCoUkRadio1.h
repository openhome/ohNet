#ifndef HEADER_DVLINNCOUKRADIO1
#define HEADER_DVLINNCOUKRADIO1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Radio:1
 */
class DvProviderLinnCoUkRadio1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkRadio1() {}
    TBool SetPropertyChannelUri(const Brx& aValue);
    void GetPropertyChannelUri(Brhz& aValue);
    TBool SetPropertyChannelMetadata(const Brx& aValue);
    void GetPropertyChannelMetadata(Brhz& aValue);
    TBool SetPropertyTransportState(const Brx& aValue);
    void GetPropertyTransportState(Brhz& aValue);
    TBool SetPropertyProtocolInfo(const Brx& aValue);
    void GetPropertyProtocolInfo(Brhz& aValue);
    TBool SetPropertyId(TUint aValue);
    void GetPropertyId(TUint& aValue);
    TBool SetPropertyIdArray(const Brx& aValue);
    void GetPropertyIdArray(Brh& aValue);
    TBool SetPropertyIdsMax(TUint aValue);
    void GetPropertyIdsMax(TUint& aValue);
protected:
    DvProviderLinnCoUkRadio1(DvDevice& aDevice);
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
    DvProviderLinnCoUkRadio1();
    void DoPlay(IDviInvocation& aInvocation, TUint aVersion);
    void DoPause(IDviInvocation& aInvocation, TUint aVersion);
    void DoStop(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondAbsolute(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeekSecondRelative(IDviInvocation& aInvocation, TUint aVersion);
    void DoChannel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetChannel(IDviInvocation& aInvocation, TUint aVersion);
    void DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoTransportState(IDviInvocation& aInvocation, TUint aVersion);
    void DoId(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetId(IDviInvocation& aInvocation, TUint aVersion);
    void DoRead(IDviInvocation& aInvocation, TUint aVersion);
    void DoReadList(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdArray(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdsMax(IDviInvocation& aInvocation, TUint aVersion);
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

