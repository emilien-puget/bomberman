#include "server.h"

void create_client(t_env *e, int posx, int posy, int new_fd)
{
    t_client *client;
    t_client *tmp;


    client = malloc(sizeof (t_client));
    client->socket = new_fd;
    client->pos = malloc(2 * sizeof (int*));
    client->pos[0] = posx;
    client->pos[1] = posy;
    client->next = NULL;
    client->bomb_num = 1;
    client->bomb_range = 3;

    if (e->clients == NULL)
        e->clients = client;
    else
    {
        tmp = e->clients;
        while (e->clients->next != NULL)
        {
            e->clients = e->clients->next;
        }
        e->clients->next = client;
        e->clients = tmp;
    }
}

int main_loop(t_env *e)
{
    int i;
    struct timeval tv;

    int new_fd;
    struct sockaddr_in their_addr;
    socklen_t sin_size;

    int posx;
    int posy;

    tv.tv_sec = 0;
    tv.tv_usec = 250000;
    sin_size = sizeof (struct sockaddr_in);


    while (1)
    {
        explodeBomb(e);

        FD_ZERO(&e->fd_read);

        i = 0;
        while (i < e->maxfd)
        {
            if (e->fds[i].type != FD_FREE)
            {
                FD_SET(i, &e->fd_read);
            }
            i++;
        }
        if (select(e->maxfd + 1, &e->fd_read, NULL, NULL, &tv) >= 0)
        {
            if (FD_ISSET(e->so_serv, &e->fd_read))
            {
                if ((new_fd = accept(e->so_serv, (struct sockaddr *) &their_addr, &sin_size)) == -1)
                {
                    perror("accept");
                    continue;
                }

                i = 0;
                e->fds[new_fd].type = FD_CLIENT;
                printf("Connexion received from %s (slot %i) \n", inet_ntoa(their_addr.sin_addr), new_fd);
                FD_SET(new_fd, &e->fd_read);
                my_send(new_fd, "OK");

                posx = rand() % e->map_size[0];
                posy = rand() % e->map_size[1];

                while (e->map[posx][posy] != '-')
                {
                    posx = rand() % e->map_size[0];
                    posy = rand() % e->map_size[1];
                }
                char c = new_fd + '0' - 4;

                printf("new player at %i : %i\n", posx, posy);
                if (e->map[posx][posy] == '-')
                    e->map[posx][posy] = c;


                create_client(e, posx, posy, new_fd);
            }
        }
        else
        {
            perror("select");
            return -1;
        }
        receive(e);
    }
    return 0;
}