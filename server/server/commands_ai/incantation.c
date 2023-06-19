/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** incantation.c
*/

#include "../../include/my.h"

int check_material(this_t *this, player_t *player, int elevation_ritual[7][7])
{
    if (player->inventory->linemate < elevation_ritual[player->level - 1][1] ||
    player->inventory->deraumere < elevation_ritual[player->level - 1][2] ||
    player->inventory->sibur < elevation_ritual[player->level - 1][3] ||
    player->inventory->mendiane < elevation_ritual[player->level - 1][4] ||
    player->inventory->phiras < elevation_ritual[player->level - 1][5] ||
    player->inventory->thystame < elevation_ritual[player->level - 1][6]) {
        dprintf(player->socket, "ko\n");
        return 1;
    }

    list_players_t *tmp = this->players;
    int nb_players = 0;
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->player->x == player->x && tmp->player->y == player->y && tmp->player->level == player->level)
            nb_players += 1;
    }


    return 0;
}

void incantation(this_t *this, player_t *player, int exec)
{
    if (exec == 0) {
        cmd_ai_t *action = create_action_ai(this, player, "Incantation", (300 / this->freq));
        this->actions = add_element_ai(this->actions, action, list_len_ai(this->actions));
        return;
    }
    int elevation_ritual[7][7] = {{ 1, 1, 0, 0, 0, 0, 0 }, { 2, 1, 1, 1, 0, 0, 0 }, { 2, 2, 0, 1, 0, 2, 0 }, { 4, 1, 1, 2, 0, 1, 0 },
                                { 4, 1, 2, 1, 3, 0, 0 }, { 6, 1, 2, 3, 0, 1, 0 }, { 6, 2, 2, 2, 2, 2, 1 }};
    if (check_material(this, player, elevation_ritual) == 1)
        return;

    for (int i = 0; i < 7; i++) {
        printf("values: %d\n",elevation_ritual[player->level - 1][i]);
    }

    dprintf(player->socket, "Elevation underway\n");
}