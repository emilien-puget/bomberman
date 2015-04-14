#include "server.h"

int receive(t_env *e)
{
    int i;
    int numbytes;
    char buffer[4096];
    bzero(buffer, 4096);

    for (i = 0; i < e->maxfd; i++)
    {
        if (e->fds[i].type != FD_SERV)
        {
            if (e->fds[i].type != FD_SERV && FD_ISSET(i, &e->fd_read))
            {
                if ((numbytes = recv(i, buffer, 4096, 0)) <= 0)
                {
                    printf("Connexion lost from slot %i \n", i);
                    kill_player(e, i);
                    close(i);
                    e->fds[i].type = FD_FREE;
                }
                else
                {
                    buffer[numbytes] = '\0';

                    size_t j;
                    for (j = 0; j < strlen(buffer); ++j)
                    {
                        if (buffer[j] == 13)
                            buffer[j] = '\0';
                    }

                    process_command(e, i, buffer);
                }
            }
        }
    }
    return 0;
}