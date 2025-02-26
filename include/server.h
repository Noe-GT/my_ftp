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
    int *sockets;
    char **available_cmds;
    char **cmds_desc;
    struct pollfd *client_fds;
    int nfds;
    bool stop_serv;
} server_t;

#endif /* !SOCKET_H_ */
