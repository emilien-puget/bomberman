/* 
 * File:   client.h
 * Author: emilien
 *
 * Created on 12 June 2013, 14:14
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/keysymdef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <sys/time.h>

typedef struct  s_env {
    int*        map_size;
    int         srv_sock;
    char*       map;
    Display*    dpy;
    Window      win;
    XEvent      ev;
    GC          gc;
    XGCValues   values;
    time_t      lastUpdate;
    struct timeval now;
    int         width;
    int         height;
}               t_env;

int             do_client(t_env *e);
void            do_read(t_env *e);
void            init_connection(t_env *e, char** argv);
void            draw_map(t_env *e);
void            getMapInfo(t_env *e);


/*
 COMMAND
 */

int            update(t_env *e);
void            contact(t_env *e);
int            up(t_env *e);
int            down(t_env *e);
int            left(t_env *e);
int            right(t_env *e);

#endif	/* CLIENT_H */

