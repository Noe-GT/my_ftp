/*
** EPITECH PROJECT, 2025
** linked_list_t
** File description:
** list_add_end
*/

#include "linked_list.h"

static void add_elem(linked_list_t *parse, void *data, int id)
{
    linked_list_t *new_node = (linked_list_t *)malloc(sizeof(linked_list_t));

    new_node->next = parse->next;
    new_node->previous = parse;
    new_node->data = data;
    new_node->id = id;
    parse->next = new_node;
}

static linked_list_t *add_first(linked_list_t *parse, void *data, int id)
{
    linked_list_t *new_node = (linked_list_t *)malloc(sizeof(linked_list_t));

    parse->previous = new_node;
    new_node->next = parse;
    new_node->previous = NULL;
    new_node->data = data;
    new_node->id = id;
    return new_node;
}

linked_list_t *list_add(linked_list_t *list, size_t pos, void *data, int id)
{
    linked_list_t *parse = list;

    if (list == NULL)
        return NULL;
    if (pos == 0)
        return add_first(parse, data, id);
    for (size_t i = 0; i < pos - 1 && parse != NULL; i++)
        parse = parse->next;
    if (parse != NULL)
        add_elem(parse, data, id);
    return list;
}
