/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** look_list_utils.c
*/

#include "../include/my.h"

list_vector2d_t *create_cell_vector(vector2d_t *vector)
{
    list_vector2d_t *cell = malloc(sizeof(list_vector2d_t));
    if (cell == NULL)
        return (NULL);
    cell->vector = malloc(sizeof(list_vector2d_t));
    cell->vector->x= vector->x;
    cell->vector->y = vector->y;
    cell->next = NULL;
    return (cell);
}

list_vector2d_t *add_element_vector(list_vector2d_t *list, vector2d_t *vector, int pos)
{
    list_vector2d_t *prev = list;
    list_vector2d_t *curr = list;
    list_vector2d_t *cell = create_cell_vector(vector);
    if (list == NULL)
        return (cell);
    if (pos == 0) {
        cell->next = list;
        return (cell);
    }
    for (int i = 0; i < pos; i += 1) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = cell;
    cell->next = curr;
    return (list);
}

list_vector2d_t *free_first_element_vector(list_vector2d_t *list)
{
    if (list == NULL)
        return (NULL);
    list_vector2d_t *tmp = list;
    list = tmp->next;
    return (list);
}

list_vector2d_t *free_element_at_vector(list_vector2d_t *list, int pos)
{
    list_vector2d_t *prev = list;
    list_vector2d_t *curr = list;
    if (list == NULL)
        return (NULL);
    if (pos == 0) {
        list = free_first_element_vector(list);
        return list;
    }
    for (int i = 0; i < pos; i += 1) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
    free(curr);
    return (list);
}

int list_len_vector(list_vector2d_t *list)
{
    int i = 0;
    list_vector2d_t *tmp = list;
    while (tmp != NULL) {
        tmp = tmp->next;
        i += 1;
    }
    return (i);
}
