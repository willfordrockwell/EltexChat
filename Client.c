#include "server.h"

int main(int argc, const char** argv) { //idSem idShm username

    if (argc != 4) {
        fprintf(stderr, "type idSem idShm username\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter+Enter to send message, Enter+Esc to exit\n");
    getc(stdin);

    time_t Last_Update = 0;

    int idSem = atoi(argv[1]);
    int idShm = atoi(argv[2]);

    char Chat[SHM_SIZE];

    int InChar = '\0';
    int Exit = 0;

    char *Memory;
    int Chat_Len = 0;
    memset(Chat, 0, SHM_SIZE);

    int Uname_Len;
    char Username[UNAME_MAX_LEN];
    memset(Username, 0, UNAME_MAX_LEN);
    sprintf(Username, "%s%d", argv[3], getpid());

    Uname_Len = strlen(Username);

    struct Tab_s *Tab = (struct Tab_s *) malloc (sizeof(struct Tab_s));
    int Rows = getmaxy(stdscr);
    int Cols = getmaxx(stdscr);

    Init(Tab, Username);

    *(Username + Uname_Len) = ' ';
    Uname_Len++;

    char Message[MSG_LEN];
    strcpy(Message, Username);
    memset(Message + Uname_Len, 0, MSG_LEN - Uname_Len);

    while (Last_Update == 0) {
        //try read
        if (semop(idSem, &Read_Lock, 1) == 0) {
            Memory = (char *) shmat(idShm, NULL, 0);
            strcpy(Chat, Memory);
            shmdt(Memory);
            semop(idSem, &Read_Ulock, 1);
            Last_Update = time(NULL);
        }
        Chat_Len = strlen(Chat);
        //!try read
    }

    //print messages
    Out_Str_Window(Tab->Messages, 0, 0, Chat);
    //! print messages

    #ifndef DEBUG
        Refresh_Tab(Tab);
    #endif // !DEBUG

    while (!Exit) {
        //type message
        wclrtoeol(Tab->Input);
        curs_set(1);
        wmove(Tab->Input, 0, 0);
        wgetnstr(Tab->Input, Message + Uname_Len, MSG_LEN - Uname_Len);
        strcat(Message, "\n");
        //!type message
        InChar = getc(stdin);
        switch (InChar)
        {
        case ESC:
            Exit = 1;
            break;
            //write new message

        case '\r':
        case '\n':
            if (semop(idSem, &Read_Lock, 1) == 0) {
                if (semop(idSem, &Write_Lock, 1) == 0) {
                    //locked
                    Memory = (char *) shmat(idShm, NULL, 0);
                    Chat_Len = strlen(Memory);
                    strncpy(Memory + Chat_Len, Message,
                            (strlen(Message) + Chat_Len > SHM_SIZE) ? 
                            SHM_SIZE - Chat_Len : strlen(Message));
                    strcpy(Chat, Memory);
                    shmdt(Memory);
                    semop(idSem, &Write_Ulock, 1);
                }
                Chat_Len = strlen(Chat);
                semop(idSem, &Read_Ulock, 1);
            }
            //!write new message
            break;

        default:
             //try read
            if (semop(idSem, &Read_Lock, 1) == 0) {
                Memory = (char *) shmat(idShm, NULL, 0);
                strcpy(Chat, Memory);
                shmdt(Memory);
                semop(idSem, &Read_Ulock, 1);
            }
            Chat_Len = strlen(Chat);
            //!try read
            break;
        }
        //print messages
        Out_Str_Window(Tab->Messages, 0, 0, Chat);
        //! print messages
        Refresh_Tab(Tab);
    }

    Delete_Tab(Tab);
    End_Window();
    free(Tab);

    exit(EXIT_SUCCESS);
}
