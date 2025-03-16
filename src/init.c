/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** init
*/

#include "../include/ftp.h"

static void init_users(server_t *server)
{
    server->n_users = 3;
    server->users = (user_t **)malloc(sizeof(user_t *) * server->n_users);
    server->users[0] = (user_t *)malloc(sizeof(user_t));
    server->users[0]->name = strdup("Anonymous");
    server->users[0]->pass = strdup("");
    server->users[1] = (user_t *)malloc(sizeof(user_t));
    server->users[1]->name = strdup("Jhon");
    server->users[1]->pass = strdup("12345678");
    server->users[2] = (user_t *)malloc(sizeof(user_t));
    server->users[2]->name = strdup("Paul");
    server->users[2]->pass = strdup("1234");
}

static void init_cmds(server_t *server)
{
    server->available_cmds = (char **)malloc(sizeof(char *) * 14);
    server->available_cmds[0] = strdup("USER");
    server->available_cmds[1] = strdup("PASS");
    server->available_cmds[2] = strdup("CWD");
    server->available_cmds[3] = strdup("CDUP");
    server->available_cmds[4] = strdup("QUIT");
    server->available_cmds[5] = strdup("DELE");
    server->available_cmds[6] = strdup("PWD");
    server->available_cmds[7] = strdup("PASV");
    server->available_cmds[8] = strdup("HELP");
    server->available_cmds[9] = strdup("NOOP");
    server->available_cmds[10] = strdup("RETR");
    server->available_cmds[11] = strdup("STOR");
    server->available_cmds[12] = strdup("LIST");
    server->available_cmds[13] = NULL;
}

static void init_cmds_desc2(server_t *server)
{
    server->cmds_desc[7] = strdup("PASV <CRLF> :"
        " Enable 'passive' mode for data transfer");
    server->cmds_desc[8] = strdup("HELP [<SP> <string>] <CRLF>"
        " : List available commands");
    server->cmds_desc[9] = strdup("NOOP <CRLF> : Do nothing");
    server->cmds_desc[10] = strdup("RETR <SP> <pathname> <CRLF> :"
        " Download file from server to client");
    server->cmds_desc[11] = strdup("STOR <SP> <pathname> <CRLF> :"
        " Upload file from client to server");
    server->cmds_desc[12] = strdup("LIST [<SP> <pathname>] <CRLF> :"
        " List files in the current working directory");
    server->cmds_desc[13] = NULL;
}

static void init_cmds_desc(server_t *server)
{
    server->cmds_desc = (char **)malloc(sizeof(char *) * 14);
    server->cmds_desc[0] = strdup("USER <SP> <username> <CRLF> : "
        "Specify user for authentication");
    server->cmds_desc[1] = strdup("PASS <SP> <password> <CRLF> : "
        "Specify password for authentication");
    server->cmds_desc[2] = strdup("CWD  <SP> <pathname> <CRLF>"
        " : Change working directory");
    server->cmds_desc[3] = strdup("CDUP <CRLF> : Change working "
        "directory to parent directory");
    server->cmds_desc[4] = strdup("QUIT <CRLF> : Disconnection");
    server->cmds_desc[5] = strdup("DELE <SP> <pathname> <CRLF> "
        ": Delete file on the server");
    server->cmds_desc[6] = strdup("PWD  <CRLF> :"
        " Print working directory");
    init_cmds_desc2(server);
}

int init(server_t *server, int port)
{
    struct sockaddr_in *addr = make_addr(port);

    init_cmds(server);
    init_cmds_desc(server);
    server->mport = port;
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
