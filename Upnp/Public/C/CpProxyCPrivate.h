#ifndef HEADER_PROXY_C_PRIVATE
#define HEADER_PROXY_C_PRIVATE

#include <CpProxy.h>
#include <CpiDevice.h>
#include <Core/CpDevice.h>

namespace OpenHome {
namespace Net {

class CpiService;
    
class DllExportClass CpProxyC
{
public:
    DllExport CpProxyC(const TChar* aDomain, const TChar* aName, TUint aVersion, CpiDevice& aDevice);
    DllExport virtual ~CpProxyC();
    DllExport void Subscribe() { iProxy->Subscribe(); }
    DllExport void Unsubscribe() { iProxy->Unsubscribe(); }
    DllExport void SetPropertyChanged(Functor& aFunctor) { iProxy->SetPropertyChanged(aFunctor); }
    DllExport void SetPropertyInitialEvent(Functor& aFunctor) { iProxy->SetPropertyInitialEvent(aFunctor); }
    DllExport CpiService* Service() const { return iProxy->iService; }
    DllExport void AddProperty(Property* aProperty) { iProxy->AddProperty(aProperty); }
    DllExport void PropertyReadLock() const { iProxy->PropertyReadLock(); }
    DllExport void PropertyReadUnlock() const { iProxy->PropertyReadUnlock(); }
protected:
    DllExport CpProxyC(CpiDevice& aDevice);
    DllExport void DestroyService() { iProxy->DestroyService(); }
    DllExport IInvocable& Invocable() { return iProxy->iInvocable; }
    DllExport void ReportEvent(Functor aFunctor) { iProxy->ReportEvent(aFunctor); }
    DllExport TBool IsSubscribed() const { return iProxy->iCpSubscriptionStatus == CpProxy::eSubscribed; }
protected:
    CpProxy* iProxy;
    CpDevice* iDevice;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_PROXY_C_PRIVATE
