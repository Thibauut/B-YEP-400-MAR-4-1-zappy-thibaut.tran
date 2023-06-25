/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** set_object.c
*/

#include "../../include/my.h"

int object_to_set_food(this_t *this, player_t *player, int *ret)
{
    char *obj = strdup(this->cmd[1]);
    if (my_strcmp(obj, "food") == 0) {
        if (player->inventory->food <= 0) {
            dprintf(player->socket, "ko\n");
            return 1;
        }
        player->inventory->food -= 1;
        this->map->map[player->y][player->x]->food += 1;
        // send_pdr_to_gui(this, player->id, 0);
        return 0;
    }
    *ret += 1;
    return 0;
}

int object_to_set_linemate(this_t *this, player_t *player, int *ret)
{
    char *obj = strdup(this->cmd[1]);
    if (my_strcmp(obj, "linemate") == 0) {
        if (player->inventory->linemate <= 0) {
            dprintf(player->socket, "ko\n");
            return 1;
        }
        player->inventory->linemate -= 1;
        this->map->map[player->y][player->x]->linemate += 1;
        // send_pdr_to_gui(this, player->id, 1);
        return 0;
    }
    *ret += 1;
    return 0;
}

int objet_to_set_deraumere(this_t *this, player_t *player, int *ret)
{
    char *obj = strdup(this->cmd[1]);
    if (my_strcmp(obj, "deraumere") == 0) {
        if (player->inventory->deraumere <= 0) {
            dprintf(player->socket, "ko\n");
            return 1;
        }
        player->inventory->deraumere -= 1;
        this->map->map[player->y][player->x]->deraumere += 1;
        // send_pdr_to_gui(this, player->id, 2);
        return 0;
    }
    *ret += 1;
    return 0;
}

int object_to_set_sibur(this_t *this, player_t *player, int *ret)
{
    char *obj = strdup(this->cmd[1]);
    if (my_strcmp(obj, "sibur") == 0) {
        if (player->inventory->sibur <= 0) {
            dprintf(player->socket, "ko\n");
            return 1;
        }
        player->inventory->sibur -= 1;
        this->map->map[player->y][player->x]->sibur += 1;
        // send_pdr_to_gui(this, player->id, 3);
        return 0;
    }
    *ret += 1;
    return 0;
}

int object_to_set_mendiane(this_t *this, player_t *player, int *ret)
{
    char *obj = strdup(this->cmd[1]);
    if (my_strcmp(obj, "mendiane") == 0) {
        if (player->inventory->mendiane <= 0) {
            dprintf(player->socket, "ko\n");
            return 1;
        }
        player->inventory->mendiane -= 1;
        this->map->map[player->y][player->x]->mendiane += 1;
        // send_pdr_to_gui(this, player->id, 4);
        return 0;
    }
    *ret += 1;
    return 0;
}

int object_to_set_phiras(this_t *this, player_t *player, int *ret)
{
    char *obj = strdup(this->cmd[1]);
    if (my_strcmp(obj, "phiras") == 0) {
        if (player->inventory->phiras <= 0) {
            dprintf(player->socket, "ko\n");
            return 1;
        }
        player->inventory->phiras -= 1;
        this->map->map[player->y][player->x]->phiras += 1;
        // send_pdr_to_gui(this, player->id, 5);
        return 0;
    }
    *ret += 1;
    return 0;
}

int object_to_set_thystame(this_t *this, player_t *player, int *ret)
{
    char *obj = strdup(this->cmd[1]);
    if (my_strcmp(obj, "thystame") == 0) {
        if (player->inventory->thystame <= 0) {
            dprintf(player->socket, "ko\n");
            return 1;
        }
        player->inventory->thystame -= 1;
        this->map->map[player->y][player->x]->thystame += 1;
        // send_pdr_to_gui(this, player->id, 6);
        return 0;
    }
    *ret += 1;
    return 0;
}

void set_object(this_t *this, player_t *player, int exec)
{
    if (exec == 0) {
        cmd_ai_t *action = create_action_ai(this, player, "Set", this->cmd[1], 7);
        this->actions = add_element_ai(this->actions, action, list_len_ai(this->actions));
        return;
    }
    if (this->cmd[1] == NULL) {
        dprintf(player->socket, "ko\n");
        return;
    }
    int ret = 0;
    if (object_to_set_food(this, player, &ret) == 1)
        return;
    if (object_to_set_linemate(this, player, &ret) == 1)
        return;
    if (objet_to_set_deraumere(this, player, &ret) == 1)
        return;
    if (object_to_set_sibur(this, player, &ret) == 1)
        return;
    if (object_to_set_mendiane(this, player, &ret) == 1)
        return;
    if (object_to_set_phiras(this, player, &ret) == 1)
        return;
    if (object_to_set_thystame(this, player, &ret) == 1)
        return;
    if (ret == 7) {
        dprintf(player->socket, "ko\n");
        return;
    }
    dprintf(player->socket, "ok\n");
}
