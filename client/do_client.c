#include "client.h"

void do_read(t_env *e)
{
    char buff[500];
    int len;

    memset(buff, '\0', strlen(buff));
    len = read(e->srv_sock, buff, 500);
    if (len == -1)
    {
        write(2, "Read has failed\n", 17);
        close(e->srv_sock);
        exit(1);
    }
    buff[len] = '\0';
    write(1, buff, strlen(buff));
}

int do_client(t_env *e)
{
    fd_set fd_read;
    //char buffer[4096];
    //ddddint numbytes;
    struct timeval  tv;
    
    tv.tv_sec = 0;
    tv.tv_usec = 25000;


    FD_ZERO(&fd_read);
    FD_SET(e->srv_sock, &fd_read);
    FD_SET(0, &fd_read);
    if (select(e->srv_sock + 1, &fd_read, NULL, NULL, &tv) == -1)
    {
        write(2, "Select has failed\n", 19);
        close(e->srv_sock);
        exit(1);
    }

    if (FD_ISSET(e->srv_sock, &fd_read))
    {
        //do_read(e);
        /*
        if ((numbytes = recv(e->srv_sock, buffer, 4096, 0)) <= 0)
        {
            buffer[numbytes] = '\0';
            printf("Received from server %s\n", buffer);
        }*/
    }
    return 0;
}
