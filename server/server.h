#ifndef SERVER_H
#define	SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <netdb.h>
#include <sys/resource.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/time.h>
#include <ctype.h>


#define FD_FREE	0
#define FD_SERV	1
#define FD_CLIENT	2

#define MAX(a, b)	((a > b) ? a : b)

#define BUF_SIZE	4096

typedef struct s_client {
    int bomb_range;
    int bomb_num;
    int socket;
    int *pos;
    char *name;
    struct s_client *next;
} t_client;

typedef struct s_fd {
    int type;
    void (*fct_read)();
    void (*fct_write)();
    char buf_read[BUF_SIZE + 1];
    char buf_write[BUF_SIZE + 1];
} t_fd;

typedef struct s_bomb{
    int posx;
    int posy;
    int player_socket_id;
    int range;
    struct timeval now;
    struct s_bomb *next;
} t_bomb;

typedef struct s_env {
    
    t_fd *fds;
    int port;
    int maxfd;
    int max;
    int so_serv;
    fd_set fd_read;
    fd_set fd_write;
    char **map;
    size_t *map_size;
    t_bomb      *bombs;
    t_client *clients;
} t_env;

void init_env(t_env *e);
void clean_fd(t_fd *fd);
void srv_create(t_env *e, int port);
int main_loop(t_env *e);
int my_send(int fd, const char* msg);
int receive(t_env *e);
int process_command(t_env *e, int socket, const char* cmd);
char *join_strings(char* strings[], char* seperator, int count);
int mapinfo(int socket, t_env *e);
int kill_player(t_env *e, int socket);

int move_player(t_env *e, int socket, int x, int y);
int dropBomb(t_env *e, int socket);
void createBomb(t_env *e, int posx, int posy, int socket, int range);
int explodeBomb(t_env *e);
void putFire(t_env *e, int posx, int posy, int range);

void putFireUp(t_env *e, int posx, int posy, int nb);
void putFireDown(t_env *e, int posx, int posy, int nb);
void putFireLeft(t_env *e, int posx, int posy, int nb);
void putFireRight(t_env *e, int posx, int posy, int nb);

void removeFire(t_env *e, int posx, int posy, int range);

/*
 * func ptr 
 */
typedef struct s_function_table {
    char *name;
    int (*some_fun)(int, t_env *);
} t_func_table;


int test(int socket, t_env *e);
int truc(int socket, t_env *e);
int update(int socket, t_env *e);
int up(int socket, t_env *e);
int down(int socket, t_env *e);
int left(int socket, t_env *e);
int right(int socket, t_env *e);
int bomb(int socket, t_env *e);


#endif	/* SERVER_H */

