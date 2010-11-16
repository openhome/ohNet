#include <Core/CpDeviceDv.h>
#include <CpiDeviceDv.h>
#include <DviDevice.h>

using namespace Zapp;

CpDeviceDv* CpDeviceDv::New(DvDevice& aDevice)
{
    CpiDeviceDv* device = new CpiDeviceDv(aDevice.Device());
    return new CpDeviceDv(*device);
}

CpDeviceDv::~CpDeviceDv()
{
}

CpDeviceDv::CpDeviceDv(CpiDeviceDv& aDevice)
    : CpDevice(aDevice.Device())
{
}
