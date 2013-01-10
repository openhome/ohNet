#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Private/Globals.h>

using namespace OpenHome;
using namespace OpenHome::Net;

DvStack* Library::StartDv()
{
    return new DvStack(*iEnv);
}

void UpnpLibrary::StartDv()
{ // static
    gDvStack = new DvStack(*gEnv);
}
