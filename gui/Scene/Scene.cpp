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
    std::lock_guard<std::mutex> lock(_mutexPlayer);
    return _players;
}

void Scene::setPlayers(std::vector<Player> players)
{
    std::lock_guard<std::mutex> lock(_mutexPlayer);
    _players = players;
}

void Scene::addPlayer(Player &player)
{
    std::lock_guard<std::mutex> lock(_mutexPlayer);
    _players.push_back(player);
}

void Scene::removePlayer(int pos)
{
    std::lock_guard<std::mutex> lock(_mutexPlayer);
    _players.erase(_players.begin() + pos);
}

void Scene::isIncantingPlayer(std::string id, bool isIncanting)
{
    std::lock_guard<std::mutex> lock(_mutexPlayer);
    int i = getPlayerById(id);
    _players.at(i).isIncanting(isIncanting);
}

void Scene::drawPlayers(Texture2D texture, Texture2D incantation)
{
    std::lock_guard<std::mutex> lock(_mutexPlayer);
    for (size_t i = 0; i < _players.size(); i++) {
        _players.at(i).draw(texture, incantation);
    }
}

void Scene::setPositionPlayer(std::string id, Vector2 pos)
{
    std::lock_guard<std::mutex> lock(_mutexPlayer);
    int i = getPlayerById(id);
    _players.at(i).setPosition(pos);
}

void Scene::setOrientationPlayer(std::string id, int orientation)
{
    std::lock_guard<std::mutex> lock(_mutexPlayer);
    int i = getPlayerById(id);
    _players.at(i).setOrientation(orientation);
}

void Scene::setLevelPlayer(std::string id, int level)
{
    std::lock_guard<std::mutex> lock(_mutexPlayer);
    int i = getPlayerById(id);
    _players.at(i).setLevel(level);
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
        if (_players.at(i).getName() == id)
            return i;
    }
    return -1;
}

std::vector<Egg> Scene::getEggs()
{
    std::lock_guard<std::mutex> lock(_mutexEgg);
    return _eggs;
}

void Scene::setEggs(std::vector<Egg> eggs)
{
    std::lock_guard<std::mutex> lock(_mutexEgg);
    _eggs = eggs;
}

void Scene::addEgg(Egg &egg)
{
    std::lock_guard<std::mutex> lock(_mutexEgg);
    _eggs.push_back(egg);
}

void Scene::removeEgg(int eggPos)
{
    std::lock_guard<std::mutex> lock(_mutexEgg);
    _eggs.erase(_eggs.begin() + eggPos);
}

void Scene::drawEggs(Texture2D texture)
{
    std::lock_guard<std::mutex> lock(_mutexEgg);
    for (size_t i = 0; i < _eggs.size(); i++) {
        _eggs.at(i).draw(texture);
    }
}

void Scene::setPositionEgg(std::string id, Vector2 pos)
{
    std::lock_guard<std::mutex> lock(_mutexEgg);
    int i = getEggById(id);
    _eggs.at(i).setPosition(pos);
}

int Scene::getEggById(std::string id) const
{
    for (size_t i = 0; i < _eggs.size(); i++) {
        if (_eggs.at(i).getId() == id)
            return i;
    }
    return -1;
}