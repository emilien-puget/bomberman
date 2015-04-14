#include "server.h"

int kill_player(t_env *e, int socket)
{
    t_client *tmp;

    t_client *prev = NULL;

    tmp = e->clients;

    while (e->clients != NULL)
    {
        if (e->clients->socket == socket)
        {
            if (prev != NULL)
                prev->next = e->clients->next;
            else
                tmp = e->clients->next;

            e->map[e->clients->pos[0]][e->clients->pos[1]] = '-';
            e->clients = tmp;
            return 0;

        }
        prev = e->clients;
        e->clients = e->clients->next;
    }
    e->clients = tmp;
    return 0;
}