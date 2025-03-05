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
		src/manage_client.c \
		src/commands/noop_cmd.c \
		src/commands/user_cmd.c \
		src/commands/pass_cmd.c \
		src/commands/quit_cmd.c \
		src/commands/help_cmd.c \
		src/commands/pwd_cmd.c \
		src/commands/pasv_cmd.c \
		src/commands/list_cmd.c \
		src/commands/cwd_cmd.c \
		src/modes.c \
		src/errors.c \
		src/server_utils.c \
		src/client/clients.c \
		src/client/clients2.c \
		src/system_utils.c \

OBJ	=	$(SRC:src/%.c=bin/%.o)

CFLAGS	=	-g3 -W -Wall

EXEC	=	myftp

all:	compile_libs	$(EXEC)

compile_libs:
	make -C lib/my

$(EXEC):	$(OBJ)
	$(CC) -o $(EXEC) $(OBJ) -L. -lmy $(CFLAGS)

bin/%.o:	src/%.c
	@mkdir -p bin
	@mkdir -p bin/commands
	@mkdir -p bin/client
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)
	@rm -rf bin
	make clean -C lib/my

fclean:	clean
	rm -f $(EXEC)
	make fclean -C lib/my

re:	fclean all

.PHONY:	all compile_libs clean fclean re
