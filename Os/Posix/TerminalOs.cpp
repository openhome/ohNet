#include <OpenHome/Private/Terminal.h>
#include <OpenHome/Private/Printer.h>
#include <termios.h>
#include <unistd.h>

namespace OpenHome {

TerminalOs::TerminalOs()
    : iHandle(0)
{
}

TerminalOs::~TerminalOs()
{
    ASSERT(iHandle == 0); // suppress unused variable warning from clang
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

void TerminalOs::Print(const Brx& aBuffer)
{
    Log::Print(aBuffer);
}

} // namespace OpenHome

