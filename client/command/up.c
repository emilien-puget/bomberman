#include "../client.h"

int up(t_env *e)
{
    char buffer[2];
    bzero(buffer, 2);

    send(e->srv_sock, "up", strlen("up"), MSG_NOSIGNAL);
    usleep(1000);
    read(e->srv_sock, buffer, 2);
    puts(buffer);
    return update(e);
}
