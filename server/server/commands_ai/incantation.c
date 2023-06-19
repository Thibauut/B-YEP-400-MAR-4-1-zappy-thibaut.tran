/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** incantation.c
*/

#include "../../include/my.h"

int check_material(this_t *this, player_t *player, int elevation_ritual[7][7], int *nb_players)
{
    if (this->map->map[player->y][player->x].linemate < elevation_ritual[player->level - 1][1] ||
    this->map->map[player->y][player->x].deraumere < elevation_ritual[player->level - 1][2] ||
    this->map->map[player->y][player->x].sibur < elevation_ritual[player->level - 1][3] ||
    this->map->map[player->y][player->x].mendiane < elevation_ritual[player->level - 1][4] ||
    this->map->map[player->y][player->x].phiras < elevation_ritual[player->level - 1][5] ||
    this->map->map[player->y][player->x].thystame < elevation_ritual[player->level - 1][6]) {
        return 1;
    }
    list_players_t *tmp = this->players;
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->player->x == player->x && tmp->player->y == player->y && tmp->player->level == player->level)
            *nb_players += 1;
    }
    dprintf(player->socket, "Elevation underway\n");
    return 0;
}

void level_up_all_on_tile(this_t *this, player_t *player)
{
    list_players_t *tmp = this->players;
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->player->x == player->x && tmp->player->y == player->y) {
            tmp->player->incantation = true;
            tmp->player->level += 1;
            dprintf(tmp->player->socket, "Current level: %d\n", tmp->player->level);
        }
    }
}

void remove_material(this_t *this, player_t *player, int elevation_ritual[7][7])
{
    this->map->map[player->y][player->x].linemate -= elevation_ritual[player->level - 1][1];
    this->map->map[player->y][player->x].deraumere -= elevation_ritual[player->level - 1][2];
    this->map->map[player->y][player->x].sibur -= elevation_ritual[player->level - 1][3];
    this->map->map[player->y][player->x].mendiane -= elevation_ritual[player->level - 1][4];
    this->map->map[player->y][player->x].phiras -= elevation_ritual[player->level - 1][5];
    this->map->map[player->y][player->x].thystame -= elevation_ritual[player->level - 1][6];
}

void create_incantation_events(this_t *this, player_t *player)
{
    list_players_t *tmp = this->players;
    list_players_t *list = NULL;
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->player->x == player->x && tmp->player->y == player->y)
            list = add_element(list, tmp->player, list_len(list));
    }
    send_pic_to_gui(this, player->x, player->y, player->id, list);
}

void incantation(this_t *this, player_t *player, int exec)
{
    if (exec == 0) {
        cmd_ai_t *action = create_action_ai(this, player, "Incantation", (300 / this->freq));
        this->actions = add_element_ai(this->actions, action, list_len_ai(this->actions));
        create_incantation_events(this, player);
        return;
    }

    int nb_players = 0;
    int elevation_ritual[7][7] = {{ 1, 1, 0, 0, 0, 0, 0 }, { 2, 1, 1, 1, 0, 0, 0 }, { 2, 2, 0, 1, 0, 2, 0 }, { 4, 1, 1, 2, 0, 1, 0 },
                                { 4, 1, 2, 1, 3, 0, 0 }, { 6, 1, 2, 3, 0, 1, 0 }, { 6, 2, 2, 2, 2, 2, 1 }};
    // check if player has enough material to level up && if there is enough players on the tile
    list_players_t *tmp = this->players;
    if (check_material(this, player, elevation_ritual, &nb_players) == 1 || nb_players < elevation_ritual[player->level - 1][0]) {
        for (; tmp != NULL; tmp = tmp->next) {
            if (tmp->player->x == player->x && tmp->player->y == player->y) {
                tmp->player->incantation = false;
                dprintf(tmp->player->socket, "ko\n");
            }
        }
        send_pie_to_gui(this, player->x, player->y, "ko");
        return;
    }
    // level up all players on the tile
    level_up_all_on_tile(this, player);
    // remove material from the tile
    remove_material(this, player, elevation_ritual);
    send_pie_to_gui(this, player->x, player->y, "ok");
}