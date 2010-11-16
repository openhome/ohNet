#ifndef HEADER_DVLINNCOUKDEBUG2
#define HEADER_DVLINNCOUKDEBUG2

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
 * Base Device for linn.co.uk:Debug:2
 */
class DvProviderLinnCoUkDebug2 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkDebug2() {}
protected:
    DvProviderLinnCoUkDebug2(DvDevice& aDevice);
    void EnableActionSetDebugLevel();
    void EnableActionDebugLevel();
    void EnableActionMemWrite();
private:
    virtual void SetDebugLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aaDebugLevel);
    virtual void DebugLevel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDebugLevel);
    virtual void MemWrite(IInvocationResponse& aResponse, TUint aVersion, TUint aaMemAddress, const Brx& aaMemData);
private:
    DvProviderLinnCoUkDebug2();
    void DoSetDebugLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoDebugLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoMemWrite(IDviInvocation& aInvocation, TUint aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDEBUG2

