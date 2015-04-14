#include "server.h"

int process_command(t_env *e, int socket, const char* cmd)
{
    t_func_table arrayFunct[10] = {
        {"up", &up},
        {"down", &down},
        {"left", &left},
        {"right", &right},
        {"update", &update},
        {"mapinfo", &mapinfo},
        {"bomb", &bomb},
        {NULL, NULL}
    };

    size_t i = 0;

    while (arrayFunct[i].name != NULL)
    {

        if (strcmp(cmd, arrayFunct[i].name) == 0)
        {
            return arrayFunct[i].some_fun(socket, e);
        }
        ++i;
    }
    //puts("INVALID COMMAND");
    return -1;
}

int get_int_len (int value){
  int l=1;
  while(value>9){ l++; value/=10; }
  return l;
}

int mapinfo(int socket, t_env *e)
{
    char        *sizemap;
    
    char        *tmp;
    
    tmp = malloc(sizeof(char*) * get_int_len(e->map_size[1]));
    sizemap = malloc(sizeof(char*) * (get_int_len(e->map_size[0]) + get_int_len(e->map_size[1]) + 1));
    
    sprintf(sizemap, "%zu", e->map_size[0]);
    strcat(sizemap, ",");
    sprintf(tmp, "%zu", e->map_size[1]);
    strcat(sizemap, tmp);
    //puts(sizemap);
    my_send(socket, sizemap);
    return 0;
}

int bomb(int socket, t_env *e)
{
    dropBomb(e, socket);
    return 0;
}

int update(int socket, t_env *e)
{
    t_client* tmp;
    int         alive;
    
    alive = 0;
    tmp = e->clients;
    while (e->clients != NULL)
    {
        if (e->clients->socket == socket)
        {
            alive = 1;
            break;
        }
        e->clients = e->clients->next;
    }
    e->clients = tmp;
    if (alive == 0)
    {
        my_send(socket, "ko");
        return -1;
    }
    char *map = join_strings(e->map, "\n", e->map_size[0] + 1);
    //puts(map);
    my_send(socket, map);
    return 0;
}

int left(int socket, t_env *e)
{
    if (move_player(e, socket, 0, -1) == 0)
        send(socket, "OK", strlen("OK"), MSG_NOSIGNAL);
    else
        send(socket, "KO", strlen("KO"), MSG_NOSIGNAL);
    return 0;
}

int right(int socket, t_env *e)
{
    if (move_player(e, socket, 0, 1) == 0)
        send(socket, "OK", strlen("OK"), MSG_NOSIGNAL);
    else
        send(socket, "KO", strlen("KO"), MSG_NOSIGNAL);
    return 0;
}

int down(int socket, t_env *e)
{
    if (move_player(e, socket, 1, 0) == 0)
        send(socket, "OK", strlen("OK"), MSG_NOSIGNAL);
    else
        send(socket, "KO", strlen("KO"), MSG_NOSIGNAL);
    return 0;
}

int up(int socket, t_env *e)
{
    if (move_player(e, socket, -1, 0) == 0)
        send(socket, "OK", strlen("OK"), MSG_NOSIGNAL);
    else
        send(socket, "KO", strlen("KO"), MSG_NOSIGNAL);
    return 0;
}
