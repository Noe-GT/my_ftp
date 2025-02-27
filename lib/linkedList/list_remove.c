/*
** EPITECH PROJECT, 2025
** linked_list_t
** File description:
** list_add_end
*/

#include "linked_list.h"

static void remove_elem(linked_list_t *parse)
{
    linked_list_t *temp = parse->next;

    parse->next = parse->next->next;
    if (parse->next != NULL)
        parse->next->previous = parse;
    free(temp->data);
    free(temp);
}

static linked_list_t *remove_first(linked_list_t *parse)
{
    linked_list_t *temp = parse->next;

    if (temp != NULL)
        temp->previous = NULL;
    free(parse->data);
    free(parse);
    return temp;
}

linked_list_t *list_remove(linked_list_t *list, size_t pos)
{
    linked_list_t *parse = list;

    if (parse == NULL)
        return NULL;
    if (pos == 0)
        return remove_first(parse);
    for (size_t i = 0; i < pos - 1 && parse->next != NULL; i++)
        parse = parse->next;
    if (parse->next != NULL)
        remove_elem(parse);
    return list;
}
