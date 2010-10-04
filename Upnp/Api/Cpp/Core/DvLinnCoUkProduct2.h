#ifndef HEADER_DVLINNCOUKPRODUCT2
#define HEADER_DVLINNCOUKPRODUCT2

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
 * Base Device for linn.co.uk:Product:2
 */
class DvServiceLinnCoUkProduct2 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkProduct2() {}
    void SetPropertyProductName(const Brx& aValue);
    void GetPropertyProductName(Brhz& aValue);
    void SetPropertyProductRoom(const Brx& aValue);
    void GetPropertyProductRoom(Brhz& aValue);
    void SetPropertyProductStandby(TBool aValue);
    void GetPropertyProductStandby(TBool& aValue);
    void SetPropertyProductSourceIndex(TUint aValue);
    void GetPropertyProductSourceIndex(TUint& aValue);
protected:
    DvServiceLinnCoUkProduct2(DvDevice& aDevice);
    void EnableActionType();
    void EnableActionModel();
    void EnableActionName();
    void EnableActionSetName();
    void EnableActionRoom();
    void EnableActionSetRoom();
    void EnableActionStandby();
    void EnableActionSetStandby();
    void EnableActionSourceCount();
    void EnableActionSourceIndex();
    void EnableActionSetSourceIndex();
    void EnableActionSourceType();
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
    virtual void SourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceIndex);
    virtual void SetSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex);
    virtual void SourceType(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceType);
private:
    DvServiceLinnCoUkProduct2();
    void DoType(IDvInvocation& aInvocation, TUint aVersion);
    void DoModel(IDvInvocation& aInvocation, TUint aVersion);
    void DoName(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetName(IDvInvocation& aInvocation, TUint aVersion);
    void DoRoom(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetRoom(IDvInvocation& aInvocation, TUint aVersion);
    void DoStandby(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetStandby(IDvInvocation& aInvocation, TUint aVersion);
    void DoSourceCount(IDvInvocation& aInvocation, TUint aVersion);
    void DoSourceIndex(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetSourceIndex(IDvInvocation& aInvocation, TUint aVersion);
    void DoSourceType(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyProductName;
    PropertyString* iPropertyProductRoom;
    PropertyBool* iPropertyProductStandby;
    PropertyUint* iPropertyProductSourceIndex;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPRODUCT2

