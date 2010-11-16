#ifndef HEADER_DVLINNCOUKPRODUCT1
#define HEADER_DVLINNCOUKPRODUCT1

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
 * Base Device for linn.co.uk:Product:1
 */
class DvProviderLinnCoUkProduct1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkProduct1() {}
    TBool SetPropertyRoom(const Brx& aValue);
    void GetPropertyRoom(Brhz& aValue);
    TBool SetPropertyStandby(TBool aValue);
    void GetPropertyStandby(TBool& aValue);
protected:
    DvProviderLinnCoUkProduct1(DvDevice& aDevice);
    void EnableActionRoom();
    void EnableActionSetRoom();
    void EnableActionStandby();
    void EnableActionSetStandby();
private:
    virtual void Room(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaRoom);
    virtual void SetRoom(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaRoom);
    virtual void Standby(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStandby);
    virtual void SetStandby(IInvocationResponse& aResponse, TUint aVersion, TBool aaStandby);
private:
    DvProviderLinnCoUkProduct1();
    void DoRoom(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRoom(IDviInvocation& aInvocation, TUint aVersion);
    void DoStandby(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStandby(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyRoom;
    PropertyBool* iPropertyStandby;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPRODUCT1

