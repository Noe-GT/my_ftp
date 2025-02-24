/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** server
*/

#include "../include/ftp.h"

int run_server(server_t *server)
{
    int client_sock;
    int stop = 0;

    if (listen(server->msock_fd, 3) < 0) {
        perror("ERROR : listen failed");
        return 84;
    }
    client_sock = accept(server->msock_fd,
        (struct sockaddr*)server->msock_addr, &server->msock_addrlen);
    if (client_sock == -1) {
        perror("ERROR : accept failed");
    } else
        printf("Connection from %s\n",
            inet_ntoa(server->msock_addr->sin_addr));
    while (stop == 0) {
        stop = read_from_socket(server, client_sock);
    }
    return 0;
}
