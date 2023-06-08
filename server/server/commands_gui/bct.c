/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** bct.c
*/

#include "../../include/my.h"

void bct(this_t *this, player_t *player)
{
    if (this->cmd[1] == NULL || this->cmd[2] == NULL) {
        dprintf(player->socket, "ko\n");
        return;
    }
    if ((atoi(this->cmd[1]) - 1) < 0 || (atoi(this->cmd[1]) - 1) >= this->width || (atoi(this->cmd[2]) - 1) < 0 || (atoi(this->cmd[2]) - 1) >= this->height) {
        dprintf(player->socket, "ko\n");
        return;
    }
    dprintf(player->socket,
    "{\n\t\"x\": %d,\n\t\"y\": %d,\n\t\"food\": %d,\n\t\"linemate\": %d,\n\t\"deraumere\": %d,\n\t\"sibur\": %d,\n\t\"mendiane\": %d,\n\t\"phiras\": %d,\n\t\"thystame\": %d\n}\n", atoi(this->cmd[1]), atoi(this->cmd[2]),
    this->map->map[atoi(this->cmd[2])][atoi(this->cmd[1])].food,
    this->map->map[atoi(this->cmd[2])][atoi(this->cmd[1])].linemate,
    this->map->map[atoi(this->cmd[2])][atoi(this->cmd[1])].deraumere,
    this->map->map[atoi(this->cmd[2])][atoi(this->cmd[1])].sibur,
    this->map->map[atoi(this->cmd[2])][atoi(this->cmd[1])].mendiane,
    this->map->map[atoi(this->cmd[2])][atoi(this->cmd[1])].phiras,
    this->map->map[atoi(this->cmd[2])][atoi(this->cmd[1])].thystame);
}

