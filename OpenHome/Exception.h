#ifndef HEADER_EXCEPTION
#define HEADER_EXCEPTION

#include <OpenHome/OhNetTypes.h>
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
class aClass : public OpenHome::Exception \
{ \
public: \
    aClass(const TChar* aFile, TUint aLine) \
        : OpenHome::Exception(#aClass, aFile, aLine){} \
}; \
}

#else // DEFINE_TRACE
# define EXCEPTION(aClass) \
namespace OpenHome { \
class aClass : public OpenHome::Exception \
{ \
public: \
    aClass() : OpenHome::Exception(#aClass) {} \
}; \
}

#endif // DEFINE_TRACE

namespace OpenHome {

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
    DllExport Exception(const Exception& aException);
    DllExport ~Exception();
    DllExport const TChar* File();
    DllExport TUint Line();
    DllExport const TChar* Message();
    DllExport THandle StackTrace();
    DllExport void LogStackTrace();
protected:
    DllExport Exception(const TChar* aMsg, const TChar* aFile, TUint aLine);
    DllExport Exception(const TChar* aMsg);
    Exception& operator=(const Exception&);
private:
    Exception();
private:
    const TChar* iMsg;
    THandle iStackTrace;
    const TChar* iFile;
    TUint iLine;
};

void UnhandledExceptionHandler(const TChar* aExceptionMessage, const TChar* aFile, TUint aLine);
void UnhandledExceptionHandler(std::exception& aException);
void UnhandledExceptionHandler(Exception& aException);

/* @@} */

} // namespace OpenHome

#endif //HEADER_EXCEPTION
