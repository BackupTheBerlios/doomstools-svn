NAME	=	soundexemple

SRCS	=	$(NAME).cpp
OBJS	=	$(SRCS:.cpp=.o)

CFLAGS	=	-Wall -g3\
		-I../libsoundtool -I/usr/include/AL
CXXFLAGS=	$(CFLAGS)

LIBS	=	-L../libsoundtool/ -lsoundtool -lopenal

CC	=	g++
RM	=	rm -f

$(NAME)	:	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LIBS)
all	:	$(NAME)

clean	:
		$(RM) $(OBJS) *~
fclean	:	clean
		$(RM) $(NAME)
re	:	fclean all
