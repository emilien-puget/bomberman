NAME	=   client

SRCS	=   main.c		    \
	    do_client.c		    \
	    command/contact.c	    \
	    command/up.c	    \
	    command/update.c	    \
	    command/down.c	    \
	    command/left.c	    \
	    command/right.c	    \
	    init/init_connection.c  \
	    draw_map.c

OBJS	= $(SRCS:.c=.o)

CC	= gcc

CFLAGS	= -W -Wall -Werror -Wextra

RM	= rm -f

#############################
# Complilation Instructions #
#############################

all	: $(NAME)

$(NAME)	: $(OBJS)
	$(CC) -o $(NAME) $(OBJS)  -lX11

clean	:
	$(RM) *.o $(NAME)
	$(RM) command/*.o $(NAME)
	$(RM) init/*.o $(NAME)
	
fclean	: clean
	$(RM) $(NAME)

re	: fclean all