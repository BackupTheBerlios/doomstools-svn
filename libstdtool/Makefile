NAME	=	stdtool
SRCS	=	lib$(NAME).c
OBJS	=	$(SRCS:.c=.o)
CC	=	gcc
CXXFLAGS=	-Wall

$(NAME)	:	$(OBJS)
		ar r lib$(NAME).a $(OBJS)
		ranlib lib$(NAME).a
all	:	$(NAME)

clean	:	
		$(RM) $(OBJS) *~
fclean	:	clean 
		$(RM) lib$(NAME).a
re	:	fclean all
