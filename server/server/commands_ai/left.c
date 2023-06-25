/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** left.c
*/

#include "../../include/my.h"

void set_direction_left(player_t *player, int orientation)
{
    if (orientation == NORTH) {
        player->o = WEST;
        return;
    }
    if (orientation == EAST) {
        player->o = SOUTH;
        return;
    }
    if (orientation == SOUTH) {
        player->o = WEST;
        return;
    }
    if (orientation == WEST) {
        player->o = SOUTH;
        return;
    }
}

void left(this_t *this, player_t *player, int exec)
{
    if (exec == 0) {
        cmd_ai_t *action = create_action_ai(this, player, "Left", NULL, 7);
        this->actions = add_element_ai(this->actions, action, list_len_ai(this->actions));
        return;
    }
    set_direction_left(player, player->o);
    dprintf(player->socket, "ok\n");
}
