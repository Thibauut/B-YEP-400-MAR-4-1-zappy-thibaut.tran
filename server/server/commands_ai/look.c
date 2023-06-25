/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** look.c
*/

#include "../../include/my.h"

vector2d_t *create_vector(int x, int y)
{
    vector2d_t *vector = malloc(sizeof(vector2d_t));
    vector->x = x;
    vector->y = y;
    return (vector);
}

void update_pos(this_t *this, int *x, int *y)
{
    if (*x < 0)
        *x = *x + this->width;
    if (*y < 0)
        *y = *y + this->height;
    if (*x >= this->width)
        *x = *x - this->width;
    if (*y >= this->height)
        *y = *y - this->height;
}

void positions_north(this_t *this, player_t *player)
{
    int x = player->x, y = player->y, distance = player->level;
    for (int i = 1; i <= distance; i++) {
        for (int j = -i; j <= i; j++) {
            x = player->x + j, y = player->y + i;
            update_pos(this, &x, &y);
            this->tiles_pos = add_element_vector(this->tiles_pos, create_vector(x, y), list_len_vector(this->tiles_pos));
        }
    }
}

void positions_east(this_t *this, player_t *player)
{
    int x = player->x, y = player->y, distance = player->level;
    for (int i = 1; i <= distance; i++) {
        for (int j = -i; j <= i; j++) {
            x = player->x + i, y = player->y + j;
            update_pos(this, &x, &y);
            this->tiles_pos = add_element_vector(this->tiles_pos, create_vector(x, y), list_len_vector(this->tiles_pos));
        }
    }
}

void positions_south(this_t *this, player_t *player)
{
    int x = player->x, y = player->y, distance = player->level;
    for (int i = 1; i <= distance; i++) {
        for (int j = -i; j <= i; j++) {
            x = player->x + j, y = player->y - i;
            update_pos(this, &x, &y);
            this->tiles_pos = add_element_vector(this->tiles_pos, create_vector(x, y), list_len_vector(this->tiles_pos));
        }
    }
}

void positions_west(this_t *this, player_t *player)
{
    int x = player->x, y = player->y, distance = player->level;
    for (int i = 1; i <= distance; i++) {
        for (int j = -i; j <= i; j++) {
            x = player->x - i, y = player->y + j;
            update_pos(this, &x, &y);
            this->tiles_pos = add_element_vector(this->tiles_pos, create_vector(x, y), list_len_vector(this->tiles_pos));
        }
    }
}

void get_tiles_positions(this_t *this, player_t *player)
{
    if (player->o == NORTH) {
        positions_north(this, player);
        return;
    }
    if (player->o == EAST) {
        positions_east(this, player);
        return;
    }
    if (player->o == SOUTH) {
        positions_south(this, player);
        return;
    }
    if (player->o == WEST) {
        positions_west(this, player);
        return;
    }
}

void get_players_positions(this_t *this, player_t *player)
{
    list_players_t *tmp_players = this->players;
    for (; tmp_players; tmp_players = tmp_players->next) {
        if (player->x == tmp_players->player->x && player->y == tmp_players->player->y && player->id != tmp_players->player->id && tmp_players->player->in_team == true)
            this->players_pos = add_element_vector(this->players_pos, create_vector(tmp_players->player->x, tmp_players->player->y), list_len_vector(this->players_pos));
    }
}

