#include <Std/CpDeviceDv.h>
#include <CpiDeviceDv.h>
#include <Std/DvDevice.h>
#include <DviDevice.h>

using namespace Zapp;

CpDeviceDvCpp* CpDeviceDvCpp::New(DvDeviceStd& aDevice)
{
    CpiDeviceDv* device = new CpiDeviceDv(aDevice.Device());
    return new CpDeviceDvCpp(*device);
}

CpDeviceDvCpp::~CpDeviceDvCpp()
{
}

CpDeviceDvCpp::CpDeviceDvCpp(CpiDeviceDv& aDevice)
    : CpDeviceCpp(aDevice.Device())
{
}
