/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** init
*/

#include "../include/ftp.h"

void init(server_t *server, int port)
{
    struct sockaddr_in *addr;

    server->available_cmds = (char **)malloc(sizeof(char *) * 3);
    server->cmds_desc = (char **)malloc(sizeof(char *) * 3);
    server->available_cmds[0] = strdup("HELP");
    server->available_cmds[1] = strdup("QUIT");
    server->available_cmds[2] = NULL;
    server->cmds_desc[0] = strdup("HELP [<SP> <string>] <CRLF> :"
        "List available commands");
    server->cmds_desc[1] = strdup("QUIT <CRLF> : Disconnection");
    server->cmds_desc[2] = NULL;
    addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(port);
    server->msock_addrlen = sizeof(*addr);
    server->msock_addr = addr;
    server->msock_fd = create_socket(addr, sizeof(*addr));
}
