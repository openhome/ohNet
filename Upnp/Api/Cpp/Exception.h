#ifndef HEADER_EXCEPTION
#define HEADER_EXCEPTION

#include <ZappTypes.h>
#include <exception>

#ifdef DEFINE_TRACE
# define THROW_WITH_FILE_LINE(aClass, aFile, aLine) throw aClass(aFile, aLine)
# define THROW(aClass) throw aClass(__FILE__,__LINE__)
#else
# define THROW_WITH_FILE_LINE(aClass, aFile, aLine) throw aClass()
# define THROW(aClass) throw aClass()
#endif //DEFINE_TRACE

#ifdef DEFINE_TRACE
# define EXCEPTION(aClass) \
namespace Zapp { \
class aClass : public Zapp::Exception \
{ \
public: \
    aClass(const TChar* aFile, TUint aLine) \
        : Zapp::Exception(#aClass, aFile, aLine){} \
}; \
} \

#else //DEFINE_TRACE
# define EXCEPTION(aClass) \
namespace Zapp { \
class aClass : public Zapp::Exception \
{ \
public: \
    aClass() : Zapp::Exception(#aClass) {} \
}; \
} \

#endif // DEFINE_TRACE

namespace Zapp
{

typedef void (*AssertHandler)(const TChar*, TUint);

void AssertHandlerDefault(const TChar*, TUint);

AssertHandler SetAssertHandler(AssertHandler);
DllExport void CallAssertHandler(const TChar*, TUint);

/** Base class for all Zapp exceptions.  Some may be recoverable, others may
not. */
class Exception
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

} //namespace Zapp

#endif //HEADER_EXCEPTION
