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
 * Base Device for linn.co.uk:Playlist:1
 */
class DvProviderLinnCoUkPlaylist1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkPlaylist1Cpp() {}
    bool SetPropertyIdArray(const std::string& aValue);
    void GetPropertyIdArray(std::string& aValue);
    bool SetPropertyRepeat(bool aValue);
    void GetPropertyRepeat(bool& aValue);
    bool SetPropertyShuffle(bool aValue);
    void GetPropertyShuffle(bool& aValue);
    bool SetPropertyTracksMax(uint32_t aValue);
    void GetPropertyTracksMax(uint32_t& aValue);
protected:
    DvProviderLinnCoUkPlaylist1Cpp(DvDeviceStd& aDevice);
    void EnableActionRead();
    void EnableActionReadList();
    void EnableActionInsert();
    void EnableActionDelete();
    void EnableActionDeleteAll();
    void EnableActionSetRepeat();
    void EnableActionRepeat();
    void EnableActionSetShuffle();
    void EnableActionShuffle();
    void EnableActionTracksMax();
    void EnableActionIdArray();
    void EnableActionIdArrayChanged();
private:
    virtual void Read(uint32_t aVersion, uint32_t aaId, std::string& aaUri, std::string& aaMetaData);
    virtual void ReadList(uint32_t aVersion, const std::string& aaIdList, std::string& aaMetaDataList);
    virtual void Insert(uint32_t aVersion, uint32_t aaAfterId, const std::string& aaUri, const std::string& aaMetaData, uint32_t& aaNewId);
    virtual void Delete(uint32_t aVersion, uint32_t aaId);
    virtual void DeleteAll(uint32_t aVersion);
    virtual void SetRepeat(uint32_t aVersion, bool aaRepeat);
    virtual void Repeat(uint32_t aVersion, bool& aaRepeat);
    virtual void SetShuffle(uint32_t aVersion, bool aaShuffle);
    virtual void Shuffle(uint32_t aVersion, bool& aaShuffle);
    virtual void TracksMax(uint32_t aVersion, uint32_t& aaTracksMax);
    virtual void IdArray(uint32_t aVersion, uint32_t& aaIdArrayToken, std::string& aaIdArray);
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

