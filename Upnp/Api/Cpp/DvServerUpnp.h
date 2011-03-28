#ifndef HEADER_DVSERVERUPNP
#define HEADER_DVSERVERUPNP

#include <Core/DvDevice.h>

namespace Zapp {

class DviServerUpnp;
    
class DvServerUpnp
{
public:
    DvServerUpnp();
    ~DvServerUpnp();
    void AddDevice(DvDevice& aDevice);
private:
    DviServerUpnp* iServer;
};

} // namespace Zapp

#endif // HEADER_DVSERVERUPNP