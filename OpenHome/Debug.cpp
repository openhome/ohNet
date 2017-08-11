#include <stdarg.h>
#include <stdio.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;

TUint64 Debug::iLevel = Debug::kNone;
TUint Debug::iSeverity = Debug::kSeverityError;

void Debug::SetSeverity(TUint aSeverity)
{
    iSeverity = aSeverity;
}

TUint Debug::Severity()
{
    return iSeverity;
}

TUint64 Debug::Level()
{
    return iLevel;
}

void Debug::SetLevel(TUint64 aLevel)
{
    iLevel = aLevel;
}

void Debug::AddLevel(TUint64 aLevel)
{
    iLevel |= aLevel;
}

void Debug::RemoveLevel(TUint64 aLevel)
{
    iLevel &= ~aLevel;
}


AutoLog::AutoLog(TUint64 aLevel, const TChar* aString)
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
