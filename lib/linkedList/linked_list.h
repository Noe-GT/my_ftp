/*
** EPITECH PROJECT, 2025
** linked_list_t
** File description:
** linked_list_t
*/

#ifndef LINKEDLIST_H_
    #define LINKEDLIST_H_
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>

typedef struct linked_list_t_s {
    void *data;
    int id;
    struct linked_list_t_s *next;
    struct linked_list_t_s *previous;
} linked_list_t;

linked_list_t *list_create(void *data, int id);
linked_list_t *list_add_end(linked_list_t *list, void *data, int id);
linked_list_t *list_add(linked_list_t *list, size_t pos, void *data, int id);
linked_list_t *list_remove(linked_list_t *list, size_t pos);
void list_destroy(linked_list_t *list);
size_t list_display(linked_list_t *list);
#endif /* !LINKEDLIST_H_ */
