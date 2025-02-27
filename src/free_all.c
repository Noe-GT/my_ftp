/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** free_all
*/

#include "../include/ftp.h"

void free_all(server_t *server)
{
    free_array(server->available_cmds);
    free_array(server->cmds_desc);
    free(server->msock_addr);
    client_list_destroy(server->clients);
}
