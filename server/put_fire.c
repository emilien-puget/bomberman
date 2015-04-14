#include "server.h"

void putFire(t_env *e, int posx, int posy, int range)
{
    putFireUp(e, posx, posy, range);

    putFireDown(e, posx, posy, range);

    putFireLeft(e, posx, posy, range);

    putFireRight(e, posx, posy, range);
}

int putFireX(t_env *e, int currentposx, int currentposy)
{
    if (currentposx >= 0 && currentposx < (int) e->map_size[0] && currentposy >= 0 && currentposy < (int) e->map_size[1] && (e->map[currentposx][currentposy] == '-' || e->map[currentposx][currentposy] == 'f' || e->map[currentposx][currentposy] == 'w' || isdigit(e->map[currentposx][currentposy])))
    {
        if (isdigit(e->map[currentposx][currentposy]))
        {
            kill_player(e, e->map[currentposx][currentposy] - '0' + 4);
        }

        if (e->map[currentposx][currentposy] != '-' && e->map[currentposx][currentposy] != 'f')
        {
            e->map[currentposx][currentposy] = 'F';
            return -1;
        }

        e->map[currentposx][currentposy] = 'f';
    }
    else
        return -1;
    return 0;
}

void putFireUp(t_env *e, int posx, int posy, int nb)
{
    int current;

    current = 1;
    while (current <= nb)
    {
        if (putFireX(e, posx - current, posy) == -1)
            return;
        ++current;
    }
}

void putFireDown(t_env *e, int posx, int posy, int nb)
{
    int current;

    current = 1;
    while (current <= nb)
    {
        if (putFireX(e, posx + current, posy) == -1)
            return;
        ++current;
    }
}

void putFireLeft(t_env *e, int posx, int posy, int nb)
{
    int current;

    current = 1;
    while (current <= nb)
    {
        if (putFireX(e, posx, posy - current) == -1)
            return;
        ++current;
    }
}

void putFireRight(t_env *e, int posx, int posy, int nb)
{
    int current;

    current = 1;
    while (current <= nb)
    {
        if (putFireX(e, posx, posy + current) == -1)
            return;
        ++current;
    }
}
