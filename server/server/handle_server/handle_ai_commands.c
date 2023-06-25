/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** handle_ai_commands.c
*/

#include "../../include/my.h"

cmd_ai_t *create_action_ai(this_t *this, player_t *player, char *cmd, char *arg, int duration)
{
    cmd_ai_t *new_action = malloc(sizeof(cmd_ai_t));
    new_action->cmd = malloc(sizeof(char *) * 3);
    new_action->cmd[0] = strdup(cmd);
    if (arg != NULL)
        new_action->cmd[1] = strdup(arg);
    else
        new_action->cmd[1] = NULL;
    new_action->duration = duration;
    new_action->uuid = strdup(player->id);
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
    if (player == NULL)
        return 0;
    if (player->in_team == true && player->incantation == true && player->is_gui == false) {
        if (my_strcmp(this->cmd[0], "Incantation") == 0) {
            incantation(this, player, exec);
            return 0;
        }
    }
    if (this->cmd[0] != NULL || this->cmd[1] != NULL && exec == EXECUTE)
        printf("AI: %s %s\n", this->cmd[0], this->cmd[1]);
    if (player->in_team == true && (player->incantation == false) && player->is_gui == false) {
        if (move_commands(this, player, exec) == 0)
            return 0;
        if (object_commands(this, player, exec) == 0)
            return 0;
        if (action_commands(this, player, exec) == 0)
            return 0;
        if (player_commands(this, player, exec) == 0)
            return 0;
    }
    return 1;
}
