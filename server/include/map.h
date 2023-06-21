/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** ressources.h
*/

#pragma once

enum ressources_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
};

typedef struct tile_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} tile_t;

typedef struct map_s {
    float food_density;
    float linemate_density;
    float deraumere_density;
    float sibur_density;
    float mendiane_density;
    float phiras_density;
    float thystame_density;

    int max_food;
    int max_linemate;
    int max_deraumere;
    int max_sibur;
    int max_mendiane;
    int max_phiras;
    int max_thystame;

    enum ressources_e ressources[7];
    tile_t ***map;

} map_t;

