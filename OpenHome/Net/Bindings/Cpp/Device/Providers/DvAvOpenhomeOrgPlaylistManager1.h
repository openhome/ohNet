#ifndef HEADER_DVAVOPENHOMEORGPLAYLISTMANAGER1CPP
#define HEADER_DVAVOPENHOMEORGPLAYLISTMANAGER1CPP

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

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
 * Provider for the av.openhome.org:PlaylistManager:1 UPnP service
 * @ingroup Providers
 */
class DvProviderAvOpenhomeOrgPlaylistManager1Cpp : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgPlaylistManager1Cpp() {}
    /**
     * Set the value of the Metadata property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyMetadata(const std::string& aValue);
    /**
     * Get a copy of the value of the Metadata property
     */
    void GetPropertyMetadata(std::string& aValue);
    /**
     * Set the value of the ImagesXml property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyImagesXml(const std::string& aValue);
    /**
     * Get a copy of the value of the ImagesXml property
     */
    void GetPropertyImagesXml(std::string& aValue);
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
     * Set the value of the TokenArray property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTokenArray(const std::string& aValue);
    /**
     * Get a copy of the value of the TokenArray property
     */
    void GetPropertyTokenArray(std::string& aValue);
    /**
     * Set the value of the PlaylistsMax property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyPlaylistsMax(uint32_t aValue);
    /**
     * Get a copy of the value of the PlaylistsMax property
     */
    void GetPropertyPlaylistsMax(uint32_t& aValue);
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
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgPlaylistManager1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action Metadata is supported.
     * The action's availability will be published in the device's service.xml.
     * Metadata must be overridden if this is called.
     */
    void EnableActionMetadata();
    /**
     * Signal that the action ImagesXml is supported.
     * The action's availability will be published in the device's service.xml.
     * ImagesXml must be overridden if this is called.
     */
    void EnableActionImagesXml();
    /**
     * Signal that the action PlaylistReadArray is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistReadArray must be overridden if this is called.
     */
    void EnableActionPlaylistReadArray();
    /**
     * Signal that the action PlaylistReadList is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistReadList must be overridden if this is called.
     */
    void EnableActionPlaylistReadList();
    /**
     * Signal that the action PlaylistRead is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistRead must be overridden if this is called.
     */
    void EnableActionPlaylistRead();
    /**
     * Signal that the action PlaylistSetName is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistSetName must be overridden if this is called.
     */
    void EnableActionPlaylistSetName();
    /**
     * Signal that the action PlaylistSetDescription is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistSetDescription must be overridden if this is called.
     */
    void EnableActionPlaylistSetDescription();
    /**
     * Signal that the action PlaylistSetImageId is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistSetImageId must be overridden if this is called.
     */
    void EnableActionPlaylistSetImageId();
    /**
     * Signal that the action PlaylistInsert is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistInsert must be overridden if this is called.
     */
    void EnableActionPlaylistInsert();
    /**
     * Signal that the action PlaylistDeleteId is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistDeleteId must be overridden if this is called.
     */
    void EnableActionPlaylistDeleteId();
    /**
     * Signal that the action PlaylistMove is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistMove must be overridden if this is called.
     */
    void EnableActionPlaylistMove();
    /**
     * Signal that the action PlaylistsMax is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistsMax must be overridden if this is called.
     */
    void EnableActionPlaylistsMax();
    /**
     * Signal that the action TracksMax is supported.
     * The action's availability will be published in the device's service.xml.
     * TracksMax must be overridden if this is called.
     */
    void EnableActionTracksMax();
    /**
     * Signal that the action PlaylistArrays is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistArrays must be overridden if this is called.
     */
    void EnableActionPlaylistArrays();
    /**
     * Signal that the action PlaylistArraysChanged is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistArraysChanged must be overridden if this is called.
     */
    void EnableActionPlaylistArraysChanged();
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
private:
    /**
     * Metadata action.
     *
     * Will be called when the device stack receives an invocation of the
     * Metadata action for the owning device.
     * Must be implemented iff EnableActionMetadata was called.
     */
    virtual void Metadata(uint32_t aVersion, std::string& aMetadata);
    /**
     * ImagesXml action.
     *
     * Will be called when the device stack receives an invocation of the
     * ImagesXml action for the owning device.
     * Must be implemented iff EnableActionImagesXml was called.
     */
    virtual void ImagesXml(uint32_t aVersion, std::string& aImagesXml);
    /**
     * PlaylistReadArray action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistReadArray action for the owning device.
     * Must be implemented iff EnableActionPlaylistReadArray was called.
     */
    virtual void PlaylistReadArray(uint32_t aVersion, uint32_t aId, std::string& aArray);
    /**
     * PlaylistReadList action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistReadList action for the owning device.
     * Must be implemented iff EnableActionPlaylistReadList was called.
     */
    virtual void PlaylistReadList(uint32_t aVersion, const std::string& aIdList, std::string& aPlaylistList);
    /**
     * PlaylistRead action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistRead action for the owning device.
     * Must be implemented iff EnableActionPlaylistRead was called.
     */
    virtual void PlaylistRead(uint32_t aVersion, uint32_t aId, std::string& aName, std::string& aDescription, uint32_t& aImageId);
    /**
     * PlaylistSetName action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistSetName action for the owning device.
     * Must be implemented iff EnableActionPlaylistSetName was called.
     */
    virtual void PlaylistSetName(uint32_t aVersion, uint32_t aId, const std::string& aName);
    /**
     * PlaylistSetDescription action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistSetDescription action for the owning device.
     * Must be implemented iff EnableActionPlaylistSetDescription was called.
     */
    virtual void PlaylistSetDescription(uint32_t aVersion, uint32_t aId, const std::string& aDescription);
    /**
     * PlaylistSetImageId action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistSetImageId action for the owning device.
     * Must be implemented iff EnableActionPlaylistSetImageId was called.
     */
    virtual void PlaylistSetImageId(uint32_t aVersion, uint32_t aId, uint32_t aImageId);
    /**
     * PlaylistInsert action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistInsert action for the owning device.
     * Must be implemented iff EnableActionPlaylistInsert was called.
     */
    virtual void PlaylistInsert(uint32_t aVersion, uint32_t aAfterId, const std::string& aName, const std::string& aDescription, uint32_t aImageId, uint32_t& aNewId);
    /**
     * PlaylistDeleteId action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistDeleteId action for the owning device.
     * Must be implemented iff EnableActionPlaylistDeleteId was called.
     */
    virtual void PlaylistDeleteId(uint32_t aVersion, uint32_t aValue);
    /**
     * PlaylistMove action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistMove action for the owning device.
     * Must be implemented iff EnableActionPlaylistMove was called.
     */
    virtual void PlaylistMove(uint32_t aVersion, uint32_t aId, uint32_t aAfterId);
    /**
     * PlaylistsMax action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistsMax action for the owning device.
     * Must be implemented iff EnableActionPlaylistsMax was called.
     */
    virtual void PlaylistsMax(uint32_t aVersion, uint32_t& aValue);
    /**
     * TracksMax action.
     *
     * Will be called when the device stack receives an invocation of the
     * TracksMax action for the owning device.
     * Must be implemented iff EnableActionTracksMax was called.
     */
    virtual void TracksMax(uint32_t aVersion, uint32_t& aValue);
    /**
     * PlaylistArrays action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistArrays action for the owning device.
     * Must be implemented iff EnableActionPlaylistArrays was called.
     */
    virtual void PlaylistArrays(uint32_t aVersion, uint32_t& aToken, std::string& aIdArray, std::string& aTokenArray);
    /**
     * PlaylistArraysChanged action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistArraysChanged action for the owning device.
     * Must be implemented iff EnableActionPlaylistArraysChanged was called.
     */
    virtual void PlaylistArraysChanged(uint32_t aVersion, uint32_t aToken, bool& aValue);
    /**
     * Read action.
     *
     * Will be called when the device stack receives an invocation of the
     * Read action for the owning device.
     * Must be implemented iff EnableActionRead was called.
     */
    virtual void Read(uint32_t aVersion, uint32_t aId, uint32_t aTrackId, std::string& aMetadata);
    /**
     * ReadList action.
     *
     * Will be called when the device stack receives an invocation of the
     * ReadList action for the owning device.
     * Must be implemented iff EnableActionReadList was called.
     */
    virtual void ReadList(uint32_t aVersion, uint32_t aId, const std::string& aTrackIdList, std::string& aTrackList);
    /**
     * Insert action.
     *
     * Will be called when the device stack receives an invocation of the
     * Insert action for the owning device.
     * Must be implemented iff EnableActionInsert was called.
     */
    virtual void Insert(uint32_t aVersion, uint32_t aId, uint32_t aAfterTrackId, const std::string& aUdn, const std::string& aMetadataId, uint32_t& aNewTrackId);
    /**
     * DeleteId action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteId action for the owning device.
     * Must be implemented iff EnableActionDeleteId was called.
     */
    virtual void DeleteId(uint32_t aVersion, uint32_t aId, uint32_t aTrackId);
    /**
     * DeleteAll action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteAll action for the owning device.
     * Must be implemented iff EnableActionDeleteAll was called.
     */
    virtual void DeleteAll(uint32_t aVersion, uint32_t aId);
private:
    DvProviderAvOpenhomeOrgPlaylistManager1Cpp();
    void DoMetadata(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoImagesXml(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPlaylistReadArray(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPlaylistReadList(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPlaylistRead(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPlaylistSetName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPlaylistSetDescription(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPlaylistSetImageId(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPlaylistInsert(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPlaylistDeleteId(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPlaylistMove(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPlaylistsMax(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoTracksMax(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPlaylistArrays(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPlaylistArraysChanged(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoRead(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoReadList(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoInsert(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDeleteId(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDeleteAll(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyMetadata;
    PropertyString* iPropertyImagesXml;
    PropertyBinary* iPropertyIdArray;
    PropertyBinary* iPropertyTokenArray;
    PropertyUint* iPropertyPlaylistsMax;
    PropertyUint* iPropertyTracksMax;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGPLAYLISTMANAGER1CPP

