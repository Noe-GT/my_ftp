/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** clients2
*/

#include "../include/server.h"

client_t *client_list_get_fd(client_t *list, int fd)
{
    client_t *parse = list;

    while (parse != NULL) {
        if (parse->fd == fd)
            return parse;
        parse = parse->next;
    }
    return NULL;
}

static char *get_status(client_t *client)
{
    switch (client->serv_status) {
    case NEEDUSER:
        return "NEEDUSER";
    case NEEDPASS:
        return "NEEDPASS";
    case PASSIVE:
        return "PASSIVE";
    case ACTIVE:
        return "ACTIVE";
    default:
        return "NONE";
    }
}

size_t client_list_display(client_t *list)
{
    client_t *parse = list;
    size_t count = 0;

    if (parse == NULL)
        printf("(nothing to display)\n");
    while (parse != NULL) {
        printf("Client %d (fd:%d) (status:%s)\n", parse->id, parse->fd,
            get_status(parse));
        count++;
        parse = parse->next;
    }
    return count;
}
