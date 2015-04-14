#include "../client.h"

int down(t_env *e)
{
    char buffer[4];
    bzero(buffer, 4);

    send(e->srv_sock, "down", strlen("down"), MSG_NOSIGNAL);
    usleep(1000);
    read(e->srv_sock, buffer, 2);
    puts(buffer);
    return update(e);
}
