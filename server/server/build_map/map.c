/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** map.c
*/

#include "../../include/my.h"

void init_density(this_t *this)
{
    this->map->food_density = 0.5;
    this->map->linemate_density = 0.3;
    this->map->deraumere_density = 0.15;
    this->map->sibur_density = 0.1;
    this->map->mendiane_density = 0.1;
    this->map->phiras_density = 0.08;
    this->map->thystame_density = 0.05;
}

void init_max_ressources(this_t *this)
{
    this->map->max_food = this->map->food_density * this->width * this->height;
    this->map->max_linemate = this->map->linemate_density * this->width * this->height;
    this->map->max_deraumere = this->map->deraumere_density * this->width * this->height;
    this->map->max_sibur = this->map->sibur_density * this->width * this->height;
    this->map->max_mendiane = this->map->mendiane_density * this->width * this->height;
    this->map->max_phiras = this->map->phiras_density * this->width * this->height;
    this->map->max_thystame = this->map->thystame_density * this->width * this->height;
}

void pop_ressources(this_t *this, int max, int nb, enum ressources_e ressource)
{
    for (int i = nb, rand_x = 0, rand_y = 0; i < max; i++) {
        rand_x = rand() % this->width;
        rand_y = rand() % this->height;
        if (ressource == FOOD)
            this->map->map[rand_y][rand_x].food++;
        if (ressource == LINEMATE)
            this->map->map[rand_y][rand_x].linemate++;
        if (ressource == DERAUMERE)
            this->map->map[rand_y][rand_x].deraumere++;
        if (ressource == SIBUR)
            this->map->map[rand_y][rand_x].sibur++;
        if (ressource == MENDIANE)
            this->map->map[rand_y][rand_x].mendiane++;
        if (ressource == PHIRAS)
            this->map->map[rand_y][rand_x].phiras++;
        if (ressource == THYSTAME)
            this->map->map[rand_y][rand_x].thystame++;
    }
}

void build_zappy_map(this_t *this)
{
    pop_ressources(this, this->map->max_food, 0, FOOD);
    pop_ressources(this, this->map->max_linemate, 0, LINEMATE);
    pop_ressources(this, this->map->max_deraumere, 0, DERAUMERE);
    pop_ressources(this, this->map->max_sibur, 0, SIBUR);
    pop_ressources(this, this->map->max_mendiane, 0, MENDIANE);
    pop_ressources(this, this->map->max_phiras, 0, PHIRAS);
    pop_ressources(this, this->map->max_thystame, 0, THYSTAME);
}

void init_zappy_map(this_t *this)
{
    this->map = malloc(sizeof(map_t));
    init_density(this);
    init_max_ressources(this);
    int y = 0, x = 0;
    this->map->map = malloc(sizeof(tile_t *) * this->height + 1);
    for (; y < this->height; y++) {
        this->map->map[y] = malloc(sizeof(tile_t) * this->width + 1);
        for (x = 0; x < this->width; x++) {
            this->map->map[y][x].food = 0;
            this->map->map[y][x].linemate = 0;
            this->map->map[y][x].deraumere = 0;
            this->map->map[y][x].sibur = 0;
            this->map->map[y][x].mendiane = 0;
            this->map->map[y][x].phiras = 0;
            this->map->map[y][x].thystame = 0;
        }
    }
    this->map->map[y] = NULL;
    build_zappy_map(this);
}

int get_max_ressources(this_t *this, enum ressources_e type)
{
    int max = 0;
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            if (type == FOOD)
                max += this->map->map[y][x].food;
            if (type == LINEMATE)
                max += this->map->map[y][x].linemate;
            if (type == DERAUMERE)
                max += this->map->map[y][x].deraumere;
            if (type == SIBUR)
                max += this->map->map[y][x].sibur;
            if (type == MENDIANE)
                max += this->map->map[y][x].mendiane;
            if (type == PHIRAS)
                max += this->map->map[y][x].phiras;
            if (type == THYSTAME)
                max += this->map->map[y][x].thystame;
        }
    }
    return (max);
}

void refill_map(this_t *this)
{
    int current_size[7];
    current_size[0] = get_max_ressources(this, FOOD);
    current_size[1] = get_max_ressources(this, LINEMATE);
    current_size[2] = get_max_ressources(this, DERAUMERE);
    current_size[3] = get_max_ressources(this, SIBUR);
    current_size[4] = get_max_ressources(this, MENDIANE);
    current_size[5] = get_max_ressources(this, PHIRAS);
    current_size[6] = get_max_ressources(this, THYSTAME);
    if (current_size[0] < this->map->max_food)
        pop_ressources(this, this->map->max_food - current_size[0], 0, FOOD);
    if (current_size[1] < this->map->max_linemate)
        pop_ressources(this, this->map->max_linemate - current_size[1], 0, LINEMATE);
    if (current_size[2] < this->map->max_deraumere)
        pop_ressources(this, this->map->max_deraumere - current_size[2], 0, DERAUMERE);
    if (current_size[3] < this->map->max_sibur)
        pop_ressources(this, this->map->max_sibur - current_size[3], 0, SIBUR);
    if (current_size[4] < this->map->max_mendiane)
        pop_ressources(this, this->map->max_mendiane - current_size[4], 0, MENDIANE);
    if (current_size[5] < this->map->max_phiras)
        pop_ressources(this, this->map->max_phiras - current_size[5], 0, PHIRAS);
    if (current_size[6] < this->map->max_thystame)
        pop_ressources(this, this->map->max_thystame - current_size[6], 0, THYSTAME);
}
