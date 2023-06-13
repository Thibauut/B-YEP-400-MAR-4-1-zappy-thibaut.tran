/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** handle_ai_commands.c
*/

#include "../../include/my.h"

int get_ai_commands(this_t *this, player_t *player)
{
    this->timeout = malloc(sizeof(struct timeval));
    if ((add_player_to_team(this, player) == 0) && player->is_gui == false) {
        player->in_team = true;
        return 0;
    }

    list_cmd_ai_t *tmp = this->actions;
    printf("----------------------------------\n");
    for (; tmp; tmp = tmp->next) {
        printf("cmd: %s\n", tmp->action->cmd);
        printf("uuid: %s\n", tmp->action->uuid);
        printf("duration: %f\n", tmp->action->duration);

    }
    printf("----------------------------------\n");

    if (exec_ai_commands(this, player, 0) == 0)
        return 0;
    return 1;
}

int exec_ai_commands(this_t *this, player_t *player, int exec)
{
    if (player->in_team == true && player->is_gui == false) {
        printf("cmd: %s\n", this->cmd[0]);
        if (move_commands(this, player, exec) == 0)
            return 0;
        if (action_commands(this, player, exec) == 0)
            return 0;
        if (player_commands(this, player, exec) == 0)
            return 0;
    }
    return 1;
}
