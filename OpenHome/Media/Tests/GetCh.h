#pragma once

#include <OpenHome/Private/Thread.h>

#ifdef _WIN32
# include <conio.h>

int mygetch()
{
    return (_getch());
}

#elif defined(NOTERMIOS)

int mygetch()
{
    // This implementation is for embedded platforms.
    // We intend to block here for eternity.
    OpenHome::Semaphore localSema("private", 0);
    localSema.Wait();
    return 0; // will never happen.
}

#else

# include <stdio.h>
# include <termios.h>
# include <unistd.h>

int mygetch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

#endif // _WIN32

