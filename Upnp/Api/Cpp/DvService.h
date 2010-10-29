#ifndef HEADER_DVSERVICE
#define HEADER_DVSERVICE

#include <ZappTypes.h>
#include <Buffer.h>
#include <DviDevice.h>

namespace Zapp {

class DviService;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

class DllExportClass DvService
{
public:
    void PropertiesLock();
    void PropertiesUnlock();
protected:
    DllExport DvService(DviDevice& aDevice, const TChar* aDomain, const TChar* aType, TUint aVersion);
    DllExport virtual ~DvService();
    DllExport bool SetPropertyInt(PropertyInt& aProperty, TInt aValue);
    DllExport bool SetPropertyUint(PropertyUint& aProperty, TUint aValue);
    DllExport bool SetPropertyBool(PropertyBool& aProperty, TBool aValue);
    DllExport bool SetPropertyString(PropertyString& aProperty, const Brx& aValue);
    DllExport bool SetPropertyBinary(PropertyBinary& aProperty, const Brx& aValue);
protected:
    DviService* iService;
private:
    TBool iDelayPropertyUpdates;
    TBool iPropertyChanged;
};

} // namespace Zapp

#endif // HEADER_DVSERVICE

