/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** inventory.c
*/

#include "../../include/my.h"

void inventory(this_t *this, player_t *player, int exec)
{
    if (exec == 0) {
        cmd_ai_t *action = create_action_ai(this, player, "Inventory", 1);
        this->actions = add_element_ai(this->actions, action, list_len_ai(this->actions));
        return;
    }
    printf("Inventory done by %s\n", player->id);
}