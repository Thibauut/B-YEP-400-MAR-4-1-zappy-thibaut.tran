/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** handle_cmd.c
*/

#include "../../include/my.h"

cmd_ai_t *create_action(this_t *this, player_t *player, char *cmd, float duration)
{
    cmd_ai_t *new_action = malloc(sizeof(cmd_ai_t));
    new_action->cmd = strdup(cmd);
    new_action->duration = duration / this->freq;
    new_action->uuid = player->id;
    return (new_action);
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
    } else if (get_ai_commands(this, player) == 0)
        return;
    else if (exec_gui_commands(this, player) == 0)
        return;
    dprintf(player->socket, "ko\n");
}
