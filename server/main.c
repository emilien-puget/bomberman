#include "server.h"

int main(int argc, char** argv)
{
    t_env e;
    int port;

    if (argc == 2)
        port = atoi(argv[1]);
    else
        port = 4242;

    init_env(&e);
    srv_create(&e, port);
    main_loop(&e);

    return 0;
}