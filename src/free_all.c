/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** free_all
*/

#include "../include/ftp.h"

void free_users(user_t **users)
{
    for (int i = 0; i < 1; i++) {
        free(users[i]->name);
        free(users[i]->pass);
        free(users[i]);
    }
    free(users);
}

void free_all(server_t *server)
{
    free_array(server->available_cmds);
    free_array(server->cmds_desc);
    free(server->msock_addr);
    client_list_destroy(server->clients);
    free_users(server->users);
}
