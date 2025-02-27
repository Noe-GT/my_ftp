/*
** EPITECH PROJECT, 2025
** linked_list_t
** File description:
** list_display
*/

#include "linked_list.h"

size_t list_display(linked_list_t *list)
{
    linked_list_t *parse = list;
    size_t count = 0;

    if (parse == NULL)
        printf("(nothing to display)\n");
    while (parse != NULL) {
        printf("node : %d\n", parse->id);
        count++;
        parse = parse->next;
    }
    return count;
}
