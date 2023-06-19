/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** eject.c
*/

#include "../../include/my.h"

void eject(this_t *this, player_t *player, int exec)
{
    if (exec == 0) {
        cmd_ai_t *action = create_action_ai(this, player, "Eject", (7 / this->freq));
        this->actions = add_element_ai(this->actions, action, list_len_ai(this->actions));
        return;
    }
    dprintf(player->socket, "ok\n");
}

//BROADCAST
//EJECT
//EGGS
