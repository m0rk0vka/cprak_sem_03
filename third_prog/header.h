#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define PERMS    0666        /* права доступа */
#define N_Seller   10        /* количество отделов */
#define N_Customer 10        /* количетво посетителей*/

typedef struct
{
    int cnt; // количество в очереди
    int list [N_Seller]; // список покупок
} customer_t;