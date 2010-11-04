#include <C/DvProvider.h>
#include <DvProvider.h>

using namespace Zapp;

void DvProviderPropertiesLock(THandle aProvider)
{
    reinterpret_cast<DvProvider*>(aProvider)->PropertiesLock();
}

void DvProviderPropertiesUnlock(THandle aProvider)
{
    reinterpret_cast<DvProvider*>(aProvider)->PropertiesUnlock();
}
