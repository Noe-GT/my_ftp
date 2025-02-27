/*
** EPITECH PROJECT, 2025
** linked_list_t
** File description:
** list_create
*/

#include "linked_list.h"

linked_list_t *list_create(void *data, int id)
{
    linked_list_t *list = (linked_list_t *)malloc(sizeof(linked_list_t));

    list->data = data;
    list->id = id;
    list->next = NULL;
    list->previous = NULL;
    return list;
}
