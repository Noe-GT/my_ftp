##
## EPITECH PROJECT, 2025
## my_ftp
## File description:
## Makefile for c
##

CC	=	gcc

SRC	=	src/main.c \
		src/init.c \
		src/free_all.c \
		src/server.c \
		src/read_from_socket.c \
		src/commands.c \
		src/server_utils.c \

OBJ	=	$(SRC:src/%.c=bin/%.o)

CFLAGS	=	-g3 -W -Wall

EXEC	=	myftp

all:	compile_lib	$(EXEC)

compile_lib:
	make -C lib/my

$(EXEC):	$(OBJ)
	$(CC) -o $(EXEC) $(OBJ) -L. -lmy $(CFLAGS)

bin/%.o:	src/%.c
	@mkdir -p bin
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)
	@rm -rf bin
	make clean -C lib/my

fclean:	clean
	rm -f $(EXEC)
	make fclean -C lib/my

re:	fclean all

.PHONY:	all compile_lib clean fclean re
