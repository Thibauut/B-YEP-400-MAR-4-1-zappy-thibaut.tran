/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Egg.cpp
*/

#include "Egg.hpp"

Egg::Egg()
{
    _id = "";
}

Egg::Egg(std::string id)
{
    _id = id;
}

Egg::~Egg()
{
}

void Egg::draw(Texture2D texture)
{
    DrawTextureEx(texture, _position, 0, 0.03f, WHITE);
}

void Egg::setPosition(Vector2 position)
{
    int renderIndex = (position.y * (width_map)) + position.x;
    _position.x = (screenWidth / 2) + (renderIndex % (width_map)) * (30) - (renderIndex / (width_map)) * 30;
    _position.y = (renderIndex % (height_map)) * 25 + (renderIndex / (height_map)) * 25;
}

Vector2 Egg::getPosition() const
{
    return _position;
}

void Egg::setId(std::string id)
{
    _id = id;
}

std::string Egg::getId() const
{
    return _id;
}
