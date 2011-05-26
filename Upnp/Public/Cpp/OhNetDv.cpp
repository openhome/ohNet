#include <OhNet.h>
#include <DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void UpnpLibrary::StartDv()
{
    new DviStack();
}
