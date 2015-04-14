#include "server.h"

void           init_map(t_env* e)
{
    char        **map;
    
    char buffer[4096];
    int fd = open("map", O_RDONLY);
    
    read(fd, &buffer, 4096);
    
    size_t width;
    size_t cpt;
    int i;
    
    width = 0;
    cpt = 0;
    for (i = 0; buffer[i] != '\0'; ++i)
    {
        if (buffer[i] == '\n')
            ++cpt;
    }
    
    map = malloc(cpt * sizeof(*map));
    char *token;
    token = strtok(buffer, "\n");
    
    i = 0;
    while( token != NULL ) 
    {
        map[i] = malloc(strlen(token) * sizeof(map));
        
        if (width < strlen(token))
                width = strlen(token);
        memcpy(map[i], token, strlen(token));
        map[i][strlen(token)] = '\0';

        ++i;
        token = strtok(NULL, "\n");
    }
    e->map = map;
    
    size_t* map_size;
    map_size = malloc(2*sizeof(e->map_size));
    map_size[0] = cpt;
    map_size[1] = width;
    e->map_size = map_size;
    
    
}

void		init_env(t_env *e)
{
  int		i;
  struct rlimit	rlp;

  e->clients = NULL;
  e->bombs = NULL;
  getrlimit(RLIMIT_NOFILE, &rlp);
  e->maxfd = rlp.rlim_cur;
  e->fds = malloc(sizeof(*e->fds) * e->maxfd);
  i = 0;
  while (i < e->maxfd)
    {
      clean_fd(&e->fds[i]);
      i++;
    }
  init_map(e);
}


