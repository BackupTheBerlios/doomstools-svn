NAME	=	soundtool
SRCS	=	lib$(NAME).c soundxstd.c
OBJS	=	$(SRCS:.c=.o)

CC	=	g++
CXXFLAGS=	-Wall
CFLAGS	=	$(CXXFLAGS)

$(NAME)	:	$(OBJS)
		ar r lib$(NAME).a $(OBJS)
		ranlib lib$(NAME).a
all	:	$(NAME)

clean	:	
		$(RM) $(OBJS) *~
fclean	:	clean 
		$(RM) lib$(NAME).a
re	:	fclean all
