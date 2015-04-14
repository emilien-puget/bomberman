#include "client.h"

void draw_map(t_env *e)
{
    char *color_names[9] = {
        "black",
        "brown",
        "red",
        "green",
        "yellow",
        "blue",
        "magenta",
        "cyan",
        "white"
    };

    int i;
    int x;
    int y;
    int cpt_color;

    int widthElem;
    int heightElem;

    XColor x_colors[9];
    Colormap screen_colormap = DefaultColormap(e->dpy, DefaultScreen(e->dpy));

    for (cpt_color = 0; cpt_color != 9; cpt_color++)
    {
        if (!XAllocNamedColor(e->dpy, screen_colormap, color_names[cpt_color], &x_colors[cpt_color], &x_colors[cpt_color]))
        {
            fprintf(stderr, "cant't alloc color %s\n", color_names[cpt_color]);
            exit(1);
        }
    }


    widthElem = e->width / (e->map_size[1]);
    heightElem = e->height / (e->map_size[0]);

    x = 0;
    i = 0;
    y = 0;
    for (i = 0; e->map[i] != '\0'; ++i)
    {
        XSetForeground(e->dpy, e->gc, x_colors[2].pixel);
        if (e->map[i] == 'x')
        {
            XSetForeground(e->dpy, e->gc, x_colors[2].pixel);
            XFillRectangle(e->dpy, e->win, e->gc, x*widthElem, y*heightElem, widthElem, heightElem);
        }
        else if (e->map[i] == 'g' || e->map[i] == 'h')
        {
            XSetForeground(e->dpy, e->gc, x_colors[6].pixel);
            XFillRectangle(e->dpy, e->win, e->gc, x*widthElem, y*heightElem, widthElem, heightElem);
        }
        else if (e->map[i] == 'y' || e->map[i] == 'u')
        {
            XSetForeground(e->dpy, e->gc, x_colors[8].pixel);
            XFillRectangle(e->dpy, e->win, e->gc, x*widthElem, y*heightElem, widthElem, heightElem);
        }
        else if (e->map[i] == 'b' || e->map[i] == 'B')
        {
            XSetForeground(e->dpy, e->gc, x_colors[1].pixel);
            XFillRectangle(e->dpy, e->win, e->gc, x*widthElem, y*heightElem, widthElem, heightElem);
        }
        else if (e->map[i] == 'f' || e->map[i] == 'F')
        {
            XSetForeground(e->dpy, e->gc, x_colors[4].pixel);
            XFillRectangle(e->dpy, e->win, e->gc, x*widthElem, y*heightElem, widthElem, heightElem);
        }
        else if (e->map[i] == 'w')
        {
            XSetForeground(e->dpy, e->gc, x_colors[3].pixel);
            XFillRectangle(e->dpy, e->win, e->gc, x*widthElem, y*heightElem, widthElem, heightElem);
        }
        else if (e->map[i] != '-')
        {
            XSetForeground(e->dpy, e->gc, x_colors[5].pixel);
            XFillRectangle(e->dpy, e->win, e->gc, x*widthElem, y*heightElem, widthElem, heightElem);
        }
        else
        {
            XSetForeground(e->dpy, e->gc, x_colors[0].pixel);
            XFillRectangle(e->dpy, e->win, e->gc, x*widthElem, y*heightElem, widthElem, heightElem);
        }
        if (e->map[i] == '\n')
        {
            x = 0;
            ++y;
        }
        else
            ++x;
    }
}
