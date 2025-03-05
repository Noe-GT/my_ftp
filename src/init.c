/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** init
*/

#include "../include/ftp.h"

static void init_users(server_t *server)
{
    user_t *usr1 = (user_t *)malloc(sizeof(user_t));

    server->n_users = 1;
    usr1->name = strdup("Anonymous");
    usr1->pass = strdup("");
    server->users = (user_t **)malloc(sizeof(user_t *) * server->n_users);
    server->users[0] = usr1;
}

static void init_cmd_desc(server_t *server)
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

int init(server_t *server, int port)
{
    struct sockaddr_in *addr = make_addr(port);

    init_cmd_desc(server);
    server->msock_addrlen = sizeof(*addr);
    server->msock_addr = addr;
    server->msock_fd = create_socket(addr, sizeof(*addr), 200);
    if (server->msock_fd == -1)
        return -1;
    server->stop_serv = false;
    server->nfds = 1;
    server->client_fds = (struct pollfd *)malloc(sizeof(struct pollfd) * 1);
    memset(server->client_fds, 0, sizeof(*server->client_fds));
    server->client_fds[0].fd = server->msock_fd;
    server->client_fds[0].events = POLLIN;
    server->clients = client_list_create();
    init_users(server);
    return 0;
}
