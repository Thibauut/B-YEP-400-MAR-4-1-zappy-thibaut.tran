/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** forward.c
*/

#include "../../include/my.h"

void handle_borders(this_t *this, player_t *player)
{
    if (player->x < 0)
        player->x = player->x + this->width;
    if (player->y < 0)
        player->y = player->y + this->height;
    if (player->x >= this->width)
        player->x = player->x - this->width;
    if (player->y >= this->height)
        player->y = player->y - this->height;
}

void forward(this_t *this, player_t *player, int exec)
{
    if (exec == 0) {
        cmd_ai_t *action = create_action_ai(this, player, "Forward", (7 / this->freq));
        this->actions = add_element_ai(this->actions, action, list_len_ai(this->actions));
        return;
    }
    vector2d_t new_pos[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    player->x += new_pos[player->o].x;
    player->y += new_pos[player->o].y;
    handle_borders(this, player);
    printf("position: %d %d\n", player->x, player->y);
    dprintf(player->socket, "ok\n");
}
