#include "graph.h"

void Out_Str_Window(WINDOW *Wnd, int Start_Y, int Start_X, char *Input)
{
    mvwaddstr(Wnd, Start_Y, Start_X, Input);
    #ifndef DEBUG
        wrefresh(Wnd);
    #endif // !DEBUG
}