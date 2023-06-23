/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** Map.hpp
*/

#pragma once

#include "../Utils/Global.hpp"
#include "../tile/Tile.hpp"
// #include "../requests/Client.hpp"
#include "../../dependencies/json.hpp"
#include "../items/Food.hpp"
#include "../items/Deraumere.hpp"
#include "../items/Linemate.hpp"
#include "../items/Sibur.hpp"
#include "../items/Mendiane.hpp"
#include "../items/Phiras.hpp"
#include "../items/Thystame.hpp"
// #include "../Utils/ThreadTool.hpp"

using json = nlohmann::json;

class Map {
    public:
        Map();
        ~Map();

        void drawMap();
        void setMap(std::vector<Tile> map);

        // std::vector<Model> getMap();

        void push(Tile tile);

        std::vector<Tile> _map;
    private:
        std::mutex _mutex;
};