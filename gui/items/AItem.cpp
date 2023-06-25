/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** AItem.cpp
*/

#include "AItem.hpp"

// : _anim(Rectangle{0, 0, 115, 115}, 10, Vector2{0, 0})
AItem::AItem()
{
    _texture = LoadTexture("gui/models/meat.png");
    _position = {0, 0};
}

AItem::AItem(Vector2 position)
{
    _texture = LoadTexture("gui/models/meat.png");
    _position = position;
}

AItem::~AItem()
{
    UnloadTexture(_texture);
}

void AItem::drawItem()
{
    DrawTexture(_texture, _position.x, _position.y, WHITE);
    // _anim.draw(_texture);
}

void AItem::setItemPosition(Vector2 position)
{
    _position = position;
}

Vector2 AItem::getItemPosition() const
{
    return _position;
}

std::string AItem::getName() const
{
    return "unknow item";
}

Texture2D AItem::getTexture() const
{
    return _texture;
}

int AItem::getId() const
{
    return 0;
}
