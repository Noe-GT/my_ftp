##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC	=	$(wildcard *.c)

OBJ	=	$(SRC:%.c=bin/%.o)

NAME	=	liblinkedList.a

CFLAGS	=	-g3 -W -Wall

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../..
	cp linkedList.h ../../include

bin/%.o:	%.c
	@mkdir -p bin
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)
	@rm -rf bin

fclean:	clean
	rm -f $(NAME) ../../$(NAME)

re:	fclean all

.PHONY:	all clean fclean re
