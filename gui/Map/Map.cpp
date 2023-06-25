/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Map.cpp
*/

#include "Map.hpp"
#include <iostream>

Map::Map()
{
}

Map::~Map()
{
}

void Map::drawMap()
{
    std::lock_guard<std::mutex> lock(_mutex);
    int startX = screenWidth / 2;
    int startY = 0;
    int spriteSpacingX = 60 / 2;
    int spriteSpacingY = 50 / 2;
    int renderIndex = 0;
    // std::cout << "SizeHERE: " << _map.size() << std::endl;
    for (size_t i = 0; i < _map.size(); i++) {
        _map.at(i).drawTile(startX, startY, spriteSpacingX, spriteSpacingY, renderIndex);
        renderIndex++;
    }
    renderIndex = 0;
    for (size_t i = 0; i < _map.size(); i++) {
        _map.at(i).drawTiles(renderIndex);
        renderIndex++;
    }
}

void Map::setMap(std::vector<Tile> map)
{
    _map = map;
}

// std::vector<Model> Map::getMap()
// {
//     std::vector<Model> map;
//     for (size_t i = 0; i != _map.size(); i++)
//         map.push_back(_map[i].getModel());
//     return map;
// }

void Map::push(Tile tile)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _map.push_back(tile);
}