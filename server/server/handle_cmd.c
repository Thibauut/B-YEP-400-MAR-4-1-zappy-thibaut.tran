/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** handle_cmd.c
*/

#include "../include/my.h"

int exec_ai_commands(this_t *this, player_t *player)
{
    if ((add_player_to_team(this, player) == 0) && player->is_gui == false) {
        player->in_team = true;
        return 0;
    }
    if (player->in_team == true && player->is_gui == false) {
        if (move_commands(this, player) == 0)
            return 0;
        if (action_commands(this, player) == 0)
            return 0;
        if (player_commands(this, player) == 0)
            return 0;
    }
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
