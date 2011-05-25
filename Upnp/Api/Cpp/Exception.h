#ifndef HEADER_EXCEPTION
#define HEADER_EXCEPTION

#include <OhNetTypes.h>
#include <exception>

#ifdef DEFINE_TRACE
# define THROW_WITH_FILE_LINE(aClass, aFile, aLine) throw aClass(aFile, aLine)
# define THROW(aClass) throw aClass(__FILE__,__LINE__)
#else
# define THROW_WITH_FILE_LINE(aClass, aFile, aLine) throw aClass()
# define THROW(aClass) throw aClass()
#endif // DEFINE_TRACE

#ifdef DEFINE_TRACE
# define EXCEPTION(aClass) \
namespace OpenHome { \
namespace Net { \
class aClass : public OpenHome::Net::Exception \
{ \
public: \
    aClass(const TChar* aFile, TUint aLine) \
        : OpenHome::Net::Exception(#aClass, aFile, aLine){} \
}; \
} }

#else // DEFINE_TRACE
# define EXCEPTION(aClass) \
namespace OpenHome { \
namespace Net { \
class aClass : public OpenHome::Net::Exception \
{ \
public: \
    aClass() : OpenHome::Net::Exception(#aClass) {} \
}; \
} }

#endif // DEFINE_TRACE

namespace OpenHome {
namespace Net {

/**
 * @internal
 * @@ {
 */

typedef void (*AssertHandler)(const TChar*, TUint);

void AssertHandlerDefault(const TChar*, TUint);

AssertHandler SetAssertHandler(AssertHandler);
DllExport void CallAssertHandler(const TChar*, TUint);

/** Base class for all ohNet exceptions.  Some may be recoverable, others may
not. */
class DllExportClass Exception
{
public:
    DllExport Exception(const TChar* aMsg, const TChar* aFile, TUint aLine);
    DllExport Exception(const TChar* aMsg);
    DllExport ~Exception();
    DllExport const TChar* File();
    DllExport TUint Line();
    DllExport const TChar* Message();
private:
    Exception();
private:
    const TChar* iMsg;
    const TChar* iFile;
    TUint iLine;
};

void UnhandledExceptionHandler(const TChar* aExceptionMessage, const TChar* aFile, TUint aLine);
void UnhandledExceptionHandler(std::exception& aException);
void UnhandledExceptionHandler(Exception& aException);

/* @@} */

} // namespace Net
} // namespace OpenHome

#endif //HEADER_EXCEPTION
