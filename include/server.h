/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** socket
*/

#ifndef SOCKET_H_
    #define SOCKET_H_

typedef struct server_s {
    struct sockaddr_in *msock_addr;
    int msock_fd;
    socklen_t msock_addrlen;
} server_t;

#endif /* !SOCKET_H_ */
