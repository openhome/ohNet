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
 * Provider for the linn.co.uk:Debug:2 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkDebug2 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkDebug2() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkDebug2(DvDevice& aDevice);
    /**
     * Signal that the action SetDebugLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * SetDebugLevel must be overridden if this is called.
     */
    void EnableActionSetDebugLevel();
    /**
     * Signal that the action DebugLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * DebugLevel must be overridden if this is called.
     */
    void EnableActionDebugLevel();
    /**
     * Signal that the action MemWrite is supported.
     * The action's availability will be published in the device's service.xml.
     * MemWrite must be overridden if this is called.
     */
    void EnableActionMemWrite();
private:
    /**
     * SetDebugLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDebugLevel action for the owning device.
     * Must be implemented iff EnableActionSetDebugLevel was called.
     */
    virtual void SetDebugLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aaDebugLevel);
    /**
     * DebugLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * DebugLevel action for the owning device.
     * Must be implemented iff EnableActionDebugLevel was called.
     */
    virtual void DebugLevel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDebugLevel);
    /**
     * MemWrite action.
     *
     * Will be called when the device stack receives an invocation of the
     * MemWrite action for the owning device.
     * Must be implemented iff EnableActionMemWrite was called.
     */
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

