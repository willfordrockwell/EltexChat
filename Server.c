#include "server.h"

int main(int argc, char const *argv[])
{
    int idShm;
    int idSem;

    int Returns;

    Returns = semget(ftok("./Server.elf", 1), 2, 0666 | IPC_CREAT);
    if (Returns >= 0) {
        idSem = Returns;
        printf("Semaphore with id %d was created\n", idSem);
    }
    else {
        printf("Semaphore was NOT created: %s\n", strerror(Returns));
        exit(EXIT_FAILURE);
    }

    semop(idSem, &Read_Ulock, 1);
    semop(idSem, &Write_Ulock, 1);

    Returns = shmget(ftok("./Server.elf", 2), SHM_SIZE, 0666 | IPC_CREAT);
    if (Returns >= 0) {
        idShm = Returns;
        printf("Memory with id %d was created\n", idShm);
    }
    else {
        printf("Memory was NOT created: %s\n", strerror(Returns));
        exit(EXIT_FAILURE);
    }

    char Input = '\0';

    while (Input != 'q') {
        switch (Input)
        {
        case 'u':
            semop(idSem, &Write_Ulock, 1);
            semop(idSem, &Read_Ulock, 1);
            printf("Sem's unlocked\n");
            break;
        
        default:
            break;
        }
        Input = fgetc(stdin);
    }

    Returns = shmctl(idShm, IPC_RMID, 0);
    if (Returns == 0) {
        printf("Memory with id %d was deleted\n", idShm);
    }
    else {
        printf("Memory was NOT deleted: %s\n", strerror(Returns));
        exit(EXIT_FAILURE);
    }

    Returns = semctl(idSem, 0, IPC_RMID, 0);
    if (Returns == 0) {
        printf("Semaphore with id %d was deleted\n", idSem);
    }
    else {
        printf("Semaphore was NOT deleted: %s\n", strerror(Returns));
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
