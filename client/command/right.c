#include "../client.h"

int right(t_env *e)
{
    char buffer[5];
    bzero(buffer, 5);

    send(e->srv_sock, "right", strlen("right"), MSG_NOSIGNAL);
    usleep(1000);
    read(e->srv_sock, buffer, 2);
    puts(buffer);
    return update(e);
}
