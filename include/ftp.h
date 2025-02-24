/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** ftp
*/

#ifndef FTP_H_
    #define FTP_H_
    #include "include.h"
    #include "server.h"
    #include "my.h"

void init(server_t *server, int port);
int send_buff(int client_fd, char *buffer);
int read_from_socket(server_t *server, int client_fd);
int quit_cmd(server_t *server, int client_fd);
int help_cmd(server_t *server, int client_fd, char **tokens, int tks_len);
void free_all(server_t *server);
int create_socket(struct sockaddr_in *addr, socklen_t addrlen);
int run_server(server_t *server);

#endif /* !FTP_H_ */
