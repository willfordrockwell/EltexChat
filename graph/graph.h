#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <curses.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

struct Tab_s {
    WINDOW *Tab;
    WINDOW *Messages;
    WINDOW *Input_Border;
    WINDOW *Input;
};

void Sig_Winch (int signo);

void Init (struct Tab_s *First, char *Username);

void Init_Tab (struct Tab_s *Tab, int Tab_Height, int Tab_Length, int Start_Y,
               int Start_X);

void Refresh_Tab (struct Tab_s *Tab);

void Delete_Tab (struct Tab_s *Tab);

void Out_Window_Title (WINDOW *Wnd, char *Title);

void Out_Str_Window (WINDOW *Wnd, int Start_Y, int Start_X, char *Input);

void End_Window();

#endif
