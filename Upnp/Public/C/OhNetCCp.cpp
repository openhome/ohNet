#include <C/OhNet.h>
#include <OhNet.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void OhNetLibraryStartCp(TIpAddress aSubnet)
{
    UpnpLibrary::StartCp(aSubnet);
}
