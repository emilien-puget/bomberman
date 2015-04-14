#include "../client.h"

void            getMapInfo(t_env *e)
{
    int numbytes;
    char buffer[4096];
    bzero(buffer, 4096);
    int i;
    
    i = 0;
    puts("get map info ...");
    e->map_size = malloc(2*sizeof(e->map_size));
    send(e->srv_sock, "mapinfo", strlen("mapinfo"), MSG_NOSIGNAL);

    numbytes = recv(e->srv_sock, buffer, 4096, 0);
    numbytes = numbytes;
    //e->map = (char**)buffer;
    char *token;
    token = strtok(buffer, ",");

    
    while( token != NULL ) 
    {
        puts(token);
        e->map_size[i] = atoi(token);

        token = strtok(NULL, ",");
        ++i;
    }
    ++e->map_size[0];
    //printf("%i\n", e->map_size[0]);
    //printf("%i\n", e->map_size[1]);
    //ssputs(buffer);
}

void            init_connection(t_env *e, char** argv)
{
    int         sockfd;
    struct      hostent *server;
    struct      sockaddr_in serveraddr;

    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        puts("ERROR, no such host\n");
        exit(EXIT_FAILURE);
    }
    bzero((char *) &serveraddr, sizeof (serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(atoi(argv[2]));

    if (connect(sockfd, (const struct sockaddr *) &serveraddr, sizeof (serveraddr)) < 0)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    e->srv_sock = sockfd;
    contact(e);
    getMapInfo(e);
    
    update(e);

}
