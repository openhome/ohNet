#include <OpenHome/Private/Terminal.h>
#include <OpenHome/Private/Printer.h>
#include <termios.h>
#include <unistd.h>
#include <cstdarg>

namespace OpenHome {

TerminalOs::TerminalOs()
    : iHandle(0)
{
}

TChar TerminalOs::GetChar()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return (TChar) ch;
}

void TerminalOs::Print(const TChar* aFormat, ...)
{
    va_list args;
    va_start(args, aFormat);
    PrintVA(aFormat, args);
    va_end(args);
}

void TerminalOs::Print(const Brx& aBuffer)
{
    Log::Print(aBuffer);
}

void TerminalOs::PrintVA(const TChar* aFormat, va_list aArgs)
{
    Log::PrintVA(aFormat, aArgs);
}

} // namespace OpenHome

