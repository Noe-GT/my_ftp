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

static int add_client(server_t *server, int new_fd, struct sockaddr_in *addr)
{
    client_t *new_client = client_list_create_elem(new_fd, server->nfds + 1,
        server->root_directory, addr);

    server->clients = client_list_add_end(server->clients, new_client);
    server->client_fds = add_fd_to_array(server->client_fds,
        new_fd, server->nfds);
    server->nfds++;
}

static int new_client(server_t *server)
{
    struct sockaddr_in *addr = make_addr(server->mport);
    socklen_t addr_len = sizeof(addr);
    int new_fd = accept(server->msock_fd, (struct sockaddr*)addr, &addr_len);

    if (new_fd < 0) {
        if (errno != EWOULDBLOCK) {
            perror("ERROR: accept failed");
            server->stop_serv = true;
        }
        free(addr);
        return 1;
    }
    add_client(server, new_fd, addr);
    printf("New client connection (%d)\n", new_fd);
    send_buff(new_fd, "220 FTP Server ready.\n");
    return 0;
}

static int check_event(server_t *server, int i)
{
    if (server->client_fds[i].revents == POLLERR ||
        server->client_fds[i].revents == POLLHUP ||
        server->client_fds[i].revents == POLLNVAL) {
        printf("Error: client %d - bad revents (%d)\n", i,
            server->client_fds[i].revents);
        client_remove(server, client_list_get_fd(server->clients,
            server->client_fds[i].fd));
        return -1;
    }
    if (server->client_fds[i].revents == POLLIN) {
        if (server->client_fds[i].fd == server->msock_fd)
            new_client(server);
        else
            manage_client(server, i);
    }
    return 0;
}

static int parse_clients(server_t *server)
{
    int clientn = server->nfds;

    for (int i = 0; i < clientn && server->stop_serv == false; i++) {
        check_event(server, i);
    }
    return 0;
}

static int loop(server_t *server)
{
    int out_code = 0;

    do {
        if (poll(server->client_fds, server->nfds, -1) < 0) {
            perror("ERROR: poll failed");
            return -1;
        }
        out_code = parse_clients(server);
    } while (server->stop_serv == false);
    return out_code;
}

int run_server(server_t *server)
{
    int out = 0;

    out = loop(server);
    close_client_socks(server);
    return out;
}
