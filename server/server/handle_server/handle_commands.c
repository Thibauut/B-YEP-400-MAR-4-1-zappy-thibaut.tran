/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** handle_commands.c
*/

#include "../../include/my.h"

void commands(this_t *this, player_t *player)
{
    if (this->cmd == NULL) {
        dprintf(player->socket, "ko\n");
        return;
    } else if (get_ai_commands(this, player) == 0)
        return;
    else if (exec_gui_commands(this, player) == 0)
        return;
    dprintf(player->socket, "ko\n");
}
