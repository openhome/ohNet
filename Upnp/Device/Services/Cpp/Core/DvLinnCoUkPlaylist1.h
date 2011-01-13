#ifndef HEADER_DVLINNCOUKPLAYLIST1
#define HEADER_DVLINNCOUKPLAYLIST1

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
 * Provider for the linn.co.uk:Playlist:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkPlaylist1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkPlaylist1() {}
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
     * Set the value of the Repeat property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyRepeat(TBool aValue);
    /**
     * Get a copy of the value of the Repeat property
     */
    void GetPropertyRepeat(TBool& aValue);
    /**
     * Set the value of the Shuffle property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyShuffle(TBool aValue);
    /**
     * Get a copy of the value of the Shuffle property
     */
    void GetPropertyShuffle(TBool& aValue);
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
    DvProviderLinnCoUkPlaylist1(DvDevice& aDevice);
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
     * Signal that the action Delete is supported.
     * The action's availability will be published in the device's service.xml.
     * Delete must be overridden if this is called.
     */
    void EnableActionDelete();
    /**
     * Signal that the action DeleteAll is supported.
     * The action's availability will be published in the device's service.xml.
     * DeleteAll must be overridden if this is called.
     */
    void EnableActionDeleteAll();
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
private:
    /**
     * Read action.
     *
     * Will be called when the device stack receives an invocation of the
     * Read action for the owning device.
     * Must be implemented iff EnableActionRead was called.
     */
    virtual void Read(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetaData);
    /**
     * ReadList action.
     *
     * Will be called when the device stack receives an invocation of the
     * ReadList action for the owning device.
     * Must be implemented iff EnableActionReadList was called.
     */
    virtual void ReadList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIdList, IInvocationResponseString& aaMetaDataList);
    /**
     * Insert action.
     *
     * Will be called when the device stack receives an invocation of the
     * Insert action for the owning device.
     * Must be implemented iff EnableActionInsert was called.
     */
    virtual void Insert(IInvocationResponse& aResponse, TUint aVersion, TUint aaAfterId, const Brx& aaUri, const Brx& aaMetaData, IInvocationResponseUint& aaNewId);
    /**
     * Delete action.
     *
     * Will be called when the device stack receives an invocation of the
     * Delete action for the owning device.
     * Must be implemented iff EnableActionDelete was called.
     */
    virtual void Delete(IInvocationResponse& aResponse, TUint aVersion, TUint aaId);
    /**
     * DeleteAll action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteAll action for the owning device.
     * Must be implemented iff EnableActionDeleteAll was called.
     */
    virtual void DeleteAll(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * SetRepeat action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRepeat action for the owning device.
     * Must be implemented iff EnableActionSetRepeat was called.
     */
    virtual void SetRepeat(IInvocationResponse& aResponse, TUint aVersion, TBool aaRepeat);
    /**
     * Repeat action.
     *
     * Will be called when the device stack receives an invocation of the
     * Repeat action for the owning device.
     * Must be implemented iff EnableActionRepeat was called.
     */
    virtual void Repeat(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaRepeat);
    /**
     * SetShuffle action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetShuffle action for the owning device.
     * Must be implemented iff EnableActionSetShuffle was called.
     */
    virtual void SetShuffle(IInvocationResponse& aResponse, TUint aVersion, TBool aaShuffle);
    /**
     * Shuffle action.
     *
     * Will be called when the device stack receives an invocation of the
     * Shuffle action for the owning device.
     * Must be implemented iff EnableActionShuffle was called.
     */
    virtual void Shuffle(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaShuffle);
    /**
     * TracksMax action.
     *
     * Will be called when the device stack receives an invocation of the
     * TracksMax action for the owning device.
     * Must be implemented iff EnableActionTracksMax was called.
     */
    virtual void TracksMax(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTracksMax);
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
private:
    DvProviderLinnCoUkPlaylist1();
    void DoRead(IDviInvocation& aInvocation, TUint aVersion);
    void DoReadList(IDviInvocation& aInvocation, TUint aVersion);
    void DoInsert(IDviInvocation& aInvocation, TUint aVersion);
    void DoDelete(IDviInvocation& aInvocation, TUint aVersion);
    void DoDeleteAll(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRepeat(IDviInvocation& aInvocation, TUint aVersion);
    void DoRepeat(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetShuffle(IDviInvocation& aInvocation, TUint aVersion);
    void DoShuffle(IDviInvocation& aInvocation, TUint aVersion);
    void DoTracksMax(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdArray(IDviInvocation& aInvocation, TUint aVersion);
    void DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyBinary* iPropertyIdArray;
    PropertyBool* iPropertyRepeat;
    PropertyBool* iPropertyShuffle;
    PropertyUint* iPropertyTracksMax;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPLAYLIST1

