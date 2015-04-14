#include "client.h"

int juce_XNextEventOrTimeout(Display *display, XEvent *evt, int timeout_ms)
{
    int pending = XPending(display);
    if (pending == 0)
    {
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = timeout_ms * 1000;
        int fd = XConnectionNumber(display);
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(fd, &readset);
        select(fd + 1, &readset, 0, 0, &tv);
        pending = XPending(display);
    }
    if (pending > 0)
    {
        XNextEvent(display, evt);
        return 0;
    }
    return -1;
}

int main(int argc, char ** argv)
{
    t_env e;


    e.lastUpdate = 0;

    if (argc != 3)
    {
        puts("usage : ./client <hostname> <port>");
        return -1;
    }

    init_connection(&e, argv);

    int screen_num;
    unsigned long background;
    unsigned long border;


    e.dpy = XOpenDisplay(NULL);
    if (!e.dpy)
    {
        fprintf(stderr, "unable to connect to display\n");
        exit(EXIT_FAILURE);
    }

    screen_num = DefaultScreen(e.dpy);
    background = BlackPixel(e.dpy, screen_num);
    border = WhitePixel(e.dpy, screen_num);

    e.width = 600;
    e.height = 600;

    e.win = XCreateSimpleWindow(e.dpy, DefaultRootWindow(e.dpy),
                                0, 0,
                                e.width, e.height,
                                2, border,
                                background);

    XSelectInput(e.dpy, e.win, ButtonPressMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask | KeymapStateMask);

    e.gc = XCreateGC(e.dpy, e.win, 0, &e.values);

    XSetFillStyle(e.dpy, e.gc, FillSolid);

    XMapWindow(e.dpy, e.win);

    while (1)
    {
        do_client(&e);
        if (update(&e) == -1)
        {
            XCloseDisplay(e.dpy);
            send(e.srv_sock, "quit", strlen("quit"), MSG_NOSIGNAL);
            close(e.srv_sock);
            return -1;
        }
        draw_map(&e);

        while (juce_XNextEventOrTimeout(e.dpy, &e.ev, 100) == 0)
        {
            switch (e.ev.type)
            {
            case KeyRelease:
            {
                switch (e.ev.xkey.keycode)
                {
                case 65:
                    //space
                    puts("place bomb");
                    send(e.srv_sock, "bomb", strlen("bomb"), MSG_NOSIGNAL);
                    break;
                case 9:
                    //escape
                    XCloseDisplay(e.dpy);
                    send(e.srv_sock, "quit", strlen("quit"), MSG_NOSIGNAL);
                    close(e.srv_sock);
                    return -1;
                case 111:
                    //up
                    if (up(&e) == -1)
                    {
                        XCloseDisplay(e.dpy);
                        send(e.srv_sock, "quit", strlen("quit"), MSG_NOSIGNAL);
                        close(e.srv_sock);
                        return -1;
                    }
                    puts("up");
                    break;
                case 113:
                    //left
                    if (left(&e) == -1)
                    {
                        XCloseDisplay(e.dpy);
                        send(e.srv_sock, "quit", strlen("quit"), MSG_NOSIGNAL);
                        close(e.srv_sock);
                        return -1;
                    }
                    puts("left");
                    break;
                case 116:
                    //down
                    if (down(&e) == -1)
                    {
                        XCloseDisplay(e.dpy);
                        send(e.srv_sock, "quit", strlen("quit"), MSG_NOSIGNAL);
                        close(e.srv_sock);
                        return -1;
                    }
                    puts("down");
                    break;
                case 114:
                    //right
                    if (right(&e) == -1)
                    {
                        XCloseDisplay(e.dpy);
                        send(e.srv_sock, "quit", strlen("quit"), MSG_NOSIGNAL);
                        close(e.srv_sock);
                        return -1;
                    }
                    puts("right");
                    break;
                default:
                    break;
                }
            }
            draw_map(&e);
                break;
            }
        }
        XFlush(e.dpy);
        XSync(e.dpy, False);
    }
}

