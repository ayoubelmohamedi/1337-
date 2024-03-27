
#include "minitalk.h"

// #include <stdio.h>
// #include <signal.h>
// #include<unistd.h>

void signal_handler(int signbr)
{
    printf("Received signal %d\n", signbr);
}

int  main()
{
    int pid = getpid();
    printf("pid : %d\n",pid);
    printf("waiting...\n");
    if (signal(SIGUSR1, signal_handler) == SIG_ERR)
    {
        perror("signal");
    }
    pause();

    printf("finished\n");
    // sleep(3);
    return (0);
}