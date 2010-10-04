#ifndef HEADER_DEBUG
#define HEADER_DEBUG

#include <Standard.h>
#include <stdarg.h>
#include <Printer.h>

EXCEPTION(AssertionFailed);

class AutoLog
{
public:
    AutoLog(Zapp::TUint aLevel, const Zapp::TChar* aString);
    ~AutoLog();
private:
    Zapp::TUint  iLevel;
    const Zapp::TChar* iString;
};

#ifdef DEFINE_TRACE
    #define LOG(x,...) \
        {if(Zapp::Debug::TestLevel(Zapp::Debug::x)) \
         { \
            Zapp::Log::Print(__VA_ARGS__); \
         } \
        }
    #define LOG2(x,y,...) \
        {if(Zapp::Debug::TestLevel(Zapp::Debug::x|Zapp::Debug::y)) \
         { \
            Zapp::Log::Print(__VA_ARGS__); \
         } \
        }
    #define LOG2F(x,y,...) \
        {if(Zapp::Debug::TestLevel(Zapp::Debug::x|Zapp::Debug::y)) \
         { \
            Zapp::Log::Print("%s:%d: ",__FILE__,__LINE__); \
            Zapp::Log::Print(__VA_ARGS__); \
         } \
        }
    #define LOG2T(x,y,...) \
        {if(Zapp::Debug::TestLevel(Zapp::Debug::x|Zapp::Debug::y)) \
         { \
            Zapp::Log::Print("Thread: %p: ",(Zapp::Thread*)(Zapp::Thread::Current())); \
            Zapp::Log::Print(__VA_ARGS__); \
         } \
        }
    #define LOGF(x,...) \
        {if(Zapp::Debug::TestLevel(Zapp::Debug::x)) \
         { \
            Zapp::Log::Print("%s:%d: ",__FILE__,__LINE__); \
            Zapp::Log::Print(__VA_ARGS__); \
         } \
        }
    #define LOGT(x,...) \
        {if(Zapp::Debug::TestLevel(Zapp::Debug::x)) \
         { \
            const Brx& name = Zapp::Thread::Current()->Name(); \
            Zapp::Log::Print("T:%c%c%c%c:",name[0],name[1],name[2],name[3]); \
            Zapp::Log::Print(__VA_ARGS__); \
         } \
        }
    #define LOG_HEX(x,aBrx) \
        {if(Zapp::Debug::TestLevel(Zapp::Debug::x)) \
         { \
            Zapp::Log::PrintHex(aBrx); \
         } \
        }
    #define LOGF_HEX(x,aBrx) \
        {if(Zapp::Debug::TestLevel(Zapp::Debug::x)) \
         { \
            Zapp::Log::Print("%s:%d: ",__FILE__,__LINE__); \
            Zapp::Log::PrintHex(aBrx); \
         } \
        }
    #define LOGFUNC(x) \
        AutoLog localAutolog(Zapp::Debug::x , __PRETTY_FUNCTION__)
#else //DEFINE_TRACE
    #define LOG(x,...)
    #define LOGF(x,...)
    #define LOGT(x,...)
    #define LOG2(x,y,...)
    #define LOG2F(x,y,...)
    #define LOG2T(x,y,...)
    #define LOG_HEX(x,aBrx)
    #define LOGF_HEX(x,aBrx)
    #define LOGFUNC(x)
#endif //DEFINE_TRACE

namespace Zapp {

class Brx;

class Debug
{
public:
    static const TUint kNone           = 0;
    static const TUint kError          = 1<<1;
    static const TUint kThread         = 1<<2;
    static const TUint kNetwork        = 1<<3;
    static const TUint kTimer          = 1<<4;
    static const TUint kSsdpMulticast  = 1<<5;
    static const TUint kSsdpUnicast    = 1<<6;
    static const TUint kHttp           = 1<<7;
    static const TUint kDevice         = 1<<8;
    static const TUint kXmlFetch       = 1<<9;
    static const TUint kService        = 1<<10;
    static const TUint kEvent          = 1<<11;
    static const TUint kTopology       = 1<<12;
    static const TUint KDvInvocation   = 1<<13;
    static const TUint kDvEvent        = 1<<14;

    static const TUint kAll            = 0x7FFFFFFF;
    static const TUint kVerbose        = 0x80000000;

    static TBool TestLevel(TUint aLevel);
    static TUint Level();
    static void SetLevel(TUint aLevel);
    static TBool BreakBeforeThrow();
    static void SetBreakBeforeThrow(TBool aBreak);

private:
    static TUint iLevel;
    static TBool iBreak;
    static const TUint kMaxDebugPrintBytes = 256;
};

} //namespace Zapp

#endif //HEADER_DEBUG
