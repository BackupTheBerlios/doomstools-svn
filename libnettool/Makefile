NAME	=	nettool
SRCS	=	lib$(NAME).c check_select.c check_sockets.c\
		close_connection.c free_net.c init_client.c\
		init_msg.c init_nettool.c list.c loss_client.c\
		move_last_client.c msg_wait.c new_client.c\
		recv.c send.c init_connection.c authorize_client.c\
		assign.c netxstd.c old.c nettool_quit.c insert_client.c\
		delete_client.c create_client.c call_handler.c\
		set_data_client.c close_socket.c is_quitting.c\
		no_more.c
OBJS	=	$(SRCS:.c=.o)

CC	=	gcc
CFLAGS	=	-Wall -g3 `sdl-config --cflags`

$(NAME)	:	$(OBJS)
		ar r lib$(NAME).a $(OBJS)
		ranlib lib$(NAME).a
all	:	$(NAME)

clean	:	
		$(RM) $(OBJS) *~
fclean	:	clean 
		$(RM) lib$(NAME).a
re	:	fclean all
