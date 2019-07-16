#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>

#include "graph/graph.h"

#define SHM_SIZE 1000       //All messages max len

#define UNAME_MAX_LEN 30    //Username max len
#define MSG_LEN 76          //Message max len
#define ESC 27              //Esc char

#define UPDATE_TIME 60      //in seconds

struct sembuf Read_Lock = {0, -1, 0};
struct sembuf Read_Ulock = {0, 1, 0};
struct sembuf Write_Lock = {1, -1, 0};
struct sembuf Write_Ulock = {1, 1, 0};

