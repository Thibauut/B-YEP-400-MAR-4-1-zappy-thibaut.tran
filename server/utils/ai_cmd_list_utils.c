/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** ai_cmd_list_utils.c
*/

#include "../include/my.h"

list_cmd_ai_t *create_cell_ai(cmd_ai_t *cmd)
{
    list_cmd_ai_t *cell = malloc(sizeof(list_cmd_ai_t));
    if (cell == NULL)
        return (NULL);
    cell->action = malloc(sizeof(cmd_ai_t));
    cell->action->cmd = cmd->cmd;
    cell->action->time_exec = cmd->time_exec;
    cell->action->start_time = cmd->start_time;
    cell->action->uuid = cmd->uuid;
    cell->next = NULL;
    return (cell);
}

list_cmd_ai_t *add_element_ai(list_cmd_ai_t *list, cmd_ai_t *cmd, int pos)
{
    list_cmd_ai_t *prev = list;
    list_cmd_ai_t *curr = list;
    list_cmd_ai_t *cell = create_cell_ai(cmd);
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

list_cmd_ai_t *free_first_element_ai(list_cmd_ai_t *list)
{
    if (list == NULL)
        return (NULL);
    list_cmd_ai_t *tmp = list;
    list = tmp->next;
    return (list);
}

list_cmd_ai_t *free_element_at_ai(list_cmd_ai_t *list, int pos)
{
    list_cmd_ai_t *prev = list;
    list_cmd_ai_t *curr = list;
    if (list == NULL)
        return (NULL);
    if (pos == 0) {
        list = free_first_element_ai(list);
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

int list_len_ai(list_cmd_ai_t *list)
{
    list_cmd_ai_t *tmp = list;
    int i = 0;
    for (; tmp != NULL; tmp = tmp->next, i += 1);
    return (i);
}
