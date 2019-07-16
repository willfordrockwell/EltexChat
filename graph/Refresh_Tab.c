#include "graph.h"

void Refresh_Tab (struct Tab_s *Tab)
{
    wrefresh(Tab->Tab);
    wrefresh(Tab->Messages);
    wrefresh(Tab->Input_Border);
    wrefresh(Tab->Input);
}