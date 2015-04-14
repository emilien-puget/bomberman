#include "server.h"

void			srv_create(t_env *e, int port)
{
  int			s;
  struct sockaddr_in	sin;
  struct protoent	*pe;

  pe = (struct protoent*)getprotobyname("tcp");
  s = socket(PF_INET,SOCK_STREAM, pe->p_proto);
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(port);
  
  if (bind(s, (struct sockaddr*)&sin,sizeof(sin)) == -1) 
   {
      perror("bind");
      exit(-1);
   }
  if (listen(s, 42) == -1) 
   {
      perror("listen");
      exit(-1);
   }
  
  e->so_serv = s;
  e->fds[s].type = FD_SERV;
  //e->fds[s].fct_read = srv_accept;
}
