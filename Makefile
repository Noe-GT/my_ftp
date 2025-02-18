##
## EPITECH PROJECT, 2025
## my_ftp
## File description:
## Makefile for c
##

CC	=	gcc

SRC	=	src/main.c

OBJ	=	$(SRC:src/%.c=bin/%.o)

CFLAGS	=	-g3 -W -Wall

EXEC	=	ftp

all:	$(EXEC)

$(EXEC):	$(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(CFLAGS)

bin/%.o:	src/%.c
	@mkdir -p bin
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)
	@rm -rf bin

fclean:	clean
	rm -f $(EXEC)

re:	fclean all

.PHONY:	all clean fclean re
