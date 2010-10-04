#ifndef HEADER_DVDEVICE_STD
#define HEADER_DVDEVICE_STD

#include <OsTypes.h>
#include <Functor.h>
#include <DvResourceWriter.h>
#include <Core/DvDevice.h>

#include <string>

namespace Zapp {

class IResourceManagerStd
{
public:
    virtual ~IResourceManagerStd() {}
    virtual void WriteResource(const std::string& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter) = 0;
};

class DviDevice;
class DvDeviceStd : private IResourceManager
{
public:
    DvDeviceStd(const std::string& aUdn);
    DvDeviceStd(const std::string& aUdn, IResourceManagerStd& aResourceManager);
    ~DvDeviceStd();
    DviDevice& Device();
    const std::string& Udn() const;
    TBool Enabled() const;
    void SetEnabled();
    void SetDisabled(Functor aCompleted);
    void GetAttribute(const char* aKey, const char** aValue) const;
    void SetAttribute(const char* aKey, const char* aValue);
private:
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter);
private:
    DviDevice* iDevice;
    std::string iUdn;
    IResourceManagerStd* iResourceManager;
};

} // namespace Zapp

#endif // HEADER_DVDEVICE_STD
