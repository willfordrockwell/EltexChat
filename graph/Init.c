#include "graph.h"

void Init(struct Tab_s *First, char *Username)
{
    int Start_Y = 0;
    int Start_X_First = 0;
    initscr();
    #ifndef DEBUG
        noecho();
    #endif
    int Rows, Cols;
    getmaxyx(stdscr, Rows, Cols);
    //cbreak();
    echo();
    signal(SIGWINCH, Sig_Winch);
    keypad(stdscr, 1);

    start_color();
    #ifndef DEBUG
        curs_set(1);
    #endif
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    #ifndef DEBUG
        wattron(stdscr, A_BOLD);
        refresh();
    #endif // !DEBUG

    Init_Tab(First, Rows, Cols, Start_Y, Start_X_First);
    Out_Window_Title(First->Tab, "Messenger");
    Out_Window_Title(First->Input_Border, Username);

    #ifndef DEBUG
        curs_set(0);
        Refresh_Tab(First);
    #endif
}
