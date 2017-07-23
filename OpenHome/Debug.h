#ifndef HEADER_DEBUG
#define HEADER_DEBUG

#include <OpenHome/Private/Standard.h>
#include <stdarg.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Types.h>

class AutoLog
{
public:
    AutoLog(OpenHome::TUint64 aLevel, const OpenHome::TChar* aString);
    ~AutoLog();
private:
    OpenHome::TUint64  iLevel;
    const OpenHome::TChar* iString;
};

#ifdef DEFINE_TRACE
    #define LOG(x,...) \
        {if(OpenHome::Debug::TestLevel(OpenHome::Debug::x)) { \
            OpenHome::Log::Print(__VA_ARGS__); \
         } \
        }
    #define LOG2(x,y,...) \
        {if(OpenHome::Debug::TestLevel(OpenHome::Debug::x|OpenHome::Debug::y)) { \
            OpenHome::Log::Print(__VA_ARGS__); \
         } \
        }
    #define LOG3(x,y,z,...) \
        {if(OpenHome::Debug::TestLevel(OpenHome::Debug::x|OpenHome::Debug::y|OpenHome::Debug::z)) { \
            OpenHome::Log::Print(__VA_ARGS__); \
         } \
        }
    #define LOG2F(x,y,...) \
        {if(OpenHome::Debug::TestLevel(OpenHome::Debug::x|OpenHome::Debug::y)) { \
            OpenHome::Log::Print("%s:%d: ",__FILE__,__LINE__); \
            OpenHome::Log::Print(__VA_ARGS__); \
         } \
        }
    #define LOGF(x,...) \
        {if(OpenHome::Debug::TestLevel(OpenHome::Debug::x)) { \
            OpenHome::Log::Print("%s:%d: ",__FILE__,__LINE__); \
            OpenHome::Log::Print(__VA_ARGS__); \
         } \
        }
    #define LOGT(x,...) \
        {if(OpenHome::Debug::TestLevel(OpenHome::Debug::x)) { \
            const OpenHome::Brx& name = OpenHome::Thread::CurrentThreadName(); \
            OpenHome::Log::Print("T:%c%c%c%c:",name[0],name[1],name[2],name[3]); \
            OpenHome::Log::Print(__VA_ARGS__); \
         } \
        }
    #define LOG_HEX(x,aBrx) \
        {if(OpenHome::Debug::TestLevel(OpenHome::Debug::x)) { \
            OpenHome::Log::PrintHex(aBrx); \
         } \
        }
    #define LOGF_HEX(x,aBrx) \
        {if(OpenHome::Debug::TestLevel(OpenHome::Debug::x)) { \
            OpenHome::Log::Print("%s:%d: ",__FILE__,__LINE__); \
            OpenHome::Log::PrintHex(aBrx); \
         } \
        }
    #ifdef _MSC_VER
        #define LOGFUNC(x) \
            AutoLog localAutolog(OpenHome::Debug::x , __FUNCSIG__)
    #else
        #define LOGFUNC(x) \
            AutoLog localAutolog(OpenHome::Debug::x , __PRETTY_FUNCTION__)
    #endif
#else //DEFINE_TRACE
    #define LOG(x,...)
    #define LOGF(x,...)
    #define LOGT(x,...)
    #define LOG2(x,y,...)
    #define LOG2F(x,y,...)
    #define LOG3(x,y,z,...)
    #define LOG_HEX(x,aBrx)
    #define LOGF_HEX(x,aBrx)
    #define LOGFUNC(x)
#endif //DEFINE_TRACE

