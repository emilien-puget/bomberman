#include "../client.h"

void contact(t_env *e)
{

    // int numbytes;
    char buffer[4096];
    bzero(buffer, 4096);

    puts("connecting...");
    send(e->srv_sock, "connect johnny", strlen("connect johnny"), MSG_NOSIGNAL);
    sleep(2);
    read(e->srv_sock, buffer, 4096);
    puts(buffer);
    /*
    numbytes=recv(e->srv_sock,buffer,4096,0);
    if (strncmp(buffer, "OK", 2) != 0)
    {
        puts("something bad happened");
        exit(1);
    }
    puts(buffer);*/
}
