#include <OpenHome/Net/Cpp/CpDeviceDv.h>
#include <OpenHome/Net/Private/CpiDeviceDv.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/Globals.h>

using namespace OpenHome;
using namespace OpenHome::Net;

CpDeviceDvCpp* CpDeviceDvCpp::New(DvDeviceStd& aDevice)
{
    CpiDeviceDv* device = new CpiDeviceDv(*gCpStack, aDevice.Device());
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
