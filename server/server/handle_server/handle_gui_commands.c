/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** handle_cmd.c
*/

#include "../../include/my.h"

int exec_gui_commands(this_t *this, player_t *player)
{
    if (my_strcmp(this->cmd[0], "GUI") == 0 && player->in_team == false) {
        player->is_gui = true;
        return 0;
    }
    if (player->is_gui == true && (this->cmd[0] != NULL || this->cmd[1] != NULL))
        printf("GUI: %s %s\n", this->cmd[0], this->cmd[1]);
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
