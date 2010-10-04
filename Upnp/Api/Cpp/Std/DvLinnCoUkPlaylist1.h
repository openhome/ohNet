#ifndef HEADER_DVLINNCOUKPLAYLIST1CPP
#define HEADER_DVLINNCOUKPLAYLIST1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvService.h>

#include <string>

namespace Zapp {

class IDvInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Playlist:1
 */
class DvServiceLinnCoUkPlaylist1Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkPlaylist1Cpp() {}
    void SetPropertyIdArray(const std::string& aValue);
    void GetPropertyIdArray(std::string& aValue);
    void SetPropertyRepeat(bool aValue);
    void GetPropertyRepeat(bool& aValue);
    void SetPropertyShuffle(bool aValue);
    void GetPropertyShuffle(bool& aValue);
    void SetPropertyTracksMax(uint32_t aValue);
    void GetPropertyTracksMax(uint32_t& aValue);
protected:
    DvServiceLinnCoUkPlaylist1Cpp(DvDeviceStd& aDevice);
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
    DvServiceLinnCoUkPlaylist1Cpp();
    void DoRead(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoReadList(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoInsert(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDelete(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDeleteAll(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetRepeat(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoRepeat(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetShuffle(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoShuffle(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoTracksMax(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoIdArray(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoIdArrayChanged(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyBinary* iPropertyIdArray;
    PropertyBool* iPropertyRepeat;
    PropertyBool* iPropertyShuffle;
    PropertyUint* iPropertyTracksMax;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPLAYLIST1CPP

