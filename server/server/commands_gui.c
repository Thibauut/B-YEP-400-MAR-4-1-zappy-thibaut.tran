/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** commands_gui.c
*/

#include "../include/my.h"

int map_info_gui_commands(this_t *this, player_t *player)
{
    if (my_strcmp(this->cmd[0], "msz") == 0) {
        msz(this, player);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "bct") == 0) {
        bct(this, player);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "mct") == 0) {
        mct(this, player);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "tna") == 0) {
        tna(this, player);
        return 0;
    }
    return 1;
}

int player_info_gui_commands(this_t *this, player_t *player)
{
    if (my_strcmp(this->cmd[0], "ppo") == 0) {
        ppo(this, player);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "plv") == 0) {
        plv(this, player);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "pin") == 0) {
        pin(this, player);
        return 0;
    }
    return 1;
}

int time_info_gui_commands(this_t *this, player_t *player)
{
    if (my_strcmp(this->cmd[0], "sgt") == 0) {
        sgt(this, player);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "sst") == 0) {
        sst(this, player);
        return 0;
    }
    return 1;
}