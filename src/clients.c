/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** client
*/

#include "../include/server.h"

static void remove_elem(client_t *parse)
{
    client_t *temp = parse->next;

    parse->next = parse->next->next;
    if (temp->user != NULL)
        free(temp->user);
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
    client_t *temp = parse;

    if (parse == NULL)
        return NULL;
    while (parse != NULL) {
        if (parse->fd == fd)
            remove_elem(temp);
        temp = parse;
        parse = parse->next;
    }
    return list;
}

client_t *client_list_create(void)
{
    client_t *list = (client_t *)malloc(sizeof(client_t));

    list->next = NULL;
    list->fd = -1;
    list->id = -1;
    list->user = NULL;
    list->user = NULL;
    list->serv_status = -1;
    return list;
}

void client_list_destroy(client_t *clients)
{
    client_t *parse = clients;
    client_t *temp = NULL;

    while (parse != NULL) {
        temp = parse;
        parse = parse->next;
        if (parse->user != NULL)
            free(parse->user);
        free(temp);
    }
}

client_t *client_list_add_end(client_t *list, int fd, int id)
{
    client_t *new_node = (client_t *)malloc(sizeof(client_t));
    client_t *parse = list;

    new_node->fd = fd;
    new_node->id = id;
    new_node->user = NULL;
    new_node->next = NULL;
    new_node->user = NULL;
    new_node->serv_status = NEEDUSER;
    while (parse->next != NULL)
        parse = parse->next;
    parse->next = new_node;
    return list;
}
