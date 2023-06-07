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
        // dprintf(player->socket, "bct %d %d %d %d %d %d %d %d %d\n", this->cmd[1], this->cmd[2], this->map[this->cmd[1]][this->cmd[2]].food, this->map[this->cmd[1]][this->cmd[2]].linemate, this->map[this->cmd[1]][this->cmd[2]].deraumere, this->map[this->cmd[1]][this->cmd[2]].sibur, this->map[this->cmd[1]][this->cmd[2]].mendiane, this->map[this->cmd[1]][this->cmd[2]].phiras, this->map[this->cmd[1]][this->cmd[2]].thystame);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "mct") == 0) {
        // dprintf(player->socket, "mct\n");
        return 0;
    }
    if (my_strcmp(this->cmd[0], "tna") == 0) {
        // dprintf(player->socket, "tna\n");
        return 0;
    }
    return 1;
}

int player_info_gui_commands(this_t *this, player_t *player)
{
    if (my_strcmp(this->cmd[0], "ppo") == 0) {
        // dprintf(player->socket, "ppo\n");
        return 0;
    }
    if (my_strcmp(this->cmd[0], "plv") == 0) {
        // dprintf(player->socket, "plv\n");
        return 0;
    }
    if (my_strcmp(this->cmd[0], "pin") == 0) {
        // dprintf(player->socket, "pin\n");
        return 0;
    }
    return 1;
}

int time_info_gui_commands(this_t *this, player_t *player)
{
    if (my_strcmp(this->cmd[0], "sgt") == 0) {
        // dprintf(player->socket, "sgt\n");
        return 0;
    }
    if (my_strcmp(this->cmd[0], "sst") == 0) {
        // dprintf(player->socket, "sst\n");
        return 0;
    }
    return 1;
}