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

class DvService
{
public:
    void PropertiesLock();
    void PropertiesUnlock();
protected:
    DllExport DvService(DviDevice& aDevice, const TChar* aDomain, const TChar* aType, TUint aVersion);
    DllExport virtual ~DvService();
    DllExport void SetPropertyInt(PropertyInt& aProperty, TInt aValue);
    DllExport void SetPropertyUint(PropertyUint& aProperty, TUint aValue);
    DllExport void SetPropertyBool(PropertyBool& aProperty, TBool aValue);
    DllExport void SetPropertyString(PropertyString& aProperty, const Brx& aValue);
    DllExport void SetPropertyBinary(PropertyBinary& aProperty, const Brx& aValue);
protected:
    DviService* iService;
private:
    TBool iDelayPropertyUpdates;
    TBool iPropertyChanged;
};

} // namespace Zapp

#endif // HEADER_DVSERVICE

