/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** handle_cmd.c
*/

#include "../include/my.h"

cmd_ai_t *create_action(this_t *this, player_t *player, char *cmd)
{
    cmd_ai_t *new_action = malloc(sizeof(cmd_ai_t));
    new_action->cmd = strdup(cmd);
    new_action->time_exec = 126 / this->freq;
    new_action->start_time = (float)this->current_time;
    new_action->uuid = player->id;
    return (new_action);
}

int exec_ai_commands(this_t *this, player_t *player)
{
    this->timeout = malloc(sizeof(struct timeval));
    if ((add_player_to_team(this, player) == 0) && player->is_gui == false) {
        player->in_team = true;
        return 0;
    }

    this->actions = add_element_ai(this->actions, create_action(this, player, this->cmd[0]), list_len_ai(this->actions));

    // for (list_cmd_ai_t *tmp = this->actions; tmp != NULL; tmp = tmp->next) {
    //     printf("time exe: %f\n", tmp->action->time_exec);
    //     printf("time start: %f\n", tmp->action->start_time);
    //     printf("id: %s\n", tmp->action->uuid);
    //     printf("type: %s\n", tmp->action->cmd);
    // }
    // printf("\n");

    // if (player->in_team == true && player->is_gui == false) {
    //     printf("cmd: %s\n", this->cmd[0]);
    //     // if (move_commands(this, player) == 0)
    //     //     return 0;
    //     // if (action_commands(this, player) == 0)
    //     //     return 0;
    //     // if (player_commands(this, player) == 0)
    //     //     return 0;
    // }
    // return 0;
    return 1;
}

int exec_gui_commands(this_t *this, player_t *player)
{
    if (my_strcmp(this->cmd[0], "GUI") == 0 && player->in_team == false) {
        player->is_gui = true;
        return 0;
    }
    if (player->is_gui == true && player->in_team == false) {
        if (map_info_gui_commands(this, player) == 0)
            return 0;
        if (player_info_gui_commands(this, player) == 0)
            return 0;
        if (time_info_gui_commands(this, player) == 0)
            return 0;
    }
    return 1;
}

void commands(this_t *this, player_t *player)
{
    if (this->cmd == NULL) {
        dprintf(player->socket, "ko\n");
        return;
    } else if (exec_ai_commands(this, player) == 0)
        return;
    else if (exec_gui_commands(this, player) == 0)
        return;
    dprintf(player->socket, "ko\n");
}
