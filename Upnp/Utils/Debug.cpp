#include <stdarg.h>
#include <stdio.h>
#include <Buffer.h>
#include <Debug.h>

using namespace Zapp;

TUint Debug::iLevel = Debug::kNone;
TBool Debug::iBreak = false;

TUint Debug::Level()
{
    return iLevel;
}

void Debug::SetLevel(TUint aLevel)
{
    iLevel = aLevel;
}

TBool Debug::TestLevel(TUint aLevel)
{
    if ((iLevel & aLevel) != 0) 
    {
        return true;
    }
    
    return false;   
}

TBool Debug::BreakBeforeThrow()
{
    return iBreak;
}

void Debug::SetBreakBeforeThrow(TBool aBreak)
{
    iBreak = aBreak;
}

AutoLog::AutoLog(TUint aLevel, const TChar* aString)
    : iLevel(aLevel)
    , iString(aString)
{
    if( Zapp::Debug::TestLevel(iLevel) )
        Zapp::Log::Print(">%s\n", iString);
}

AutoLog::~AutoLog()
{
    if( Zapp::Debug::TestLevel(iLevel) )
        Zapp::Log::Print("<%s\n", iString);
}

