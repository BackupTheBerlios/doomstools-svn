NAME	=	netexemple

SRCS	=	$(NAME).cpp
OBJS	=	$(SRCS:.cpp=.o)

CFLAGS	=	-Wall -g3\
		-I../libnettool
CXXFLAGS=	$(CFLAGS)

LIBS	=	-lSDL_net -L../libnettool/ -lnettool

CC	=	g++
RM	=	rm -f

$(NAME)	:	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LIBS)
all	:	$(NAME)

leaks	:	
		$(CC) -o memoryleaks memoryleaaaks.cpp $(LIBS) $(CFLAGS)
flood	:	
		$(CC) -o flood flood.cpp $(LIBS) $(CFLAGS)
clean	:
		$(RM) $(OBJS) *~
fclean	:	clean
		$(RM) $(NAME)
re	:	fclean all
