#include "server.h"

int move_player(t_env *e, int socket, int x, int y)
{
    int posx;
    int posy;
    t_client *tmp;

    tmp = e->clients;
    while (e->clients != NULL)
    {
        if (e->clients->socket == socket)
        {
            posx = e->clients->pos[0];
            posy = e->clients->pos[1];

            if (posx + x >= 0 && posy + y >= 0 && posx + x < (int) e->map_size[0] && posy + y < (int) e->map_size[1] && e->map[posx + x][posy + y] != 'B' && e->map[posx + x][posy + y] != 'b' && e->map[posx + x][posy + y] != 'x' && e->map[posx + x][posy + y] != 'w')
            {
                if (e->map[posx + x][posy + y] == 'f' || e->map[posx + x][posy + y] == 'F')
                {
                    kill_player(e, socket);
                    return (-1);
                }
                else
                {
                    if (e->map[posx +x][posy + y] == 'g')
                        e->clients->bomb_num += 1;
                    else if (e->map[posx + x][posy + y] == 'h')
                        e->clients->bomb_range += 1;
                    else if (e->map[posx + x][posy + y] == 'y' && e->clients->bomb_num > 1)
                        e->clients->bomb_num -= 1;
                    else if (e->map[posx + x][posy + y] == 'u' && e->clients->bomb_range > 1)
                        e->clients->bomb_range -= 1;
                        
                    if (e->map[posx][posy] != 'b')
                        e->map[posx][posy] = '-';
                    e->map[posx + x][posy + y] = socket + '0' - 4;
                    e->clients->pos[0] = posx + x;
                    e->clients->pos[1] = posy + y;
                    e->clients = tmp;
                    return (0);
                }
            }
            e->clients = tmp;
            return -1;
        }
        e->clients = e->clients->next;

    }

    e->clients = tmp;
    return (-1);
}