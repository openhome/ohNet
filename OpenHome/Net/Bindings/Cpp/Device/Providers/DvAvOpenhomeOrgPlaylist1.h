#ifndef HEADER_DVAVOPENHOMEORGPLAYLIST1CPP
#define HEADER_DVAVOPENHOMEORGPLAYLIST1CPP

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>

#include <string>

namespace OpenHome {
namespace Net {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the av.openhome.org:Playlist:1 UPnP service
 * @ingroup Providers
 */
class DvProviderAvOpenhomeOrgPlaylist1Cpp : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgPlaylist1Cpp() {}
    /**
     * Set the value of the TransportState property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTransportState(const std::string& aValue);
    /**
     * Get a copy of the value of the TransportState property
     */
    void GetPropertyTransportState(std::string& aValue);
    /**
     * Set the value of the Repeat property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyRepeat(bool aValue);
    /**
     * Get a copy of the value of the Repeat property
     */
    void GetPropertyRepeat(bool& aValue);
    /**
     * Set the value of the Shuffle property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyShuffle(bool aValue);
    /**
     * Get a copy of the value of the Shuffle property
     */
    void GetPropertyShuffle(bool& aValue);
    /**
     * Set the value of the Id property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyId(uint32_t aValue);
    /**
     * Get a copy of the value of the Id property
     */
    void GetPropertyId(uint32_t& aValue);
    /**
     * Set the value of the IdArray property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyIdArray(const std::string& aValue);
    /**
     * Get a copy of the value of the IdArray property
     */
    void GetPropertyIdArray(std::string& aValue);
    /**
     * Set the value of the TracksMax property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTracksMax(uint32_t aValue);
    /**
     * Get a copy of the value of the TracksMax property
     */
    void GetPropertyTracksMax(uint32_t& aValue);
    /**
     * Set the value of the ProtocolInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProtocolInfo(const std::string& aValue);
    /**
     * Get a copy of the value of the ProtocolInfo property
     */
    void GetPropertyProtocolInfo(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgPlaylist1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action Play is supported.
     * The action's availability will be published in the device's service.xml.
     * Play must be overridden if this is called.
     */
    void EnableActionPlay();
    /**
     * Signal that the action Pause is supported.
     * The action's availability will be published in the device's service.xml.
     * Pause must be overridden if this is called.
     */
    void EnableActionPause();
    /**
     * Signal that the action Stop is supported.
     * The action's availability will be published in the device's service.xml.
     * Stop must be overridden if this is called.
     */
    void EnableActionStop();
    /**
     * Signal that the action Next is supported.
     * The action's availability will be published in the device's service.xml.
     * Next must be overridden if this is called.
     */
    void EnableActionNext();
    /**
     * Signal that the action Previous is supported.
     * The action's availability will be published in the device's service.xml.
     * Previous must be overridden if this is called.
     */
    void EnableActionPrevious();
    /**
     * Signal that the action SetRepeat is supported.
     * The action's availability will be published in the device's service.xml.
     * SetRepeat must be overridden if this is called.
     */
    void EnableActionSetRepeat();
    /**
     * Signal that the action Repeat is supported.
     * The action's availability will be published in the device's service.xml.
     * Repeat must be overridden if this is called.
     */
    void EnableActionRepeat();
    /**
     * Signal that the action SetShuffle is supported.
     * The action's availability will be published in the device's service.xml.
     * SetShuffle must be overridden if this is called.
     */
    void EnableActionSetShuffle();
    /**
     * Signal that the action Shuffle is supported.
     * The action's availability will be published in the device's service.xml.
     * Shuffle must be overridden if this is called.
     */
    void EnableActionShuffle();
    /**
     * Signal that the action SeekSecondAbsolute is supported.
     * The action's availability will be published in the device's service.xml.
     * SeekSecondAbsolute must be overridden if this is called.
     */
    void EnableActionSeekSecondAbsolute();
    /**
     * Signal that the action SeekSecondRelative is supported.
     * The action's availability will be published in the device's service.xml.
     * SeekSecondRelative must be overridden if this is called.
     */
    void EnableActionSeekSecondRelative();
    /**
     * Signal that the action SeekId is supported.
     * The action's availability will be published in the device's service.xml.
     * SeekId must be overridden if this is called.
     */
    void EnableActionSeekId();
    /**
     * Signal that the action SeekIndex is supported.
     * The action's availability will be published in the device's service.xml.
     * SeekIndex must be overridden if this is called.
     */
    void EnableActionSeekIndex();
    /**
     * Signal that the action TransportState is supported.
     * The action's availability will be published in the device's service.xml.
     * TransportState must be overridden if this is called.
     */
    void EnableActionTransportState();
    /**
     * Signal that the action Id is supported.
     * The action's availability will be published in the device's service.xml.
     * Id must be overridden if this is called.
     */
    void EnableActionId();
    /**
     * Signal that the action Read is supported.
     * The action's availability will be published in the device's service.xml.
     * Read must be overridden if this is called.
     */
    void EnableActionRead();
    /**
     * Signal that the action ReadList is supported.
     * The action's availability will be published in the device's service.xml.
     * ReadList must be overridden if this is called.
     */
    void EnableActionReadList();
    /**
     * Signal that the action Insert is supported.
     * The action's availability will be published in the device's service.xml.
     * Insert must be overridden if this is called.
     */
    void EnableActionInsert();
    /**
     * Signal that the action DeleteId is supported.
     * The action's availability will be published in the device's service.xml.
     * DeleteId must be overridden if this is called.
     */
    void EnableActionDeleteId();
    /**
     * Signal that the action DeleteAll is supported.
     * The action's availability will be published in the device's service.xml.
     * DeleteAll must be overridden if this is called.
     */
    void EnableActionDeleteAll();
    /**
     * Signal that the action TracksMax is supported.
     * The action's availability will be published in the device's service.xml.
     * TracksMax must be overridden if this is called.
     */
    void EnableActionTracksMax();
    /**
     * Signal that the action IdArray is supported.
     * The action's availability will be published in the device's service.xml.
     * IdArray must be overridden if this is called.
     */
    void EnableActionIdArray();
    /**
     * Signal that the action IdArrayChanged is supported.
     * The action's availability will be published in the device's service.xml.
     * IdArrayChanged must be overridden if this is called.
     */
    void EnableActionIdArrayChanged();
    /**
     * Signal that the action ProtocolInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * ProtocolInfo must be overridden if this is called.
     */
    void EnableActionProtocolInfo();
private:
    /**
     * Play action.
     *
     * Will be called when the device stack receives an invocation of the
     * Play action for the owning device.
     * Must be implemented iff EnableActionPlay was called.
     */
    virtual void Play(IDvInvocationStd& aInvocation);
    /**
     * Pause action.
     *
     * Will be called when the device stack receives an invocation of the
     * Pause action for the owning device.
     * Must be implemented iff EnableActionPause was called.
     */
    virtual void Pause(IDvInvocationStd& aInvocation);
    /**
     * Stop action.
     *
     * Will be called when the device stack receives an invocation of the
     * Stop action for the owning device.
     * Must be implemented iff EnableActionStop was called.
     */
    virtual void Stop(IDvInvocationStd& aInvocation);
    /**
     * Next action.
     *
     * Will be called when the device stack receives an invocation of the
     * Next action for the owning device.
     * Must be implemented iff EnableActionNext was called.
     */
    virtual void Next(IDvInvocationStd& aInvocation);
    /**
     * Previous action.
     *
     * Will be called when the device stack receives an invocation of the
     * Previous action for the owning device.
     * Must be implemented iff EnableActionPrevious was called.
     */
    virtual void Previous(IDvInvocationStd& aInvocation);
    /**
     * SetRepeat action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRepeat action for the owning device.
     * Must be implemented iff EnableActionSetRepeat was called.
     */
    virtual void SetRepeat(IDvInvocationStd& aInvocation, bool aValue);
    /**
     * Repeat action.
     *
     * Will be called when the device stack receives an invocation of the
     * Repeat action for the owning device.
     * Must be implemented iff EnableActionRepeat was called.
     */
    virtual void Repeat(IDvInvocationStd& aInvocation, bool& aValue);
    /**
     * SetShuffle action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetShuffle action for the owning device.
     * Must be implemented iff EnableActionSetShuffle was called.
     */
    virtual void SetShuffle(IDvInvocationStd& aInvocation, bool aValue);
    /**
     * Shuffle action.
     *
     * Will be called when the device stack receives an invocation of the
     * Shuffle action for the owning device.
     * Must be implemented iff EnableActionShuffle was called.
     */
    virtual void Shuffle(IDvInvocationStd& aInvocation, bool& aValue);
    /**
     * SeekSecondAbsolute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondAbsolute action for the owning device.
     * Must be implemented iff EnableActionSeekSecondAbsolute was called.
     */
    virtual void SeekSecondAbsolute(IDvInvocationStd& aInvocation, uint32_t aValue);
    /**
     * SeekSecondRelative action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekSecondRelative action for the owning device.
     * Must be implemented iff EnableActionSeekSecondRelative was called.
     */
    virtual void SeekSecondRelative(IDvInvocationStd& aInvocation, int32_t aValue);
    /**
     * SeekId action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekId action for the owning device.
     * Must be implemented iff EnableActionSeekId was called.
     */
    virtual void SeekId(IDvInvocationStd& aInvocation, uint32_t aValue);
    /**
     * SeekIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * SeekIndex action for the owning device.
     * Must be implemented iff EnableActionSeekIndex was called.
     */
    virtual void SeekIndex(IDvInvocationStd& aInvocation, uint32_t aValue);
    /**
     * TransportState action.
     *
     * Will be called when the device stack receives an invocation of the
     * TransportState action for the owning device.
     * Must be implemented iff EnableActionTransportState was called.
     */
    virtual void TransportState(IDvInvocationStd& aInvocation, std::string& aValue);
    /**
     * Id action.
     *
     * Will be called when the device stack receives an invocation of the
     * Id action for the owning device.
     * Must be implemented iff EnableActionId was called.
     */
    virtual void Id(IDvInvocationStd& aInvocation, uint32_t& aValue);
    /**
     * Read action.
     *
     * Will be called when the device stack receives an invocation of the
     * Read action for the owning device.
     * Must be implemented iff EnableActionRead was called.
     */
    virtual void Read(IDvInvocationStd& aInvocation, uint32_t aId, std::string& aUri, std::string& aMetadata);
    /**
     * ReadList action.
     *
     * Will be called when the device stack receives an invocation of the
     * ReadList action for the owning device.
     * Must be implemented iff EnableActionReadList was called.
     */
    virtual void ReadList(IDvInvocationStd& aInvocation, const std::string& aIdList, std::string& aTrackList);
    /**
     * Insert action.
     *
     * Will be called when the device stack receives an invocation of the
     * Insert action for the owning device.
     * Must be implemented iff EnableActionInsert was called.
     */
    virtual void Insert(IDvInvocationStd& aInvocation, uint32_t aAfterId, const std::string& aUri, const std::string& aMetadata, uint32_t& aNewId);
    /**
     * DeleteId action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteId action for the owning device.
     * Must be implemented iff EnableActionDeleteId was called.
     */
    virtual void DeleteId(IDvInvocationStd& aInvocation, uint32_t aValue);
    /**
     * DeleteAll action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteAll action for the owning device.
     * Must be implemented iff EnableActionDeleteAll was called.
     */
    virtual void DeleteAll(IDvInvocationStd& aInvocation);
    /**
     * TracksMax action.
     *
     * Will be called when the device stack receives an invocation of the
     * TracksMax action for the owning device.
     * Must be implemented iff EnableActionTracksMax was called.
     */
    virtual void TracksMax(IDvInvocationStd& aInvocation, uint32_t& aValue);
    /**
     * IdArray action.
     *
     * Will be called when the device stack receives an invocation of the
     * IdArray action for the owning device.
     * Must be implemented iff EnableActionIdArray was called.
     */
    virtual void IdArray(IDvInvocationStd& aInvocation, uint32_t& aToken, std::string& aArray);
    /**
     * IdArrayChanged action.
     *
     * Will be called when the device stack receives an invocation of the
     * IdArrayChanged action for the owning device.
     * Must be implemented iff EnableActionIdArrayChanged was called.
     */
    virtual void IdArrayChanged(IDvInvocationStd& aInvocation, uint32_t aToken, bool& aValue);
    /**
     * ProtocolInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * ProtocolInfo action for the owning device.
     * Must be implemented iff EnableActionProtocolInfo was called.
     */
    virtual void ProtocolInfo(IDvInvocationStd& aInvocation, std::string& aValue);
private:
    DvProviderAvOpenhomeOrgPlaylist1Cpp();
    void DoPlay(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPause(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStop(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoNext(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPrevious(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetRepeat(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoRepeat(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetShuffle(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoShuffle(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSeekSecondAbsolute(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSeekSecondRelative(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSeekId(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSeekIndex(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoTransportState(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoId(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoRead(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoReadList(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoInsert(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDeleteId(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDeleteAll(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoTracksMax(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoIdArray(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoIdArrayChanged(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoProtocolInfo(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyTransportState;
    PropertyBool* iPropertyRepeat;
    PropertyBool* iPropertyShuffle;
    PropertyUint* iPropertyId;
    PropertyBinary* iPropertyIdArray;
    PropertyUint* iPropertyTracksMax;
    PropertyString* iPropertyProtocolInfo;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGPLAYLIST1CPP

