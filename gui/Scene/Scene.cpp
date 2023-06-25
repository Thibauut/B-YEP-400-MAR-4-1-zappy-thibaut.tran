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
    std::unique_lock<std::mutex> lock(_mutexPlayer);
    return _players;
}

void Scene::setPlayers(std::vector<Player> players)
{
    std::unique_lock<std::mutex> lock(_mutexPlayer);
    _players = players;
}

void Scene::addPlayer(Player &player)
{
    std::unique_lock<std::mutex> lock(_mutexPlayer);
    _players.push_back(player);
}

void Scene::removePlayer(int pos)
{
    std::unique_lock<std::mutex> lock(_mutexPlayer);
    _players.erase(_players.begin() + pos);
}

void Scene::isIncantingPlayer(std::string id, bool isIncanting)
{
    std::unique_lock<std::mutex> lock(_mutexPlayer);
    int i = getPlayerById(id);
    _players.at(i).isIncanting(isIncanting);
}

std::string Scene::getPlayerName(size_t pos)
{
    std::unique_lock<std::mutex> lock(_mutexPlayer);
    if (pos >= _players.size())
        return "";
    return _players.at(pos).getName();
}

std::vector<AItem *> Scene::getInventoryPlayer(std::string id)
{
    std::unique_lock<std::mutex> lock(_mutexPlayer);
    int i = getPlayerById(id);
    return _players.at(i).getInventory();
}

std::string Scene::isPlayerAtPosition(Vector2 position)
{
    std::unique_lock<std::mutex> lock(_mutexPlayer);
    for (size_t i = 0; i < _players.size(); i++) {
        if (_players.at(i).getPosition().x == position.x && _players.at(i).getPosition().y == position.y)
            return _players.at(i).getName();
    }
    return "";
}

void Scene::setInventoryPlayer(std::string id, std::vector<AItem *> inventory)
{
    std::unique_lock<std::mutex> lock(_mutexPlayer);
    int i = getPlayerById(id);
    _players.at(i).setInventory(inventory);
}

void Scene::drawPlayers(Texture2D texture, Texture2D incantation)
{
    std::unique_lock<std::mutex> lock(_mutexPlayer);
    for (size_t i = 0; i < _players.size(); i++) {
        _players.at(i).draw(texture, incantation);
    }
}

void Scene::setPositionPlayer(std::string id, Vector2 pos)
{
    std::unique_lock<std::mutex> lock(_mutexPlayer);
    int i = getPlayerById(id);
    _players.at(i).setPosition(pos);
}

void Scene::setOrientationPlayer(std::string id, int orientation)
{
    std::unique_lock<std::mutex> lock(_mutexPlayer);
    int i = getPlayerById(id);
    _players.at(i).setOrientation(orientation);
}

void Scene::setLevelPlayer(std::string id, int level)
{
    std::unique_lock<std::mutex> lock(_mutexPlayer);
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

int Scene::getPlayerById(std::string id)
{
    size_t i = 0;
    for (; i < _players.size(); i++) {
        if (_players.at(i).getName() == id)
            return i;
    }
    std::cout << "WARNING " << "Player " << id << " does not exist" << std::endl;
    // exit(84);
    return 0;
}

std::vector<Egg> Scene::getEggs()
{
    std::unique_lock<std::mutex> lock(_mutexEgg);
    return _eggs;
}

void Scene::setEggs(std::vector<Egg> eggs)
{
    std::unique_lock<std::mutex> lock(_mutexEgg);
    _eggs = eggs;
}

void Scene::addEgg(Egg &egg)
{
    std::unique_lock<std::mutex> lock(_mutexEgg);
    _eggs.push_back(egg);
}

void Scene::removeEgg(int eggPos)
{
    std::unique_lock<std::mutex> lock(_mutexEgg);
    _eggs.erase(_eggs.begin() + eggPos);
    std::cout << "EGG REMOVED AT " << eggPos << std::endl;
}

void Scene::drawEggs(Texture2D texture)
{
    std::unique_lock<std::mutex> lock(_mutexEgg);
    for (size_t i = 0; i < _eggs.size(); i++) {
        _eggs.at(i).draw(texture);
    }
}

void Scene::setPositionEgg(std::string id, Vector2 pos)
{
    std::unique_lock<std::mutex> lock(_mutexEgg);
    int i = getEggById(id);
    _eggs.at(i).setPosition(pos);
}

int Scene::getEggById(std::string id)
{
    for (size_t i = 0; i < _eggs.size(); i++) {
        if (_eggs.at(i).getId() == id)
            return i;
    }
    return 0;
}