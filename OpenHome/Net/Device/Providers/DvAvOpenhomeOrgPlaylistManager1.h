#ifndef HEADER_DVAVOPENHOMEORGPLAYLISTMANAGER1
#define HEADER_DVAVOPENHOMEORGPLAYLISTMANAGER1

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

namespace OpenHome {
namespace Net {

class DviDevice;
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
class DvProviderAvOpenhomeOrgPlaylistManager1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgPlaylistManager1() {}
    /**
     * Set the value of the Metadata property
     *
     * Can only be called if EnablePropertyMetadata has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyMetadata(const Brx& aValue);
    /**
     * Get a copy of the value of the Metadata property
     *
     * Can only be called if EnablePropertyMetadata has previously been called.
     */
    void GetPropertyMetadata(Brhz& aValue);
    /**
     * Set the value of the ImagesXml property
     *
     * Can only be called if EnablePropertyImagesXml has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyImagesXml(const Brx& aValue);
    /**
     * Get a copy of the value of the ImagesXml property
     *
     * Can only be called if EnablePropertyImagesXml has previously been called.
     */
    void GetPropertyImagesXml(Brhz& aValue);
    /**
     * Set the value of the IdArray property
     *
     * Can only be called if EnablePropertyIdArray has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyIdArray(const Brx& aValue);
    /**
     * Get a copy of the value of the IdArray property
     *
     * Can only be called if EnablePropertyIdArray has previously been called.
     */
    void GetPropertyIdArray(Brh& aValue);
    /**
     * Set the value of the TokenArray property
     *
     * Can only be called if EnablePropertyTokenArray has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTokenArray(const Brx& aValue);
    /**
     * Get a copy of the value of the TokenArray property
     *
     * Can only be called if EnablePropertyTokenArray has previously been called.
     */
    void GetPropertyTokenArray(Brh& aValue);
    /**
     * Set the value of the PlaylistsMax property
     *
     * Can only be called if EnablePropertyPlaylistsMax has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyPlaylistsMax(TUint aValue);
    /**
     * Get a copy of the value of the PlaylistsMax property
     *
     * Can only be called if EnablePropertyPlaylistsMax has previously been called.
     */
    void GetPropertyPlaylistsMax(TUint& aValue);
    /**
     * Set the value of the TracksMax property
     *
     * Can only be called if EnablePropertyTracksMax has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTracksMax(TUint aValue);
    /**
     * Get a copy of the value of the TracksMax property
     *
     * Can only be called if EnablePropertyTracksMax has previously been called.
     */
    void GetPropertyTracksMax(TUint& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgPlaylistManager1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgPlaylistManager1(DviDevice& aDevice);
    /**
     * Enable the Metadata property.
     */
    void EnablePropertyMetadata();
    /**
     * Enable the ImagesXml property.
     */
    void EnablePropertyImagesXml();
    /**
     * Enable the IdArray property.
     */
    void EnablePropertyIdArray();
    /**
     * Enable the TokenArray property.
     */
    void EnablePropertyTokenArray();
    /**
     * Enable the PlaylistsMax property.
     */
    void EnablePropertyPlaylistsMax();
    /**
     * Enable the TracksMax property.
     */
    void EnablePropertyTracksMax();
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
    virtual void Metadata(IDvInvocation& aInvocation, IDvInvocationResponseString& aMetadata);
    /**
     * ImagesXml action.
     *
     * Will be called when the device stack receives an invocation of the
     * ImagesXml action for the owning device.
     * Must be implemented iff EnableActionImagesXml was called.
     */
    virtual void ImagesXml(IDvInvocation& aInvocation, IDvInvocationResponseString& aImagesXml);
    /**
     * PlaylistReadArray action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistReadArray action for the owning device.
     * Must be implemented iff EnableActionPlaylistReadArray was called.
     */
    virtual void PlaylistReadArray(IDvInvocation& aInvocation, TUint aId, IDvInvocationResponseBinary& aArray);
    /**
     * PlaylistReadList action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistReadList action for the owning device.
     * Must be implemented iff EnableActionPlaylistReadList was called.
     */
    virtual void PlaylistReadList(IDvInvocation& aInvocation, const Brx& aIdList, IDvInvocationResponseString& aPlaylistList);
    /**
     * PlaylistRead action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistRead action for the owning device.
     * Must be implemented iff EnableActionPlaylistRead was called.
     */
    virtual void PlaylistRead(IDvInvocation& aInvocation, TUint aId, IDvInvocationResponseString& aName, IDvInvocationResponseString& aDescription, IDvInvocationResponseUint& aImageId);
    /**
     * PlaylistSetName action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistSetName action for the owning device.
     * Must be implemented iff EnableActionPlaylistSetName was called.
     */
    virtual void PlaylistSetName(IDvInvocation& aInvocation, TUint aId, const Brx& aName);
    /**
     * PlaylistSetDescription action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistSetDescription action for the owning device.
     * Must be implemented iff EnableActionPlaylistSetDescription was called.
     */
    virtual void PlaylistSetDescription(IDvInvocation& aInvocation, TUint aId, const Brx& aDescription);
    /**
     * PlaylistSetImageId action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistSetImageId action for the owning device.
     * Must be implemented iff EnableActionPlaylistSetImageId was called.
     */
    virtual void PlaylistSetImageId(IDvInvocation& aInvocation, TUint aId, TUint aImageId);
    /**
     * PlaylistInsert action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistInsert action for the owning device.
     * Must be implemented iff EnableActionPlaylistInsert was called.
     */
    virtual void PlaylistInsert(IDvInvocation& aInvocation, TUint aAfterId, const Brx& aName, const Brx& aDescription, TUint aImageId, IDvInvocationResponseUint& aNewId);
    /**
     * PlaylistDeleteId action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistDeleteId action for the owning device.
     * Must be implemented iff EnableActionPlaylistDeleteId was called.
     */
    virtual void PlaylistDeleteId(IDvInvocation& aInvocation, TUint aValue);
    /**
     * PlaylistMove action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistMove action for the owning device.
     * Must be implemented iff EnableActionPlaylistMove was called.
     */
    virtual void PlaylistMove(IDvInvocation& aInvocation, TUint aId, TUint aAfterId);
    /**
     * PlaylistsMax action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistsMax action for the owning device.
     * Must be implemented iff EnableActionPlaylistsMax was called.
     */
    virtual void PlaylistsMax(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
    /**
     * TracksMax action.
     *
     * Will be called when the device stack receives an invocation of the
     * TracksMax action for the owning device.
     * Must be implemented iff EnableActionTracksMax was called.
     */
    virtual void TracksMax(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
    /**
     * PlaylistArrays action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistArrays action for the owning device.
     * Must be implemented iff EnableActionPlaylistArrays was called.
     */
    virtual void PlaylistArrays(IDvInvocation& aInvocation, IDvInvocationResponseUint& aToken, IDvInvocationResponseBinary& aIdArray, IDvInvocationResponseBinary& aTokenArray);
    /**
     * PlaylistArraysChanged action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistArraysChanged action for the owning device.
     * Must be implemented iff EnableActionPlaylistArraysChanged was called.
     */
    virtual void PlaylistArraysChanged(IDvInvocation& aInvocation, TUint aToken, IDvInvocationResponseBool& aValue);
    /**
     * Read action.
     *
     * Will be called when the device stack receives an invocation of the
     * Read action for the owning device.
     * Must be implemented iff EnableActionRead was called.
     */
    virtual void Read(IDvInvocation& aInvocation, TUint aId, TUint aTrackId, IDvInvocationResponseString& aMetadata);
    /**
     * ReadList action.
     *
     * Will be called when the device stack receives an invocation of the
     * ReadList action for the owning device.
     * Must be implemented iff EnableActionReadList was called.
     */
    virtual void ReadList(IDvInvocation& aInvocation, TUint aId, const Brx& aTrackIdList, IDvInvocationResponseString& aTrackList);
    /**
     * Insert action.
     *
     * Will be called when the device stack receives an invocation of the
     * Insert action for the owning device.
     * Must be implemented iff EnableActionInsert was called.
     */
    virtual void Insert(IDvInvocation& aInvocation, TUint aId, TUint aAfterTrackId, const Brx& aMetadata, IDvInvocationResponseUint& aNewTrackId);
    /**
     * DeleteId action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteId action for the owning device.
     * Must be implemented iff EnableActionDeleteId was called.
     */
    virtual void DeleteId(IDvInvocation& aInvocation, TUint aId, TUint aTrackId);
    /**
     * DeleteAll action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteAll action for the owning device.
     * Must be implemented iff EnableActionDeleteAll was called.
     */
    virtual void DeleteAll(IDvInvocation& aInvocation, TUint aId);
private:
    DvProviderAvOpenhomeOrgPlaylistManager1();
    void Construct();
    void DoMetadata(IDviInvocation& aInvocation);
    void DoImagesXml(IDviInvocation& aInvocation);
    void DoPlaylistReadArray(IDviInvocation& aInvocation);
    void DoPlaylistReadList(IDviInvocation& aInvocation);
    void DoPlaylistRead(IDviInvocation& aInvocation);
    void DoPlaylistSetName(IDviInvocation& aInvocation);
    void DoPlaylistSetDescription(IDviInvocation& aInvocation);
    void DoPlaylistSetImageId(IDviInvocation& aInvocation);
    void DoPlaylistInsert(IDviInvocation& aInvocation);
    void DoPlaylistDeleteId(IDviInvocation& aInvocation);
    void DoPlaylistMove(IDviInvocation& aInvocation);
    void DoPlaylistsMax(IDviInvocation& aInvocation);
    void DoTracksMax(IDviInvocation& aInvocation);
    void DoPlaylistArrays(IDviInvocation& aInvocation);
    void DoPlaylistArraysChanged(IDviInvocation& aInvocation);
    void DoRead(IDviInvocation& aInvocation);
    void DoReadList(IDviInvocation& aInvocation);
    void DoInsert(IDviInvocation& aInvocation);
    void DoDeleteId(IDviInvocation& aInvocation);
    void DoDeleteAll(IDviInvocation& aInvocation);
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

#endif // HEADER_DVAVOPENHOMEORGPLAYLISTMANAGER1

