#include <stdarg.h>
#include <stdio.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;

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

void Debug::AddLevel(TUint aLevel)
{
    iLevel |= aLevel;
}

void Debug::RemoveLevel(TUint aLevel)
{
    iLevel &= ~aLevel;
}

TBool Debug::TestLevel(TUint aLevel)
{
    if ((iLevel & aLevel) != 0) 
    {
        return true;
    }
    
    return false;   
}

AutoLog::AutoLog(TUint aLevel, const TChar* aString)
    : iLevel(aLevel)
    , iString(aString)
{
    if( OpenHome::Debug::TestLevel(iLevel) )
        OpenHome::Log::Print(">%s\n", iString);
}

AutoLog::~AutoLog()
{
    if( OpenHome::Debug::TestLevel(iLevel) )
        OpenHome::Log::Print("<%s\n", iString);
}
