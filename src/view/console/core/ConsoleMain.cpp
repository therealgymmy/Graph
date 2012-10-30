#include "../_include/ConsoleMain.h"

// Dependencies
#include <ncurses.h>

void ConsoleMain::start ()
{
    initscr();
    printw("Hello World !!!");
    refresh();
    getch();
    endwin();
}
