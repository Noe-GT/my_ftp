/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** client
*/


#ifndef CLIENT_H_
    #define CLIENT_H_
    #include "shared.h"

typedef struct client_s {
    int cmd_fd;
    int c_transfer_fd;
    int s_transfer_fd;
    int id;
    user_t *user;
    struct client_s *next;
    serv_status_t serv_status;
    char *cwd;
} client_t;

client_t *client_list_create(void);
client_t *client_list_add_end(client_t *list, int fd, int id, char *cwd);
size_t client_list_display(client_t *list);
client_t *client_list_get_fd(client_t *list, int fd);
client_t *client_list_remove(client_t *list, size_t pos);
client_t *client_list_remove_fd(client_t *list, int fd);
void client_list_destroy(client_t *clients);

#endif
