

#include <stdio.h>

enum Colors
{
    RESET_COLOR,
    BLACK_TXT = 30,
    RED_TXT,
    GREEN_TXT,
    YELLOW_TXT,
    BLUE_TXT,
    MAGENTA_TXT,
    CYAN_TXT,
    WHITE_TXT,

    BLACK_BKG = 40,
    RED_BKG,
    GREEN_BKG,
    YELLOW_BKG,
    BLUE_BKG,
    MAGENTA_BKG,
    CYAN_BKG,
    WHITE_BKG
};

enum ClearCodes
{
    CLEAR_FROM_CURSOR_TO_END,
    CLEAR_FROM_CURSOR_TO_BEGIN,
    CLEAR_ALL
};

void setupConsole(void);
void restoreConsole(void);
void getCursorPosition(int *row, int *col);

static inline void setTextColor(int code)
{
    printf("\x1b[%dm", code);
}

static inline void setTextColorBright(int code)
{
    printf("\x1b[%d;1m", code);
}

static inline void setBackgroundColor(int code)
{
    printf("\x1b[%dm", code);
}

static inline void setBackgroundColorBright(int code)
{
    printf("\x1b[%d;1m", code);
}

static inline void resetColor(void)
{
    printf("\x1b[%dm", RESET_COLOR);
}

static inline void clearScreen(void)
{
    printf("\x1b[%dJ", CLEAR_ALL);
}

static inline void clearScreenToBottom(void)
{
    printf("\x1b[%dJ", CLEAR_FROM_CURSOR_TO_END);
}

static inline void clearScreenToTop(void)
{
    printf("\x1b[%dJ", CLEAR_FROM_CURSOR_TO_BEGIN);
}

static inline void clearLine(void)
{
    printf("\x1b[%dK", CLEAR_ALL);
}

static inline void clearLineToRight(void)
{
    printf("\x1b[%dK", CLEAR_FROM_CURSOR_TO_END);
}

static inline void clearLineToLeft(void)
{
    printf("\x1b[%dK", CLEAR_FROM_CURSOR_TO_BEGIN);
}

static inline void moveUp(int positions)
{
    printf("\x1b[%dA", positions);
}

static inline void moveDown(int positions)
{
    printf("\x1b[%dB", positions);
}

static inline void moveRight(int positions)
{
    printf("\x1b[%dC", positions);
}

static inline void moveLeft(int positions)
{
    printf("\x1b[%dD", positions);
}

static inline void moveTo(int row, int col)
{
    printf("\x1b[%d;%df", row, col);
}

static inline void saveCursorPosition(void)
{
    printf("\x1b%d", 7);
}

static inline void restoreCursorPosition(void)
{
    printf("\x1b%d", 8);
}


#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

static HANDLE stdoutHandle, stdinHandle;
static DWORD outModeInit, inModeInit;

void setupConsole(void)
{
    DWORD outMode = 0, inMode = 0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    stdinHandle = GetStdHandle(STD_INPUT_HANDLE);

    if (stdoutHandle == INVALID_HANDLE_VALUE || stdinHandle == INVALID_HANDLE_VALUE)
    {
        exit(GetLastError());
    }

    if (!GetConsoleMode(stdoutHandle, &outMode) || !GetConsoleMode(stdinHandle, &inMode))
    {
        exit(GetLastError());
    }

    outModeInit = outMode;
    inModeInit = inMode;

    // Enable ANSI escape codes
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    // Set stdin as no echo and unbuffered
    inMode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);

    if (!SetConsoleMode(stdoutHandle, outMode) || !SetConsoleMode(stdinHandle, inMode))
    {
        exit(GetLastError());
    }
}

void restoreConsole(void)
{
    // Reset colors
    printf("\x1b[0m");

    // Reset console mode
    if (!SetConsoleMode(stdoutHandle, outModeInit) || !SetConsoleMode(stdinHandle, inModeInit))
    {
        exit(GetLastError());
    }
}
#else

static struct termios orig_term;
static struct termios new_term;

void setupConsole(void)
{
    tcgetattr(STDIN_FILENO, &orig_term);
    new_term = orig_term;

    new_term.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

void restoreConsole(void)
{
    // Reset colors
    printf("\x1b[0m");

    // Reset console mode
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
}
#endif

void getCursorPosition(int *row, int *col)
{
    printf("\x1b[6n");
    char buff[128];
    int indx = 0;
    for (;;)
    {
        int cc = getchar();
        buff[indx] = (char)cc;
        indx++;
        if (cc == 'R')
        {
            buff[indx + 1] = '\0';
            break;
        }
    }
    sscanf(buff, "\x1b[%d;%dR", row, col);
    fseek(stdin, 0, SEEK_END);
}



#include <iostream>
#ifdef _WIN32

#include <wchar.h>
#include <locale.h>

void testBlueBlankCanvas(const unsigned x_dim, 
            const unsigned y_dim)
{
  setlocale(LC_CTYPE, "");
  wchar_t FULLBLOCK = 0x2588;
  for ( unsigned i = 0; i < x_dim; i++)
  {
    setTextColor(BLUE_TXT);
    printf("|");
    for (unsigned j = 0; j < y_dim; j++)
    {

      //wprintf(L"\xe2\x96\x88"); 
      //wprintf(L"\xe2\x96\x88"); 
      wprintf(L"\u2588");
    }
    printf("|");
    puts("");
  }
  setTextColor(RESET_COLOR);
}

void blankCanvas(const unsigned x_dim, 
            const unsigned y_dim)
{
  std::cout << "Existance game of Agents - Population." << std::endl; 
  setlocale(LC_CTYPE, "");
  wchar_t FULLBLOCK = 0x2588;
  for ( unsigned i = 0; i < x_dim; i++)
  {
    setTextColor(BLUE_TXT);
    printf("|");
    for (unsigned j = 0; j < y_dim; j++)
    {

      //wprintf(L"\xe2\x96\x88"); 
      //wprintf(L"\xe2\x96\x88"); 
      wprintf(L"\u2588");
    }
    printf("|");
    puts("");
  }
  setTextColor(RESET_COLOR);
}





#endif