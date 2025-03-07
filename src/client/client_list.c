/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** client
*/

#include "../../include/server.h"

static void remove_elem(client_t *parse)
{
    client_t *temp = parse->next;

    parse->next = parse->next->next;
    if (parse->cwd != NULL)
        free(parse->cwd);
    if (parse->transfer_addr != NULL)
        free(parse->transfer_addr);
    free(temp);
}

client_t *client_list_remove(client_t *list, size_t pos)
{
    client_t *parse = list;

    if (parse == NULL)
        return NULL;
    if (pos == 0)
        return list;
    for (size_t i = 0; i < pos - 1 && parse->next != NULL; i++)
        parse = parse->next;
    if (parse->next != NULL)
        remove_elem(parse);
    return list;
}

client_t *client_list_remove_fd(client_t *list, int fd)
{
    client_t *parse = list;
    client_t *temp = NULL;

    if (parse == NULL)
        return NULL;
    while (parse != NULL) {
        printf("fd : %d\n", parse->cmd_fd);
        if (parse->cmd_fd == fd) {
            remove_elem(temp);
            return list;
        }
        temp = parse;
        parse = parse->next;
    }
    return list;
}

client_t *client_list_add_end(client_t *list, client_t *client)
{
    client_t *parse = list;

    while (parse->next != NULL)
        parse = parse->next;
    client->next = NULL;
    parse->next = client;
    return list;
}

client_t *client_list_create_elem(int fd, int id, char *cwd,
    struct sockaddr_in *addr)
{
    client_t *client = (client_t *)malloc(sizeof(client_t));

    client->cmd_fd = fd;
    client->c_transfer_fd = -1;
    client->s_transfer_fd = -1;
    client->id = id;
    client->user = NULL;
    client->next = NULL;
    client->user = NULL;
    client->serv_status = INITIAL_STATUS;
    client->cwd = strdup(cwd);
    client->transfer_addr = addr;
    return client;
}
