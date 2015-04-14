#include "../client.h"

int update(t_env *e)
{


    int numbytes;
    char buffer[4096];
    bzero(buffer, 4096);

    send(e->srv_sock, "update", strlen("update"), MSG_NOSIGNAL);
    usleep(1000);
    numbytes = recv(e->srv_sock, buffer, 4096, 0);
    numbytes = numbytes;
    if (strncmp(buffer, "ko", 2) == 0)
    {
        return -1;
    }
    else
        e->map = buffer;

    return 0;
}
