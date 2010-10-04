#ifndef HEADER_CPDEVICE
#define HEADER_CPDEVICE

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/FunctorCpDevice.h>

#include <map>

namespace Zapp {

class CpiDevice;
class CpDevice
{
public:
    CpDevice(CpiDevice& aDevice);
    DllExport const Brx& Udn() const;
    DllExport TBool operator==(const CpDevice& aDevice) const;
    DllExport TBool operator!=(const CpDevice& aDevice) const;
    DllExport void AddRef();
    DllExport void RemoveRef();
    DllExport TBool GetAttribute(const char* aKey, Brh& aValue) const;
    DllExport CpiDevice& Device();
private:
    ~CpDevice();
    CpDevice(const CpDevice&);
    void operator=(const CpDevice&);
private:
    CpiDevice& iDevice;
    TUint iRefCount;
};

class CpiDeviceList;
class FunctorCpiDevice;
/**
 * List of devices available on the current subnet
 */
class CpDeviceList
{
public:
    DllExport ~CpDeviceList();
    DllExport void Refresh();
protected:
    CpDeviceList(FunctorCpDevice aAdded, FunctorCpDevice aRemoved);
    void GetAddedFunctor(FunctorCpiDevice& aFunctor);
    void GetRemovedFunctor(FunctorCpiDevice& aFunctor);
private:
    void Added(CpiDevice& aDevice);
    void Removed(CpiDevice& aDevice);
protected:
    CpiDeviceList* iList;
private:
    typedef std::map<Brn,CpDevice*,BufferCmp> Map;
    Map iMap;
    FunctorCpDevice iAdded;
    FunctorCpDevice iRemoved;
};

} // namespace Zapp

#endif // HEADER_CPDEVICE
