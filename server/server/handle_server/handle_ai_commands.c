/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** handle_ai_commands.c
*/

#include "../../include/my.h"

cmd_ai_t *create_action_ai(this_t *this, player_t *player, char *cmd, float duration)
{
    cmd_ai_t *new_action = malloc(sizeof(cmd_ai_t));
    new_action->cmd = strdup(cmd);
    new_action->duration = duration / this->freq;
    new_action->uuid = player->id;
    return (new_action);
}

int get_ai_commands(this_t *this, player_t *player)
{
    this->timeout = malloc(sizeof(struct timeval));
    if ((add_player_to_team(this, player) == 0) && player->is_gui == false) {
        player->in_team = true;
        return 0;
    }
    if (exec_ai_commands(this, player, ADD_TO_QUEUE) == 0)
        return 0;
    return 1;
}

int exec_ai_commands(this_t *this, player_t *player, int exec)
{
    if (player->in_team == true && player->is_gui == false) {
        if (move_commands(this, player, exec) == 0)
            return 0;
        if (action_commands(this, player, exec) == 0)
            return 0;
        if (player_commands(this, player, exec) == 0)
            return 0;
    }
    return 1;
}
