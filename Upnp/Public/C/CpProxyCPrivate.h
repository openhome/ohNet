#ifndef HEADER_PROXY_C_PRIVATE
#define HEADER_PROXY_C_PRIVATE

#include <CpProxy.h>
#include <CpiDevice.h>
#include <Core/CpDevice.h>

namespace Zapp {

class CpProxyC
{
public:
    void Subscribe() { iProxy->Subscribe(); }
    void Unsubscribe() { iProxy->Unsubscribe(); }
    void SetPropertyChanged(Functor& aFunctor) { iProxy->SetPropertyChanged(aFunctor); }
protected:
    DllExport CpProxyC(CpiDevice& aDevice);
    DllExport virtual ~CpProxyC();
protected:
    CpProxy* iProxy;
    CpDevice* iDevice;
};

} // namespace Zapp

#endif // HEADER_PROXY_C_PRIVATE
