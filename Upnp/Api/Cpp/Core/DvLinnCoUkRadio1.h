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
 * Provider for the linn.co.uk:Radio:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkRadio1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkRadio1() {}
    /**
     * Set the value of the ChannelUri property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyChannelUri(const Brx& aValue);
    /**
     * Get a copy of the value of the ChannelUri property
     */
    void GetPropertyChannelUri(Brhz& aValue);
    /**
     * Set the value of the ChannelMetadata property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyChannelMetadata(const Brx& aValue);
    /**
     * Get a copy of the value of the ChannelMetadata property
     */
    void GetPropertyChannelMetadata(Brhz& aValue);
    /**
     * Set the value of the TransportState property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTransportState(const Brx& aValue);
    /**
     * Get a copy of the value of the TransportState property
     */
    void GetPropertyTransportState(Brhz& aValue);
    /**
     * Set the value of the ProtocolInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProtocolInfo(const Brx& aValue);
    /**
     * Get a copy of the value of the ProtocolInfo property
     */
    void GetPropertyProtocolInfo(Brhz& aValue);
    /**
     * Set the value of the Id property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyId(TUint aValue);
    /**
     * Get a copy of the value of the Id property
     */
    void GetPropertyId(TUint& aValue);
    /**
     * Set the value of the IdArray property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyIdArray(const Brx& aValue);
    /**
     * Get a copy of the value of the IdArray property
     */
    void GetPropertyIdArray(Brh& aValue);
    /**
     * Set the value of the IdsMax property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyIdsMax(TUint aValue);
    /**
     * Get a copy of the value of the IdsMax property
     */
    void GetPropertyIdsMax(TUint& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkRadio1(DvDevice& aDevice);
    /**
     * Signal that the action Play is supported.
     * The action's availability will be published in the device's service.xml.
     * DoPlay must be overridden if this is called.
     */
    void EnableActionPlay();
    /**
     * Signal that the action Pause is supported.
     * The action's availability will be published in the device's service.xml.
     * DoPause must be overridden if this is called.
     */
    void EnableActionPause();
    /**
     * Signal that the action Stop is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStop must be overridden if this is called.
     */
    void EnableActionStop();
    /**
     * Signal that the action SeekSecondAbsolute is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSeekSecondAbsolute must be overridden if this is called.
     */
    void EnableActionSeekSecondAbsolute();
    /**
     * Signal that the action SeekSecondRelative is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSeekSecondRelative must be overridden if this is called.
     */
    void EnableActionSeekSecondRelative();
    /**
     * Signal that the action Channel is supported.
     * The action's availability will be published in the device's service.xml.
     * DoChannel must be overridden if this is called.
     */
    void EnableActionChannel();
    /**
     * Signal that the action SetChannel is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetChannel must be overridden if this is called.
     */
    void EnableActionSetChannel();
    /**
     * Signal that the action ProtocolInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * DoProtocolInfo must be overridden if this is called.
     */
    void EnableActionProtocolInfo();
    /**
     * Signal that the action TransportState is supported.
     * The action's availability will be published in the device's service.xml.
     * DoTransportState must be overridden if this is called.
     */
    void EnableActionTransportState();
    /**
     * Signal that the action Id is supported.
     * The action's availability will be published in the device's service.xml.
     * DoId must be overridden if this is called.
     */
    void EnableActionId();
    /**
     * Signal that the action SetId is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetId must be overridden if this is called.
     */
    void EnableActionSetId();
    /**
     * Signal that the action Read is supported.
     * The action's availability will be published in the device's service.xml.
     * DoRead must be overridden if this is called.
     */
    void EnableActionRead();
    /**
     * Signal that the action ReadList is supported.
     * The action's availability will be published in the device's service.xml.
     * DoReadList must be overridden if this is called.
     */
    void EnableActionReadList();
    /**
     * Signal that the action IdArray is supported.
     * The action's availability will be published in the device's service.xml.
     * DoIdArray must be overridden if this is called.
     */
    void EnableActionIdArray();
    /**
     * Signal that the action IdArrayChanged is supported.
     * The action's availability will be published in the device's service.xml.
     * DoIdArrayChanged must be overridden if this is called.
     */
    void EnableActionIdArrayChanged();
    /**
     * Signal that the action IdsMax is supported.
     * The action's availability will be published in the device's service.xml.
     * DoIdsMax must be overridden if this is called.
     */
    void EnableActionIdsMax();
private:
    /**
     * Play action.
     *
     * Will be called when the device stack receives an invocation of the
     * Play action for the owning device.
     * Must be implemented iff EnableActionPlay was called.
     */
    virtual void Play(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * Pause action.
     *
     * Will be called when the device stack receives an invocation of the
     * Pause action for the owning device.
     * Must be implemented iff EnableActionPause was called.
     */
    virtual void Pause(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * Stop action.
     *
     * Will be called when the device stack receives an invocation of the
     * Stop action for the owning device.
     * Must be implemented iff EnableActionStop was called.
     */
    virtual void Stop(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * SeekSecondAbsolute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondAbsolute action for the owning device.
     * Must be implemented iff EnableActionSeekSecondAbsolute was called.
     */
    virtual void SeekSecondAbsolute(IInvocationResponse& aResponse, TUint aVersion, TUint aaSecond);
    /**
     * SeekSecondRelative action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondRelative action for the owning device.
     * Must be implemented iff EnableActionSeekSecondRelative was called.
     */
    virtual void SeekSecondRelative(IInvocationResponse& aResponse, TUint aVersion, TInt aaSecond);
    /**
     * Channel action.
     *
     * Will be called when the device stack receives an invocation of the
     * Channel action for the owning device.
     * Must be implemented iff EnableActionChannel was called.
     */
    virtual void Channel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetadata);
    /**
     * SetChannel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetChannel action for the owning device.
     * Must be implemented iff EnableActionSetChannel was called.
     */
    virtual void SetChannel(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaUri, const Brx& aaMetadata);
    /**
     * ProtocolInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * ProtocolInfo action for the owning device.
     * Must be implemented iff EnableActionProtocolInfo was called.
     */
    virtual void ProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaInfo);
    /**
     * TransportState action.
     *
     * Will be called when the device stack receives an invocation of the
     * TransportState action for the owning device.
     * Must be implemented iff EnableActionTransportState was called.
     */
    virtual void TransportState(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaState);
    /**
     * Id action.
     *
     * Will be called when the device stack receives an invocation of the
     * Id action for the owning device.
     * Must be implemented iff EnableActionId was called.
     */
    virtual void Id(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaId);
    /**
     * SetId action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetId action for the owning device.
     * Must be implemented iff EnableActionSetId was called.
     */
    virtual void SetId(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, const Brx& aaUri);
    /**
     * Read action.
     *
     * Will be called when the device stack receives an invocation of the
     * Read action for the owning device.
     * Must be implemented iff EnableActionRead was called.
     */
    virtual void Read(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, IInvocationResponseString& aaMetadata);
    /**
     * ReadList action.
     *
     * Will be called when the device stack receives an invocation of the
     * ReadList action for the owning device.
     * Must be implemented iff EnableActionReadList was called.
     */
    virtual void ReadList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIdList, IInvocationResponseString& aaMetadataList);
    /**
     * IdArray action.
     *
     * Will be called when the device stack receives an invocation of the
     * IdArray action for the owning device.
     * Must be implemented iff EnableActionIdArray was called.
     */
    virtual void IdArray(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIdArrayToken, IInvocationResponseBinary& aaIdArray);
    /**
     * IdArrayChanged action.
     *
     * Will be called when the device stack receives an invocation of the
     * IdArrayChanged action for the owning device.
     * Must be implemented iff EnableActionIdArrayChanged was called.
     */
    virtual void IdArrayChanged(IInvocationResponse& aResponse, TUint aVersion, TUint aaIdArrayToken, IInvocationResponseBool& aaIdArrayChanged);
    /**
     * IdsMax action.
     *
     * Will be called when the device stack receives an invocation of the
     * IdsMax action for the owning device.
     * Must be implemented iff EnableActionIdsMax was called.
     */
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

