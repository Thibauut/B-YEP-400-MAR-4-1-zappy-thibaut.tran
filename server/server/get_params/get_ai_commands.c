/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** commands.c
*/

#include "../../include/my.h"

int move_commands(this_t *this, player_t *player, int exec)
{
    if (my_strcmp(this->cmd[0], "Forward") == 0) {
        forward(this, player, exec);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "Right") == 0) {
        right(this, player, exec);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "Left") == 0) {
        left(this, player, exec);
        return 0;
    }
    return 1;
}

int object_commands(this_t *this, player_t *player, int exec)
{
    if (my_strcmp(this->cmd[0], "Take") == 0 && my_strcmp(this->cmd[1], "object") == 0) {
        take_object(this, player, exec);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "Set") == 0 && my_strcmp(this->cmd[1], "object") == 0) {
        set_object(this, player, exec);
        return 0;
    }
    return 1;
}

int action_commands(this_t *this, player_t *player, int exec)
{
    if (my_strcmp(this->cmd[0], "Inventory") == 0) {
        inventory(this, player, exec);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "Look") == 0) {
        look(this, player, exec);
        return 0;
    }
    if (my_strcmp(this->cmd[0], "Incantation") == 0) {
        incantation(this, player, exec);
        return 0;
    }
    return 1;
}

int player_commands(this_t *this, player_t *player, int exec)
{
    if (my_strcmp(this->cmd[0], "Connect_nbr") == 0) {
        connect_nbr(this, player);
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

