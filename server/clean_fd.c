#include "server.h"

void	clean_fd(t_fd *fd)
{
  fd->type = FD_FREE;
  fd->fct_read = NULL;
  fd->fct_write = NULL;
  fd->buf_read[0] = '\0';
  fd->buf_write[0] = '\0';
}
