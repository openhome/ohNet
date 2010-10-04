#include <Zapp.h>

using namespace Zapp;

void UpnpLibrary::StartCombined()
{
    UpnpLibrary::StartCp();
    UpnpLibrary::StartDv();
}
