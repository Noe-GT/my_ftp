/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** ftp
*/

#ifndef FTP_H_
    #define FTP_H_
    #include "server.h"
    #include "my.h"

void init(server_t *server, int port);
void free_all(server_t *server);
int create_socket(struct sockaddr_in *addr, socklen_t addrlen);
int run_server(server_t *server);
#endif /* !FTP_H_ */
