#include <Std/CpDeviceDv.h>
#include <CpiDeviceDv.h>
#include <Std/DvDevice.h>
#include <DviDevice.h>

using namespace OpenHome::Net;

CpDeviceDvCpp* CpDeviceDvCpp::New(DvDeviceStd& aDevice)
{
    CpiDeviceDv* device = new CpiDeviceDv(aDevice.Device());
    CpDeviceDvCpp* self = new CpDeviceDvCpp(*device);
    self->Device().RemoveRef();
    return self;
}

CpDeviceDvCpp::~CpDeviceDvCpp()
{
}

CpDeviceDvCpp::CpDeviceDvCpp(CpiDeviceDv& aDevice)
    : CpDeviceCpp(aDevice.Device())
{
}
