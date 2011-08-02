#ifndef HEADER_DVAVOPENHOMEORGPLAYLISTMANAGER1
#define HEADER_DVAVOPENHOMEORGPLAYLISTMANAGER1

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

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
class DvProviderAvOpenhomeOrgPlaylistManager1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgPlaylistManager1() {}
    /**
     * Set the value of the Metadata property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyMetadata(const Brx& aValue);
    /**
     * Get a copy of the value of the Metadata property
     */
    void GetPropertyMetadata(Brhz& aValue);
    /**
     * Set the value of the ImagesXml property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyImagesXml(const Brx& aValue);
    /**
     * Get a copy of the value of the ImagesXml property
     */
    void GetPropertyImagesXml(Brhz& aValue);
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
     * Set the value of the TokenArray property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTokenArray(const Brx& aValue);
    /**
     * Get a copy of the value of the TokenArray property
     */
    void GetPropertyTokenArray(Brh& aValue);
    /**
     * Set the value of the PlaylistsMax property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyPlaylistsMax(TUint aValue);
    /**
     * Get a copy of the value of the PlaylistsMax property
     */
    void GetPropertyPlaylistsMax(TUint& aValue);
    /**
     * Set the value of the TracksMax property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTracksMax(TUint aValue);
    /**
     * Get a copy of the value of the TracksMax property
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
     * Signal that the action PlaylistReadMetadata is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistReadMetadata must be overridden if this is called.
     */
    void EnableActionPlaylistReadMetadata();
    /**
     * Signal that the action PlaylistRead is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistRead must be overridden if this is called.
     */
    void EnableActionPlaylistRead();
    /**
     * Signal that the action PlaylistUpdate is supported.
     * The action's availability will be published in the device's service.xml.
     * PlaylistUpdate must be overridden if this is called.
     */
    void EnableActionPlaylistUpdate();
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
    virtual void Metadata(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aMetadata);
    /**
     * ImagesXml action.
     *
     * Will be called when the device stack receives an invocation of the
     * ImagesXml action for the owning device.
     * Must be implemented iff EnableActionImagesXml was called.
     */
    virtual void ImagesXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aImagesXml);
    /**
     * PlaylistReadArray action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistReadArray action for the owning device.
     * Must be implemented iff EnableActionPlaylistReadArray was called.
     */
    virtual void PlaylistReadArray(IInvocationResponse& aResponse, TUint aVersion, TUint aId, IInvocationResponseBinary& aArray);
    /**
     * PlaylistReadMetadata action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistReadMetadata action for the owning device.
     * Must be implemented iff EnableActionPlaylistReadMetadata was called.
     */
    virtual void PlaylistReadMetadata(IInvocationResponse& aResponse, TUint aVersion, const Brx& aIdList, IInvocationResponseString& aMetadata);
    /**
     * PlaylistRead action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistRead action for the owning device.
     * Must be implemented iff EnableActionPlaylistRead was called.
     */
    virtual void PlaylistRead(IInvocationResponse& aResponse, TUint aVersion, TUint aId, IInvocationResponseString& aName, IInvocationResponseString& aDescription, IInvocationResponseUint& aImageId);
    /**
     * PlaylistUpdate action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistUpdate action for the owning device.
     * Must be implemented iff EnableActionPlaylistUpdate was called.
     */
    virtual void PlaylistUpdate(IInvocationResponse& aResponse, TUint aVersion, TUint aId, const Brx& aName, const Brx& aDescription, TUint aImageId);
    /**
     * PlaylistInsert action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistInsert action for the owning device.
     * Must be implemented iff EnableActionPlaylistInsert was called.
     */
    virtual void PlaylistInsert(IInvocationResponse& aResponse, TUint aVersion, TUint aAfterId, const Brx& aName, const Brx& aDescription, TUint aImageId, IInvocationResponseUint& aNewId);
    /**
     * PlaylistDeleteId action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistDeleteId action for the owning device.
     * Must be implemented iff EnableActionPlaylistDeleteId was called.
     */
    virtual void PlaylistDeleteId(IInvocationResponse& aResponse, TUint aVersion, TUint aValue);
    /**
     * PlaylistsMax action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistsMax action for the owning device.
     * Must be implemented iff EnableActionPlaylistsMax was called.
     */
    virtual void PlaylistsMax(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue);
    /**
     * TracksMax action.
     *
     * Will be called when the device stack receives an invocation of the
     * TracksMax action for the owning device.
     * Must be implemented iff EnableActionTracksMax was called.
     */
    virtual void TracksMax(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue);
    /**
     * PlaylistArrays action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistArrays action for the owning device.
     * Must be implemented iff EnableActionPlaylistArrays was called.
     */
    virtual void PlaylistArrays(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aToken, IInvocationResponseBinary& aIdArray, IInvocationResponseBinary& aTokenArray);
    /**
     * PlaylistArraysChanged action.
     *
     * Will be called when the device stack receives an invocation of the
     * PlaylistArraysChanged action for the owning device.
     * Must be implemented iff EnableActionPlaylistArraysChanged was called.
     */
    virtual void PlaylistArraysChanged(IInvocationResponse& aResponse, TUint aVersion, TUint aToken, IInvocationResponseBool& aValue);
    /**
     * Read action.
     *
     * Will be called when the device stack receives an invocation of the
     * Read action for the owning device.
     * Must be implemented iff EnableActionRead was called.
     */
    virtual void Read(IInvocationResponse& aResponse, TUint aVersion, TUint aId, TUint aTrackId, IInvocationResponseString& aMetadata);
    /**
     * ReadList action.
     *
     * Will be called when the device stack receives an invocation of the
     * ReadList action for the owning device.
     * Must be implemented iff EnableActionReadList was called.
     */
    virtual void ReadList(IInvocationResponse& aResponse, TUint aVersion, TUint aId, const Brx& aTrackIdList, IInvocationResponseString& aTrackList);
    /**
     * Insert action.
     *
     * Will be called when the device stack receives an invocation of the
     * Insert action for the owning device.
     * Must be implemented iff EnableActionInsert was called.
     */
    virtual void Insert(IInvocationResponse& aResponse, TUint aVersion, TUint aId, TUint aAfterTrackId, const Brx& aUdn, const Brx& aMetadataId, IInvocationResponseUint& aNewTrackId);
    /**
     * DeleteId action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteId action for the owning device.
     * Must be implemented iff EnableActionDeleteId was called.
     */
    virtual void DeleteId(IInvocationResponse& aResponse, TUint aVersion, TUint aTrackId, TUint aValue);
    /**
     * DeleteAll action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteAll action for the owning device.
     * Must be implemented iff EnableActionDeleteAll was called.
     */
    virtual void DeleteAll(IInvocationResponse& aResponse, TUint aVersion, TUint aTrackId);
private:
    DvProviderAvOpenhomeOrgPlaylistManager1();
    void DoMetadata(IDviInvocation& aInvocation, TUint aVersion);
    void DoImagesXml(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistReadArray(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistReadMetadata(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistRead(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistUpdate(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistInsert(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistDeleteId(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistsMax(IDviInvocation& aInvocation, TUint aVersion);
    void DoTracksMax(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistArrays(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistArraysChanged(IDviInvocation& aInvocation, TUint aVersion);
    void DoRead(IDviInvocation& aInvocation, TUint aVersion);
    void DoReadList(IDviInvocation& aInvocation, TUint aVersion);
    void DoInsert(IDviInvocation& aInvocation, TUint aVersion);
    void DoDeleteId(IDviInvocation& aInvocation, TUint aVersion);
    void DoDeleteAll(IDviInvocation& aInvocation, TUint aVersion);
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

