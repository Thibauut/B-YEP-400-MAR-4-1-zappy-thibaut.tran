/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** mct.c
*/

#include "../../include/my.h"

void mct(this_t *this, player_t *player)
{
    if (this->cmd[1] != NULL) {
        dprintf(player->socket, "ko\n");
        return;
    }
    dprintf(player->socket, "{\n\t\"map\": [\n");
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            dprintf(player->socket,
            "\t\t{\n\t\t\t\"x\": %d,\n\t\t\t\"y\": %d,\n\t\t\t\"food\": %d,\n\t\t\t\"linemate\": %d,\n\t\t\t\"deraumere\": %d,\n\t\t\t\"sibur\": %d,\n\t\t\t\"mendiane\": %d,\n\t\t\t\"phiras\": %d,\n\t\t\t\"thystame\": %d\n\t\t}",
            x,
            y,
            this->map->map[y][x]->food,
            this->map->map[y][x]->linemate,
            this->map->map[y][x]->deraumere,
            this->map->map[y][x]->sibur,
            this->map->map[y][x]->mendiane,
            this->map->map[y][x]->phiras,
            this->map->map[y][x]->thystame);
            if (x != this->width - 1 || y != this->height - 1)
                dprintf(player->socket, ",\n");
        }
    }
    dprintf(player->socket, "\n\t]\n}\n");
}

