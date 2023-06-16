/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** handle_player.c
*/

#include "../../include/my.h"

void init_inventory(player_t *player)
{
    player->inventory = malloc(sizeof(inventory_t));
    player->inventory->food = 10;
    player->inventory->linemate = 0;
    player->inventory->deraumere = 0;
    player->inventory->sibur = 0;
    player->inventory->mendiane = 0;
    player->inventory->phiras = 0;
    player->inventory->thystame = 0;
}

int add_player_to_team(this_t *this, player_t *player)
{
    list_teams_t *tmp = this->teams;
    for (; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->team->name, this->cmd[0]) == 0) {
            if (tmp->team->max_players - tmp->team->nb_players <= 0)
                return 1;
            tmp->team->nb_players += 1;
            player->team = tmp->team;
            player->level = 1;
            player->x = rand() % this->width;
            player->y = rand() % this->height;
            player->o = rand() % 4;
            player->life = 1260 / this->freq;
            player->incantation = false;
            init_inventory(player);
            dprintf(player->socket, "%d\n", tmp->team->max_players - tmp->team->nb_players);
            dprintf(player->socket, "%d %d\n", this->width, this->height);
            pnw(this, player);
            return 0;
        }
    }
    return 1;
}
