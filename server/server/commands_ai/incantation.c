/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** incantation.c
*/

#include "../../include/my.h"

int check_material(this_t *this, player_t *player, int elevation_ritual[7][7], int *nb_players)
{
    if (this->map->map[player->y][player->x]->linemate < elevation_ritual[player->level - 1][1] ||
    this->map->map[player->y][player->x]->deraumere < elevation_ritual[player->level - 1][2] ||
    this->map->map[player->y][player->x]->sibur < elevation_ritual[player->level - 1][3] ||
    this->map->map[player->y][player->x]->mendiane < elevation_ritual[player->level - 1][4] ||
    this->map->map[player->y][player->x]->phiras < elevation_ritual[player->level - 1][5] ||
    this->map->map[player->y][player->x]->thystame < elevation_ritual[player->level - 1][6]) {
        return 1;
    }
    list_players_t *tmp = this->players;
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->player->x == player->x && tmp->player->y == player->y && tmp->player->level == player->level) {
            *nb_players += 1;
        }
    }
    return 0;
}

void level_up_all_on_tile(this_t *this, player_t *player)
{
    list_players_t *tmp = this->players;
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->player->x == player->x && tmp->player->y == player->y && tmp->player->level == player->level) {
            tmp->player->incantation = true;
            tmp->player->level += 1;
        }
    }
}

void remove_material(this_t *this, player_t *player, int elevation_ritual[7][7])
{
    this->map->map[player->y][player->x]->linemate -= elevation_ritual[player->level - 1][1];
    this->map->map[player->y][player->x]->deraumere -= elevation_ritual[player->level - 1][2];
    this->map->map[player->y][player->x]->sibur -= elevation_ritual[player->level - 1][3];
    this->map->map[player->y][player->x]->mendiane -= elevation_ritual[player->level - 1][4];
    this->map->map[player->y][player->x]->phiras -= elevation_ritual[player->level - 1][5];
    this->map->map[player->y][player->x]->thystame -= elevation_ritual[player->level - 1][6];
}

void create_incantation_events(this_t *this, player_t *player)
{
    list_players_t *tmp = this->players;
    list_players_t *list = NULL;
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->player->x == player->x && tmp->player->y == player->y && tmp->player->in_team == true)
            list = add_element(list, tmp->player, list_len(list));
    }
    send_pic_to_gui(this, player->x, player->y, player->id, list);
}

void send_end_incantation(this_t *this, player_t *player)
{
    list_players_t *tmp = this->players;
    for (; tmp; tmp = tmp->next) {
        if (tmp->player->x == player->x && tmp->player->y == player->y && tmp->player->in_team == true
        && tmp->player->incantation == true) {
            dprintf(tmp->player->socket, "Current level: %d\n", tmp->player->level);
            tmp->player->incantation = false;
        }
    }
}

int can_incant(this_t *this, player_t *player, int elevation_ritual[7][7], int *nb_players)
{
    // check if player has enough material to level up && if there is enough players on the tile
    list_players_t *tmp = this->players;
    if (check_material(this, player, elevation_ritual, nb_players) == 1 || *nb_players < elevation_ritual[player->level - 1][0]) {
        for (; tmp != NULL; tmp = tmp->next) {
            if (tmp->player->x == player->x && tmp->player->y == player->y && tmp->player->in_team == true) {
                tmp->player->incantation = false;
                dprintf(tmp->player->socket, "ko\n");
            }
            if (tmp->player->is_gui == true && tmp->player->in_team == false)
                send_pie_to_gui(this, player->x, player->y, "ko");
        }
        return 1;
    }
    return 0;
}

void send_permission_to_incant(this_t *this, player_t *player)
{
    list_players_t *tmp = this->players;
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->player->x == player->x && tmp->player->y == player->y && tmp->player->in_team == true) {
            dprintf(tmp->player->socket, "Elevation underway\n");
            tmp->player->incantation = true;
        }
    }
}

void incantation(this_t *this, player_t *player, int exec)
{
    int nb_players = 0;
    int elevation_ritual[7][7] = {{ 1, 1, 0, 0, 0, 0, 0 }, { 2, 1, 1, 1, 0, 0, 0 }, { 2, 2, 0, 1, 0, 2, 0 }, { 4, 1, 1, 2, 0, 1, 0 },
                                { 4, 1, 2, 1, 3, 0, 0 }, { 6, 1, 2, 3, 0, 1, 0 }, { 6, 2, 2, 2, 2, 2, 1 }};
    if (exec == 0) {
        if (can_incant(this, player, elevation_ritual, &nb_players) == 1)
            return;
        cmd_ai_t *action = create_action_ai(this, player, "Incantation", NULL, 300);
        this->actions = add_element_ai(this->actions, action, list_len_ai(this->actions));
        send_permission_to_incant(this, player);
        create_incantation_events(this, player);
        return;
    }
    if (can_incant(this, player, elevation_ritual, &nb_players) == 1)
        return;
    // level up all players on the tile
    level_up_all_on_tile(this, player);
    // remove material from the tile
    remove_material(this, player, elevation_ritual);
    send_end_incantation(this, player);
    send_pie_to_gui(this, player->x, player->y, "ok");
}