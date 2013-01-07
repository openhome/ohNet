#include <OpenHome/Net/Core/CpDeviceDv.h>
#include <OpenHome/Net/Private/CpiDeviceDv.h>
#include <OpenHome/Net/Private/DviDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

CpDeviceDv* CpDeviceDv::New(CpStack& aCpStack, DvDevice& aDevice)
{
    CpiDeviceDv* device = new CpiDeviceDv(aCpStack, aDevice.Device());
    CpDeviceDv* self = new CpDeviceDv(*device);
    self->Device().RemoveRef();
    return self;
}

CpDeviceDv::~CpDeviceDv()
{
}

CpDeviceDv::CpDeviceDv(CpiDeviceDv& aDevice)
    : CpDevice(aDevice.Device())
{
}
