#ifndef HEADER_PROXY_C_PRIVATE
#define HEADER_PROXY_C_PRIVATE

#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Net/Core/CpDevice.h>

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
    DllExport uint32_t Version() const { return iProxy->Version(); }
    DllExport CpiService* Service() const { return iProxy->iService; }
    DllExport void AddProperty(Property* aProperty) { iProxy->AddProperty(aProperty); }
    DllExport Mutex& GetPropertyReadLock() const { return iProxy->PropertyReadLock(); }
    DllExport void PropertyReadLock() const { iProxy->PropertyReadLock().Wait(); }
    DllExport void PropertyReadUnlock() const { iProxy->PropertyReadLock().Signal(); }
protected:
    DllExport CpProxyC(CpiDevice& aDevice);
    DllExport void DestroyService() { iProxy->DestroyService(); }
    DllExport IInvocable& Invocable() { return iProxy->iInvocable; }
    DllExport void ReportEvent(Functor aFunctor) { iProxy->ReportEvent(aFunctor); }
    DllExport void CheckSubscribed() const { if (iProxy->iCpSubscriptionStatus != CpProxy::eSubscribed) { THROW(ProxyNotSubscribed); } }
protected:
    CpProxy* iProxy;
    CpDevice* iDevice;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_PROXY_C_PRIVATE
