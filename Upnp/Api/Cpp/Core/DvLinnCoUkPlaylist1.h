#ifndef HEADER_DVLINNCOUKPLAYLIST1
#define HEADER_DVLINNCOUKPLAYLIST1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Playlist:1
 */
class DvServiceLinnCoUkPlaylist1 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkPlaylist1() {}
    void SetPropertyIdArray(const Brx& aValue);
    void GetPropertyIdArray(Brh& aValue);
    void SetPropertyRepeat(TBool aValue);
    void GetPropertyRepeat(TBool& aValue);
    void SetPropertyShuffle(TBool aValue);
    void GetPropertyShuffle(TBool& aValue);
    void SetPropertyTracksMax(TUint aValue);
    void GetPropertyTracksMax(TUint& aValue);
protected:
    DvServiceLinnCoUkPlaylist1(DvDevice& aDevice);
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
    virtual void Read(IInvocationResponse& aResponse, TUint aVersion, TUint aaId, IInvocationResponseString& aaUri, IInvocationResponseString& aaMetaData);
    virtual void ReadList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIdList, IInvocationResponseString& aaMetaDataList);
    virtual void Insert(IInvocationResponse& aResponse, TUint aVersion, TUint aaAfterId, const Brx& aaUri, const Brx& aaMetaData, IInvocationResponseUint& aaNewId);
    virtual void Delete(IInvocationResponse& aResponse, TUint aVersion, TUint aaId);
    virtual void DeleteAll(IInvocationResponse& aResponse, TUint aVersion);
    virtual void SetRepeat(IInvocationResponse& aResponse, TUint aVersion, TBool aaRepeat);
    virtual void Repeat(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaRepeat);
    virtual void SetShuffle(IInvocationResponse& aResponse, TUint aVersion, TBool aaShuffle);
    virtual void Shuffle(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaShuffle);
    virtual void TracksMax(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTracksMax);
    virtual void IdArray(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIdArrayToken, IInvocationResponseBinary& aaIdArray);
    virtual void IdArrayChanged(IInvocationResponse& aResponse, TUint aVersion, TUint aaIdArrayToken, IInvocationResponseBool& aaIdArrayChanged);
private:
    DvServiceLinnCoUkPlaylist1();
    void DoRead(IDvInvocation& aInvocation, TUint aVersion);
    void DoReadList(IDvInvocation& aInvocation, TUint aVersion);
    void DoInsert(IDvInvocation& aInvocation, TUint aVersion);
    void DoDelete(IDvInvocation& aInvocation, TUint aVersion);
    void DoDeleteAll(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetRepeat(IDvInvocation& aInvocation, TUint aVersion);
    void DoRepeat(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetShuffle(IDvInvocation& aInvocation, TUint aVersion);
    void DoShuffle(IDvInvocation& aInvocation, TUint aVersion);
    void DoTracksMax(IDvInvocation& aInvocation, TUint aVersion);
    void DoIdArray(IDvInvocation& aInvocation, TUint aVersion);
    void DoIdArrayChanged(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyBinary* iPropertyIdArray;
    PropertyBool* iPropertyRepeat;
    PropertyBool* iPropertyShuffle;
    PropertyUint* iPropertyTracksMax;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPLAYLIST1

