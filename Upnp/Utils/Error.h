#ifndef HEADER_ERROR
#define HEADER_ERROR

#include <ZappTypes.h>
#include <Buffer.h>
#include <FunctorAsync.h>

namespace Zapp {

/**
 * Utility class for storing error information.
 * Some error levels have codes/reasons provided elsewhere (e.g. HttpStatus
 * provides detailed reporting for Http, Upnp action errors are reported as XML
 * responses).  Other error levels are outlined here.
 * Clients are free to add levels/codes as required.
 * Or, equally, clients may choose to ignore this and report errors in any other way
 */
class Error
{
public:
    static const TUint kCodeNoError = 0;
    static const TUint kCodeUnknown = 1;

    static const Brn kDescriptionUnknown;
    static const Brn kDescriptionSocketTimeout;
    static const Brn kDescriptionParameterInvalid;
    static const Brn kDescriptionAsyncInterrupted;
    static const Brn kDescriptionAsyncShutdown;

    enum ELevel
    {
        eNone
       ,eSocket
       ,eHttp
       ,eUpnp
       ,eService
       ,eAsync
    };
    enum ECodeSocket
    {
        eCodeTimeout = kCodeUnknown+1
    };
    enum ECodeService
    {
        eCodeParameterInvalid = kCodeUnknown+1
    };
    enum ECodeAsync
    {
        eCodeInterrupted = kCodeUnknown+1
       ,eCodeShutdown
    };

    Error();
    void Set(ELevel aLevel, TUint aCode, const Brx& aDescription);
    void Output(IAsyncOutput& aConsole);
    void Clear();
    ELevel Level() const { return iLevel; }
    const TChar* LevelName() const;
    TUint Code() const { return iCode; }
    const TChar* Description() const { return (const TChar*)iDescription.Ptr(); }
private:
    ELevel iLevel;
    TUint iCode;
    Brhz  iDescription;
};


} // namespace Zapp

#endif // HEADER_ERROR
