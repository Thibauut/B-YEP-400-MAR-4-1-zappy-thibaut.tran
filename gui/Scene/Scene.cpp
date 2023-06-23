/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Scene.cpp
*/

#include "Scene.hpp"
#include <iostream>

Scene::Scene()
{
}

Scene::~Scene()
{
}

std::vector<Player> Scene::getPlayers()
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _players;
}

void Scene::setPlayers(std::vector<Player> players)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _players = players;
}

void Scene::addPlayer(Player &player)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _players.push_back(player);
}

void Scene::removePlayer(Player &player)
{
    std::lock_guard<std::mutex> lock(_mutex);
    for (size_t i = 0; i < _players.size(); i++) {
        if (_players[i].getName() == player.getName())
            _players.erase(_players.begin() + i);
    }
}

void Scene::drawPlayers(Texture2D texture)
{
    for (size_t i = 0; i < _players.size(); i++) {
        // Vector2 pos = _players[i].getPosition();
        // pos.x = (pos.x * (screenWidth / width_map));
        // pos.y = (pos.y * (screenHeight / height_map));
        // if (_players[i].getOrientation() == 0)
        //     DrawTexturePro(texture, pos.x, pos.y, 0, WHITE);
        // if (_players[i].getOrientation() == 1)
        //     DrawTexturePro(texture, pos.x, pos.y, 0, WHITE);
        // if (_players[i].getOrientation() == 2)
        //     DrawTexturePro(texture, pos.x, pos.y, 0, WHITE);
        // if (_players[i].getOrientation() == 3)
        //     DrawTexturePro(texture, pos.x, pos.y, 0, WHITE);
        _players[i].draw(texture);
    }
}

void Scene::setBase(Texture2D base)
{
    _base = base;
}

Texture2D Scene::getBase() const
{
    return _base;
}

void Scene::drawBase() const
{
    DrawTexture(_base, 0.0f, 0.0f, WHITE);
}

int Scene::getPlayerById(std::string id) const
{
    for (size_t i = 0; i < _players.size(); i++) {
        if (_players[i].getName() == id)
            return i;
    }
    return -1;
}