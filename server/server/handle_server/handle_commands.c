/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** handle_commands.c
*/

#include "../../include/my.h"

void exec_actions(this_t *this)
{
    list_cmd_ai_t *tmp = this->actions;
    for (int i = 0; tmp != NULL; tmp = tmp->next, i += 1) {
        if (tmp->action->duration <= 0) {
            this->cmd[0] = strdup(tmp->action->cmd[0]);
            if (tmp->action->cmd[1] != NULL)
                this->cmd[1] = strdup(tmp->action->cmd[1]);
            else
                this->cmd[1] = NULL;
            exec_ai_commands(this, get_player_by_uuid(this, tmp->action->uuid), EXECUTE);
            this->actions = free_element_at_ai(this->actions, i);
            tmp = this->actions;
            return;
        }
        tmp->action->duration -= 1;
    }
    free(tmp);
}

void commands(this_t *this, player_t *player)
{
    if (this->cmd == NULL) {
        dprintf(player->socket, "ko\n");
        return;
    } else if (get_ai_commands(this, player) == 0)
        return;
    else if (exec_gui_commands(this, player) == 0)
        return;
    dprintf(player->socket, "ko\n");
}
