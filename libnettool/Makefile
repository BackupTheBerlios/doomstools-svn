NAME	=	nettool
SRCS	=	lib$(NAME).cpp check_select.cpp check_sockets.cpp\
		close_connection.cpp free_net.cpp init_client.cpp\
		init_msg.cpp list.cpp loss_client.cpp move_last_player.cpp\
		msg_wait.cpp new_client.cpp old.cpp recv.cpp send.cpp
OBJS	=	$(SRCS:.cpp=.o)
CC	=	g++
CXXFLAGS=	-Wall

$(NAME)	:	$(OBJS)
		$(CC) -o lib$(NAME).so -shared $(OBJS)
all	:	$(NAME)

clean	:	
		$(RM) $(OBJS) *~
fclean	:	clean 
		$(RM) lib$(NAME).a
re	:	fclean all
