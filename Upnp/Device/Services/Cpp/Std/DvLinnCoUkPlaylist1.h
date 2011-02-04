#ifndef HEADER_DVLINNCOUKPLAYLIST1CPP
#define HEADER_DVLINNCOUKPLAYLIST1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

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
class DvProviderLinnCoUkPlaylist1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkPlaylist1Cpp() {}
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
    DvProviderLinnCoUkPlaylist1Cpp(DvDeviceStd& aDevice);
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
    virtual void Read(uint32_t aVersion, uint32_t aaId, std::string& aaUri, std::string& aaMetaData);
    /**
     * ReadList action.
     *
     * Will be called when the device stack receives an invocation of the
     * ReadList action for the owning device.
     * Must be implemented iff EnableActionReadList was called.
     */
    virtual void ReadList(uint32_t aVersion, const std::string& aaIdList, std::string& aaMetaDataList);
    /**
     * Insert action.
     *
     * Will be called when the device stack receives an invocation of the
     * Insert action for the owning device.
     * Must be implemented iff EnableActionInsert was called.
     */
    virtual void Insert(uint32_t aVersion, uint32_t aaAfterId, const std::string& aaUri, const std::string& aaMetaData, uint32_t& aaNewId);
    /**
     * Delete action.
     *
     * Will be called when the device stack receives an invocation of the
     * Delete action for the owning device.
     * Must be implemented iff EnableActionDelete was called.
     */
    virtual void Delete(uint32_t aVersion, uint32_t aaId);
    /**
     * DeleteAll action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteAll action for the owning device.
     * Must be implemented iff EnableActionDeleteAll was called.
     */
    virtual void DeleteAll(uint32_t aVersion);
    /**
     * SetRepeat action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRepeat action for the owning device.
     * Must be implemented iff EnableActionSetRepeat was called.
     */
    virtual void SetRepeat(uint32_t aVersion, bool aaRepeat);
    /**
     * Repeat action.
     *
     * Will be called when the device stack receives an invocation of the
     * Repeat action for the owning device.
     * Must be implemented iff EnableActionRepeat was called.
     */
    virtual void Repeat(uint32_t aVersion, bool& aaRepeat);
    /**
     * SetShuffle action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetShuffle action for the owning device.
     * Must be implemented iff EnableActionSetShuffle was called.
     */
    virtual void SetShuffle(uint32_t aVersion, bool aaShuffle);
    /**
     * Shuffle action.
     *
     * Will be called when the device stack receives an invocation of the
     * Shuffle action for the owning device.
     * Must be implemented iff EnableActionShuffle was called.
     */
    virtual void Shuffle(uint32_t aVersion, bool& aaShuffle);
    /**
     * TracksMax action.
     *
     * Will be called when the device stack receives an invocation of the
     * TracksMax action for the owning device.
     * Must be implemented iff EnableActionTracksMax was called.
     */
    virtual void TracksMax(uint32_t aVersion, uint32_t& aaTracksMax);
    /**
     * IdArray action.
     *
     * Will be called when the device stack receives an invocation of the
     * IdArray action for the owning device.
     * Must be implemented iff EnableActionIdArray was called.
     */
    virtual void IdArray(uint32_t aVersion, uint32_t& aaIdArrayToken, std::string& aaIdArray);
    /**
     * IdArrayChanged action.
     *
     * Will be called when the device stack receives an invocation of the
     * IdArrayChanged action for the owning device.
     * Must be implemented iff EnableActionIdArrayChanged was called.
     */
    virtual void IdArrayChanged(uint32_t aVersion, uint32_t aaIdArrayToken, bool& aaIdArrayChanged);
private:
    DvProviderLinnCoUkPlaylist1Cpp();
    void DoRead(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoReadList(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoInsert(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDelete(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDeleteAll(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetRepeat(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoRepeat(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetShuffle(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoShuffle(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoTracksMax(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoIdArray(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoIdArrayChanged(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyBinary* iPropertyIdArray;
    PropertyBool* iPropertyRepeat;
    PropertyBool* iPropertyShuffle;
    PropertyUint* iPropertyTracksMax;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPLAYLIST1CPP

