/*
** EPITECH PROJECT, 2025
** linked_list_t
** File description:
** list_add_end
*/

#include "linked_list.h"

linked_list_t *list_add_end(linked_list_t *list, void *data, int id)
{
    linked_list_t *new_node = (linked_list_t *)malloc(sizeof(linked_list_t));
    linked_list_t *parse = list;

    new_node->data = data;
    new_node->id = id;
    new_node->next = NULL;
    while (parse->next != NULL)
        parse = parse->next;
    new_node->previous = parse;
    parse->next = new_node;
    return list;
}
