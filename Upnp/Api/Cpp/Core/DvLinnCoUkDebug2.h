#ifndef HEADER_DVLINNCOUKDEBUG2
#define HEADER_DVLINNCOUKDEBUG2

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
 * Base Device for linn.co.uk:Debug:2
 */
class DvServiceLinnCoUkDebug2 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkDebug2() {}
protected:
    DvServiceLinnCoUkDebug2(DvDevice& aDevice);
    void EnableActionSetDebugLevel();
    void EnableActionDebugLevel();
    void EnableActionMemWrite();
private:
    virtual void SetDebugLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aaDebugLevel);
    virtual void DebugLevel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDebugLevel);
    virtual void MemWrite(IInvocationResponse& aResponse, TUint aVersion, TUint aaMemAddress, const Brx& aaMemData);
private:
    DvServiceLinnCoUkDebug2();
    void DoSetDebugLevel(IDvInvocation& aInvocation, TUint aVersion);
    void DoDebugLevel(IDvInvocation& aInvocation, TUint aVersion);
    void DoMemWrite(IDvInvocation& aInvocation, TUint aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDEBUG2

