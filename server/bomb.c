#include "server.h"

int dropBomb(t_env *e, int socket)
{
    int posx;
    int posy;
    t_client *tmp;
    t_bomb *tmp_bomb;
    int nb_bomb;

    
    tmp = e->clients;
    tmp_bomb = e->bombs;
    while (e->clients != NULL)
    {
        nb_bomb = 0;
        if (e->clients->socket == socket)
        {
            posx = e->clients->pos[0];
            posy = e->clients->pos[1];

            while (e->bombs != NULL)
            {
                if (e->bombs->player_socket_id == socket)
                    ++nb_bomb;
                e->bombs = e->bombs->next;
            }
            e->bombs = tmp_bomb;

            if (nb_bomb < e->clients->bomb_num)
            {
                createBomb(e, posx, posy, socket, e->clients->bomb_range);
                e->map[posx][posy] = 'b';
            }
            e->clients = tmp;
            return (0);
        }
        e->clients = e->clients->next;

    }
    e->clients = tmp;
    return (-1);
}

void createBomb(t_env *e, int posx, int posy, int socket, int range)
{
    t_bomb *bomb;
    t_bomb *tmp;

    bomb = malloc(sizeof (t_bomb));
    gettimeofday(&bomb->now, NULL);
    bomb->posx = posx;
    bomb->posy = posy;
    bomb->next = NULL;
    bomb->range = range;
    bomb->player_socket_id = socket;

    if (e->bombs == NULL)
        e->bombs = bomb;
    else
    {
        tmp = e->bombs;
        while (e->bombs->next != NULL)
        {
            e->bombs = e->bombs->next;
        }
        e->bombs->next = bomb;
        e->bombs = tmp;
    }
}

int explodeBomb(t_env *e)
{
    struct timeval now;
    t_bomb *tmp = e->bombs;
    t_bomb *prev = NULL;

    while (e->bombs != NULL)
    {
        gettimeofday(&now, NULL);
        if (now.tv_sec - e->bombs->now.tv_sec >= 4)
        {
            if (prev != NULL)
                prev->next = e->bombs->next;
            else
                tmp = e->bombs->next;

            removeFire(e, e->bombs->posx, e->bombs->posy, e->bombs->range);

            e->map[e->bombs->posx][e->bombs->posy] = '-';
        }
        else if (now.tv_sec - e->bombs->now.tv_sec >= 3 && e->map[e->bombs->posx][e->bombs->posy] != 'B')
        {
            putFire(e, e->bombs->posx, e->bombs->posy, e->bombs->range);

            e->map[e->bombs->posx][e->bombs->posy] = 'B';
        }
        prev = e->bombs;
        e->bombs = e->bombs->next;
    }
    e->bombs = tmp;
    return 0;
}