/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** commands.c
*/

#include "../include/my.h"

int move_commands(this_t *this, player_t *player)
{
    if (my_strcmp(this->cmd[0], "Forward") == 0) {
        // move_forward(this, player);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "Right") == 0) {
        // move_right(this, player);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "Left") == 0) {
        // move_left(this, player);
        return 0;
    }
    return 1;
}

int action_commands(this_t *this, player_t *player)
{
    if (my_strcmp(this->cmd[0], "Look") == 0) {
        // look(this, player);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "Inventory") == 0) {
        // inventory(this, player);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "Incantation") == 0) {
        // incantation(this, player);
        return 0;
    }

    return 1;
}

int player_commands(this_t *this, player_t *player)
{
    if (my_strcmp(this->cmd[0], "Connect_nbr") == 0) {
        // connect_nbr(this, player);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "Fork") == 0) {
        // fork(this, player);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "Eject") == 0) {
        // eject(this, player);
        return 0;
    }
    return 1;
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

            // send game infos to player
            dprintf(player->socket, "%d\n", tmp->team->max_players - tmp->team->nb_players);
            dprintf(player->socket, "%d %d\n", this->width, this->height);
            return 0;
        }
    }
    return 1;
}

int exec_ai_commands(this_t *this, player_t *player)
{
    printf("cmd: %s\n", this->cmd[0]);
    if ((add_player_to_team(this, player) == 0)) {
        player->in_team = true;
        return 0;
    }
    if (player->in_team == true) {
        if (move_commands(this, player) == 0)
            return 0;
        if (action_commands(this, player) == 0)
            return 0;
        if (player_commands(this, player) == 0)
            return 0;
    }
    return 1;
}

void commands(this_t *this, player_t *player)
{
    if (this->cmd == NULL) {
        dprintf(player->socket, "ko\n");
        return;
    } else if (exec_ai_commands(this, player) == 0)
        return;
    dprintf(player->socket, "ko\n");
}