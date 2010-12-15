#ifndef HEADER_PROXY_C_PRIVATE
#define HEADER_PROXY_C_PRIVATE

#include <CpProxy.h>
#include <CpiDevice.h>
#include <Core/CpDevice.h>

namespace Zapp {

class CpiService;
    
class DllExportClass CpProxyC
{
public:
    CpProxyC(const TChar* aDomain, const TChar* aName, TUint aVersion, CpiDevice& aDevice);
    DllExport virtual ~CpProxyC();
    void Subscribe() { iProxy->Subscribe(); }
    void Unsubscribe() { iProxy->Unsubscribe(); }
    void SetPropertyChanged(Functor& aFunctor) { iProxy->SetPropertyChanged(aFunctor); }
    void SetPropertyInitialEvent(Functor& aFunctor) { iProxy->SetPropertyInitialEvent(aFunctor); }
    CpiService* Service() const { return iProxy->iService; }
    void AddProperty(Property* aProperty) { iProxy->AddProperty(aProperty); }
protected:
    DllExport CpProxyC(CpiDevice& aDevice);
protected:
    CpProxy* iProxy;
    CpDevice* iDevice;
};

} // namespace Zapp

#endif // HEADER_PROXY_C_PRIVATE
