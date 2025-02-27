/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** server
*/

#include "../include/ftp.h"

static void close_client_socks(server_t *server)
{
    for (int i = 0; i < server->nfds; i++) {
        if (server->client_fds[i].fd >= 0)
            close(server->client_fds[i].fd);
    }
}

static int new_client(server_t *server)
{
    int new_fd;

    new_fd = accept(server->msock_fd, NULL, NULL);
    if (new_fd < 0) {
        if (errno != EWOULDBLOCK) {
            perror("ERROR: accept failed");
            server->stop_serv = true;
        }
        return 1;
    }
    printf("New client connection (%d)\n", new_fd);
    server->clients = client_list_add_end(server->clients,
        new_fd, server->nfds + 1);
    server->client_fds = add_fd_to_array(server->client_fds,
        new_fd, server->nfds);
    server->nfds++;
    send_buff(new_fd, "220 Service ready for new user.\n");
    return 0;
}

static int parse_clients(server_t *server)
{
    int clientn = server->nfds;

    for (int i = 0; i < clientn; i++) {
        if (server->client_fds[i].revents == 0)
            continue;
        if (server->client_fds[i].revents != POLLIN) {
            printf("Error: client %d - bad revents (%d)\n", i,
                server->client_fds[i].revents);
            server->stop_serv = true;
            return -1;
        }
        if (server->client_fds[i].fd == server->msock_fd) {
            new_client(server);
        } else {
            manage_client(server, i);
        }
    }
    return 0;
}

static int loop(server_t *server)
{
    do {
        if (poll(server->client_fds, server->nfds, -1) < 0) {
            perror("ERROR: poll failed");
            return -1;
        }
        parse_clients(server);
    } while (server->stop_serv == false);
    return 0;
}

int run_server(server_t *server)
{
    int out = 0;

    if (listen(server->msock_fd, 200) < 0) {
        perror("ERROR: listen failed");
        return -1;
    }
    out = loop(server);
    close_client_socks(server);
    return out;
}
