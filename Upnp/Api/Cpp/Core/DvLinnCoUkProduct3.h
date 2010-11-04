#ifndef HEADER_DVLINNCOUKPRODUCT3
#define HEADER_DVLINNCOUKPRODUCT3

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Product:3
 */
class DvProviderLinnCoUkProduct3 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkProduct3() {}
    TBool SetPropertyProductType(const Brx& aValue);
    void GetPropertyProductType(Brhz& aValue);
    TBool SetPropertyProductModel(const Brx& aValue);
    void GetPropertyProductModel(Brhz& aValue);
    TBool SetPropertyProductName(const Brx& aValue);
    void GetPropertyProductName(Brhz& aValue);
    TBool SetPropertyProductRoom(const Brx& aValue);
    void GetPropertyProductRoom(Brhz& aValue);
    TBool SetPropertyProductStandby(TBool aValue);
    void GetPropertyProductStandby(TBool& aValue);
    TBool SetPropertyProductSourceIndex(TUint aValue);
    void GetPropertyProductSourceIndex(TUint& aValue);
    TBool SetPropertyProductSourceCount(TUint aValue);
    void GetPropertyProductSourceCount(TUint& aValue);
    TBool SetPropertyProductSourceXml(const Brx& aValue);
    void GetPropertyProductSourceXml(Brhz& aValue);
    TBool SetPropertyStartupSourceIndex(TUint aValue);
    void GetPropertyStartupSourceIndex(TUint& aValue);
    TBool SetPropertyStartupSourceEnabled(TBool aValue);
    void GetPropertyStartupSourceEnabled(TBool& aValue);
    TBool SetPropertyProductAnySourceName(TUint aValue);
    void GetPropertyProductAnySourceName(TUint& aValue);
    TBool SetPropertyProductAnySourceVisible(TUint aValue);
    void GetPropertyProductAnySourceVisible(TUint& aValue);
    TBool SetPropertyProductAnySourceType(TUint aValue);
    void GetPropertyProductAnySourceType(TUint& aValue);
protected:
    DvProviderLinnCoUkProduct3(DvDevice& aDevice);
    void EnableActionType();
    void EnableActionModel();
    void EnableActionName();
    void EnableActionSetName();
    void EnableActionRoom();
    void EnableActionSetRoom();
    void EnableActionStandby();
    void EnableActionSetStandby();
    void EnableActionSourceCount();
    void EnableActionSourceXml();
    void EnableActionSourceIndex();
    void EnableActionSetSourceIndex();
    void EnableActionSetSourceIndexByName();
    void EnableActionSetStartupSourceIndexByName();
    void EnableActionStartupSourceIndex();
    void EnableActionSetStartupSourceIndex();
    void EnableActionStartupSourceEnabled();
    void EnableActionSetStartupSourceEnabled();
    void EnableActionSourceSystemName();
    void EnableActionSourceName();
    void EnableActionSetSourceName();
    void EnableActionSourceType();
    void EnableActionSourceVisible();
    void EnableActionSetSourceVisible();
private:
    virtual void Type(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaType);
    virtual void Model(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaModel);
    virtual void Name(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaName);
    virtual void SetName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaName);
    virtual void Room(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaRoom);
    virtual void SetRoom(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaRoom);
    virtual void Standby(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStandby);
    virtual void SetStandby(IInvocationResponse& aResponse, TUint aVersion, TBool aaStandby);
    virtual void SourceCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceCount);
    virtual void SourceXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSourceXml);
    virtual void SourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceIndex);
    virtual void SetSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex);
    virtual void SetSourceIndexByName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaSourceName);
    virtual void SetStartupSourceIndexByName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaSourceName);
    virtual void StartupSourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceIndex);
    virtual void SetStartupSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex);
    virtual void StartupSourceEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStartupSourceEnabled);
    virtual void SetStartupSourceEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaStartupSourceEnabled);
    virtual void SourceSystemName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceName);
    virtual void SourceName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceName);
    virtual void SetSourceName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, const Brx& aaSourceName);
    virtual void SourceType(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceType);
    virtual void SourceVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseBool& aaSourceVisible);
    virtual void SetSourceVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, TBool aaSourceVisible);
private:
    DvProviderLinnCoUkProduct3();
    void DoType(IDvInvocation& aInvocation, TUint aVersion);
    void DoModel(IDvInvocation& aInvocation, TUint aVersion);
    void DoName(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetName(IDvInvocation& aInvocation, TUint aVersion);
    void DoRoom(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetRoom(IDvInvocation& aInvocation, TUint aVersion);
    void DoStandby(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetStandby(IDvInvocation& aInvocation, TUint aVersion);
    void DoSourceCount(IDvInvocation& aInvocation, TUint aVersion);
    void DoSourceXml(IDvInvocation& aInvocation, TUint aVersion);
    void DoSourceIndex(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetSourceIndex(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetSourceIndexByName(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetStartupSourceIndexByName(IDvInvocation& aInvocation, TUint aVersion);
    void DoStartupSourceIndex(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetStartupSourceIndex(IDvInvocation& aInvocation, TUint aVersion);
    void DoStartupSourceEnabled(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetStartupSourceEnabled(IDvInvocation& aInvocation, TUint aVersion);
    void DoSourceSystemName(IDvInvocation& aInvocation, TUint aVersion);
    void DoSourceName(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetSourceName(IDvInvocation& aInvocation, TUint aVersion);
    void DoSourceType(IDvInvocation& aInvocation, TUint aVersion);
    void DoSourceVisible(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetSourceVisible(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyProductType;
    PropertyString* iPropertyProductModel;
    PropertyString* iPropertyProductName;
    PropertyString* iPropertyProductRoom;
    PropertyBool* iPropertyProductStandby;
    PropertyUint* iPropertyProductSourceIndex;
    PropertyUint* iPropertyProductSourceCount;
    PropertyString* iPropertyProductSourceXml;
    PropertyUint* iPropertyStartupSourceIndex;
    PropertyBool* iPropertyStartupSourceEnabled;
    PropertyUint* iPropertyProductAnySourceName;
    PropertyUint* iPropertyProductAnySourceVisible;
    PropertyUint* iPropertyProductAnySourceType;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPRODUCT3