namespace OpenHome {

class Brx;

class Debug
{
public:
    static const TUint   kNone           = 0;
    static const TUint   kTrace          = 1<<1;
    static const TUint   kThread         = 1<<2;
    static const TUint   kNetwork        = 1<<3;
    static const TUint   kTimer          = 1<<4;
    static const TUint   kSsdpMulticast  = 1<<5;
    static const TUint   kSsdpUnicast    = 1<<6;
    static const TUint   kHttp           = 1<<7;
    static const TUint   kDevice         = 1<<8;
    static const TUint   kXmlFetch       = 1<<9;
    static const TUint   kService        = 1<<10;
    static const TUint   kEvent          = 1<<11;
    static const TUint   kDvSsdpNotifier = 1<<12;
    static const TUint   kDvInvocation   = 1<<13;
    static const TUint   kDvEvent        = 1<<14;
    static const TUint   kDvWebSocket    = 1<<15;
    static const TUint   kLpec           = 1<<16;
    static const TUint   kBonjour        = 1<<17;
    static const TUint   kDvDevice       = 1<<18;
    static const TUint   kApplication0   = 1<<20;
    static const TUint   kApplication1   = 1<<21;
    static const TUint   kApplication2   = 1<<22;
    static const TUint   kApplication3   = 1<<23;
    static const TUint   kApplication4   = 1<<24;
    static const TUint   kApplication5   = 1<<25;
    static const TUint   kApplication6   = 1<<26;
    static const TUint   kApplication7   = 1<<27;
    static const TUint   kApplication8   = 1<<28;
    static const TUint   kApplication9   = 1<<29;
    static const TUint   kError          = 1<<30;
    static const TUint   kVerbose        = 0x80000000;
    static const TUint64 kAdapterChange  = static_cast<TUint64>(1)<<32;
    static const TUint64 kApplication13  = static_cast<TUint64>(1)<<33;
    static const TUint64 kApplication14  = static_cast<TUint64>(1)<<34;
    static const TUint64 kApplication15  = static_cast<TUint64>(1)<<35;
    static const TUint64 kApplication16  = static_cast<TUint64>(1)<<36;
    static const TUint64 kApplication17  = static_cast<TUint64>(1)<<37;
    static const TUint64 kApplication18  = static_cast<TUint64>(1)<<38;
    static const TUint64 kApplication19  = static_cast<TUint64>(1)<<39;
    static const TUint64 kApplication20  = static_cast<TUint64>(1)<<40;
    static const TUint64 kApplication21  = static_cast<TUint64>(1)<<41;
    static const TUint64 kApplication22  = static_cast<TUint64>(1)<<42;
    static const TUint64 kApplication23  = static_cast<TUint64>(1)<<43;
    static const TUint64 kApplication24  = static_cast<TUint64>(1)<<44;
    static const TUint64 kApplication25  = static_cast<TUint64>(1)<<45;
    static const TUint64 kApplication26  = static_cast<TUint64>(1)<<46;
    static const TUint64 kApplication27  = static_cast<TUint64>(1)<<47;
    static const TUint64 kApplication28  = static_cast<TUint64>(1)<<48;
    static const TUint64 kApplication29  = static_cast<TUint64>(1)<<49;
    static const TUint64 kApplication30  = static_cast<TUint64>(1)<<50;
    static const TUint64 kApplication31  = static_cast<TUint64>(1)<<51;
    static const TUint64 kApplication32  = static_cast<TUint64>(1)<<52;
    static const TUint64 kApplication33  = static_cast<TUint64>(1)<<53;
    static const TUint64 kApplication34  = static_cast<TUint64>(1)<<54;
    static const TUint64 kApplication35  = static_cast<TUint64>(1)<<55;
    static const TUint64 kApplication36  = static_cast<TUint64>(1)<<56;
    static const TUint64 kApplication37  = static_cast<TUint64>(1)<<57;
    static const TUint64 kApplication38  = static_cast<TUint64>(1)<<58;
    static const TUint64 kApplication39  = static_cast<TUint64>(1)<<59;
    static const TUint64 kApplication40  = static_cast<TUint64>(1)<<60;
    static const TUint64 kApplication41  = static_cast<TUint64>(1)<<61;
    static const TUint64 kApplication42  = static_cast<TUint64>(1)<<62;
    static const TUint64 kCpDeviceDv     = static_cast<TUint64>(1)<<63;
    static const TUint64 kAll            = 0xFFFFFFFF7FFFFFFFull;

    static TBool TestLevel(TUint aLevel)   { return ((iLevel & aLevel) != 0); }
    static TBool TestLevel(TUint64 aLevel) { return ((iLevel & aLevel) != 0); }
    static TUint64 Level();
    static void SetLevel(TUint64 aLevel);
    static void AddLevel(TUint64 aLevel);
    static void RemoveLevel(TUint64 aLevel);
private:
    static TUint64 iLevel;
};

} // namespace OpenHome

#endif //HEADER_DEBUG
