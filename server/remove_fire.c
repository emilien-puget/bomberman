#include "server.h"

int removeFirex(t_env *e, int currentposx, int currentposy)
{
    int rand1;
    int rand2;

    if (currentposx >= 0 && currentposx < (int) e->map_size[0] && currentposy >= 0 && currentposy < (int) e->map_size[1] && (e->map[currentposx][currentposy] == 'f' || e->map[currentposx][currentposy] == 'F'))
    {

        if (e->map[currentposx][currentposy] == 'F')
        {
            rand1 = rand() % 5;
            if (rand1 == 0)
            {
                rand2 = rand() % 4;
                if (rand2 == 0)
                    e->map[currentposx][currentposy] = 'g';
                else if (rand2 == 1)
                    e->map[currentposx][currentposy] = 'h';
                else if (rand2 == 2)
                    e->map[currentposx][currentposy] = 'y';
                else if (rand2 == 3)
                    e->map[currentposx][currentposy] = 'u';
            }
            else
                e->map[currentposx][currentposy] = '-';
        }
        else
            e->map[currentposx][currentposy] = '-';
        return 0;
    }
    return -1;
}

void removeFireUp(t_env *e, int posx, int posy, int nb)
{
    int current;

    current = 1;
    while (current <= nb)
    {
        if (removeFirex(e, posx - current, posy) == -1)
            return;
        ++current;
    }
}

void removeFireDown(t_env *e, int posx, int posy, int nb)
{
    int current;

    current = 1;
    while (current <= nb)
    {
        if (removeFirex(e, posx + current, posy) == -1)
            return;
        ++current;
    }
}

void removeFireLeft(t_env *e, int posx, int posy, int nb)
{
    int current;

    current = 1;
    while (current <= nb)
    {
        if (removeFirex(e, posx, posy - current) == -1)
            return;
        ++current;
    }

}

void removeFireRight(t_env *e, int posx, int posy, int nb)
{
    int current;

    current = 1;
    while (current <= nb)
    {
        if (removeFirex(e, posx, posy + current) == -1)
            return;
        ++current;
    }
}

void removeFire(t_env *e, int posx, int posy, int range)
{
    removeFireUp(e, posx, posy, range);

    removeFireDown(e, posx, posy, range);

    removeFireLeft(e, posx, posy, range);

    removeFireRight(e, posx, posy, range);
}
