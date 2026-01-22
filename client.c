#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
// #include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int    g_ack;

void    ack_handler(int sig)
{
    (void)sig;
    g_ack = 1;
}

void    send_bits(int pid, char c)
{
    int     i;

    i = 7;
    while(i >= 0)
    {
        g_ack = 0;
        if (((c >> i) & 1) == 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        i--;
        while (g_ack == 0)
            pause();
    }
}

void    send_message(int pid, char *message)
{
    int     i;
    if (!message)
        return ;
    i = 0;
    while (message[i])
    {
        send_bits(pid, message[i]);
        write(1,&message[i],1);
        i++;
    }
    if (message[i] == '\0')
        send_bits(pid, '\0');
    // kill(pid, SIGSTOP);

}

int main(int argc, char **argv)
{
    if (argc < 3)
        return (0);
    int pid =atoi(argv[1]);
    write(1,"y\n",2);
    if (kill(pid, 0) == -1)
        return (-1);
    write(1,"y\n",2);
    signal(SIGUSR1, ack_handler);
    send_message(pid, argv[2]);
    return (0);
}