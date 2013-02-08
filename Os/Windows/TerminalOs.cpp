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
    return (TChar) (_getch());
}

void TerminalOs::Print(const Brx& aBuffer)
{
    Log::Print(aBuffer);
}

} // namespace OpenHome

