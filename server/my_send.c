#include "server.h"

int     my_send(int fd, const char* msg)
{
    ssize_t ret;
    
    ret = send(fd,msg,strlen(msg),MSG_NOSIGNAL);
    if (ret != (ssize_t)strlen(msg))
    {
        perror("send");
    }
    return 0;
}
