##
## Makefile for kml-c
##

NAME	= kamoulox
SRCS	= srcs/kml.c		\
	  srcs/init.c		\
	  srcs/xml.c		\
	  srcs/end.c		\
	  srcs/kamoulox.c	\
	  srcs/error.c		\
	  srcs/utils.c
OBJS	= $(SRCS:.c=.o)

CC	= gcc
CFLAGS	= -I./includes/ `xml2-config --cflags` -W -Wall -Werror -Wstrict-prototypes -ansi -pedantic
LFLAGS  = `xml2-config --libs`
RM	= rm -f


all	: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS)
	@ echo -e "\033[1;5;35m--> $(NAME) : C o m p i l a t i o n   C o m p l e t e\033[0m"

clean	:
	$(RM) $(OBJS)
	@ echo -e "\033[0;35m--> $(NAME) : C l e a n e d\033[0m"

fclean	:
	$(RM) $(OBJS) $(NAME)
	@ echo -e "\033[0;35m--> $(NAME) : C l e a n e d\033[0m"

re	: fclean all

