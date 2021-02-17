#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Net/Private/Globals.h>

#include <string>

namespace OpenHome {
namespace Net {

class DvResourceManagerStd : public IResourceManager, private INonCopyable
{
public:
    DvResourceManagerStd(IResourceManagerStd& aResourceManager);
private:
    void WriteResource(const Brx& aUriTail, const TIpAddress& aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter);
private:
    IResourceManagerStd& iResourceManager;
};

} // namespace Net
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Net;

// DvDeviceStd

DvDeviceStd::DvDeviceStd(const std::string& aUdn)
{
    Brn buf((const TByte*)aUdn.c_str(), (TUint)aUdn.length());
    iDevice = new DviDevice(*gDvStack, buf);
    SetUdn(aUdn);
}
    
DvDeviceStd::DvDeviceStd()
    : iDevice(NULL)
{
}
    
DvDeviceStd::~DvDeviceStd()
{
    iDevice->Destroy();
}
    
void DvDeviceStd::SetUdn(const std::string& aUdn)
{
    iUdn.assign(aUdn);
}

DviDevice& DvDeviceStd::Device()
{
    return *iDevice;
}
    
const std::string& DvDeviceStd::Udn() const
{
    return iUdn;
}
    
TBool DvDeviceStd::Enabled() const
{
    return iDevice->Enabled();
}
    
void DvDeviceStd::SetEnabled()
{
    iDevice->SetEnabled();
}
    
void DvDeviceStd::SetDisabled(Functor aCompleted)
{
    iDevice->SetDisabled(aCompleted);
}
    
void DvDeviceStd::GetAttribute(const char* aKey, const char** aValue) const
{
    iDevice->GetAttribute(aKey, aValue);
}
    
void DvDeviceStd::SetAttribute(const char* aKey, const char* aValue)
{
    iDevice->SetAttribute(aKey, aValue);
}

void DvDeviceStd::AddDevice(DvDeviceStd* aDevice)
{
    iDevice->AddDevice(aDevice->iDevice);
}


// DvResourceManagerStd

DvResourceManagerStd::DvResourceManagerStd(IResourceManagerStd& aResourceManager)
    : iResourceManager(aResourceManager)
{
}

void DvResourceManagerStd::WriteResource(const Brx& aUriTail, const TIpAddress& aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter)
{
    std::string uriTail((const char*)aUriTail.Ptr(), aUriTail.Bytes());
    iResourceManager.WriteResource(uriTail, aInterface, aLanguageList, aResourceWriter);
}


// DvDeviceStdStandard

DvDeviceStdStandard::DvDeviceStdStandard(const std::string& aUdn)
{
    Brn buf((const TByte*)aUdn.c_str(), (TUint)aUdn.length());
    iDevice = new DviDeviceStandard(*gDvStack, buf);
    SetUdn(aUdn);
    iResourceManager = NULL;
}

DvDeviceStdStandard::DvDeviceStdStandard(const std::string& aUdn, IResourceManagerStd& aResourceManager)
{
    iResourceManager = new DvResourceManagerStd(aResourceManager);
    Brn buf((const TByte*)aUdn.c_str(), (TUint)aUdn.length());
    iDevice = new DviDeviceStandard(*gDvStack, buf, *iResourceManager);
    SetUdn(aUdn);
}

DvDeviceStdStandard::~DvDeviceStdStandard()
{
    delete iResourceManager;
}

void DvDeviceStdStandard::GetResourceManagerUri(const NetworkAdapter& aAdapter, std::string& aUri)
{
    Brh uri;
    iDevice->GetResourceManagerUri(aAdapter, uri);
    if (uri.Bytes() == 0) {
        aUri = std::string();
    }
    else {
        aUri = std::string((const char*)uri.Ptr(), (size_t)uri.Bytes());
    }
}
