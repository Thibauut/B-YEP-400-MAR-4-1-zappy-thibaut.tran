/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** eject.c
*/

#include "../../include/my.h"

void ejection(this_t *this, player_t *player, player_t *player_to_eject)
{
    if (player->o == NORTH) {
        if (player_to_eject->incantation == true)
            player_to_eject->incantation = false;
        player_to_eject->y += 1;
        update_pos(this, &player_to_eject->x, &player_to_eject->y);
        return;
    }
    if (player->o == SOUTH) {
        if (player_to_eject->incantation == true)
            player_to_eject->incantation = false;
        player_to_eject->y -= 1;
        update_pos(this, &player_to_eject->x, &player_to_eject->y);
        return;
    }
    if (player->o == EAST) {
        if (player_to_eject->incantation == true)
            player_to_eject->incantation = false;
        player_to_eject->x += 1;
        update_pos(this, &player_to_eject->x, &player_to_eject->y);
        return;
    }
    if (player->o == WEST) {
        if (player_to_eject->incantation == true)
            player_to_eject->incantation = false;
        player_to_eject->x -= 1;
        update_pos(this, &player_to_eject->x, &player_to_eject->y);
        return;
    }
}

void correct_north(this_t *this, player_t *player, player_t *player_ejected)
{
    int nord = 1, east = 2, sud = 3, west = 4;
    if (player->o == NORTH) {
        if (player_ejected->o == NORTH) {
            dprintf(player_ejected->socket, "Eject: %d\n", sud);
            return;
        }
        if (player_ejected->o == SOUTH) {
            dprintf(player_ejected->socket, "Eject: %d\n", nord);
            return;
        }
        if (player_ejected->o == EAST) {
            dprintf(player_ejected->socket, "Eject: %d\n", east);
            return;
        }
        if (player_ejected->o == WEST) {
            dprintf(player_ejected->socket, "Eject: %d\n", west);
            return;
        }
    }
}

void correct_south(this_t *this, player_t *player, player_t *player_ejected)
{
    int nord = 1, east = 2, sud = 3, west = 4;
    if (player->o == SOUTH) {
        if (player_ejected->o == NORTH) {
            dprintf(player_ejected->socket, "Eject: %d\n", sud);
            return;
        }
        if (player_ejected->o == SOUTH) {
            dprintf(player_ejected->socket, "Eject: %d\n", sud);
            return;
        }
        if (player_ejected->o == EAST) {
            dprintf(player_ejected->socket, "Eject: %d\n", west);
            return;
        }
        if (player_ejected->o == WEST) {
            dprintf(player_ejected->socket, "Eject: %d\n", east);
            return;
        }
    }
}

void correct_west(this_t *this, player_t *player, player_t *player_ejected)
{
    int nord = 1, east = 2, sud = 3, west = 4;
    if (player->o == WEST) {
        if (player_ejected->o == NORTH) {
            dprintf(player_ejected->socket, "Eject: %d\n", east);
            return;
        }
        if (player_ejected->o == SOUTH) {
            dprintf(player_ejected->socket, "Eject: %d\n", west);
            return;
        }
        if (player_ejected->o == EAST) {
            dprintf(player_ejected->socket, "Eject: %d\n", nord);
            return;
        }
        if (player_ejected->o == WEST) {
            dprintf(player_ejected->socket, "Eject: %d\n", sud);
            return;
        }
    }
}

void correct_east(this_t *this, player_t *player, player_t *player_ejected)
{
    int nord = 1, east = 2, sud = 3, west = 4;
    if (player->o == EAST) {
        if (player_ejected->o == NORTH) {
            dprintf(player_ejected->socket, "Eject: %d\n", west);
            return;
        }
        if (player_ejected->o == SOUTH) {
            dprintf(player_ejected->socket, "Eject: %d\n", east);
            return;
        }
        if (player_ejected->o == EAST) {
            dprintf(player_ejected->socket, "Eject: %d\n", sud);
            return;
        }
        if (player_ejected->o == WEST) {
            dprintf(player_ejected->socket, "Eject: %d\n", nord);
            return;
        }
    }
}

void send_correct_dir(this_t *this, player_t *player, player_t *player_ejected)
{
    correct_north(this, player, player_ejected);
    correct_south(this, player, player_ejected);
    correct_west(this, player, player_ejected);
    correct_east(this, player, player_ejected);
    return;
}

list_players_t *get_players_on_tile(this_t *this, player_t *player)
{
    list_players_t *tmp = this->players;
    list_players_t *players_ejected = NULL;
    for (; tmp; tmp = tmp->next) {
        if (tmp->player->x == player->x && tmp->player->y == player->y && tmp->player->id != player->id)
            players_ejected = add_element(players_ejected, tmp->player, list_len(players_ejected));
    }
}

void eject(this_t *this, player_t *player, int exec)
{
    if (exec == 0) {
        cmd_ai_t *action = create_action_ai(this, player, "Eject", NULL, 7);
        this->actions = add_element_ai(this->actions, action, list_len_ai(this->actions));
        return;
    }
    list_players_t *players_ejected = get_players_on_tile(this, player);
    if (list_len(players_ejected) == 0) {
        dprintf(player->socket, "ko\n");
        return;
    }
    for (list_players_t *tmp = players_ejected; tmp; tmp = tmp->next) {
        ejection(this, player, tmp->player);
        //kill eggs
        send_correct_dir(this, player, tmp->player);
    }
    send_pex_to_gui(this, player->id);
    dprintf(player->socket, "ok\n");
}
