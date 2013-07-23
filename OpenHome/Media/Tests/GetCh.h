#ifndef HEADER_W32GETCH
#define HEADER_W32GETCH

#ifdef _WIN32
# include <conio.h>

int mygetch()
{
    return (_getch());
}

#elif defined(NOTERMIOS)

int mygetch()
{
    return 0;
}

#else

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

#endif // HEADER_W32GETCH
