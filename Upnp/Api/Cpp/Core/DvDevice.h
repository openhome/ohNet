#ifndef HEADER_DVDEVICE
#define HEADER_DVDEVICE

#include <ZappTypes.h>
#include <Buffer.h>
#include <Functor.h>
#include <DvResourceWriter.h>

namespace Zapp {

class IResourceManager
{
public:
    virtual ~IResourceManager() {}
    virtual void WriteResource(const Brx& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter) = 0;
};

class DviDevice;
class DvDevice
{
public:
    DvDevice(const Brx& aUdn);
    DvDevice(const Brx& aUdn, IResourceManager& aResourceManager);
    ~DvDevice();
    DllExport DviDevice& Device();
    const Brx& Udn() const;
    TBool Enabled() const;
    void SetEnabled();
    void SetDisabled(Functor aCompleted);
    void GetAttribute(const TChar* aKey, const TChar** aValue) const;
    void SetAttribute(const TChar* aKey, const TChar* aValue);
private:
    DviDevice* iDevice;
};

} // namespace Zapp

#endif // HEADER_DVDEVICE
