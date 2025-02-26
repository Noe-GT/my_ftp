/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** init
*/

#include "../include/ftp.h"

void init_cmd_desc(server_t *server)
{
    server->available_cmds = (char **)malloc(sizeof(char *) * 3);
    server->cmds_desc = (char **)malloc(sizeof(char *) * 3);
    server->available_cmds[0] = strdup("HELP");
    server->available_cmds[1] = strdup("QUIT");
    server->available_cmds[2] = NULL;
    server->cmds_desc[0] = strdup("HELP [<SP> <string>] <CRLF> :"
        "List available commands");
    server->cmds_desc[1] = strdup("QUIT <CRLF> : Disconnection");
    server->cmds_desc[2] = NULL;
}

void init(server_t *server, int port)
{
    struct sockaddr_in *addr;

    init_cmd_desc(server);
    addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(port);
    server->msock_addrlen = sizeof(*addr);
    server->msock_addr = addr;
    server->msock_fd = create_socket(addr, sizeof(*addr));
    server->stop_serv = false;
    server->nfds = 1;
    server->client_fds = (struct pollfd *)malloc(sizeof(struct pollfd) * 1);
    memset(server->client_fds, 0, sizeof(*server->client_fds));
    server->client_fds[0].fd = server->msock_fd;
    server->client_fds[0].events = POLLIN;
}
