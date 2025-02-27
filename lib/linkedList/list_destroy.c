/*
** EPITECH PROJECT, 2025
** linked_list_t
** File description:
** list_destroy
*/

#include "linked_list.h"

void list_destroy(linked_list_t *list)
{
    linked_list_t *parse = list;
    linked_list_t *temp = NULL;

    while (parse != NULL) {
        temp = parse;
        parse = parse->next;
        free(temp->data);
        free(temp);
    }
}
