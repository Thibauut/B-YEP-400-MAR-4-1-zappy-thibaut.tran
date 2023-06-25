/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** eggs_list_utils.c
*/

#include "../include/my.h"

list_eggs_t *create_cell_egg(egg_t *egg)
{
    list_eggs_t *cell = malloc(sizeof(list_eggs_t));
    if (cell == NULL)
        return (NULL);
    cell->egg = malloc(sizeof(egg_t));
    cell->egg->socket = egg->socket;
    cell->egg->x = egg->x;
    cell->egg->y = egg->y;
    cell->egg->o = egg->o;
    cell->egg->team = egg->team;
    cell->egg->uuid_creator = egg->uuid_creator;
    cell->egg->id = egg->id;
    cell->egg->in_team = egg->in_team;
    cell->egg->incantation = egg->incantation;
    cell->egg->inventory = egg->inventory;
    cell->egg->is_gui = egg->is_gui;
    cell->egg->level = egg->level;
    cell->egg->life = egg->life;
    cell->egg->socket = egg->socket;
    cell->egg->uuid_creator = egg->uuid_creator;
    cell->next = NULL;
    return (cell);
}

list_eggs_t *add_element_egg(list_eggs_t *list, egg_t *egg, int pos)
{
    list_eggs_t *prev = list;
    list_eggs_t *curr = list;
    list_eggs_t *cell = create_cell_egg(egg);
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

list_eggs_t *free_first_element_egg(list_eggs_t *list)
{
    if (list == NULL)
        return (NULL);
    list_eggs_t *tmp = list;
    list = tmp->next;
    return (list);
}

list_eggs_t *free_element_at_egg(list_eggs_t *list, int pos)
{
    list_eggs_t *prev = list;
    list_eggs_t *curr = list;
    if (list == NULL)
        return (NULL);
    if (pos == 0) {
        list = free_first_element_egg(list);
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

int list_len_egg(list_eggs_t *list)
{
    list_eggs_t *tmp = list;
    int i = 0;
    for (; tmp != NULL; tmp = tmp->next, i += 1);
    return (i);
}

egg_t *get_element_egg(list_eggs_t *list, int pos)
{
    for (int i = 0; i < pos; i += 1)
        list = list->next;
    return (list->egg);
}

