#include "graph.h"

void Out_Window_Title (WINDOW *Wnd, char *Title)
{
    char Sides_Title = '|';
    box(Wnd, ACS_VLINE, ACS_HLINE);
    wmove(Wnd, 0, 1);
    wprintw(Wnd, "%c%s%c", Sides_Title, Title, Sides_Title);
    #ifndef DEBUG
        wrefresh(Wnd);
    #endif
}