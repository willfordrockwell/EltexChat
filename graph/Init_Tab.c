#include "graph.h"

void Init_Tab(struct Tab_s *Tab, int Tab_Height, int Tab_Length, int Start_Y,
              int Start_X)
{
    int Input_High = 3;
    int Messages_High = getmaxy(stdscr) - Input_High - 2;
    Tab->Tab = newwin(Tab_Height, Tab_Length, Start_Y, Start_X);

    Tab->Messages = derwin(Tab->Tab, Messages_High - 2, Tab_Length - 2, 1, 1);
    Tab->Input_Border = derwin(Tab->Tab, Input_High, Tab_Length - 2, Messages_High + 1, 1);
    Tab->Input = derwin(Tab->Input_Border, 1, Tab_Length - 4, 1, 1);

    box(Tab->Tab, ACS_VLINE, ACS_HLINE);
    box(Tab->Input_Border, ACS_VLINE, ACS_HLINE);
    
    scrollok(Tab->Messages, 1);

    wattron(Tab->Tab, COLOR_PAIR(1));
    wbkgd(Tab->Tab, COLOR_PAIR(1));
    wattron(Tab->Messages, COLOR_PAIR(2));
    wbkgd(Tab->Messages, COLOR_PAIR(2));
    wattron(Tab->Input_Border, COLOR_PAIR(1));
    wbkgd(Tab->Input_Border, COLOR_PAIR(1));
    wattron(Tab->Input, COLOR_PAIR(1));
    wbkgd(Tab->Input, COLOR_PAIR(1));
}