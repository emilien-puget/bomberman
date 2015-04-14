NAME	=   server

SRCS	=   main.c    \
	    init_env.c	\
	    srv_create.c    \
	    clean_fd.c	    \
	    main_loop.c	    \
	    my_send.c	    \
	    receive.c	    \
	    bomb.c	    \
	    put_fire.c	    \
	    remove_fire.c   \
	    process_command.c	\
	    join_strings.c  \
	    kill_player.c  \
	    move_player.c

OBJS	= $(SRCS:.c=.o)

CC	= gcc

CFLAGS	= -W -Wall -Werror -Wextra

RM	= rm -f

#############################
# Complilation Instructions #
#############################

all	: $(NAME)

$(NAME)	: $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean	:
	$(RM) *.o $(NAME)
	
fclean	: clean
	$(RM) $(NAME)

re	: fclean all