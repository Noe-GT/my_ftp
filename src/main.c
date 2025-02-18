/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** main
*/

#include "../include/ftp.h"

int create_socket(struct sockaddr_in *addr, socklen_t addrlen)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int br;

    if (sockfd < 0) {
        perror("socket creation failed");
        return -1;
    }
    br = bind(sockfd, (struct sockaddr*)addr, addrlen);
    if (br < 0) {
        perror("Bind failed");
        return -1;
    }
    return sockfd;
}

int run_server(server_t *server)
{
    int client_sock;

    if (listen(server->msock_fd, 3) < 0) {
        perror("ERROR : listen failed");
        return 84;
    }
    while (1) {
        client_sock = accept(server->msock_fd,
            (struct sockaddr*)server->msock_addr, &server->msock_addrlen);
        if (client_sock == -1) {
            perror("ERROR : accept failed");
        } else {
            printf("Connection from %s\n",
                inet_ntoa(server->msock_addr->sin_addr));
            close(client_sock);
        }
    }
    return 0;
}

void init(server_t *server, int port)
{
    struct sockaddr_in *addr;

    addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(port);
    server->msock_addrlen = sizeof(*addr);
    server->msock_addr = addr;
    server->msock_fd = create_socket(addr, sizeof(*addr));
}

int main(int ac, char **av)
{
    server_t *server = (server_t *)malloc(sizeof(server_t));

    if (ac != 2) {
        perror("Wrong number of arguments");
        return 1;
    }
    init(server, atoi(av[1]));
    return run_server(server);
}
