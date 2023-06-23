/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** ThreadTool.hpp
*/

#pragma once

#include <pthread.h>
#include "../requests/Client.hpp"
#include "../tile/Tile.hpp"
#include "../Map/Map.hpp"

typedef struct {
    double progress;
    bool loaded;
    Client *client;
    Map &map;
} LoadingState;

typedef struct {
    std::string id;
    Vector2 position;
    int level;
    float oriantation;
    std::string team;
    Client *client;
} PlayerState;