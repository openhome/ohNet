#ifndef HEADER_CPDEVICECPP
#define HEADER_CPDEVICECPP

#include <Buffer.h>
#include <Std/FunctorCpDevice.h>

#include <string>
#include <map>

namespace Zapp {

class CpiDevice;
class CpDeviceCpp
{
public:
    const std::string& Udn() const;
    TBool operator==(const CpDeviceCpp& aDevice) const;
    TBool operator!=(const CpDeviceCpp& aDevice) const;
    void AddRef();
    void RemoveRef();
    TBool GetAttribute(const char* aKey, std::string& aValue) const;
    CpiDevice& Device();
private:
    CpDeviceCpp(CpiDevice& aDevice);
    ~CpDeviceCpp();
    CpDeviceCpp(const CpDeviceCpp&);
    void operator=(const CpDeviceCpp&);
    friend class CpDeviceListCpp;
private:
    CpiDevice& iDevice;
    std::string iUdn;
    uint32_t iRefCount;
};

class CpiDeviceList;
class FunctorCpiDevice;
/**
 * List of devices available on the current subnet
 */
class CpDeviceListCpp
{
public:
    ~CpDeviceListCpp();
    void Refresh();
protected:
    CpDeviceListCpp(FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved);
    void GetAddedFunctor(FunctorCpiDevice& aFunctor);
    void GetRemovedFunctor(FunctorCpiDevice& aFunctor);
private:
    void Added(CpiDevice& aDevice);
    void Removed(CpiDevice& aDevice);
protected:
    CpiDeviceList* iList;
private:
    typedef std::map<Brn,CpDeviceCpp*,BufferCmp> Map;
    Map iMap;
    FunctorCpDeviceCpp iAdded;
    FunctorCpDeviceCpp iRemoved;
};

} // namespace Zapp

#endif // HEADER_CPDEVICECPP
