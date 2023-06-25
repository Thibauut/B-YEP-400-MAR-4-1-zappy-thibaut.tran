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

list_eggs_t *get_eggs_by_team(list_eggs_t *eggs, team_t *team)
{
    list_eggs_t *tmp = eggs;
    list_eggs_t *new = NULL;
    for (; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->egg->team->name, team->name) == 0)
            new = add_element_egg(new, tmp->egg, list_len_egg(new));
    }
    return new;
}

void add_player_by_egg(this_t *this, player_t *player, list_teams_t *tmp)
{
    list_eggs_t *egg_teams = get_eggs_by_team(this->eggs, tmp->team);
    int index = rand() % list_len_egg(egg_teams);
    egg_t *egg = get_element_egg(egg_teams, index);
    tmp->team->nb_players += 1;
    this->nb_clients_egg -= 1;
    player->team = egg->team;
    player->level = 1;
    player->x = egg->x;
    player->y = egg->y;
    player->o = egg->o;
    player->life = egg->life;
    player->id = strdup(egg->id);
    player->incantation = egg->incantation;
    init_inventory(player);
    dprintf(player->socket, "%d\n", (tmp->team->max_players - tmp->team->nb_players));
    dprintf(player->socket, "%d %d\n", this->width, this->height);
    // send_ebo_to_gui(this, egg->id);
    send_edi_to_gui(this, egg->id);
    this->eggs = free_element_at_egg(this->eggs, index);
    pnw(this, player);
}

int add_player_to_team(this_t *this, player_t *player)
{
    list_teams_t *tmp = this->teams;
    for (; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->team->name, this->cmd[0]) == 0) {
            if (((tmp->team->max_players - tmp->team->nb_players)) <= 0)
                return 1;
            if (this->nb_clients_egg <= 0) {
                tmp->team->nb_players += 1;
                player->team = tmp->team;
                player->level = 1;
                player->x = rand() % this->width;
                player->y = rand() % this->height;
                player->o = rand() % 4;
                player->life = 126;
                player->incantation = false;
                init_inventory(player);
                dprintf(player->socket, "%d\n", tmp->team->max_players - tmp->team->nb_players);
                dprintf(player->socket, "%d %d\n", this->width, this->height);
                pnw(this, player);
                return 0;
            }
            if (this->nb_clients_egg > 0) {
                add_player_by_egg(this, player, tmp);
                return 0;
            }
        }
    }
    return 1;
}
