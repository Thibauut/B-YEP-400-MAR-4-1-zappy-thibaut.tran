/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** team_list_utils.c
*/

#include "../include/my.h"

list_teams_t *create_cell_team(team_t *team)
{
    list_teams_t *cell = malloc(sizeof(list_teams_t));
    if (cell == NULL)
        return (NULL);
    cell->team = malloc(sizeof(team_t));
    cell->team->max_players = team->max_players;
    cell->team->name = team->name;
    cell->team->nb_players = team->nb_players;
    cell->team->players_id = team->players_id;
    cell->next = NULL;
    return (cell);
}

list_teams_t *add_element_team(list_teams_t *list, team_t *team, int pos)
{
    list_teams_t *prev = list;
    list_teams_t *curr = list;
    list_teams_t *cell = create_cell_team(team);
    if (list == NULL)
        return (cell);
    if (pos == 0) {
        cell->next = list;
        return (cell);
    }
    for (int i = 0; i < pos && curr != NULL; i += 1) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = cell;
    cell->next = curr;
    return (list);
}

list_teams_t *free_first_element_team(list_teams_t *list)
{
    if (list == NULL)
        return (NULL);
    list_teams_t *tmp = list;
    list = tmp->next;
    return (list);
}

list_teams_t *free_element_at_team(list_teams_t *list, int pos)
{
    list_teams_t *prev = list;
    list_teams_t *curr = list;
    if (list == NULL)
        return (NULL);
    if (pos == 0) {
        list = free_first_element_team(list);
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

int list_len_team(list_teams_t *list)
{
    int i = 0;
    list_teams_t *tmp = list;
    while (tmp != NULL) {
        tmp = tmp->next;
        i += 1;
    }
    return (i);
}
