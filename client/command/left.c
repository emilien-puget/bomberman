#include "../client.h"

int left(t_env *e)
{
    char buffer[4];
    bzero(buffer, 4);

    send(e->srv_sock, "left", strlen("left"), MSG_NOSIGNAL);
    usleep(1000);
    read(e->srv_sock, buffer, 2);
    puts(buffer);
    return update(e);
}
