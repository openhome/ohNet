#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Terminal.h>

#include <conio.h>

namespace OpenHome {

TerminalOs::TerminalOs()
    : iHandle(0)
{
}

TerminalOs::~TerminalOs()
{
}

TChar TerminalOs::GetChar()
{
#ifndef DEFINE_WINDOWS_UNIVERSAL
    return (TChar) (_getch());
#else
  return (TChar)'\0';
#endif
}

void TerminalOs::Print(const Brx& aBuffer)
{
    Log::Print(aBuffer);
}

} // namespace OpenHome

