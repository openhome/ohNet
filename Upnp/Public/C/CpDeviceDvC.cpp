#include <C/CpDeviceDv.h>
#include <Core/CpDeviceDv.h>
#include <C/DviDeviceC.h>

using namespace Zapp;

CpDeviceC CpDeviceDvCreate(DvDeviceC aDevice)
{
    CpDeviceDv* d = CpDeviceDv::New(*DviDeviceC::DeviceFromHandle(aDevice));
    return (CpDeviceC)&d->Device();
}
