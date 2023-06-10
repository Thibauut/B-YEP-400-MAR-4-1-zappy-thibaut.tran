/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** linked_list_utils.c
*/

#include "../include/my.h"

list_players_t *create_cell(player_t *player)
{
    list_players_t *cell = malloc(sizeof(list_players_t));
    if (cell == NULL)
        return (NULL);
    cell->player = malloc(sizeof(player_t));
    cell->player->id = player->id;
    cell->player->in_team = player->in_team;
    cell->player->socket = player->socket;
    cell->player->team = player->team;
    cell->player->is_gui = player->is_gui;
    cell->player->incentation = player->incentation;
    cell->player->x = player->x;
    cell->player->y = player->y;
    cell->player->o = player->o;
    cell->next = NULL;
    return (cell);
}

list_players_t *add_element(list_players_t *list, player_t *player, int pos)
{
    list_players_t *prev = list;
    list_players_t *curr = list;
    list_players_t *cell = create_cell(player);
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

list_players_t *free_first_element(list_players_t *list)
{
    if (list == NULL)
        return (NULL);
    list_players_t *tmp = list;
    list = tmp->next;
    return (list);
}

list_players_t *free_element_at(list_players_t *list, int pos)
{
    list_players_t *prev = list;
    list_players_t *curr = list;
    if (list == NULL)
        return (NULL);
    if (pos == 0) {
        list = free_first_element(list);
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
