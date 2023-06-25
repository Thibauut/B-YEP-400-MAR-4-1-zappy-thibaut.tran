/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** broadcast.c
*/

#include "../../include/my.h"

enum direction {NORTH_, EAST_, SOUTH_, WEST_, SOUTH_EAST, SOUTH_WEST, NORTH_EAST, NORTH_WEST};


int get_direction(this_t *this, player_t *player, player_t *player2)
{
    float pente = 0;
    if (player->x == player2->x && player->y == player2->y)
        return 84;
    if (player->x != player2->x)
        pente = ((float)player->y - (float)player2->y) / ((float)player->x - (float)player2->x);
    if (player->x == player2->x && player->y > player2->y || (pente > 3 || pente < -3))
        return NORTH_;
    if ((player->x == player2->x && player->y < player2->y) || (pente > 3 || pente < -3))
        return (SOUTH_);
    if ((player->x > player2->x) && (pente > -0.5 && pente <= 0.5))
        return (WEST_);
    if ((player->x < player2->x) && (pente > -0.5 && pente <= 0.5))
        return (EAST_);
    if ((player->x > player2->x) && (pente > 0.5 && pente <= 3))
        return (NORTH_WEST);
    if ((player->x < player2->x) && (pente <= -0.5 && pente > -3))
        return (NORTH_EAST);
    if ((player->x > player2->x) && (pente <= -0.5 && pente > -3))
        return (SOUTH_WEST);
    if ((player->x < player2->x) && (pente > 0.5 && pente <= 3))
        return (SOUTH_EAST);
}

int convert_north_(int dir,  player_t *player2)
{
    if (player2->o == NORTH_ && dir == NORTH_)
        return SOUTH_;
    if (player2->o == SOUTH_ && dir == NORTH_)
        return NORTH_;
    if (player2->o == EAST_ && dir == NORTH_)
        return EAST_;
    if (player2->o == WEST_ && dir == NORTH_)
        return WEST_;
    return 84;
}

int convert_south_(int dir,  player_t *player2)
{
    if (player2->o == NORTH_ && dir == SOUTH_)
        return NORTH_;
    if (player2->o == SOUTH_ && dir == SOUTH_)
        return SOUTH_;
    if (player2->o == EAST_ && dir == SOUTH_)
        return WEST_;
    if (player2->o == WEST_ && dir == SOUTH_)
        return EAST_;
    return 84;
}

int convert_east_(int dir,  player_t *player2)
{
    if (player2->o == NORTH_ && dir == EAST_)
        return EAST_;
    if (player2->o == SOUTH_ && dir == EAST_)
        return WEST_;
    if (player2->o == EAST_ && dir == EAST_)
        return SOUTH_;
    if (player2->o == WEST_ && dir == EAST_)
        return NORTH_;
    return 84;
}

int convert_west_(int dir,  player_t *player2)
{
    if (player2->o == NORTH_ && dir == WEST_)
        return WEST_;
    if (player2->o == SOUTH_ && dir == WEST_)
        return EAST_;
    if (player2->o == EAST_ && dir == WEST_)
        return NORTH_;
    if (player2->o == WEST_ && dir == WEST_)
        return SOUTH_;
    return 84;
}

int convert_south_east(int dir, player_t *player2)
{
    if (player2->o == NORTH_ && dir == SOUTH_EAST)
        return NORTH_WEST;
    if (player2->o == SOUTH_ && dir == SOUTH_EAST)
        return SOUTH_WEST;
    if (player2->o == EAST_ && dir == SOUTH_EAST)
        return SOUTH_WEST;
    if (player2->o == WEST_ && dir == SOUTH_EAST)
        return NORTH_EAST;
    return 84;
}

int convert_south_west(int dir, player_t *player2)
{
    if (player2->o == NORTH_ && dir == SOUTH_WEST)
        return NORTH_EAST;
    if (player2->o == SOUTH_ && dir == SOUTH_WEST)
        return SOUTH_EAST;
    if (player2->o == EAST_ && dir == SOUTH_WEST)
        return NORTH_WEST;
    if (player2->o == WEST_ && dir == SOUTH_WEST)
        return SOUTH_WEST;
    return 84;
}

int convert_north_east(int dir, player_t *player2)
{
    if (player2->o == NORTH_ && dir == NORTH_EAST)
        return SOUTH_WEST;
    if (player2->o == SOUTH_ && dir == NORTH_EAST)
        return NORTH_EAST;
    if (player2->o == EAST_ && dir == NORTH_EAST)
        return SOUTH_EAST;
    if (player2->o == WEST_ && dir == NORTH_EAST)
        return NORTH_WEST;
    return 84;
}

int convert_north_west(int dir, player_t *player2)
{
    if (player2->o == NORTH_ && dir == NORTH_WEST)
        return SOUTH_EAST;
    if (player2->o == SOUTH_ && dir == NORTH_WEST)
        return NORTH_WEST;
    if (player2->o == EAST_ && dir == NORTH_WEST)
        return NORTH_EAST;
    if (player2->o == WEST_ && dir == NORTH_WEST)
        return SOUTH_WEST;
    return 84;
}

int convert_dir_with_orientation(this_t *this, int dir, player_t *player, player_t *player2)
{
    int final_dir = 0;
    printf("dir %d & dirPlayer %d\n", dir, player2->o);
    if (final_dir = convert_north_(dir, player2) != 84)
        return final_dir;
    if (final_dir = convert_south_(dir, player2) != 84)
        return final_dir;
    if (final_dir = convert_east_(dir, player2) != 84)
        return final_dir;
    if (final_dir = convert_west_(dir, player2) != 84)
        return final_dir;
    if (final_dir = convert_south_east(dir, player2) != 84)
        return final_dir;
    if (final_dir = convert_south_west(dir, player2) != 84)
        return final_dir;
    if (final_dir = convert_north_east(dir, player2) != 84)
        return final_dir;
    if (final_dir = convert_north_west(dir, player2) != 84)
        return final_dir;
}


void broadcast(this_t *this, player_t *player, int exec)
{
    if (exec == 0) {
        cmd_ai_t *action = create_action_ai(this, player, "Broadcast", this->cmd[1],  7);
        this->actions = add_element_ai(this->actions, action, list_len_ai(this->actions));
        return;
    }
    if (this->cmd[1] == NULL) {
        dprintf(player->socket, "ko\n");
        return;
    }
    int direction = 0, final_direction = 0;
    list_players_t *tmp = this->players;
    for (; tmp; tmp = tmp->next) {
        if (tmp->player->is_gui == false && tmp->player->in_team == true && my_strcmp(tmp->player->id, player->id) != 0) {
            direction = get_direction(this, player, tmp->player);
            final_direction = convert_dir_with_orientation(this, direction, player, tmp->player);
            if (direction == 84) {
                send_pbc_to_gui(this, player->id, this->cmd[1]);
                dprintf(tmp->player->socket, "message %s\n", this->cmd[1]);
            }
            else {
                printf("pos x = %d, pos y = %d\n", player->x, player->y);
                printf("pos2 x = %d, pos2 y = %d\n", tmp->player->x, tmp->player->y);
                dprintf(tmp->player->socket, "message %s %d\n", this->cmd[1], final_direction + 1);
            }
        }
    }
    send_pbc_to_gui(this, player->id, this->cmd[1]);
    dprintf(player->socket, "ok\n");
}