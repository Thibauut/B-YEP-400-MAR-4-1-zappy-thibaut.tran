/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** handle_player.c
*/

#include "../include/my.h"

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

cmd_ai_t *create_action(this_t *this, player_t *player, char *cmd)
{
    cmd_ai_t *new_action = malloc(sizeof(cmd_ai_t));
    new_action->cmd = strdup(cmd);
    new_action->time_exec = 126 / this->freq;
    new_action->current_time = this->current_time;
    new_action->uuid = player->id;
    return (new_action);
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

            init_inventory(player);
            cmd_ai_t *new_action = create_action(this, player, "Life");
            this->actions = add_element_ai(this->actions, new_action, list_len_ai(this->actions));

            dprintf(player->socket, "%d\n", tmp->team->max_players - tmp->team->nb_players);
            dprintf(player->socket, "%d %d\n", this->width, this->height);
            pnw(this, player);
            return 0;
        }
    }
    return 1;
}