char *print_actual_tile(this_t *this, player_t *player, char *str)
{
    list_vector2d_t *tmp_tiles = this->tiles_pos;
    list_vector2d_t *tmp_players = this->players_pos;
    char *content = malloc(sizeof(char *) * 4096);
    content[0] = '\0';
    int count = 0;
    for(; tmp_players; tmp_players = tmp_players->next) {
        if (player->x == tmp_players->vector->x && player->y == tmp_players->vector->y)
            content = my_strcat(content, " player");
    }
    for (int i = 0; i < this->map->map[player->y][player->x]->food; i++)
        content = my_strcat(content, " food");
    for (int i = 0; i < this->map->map[player->y][player->x]->linemate; i++)
        content = my_strcat(content, " linemate");
    for (int i = 0; i < this->map->map[player->y][player->x]->deraumere; i++)
        content = my_strcat(content, " deraumere");
    for (int i = 0; i < this->map->map[player->y][player->x]->sibur; i++)
        content = my_strcat(content, " sibur");
    for (int i = 0; i < this->map->map[player->y][player->x]->mendiane; i++)
        content = my_strcat(content, " mendiane");
    for (int i = 0; i < this->map->map[player->y][player->x]->phiras; i++)
        content = my_strcat(content, " phiras");
    for (int i = 0; i < this->map->map[player->y][player->x]->thystame; i++)
        content = my_strcat(content, " thystame");
    str = my_strcat(str, "[ player");
    str = my_strcat(str, content);
    str = my_strcat(str, ",");
    return (str);
}

void get_tiles_contents(this_t *this, player_t *player)
{
    list_vector2d_t *tmp_tiles = this->tiles_pos;
    list_players_t *tmp_players = this->players;
    char **content = malloc(sizeof(char *) * (list_len_vector(tmp_tiles) + 1));
    int count = 0;
    int index = 0;
    for (; tmp_tiles; tmp_tiles = tmp_tiles->next, index++) {
        content[index] = malloc(sizeof(char) * 4096);
        content[index][0] = '\0';
        for(tmp_players = this->players; tmp_players; tmp_players = tmp_players->next) {
            if (tmp_tiles->vector->x == tmp_players->player->x && tmp_tiles->vector->y == tmp_players->player->y && player->id != tmp_players->player->id && tmp_players->player->in_team == true)
                content[index] = my_strcat(content[index], " player");
        }
        for (int i = 0; i < this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->food; i++)
            content[index] = my_strcat(content[index], " food");
        for (int i = 0; i < this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->linemate; i++)
            content[index] = my_strcat(content[index], " linemate");
        for (int i = 0; i < this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->deraumere; i++)
            content[index] = my_strcat(content[index], " deraumere");
        for (int i = 0; i < this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->sibur; i++)
            content[index] = my_strcat(content[index], " sibur");
        for (int i = 0; i < this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->mendiane; i++)
            content[index] = my_strcat(content[index], " mendiane");
        for (int i = 0; i < this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->phiras; i++)
            content[index] = my_strcat(content[index], " phiras");
        for (int i = 0; i < this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->thystame; i++)
            content[index] = my_strcat(content[index], " thystame");
        if (this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->food <= 0 &&
            this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->linemate <= 0 &&
            this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->deraumere <= 0 &&
            this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->sibur <= 0 &&
            this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->mendiane <= 0 &&
            this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->phiras <= 0 &&
            this->map->map[tmp_tiles->vector->y][tmp_tiles->vector->x]->thystame <= 0)
            content[index] = my_strcat(content[index], ", ");
    }
    content[index] = NULL;
    char *tmp;
    char *FINAL_PRINT = malloc(sizeof(char) * 4096);
    FINAL_PRINT = print_actual_tile(this, player, FINAL_PRINT);
    int i = 0;
    for (; content[i]; i++) {
        tmp = rm_extra_spaces(content[i]);
        content[i] = strdup(tmp);
        FINAL_PRINT = my_strcat(FINAL_PRINT, content[i]);
        if (content[i + 1] != NULL && content[i][0] != ',')
            FINAL_PRINT = my_strcat(FINAL_PRINT, ",");
    }
    FINAL_PRINT = my_strcat(FINAL_PRINT, " ]");
    dprintf(player->socket, "%s\n", FINAL_PRINT);
}

void look(this_t *this, player_t *player, int exec)
{
    if (exec == 0) {
        cmd_ai_t *action = create_action_ai(this, player, "Look", NULL, 7);
        this->actions = add_element_ai(this->actions, action, list_len_ai(this->actions));
        return;
    }
    this->tiles_pos = NULL;
    this->players_pos = NULL;
    get_tiles_positions(this, player);
    get_players_positions(this, player);
    get_tiles_contents(this, player);
}