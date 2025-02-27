/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** socket
*/

#ifndef SOCKET_H_
    #define SOCKET_H_
    #include "include.h"

typedef enum serv_status_e {
    NEEDUSER,
    NEEDPASS,
    PASSIVE,
    ACTIVE
} serv_status_t;

typedef struct client_s {
    int fd;
    int id;
    char *user;
    struct client_s *next;
    serv_status_t serv_status;
} client_t;

typedef struct server_s {
    bool stop_serv;
    struct sockaddr_in *msock_addr;
    int msock_fd;
    socklen_t msock_addrlen;
    int *sockets;
    char **available_cmds;
    char **cmds_desc;
    struct pollfd *client_fds;
    int nfds;
    client_t *clients;
} server_t;

client_t *client_list_create(void);
client_t *client_list_add_end(client_t *list, int fd, int id);
size_t client_list_display(client_t *list);
client_t *client_list_get_fd(client_t *list, int fd);
client_t *client_list_remove(client_t *list, size_t pos);
client_t *client_list_remove_fd(client_t *list, int fd);
void client_list_destroy(client_t *clients);
int quit_cmd(server_t *server, int client_i);
int help_cmd(server_t *server, int client_i, char **tokens, int tks_len);
int noop_cmd(int client_fd);
int pass_cmd(server_t *server, char **tokens);
int user_cmd(server_t *server, char **tokens);
int manage_client(server_t *server, int client_i);
int send_buff(int client_fd, char *buffer);
struct pollfd *add_fd_to_array(struct pollfd *array, int new_fd, int a_size);
struct pollfd *remove_fd_from_array(struct pollfd *array,
    int elemi, int arr_s);
#endif /* !SOCKET_H_ */
