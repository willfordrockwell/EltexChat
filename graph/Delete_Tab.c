#include "graph.h"

void Delete_Tab(struct Tab_s *Tab)
{
    delwin(Tab->Tab);
    delwin(Tab->Messages);
    delwin(Tab->Input_Border);
    delwin(Tab->Input);
}