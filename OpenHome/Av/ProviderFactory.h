#ifndef HEADER_PROVIDER_FACTORY
#define HEADER_PROVIDER_FACTORY

#include <OpenHome/OhNetTypes.h>

namespace OpenHome {
namespace Configuration {
    class IConfigManagerWriter;
}
namespace Media {
    class IVolumeProfile;
    class IVolume;
    class IBalance;
    class IMute;
}
namespace Net {
    class DvDevice;
    class DvProvider;
}
namespace Av {
    class Product;

class ProviderFactory
{
public:
    static Net::DvProvider* NewVolume(Product& aProduct, Net::DvDevice& aDevice, Configuration::IConfigManagerWriter& aConfigManager, Media::IVolumeProfile& aVolumeProfile, Media::IVolume& aVolume, Media::IBalance& aBalance, Media::IMute& aMute);
};

} // namespace Av
} // namespaceOpenHome

#endif // HEADER_PROVIDER_FACTORY
