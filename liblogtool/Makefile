NAME	=	logtool
SRCS	=	lib$(NAME).cpp
OBJS	=	$(SRCS:.cpp=.o)
CC	=	g++
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
