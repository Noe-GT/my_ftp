/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** socket
*/

#ifndef SOCKET_H_
    #define SOCKET_H_
    #include "errors.h"
    #include "shared.h"
    #include "client.h"
    #define INITIAL_STATUS NEEDUSER

typedef struct server_s {
    bool stop_serv;
    struct sockaddr_in *msock_addr;
    int msock_fd;
    int mport;
    socklen_t msock_addrlen;
    int *sockets;
    char **available_cmds;
    char **cmds_desc;
    struct pollfd *client_fds;
    int nfds;
    client_t *clients;
    user_t **users;
    int n_users;
    char *root_directory;
} server_t;

int create_socket(struct sockaddr_in *addr, socklen_t addrlen, int listen_n);
int run_server(server_t *server);
int quit_cmd(server_t *server, client_t *client);
int help_cmd(server_t *server, client_t *client, char **tokens, int n_tokens);
int noop_cmd(int client_fd);
int pass_cmd(client_t *client, char **tokens, int n_tokens);
int user_cmd(server_t *server, client_t *client, char **tokens, int n_tokens);
int pwd_cmd(client_t *client, int n_tokens);
int pasv_cmd(client_t *client, int n_tokens);
int list_cmd(server_t *server, client_t *client, char **tokens, int n_tokens);
int cwd_cmd(client_t *client, char **tokens, int n_tokens);
int cdup_cmd(client_t *client, int n_tokens);
int dele_cmd(client_t *client, char **tokens, int n_tokens);
int manage_client(server_t *server, int client_i);
int manage_commands(server_t *server, client_t *client);
int send_buff(int client_fd, char *buffer);
struct pollfd *add_fd_to_array(struct pollfd *array, int new_fd, int a_size);
struct pollfd *remove_fd_from_array(struct pollfd *array,
    int elemi, int arr_s);
struct sockaddr_in *make_addr(int port);
int passive_mode(server_t *server, client_t *client);
void free_passive(server_t *server);
bool directory_exists(const char *path);
int client_remove(server_t *server, client_t *client);
#endif /* !SOCKET_H_ */
